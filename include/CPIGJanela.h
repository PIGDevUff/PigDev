#ifndef _CPIGJanela_
#define _CPIGJanela_

#include "CPIGCamera.h"

class CPIGJanela: public CPIGCamera{

private:

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *textFundo;
SDL_GLContext maincontext;
PIGCor corFundo;
int altura,largura;
SDL_Point pos;
int id;
int modo;
bool fechada;
float opacidade;
SDL_Rect block;
string titulo;

public:

CPIGJanela(string tituloJanela, int idJanela, int altTela, int largTela):
    CPIGCamera(altTela,largTela){

    id = idJanela;
    titulo = tituloJanela;
    altura = altTela;
    largura = largTela;
    window = SDL_CreateWindow( titulo.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, largura, altura, SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL );
    if( window == NULL ){
        printf( "Janela %d nao pode ser criada! Erro da SDL: %s\n",id, SDL_GetError() );
    }else{
        SDL_GetWindowPosition(window,&pos.x,&pos.y);

        maincontext = SDL_GL_CreateContext(window);
        //SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_TARGETTEXTURE);
        corFundo = PRETO;
        SDL_SetRenderDrawColor( renderer, corFundo.r, corFundo.g, corFundo.b, corFundo.a );
        SDL_SetRenderDrawBlendMode(renderer,SDL_BLENDMODE_BLEND);
        fechada = false;
        modo = PIG_JANELA_NORMAL;
    }
    opacidade = 1.0f;
    textFundo = NULL;
    SetTipoCamera(PIG_CAMERA2D_FIXA);
    FazCorrente();
}

~CPIGJanela(){
    SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
}

void PreparaCameraFixa(){
    SetTipoCamera(PIG_CAMERA2D_FIXA);
}

void PreparaCameraMovel(){
    SetTipoCamera(PIG_CAMERA2D_MOVEL);
}

bool GetUsandoCameraFixa(){
    return GetTipoCamera()==PIG_CAMERA2D_FIXA;
}

void FazCorrente(){
    SDL_GL_MakeCurrent(window,maincontext);
}

void SetVsync(bool valor){
    SDL_GL_SetSwapInterval(valor);
}

void IniciaDesenho(){
    FazCorrente();
    glClearColor(1.0*corFundo.r/255,1.0*corFundo.g/255,1.0*corFundo.b/255,1.0*corFundo.a/255);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void EncerraDesenho(){
    FazCorrente();
    SDL_GL_SwapWindow(window);
}

SDL_Window *GetWindow(){
    return window;
}

SDL_Renderer *GetRenderer(){
    return renderer;
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

inline SDL_Point GetPosicaoCamera(){
    return GetXY();
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

    //GetCamera()->ConverteCoordenadaWorldScreen(block.x,block.y,block.x,block.y);
    //SDL_RenderSetClipRect(renderer,&block);
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
