#ifndef _CPIGBOTAOCLICK_
#define _CPIGBOTAOCLICK_

#include "CPIGBotao.h"

class CPIGBotaoClick: public CPIGBotao{

protected:

    PIGTimer timer;
    bool botaoRepeticao;
    double tempoRepeticao;

    void IniciaCoresBasicas(){
        coresBasicas[1] = AZUL;
        coresBasicas[2] = {100,100,255,255};
        coresBasicas[3] = AMARELO;
        coresBasicas[4] = CINZA;
        corAtual = 1;
    }

    virtual void ProcessaAtributos(CPIGAtributos atrib)override{
        CPIGBotao::ProcessaAtributos(atrib);

        int valorInt = atrib.GetInt("repeticao",0);
        if (valorInt == true) DefineBotaoRepeticao(true);

        float valorFloat = atrib.GetFloat("tempoRepeticao",-1);
        if (valorFloat > 0) DefineTempoRepeticao(valorFloat);

        string valorStr = atrib.GetString("corNormal","");
        if (valorStr != "") SetCorNormal(PIGCriaCorString(valorStr));

        valorStr = atrib.GetString("corMouseSobre","");
        if (valorStr != "") SetCorMouseSobre(PIGCriaCorString(valorStr));

        valorStr = atrib.GetString("corAcionado","");
        if (valorStr != "") SetCorAcionado(PIGCriaCorString(valorStr));

        valorStr = atrib.GetString("corDesabilitado","");
        if (valorStr != "") SetCorDesabilitado(PIGCriaCorString(valorStr));
    }

    static CPIGBotaoClick LeParametros(int idComponente,CPIGAtributos atrib){
        CPIGBotaoClick *resp;

        if (atrib.GetString("nomeArq","")!=""){
            resp = new CPIGBotaoClick(idComponente,atrib.GetInt("px",0),atrib.GetInt("py",0),atrib.GetInt("altura",0),atrib.GetInt("largura",0),
                       atrib.GetString("nomeArq",""),atrib.GetInt("retiraFundo",1),atrib.GetInt("janela",0));
        }else{
            resp = new CPIGBotaoClick(idComponente,atrib.GetInt("px",0),atrib.GetInt("py",0),atrib.GetInt("altura",0),atrib.GetInt("largura",0),
                       atrib.GetInt("janela",0));
        }

        resp->ProcessaAtributos(atrib);

        return *resp;
    }

    void AjustaFrame(){
        if (visivel==false) return;
        corAtual = 1;
        if (habilitado==false){
            corAtual=4;
        }else{
            if (acionado){
                corAtual=3;
            }else if (mouseOver){
                corAtual=2;
            }
        }

        if (text)
            MudaFrameAtual(corAtual);
    }

    void TrataTimer(){
        if (timer->GetTempoDecorrido()>=tempoRepeticao){
            if (botaoRepeticao&&mouseOver&&CPIGMouse::GetEstadoBotaoEsquerdo()==PIG_MOUSE_PRESSIONADO){
                OnAction();
            }else{
                SetAcionado(false);
            }
        }
    }

    int OnAction()override{
        SetAcionado(true);
        timer->Reinicia(false);
        return CPIGComponente::OnAction();
    }

public:

    CPIGBotaoClick(int idComponente,int px, int py, int alt,int larg,std::string nomeArq, int retiraFundo=1,int janela=0):
        CPIGBotao(idComponente,px,py,alt,larg,nomeArq,retiraFundo,janela){
            CriaFramesAutomaticosPorLinha(1,1,4);
            MudaFrameAtual(1); //frame de estado normal do botao
            tempoRepeticao = 0.2;
            botaoRepeticao = false;
            timer = new CPIGTimer(false);
        }

    CPIGBotaoClick(int idComponente,int px, int py, int alt,int larg,int janela=0):
        CPIGBotao(idComponente,px,py,alt,larg,janela){
            IniciaCoresBasicas();
            tempoRepeticao = 0.2;
            botaoRepeticao = false;
            timer = new CPIGTimer(false);
        }

    CPIGBotaoClick(int idComponente,CPIGAtributos atrib):CPIGBotaoClick(LeParametros(idComponente,atrib)){}

    virtual ~CPIGBotaoClick(){
        delete timer;
    }

    int TrataEventoTeclado(PIGEvento evento){
        if (evento.teclado.acao==PIG_TECLA_PRESSIONADA && evento.teclado.tecla==tecla){
            if (!habilitado) return PIG_SELECIONADO_DESABILITADO;
            if (!visivel) return PIG_SELECIONADO_INVISIVEL;
            if (timer->GetTempoDecorrido()>tempoRepeticao) return OnAction();
        }

        return 0;
    }

    inline void DefineTempoRepeticao(double segundos){
        tempoRepeticao = segundos;
    }

    inline void DefineBotaoRepeticao(bool repeticao){
        botaoRepeticao = repeticao;
    }

    int Desenha(){
        TrataTimer();
        return CPIGBotao::Desenha();
    }

    inline void SetCorNormal(PIGCor cor){
        coresBasicas[1] = cor;
    }

    inline void SetCorMouseSobre(PIGCor cor){
        coresBasicas[2] = cor;
    }

    inline void SetCorAcionado(PIGCor cor){
        coresBasicas[3] = cor;
    }

    inline void SetCorDesabilitado(PIGCor cor){
        coresBasicas[4] = cor;
    }

};

typedef CPIGBotaoClick *PIGBotaoClick;
#endif // _CPIGBOTAOCLICK_
