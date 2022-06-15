#ifndef _CPIGJanela_
#define _CPIGJanela_

#include "CPIGCamera.h"

class CPIGJanela{

private:

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *textFundo;
int contFPS,lastFPS;
PIGTimer timerFPS;
PIGCor corFundo;
int altura,largura;
SDL_Point pos;
int id;
int modo;
bool fechada;
float opacidade;
string titulo;
SDL_Rect block;
PIGCamera cameraMovel,cameraFixa;
SDL_sem *semRender;
bool fixo;

public:

CPIGJanela(string tituloJanela, int idJanela, int altTela, int largTela){
    id = idJanela;
    titulo = tituloJanela;
    altura = altTela;
    largura = largTela;
    window = SDL_CreateWindow( tituloJanela.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, largura, altura, SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL );
    if( window == NULL ){
        printf( "Janela %d nao pode ser criada! Erro da SDL: %s\n",id, SDL_GetError() );
    }else{
        //handler = SDL_GetWindowID(window);
        //printf("Meu id %d meu handler %d\n",idJanela,handler);
        SDL_GetWindowPosition(window,&pos.x,&pos.y);
        SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_TARGETTEXTURE);
        corFundo = PRETO;
        contFPS = lastFPS = 0;
        timerFPS = new CPIGTimer(false);
        SDL_SetRenderDrawColor( renderer, corFundo.r, corFundo.g, corFundo.b, corFundo.a );
        SDL_SetRenderDrawBlendMode(renderer,SDL_BLENDMODE_BLEND);
        fechada = false;
        modo = PIG_JANELA_NORMAL;
        cameraMovel = new CPIGCamera(altTela,largTela);
        cameraFixa = new CPIGCamera(altTela,largTela);
        fixo = true;
    }

    opacidade = 1.0f;
    textFundo = NULL;
    block = {0,0,-1,-1};
    semRender = SDL_CreateSemaphore(1);
}

~CPIGJanela(){
    delete timerFPS;
    SDL_DestroySemaphore(semRender);
    SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    delete cameraMovel;
    delete cameraFixa;
}

SDL_Window *GetWindow(){
    return window;
}

SDL_Renderer *GetRenderer(){
    return renderer;
}

inline PIGCamera GetCamera(){
    if (fixo) return cameraFixa;
    return cameraMovel;
}

void PreparaCameraFixa(){
    fixo = true;
    SDL_RenderSetLogicalSize(renderer,largura,altura);
}

void PreparaCameraMovel(){
    fixo = false;
    double pan = cameraMovel->GetAfastamento();
    SDL_RenderSetLogicalSize(renderer,pan*largura,pan*altura);
}

void Fecha(){
    if (window==NULL) return;
    SDL_DestroyWindow(window);
    window = NULL;
    fechada = true;
}

bool GetFechada(){
    return fechada;
}

void Esconde(){
    SDL_HideWindow(window);
}

void Exibe(){
    SDL_ShowWindow(window);
}

void GanhaFoco(){
    SDL_RaiseWindow(window);
}

bool GetUsandoCameraFixa(){
    return fixo;
}

inline void MoveCamera(int nx, int ny){
    cameraMovel->Move({nx,ny});
}

inline void DeslocaCamera(int dx, int dy){
    cameraMovel->Desloca(dx,dy);
}

double SetAfastamento(double valor){
    double afastamento = cameraMovel->DefineAfastamento(valor);
    SDL_RenderSetLogicalSize(renderer,afastamento*largura,afastamento*altura);
    return afastamento;
}

inline void ConverteCoordenadaScreenWorld(int screenX, int screenY, int &worldX, int &worldY){
    GetCamera()->ConverteCoordenadaScreenWorld(screenX, screenY, worldX, worldY);
}

inline void ConverteCoordenadaWorldScreen(int worldX, int worldY, int &screenX, int &screenY){
    GetCamera()->ConverteCoordenadaWorldScreen( worldX, worldY, screenX, screenY);
}

