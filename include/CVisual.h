#ifndef _CPigVisual_
#define _CPigVisual_

class CPigVisual{

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
    std::string nomeArquivo;

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
        }else SDL_SetColorKey( bitmap, SDL_FALSE, 0);

        if (text) SDL_DestroyTexture(text);
        text = SDL_CreateTextureFromSurface(renderer, bitmap);
    }

    void CarregaImagem(std::string nomeArq){
        nomeArquivo = nomeArq;

        #ifdef SHARE_BITMAP
        bitmap = CAssetLoader::LoadImage(nomeArquivo);
        #else
        bitmap = IMG_Load(nomeArquivo.c_str());
        #endif
        if (!bitmap) throw CPigErroArquivo(nomeArquivo);
    }

    void IniciaBase(int altura,int largura,int janela){
        IniciaCor();
        IniciaJanela(janela);
        IniciaDimensoes(altura,largura);
        IniciaOrientacao();
    }

    CPigVisual(int altura,int largura,std::string nomeArq,int janela=0){
        nomeArquivo = nomeArq;
        IniciaBase(altura,largura,janela);
    }

    CPigVisual(std::string nomeArq,int retiraFundo=1,PIG_Cor *corFundo=NULL,int janela=0){
        nomeArquivo = nomeArq;

        CarregaImagem(nomeArq);

        IniciaBase(bitmap->h,bitmap->w,janela);

        CriaTextura(retiraFundo,corFundo);
    }

    CPigVisual(OffscreenRenderer offRender, int retiraFundo=1,PIG_Cor *corFundo=NULL,int janela=0){
        nomeArquivo = "";

        SDL_Surface *surface = offRender->GetSurface();

        bitmap = SDL_CreateRGBSurfaceWithFormatFrom(surface->pixels,surface->w,surface->h,offRender->GetDepth(),surface->pitch,surface->format->format);

        IniciaBase(bitmap->h,bitmap->w,janela);
        CriaTextura(retiraFundo,corFundo);
    }

    CPigVisual(CPigVisual *visualBase,int retiraFundo=1,PIG_Cor *corFundo=NULL,int janela=0){
        nomeArquivo = visualBase->nomeArquivo;

        #ifdef SHARE_BITMAP
        bitmap = CAssetLoader::LoadImage(visualBase->nomeArquivo);
        #else
        bitmap = IMG_Load(visualBase->nomeImagem);
        #endif

        IniciaBase(bitmap->h,bitmap->w,janela);
        CriaTextura(retiraFundo,corFundo);
    }

    CPigVisual(int janela){
        idJanela = janela;
        nomeArquivo = "";
        text = NULL;
        renderer = NULL;
        bitmap = NULL;
    }

    ~CPigVisual(){
        if (text) SDL_DestroyTexture(text);

        if (nomeArquivo == ""){
            if (bitmap) SDL_FreeSurface(bitmap);
        }else{
            #ifdef SHARE_BITMAP
            CAssetLoader::FreeImage(nomeArquivo);
            #else
            if (bitmap) SDL_FreeSurface(bitmap);
            #endif
        }
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
        SDL_SetTextureColorMod(text,cor.r,cor.g,cor.b);
    }

    virtual void SetAngulo(float a){
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

    virtual void Move(int nx,int ny){
        x = nx;
        y = ny;
        dest.x = x;
        dest.y = altJanela-alt-y;
    }

    virtual void Desloca(int dx, int dy){
        x += dx;
        y += dy;
        dest.x = x;
        dest.y = altJanela-alt-y;
    }

    virtual void SetDimensoes(int altura,int largura){
        dest.h = alt = altura;
        dest.w = larg = largura;
        dest.x = x;
        dest.y = altJanela-y-alt;

        pivoRelativo.y = alt;//necessário porque o poivô relativo é usado com eixo Y invertido (para baixo)
    }

    virtual void GetDimensoes(int &altura, int &largura){
        altura = alt;
        largura = larg;
    }

    void GetDimensoesOriginais(int &altura,int &largura){
        altura = altOriginal;
        largura = largOriginal;
    }

    void SetOpacidade(int valor){
        opacidade = valor;
        SDL_SetTextureAlphaMod(text,valor);
    }

    int GetOpacidade(){
        return opacidade;
    }

    std::string GetNomeArquivo(){
        return nomeArquivo;
    }
};
#endif // _CPigVisual_
