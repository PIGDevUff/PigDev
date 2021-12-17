#ifndef _CPIGLABEL_
#define _CPIGLABEL_

#include "CPIGSprite.h"

class CPIGLabel:public CPIGSprite{

private:
string frase;
int fonte;
PIGCor corFonte;

void AtualizaTextura()override{

    PIGMapaCaracteres mapa = CPIGGerenciadorFontes::GetFonte(fonte);
    larg = mapa->GetLarguraPixelsString(frase);
    alt = mapa->GetFonteAscent()+mapa->GetFonteDescent()+5;

    if (this_thread::get_id()!=PIG_MAIN_THREAD_ID)
        CPIGGerenciadorJanelas::GetJanela(idJanela)->TravaRenderer();

    if (text) SDL_DestroyTexture(text);
    text = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,larg,alt);

    int erro = SDL_SetRenderTarget(renderer,text);
    if (!erro){
        SDL_SetRenderDrawColor(renderer,0,0,0,0);
        SDL_RenderClear(renderer);
        SDL_SetRenderTarget(renderer,NULL);
        mapa->Escreve(frase,text,corFonte);

        SetDimensoes(alt,larg);
        DefineFrame(0,{0,0,larg,alt});
        MudaFrameAtual(0);

        criada = this_thread::get_id();
    }else{
        SDL_DestroyTexture(text);
        text = NULL;
    }

    if (this_thread::get_id()!=PIG_MAIN_THREAD_ID)
        CPIGGerenciadorJanelas::GetJanela(idJanela)->DestravaRenderer();
}

public:

CPIGLabel(string texto, int numFonte, int idJanela=0):CPIGSprite(idJanela){
    fonte = numFonte;
    text = NULL;
    corFonte = BRANCO;
    frase = texto;
    AtualizaTextura();
}

inline void SetTexto(string texto){
    frase = texto;
    AtualizaTextura();
}

inline void SetFonte(int numFonte){
    fonte = numFonte;
    AtualizaTextura();
}

inline void SetCorFonte(PIGCor novaCor){
    corFonte = novaCor;
    AtualizaTextura();
}

inline int GetAltura(){
    return alt;
}

inline int GetLargura(){
    return larg;
}

inline string GetTexto(){
    return frase;
}

inline int GetFonte(){
    return fonte;
}

inline PIGCor GetCorFonte(){
    return corFonte;
}

};

typedef CPIGLabel* PIGLabel;
#endif // _CPIGLABEL_
