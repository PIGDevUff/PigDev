#ifndef _CPIGSEQUENCIATRANSICOES_
#define _CPIGSEQUENCIATRANSICOES_

#include "CPIGTransicao.h"

typedef enum {PIG_TRANSICAO_NORMAL,PIG_TRANSICAO_LOOP, PIG_TRANSICAO_INVERTIDA} PIG_TipoTransicao;

class CPIGSequenciaTransicoes{

private:
PIG_TipoTransicao tipo;
int transAtual;
vector<PIGTransicao> trans;

public:

CPIGSequenciaTransicoes(){
    tipo = PIG_TRANSICAO_NORMAL;
    transAtual=0;
}

~CPIGSequenciaTransicoes(){
    for (int i=0;i<trans.size();i++)
        delete trans[i];
}

bool TemTransicoes(){
    return trans.size()>0;
}

void Insere(PIGTransicao t){
    trans.push_back(t);
}

void SetTipoTransicao(PIG_TipoTransicao valor){
    tipo = valor;
}

void IniciaTransicoes(){
    if (transAtual<trans.size()){
        transAtual = 0;
        trans[transAtual]->IniciaTransicao();
    }
}

PIGTransicao GetTransicaoAtual(){
    if (trans.size()==transAtual) return NULL;
    if (trans[transAtual]->CalculaTransicao()==0){
        if (tipo == PIG_TRANSICAO_INVERTIDA){
            static int somaTrans = 1;
            transAtual += somaTrans;
            if (transAtual==trans.size()||transAtual==-1){
                somaTrans=-somaTrans;
                transAtual += somaTrans;
                for (int i=0;i<trans.size();i++)
                    trans[i]->Inverte();
            }
        }else{
            transAtual++;
            if (tipo == PIG_TRANSICAO_LOOP)
                transAtual %= trans.size(); //volta à transicao com índice 0
            else{
                if (transAtual==trans.size()) return NULL;//as transicoes acabaram
            }
        }
        printf("trans atual: %d\n",transAtual);
        trans[transAtual]->IniciaTransicao();
    }
    return trans[transAtual];
}

};
typedef CPIGSequenciaTransicoes *PIGSequenciaTransicoes;

#endif // _CPIGSEQUENCIATRANSICOES_
