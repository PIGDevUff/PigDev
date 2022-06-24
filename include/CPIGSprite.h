#ifndef _CPIGSPRITE_
#define _CPIGSPRITE_

#include "CPIGAutomacao.h"

class CPIGSprite{

protected:

    int alt,larg,altOriginal,largOriginal;
    int id,idJanela,&altJanela;
    PIGPonto2D pos,proporcaoPivo,pivoAbs;
    SDL_Point pivoInteiro;
    bool usaPivoRelativo;
    double angulo;
    SDL_Rect dest;
    int frameAtual;
    unordered_map<int,SDL_Rect> frames;
    SDL_Texture* text;
    SDL_Renderer* renderer;
    SDL_RendererFlip flip;
    SDL_Surface* bitmap;
    PIGCor coloracao;
    PIGCor **pixels;
    int opacidade;
    string nomeArquivo;
    PIGAutomacao automacao;
    int tipoFixo;
    vector<CPIGSprite*> filhos;
    bool precisaAtualizar;

private:

    void CarregaImagem(string nomeArq){
        nomeArquivo = nomeArq;

        #ifdef PIG_SHARE_BITMAP
        bitmap = CPIGAssetLoader::LoadImage(nomeArquivo);
        #else
        bitmap = IMG_Load(nomeArquivo.c_str());
        #endif
        if (!bitmap) throw CPIGErroArquivo(nomeArquivo);
    }

    void IniciaBase(int altura, int largura, int janela){
        frameAtual = 0;
        automacao = NULL;
        tipoFixo = 0;
        IniciaCor();
        IniciaJanela(janela);
        IniciaDimensoes(altura,largura);
        IniciaOrientacao();
    }

    void ExtraiPixels() {
        if (!bitmap) return;
        pixels = (PIGCor **)malloc(sizeof(PIGCor*) * bitmap->h);
        for (int i = 0; i < bitmap->h; i++) {
            pixels[i] = (PIGCor *)calloc(sizeof(PIGCor), bitmap->w);
        }

        Uint32 *pix32 = (Uint32 *)bitmap->pixels;
        for (int h = 0; h < bitmap->h; h++) {
            for (int w = 0; w < bitmap->w; w++) {
                SDL_GetRGBA((Uint32)*pix32, bitmap->format, &(pixels[h][w].r), &(pixels[h][w].g), &(pixels[h][w].b), &(pixels[h][w].a));
                pix32++;
            }
        }

    }

    //Atributos relativos à coloração e textura do Sprite
    inline void IniciaCor(){
        coloracao = BRANCO;
        opacidade = 255; //totalmente opaco
        text = NULL;
    }

    //Atributos relativos à janela do Sprite
    inline void IniciaJanela(int janela){
        idJanela = janela;
        //altJanela = CPIGGerenciadorJanelas::GetJanela(idJanela)->GetAltura();
        renderer = CPIGGerenciadorJanelas::GetJanela(idJanela)->GetRenderer();
    }

    //Atributos relativos ao tamanho do Sprite
    inline void IniciaDimensoes(int altura,int largura){
        altOriginal = alt = altura;
        largOriginal = larg = largura;
    }

    //Atributos relativos à rotação do Sprite
    void IniciaOrientacao(){
        pos = {0,0};
        angulo = 0;
        pivoAbs = {0,1.0*alt};
        pivoInteiro = {0,alt};
        proporcaoPivo = {0,0};
        usaPivoRelativo = false;

        dest.x = pos.x;
        dest.y = altJanela-pos.y-alt;
        dest.h = alt;
        dest.w = larg;

        frames[0].x = frames[0].y = 0;
        frames[0].h = alt;
        frames[0].w = larg;

        flip = SDL_FLIP_NONE;
    }

protected:

    void AplicaTransicao(PIGEstadoTransicao estado){
        Move(estado.x,estado.y);
        if (estado.alt!=alt||estado.larg!=larg) SetDimensoes(estado.alt,estado.larg);
        if (!(estado.cor==BRANCO)) SetColoracao(estado.cor);
        if (estado.opacidade!=opacidade) SetOpacidade(estado.opacidade);
        if (estado.ang!=angulo) SetAngulo(estado.ang);
    }

    inline virtual void AtualizaTextura(){
        if (this_thread::get_id()==PIG_MAIN_THREAD_ID){
            if (text) SDL_DestroyTexture(text);
            text = SDL_CreateTextureFromSurface(renderer, bitmap);
            precisaAtualizar = false;
        }
    }

public:

    int GetId(){
        return id;
    }

