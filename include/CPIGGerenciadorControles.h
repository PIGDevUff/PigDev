#ifndef _CPIGGERENCIADORCONTROLE_
#define _CPIGGERENCIADORCONTROLE_

#include "CPIGControle.h"

class CPIGGerenciadorControles{

private:

static int qtdControles;
static PIGControle controles[MAX_CONTROLES];

public:

static void Inicia(){
    qtdControles = SDL_NumJoysticks();
    for(int i = 0; i < qtdControles; ++i) {
        controles[i] = new CPIGControle(i);
    }
}

static void Encerra(){
    for(int i = 0; i < qtdControles; ++i) {
        delete controles[i];
    }
}

static int BotaoPressionado(int idControle,int botao){
    return controles[idControle]->BotaoPressionado((SDL_GameControllerButton)botao);
}

static int EixoAcionado(int idControle,int eixo){
    return controles[idControle]->EixoAcionado((SDL_GameControllerAxis)eixo);
}

static float EixoAcionadoPercentual(int idControle,int eixo){
    return controles[idControle]->EixoAcionadoPercentual((SDL_GameControllerAxis)eixo);
}

static int GetQtdEixos(int idControle){
    return controles[idControle]->GetQtdEixos();
}

static int GetQtdBotoes(int idControle){
    return controles[idControle]->GetQtdBotoes();
}

static void GetNome(int idControle,char *nomeControle){
    controles[idControle]->GetNome(nomeControle);
}



};

int CPIGGerenciadorControles::qtdControles;
PIGControle CPIGGerenciadorControles::controles[MAX_CONTROLES];
#endif // _CPIGGERENCIADORCONTROLE_
