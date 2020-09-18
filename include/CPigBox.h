class CPigBox: public CPigComponente{

protected:

    int largItem,altItem;//altura e largura da imagem de cada item
    std::string nomeImgItem;//nome da imagem de cada item
    int espacoLinha; //espaço vertical entre os itens
    PIG_PosicaoComponente posItens;
    std::vector <CPigItemCheck*> itens;

    void IniciaBase(int alturaItem, int larguraItem, int espacoVertical, std::string nomeArqItem){
        SetPosicaoPadraoLabel(PIG_COMPONENTE_CIMA_CENTRO);//posição padrão do label
        nomeImgItem = nomeArqItem;
        largItem = larguraItem;
        altItem = alturaItem;
        espacoLinha = espacoVertical;
        posItens = PIG_COMPONENTE_DIR_CENTRO;//só pode ser posicionamento à esquerda ou à direita
    }

public:

    CPigBox(int idComponente, int posX, int posY, int largura, std::string nomeArqFundo, std::string nomeArqItem, int alturaItem, int larguraItem, int espacoVertical, int retiraFundo=1,int janela = 0):
        CPigComponente(idComponente,posX,posY,0,largura,nomeArqFundo,retiraFundo,janela){
        IniciaBase(alturaItem, larguraItem, espacoVertical, nomeArqItem);
    }

    ~CPigBox(){
        for (CPigItemCheck* i: itens)
            delete i;
        itens.clear();
    }

    void AlinhaDireita(){
        if (posItens==PIG_COMPONENTE_DIR_CENTRO){//se os labels estão à direita do botões, inverte
            for (CPigItemCheck* i: itens)
                i->AlinhaDireita(larg);
            posItens = PIG_COMPONENTE_ESQ_CENTRO;
        }
    }

    void AlinhaEsquerda(){
    if (posItens==PIG_COMPONENTE_ESQ_CENTRO){//se os labels estão à esquerda dos botões, inverte
        for (CPigItemCheck* i: itens)
            i->AlinhaEsquerda(larg);
        posItens = PIG_COMPONENTE_DIR_CENTRO;
    }
}

    int VerificaSeComponenteEstaSelecionado(PIG_Evento evento){
        SDL_Point p;
        CMouse::PegaXY(p.x,p.y);
        MouseSobre(p.x,p.y);

        if(agoraOn){
            if(evento.tipoEvento == EVENTO_MOUSE){
                if(evento.mouse.acao==MOUSE_PRESSIONADO && evento.mouse.botao == MOUSE_ESQUERDO)
                    return 1;
            }
        }
        return 2;
    }

    int Desenha(){
        if (visivel==false) return 0;

        if (text){//se tiver imagem de fundo
            SDL_RenderCopyEx(renderer,text,NULL,&dest,-angulo,NULL,flip);
        }
        DesenhaLabel();

        for (CPigItemCheck* i: itens)
            i->Desenha();

        return 1;
    }

    /****/

    int GetMarcadoItem(int item){
        if (item<0||item>=itens.size()) return -1;
        return itens[item]->GetMarcado();
    }

    int SetAudioItem(int item, int audio){
        if (item<0||item>=itens.size()) return -1;
        itens[item]->SetAudio(audio);
        return 1;
    }

    int GetHabilitadoItem(int item){
        if (item<0||item>=itens.size()) return -1;
        return itens[item]->GetHabilitado();
    }

    int SetHabilitadoItem(int item, bool valor){
        if (item<0||item>=itens.size()) return -1;
        itens[item]->SetHabilitado(valor);
        return 1;
    }

    void SetHabilitado(bool valor) override{
        habilitado = valor;
        for(CPigItemCheck *i :itens)
            i->SetHabilitado(habilitado);
    }

    /*****/

    void SetFonteHint(int fonte) override{
        for (CPigItemCheck* i: itens)
            i->SetFonteHint(fonte);
    }

    void SetAudio(int audio) override{
        audioComponente = audio;
        for (CPigItemCheck* i: itens)
            i->SetAudio(audio);
    }

    void Move(int nx,int ny){
        CVisual::Move(nx,ny);
        for(int i=0;i<itens.size();i++)
            itens[i]->Move(nx , ny + (espacoLinha + altItem) * i);
    }

    int OnMouseOn(){return 1;} //o evento é repassado para cada item

    int OnMouseOff(){return 1;} //oevento é repassado para cada item

    //define o estado global de todos os itens
    void DefineEstado(PIG_EstadoComponente estadoComponente){
        if(estadoComponente == COMPONENTE_DESABILITADO)
            for (CPigItemCheck* i: itens)
                i->DefineEstado(COMPONENTE_DESABILITADO);

        if(estadoComponente == COMPONENTE_NORMAL)
            for (CPigItemCheck* i: itens)
                i->DefineEstado(COMPONENTE_NORMAL);
    }

};

