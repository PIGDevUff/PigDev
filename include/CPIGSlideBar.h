#ifndef _CPIGSLIDEBAR_
#define _CPIGSLIDEBAR_

#include "CPIGGauge.h"

class CPIGSlideBar : public CPIGGauge{

    int deltaRodinha,deltaTeclado;

    CPIGSlideBar LeParametros(int idComponente,string parametros){
        CPIGAtributos atrib = CPIGComponente::GetAtributos(parametros);

        CPIGSlideBar resp(idComponente,atrib.GetInt("px",0),atrib.GetInt("py",0),atrib.GetInt("altura",0),atrib.GetInt("largura",0),
                          atrib.GetString("nomeArq",""),atrib.GetInt("alturaMarcador",0),atrib.GetInt("larguraMarcador",0),atrib.GetString("nomeArqMarcador",""),
                          atrib.GetInt("retiraFundo",1),atrib.GetInt("retiraFundoMarcador",1),atrib.GetInt("janela",0));

        return resp;
    }

    void AtualizaMarcador()override{
        int altMarcador,largMarcador;
        marcador->GetDimensoes(altMarcador,largMarcador);

        switch (orientacaoCrescimento){
        case PIG_GAUGE_ESQ_DIR:
                marcador->Move(pos.x+(int)(porcentagemConcluida*(larg-largMarcador)),pos.y);
                break;
        case PIG_GAUGE_DIR_ESQ:
                marcador->Move(pos.x+(int)((1-porcentagemConcluida)*(larg-largMarcador)),pos.y);
                break;
        case PIG_GAUGE_BAIXO_CIMA:
                marcador->Move(pos.x,pos.y+(int)(porcentagemConcluida*(alt-altMarcador)));
                break;
        case PIG_GAUGE_CIMA_BAIXO:
                marcador->Move(pos.x,pos.y+(int)((1-porcentagemConcluida)*(alt-altMarcador)));
                break;
        }

        OnAction();
    }

    int TrataClickTrilha(int px,int py){
        int altMarcador,largMarcador;
        double perc;
        marcador->GetDimensoes(altMarcador,largMarcador);

        px = PIGLimitaValor(px,(int)pos.x+largMarcador/2,(int)pos.x+larg-largMarcador/2);
        py = PIGLimitaValor(py,(int)pos.y+altMarcador/2,(int)pos.y+alt-altMarcador/2);

        switch(orientacaoCrescimento){
        case PIG_GAUGE_ESQ_DIR:
            perc = 1.0*(px-(pos.x+largMarcador/2))/(larg-largMarcador);
            break;
        case PIG_GAUGE_DIR_ESQ:
            perc = 1.0 - 1.0*(px-(pos.x+largMarcador/2))/(larg-largMarcador);
            break;
        case PIG_GAUGE_BAIXO_CIMA:
            perc = 1.0*(py-(pos.y+altMarcador/2))/(alt-altMarcador);
            break;
        case PIG_GAUGE_CIMA_BAIXO:
            perc = 1.0 - 1.0*(py-(pos.y+altMarcador/2))/(alt-altMarcador);
            break;
        }

        SetPorcentagemConcluida(perc);

        return PIG_SELECIONADO_TRATADO;
    }

    int TrataRodinha(PIG_Evento evento){
        if(evento.mouse.relY > 0){
            AvancaMarcador(deltaRodinha);
            return PIG_SELECIONADO_TRATADO;
        }else if (evento.mouse.relY < 0){
            AvancaMarcador(-deltaRodinha);
            return PIG_SELECIONADO_TRATADO;
        }
        return PIG_NAO_SELECIONADO;
    }

public:

    CPIGSlideBar(int idComponente,int px, int py,int altTrilha, int largTrilha, std::string imgTrilha, int altMarcador, int largMarcador, std::string imgMarcador,int retiraFundoTrilha=1, int retiraFundoMarcador=1,int janela=0):
        CPIGGauge(idComponente,px,py,altTrilha,largTrilha,imgTrilha,altMarcador,largMarcador,imgMarcador,retiraFundoTrilha,retiraFundoMarcador,janela){
            deltaTeclado = deltaRodinha = 10;
            marcador = new CPIGImagem(-1,imgMarcador,retiraFundoMarcador,NULL,janela);
            AtualizaMarcador();
    }

    CPIGSlideBar(int idComponente,string parametros):CPIGSlideBar(LeParametros(idComponente,parametros)){}

    ~CPIGSlideBar(){
        delete marcador;
    }

    int TrataEventoMouse(PIG_Evento evento){
        SDL_Point p = GetPosicaoMouse();
        ChecaMouseOver(p);

        if (mouseOver){
            if(evento.mouse.acao == PIG_MOUSE_RODINHA) return TrataRodinha(evento);
            if(evento.mouse.acao == PIG_MOUSE_PRESSIONADO && evento.mouse.botao == PIG_MOUSE_ESQUERDO ){
                return TrataClickTrilha(p.x,p.y);
            }
            return PIG_SELECIONADO_MOUSEOVER;
        }
        return PIG_NAO_SELECIONADO;
    }

    int TrataEventoTeclado(PIG_Evento evento){
        if (!temFoco) return 0;
        if(evento.teclado.acao == PIG_TECLA_PRESSIONADA){
            switch(orientacaoCrescimento){
            case PIG_GAUGE_ESQ_DIR:
                if(evento.teclado.tecla == PIG_TECLA_DIREITA) AvancaMarcador(deltaTeclado);
                if(evento.teclado.tecla == PIG_TECLA_ESQUERDA) AvancaMarcador(-deltaTeclado);
                break;
            case PIG_GAUGE_DIR_ESQ:
                if(evento.teclado.tecla == PIG_TECLA_DIREITA) AvancaMarcador(-deltaTeclado);
                if(evento.teclado.tecla == PIG_TECLA_ESQUERDA) AvancaMarcador(deltaTeclado);
                break;
            case PIG_GAUGE_BAIXO_CIMA:
                if(evento.teclado.tecla == PIG_TECLA_CIMA) AvancaMarcador(deltaTeclado);
                if(evento.teclado.tecla == PIG_TECLA_BAIXO) AvancaMarcador(-deltaTeclado);
                break;
            case PIG_GAUGE_CIMA_BAIXO:
                if(evento.teclado.tecla == PIG_TECLA_CIMA) AvancaMarcador(-deltaTeclado);
                if(evento.teclado.tecla == PIG_TECLA_BAIXO) AvancaMarcador(deltaTeclado);
                break;
            }
            return PIG_SELECIONADO_TRATADO;
        }
        return PIG_NAO_SELECIONADO;
    }

    void SetDeltas(int dPadrao = 1,int dRodinha = 10,int dTeclado = 10){
        delta = dPadrao;
        deltaRodinha = dRodinha;
        deltaTeclado = dTeclado;
    }

    int Desenha(){
        if(visivel==false) return -1;

        CPIGImagem::Desenha();

        marcador->Desenha();

        DesenhaLabel();

        EscreveHint();

        return 0;
    }


};
typedef CPIGSlideBar *PIGSlideBar;
#endif // _CPIGSCROLLBAR_
