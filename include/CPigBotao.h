typedef int (*AcaoBotao)(int,void*);

class CPigBotao: public CPigComponente{

private:

    int tecla;
    int largFrame;
    AcaoBotao acao;
    void *param;
    Timer timer;

    int TrataMouse(int acao){
        SDL_Point p;
        CMouse::PegaXY(p.x,p.y);
        MouseSobre(p.x,p.y);

        if(agoraOn)
            if (acao==MOUSE_PRESSIONADO) return OnMouseClick();

        return 0;
    }

    int TrataTeclado(PIG_Evento evento){
        if (evento.teclado.acao==TECLA_PRESSIONADA)
            if (evento.teclado.tecla==tecla) return OnMouseClick();

        return 0;
    }

    void TrataTimer(){
        if (timer->GetTempoDecorrido()<0.2){
            if(estado!=COMPONENTE_DESABILITADO)
                DefineEstado(COMPONENTE_ACIONADO);
        }else{
            delete timer;
            timer = NULL;
            if (estado==COMPONENTE_ACIONADO){
                if (agoraOn) DefineEstado(COMPONENTE_MOUSEOVER);
                else DefineEstado(COMPONENTE_NORMAL);
            }
        }
    }

    int OnMouseClick(){
        DefineEstado(COMPONENTE_ACIONADO);
        if (timer) delete timer;
        timer = new CTimer(false);
        if (acao) acao(id,param);//rever se NULL é necessário
        if (audioComponente>=0) CGerenciadorAudios::Play(audioComponente);
        return 1;
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

    void IniciaBase(){
        tecla = -1;//sem tecla de atalho
        timer = NULL;//sem timer para "soltar" o botão
        acao = NULL;//não tem ação registrada
        param = NULL;//não tem parâmetro associado à ação
        largFrame = largOriginal/4;
        DefineEstado(COMPONENTE_NORMAL);
        SetPosicaoPadraoLabel(PIG_COMPONENTE_CENTRO_CENTRO);
    }

public:

    CPigBotao(int idComponente,int px, int py, int alt,int larg,char *nomeArq, int retiraFundo=1,int janela=0):
        CPigComponente(idComponente,px,py,alt,larg,nomeArq,retiraFundo,janela){
        IniciaBase();
    }

    ~CPigBotao(){
        if (timer) delete timer;
    }

    void DefineAcao(AcaoBotao funcao,void *parametro){
        acao = funcao;
        param = parametro;
    }

    void DefineAtalho(int teclaAtalho){
        tecla = teclaAtalho;
    }

    void DefineCursor(PIG_EstadoComponente estado, int indiceMouse){
        //mouse[estado]=indiceMouse;
    }

    void DefineEstado(PIG_EstadoComponente estadoComponente){
        SDL_Rect r={0,0,largFrame,altOriginal};
        estado = estadoComponente;
        switch(estado){
        case COMPONENTE_NORMAL:
            break;
        case COMPONENTE_MOUSEOVER:
            r.x += largFrame;
            break;
        case COMPONENTE_ACIONADO:
            r.x += 2*largFrame;
            break;
        case COMPONENTE_DESABILITADO:
            r.x += 3*largFrame;
            break;
        }
        DefineFrame(r);
    }

    int TrataEvento(PIG_Evento evento){

        if (estado == COMPONENTE_DESABILITADO || estado == COMPONENTE_INVISIVEL) return -1;

        if (evento.tipoEvento == EVENTO_MOUSE) return TrataMouse(evento.mouse.acao);

        if (evento.tipoEvento == EVENTO_TECLADO) return TrataTeclado(evento);

        return 0;
    }

    int Desenha(){

        if (estado==COMPONENTE_INVISIVEL) return 0;

        if (timer) TrataTimer();

        SDL_RenderCopyEx(renderer, text, &frame,&dest,-angulo,&pivoRelativo,flip);

        DesenhaLabel();
        EscreveHint();

        return 1;
    }


};

typedef CPigBotao *PigBotao;
