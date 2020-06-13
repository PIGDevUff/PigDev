PIG_Cor MixCor(PIG_Cor iniCor, PIG_Cor fimCor, double porc){
    PIG_Cor resp;
    resp.r = fimCor.r*porc + (iniCor.r)*(1-porc);
    resp.g = fimCor.g*porc + (iniCor.g)*(1-porc);
    resp.b = fimCor.b*porc + (iniCor.b)*(1-porc);
    resp.a = fimCor.a*porc + (iniCor.a)*(1-porc);
    return resp;
}


class CPigGaugeCircular:public CPigComponente{

private:

    double angBase,deltaAng;
    int raioInterno;
    PIG_Cor corInicial,corFinal,corFundo;
    OffscreenRenderer off;
    bool crescimentoHorario;
    int valor,valorMin,valorMax;
    double porcentagemConcluida;
    SDL_Texture *textFundo;
    void DefineEstado(PIG_EstadoComponente estadoComponente){}
    int OnMouseOn(){return 0;}
    int OnMouseOff(){return 0;}
    int TrataEvento(PIG_Evento evento){return 0;}

public:

CPigGaugeCircular(int idComponente,int px, int py,int altura,int largura,int raioInterior,int janela=0):
    CPigComponente(idComponente,px,py,altura,largura,janela){

    angBase = 0;
    deltaAng = 360;
    raioInterno = raioInterior;
    valor = 40;
    valorMin = 0;
    valorMax = 100;
    porcentagemConcluida = 0.4;
    corInicial = corFinal = LARANJA;
    corFundo = PRETO;
    off = new COffscreenRenderer(altura,largura,3);

    Move(px,py);
    SetPivo(larg/2,alt/2);
    textFundo = NULL;
    AtualizaTextura();
    AtualizaTexturaFundo();
    crescimentoHorario=true;
}

~CPigGaugeCircular(){
    delete off;
}

void SetRaioInterno(int valorRaio){
    if (valorRaio<0||valorRaio>0.9*larg/2) return;

    raioInterno = valorRaio;
    printf("atualizei %d\n",raioInterno);
    AtualizaTextura();
    AtualizaTexturaFundo();
}

void SetAnguloBase(double novoAng){
    angBase = novoAng;
}

void SetDeltaAngulo(double novoDelta){
    deltaAng = novoDelta;
    AtualizaTextura();
    AtualizaTexturaFundo();
}

void IncrementaValor(int delta){
    valor+=delta;
    //printf("novo valor %d\n",valor);
    if (valor>valorMax) valor=valorMax;
    if (valor<valorMin) valor=valorMin;
    porcentagemConcluida = 1.*(valor-valorMin)/(valorMax-valorMin);
    AtualizaTextura();
}

void SetValorMax(int novoValor){
    if (novoValor<=valorMin)return;
    valorMax = novoValor;
    if (valor>valorMax) valor = valorMax;
    porcentagemConcluida = 1.*(valor-valorMin)/(valorMax-valorMin);
    AtualizaTextura();
}

void SetValorMin(int novoValor){
    if (novoValor>=valorMax) return;
    valorMin = novoValor;
    if (valor<valorMin) valor=valorMin;
    porcentagemConcluida = 1.*(valor-valorMin)/(valorMax-valorMin);
    AtualizaTextura();
}

void SetCorInicial(PIG_Cor cor){
    corInicial = cor;
    AtualizaTextura();
}

void SetCorFinal(PIG_Cor cor){
    corFinal = cor;
    AtualizaTextura();
}

int GetValor(){
    return valor;
}

std::string GetValorString(){
    std::stringstream ss;
    ss <<valor;
    return ss.str();
}

int GetValorMax(){
    return valorMax;
}

int GetValorMin(){
    return valorMin;
}

void AtualizaValor(int novoValor){
    if (valor==novoValor) return;
    valor = novoValor;
    AtualizaTextura();
}

void AtualizaTextura(){
    off->LimpaLayer(0,VERDE);
    off->DesenhaCirculo(raioInterno,95,MixCor(corInicial,corFinal,porcentagemConcluida*(deltaAng)),porcentagemConcluida*(deltaAng),true,0);
    off->SetCorTransparente(0,valor>0,VERDE);
    //off->SalvarImagemPNG("circulo0.png",0);
    bitmap = off->GetSurface(0);
    CriaTextura(1);
}

void AtualizaTexturaFundo(){
    off->LimpaLayer(1,VERDE);
    off->DesenhaCirculo(raioInterno,95,corFundo,deltaAng,true,1);
    off->SetCorTransparente(1,true,VERDE);
    off->SalvarImagemPNG("circulo1.png",1);
    //if (textFundo) SDL_DestroyTexture(textFundo);
    textFundo = SDL_CreateTextureFromSurface(renderer,off->GetSurface(1));
}

int Desenha(){
    //if (text) printf("%d, %d, %d, %d\n",dest.x,dest.y,dest.w,dest.h);
    if (crescimentoHorario)
        angulo = angBase;
    else angulo = floor(angBase+porcentagemConcluida*deltaAng);
    SDL_RenderCopyEx(renderer,textFundo,NULL,&dest,-angulo,&pivoRelativo,flip);
    SDL_RenderCopyEx(renderer,text,NULL,&dest,-angulo,&pivoRelativo,flip);

    DesenhaLabel();
}

};

typedef CPigGaugeCircular *PigGaugeCircular;
