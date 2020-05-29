#include "CModoAnimacao.h"

class CAnimacao:public CObjeto{

private:

int souCopia;                   //indica se esta animação é cópia (foi criada a partir) de outra animação
int qtdTotalFrames;             //indica o total de frames existentes nesta animação
ModoAnimacao modos[MAX_MODOS];  //modos da animaçãoi
SDL_Rect *frames[MAX_FRAMES];   //frames da animação
Timer tempoFrame;               //timer da animação (se estiver sendo utilizado um timer específico)
int idTimer;                    //timer da animação (se estiver sendo utilizado o gerenciador de timers)
int offx,offy;                  //offset (x,y) a ser utilizado junto com a posição (x,y) para desenhar oa animação
int modoAtual;                  //número que indica o modo atual
int frameAtual;                 //número que indica o frame atual


//muda o frame a ser exibido do modo atual
void AtualizaFrameAtual(ModoAnimacao modo){
    frameAtual = modo->GetFrameAtual();
    CObjeto::DefineFrame(*(frames[frameAtual]));

    int audio = modo->GetAudioAtual();
    if (audio>=0){
        CGerenciadorAudios::Play(audio);
    }

    if (tempoFrame)
        tempoFrame->Reinicia(false);
    else CGerenciadorTimers::ReiniciaTimer(idTimer);
}

public:

//cria uma animação a partir de um arquivo de spritesheet
CAnimacao(std::string nomeArq,int usaGerenciadorTimer=0,PIG_Cor *corFundo=NULL,int retiraFundo=1,int idJanela=0):CObjeto(nomeArq,corFundo,retiraFundo,idJanela){
    souCopia = 0;
    offx = offy = 0;
    modoAtual = 0;

    for (int i=0;i<MAX_FRAMES;i++)
        frames[i] = NULL;

    qtdTotalFrames = 0;
    for (int i=0;i<MAX_MODOS;i++){
        modos[i] = NULL;
    }

    if (usaGerenciadorTimer){
        tempoFrame = NULL;
        idTimer = CGerenciadorTimers::CriaTimer();
    }else{
        tempoFrame = new CTimer(false);
        idTimer = -1;
    }
}

//cria uma animaçãoa partir deoutra animação já existente
CAnimacao(CAnimacao* base,int usaGerenciadorTimer=0,PIG_Cor *corFundo=NULL,int retiraFundo=1,int idJanela=0):CObjeto(base->nomeArquivo,corFundo,retiraFundo,idJanela){
    souCopia= 1;

    qtdTotalFrames = base->qtdTotalFrames;
    for (int i=0;i<MAX_FRAMES;i++){
        frames[i] = base->frames[i];
    }

    for (int i=0;i<MAX_MODOS;i++){
        modos[i] = base->modos[i];
    }
    CObjeto::SetDimensoes(base->alt,base->larg);

    offx = base->offx;
    offy = base->offy;
    modoAtual = base->modoAtual;

    if (usaGerenciadorTimer){
        tempoFrame = NULL;
        idTimer = CGerenciadorTimers::CriaTimer();
    }else{
        tempoFrame = new CTimer(false);
        idTimer = -1;
    }
}

//cria uma animação a aprtir de um objeto
CAnimacao(Objeto base,int usaGerenciadorTimer=0,PIG_Cor *corFundo=NULL,int retiraFundo=1,int idJanela=0):CObjeto(base,corFundo,retiraFundo,idJanela){
    offx = offy = 0;
    modoAtual = 0;

    for (int i=0;i<MAX_FRAMES;i++){
        frames[i] = NULL;
    }

    for (int i=0;i<MAX_MODOS;i++){
        modos[i] = NULL;
    }

    idTimer = -1;
    tempoFrame = NULL;
}

//destroi uma animação
~CAnimacao(){
    if (!souCopia){
        for (int i=0;i<MAX_MODOS;i++){
            if (modos[i])
                delete modos[i];
        }
        for (int i=0;i<MAX_FRAMES;i++)
            if (frames[i])
                free(frames[i]);
    }

    if (tempoFrame)
        delete tempoFrame;
    else if (idTimer!=-1)
        CGerenciadorTimers::DestroiTimer(idTimer);
}

//define o retangulo da imagem que corresponde ao frame
void CriaFrame(int codFrame,int x,int y,int altura,int largura){
    if (frames[codFrame]) free(frames[codFrame]);
    frames[codFrame] = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    frames[codFrame]->x = x;
    frames[codFrame]->y = y;
    frames[codFrame]->h = altura;
    frames[codFrame]->w = largura;
}

//cria um modo vazio, sem frames associados
void CriaModo(int idModo, int loop){
    if (modos[idModo]) delete modos[idModo];
    modos[idModo] = new CModoAnimacao(loop);
}

//insere um frame em um dos modos
void InsereFrame(int idModo, int idFrame, float delayFrame,int audio){
    modos[idModo]->InsereEstagio(idFrame,delayFrame,audio);
}

//muda o modo atual
void MudaModo(int idModo,int indiceFrame=0,int forcado=1){
    if (forcado||(modos[modoAtual]&&modos[modoAtual]->GetEncerrou())){
        modoAtual = idModo;

        modos[modoAtual]->SetIndiceFrameAtual(indiceFrame);

        AtualizaFrameAtual(modos[modoAtual]);
    }
}

//retorna o númerodo modo atual
int GetModoAtual(){
    return modoAtual;
}

//desenha a animação
int Desenha(){
    int resp=0; //0 indica que que o modo de animação atual não encerrou

    if (modos[modoAtual]!=NULL){
        float tempoDecorrido;

        if (tempoFrame)
            tempoDecorrido = tempoFrame->GetTempoDecorrido();
        else tempoDecorrido = CGerenciadorTimers::GetTempoDecorrido(idTimer);

        if (modos[modoAtual]->TestaTempo(tempoDecorrido)){
            AtualizaFrameAtual(modos[modoAtual]);
        }else resp = modos[modoAtual]->GetEncerrou();//pode ter encerrado de desenhar todos os estágios do modo
    }

    int px = x+offx;
    int py = y+offy;

    CObjeto::Move(px,py);
    CObjeto::Desenha(NULL);

    px -=offx;
    py -=offy;

    CObjeto::Move(px,py);

    return resp;
}

//pausa a animação
void Pausa(){
    if (tempoFrame)
        tempoFrame->Pausa();
    else CGerenciadorTimers::PausaTimer(idTimer);
}

//despausa a animação
void Despausa(){
    if (tempoFrame)
        tempoFrame->Despausa();
    else CGerenciadorTimers::DespausaTimer(idTimer);
}

//define o tempo de um frame já criado
void SetTempoFrame(int modo, int indiceFrame, double tempo){
    modos[modo]->SetTempo(indiceFrame,tempo);
}

//define se um modo já criado terá ou não loop
void SetLoopModo(int modo, int loop){
    modos[modo]->SetLoop(loop);
}

//define o audio de um frame já criado
void SetAudioFrame(int modo, int indiceFrame, int idAudio){
    modos[modo]->SetAudio(indiceFrame,idAudio);
}

//retorna o tempo de duração de um frame já criado
double GetTempoFrame(int modo, int indiceFrame){
    return modos[modo]->GetTempoFrame(indiceFrame);
}

//retorna se um modo tem ou não loop
bool GetLoopModo(int modo){
    return modos[modo]->GetLoop();
}

//retorna o audio de um frame já criado
int GetAudioFrame(int modo, int indiceFrame){
    return modos[modo]->GetAudioFrame(indiceFrame);
}

};

typedef CAnimacao* Animacao;
