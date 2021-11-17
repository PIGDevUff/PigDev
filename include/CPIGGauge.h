#ifndef _CPIGGAUGE_
#define _CPIGGAUGE_

#include "CPIGComponente.h"

typedef enum {PIG_GAUGE_CIMA_BAIXO,PIG_GAUGE_BAIXO_CIMA,PIG_GAUGE_ESQ_DIR,PIG_GAUGE_DIR_ESQ} PIGGaugeCrescimento;

class CPIGGauge: public CPIGComponente{

protected:

    PIGSprite marcador;
    double delta,porcentagemConcluida;
    double valorMax,valorMin,valorAtual;
    bool marcadorAtualizado;
    PIGGaugeCrescimento orientacaoCrescimento;

    virtual void AtualizaMarcador(){
        coresBasicas[3] = PIGMixCor(coresBasicas[1],coresBasicas[2],porcentagemConcluida);
        marcadorAtualizado = true;
    }

    inline void IniciaCoresBasicas(){
        coresBasicas[0] = BRANCO;
        coresBasicas[1] = CINZA;
        coresBasicas[2] = CINZA;
    }

    void ProcessaAtributos(CPIGAtributos atrib)override{
        CPIGComponente::ProcessaAtributos(atrib);

        int valorInt = atrib.GetInt("valorMin",INT_MAX);
        if (valorInt != INT_MAX) SetValorMin(valorInt);

        valorInt = atrib.GetInt("valorMax",INT_MIN);
        if (valorInt != INT_MIN) SetValorMax(valorInt);

        valorInt = atrib.GetInt("valorAtual",INT_MIN);
        if (valorInt != INT_MIN) SetValorAtual(valorInt);

        valorInt = atrib.GetInt("delta",0);
        if (valorInt != 0) SetDelta(valorInt);

        float valorFloat = atrib.GetFloat("porcentagem",0);
        if (valorFloat != 0) SetPorcentagemConcluida(valorFloat);

        string valorStr = atrib.GetString("corTrilha","");
        if (valorStr != "") SetCorTrilha(PIGCriaCorString(valorStr));

        valorStr = atrib.GetString("corInicial","");
        if (valorStr != "") SetCorInicial(PIGCriaCorString(valorStr));

        valorStr = atrib.GetString("corFinal","");
        if (valorStr != "") SetCorFinal(PIGCriaCorString(valorStr));
    }

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
        IniciaCoresBasicas();
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
            marcadorAtualizado = false;
            return 1;
        }
        return 0;
    }

    virtual int SetValorMax(double maximo){
        if(valorMin <= maximo){
            valorMax = maximo;
            marcadorAtualizado = false;
            return 1;
        }
        return 0;
    }

    virtual int SetValorAtual(double valor){
        if(valor>=valorMin && valor<=valorMax){
            valorAtual = valor;
            marcadorAtualizado = false;
            return 1;
        }
        return 0;
    }

    void SetDelta(double valor){
        delta = valor;
    }

    void SetOrientacao(PIGGaugeCrescimento orientacao){
        orientacaoCrescimento = orientacao;
        marcadorAtualizado = false;
    }

    void SetPorcentagemConcluida(double porcentagem){
        porcentagemConcluida = PIGLimitaValor(porcentagem,0.0,1.0);
        valorAtual = valorMin + (valorMax - valorMin)*porcentagemConcluida;
        marcadorAtualizado = false;
        OnAction();
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

    string GetStringValorMarcador(){
        stringstream ss;
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

        marcadorAtualizado = false;

        if (valor!=0)
            OnAction();
    }

    void AvancaDelta(){
        AvancaMarcador(delta);
    }

    void MinimizaValorAtual(){
        valorAtual = valorMin;
        marcadorAtualizado = false;
    }

    void MaximizaValorAtual(){
        valorAtual = valorMax;
        marcadorAtualizado = false;
    }

    void SetCorInicial(PIGCor cor){
        coresBasicas[1] = cor;
        marcadorAtualizado = false;
    }

    void SetCorFinal(PIGCor cor){
        coresBasicas[2] = cor;
        marcadorAtualizado = false;
    }

    void SetCorTrilha(PIGCor cor){
        coresBasicas[0] = cor;
        marcadorAtualizado = false;
    }

    virtual void Desloca(double dx, double dy)override{
        CPIGSprite::Desloca(dx,dy);
        if (marcador) marcador->Desloca(dx,dy);
    }
};
typedef CPIGGauge *PIGGauge;
#endif // _CPIGGAUGE_
