#ifndef _CPIGTELA_
#define _CPIGTELA_

typedef enum {PIG_TELA_INEXISTENTE,PIG_TELA_CRIANDO,PIG_TELA_CRIADA,PIG_TELA_CARREGANDO,PIG_TELA_CARREGADA,PIG_TELA_SAINDO,PIG_TELA_DESCARREGADA} PIGEstadoTela;

typedef struct {
    int id;
    void *param;
    void *tela;
    PIGEstadoTela estadoFinal;
    PIGFuncaoSimples funcao;
} PIGStructThread;

typedef struct{
    void *dados;
    PIGFuncaoSimples acaoCria,acaoDestroi,acaoCarrega,acaoDescarrega,acaoAtualiza,acaoDesenha;
    PIGFuncaoEvento acaoTrataEvento;
}PIGComportamentoTela;

class CPIGTela{

protected:

int mudarPara;
int id,janela;
double tempoSaida;
int timerSaida;
int spriteCarrega;
bool criaBackground,carregaBackground;
PIGEstadoTela estado;
PIGComportamentoTela comportamento;
bool destruirAoDescarregar;

public:

static ExecutaFuncaoBackground(void *param){
    PIGStructThread *st = (PIGStructThread*) param;
    st->funcao(st->id,st->param);
    //printf("terminei funcao de criacao\n");
    CPIGTela *tela = (CPIGTela*) st->tela;
    //printf("vou alterar o estado da tela %d\n",st->tela);
    tela->estado = st->estadoFinal;

    //if(tela->id==TELA_JOGO)
    //    printf("alterei para %d\n",tela->estado);

    free(param);
    //printf("terminei background\n");
}

CPIGTela(int idTela, PIGComportamentoTela comporta, bool criarBackground=false, bool carregarBackground=false, string imgLoading="", int idJanela=0){
    id = idTela;
    janela = idJanela;
    comportamento = comporta;
    tempoSaida = PIG_TEMPO_SAIDA_TELA_PADRAO;
    timerSaida = CPIGGerenciadorTimers::CriaTimer(true);
    criaBackground = criarBackground;
    carregaBackground = carregarBackground;
    spriteCarrega = -1;
    if (imgLoading!=""){
        spriteCarrega = CPIGGerenciadorSprites::CriaSprite(imgLoading,1,NULL,janela);
        CPIGGerenciadorSprites::GetSprite(spriteCarrega)->SetDimensoes(PIG_ALT_TELA,PIG_LARG_TELA);
    }

    if (comportamento.acaoCria!=NULL){
        if (criaBackground){
            estado = PIG_TELA_CRIANDO;
            PIGStructThread *st = (PIGStructThread*)malloc(sizeof(PIGStructThread));
            st->funcao = comportamento.acaoCria;
            st->id = id;
            st->param = comportamento.dados;
            st->tela = this;
            st->estadoFinal = PIG_TELA_CRIADA;
            SDL_CreateThread(ExecutaFuncaoBackground,"",st);
        }else{
            comportamento.acaoCria(id,comportamento.dados);
            estado = PIG_TELA_CRIADA;
        }
    }else estado = PIG_TELA_CRIADA;
    destruirAoDescarregar = false;
    //printf("%d terminei o construtor\n",id);
}

~CPIGTela(){
    while (estado==PIG_TELA_CRIANDO||estado==PIG_TELA_CARREGANDO){
        SDL_Delay(10);
    }
    CPIGGerenciadorTimers::DestroiTimer(timerSaida);
    if (comportamento.acaoDestroi!=NULL)
        comportamento.acaoDestroi(id,comportamento.dados);
}

PIGEstadoTela GetEstado(){
    return estado;
}

bool GetDestruirAoDescarregar(){
    return destruirAoDescarregar;
}

int CarregaTela(){
    if (estado==PIG_TELA_CARREGADA||estado==PIG_TELA_CARREGANDO||estado==PIG_TELA_CRIANDO) return -1;
    mudarPara = -1;
    CPIGGerenciadorTimers::GetTimer(timerSaida)->Reinicia(true);
    if (comportamento.acaoCarrega!=NULL){
        if (carregaBackground){
            estado = PIG_TELA_CARREGANDO;
            PIGStructThread *st = (PIGStructThread*)malloc(sizeof(PIGStructThread));
            st->funcao = comportamento.acaoCarrega;
            st->id = id;
            st->param = comportamento.dados;
            st->tela = this;
            st->estadoFinal = PIG_TELA_CARREGADA;
            SDL_CreateThread(ExecutaFuncaoBackground,"",st);
        }else{
            comportamento.acaoCarrega(id,comportamento.dados);
            estado = PIG_TELA_CARREGADA;
        }
    }else estado = PIG_TELA_CARREGADA;
    return 1;
}

int DescarregaTela(){
    if (estado!=PIG_TELA_SAINDO) return -1;
    estado = PIG_TELA_DESCARREGADA;
    if (comportamento.acaoDescarrega!=NULL)
        return comportamento.acaoDescarrega(id,comportamento.dados);
    return 0;
}

int TrataEvento(PIGEvento evento){
    if (estado!=PIG_TELA_CARREGADA) return PIG_COMPONENTE_NAOTRATADO;
    if (comportamento.acaoTrataEvento!=NULL)
        return comportamento.acaoTrataEvento(id,evento,comportamento.dados);
    return PIG_COMPONENTE_NAOTRATADO;
}

void PreparaSaida(int outraTela, double tempo=PIG_TEMPO_SAIDA_TELA_PADRAO, bool destroiDescarga=false){
    while (estado==PIG_TELA_CRIANDO||estado==PIG_TELA_CARREGANDO)
        SDL_Delay(10);
    estado = PIG_TELA_SAINDO;
    tempoSaida = tempo;
    CPIGGerenciadorTimers::GetTimer(timerSaida)->Despausa();
    mudarPara = outraTela;
    destruirAoDescarregar = destroiDescarga;
}

int Atualiza(){
    if (estado==PIG_TELA_CRIANDO||estado==PIG_TELA_CARREGANDO)
        return -1;
    if (estado==PIG_TELA_CRIADA){
        CarregaTela();
    }
    if (estado==PIG_TELA_CARREGADA&&comportamento.acaoAtualiza!=NULL)
        comportamento.acaoAtualiza(id,comportamento.dados);
    if (CPIGGerenciadorTimers::GetTimer(timerSaida)->GetTempoDecorrido()>tempoSaida)
        return mudarPara;
    else return -1;
}

int Desenha(){
    if (spriteCarrega!=-1&&(estado==PIG_TELA_CRIANDO||estado==PIG_TELA_CARREGANDO)){
        CPIGGerenciadorJanelas::GetJanela(janela)->PreparaCameraFixa();
        CPIGGerenciadorSprites::GetSprite(spriteCarrega)->Desenha();
    }
    //if (id==TELA_JOGO)
    //    printf("estado %d\n",estado);
    if ((estado==PIG_TELA_CARREGADA||estado==PIG_TELA_SAINDO)&&comportamento.acaoDesenha!=NULL)
        return comportamento.acaoDesenha(id,comportamento.dados);
    return 0;
}

void SetComportamento(PIGComportamentoTela comporta){
    comportamento = comporta;
}

};

typedef CPIGTela *PIGTela;
#endif // _CPIGTELA_
