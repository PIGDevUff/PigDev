#ifndef _CPIGGAUGECIRCULAR_
#define _CPIGGAUGECIRCULAR_

#include "CPIGGauge.h"

class CPIGGaugeCircular:public CPIGGauge{

private:

    double angBase,deltaAng;
    int raioInterno;
    bool crescimentoHorario;

    PIG_Cor corInicial,corFinal,corInterna;
    PIGOffscreenRenderer off;
    SDL_Texture *textGauge;

    CPIGGaugeCircular LeParametros(int idComponente,string parametros){
        CPIGAtributos atrib = CPIGComponente::GetAtributos(parametros);

        CPIGGaugeCircular resp(idComponente,atrib.GetInt("px",0),atrib.GetInt("py",0),atrib.GetInt("altura",0),atrib.GetInt("largura",0),
                          atrib.GetInt("raioInterior",0),atrib.GetInt("janela",0));

        return resp;
    }

    virtual void AtualizaMarcador()override{
        PIG_Cor corBarra = PIGMixCor(corInicial,corFinal,porcentagemConcluida);//cor da barra mizada entre a cor inicial e a final
        PIG_Cor opcoes[4] = {VERDE,AZUL,ROXO,LARANJA}; //4 cores quaisquer
        PIG_Cor croma1, croma2; //cores usada como cromakey para transparencias (não podem ser nem a cor da barra, nem a cor do fundo)

        //escolha das cores
        int i=0;
        croma1=opcoes[i];
        while (PIGCoresIguais(croma1,corBarra)||PIGCoresIguais(croma1,corInterna)){//não pode ser a cor da barra nem do fundo
            croma1=opcoes[++i];
        }
        croma2=opcoes[i];
        while (PIGCoresIguais(croma2,corBarra)||PIGCoresIguais(croma2,corInterna)||PIGCoresIguais(croma2,croma1)){//não pode ser a cor da barra, nem do fundo, nem a cor croma1
            croma2=opcoes[++i];
        }

        //circulo interno para criar efeito de coroa circular
        off->DesenhaCirculoFinal(raioInterno,croma2,croma1,0,360.0,2);
        off->SetCorTransparente(2,true,croma2);
        //off->SalvarImagemPNG("interno.png",2);

        //circulo com a barra na cor desejada
        off->DesenhaCirculoFinal(larg/2-2,croma1,corBarra,angBase,porcentagemConcluida*(deltaAng)+angBase,0);
        off->SetCorTransparente(0,true,croma1);
        //off->SalvarImagemPNG("barra.png",0);

        //criculo com o fundo na cor de fundo
        off->DesenhaCirculoFinal(larg/2-2,croma1,corInterna,angBase,angBase+deltaAng,1);
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

        if (textGauge) SDL_DestroyTexture(textGauge);
        textGauge = SDL_CreateTextureFromSurface(renderer,off->GetSurface(1));
        //bitmap = off->GetSurface(1);
        //CriaTextura(1);

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

        off = new CPIGOffscreenRenderer(altura,largura,3);

        Move(px,py);
        SetPivoProporcional({larg/2.0,alt/2.0});
        textGauge = NULL;
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
        off = new CPIGOffscreenRenderer(altura,largura,3);

        Move(px,py);
        SetPivoProporcional({larg/2.0,alt/2.0});
        textGauge = NULL;
        AtualizaTextura();
        crescimentoHorario=true;
    }*/

    CPIGGaugeCircular(int idComponente,string parametros):CPIGGaugeCircular(LeParametros(idComponente,parametros)){}

    ~CPIGGaugeCircular(){
        delete off;
    }

    int Desenha(){
        //SDL_Point p = {pivoRelativo.x,pivoRelativo.y};

        //vai desenhar a textura de base
        CPIGSprite::Desenha();
        //SDL_RenderCopyEx(renderer,text,NULL,&dest,-angulo,&p,flip);
        SDL_Texture *textAux = text;
        text = textGauge;

        //vai desenhar o gauge em si
        CPIGSprite::Desenha();
        //SDL_RenderCopyEx(renderer,textGauge,NULL,&dest,-angulo,&p,flip);

        //recupera a textura de base
        text = textAux;

        DesenhaLabel();

        EscreveHint();
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
