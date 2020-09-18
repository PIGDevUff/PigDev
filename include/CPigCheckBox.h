class CPigCheckBox: public CPigBox{

public:

    CPigCheckBox(int idComponente, int posX, int posY, int larguraImgFundo,std::string imgFundo,std::string imgItem, int alturaItem, int larguraItem, int espacoVertical, int retiraFundo=1,int janela = 0):
        CPigBox(idComponente,posX,posY,larguraImgFundo,imgFundo,imgItem,alturaItem,larguraItem,espacoVertical,retiraFundo,janela){}

    CPigCheckBox(std::string nomeArqParam):CPigCheckBox(LeArquivoParametros(nomeArqParam)){}

    static CPigCheckBox LeArquivoParametros(std::string nomeArqParam){

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
            if(variavel == "imgFundo") arquivo >> imgFundo;
            if(variavel == "imgItem") arquivo >> imgItem;
            if(variavel == "espacoVertical") arquivo >> espacoVertical;
            if(variavel == "retiraFundo") arquivo >> retiraFundo;
            if(variavel == "janela") arquivo >> janela;
        }

        arquivo.close();

       // std::cout<<idComponente<<" "<<px<<" "<<py<<" "<<altura<<" "<<largura<<" "<<nomeArq<<" "<<retiraFundo<<" "<<janela<<std::endl;

        if(imgItem == "") throw CPigErroParametro("imgItem",imgItem);

        return CPigCheckBox(idComponente,px,py,larguraImgFundo,imgFundo,imgItem,alturaItem,larguraItem,espacoVertical);

    }

    void CriaItem(std::string itemLabel, bool itemMarcado = false, bool itemHabilitado = true, int audio=-1, std::string hintMsg="", int retiraFundo=1){
        alt =( espacoLinha*itens.size() ) + ( altItem*(itens.size()+1) );
        CPigItemCheck *item = new CPigItemCheck(itens.size(),x,y+(espacoLinha + altItem)*(itens.size()),altItem,largItem,nomeImgItem,itemLabel,retiraFundo,idJanela);
        itens.push_back(item);
        SetDimensoes(alt,larg);
        item->SetHint(hintMsg);
        if (audio==-1)
            audio = audioComponente;//audio padrao do componente
        item->SetAudio(audio);
        item->SetMarcado(itemMarcado);
        item->SetHabilitado(itemHabilitado);
    }

    int TrataEventoMouse(PIG_Evento evento)override{
        for (CPigItemCheck* i: itens)
            if(i->TrataEventoMouse(evento) == SELECIONADO_TRATADO) return SELECIONADO_TRATADO;

        return NAO_SELECIONADO;
    }

    void SetMarcadoTodos(bool marcado){
        for (CPigItemCheck* i: itens)
            i->SetMarcado(marcado);
    }

    int SetMarcadoItem(int indice, bool marcado){
        if (indice<0||indice>=itens.size()) return -1;
        itens[indice]->SetMarcado(marcado);
        return 1;
    }

    std::vector <int> GetItensMarcados(){
        std::vector <int> resp;
        for(int i=0;i<itens.size();i++)
            if(itens[i]->GetMarcado())resp.push_back(i);

        return resp;

    }

};

