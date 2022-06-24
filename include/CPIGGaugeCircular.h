#ifndef _CPIGGAUGECIRCULAR_
#define _CPIGGAUGECIRCULAR_

#include "CPIGGauge.h"
#include "CPIGOffscreenRenderer.h"

class CPIGGaugeCircular:public CPIGGauge{

private:

    double angBase,deltaAng;
    int raioInterno;

    void ProcessaAtributos(CPIGAtributos atrib)override{
        CPIGGauge::ProcessaAtributos(atrib);

        float valorFloat = atrib.GetFloat("anguloBase",0);
        if (valorFloat != 0) SetAnguloBase(valorFloat);

        valorFloat = atrib.GetFloat("deltaAngulo",0);
        if (valorFloat != 0) SetDeltaAngulo(valorFloat);

        int valorInt = atrib.GetInt("raioInterno",0);
        if (valorInt > 0) SetRaioInterno(valorInt);
    }

    static CPIGGaugeCircular LeParametros(int idComponente, CPIGAtributos atrib){
        CPIGGaugeCircular *resp;

        if (atrib.GetString("nomeArq","") != ""){
            resp = new CPIGGaugeCircular(idComponente,atrib.GetInt("altura",0),atrib.GetInt("largura",0),
                        atrib.GetString("nomeArq",""),atrib.GetInt("alturaMarcador",0),atrib.GetInt("larguraMarcador",0),atrib.GetString("nomeArqMarcador",""),
                        atrib.GetInt("retiraFundo",1),atrib.GetInt("retiraFundoMarcador",1),atrib.GetInt("janela",0));

        }else{
            resp = new CPIGGaugeCircular(idComponente,atrib.GetInt("altura",0),atrib.GetInt("largura",0),atrib.GetInt("janela",0));
        }
        resp->ProcessaAtributos(atrib);

        return *resp;
    }

    void AtualizaTextura()override{

        if (this_thread::get_id()!=PIG_MAIN_THREAD_ID) return;

        if (imagemPropria){
            CPIGSprite::AtualizaTextura();
            return;
        }

        PIGCor opcoes[4] = {VERDE,AZUL,ROXO,LARANJA}; //4 cores quaisquer
        PIGCor croma1, croma2; //cores usada como cromakey para transparencias (não podem ser nem a cor da barra, nem a cor do fundo)


        //escolha das cores; coresBasicas[3] é a cor a ser utilizada no marcador
        int i=0;
        croma1=opcoes[i];
        while (PIGCoresIguais(croma1,coresBasicas[3])||PIGCoresIguais(croma1,coresBasicas[0])){//não pode ser a cor da barra nem do fundo
            croma1=opcoes[++i];
        }
        croma2=opcoes[i];
        while (PIGCoresIguais(croma2,coresBasicas[3])||PIGCoresIguais(croma2,coresBasicas[0])||PIGCoresIguais(croma2,croma1)){//não pode ser a cor da barra, nem do fundo, nem a cor croma1
            croma2=opcoes[++i];
        }

        PIGOffscreenRenderer off = new CPIGOffscreenRenderer(alt,larg,3);

        //circulo interno para criar efeito de coroa circular
        off->DesenhaCirculoFinal(raioInterno,croma2,croma1,0,360.0,2);
        off->SetCorTransparente(2,true,croma2);
        //off->SalvarImagemPNG("interno.png",2);

        double deltaCrescimento=0;
        if (orientacaoCrescimento==PIG_GAUGE_HORARIO)
            deltaCrescimento = deltaAng-porcentagemConcluida*(deltaAng);

        //circulo com a barra na cor desejada
        off->DesenhaCirculoFinal(larg/2-2,croma1,coresBasicas[3],deltaCrescimento,porcentagemConcluida*(deltaAng)+deltaCrescimento,0);
        off->SetCorTransparente(0,true,croma1);
        //off->SalvarImagemPNG("barra.png",0);

        //criculo com o fundo na cor de fundo
        //printf("base %f final %f\n",angBase,angBase+deltaAng);
        off->DesenhaCirculoFinal(larg/2-2,croma1,coresBasicas[0],0,deltaAng,1);
        off->SetCorTransparente(1,true,croma1);
        //off->SalvarImagemPNG("trilha.png",1);

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

        delete off;

        precisaAtualizar = false;

        SetAngulo(angBase);
    }

