typedef enum {COMPONENTE_NORMAL,COMPONENTE_MOUSEOVER,COMPONENTE_ACIONADO,COMPONENTE_DESABILITADO,COMPONENTE_EDITANDO,COMPONENTE_INVISIVEL} PIG_EstadoComponente;
typedef enum{PIG_COMPONENTE_CIMA_CENTRO,PIG_COMPONENTE_CIMA_ESQ,PIG_COMPONENTE_CIMA_DIR,PIG_COMPONENTE_BAIXO_CENTRO,PIG_COMPONENTE_BAIXO_DIR,PIG_COMPONENTE_BAIXO_ESQ,PIG_COMPONENTE_DIR_CIMA,PIG_COMPONENTE_DIR_BAIXO,PIG_COMPONENTE_DIR_CENTRO,PIG_COMPONENTE_ESQ_BAIXO,PIG_COMPONENTE_ESQ_CENTRO,PIG_COMPONENTE_ESQ_CIMA,PIG_COMPONENTE_CENTRO_CENTRO,PIG_COMPONENTE_PERSONALIZADA}PIG_PosicaoComponente;
class CPigComponente: public CVisual{

protected:

PIG_EstadoComponente estado;
std::string hint,label;
int fonteHint,fonteLabel;
int audioComponente;
int antesOn,agoraOn;
int id;
int labelX,labelY;
int altLetraLabel;
PIG_PosicaoComponente posLabel;

virtual int OnMouseOn()=0;
virtual int OnMouseOff()=0;

void IniciaBase(int idComponente, int px, int py){
    id = idComponente;
    hint = label = "";
    SetFonteHint(0);
    SetFonteLabel(0);
    audioComponente = -1;
    estado = COMPONENTE_NORMAL;
    x = px;
    y = py;
    agoraOn = antesOn = 0;
}

//verifica se uma string possui apenas digitos de 0 a 9
bool SomenteNumeros(std::string frase){
    for (int i=0;i<frase.size();i++)
        if (frase[i]<'0'||frase[i]>'9')
            return false;
    return true;
}

//escreve o hint do componente na tela
void EscreveHint(){
    if (agoraOn&&hint!=""){
        int mx,my;
        CMouse::PegaXY(mx,my);
        CGerenciadorFontes::EscreverString(hint,mx+16,my+5,fonteHint);
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
    //printf("vai <%s> %d\n",label.c_str(),fonteLabel);
    if (label!="") {
        switch(posLabel){
        case PIG_COMPONENTE_CIMA_CENTRO:
            CGerenciadorFontes::EscreverString(label,x+larg/2,y+alt+5,fonteLabel,CPIG_TEXTO_CENTRO);
            break;
        case PIG_COMPONENTE_CIMA_DIR:
            CGerenciadorFontes::EscreverString(label,x+larg,y+alt+5,fonteLabel,CPIG_TEXTO_DIREITA);
            break;
        case PIG_COMPONENTE_CIMA_ESQ:
            CGerenciadorFontes::EscreverString(label,x,y+alt+5,fonteLabel,CPIG_TEXTO_ESQUERDA);
            break;
        case PIG_COMPONENTE_BAIXO_CENTRO:
            CGerenciadorFontes::EscreverString(label,x+larg/2,y-altLetraLabel,fonteLabel,CPIG_TEXTO_CENTRO);
            break;
        case PIG_COMPONENTE_BAIXO_DIR:
            CGerenciadorFontes::EscreverString(label,x+larg,y-altLetraLabel,fonteLabel,CPIG_TEXTO_DIREITA);
            break;
        case PIG_COMPONENTE_BAIXO_ESQ:
            CGerenciadorFontes::EscreverString(label,x,y-altLetraLabel,fonteLabel,CPIG_TEXTO_ESQUERDA);
            break;
        case PIG_COMPONENTE_ESQ_BAIXO:
            CGerenciadorFontes::EscreverString(label,x-5,y,fonteLabel,CPIG_TEXTO_DIREITA);
            break;
        case PIG_COMPONENTE_ESQ_CENTRO:
            CGerenciadorFontes::EscreverString(label,x-5,y+(alt-altLetraLabel)/2,fonteLabel,CPIG_TEXTO_DIREITA);
            break;
        case PIG_COMPONENTE_ESQ_CIMA:
            CGerenciadorFontes::EscreverString(label,x-5,y + (alt-altLetraLabel),fonteLabel,CPIG_TEXTO_ESQUERDA);
            break;
        case PIG_COMPONENTE_DIR_BAIXO:
            CGerenciadorFontes::EscreverString(label,x+larg+5,y,fonteLabel,CPIG_TEXTO_ESQUERDA);
            break;
        case PIG_COMPONENTE_DIR_CENTRO:
            CGerenciadorFontes::EscreverString(label,x+larg+5,y + (alt-altLetraLabel)/2,fonteLabel,CPIG_TEXTO_ESQUERDA);
            break;
        case PIG_COMPONENTE_DIR_CIMA:
            CGerenciadorFontes::EscreverString(label,x+larg+5,y + (alt-altLetraLabel),fonteLabel,CPIG_TEXTO_ESQUERDA);
            break;
        case PIG_COMPONENTE_CENTRO_CENTRO:
            CGerenciadorFontes::EscreverString(label,x+larg/2,y+(alt-altLetraLabel)/2,fonteLabel,CPIG_TEXTO_CENTRO);
            break;
        case PIG_COMPONENTE_PERSONALIZADA:
            CGerenciadorFontes::EscreverString(label,labelX,labelY,fonteLabel,CPIG_TEXTO_ESQUERDA);
        }
    }
}

public:

//construtor temporário (apenas para compilação funcionar neste momento) - remover depois


CPigComponente(int idComponente,int px,int py, int altura, int largura, int janela=0):CVisual(altura, largura, "",janela){
    IniciaBase(idComponente,px,py);
}

CPigComponente(int idComponente,int px,int py, int altura, int largura, std::string nomeArq,int retiraFundo=1,int janela=0):CVisual(nomeArq,retiraFundo,NULL,janela){
    IniciaBase(idComponente,px,py);
    CVisual::SetDimensoes(altura,largura);
}

~CPigComponente(){
    hint.clear();
    label.clear();
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
void SetHint(std::string novoHint){
    hint = novoHint;
}

//define o label do componente
void SetLabel(std::string novoLabel){
    label = novoLabel;
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
virtual void SetFonteLabel(int fonte){
    fonteLabel = fonte;
    altLetraLabel = CGerenciadorFontes::GetTamanhoBaseFonte(fonteLabel)+CGerenciadorFontes::GetFonteDescent(fonteLabel);
}

//recupera o label
std::string GetLabel(){
    return label;
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
    posLabel = PIG_COMPONENTE_PERSONALIZADA;//evitar que o usuário esqueça de chamar também a SetPosicaoPadraoLabel
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
