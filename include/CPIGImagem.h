#ifndef _CPIGIMAGEM_
#define _CPIGIMAGEM_

#include "CPIGOffscreenRenderer.h"

class CPIGImagem{

protected:

int id,idJanela;
int alt,larg,altOriginal,largOriginal;
PIGPonto2D pos,pivoAbs,pivoProporcional;
bool usaPivoRelativo;
double angulo;
unordered_map<int,SDL_Rect> frames;
PIGPonto2D supEsq,supDir,infEsq,infDir; //pontos que correspondem ŕ area da imagem a ser mostrada (valores duble)
SDL_RendererFlip flip;
SDL_Surface *bitmap;
PIGCor coloracao;
string nomeArquivo;
GLuint idTextura;
int frameAtual;
bool precisaAtualizar;

private:

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
    idJanela = janela;
    coloracao = BRANCO;
    altOriginal = alt = altura;
    largOriginal = larg = largura;
    pos = {0,0};
    angulo = 0;
    pivoAbs = {0,0};
    pivoProporcional = {0,0};
    usaPivoRelativo = false;
    flip = SDL_FLIP_NONE;
    frameAtual = 0;
    DefineFrame(frameAtual,{0,0,larg,alt});
    AtualizaFrame();
}

//prepara os valores dos pontos que delimitam a área da imagem a ser mostrada
void AtualizaFrame(){
    SDL_Rect r = frames[frameAtual];
    supDir = {(r.x+r.w)*1.0/largOriginal,r.y*1.0/altOriginal};
    supEsq = {r.x*1.0/largOriginal,r.y*1.0/altOriginal};
    infDir = {(r.x+r.w)*1.0/largOriginal,(r.y+r.h)*1.0/altOriginal};
    infEsq = {r.x*1.0/largOriginal,(r.y+r.h)*1.0/altOriginal};
}

protected:

GLuint PreparaTextura(int retiraFundo, PIGCor *corFundo=NULL){
    if (!bitmap) return 0;

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

    CPIGGerenciadorJanelas::GetJanela(idJanela)->FazCorrente();
    return PIGCriaTexturaSurface(bitmap);
}

void LiberaTextura(){
    if (idTextura!=0)
        glDeleteTextures(1,&idTextura);
}

virtual void AtualizaTextura(){
    if (this_thread::get_id()==PIG_MAIN_THREAD_ID){
        LiberaTextura();
        idTextura = PreparaTextura(1,NULL);
        precisaAtualizar = false;
    }
}

public:

int GetID(){
    return id;
}

//Construtor para arquivos de vídeo ou Componentes
CPIGImagem(int idSprite=-1,int altura=0,int largura=0,string nomeArq="",int janela=0){
    id = idSprite;
    nomeArquivo = nomeArq;
    IniciaBase(altura,largura,janela);
    bitmap = NULL;
    idTextura = 0;
}

//Construtor básico para leitura de imagens digitais
CPIGImagem(int idSprite,string nomeArq,int retiraFundo=1,PIGCor *corFundo=NULL,int janela=0){
    id = idSprite;

    CarregaImagem(nomeArq);//carrega o bitmap

    IniciaBase(bitmap->h,bitmap->w,janela);

    idTextura = PreparaTextura(retiraFundo,corFundo);
}

//Construtor para imagens provenientes do renderizador offscreen
CPIGImagem(int idSprite,PIGOffscreenRenderer offRender, int retiraFundo=1,PIGCor *corFundo=NULL,int janela=0){
    id = idSprite;
    nomeArquivo = "";

    SDL_Surface *surface = offRender->GetSurface();

    bitmap = SDL_CreateRGBSurfaceWithFormatFrom(surface->pixels,surface->w,surface->h,offRender->GetDepth(),surface->pitch,surface->format->format);

    IniciaBase(bitmap->h,bitmap->w,janela);

    idTextura = PreparaTextura(retiraFundo,corFundo);
}

//Construtor para Sprite "copiado" de outro Sprite
CPIGImagem(int idSprite,CPIGImagem *imagemBase,int retiraFundo=1,PIGCor *corFundo=NULL,int janela=0){
    id = idSprite;

    CarregaImagem(imagemBase->nomeArquivo);

    IniciaBase(bitmap->h,bitmap->w,janela);

    idTextura = PreparaTextura(retiraFundo,corFundo);

    frameAtual = imagemBase->frameAtual;
    frames = imagemBase->frames;
    AtualizaFrame();

    SetColoracao(imagemBase->coloracao);
    SetAngulo(imagemBase->angulo);
    SetFlip(imagemBase->flip);
    SetDimensoes(imagemBase->alt,imagemBase->larg);

    usaPivoRelativo = imagemBase->usaPivoRelativo;
    if (usaPivoRelativo){
        SetPivoProporcional(imagemBase->pivoProporcional);
    }else{
        pivoProporcional = imagemBase->pivoProporcional;
        SetPivoAbsoluto(imagemBase->pivoAbs);
    }

    Move(imagemBase->pos.x,imagemBase->pos.y);
}

//Destrutor para todos os tipos de Sprites
~CPIGImagem(){
    if (nomeArquivo == ""){
        if (bitmap) SDL_FreeSurface(bitmap);
    }else{
        #ifdef PIG_SHARE_BITMAP
        CPIGAssetLoader::FreeImage(nomeArquivo);
        #else
        if (bitmap) SDL_FreeSurface(bitmap);
        #endif
    }
    LiberaTextura();
}

int GetIdJanela(){
    return idJanela;
}

