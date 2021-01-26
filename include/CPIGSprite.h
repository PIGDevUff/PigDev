#ifndef _CPIGSPRITE_
#define _CPIGSPRITE_

#include "CPIGAutomacao.h"

class CPIGSprite{

protected:
PIGPonto2D pos;
PIGPonto2D pivoRelativo;
int alt,larg,altOriginal,largOriginal;
int idJanela,*altJanela;
double angulo,pivoX,pivoY;
SDL_Rect dest;
int frameAtual;
std::unordered_map<int,SDL_Rect> frames;
SDL_Texture* text;
SDL_Renderer* renderer;
SDL_RendererFlip flip;
SDL_Surface* bitmap;
PIG_Cor coloracao;
PIG_Cor **pixels;
int opacidade;
std::string nomeArquivo;
PIGAutomacao automacao;
int tipoFixo;
vector<CPIGSprite*> filhos;

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
    automacao = NULL;
    tipoFixo = 0;
    IniciaCor();
    IniciaJanela(janela);
    IniciaDimensoes(altura,largura);
    IniciaOrientacao();
    //pai = NULL;
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
    pivoRelativo = {0,alt};
    pivoX = pivoY = -1;

    dest.x = pos.x;
    dest.y = *altJanela-pos.y-alt;
    dest.h = alt;
    dest.w = larg;

    frames[0].x = frames[0].y = 0;
    frames[0].h = alt;
    frames[0].w = larg;

    flip = SDL_FLIP_NONE;
}

void AplicaTransicao(PIG_EstadoTransicao estado){
    //fprintf(arqP,"set %f %d %d %d %d %f\n",estado.tempoAtual,estado.x,estado.y,estado.alt,estado.larg,estado.ang);
    Move(estado.x,estado.y);
    if (estado.alt!=alt||estado.larg!=larg) SetDimensoes(estado.alt,estado.larg);
    if (!(estado.cor==BRANCO)) SetColoracao(estado.cor);
    if (estado.opacidade!=opacidade) SetOpacidade(estado.opacidade);
    if (estado.ang!=angulo) SetAngulo(estado.ang);
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

    if (spriteBase->automacao)
        automacao = new CPIGAutomacao(1,spriteBase->automacao);
}

//Construtor para sprite "vazio", cuja imagem será gerada posteriormente
CPIGSprite(int janela){
    idJanela = janela;
    nomeArquivo = "";
    pivoRelativo = {0,alt};
    angulo = 0;
    flip = PIG_FLIP_NENHUM;
    text = NULL;
    bitmap = NULL;
    frameAtual = 0;
    frames[0] ={0,0,0,0};
    pixels = NULL;
    automacao = NULL;
    altJanela = CPIGGerenciadorJanelas::GetJanela(idJanela)->GetAltura();
    renderer = CPIGGerenciadorJanelas::GetJanela(idJanela)->GetRenderer();
    //pai = NULL;
}

int RecebeFilho(CPIGSprite *filho, int fixo){
    filho->tipoFixo = fixo;
    filhos.push_back(filho);
    return 1;
}

int Retirafilho(CPIGSprite *filho){
    for (int i=0;i<filhos.size();i++)
        if (filhos[i] == filho){
            filhos.erase(filhos.begin()+i);
            return 1;
        }
    return 0;
}

void InsereTransicao(PIGTransicao t){
    if (!automacao)
        automacao = new CPIGAutomacao(1);
    automacao->InsereTransicao(t);
}

void InsereTransicao(double tempo, PIG_EstadoTransicao estado){
    if (!automacao)
        automacao = new CPIGAutomacao(1);
    automacao->InsereTransicao(new CPIGTransicao(tempo,estado));
}

