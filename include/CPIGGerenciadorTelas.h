#ifndef _CPIGGERENCIADORTELAS_
#define _CPIGGERENCIADORTELAS_

#include "CPIGTela.h"
#include "CPIGRepositorio.h"

class CPIGGerenciadorTelas:public CPIGRepositorio<PIGTela>{

private:

    int telaAtual;
    void *dadosGerais;
    PIGComportamentoTela comportamento[PIG_MAX_TELAS];

public:

    CPIGGerenciadorTelas():CPIGRepositorio<PIGTela>(PIG_MAX_TELAS,"CPIGTela"){
        telaAtual = -1;
        for (int i=0;i<PIG_MAX_TELAS;i++){
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

    inline void SetDadosGerais(void *dados){
        dadosGerais = dados;
    }

    inline void *GetDadosGerais(){
        return dadosGerais;
    }

    inline int CriaTela(int idTela, bool criarBackground=false, bool carregarBackground=false, string imgFundo="", int idJanela=0){
        if (idTela>=0&&idTela<PIG_MAX_TELAS){
            if (elementos[idTela]!=NULL){
                printf("Tela %d criada novamente\n",idTela);
                return 0;
            }

            elementos[idTela] = new CPIGTela(idTela,comportamento[idTela],criarBackground,carregarBackground,imgFundo,idJanela);

            if (telaAtual==-1)//se for a primeira tela criada, ela será considerada telaAtual
                telaAtual = idTela;
            return 1;
        }
        return -1;
    }

    inline int InsereTela(int idTela, PIGTela tela){
        if (idTela>=0&&idTela<PIG_MAX_TELAS){
            if (elementos[idTela]!=NULL){
                printf("Tela %d criada novamente\n",idTela);
                return 0;
            }

            elementos[idTela] = tela;

            if (telaAtual==-1)//se for a primeira tela criada, ela será considerada telaAtual
                telaAtual = idTela;
            return 1;
        }
        return -1;
    }

    inline void SetComportamento(int idTela, void *dados, PIGFuncaoSimples cria, PIGFuncaoSimples destroi, PIGFuncaoSimples carrega, PIGFuncaoSimples descarrega, PIGFuncaoSimples atualiza, PIGFuncaoSimples desenha, PIGFuncaoEvento trataEvento){
        PIGComportamentoTela comporta={dados,cria,destroi,carrega,descarrega,atualiza,desenha,trataEvento};
        GetElemento(idTela)->SetComportamento(comporta);
        comportamento[idTela] = comporta;
    }

    inline PIGEstadoTela GetEstadoTela(int idTela){
        return GetElemento(idTela)->GetEstado();
    }

    inline int TrataEvento(PIGEvento evento){
        return GetElemento(telaAtual)->TrataEvento(evento);
    }

    inline void PreparaMudancaTela(int novaTela, double tempoSaida=PIG_TEMPO_SAIDA_TELA_PADRAO, bool destroiDescarregar=false){
        GetElemento(telaAtual)->PreparaSaida(novaTela,tempoSaida,destroiDescarregar);
    }

    inline int Atualiza(){
        PIGTela atual = GetElemento(telaAtual);
        int novaTela = atual->Atualiza();
        if (novaTela>=0){
            //printf("mudando para %d\n",novaTela);
            atual->DescarregaTela();
            if (atual->GetDestruirAoDescarregar())
                Remove(telaAtual);
            //printf("descarreg %d\n",novaTela);
            telaAtual = novaTela;
            atual = GetElemento(telaAtual);
            if (atual->CarregaTela()>0){
                //printf("carregando %d\n",novaTela);
                return atual->Atualiza();
            }else return telaAtual;
        }
        return -1;
    }

    inline int Desenha(){
        return GetElemento(telaAtual)->Desenha();
    }

};

CPIGGerenciadorTelas pigGerTelas;
#endif // _CPIGGERENCIADORTELAS_
