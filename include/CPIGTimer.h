#ifndef _CPIGTIMER_
#define _CPIGTIMER_

#include <chrono>

class CPIGTimer{

private:
    chrono::system_clock::time_point inicio;
    chrono::system_clock::time_point pausa;
    double totalPausa;
    bool pausado,pausadoGeral;

public:

    CPIGTimer(bool congelado){
        pausadoGeral=false;
        Reinicia(congelado);
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

    void Reinicia(bool congelado){
        pausa = inicio = chrono::system_clock::now();
        totalPausa = 0;
        pausado = congelado;
    }
};
typedef CPIGTimer* PIGTimer;
#endif // _CPIGTIMER_
