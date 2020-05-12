class CPigItemCheck:public CPigComponente{

private:

    Timer timer;
    int largFrame;
    bool marcado;

    int TrataMouse(int acao){
        SDL_Point p;
        CMouse::PegaXY(p.x,p.y);
        MouseSobre(p.x,p.y);

        if (acao==MOUSE_PRESSIONADO){
            if (agoraOn){
                return OnMouseClick();
            }
        }
        return 0;
    }

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
        if (audioComponente>=0) PlayAudio(audioComponente);
        DefineEstado(COMPONENTE_MOUSEOVER);
        return 1;
    }

public:

    CPigItemCheck(int idComponente,int px, int py, int alt,int larg,char *nomeArq,char *labelItem,int retiraFundo=1,int janela=0):
        CPigComponente(idComponente,px,py,alt,larg,nomeArq,janela){
        timer = NULL;
        largFrame = largOriginal/6;
        marcado = false;
        posLabel = COMPONENTE_DIREITA;
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


    int TrataEvento(PIG_Evento evento){
        if (estado==COMPONENTE_DESABILITADO||estado==COMPONENTE_INVISIVEL)
            return -1;
        if (evento.tipoEvento==EVENTO_MOUSE){
            return TrataMouse(evento.mouse.acao);
        }else if (evento.tipoEvento==EVENTO_TECLADO){
            return 0;//TrataTeclado(evento);
        }

        return 0;
    }

    int Desenha(){
        SDL_RenderCopyEx(renderer,text,&frame,&dest,-angulo,NULL,flip);
        DesenhaLabel();
        EscreveHint();
    }

    void AlinhaDireita(int largTotal){
        Move(x+largTotal-larg,y);
        SetPosicaoPadraoLabel(COMPONENTE_ESQUERDA);
    }

    void AlinhaEsquerda(int largTotal){
        Move(x-largTotal+larg,y);
        SetPosicaoPadraoLabel(COMPONENTE_DIREITA);
    }

    //define a posição do label (dentre posições pré-estabelecidas)
    int SetPosicaoPadraoLabel(PIG_PosicaoComponente pos) override{
        if (pos!=COMPONENTE_ESQUERDA)
            pos = COMPONENTE_DIREITA;
        CPigComponente::SetPosicaoPadraoLabel(pos);
        return 0;
    }

    //define a posição do label (posição arbiraria, relativa à posição do componente)
    int SetPosicaoPersonalizadaLabel(int rx, int ry) override{
        return 0;
    }

};

typedef CPigItemCheck *PigItemCheck;
