class CAnimacao:public CObjeto{

typedef struct {
    int loop;
    int qtdFrames;
    int frames[MAX_FRAMES_MODO];
    int audio[MAX_FRAMES_MODO];
    float delays[MAX_FRAMES_MODO];
}Modo;

private:

int souCopia;
int qtdTotalFrames;
Modo *modos[MAX_MODOS];
int frameDoModo;
SDL_Rect *frames[MAX_FRAMES];
Timer tempoFrame;
int idTimer;
int offx,offy;
int modoAtual;
int frameAtual;

public:

CAnimacao(char *nomeArq,int usaGerenciadorTimer=0,PIG_Cor *corFundo=NULL,int retiraFundo=1,int idJanela=0):CObjeto(nomeArq,corFundo,retiraFundo,idJanela){
    souCopia = 0;
    offx = offy = 0;
    modoAtual = 0;
    frameDoModo=-1;
    //printf("retirado\n");

    for (int i=0;i<MAX_FRAMES;i++)
        frames[i] = (SDL_Rect*)malloc(sizeof(SDL_Rect));

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

CAnimacao(CAnimacao* base,int usaGerenciadorTimer=0,PIG_Cor *corFundo=NULL,int retiraFundo=1,int idJanela=0):CObjeto(base->nomeArquivo,corFundo,retiraFundo,idJanela){
    souCopia= 1;
    frameDoModo=-1;

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

CAnimacao(Objeto base,int usaGerenciadorTimer=0,PIG_Cor *corFundo=NULL,int retiraFundo=1,int idJanela=0):CObjeto(base,corFundo,retiraFundo,idJanela){
    offx = offy = 0;
    modoAtual = 0;
    frameDoModo=-1;

    for (int i=0;i<MAX_FRAMES;i++){
        frames[i] = NULL;
    }

    for (int i=0;i<MAX_MODOS;i++){
        modos[i] = NULL;
    }

    idTimer = -1;
    tempoFrame = NULL;
}

~CAnimacao(){
    if (!souCopia){
        for (int i=0;i<MAX_MODOS;i++){
            if (modos[i])
                free(modos[i]);
        }
        for (int i=0;i<MAX_FRAMES;i++)
            free(frames[i]);
    }

    if (tempoFrame)
        delete tempoFrame;
    else if (idTimer!=-1)
        CGerenciadorTimers::DestroiTimer(idTimer);
}

//define o retangulo da imagem que corresponde ao frame
void CriaFrame(int codFrame,int x,int y,int altura,int largura){
    frames[codFrame]->x = x;
    frames[codFrame]->y = y;
    frames[codFrame]->h = altura;
    frames[codFrame]->w = largura;
}

//cria um modo vazio, sem frames associados
void CriaModo(int idModo, int loop){
    if (modos[idModo]) free(modos[idModo]);
    modos[idModo] = (Modo*) malloc(sizeof(Modo));
    Modo *atual = modos[idModo];
    atual->loop = loop;
    atual->qtdFrames = 0;
}

//insere um frame em um dos modos
void InsereFrame(int idModo, int idFrame, float delayFrame,int audio){
    int aux = modos[idModo]->qtdFrames;
    modos[idModo]->frames[ aux ] = idFrame;
    modos[idModo]->delays[ aux ] = delayFrame;
    modos[idModo]->audio[ aux ] = audio;
    //printf("inserido %d na posicao %d\n",audio,aux);
    modos[idModo]->qtdFrames++;
}

//muda o modo atual
void MudaModo(int idModo,int inicia){
    modoAtual = idModo;

    if (inicia){
        frameDoModo = 0;
        int audio = modos[modoAtual]->audio[frameDoModo];
        if (audio>=0){
            //printf("vou tocar %d\n",audio);
            CGerenciadorAudios::Play(audio);
        }
        frameAtual = modos[modoAtual]->frames[frameDoModo];
        CObjeto::DefineFrame(*(frames[frameAtual]));
    }
    else frameDoModo = modos[idModo]->qtdFrames-1;

    if (tempoFrame)
        tempoFrame->Reinicia(false);
    else CGerenciadorTimers::ReiniciaTimer(idTimer);
}

//desenha a animação
int Desenha(){
    int resp=0; //0 indica que que o modo de animação atual não terminou
    Modo *modo = modos[modoAtual];

    if (modo!=NULL){

        float tempo = modo->delays[frameDoModo];
        float tempoDecorrido;

        if (tempoFrame)
            tempoDecorrido = tempoFrame->GetTempoDecorrido();
        else tempoDecorrido = CGerenciadorTimers::GetTempoDecorrido(idTimer);

        if (tempoDecorrido>tempo){//já passou o tempo de exibição do frame atual
            if (frameDoModo==modo->qtdFrames-1){//se estamos no último frame do modo
                if (modo->loop){//se deve voltar ao primeiro frame
                    frameDoModo=0;
                }else resp=1;//indica que acabou a exibição dos frames deste modo
            }else{//se devemos passar para o próximo frame
                frameDoModo++;
                int audio = modo->audio[frameDoModo];
                //printf("audio seria %d (frame %d)\n",audio,frameDoModo);
                if (audio>=0){//se devemos tocar algum audio para este frame neste modo
                    //printf("desenha audio %d\n",audio);
                    CGerenciadorAudios::Play(audio);
                }
            }

            if (tempoFrame)
                tempoFrame->Reinicia(false);
            else CGerenciadorTimers::ReiniciaTimer(idTimer);

            frameAtual = modo->frames[frameDoModo];
            CObjeto::DefineFrame(*(frames[frameAtual]));
        }

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

};


typedef CAnimacao* Animacao;
