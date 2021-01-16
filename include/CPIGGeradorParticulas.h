#ifndef _CPIGGERADORPARTICULAS_
#define _CPIGGERADORPARTICULAS_

#include "CPIGParticula.h"

class CPIGGeradorParticulas{

private:
PIGParticula parts[PIG_MAX_PARTICULAS];
SDL_Point pos;
int dx,dy;            //posicao e direcao atual das particulas
int pivoAbsX,pivoAbsY;          //pivo das particulas
float pivoRelX,pivoRelY;
bool modoPivoRelativo;
int idJanela;
int hp;
float anguloRot;
float escalaInicial,escalaFinal;
int maxParticulas;
std::string nomeArqImagem;
int ativas;
int usaGerTimer,tipoGerador;
int audioInicio,audioFim;
PIG_Cor corAtual;
PIGAnimacao animacaoBase;
PIGObjeto objetoBase;

void IniciaBase(int maximoParticulas,std::string nomeArq,int usaGerenciadorTimer, int audioCriacao, int audioEncerramento,int janela,PIGObjeto objBase,PIGAnimacao animaBase){
    maxParticulas = maximoParticulas;
    nomeArqImagem = nomeArq;
    usaGerTimer = usaGerenciadorTimer;
    audioInicio = audioCriacao;
    audioFim = audioEncerramento;
    animacaoBase = animaBase;
    objetoBase = objBase;
    idJanela = janela;

    for (int i=0;i<maxParticulas;i++)
        parts[i] = NULL;

    dx = dy = 0;
    pivoAbsX = pivoAbsY = 0;
    pivoRelX = pivoRelY = 0.0f;
    hp = 1;
    anguloRot = 0.0f;
    escalaInicial = escalaFinal = 1.0f;
    ativas = 0;
    modoPivoRelativo = false;
    corAtual = BRANCO;
}

public:

    CPIGGeradorParticulas(int maximoParticulas,PIGObjeto objBase, int audioCriacao,int audioEncerramento, int usaGerenciadorTimer, int idJanela){
        IniciaBase(maximoParticulas,"",usaGerenciadorTimer,audioCriacao,audioEncerramento,idJanela,objBase,NULL);
        tipoGerador = 1;
    }

    CPIGGeradorParticulas(int maximoParticulas,PIGAnimacao animaBase, int audioCriacao,int audioEncerramento, int usaGerenciadorTimer,int idJanela){
        IniciaBase(maximoParticulas,"",usaGerenciadorTimer,audioCriacao,audioEncerramento,idJanela,NULL,animaBase);
        tipoGerador = 2;
    }

    CPIGGeradorParticulas(int maximoParticulas,std::string nomeArq,int audioCriacao,int audioEncerramento, int usaGerenciadorTimer, int idJanela){
        IniciaBase(maximoParticulas,nomeArq,usaGerenciadorTimer,audioCriacao,audioEncerramento,idJanela,NULL,NULL);
        tipoGerador = 3;
    }

    ~CPIGGeradorParticulas(){
        for (int i=0;i<maxParticulas;i++)
            if (parts[i]) delete parts[i];
    }

    void MoveParticulas(){
        for (int i=0;i<maxParticulas;i++)
            if (parts[i]) {
                parts[i]->Move();
                //printf("viva %d\n",parts[i]->viva);
                if (!parts[i]->viva){
                    if (audioFim>=0)
                        CPIGGerenciadorAudios::Play(audioFim);
                    //printf("vai deletar\n");
                    delete parts[i];
                    //printf("deletou\n");
                    parts[i] = NULL;
                    ativas--;
                }
            }
    }

    void Move(int nx,int ny){
        pos.x = nx;
        pos.y = ny;
    }

    void Desloca(int dx,int dy){
        pos.x += dx;
        pos.y += dy;
    }

    void MudaDirecao(int novaDx,int novaDy){
        dx = novaDx;
        dy = novaDy;
    }

    void MudaRotacao(float angPerSec){
        anguloRot = angPerSec;
    }

    void MudaEscala(float escalaIni,float escalaFim){
        escalaInicial = escalaIni;
        escalaFinal = escalaFim;
    }

    void MudaHP(int novoValor){
        hp = novoValor;
    }

    void MudaCor(PIG_Cor cor){
        corAtual = cor;
    }

    void Desenha(){
        for (int i=0;i<maxParticulas;i++)
            if ((parts[i])&&(parts[i]->viva)) {
                //printf("Vou desenhar\n");
                parts[i]->Desenha();
                //printf("desenhei\n");
            }
    }

    void SetPivo(int pivoX,int pivoY){
        pivoAbsX = pivoX;
        pivoAbsY = pivoY;
        modoPivoRelativo = false;
    }

    void SetPivo(float pivoX,float pivoY){
        pivoRelX = pivoX;
        pivoRelY = pivoY;
        modoPivoRelativo = true;
    }

    int CriaParticula(int fadingOut=0,int minX=-50,int minY=-50,int maxX=PIG_LARG_TELA+50,int maxY=PIG_ALT_TELA+50,float maxTempo=9999999.9){
        int i=0;
        if (ativas>=maxParticulas) return -1;
        while (parts[i])
            i++;
        //printf("sou do tipo %d\n",tipoGerador);
        switch (tipoGerador){
        case 1: parts[i] = new CPIGParticula(pos.x,pos.y,dx,dy,hp,anguloRot,escalaInicial,escalaFinal,fadingOut,objetoBase,usaGerTimer,idJanela);
            break;
        case 2: parts[i] = new CPIGParticula(pos.x,pos.y,dx,dy,hp,anguloRot,escalaInicial,escalaFinal,fadingOut,animacaoBase,usaGerTimer,idJanela);
            break;
        case 3: parts[i] = new CPIGParticula(pos.x,pos.y,dx,dy,hp,anguloRot,escalaInicial,escalaFinal,fadingOut,nomeArqImagem,usaGerTimer,idJanela);
            break;
        }
        //printf("Gerei\n");
        parts[i]->SetColoracao(corAtual);
        //parts[i]->Move(inix,iniy);
        //printf("Gerei2\n");
        int alt,larg;
        parts[i]->GetDimensoes(alt,larg);
        if (modoPivoRelativo==false){
            parts[i]->SetPivo(pivoAbsX,pivoAbsY);
        }else{
            parts[i]->SetPivo(pivoRelX,pivoRelY);
        }
        //printf("Gerei3\n");
        parts[i]->DefineLimites(minX,maxX,minY,maxY,maxTempo);
        //printf("Gerei4\n");
        ativas++;
        if (audioInicio>=0)
            CPIGGerenciadorAudios::Play(audioInicio);
        //printf("Gerei5\n");
        return i;
    }

    int Colisao(PIGObjeto outro){
        int resp = 0;
        int i=0,cont=0;
        while (!resp && i<maxParticulas && cont<ativas){
            if (parts[i]){
                cont++;
                resp = parts[i]->Colisao(outro);
            }
            i++;
        }
        return resp;
    }

    int Colisao(){
        int resp = 0;
        int i=0;
        while (!resp && i<maxParticulas-1){
            if (parts[i]){
                int j=i+1;
                while (!resp&&j<maxParticulas){
                    if (parts[j]){
                        resp = parts[i]->Colisao(parts[j]);
                    }
                    j++;
                }
            }
            i++;
        }
        return resp;
    }

    int GetQtdAtivas(){
        return ativas;
    }
};

typedef CPIGGeradorParticulas* PIGGeradorParticulas;
#endif // _CPIGGERADORPARTICULAS_