inline double GetAfastamento(){
    return cameraMovel->GetAfastamento();
}

inline SDL_Point GetPosicaoCamera(){
    return cameraMovel->GetXY();
}

void DefineFundo(string nomeArquivo){
    SDL_Surface* bitmap = IMG_Load(nomeArquivo.c_str());
    if (textFundo)
        SDL_DestroyTexture(textFundo);
    textFundo = SDL_CreateTextureFromSurface(renderer,bitmap);
    SDL_FreeSurface(bitmap);
}

void SaveScreenshot(string nomeArquivo, bool BMP) {
    if (window==NULL) return;
    SDL_Surface* saveSurface = NULL;
    SDL_Surface* infoSurface = NULL;
    infoSurface = SDL_GetWindowSurface(window);
    if (infoSurface != NULL) {
        unsigned char * pixels = new unsigned char[infoSurface->w * infoSurface->h * infoSurface->format->BytesPerPixel];
        if (pixels != 0) {
            if (SDL_RenderReadPixels(renderer, &infoSurface->clip_rect, infoSurface->format->format, pixels, infoSurface->w * infoSurface->format->BytesPerPixel) == 0) {
                saveSurface = SDL_CreateRGBSurfaceFrom(pixels, infoSurface->w, infoSurface->h, infoSurface->format->BitsPerPixel, infoSurface->w * infoSurface->format->BytesPerPixel, infoSurface->format->Rmask, infoSurface->format->Gmask, infoSurface->format->Bmask, infoSurface->format->Amask);
                if (saveSurface != NULL) {
                    if (BMP)
                        SDL_SaveBMP(saveSurface, nomeArquivo.c_str());
                    else IMG_SavePNG(saveSurface, nomeArquivo.c_str());
                    SDL_FreeSurface(saveSurface);
                }
            }
            delete[] pixels;
        }
        SDL_FreeSurface(infoSurface);
    }
}

inline void TravaRenderer(){
    SDL_SemWait(semRender);
}

inline void DestravaRenderer(){
    SDL_SemPost(semRender);
}

void IniciaDesenho(){
    TravaRenderer();
    if (textFundo==NULL) {
        SDL_SetRenderDrawColor(renderer,corFundo.r,corFundo.g,corFundo.b,corFundo.a);
        SDL_RenderClear( renderer );
    }
    else SDL_RenderCopy(renderer,textFundo,NULL,NULL);
}

inline void EncerraDesenho(){
    SDL_RenderPresent(renderer);
    DestravaRenderer();
    contFPS++;
    if (timerFPS->GetTempoDecorrido()>PIG_INTERVALO_FPS){
        lastFPS=contFPS;
        contFPS=0;

        timerFPS->Reinicia(false);
    }
}

inline float GetFPS(int idJanela=0){
    return lastFPS/PIG_INTERVALO_FPS;
}

int &GetAltura(){
    return altura;
}

int GetLargura(){
    return largura;
}

string GetTitulo(){
    return titulo;
}

void SetTitulo(string novoTitulo){
    if (window==NULL) return;
    titulo = novoTitulo;
    SDL_SetWindowTitle(window,titulo.c_str());
}

PIGCor GetCorFundo(){
    return corFundo;
}

void SetCorFundo(PIGCor cor){
    corFundo = cor;
}

float GetOpacidade(){
    return opacidade;
}

void SetOpacidade(float valor){
    opacidade = valor;
    SDL_SetWindowOpacity(window,opacidade);
}

void SetPosicao(int x, int y){
    if (window==NULL) return;
    SDL_SetWindowPosition(window,x,y);
}

SDL_Point GetXY(){
    return pos;
}

void SetBorda(int valor){
    if (window==NULL) return;
    SDL_SetWindowBordered(window,SDL_bool(valor));
}

void SetModo(int valor){
    if (window==NULL) return;
    modo = valor;
    SDL_SetWindowFullscreen(window,modo);
    SDL_GetWindowSize(window,&largura,&altura);
}

