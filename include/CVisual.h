class CVisual{

protected:

int alt,larg,altOriginal,largOriginal;
int idJanela,altJanela;
float angulo;
SDL_Rect dest,frame;
SDL_Texture* text;
SDL_Point pivoRelativo;
SDL_Renderer* renderer;
SDL_RendererFlip flip;
SDL_Surface* bitmap;
PIG_Cor coloracao;
int opacidade;
int x,y;
char nomeArquivo[1024];

void CriaTextura(int retiraFundo, PIG_Cor *corFundo=NULL){
    if (retiraFundo){
        Uint8 red, green, blue, alpha;
        //printf("vou retirar cor de fundo\n");
        if (corFundo!=NULL){
            red = corFundo->r;
            green = corFundo->g;
            blue = corFundo->b;
            alpha = corFundo->a;
        }else{
            Uint32 *pixel = (Uint32*)bitmap->pixels;
            SDL_GetRGBA(*pixel,bitmap->format,&red,&green,&blue,&alpha);
        }
        SDL_SetColorKey( bitmap, SDL_TRUE, SDL_MapRGBA(bitmap->format, red, green, blue,alpha) );
    }

    if (text) SDL_DestroyTexture(text);
    text = SDL_CreateTextureFromSurface(renderer, bitmap);
}


private:

void IniciaCor(){
    coloracao = BRANCO;
    opacidade = 255; //totalmente opaco
    text = NULL;
}

void IniciaJanela(int janela){
    idJanela = janela;
    altJanela = CGerenciadorJanelas::GetJanela(idJanela)->GetAltura();
    renderer = CGerenciadorJanelas::GetJanela(idJanela)->GetRenderer();
}

void IniciaDimensoes(int altura,int largura){
    altOriginal = alt = altura;
    largOriginal = larg = largura;
}

void IniciaOrientacao(){
    x = y = 0;
    angulo = 0;
    pivoRelativo.x = 0;
    pivoRelativo.y = alt;

    dest.x = x;
    dest.y = altJanela-y-alt;
    dest.h = alt;
    dest.w = larg;

    frame.x = frame.y = 0;
    frame.h = alt;
    frame.w = larg;

    flip = SDL_FLIP_NONE;
}

public:

CVisual(int altura,int largura,char *nomeArq,int janela=0){
    strcpy(nomeArquivo,nomeArq);

    IniciaCor();
    IniciaJanela(janela);
    IniciaDimensoes(altura,largura);
    IniciaOrientacao();
}

CVisual(char* nomeArq,int retiraFundo=1,PIG_Cor *corFundo=NULL,int janela=0){
    //printf("vamos visual %d\n",retiraFundo);
    strcpy(nomeArquivo,nomeArq);

    #ifdef SHARE_BITMAP
    bitmap = CAssetLoader::LoadImage(nomeArquivo);
    #else
    bitmap = IMG_Load(nomeArquivo);
    #endif
    if (!bitmap)
        printf("Erro ao ler arquivo: %s\n",nomeArquivo);

    //opacidade = 255;
    //text = NULL;
    IniciaCor();
    IniciaJanela(janela);
    IniciaDimensoes(bitmap->h,bitmap->w);
    IniciaOrientacao();
    CriaTextura(retiraFundo,corFundo);
}

CVisual(OffscreenRenderer offRender, int retiraFundo=1,PIG_Cor *corFundo=NULL,int janela=0){
    strcpy(nomeArquivo,"");

    SDL_Surface *surface = offRender->GetSurface();
    //printf("depth %d  wid  %d  hei %d\n",offRender->GetDepth(),surface->w,surface->h);
    bitmap = SDL_CreateRGBSurfaceWithFormatFrom(surface->pixels,surface->w,surface->h,offRender->GetDepth(),surface->pitch,surface->format->format);
    if (!bitmap)
        printf("Erro ao copiar superficie\n");

    //opacidade = 255;
    //text = NULL;
    IniciaCor();
    IniciaJanela(janela);
    IniciaDimensoes(bitmap->h,bitmap->w);
    IniciaOrientacao();
    CriaTextura(retiraFundo,corFundo);
}

CVisual(CVisual *visualBase,int retiraFundo=1,PIG_Cor *corFundo=NULL,int janela=0){
    strcpy(nomeArquivo,visualBase->nomeArquivo);

    #ifdef SHARE_BITMAP
    bitmap = CAssetLoader::LoadImage(visualBase->nomeArquivo);
    #else
    bitmap = IMG_Load(visualBase->nomeImagem);
    #endif
    if (!bitmap)
        printf("Erro ao ler arquivo: %s\n",visualBase->nomeArquivo);

    //opacidade = 255;
    //text = NULL;
    IniciaCor();
    IniciaJanela(janela);
    IniciaDimensoes(bitmap->h,bitmap->w);
    IniciaOrientacao();
    CriaTextura(retiraFundo,corFundo);
}

~CVisual(){
    if (text) SDL_DestroyTexture(text);

    if (strcmp(nomeArquivo,"")==0){
        if (bitmap) SDL_FreeSurface(bitmap);
    }else{
        #ifdef SHARE_BITMAP
        CAssetLoader::FreeImage(nomeArquivo);
        #else
        if (bitmap) SDL_FreeSurface(bitmap);
        #endif
    }
}

int GetIdJanela(){
    return idJanela;
}

void DefineFrame(SDL_Rect r){
    frame = r;
}

void GetXY(int &x,int &y){
    x = this->x;
    y = this->y;
}

void SetColoracao(PIG_Cor cor){
    coloracao = cor;
    //SDL_SetTextureColorMod(text,cor.r,cor.g,cor.b);
}

/*virtual int Desenha(OffscreenRenderer offRender=NULL)=0;{
    if (offRender==NULL){
        SDL_RenderCopyEx(renderer, text, &frame,&dest,-angulo,&pivoRelativo,flip);
    }else{
        SDL_Texture *textAux = SDL_CreateTextureFromSurface(offRender->GetRenderer(),bitmap);
        SDL_Rect rectAux = dest;
        rectAux.y = offRender->GetAltura()-alt-y;
        SDL_RenderCopyEx(offRender->GetRenderer(), textAux, &frame,&rectAux,-angulo,&pivoRelativo,flip);
        SDL_DestroyTexture(textAux);
    }
}*/

void SetAngulo(float a){
    angulo = a;
}

float GetAngulo(){
    return angulo;
}

void SetFlip(PIG_Flip valor){
    flip = valor;
}

PIG_Flip GetFlip(){
    return flip;
}

void SetPivo(int px,int py){
    pivoRelativo.x = px;
    pivoRelativo.y = dest.h-py;
}

void SetPivo(float px,float py){
    pivoRelativo.x = px*dest.w;
    pivoRelativo.y = dest.h-py*dest.h;
}

void GetPivo(int &px,int &py){
    px = pivoRelativo.x;
    py = pivoRelativo.y;
}

void Move(int nx,int ny){
    x = nx;
    y = ny;
    dest.x = x;
    dest.y = altJanela-alt-y;
}

void SetDimensoes(int altura,int largura){
    dest.h = alt = altura;
    dest.w = larg = largura;
    dest.x = x;
    dest.y = altJanela-y-alt;
}

void GetDimensoes(int &altura, int &largura){
    altura = alt;
    largura = larg;
}

void GetDimensoesOriginais(int &altura,int &largura){
    altura = altOriginal;
    largura = largOriginal;
}

void SetOpacidade(int valor){
    opacidade = valor;
    //SDL_SetTextureAlphaMod(text,valor);
}

int GetOpacidade(){
    return opacidade;
}

void GetNomeArquivo(char *nome){
    strcpy(nome,nomeArquivo);
}

};
