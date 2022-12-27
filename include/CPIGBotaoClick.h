#ifndef _CPIGBOTAOCLICK_
#define _CPIGBOTAOCLICK_

#include "CPIGBotao.h"

class CPIGBotaoClick: public CPIGBotao{

protected:

    PIGTimer timer;
    double tempoRepeticao,tempoAcionamento;

    void IniciaCoresBasicas(){
        coresBasicas[0] = coresBasicas[1] = AZUL;
        coresBasicas[2] = {100,100,255,255};
        coresBasicas[3] = AMARELO;
        coresBasicas[4] = CINZA;
    }

    virtual void ProcessaAtributos(CPIGAtributos atrib)override{
        CPIGBotao::ProcessaAtributos(atrib);

        float valorFloat = atrib.GetFloat(PIG_STR_TEMPOREPETICAO,-1);
        if (valorFloat > 0) DefineTempoRepeticao(valorFloat);

        valorFloat = atrib.GetFloat(PIG_STR_TEMPOACIONAMENTO,-1);
        if (valorFloat > 0) DefineTempoAcionamento(valorFloat);

        string valorStr = atrib.GetString(PIG_STR_CORNORMAL,"");
        if (valorStr != "") SetCorNormal(PIGCriaCorString(valorStr));

        valorStr = atrib.GetString(PIG_STR_CORMOUSESOBRE,"");
        if (valorStr != "") SetCorMouseSobre(PIGCriaCorString(valorStr));

        valorStr = atrib.GetString(PIG_STR_CORACIONADO,"");
        if (valorStr != "") SetCorAcionado(PIGCriaCorString(valorStr));

        valorStr = atrib.GetString(PIG_STR_CORDESABILITADO,"");
        if (valorStr != "") SetCorDesabilitado(PIGCriaCorString(valorStr));
    }

    static CPIGBotaoClick LeParametros(int idComponente, CPIGAtributos atrib){
        CPIGBotaoClick *resp;

        if (atrib.GetString(PIG_STR_NOMEARQ,"")!=""){
            resp = new CPIGBotaoClick(idComponente,atrib.GetInt(PIG_STR_ALTURA,0),atrib.GetInt(PIG_STR_LARGURA,0),
                       atrib.GetString(PIG_STR_NOMEARQ,""),atrib.GetInt(PIG_STR_RETIRAFUNDO,1),atrib.GetInt(PIG_STR_JANELA,0));
        }else{
            resp = new CPIGBotaoClick(idComponente,atrib.GetInt(PIG_STR_ALTURA,0),atrib.GetInt(PIG_STR_LARGURA,0),atrib.GetInt(PIG_STR_JANELA,0));
        }

        resp->ProcessaAtributos(atrib);

        return *resp;
    }

    void AjustaFrame(){
        if (visivel==false) return;
        int corAtual = 1;
        if (habilitado==false){
            corAtual=4;
        }else{
            if (acionado){
                corAtual=3;
            }else if (mouseOver){
                corAtual=2;
            }
        }

        coresBasicas[0] = coresBasicas[corAtual];
        if (imagemPropria)
            MudaFrameAtual(corAtual);
    }

    void TrataTimer(){
        double tempo = timer->GetTempoDecorrido();
        if (tempo>=tempoRepeticao){
            if (tempoRepeticao>0 && mouseOver && pigMouse.GetEstadoBotaoEsquerdo()==PIG_MOUSE_PRESSIONADO){
                OnAction();
            }
        }else if (tempo>tempoAcionamento)
            SetAcionado(false);
    }

    PIGEstadoEvento OnAction()override{
        if (timer->GetTempoDecorrido()>tempoRepeticao){
            SetAcionado(true);
            timer->Reinicia(false);
        }
        return CPIGComponente::OnAction();
    }

    void IniciaBase(){
        tempoRepeticao = 0.5;
        tempoAcionamento = 0.2;
        timer = pigGerTimers.CriaTimer(false);
        tipo = PIG_BOTAOCLICK;
    }

public:

    CPIGBotaoClick(int idComponente, int alt, int larg, string nomeArq, int retiraFundo=1, int janela=0)
    :CPIGBotao(idComponente,alt,larg,nomeArq,retiraFundo,janela){
        CriaFramesAutomaticosPorLinha(1,1,4);
        MudaFrameAtual(1); //frame de estado normal do botao
        IniciaBase();
    }

    CPIGBotaoClick(int idComponente, int alt, int larg, int janela=0)
    :CPIGBotao(idComponente,alt,larg,janela){
        IniciaCoresBasicas();
        IniciaBase();
    }

    CPIGBotaoClick(int idComponente,CPIGAtributos atrib):CPIGBotaoClick(LeParametros(idComponente,atrib)){}

    virtual ~CPIGBotaoClick(){
        pigGerTimers.Remove(timer->GetID());
    }

    inline void DefineTempoRepeticao(double segundos){
        tempoRepeticao = segundos;
    }

    inline void DefineTempoAcionamento(double segundos){
        tempoAcionamento = segundos;
    }

    int Desenha()override{
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