    //Construtor para arquivos de vídeo ou Componentes
    CPIGSprite(int idSprite, int altura, int largura, string nomeArq, int janela=0)
        :altJanela(CPIGGerenciadorJanelas::GetJanela(janela)->GetAltura()){
        id = idSprite;

        precisaAtualizar = true;
        nomeArquivo = nomeArq;
        bitmap = NULL;

        IniciaBase(altura,largura,janela);
        pixels = NULL;
    }

    //Construtor básico para leitura de imagens digitais
    CPIGSprite(int idSprite, string nomeArq, int retiraFundo=1, PIGCor *corFundo=NULL, int janela=0)
        :altJanela(CPIGGerenciadorJanelas::GetJanela(janela)->GetAltura()){
        id = idSprite;

        precisaAtualizar = true;
        nomeArquivo = nomeArq;

        CarregaImagem(nomeArq);

        IniciaBase(bitmap->h,bitmap->w,janela);
        PreparaTextura(retiraFundo,corFundo);
        ExtraiPixels();
    }

    //Construtor para imagens provenientes do renderizador offscreen
    CPIGSprite(int idSprite, PIGOffscreenRenderer offRender, int retiraFundo=1, PIGCor *corFundo=NULL, int janela=0)
        :altJanela(CPIGGerenciadorJanelas::GetJanela(janela)->GetAltura()){
        id = idSprite;

        precisaAtualizar = true;
        nomeArquivo = "";

        SDL_Surface *surface = offRender->GetSurface();

        bitmap = SDL_CreateRGBSurfaceWithFormatFrom(surface->pixels,surface->w,surface->h,offRender->GetDepth(),surface->pitch,surface->format->format);

        IniciaBase(bitmap->h,bitmap->w,janela);
        PreparaTextura(retiraFundo,corFundo);
        ExtraiPixels();
    }

    //Construtor para Sprite "copiado" de outro Sprite
    CPIGSprite(int idSprite, CPIGSprite *spriteBase, int retiraFundo=1, PIGCor *corFundo=NULL, int janela=0)
        :altJanela(CPIGGerenciadorJanelas::GetJanela(janela)->GetAltura()){
        id = idSprite;

        precisaAtualizar = true;

        CarregaImagem(spriteBase->nomeArquivo);

        IniciaBase(bitmap->h,bitmap->w,janela);
        PreparaTextura(retiraFundo,corFundo);
        ExtraiPixels();

        frameAtual = spriteBase->frameAtual;
        frames = spriteBase->frames;

        SetColoracao(spriteBase->coloracao);
        SetOpacidade(spriteBase->opacidade);
        SetAngulo(spriteBase->angulo);
        SetFlip(spriteBase->flip);
        SetDimensoes(spriteBase->alt,spriteBase->larg);

        usaPivoRelativo = spriteBase->usaPivoRelativo;
        if (usaPivoRelativo){
            SetPivoProporcional(spriteBase->proporcaoPivo);
        }else{
            proporcaoPivo = spriteBase->proporcaoPivo;
            SetPivoAbsoluto(spriteBase->pivoAbs);
        }

        Move(spriteBase->pos.x,spriteBase->pos.y);

        if (spriteBase->automacao){
            automacao = new CPIGAutomacao(id,spriteBase->automacao);
        }else automacao = NULL;
    }

    //Construtor para sprite "vazio", cuja imagem será gerada posteriormente
    CPIGSprite(int janela)
        :altJanela(CPIGGerenciadorJanelas::GetJanela(janela)->GetAltura()){
        id = -1;
        idJanela = janela;
        nomeArquivo = "";
        pivoAbs = {0,1.0*alt};
        pivoInteiro = {0,alt};
        proporcaoPivo = {0,0};
        usaPivoRelativo = false;
        angulo = 0;
        flip = PIG_FLIP_NENHUM;
        text = NULL;
        bitmap = NULL;
        frameAtual = 0;
        frames[0] ={0,0,0,0};
        pos = {0,0};
        pixels = NULL;
        automacao = NULL;
        //altJanela = CPIGGerenciadorJanelas::GetJanela(idJanela)->GetAltura();
        renderer = CPIGGerenciadorJanelas::GetJanela(idJanela)->GetRenderer();
    }

    void PreparaTextura(int retiraFundo, PIGCor *corFundo=NULL){
        if (!bitmap) return;
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

        AtualizaTextura();
    }

    int RecebeFilho(CPIGSprite *filho, int fixo){
        filho->tipoFixo = fixo;
        filhos.push_back(filho);
        return 1;
    }

