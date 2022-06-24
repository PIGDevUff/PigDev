#ifndef _CPIGGERENCIADORGDP_
#define _CPIGGERENCIADORGDP_

#include "CPIGGeradorParticulas.h"

class CPIGGerenciadorGDP{

private:

    static CPIGRepositorio<PIGGeradorParticulas> *geradores;

public:

    inline static PIGGeradorParticulas GetGerador(int idGerador){
        return geradores->GetElemento(idGerador);
    }

    inline static void Inicia(){
        geradores = new CPIGRepositorio<PIGGeradorParticulas>(PIG_MAX_GERADORPARTICULAS,"geradores");
    }

    inline static void Encerra(){
        delete geradores;
    }

    inline static int CriaGeradorParticulas(int maxParticulas, string nomeArquivoBMP, int audioCriacao, int audioEncerramento, bool retiraFundo=true, PIGCor *corFundo=NULL, int idJanela=0){
        int id = geradores->ProxID();
        return geradores->Insere(new CPIGGeradorParticulas(id,maxParticulas,nomeArquivoBMP,audioCriacao,audioEncerramento,retiraFundo,corFundo,idJanela));
    }

    inline static int CriaGeradorParticulas(int maxParticulas, PIGAnimacao animacaoBase, int audioCriacao, int audioEncerramento, bool retiraFundo=true, PIGCor *corFundo=NULL, int idJanela=0){
        int id = geradores->ProxID();
        return geradores->Insere(new CPIGGeradorParticulas(id,maxParticulas,animacaoBase,audioCriacao,audioEncerramento,retiraFundo,corFundo,idJanela));
    }

    inline static int CriaGeradorParticulas(int maxParticulas, PIGObjeto objetoBase, int audioCriacao, int audioEncerramento, bool retiraFundo=true, PIGCor *corFundo=NULL, int idJanela=0){
        int id = geradores->ProxID();
        return geradores->Insere(new CPIGGeradorParticulas(id,maxParticulas,objetoBase,audioCriacao,audioEncerramento,retiraFundo,corFundo,idJanela));
    }

    inline static int InsereGeradorParticulas(PIGGeradorParticulas gerador){
        return geradores->Insere(gerador);
    }

    inline static void DestroiGeradorParticulas(int idGerador){
        geradores->Remove(idGerador);
    }
};

CPIGRepositorio<PIGGeradorParticulas> *CPIGGerenciadorGDP::geradores;
#endif //_CPIGGERENCIADORGDP_
