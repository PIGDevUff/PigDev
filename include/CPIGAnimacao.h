#ifndef _CPIGANIMACAO_
#define _CPIGANIMACAO_

#include "CPIGModoAnimacao.h"

class CPIGAnimacao:public CPIGObjeto{

private:

PIGModoAnimacao modos[PIG_MAX_MODOS];  //modos da anima��o
int idTimer;                    //timer da anima��o (se estiver sendo utilizado o gerenciador de timers)
SDL_Point offset;                  //offset (x,y) a ser utilizado junto com a posi��o (x,y) para desenhar oa anima��o
int modoAtual;                  //n�mero que indica o modo atual

//muda o frame a ser exibido do modo atual
void AtualizaFrameAtual(PIGModoAnimacao modo){
    CPIGSprite::MudaFrameAtual(modo->GetFrameAtual());

    int a,l;
    modo->GetDimensoesAtual(a,l);
    SetDimensoes(a,l);

    int audio = modo->GetAudioAtual();
    if (audio>=0){
        CPIGGerenciadorAudios::Play(audio);
    }

    CPIGGerenciadorTimers::GetTimer(idTimer)->Reinicia(false);
}

public:

//cria uma anima��o a partir de um arquivo de spritesheet
CPIGAnimacao(int idAnimacao,std::string nomeArq,int retiraFundo=1,PIG_Cor *corFundo=NULL,int idJanela=0)
:CPIGObjeto(idAnimacao,nomeArq,retiraFundo,corFundo,idJanela){
    offset= {0,0};
    modoAtual = 0;

    for (int i=0;i<PIG_MAX_MODOS;i++)
        modos[i] = NULL;

    idTimer = CPIGGerenciadorTimers::CriaTimer();
}

//cria uma anima��o a partir deoutra anima��o j� existente
CPIGAnimacao(int idAnimacao,CPIGAnimacao* base,int retiraFundo=1,PIG_Cor *corFundo=NULL,int idJanela=0)
:CPIGObjeto(idAnimacao,(PIGObjeto)base,retiraFundo,corFundo,idJanela){
    for (int i=0;i<PIG_MAX_MODOS;i++){
        if (base->modos[i])
            modos[i] = new CPIGModoAnimacao(base->modos[i]);
        else modos[i]=NULL;
    }

    offset = base->offset;
    modoAtual = base->modoAtual;

    idTimer = CPIGGerenciadorTimers::CriaTimer();
}

//cria uma anima��o a partir de um objeto
CPIGAnimacao(int idAnimacao,PIGObjeto base,int retiraFundo=1,PIG_Cor *corFundo=NULL,int idJanela=0)
:CPIGObjeto(idAnimacao,base,retiraFundo,corFundo,idJanela){
    offset = {0,0};
    modoAtual = 0;

    for (int i=0;i<PIG_MAX_MODOS;i++){
        modos[i] = NULL;
    }

    idTimer = CPIGGerenciadorTimers::CriaTimer();
}

//destroi uma anima��o
~CPIGAnimacao(){
    for (int i=0;i<PIG_MAX_MODOS;i++){
        if (modos[i])
            delete modos[i];
    }

    CPIGGerenciadorTimers::DestroiTimer(idTimer);
}

//cria um modo vazio, sem frames associados
void CriaModo(int idModo, int loop){
    if (modos[idModo]) delete modos[idModo];
    modos[idModo] = new CPIGModoAnimacao(loop);
}

//insere um frame em um dos modos
void InsereFrame(int idModo, int idFrame, float delayFrame, int audio, int alturaFrame=-1, int larguraFrame=-1){
    if (alturaFrame==-1)
        alturaFrame = alt;
    if (larguraFrame==-1)
        larguraFrame = larg;
    modos[idModo]->InsereEstagio(idFrame,delayFrame,audio,alturaFrame,larguraFrame);
}

//muda o modo atual
void MudaModo(int idModo,int indiceFrame=0,int forcado=1){
    if (forcado||(modos[modoAtual]&&modos[modoAtual]->GetEncerrou())){
        modoAtual = idModo;

        modos[modoAtual]->SetIndiceFrameAtual(indiceFrame);

        AtualizaFrameAtual(modos[modoAtual]);
    }
}

//retorna o n�merodo modo atual
int GetModoAtual(){
    return modoAtual;
}

//desenha a anima��o
int Desenha()override{
    int resp=0; //0 indica que que o modo de anima��o atual n�o encerrou
    //printf("comecando\n");
    if (modos[modoAtual]!=NULL){
        float tempoDecorrido;
        //printf("calculando %d\n",idTimer);
        tempoDecorrido = CPIGGerenciadorTimers::GetTimer(idTimer)->GetTempoDecorrido();

        if (modos[modoAtual]->TestaTempo(tempoDecorrido)){
            //printf("mudando frame (%d)\n",modoAtual);
            AtualizaFrameAtual(modos[modoAtual]);
        }else resp = modos[modoAtual]->GetEncerrou();//pode ter encerrado de desenhar todos os est�gios do modo
    }

    int px = pos.x+offset.x;
    int py = pos.y+offset.y;

    CPIGObjeto::Move(px,py);
    CPIGObjeto::Desenha();

    px -= offset.x;
    py -= offset.y;

    CPIGObjeto::Move(px,py);

    return resp;
}

//pausa a anima��o
void Pausa(){
    CPIGGerenciadorTimers::GetTimer(idTimer)->Pausa();
}

//despausa a anima��o
void Despausa(){
    CPIGGerenciadorTimers::GetTimer(idTimer)->Despausa();
}

//define o tempo de um frame j� criado
void SetTempoFrame(int modo, int indiceFrame, double tempo){
    modos[modo]->SetTempo(indiceFrame,tempo);
}

//define se um modo j� criado ter� ou n�o loop
void SetLoopModo(int modo, int loop){
    modos[modo]->SetLoop(loop);
}

//define o audio de um frame j� criado
void SetAudioFrame(int modo, int indiceFrame, int idAudio){
    modos[modo]->SetAudio(indiceFrame,idAudio);
}

//retorna o tempo de dura��o de um frame j� criado
double GetTempoFrame(int modo, int indiceFrame){
    return modos[modo]->GetTempoFrame(indiceFrame);
}

//retorna se um modo tem ou n�o loop
bool GetLoopModo(int modo){
    return modos[modo]->GetLoop();
}

//retorna o audio de um frame j� criado
int GetAudioFrame(int modo, int indiceFrame){
    return modos[modo]->GetAudioFrame(indiceFrame);
}

};

typedef CPIGAnimacao* PIGAnimacao;
#endif // _CPIGANIMACAO_
