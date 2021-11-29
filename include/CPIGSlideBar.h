#ifndef _CPIGSLIDEBAR_
#define _CPIGSLIDEBAR_

#include "CPIGGauge.h"

class CPIGSlideBar: public CPIGGauge{

    int deltaRodinha,deltaTeclado;
    int altMarcador,largMarcador,xMarc,yMarc;

    void ProcessaAtributos(CPIGAtributos atrib)override{
        CPIGGauge::ProcessaAtributos(atrib);
    }

    static CPIGSlideBar LeParametros(int idComponente,CPIGAtributos atrib){
        CPIGSlideBar *resp;

        if (atrib.GetString("nomeArq","")!=""){
            resp = new CPIGSlideBar(idComponente,atrib.GetInt("altura",0),atrib.GetInt("largura",0),
                          atrib.GetString("nomeArq",""),atrib.GetInt("alturaMarcador",0),atrib.GetInt("larguraMarcador",0),atrib.GetString("nomeArqMarcador",""),
                          atrib.GetInt("retiraFundo",1),atrib.GetInt("retiraFundoMarcador",1),atrib.GetInt("janela",0));
        }else{
            resp = new CPIGSlideBar(idComponente,atrib.GetInt("altura",0),atrib.GetInt("largura",0),
                          atrib.GetInt("alturaMarcador",0),atrib.GetInt("larguraMarcador",0),atrib.GetInt("janela",0));
        }

        resp->ProcessaAtributos(atrib);

        return *resp;
    }

    void AtualizaMarcador()override{
        CPIGGauge::AtualizaMarcador();

        switch (orientacaoCrescimento){
        case PIG_GAUGE_ESQ_DIR:
                xMarc = pos.x+(int)(porcentagemConcluida*(larg-largMarcador));
                yMarc = pos.y;
                break;
        case PIG_GAUGE_DIR_ESQ:
                xMarc = pos.x+(int)((1-porcentagemConcluida)*(larg-largMarcador));
                yMarc = pos.y;
                break;
        case PIG_GAUGE_BAIXO_CIMA:
                xMarc = pos.x;
                yMarc = pos.y+(int)(porcentagemConcluida*(alt-altMarcador));
                break;
        case PIG_GAUGE_CIMA_BAIXO:
                xMarc = pos.x;
                yMarc = pos.y+(int)((1-porcentagemConcluida)*(alt-altMarcador));
                break;
        }

        xMarc += margemEsq;
        yMarc += margemBaixo;
        if (marcador){
            //printf("%d,%d  %d %d\n",xMarc,yMarc,altMarcador-(margemBaixo+margemCima),largMarcador-(margemEsq+margemDir));
            marcador->Move(xMarc,yMarc);
            marcador->SetDimensoes(altMarcador-(margemBaixo+margemCima),largMarcador-(margemEsq+margemDir));
        }
    }

    PIGEstadoEvento TrataClickTrilha(int px, int py){
        double perc;
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
        //printf("vou definir perc %f\n",perc);
        SetPorcentagemConcluida(perc);

        return PIG_TRATADO;
    }

    PIGEstadoEvento TrataRodinha(PIGEvento evento){
        if(evento.mouse.relY > 0){
            AvancaMarcador(deltaRodinha);
            return PIG_TRATADO;
        }else if (evento.mouse.relY < 0){
            AvancaMarcador(-deltaRodinha);
            return PIG_TRATADO;
        }
        return PIG_NAOSELECIONADO;
    }

public:

    CPIGSlideBar(int idComponente, int altTrilha, int largTrilha, string imgTrilha, int alturaMarcador, int larguraMarcador, string imgMarcador,int retiraFundoTrilha=1, int retiraFundoMarcador=1, int janela=0):
        CPIGGauge(idComponente,altTrilha,largTrilha,imgTrilha,retiraFundoTrilha,janela){
            deltaTeclado = deltaRodinha = 10;
            altMarcador = alturaMarcador;
            largMarcador = larguraMarcador;
            tipo = PIG_SLIDEBAR;
            marcador = new CPIGSprite(-1,imgMarcador,retiraFundoMarcador,NULL,janela);
            AtualizaMarcador();
    }

