/*******FORM*********/

int CriaForm(int xForm, int yForm, int altForm, int largForm,int janela = 0){
    return CPigGerenciadorForms::CriaForm(xForm,yForm,altForm,largForm,janela);
}

/*******COMPONENTES*********/

int Pig_Componentes_CriaComponentePorArquivo(int idForm,tipos_Componentes componente,std::string nomeArquivo){
    return CPigGerenciadorForms::CriaComponentePorArquivo(idForm,componente,nomeArquivo);
}

void Pig_Componentes_SetLabel(int idComponente,std::string novoLabel){
    CPigGerenciadorForms::GetComponente(idComponente)->SetLabel(novoLabel);
}

void Pig_Componentes_SetFonteLabel(int idComponente,int fonte){
    CPigGerenciadorForms::GetComponente(idComponente)->SetFonteLabel(fonte);
}

void Pig_Componentes_SetFonteHint(int idComponente,int fonte){
    CPigGerenciadorForms::GetComponente(idComponente)->SetFonteHint(fonte);
}

void Pig_Componentes_SetAudio(int idComponente,int idAudio){
    CPigGerenciadorForms::GetComponente(idComponente)->SetAudio(idAudio);
}

void Pig_Componentes_GetLabel(int idComponente,char *label){
    if(label) free(label);
    label = (char*)(CPigGerenciadorForms::GetComponente(idComponente)->GetLabel()).c_str();
}

void Pig_Componentes_Move(int idComponente,int x,int y){
    CPigGerenciadorForms::GetComponente(idComponente)->Move(x,y);
}

void Pig_Componentes_SetDimensoes(int idComponente,int altura,int largura){
    CPigGerenciadorForms::GetComponente(idComponente)->SetDimensoes(altura,largura);
}

void Pig_Componentes_SetPosicaoPadraoLabel(int idComponente,PIG_PosicaoComponente pos){
    CPigGerenciadorForms::GetComponente(idComponente)->SetPosicaoPadraoLabel(pos);
}

void Pig_Componentes_SetPosicaoPersonalizadaLabel(int idComponente,int x,int y){
    CPigGerenciadorForms::GetComponente(idComponente)->SetPosicaoPersonalizadaLabel(x,y);
}

void Pig_Componentes_SetPosPadraoExternaComponente(int idComponente,PIG_PosicaoComponente pos,CPigComponente *componenteAssociado){
    CPigGerenciadorForms::GetComponente(idComponente)->SetPosPadraoExternaComponente(pos,componenteAssociado);
}

void Pig_Componentes_SetPosPadraoComponenteNaTela(int idComponente,PIG_Ancora pos){
    CPigGerenciadorForms::GetComponente(idComponente)->SetPosPadraoComponenteNaTela(pos);
}

void Pig_Componentes_TrataEvento(int idComponente,PIG_Evento evento){
    CPigGerenciadorForms::TrataEvento(idComponente,evento);
}

void Pig_Componentes_Desenha(int idComponente){
    CPigGerenciadorForms::Desenha(idComponente);
}

/*******BOTAO*********/

int Pig_Botao_CriaBotao(int idForm,int x,int y,int alt,int larg,std::string nomeArq,int retiraFundo = 1){
    return CPigGerenciadorForms::CriaBotao(idForm,x,y,alt,larg,nomeArq,retiraFundo);
}

void Pig_Botao_DefineAcao(int idComponente,AcaoBotao funcao,void *parametro){
    ((CPigBotao*)CPigGerenciadorForms::GetComponente(idComponente))->DefineAcao(funcao,parametro);
}

void Pig_Botao_DefineAtalho(int idComponente,int teclaAtalho){
    ((CPigBotao*)CPigGerenciadorForms::GetComponente(idComponente))->DefineAtalho(teclaAtalho);
}

void Pig_Botao_DefineTempoRepeticao(int idComponente,double segundos){
    ((CPigBotao*)CPigGerenciadorForms::GetComponente(idComponente))->DefineTempoRepeticao(segundos);
}

