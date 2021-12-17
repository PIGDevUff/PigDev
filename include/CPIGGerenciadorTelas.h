#ifndef _CPIGGERENCIADORTELAS_
#define _CPIGGERENCIADORTELAS_

#include "CPIGTela.h"

class CPIGGerenciadorTelas{

private:

static int telaAtual;
static void *dadosGerais;
static PIGTela telas[PIG_MAX_TELAS];
static PIGComportamentoTela comportamento[PIG_MAX_TELAS];

public:

static void Inicia(){
    telaAtual = -1;
    for (int i=0;i<PIG_MAX_TELAS;i++){
        telas[i] = NULL;
        comportamento[i].dados = NULL;
        comportamento[i].acaoCria = NULL;
        comportamento[i].acaoDestroi = NULL;
        comportamento[i].acaoCarrega = NULL;
        comportamento[i].acaoDescarrega = NULL;
        comportamento[i].acaoAtualiza = NULL;
        comportamento[i].acaoDesenha = NULL;
        comportamento[i].acaoTrataEvento = NULL;
    }
}

static void Encerra(){
    for (int i=0;i<PIG_MAX_TELAS;i++)
        if (telas[i]) delete telas[i];
}

static PIGTela GetTela(int idTela){
    if (idTela<0||idTela>=PIG_MAX_TELAS||telas[idTela]==NULL) throw CPIGErroIndice(idTela,"telas");
    return telas[idTela];
}

static void SetDadosGerais(void *dados){
    dadosGerais = dados;
}

static void *GetDadosGerais(){
    return dadosGerais;
}

static int CriaTela(int idTela, bool criarBackground=false, bool carregarBackground=false, string imgFundo="", int idJanela=0){
    if (idTela>=0&&idTela<PIG_MAX_TELAS){
        if (telas[idTela]!=NULL){
            printf("Tela %d criada novamente\n",idTela);
            return 0;
        }

        telas[idTela] = new CPIGTela(idTela,comportamento[idTela],criarBackground,carregarBackground,imgFundo,idJanela);

        if (telaAtual==-1)//se for a primeira tela criada, ela será considerada telaAtual
            telaAtual = idTela;
        return 1;
    }
    return -1;
}

static void SetComportamento(int idTela, void *dados, PIGFuncaoSimples cria, PIGFuncaoSimples destroi, PIGFuncaoSimples carrega, PIGFuncaoSimples descarrega, PIGFuncaoSimples atualiza, PIGFuncaoSimples desenha, PIGFuncaoEvento trataEvento){
    if (idTela>=0&&idTela<PIG_MAX_TELAS){
        PIGComportamentoTela comporta={dados,cria,destroi,carrega,descarrega,atualiza,desenha,trataEvento};
        comportamento[idTela] = comporta;
        if (telas[idTela])
            telas[idTela]->SetComportamento(comporta);
    }
}

static int DestroiTela(int idTela){
    if (idTela<0||idTela>=PIG_MAX_TELAS||telas[idTela]==NULL) throw CPIGErroIndice(idTela,"telas");
    delete telas[idTela];
    telas[idTela] = NULL;
    return 1;
}

static PIGEstadoTela GetEstadoTela(int idTela){
    if (idTela<0||idTela>=PIG_MAX_TELAS) throw CPIGErroIndice(idTela,"telas");
    if (telas[idTela]==NULL) return PIG_TELA_INEXISTENTE;
    return telas[idTela]->GetEstado();
}

static int TrataEvento(PIGEvento evento){
    return GetTela(telaAtual)->TrataEvento(evento);
}

static void PreparaMudancaTela(int novaTela, double tempoSaida=PIG_TEMPO_SAIDA_TELA_PADRAO, bool destroiDescarregar=false){
    GetTela(telaAtual)->PreparaSaida(novaTela,tempoSaida,destroiDescarregar);
}

static int Atualiza(){
    PIGTela atual = GetTela(telaAtual);
    int novaTela = atual->Atualiza();
    if (novaTela>=0){
        //printf("mudando para %d\n",novaTela);
        atual->DescarregaTela();
        if (atual->GetDestruirAoDescarregar())
            DestroiTela(telaAtual);
        //printf("descarreg %d\n",novaTela);
        telaAtual = novaTela;
        atual = GetTela(telaAtual);
        if (atual->CarregaTela()>0){
            //printf("carregando %d\n",novaTela);
            return atual->Atualiza();
        }else return telaAtual;
    }
    return -1;
}

static int Desenha(){
    return GetTela(telaAtual)->Desenha();
}

};

int CPIGGerenciadorTelas::telaAtual;
void *CPIGGerenciadorTelas::dadosGerais;
PIGComportamentoTela CPIGGerenciadorTelas::comportamento[PIG_MAX_TELAS];
PIGTela CPIGGerenciadorTelas::telas[PIG_MAX_TELAS];

#endif // _CPIGGERENCIADORTELAS_
