#ifndef _CPIGBOTAOONOFF_
#define _CPIGBOTAOONOFF_

#include "CPIGBotao.h"

class CPIGBotaoOnOff: public CPIGBotao{

protected:

    static CPIGBotaoOnOff LeParametros(int idComponente,string parametros){
        CPIGAtributos atrib = CPIGComponente::GetAtributos(parametros);

        CPIGBotaoOnOff resp(idComponente,atrib.GetInt("px",0),atrib.GetInt("py",0),atrib.GetInt("altura",0),atrib.GetInt("largura",0),
                       atrib.GetString("nomeArq",""),atrib.GetInt("retiraFundo",1),atrib.GetInt("janela",0));
        return resp;
    }

    void AjustaFrame(){
        if (acionado){
            if (habilitado==false){
                MudaFrameAtual(6);
            }
            else if (mouseOver){
                MudaFrameAtual(5);
            }else MudaFrameAtual(4);
        }else{
            if (habilitado==false){
                MudaFrameAtual(3);
            }
            else if (mouseOver){
                MudaFrameAtual(2);
            }else MudaFrameAtual(1);
        }
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

    CPIGBotaoOnOff(int idComponente,std::string nomeArqParam):CPIGBotaoOnOff(LeParametros(idComponente,nomeArqParam)){}

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
