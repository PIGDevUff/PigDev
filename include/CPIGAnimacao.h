#ifndef _CPIGANIMACAO_
#define _CPIGANIMACAO_

#include "CPIGModoAnimacao.h"

class CPIGAnimacao:public CPIGObjeto{

private:

    PIGModoAnimacao modos[PIG_MAX_MODOS];   //modos da animação
    SDL_Point offset;                       //offset (x,y) a ser utilizado junto com a posição (x,y) para desenhar oa animação
    int idTimer;                            //timer para controle dos frames da animação (usado apenas na contrução e destruição de um objeto)
    PIGTimer timer;                          //ponteiro para o timer indicado por idTimer (usado diretamente para otimizar a execução dos códigos)
    int modoAtual;                          //número que indica o modo atual

    //muda o frame a ser exibido do modo atual
    void AtualizaFrameAtual(PIGModoAnimacao modo){
        frameAtual = modo->GetFrameAtual();
        CPIGSprite::MudaFrameAtual(frameAtual);

        int a,l;
        modo->GetDimensoesAtual(a,l);
        SetDimensoes(a,l);

        #ifdef PIGCOMAUDIO
        int audio = modo->GetAudioAtual();
        if (audio>=0){
            pigGerAudios.Play(audio);
        }
        #endif

        timer->Reinicia(false);
    }

public:

    //cria uma animação a partir de um arquivo de spritesheet
    CPIGAnimacao(int idAnimacao, string nomeArq, int retiraFundo=1, PIGCor *corFundo=NULL, int idJanela=0)
    :CPIGObjeto(idAnimacao,nomeArq,retiraFundo,corFundo,idJanela){
        offset= {0,0};
        modoAtual = 0;

        for (int i=0;i<PIG_MAX_MODOS;i++)
            modos[i] = NULL;

        idTimer = pigGerTimers.CriaTimer(false);
        timer = pigGerTimers.GetElemento(idTimer);
    }

    //cria uma animação a partir deoutra animação já existente
    CPIGAnimacao(int idAnimacao, CPIGAnimacao* base, int retiraFundo=1, PIGCor *corFundo=NULL,int idJanela=0)
    :CPIGObjeto(idAnimacao,(PIGObjeto)base,retiraFundo,corFundo,idJanela){
        for (int i=0;i<PIG_MAX_MODOS;i++){
            if (base->modos[i])
                modos[i] = new CPIGModoAnimacao(base->modos[i]);
            else modos[i] = NULL;
        }

        offset = base->offset;
        modoAtual = base->modoAtual;

        idTimer = pigGerTimers.CriaTimer(false);
        timer = pigGerTimers.GetElemento(idTimer);
    }

    //cria uma animação a partir de um objeto
    CPIGAnimacao(int idAnimacao, PIGObjeto base, int retiraFundo=1, PIGCor *corFundo=NULL, int idJanela=0)
    :CPIGObjeto(idAnimacao,base,retiraFundo,corFundo,idJanela){
        offset = {0,0};
        modoAtual = 0;

        for (int i=0;i<PIG_MAX_MODOS;i++){
            modos[i] = NULL;
        }

        idTimer = pigGerTimers.CriaTimer(false);
        timer = pigGerTimers.GetElemento(idTimer);
    }

    //destroi uma animação
    virtual ~CPIGAnimacao(){
        for (int i=0;i<PIG_MAX_MODOS;i++){
            if (modos[i])
                delete modos[i];
        }
        timer = NULL;
        pigGerTimers.Remove(idTimer);
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
    void MudaModo(int idModo, int indiceFrame=0, int forcado=1){
        if (forcado||(modos[modoAtual]&&modos[modoAtual]->GetEncerrou())){
            modoAtual = idModo;

            modos[modoAtual]->SetIndiceFrameAtual(indiceFrame);

            AtualizaFrameAtual(modos[modoAtual]);
        }
    }

    //retorna o númerodo modo atual
    inline int GetModoAtual(){
        return modoAtual;
    }

    virtual void Pausa(){
        timer->Pausa();
    }

    virtual void Despausa(){
        timer->Despausa();
    }

    virtual void Reinicia(bool congelado=false){
        timer->Reinicia(congelado);
    }

    //desenha a animação
    int Desenha()override{
        int resp=0; //0 indica que que o modo de animação atual não encerrou

        if (modos[modoAtual]!=NULL){
            float tempoDecorrido = timer->GetTempoDecorrido();//tempo da própria animação (herdado de CPIGTimer)

            if (modos[modoAtual]->TestaTempo(tempoDecorrido)){
                AtualizaFrameAtual(modos[modoAtual]);
            }else resp = modos[modoAtual]->GetEncerrou();//pode ter encerrado de desenhar todos os estágios do modo
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

    //define o tempo de um frame já criado
    inline void SetTempoFrame(int modo, int indiceFrame, double tempo){
        modos[modo]->SetTempo(indiceFrame,tempo);
    }

    //define se um modo já criado terá ou não loop
    inline void SetLoopModo(int modo, int loop){
        modos[modo]->SetLoop(loop);
    }

    //define o audio de um frame já criado
    inline void SetAudioFrame(int modo, int indiceFrame, int idAudio){
        modos[modo]->SetAudio(indiceFrame,idAudio);
    }

    //retorna o tempo de duração de um frame já criado
    inline double GetTempoFrame(int modo, int indiceFrame){
        return modos[modo]->GetTempoFrame(indiceFrame);
    }

    //retorna se um modo tem ou não loop
    inline bool GetLoopModo(int modo){
        return modos[modo]->GetLoop();
    }

    //retorna o audio de um frame já criado
    inline int GetAudioFrame(int modo, int indiceFrame){
        return modos[modo]->GetAudioFrame(indiceFrame);
    }

};
typedef CPIGAnimacao* PIGAnimacao;
#endif // _CPIGANIMACAO_
