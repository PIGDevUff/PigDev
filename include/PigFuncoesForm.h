/*******FORM*********/

int Pig_Form_CriaForm(int xForm, int yForm, int altForm, int largForm,int janela = 0){
    return CGerenciadorForms::CriaForm(xForm,yForm,altForm,largForm,janela);
}

int Pig_Form_TrataEvento(int idForm,PIG_Evento evento){
    return CGerenciadorForms::TrataEvento(idForm,evento);
}

int Pig_Form_Desenha(int idForm){
    return CGerenciadorForms::Desenha(idForm);
}

/*******COMPONENTES*********/

int Pig_Componentes_CriaComponentePorArquivo(int idForm,tipos_Componentes componente,char* nomeArquivo){
    return CGerenciadorForms::CriaComponentePorArquivo(idForm,componente,nomeArquivo);
}

void Pig_Componentes_SetLabel(int idComponente,char* novoLabel){
    CGerenciadorForms::GetComponente(idComponente)->SetLabel(novoLabel);
}

void Pig_Componentes_SetFonteLabel(int idComponente,int fonte){
    CGerenciadorForms::GetComponente(idComponente)->SetFonteLabel(fonte);
}

void Pig_Componentes_SetFonteHint(int idComponente,int fonte){
    CGerenciadorForms::GetComponente(idComponente)->SetFonteHint(fonte);
}

void Pig_Componentes_SetAudio(int idComponente,int idAudio){
    CGerenciadorForms::GetComponente(idComponente)->SetAudio(idAudio);
}

void Pig_Componentes_GetLabel(int idComponente,char *label){
    if(label) free(label);
    label = (char*)(CGerenciadorForms::GetComponente(idComponente)->GetLabel()).c_str();
}

void Pig_Componentes_SetHint(int idComponente,char *hint){
    CGerenciadorForms::GetComponente(idComponente)->SetHint(hint);
}

void Pig_Componentes_Move(int idComponente,int x,int y){
    CGerenciadorForms::GetComponente(idComponente)->Move(x,y);
}

void Pig_Componentes_SetDimensoes(int idComponente,int altura,int largura){
    CGerenciadorForms::GetComponente(idComponente)->SetDimensoes(altura,largura);
}

void Pig_Componentes_SetPosicaoPadraoLabel(int idComponente,PIG_PosicaoComponente pos){
    CGerenciadorForms::GetComponente(idComponente)->SetPosicaoPadraoLabel(pos);
}

void Pig_Componentes_SetPosicaoPersonalizadaLabel(int idComponente,int x,int y){
    CGerenciadorForms::GetComponente(idComponente)->SetPosicaoPersonalizadaLabel(x,y);
}

void Pig_Componentes_SetPosPadraoExternaComponente(int idComponente,PIG_PosicaoComponente pos,CPigComponente *componenteAssociado){
    CGerenciadorForms::GetComponente(idComponente)->SetPosPadraoExternaComponente(pos,componenteAssociado);
}

void Pig_Componentes_SetPosPadraoComponenteNaTela(int idComponente,PIG_Ancora pos){
    CGerenciadorForms::GetComponente(idComponente)->SetPosPadraoComponenteNaTela(pos);
}

/*******BOTAO*********/

int Pig_Botao_CriaBotao(int idForm,int x,int y,int alt,int larg,char* nomeArq,int retiraFundo = 1){
    return CGerenciadorForms::CriaBotao(idForm,x,y,alt,larg,nomeArq,retiraFundo);
}

void Pig_Botao_DefineAcao(int idComponente,AcaoBotao funcao,void *parametro){
    ((CPigBotao*)CGerenciadorForms::GetComponente(idComponente))->DefineAcao(funcao,parametro);
}

void Pig_Botao_DefineAtalho(int idComponente,int teclaAtalho){
    ((CPigBotao*)CGerenciadorForms::GetComponente(idComponente))->DefineAtalho(teclaAtalho);
}

void Pig_Botao_DefineTempoRepeticao(int idComponente,double segundos){
    ((CPigBotao*)CGerenciadorForms::GetComponente(idComponente))->DefineTempoRepeticao(segundos);
}

