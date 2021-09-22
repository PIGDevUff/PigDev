#ifndef _CPIGLABEL_
#define _CPIGLABEL_

#include "CPIGImagem.h"

class CPIGLabel: public CPIGImagem{

private:
std::string frase;
int fonte;

void AtualizaTextura(){
    if (bitmap){
        SDL_FreeSurface(bitmap);
        LiberaTextura();
    }

    PIGMapaCaracteres mapa = CPIGGerenciadorFontes::GetFonte(fonte);
    largOriginal = larg = mapa->GetLarguraPixelsString(frase);
    altOriginal = alt = mapa->GetFonteAscent()+mapa->GetFonteDescent()+5;

    PIGOffscreenRenderer off = new CPIGOffscreenRenderer(alt,larg,1);
    off->Ativa();
    mapa->Escreve(frase,0,0,false,coloracao,PIG_TEXTO_ESQUERDA,0);
    bitmap = SDL_ConvertSurfaceFormat(off->GetSurface(),SDL_PIXELFORMAT_RGBA32,0);
    delete off;

    DefineFrame(0,{0,0,larg,alt});
    MudaFrameAtual(0);

    idTextura = PreparaTextura(0);
}

public:

CPIGLabel(std::string texto,int numFonte,PIG_Cor corFonte=BRANCO,int idJanela=0):
    CPIGImagem(idJanela){
    fonte = numFonte;
    frase = texto;
    SetColoracao(corFonte);
    if (frase!="")
        AtualizaTextura();
    //printf("label criado em %d,%d\n",(int)pos.x,(int)pos.y);
}

void SetTexto(std::string texto){
    frase = texto;
    AtualizaTextura();
}

void SetFonte(int numFonte){
    fonte = numFonte;
    AtualizaTextura();
}

int GetAltura(){
    return alt;
}

int GetLargura(){
    return larg;
}

std::string GetTexto(){
    return frase;
}

int GetFonte(){
    return fonte;
}

virtual int Desenha() override{
    CPIGImagem::Desenha();
}

};

typedef CPIGLabel* PIGLabel;
#endif // _CPIGLABEL_
