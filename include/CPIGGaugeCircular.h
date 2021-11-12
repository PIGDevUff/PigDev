#ifndef _CPIGGAUGECIRCULAR_
#define _CPIGGAUGECIRCULAR_

#include "CPIGGauge.h"

class CPIGGaugeCircular:public CPIGGauge{

private:

    double angBase,deltaAng;
    int raioInterno;
    bool crescimentoHorario;
    PIGOffscreenRenderer off;

    void ProcessaAtributos(CPIGAtributos atrib)override{
        CPIGGauge::ProcessaAtributos(atrib);

        int valorFloat = atrib.GetFloat("anguloBase",0);
        if (valorFloat != 0) SetAnguloBase(valorFloat);

        valorFloat = atrib.GetFloat("deltaAngulo",0);
        if (valorFloat != 0) SetDeltaAngulo(valorFloat);

        int valorInt = atrib.GetInt("horario",0);
        if (valorInt) SetCrescimentoHorario(valorInt);
    }

    static CPIGGaugeCircular LeParametros(int idComponente, CPIGAtributos atrib){
        CPIGGaugeCircular *resp = new CPIGGaugeCircular(idComponente,atrib.GetInt("px",0),atrib.GetInt("py",0),atrib.GetInt("altura",0),atrib.GetInt("largura",0),
                          atrib.GetInt("raioInterno",0),atrib.GetInt("janela",0));

        resp->ProcessaAtributos(atrib);

        return *resp;
    }

    virtual void AtualizaMarcador()override{
        //PIGCor corBarra = PIGMixCor(coresBasicas[1],coresBasicas[2],porcentagemConcluida);//cor da barra mizada entre a cor inicial e a final
        //coresBasicas[3] é a cor a ser utilizada no marcador

        CPIGGauge::AtualizaMarcador();
        PIGCor opcoes[4] = {VERDE,AZUL,ROXO,LARANJA}; //4 cores quaisquer
        PIGCor croma1, croma2; //cores usada como cromakey para transparencias (não podem ser nem a cor da barra, nem a cor do fundo)

        //escolha das cores
        int i=0;
        croma1=opcoes[i];
        while (PIGCoresIguais(croma1,coresBasicas[3])||PIGCoresIguais(croma1,coresBasicas[0])){//não pode ser a cor da barra nem do fundo
            croma1=opcoes[++i];
        }
        croma2=opcoes[i];
        while (PIGCoresIguais(croma2,coresBasicas[3])||PIGCoresIguais(croma2,coresBasicas[0])||PIGCoresIguais(croma2,croma1)){//não pode ser a cor da barra, nem do fundo, nem a cor croma1
            croma2=opcoes[++i];
        }

        //circulo interno para criar efeito de coroa circular
        off->DesenhaCirculoFinal(raioInterno,croma2,croma1,0,360.0,2);
        off->SetCorTransparente(2,true,croma2);
        //off->SalvarImagemPNG("interno.png",2);

        //circulo com a barra na cor desejada
        off->DesenhaCirculoFinal(larg/2-2,croma1,coresBasicas[3],angBase,porcentagemConcluida*(deltaAng)+angBase,0);
        off->SetCorTransparente(0,true,croma1);
        //off->SalvarImagemPNG("barra.png",0);

        //criculo com o fundo na cor de fundo
        off->DesenhaCirculoFinal(larg/2-2,croma1,coresBasicas[0],angBase,angBase+deltaAng,1);
        off->SetCorTransparente(1,true,croma1);
        //off->SalvarImagemPNG("fundo.png",1);

        //mistura o circulo interno com a barra
        off->MergeSurface(2,0,SDL_BLENDMODE_NONE);
        //off->SalvarImagemPNG("circ20.png",0);

        //mistura o circulo interno com o fundo
        off->MergeSurface(2,1,SDL_BLENDMODE_NONE);
        //off->SalvarImagemPNG("circ21.png",1);

        //sobre a barra em cima do fundo
        off->MergeSurface(0,1,SDL_BLENDMODE_NONE);
        //off->SalvarImagemPNG("circ01.png",1);

        if (text) SDL_DestroyTexture(text);
        text = SDL_CreateTextureFromSurface(renderer,off->GetSurface(1));

        //OnAction();
    }

public:

    CPIGGaugeCircular(int idComponente, int px, int py, int altura, int largura, int raioInterior, int janela=0):
        CPIGGauge(idComponente,px,py,altura,largura,janela){

        angBase = 0;
        deltaAng = 360;
        raioInterno = raioInterior;
        crescimentoHorario = true;

        IniciaCoresBasicas();

        off = new CPIGOffscreenRenderer(altura,largura,3);

        Move(px,py);
        SetPivoProporcional({larg/2.0,alt/2.0});

        AtualizaMarcador();
    }

    CPIGGaugeCircular(int idComponente, CPIGAtributos atrib):CPIGGaugeCircular(LeParametros(idComponente,atrib)){}

    virtual ~CPIGGaugeCircular(){
        delete off;
    }

    int Desenha(){
        if(visivel==false) return -1;

        if (!marcadorAtualizado) AtualizaMarcador();

        //vai desenhar o gauge em si
        CPIGSprite::Desenha();

        DesenhaLabel();

        EscreveHint();

        return 1;
    }

    void SetCrescimentoHorario(bool horario){
        crescimentoHorario = horario;
        //AtualizaMarcador();
        marcadorAtualizado = false;
    }

    void SetRaioInterno(int valorRaio){
        if (valorRaio<0||valorRaio>0.9*larg/2) return;

        raioInterno = valorRaio;
        //AtualizaMarcador();
        marcadorAtualizado = false;
    }

    void SetAnguloBase(double novoAng){
        angBase = novoAng;
        //AtualizaMarcador();
        marcadorAtualizado = false;
    }

    void SetDeltaAngulo(double novoDelta){
        deltaAng = novoDelta;
        //AtualizaMarcador();
        marcadorAtualizado = false;
    }

    int TrataEventoMouse(PIGEvento evento){
        return 0;
    }

    int TrataEventoTeclado(PIGEvento evento){
        return 0;
    }
};

typedef CPIGGaugeCircular *PIGGaugeCircular;
#endif // _CPIGGAUGECIRCULAR_
