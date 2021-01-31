#ifndef _CPIGTIMER_
#define _CPIGTIMER_

#include <chrono>
class CPIGTimer{

private:
    std::chrono::system_clock::time_point inicio;
    std::chrono::system_clock::time_point pausa;
    double totalPausa;
    bool pausado;

public:
    CPIGTimer(bool congelado){
        Reinicia(congelado);
    }

    ~CPIGTimer(){
    }

    double GetTempoDecorrido(){
        std::chrono::duration<double> tempo;
        if (pausado){
            tempo = std::chrono::duration_cast<std::chrono::duration<double>>(pausa-inicio);
        }else{
            tempo = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::system_clock::now()-inicio);
        }
        return tempo.count()-totalPausa;
    }

    void Pausa(){
        if (!pausado){
            pausado = true;
            pausa = std::chrono::system_clock::now();
        }
    }

    void Despausa(){
        if (pausado){
            std::chrono::duration<double> tempo = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::system_clock::now()-pausa);
            totalPausa += tempo.count();
            pausado = false;
        }
    }

    void Reinicia(bool congelado){
        pausa = inicio = std::chrono::system_clock::now();
        totalPausa = 0;
        pausado = congelado;
    }

    CPIGTimer* Copia(){
        CPIGTimer* outro = new CPIGTimer(pausado);
        outro->inicio = inicio;
        outro->pausa = pausa;
        outro->totalPausa = totalPausa;
        return outro;
    }
};

typedef CPIGTimer* PIGTimer;
#endif // _CPIGTIMER_
