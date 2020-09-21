class CPigItemComponente:public CPigComponente{

private:

    int largBaseLista;  //largura ocupada pelo item inteiro (dentro da lista)
    int altBaseLista;   //altura ocupada pelo item inteiro (dentro da lista)
    void (*AjustaFrame)(CPigItemComponente*);       //ponteiro para função que será chamada sempre que algum estado do item mudar

    int OnMouseClick(){
        SetAcionado(!GetAcionado());
        if (audioComponente>=0) CGerenciadorAudios::Play(audioComponente);
        return SELECIONADO_TRATADO;
    }

    void IniciaBase(std::string labelItem,int larguraLista,int alturaLista){
        largBaseLista = larguraLista;
        altBaseLista = alturaLista;
        SetPosicaoPadraoLabel(PIG_COMPONENTE_DIR_CENTRO);
        SetLabel(labelItem);
        AjustaFrame = NULL;
    }

    int ChecaMouseOver(SDL_Point pMouse)override{
        if (visivel==false||habilitado==false)
            return -1;

        SDL_Rect r={x,y,largBaseLista,altBaseLista};
        //printf("%d %d,%d,%d,%d %d,%d\n",id,r.x,r.y,r.h,r.w,pMouse.x,pMouse.y);
        SetMouseOver(SDL_PointInRect(&pMouse,&r));

        return mouseOver;
    }

public:

    CPigItemComponente(int idComponente,int px, int py, int altImagem,int largImagem,std::string arqImagem,std::string labelItem,int larguraLista,int alturaItemLista,int retiraFundo=1,int janela=0):
        CPigComponente(idComponente,px,py,altImagem,largImagem,arqImagem,retiraFundo,janela){
        IniciaBase(labelItem,larguraLista,alturaItemLista);
    }

    CPigItemComponente(int idComponente,int px, int py, int altImagem,int largImagem,std::string labelItem,int larguraLista,int alturaItemLista,int retiraFundo=1,int janela=0):
        CPigComponente(idComponente,px,py,altImagem,largImagem,janela){
        IniciaBase(labelItem,larguraLista,alturaItemLista);
    }

    ~CPigItemComponente(){

    }

    bool GetAcionado(){
        return acionado;
    }

    void SetAcionado(bool valor){
        acionado = valor;
        if (AjustaFrame) AjustaFrame(this);
    }

    void SetHabilitado(bool valor){
        habilitado = valor;
        if (AjustaFrame) AjustaFrame(this);
    }

    void SetFoco(bool valor){
        temFoco = valor;
    }

    void SetMouseOver(bool valor){
        mouseOver = valor;
        if (AjustaFrame) AjustaFrame(this);
    }

    void DefineFuncaoAjusteFrame(void (*funcao)(CPigItemComponente*)){
        AjustaFrame = funcao;
        if (AjustaFrame) AjustaFrame(this);
    }

    int Desenha(){
        SDL_RenderCopyEx(renderer,text,&frame,&dest,-angulo,NULL,flip);
        DesenhaLabel();
        EscreveHint();
    }

    void AlinhaDireita(int largTotal){
        Move(x+largBaseLista-larg,y);
        SetPosicaoPadraoLabel(PIG_COMPONENTE_ESQ_CENTRO);
    }

    void AlinhaEsquerda(int largTotal){
        Move(x-largBaseLista+larg,y);
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
        ChecaMouseOver(CMouse::PegaXY());

        if(mouseOver){
            if (evento.mouse.acao==MOUSE_PRESSIONADO && evento.mouse.botao == MOUSE_ESQUERDO){
                if (habilitado==false) return SELECIONADO_DESABILITADO;
                if (visivel==false) return SELECIONADO_INVISIVEL;
                return OnMouseClick();
            }else return SELECIONADO_TRATADO;
        }

        return NAO_SELECIONADO;
    }

    int TrataEventoTeclado(PIG_Evento evento){
        return 0;
    }

};

typedef CPigItemComponente *PigItemComponente;
