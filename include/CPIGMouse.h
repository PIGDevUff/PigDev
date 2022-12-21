#ifndef _CPIGMouse_
#define _CPIGMouse_

#include "CPIGSprite.h"

class CPIGMouse{

private:

    PIGSprite cursores;
    SDL_Point pTela,pWorld;
    int estadoBotaoDireito,estadoBotaoEsquerdo,estadoBotaoCentral;

public:

    CPIGMouse(bool cursorCustomizado=false){
        SDL_ShowCursor(!cursorCustomizado);
        cursores = NULL;
    }

    ~CPIGMouse(){
        if (cursores) delete cursores;
    }

    void SetCustomizado(bool cursorCustomizado){
        SDL_ShowCursor(!cursorCustomizado);
    }

    int GetEstadoBotaoDireito(){
        return estadoBotaoDireito;
    }

    int GetEstadoBotaoCentral(){
        return estadoBotaoCentral;
    }

    int GetEstadoBotaoEsquerdo(){
        return estadoBotaoEsquerdo;
    }

    void PegaXYTela(int &x, int &y){
        x = pTela.x;
        y = pTela.y;
    }

    SDL_Point PegaXYWorld(){
        return pWorld;
    }

    SDL_Point PegaXYTela(){
        return pTela;
    }

    int ProcessaEvento(PIGEvento &evento){
        if (evento.tipoEvento!=PIG_EVENTO_MOUSE) return 0;
        if (evento.mouse.acao==PIG_MOUSE_PRESSIONADO||evento.mouse.acao==PIG_MOUSE_LIBERADO){
            switch(evento.mouse.botao){
            case PIG_MOUSE_DIREITO: estadoBotaoDireito = evento.mouse.acao;break;
            case PIG_MOUSE_CENTRAL: estadoBotaoCentral = evento.mouse.acao;break;
            case PIG_MOUSE_ESQUERDO: estadoBotaoEsquerdo = evento.mouse.acao;break;
            }
        }else if (evento.mouse.acao==PIG_MOUSE_MOVIDO){
            Move(evento.mouse.posX,evento.mouse.posY,evento.mouse.numeroJanela);

        }
        pigGerJanelas.GetElemento(evento.mouse.numeroJanela)->ConverteCoordenadaScreenWorld(pTela.x,pTela.y,pWorld.x,pWorld.y);
        evento.mouse.worldX = pWorld.x;
        evento.mouse.worldY = pWorld.y;
        return 1;
    }

    int GetEstadoBotao(int botao){
        switch(botao){
        case PIG_MOUSE_DIREITO: return estadoBotaoDireito;
        case PIG_MOUSE_CENTRAL: return estadoBotaoCentral;
        case PIG_MOUSE_ESQUERDO: return estadoBotaoEsquerdo;
        }
        return 0;
    }

    int MudaCursor(int indice){
        if (cursores)
            return cursores->MudaFrameAtual(indice);
        return 0;
    }

    void Desenha(int idJanela=0){
        if (cursores) cursores->Desenha();
    }

    void Move(int x,int y, int idJanela=0){
        pTela.x = x;
        pTela.y = y;
        if (cursores) cursores->Move(x,y-32);
    }

    void CarregaCursor(string nomeArquivo, int idJanela=0){
        if (cursores) delete cursores;
        cursores = new CPIGSprite(-1,nomeArquivo,idJanela);
        cursores->SetDimensoes(32,32);
    }

    void CarregaFramesPorColuna(int frameInicial, int qtdLinhas, int qtdColunas){
        if (cursores) cursores->CriaFramesAutomaticosPorColuna(frameInicial,qtdLinhas,qtdColunas);
    }

    void CarregaFramesPorLinha(int frameInicial, int qtdLinhas, int qtdColunas){
        if (cursores) cursores->CriaFramesAutomaticosPorLinha(frameInicial,qtdLinhas,qtdColunas);
    }

    void CriaFrameCursor(int idFrame,int x, int y, int alt, int larg){
        if (cursores) cursores->DefineFrame(idFrame,{x,y,larg,alt});
    }

};
CPIGMouse pigMouse;
#endif // _CPIGMouse_
