#ifndef _CPIGTIMER_
#define _CPIGTIMER_

#include <chrono>

class CPIGTimer{

private:

    int id;
    chrono::system_clock::time_point inicio;
    chrono::system_clock::time_point pausa;
    double totalPausa;
    bool pausado,pausadoGeral;

public:

    CPIGTimer(int idTimer,bool congelado){
        id = idTimer;
        pausadoGeral=false;
        SetTempo(0,congelado);
    }

    ~CPIGTimer(){}

    double GetTempoDecorrido(){
        chrono::duration<double> tempo;
        if (pausado||pausadoGeral){
            tempo = chrono::duration_cast<chrono::duration<double>>(pausa-inicio);
        }else{
            tempo = chrono::duration_cast<chrono::duration<double>>(chrono::system_clock::now()-inicio);
        }
        return tempo.count()-totalPausa;
    }

    int GetID(){
        return id;
    }

    virtual void Pausa(){
        if (!pausado){
            pausado = true;
            if (!pausadoGeral)
                pausa = chrono::system_clock::now();
        }
    }

    virtual void PausaGeral(){
        if (!pausadoGeral){
            pausadoGeral = true;
            if (!pausado){
                pausa = chrono::system_clock::now();
            }
        }
    }

    virtual void DespausaGeral(){
        if (pausadoGeral){
            pausadoGeral = false;
            if (!pausado){
                chrono::duration<double> tempo = chrono::duration_cast<chrono::duration<double>>(chrono::system_clock::now()-pausa);
                totalPausa += tempo.count();
            }
        }
    }

    double GetPausa(){
        return totalPausa;
    }

    virtual void Despausa(){
        if (pausado){
            if (!pausadoGeral){
                chrono::duration<double> tempo = chrono::duration_cast<chrono::duration<double>>(chrono::system_clock::now()-pausa);
                totalPausa += tempo.count();
            }
            pausado = false;
        }
    }

    inline void Reinicia(bool congelado){
        SetTempo(0,congelado);
    }

    inline void SetTempo(double tempo, bool congelado){
        pausa = inicio = chrono::system_clock::now();
        totalPausa = -tempo;
        pausado = congelado;
    }
};
typedef CPIGTimer* PIGTimer;
#endif // _CPIGTIMER_
