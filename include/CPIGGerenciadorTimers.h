#ifndef _CPIGGERENCIADORTIMERS_
#define _CPIGGERENCIADORTIMERS_

#include "CPIGTimer.h"
class CPIGGerenciadorTimers{

private:

    static CPIGRepositorio<PIGTimer> *timers;
public:

    static void Inicia(){
        timers = new CPIGRepositorio<PIGTimer>(PIG_MAX_TIMERS,"timers");
    }

    static void Encerra(){
        delete timers;
    }

    static PIGTimer GetTimer(int idTimer){
        return timers->GetElemento(idTimer);
    }

    static int CriaTimer(bool congelado=false){
        return timers->Insere(new CPIGTimer(congelado));
    }

    static void DestroiTimer(int idTimer){
        timers->Remove(idTimer);
    }

    static void PausaTodos(){
        PIGTimer t = timers->GetPrimeiroElemento();
        while (t != NULL){
            t->Pausa();
            t = timers->GetProximoElemento();
        }
    }

    static void DespausaTodos(){
        PIGTimer t = timers->GetPrimeiroElemento();
        while (t != NULL){
            t->Despausa();
            t = timers->GetProximoElemento();
        }
    }


};
CPIGRepositorio<PIGTimer> *CPIGGerenciadorTimers::timers;
#endif // _CPIGGERENCIADORTIMERS_