void Pig_Botao_DefineBotaoRepeticao(int idComponente,bool repeticao){
    ((CPigBotao*)CPigGerenciadorForms::GetComponente(idComponente))->DefineBotaoRepeticao(repeticao);
}

/*******AREADETEXTO*********/

int Pig_AreaDeTexto_CriaAreaDeTexto(int idForm,int x, int y, int altura,int largura,std::string nomeArq,int maxCars = 200,int retiraFundo=1){
    return CPigGerenciadorForms::CriaAreaDeTexto(idForm,x,y,altura,largura,nomeArq,maxCars,retiraFundo);
}

void Pig_AreaDeTexto_SetScrollBarVertical(int idComponente,int larguraTotal,int comprimentoTotal,int larguraHandle,std::string imgHandle,std::string imgTrilha,int retiraFundoHandle=1,int retiraFundoTrilha=1){
    ((CPigAreaDeTexto*)CPigGerenciadorForms::GetComponente(idComponente))->SetScrollBarVertical(larguraTotal,comprimentoTotal,larguraHandle,imgHandle,imgTrilha,retiraFundoHandle,retiraFundoTrilha);
}

void Pig_AreaDeTexto_SetScrollBarHorizontal(int idComponente,int larguraTotal,int comprimentoTotal,int larguraHandle,std::string imgHandle,std::string imgTrilha,int retiraFundoHandle=1,int retiraFundoTrilha=1){
    ((CPigAreaDeTexto*)CPigGerenciadorForms::GetComponente(idComponente))->SetScrollBarHorizontal(larguraTotal,comprimentoTotal,larguraHandle,imgHandle,imgTrilha,retiraFundoHandle,retiraFundoTrilha);
}

void Pig_AreaDeTexto_SetBotoesScrollBarVertical(int idComponente,int larguraBotoes,std::string imgBotao1,std::string imgBotao2,int retiraFundoB1 = 1,int retiraFundoB2 = 1){
    ((CPigAreaDeTexto*)CPigGerenciadorForms::GetComponente(idComponente))->SetBotoesScrollBarVertical(larguraBotoes,imgBotao1,imgBotao2,retiraFundoB1,retiraFundoB2);
}

void Pig_AreaDeTexto_SetBotoesScrollBarHorizontal(int idComponente,int larguraBotoes,std::string imgBotao1,std::string imgBotao2,int retiraFundoB1 = 1,int retiraFundoB2 = 1){
    ((CPigAreaDeTexto*)CPigGerenciadorForms::GetComponente(idComponente))->SetBotoesScrollBarVertical(larguraBotoes,imgBotao1,imgBotao2,retiraFundoB1,retiraFundoB2);
}

void Pig_AreaDeTexto_SetPosPadraoScrollHorizontal(int idComponente,PIG_PosicaoComponente pos){
    ((CPigAreaDeTexto*)CPigGerenciadorForms::GetComponente(idComponente))->SetPosPadraoScrollHorizontal(pos);
}

void Pig_AreaDeTexto_SetPosPadraoScrollVertical(int idComponente,PIG_PosicaoComponente pos){
    ((CPigAreaDeTexto*)CPigGerenciadorForms::GetComponente(idComponente))->SetPosPadraoScrollVertical(pos);
}

void Pig_AreaDeTexto_MoveScrollBarHorizontal(int idComponente,int x,int y){
    ((CPigAreaDeTexto*)CPigGerenciadorForms::GetComponente(idComponente))->MoveScrollBarHorizontal(x,y);
}

void Pig_AreaDeTexto_MoveScrollBarVertical(int idComponente,int x,int y){
    ((CPigAreaDeTexto*)CPigGerenciadorForms::GetComponente(idComponente))->MoveScrollBarVertical(x,y);
}

void Pig_AreaDeTexto_SetFonteTexto(int idComponente,int fonte){
    ((CPigAreaDeTexto*)CPigGerenciadorForms::GetComponente(idComponente))->SetFonteTexto(fonte);
}

