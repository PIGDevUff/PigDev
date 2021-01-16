#ifndef _CPIGGERENCIADORPARTICULAS_
#define _CPIGGERENCIADORPARTICULAS_

#include "CPIGGeradorParticulas.h"
class CPIGGerenciadorParticulas{

private:

    static CPIGRepositorio<PIGGeradorParticulas> *geradores;

public:

    static void Inicia(SDL_Renderer *renderer=NULL){
        geradores = new CPIGRepositorio<PIGGeradorParticulas>(PIG_MAX_GERADORPARTICULAS,"geradores");
    }

    static void Encerra(){
        delete geradores;
    }

    inline static PIGGeradorParticulas GetGerador(int idGerador){
        return geradores->GetElemento(idGerador);
    }

    static int CriaGeradorParticulas(int maxParticulas,std::string nomeArquivoBMP,int audioCriacao, int audioEncerramento, int idJanela=0,int usaGerenciadorTimer=1){
        return geradores->Insere(new CPIGGeradorParticulas(maxParticulas,nomeArquivoBMP,audioCriacao,audioEncerramento,usaGerenciadorTimer,idJanela));
    }

    static int CriaGeradorParticulas(int maxParticulas,PIGAnimacao animacaoBase,int audioCriacao, int audioEncerramento, int idJanela=0,int usaGerenciadorTimer=1){
        return geradores->Insere(new CPIGGeradorParticulas(maxParticulas,animacaoBase,audioCriacao,audioEncerramento,usaGerenciadorTimer,idJanela));
    }

    static int CriaGeradorParticulas(int maxParticulas,PIGObjeto objetoBase,int audioCriacao, int audioEncerramento, int idJanela=0,int usaGerenciadorTimer=1){
        return geradores->Insere(new CPIGGeradorParticulas(maxParticulas,objetoBase,audioCriacao,audioEncerramento,usaGerenciadorTimer,idJanela));
    }

    static void DestroiGeradorParticulas(int idGerador){
        geradores->Remove(idGerador);
    }


};
CPIGRepositorio<PIGGeradorParticulas> *CPIGGerenciadorParticulas::geradores;

#endif // _CPIGGERENCIADORPARTICULAS_