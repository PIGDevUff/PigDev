#ifndef _CPIGMouse_
#define _CPIGMouse_

#include "CPIGSprite.h"

class CPIGMouse{

private:

    static PIGSprite cursores;
    static SDL_Point pTela,pWorld;
    static int estadoBotaoDireito,estadoBotaoEsquerdo,estadoBotaoCentral;

public:

    static void Inicia(bool cursorCustomizado){
        SDL_ShowCursor(!cursorCustomizado);
        cursores = NULL;
    }

    static void Encerra(){
        if (cursores) delete cursores;
    }

    static int GetEstadoBotaoDireito(){
        return estadoBotaoDireito;
    }

    static int GetEstadoBotaoCentral(){
        return estadoBotaoCentral;
    }

    static int GetEstadoBotaoEsquerdo(){
        return estadoBotaoEsquerdo;
    }

    static void PegaXYTela(int &x, int &y){
        x = pTela.x;
        y = pTela.y;
    }

    static SDL_Point PegaXYWorld(){
        return pWorld;
    }

    static SDL_Point PegaXYTela(){
        return pTela;
    }

    static int ProcessaEvento(PIGEvento &evento){
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
        CPIGGerenciadorJanelas::GetJanela(evento.mouse.numeroJanela)->ConverteCoordenadaScreenWorld(pTela.x,pTela.y,pWorld.x,pWorld.y);
        evento.mouse.worldX = pWorld.x;
        evento.mouse.worldY = pWorld.y;
        return 1;
    }

    static int GetEstadoBotao(int botao){
        switch(botao){
        case PIG_MOUSE_DIREITO: return estadoBotaoDireito;
        case PIG_MOUSE_CENTRAL: return estadoBotaoCentral;
        case PIG_MOUSE_ESQUERDO: return estadoBotaoEsquerdo;
        }
        return 0;
    }

    static int MudaCursor(int indice){
        if (cursores)
            return cursores->MudaFrameAtual(indice);
        return 0;
    }

    static void Desenha(int idJanela=0){
        if (cursores) cursores->Desenha();
    }

    static void Move(int x,int y, int idJanela=0){
        pTela.x = x;
        pTela.y = y;
        if (cursores) cursores->Move(x,y-32);
    }

    static void CarregaCursor(std::string nomeArquivo,int idJanela=0){
        if (cursores) delete cursores;
        cursores = new CPIGSprite(-1,nomeArquivo,idJanela);
        cursores->SetDimensoes(32,32);
    }

    static void CarregaFramesPorColuna(int frameInicial, int qtdLinhas, int qtdColunas){
        if (cursores) cursores->CriaFramesAutomaticosPorColuna(frameInicial,qtdLinhas,qtdColunas);
    }

    static void CarregaFramesPorLinha(int frameInicial, int qtdLinhas, int qtdColunas){
        if (cursores) cursores->CriaFramesAutomaticosPorLinha(frameInicial,qtdLinhas,qtdColunas);
    }

    static void CriaFrameCursor(int idFrame,int x, int y, int alt, int larg){
        if (cursores) cursores->DefineFrame(idFrame,{x,y,larg,alt});
    }

};

PIGSprite CPIGMouse::cursores;
SDL_Point CPIGMouse::pTela;
SDL_Point CPIGMouse::pWorld;
int CPIGMouse::estadoBotaoDireito;
int CPIGMouse::estadoBotaoEsquerdo;
int CPIGMouse::estadoBotaoCentral;
#endif // _CPIGMouse_
