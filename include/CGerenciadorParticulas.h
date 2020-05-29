#include "CGeradorParticulas.h"
class CGerenciadorParticulas{

private:

    //static SDL_Renderer *render;
    static int totalGeradores;
    static PoolNumeros numGeradores;
    static GeradorParticulas geradores[MAX_GERADORPARTICULAS];

public:

    static void Inicia(SDL_Renderer *renderer=NULL){
        //render = renderer;
        totalGeradores = 0;
        for (int i=0;i<MAX_GERADORPARTICULAS;i++)
            geradores[i] = NULL;
        numGeradores = new CPoolNumeros(MAX_GERADORPARTICULAS);
    }

    static void Encerra(){
        for (int i=0;i<MAX_GERADORPARTICULAS;i++){
            if (geradores[i]) delete geradores[i];
        }
        delete numGeradores;
    }

    static int CriaGeradorParticulas(int maxParticulas,std::string nomeArquivoBMP,int audioCriacao, int audioEncerramento, int idJanela=0,int usaGerenciadorTimer=1){
        int resp = numGeradores->RetiraLivre();
        geradores[resp] = new CGeradorParticulas(maxParticulas,nomeArquivoBMP,audioCriacao,audioEncerramento,usaGerenciadorTimer,idJanela);
        totalGeradores++;
        return resp;
    }

    static int CriaGeradorParticulas(int maxParticulas,Animacao animacaoBase,int audioCriacao, int audioEncerramento, int idJanela=0,int usaGerenciadorTimer=1){
        int resp = numGeradores->RetiraLivre();
        geradores[resp] = new CGeradorParticulas(maxParticulas,animacaoBase,audioCriacao,audioEncerramento,usaGerenciadorTimer,idJanela);
        totalGeradores++;
        return resp;
    }

    static int CriaGeradorParticulas(int maxParticulas,Objeto objetoBase,int audioCriacao, int audioEncerramento, int idJanela=0,int usaGerenciadorTimer=1){
        int resp = numGeradores->RetiraLivre();
        geradores[resp] = new CGeradorParticulas(maxParticulas,objetoBase,audioCriacao,audioEncerramento,usaGerenciadorTimer,idJanela);
        totalGeradores++;
        return resp;
    }

    static void DestroiGeradorParticulas(int idGerador){
        numGeradores->DevolveUsado(idGerador);
        delete geradores[idGerador];
        totalGeradores--;
        geradores[idGerador] = NULL;
    }

    inline static void Move(int idGerador,int px,int py){
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

    inline static int Colisao(int idGerador,Objeto obj){
        return geradores[idGerador]->Colisao(obj);
    }

};

PoolNumeros CGerenciadorParticulas::numGeradores;
int CGerenciadorParticulas::totalGeradores;
GeradorParticulas CGerenciadorParticulas::geradores[MAX_GERADORPARTICULAS];

