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
    altJanela = CGerenciadorJanelas::GetAltura(idJanela);
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

void Desenha(){
    SDL_RenderCopy(renderer,text,NULL,&dest);
}


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