    int Retirafilho(CPIGSprite *filho){
        for (unsigned int i=0;i<filhos.size();i++)
            if (filhos[i] == filho){
                filhos.erase(filhos.begin()+i);
                return 1;
            }
        return 0;
    }

    void InsereTransicao(PIGTransicao t, PIGAutomacao *automaExt=NULL){
        if (automaExt==NULL) automaExt=&automacao;
        if (*automaExt==NULL)
            *automaExt = new CPIGAutomacao(id);
        (*automaExt)->InsereTransicao(t);
    }

    void InsereTransicao(double tempo, PIGEstadoTransicao estado, PIGAutomacao *automaExt=NULL){
        if (automaExt==NULL) automaExt=&automacao;
        if (*automaExt==NULL)
            *automaExt = new CPIGAutomacao(id);
        (*automaExt)->InsereTransicao(new CPIGTransicao(tempo,estado));
    }

    void LeTransicoes(string nomeArq, PIGAutomacao *automaExt=NULL){
        int dx=0,dy=0,dAlt=0,dLarg=0,dOpa=0;
        double dAng=0,tempo=0;
        PIGCor dCor=BRANCO;

        if (automaExt==NULL) automaExt=&automacao;
        if (*automaExt==NULL){
            *automaExt = new CPIGAutomacao(id);
        }
        //printf("arquivo %s\n",nomeArq.c_str());
        FILE *arq = fopen(nomeArq.c_str(),"r");
        while (fscanf(arq,"%lf %d %d %d %d %lf %d %d %d %d %d\n",&tempo,&dx,&dy,&dAlt,&dLarg,&dAng,&dCor.r,&dCor.g,&dCor.b,&dCor.a,&dOpa)>0){
            //printf("%f %d %d %d %d %f %d %d %d %d %d\n",tempo,dx,dy,dAlt,dLarg,dAng,dCor.r,dCor.g,dCor.b,dCor.a,dOpa);
            (*automaExt)->InsereTransicao(new CPIGTransicao(tempo,{dx,dy,dAlt,dLarg,dAng,dCor,dOpa}));
        }
        fclose(arq);
    }

    void IniciaAutomacao(PIGAutomacao *automaExt=NULL){
        if ( automaExt ==NULL) automaExt=&automacao;
        if (*automaExt)
            (*automaExt)->IniciaAutomacao({(int)pos.x,(int)pos.y,alt,larg,angulo,coloracao,opacidade});
    }

    void LimpaTransicoes(PIGAutomacao *automaExt=NULL){
        if (automaExt==NULL) automaExt=&automacao;
        if (*automaExt) (*automaExt)->LimpaTransicoes();
    }

    bool ExecutandoTransicao(PIGAutomacao *automaExt=NULL){
        if (automaExt==NULL) automaExt=&automacao;
        if (*automaExt==NULL) return NULL;
        return (*automaExt)->ExecutandoTransicao();
    }

    void TrataAutomacao(PIGAutomacao *automaExt=NULL){
        if (automaExt==NULL) automaExt=&automacao;
        if (*automaExt){
            PIGTransicao t = (*automaExt)->GetTransicaoAtual();
            if (t) AplicaTransicao(t->GetEstado());
            (*automaExt)->TrataAcao();
        }
    }

    void PausaAutomacao(PIGAutomacao *automaExt=NULL){
        if (automaExt==NULL) automaExt=&automacao;
        if (*automaExt){
            (*automaExt)->PausaAutomacao();
        }
    }

    void DespausaAutomacao(PIGAutomacao *automaExt=NULL){
        if (automaExt==NULL) automaExt=&automacao;
        if (*automaExt){
            (*automaExt)->DespausaAutomacao();
        }
    }

    void InsereAcao(double tempo, double repeticao, PIGFuncaoSimples acao, void *param, PIGAutomacao *automaExt=NULL){
        if (automaExt==NULL) automaExt=&automacao;
        if (*automaExt==NULL)
            *automaExt = new CPIGAutomacao(id);

        (*automaExt)->InsereAcao(acao,tempo,repeticao,param);
    }

    void LimpaAcoes(PIGAutomacao *automaExt=NULL){
        if (automaExt==NULL) automaExt=&automacao;
        if (*automaExt) (*automaExt)->LimpaAcoes();
    }

    void DefineTipoTransicao(PIGTipoTransicao tipo, PIGAutomacao *automaExt=NULL){
        if (automaExt==NULL) automaExt=&automacao;
        if (*automaExt) (*automaExt)->SetTipoTransicao(tipo);
    }

