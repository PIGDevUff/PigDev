#include "CGeradorParticulas.h"
class CGerenciadorParticulas{

private:

    static SDL_Renderer *render;
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

    static int CriaGeradorParticulas(int maxParticulas,char* nomeArquivoBMP,int audioCriacao, int audioEncerramento, int idJanela=0,int usaGerenciadorTimer=1){
        int resp = numGeradores->RetiraLivre();
        geradores[resp] = new CGeradorParticulas(maxParticulas,CGerenciadorJanelas::GetJanela(idJanela)->GetRenderer(),nomeArquivoBMP,audioCriacao,audioEncerramento,usaGerenciadorTimer);
        totalGeradores++;
        return resp;
    }

    static int CriaGeradorParticulas(int maxParticulas,Animacao animacaoBase,int audioCriacao, int audioEncerramento, int idJanela=0,int usaGerenciadorTimer=1){
        int resp = numGeradores->RetiraLivre();
        geradores[resp] = new CGeradorParticulas(maxParticulas,CGerenciadorJanelas::GetJanela(idJanela)->GetRenderer(),animacaoBase,audioCriacao,audioEncerramento,usaGerenciadorTimer);
        totalGeradores++;
        return resp;
    }

    static int CriaGeradorParticulas(int maxParticulas,Objeto objetoBase,int audioCriacao, int audioEncerramento, int idJanela=0,int usaGerenciadorTimer=1){
        int resp = numGeradores->RetiraLivre();
        geradores[resp] = new CGeradorParticulas(maxParticulas,CGerenciadorJanelas::GetJanela(idJanela)->GetRenderer(),objetoBase,audioCriacao,audioEncerramento,usaGerenciadorTimer);
        totalGeradores++;
        return resp;
    }

    static void DestroiGeradorParticulas(int id_gerador){
        numGeradores->DevolveUsado(id_gerador);
        delete geradores[id_gerador];
        totalGeradores--;
        geradores[id_gerador] = NULL;
    }

    inline static void Move(int id_gerador,int px,int py){
        geradores[id_gerador]->Move(px,py);
    }

    inline static void MudaDirecaoParticulas(int id_gerador,int dx,int dy){
        geradores[id_gerador]->MudaDirecao(dx,dy);
    }

    inline static void MudaRotacaoParticulas(int id_gerador,float angPerSec){
        geradores[id_gerador]->MudaRotacao(angPerSec);
    }

    inline static void MudaCorParticulas(int id_gerador,PIG_Cor cor){
        geradores[id_gerador]->MudaCor(cor);
    }

    inline static void MudaEscalaParticulas(int id_gerador,float escalaInicial,float escalaFinal){
        geradores[id_gerador]->MudaEscala(escalaInicial,escalaFinal);
    }

    inline static void SetPivoParticulas(int id_gerador,int pivoX,int pivoY){
        geradores[id_gerador]->SetPivo(pivoX,pivoY);
    }

    inline static void SetPivoParticulas(int id_gerador,float pivoX,float pivoY){
        geradores[id_gerador]->SetPivo(pivoX,pivoY);
    }

    inline static int CriaParticula(int id_gerador,int fadingOut=0,int minX=-50,int minY=-50,int maxX=LARG_TELA+50,int maxY=ALT_TELA+50,float maxTempo=9999999.9){
        return geradores[id_gerador]->CriaParticula(fadingOut,minX,minY,maxX,maxY,maxTempo);
    }

    inline static void MoveParticulas(int id_gerador){
        geradores[id_gerador]->MoveParticulas();
    }

    inline static int GetQtdAtivas(int id_gerador){
        return geradores[id_gerador]->GetQtdAtivas();
    }

    inline static void Desenha(int id_gerador){
        geradores[id_gerador]->Desenha();
    }

    inline static int Colisao(int id_gerador,Objeto obj){
        return geradores[id_gerador]->Colisao(obj);
    }

};

PoolNumeros CGerenciadorParticulas::numGeradores;
int CGerenciadorParticulas::totalGeradores;
GeradorParticulas CGerenciadorParticulas::geradores[MAX_GERADORPARTICULAS];

