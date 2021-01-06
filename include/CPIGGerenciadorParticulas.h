#ifndef _CPIGGERENCIADORPARTICULAS_
#define _CPIGGERENCIADORPARTICULAS_

#include "CPIGGeradorParticulas.h"
class CPIGGerenciadorParticulas{

private:

    /*static int totalGeradores;
    static PIGPoolNumeros numGeradores;
    static PIGGeradorParticulas geradores[MAX_GERADORPARTICULAS];*/

    /*static std::vector<int> posLivres;
    static std::unordered_map<int,PIGGeradorParticulas> geradores;
    static std::unordered_map<int,PIGGeradorParticulas>::iterator it;*/

    static CPIGRepositorio<PIGGeradorParticulas> *geradores;

public:

    static void Inicia(SDL_Renderer *renderer=NULL){
        //render = renderer;
        /*totalGeradores = 0;
        for (int i=0;i<MAX_GERADORPARTICULAS;i++)
            geradores[i] = NULL;
        numGeradores = new CPIGPoolNumeros(MAX_GERADORPARTICULAS);*/
        //for (int i=0;i<MAX_GERADORPARTICULAS;i++)
        //    posLivres.push_back(i);
        geradores = new CPIGRepositorio<PIGGeradorParticulas>(MAX_GERADORPARTICULAS,"geradores");
    }

    static void Encerra(){
        /*for (int i=0;i<MAX_GERADORPARTICULAS;i++){
            if (geradores[i]) delete geradores[i];
        }
        delete numGeradores;*/
        //for(it = geradores.begin(); it != geradores.end(); ++it) {
        //    delete it->second;
        //}
        delete geradores;
    }

    inline static PIGGeradorParticulas GetGerador(int idGerador){
        /*if (idAudio<0||idAudio>=MAX_AUDIOS||audios[idAudio]==NULL) throw CPIGErroIndice(idAudio,"audios");
        return audios[idAudio];*/
        /*it = geradores.find(idGerador);
        if (it==geradores.end()) throw CPIGErroIndice(idGerador,"geradores");
        return it->second;*/
        return geradores->GetElemento(idGerador);
    }

    static int CriaGeradorParticulas(int maxParticulas,std::string nomeArquivoBMP,int audioCriacao, int audioEncerramento, int idJanela=0,int usaGerenciadorTimer=1){
        /*int resp = numGeradores->RetiraLivre();
        geradores[resp] = new CPIGGeradorParticulas(maxParticulas,nomeArquivoBMP,audioCriacao,audioEncerramento,usaGerenciadorTimer,idJanela);
        totalGeradores++;
        return resp;*/
        /*int resp = posLivres[0];
        posLivres.erase(posLivres.begin());
        geradores[resp] = new CPIGGeradorParticulas(maxParticulas,nomeArquivoBMP,audioCriacao,audioEncerramento,usaGerenciadorTimer,idJanela);
        return resp;*/
        return geradores->Insere(new CPIGGeradorParticulas(maxParticulas,nomeArquivoBMP,audioCriacao,audioEncerramento,usaGerenciadorTimer,idJanela));
    }

    static int CriaGeradorParticulas(int maxParticulas,PIGAnimacao animacaoBase,int audioCriacao, int audioEncerramento, int idJanela=0,int usaGerenciadorTimer=1){
        /*int resp = numGeradores->RetiraLivre();
        geradores[resp] = new CPIGGeradorParticulas(maxParticulas,animacaoBase,audioCriacao,audioEncerramento,usaGerenciadorTimer,idJanela);
        totalGeradores++;
        return resp;*/
        /*int resp = posLivres[0];
        posLivres.erase(posLivres.begin());
        geradores[resp] = new CPIGGeradorParticulas(maxParticulas,animacaoBase,audioCriacao,audioEncerramento,usaGerenciadorTimer,idJanela);
        return resp;*/
        return geradores->Insere(new CPIGGeradorParticulas(maxParticulas,animacaoBase,audioCriacao,audioEncerramento,usaGerenciadorTimer,idJanela));
    }

    static int CriaGeradorParticulas(int maxParticulas,PIGObjeto objetoBase,int audioCriacao, int audioEncerramento, int idJanela=0,int usaGerenciadorTimer=1){
        /*int resp = numGeradores->RetiraLivre();
        geradores[resp] = new CPIGGeradorParticulas(maxParticulas,objetoBase,audioCriacao,audioEncerramento,usaGerenciadorTimer,idJanela);
        totalGeradores++;
        return resp;*/
        /*int resp = posLivres[0];
        posLivres.erase(posLivres.begin());
        geradores[resp] = new CPIGGeradorParticulas(maxParticulas,objetoBase,audioCriacao,audioEncerramento,usaGerenciadorTimer,idJanela);
        return resp;*/
        return geradores->Insere(new CPIGGeradorParticulas(maxParticulas,objetoBase,audioCriacao,audioEncerramento,usaGerenciadorTimer,idJanela));
    }

    static void DestroiGeradorParticulas(int idGerador){
        /*numGeradores->DevolveUsado(idGerador);
        delete geradores[idGerador];
        totalGeradores--;
        geradores[idGerador] = NULL;*/
        /*PIGGeradorParticulas gerador = GetGerador(idGerador);
        delete gerador;
        geradores.erase(idGerador);*/
        geradores->Remove(idGerador);
    }



};
CPIGRepositorio<PIGGeradorParticulas> *CPIGGerenciadorParticulas::geradores;

#endif // _CPIGGERENCIADORPARTICULAS_