void Pig_AreaDeTexto_SetLinhasAbaixoTexto(int idComponente,bool visivel,PIG_Cor cor = PRETO){
    ((CPigAreaDeTexto*)CPigGerenciadorForms::GetComponente(idComponente))->SetLinhasAbaixoTexto(visivel,cor);
}

void Pig_AreaDeTexto_SetLargMaxTexto(int idComponente,int largMaxTexto){
    ((CPigAreaDeTexto*)CPigGerenciadorForms::GetComponente(idComponente))->SetLargMaxTexto(largMaxTexto);
}

void Pig_AreaDeTexto_SetEspacoEntreAsLinhas(int idComponente,int espaco){
    ((CPigAreaDeTexto*)CPigGerenciadorForms::GetComponente(idComponente))->SetEspacoEntreAsLinhas(espaco);
}

void Pig_AreaDeTexto_SetTexto(int idComponente,std::string frase){
    ((CPigAreaDeTexto*)CPigGerenciadorForms::GetComponente(idComponente))->SetTexto(frase);
}

void Pig_AreaDeTexto_SetMargens(int idComponente,int horEsq,int horDir, int vertBaixo,int vertCima){
    ((CPigAreaDeTexto*)CPigGerenciadorForms::GetComponente(idComponente))->SetMargens(horEsq,horDir,vertBaixo,vertCima);
}

std::vector<std::string> Pig_AreaDeTexto_GetLinhasTexto(int idComponente){
    ((CPigAreaDeTexto*)CPigGerenciadorForms::GetComponente(idComponente))->GetLinhasTexto();
}

/**********CAMPOTEXTOESENHA**************/

int Pig_CampoTextoESenha_CriaCampoTextoESenha(int idForm,int x, int y, int altura,int largura,std::string nomeArq,int maxCars = 200, bool apenasNumeros=false, int retiraFundo=1,bool campoSenha = false){
    return CPigGerenciadorForms::CriaCampoTextoESenha(idForm,x,y,altura,largura,nomeArq,maxCars,apenasNumeros,retiraFundo,campoSenha);
}

/**********LISTA**************/

int Pig_Lista_CriaLista(int idForm,int x, int y,int altura,int largura,int alturaItens,std::string nomeArq,int retiraFundo=1){
    return CPigGerenciadorForms::CriaLista(idForm,x,y,altura,largura,alturaItens,nomeArq,retiraFundo);
}

int Pig_Lista_CriaItem(int idComponente,std::string texto,std::string imagem = "",int largImg = 0,int retiraFundoImg = 1){
    ((CPigLista*)CPigGerenciadorForms::GetComponente(idComponente))->CriaItem(texto,imagem,largImg,retiraFundoImg);
}

/**********DROPDOWN**************/

int Pig_DropDown_CriaDropDown(int idForm,int x, int y, int altura,int largura,int alturaLista,std::string nomeArq,std::string fundoLista,int retiraFundoLista,int retiraFundo=1){
    return CPigGerenciadorForms::CriaDropDown(idForm,x,y,altura,largura,alturaLista,nomeArq,fundoLista,retiraFundoLista,retiraFundo);
}

int Pig_DropDown_CriaItem(int idComponente,std::string texto,std::string imagem = "",int largImg = 0,int retiraFundoImg = 1){
    return ((CPigDropDown*)CPigGerenciadorForms::GetComponente(idComponente))->CriaItem(texto,imagem,largImg,retiraFundoImg);
}

/**********GAUGE**************/

int Pig_Gauge_CriaGauge(int idForm,int x, int y,int altura,int largura,std::string imgGauge,int retiraFundo=1){
    return CPigGerenciadorForms::CriaGauge(idForm,x,y,altura,largura,imgGauge,retiraFundo);
}

void Pig_Gauge_SetFrames(int idComponente,SDL_Rect fBase,SDL_Rect fBarra){
    ((CPigGauge*)CPigGerenciadorForms::GetComponente(idComponente))->SetFrames(fBase,fBarra);
}

