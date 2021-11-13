#ifndef _CPIGGERENCIADORGDP_
#define _CPIGGERENCIADORGDP_

#include "CPIGAnimacao.h"
#include "CPIGGeradorParticulas.h"

class CPIGGerenciadorGDP{

private:

    static CPIGRepositorio<PIGGeradorParticulas> *geradores;

public:

    static PIGGeradorParticulas GetGerador(int idGerador){
        return geradores->GetElemento(idGerador);
    }

    static void Inicia(){
        geradores = new CPIGRepositorio<PIGGeradorParticulas>(PIG_MAX_GERADORPARTICULAS,"geradores");
    }

    static void Encerra(){
        delete geradores;
    }

    static int CriaGeradorParticulas(int maxParticulas, string nomeArquivoBMP, int audioCriacao, int audioEncerramento, bool retiraFundo=true, PIGCor *corFundo=NULL, int idJanela=0){
        int id = geradores->ProxID();
        return geradores->Insere(new CPIGGeradorParticulas(id,maxParticulas,nomeArquivoBMP,audioCriacao,audioEncerramento,retiraFundo,corFundo,idJanela));
    }

    static int CriaGeradorParticulas(int maxParticulas, PIGAnimacao animacaoBase, int audioCriacao, int audioEncerramento, bool retiraFundo=true, PIGCor *corFundo=NULL, int idJanela=0){
        int id = geradores->ProxID();
        return geradores->Insere(new CPIGGeradorParticulas(id,maxParticulas,animacaoBase,audioCriacao,audioEncerramento,retiraFundo,corFundo,idJanela));
    }

    static int CriaGeradorParticulas(int maxParticulas, PIGObjeto objetoBase, int audioCriacao, int audioEncerramento, bool retiraFundo=true, PIGCor *corFundo=NULL, int idJanela=0){
        int id = geradores->ProxID();
        return geradores->Insere(new CPIGGeradorParticulas(id,maxParticulas,objetoBase,audioCriacao,audioEncerramento,retiraFundo,corFundo,idJanela));
    }

    static void DestroiGeradorParticulas(int idGerador){
        geradores->Remove(idGerador);
    }
};

CPIGRepositorio<PIGGeradorParticulas> *CPIGGerenciadorGDP::geradores;
#endif //_CPIGGERENCIADORGDP_
