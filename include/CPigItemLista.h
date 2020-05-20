
class CPigItemLista: public CPigComponente{

private:

    int largBase;
    int xBase;
    Timer timer;
    PIG_PosicaoComponente posItem;


    void DefineEstado(PIG_EstadoComponente estadoComponente){}
    int OnMouseOn(){return 0;}
    int OnMouseOff(){return 0;}

    int OnMouseClick(){
        DefineEstado(COMPONENTE_ACIONADO);
        if (timer) delete timer;
        timer = new CTimer(false);
        if (audioComponente>=0) PlayAudio(audioComponente);
        return 1;
    }

    int MouseSobre(int mx, int my){
        SDL_Point p={mx,my};
        SDL_Rect r={xBase,y,largBase,alt};

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

    int TrataMouse(int acao){
        SDL_Point p;
        CMouse::PegaXY(p.x,p.y);
        MouseSobre(p.x,p.y);

        if(agoraOn)
            if (acao==MOUSE_PRESSIONADO) return OnMouseClick();

        return 0;
    }

    void AlinhaDireita(int nx,int ny){
        CVisual::Move(nx+largBase-larg,ny);
        SetPosicaoPadraoLabel(COMPONENTE_ESQUERDA);
    }

    void AlinhaEsquerda(int nx,int ny){
        CVisual::Move(nx,ny);
        SetPosicaoPadraoLabel(COMPONENTE_DIREITA);
    }

    void IniciaBase(int larguraLista,int posXLista){

        timer = NULL;
        largBase = larguraLista;
        xBase = posXLista;
        posItem = COMPONENTE_ESQUERDA;

    }

public:

    CPigItemLista(int idComponente,int px, int py, int altItem,int largItem,int larguraLista,int posXLista,char *nomeArq, int retiraFundo=1,int janela=0):
        CPigComponente(idComponente,px,py,altItem,largItem,nomeArq,retiraFundo,janela){
            IniciaBase(larguraLista,posXLista);
    }

    CPigItemLista(int idComponente,int px, int py,int altItem,int largItem,int larguraLista,int posXLista,int janela=0):
        CPigComponente(idComponente,px,py,altItem,largItem,janela){
            IniciaBase(larguraLista,posXLista);
    }

    int TrataEvento(PIG_Evento evento){

        if (evento.tipoEvento == EVENTO_MOUSE) return TrataMouse(evento.mouse.acao);

        return 0;
    }

    int Desenha(){

        SDL_RenderCopyEx(renderer, text, &frame,&dest,-angulo,&pivoRelativo,flip);
        DesenhaLabel();

        return 1;
    }

    void SetPosItem(PIG_PosicaoComponente pos){
        posItem = pos;
        Move(xBase,y);
    }

    void Move(int nx,int ny){
        if(posItem == COMPONENTE_DIREITA) AlinhaDireita(nx,ny);
        if(posItem == COMPONENTE_ESQUERDA) AlinhaEsquerda(nx,ny);
        xBase = nx;
    }

};
