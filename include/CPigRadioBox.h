class CPigRadioBox: public CPigBox{

private:

int itemMarcado;

public:

CPigRadioBox(int idComponente, int posX, int posY, int largura, char *nomeArqFundo, char *nomeArqItem, int alturaItem, int larguraItem, int espacoVertical, int retiraFundo=1):
    CPigBox(idComponente,posX,posY,largura,nomeArqFundo,nomeArqItem,alturaItem,larguraItem,espacoVertical,retiraFundo){
    itemMarcado = -1;
}

CPigRadioBox(int idComponente, int posX, int posY, int largura, char *nomeArqItem,int alturaItem, int larguraItem, int espacoVertical):
    CPigBox(idComponente,posX,posY,largura,nomeArqItem,alturaItem,larguraItem,espacoVertical){
    itemMarcado = -1;
}

//Diferente
void CriaItem(char *itemLabel, bool itemHabilitado, int audio=-1, char *hintMsg=NULL, int retiraFundo=1,int janela=0){
    alt =( espacoLinha*itens.size() ) + ( altItem*(itens.size()+1) );
    CPigItemCheck *item = new CPigItemCheck(itens.size(),x,y+(espacoLinha + altItem)*(itens.size()),altItem,largItem,(char*)nomeImgItem.c_str(),itemLabel,retiraFundo,janela);
    itens.push_back(item);
    SetDimensoes(alt,larg);
    item->SetHint(hintMsg);
    if (audio==-1)
        audio = audioComponente;//audio padrao do radiobox
    item->SetAudio(audio);
    item->SetMarcado(false);
    item->SetHabilitado(itemHabilitado);
}

int TrataEvento(PIG_Evento evento)override{
    itemMarcado = -1;
    for (int i=0;i<itens.size();i++){
        if (itens[i]->TrataEvento(evento)==1 && itens[i]->GetMarcado()){
            itemMarcado = i;
        }
    }
    if (itemMarcado!=-1){
        for (int i=0;i<itens.size();i++){
            if (i!=itemMarcado)
                itens[i]->SetMarcado(false);
        }
        return 1;
    }
    return 0;
}

int GetMarcado(){
    return itemMarcado;
}

int SetMarcado(int indice, bool marcado){
    if (indice<0||indice>=itens.size()) return 0;
    if (marcado){
        for (CPigItemCheck* i: itens)
            i->SetMarcado(false);
    }
    itens[indice]->SetMarcado(marcado);
    return 1;
}

};


