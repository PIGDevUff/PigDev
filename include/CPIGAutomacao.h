#ifndef _CPIGAUTOMACAO_
#define _CPIGAUTOMACAO_

#include "CPIGTransicao.h"

typedef struct tipoacao{
    double inicio;
    double tempoRepeticao;
    PIG_FuncaoSimples acao;
    void *param;
} PIG_Automacao;

typedef enum {PIG_TRANSICAO_NORMAL,PIG_TRANSICAO_LOOP, PIG_TRANSICAO_INVERTIDA} PIG_TipoTransicao;

class CPIGAutomacao{

private:
PIG_TipoTransicao tipo;
int transAtual;
vector<PIGTransicao> transicoes;
vector<PIG_Automacao> timelineAcoes;
int timerAcoes;
int idDono;

public:

CPIGAutomacao(int idProprietario){
    idDono = idProprietario;
    tipo = PIG_TRANSICAO_NORMAL;
    transAtual = 0;
    timerAcoes = CPIGGerenciadorTimers::CriaTimer(true);
}

~CPIGAutomacao(){
    CPIGGerenciadorTimers::DestroiTimer(timerAcoes);
    for (int i=0;i<transicoes.size();i++)
        delete transicoes[i];
}

bool TemTransicoes(){
    return transicoes.size()>0;
}

void InsereTransicao(PIGTransicao t){
    transicoes.push_back(t);
}

void SetTipoTransicao(PIG_TipoTransicao valor){
    tipo = valor;
}

void IniciaTransicoes(){
    if (transAtual<transicoes.size()){
        CPIGGerenciadorTimers::GetTimer(timerAcoes)->Despausa();
        transAtual = 0;
        transicoes[transAtual]->IniciaTransicao();
    }
}

PIGTransicao GetTransicaoAtual(){
    if (transicoes.size()==transAtual) return NULL;
    if (transicoes[transAtual]->CalculaTransicao()==0){
        if (tipo == PIG_TRANSICAO_INVERTIDA){
            static int somaTrans = 1;
            transAtual += somaTrans;
            if (transAtual==transicoes.size()||transAtual==-1){
                somaTrans=-somaTrans;
                transAtual += somaTrans;
                for (int i=0;i<transicoes.size();i++)
                    transicoes[i]->Inverte();
            }
        }else{
            transAtual++;
            if (tipo == PIG_TRANSICAO_LOOP)
                transAtual %= transicoes.size(); //volta à transicao com índice 0
            else{
                if (transAtual==transicoes.size()) return NULL;//as transicoes acabaram
            }
        }
        printf("trans atual: %d\n",transAtual);
        transicoes[transAtual]->IniciaTransicao();
    }
    return transicoes[transAtual];
}

bool TemAcoes(){
    return timelineAcoes.size()>0;
}

int InsereAcao(PIG_FuncaoSimples acao,double inicio,double repeticao,void *param){
    int i=0;
    while (i<timelineAcoes.size()&&timelineAcoes[i].inicio<inicio)
        i++;
    timelineAcoes.insert(timelineAcoes.begin()+i,{inicio,repeticao,acao,param});
    return i;
}

int TrataAcao(){
    PIG_Automacao acaoAtual;
    while (timelineAcoes.size()>0 && CPIGGerenciadorTimers::GetTimer(timerAcoes)->GetTempoDecorrido()>=(acaoAtual = timelineAcoes[0]).inicio){
        acaoAtual.acao(idDono,acaoAtual.param);
        if (acaoAtual.tempoRepeticao>0)
            InsereAcao(acaoAtual.acao,acaoAtual.inicio+acaoAtual.tempoRepeticao,acaoAtual.tempoRepeticao,acaoAtual.param);//
        timelineAcoes.erase(timelineAcoes.begin());
    }
    return timelineAcoes.size();
}


};
typedef CPIGAutomacao *PIGAutomacao;


#endif // _CPIGAUTOMACAO_
