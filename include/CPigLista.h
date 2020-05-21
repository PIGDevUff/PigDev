
class CPigLista: public CPigComponente{

private:

    int fonteItens;
    int qntItens;
    int altItem;
    int itemMarcado;
    std::vector <CPigItemLista*> itens;
    bool ajAutomatico,retanguloMarcado;
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
            DesenhaRetanguloVazado(x,posY,altItem,larg,AZUL,idJanela);
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

    CPigLista(int idComponente,int px, int py,int larg,int alturaItens,char *nomeArq,int retiraFundo=1,int janela=0):
        CPigComponente(idComponente,px,py,0,larg,nomeArq,retiraFundo,janela){
            IniciaBase(alturaItens);
            ajAutomatico = true;
    }

    CPigLista(int idComponente,int px, int py,int alt,int larg,int alturaItens,char *nomeArq,int retiraFundo=1,int janela=0):
        CPigComponente(idComponente,px,py,alt,larg,nomeArq,retiraFundo,janela){
            IniciaBase(alturaItens);
            ajAutomatico = false;
    }

    ~CPigLista(){
        for (CPigItemLista* x: itens) delete x;
    }

    int Desenha() override{

        SDL_RenderCopyEx(renderer, text, &frame,&dest,-angulo,&pivoRelativo,flip);

        SDL_Rect r={x,altJanela-y-alt,larg,alt+1};
        SDL_RenderSetClipRect(renderer,&r);

        for(CPigItemLista *item :itens) item->Desenha();

        if(retanguloMarcado)DesenhaRetanguloMarcacao();

        SDL_RenderSetClipRect(renderer,NULL);

        DesenhaLabel();
        return 1;
    }

    int TrataEvento(PIG_Evento evento){

        for(int i=0;i<itens.size();i++){
            if(itens[i]->TrataEvento(evento)){
                itemMarcado = i;
                return 1;
            }
        }

        return 0;
    }

    int CriaItem(char *texto,char *imagem = NULL,int largImg = 0,int retiraFundoImg = 1){

        int posX = x;
        int posY = (y + alt) - (altItem*(qntItens+1));

        CPigItemLista *item;

        if(imagem !=NULL && imagem!=""){
            item = new CPigItemLista(qntItens,posX,posY,altItem,largImg,larg,x,imagem,retiraFundoImg,idJanela);
        }else{
            item = new CPigItemLista(qntItens,posX,posY,altItem,largImg,larg,x,idJanela);
        }

        item->SetLabel(texto);
        item->SetFonteLabel(fonteItens);
        item->Move(posX,posY);

        itens.push_back(item);
        qntItens++;

        if(ajAutomatico){
            SetDimensoes(altItem * (qntItens),larg);
            Move(x,y);
        }

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
