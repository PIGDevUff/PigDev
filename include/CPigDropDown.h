
class CPigDropDown: public CPigComponente{

private:

    char *texto;
    CPigLista *lista;
    PIG_PosicaoComponente posLista;
    bool marcado;
    int xLista,yLista;
    Timer timer;
    CPigItemLista *itemSelecionado;

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

    void TrataLista(PIG_Evento evento){
        if(lista->TrataEvento(evento)){
            CPigItemLista *item = new CPigItemLista(*lista->GetItemMarcado());
            item->Move(x,y);
            itemSelecionado = item;
            marcado = false;
        }
    }

    int OnMouseClick(){
        if (timer) delete timer;
        timer = new CTimer(false);
        marcado = !(marcado == true);
        if (audioComponente>=0) PlayAudio(audioComponente);
        DefineEstado(COMPONENTE_MOUSEOVER);
        return 1;
    }

    int TrataMouse(int acao){
        SDL_Point p;
        CMouse::PegaXY(p.x,p.y);
        MouseSobre(p.x,p.y);

        if(agoraOn)
            if (acao==MOUSE_PRESSIONADO) return this->OnMouseClick();

        return 0;
    }

    void DefineEstado(PIG_EstadoComponente estadoComponente){}

public:

    CPigDropDown(int idComponente,int px, int py, int alt,int larg,char *nomeArq,char *fundoLista,int retiraFundoLista,int retiraFundo=1,int janela=0):
        CPigComponente(idComponente,px,py,alt,larg,nomeArq,retiraFundo,janela){

            posLista = COMPONENTE_BAIXO;
            marcado = false;
            timer = NULL;
            posLabel = COMPONENTE_CIMA;
            xLista = 0;
            yLista = 0;
            itemSelecionado = NULL;
            lista = new CPigLista(id + 1,x,y,larg,alt,fundoLista,retiraFundoLista,idJanela);
            lista->SetRetanguloMarcacao(false);

    }

    ~CPigDropDown(){
        if(lista) delete lista;
        if(itemSelecionado) delete itemSelecionado;
        if(timer) delete timer;
    }

    int TrataEvento(PIG_Evento evento)override{

        if(marcado) TrataLista(evento);

        if (evento.tipoEvento == EVENTO_MOUSE) return TrataMouse(evento.mouse.acao);

        return 0;
    }

    void CriaItem(char *texto,char *imagemSecundaria = NULL,int largImg = 0,int retiraFundoImg = 1){
        lista->CriaItem(texto,imagemSecundaria,largImg,retiraFundoImg);
        MoveLista(posLista);
    }

    void SetItemSelecionado(int indice){
        itemSelecionado = lista->GetItem(indice);
    }

    void MoveLista(PIG_PosicaoComponente pos){

        int altura,largura;
        lista->GetDimensoes(altura,largura);

        switch(pos){

        case COMPONENTE_BAIXODIR:
            lista->Move(x+larg,y+alt-altura);break;

        case COMPONENTE_BAIXO:
            lista->Move(x,y-altura);break;

        case COMPONENTE_CIMA:
            lista->Move(x,y+alt);break;

        case COMPONENTE_CIMADIR:
            lista->Move(x+larg,y);break;

        case COMPONENTE_BAIXOESQ:
            lista->Move(x-largura,y+alt-altura);break;

        case COMPONENTE_CIMAESQ:
            lista->Move(x-largura,y);break;

        case COMPONENTE_POSICAO_PERSONALIZADA:
            lista->Move(xLista,yLista);break;

        }

    }

    void SetPosPersonalizadaLista(int posX,int posY){
        xLista = posX;
        yLista = posY;
    }

    void SetPosLista(PIG_PosicaoComponente pos){
        posLista = pos;
        MoveLista(posLista);
    }

    void SetFonteItens(int fonte){
        lista->SetFonteItensLista(fonte);
    }

    CPigItemLista *GetItemMarcadoLista(){
        return lista->GetItemMarcado();
    }

    int GetPosItemMarcadoLista(){
        return lista->GetPosItemMarcado();
    }

    int Desenha(){

        SDL_RenderCopyEx(renderer,text,NULL,&dest,-angulo,NULL,flip);
        if(itemSelecionado !=NULL) itemSelecionado->Desenha();

        if(marcado)lista->Desenha();
        DesenhaLabel();

    }

    void SetPosItensLista(PIG_PosicaoComponente pos){
        lista->SetPosItensLista(pos);
    }

};