void Pig_Botao_DefineBotaoRepeticao(int idComponente,bool repeticao){
    ((CPigBotao*)CGerenciadorForms::GetComponente(idComponente))->DefineBotaoRepeticao(repeticao);
}

/*******AREADETEXTO*********/

int Pig_AreaDeTexto_CriaAreaDeTexto(int idForm,int x, int y, int altura,int largura,char* nomeArq,int maxCars = 200,int retiraFundo=1){
    return CGerenciadorForms::CriaAreaDeTexto(idForm,x,y,altura,largura,nomeArq,maxCars,retiraFundo);
}

void Pig_AreaDeTexto_SetScrollBarVertical(int idComponente,int larguraTotal,int comprimentoTotal,int larguraHandle,char* imgHandle,char* imgTrilha,int retiraFundoHandle=1,int retiraFundoTrilha=1){
    ((CPigAreaDeTexto*)CGerenciadorForms::GetComponente(idComponente))->SetScrollBarVertical(larguraTotal,comprimentoTotal,larguraHandle,imgHandle,imgTrilha,retiraFundoHandle,retiraFundoTrilha);
}

void Pig_AreaDeTexto_SetScrollBarHorizontal(int idComponente,int larguraTotal,int comprimentoTotal,int larguraHandle,char* imgHandle,char* imgTrilha,int retiraFundoHandle=1,int retiraFundoTrilha=1){
    ((CPigAreaDeTexto*)CGerenciadorForms::GetComponente(idComponente))->SetScrollBarHorizontal(larguraTotal,comprimentoTotal,larguraHandle,imgHandle,imgTrilha,retiraFundoHandle,retiraFundoTrilha);
}

void Pig_AreaDeTexto_SetBotoesScrollBarVertical(int idComponente,int larguraBotoes,char* imgBotao1,char* imgBotao2,int retiraFundoB1 = 1,int retiraFundoB2 = 1){
    ((CPigAreaDeTexto*)CGerenciadorForms::GetComponente(idComponente))->SetBotoesScrollBarVertical(larguraBotoes,imgBotao1,imgBotao2,retiraFundoB1,retiraFundoB2);
}

void Pig_AreaDeTexto_SetBotoesScrollBarHorizontal(int idComponente,int larguraBotoes,char* imgBotao1,char* imgBotao2,int retiraFundoB1 = 1,int retiraFundoB2 = 1){
    ((CPigAreaDeTexto*)CGerenciadorForms::GetComponente(idComponente))->SetBotoesScrollBarVertical(larguraBotoes,imgBotao1,imgBotao2,retiraFundoB1,retiraFundoB2);
}

void Pig_AreaDeTexto_SetPosPadraoScrollHorizontal(int idComponente,PIG_PosicaoComponente pos){
    ((CPigAreaDeTexto*)CGerenciadorForms::GetComponente(idComponente))->SetPosPadraoScrollHorizontal(pos);
}

void Pig_AreaDeTexto_SetPosPadraoScrollVertical(int idComponente,PIG_PosicaoComponente pos){
    ((CPigAreaDeTexto*)CGerenciadorForms::GetComponente(idComponente))->SetPosPadraoScrollVertical(pos);
}

void Pig_AreaDeTexto_MoveScrollBarHorizontal(int idComponente,int x,int y){
    ((CPigAreaDeTexto*)CGerenciadorForms::GetComponente(idComponente))->MoveScrollBarHorizontal(x,y);
}

void Pig_AreaDeTexto_MoveScrollBarVertical(int idComponente,int x,int y){
    ((CPigAreaDeTexto*)CGerenciadorForms::GetComponente(idComponente))->MoveScrollBarVertical(x,y);
}

void Pig_AreaDeTexto_SetFonteTexto(int idComponente,int fonte){
    ((CPigAreaDeTexto*)CGerenciadorForms::GetComponente(idComponente))->SetFonteTexto(fonte);
}

void Pig_AreaDeTexto_SetLinhasAbaixoTexto(int idComponente,bool visivel,PIG_Cor cor = PRETO){
    ((CPigAreaDeTexto*)CGerenciadorForms::GetComponente(idComponente))->SetLinhasAbaixoTexto(visivel,cor);
}

