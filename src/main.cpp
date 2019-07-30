#include "PIG.h"

PIG_Evento evento;
PIG_Teclado meuTeclado;

int main( int argc, char* args[] ){

    CriaJogo("Meu Jogo");

    meuTeclado = GetTeclado();

    while(JogoRodando()){
        evento = GetEvento();

        IniciaDesenho();

        EncerraDesenho();
    }

    FinalizaJogo();
    return 0;
}
