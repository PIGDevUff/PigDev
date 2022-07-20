#ifndef _CPIGOFFSCREENRENDERER_
#define _CPIGOFFSCREENRENDERER_

#include "CPIGOffscreenLayer.h"

class CPIGOffscreenRenderer{

private:

PIGOffscreenLayer layers[PIG_MAX_CAMADAS_OFFSCREEN];
int qtdLayers,maxLayers;

int alt,larg,depth;
double px,py;
double ang;
PIGCor corAtual;
PIGCor (*userFunctionPintarArea)(int, int, int, int, PIGCor, PIGCor);

public:

    SDL_Surface *GetSurface(int layer=0){
        layers[layer]->Ativa();
        SDL_Surface *resp = layers[layer]->GetSurface();
        layers[layer]->Desativa();
        return resp;
    }

    int GetAltura(){
        return alt;
    }

    int GetLargura(){
        return larg;
    }

    int GetDepth(){
        return depth;
    }

    void MergeSurface(int layerSuperior, int layerInferior){
        layers[layerInferior]->Merge(layers[layerSuperior]);
    }

    CPIGOffscreenRenderer(int altura,int largura,int qtdMaxCamadas=10){
        alt = altura;
        larg=largura;
        depth = 32; //32 bits por pixel
        maxLayers = qtdMaxCamadas;
        qtdLayers = maxLayers;
        for (int i=0;i<maxLayers;i++){
            layers[i] = new CPIGOffscreenLayer(alt,larg);
        }

        userFunctionPintarArea = NULL;

        px = py = 1;
        ang = 0;
        corAtual = BRANCO;
    }

    void Ativa(int layer=0){
        layers[layer]->Ativa();
    }

    void Desativa(int layer=0){
        layers[layer]->Desativa();
    }

    void SalvarImagemBMP(char *nomeArq,int layer=0){
        SDL_Surface *s = layers[layer]->GetSurface();
        SDL_SaveBMP(s,nomeArq);
        SDL_FreeSurface(s);
    }

    void SalvarImagemPNG(char *nomeArq,int layer=0){
        SDL_Surface *s = layers[layer]->GetSurface();
        IMG_SavePNG(s,nomeArq);
        SDL_FreeSurface(s);
    }

    void DefineFuncaoPintarArea(PIGCor (*funcao)(int, int, int, int, PIGCor, PIGCor)){
        userFunctionPintarArea = funcao;
    }

    void PintarArea(int posicaoX, int posicaoY, PIGCor cor, int layer=0){
        layers[layer]->PintarArea(posicaoX,posicaoY,cor,userFunctionPintarArea);
    }

    void MoveCanetaPara(double nx,double ny){
        px = nx;
        py = ny;
    }

    void GiraCanetaHorario(double angulo){
        ang -= angulo;
    }

    void GiraCanetaAntiHorario(double angulo){
        ang += angulo;
    }

    void GiraAnguloFixo(double angulo){
        ang = angulo;
    }

    double GetAngAtual(){
        return ang;
    }

    void AvancaCaneta(double distancia,int layer=0){
        double nx = px + cos(ang*M_PI/180.0)*distancia;
        double ny = py + sin(ang*M_PI/180.0)*distancia;
        layers[layer]->Ativa();
        PIGDesenhaLinhaSimples(px,py,nx,ny,corAtual);
        layers[layer]->Desativa();
        px = nx;
        py = ny;
    }

    void MudaCorAtualCaneta(PIGCor novaCor){
        corAtual = novaCor;
    }

    double GetXCaneta(){
        return px;
    }

    double GetYCaneta(){
        return py;
    }

    PIGOffscreenLayer *GetLayer(int indice){
        if (indice<qtdLayers){
            return &layers[indice];
        }else throw CPIGErroIndice(indice,"layer do renderizador offscreen");
    }

    ~CPIGOffscreenRenderer(){
        for (int i=0;i<maxLayers;i++){
            delete layers[i];
        }
    }

};

typedef CPIGOffscreenRenderer* PIGOffscreenRenderer;
#endif // _CPIGOFFSCREENRENDERER_
