class CPigCheckBox: public CPigBox{

public:

CPigCheckBox(int idComponente, int posX, int posY, int largura, std::string nomeArqFundo, char *nomeArqItem, int alturaItem, int larguraItem, int espacoVertical, int retiraFundo=1):
    CPigBox(idComponente,posX,posY,largura,nomeArqFundo,nomeArqItem,alturaItem,larguraItem,espacoVertical,retiraFundo){

}

CPigCheckBox(int idComponente, int posX, int posY, int largura, std::string nomeArqItem,int alturaItem, int larguraItem, int espacoVertical):
    CPigBox(idComponente,posX,posY,largura,nomeArqItem,alturaItem,larguraItem,espacoVertical){

}

void CriaItem(std::string itemLabel, bool itemMarcado = false, bool itemHabilitado = true, int audio=-1, std::string hintMsg="", int retiraFundo=1,int janela=0){
    alt =( espacoLinha*itens.size() ) + ( altItem*(itens.size()+1) );
    CPigItemCheck *item = new CPigItemCheck(itens.size(),x,y+(espacoLinha + altItem)*(itens.size()),altItem,largItem,(char*)nomeImgItem.c_str(),itemLabel,retiraFundo,janela);
    itens.push_back(item);
    SetDimensoes(alt,larg);
    item->SetHint(hintMsg);
    if (audio==-1)
        audio = audioComponente;//audio padrao do componente
    item->SetAudio(audio);
    item->SetMarcado(itemMarcado);
    item->SetHabilitado(itemHabilitado);
}

int TrataEvento(PIG_Evento evento)override{
    int resp = 0;
    for (CPigItemCheck* i: itens)
        resp += i->TrataEvento(evento);
     return resp;
}

void SetMarcadoTodos(bool marcado){
    for (CPigItemCheck* i: itens)
        i->SetMarcado(false);
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