    CPIGSlideBar(int idComponente, int altTrilha, int largTrilha, int alturaMarcador, int larguraMarcador,int janela=0):
        CPIGGauge(idComponente,altTrilha,largTrilha,janela){
            deltaTeclado = deltaRodinha = 10;
            altMarcador = alturaMarcador;
            largMarcador = larguraMarcador;
            tipo = PIG_SLIDEBAR;
            AtualizaMarcador();
            IniciaCoresBasicas();
    }

    CPIGSlideBar(int idComponente,CPIGAtributos atrib):CPIGSlideBar(LeParametros(idComponente,atrib)){}

    virtual ~CPIGSlideBar(){}

    PIGEstadoEvento TrataEventoMouse(PIGEvento evento)override{
        if (!habilitado) return PIG_DESABILITADO;
        if (!visivel) return PIG_INVISIVEL;

        SDL_Point p = GetPosicaoMouse();
        ChecaMouseOver(p);

        if (mouseOver){
            if(evento.mouse.acao == PIG_MOUSE_RODINHA)
                return TrataRodinha(evento);

            if(evento.mouse.acao == PIG_MOUSE_PRESSIONADO && evento.mouse.botao == PIG_MOUSE_ESQUERDO)
                return TrataClickTrilha(p.x,p.y);

            if(temFoco && CPIGMouse::GetEstadoBotao(PIG_MOUSE_ESQUERDO)==PIG_MOUSE_PRESSIONADO)
                return TrataClickTrilha(p.x,p.y);

            return PIG_MOUSEOVER;
        }
        return PIG_NAOSELECIONADO;
    }

    PIGEstadoEvento TrataEventoTeclado(PIGEvento evento)override{
        if (!temFoco) return PIG_SEMFOCO;
        if (!habilitado) return PIG_DESABILITADO;
        if (!visivel) return PIG_INVISIVEL;

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
            return PIG_TRATADO;
        }
        return PIG_NAOSELECIONADO;
    }

    void SetDeltas(int dPadrao = 1,int dRodinha = 10,int dTeclado = 10){
        delta = dPadrao;
        deltaRodinha = dRodinha;
        deltaTeclado = dTeclado;
    }

    int SetOrientacao(PIGGaugeCrescimento orientacao){
        if (orientacao==PIG_GAUGE_HORARIO||orientacao==PIG_GAUGE_ANTIHORARIO)
            return 0;

        orientacaoCrescimento = orientacao;
        marcadorAtualizado = false;

        return 1;
    }

    virtual void Desloca(double dx, double dy)override{
        CPIGGauge::Desloca(dx,dy);
        xMarc += dx;
        yMarc += dy;
    }

    virtual void Move(double nx, double ny)override{
        Desloca(nx-pos.x,ny-pos.y);
    }

    int Desenha(){
        if(visivel==false) return 0;

        if (!marcadorAtualizado) AtualizaMarcador();

        CPIGGerenciadorJanelas::GetJanela(idJanela)->BloqueiaArea(pos.x,pos.y,alt,larg);

        if (text)
            CPIGSprite::Desenha();
        else CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetangulo((int)pos.x,(int)pos.y,alt,larg,coresBasicas[0]);

        if (marcador)
            marcador->Desenha();
        else CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetangulo(xMarc,yMarc,altMarcador-(margemBaixo+margemCima),largMarcador-(margemEsq+margemDir),coresBasicas[1]);

        CPIGGerenciadorJanelas::GetJanela(idJanela)->DesbloqueiaArea();

        return CPIGComponente::Desenha();
    }


};
typedef CPIGSlideBar *PIGSlideBar;
#endif // _CPIGSCROLLBAR_
