class CPigBox: public CPigComponente{

protected:

int largItem,altItem;//altura e largura da imagem de cada item
std::string nomeImgItem;//nome da imagem de cada item
int espacoLinha; //espaço vertical entre os itens
PIG_PosicaoComponente posItens;
std::vector <CPigItemCheck*> itens;

void IniciaBase(int alturaItem, int larguraItem, int espacoVertical, char *nomeArqItem){
    SetPosicaoPadraoLabel(PIG_COMPONENTE_CIMA_ESQ);//posição padrão do label
    nomeImgItem.assign(nomeArqItem);
    largItem = larguraItem;
    altItem = alturaItem;
    espacoLinha = espacoVertical;
    posItens = PIG_COMPONENTE_DIR_CENTRO;//só pode ser posicionamento à esquerda ou à direita
}

public:

CPigBox(int idComponente, int posX, int posY, int largura, char *nomeArqFundo, char *nomeArqItem, int alturaItem, int larguraItem, int espacoVertical, int retiraFundo=1):
    CPigComponente(idComponente,posX,posY,0,largura,nomeArqFundo,retiraFundo){
    IniciaBase(alturaItem, larguraItem, espacoVertical, nomeArqItem);
}

CPigBox(int idComponente, int posX, int posY, int largura, char *nomeArqItem,int alturaItem, int larguraItem, int espacoVertical):
    CPigComponente(idComponente,posX,posY,0,largura){
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

int Desenha(){
    if (estado==COMPONENTE_INVISIVEL) return 0;

    if (text){//se tiver imagem de fundo
        SDL_RenderCopyEx(renderer,text,NULL,&dest,-angulo,NULL,flip);
    }
    DesenhaLabel();

    for (CPigItemCheck* i: itens)
        i->Desenha();

    return 1;
}

int GetMarcadoItem(int indice){
    if (indice<0||indice>=itens.size()) return -1;
    return itens[indice]->GetMarcado();
}

int SetMarcadoItem(int indice, bool marcado){
    if (indice<0||indice>=itens.size()) return -1;
    itens[indice]->SetMarcado(marcado);
    return 1;
}

int SetAudioItem(int indice, int audio){
    if (indice<0||indice>=itens.size()) return -1;
    itens[indice]->SetAudio(audio);
    return 1;
}

int GetHabilitadoItem(int indice){
    if (indice<0||indice>=itens.size()) return -1;
    return itens[indice]->GetHabilitado();
}

int SetHabilitadoItem(int indice, bool habilitado){
    if (indice<0||indice>=itens.size()) return -1;
    itens[indice]->SetHabilitado(habilitado);
    return 1;
}

int SetHabilitado(bool habilitado){
    if(habilitado)
        DefineEstado(COMPONENTE_NORMAL);
    else
        DefineEstado(COMPONENTE_DESABILITADO);

    for(CPigItemCheck *i :itens)
        i->SetHabilitado(habilitado);

    return 1;
}

int SetLabelIndice(int indice, char *label){
    if (indice<0||indice>=itens.size()) return -1;
    itens[indice]->SetLabel(label);
    return 1;
}

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

//cadaclasses derivada tratará de uma forma diferente
virtual int TrataEvento(PIG_Evento evento) = 0;

};

