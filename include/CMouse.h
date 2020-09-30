#ifndef _CMouse_
#define _CMouse_

#include "CPIGIcone.h"

class CMouse{

private:

    static int cursorAtual;
    static PIGIcone cursores[MAX_CURSORES];
    static bool cursorProprio;
    static SDL_Point p;
    static int estadoBotaoDireito,estadoBotaoEsquerdo,estadoBotaoCentral;

public:

    static void Inicia(bool cursorCustomizado){
        cursorAtual = -1;
        cursorProprio = cursorCustomizado;
        SDL_ShowCursor(cursorProprio==false);
        for (int i=0;i<MAX_CURSORES;i++)
            cursores[i] = NULL;
    }

    static void Encerra(){
        for (int i=0;i<MAX_CURSORES;i++){
            if (cursores[i])
                delete cursores[i];
        }
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

    static SDL_Point PegaXY(){
        return p;
    }

    static int ProcessaEvento(PIG_Evento evento){
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
        return 1;
    }

    static void MudaCursor(int indice){
        cursorAtual = indice;
    }

    static void Desenha(int idJanela=0){
        if (cursorAtual==-1) return;
        cursores[cursorAtual]->Desenha();
    }

    static void Move(int x,int y, int idJanela=0){
        p.x = x;
        p.y = y;
        if (cursorAtual==-1) return;
        cursores[cursorAtual]->Move(x,y-32);
    }

    static void CarregaCursor(int indice,std::string nomeArquivo,int idJanela=0){
        if (cursores[indice]) delete cursores[indice];
        cursores[indice] = new CPIGIcone(nomeArquivo,1,idJanela);
        cursores[indice]->SetDimensoes(32,32);
        if (cursorAtual==-1) cursorAtual=indice;
    }

};

int CMouse::cursorAtual;
bool CMouse::cursorProprio;
PIGIcone CMouse::cursores[MAX_CURSORES];
SDL_Point CMouse::p;
int CMouse::estadoBotaoDireito;
int CMouse::estadoBotaoEsquerdo;
int CMouse::estadoBotaoCentral;

#endif // _CMouse_
