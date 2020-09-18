typedef enum{COMPONENTE_NORMAL,COMPONENTE_MOUSEOVER,COMPONENTE_ACIONADO,COMPONENTE_DESABILITADO} PIG_EstadoComponente;
typedef enum{PIG_COMPONENTE_CIMA_CENTRO,PIG_COMPONENTE_CIMA_ESQ,PIG_COMPONENTE_CIMA_DIR,PIG_COMPONENTE_BAIXO_CENTRO,PIG_COMPONENTE_BAIXO_DIR,PIG_COMPONENTE_BAIXO_ESQ,PIG_COMPONENTE_DIR_CIMA,PIG_COMPONENTE_DIR_BAIXO,PIG_COMPONENTE_DIR_CENTRO,PIG_COMPONENTE_ESQ_BAIXO,PIG_COMPONENTE_ESQ_CENTRO,PIG_COMPONENTE_ESQ_CIMA,PIG_COMPONENTE_CENTRO_CENTRO,PIG_COMPONENTE_PERSONALIZADA}PIG_PosicaoComponente;
typedef enum{NORTE,SUL,LESTE,OESTE,NORDESTE,NOROESTE,SUDESTE,SUDOESTE,CENTRO}PIG_Ancora;
typedef enum{NAO_SELECIONADO,SELECIONADO_INVISIVEL,SELECIONADO_DESABILITADO,SELECIONADO_TRATADO}Pig_EstadosEventos;

class CPigComponente: public CVisual{

protected:

    bool temFoco,visivel,habilitado,mouseOver,acionado;
    PIG_EstadoComponente estado;
    std::string hint,label;
    int fonteHint,fonteLabel;
    int audioComponente;
    int antesOn,agoraOn;
    int id;
    int labelX,labelY;
    int altLetraLabel;
    PIG_PosicaoComponente posLabel,posComponente;

    virtual int OnMouseOn()=0;
    virtual int OnMouseOff()=0;

    void IniciaBase(int idComponente, int px, int py){
        id = idComponente;
        hint = label = "";
        SetFonteHint(0);
        SetFonteLabel(0);
        audioComponente = -1;
        estado = COMPONENTE_NORMAL;
        posLabel = PIG_COMPONENTE_CENTRO_CENTRO;
        x = px;
        y = py;
        agoraOn = antesOn = 0;
        temFoco = false;
        visivel = true;
        habilitado = true;
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
        if (visivel==false||habilitado==false)
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
                break;
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

    virtual int TrataEventoMouse(PIG_Evento evento){return NAO_SELECIONADO;}
    virtual int TrataEventoTeclado(PIG_Evento evento){return NAO_SELECIONADO;}

    //define a mensagem de hint do componente
    void SetHint(std::string novoHint){
        hint = novoHint;
    }

    //define o label do componente
    void SetLabel(std::string novoLabel){
        label = novoLabel;
    }

    //define o audio padrão do componentePIG_COMPONENTE_CENTRO_CENTRO
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

    /*virtual void GanhaFoco(){
        temFoco = true;
    }

    virtual void PerdeFoco(){
        temFoco = false;
    }

    virtual void SetVisivel(){
        visivel = true;
    }

    virtual void SetInvisivel(){
        visivel = false;
    }

    virtual void SetHabilitado(){
        habilitado = true;
    }

    virtual void SetHabilitado(){
        habilitado = true;
    }*/

    virtual void SetFoco(bool valor){
        temFoco = valor;
    }

    virtual void SetVisivel(bool valor){
        visivel = valor;
    }

    virtual void SetHabilitado(bool valor){
        habilitado = valor;
    }

    //define o estado do componente, cada subclasse precisa definir como implementar isso
    virtual void DefineEstado(PIG_EstadoComponente estadoComponente)=0;

    //recupera o estado do componente
    PIG_EstadoComponente GetEstado(){
        return estado;
    }

    PIG_PosicaoComponente GetPosComponente(){
        return posComponente;
    }

    void SetPosPadraoExternaComponente(PIG_PosicaoComponente pos,CPigComponente *componenteAssociado){
        int xComponente,yComponente,altComponente,largComponente;
        int largura,altura;

        posComponente = pos;
        componenteAssociado->GetDimensoes(altComponente,largComponente);
        componenteAssociado->GetXY(xComponente,yComponente);
        this->GetDimensoes(altura,largura);

        switch(pos){
        case PIG_COMPONENTE_CIMA_CENTRO:
            Move(xComponente + (largComponente - largura)/2,yComponente+altComponente);
            break;
        case PIG_COMPONENTE_CIMA_ESQ:
            Move(xComponente,yComponente+altComponente);
            break;
        case PIG_COMPONENTE_CIMA_DIR:
            Move(xComponente + largComponente - largura,yComponente+altComponente);
            break;
        case PIG_COMPONENTE_BAIXO_CENTRO:
            Move(xComponente + (largComponente - largura)/2,yComponente - altura);
            break;
        case PIG_COMPONENTE_BAIXO_ESQ:
            Move(xComponente,yComponente - altura);
            break;
        case PIG_COMPONENTE_BAIXO_DIR:
            Move(xComponente + largComponente - largura,yComponente - altura);
            break;
        case PIG_COMPONENTE_DIR_BAIXO:
            Move(xComponente + largComponente,yComponente);
            break;
        case PIG_COMPONENTE_DIR_CENTRO:
            Move(xComponente + largComponente,yComponente + (altComponente - altura)/2);
            break;
        case PIG_COMPONENTE_DIR_CIMA:
            Move(xComponente + largComponente,yComponente + altComponente - altura);
            break;
        case PIG_COMPONENTE_ESQ_BAIXO:
            Move(xComponente - largura,yComponente);
            break;
        case PIG_COMPONENTE_ESQ_CIMA:
            Move(xComponente - largura,yComponente + altComponente - altura);
            break;
        case PIG_COMPONENTE_ESQ_CENTRO:
            Move(xComponente - largura,yComponente + (altComponente - altura)/2);
            break;
        case PIG_COMPONENTE_CENTRO_CENTRO:
            Move(xComponente + (largComponente - largura)/2,yComponente + (altComponente - altura)/2);
            break;
        }

    }

    void SetPosPadraoComponenteNaTela(PIG_Ancora ancora){
        int largTela,altTela;
        int altura,largura;
        largTela = CGerenciadorJanelas::GetLargura(idJanela);
        altTela = CGerenciadorJanelas::GetAltura(idJanela);

        this->GetDimensoes(altura,largura);

        switch(ancora){
        case SUL:
            Move((largTela - largura)/2,0);
            break;
        case SUDOESTE:
            Move(0,0);
            break;
        case SUDESTE:
            Move(largTela - largura,0);
            break;
        case NORTE:
            Move((largTela - largura)/2,altTela - altura);
            break;
        case NOROESTE:
            Move(0,altTela - altura);
            break;
        case NORDESTE:
            Move(largTela - largura,altTela - altura);
            break;
        case CENTRO:
            Move((largTela - largura)/2,(altTela - altura)/2);
            break;
        case OESTE:
            Move(0,(altTela - altura)/2);
            break;
        case LESTE:
            Move(largTela - largura,(altTela - altura)/2);
            break;
        }

    }

};

typedef CPigComponente *PigComponente;