    virtual void AtualizaMarcador()override{
        CPIGGauge::AtualizaMarcador();
        OnAction();
        if (marcador){
            marcador->SetPivoAbsoluto({(double)margemEsq,(double)margemBaixo});
            marcador->Move(pos.x+larg/2-margemEsq,pos.y+alt/2-margemBaixo);
            double angMarcador=0;
            if (orientacaoCrescimento==PIG_GAUGE_HORARIO)
                angMarcador = porcentagemConcluida*(deltaAng)+angBase;
            else angMarcador = angBase+deltaAng-porcentagemConcluida*(deltaAng);
            marcador->SetAngulo(angMarcador);
        }else{
            AtualizaTextura();
        }
    }

    void IniciaBase(){
        angBase = 0;
        deltaAng = 360;
        raioInterno = 0;
        orientacaoCrescimento = PIG_GAUGE_HORARIO;
        tipo = PIG_GAUGECIRCULAR;
        AtualizaMarcador();
    }

public:

    CPIGGaugeCircular(int idComponente, int altura, int largura, int janela=0):
        CPIGGauge(idComponente,altura,largura,janela){

        SetPivoProporcional({0.5,0.5});

        IniciaCoresBasicas();

        IniciaBase();
    }

    CPIGGaugeCircular(int idComponente, int altura, int largura, string imgTrilha, int alturaMarcador, int larguraMarcador, string imgMarcador, int retiraFundoTrilha=1, int retiraFundoMarcador=1, int janela=0):
        CPIGGauge(idComponente,altura,largura,imgTrilha,retiraFundoTrilha,janela){

        marcador = new CPIGSprite(-1,imgMarcador,retiraFundoMarcador,NULL,janela);
        marcador->SetDimensoes(alturaMarcador,larguraMarcador);

        IniciaBase();
    }

    CPIGGaugeCircular(int idComponente, CPIGAtributos atrib):CPIGGaugeCircular(LeParametros(idComponente,atrib)){}

    virtual ~CPIGGaugeCircular(){}

    int Desenha()override{
        if(visivel==false) return 0;

        if (!marcadorAtualizado) AtualizaMarcador();

        CPIGGerenciadorJanelas::GetJanela(idJanela)->BloqueiaArea(pos.x,pos.y,alt,larg);

        //vai desenhar o gauge em si
        CPIGSprite::Desenha();
        if (marcador)
            marcador->Desenha();

        CPIGGerenciadorJanelas::GetJanela(idJanela)->DesbloqueiaArea();

        return CPIGComponente::Desenha();
    }

    int SetOrientacao(PIGGaugeCrescimento orientacao){
        if (orientacao==PIG_GAUGE_HORARIO||orientacao==PIG_GAUGE_ANTIHORARIO){
            orientacaoCrescimento = orientacao;
            marcadorAtualizado = false;

            return 1;
        }
        return 0;
    }

    void SetRaioInterno(int valorRaio){
        if (valorRaio<0||valorRaio>0.9*larg/2) return;

        raioInterno = valorRaio;
        marcadorAtualizado = false;
    }

    void SetAnguloBase(double novoAng){
        angBase = novoAng;
        marcadorAtualizado = false;
    }

    void SetDeltaAngulo(double novoDelta){
        deltaAng = novoDelta;
        marcadorAtualizado = false;
    }

};

typedef CPIGGaugeCircular *PIGGaugeCircular;
#endif // _CPIGGAUGECIRCULAR_