int GetModo(){
    return modo;
}

void SetTamanho(int alt, int larg){
    altura = alt;
    largura = larg;
    SDL_SetWindowSize(window,larg,alt);
    cameraMovel->AjustaTela(altura,largura);
    cameraFixa->AjustaTela(altura,largura);
}

void DesenhaRetangulo(int x, int y, int alturaRet, int larguraRet, PIGCor cor){
    SDL_Rect rect;
    rect.x = x;
    rect.y = altura-(y+alturaRet);
    rect.h = alturaRet;
    rect.w = larguraRet;

    GetCamera()->ConverteCoordenadaWorldScreen(rect.x,rect.y,rect.x,rect.y);

    //printf("%d,%d,%d,%d\n",rect.x,rect.y,rect.h,rect.w);

    SDL_SetRenderDrawColor(renderer, cor.r,cor.g,cor.b,cor.a);
    SDL_RenderFillRect(renderer,&rect);
}

void DesenhaRetanguloVazado(int x, int y, int alturaRet, int larguraRet, PIGCor cor){
    SDL_Rect rect;
    rect.x = x;
    rect.y = altura-(y+alturaRet);
    rect.h = alturaRet;
    rect.w = larguraRet;

    GetCamera()->ConverteCoordenadaWorldScreen(rect.x,rect.y,rect.x,rect.y);

    SDL_SetRenderDrawColor(renderer, cor.r,cor.g,cor.b,cor.a);
    SDL_RenderDrawRect(renderer,&rect);
}

void DesenhaLinhaSimples(int x1, int y1, int x2, int y2, PIGCor cor){
    SDL_SetRenderDrawColor(renderer,cor.r,cor.g,cor.b,255);
    int camX1,camY1,camX2,camY2;
    GetCamera()->ConverteCoordenadaWorldScreen(x1,altura-y1-1,camX1,camY1);
    GetCamera()->ConverteCoordenadaWorldScreen(x2,altura-y2-1,camX2,camY2);
    SDL_RenderDrawLine(renderer,camX1,camY1,camX2,camY2);
    //SDL_RenderDrawLine(renderer,x1-camera->GetX(),altura-y1-1+camera->GetY(),x2-camera->GetX(),altura-y2-1+camera->GetY());
}

void DesenhaLinhasDisjuntas(int x[], int y[], int qtd, PIGCor cor){
    SDL_SetRenderDrawColor(renderer,cor.r,cor.g,cor.b,255);
    int camX1,camY1,camX2,camY2;
    for (int k=0;k<qtd;k+=2){
        GetCamera()->ConverteCoordenadaWorldScreen(x[k],altura-y[k],camX1,camY1);
        GetCamera()->ConverteCoordenadaWorldScreen(x[k+1],altura-y[k+1],camX2,camY2);
        SDL_RenderDrawLine(renderer,camX1,camY1,camX2,camY2);
        //SDL_RenderDrawLine(renderer,x[k]-camera->GetX(),altura-y[k]+camera->GetY(),x[k+1]-camera->GetX(),altura-y[k+1]+camera->GetY());
    }
}

void DesenhaLinhasSequencia(int x[], int y[], int qtd, PIGCor cor){
    SDL_SetRenderDrawColor(renderer,cor.r,cor.g,cor.b,255);
    int camX1,camY1,camX2,camY2;
    for (int k=0;k<qtd-1;k++){
        GetCamera()->ConverteCoordenadaWorldScreen(x[k],altura-y[k],camX1,camY1);
        GetCamera()->ConverteCoordenadaWorldScreen(x[k+1],altura-y[k+1],camX2,camY2);
        SDL_RenderDrawLine(renderer,camX1,camY1,camX2,camY2);
        //SDL_RenderDrawLine(renderer,x[k]-camera->GetX(),altura-y[k]+camera->GetY(),x[k+1]-camera->GetX(),altura-y[k+1]+camera->GetY());
    }
}

