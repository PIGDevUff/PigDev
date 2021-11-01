#ifndef _CPIGBOTAOCLICK_
#define _CPIGBOTAOCLICK_

#include "CPIGBotao.h"

class CPIGBotaoClick: public CPIGBotao{

protected:

    PIGTimer timer;
    bool botaoRepeticao;
    double tempoRepeticao;

    static CPIGBotaoClick LeParametros(int idComponente,string parametros){
        CPIGAtributos atrib = CPIGComponente::GetAtributos(parametros);

        CPIGBotaoClick resp(idComponente,atrib.GetInt("px",0),atrib.GetInt("py",0),atrib.GetInt("altura",0),atrib.GetInt("largura",0),
                       atrib.GetString("nomeArq",""),atrib.GetInt("retiraFundo",1),atrib.GetInt("janela",0));
        return resp;
    }

    void AjustaFrame(){
        if (visivel==false) return;
        MudaFrameAtual(1);
        if (habilitado==false){
            MudaFrameAtual(4);
        }else{
            if (acionado){
                MudaFrameAtual(3);
            }else if (mouseOver){
                MudaFrameAtual(2);
            }
        }
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

    CPIGBotaoClick(int idComponente,std::string nomeArqParam):CPIGBotaoClick(LeParametros(idComponente,nomeArqParam)){}

    ~CPIGBotaoClick(){
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
