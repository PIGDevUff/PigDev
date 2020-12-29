class CPigLabel:public CPigVisual{

private:
std::string frase;
int fonte;
PIG_Cor cor;

void AtualizaTextura(){
    MapaCaracteres mapa = CGerenciadorFontes::GetFonte(fonte);
    larg = mapa->GetLarguraPixelsString(frase);
    alt = mapa->GetFonteAscent()+mapa->GetFonteDescent()+5;
    if (text) SDL_DestroyTexture(text);
    text = SDL_CreateTexture(CGerenciadorJanelas::GetJanela(idJanela)->GetRenderer(),SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,larg,alt);
    mapa->Escreve(frase,text,cor);
    dest.w = larg;
    dest.h = alt;
    frame.x = frame.y = 0;
    frame.h = alt;
    frame.w = larg;
    altJanela = CGerenciadorJanelas::GetJanela(idJanela)->GetAltura();
    //printf("atual %d\n",*altJanela);
}

public:

CPigLabel(std::string texto,int numFonte,PIG_Cor corFonte=BRANCO,int idJanela=0):CPigVisual(idJanela){
    renderer = CGerenciadorJanelas::GetJanela(idJanela)->GetRenderer();
    fonte = numFonte;
    text = NULL;
    cor = corFonte;
    frase = texto;
    AtualizaTextura();
}

//void Desenha(){
    //SDL_RenderCopy(renderer,text,NULL,&dest);
    //AtualizaTextura();
    //printf("desenha %d\n",*altJanela);
    //if (text==NULL) printf("erro\n");
//    CPigVisual::Desenha();
//}


void SetTexto(std::string texto){
    frase = texto;
    AtualizaTextura();
}

void SetFonte(int numFonte){
    fonte = numFonte;
    AtualizaTextura();
}

void SetCor(PIG_Cor novaCor){
    cor = novaCor;
    AtualizaTextura();
}

int GetAltura(){
    return alt;
}

int GetLargura(){
    return larg;
}

std::string GetTexto(){
    return frase;
}

int GetFonte(){
    return fonte;
}

PIG_Cor GetCor(){
    return cor;
}

};

typedef CPigLabel* PigLabel;