    //Destrutor para todos os tipos de Sprites
    virtual ~CPIGSprite(){
        if (pixels){
            for (int i = 0; i < bitmap->h; i++)
                free(pixels[i]);
            free(pixels);
        }

        if (automacao) delete automacao;

        if (text) SDL_DestroyTexture(text);

        if (nomeArquivo == ""){
            if (bitmap) SDL_FreeSurface(bitmap);
        }else{
            #ifdef PIG_SHARE_BITMAP
            CPIGAssetLoader::FreeImage(nomeArquivo);
            #else
            if (bitmap) SDL_FreeSurface(bitmap);
            #endif
        }
    }

    inline int GetIdJanela(){
        return idJanela;
    }

    inline void DefineFrame(int idFrame, SDL_Rect r){
        frames[idFrame] = r;
    }

    inline PIGPonto2D GetXY(){
        return pos;
    }

    inline void SetColoracao(PIGCor cor){
        coloracao = cor;
        SDL_SetTextureColorMod(text,cor.r,cor.g,cor.b);
    }

    inline PIGCor GetColoracao(){
        return coloracao;
    }

    void Rotaciona(double px, double py, double graus){
        double cosseno = cos(graus*M_PI/180.0);
        double seno = sin(graus*M_PI/180.0);

        double dx = pos.x-px;
        double dy = pos.y-py;
        double nx = cosseno*dx - seno*dy;
        double ny = seno*dx + cosseno*dy;

        Move(nx+px,ny+py);

        SetAngulo(angulo+graus);
    }

    virtual void SetAngulo(double a){
        double delta = a-angulo;
        angulo = a;
        double pivoRealX = pos.x+pivoAbs.x;
        double pivoRealY = pos.y+(alt-pivoAbs.y);

        for (unsigned int i=0;i<filhos.size();i++){
            if (filhos[i]->tipoFixo==0) continue;
            if (filhos[i]->tipoFixo==1){
                filhos[i]->Rotaciona(pivoRealX,pivoRealY,delta);
            }else{//tipoFixo==2
                double pivoFilhoX = filhos[i]->pivoAbs.x+filhos[i]->pos.x;
                double pivoFilhoY = filhos[i]->pos.y+filhos[i]->alt-filhos[i]->pivoAbs.y;
                filhos[i]->Rotaciona(pivoFilhoX, pivoFilhoY,delta);
                filhos[i]->Desloca(-pivoFilhoX+pivoRealX,-pivoFilhoY+pivoRealY);//-pivoFilhoY-(alt-filhos[i]->pivoRelativo.y));
                //printf("%f,%f\n",filhos[i]->pos.x,filhos[i]->pos.y);
            }
        }
    }

    inline double GetAngulo(){
        return angulo;
    }

    inline void SetFlip(PIGFlip valor){
        flip = valor;
    }

    inline PIGFlip GetFlip(){
        return flip;
    }

    //Pivô relativo ao ponto (0,0) por meio de soma
    void SetPivoAbsoluto(PIGPonto2D pivo){
        pivoAbs.x = pivo.x;
        pivoAbs.y = alt-pivo.y;
        pivoInteiro = {(int)pivoAbs.x,(int)pivoAbs.y};
        usaPivoRelativo = false;
    }

    //Pivo relativo ao ponto (0,0) por meio de multiplicação
    void SetPivoProporcional(PIGPonto2D pivo){
        proporcaoPivo = pivo;
        pivoAbs.x = pivo.x*larg;
        pivoAbs.y = alt*pivo.y;
        pivoInteiro = {(int)pivoAbs.x,(int)(alt-pivoAbs.y)};
        usaPivoRelativo = true;
    }

    //recupera o ponto pivô
    inline PIGPonto2D GetPivo(){
        return pivoAbs;
    }

    inline virtual void Move(double nx, double ny){
        Desloca(nx-pos.x,ny-pos.y);
    }

    virtual void Desloca(double dx, double dy){
        pos.x += dx;
        pos.y += dy;
        dest.x = pos.x;
        dest.y = altJanela-alt-pos.y;
        for (unsigned int i=0;i<filhos.size();i++){
            if (filhos[i]->tipoFixo!=0)
                filhos[i]->Desloca(dx,dy);
        }
    }

    virtual void SetDimensoes(int altura, int largura){
        dest.h = alt = altura;
        dest.w = larg = largura;
        dest.x = pos.x;
        dest.y = altJanela-alt-pos.y;

        if (usaPivoRelativo){
            SetPivoProporcional(proporcaoPivo);
        }else{
            SetPivoAbsoluto(pivoAbs);
        }
    }

