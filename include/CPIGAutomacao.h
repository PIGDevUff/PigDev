#ifndef _CPIGAUTOMACAO_
#define _CPIGAUTOMACAO_

#include "CPIGTransicao.h"

typedef struct tipoacao{
    double inicio;
    double tempoRepeticao;
    PIGFuncaoSimples acao;
    void *param;
}PIGAcao;

typedef enum {PIG_TRANSICAO_NORMAL,PIG_TRANSICAO_LOOP, PIG_TRANSICAO_VAIVEM} PIGTipoTransicao;

class CPIGAutomacao{

private:
PIGTipoTransicao tipo;
int transAtual,somaTrans;
vector<PIGTransicao> transicoes;
vector<PIGAcao> timelineAcoes;
PIGTimer timerAcoes;
int idDono;
bool iniciado;

public:

CPIGAutomacao(int idProprietario){
    idDono = idProprietario;
    tipo = PIG_TRANSICAO_NORMAL;
    transAtual = 0;
    somaTrans = +1;
    timerAcoes = new CPIGTimer(true);
    iniciado = false;
}

CPIGAutomacao(int idProprietario, CPIGAutomacao *outro){
    idDono = idProprietario;
    tipo = outro->tipo;
    transAtual = outro->transAtual;
    somaTrans = outro->somaTrans;
    timerAcoes = new CPIGTimer(true);
    timelineAcoes = outro->timelineAcoes;
    for (unsigned int i=0;i<outro->transicoes.size();i++){
        PIGTransicao t = new CPIGTransicao(outro->transicoes[i]);
        transicoes.push_back(t);
    }
    iniciado = false;
}

virtual ~CPIGAutomacao(){
    delete timerAcoes;
    LimpaTransicoes();
    timelineAcoes.clear();
}

bool TemTransicoes(){
    return transicoes.size()>0;
}

void InsereTransicao(PIGTransicao t){
    transicoes.push_back(t);
}

void SetTipoTransicao(PIGTipoTransicao valor){
    tipo = valor;
}

void IniciaAutomacao(PIGEstadoTransicao inicial){
    iniciado=true;
    timerAcoes->Despausa();
    if (transAtual<transicoes.size()){
        transAtual = 0;
        transicoes[transAtual]->IniciaTransicao(inicial);
    }
}

void PausaAutomacao(){
    timerAcoes->Pausa();
    if (transAtual<transicoes.size()){
        transicoes[transAtual]->Pausa();
    }
}

void DespausaAutomacao(){
    timerAcoes->Despausa();
    if (transAtual<transicoes.size()){
        transicoes[transAtual]->Despausa();
    }
}

bool ExecutandoTransicao(){
    return iniciado&&transAtual<transicoes.size();
}

PIGTransicao GetTransicaoAtual(){
    if (transicoes.size()<=transAtual||iniciado==false) return NULL;
    double sobra = transicoes[transAtual]->CalculaTransicao();
    if (sobra>=0){
        PIGEstadoTransicao atual = transicoes[transAtual]->GetFim();
        if (tipo == PIG_TRANSICAO_VAIVEM){
            transAtual += somaTrans;
            if (transAtual==transicoes.size()||transAtual==-1){
                somaTrans=-somaTrans;
                transAtual += somaTrans;
                for (unsigned int i=0;i<transicoes.size();i++)
                    transicoes[i]->Inverte();
            }
        }else{
            transAtual++;
            if (tipo == PIG_TRANSICAO_LOOP)
                transAtual %= transicoes.size(); //volta à transicao com índice 0
            else{
                if (transAtual==transicoes.size()) return transicoes[transAtual-1];//as transicoes acabaram
            }
        }
        transicoes[transAtual]->IniciaTransicao(atual,sobra);
    }
    return transicoes[transAtual];
}

void LimpaTransicoes(){
    for (unsigned int i=0;i<transicoes.size();i++)
        delete transicoes[i];
    transicoes.clear();
    transAtual = 0;
}

void LimpaAcoes(){
    timelineAcoes.clear();
}

bool TemAcoes(){
    return timelineAcoes.size()>0;
}

int InsereAcao(PIGFuncaoSimples acao, double inicio, double repeticao, void *param){
    //printf("inserindo acao no tempo %.2f com rep %.2f\n",inicio,repeticao);
    unsigned int i=0;
    inicio += timerAcoes->GetTempoDecorrido();
    while (i<timelineAcoes.size()&&timelineAcoes[i].inicio<inicio)
        i++;
    timelineAcoes.insert(timelineAcoes.begin()+i,{inicio,repeticao,acao,param});
    return i;
}

int TrataAcao(){
    PIGAcao acaoAtual;
    while (timelineAcoes.size()>0 && timerAcoes->GetTempoDecorrido()>=(acaoAtual = timelineAcoes[0]).inicio){
        acaoAtual.acao(idDono,acaoAtual.param);
        //printf("exec acao no tempo %.2f\n",acaoAtual.inicio);
        if (acaoAtual.tempoRepeticao>0)
            InsereAcao(acaoAtual.acao,acaoAtual.tempoRepeticao,acaoAtual.tempoRepeticao,acaoAtual.param);//
        timelineAcoes.erase(timelineAcoes.begin());
    }
    return timelineAcoes.size();
}


};
typedef CPIGAutomacao *PIGAutomacao;

#endif // _CPIGAUTOMACAO_
