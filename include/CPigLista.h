
class CPigLista: public CPigComponente{

private:

    int fonteItens;
    int qntItens;
    int altItem;
    int itemMarcado;
    std::vector <CPigItemLista*> itens;
    bool retanguloMarcado;
    PIG_PosicaoComponente posItens;

    int OnMouseOn(){return 0;}
    int OnMouseOff(){return 0;}
    void DefineEstado(PIG_EstadoComponente estadoComponente){}

    void IniciaBase(int alturaItens){
        itemMarcado = -1;
        qntItens = 0;
        SetPosicaoPadraoLabel(PIG_COMPONENTE_ESQ_CENTRO);
        altItem = alturaItens;
        fonteItens = 0;
        posItens = PIG_COMPONENTE_ESQ_CENTRO;
        retanguloMarcado = true;
    }

    void DesenhaRetanguloMarcacao(){
        if(itemMarcado !=-1 && retanguloMarcado){
            int posX,posY;
            itens[itemMarcado]->GetXY(posX,posY);
            CGerenciadorJanelas::DesenhaRetanguloVazado(x,posY,altItem,larg,AZUL,idJanela);
        }
    }

    int GetItemSelecionado(){
        SDL_Point p;
        CMouse::PegaXY(p.x,p.y);
        MouseSobre(p.x,p.y);

        for (int i=0;i<itens.size();i++){
            int posX,posY;
            itens[i]->GetXY(posX,posY);
            if(posY < p.y && (posY + altItem) > p.y) return i;
        }

        return -1;
    }

public:

    CPigLista(int idComponente,int px, int py,int altura,int largura,int alturaItens,std::string nomeArq,int retiraFundo=1,int janela=0):
        CPigComponente(idComponente,px,py,altura,largura,nomeArq,retiraFundo,janela){
            IniciaBase(alturaItens);
    }

    CPigLista(std::string nomeArqParam):CPigLista(LeArquivoParametros(nomeArqParam)){}

    ~CPigLista(){
        for (CPigItemLista* x: itens) delete x;
    }

    static CPigLista LeArquivoParametros(std::string nomeArqParam){

        std::ifstream arquivo;
        int idComponente,px,py,altura = 0,largura,alturaItens,retiraFundo = 0,janela = 0;

        std::string nomeArq = "",variavel;

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
            if(variavel == "alturaItens") arquivo >> alturaItens;
            if(variavel == "nomeArq") arquivo >> nomeArq;
            if(variavel == "retiraFundo") arquivo >> retiraFundo;
            if(variavel == "janela") arquivo >> janela;
        }
        arquivo.close();
       // std::cout<<idComponente<<" "<<px<<" "<<py<<" "<<altura<<" "<<largura<<" "<<nomeArq<<" "<<retiraFundo<<" "<<janela<<std::endl;

        if(nomeArq == "") throw CPigErroParametro("nomeArq",nomeArqParam);

        return CPigLista(idComponente,px,py,altura,largura,alturaItens,nomeArq,retiraFundo,janela);

    }

    int Desenha() override{

        SDL_RenderCopyEx(renderer, text, &frame,&dest,-angulo,&pivoRelativo,flip);

        SDL_Rect r={x,altJanela-y-alt,larg,alt+1};
        SDL_RenderSetClipRect(renderer,&r);

        for(CPigItemLista *item :itens) item->Desenha();

        if(retanguloMarcado)DesenhaRetanguloMarcacao();

        SDL_RenderSetClipRect(renderer,NULL);

        DesenhaLabel();
        EscreveHint();
        return 1;
    }

    int TrataEventoTeclado(PIG_Evento evento)override{

        if(!temFoco) return 0;

        if(evento.teclado.acao == TECLA_PRESSIONADA){
            if(evento.teclado.tecla == TECLA_CIMA && evento.teclado.repeticao == 0){
                itemMarcado--;
                if(itemMarcado<0) itemMarcado = itens.size()-1;
            }

            if(evento.teclado.tecla == TECLA_BAIXO && evento.teclado.repeticao == 0)
                itemMarcado = (itemMarcado + 1) % itens.size();
        }
        return 1;
    }

    int TrataEventoMouse(PIG_Evento evento)override{
        SDL_Point p;
        CMouse::PegaXY(p.x,p.y);
        MouseSobre(p.x,p.y);

        if(agoraOn){
            if (habilitado==false) return SELECIONADO_DESABILITADO;
            if (visivel==false) return SELECIONADO_INVISIVEL;

            for(int i=0;i<itens.size();i++){
                if(itens[i]->TrataEventoMouse(evento) == SELECIONADO_TRATADO){
                    itemMarcado = i;
                    return SELECIONADO_TRATADO;
                }
            }
        }
        return NAO_SELECIONADO;
    }

    int CriaItem(std::string texto,std::string imagem = "",int largImg = 0,int retiraFundoImg = 1){

        int posX = x;
        int posY = (y + alt) - (altItem*(qntItens+1));

        CPigItemLista *item;

        if(imagem!=""){
            item = new CPigItemLista(qntItens,posX,posY,altItem,largImg,larg,x,imagem,retiraFundoImg,idJanela);
        }else{
            item = new CPigItemLista(qntItens,posX,posY,altItem,largImg,larg,x,idJanela);
        }

        item->SetLabel(texto);
        item->SetFonteLabel(fonteItens);
        item->Move(posX,posY);

        itens.push_back(item);
        qntItens++;

        return 1;

    }

    int GetPosItemMarcado(){
        return itemMarcado;
    }

    void SetRetanguloMarcacao(bool status){
        retanguloMarcado = status;
    }

    void SetFonteItensLista(int fonte){
        fonteItens = fonte;
        for(CPigItemLista *item :itens) item->SetFonteLabel(fonte);
    }

    CPigItemLista *GetItemMarcado(){
        if(itemMarcado != -1)return itens[itemMarcado];
        return NULL;
    }

    CPigItemLista *GetItem(int indice){
        if(indice>=0 && indice<itens.size()) return itens[indice];
        return NULL;
    }

    void Move(int nx,int ny){

        CVisual::Move(nx,ny);
        int posY;

        for(int i=0;i<itens.size();i++){
            posY = (y + alt) - (altItem*(i+1));
            itens[i]->Move(x,posY);
        }

    }

    void SetPosItensLista(PIG_PosicaoComponente pos){
        posItens = pos;
        for(int i=0;i<itens.size();i++){
            itens[i]->SetPosItem(posItens);
        }
    }

};