    inline virtual void GetDimensoes(int &altura, int &largura){
        altura = alt;
        largura = larg;
    }

    inline void GetDimensoesOriginais(int &altura,int &largura){
        altura = altOriginal;
        largura = largOriginal;
    }

    inline void SetOpacidade(int valor){
        opacidade = valor;
        SDL_SetTextureAlphaMod(text,valor);
    }

    inline void RestauraDimensoesOriginais(){
        SetDimensoes(altOriginal,largOriginal);
    }

    inline int GetOpacidade(){
        return opacidade;
    }

    int MudaFrameAtual(int novoFrame){
        if (frames.find(novoFrame) == frames.end())
            return 0;
        frameAtual = novoFrame;
        return 1;
    }

    inline int GetFrameAtual(){
        return frameAtual;
    }

    void CarregaArquivoFrames(string nomeArq){
        int idFrame,xBitmap,yBitmap,altFrame,largFrame;
        FILE *arq = fopen(nomeArq.c_str(),"r");
        while (fscanf(arq,"%d %d %d %d %d\n",&idFrame,&xBitmap,&yBitmap,&altFrame,&largFrame) == 5){
            DefineFrame(idFrame,{xBitmap,yBitmap,largFrame,altFrame});
        }
        fclose(arq);
    }

    void CriaFramesAutomaticosPorLinha(int idFrameInicial, int qtdLinhas, int qtdColunas){
        if (qtdLinhas<=0||qtdColunas<=0) return;
        int largFrame = largOriginal/qtdColunas;
        int altFrame = altOriginal/qtdLinhas;
        for (int i=0;i<qtdLinhas;i++){
            for (int j=0;j<qtdColunas;j++){
                DefineFrame(idFrameInicial++,{j*largFrame,i*altFrame,largFrame,altFrame});
            }
        }
    }

    void CriaFramesAutomaticosPorColuna(int idFrameInicial, int qtdLinhas, int qtdColunas){
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
        dest.y = altJanela-alt-pos.y;
        SDL_Rect enquadrado = dest;
        //printf("%d,%d,%d,%d\n",dest.x,*altJanela-dest.y,dest.h,dest.w);
        //SDL_Point p = {pivoRelativo.x,pivoRelativo.y};
        CPIGGerenciadorJanelas::GetJanela(idJanela)->ConverteCoordenadaWorldScreen(enquadrado.x,enquadrado.y,enquadrado.x,enquadrado.y);
        //
        #if PIG_MULTITHREAD_TELAS==1
        if (precisaAtualizar){//criada!=PIG_MAIN_THREAD_ID){
            //printf("mandei atualizar...");
            AtualizaTextura();
            //printf("resultado: %d\n",precisaAtualizar);
        }
        #endif

        SDL_RenderCopyEx(renderer, text, &frames[frameAtual], &enquadrado, -angulo, &pivoInteiro, flip);
        //printf("%d %d\n",pivoInteiro.x,pivoInteiro.y);
        for (unsigned int i=0;i<filhos.size();i++){
            filhos[i]->Desenha();
        }
        return 0;
    }

    void DesenhaOffScreen(PIGOffscreenRenderer offRender){
        SDL_Texture *textAux = SDL_CreateTextureFromSurface(offRender->GetRenderer(), bitmap);
        SDL_Rect rectAux = dest;
        rectAux.y = offRender->GetAltura() - alt - pos.y;
        SDL_RenderCopyEx(offRender->GetRenderer(), textAux, &frames[frameAtual], &rectAux, -angulo, &pivoInteiro, flip);
        SDL_DestroyTexture(textAux);
        for (unsigned int i=0;i<filhos.size();i++)
            filhos[i]->DesenhaOffScreen(offRender);
    }

    void AtualizaPixels(int retiraFundo = 1, int opacidadeObj = 255) {
        if (!pixels) return;

        Uint32 *pix32 = (Uint32 *)bitmap->pixels;
        for (int h = 0; h < bitmap->h; h++) {
            for (int w = 0; w < bitmap->w; w++) {
                SDL_GetRGBA((Uint32)*pix32, bitmap->format, &(pixels[h][w].r), &(pixels[h][w].g), &(pixels[h][w].b), &(pixels[h][w].a));
                pix32++;
            }
        }

        SetOpacidade(opacidadeObj);
        PreparaTextura(retiraFundo);
    }

    inline PIGCor **GetPixels() {
        return pixels;
    }

    inline string GetNomeArquivo(){
        return nomeArquivo;
    }

};
typedef CPIGSprite *PIGSprite;
#endif // _CPIGSPRITE_
