#ifndef _CPIGGERENCIADORTIMERS_
#define _CPIGGERENCIADORTIMERS_

#include "CPIGTimer.h"
class CPIGGerenciadorTimers{

private:

    static int totalTimers;
    static PIGPoolNumeros numTimers;
    static PIGTimer timers[MAX_TIMERS];

public:

    static void Inicia(){
        totalTimers = 0;
        for (int i=0;i<MAX_TIMERS;i++)
            timers[i] = NULL;
        numTimers = new CPIGPoolNumeros(MAX_TIMERS);
    }

    static void Encerra(){
        for (int i=0;i<MAX_TIMERS;i++){
            if (timers[i]) delete timers[i];
        }
        delete numTimers;
    }

    static int CriaTimer(bool congelado=false){
        int resp = numTimers->RetiraLivre();
        timers[resp] = new CPIGTimer(congelado);
        totalTimers++;
        return resp;
    }

    static void DestroiTimer(int id_timer){
        numTimers->DevolveUsado(id_timer);
        totalTimers--;
        delete timers[id_timer];
        timers[id_timer] = NULL;
    }

    static void PausaTodos(){
        for (int i=0;i<MAX_TIMERS;i++){
            if (timers[i])
                timers[i]->Pausa();
        }
    }

    static void DespausaTodos(){
        for (int i=0;i<MAX_TIMERS;i++){
            if (timers[i]){
                timers[i]->Despausa();
            }
        }
    }

    inline static float GetTempoDecorrido(int idTimer){
        return timers[idTimer]->GetTempoDecorrido();
    }

    inline static void ReiniciaTimer(int idTimer,bool congelado=false){
        timers[idTimer]->Reinicia(congelado);
    }

    inline static void PausaTimer(int idTimer){
        timers[idTimer]->Pausa();
    }

    inline static void DespausaTimer(int idTimer){
        timers[idTimer]->Despausa();
    }

};

PIGPoolNumeros CPIGGerenciadorTimers::numTimers;
int CPIGGerenciadorTimers::totalTimers;
PIGTimer CPIGGerenciadorTimers::timers[MAX_TIMERS];
#endif // _CPIGGERENCIADORTIMERS_