void Pig_AreaDeTexto_SetLargMaxTexto(int idComponente,int largMaxTexto){
    ((CPigAreaDeTexto*)CGerenciadorForms::GetComponente(idComponente))->SetLargMaxTexto(largMaxTexto);
}

void Pig_AreaDeTexto_SetEspacoEntreAsLinhas(int idComponente,int espaco){
    ((CPigAreaDeTexto*)CGerenciadorForms::GetComponente(idComponente))->SetEspacoEntreAsLinhas(espaco);
}

void Pig_AreaDeTexto_SetTexto(int idComponente,char* frase){
    ((CPigAreaDeTexto*)CGerenciadorForms::GetComponente(idComponente))->SetTexto(frase);
}

void Pig_AreaDeTexto_SetMargens(int idComponente,int horEsq,int horDir, int vertBaixo,int vertCima){
    ((CPigAreaDeTexto*)CGerenciadorForms::GetComponente(idComponente))->SetMargens(horEsq,horDir,vertBaixo,vertCima);
}

void Pig_AreaDeTexto_SetCorCursor(int idComponente,PIG_Cor cor){
    ((CPigAreaDeTexto*)CGerenciadorForms::GetComponente(idComponente))->SetCorCursor(cor);
}

std::vector<std::string> Pig_AreaDeTexto_GetLinhasTexto(int idComponente){
    ((CPigAreaDeTexto*)CGerenciadorForms::GetComponente(idComponente))->GetLinhasTexto();
}

/**********CAMPOTEXTO**************/

int Pig_CampoTexto_CriaCampoTexto(int idForm,int x, int y, int altura,int largura,char* nomeArq,int maxCars = 200, bool apenasNumeros=false, int retiraFundo=1){
    return CGerenciadorForms::CriaCampoTextoESenha(idForm,x,y,altura,largura,nomeArq,maxCars,apenasNumeros,retiraFundo,false);
}

void Pig_CampoTexto_SetMargens(int idComponente,int horEsq,int horDir, int vertBaixo,int vertCima){
    ((CPigCampoTextoESenha*)CGerenciadorForms::GetComponente(idComponente))->SetMargens(horEsq,horDir,vertBaixo,vertCima);
}

void Pig_CampoTexto_SetTexto(int idComponente,char* frase){
    ((CPigCampoTextoESenha*)CGerenciadorForms::GetComponente(idComponente))->SetTexto(frase);
}

void Pig_CampoTexto_SetFonteTexto(int idComponente,int fonte){
    ((CPigCampoTextoESenha*)CGerenciadorForms::GetComponente(idComponente))->SetFonteTexto(fonte);
}

void Pig_CampoTexto_SetCorCursor(int idComponente,PIG_Cor cor){
    ((CPigCampoTextoESenha*)CGerenciadorForms::GetComponente(idComponente))->SetCorCursor(cor);
}

/**********CAMPOSENHA**************/

int Pig_CampoSenha_CriaCampoSenha(int idForm,int x, int y, int altura,int largura,char* nomeArq,int maxCars = 200, bool apenasNumeros=false, int retiraFundo=1){
    return CGerenciadorForms::CriaCampoTextoESenha(idForm,x,y,altura,largura,nomeArq,maxCars,apenasNumeros,retiraFundo,true);
}

void Pig_CampoSenha_SetMargens(int idComponente,int horEsq,int horDir, int vertBaixo,int vertCima){
    ((CPigCampoTextoESenha*)CGerenciadorForms::GetComponente(idComponente))->SetMargens(horEsq,horDir,vertBaixo,vertCima);
}

void Pig_CampoSenha_SetTexto(int idComponente,char* frase){
    ((CPigCampoTextoESenha*)CGerenciadorForms::GetComponente(idComponente))->SetTexto(frase);
}

void Pig_CampoSenha_SetFonteTexto(int idComponente,int fonte){
    ((CPigCampoTextoESenha*)CGerenciadorForms::GetComponente(idComponente))->SetFonteTexto(fonte);
}

