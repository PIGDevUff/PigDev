#ifndef _CPIGGAUGEBAR_
#define _CPIGGAUGEBAR_

#include "CPIGGauge.h"

class CPIGGaugeBar: public CPIGGauge{

private:

    void ProcessaAtributos(CPIGAtributos atrib)override{
        CPIGGauge::ProcessaAtributos(atrib);
    }

    static CPIGGaugeBar LeParametros(int idComponente, CPIGAtributos atrib){
        CPIGGaugeBar *resp;

        if (atrib.GetString("nomeArq","")!=""){
            resp = new CPIGGaugeBar(idComponente,atrib.GetInt("altura",0),atrib.GetInt("largura",0),
                          atrib.GetString("nomeArq",""),atrib.GetString("nomeArqMarcador",""),
                          atrib.GetInt("retiraFundo",1),atrib.GetInt("retiraFundoMarcador",1),atrib.GetInt("janela",0));
        }else{
            resp = new CPIGGaugeBar(idComponente,atrib.GetInt("altura",0),atrib.GetInt("largura",0),atrib.GetInt("janela",0));
        }

        resp->ProcessaAtributos(atrib);

        return *resp;
    }

    void DesenhaBarraCor(){
        double perc = porcentagemConcluida;
        int largBarra = larg-margemDir-margemEsq;
        int altBarra = alt-margemBaixo-margemCima;

        switch(orientacaoCrescimento){
        case PIG_GAUGE_ESQ_DIR:
            CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetangulo(((int)pos.x)+margemEsq,((int)pos.y)+margemBaixo,altBarra,((int)largBarra*perc),coresBasicas[3]);
            break;
        case PIG_GAUGE_DIR_ESQ:
            CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetangulo(pos.x+larg-margemDir-largBarra*perc,pos.y+margemBaixo,altBarra,largBarra*perc,coresBasicas[3]);
            break;
        case PIG_GAUGE_BAIXO_CIMA:
            CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetangulo(pos.x+margemEsq,pos.y+margemBaixo,altBarra*perc,largBarra,coresBasicas[3]);
            break;
        case PIG_GAUGE_CIMA_BAIXO:
            CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetangulo(pos.x+margemEsq,pos.y+alt-margemCima-altBarra*perc,altBarra*perc,largBarra,coresBasicas[3]);
            break;
        }
    }

    virtual void AtualizaMarcador()override{
        CPIGGauge::AtualizaMarcador();
        //OnAction();
        if (marcador==NULL) return;

        int altBarraFinal=0,largBarraFinal=0;
        int altBarraOrig=0,largBarraOrig=0;

        marcador->GetDimensoesOriginais(altBarraOrig,largBarraOrig);

        int altUtilBarraTela = alt - (margemCima+margemBaixo);
        int largUtilBarraTela = larg - (margemDir+margemEsq);

        PIGPonto2D posBarra={0,0};

        double perc = porcentagemConcluida;
        SDL_Rect r={0,0,0,0};

        switch(orientacaoCrescimento){
        case PIG_GAUGE_ESQ_DIR:
            altBarraFinal = altUtilBarraTela;
            largBarraFinal = largUtilBarraTela*perc;
            posBarra = {pos.x+margemEsq,pos.y+margemBaixo};
            r.x = 0;
            r.y = 0;
            r.w = largBarraOrig*perc;
            r.h = altBarraOrig;
            break;
        case PIG_GAUGE_DIR_ESQ:
            altBarraFinal = altUtilBarraTela;
            largBarraFinal = largUtilBarraTela*perc;
            posBarra = {pos.x+larg-margemDir-largBarraFinal-1,pos.y+margemBaixo};
            r.x = (largBarraOrig)*(1-perc);
            r.y = 0;
            r.w = (largBarraOrig)*perc;
            r.h = altBarraOrig;
            break;
        case PIG_GAUGE_BAIXO_CIMA:
            altBarraFinal = (altUtilBarraTela)*perc;
            largBarraFinal = largUtilBarraTela;
            posBarra = {pos.x+margemEsq,pos.y+margemBaixo};
            r.x = 0;
            r.y = altBarraOrig*(1-perc);
            r.w = largBarraOrig;
            r.h = (altBarraOrig)*perc;
            break;
        case PIG_GAUGE_CIMA_BAIXO:
            altBarraFinal = (altUtilBarraTela)*perc;
            largBarraFinal = largUtilBarraTela;
            posBarra = {pos.x+margemEsq,pos.y+alt-margemCima-altBarraFinal};
            r.x = 0;
            r.y = 0;
            r.w = largBarraOrig;
            r.h = (altBarraOrig)*perc;
            break;
        }

        //printf("x y w h %d %d %d %d %.1f\n",r.x,r.y,r.w,r.h,perc);
        //printf("x %d y %d alt %d larg %d %d,%d,%d,%d\n",(int)posBarra.x,(int)posBarra.y,altBarraFinal,largBarraFinal,margemEsq,margemDir,margemCima,margemBaixo);
        marcador->DefineFrame(1,r);
        marcador->SetDimensoes(altBarraFinal,largBarraFinal);
        marcador->MudaFrameAtual(1);
        marcador->Move((int)posBarra.x,(int)posBarra.y);
    }

public:

    CPIGGaugeBar(int idComponente, int altura, int largura, string imgMoldura, string imgMarcador, int retiraFundoTrilha=1, int retiraFundoMarcador=1, int janela=0):
        CPIGGauge(idComponente,altura,largura,imgMoldura,retiraFundoTrilha,janela){
        IniciaCoresBasicas();
        tipo = PIG_GAUGEBAR;
        if (imgMarcador!=""){
            marcador = new CPIGSprite(-1,imgMarcador,retiraFundoMarcador,NULL,janela);
            AtualizaMarcador();
        }
    }

    CPIGGaugeBar(int idComponente, int altura, int largura, int janela=0):
        CPIGGauge(idComponente,altura,largura,janela){
        tipo = PIG_GAUGEBAR;
        IniciaCoresBasicas();
    }

    virtual ~CPIGGaugeBar(){}

    CPIGGaugeBar(int idComponente, CPIGAtributos atrib):CPIGGaugeBar(LeParametros(idComponente,atrib)){}

    int Desenha()override{
        if(visivel==false) return 0;

        if (!marcadorAtualizado) AtualizaMarcador();

        CPIGGerenciadorJanelas::GetJanela(idJanela)->BloqueiaArea(pos.x,pos.y,alt,larg);

        //moldura
        if (imagemPropria){
            if (marcadorFrente){
                //Desenha Barra
                CPIGSprite::Desenha();
                if (marcador) marcador->Desenha();
            }else{
                if (marcador) marcador->Desenha();
                CPIGSprite::Desenha();
            }
        }else{
            CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetangulo((int)pos.x,(int)pos.y,alt,larg,coresBasicas[0]);
            DesenhaBarraCor();
        }

        CPIGGerenciadorJanelas::GetJanela(idJanela)->DesbloqueiaArea();

        return CPIGComponente::Desenha();
    }

    int SetOrientacao(PIGGaugeCrescimento orientacao){
        if (orientacao==PIG_GAUGE_HORARIO||orientacao==PIG_GAUGE_ANTIHORARIO)
            return 0;

        orientacaoCrescimento = orientacao;
        marcadorAtualizado = false;
        return 1;
    }

};
typedef CPIGGaugeBar *PIGGaugeBar;
#endif // _CPIGGAUGE_
