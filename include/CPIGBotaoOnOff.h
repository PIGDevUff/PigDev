#ifndef _CPIGBOTAOONOFF_
#define _CPIGBOTAOONOFF_

#include "CPIGBotao.h"

class CPIGBotaoOnOff: public CPIGBotao{

protected:

    void IniciaCoresBasicas(){
        coresBasicas[1] = VERDE;
        coresBasicas[2] = {100,255,100,255};
        coresBasicas[3] = CINZA;
        coresBasicas[4] = VERMELHO;
        coresBasicas[5] = {255,100,100,255};
        coresBasicas[6] = {160,160,160,255};
        corAtual = 1;
    }

    static CPIGBotaoOnOff LeParametros(int idComponente,string parametros){
        CPIGAtributos atrib = CPIGComponente::GetAtributos(parametros);

        if (atrib.GetString("nomeArq","")!=""){
            CPIGBotaoOnOff resp(idComponente,atrib.GetInt("px",0),atrib.GetInt("py",0),atrib.GetInt("altura",0),atrib.GetInt("largura",0),
                       atrib.GetString("nomeArq",""),atrib.GetInt("retiraFundo",1),atrib.GetInt("janela",0));
            return resp;
        }else{
            CPIGBotaoOnOff resp(idComponente,atrib.GetInt("px",0),atrib.GetInt("py",0),atrib.GetInt("altura",0),atrib.GetInt("largura",0),
                       atrib.GetInt("janela",0));
            return resp;
        }
    }

    void AjustaFrame(){
        if (acionado){
            if (habilitado==false){
                corAtual = 6;
            }
            else if (mouseOver){
                corAtual = 5;
            }else corAtual = 4;
        }else{
            if (habilitado==false){
                corAtual = 3;
            }
            else if (mouseOver){
                corAtual = 2;
            }else corAtual = 1;
        }

        if (text)
            MudaFrameAtual(corAtual);
    }

    int OnAction() override{
        SetAcionado(!acionado);
        return CPIGComponente::OnAction();
    }

public:

    CPIGBotaoOnOff(int idComponente,int px, int py, int alt,int larg,std::string nomeArq, int retiraFundo=1,int janela=0):
        CPIGBotao(idComponente,px,py,alt,larg,nomeArq,retiraFundo,janela){
            CriaFramesAutomaticosPorLinha(1,2,3);
            MudaFrameAtual(1); //frame de estado normal do botao
        }

    CPIGBotaoOnOff(int idComponente,int px, int py, int alt,int larg,int janela=0):
        CPIGBotao(idComponente,px,py,alt,larg,janela){
            IniciaCoresBasicas();
        }

    CPIGBotaoOnOff(int idComponente,string parametros):CPIGBotaoOnOff(LeParametros(idComponente,parametros)){}

    int TrataEventoTeclado(PIG_Evento evento){
        if (evento.teclado.acao==PIG_TECLA_PRESSIONADA && evento.teclado.tecla==tecla){
            if (!habilitado) return PIG_SELECIONADO_DESABILITADO;
            if (!visivel) return PIG_SELECIONADO_INVISIVEL;
            return OnAction();
        }
        return 0;
    }

};

typedef CPIGBotaoOnOff *PIGBotaoOnOff;
#endif // _CPIGBOTAOONOFF_