void LeTransicoes(string nomeArq){
    int dx=0,dy=0,dAlt=0,dLarg=0,dOpa=0;
    double dAng=0,tempo=0;
    PIG_Cor dCor=BRANCO;
    if (!automacao){
        automacao = new CPIGAutomacao(1);
    }
    //printf("arquivo %s\n",nomeArq.c_str());
    FILE *arq = fopen(nomeArq.c_str(),"r");
    while (fscanf(arq,"%lf %d %d %d %d %lf %d %d %d %d %d\n",&tempo,&dx,&dy,&dAlt,&dLarg,&dAng,&dCor.r,&dCor.g,&dCor.b,&dCor.a,&dOpa)>0){
        //printf("%f %d %d %d %d %f %d %d %d %d %d\n",tempo,dx,dy,dAlt,dLarg,dAng,dCor.r,dCor.g,dCor.b,dCor.a,dOpa);
        automacao->InsereTransicao(new CPIGTransicao(tempo,{dx,dy,dAlt,dLarg,dAng,dCor,dOpa}));
    }
    fclose(arq);
}

void IniciaAutomacao(){
    if (automacao)
        automacao->IniciaAutomacao({pos.x,pos.y,alt,larg,angulo,coloracao,opacidade});
}

void LimpaTransicoes(){
    if (automacao) automacao->LimpaTransicoes();
}

void TrataAutomacao(){
    if (automacao){
        PIGTransicao t = automacao->GetTransicaoAtual();
        if (t) AplicaTransicao(t->GetEstado());
        automacao->TrataAcao();
    }
}

void InsereAcao(double tempo, double repeticao, PIG_FuncaoSimples acao, int idSprite, void *param){
    if (!automacao)
        automacao = new CPIGAutomacao(idSprite);
    automacao->InsereAcao(acao,tempo,repeticao,param);
}

void DefineTipoTransicao(PIG_TipoTransicao tipo){
    if (automacao) automacao->SetTipoTransicao(tipo);
}

