#ifndef _CMouse_
#define _CMouse_

#include "CPigSprite.h"

class CMouse{

private:

    //static int cursorAtual;
    static PIGSprite cursores;
    static bool cursorProprio;
    static SDL_Point p,pWorld;
    static int estadoBotaoDireito,estadoBotaoEsquerdo,estadoBotaoCentral;

public:

    static void Inicia(bool cursorCustomizado){
        //cursorAtual = -1;
        cursorProprio = cursorCustomizado;
        SDL_ShowCursor(cursorProprio==false);
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

    static void PegaXY(int &x, int &y){
        x = p.x;
        y = p.y;
    }

    static SDL_Point PegaXYWorld(){
        return pWorld;
    }

    static SDL_Point PegaXY(){
        return p;
    }

    static int ProcessaEvento(PIG_Evento &evento){
        if (evento.tipoEvento!=EVENTO_MOUSE) return 0;
        if (evento.mouse.acao==MOUSE_PRESSIONADO||evento.mouse.acao==MOUSE_LIBERADO){
            switch(evento.mouse.botao){
            case MOUSE_DIREITO: estadoBotaoDireito = evento.mouse.acao;break;
            case MOUSE_CENTRAL: estadoBotaoCentral = evento.mouse.acao;break;
            case MOUSE_ESQUERDO: estadoBotaoEsquerdo = evento.mouse.acao;break;
            }
        }else if (evento.mouse.acao==MOUSE_MOVIDO){
            Move(evento.mouse.posX,evento.mouse.posY,evento.mouse.numeroJanela);

        }
        CGerenciadorJanelas::GetJanela(evento.mouse.numeroJanela)->ConverteCoordenadaScreenWorld(p.x,p.y,pWorld.x,pWorld.y);
        evento.mouse.worldX = pWorld.x;
        evento.mouse.worldY = pWorld.y;
        return 1;
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
        p.x = x;
        p.y = y;
        if (cursores) cursores->Move(x,y-32);
        //if (cursorAtual==-1) return;
        //cursores[cursorAtual]->Move(x,y-32);
    }

    static void CarregaCursor(std::string nomeArquivo,int idJanela=0){
        if (cursores) delete cursores;
        cursores = new CPigSprite(nomeArquivo,idJanela);
        cursores->SetDimensoes(32,32);
        //if (cursores[indice]) delete cursores[indice];
        //cursores[indice] = new CPigVisual(nomeArquivo,1,NULL,idJanela);
        //cursores[indice]->SetDimensoes(32,32);
        //if (cursorAtual==-1) cursorAtual=indice;
    }

    static void DefineFrameCursor(int idFrame,int x, int y, int alt, int larg){
        if (cursores) cursores->DefineFrame(idFrame,{x,y,larg,alt});
    }

};

//int CMouse::cursorAtual;
bool CMouse::cursorProprio;
PIGSprite CMouse::cursores;
SDL_Point CMouse::p;
SDL_Point CMouse::pWorld;
int CMouse::estadoBotaoDireito;
int CMouse::estadoBotaoEsquerdo;
int CMouse::estadoBotaoCentral;

#endif // _CMouse_
