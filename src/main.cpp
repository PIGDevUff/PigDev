#include "PIG.h"

PIGEvento evento;          //evento ser tratado a cada passada do loop principal
PIGTeclado meuTeclado;     //variável como mapeamento do teclado

int main( int argc, char* args[] ){

    //criando o jogo (aplicação)
    CriaJogo("Meu Jogo");

    //associando o teclado (basta uma única vez) com a variável meuTeclado
    meuTeclado = GetTeclado();

    //int num = CriaFonteNormal("..//fontes//arial.ttf",30,VERDE);
    int num = CriaFonteDinamica("..//fontes//arial.ttf",30);

    //loop principal do jogo
    while(JogoRodando()){

        //pega um evento que tenha ocorrido desde a última passada do loop
        evento = GetEvento();

        //aqui o evento deve ser tratado e tudo deve ser atualizado

        //será feita a preparação do frame que será exibido na tela
        IniciaDesenho();

        EscreverLongaEsquerda(lido,10,300,50,60,VERDE,num);

        //todas as chamadas de desenho devem ser feitas aqui na ordem desejada

        //o frame totalmente pronto será mostrado na tela
        EncerraDesenho();
    }

    //o jogo será encerrado
    FinalizaJogo();

    return 0;
}
