#ifndef _CPIGGERENCIADOROBJETOS_
#define _CPIGGERENCIADOROBJETOS_

#include "CPIGObjeto.h"
#include "CPIGRepositorio.h"

class CPIGGerenciadorObjetos: public CPIGRepositorio<PIGObjeto>{

public:

    CPIGGerenciadorObjetos():CPIGRepositorio<PIGObjeto>(PIG_MAX_OBJETOS,"CPIGObjeto"){}

    inline int CriaObjeto(string nomeArquivoBMP, int retiraFundo=1, PIGCor *corFundo=NULL,int idJanela=0){
        return Insere(new CPIGObjeto(ProxID(),nomeArquivoBMP,retiraFundo,corFundo,idJanela));
    }

    inline int CriaObjeto(PIGObjeto objBase, int retiraFundo=1, PIGCor *corFundo=NULL, int idJanela=0){
        return Insere(new CPIGObjeto(ProxID(),objBase,retiraFundo,corFundo,idJanela));
    }

    inline int CriaObjetoOffScreen(PIGOffscreenRenderer offRenderer, int retiraFundo=1, PIGCor *corFundo=NULL, int idJanela=0){
        return Insere(new CPIGObjeto(ProxID(),offRenderer,retiraFundo,corFundo,idJanela));
    }
};
CPIGGerenciadorObjetos pigGerObjetos;
#endif //_CPIGGERENCIADOROBJETOS_
