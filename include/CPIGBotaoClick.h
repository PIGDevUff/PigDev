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

    static CPIGBotaoClick LeParametros(int idComponente,string parametros){
        CPIGAtributos atrib = CPIGComponente::GetAtributos(parametros);

        if (atrib.GetString("nomeArq","")!=""){
            CPIGBotaoClick resp(idComponente,atrib.GetInt("px",0),atrib.GetInt("py",0),atrib.GetInt("altura",0),atrib.GetInt("largura",0),
                       atrib.GetString("nomeArq",""),atrib.GetInt("retiraFundo",1),atrib.GetInt("janela",0));
            return resp;
        }else{
            CPIGBotaoClick resp(idComponente,atrib.GetInt("px",0),atrib.GetInt("py",0),atrib.GetInt("altura",0),atrib.GetInt("largura",0),
                       atrib.GetInt("janela",0));
            return resp;
        }
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

    CPIGBotaoClick(int idComponente,std::string nomeArqParam):CPIGBotaoClick(LeParametros(idComponente,nomeArqParam)){}

    virtual ~CPIGBotaoClick(){
        delete timer;
    }

    int TrataEventoTeclado(PIG_Evento evento){
        if (evento.teclado.acao==PIG_TECLA_PRESSIONADA && evento.teclado.tecla==tecla){
            if (!habilitado) return PIG_SELECIONADO_DESABILITADO;
            if (!visivel) return PIG_SELECIONADO_INVISIVEL;
            if (timer->GetTempoDecorrido()>tempoRepeticao) return OnAction();
        }

        return 0;
    }

    void DefineTempoRepeticao(double segundos){
        tempoRepeticao = segundos;
    }

    void DefineBotaoRepeticao(bool repeticao){
        botaoRepeticao = repeticao;
    }

    int Desenha(){
        TrataTimer();
        return CPIGBotao::Desenha();
    }

};

typedef CPIGBotaoClick *PIGBotaoClick;
#endif // _CPIGBOTAOCLICK_