void Pig_CampoSenha_SetCorCursor(int idComponente,PIG_Cor cor){
    ((CPigCampoTextoESenha*)CGerenciadorForms::GetComponente(idComponente))->SetCorCursor(cor);
}

/**********LISTA**************/

int Pig_Lista_CriaLista(int idForm,int x, int y,int altura,int largura,int alturaItens,char* nomeArq,int retiraFundo=1){
    return CGerenciadorForms::CriaLista(idForm,x,y,altura,largura,alturaItens,nomeArq,retiraFundo);
}

int Pig_Lista_CriaItem(int idComponente,char* texto,char* imagem = "",int largImg = 0,int retiraFundoImg = 1){
    ((CPigLista*)CGerenciadorForms::GetComponente(idComponente))->CriaItem(texto,imagem,largImg,retiraFundoImg);
}

/**********DROPDOWN**************/

int Pig_DropDown_CriaDropDown(int idForm,int x, int y, int altura,int largura,int alturaLista,char* nomeArq,char* fundoLista,int retiraFundoLista,int retiraFundo=1){
    return CGerenciadorForms::CriaDropDown(idForm,x,y,altura,largura,alturaLista,nomeArq,fundoLista,retiraFundoLista,retiraFundo);
}

int Pig_DropDown_CriaItem(int idComponente,char* texto,char* imagem = "",int largImg = 0,int retiraFundoImg = 1){
    return ((CPigDropDown*)CGerenciadorForms::GetComponente(idComponente))->CriaItem(texto,imagem,largImg,retiraFundoImg);
}

/**********GAUGE**************/

int Pig_Gauge_CriaGauge(int idForm,int x, int y,int altura,int largura,char* imgGauge,int retiraFundo=1){
    return CGerenciadorForms::CriaGauge(idForm,x,y,altura,largura,imgGauge,retiraFundo);
}

void Pig_Gauge_SetFrames(int idComponente,SDL_Rect fBase,SDL_Rect fBarra){
    ((CPigGauge*)CGerenciadorForms::GetComponente(idComponente))->SetFrames(fBase,fBarra);
}

void Pig_Gauge_SetDelta(int idComponente,float valor){
    ((CPigGauge*)CGerenciadorForms::GetComponente(idComponente))->SetDelta(valor);
}

void Pig_Gauge_AvancaDelta(int idComponente){
    ((CPigGauge*)CGerenciadorForms::GetComponente(idComponente))->AvancaDelta();
}

float Pig_Gauge_GetPorcentagemConcluida(int idComponente){
    return ((CPigGauge*)CGerenciadorForms::GetComponente(idComponente))->GetPorcentagemConcluida();
}

void Pig_Gauge_ZeraValor(int idComponente){
    ((CPigGauge*)CGerenciadorForms::GetComponente(idComponente))->ZeraValor();
}

/**********GAUGECIRCULAR**************/

int Pig_GaugeCircular_CriaGaugeCircular(int idForm,int x, int y,int altura,int largura,int raioInterior,char* imgGauge,int retiraFundo=1){
    return CGerenciadorForms::CriaGaugeCircular(idForm,x,y,altura,largura,raioInterior,imgGauge,retiraFundo);
}

/**********RADIOBOX**************/

int Pig_RadioBox_CriaRadioBox(int idForm,int x, int y,int larguraImgFundo,char* imagemFundo,char* imagemItem, int alturaItem, int larguraItem, int espacoVertical,int retiraFundo=1){
    return CGerenciadorForms::CriaRadioBox(idForm,x,y,larguraImgFundo,imagemFundo,imagemItem,alturaItem,larguraItem,espacoVertical,retiraFundo);
}

void Pig_RadioBox_CriaItem(int idComponente,char* itemLabel, bool itemHabilitado = true, int audio=-1,char* hintMsg="", int retiraFundo=1){
    ((CPigRadioBox*)CGerenciadorForms::GetComponente(idComponente))->CriaItem(itemLabel,itemHabilitado,audio,hintMsg,retiraFundo);
}

