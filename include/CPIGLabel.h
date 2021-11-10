#ifndef _CPIGLABEL_
#define _CPIGLABEL_

#include "CPIGSprite.h"

class CPIGLabel:public CPIGSprite{

private:
std::string frase;
int fonte;
PIGCor cor;

void AtualizaTextura(){
    PIGMapaCaracteres mapa = CPIGGerenciadorFontes::GetFonte(fonte);
    larg = mapa->GetLarguraPixelsString(frase);
    alt = mapa->GetFonteAscent()+mapa->GetFonteDescent()+5;
    if (text) SDL_DestroyTexture(text);
    text = SDL_CreateTexture(CPIGGerenciadorJanelas::GetJanela(idJanela)->GetRenderer(),SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,larg,alt);
    mapa->Escreve(frase,text,cor);
    dest.w = larg;
    dest.h = alt;
    frames[0].x = frames[0].y = 0;
    frames[0].h = alt;
    frames[0].w = larg;
}

public:

CPIGLabel(std::string texto,int numFonte,PIGCor corFonte=BRANCO,int idJanela=0):CPIGSprite(idJanela){
    fonte = numFonte;
    text = NULL;
    cor = corFonte;
    frase = texto;
    AtualizaTextura();
}

void SetTexto(std::string texto){
    frase = texto;
    AtualizaTextura();
}

void SetFonte(int numFonte){
    fonte = numFonte;
    AtualizaTextura();
}

void SetCor(PIGCor novaCor){
    cor = novaCor;
    AtualizaTextura();
}

int GetAltura(){
    return alt;
}

int GetLargura(){
    return larg;
}

string GetTexto(){
    return frase;
}

int GetFonte(){
    return fonte;
}

PIGCor GetCor(){
    return cor;
}

};

typedef CPIGLabel* PIGLabel;
#endif // _CPIGLABEL_