void Pig_Gauge_SetDelta(int idComponente,float valor){
    ((CPigGauge*)CPigGerenciadorForms::GetComponente(idComponente))->SetDelta(valor);
}

void Pig_Gauge_AvancaDelta(int idComponente){
    ((CPigGauge*)CPigGerenciadorForms::GetComponente(idComponente))->AvancaDelta();
}

float Pig_Gauge_GetPorcentagemConcluida(int idComponente){
    return ((CPigGauge*)CPigGerenciadorForms::GetComponente(idComponente))->GetPorcentagemConcluida();
}

void Pig_Gauge_ZeraValor(int idComponente){
    ((CPigGauge*)CPigGerenciadorForms::GetComponente(idComponente))->ZeraValor();
}

/**********GAUGECIRCULAR**************/

int Pig_GaugeCircular_CriaGaugeCircular(int idForm,int x, int y,int altura,int largura,int raioInterior,std::string imgGauge,int retiraFundo=1){
    return CPigGerenciadorForms::CriaGaugeCircular(idForm,x,y,altura,largura,raioInterior,imgGauge,retiraFundo);
}

/**********RADIOBOX**************/

int Pig_RadioBox_CriaRadioBox(int idForm,int x, int y,int larguraImgFundo,std::string imagemFundo,std::string imagemItem, int alturaItem, int larguraItem, int espacoVertical,int retiraFundo=1){
    return CPigGerenciadorForms::CriaRadioBox(idForm,x,y,larguraImgFundo,imagemFundo,imagemItem,alturaItem,larguraItem,espacoVertical,retiraFundo);
}

void Pig_RadioBox_CriaItem(int idComponente,std::string itemLabel, bool itemHabilitado = true, int audio=-1, std::string hintMsg="", int retiraFundo=1){
    ((CPigRadioBox*)CPigGerenciadorForms::GetComponente(idComponente))->CriaItem(itemLabel,itemHabilitado,audio,hintMsg,retiraFundo);
}

int Pig_RadioBox_GetMarcado(int idComponente){
    return ((CPigRadioBox*)CPigGerenciadorForms::GetComponente(idComponente))->GetMarcado();
}

int Pig_RadioBox_SetMarcado(int idComponente,int indice, bool marcado){
    return ((CPigRadioBox*)CPigGerenciadorForms::GetComponente(idComponente))->SetMarcado(indice,marcado);
}

/**********CHECKBOX**************/

int Pig_CheckBox_CriaCheckBox(int idForm,int x, int y,int larguraImgFundo,std::string imagemFundo,std::string imagemItem, int alturaItem, int larguraItem, int espacoVertical,int retiraFundo=1){
    return CPigGerenciadorForms::CriaCheckBox(idForm,x,y,larguraImgFundo,imagemFundo,imagemItem,alturaItem,larguraItem,espacoVertical,retiraFundo);
}

void Pig_CheckBox_CriaItem(int idComponente,std::string itemLabel,bool itemMarcado = false, bool itemHabilitado = true, int audio=-1, std::string hintMsg="", int retiraFundo=1){
    ((CPigCheckBox*)CPigGerenciadorForms::GetComponente(idComponente))->CriaItem(itemLabel,itemMarcado,itemHabilitado,audio,hintMsg,retiraFundo);
}

void Pig_CheckBox_SetMarcadoTodos(int idComponente,bool marcado){
    ((CPigCheckBox*)CPigGerenciadorForms::GetComponente(idComponente))->SetMarcadoTodos(marcado);
}

int Pig_CheckBox_SetMarcadoItem(int idComponente,int indice,bool marcado){
    return ((CPigCheckBox*)CPigGerenciadorForms::GetComponente(idComponente))->SetMarcadoItem(indice,marcado);
}

std::vector <int> Pig_CheckBox_GetItensMarcados(int idComponente){
    return ((CPigCheckBox*)CPigGerenciadorForms::GetComponente(idComponente))->GetItensMarcados();
}

/********************************/