int Pig_RadioBox_GetItemMarcado(int idComponente){
    return ((CPigRadioBox*)CGerenciadorForms::GetComponente(idComponente))->GetMarcado();
}

int Pig_RadioBox_SetItemMarcado(int idComponente,int item, bool marcado){
    return ((CPigRadioBox*)CGerenciadorForms::GetComponente(idComponente))->SetMarcado(item,marcado);
}

int Pig_RadioBox_GetEstadoMarcadoItem(int idComponente,int item){
    return ((CPigRadioBox*)CGerenciadorForms::GetComponente(idComponente))->GetMarcadoItem(item);
}

int Pig_RadioBox_SetAudioItem(int idComponente,int item,int audio){
    return ((CPigRadioBox*)CGerenciadorForms::GetComponente(idComponente))->SetAudioItem(item,audio);
}

int Pig_RadioBox_GetEstadoHabilitadoItem(int idComponente,int item){
    return ((CPigRadioBox*)CGerenciadorForms::GetComponente(idComponente))->GetHabilitadoItem(item);
}

int Pig_RadioBox_SetEstadoHabilitadoItem(int idComponente,int item,bool habilitado){
    return ((CPigRadioBox*)CGerenciadorForms::GetComponente(idComponente))->SetHabilitadoItem(item,habilitado);
}

void Pig_RadioBox_SetEstadoHabilitadoItens(int idComponente,bool habilitado){
    return ((CPigRadioBox*)CGerenciadorForms::GetComponente(idComponente))->SetHabilitado(habilitado);
}

/**********CHECKBOX**************/

int Pig_CheckBox_CriaCheckBox(int idForm,int x, int y,int larguraImgFundo,char* imagemFundo,char* imagemItem, int alturaItem, int larguraItem, int espacoVertical,int retiraFundo=1){
    return CGerenciadorForms::CriaCheckBox(idForm,x,y,larguraImgFundo,imagemFundo,imagemItem,alturaItem,larguraItem,espacoVertical,retiraFundo);
}

void Pig_CheckBox_CriaItem(int idComponente,char* itemLabel,bool itemMarcado = false, bool itemHabilitado = true, int audio=-1, std::string hintMsg="", int retiraFundo=1){
    ((CPigCheckBox*)CGerenciadorForms::GetComponente(idComponente))->CriaItem(itemLabel,itemMarcado,itemHabilitado,audio,hintMsg,retiraFundo);
}

void Pig_CheckBox_SetMarcadoTodos(int idComponente,bool marcado){
    ((CPigCheckBox*)CGerenciadorForms::GetComponente(idComponente))->SetMarcadoTodos(marcado);
}

int Pig_CheckBox_SetMarcadoItem(int idComponente,int indice,bool marcado){
    return ((CPigCheckBox*)CGerenciadorForms::GetComponente(idComponente))->SetMarcadoItem(indice,marcado);
}

std::vector <int> Pig_CheckBox_GetItensMarcados(int idComponente){
    return ((CPigCheckBox*)CGerenciadorForms::GetComponente(idComponente))->GetItensMarcados();
}

int Pig_CheckBox_GetMarcadoItem(int idComponente,int item){
    return ((CPigCheckBox*)CGerenciadorForms::GetComponente(idComponente))->GetMarcadoItem(item);
}

int Pig_CheckBox_SetAudioItem(int idComponente,int item,int audio){
    return ((CPigCheckBox*)CGerenciadorForms::GetComponente(idComponente))->SetAudioItem(item,audio);
}

int Pig_CheckBox_GetHabilitadoItem(int idComponente,int item){
    return ((CPigCheckBox*)CGerenciadorForms::GetComponente(idComponente))->GetHabilitadoItem(item);
}

int Pig_CheckBox_SetHabilitadoItem(int idComponente,int item,bool habilitado){
    return ((CPigCheckBox*)CGerenciadorForms::GetComponente(idComponente))->SetHabilitadoItem(item,habilitado);
}

void Pig_CheckBox_SetHabilitado(int idComponente,bool habilitado){
    return ((CPigCheckBox*)CGerenciadorForms::GetComponente(idComponente))->SetHabilitado(habilitado);
}

/********************************/
