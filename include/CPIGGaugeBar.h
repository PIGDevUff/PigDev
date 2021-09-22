#ifndef _CPIGGAUGEBAR_
#define _CPIGGAUGEBAR_

#include "CPIGGauge.h"

class CPIGGaugeBar: public CPIGGauge{

private:
    int margemEsq,margemDir,margemCima,margemBaixo;
    PIG_Cor corInicial, corFinal;

    CPIGGaugeBar LeParametros(int idComponente,string parametros){
        CPIGAtributos atrib = CPIGComponente::GetAtributos(parametros);

        CPIGGaugeBar resp(idComponente,atrib.GetInt("px",0),atrib.GetInt("py",0),atrib.GetInt("altura",0),atrib.GetInt("largura",0),
                          atrib.GetString("nomeArq",""),atrib.GetString("nomeArqMarcador",""),
                          atrib.GetInt("retiraFundo",1),atrib.GetInt("retiraFundoMarcador",1),atrib.GetInt("janela",0));

        return resp;
    }

    void DesenhaBarraCor(){
        PIG_Cor cor = PIGMixCor(corInicial,corFinal,porcentagemConcluida);
        double perc = porcentagemConcluida;
        int largBarra = larg-margemDir-margemEsq;
        int altBarra = alt-margemBaixo-margemCima;

        switch(orientacaoCrescimento){
        case PIG_GAUGE_ESQ_DIR:
            PIGDesenhaRetangulo(pos.x+margemEsq,pos.y+margemBaixo,altBarra,largBarra*perc,cor);
            break;
        case PIG_GAUGE_DIR_ESQ:
            PIGDesenhaRetangulo(pos.x+larg-margemDir-largBarra*perc,pos.y+margemBaixo,altBarra,largBarra*perc,cor);
            break;
        case PIG_GAUGE_BAIXO_CIMA:
            PIGDesenhaRetangulo(pos.x+margemEsq,pos.y+margemBaixo,altBarra*perc,largBarra,cor);
            break;
        case PIG_GAUGE_CIMA_BAIXO:
            PIGDesenhaRetangulo(pos.x+margemEsq,pos.y+alt-margemCima-altBarra*perc,altBarra*perc,largBarra,cor);
            break;
        }
    }

    virtual void AtualizaMarcador()override{
        if (marcador==NULL) return;

        int altBarra,largBarra;
        int altBarraOrig,largBarraOrig;

        marcador->GetDimensoesOriginais(altBarraOrig,largBarraOrig);
        PIGPonto2D posBarra;

        double perc = porcentagemConcluida;
        SDL_Rect r;

        //printf(" porc %f\n",perc);

        switch(orientacaoCrescimento){
        case PIG_GAUGE_ESQ_DIR:
            altBarra = alt-margemCima-margemBaixo;
            largBarra = (larg-margemDir-margemEsq)*perc;
            posBarra = {pos.x+margemEsq,pos.y+margemBaixo};
            r.x = r.y = 0;
            r.w = largBarra*perc;
            r.h = altBarra;
            //printf("define frame \n");
            marcador->DefineFrame(1,r);
            //printf("define ok\n");
            break;
        case PIG_GAUGE_DIR_ESQ:
            altBarra = alt-margemCima-margemBaixo;
            largBarra = (larg-margemDir-margemEsq)*perc;
            posBarra = {pos.x+larg-margemDir-largBarra,pos.y+margemBaixo};
            r.x = largBarraOrig*(1-perc);
            r.y = 0;
            r.w = largBarraOrig*perc;
            r.h = altBarra;
            marcador->DefineFrame(1,r);
            break;
        case PIG_GAUGE_BAIXO_CIMA:
            altBarra = (alt-margemCima-margemBaixo)*perc;
            largBarra = larg-margemDir-margemEsq;
            posBarra = {pos.x+margemEsq,pos.y+margemBaixo};
            r.x = 0;
            r.y = altBarraOrig*(1-perc);
            r.w = largBarraOrig;
            r.h = altBarraOrig*perc;
            marcador->DefineFrame(1,r);
            break;
        case PIG_GAUGE_CIMA_BAIXO:
            altBarra = (alt-margemCima-margemBaixo)*perc;
            largBarra = larg-margemDir-margemEsq;
            posBarra = {pos.x+margemEsq,pos.y+alt-margemCima-altBarra};
            r.x = r.y = 0;
            r.w = largBarraOrig;
            r.h = altBarraOrig*perc;
            marcador->DefineFrame(1,r);
            break;
        }

        //printf("x %d y %d alt %d larg %d %d,%d,%d,%d\n",(int)posBarra.x,(int)posBarra.y,altBarra,largBarra,margemEsq,margemDir,margemCima,margemBaixo);

        marcador->SetDimensoes(altBarra,largBarra);
        marcador->MudaFrameAtual(1);
        marcador->Move((int)posBarra.x,(int)posBarra.y);
        //printf(" acao vai\n");
        OnAction();
        //printf(" acao foi\n");
    }

public:

    CPIGGaugeBar(int idComponente,int px, int py,int altura,int largura,std::string imgMoldura,std::string imgMarcador,int retiraFundoTrilha=1,int retiraFundoMarcador=1,int janela=0):
        CPIGGauge(idComponente,px,py,altura,largura,imgMoldura,altura,largura,imgMarcador,retiraFundoTrilha,retiraFundoMarcador,janela){
        //printf("criado gauge\n");
        corInicial = corFinal = BRANCO;
        if (imgMarcador!=""){
            marcador = new CPIGImagem(-1,imgMarcador,retiraFundoMarcador,NULL,janela);
            AtualizaMarcador();
        }
        //printf("criado gauge fim\n");
    }

    ~CPIGGaugeBar(){
        if (marcador) delete marcador;
    }

    CPIGGaugeBar(int idComponente,string parametros):CPIGGaugeBar(LeParametros(idComponente,parametros)){}

    int Desenha(){
        //moldura
        CPIGImagem::Desenha();

        //Desenha Barra
        if (marcador)
            marcador->Desenha();
        else{
            DesenhaBarraCor();
        }

        DesenhaLabel();

        EscreveHint();

        return 1;
    }

    void SetCorFinal(PIG_Cor cor){
        corFinal = cor;
    }

    void SetCorInicial(PIG_Cor cor){
        corInicial = cor;
    }

    int TrataEventoMouse(PIG_Evento evento){
        return 0;
    }

    int TrataEventoTeclado(PIG_Evento evento){
        return 0;
    }

    void SetMargens(int mEsq,int mDir,int mCima,int mBaixo){
        margemEsq = mEsq;
        margemDir = mDir;
        margemCima = mCima;
        margemBaixo = mBaixo;
        //printf("atualizando marc\n");
        AtualizaMarcador();
    }
};
typedef CPIGGaugeBar *PIGGaugeBar;
#endif // _CPIGGAUGE_
