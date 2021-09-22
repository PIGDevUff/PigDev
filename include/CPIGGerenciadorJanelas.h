#ifndef _CPIGGerenciadorJanelas_
#define _CPIGGerenciadorJanelas_

#include "CPIGJanela.h"

class CPIGGerenciadorJanelas{

private:

static int qtdJanelas;
static PIGJanela janelas[PIG_MAX_JANELAS];

public:

static void Inicia(std::string nome,int altura=PIG_ALT_TELA,int largura=PIG_LARG_TELA){
    qtdJanelas = 0;
    for (int i=0;i<PIG_MAX_JANELAS;i++)
        janelas[i] = NULL;

    janelas[qtdJanelas++] = new CPIGJanela(nome,qtdJanelas,altura,largura);
}

static void Encerra(){
    for (int i=0;i<qtdJanelas;i++)
        if (janelas[i]) delete janelas[i];
}

static int GetQtdJanelas(){
    int resp = qtdJanelas;
    for (int i=0;i<qtdJanelas;i++)
        if (GetJanela(i)->GetFechada()) resp--;
    return resp;
}

static int CriaJanela(std::string nome,int altura=PIG_ALT_TELA,int largura=PIG_LARG_TELA){
    if (qtdJanelas==PIG_MAX_JANELAS) return -1;
    janelas[qtdJanelas++] = new CPIGJanela(nome,qtdJanelas,altura,largura);
    return qtdJanelas-1;//foi incrmentada log acima
}

inline static PIGJanela GetJanela(int idJanela){
    if (idJanela<0||idJanela>=qtdJanelas||janelas[idJanela]==NULL) throw CPIGErroIndice(idJanela,"janelas");
    return janelas[idJanela];
}

static void IniciaDesenho(int idJanela=-1){
    if (idJanela>-1){
        GetJanela(idJanela)->IniciaDesenho();
    }else{
        for (int i=0;i<qtdJanelas;i++){
            GetJanela(i)->IniciaDesenho();
        }
    }
}

static void EncerraDesenho(int idJanela=-1){
    if (idJanela>-1){
        GetJanela(idJanela)->EncerraDesenho();
    }else{
        for (int i=0;i<qtdJanelas;i++){
            GetJanela(i)->EncerraDesenho();
        }
    }
}


};

int CPIGGerenciadorJanelas::qtdJanelas;
PIGJanela CPIGGerenciadorJanelas::janelas[PIG_MAX_JANELAS];
#endif // _CPIGGerenciadorJanelas_
