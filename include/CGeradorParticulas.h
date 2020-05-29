#include "CParticula.h"

class CGeradorParticulas{

private:
Particula parts[MAX_PARTICULAS];
int inix,iniy,dx,dy;            //posicao e direcao atual das particulas
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
Animacao animacaoBase;
Objeto objetoBase;

void IniciaBase(int maximoParticulas,std::string nomeArq,int usaGerenciadorTimer, int audioCriacao, int audioEncerramento,int janela,Objeto objBase,Animacao animaBase){
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

    CGeradorParticulas(int maximoParticulas,Objeto objBase, int audioCriacao,int audioEncerramento, int usaGerenciadorTimer, int idJanela){
        IniciaBase(maximoParticulas,"",usaGerenciadorTimer,audioCriacao,audioEncerramento,idJanela,objBase,NULL);
        tipoGerador = 1;
    }

    CGeradorParticulas(int maximoParticulas,Animacao animaBase, int audioCriacao,int audioEncerramento, int usaGerenciadorTimer,int idJanela){
        IniciaBase(maximoParticulas,"",usaGerenciadorTimer,audioCriacao,audioEncerramento,idJanela,NULL,animaBase);
        tipoGerador = 2;
    }

    CGeradorParticulas(int maximoParticulas,std::string nomeArq,int audioCriacao,int audioEncerramento, int usaGerenciadorTimer, int idJanela){
        IniciaBase(maximoParticulas,nomeArq,usaGerenciadorTimer,audioCriacao,audioEncerramento,idJanela,NULL,NULL);
        tipoGerador = 3;
    }

    ~CGeradorParticulas(){
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
                        CGerenciadorAudios::Play(audioFim);
                    //printf("vai deletar\n");
                    delete parts[i];
                    //printf("deletou\n");
                    parts[i] = NULL;
                    ativas--;
                }
            }
    }

    void Move(int nx,int ny){
        inix = nx;
        iniy = ny;
    }

    void Desloca(int dx,int dy){
        inix += dx;
        iniy += dy;
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

    int CriaParticula(int fadingOut=0,int minX=-50,int minY=-50,int maxX=LARG_TELA+50,int maxY=ALT_TELA+50,float maxTempo=9999999.9){
        int i=0;
        if (ativas>=maxParticulas) return -1;
        while (parts[i])
            i++;
        //printf("sou do tipo %d\n",tipoGerador);
        switch (tipoGerador){
        case 1: parts[i] = new CParticula(inix,iniy,dx,dy,hp,anguloRot,escalaInicial,escalaFinal,fadingOut,objetoBase,usaGerTimer,idJanela);
            break;
        case 2: parts[i] = new CParticula(inix,iniy,dx,dy,hp,anguloRot,escalaInicial,escalaFinal,fadingOut,animacaoBase,usaGerTimer,idJanela);
            break;
        case 3: parts[i] = new CParticula(inix,iniy,dx,dy,hp,anguloRot,escalaInicial,escalaFinal,fadingOut,nomeArqImagem,usaGerTimer,idJanela);
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
            CGerenciadorAudios::Play(audioInicio);
        //printf("Gerei5\n");
        return i;
    }

    int Colisao(Objeto outro){
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

typedef CGeradorParticulas* GeradorParticulas;
