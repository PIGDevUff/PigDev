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
char titulo[50];

public:

CJanela(char tituloJanela[],int idJanela,int altTela,int largTela){
    id = idJanela;
    strcpy(titulo,tituloJanela);
    altura = altTela;
    largura = largTela;
    window = SDL_CreateWindow( tituloJanela, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, largura, altura, SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL );
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

void DefineFundo(char *nomeArquivo){
    SDL_Surface* bitmap = IMG_Load(nomeArquivo);
    if (textFundo) SDL_DestroyTexture(textFundo);
    textFundo = SDL_CreateTextureFromSurface(renderer,bitmap);
    SDL_FreeSurface(bitmap);
}

void SaveScreenshotBMP(char *nomeArquivo) {
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
                    SDL_SaveBMP(saveSurface, nomeArquivo);
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

void GetTitulo(char *tituloJanela){
    strcpy(tituloJanela,titulo);
}

void SetTitulo(char *novoTitulo){
    if (window==NULL) return;
    strcpy(titulo,novoTitulo);
    SDL_SetWindowTitle(window,titulo);
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
}

int GetModo(){
    return modo;
}

};


typedef CJanela *Janela;
