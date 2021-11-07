#ifndef _CPIGGAUGE_
#define _CPIGGAUGE_

#include "CPIGComponente.h"

typedef enum {PIG_GAUGE_CIMA_BAIXO,PIG_GAUGE_BAIXO_CIMA,PIG_GAUGE_ESQ_DIR,PIG_GAUGE_DIR_ESQ} PIG_GaugeCrescimento;

class CPIGGauge: public CPIGComponente{

protected:

    PIGSprite marcador;
    double delta,porcentagemConcluida;
    double valorMax,valorMin,valorAtual;

    PIG_GaugeCrescimento orientacaoCrescimento;

    virtual void AtualizaMarcador(){}

    void SetFoco(bool valor){
        temFoco = valor;
    }

    void SetAcionado(bool valor){
        acionado = valor;
    }

    void SetMouseOver(bool valor){
        mouseOver = valor;
    }

    void SetHabilitado(bool valor){
        habilitado = valor;
    }

    void IniciaBase(){
        valorMin = valorAtual = 0;
        valorMax = 100;
        porcentagemConcluida = 0;
        orientacaoCrescimento = PIG_GAUGE_ESQ_DIR;
        delta = 1;
        marcador = NULL;
    }

    CPIGGauge(int idComponente,int px, int py,int altura,int largura,std::string imgTrilha,int altMarcador, int largMarcador, std::string imgMarcador,int retiraFundoTrilha=1, int retiraFundoMarcador=1,int janela=0):
        CPIGComponente(idComponente,px,py,altura,largura,imgTrilha,retiraFundoTrilha,janela){
        IniciaBase();
    }

    CPIGGauge(int idComponente,int px, int py,int altura,int largura,int janela=0):
        CPIGComponente(idComponente,px,py,altura,largura,janela){
        IniciaBase();
    }

    virtual ~CPIGGauge(){}

public:

    virtual int SetValorMin(double minimo){
        if(minimo <= valorMax){
            valorMin = minimo;
            AvancaMarcador(0);
            return 1;
        }
        return 0;
    }

    virtual int SetValorMax(double maximo){
        if(valorMin <= maximo){
            valorMax = maximo;
            AvancaMarcador(0);
            return 1;
        }
        return 0;
    }

    virtual int SetValorAtual(double valor){
        if(valor>=valorMin && valor<=valorMax){
            valorAtual = valor;
            AvancaMarcador(0);
            return 1;
        }
        return 0;
    }

    void SetDelta(double valor){
        delta = valor;
    }

    void SetOrientacao(PIG_GaugeCrescimento orientacao){
        orientacaoCrescimento = orientacao;
        AtualizaMarcador();
    }

    void SetPorcentagemConcluida(double porcentagem){
        porcentagemConcluida = PIGLimitaValor(porcentagem,0.0,1.0);
        valorAtual = valorMin + (valorMax - valorMin)*porcentagemConcluida;
        AtualizaMarcador();
    }

    double GetValorAtual(){
        return valorAtual;
    }

    double GetValorMax(){
        return valorMax;
    }

    double GetValorMin(){
        return valorMin;
    }

    std::string GetStringValorMarcador(){
        std::stringstream ss;
        ss <<valorAtual;
        return ss.str();
    }

    double GetPorcentagemConcluida(){
        return porcentagemConcluida;
    }

    virtual void AvancaMarcador(double valor){
        valorAtual += valor;

        valorAtual = PIGLimitaValor(valorAtual,valorMin,valorMax);
        porcentagemConcluida = (valorAtual - valorMin)/(valorMax - valorMin);

        AtualizaMarcador();
    }

    void AvancaDelta(){
        AvancaMarcador(delta);
    }

    void MinimizaValorAtual(){
        valorAtual = valorMin;
        AvancaMarcador(0);
    }

    void MaximizaValorAtual(){
        valorAtual = valorMax;
        AvancaMarcador(0);
    }

    virtual void Desloca(double dx, double dy)override{
        CPIGSprite::Desloca(dx,dy);
        if (marcador) marcador->Desloca(dx,dy);
    }
};
typedef CPIGGauge *PIGGauge;
#endif // _CPIGGAUGE_
