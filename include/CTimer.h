#include <chrono>
class CTimer{

private:
    std::chrono::system_clock::time_point inicio;
    std::chrono::system_clock::time_point pausa;
    double totalPausa;
    bool pausado;

public:
    CTimer(bool congelado){
        Reinicia(congelado);
    }

    ~CTimer(){
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
        pausado = false;
        if (congelado){
            Pausa();
        }
    }

    CTimer* Copia(){
        CTimer* outro = new CTimer(pausado);
        outro->inicio = inicio;
        outro->pausa = pausa;
        outro->totalPausa = totalPausa;
        return outro;
    }
};

typedef CTimer* Timer;
