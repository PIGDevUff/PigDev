#ifndef _CPIGGERENCIADORTELAS_
#define _CPIGGERENCIADORTELAS_

#include "CPIGTela.h"

class CPIGGerenciadorTelas{

private:

static int telaAtual;
static PIGTela telas[PIG_MAX_TELAS];

public:

static void Inicia(){
    telaAtual = -1;
    for (int i=0;i<PIG_MAX_TELAS;i++)
        telas[i] = NULL;
}

static void Encerra(){
    for (int i=0;i<PIG_MAX_TELAS;i++)
        if (telas[i]) delete telas[i];
}

static PIGTela GetTela(int idTela){
    if (idTela<0||idTela>=PIG_MAX_TELAS||telas[idTela]==NULL) throw CPIGErroIndice(idTela,"telas");
    return telas[idTela];
}

static int DefineTelaInicial(int idTela){
    if (GetTela(idTela)!=NULL)
        telaAtual = idTela;
    return 1;
}

static int CriaTela(int idTela, void *dados, PIGFuncaoSimples acaoCria, string imgFundo="", double tempoSaida=0.5, int idJanela=-1){
    if (idTela>=0&&idTela<PIG_MAX_TELAS){
        if (telas[idTela]!=NULL){
            printf("Tela %d criada novamente\n",idTela);
            return 0;
        }
        telas[idTela] = new CPIGTela(idTela,dados,acaoCria,imgFundo,tempoSaida,idJanela);
        return 1;
    }
    return -1;
}

static int TrataEvento(PIGEvento evento){
    return GetTela(telaAtual)->TrataEvento(evento);
}

static void PreparaMudancaTela(int novaTela){
    GetTela(telaAtual)->PreparaSaida(novaTela);
}

static int Atualiza(){
    int novaTela = GetTela(telaAtual)->Atualiza();
    GetTela(telaAtual)->DescarregaTela();
    telaAtual = novaTela;
    GetTela(telaAtual)->CarregaTela();
    return GetTela(telaAtual)->Atualiza();
}

static int Desenha(){
    return GetTela(telaAtual)->Desenha();
}

};

int CPIGGerenciadorTelas::telaAtual;
PIGTela CPIGGerenciadorTelas::telas[PIG_MAX_TELAS];

#endif // _CPIGGERENCIADORTELAS_
