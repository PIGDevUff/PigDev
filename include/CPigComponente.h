typedef enum {COMPONENTE_NORMAL,COMPONENTE_MOUSEOVER,COMPONENTE_ACIONADO,COMPONENTE_DESABILITADO,COMPONENTE_EDITANDO,COMPONENTE_INVISIVEL} PIG_EstadoComponente;
typedef enum {COMPONENTE_CIMA,COMPONENTE_CIMADIR,COMPONENTE_DIREITA,COMPONENTE_BAIXODIR,COMPONENTE_BAIXO,COMPONENTE_BAIXOESQ,COMPONENTE_ESQUERDA,COMPONENTE_CIMAESQ,COMPONENTE_CENTRO,COMPONENTE_POSICAO_PERSONALIZADA} PIG_PosicaoComponente;
class CPigComponente: public CVisual{

protected:

PIG_EstadoComponente estado;
char *hint,*label;
int fonteHint,fonteLabel;
int audioComponente;
int antesOn,agoraOn;
int id;
int labelX,labelY;
PIG_PosicaoComponente posLabel;

virtual int OnMouseOn()=0;
virtual int OnMouseOff()=0;

void IniciaBase(int idComponente, int px, int py){
    id = idComponente;
    hint = NULL;
    label = NULL;
    fonteHint = fonteLabel = 0;
    audioComponente = -1;
    estado = COMPONENTE_NORMAL;
    x = px;
    y = py;
    agoraOn = antesOn = 0;
}

//verifica se uma string possui apenas digitos de 0 a 9
bool SomenteNumeros(char *frase){
    for (int i=0;i<strlen(frase);i++)
        if (frase[i]<'0'||frase[i]>'9')
            return false;
    return true;
}

//escreve o hint do componente na tela
void EscreveHint(){
    if (agoraOn&&hint){
        int mx,my;
        CMouse::PegaXY(mx,my);
        jogo->EscreverEsquerda(hint,mx+16,my+5,fonteHint);
    }
}

//detecta se o mouse está sobre o componente ou não
int MouseSobre(int mx, int my){
    if (estado==COMPONENTE_INVISIVEL)
        return 0;

    SDL_Point p={mx,my};
    SDL_Rect r={x,y,larg,alt};

    antesOn = agoraOn;
    agoraOn = SDL_PointInRect(&p,&r);
    if (agoraOn&&!antesOn){
        OnMouseOn();
        return 1;
    }else if(!agoraOn&&antesOn){
        OnMouseOff();
        return -1;
    }
    return 0;
}

//desenha o label
void DesenhaLabel(){
    if (label!=NULL && strcmp(label,"")) {
        switch(posLabel){
        case COMPONENTE_CIMA:
            EscreverCentralizada(label,x+larg/2,y+alt+5,fonteLabel);
            break;
        case COMPONENTE_CIMADIR:
            EscreverDireita(label,x+larg,y+alt+5,fonteLabel);
            break;
        case COMPONENTE_CIMAESQ:
            EscreverEsquerda(label,x,y+alt+5,fonteLabel);
            break;
        case COMPONENTE_BAIXO:
            EscreverCentralizada(label,x+larg/2,y-30,fonteLabel);
            break;
        case COMPONENTE_BAIXODIR:
            EscreverDireita(label,x+larg,y-30,fonteLabel);
            break;
        case COMPONENTE_BAIXOESQ:
            EscreverEsquerda(label,x,y-30,fonteLabel);
            break;
        case COMPONENTE_ESQUERDA:
            EscreverDireita(label,x-5,y,fonteLabel);
            break;
        case COMPONENTE_DIREITA:
            EscreverEsquerda(label,x+larg+5,y,fonteLabel);
            break;
        case COMPONENTE_CENTRO:
            EscreverCentralizada(label,x+larg/2,y+(alt-20)/2,fonteLabel);
            break;
        case COMPONENTE_POSICAO_PERSONALIZADA:
            EscreverEsquerda(label,x+labelX,y+labelY,fonteLabel);
        }
    }
}

public:

//construtor temporário (apenas para compilação funcionar neste momento) - remover depois


CPigComponente(int idComponente,int px,int py, int altura, int largura, int janela=0):CVisual(altura, largura, "",janela){
    IniciaBase(idComponente,px,py);
}

CPigComponente(int idComponente,int px,int py, int altura, int largura, char *nomeArq,int retiraFundo=1,int janela=0):CVisual(nomeArq,retiraFundo,NULL,janela){
    IniciaBase(idComponente,px,py);
    CVisual::SetDimensoes(altura,largura);
}

~CPigComponente(){
    if (hint)
        free(hint);
    if (label)
        free(label);
}

//recupera o id do componente
int GetId(){
    return id;
}

//desenha o componente, cada subclasse precisa implementar como fazer isso
virtual int Desenha()=0;

//trata um evento direcionado ao componente, cada subclasse precisa implementar como fazer isso
virtual int TrataEvento(PIG_Evento evento)=0;

//define a mensagem de hint do componente
void SetHint(char *mensagem){
    if (hint)
        free(hint);
    if (mensagem){
        hint = (char*) malloc(strlen(mensagem));
        strcpy(hint,mensagem);
    }
}

//define o label do componente
void SetLabel(char *novoLabel){
    if (label)
        free(label);
    if (novoLabel){
        label = (char*) malloc(strlen(novoLabel));
        strcpy(label,novoLabel);
    }
}

//define o audio padrão do componente
virtual void SetAudio(int idAudio){
    audioComponente = idAudio;
}

//define a fonte do hint
virtual void SetFonteHint(int fonte){
    fonteHint = fonte;
}

//define a fonte do label
void SetFonteLabel(int fonte){
    fonteLabel = fonte;
}

//define a posição do label (dentre posições pré-estabelecidas)
virtual int SetPosicaoPadraoLabel(PIG_PosicaoComponente pos){
    posLabel = pos;
    return 1;
}

//define a posição do label (posição arbiraria, relativa à posição do componente)
virtual int SetPosicaoPersonalizadaLabel(int rx, int ry){
    labelX = rx;
    labelY = ry;
    return 1;
}

//define o estado do componente, cada subclasse precisa definir como implementar isso
virtual void DefineEstado(PIG_EstadoComponente estadoComponente)=0;

//recupera o estado do componente
PIG_EstadoComponente GetEstado(){
    return estado;
}

};


typedef CPigComponente *PigComponente;