void DefineFrame(int idFrame,SDL_Rect r){
    //printf("entrei %d\n",idFrame);
    unordered_map<int,SDL_Rect>::const_iterator it = frames.find(idFrame);
    //printf(" terminei busca");
    if (it !=frames.end()){
        //printf("sera 1 ? %d (%d,%d,%d,%d)\n",idFrame,r.x,r.y,r.w,r.h);
        frames.erase(it);
    }
    //printf("sera ? %d (%d,%d,%d,%d)\n",idFrame,r.x,r.y,r.w,r.h);
    frames.insert({idFrame,r});
    //printf("frame %d ok\n",idFrame);
}

PIGPonto2D GetXY(){
    return pos;
}

void SetColoracao(PIGCor cor){
    coloracao = cor;
}

PIGCor GetColoracao(){
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
    angulo = a;
}

double GetAngulo(){
    return angulo;
}

void SetFlip(PIGFlip valor){
    flip = valor;
}

PIGFlip GetFlip(){
    return flip;
}

//Pivô relativo ao ponto (0,0) por meio de soma
void SetPivoAbsoluto(PIGPonto2D pivo){
    pivoAbs = pivo;
    usaPivoRelativo = false;
}

//Pivo relativo ao ponto (0,0) por meio de multiplicaçăo
void SetPivoProporcional(PIGPonto2D pivo){
    pivoProporcional = pivo;
    pivoAbs = {pivoProporcional.x*larg,pivoProporcional.y*alt};
    usaPivoRelativo = true;
}

//recupera o ponto pivô
PIGPonto2D GetPivo(){
    return pivoAbs;
}

inline virtual void Move(double nx,double ny){
    Desloca(nx-pos.x,ny-pos.y);
}

virtual void Desloca(double dx, double dy){
    pos.x += dx;
    pos.y += dy;
}

virtual void SetDimensoes(int altura,int largura){
    alt = altura;
    larg = largura;

    if (usaPivoRelativo){
        SetPivoProporcional(pivoProporcional);
    }else{
        SetPivoAbsoluto(pivoAbs);
    }
}

///---------------

virtual void GetDimensoes(int &altura, int &largura){
    altura = alt;
    largura = larg;
}

void GetDimensoesOriginais(int &altura,int &largura){
    altura = altOriginal;
    largura = largOriginal;
}

void SetOpacidade(int valor){
    coloracao.a = valor;
}

void RestauraDimensoesOriginais(){
    SetDimensoes(altOriginal,largOriginal);
}

int GetOpacidade(){
    return coloracao.a;
}

int MudaFrameAtual(int novoFrame){
    if (frames.find(novoFrame) == frames.end())
        return 0;
    frameAtual = novoFrame;
    AtualizaFrame();
    return 1;
}

int GetIDFrameAtual(){
    return frameAtual;
}

SDL_Rect *GetFrameAtual(){
    return &frames[frameAtual];
}

void CarregaArquivoFrames(string nomeArq){
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
    if (idTextura==0) return 0;
    //printf("%d\n",idTextura);
    CPIGGerenciadorJanelas::GetJanela(idJanela)->FazCorrente();

    glPushMatrix();

    glTranslated(pos.x+pivoAbs.x,pos.y+pivoAbs.y,0);

    //if (op)
    //    printf("%f,%f ",pos.x+pivoAbs.x,pos.y+pivoAbs.y);

    glRotatef(angulo,0.0f,0,1.0f);

    glTranslated(-pivoAbs.x,-pivoAbs.y,0); //esse é ponto pivo (-100,40) em relaçăo ao ponto referęncia do quad

    PIGPonto2D *ie = &infEsq,*id = &infDir,*se = &supEsq,*sd = &supDir;

    if (flip==PIG_FLIP_HORIZONTAL||flip==PIG_FLIP_HORIZ_VERT){
        PIGPonto2D *aux = ie; ie = id;id = aux;
        aux = se; se = sd; sd = aux;
    }
    if (flip==PIG_FLIP_VERTICAL||flip==PIG_FLIP_HORIZ_VERT){
        PIGPonto2D *aux = ie; ie = se; se = aux;
        aux = id; id = sd; sd = aux;
    }


    //if (op)
    //printf("%f,%f %f,%f %f,%f %f,%f\n",ie->x,ie->y,id->x,id->y,se->x,se->y,sd->x,sd->y);

    #ifdef PIGCOMTELA
        if (precisaAtualizar){//criada!=PIG_MAIN_THREAD_ID){
            //printf("mandei atualizar...");
            AtualizaTextura();
            //printf("resultado: %d\n",precisaAtualizar);
        }
        #endif

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_COLOR_MATERIAL);

    glBindTexture(GL_TEXTURE_2D,idTextura);
    glColor4ub(coloracao.r,coloracao.g,coloracao.b,coloracao.a);
    glBegin(GL_QUADS);
        glTexCoord2f(ie->x,ie->y);glVertex2i(0,0);
        glTexCoord2f(id->x,id->y);glVertex2i(0+larg,0);
        glTexCoord2f(sd->x,sd->y);glVertex2i(0+larg,0+alt);
        glTexCoord2f(se->x,se->y);glVertex2i(0,0+alt);
    glEnd();
    glBindTexture(GL_TEXTURE_2D,0);

    glDisable(GL_COLOR_MATERIAL);

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    return 0;
}

string GetNomeArquivo(){
    return nomeArquivo;
}


};
typedef CPIGImagem *PIGImagem;
#endif // _CPIGIMAGEM_
