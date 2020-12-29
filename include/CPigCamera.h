#ifndef _CPIGCAMERA_
#define _CPIGCAMERA_

class CPigCamera{

private:

int x,y,altTela,largTela,altAtual,largAtual;
float zoom,minZoom,maxZoom;

public:

CPigCamera(int alturaTela, int larguraTela){
    x = y = 0;
    altTela  = altAtual = alturaTela;
    largTela = largAtual = larguraTela;
    zoom = 1.0f;
    minZoom = 0.1f;
    maxZoom = 100.0f;
    //AjustaTela(alturaTela,larguraTela);
}

int GetX(){
    return x;
}

int GetY(){
    return y;
}

void AjustaTela(int novaAltura, int novaLargura){
    altTela = novaAltura;
    largTela = novaLargura;
    SetZoom(zoom);
}

void Move(int nx, int ny){
    x = nx;
    y = ny;
}

void Desloca(int dx,int dy){
    x += dx;
    y += dy;
}

float SetZoom(float novoZoom){
    zoom = PIGLimitaValor(novoZoom,minZoom,maxZoom);
    largAtual = zoom*largTela;
    altAtual = zoom*altTela;
    return zoom;
}

void ConverteCoordenadaWorldScreen(int xObj, int yObj, int &cx, int &cy){
    cx = xObj - x + (largAtual-largTela)/2;
    cy = yObj + y + (altAtual-altTela)/2;
}

void ConverteCoordenadaScreenWorld(int xTela, int yTela, int &cx, int &cy){
    float propX = ((float) (xTela-largTela/2)/largTela);
    float propY = ((float) (yTela-altTela/2)/altTela);
    cx = xTela + x + propX*(largAtual-largTela);
    cy = yTela + y + propY*(altAtual-altTela);
}

};
typedef CPigCamera *PigCamera;
#endif // _CPIGCAMERA_
