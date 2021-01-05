#ifndef _CPIGGERENCIADORPARTICULAS_
#define _CPIGGERENCIADORPARTICULAS_

#include "CPIGGeradorParticulas.h"
class CPIGGerenciadorParticulas{

private:

    /*static int totalGeradores;
    static PIGPoolNumeros numGeradores;
    static PIGGeradorParticulas geradores[MAX_GERADORPARTICULAS];*/

    static std::vector<int> posLivres;
    static std::unordered_map<int,PIGGeradorParticulas> geradores;
    static std::unordered_map<int,PIGGeradorParticulas>::iterator it;

public:

    static void Inicia(SDL_Renderer *renderer=NULL){
        //render = renderer;
        /*totalGeradores = 0;
        for (int i=0;i<MAX_GERADORPARTICULAS;i++)
            geradores[i] = NULL;
        numGeradores = new CPIGPoolNumeros(MAX_GERADORPARTICULAS);*/
        for (int i=0;i<MAX_GERADORPARTICULAS;i++)
            posLivres.push_back(i);
    }

    static void Encerra(){
        /*for (int i=0;i<MAX_GERADORPARTICULAS;i++){
            if (geradores[i]) delete geradores[i];
        }
        delete numGeradores;*/
        for(it = geradores.begin(); it != geradores.end(); ++it) {
            delete it->second;
        }
    }

    inline static PIGGeradorParticulas GetGerador(int idGerador){
        /*if (idAudio<0||idAudio>=MAX_AUDIOS||audios[idAudio]==NULL) throw CPIGErroIndice(idAudio,"audios");
        return audios[idAudio];*/
        it = geradores.find(idGerador);
        if (it==geradores.end()) throw CPIGErroIndice(idGerador,"geradores");
        return it->second;
    }

    static int CriaGeradorParticulas(int maxParticulas,std::string nomeArquivoBMP,int audioCriacao, int audioEncerramento, int idJanela=0,int usaGerenciadorTimer=1){
        /*int resp = numGeradores->RetiraLivre();
        geradores[resp] = new CPIGGeradorParticulas(maxParticulas,nomeArquivoBMP,audioCriacao,audioEncerramento,usaGerenciadorTimer,idJanela);
        totalGeradores++;
        return resp;*/
        int resp = posLivres[0];
        posLivres.erase(posLivres.begin());
        geradores[resp] = new CPIGGeradorParticulas(maxParticulas,nomeArquivoBMP,audioCriacao,audioEncerramento,usaGerenciadorTimer,idJanela);
        return resp;
    }

    static int CriaGeradorParticulas(int maxParticulas,PIGAnimacao animacaoBase,int audioCriacao, int audioEncerramento, int idJanela=0,int usaGerenciadorTimer=1){
        /*int resp = numGeradores->RetiraLivre();
        geradores[resp] = new CPIGGeradorParticulas(maxParticulas,animacaoBase,audioCriacao,audioEncerramento,usaGerenciadorTimer,idJanela);
        totalGeradores++;
        return resp;*/
        int resp = posLivres[0];
        posLivres.erase(posLivres.begin());
        geradores[resp] = new CPIGGeradorParticulas(maxParticulas,animacaoBase,audioCriacao,audioEncerramento,usaGerenciadorTimer,idJanela);
        return resp;
    }

    static int CriaGeradorParticulas(int maxParticulas,PIGObjeto objetoBase,int audioCriacao, int audioEncerramento, int idJanela=0,int usaGerenciadorTimer=1){
        /*int resp = numGeradores->RetiraLivre();
        geradores[resp] = new CPIGGeradorParticulas(maxParticulas,objetoBase,audioCriacao,audioEncerramento,usaGerenciadorTimer,idJanela);
        totalGeradores++;
        return resp;*/
        int resp = posLivres[0];
        posLivres.erase(posLivres.begin());
        geradores[resp] = new CPIGGeradorParticulas(maxParticulas,objetoBase,audioCriacao,audioEncerramento,usaGerenciadorTimer,idJanela);
        return resp;
    }

    static void DestroiGeradorParticulas(int idGerador){
        /*numGeradores->DevolveUsado(idGerador);
        delete geradores[idGerador];
        totalGeradores--;
        geradores[idGerador] = NULL;*/
        PIGGeradorParticulas gerador = GetGerador(idGerador);
        delete gerador;
        geradores.erase(idGerador);
    }

    /*inline static void Move(int idGerador,int px,int py){
        geradores[idGerador]->Move(px,py);
    }

    inline static void Desloca(int idGerador,int dx,int dy){
        geradores[idGerador]->Desloca(dx,dy);
    }

    inline static void MudaDirecaoParticulas(int idGerador,int dx,int dy){
        geradores[idGerador]->MudaDirecao(dx,dy);
    }

    inline static void MudaRotacaoParticulas(int idGerador,float angPerSec){
        geradores[idGerador]->MudaRotacao(angPerSec);
    }

    inline static void MudaCorParticulas(int idGerador,PIG_Cor cor){
        geradores[idGerador]->MudaCor(cor);
    }

    inline static void MudaEscalaParticulas(int idGerador,float escalaInicial,float escalaFinal){
        geradores[idGerador]->MudaEscala(escalaInicial,escalaFinal);
    }

    inline static void SetPivoParticulas(int idGerador,int pivoX,int pivoY){
        geradores[idGerador]->SetPivo(pivoX,pivoY);
    }

    inline static void SetPivoParticulas(int idGerador,float pivoX,float pivoY){
        geradores[idGerador]->SetPivo(pivoX,pivoY);
    }

    inline static int CriaParticula(int idGerador,int fadingOut=0,int minX=-50,int minY=-50,int maxX=LARG_TELA+50,int maxY=ALT_TELA+50,float maxTempo=9999999.9){
        return geradores[idGerador]->CriaParticula(fadingOut,minX,minY,maxX,maxY,maxTempo);
    }

    inline static void MoveParticulas(int idGerador){
        geradores[idGerador]->MoveParticulas();
    }

    inline static int GetQtdAtivas(int idGerador){
        return geradores[idGerador]->GetQtdAtivas();
    }

    inline static void Desenha(int idGerador){
        geradores[idGerador]->Desenha();
    }

    inline static int Colisao(int idGerador,PIGObjeto obj){
        return geradores[idGerador]->Colisao(obj);
    }*/

};

std::vector<int> CPIGGerenciadorParticulas::posLivres;
std::unordered_map<int,PIGGeradorParticulas> CPIGGerenciadorParticulas::geradores;
std::unordered_map<int,PIGGeradorParticulas>::iterator CPIGGerenciadorParticulas::it;

//PIGPoolNumeros CPIGGerenciadorParticulas::numGeradores;
//int CPIGGerenciadorParticulas::totalGeradores;
//PIGGeradorParticulas CPIGGerenciadorParticulas::geradores[MAX_GERADORPARTICULAS];

#endif // _CPIGGERENCIADORPARTICULAS_
