#ifndef _CPIGGAUGECIRCULAR_
#define _CPIGGAUGECIRCULAR_

#include "CPIGGauge.h"

class CPIGGaugeCircular:public CPIGGauge{

private:

    double angBase,deltaAng;
    int raioInterno;
    bool crescimentoHorario;
    PIG_Cor corInicial,corFinal,corInterna;

    CPIGGaugeCircular LeParametros(int idComponente,string parametros){
        CPIGAtributos atrib = CPIGComponente::GetAtributos(parametros);

        CPIGGaugeCircular resp(idComponente,atrib.GetInt("px",0),atrib.GetInt("py",0),atrib.GetInt("altura",0),atrib.GetInt("largura",0),
                          atrib.GetInt("raioInterior",0),atrib.GetInt("janela",0));

        return resp;
    }

    virtual void AtualizaMarcador()override{
        //printf("porc conc %.1f\n",porcentagemConcluida);

        PIGOffscreenRenderer off = new CPIGOffscreenRenderer(alt,larg,2);

        PIG_Cor cor = PIGMixCor(corInicial,corFinal,porcentagemConcluida);//cor da barra mizada entre a cor inicial e a final

        off->Ativa();
        PIGDesenhaCirculo(larg/2,alt/2,larg/2,angBase,porcentagemConcluida*(deltaAng)+angBase,cor);
        PIGDesenhaCirculo(larg/2,alt/2,raioInterno,0,360,corInterna);
        off->Desativa();

        if (bitmap){
            SDL_FreeSurface(bitmap);
            LiberaTextura();
        }
        bitmap = off->GetSurface();
        //SDL_SaveBMP(bitmap,"gauge.bmp");
        SDL_SetColorKey(bitmap,SDL_TRUE,0);
        idTextura = PIGCriaTexturaSurface(bitmap,true);
        delete off;

        CPIGGerenciadorJanelas::GetJanela(idJanela)->Atualiza();

        if (crescimentoHorario==true) SetFlip(PIG_FLIP_VERTICAL);

        OnAction();
    }

public:

    CPIGGaugeCircular(int idComponente,int px, int py,int altura,int largura,int raioInterior,int janela=0):
        CPIGGauge(idComponente,px,py,altura,largura,janela){

        angBase = 0;
        deltaAng = 360;
        raioInterno = raioInterior;
        crescimentoHorario=true;

        corInicial = corFinal = BRANCO;
        corInterna = PRETO;

        SetPivoProporcional({larg/2.0,alt/2.0});

        AtualizaMarcador();
    }

    /*CPIGGaugeCircular(int idComponente,int px, int py,int altura,int largura,int raioInterior,std::string nomeArq,int retiraFundo=1,int janela=0):
        CPIGComponente(idComponente,px,py,altura,largura,nomeArq,retiraFundo,janela){

        angBase = 0;
        deltaAng = 360;
        raioInterno = raioInterior;
        valor = 0;
        valorMin = 0;
        valorMax = 100;
        porcentagemConcluida = 0.0;
        corInicial = corFinal = LARANJA;
        corFundo = PRETO;

        Move(px,py);
        SetPivoProporcional({larg/2.0,alt/2.0});

        AtualizaTextura();
        crescimentoHorario=true;
    }*/

    CPIGGaugeCircular(int idComponente,string parametros):CPIGGaugeCircular(LeParametros(idComponente,parametros)){}

    int Desenha(){
        CPIGImagem::Desenha();

        DesenhaLabel();

        EscreveHint();

        return 1;
    }

    void SetRaioInterno(int valorRaio){
        if (valorRaio<0||valorRaio>0.9*larg/2) return;

        raioInterno = valorRaio;
        AtualizaMarcador();
    }

    void SetAnguloBase(double novoAng){
        angBase = novoAng;
        AtualizaMarcador();
    }

    void SetDeltaAngulo(double novoDelta){
        deltaAng = novoDelta;
        AtualizaMarcador();
    }

    void SetCorInicial(PIG_Cor cor){
        corInicial = cor;
        AtualizaMarcador();
    }

    void SetCorFinal(PIG_Cor cor){
        corFinal = cor;
        AtualizaMarcador();
    }

    void SetCorInterna(PIG_Cor cor){
        corInterna = cor;
        AtualizaMarcador();
    }

    int TrataEventoMouse(PIG_Evento evento){
        return 0;
    }

    int TrataEventoTeclado(PIG_Evento evento){
        return 0;
    }

};

typedef CPIGGaugeCircular *PIGGaugeCircular;
#endif // _CPIGGAUGECIRCULAR_
