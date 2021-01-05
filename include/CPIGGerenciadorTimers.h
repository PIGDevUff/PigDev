#ifndef _CPIGGERENCIADORTIMERS_
#define _CPIGGERENCIADORTIMERS_

#include "CPIGTimer.h"
class CPIGGerenciadorTimers{

private:

    /*static int totalTimers;
    static PIGPoolNumeros numTimers;
    static PIGTimer timers[MAX_TIMERS];*/

    static std::vector<int> posLivres;
    static std::unordered_map<int,PIGTimer> timers;
    static std::unordered_map<int,PIGTimer>::iterator it;

public:

    static void Inicia(){
        /*totalTimers = 0;
        for (int i=0;i<MAX_TIMERS;i++)
            timers[i] = NULL;
        numTimers = new CPIGPoolNumeros(MAX_TIMERS);*/
        for (int i=0;i<MAX_TIMERS;i++)
            posLivres.push_back(i);
    }

    static void Encerra(){
        /*for (int i=0;i<MAX_TIMERS;i++){
            if (timers[i]) delete timers[i];
        }
        delete numTimers;*/
        for(it = timers.begin(); it != timers.end(); ++it) {
            delete it->second;
        }
    }

    static PIGTimer GetTimer(int idTimer){
        it = timers.find(idTimer);
        if (it==timers.end()) throw CPIGErroIndice(idTimer,"timers");
        return it->second;
    }

    static int CriaTimer(bool congelado=false){
        /*int resp = numTimers->RetiraLivre();
        timers[resp] = new CPIGTimer(congelado);
        totalTimers++;
        return resp;*/
        int resp = posLivres[0];
        posLivres.erase(posLivres.begin());
        timers[resp] = new CPIGTimer(congelado);
        return resp;
    }

    static void DestroiTimer(int idTimer){
        /*numTimers->DevolveUsado(id_timer);
        totalTimers--;
        delete timers[id_timer];
        timers[id_timer] = NULL;*/
        PIGTimer timer = GetTimer(idTimer);
        delete timer;
        timers.erase(idTimer);
    }

    static void PausaTodos(){
        /*for (int i=0;i<MAX_TIMERS;i++){
            if (timers[i])
                timers[i]->Pausa();
        }*/
        for(it = timers.begin(); it != timers.end(); ++it) {
            it->second->Pausa();
        }
    }

    static void DespausaTodos(){
        /*for (int i=0;i<MAX_TIMERS;i++){
            if (timers[i]){
                timers[i]->Despausa();
            }
        }*/
        for(it = timers.begin(); it != timers.end(); ++it) {
            it->second->Despausa();
        }
    }

    /*inline static float GetTempoDecorrido(int idTimer){
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
    }*/

};
std::vector<int> CPIGGerenciadorTimers::posLivres;
std::unordered_map<int,PIGTimer> CPIGGerenciadorTimers::timers;
std::unordered_map<int,PIGTimer>::iterator CPIGGerenciadorTimers::it;
//PIGPoolNumeros CPIGGerenciadorTimers::numTimers;
//int CPIGGerenciadorTimers::totalTimers;
//PIGTimer CPIGGerenciadorTimers::timers[MAX_TIMERS];
#endif // _CPIGGERENCIADORTIMERS_
