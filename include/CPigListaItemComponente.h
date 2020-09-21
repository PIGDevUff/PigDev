class CPigListaItemComponente: public CPigComponente{

protected:

    int fonteItens;
    int altBaseLista,altMaxima;                     //espaço vertical entre os itens
    PIG_PosicaoComponente posItens;
    std::vector <PigItemComponente> itens;
    int itemDestaque;
    //int largBaseLista;
    int altImagemItem,largImagemItem;                           //altura e largura das imagens dos itens

    void IniciaBase(int largTotal,int alturaLinha, int alturaTotal){
        SetPosicaoPadraoLabel(PIG_COMPONENTE_CIMA_CENTRO);//posição padrão do label
        //largBaseLista = largTotal;
        altBaseLista = alturaLinha;
        altMaxima = alturaTotal;
        altImagemItem = largImagemItem = alturaLinha;
        posItens = PIG_COMPONENTE_DIR_CENTRO;//só pode ser posicionamento à esquerda ou à direita
        itemDestaque = -1;
        fonteItens = 0;
    }

    void CriaItem(int yItem,std::string itemLabel, std::string arqImagem="",bool itemMarcado = false, bool itemHabilitado = true, int audio=-1, std::string hintMsg="", int retiraFundo=1){
        PigItemComponente item;
        if (arqImagem=="")
            item = new CPigItemComponente(itens.size(),x,yItem,altImagemItem,largImagemItem,itemLabel,larg,altBaseLista,retiraFundo,idJanela);
        else item = new CPigItemComponente(itens.size(),x,yItem,altImagemItem,largImagemItem,arqImagem,itemLabel,larg,altBaseLista,retiraFundo,idJanela);
        item->SetHint(hintMsg);
        if (audio==-1)
            audio = audioComponente;//audio padrao do componente
        item->SetAudio(audio);
        item->SetAcionado(itemMarcado);
        item->SetHabilitado(itemHabilitado);
        itens.push_back(item);
    }



public:

    CPigListaItemComponente(int idComponente, int posX, int posY, int larguraTotal, int alturaLinha, int alturaTotal,std::string nomeArqFundo, int retiraFundo=1,int janela = 0):
        CPigComponente(idComponente,posX,posY,alturaTotal,larguraTotal,nomeArqFundo,retiraFundo,janela){
        IniciaBase(larguraTotal,alturaLinha,alturaTotal);
    }

    ~CPigListaItemComponente(){
        for (PigItemComponente i: itens)
            delete i;
        itens.clear();
    }

    void DefineDimensaoImagemItem(int alturaImagemItem, int larguraImagemItem){
        altImagemItem = alturaImagemItem;
        largImagemItem = larguraImagemItem;
        for (int i=0;i<itens.size();i++){
            itens[i]->SetDimensoes(altImagemItem,larguraImagemItem);
        }
    }

    void AlinhaDireita(){
        if (posItens==PIG_COMPONENTE_DIR_CENTRO){//se os labels estão à direita do botões, inverte
            for (PigItemComponente i: itens)
                i->AlinhaDireita(larg);
            posItens = PIG_COMPONENTE_ESQ_CENTRO;
        }
    }

    void AlinhaEsquerda(){
        if (posItens==PIG_COMPONENTE_ESQ_CENTRO){//se os labels estão à esquerda dos botões, inverte
            for (PigItemComponente i: itens)
                i->AlinhaEsquerda(larg);
            posItens = PIG_COMPONENTE_DIR_CENTRO;
        }
    }

    void SetFonteItensLista(int fonte){
        fonteItens = fonte;
        for(PigItemComponente item :itens) item->SetFonteLabel(fonte);
    }

    virtual int Desenha()=0;

    int GetAcionadoItem(int item){
        if (item<0||item>=itens.size()) return -1;
        return itens[item]->GetAcionado();
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
        for(PigItemComponente i: itens)
            i->SetHabilitado(habilitado);
    }

    void SetVisivel(bool valor) override{
        visivel = valor;
        for(PigItemComponente i: itens)
            i->SetVisivel(visivel);
    }

    void SetFonteHint(int fonte) override{
        for (PigItemComponente i: itens)
            i->SetFonteHint(fonte);
    }

    void SetAudio(int audio) override{
        audioComponente = audio;
        for (PigItemComponente i: itens)
            i->SetAudio(audio);
    }

    void Move(int nx,int ny){
        int dx = nx-x;
        int dy = ny-y;
        CVisual::Desloca(dx,dy);
        for(int i=0;i<itens.size();i++)
            itens[i]->Desloca(dx, dy);
    }

    int GetItemDestaque(){
        return itemDestaque;
    }

    int SetAcionadoItem(int indice, bool marcado){
        if (indice<0||indice>=itens.size()) return 0;
        if (marcado){
            itemDestaque = indice;
            for (PigItemComponente i: itens)
                i->SetAcionado(false);
        }
        itens[indice]->SetAcionado(marcado);
        return 1;
    }
};
typedef CPigListaItemComponente *PigListaComponente;