void DesenhaPoligono(int px[], int py[], int lados, PIGCor cor){
    int minX=INT_MAX,maxX=-1,minY=INT_MAX,maxY=-1;
    int cx=0,cy=0;

    //calcula o bounding-box do poligono
    for (int i=0;i<lados;i++){
        if (px[i]<minX) minX = px[i];
        if (py[i]<minY) minY = py[i];
        if (px[i]>maxX) maxX = px[i];
        if (py[i]>maxY) maxY = py[i];
        cx += px[i]; //centro do poligono
        cy += py[i]; //centro do poligono
    }
    cx /= lados; //centro do poligono
    cy /= lados; //centro do poligono

    int alt = maxY-minY+1;  //altura absoluta do poligono
    int larg = maxX-minX+1; //altura absoluta do poligono

    PIGOffscreenRenderer off = new CPIGOffscreenRenderer(alt,larg); //ajustado extamente com a altura e largura

    if (PIGCoresIguais(cor,PRETO)){
        off->PintarFundo(BRANCO);
    }else off->PintarFundo(PRETO);

    for (int i=0;i<lados;i++)
        off->DesenharLinha(px[i]-minX,py[i]-minY,px[(i+1)%lados]-minX,py[(i+1)%lados]-minY,cor);

    off->PintarArea(cx-minX,cy-minY,cor);

    SDL_Surface *surf = off->GetSurface();
    if (PIGCoresIguais(cor,PRETO)){
        SDL_SetColorKey( surf, SDL_TRUE, SDL_MapRGBA(surf->format, 255, 255, 255, 255) );
    }else SDL_SetColorKey( surf, SDL_TRUE, SDL_MapRGBA(surf->format, 0, 0, 0, 255) );

    //SDL_Renderer *renderer = CGerenciadorJanelas::GetJanela(idJanela)->GetRenderer();
    SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_Rect r;
    r.h = alt;
    r.w = larg;
    r.x = minX;
    r.y = altura-minY-alt;
    GetCamera()->ConverteCoordenadaWorldScreen(r.x,r.y,r.x,r.y);
    //printf("%d,%d %d,%d\n",r.x,r.y,r.h,r.w);
    SDL_RenderCopy(renderer,text,NULL,&r);
    SDL_DestroyTexture(text);
    delete off;
}

PIGCor GetPixel(int x, int y) {
    if (x<0 || x>=largura  ||y<0 ||y>=altura) return PRETO;
    PIGCor resp;
    SDL_Surface* infoSurface = SDL_GetWindowSurface(window);
    if (infoSurface != NULL) {
        unsigned char * pixels = new unsigned char[infoSurface->w * infoSurface->h * infoSurface->format->BytesPerPixel];
        if (pixels != 0) {
            if (SDL_RenderReadPixels(renderer, &infoSurface->clip_rect, infoSurface->format->format, pixels, infoSurface->w * infoSurface->format->BytesPerPixel) == 0) {
                Uint32 *p = (Uint32*) pixels;
                p += (x+(altura-y)*largura);
                SDL_GetRGBA(*p,(const SDL_PixelFormat*) &infoSurface->format->format,&resp.r,&resp.g,&resp.b,&resp.a);
            }
            delete[] pixels;
        }
        SDL_FreeSurface(infoSurface);
    }
    return resp;
}

void BloqueiaArea(int x, int y, int alt, int larg){
    block.x = x;
    block.y = altura-(y+alt);
    block.h = alt;
    block.w = larg;

    GetCamera()->ConverteCoordenadaWorldScreen(block.x,block.y,block.x,block.y);
    SDL_RenderSetClipRect(renderer,&block);
}

SDL_Rect GetAreaBloqueada(){
    return block;
}

void DesbloqueiaArea(){
    block = {0,0,-1,-1};
    SDL_RenderSetClipRect(renderer,NULL);
}

};

typedef CPIGJanela *PIGJanela;
#endif // _CPIGJanela_
