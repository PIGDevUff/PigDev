
class CPigDropDown: public CPigComponente{

private:

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
        if(lista->TrataEventoMouse(evento) == SELECIONADO_TRATADO){
            CPigItemLista *item = new CPigItemLista(*lista->GetItemMarcado());
            item->Move(x,y);
            if(!itemSelecionado) delete itemSelecionado;
            itemSelecionado = item;
            marcado = false;
        }
    }

    int OnMouseClick(){
        if (timer) delete timer;
        timer = new CTimer(false);
        marcado = !(marcado == true);
        if (audioComponente>=0) CGerenciadorAudios::Play(audioComponente);
        DefineEstado(COMPONENTE_MOUSEOVER);
        return SELECIONADO_TRATADO;
    }

    int TrataEventoMouse(PIG_Evento evento){
        SDL_Point p;
        CMouse::PegaXY(p.x,p.y);
        MouseSobre(p.x,p.y);

        if(marcado) TrataLista(evento);

        if (evento.mouse.acao==MOUSE_PRESSIONADO){
            if(agoraOn && evento.mouse.botao == MOUSE_ESQUERDO){
                if (habilitado==false) return SELECIONADO_DESABILITADO;
                if (visivel==false) return SELECIONADO_INVISIVEL;
                return OnMouseClick();
            }else marcado = false;
        }

        return NAO_SELECIONADO;
    }

    void DefineEstado(PIG_EstadoComponente estadoComponente){}

public:

    CPigDropDown(int idComponente,int px, int py, int altura,int largura,int alturaLista,std::string nomeArq,std::string fundoLista,int retiraFundoLista,int retiraFundo=1,int janela=0):
        CPigComponente(idComponente,px,py,altura,largura,nomeArq,retiraFundo,janela){
            marcado = false;
            timer = NULL;
            posLabel = PIG_COMPONENTE_CIMA_CENTRO;
            xLista = 0;
            yLista = 0;
            itemSelecionado = NULL;
            lista = new CPigLista(id + 1,x,y,alturaLista,largura,altura,fundoLista,retiraFundoLista,idJanela);
            lista->SetRetanguloMarcacao(false);
            MoveLista(PIG_COMPONENTE_BAIXO_CENTRO);
    }

    CPigDropDown(std::string nomeArqParam):CPigDropDown(LeArquivoParametros(nomeArqParam)){}

    ~CPigDropDown(){
        if(lista) delete lista;
        if(itemSelecionado) delete itemSelecionado;
        if(timer) delete timer;
    }

    static CPigDropDown LeArquivoParametros(std::string nomeArqParam){

        std::ifstream arquivo;
        int idComponente,px,py,altura,largura,alturaLista,retiraFundoLista = 0,retiraFundo = 0,janela = 0;

        std::string nomeArq = "",fundoLista = "",variavel;

        arquivo.open(nomeArqParam);
        if(!arquivo.is_open()) throw CPigErroArquivo(nomeArqParam);
        //formato "x valor"
        while(!arquivo.eof()){
           arquivo >> variavel;
            if(variavel == "idComponente") arquivo >> idComponente;
            if(variavel == "px") arquivo >> px;
            if(variavel == "py") arquivo >> py;
            if(variavel == "altura") arquivo >> altura;
            if(variavel == "largura") arquivo >> largura;
            if(variavel == "nomeArq") arquivo >> nomeArq;
            if(variavel == "fundoLista") arquivo >> fundoLista;
            if(variavel == "alturaLista") arquivo >> alturaLista;
            if(variavel == "retiraFundoLista") arquivo >> retiraFundoLista;
            if(variavel == "retiraFundo") arquivo >> retiraFundo;
            if(variavel == "janela") arquivo >> janela;
        }
        arquivo.close();
       // std::cout<<idComponente<<" "<<px<<" "<<py<<" "<<altura<<" "<<largura<<" "<<nomeArq<<" "<<retiraFundo<<" "<<janela<<std::endl;

        if(nomeArq == "") throw CPigErroParametro("nomeArq",nomeArqParam);
        if(fundoLista == "") throw CPigErroParametro("fundoLista",nomeArqParam);

        return CPigDropDown(idComponente,px,py,altura,largura,alturaLista,nomeArq,fundoLista,retiraFundoLista,retiraFundo,janela);

    }

    int CriaItem(std::string texto,std::string imagemSecundaria = "",int largImg = 0,int retiraFundoImg = 1){
        lista->CriaItem(texto,imagemSecundaria,largImg,retiraFundoImg);
        return 1;
    }

    void SetItemSelecionado(int indice){
        itemSelecionado = lista->GetItem(indice);
    }

    void MoveLista(PIG_PosicaoComponente pos){

        int alturaLista,larguraLista;
        lista->GetDimensoes(alturaLista,larguraLista);
        posLista = pos;

        switch(pos){

        case PIG_COMPONENTE_BAIXO_DIR:
            lista->Move(x + larg,y - alturaLista);break;

        case PIG_COMPONENTE_BAIXO_CENTRO:
            lista->Move(x + (larg-larguraLista)/2,y - alturaLista);break;

        case PIG_COMPONENTE_BAIXO_ESQ:
            lista->Move(x - larguraLista,y - alturaLista);break;

        case PIG_COMPONENTE_CIMA_CENTRO:
            lista->Move(x + (larg-larguraLista)/2,y+alt);break;

        case PIG_COMPONENTE_CIMA_DIR:
            lista->Move(x + larg,y + alt);break;

        case PIG_COMPONENTE_CIMA_ESQ:
            lista->Move(x - larguraLista,y + alt);break;

        case PIG_COMPONENTE_DIR_CIMA:
            lista->Move(x + larg,y);break;

        case PIG_COMPONENTE_DIR_BAIXO:
            lista->Move(x + larg,y + alt - alturaLista);break;

        case PIG_COMPONENTE_DIR_CENTRO:
            lista->Move(x + larg,y + (alt - alturaLista)/2);break;

        case PIG_COMPONENTE_ESQ_CIMA:
            lista->Move(x - larguraLista,y);break;

        case PIG_COMPONENTE_ESQ_BAIXO:
            lista->Move(x - larguraLista,y + alt - alturaLista);break;

        case PIG_COMPONENTE_ESQ_CENTRO:
            lista->Move(x - larguraLista,y + (alt - alturaLista)/2);break;

        case PIG_COMPONENTE_PERSONALIZADA:
            lista->Move(xLista,yLista);break;

        }

    }

    void SetPosPersonalizadaLista(int posX,int posY){
        xLista = posX;
        yLista = posY;
        posLista = PIG_COMPONENTE_PERSONALIZADA;
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
        EscreveHint();
    }

    void SetPosItensLista(PIG_PosicaoComponente pos){
        lista->SetPosItensLista(pos);
    }

};

