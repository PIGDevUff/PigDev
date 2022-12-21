#ifndef _CPIGGERENCIADORGDP_
#define _CPIGGERENCIADORGDP_

#include "CPIGGeradorParticulas.h"
#include "CPIGRepositorio.h"

class CPIGGerenciadorGDP: public CPIGRepositorio<PIGGeradorParticulas>{

public:

    CPIGGerenciadorGDP():CPIGRepositorio<PIGGeradorParticulas>(PIG_MAX_GERADORPARTICULAS,"CPIGeradorParticulas"){}

    inline int CriaGeradorParticulas(int maxParticulas, string nomeArquivoBMP, int audioCriacao, int audioEncerramento, bool retiraFundo=true, PIGCor *corFundo=NULL, int idJanela=0){
        return Insere(new CPIGGeradorParticulas(ProxID(),maxParticulas,nomeArquivoBMP,audioCriacao,audioEncerramento,retiraFundo,corFundo,idJanela));
    }

    inline int CriaGeradorParticulas(int maxParticulas, PIGAnimacao animacaoBase, int audioCriacao, int audioEncerramento, bool retiraFundo=true, PIGCor *corFundo=NULL, int idJanela=0){
        return Insere(new CPIGGeradorParticulas(ProxID(),maxParticulas,animacaoBase,audioCriacao,audioEncerramento,retiraFundo,corFundo,idJanela));
    }

    inline int CriaGeradorParticulas(int maxParticulas, PIGObjeto objetoBase, int audioCriacao, int audioEncerramento, bool retiraFundo=true, PIGCor *corFundo=NULL, int idJanela=0){
        return Insere(new CPIGGeradorParticulas(ProxID(),maxParticulas,objetoBase,audioCriacao,audioEncerramento,retiraFundo,corFundo,idJanela));
    }
};
CPIGGerenciadorGDP pigGerGDP;
#endif //_CPIGGERENCIADORGDP_
