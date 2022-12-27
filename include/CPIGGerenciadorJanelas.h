#ifndef _CPIGGERENCIADORJANELAS_
#define _CPIGGERENCIADORJANELAS_

#include "CPIGJanela.h"
#include "CPIGRepositorio.h"

class CPIGGerenciadorJanelas: public CPIGRepositorio<PIGJanela>{

public:

    CPIGGerenciadorJanelas():CPIGRepositorio<PIGJanela>(PIG_MAX_JANELAS,"CPIGJanela"){}

    int CriaJanela(string nome, int altura=PIG_ALT_TELA, int largura=PIG_LARG_TELA){
        return Insere(new CPIGJanela(ProxID(),nome,altura,largura));
    }

    void IniciaDesenho(int idJanela=-1){
        if (idJanela>-1){
            GetElemento(idJanela)->IniciaDesenho();
        }else{
            for (int i=0;i<maxElementos;i++){
                if (elementos[i])
                    elementos[i]->IniciaDesenho();
            }
        }
    }

    void EncerraDesenho(int idJanela=-1){
        if (idJanela>-1){
            GetElemento(idJanela)->EncerraDesenho();
        }else{
            for (int i=0;i<maxElementos;i++){
                if (elementos[i])
                    elementos[i]->EncerraDesenho();
            }
        }
    }
};
CPIGGerenciadorJanelas pigGerJanelas;
#endif // _CPIGGERENCIADORJANELAS_
