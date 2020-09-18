class CPigRadioBox: public CPigBox{

private:

    int itemMarcado;

    void RetiraExcessoMarcados(){
        for (int i=0;i<itens.size();i++)
            if (i!=itemMarcado)
                itens[i]->SetMarcado(false);
    }

public:

    CPigRadioBox(int idComponente, int posX, int posY, int larguraImgFundo,std::string imgFundo,std::string imgItem, int alturaItem, int larguraItem, int espacoVertical, int retiraFundo=1,int janela = 0):
        CPigBox(idComponente,posX,posY,larguraImgFundo,imgFundo,imgItem,alturaItem,larguraItem,espacoVertical,retiraFundo,janela){
        itemMarcado = -1;
    }

    CPigRadioBox(std::string nomeArqParam):CPigRadioBox(LeArquivoParametros(nomeArqParam)){}

    static CPigRadioBox LeArquivoParametros(std::string nomeArqParam){

        std::ifstream arquivo;
        int idComponente,px,py,alturaItem,larguraItem,larguraImgFundo,espacoVertical,retiraFundo=1,janela=0;
        std::string imgFundo = "",imgItem = "",variavel;

        arquivo.open(nomeArqParam);

        if(!arquivo.is_open()) throw CPigErroArquivo(nomeArqParam);
        //formato "x valor"
        while(!arquivo.eof()){
           arquivo >> variavel;
            if(variavel == "idComponente") arquivo >> idComponente;
            if(variavel == "px") arquivo >> px;
            if(variavel == "py") arquivo >> py;
            if(variavel == "larguraImgFundo") arquivo >> larguraImgFundo;
            if(variavel == "alturaItem") arquivo >> alturaItem;
            if(variavel == "larguraItem") arquivo >> larguraItem;
            if(variavel == "imagemFundo") arquivo >> imgFundo;
            if(variavel == "imagemItem") arquivo >> imgItem;
            if(variavel == "espacoVertical") arquivo >> espacoVertical;
            if(variavel == "retiraFundo") arquivo >> retiraFundo;
            if(variavel == "janela") arquivo >> janela;
        }

        arquivo.close();

       // std::cout<<idComponente<<" "<<px<<" "<<py<<" "<<altura<<" "<<largura<<" "<<nomeArq<<" "<<retiraFundo<<" "<<janela<<std::endl;
        if(imgItem == "") throw CPigErroParametro("imagemItem",imgItem);
        if(imgFundo == "") throw CPigErroParametro("imagemFundo",imgFundo);

        return CPigRadioBox(idComponente,px,py,larguraImgFundo,imgFundo,imgItem,alturaItem,larguraItem,espacoVertical,retiraFundo);

    }

    void CriaItem(std::string itemLabel, bool itemHabilitado = true, int audio=-1, std::string hintMsg="", int retiraFundo=1){
        alt =( espacoLinha*itens.size() ) + ( altItem*(itens.size()+1) );
        CPigItemCheck *item = new CPigItemCheck(itens.size(),x,y+(espacoLinha + altItem)*(itens.size()),altItem,largItem,nomeImgItem,itemLabel,retiraFundo,idJanela);
        itens.push_back(item);
        SetDimensoes(alt,larg);
        item->SetHint(hintMsg);
        if (audio==-1)
            audio = audioComponente;//audio padrao do radiobox
        item->SetAudio(audio);
        item->SetMarcado(false);
        item->SetHabilitado(itemHabilitado);
    }

    int TrataEventoMouse(PIG_Evento evento)override{
        int retorno = NAO_SELECIONADO;
        for (int i=0;i<itens.size();i++){
            if (itens[i]->TrataEventoMouse(evento)==SELECIONADO_TRATADO){
                itemMarcado = i;
                RetiraExcessoMarcados();
                return SELECIONADO_TRATADO;
            }
        }
        return NAO_SELECIONADO;
    }

    int GetMarcado(){
        return itemMarcado;
    }

    int SetMarcado(int indice, bool marcado){
        if (indice<0||indice>=itens.size()) return 0;
        if (marcado){
            itemMarcado = indice;
            for (CPigItemCheck* i: itens) i->SetMarcado(false);
        }
        itens[indice]->SetMarcado(marcado);
        return 1;
    }

};


