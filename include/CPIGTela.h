#ifndef _CPIGTELA_
#define _CPIGTELA_

class CPIGTela{

protected:

int mudarPara;
int id,janela;
double tempoSaida;
int timerSaida;
int spriteFundo;
void *dados;
PIGFuncaoSimples acaoCarrega,acaoDescarrega,acaoAtualiza,acaoDesenha,acaoDestroi;
PIGFuncaoEvento acaoTrataEvento;

public:

CPIGTela(int idTela, void *dadosEspecificos, PIGFuncaoSimples cria, string imgFundo="", double tempoTotalSaida=0.5, int idJanela=0){
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
    return 1;
}

int DescarregaTela(){
    if (acaoDescarrega!=NULL)
        return acaoDescarrega(id,dados);
    return 0;
}

int TrataEvento(PIGEvento evento){
    if (acaoTrataEvento!=NULL)
        return acaoTrataEvento(id,evento,dados);
    return PIG_NAOSELECIONADO;
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

void DefineAcaoCarrega(PIGFuncaoSimples acao){
    acaoCarrega = acao;
}

void DefineAcaoDescarrega(PIGFuncaoSimples acao){
    acaoDescarrega = acao;
}

void DefineAcaoAtualiza(PIGFuncaoSimples acao){
    acaoAtualiza = acao;
}

void DefineAcaoDesenha(PIGFuncaoSimples acao){
    acaoDesenha = acao;
}

void DefineAcaoTrataEvento(PIGFuncaoEvento acao){
    acaoTrataEvento = acao;
}

void DefineAcaoDestroi(PIGFuncaoSimples acao){
    acaoDestroi = acao;
}

};

typedef CPIGTela *PIGTela;
#endif // _CPIGTELA_
