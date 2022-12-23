#ifndef _CPIGGERENCIADORTIMERS_
#define _CPIGGERENCIADORTIMERS_

#include "CPIGTimer.h"
#include "CPIGRepositorio.h"

class CPIGGerenciadorTimers: public CPIGRepositorio<PIGTimer>{

private:

    vector<int> grupos[PIG_MAX_GRUPOS_TIMERS];

public:

    CPIGGerenciadorTimers():CPIGRepositorio<PIGTimer>(PIG_MAX_TIMERS,"CPIGTimer"){}

    inline int CriaTimer(bool congelado=false){
        return Insere(new CPIGTimer(congelado));
    }

    inline void PausaTodos(){
        for (int i=0;i<maxElementos;i++)
            if (elementos[i])
                elementos[i]->PausaGeral();
    }

    inline void DespausaTodos(){
        for (int i=0;i<maxElementos;i++)
            if (elementos[i])
                elementos[i]->DespausaGeral();
    }

    inline int AssociaTimerGrupo(int idTimer, int idGrupo){
        if (idGrupo<0||idGrupo>=PIG_MAX_GRUPOS_TIMERS) return 0;
        PIGTimer t = GetElemento(idTimer);  //apenas para checar se o idTimer é valido
        grupos[idGrupo].push_back(idTimer);
        return 1;
    }

    inline int DesassociaTimerGrupo(int idTimer, int idGrupo){
        if (idGrupo<0||idGrupo>=PIG_MAX_GRUPOS_TIMERS) return 0;
        PIGTimer t = GetElemento(idTimer);  //apenas para checar se o idTimer é valido
        vector<int>::iterator it = find(grupos[idGrupo].begin(), grupos[idGrupo].end(), idTimer);
        if (it!=grupos[idGrupo].end()){
            grupos[idGrupo].erase(it);
            return 1;
        }
        return 0;
    }

    inline int PausaGrupo(int idGrupo){
        if (idGrupo<0||idGrupo>=PIG_MAX_GRUPOS_TIMERS) return -1;
        int cont=0;
        for (unsigned int i=0;i<grupos[idGrupo].size();i++){
            PIGTimer t = GetElemento(grupos[idGrupo][i]);
            if (t) t->Pausa();
            cont++;
        }
        return cont;
    }

    inline int DespausaGrupo(int idGrupo){
        if (idGrupo<0||idGrupo>=PIG_MAX_GRUPOS_TIMERS) return -1;
        int cont=0;
        for (unsigned int i=0;i<grupos[idGrupo].size();i++){
            PIGTimer t = GetElemento(grupos[idGrupo][i]);
            if (t) t->Despausa();
            cont++;
        }
        return cont;
    }

    inline int ReiniciaGrupo(int idGrupo,bool valor){
        if (idGrupo<0||idGrupo>=PIG_MAX_GRUPOS_TIMERS) return -1;
        int cont=0;
        for (unsigned int i=0;i<grupos[idGrupo].size();i++){
            PIGTimer t = GetElemento(grupos[idGrupo][i]);
            if (t) t->Reinicia(valor);
            cont++;
        }
        return cont;
    }

};
CPIGGerenciadorTimers pigGerTimers;
#endif // _CPIGGERENCIADORTIMERS_