//Destrutor para todos os tipos de Sprites
~CPIGSprite(){
    if (pixels){
        for (int i = 0; i < bitmap->h; i++)
            free(pixels[i]);
        free(pixels);
    }

    //for (int i=0;i<filhos.size();i++)
    //    delete filhos[i];

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

int GetIdJanela(){
    return idJanela;
}

void DefineFrame(int idFrame,SDL_Rect r){
    frames[idFrame] = r;
}

PIGPonto2D GetXY(){
    return pos;
}

void SetColoracao(PIG_Cor cor){
    coloracao = cor;
    SDL_SetTextureColorMod(text,cor.r,cor.g,cor.b);
}

PIG_Cor GetColoracao(){
    return coloracao;
}

void Rotaciona(double px,double py, double graus){
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

    //double cosseno = cos(delta*M_PI/180.0);
    //double seno = sin(delta*M_PI/180.0);
    double pivoRealX = pos.x+pivoRelativo.x;
    double pivoRealY = pos.y+(alt-pivoRelativo.y);

    for (int i=0;i<filhos.size();i++){
        if (filhos[i]->tipoFixo==0) continue;
        if (filhos[i]->tipoFixo==1){
            filhos[i]->Rotaciona(pivoRealX,pivoRealY,delta);
        }else{
            //double px = cosseno*pivoRelativo.x - seno*(pivoRelativo.y-alt) + pos.x;
            //double py = seno*pivoRelativo.x + cosseno*(pivoRelativo.y-alt) + pos.y;

            //printf("pivo absoluto %f,%f ",px,py);

            //double dx = -filhos[i]->pivoRelativo.x;//-filhos[i]->pos.x;
            //double dy = alt-filhos[i]->pivoRelativo.y;//-(filhos[i]->alt-filhos[i]->pos.y);

            //printf("dist relat %f,%f\n",dx,dy);

            //double nx = cosseno*dx - seno*dy;
            //double ny = seno*dx + cosseno*dy;
            //nx+filhos[i]->pivoRelativo.x+filhos[i]->pos.x-(filhos[i]->pivoRelativo.x+filhos[i]->pos.x-pivoRealX)
            //ny+{filhos[i]->pos.y-(filhos[i]->alt-filhos[i]->pivoRelativo.y)} -(filhos[i]->pos.y-(filhos[i]->alt-filhos[i]->pivoRelativo.y)+ alt-filhos[i]->pivoRelativo.y;)
            double pivoFilhoX = filhos[i]->pivoRelativo.x+filhos[i]->pos.x;
            double pivoFilhoY = filhos[i]->pos.y+filhos[i]->alt-filhos[i]->pivoRelativo.y;
            filhos[i]->Rotaciona(pivoFilhoX, pivoFilhoY,delta);
            filhos[i]->Desloca(-pivoFilhoX+pivoRealX,-(alt-filhos[i]->pivoRelativo.y));//-pivoFilhoY-(alt-filhos[i]->pivoRelativo.y));
            //filhos[i]->Move(nx+pivoRealX,ny-dy);
            //filhos[i]->SetAngulo(filhos[i]->GetAngulo()+delta);
        }


    }
    //system("pause");
}

double GetAngulo(){
    return angulo;
}

void SetFlip(PIG_Flip valor){
    flip = valor;
}

PIG_Flip GetFlip(){
    return flip;
}

//Pivô relativo ao ponto (0,0) por meio de soma
void SetPivo(int px,int py){
    pivoRelativo.x = px;
    pivoRelativo.y = alt-py;
    pivoX = pivoY = -1; //não será utilizado um pivo proporcional ao tamanho;
}

//Pivo relativo ao ponto (0,0) por meio de multiplicação
void SetPivo(double px,double py){
    pivoX = px;
    pivoY = py;
    pivoRelativo.x = px*larg;
    pivoRelativo.y = alt*(1-py);
}

//recupera o ponto pivô
PIGPonto2D GetPivo(){
    return pivoRelativo;
}

inline virtual void Move(double nx,double ny){
    Desloca(nx-pos.x,ny-pos.y);
}


virtual void Desloca(double dx, double dy){
    pos.x += dx;
    pos.y += dy;
    dest.x = pos.x;
    dest.y = *altJanela-alt-pos.y;
    for (int i=0;i<filhos.size();i++){
        filhos[i]->Desloca(dx,dy);
        //printf("desloc %f,%f\n",filhos[i]->pos.x,filhos[i]->pos.y);
    }
}

virtual void SetDimensoes(int altura,int largura){
    dest.h = alt = altura;
    dest.w = larg = largura;
    dest.x = pos.x;
    dest.y = *altJanela-alt-pos.y;

    if (pivoX>0){
        SetPivo(pivoX,pivoY);
    //}else pivoRelativo.y = alt-pivoRelativo.y;//necessário porque o poivô relativo é usado com eixo Y invertido (para baixo)
    }else SetPivo(pivoRelativo.x,pivoRelativo.y);
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
    while (fscanf(arq,"%d %d %d %d %d\n",&idFrame,&xBitmap,&yBitmap,&altFrame,&largFrame) == 5){
        DefineFrame(idFrame,{xBitmap,yBitmap,largFrame,altFrame});
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
    dest.y = *altJanela-alt-pos.y;
    SDL_Rect enquadrado = dest;
    //if (fixoPai)
    //printf("%d,%d,%d,%d\n",dest.x,*altJanela-dest.y,dest.h,dest.w);
    SDL_Point p = {pivoRelativo.x,pivoRelativo.y};
    CPIGGerenciadorJanelas::GetJanela(idJanela)->ConverteCoordenadaWorldScreen(enquadrado.x,enquadrado.y,enquadrado.x,enquadrado.y);
    SDL_RenderCopyEx(renderer, text, &frames[frameAtual], &enquadrado, -angulo, &p, flip);
    //printf("%d %d\n",pivoRelativo.x,pivoRelativo.y);
    for (int i=0;i<filhos.size();i++){
        filhos[i]->Desenha();
    }
    return 0;
}

void DesenhaOffScreen(PIGOffscreenRenderer offRender){
    SDL_Texture *textAux = SDL_CreateTextureFromSurface(offRender->GetRenderer(), bitmap);
    SDL_Rect rectAux = dest;
    rectAux.y = offRender->GetAltura() - alt - pos.y;
    SDL_Point p = {pivoRelativo.x,pivoRelativo.y};
    SDL_RenderCopyEx(offRender->GetRenderer(), textAux, &frames[frameAtual], &rectAux, -angulo, &p, flip);
    SDL_DestroyTexture(textAux);
    for (int i=0;i<filhos.size();i++)
        filhos[i]->DesenhaOffScreen(offRender);
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
