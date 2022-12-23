#ifndef _CPIGGERENCIADORANIMACOES_
#define _CPIGGERENCIADORANIMACOES_

#include "CPIGAnimacao.h"
#include "CPIGRepositorio.h"

class CPIGGerenciadorAnimacoes: public CPIGRepositorio<PIGAnimacao>{

public:

    CPIGGerenciadorAnimacoes():CPIGRepositorio<PIGAnimacao>(PIG_MAX_ANIMACOES,"CPIGAnimacao"){}

    inline int CriaAnimacao(string nomeArquivoBMP, int retiraFundo=1, PIGCor *corFundo=NULL, int idJanela=0){
        return Insere(new CPIGAnimacao(ProxID(),nomeArquivoBMP,retiraFundo,corFundo,idJanela));
    }

    inline int CriaAnimacao(PIGAnimacao animaBase, int retiraFundo=1, PIGCor *corFundo=NULL, int idJanela=0){
        return Insere(new CPIGAnimacao(ProxID(),animaBase,retiraFundo,corFundo,idJanela));
    }

    inline int CriaAnimacao(PIGObjeto objetoBase, int retiraFundo=1, PIGCor *corFundo=NULL, int idJanela=0){
        return Insere(new CPIGAnimacao(ProxID(),objetoBase,retiraFundo,corFundo,idJanela));
    }

};
CPIGGerenciadorAnimacoes pigGerAnimacoes;
#endif //_CPIGGERENCIADORANIMACOES_
