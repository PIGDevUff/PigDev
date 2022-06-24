#ifndef _CPIGCAMERA_
#define _CPIGCAMERA_

class CPIGCamera{

private:

int altTela,largTela,altAtual,largAtual;
SDL_Point pos;
double pan,minPan,maxPan;

public:

CPIGCamera(int alturaTela, int larguraTela){
    altTela  = altAtual = alturaTela;
    largTela = largAtual = larguraTela;
    pos = {0,0};
    pan = 1.0;
    minPan = PIG_AFASTAMENTO_MINIMO;
    maxPan = PIG_AFASTAMENTO_MAXIMO;
}

SDL_Point GetXY(){
    return pos;
}

//não utilizada
void AjustaTela(int novaAltura, int novaLargura){
    altTela = novaAltura;
    largTela = novaLargura;
    DefineAfastamento(pan);
}

void Move(SDL_Point nova){
    pos = nova;
}

void Desloca(int dx, int dy){
    pos.x += dx;
    pos.y += dy;
}

double DefineAfastamento(double valor){
    pan = PIGLimitaValor(valor,minPan,maxPan);
    largAtual = pan*largTela;
    altAtual = pan*altTela;
    return pan;
}

double GetAfastamento(){
    return pan;
}

void ConverteCoordenadaWorldScreen(int xObj, int yObj, int &cx, int &cy){
    cx = xObj - pos.x + (largAtual-largTela)/2;
    cy = yObj + pos.y + (altAtual-altTela)/2;
}

void ConverteCoordenadaScreenWorld(int xTela, int yTela, int &cx, int &cy){
    double propX = ((double) (xTela-largTela/2)/largTela);
    double propY = ((double) (yTela-altTela/2)/altTela);
    cx = xTela + pos.x + propX*(largAtual-largTela);
    cy = yTela + pos.y + propY*(altAtual-altTela);
}

};
typedef CPIGCamera *PIGCamera;
#endif // _CPIGCAMERA_
