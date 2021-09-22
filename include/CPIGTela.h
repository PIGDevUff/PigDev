#ifndef __CPIGTELA__
#define __CPIGTELA__

class CPIGTela{

protected:

int mudarPara;
int id,janela;
double tempoSaida;
int timerSaida;
int spriteFundo;
void *dados;
PIG_FuncaoSimples acaoCarrega,acaoDescarrega,acaoAtualiza,acaoDesenha,acaoDestroi;
PIG_FuncaoEvento acaoTrataEvento;

public:

CPIGTela(int idTela, void *dadosEspecificos, PIG_FuncaoSimples cria, string imgFundo="", double tempoTotalSaida=0.5, int idJanela=0){
    id = idTela;
    acaoAtualiza = acaoCarrega = acaoDescarrega = acaoDesenha = acaoDestroi = NULL;
    acaoTrataEvento = NULL;
    dados = dadosEspecificos;
    janela = idJanela;
    tempoSaida = tempoTotalSaida;
    timerSaida = CPIGGerenciadorTimers::CriaTimer(true);
    spriteFundo = -1;
    if (imgFundo!=""){
        spriteFundo = CPIGGerenciadorSprites::CriaSprite(imgFundo,1,NULL,janela);
        CPIGGerenciadorSprites::GetSprite(spriteFundo)->SetDimensoes(PIG_ALT_TELA,PIG_LARG_TELA);
    }
    if (cria!=NULL)
        cria(id,dados);

}

~CPIGTela(){
    CPIGGerenciadorTimers::DestroiTimer(timerSaida);
    if (acaoDestroi!=NULL)
        acaoDestroi(id,dados);
}

int CarregaTela(){
    mudarPara = -1;
    CPIGGerenciadorTimers::GetTimer(timerSaida)->Reinicia(true);
    if (acaoCarrega!=NULL)
        acaoCarrega(id,dados);
}

int DescarregaTela(){
    if (acaoDescarrega!=NULL)
        return acaoDescarrega(id,dados);
    return 0;
}

int TrataEvento(PIG_Evento evento){
    if (acaoTrataEvento!=NULL)
        return acaoTrataEvento(id,evento,dados);
    return PIG_NAO_SELECIONADO;
}

void PreparaSaida(int outraTela){
    CPIGGerenciadorTimers::GetTimer(timerSaida)->Despausa();
    mudarPara = outraTela;
}

int Atualiza(){
    if (acaoAtualiza!=NULL)
        acaoAtualiza(id,dados);
    if (CPIGGerenciadorTimers::GetTimer(timerSaida)->GetTempoDecorrido()>tempoSaida)
        return mudarPara;
    else return -1;
}

int Desenha(){
    if (spriteFundo!=-1)
        CPIGGerenciadorSprites::GetSprite(spriteFundo)->Desenha();
    if (acaoDesenha!=NULL)
        return acaoDesenha(id,dados);
    return 0;
}

void DefineAcaoCarrega(PIG_FuncaoSimples acao){
    acaoCarrega = acao;
}

void DefineAcaoDescarrega(PIG_FuncaoSimples acao){
    acaoDescarrega = acao;
}

void DefineAcaoAtualiza(PIG_FuncaoSimples acao){
    acaoAtualiza = acao;
}

void DefineAcaoDesenha(PIG_FuncaoSimples acao){
    acaoDesenha = acao;
}

void DefineAcaoTrataEvento(PIG_FuncaoEvento acao){
    acaoTrataEvento = acao;
}

void DefineAcaoDestroi(PIG_FuncaoSimples acao){
    acaoDestroi = acao;
}


};

typedef CPIGTela *PIGTela;
#endif // __CPIGTELA__
