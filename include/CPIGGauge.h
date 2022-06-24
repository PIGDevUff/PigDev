#ifndef _CPIGGAUGE_
#define _CPIGGAUGE_

#include "CPIGComponente.h"

typedef enum {PIG_GAUGE_CIMA_BAIXO,PIG_GAUGE_BAIXO_CIMA,PIG_GAUGE_ESQ_DIR,PIG_GAUGE_DIR_ESQ,PIG_GAUGE_HORARIO,PIG_GAUGE_ANTIHORARIO} PIGGaugeCrescimento;

class CPIGGauge: public CPIGComponente{

protected:

    PIGSprite marcador;
    double delta,porcentagemConcluida;
    double valorMax,valorMin,valorAtual;
    bool marcadorAtualizado,marcadorFrente;
    PIGGaugeCrescimento orientacaoCrescimento;

    static PIGGaugeCrescimento ConverteStringCrescimento(string str){
        transform(str.begin(), str.end(), str.begin(), ::toupper);
        if (str=="ESQ_DIR") return PIG_GAUGE_ESQ_DIR;
        if (str=="DIR_ESQ") return PIG_GAUGE_DIR_ESQ;
        if (str=="CIMA_BAIXO") return PIG_GAUGE_CIMA_BAIXO;
        if (str=="BAIXO_CIMA") return PIG_GAUGE_BAIXO_CIMA;
        if (str=="HORARIO") return PIG_GAUGE_HORARIO;
        if (str=="ANTIHORARIO") return PIG_GAUGE_ANTIHORARIO;
        return PIG_GAUGE_ESQ_DIR;
    }

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

        valorStr = atrib.GetString("orientacao","");
        if (valorStr != "") SetOrientacao(ConverteStringCrescimento(valorStr));
    }

    void IniciaBase(){
        valorMin = valorAtual = 0;
        valorMax = 100;
        porcentagemConcluida = 0;
        orientacaoCrescimento = PIG_GAUGE_ESQ_DIR;
        delta = 1;
        marcador = NULL;
        marcadorAtualizado = false;
        marcadorFrente = true;
        IniciaCoresBasicas();
    }

    CPIGGauge(int idComponente, int altura, int largura, string imgTrilha, int retiraFundoTrilha=1, int janela=0):
        CPIGComponente(idComponente,altura,largura,imgTrilha,retiraFundoTrilha,janela){
        IniciaBase();
    }

    CPIGGauge(int idComponente, int altura, int largura, int janela=0):
        CPIGComponente(idComponente,altura,largura,janela){
        IniciaBase();
    }

    virtual ~CPIGGauge(){
        if (marcador) delete marcador;
    }

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

    virtual int SetOrientacao(PIGGaugeCrescimento orientacao)=0;

    void SetPorcentagemConcluida(double porcentagem){
        porcentagemConcluida = PIGLimitaValor(porcentagem,0.0,1.0);
        valorAtual = valorMin + (valorMax - valorMin)*porcentagemConcluida;
        porcentagemConcluida = (valorAtual - valorMin)/(valorMax - valorMin); //correção para que o percentual represent um valor inteiro dentro da faixa min-max
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
        porcentagemConcluida = (valorAtual - valorMin)/(valorMax - valorMin);
        marcadorAtualizado = false;
    }

    void MaximizaValorAtual(){
        valorAtual = valorMax;
        porcentagemConcluida = (valorAtual - valorMin)/(valorMax - valorMin);
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
        CPIGComponente::Desloca(dx,dy);
        if (marcador) marcador->Desloca(dx,dy);
    }

    virtual void Move(double nx, double ny)override{
        if (marcador) marcador->Desloca(nx-pos.x,ny-pos.y);
        CPIGComponente::Move(nx,ny);
    }

    void SetMarcadorFrente(bool valor){
        marcadorFrente = valor;
        marcadorAtualizado = false;
    }

    virtual void SetMargens(int mEsq, int mDir, int mCima, int mBaixo)override{
        CPIGComponente::SetMargens(mEsq,mDir,mCima,mBaixo);
        marcadorAtualizado = false;
    }
};
typedef CPIGGauge *PIGGauge;
#endif // _CPIGGAUGE_
