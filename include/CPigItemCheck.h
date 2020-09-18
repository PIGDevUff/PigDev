class CPigItemCheck:public CPigComponente{

private:

    Timer timer;
    int largFrame;
    bool marcado;

    int OnMouseOn(){
        if (estado==COMPONENTE_DESABILITADO) return 0;
        DefineEstado(COMPONENTE_MOUSEOVER);
        return 1;
    }

    int OnMouseOff(){
        if (estado==COMPONENTE_DESABILITADO) return 0;
        DefineEstado(COMPONENTE_NORMAL);
        return 1;
    }

    int OnMouseClick(){
        if (timer) delete timer;
        timer = new CTimer(false);
        marcado = !marcado;
        if (audioComponente>=0) CGerenciadorAudios::Play(audioComponente);
        DefineEstado(COMPONENTE_MOUSEOVER);
        return SELECIONADO_TRATADO;
    }

public:

    CPigItemCheck(int idComponente,int px, int py, int alt,int larg,std::string nomeArq,std::string labelItem,int retiraFundo=1,int janela=0):
        CPigComponente(idComponente,px,py,alt,larg,nomeArq,retiraFundo,janela){
        timer = NULL;
        largFrame = largOriginal/6;
        marcado = false;
        SetPosicaoPadraoLabel(PIG_COMPONENTE_DIR_CENTRO);
        SetLabel(labelItem);
        DefineEstado(COMPONENTE_NORMAL);
    }

    ~CPigItemCheck(){
        if (timer)
            delete timer;
    }

    bool GetMarcado(){
        return marcado;
    }

    void SetMarcado(bool estadoMarcado){
        marcado = estadoMarcado;
        DefineEstado(estado);
    }

    bool GetHabilitado(){
        if (estado==COMPONENTE_DESABILITADO)
            return false;
        else return true;
    }

    void SetHabilitado(bool estadoHabilitado){
        if (estadoHabilitado)
            DefineEstado(COMPONENTE_NORMAL);
        else DefineEstado(COMPONENTE_DESABILITADO);
    }

    void DefineEstado(PIG_EstadoComponente estadoComponente)override{
        SDL_Rect r = {0,0,largFrame,altOriginal};
        estado = estadoComponente;
        switch(estado){
        case COMPONENTE_NORMAL:
            if (marcado)
                r.x = largFrame;
            break;
        case COMPONENTE_MOUSEOVER:
            if (marcado)
                r.x = 5*largFrame;
            else r.x = 4*largFrame;
            break;
        case COMPONENTE_DESABILITADO:
            if (marcado)
                r.x = 3*largFrame;
            else r.x = 2*largFrame;
            break;
        }
        DefineFrame(r);
    }

    int Desenha(){
        SDL_RenderCopyEx(renderer,text,&frame,&dest,-angulo,NULL,flip);
        DesenhaLabel();
        EscreveHint();
    }

    void AlinhaDireita(int largTotal){
        Move(x+largTotal-larg,y);
        SetPosicaoPadraoLabel(PIG_COMPONENTE_ESQ_CENTRO);
    }

    void AlinhaEsquerda(int largTotal){
        Move(x-largTotal+larg,y);
        SetPosicaoPadraoLabel(PIG_COMPONENTE_DIR_CENTRO);
    }

    //define a posição do label (dentre posições pré-estabelecidas)
    int SetPosicaoPadraoLabel(PIG_PosicaoComponente pos) override{
        if (pos!=PIG_COMPONENTE_ESQ_CENTRO)
            pos = PIG_COMPONENTE_DIR_CENTRO;
        CPigComponente::SetPosicaoPadraoLabel(pos);
        return 0;
    }

    //define a posição do label (posição arbiraria, relativa à posição do componente)
    int SetPosicaoPersonalizadaLabel(int rx, int ry) override{
        return 0;
    }

    int TrataEventoMouse(PIG_Evento evento)override{
        SDL_Point p;
        CMouse::PegaXY(p.x,p.y);
        MouseSobre(p.x,p.y);

        if(agoraOn){
            if (evento.mouse.acao==MOUSE_PRESSIONADO && evento.mouse.botao == MOUSE_ESQUERDO){
                if (habilitado==false) return SELECIONADO_DESABILITADO;
                if (visivel==false) return SELECIONADO_INVISIVEL;
                return OnMouseClick();
            }
        }
        return NAO_SELECIONADO;
    }

};

typedef CPigItemCheck *PigItemCheck;
