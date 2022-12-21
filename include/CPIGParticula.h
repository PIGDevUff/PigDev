#ifndef _CPIGPARTICULA_
#define _CPIGPARTICULA_

#include "CPIGAnimacao.h"

class CPIGParticula: public CPIGAnimacao{

private:

    SDL_Rect espacoVida;
    double hp;
    double tempoVida;
    int idTimerVida;                        //timer para controle do tempo de vida da partícula, a partir da sua criação (usado apenas na contrução e destruição de um objeto)
    PIGTimer timerVida;                     //ponteiro para o timer indicado por idTimerVida (usado diretamente para otimizar a execução dos códigos)
    bool viva;

    double ModificaHP(double valor){
        hp += valor;
        viva = hp>0;
        return hp;
    }

public:

    CPIGParticula(int idParticula,PIGAnimacao base,int vida,int retiraFundo=1,PIGCor *corFundo=NULL,int idJanela=0):
        CPIGAnimacao(idParticula,base,retiraFundo,corFundo,idJanela){
        hp = vida;
        espacoVida = {INT_MIN,INT_MIN,INT_MAX,INT_MAX};
        tempoVida = 9999999;
        viva = true;
        idTimerVida = pigGerTimers.CriaTimer(false);
        timerVida = pigGerTimers.GetElemento(idTimerVida);
    }

    inline void DefineLimites(SDL_Rect espacoMax, double tempoMax){
        espacoVida = espacoMax;
        tempoVida = tempoMax;
    }

    virtual ~CPIGParticula(){
        timerVida = NULL;
        pigGerTimers.Remove(idTimerVida);
    }

    inline bool ChecaViva(){
        //printf("tempo %f < %f\n",CPIGGerenciadorTimers::GetTimer(timer)->GetTempoDecorrido(),tempoVida);
        //printf("viva antes %d\n",viva);
        viva = viva &&timerVida->GetTempoDecorrido()<=tempoVida
                    &&(pos.x>espacoVida.x)&&(pos.x<espacoVida.w)
                    &&(pos.y>espacoVida.y)&&(pos.y<espacoVida.h);
        //if (!viva) printf("%d morri por tempo\n",id);
        //if (!viva) return;
        //printf("%d,%d %d,%d,%d,%d\n",(int)pos.x,(int)pos.y,espacoVida.x,espacoVida.y,espacoVida.w,espacoVida.h);
        //viva = viva
        //if (!viva) PRINTF("%d morri por tempo\n",id);
        //if (!viva) printf("%d morri por espaco\n",id);
        return viva;
    }

    /*void Move(double nx, double ny) override{
        if (!viva) return;
        CPIGObjeto::Move(nx,ny);
        //printf("rect %d,%d, %d,%d,%d,%d\n",pos.x,pos.y,espacoVida.x,espacoVida.y,espacoVida.w,espacoVida.h);
        viva = (pos.x>espacoVida.x)&&(pos.x<espacoVida.w)&&(pos.y>espacoVida.y)&&(pos.y<espacoVida.h);
        //printf("movendo %d,%d %d\n",nx,ny,viva);
        //if (!viva) {
        //    printf("morri espaco %.2f %.2f %d,%d %d,%d\n",pos.x,pos.y,espacoVida.x,espacoVida.y,espacoVida.w,espacoVida.h);
        //}
    }*/

    virtual void Pausa()override{
        CPIGAnimacao::Pausa();
        timerVida->Pausa();
    }

    virtual void Despausa()override{
        CPIGAnimacao::Despausa();
        timerVida->Despausa();
    }

    virtual void Reinicia(bool congelado=false)override{
        CPIGAnimacao::Reinicia(congelado);
        timerVida->Reinicia(congelado);
    }

    bool Colisao(PIGObjeto outro) override{
        bool resp = CPIGObjeto::Colisao(outro);
        if (resp){
            ModificaHP(-1);
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
