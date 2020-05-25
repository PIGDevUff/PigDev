class CJanela{

private:

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *textFundo;
PIG_Cor corFundo;
int altura,largura,px,py;
int id;
int fechada,modo;
float opacidade;
std::string titulo;

public:

CJanela(std::string tituloJanela,int idJanela,int altTela,int largTela){
    id = idJanela;
    titulo = tituloJanela;
    altura = altTela;
    largura = largTela;
    window = SDL_CreateWindow( tituloJanela.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, largura, altura, SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL );
    if( window == NULL ){
        printf( "Janela %d nao pode ser criada! Erro da SDL: %s\n",id, SDL_GetError() );
    }else{
        //handler = SDL_GetWindowID(window);
        //printf("Meu id %d meu handler %d\n",idJanela,handler);
        SDL_GetWindowPosition(window,&px,&py);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_TARGETTEXTURE);
        corFundo = PRETO;
        SDL_SetRenderDrawColor( renderer, corFundo.r, corFundo.g, corFundo.b, corFundo.a );
        SDL_SetRenderDrawBlendMode(renderer,SDL_BLENDMODE_BLEND);
        fechada = 0;
        modo = JANELA_NORMAL;
    }

    opacidade = 1.0f;
    textFundo = NULL;
}

~CJanela(){
    SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
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
    fechada = 1;
}

int GetFechada(){
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

void DefineFundo(std::string nomeArquivo){
    SDL_Surface* bitmap = IMG_Load(nomeArquivo.c_str());
    if (textFundo)
        SDL_DestroyTexture(textFundo);
    textFundo = SDL_CreateTextureFromSurface(renderer,bitmap);
    SDL_FreeSurface(bitmap);
}

void SaveScreenshot(std::string nomeArquivo, bool BMP) {
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

void IniciaDesenho(){
    if (textFundo==NULL) {
        SDL_SetRenderDrawColor(renderer,corFundo.r,corFundo.g,corFundo.b,corFundo.a);
        SDL_RenderClear( renderer );
    }
    else SDL_RenderCopy(renderer,textFundo,NULL,NULL);
}

void EncerraDesenho(){
    SDL_RenderPresent(renderer);

}

int GetAltura(){
    return altura;
}

int GetLargura(){
    return largura;
}

std::string GetTitulo(){
    return titulo;
}

void SetTitulo(std::string novoTitulo){
    if (window==NULL) return;
    titulo = novoTitulo;
    SDL_SetWindowTitle(window,titulo.c_str());
}

PIG_Cor GetCorFundo(){
    return corFundo;
}

void SetCorFundo(PIG_Cor cor){
    corFundo = cor;
}

float GetOpacidade(){
    return opacidade;
}

void SetOpacidade(float valor){
    opacidade = valor;
    SDL_SetWindowOpacity(window,opacidade);
}

void SetPosicao(int x,int y){
    if (window==NULL) return;
    SDL_SetWindowPosition(window,x,y);
}

void GetPosicao(int *x,int *y){
    *x = px;
    *y = py;
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

int SetTamanho(int alt, int larg){
    altura = alt;
    largura = larg;
    SDL_SetWindowSize(window,larg,alt);
}

    void DesenhaRetangulo(int x, int y, int alturaRet, int larguraRet, PIG_Cor cor){
        SDL_Rect rect;
        rect.x = x;
        rect.y = altura-(y+alturaRet);
        rect.h = alturaRet;
        rect.w = larguraRet;

        SDL_SetRenderDrawColor(renderer, cor.r,cor.g,cor.b,cor.a);
        SDL_RenderFillRect(renderer,&rect);
    }

    void DesenhaRetanguloVazado(int x, int y, int alturaRet, int larguraRet, PIG_Cor cor){
        SDL_Rect rect;
        rect.x = x;
        rect.y = altura-(y+alturaRet);
        rect.h = alturaRet;
        rect.w = larguraRet;

        SDL_SetRenderDrawColor(renderer, cor.r,cor.g,cor.b,cor.a);
        SDL_RenderDrawRect(renderer,&rect);
    }

    void DesenhaLinhaSimples(int x1,int y1,int x2,int y2,PIG_Cor cor){
        SDL_SetRenderDrawColor(renderer,cor.r,cor.g,cor.b,255);
        SDL_RenderDrawLine(renderer,x1,altura-y1-1,x2,altura-y2-1);
    }

    void DesenhaLinhasDisjuntas(int *x,int *y,int qtd,PIG_Cor cor){
        SDL_SetRenderDrawColor(renderer,cor.r,cor.g,cor.b,255);
        for (int k=0;k<qtd*2;k+=2){
            SDL_RenderDrawLine(renderer,x[k],altura-y[k],x[k+1],altura-y[k+1]);
        }
    }

    void DesenhaLinhasSequencia(int *x,int *y,int qtd,PIG_Cor cor){
        SDL_SetRenderDrawColor(renderer,cor.r,cor.g,cor.b,255);
        for (int k=0;k<qtd-1;k++){
            SDL_RenderDrawLine(renderer,x[k],altura-y[k],x[k+1],altura-y[k+1]);
        }
    }

    PIG_Cor GetPixel(int x,int y) {
        if (x<0 || x>=largura  ||y<0 ||y>=altura) return PRETO;
        PIG_Cor resp;
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

};


typedef CJanela *Janela;
