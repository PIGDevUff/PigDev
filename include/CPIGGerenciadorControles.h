#ifndef _CPIGGERENCIADORCONTROLE_
#define _CPIGGERENCIADORCONTROLE_

#include "CPIGControle.h"

class CPIGGerenciadorControles{

private:

static int qtdControles;
static PIGControle controles[PIG_MAX_CONTROLES];

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

static PIGControle GetControle(int idControle){
    return controles[idControle];
}

};

int CPIGGerenciadorControles::qtdControles;
PIGControle CPIGGerenciadorControles::controles[PIG_MAX_CONTROLES];
#endif // _CPIGGERENCIADORCONTROLE_
