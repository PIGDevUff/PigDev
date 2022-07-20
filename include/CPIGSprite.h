#ifndef _CPIGSPRITE_
#define _CPIGSPRITE_

#include "CPIGAutomacao.h"
#include "CPIGImagem.h"
#include "CPIGOffscreenRenderer.h"

class CPIGSprite: public CPIGImagem{

protected:

PIGCor **pixels;
PIGAutomacao automacao;
int tipoFixo;
vector<CPIGSprite*> filhos;

private:

void ExtraiPixels() {

    pixels = (PIGCor **)malloc(sizeof(PIGCor *) * bitmap->h);
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

protected:

void AplicaTransicao(PIGEstadoTransicao estado){
    Move(estado.x,estado.y);
    if (estado.alt!=alt||estado.larg!=larg) SetDimensoes(estado.alt,estado.larg);
    if (!(estado.cor==BRANCO)) SetColoracao(estado.cor);
    if (estado.opacidade!=coloracao.a) SetOpacidade(estado.opacidade);
    if (estado.ang!=angulo) SetAngulo(estado.ang);
}

public:


//Construtor para arquivos de vídeo ou Componentes
CPIGSprite(int idSprite,int altura,int largura,string nomeArq,int janela=0):CPIGImagem(idSprite,altura,largura,nomeArq,janela){
    pixels = NULL;
    automacao = NULL;
}

//Construtor para sprite "vazio", cuja imagem será gerada posteriormente
CPIGSprite(int janela):CPIGImagem(janela){
    pixels = NULL;
    automacao = NULL;
}

//Construtor básico para leitura de imagens digitais
CPIGSprite(int idSprite,string nomeArq,int retiraFundo=1,PIGCor *corFundo=NULL,int janela=0):
    CPIGImagem(idSprite,nomeArq,retiraFundo,corFundo,janela){
    automacao = NULL;
    ExtraiPixels();
}

//Construtor para imagens provenientes do renderizador offscreen
CPIGSprite(int idSprite,PIGOffscreenRenderer offRender, int retiraFundo=1,PIGCor *corFundo=NULL,int janela=0):
    CPIGImagem(idSprite,offRender,retiraFundo,corFundo,janela){
    automacao = NULL;
    ExtraiPixels();
}

//Construtor para Sprite "copiado" de outro Sprite
CPIGSprite(int idSprite,CPIGSprite *spriteBase,int retiraFundo=1,PIGCor *corFundo=NULL,int janela=0):
    CPIGImagem(idSprite,spriteBase,retiraFundo,corFundo,janela){

    ExtraiPixels();
    if (spriteBase->automacao){
        automacao = new CPIGAutomacao(id,spriteBase->automacao);
    }else automacao = NULL;
}

//Destrutor para todos os tipos de Sprites
~CPIGSprite(){
    if (pixels){
        for (int i = 0; i < bitmap->h; i++)
            free(pixels[i]);
        free(pixels);
    }

    if (automacao) delete automacao;
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

void InsereTransicao(PIGTransicao t,PIGAutomacao *automaExt=NULL){
    if (automaExt==NULL) automaExt=&automacao;
    if (*automaExt==NULL)
        *automaExt = new CPIGAutomacao(id);
    (*automaExt)->InsereTransicao(t);
}

void InsereTransicao(double tempo, PIGEstadoTransicao estado,PIGAutomacao *automaExt=NULL){
    if (automaExt==NULL) automaExt=&automacao;
    if (*automaExt==NULL)
        *automaExt = new CPIGAutomacao(id);
    (*automaExt)->InsereTransicao(new CPIGTransicao(tempo,estado));
}

void LeTransicoes(string nomeArq,PIGAutomacao *automaExt=NULL){
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
    int auxx = pos.x;
    int auxy = pos.y;
    if ( automaExt ==NULL) automaExt=&automacao;
    if (*automaExt)
        (*automaExt)->IniciaAutomacao({auxx,auxy,alt,larg,angulo,coloracao,coloracao.a});
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

void InsereAcao(double tempo, double repeticao, PIGFuncaoSimples acao, void *param,PIGAutomacao *automaExt=NULL){
    if (automaExt==NULL) automaExt=&automacao;
    if (*automaExt==NULL)
        *automaExt = new CPIGAutomacao(id);

    (*automaExt)->InsereAcao(acao,tempo,repeticao,param);
}

void LimpaAcoes(PIGAutomacao *automaExt=NULL){
    if (automaExt==NULL) automaExt=&automacao;
    if (*automaExt) (*automaExt)->LimpaAcoes();
}

void DefineTipoTransicao(PIGTipoTransicao tipo,PIGAutomacao *automaExt=NULL){
    if (automaExt==NULL) automaExt=&automacao;
    if (*automaExt) (*automaExt)->SetTipoTransicao(tipo);
}

virtual void SetAngulo(double a)override{
    CPIGImagem::SetAngulo(a);
    double delta = a-angulo;
    double pivoRealX = pos.x+pivoAbs.x;
    double pivoRealY = pos.y+(alt-pivoAbs.y);

    for (int i=0;i<filhos.size();i++){
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

virtual void Desloca(double dx, double dy)override{
    CPIGImagem::Desloca(dx,dy);
    for (int i=0;i<filhos.size();i++){
        if (filhos[i]->tipoFixo!=0)
            filhos[i]->Desloca(dx,dy);
    }
}

void DesenhaOffScreen(PIGOffscreenRenderer offRender){
    offRender->Ativa();
    Desenha();
    offRender->Desativa();
    for (int i=0;i<filhos.size();i++)
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
    idTextura = PreparaTextura(retiraFundo);
}

PIGCor **GetPixels() {
    return pixels;
}

};
typedef CPIGSprite *PIGSprite;
#endif // _CPIGSPRITE_
