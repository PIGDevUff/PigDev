#ifndef _CPIGPARTICULA_
#define _CPIGPARTICULA_

#include "CPIGObjeto.h"

class CPIGParticula: public CPIGObjeto{

private:

SDL_Rect espacoVida;
double hp;
double tempoVida;
int timer;

double ModificaHP(double valor){
    hp += valor;
    viva = hp>0;
}

public:
    bool viva;

    CPIGParticula(PIGObjeto objBase,int vida,PIG_Cor *corFundo=NULL,int retiraFundo=1,int idJanela=0):
        CPIGObjeto(objBase,corFundo,retiraFundo,idJanela){
        hp = vida;
        espacoVida.x = -50;
        espacoVida.y = -50;
        espacoVida.h = PIG_ALT_TELA+50;
        espacoVida.w = PIG_LARG_TELA+50;
        tempoVida = 10;
        viva = true;
        timer = CPIGGerenciadorTimers::CriaTimer();
    }

    void DefineLimites(SDL_Rect espacoMax, double tempoMax){
        espacoVida = espacoMax;
        tempoVida = tempoMax;
    }

    ~CPIGParticula(){
            CPIGGerenciadorTimers::DestroiTimer(timer);
    }

    void Move(int nx, int ny) override{
        if (!viva) return;
        if (CPIGGerenciadorTimers::GetTimer(timer)->GetTempoDecorrido()>tempoVida){
            viva = false;
            return;
        }
        CPIGObjeto::Move(nx,ny);
        //printf("rect %d,%d, %d,%d,%d,%d\n",pos.x,pos.y,espacoVida.x,espacoVida.y,espacoVida.w,espacoVida.h);
        viva = (pos.x>espacoVida.x)&&(pos.x<espacoVida.x+espacoVida.w)&&(pos.y>espacoVida.y)&&(pos.y<espacoVida.y+espacoVida.h);
        //printf("movendo %d,%d %d\n",nx,ny,viva);
    }

    bool Colisao(PIGObjeto outro) override{
        bool resp = CPIGObjeto::Colisao(outro);
        if (resp){
            ModificaHP(-1);
            //printf("colidi viva %d,%d,%d,%d   %d,%d,%d,%d\n",pos.x,pos.y,alt,larg,outro->pos.x,outro->pos.y,outro->alt,outro->larg);
        }
        return resp;
    }

    bool Colisao(CPIGParticula *outra){
        bool resp = CPIGObjeto::Colisao(outra);
        if (resp){
            ModificaHP(-1);
            outra->ModificaHP(-1);
        }
        return resp;
    }
};

typedef CPIGParticula* PIGParticula;
#endif //_CPIGPARTICULA_
