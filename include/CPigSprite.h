#ifndef _CPIGSPRITE_
#define _CPIGSPRITE_

#include "CPIGAutomacao.h"

class CPIGSprite{

protected:

    SDL_Point pos;
    int alt,larg,altOriginal,largOriginal;
    int idJanela,altJanela;
    double angulo;
    SDL_Rect dest;
    int frameAtual;
    std::unordered_map<int,SDL_Rect> frames;
    SDL_Texture* text;
    SDL_Point pivoRelativo;
    SDL_Renderer* renderer;
    SDL_RendererFlip flip;
    SDL_Surface* bitmap;
    PIG_Cor coloracao;
    PIG_Cor **pixels;
    int opacidade;
    std::string nomeArquivo;
    //PIGSequenciaTransicoes seqTrans;

    void CriaTextura(int retiraFundo, PIG_Cor *corFundo=NULL){
        if (retiraFundo){
            Uint8 red, green, blue, alpha;
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

        #ifdef PIG_SHARE_BITMAP
        bitmap = CPIGAssetLoader::LoadImage(nomeArquivo);
        #else
        bitmap = IMG_Load(nomeArquivo.c_str());
        #endif
        if (!bitmap) throw CPIGErroArquivo(nomeArquivo);
    }

    void IniciaBase(int altura,int largura,int janela){
        frameAtual = 0;
        frames[0] = {0,0,0,0};
        //seqTrans = new CPIGSequenciaTransicoes();
        IniciaCor();
        IniciaJanela(janela);
        IniciaDimensoes(altura,largura);
        IniciaOrientacao();
    }

    void ExtraiPixels() {
        Uint8 *pix8;
        Uint32 *pix32;

        pixels = (PIG_Cor **)malloc(sizeof(PIG_Cor *) * bitmap->h);
        for (int i = 0; i < bitmap->h; i++) {
            pixels[i] = (PIG_Cor *)calloc(sizeof(PIG_Cor), bitmap->w);
        }

        if (bitmap->format->BytesPerPixel == 3) {
            for (int h = 0; h < bitmap->h; h++) {
                pix8 = (Uint8 *)bitmap->pixels + (h * bitmap->pitch);
                for (int w = 0; w < bitmap->w; w++) {
                    if (bitmap->format->format == SDL_PIXELFORMAT_RGB24) {
                        pixels[h][w].r = *pix8;
                        pix8++;
                        pixels[h][w].g = *pix8;
                        pix8++;
                        pixels[h][w].b = *pix8;
                        pix8++;
                    } else {
                        pixels[h][w].b = *pix8;
                        pix8++;
                        pixels[h][w].g = *pix8;
                        pix8++;
                        pixels[h][w].r = *pix8;
                        pix8++;
                    }
                    pixels[h][w].a = 255;
                }
            }
        } else if (bitmap->format->BytesPerPixel == 4) {
            pix32 = (Uint32 *)bitmap->pixels;
            for (int h = 0; h < bitmap->h; h++) {
                for (int w = 0; w < bitmap->w; w++) {
                    SDL_GetRGBA((Uint32)*pix32, bitmap->format, &(pixels[h][w].r), &(pixels[h][w].g), &(pixels[h][w].b), &(pixels[h][w].a));
                    pix32++;
                }
            }
        }
    }


private:

    //Atributos relativos à coloração e textura do Sprite
    void IniciaCor(){
        coloracao = BRANCO;
        opacidade = 255; //totalmente opaco
        text = NULL;
    }

    //Atributos relativos à janela do Sprite
    void IniciaJanela(int janela){
        idJanela = janela;
        altJanela = CPIGGerenciadorJanelas::GetJanela(idJanela)->GetAltura();
        renderer = CPIGGerenciadorJanelas::GetJanela(idJanela)->GetRenderer();
    }

    //Atributos relativos ao tamanho do Sprite
    void IniciaDimensoes(int altura,int largura){
        altOriginal = alt = altura;
        largOriginal = larg = largura;
    }

    //Atributos relativos à rotação do Sprite
    void IniciaOrientacao(){
        pos = {0,0};
        angulo = 0;
        pivoRelativo.x = 0;
        pivoRelativo.y = alt;

        dest.x = pos.x;
        dest.y = altJanela-pos.y-alt;
        dest.h = alt;
        dest.w = larg;

        frames[0].x = frames[0].y = 0;
        frames[0].h = alt;
        frames[0].w = larg;

        flip = SDL_FLIP_NONE;
    }

public:

    //Construtor para arquivos de vídeo ou Componentes
    CPIGSprite(int altura,int largura,std::string nomeArq,int janela=0){
        nomeArquivo = nomeArq;
        IniciaBase(altura,largura,janela);
        pixels = NULL;
    }

    //Construtor básico para leitura de imagens digitais
    CPIGSprite(std::string nomeArq,int retiraFundo=1,PIG_Cor *corFundo=NULL,int janela=0){
        nomeArquivo = nomeArq;

        CarregaImagem(nomeArq);

        IniciaBase(bitmap->h,bitmap->w,janela);

        CriaTextura(retiraFundo,corFundo);
        ExtraiPixels();
    }

    //Construtor para imagens provenientes do renderizador offscreen
    CPIGSprite(PIGOffscreenRenderer offRender, int retiraFundo=1,PIG_Cor *corFundo=NULL,int janela=0){
        nomeArquivo = "";

        SDL_Surface *surface = offRender->GetSurface();

        bitmap = SDL_CreateRGBSurfaceWithFormatFrom(surface->pixels,surface->w,surface->h,offRender->GetDepth(),surface->pitch,surface->format->format);

        IniciaBase(bitmap->h,bitmap->w,janela);
        CriaTextura(retiraFundo,corFundo);
        ExtraiPixels();
    }

    //Construtor para Sprite "copiado" de outro Sprite
    CPIGSprite(CPIGSprite *spriteBase,int retiraFundo=1,PIG_Cor *corFundo=NULL,int janela=0){
        nomeArquivo = spriteBase->nomeArquivo;

        #ifdef PIG_SHARE_BITMAP
        bitmap = CPIGAssetLoader::LoadImage(spriteBase->nomeArquivo);
        #else
        bitmap = IMG_Load(spriteBase->nomeArquivo.c_str());
        #endif

        IniciaBase(bitmap->h,bitmap->w,janela);
        CriaTextura(retiraFundo,corFundo);
        ExtraiPixels();

        frameAtual = spriteBase->frameAtual;
        frames = spriteBase->frames;

        SetColoracao(spriteBase->coloracao);
        SetOpacidade(spriteBase->opacidade);
        SetAngulo(spriteBase->angulo);
        SetFlip(spriteBase->flip);
        SetDimensoes(spriteBase->alt,spriteBase->larg);
        SetPivo(spriteBase->pivoRelativo.x,spriteBase->pivoRelativo.y);
        Move(spriteBase->pos.x,spriteBase->pos.y);
    }

    //Construtor para sprite "vazio", cuja imagem será gerada posteriormente
    CPIGSprite(int janela){
        idJanela = janela;
        nomeArquivo = "";
        pivoRelativo = {0,0};
        angulo = 0;
        flip = PIG_FLIP_NENHUM;
        text = NULL;
        renderer = NULL;
        bitmap = NULL;
        frameAtual = 0;
        frames[0] ={0,0,0,0};
        pixels = NULL;
        //seqTrans = NULL;
    }

    /*void InsereTransicao(PIGTransicao t){
        if (seqTrans) seqTrans->Insere(t);
    }*/

    void AplicaTransicao(PIGTransicao t){
        int ok1,ok2;
        ok1 = t->GetX(pos.x);
        ok2 = t->GetY(pos.y);
        if (ok1||ok2)
            Move(pos.x,pos.y);
        ok1 = t->GetAltura(alt);
        ok2 = t->GetLargura(larg);
        if (ok1||ok2)
            SetDimensoes(alt,larg);
        if (t->GetCor(coloracao)) SetColoracao(coloracao);
        if (t->GetAngulo(angulo)) SetAngulo(angulo);
    }

    //Destrutor para todos os tipos de Sprites
    ~CPIGSprite(){
        if (pixels){
            for (int i = 0; i < bitmap->h; i++)
                free(pixels[i]);
            free(pixels);
        }

        //delete seqTrans;

        if (text) SDL_DestroyTexture(text);

        if (nomeArquivo == ""){
            if (bitmap) SDL_FreeSurface(bitmap);
        }else{
            #ifdef SHARE_BITMAP
            CPIGAssetLoader::FreeImage(nomeArquivo);
            #else
            if (bitmap) SDL_FreeSurface(bitmap);
            #endif
        }
    }

    int GetIdJanela(){
        return idJanela;
    }

    void DefineFrame(int idFrame,SDL_Rect r){
        frames[idFrame] = r;
    }

    SDL_Point GetXY(){
        return pos;
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

    //Pivô relativo ao ponto (,0) por meio de soma
    void SetPivo(int px,int py){
        pivoRelativo.x = px;
        pivoRelativo.y = dest.h-py;
    }

    //Pivo relativo ao ponto (0,0) por meio de multiplicação
    void SetPivo(float px,float py){
        pivoRelativo.x = px*dest.w;
        pivoRelativo.y = dest.h-py*dest.h;
    }

    //recupera o ponto pivô
    SDL_Point GetPivo(){
        return pivoRelativo;
    }

    virtual void Move(int nx,int ny){
        pos.x = nx;
        pos.y = ny;
        dest.x = pos.x;
        dest.y = altJanela-alt-pos.y;
    }

    virtual void Desloca(int dx, int dy){
        pos.x += dx;
        pos.y += dy;
        dest.x = pos.x;
        dest.y = altJanela-alt-pos.y;
    }

    virtual void SetDimensoes(int altura,int largura){
        dest.h = alt = altura;
        dest.w = larg = largura;
        dest.x = pos.x;
        dest.y = altJanela-alt-pos.y;

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

    int MudaFrameAtual(int novoFrame){
        if (frames.find(novoFrame) == frames.end())
            return 0;
        frameAtual = novoFrame;
        return 1;
    }

    void CarregaArquivoFrames(std::string nomeArq){
        int idFrame,xBitmap,yBitmap,altFrame,largFrame;
        FILE *arq = fopen(nomeArq.c_str(),"r");
        while (!feof(arq)){
            DefineFrame(idFrame,{xBitmap,yBitmap,altFrame,largFrame});
        }
        fclose(arq);
    }

    void CriaFramesAutomaticosPorLinha(int idFrameInicial,int qtdLinhas, int qtdColunas){
        if (qtdLinhas<=0||qtdColunas<=0) return;
        int largFrame = largOriginal/qtdColunas;
        int altFrame = altOriginal/qtdLinhas;
        for (int i=0;i<qtdLinhas;i++){
            for (int j=0;j<qtdColunas;j++){
                DefineFrame(idFrameInicial++,{j*largFrame,i*altFrame,largFrame,altFrame});
            }
        }
    }

    void CriaFramesAutomaticosPorColuna(int idFrameInicial,int qtdLinhas, int qtdColunas){
        if (qtdLinhas<=0||qtdColunas<=0) return;
        int largFrame = largOriginal/qtdColunas;
        int altFrame = altOriginal/qtdLinhas;
        for (int j=0;j<qtdColunas;j++){
            for (int i=0;i<qtdLinhas;i++){
                DefineFrame(idFrameInicial++,{j*largFrame,i*altFrame,largFrame,altFrame});
            }
        }
    }

    virtual int Desenha(){
        SDL_Rect enquadrado = dest;
        CPIGGerenciadorJanelas::GetJanela(idJanela)->ConverteCoordenadaWorldScreen(enquadrado.x,enquadrado.y,enquadrado.x,enquadrado.y);
        SDL_RenderCopyEx(renderer, text, &frames[frameAtual], &enquadrado, -angulo, &pivoRelativo, flip);
        return 0;
    }

    void DesenhaOffScreen(PIGOffscreenRenderer offRender){
        SDL_Texture *textAux = SDL_CreateTextureFromSurface(offRender->GetRenderer(), bitmap);
        SDL_Rect rectAux = dest;
        rectAux.y = offRender->GetAltura() - alt - pos.y;
        SDL_RenderCopyEx(offRender->GetRenderer(), textAux, &frames[frameAtual], &rectAux, -angulo, &pivoRelativo, flip);
        SDL_DestroyTexture(textAux);
    }

    void AtualizaPixels(int retiraFundo = 1, int opacidadeObj = 255) {
        if (!pixels) return;
        Uint8 *pix8;
        Uint32 *pix32;
        if (bitmap->format->BytesPerPixel == 3) {
            for (int h = 0; h < bitmap->h; h++) {
                pix8 = (Uint8 *)bitmap->pixels + (h * bitmap->pitch);
                for (int w = 0; w < bitmap->w; w++) {
                    if (bitmap->format->format == SDL_PIXELFORMAT_RGB24) {
                        *pix8 = pixels[h][w].r;
                        pix8++;
                        *pix8 = pixels[h][w].g;
                        pix8++;
                        *pix8 = pixels[h][w].b;
                        pix8++;
                    } else {
                        *pix8 = pixels[h][w].b;
                        pix8++;
                        *pix8 = pixels[h][w].g;
                        pix8++;
                        *pix8 = pixels[h][w].r;
                        pix8++;
                    }
                }
            }
        } else if (bitmap->format->BytesPerPixel == 4) {
            pix32 = (Uint32 *)bitmap->pixels;
            for (int h = 0; h < bitmap->h; h++) {
                for (int w = 0; w < bitmap->w; w++) {
                    SDL_GetRGBA((Uint32)*pix32, bitmap->format, &(pixels[h][w].r), &(pixels[h][w].g), &(pixels[h][w].b), &(pixels[h][w].a));
                    pix32++;
                }
            }
        }

        SetOpacidade(opacidadeObj);
        CriaTextura(retiraFundo);
    }

    PIG_Cor **GetPixels() {
        return pixels;
    }

    std::string GetNomeArquivo(){
        return nomeArquivo;
    }
};
typedef CPIGSprite *PIGSprite;
#endif // _CPIGSPRITE_
