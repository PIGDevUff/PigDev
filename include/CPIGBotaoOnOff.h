#ifndef _CPIGBOTAOONOFF_
#define _CPIGBOTAOONOFF_

#include "CPIGBotao.h"

class CPIGBotaoOnOff: public CPIGBotao{

protected:

    void IniciaCoresBasicas(){
        coresBasicas[0] = coresBasicas[1] = VERDE;
        coresBasicas[2] = {100,255,100,255};
        coresBasicas[3] = CINZA;
        coresBasicas[4] = VERMELHO;
        coresBasicas[5] = {255,100,100,255};
        coresBasicas[6] = {160,160,160,255};
    }

    virtual void ProcessaAtributos(CPIGAtributos atrib)override{
        CPIGBotao::ProcessaAtributos(atrib);

        string valorStr = atrib.GetString(PIG_STR_CORNORMALOFF,"");
        if (valorStr != "") SetCorNormalOff(PIGCriaCorString(valorStr));

        valorStr = atrib.GetString(PIG_STR_CORMOUSESOBREOFF,"");
        if (valorStr != "") SetCorMouseSobreOff(PIGCriaCorString(valorStr));

        valorStr = atrib.GetString(PIG_STR_CORDESABILITADOOFF,"");
        if (valorStr != "") SetCorDesabilitadoOff(PIGCriaCorString(valorStr));

        valorStr = atrib.GetString(PIG_STR_CORNORMAL,"");
        if (valorStr != "") SetCorNormalOn(PIGCriaCorString(valorStr));

        valorStr = atrib.GetString(PIG_STR_CORMOUSESOBRE,"");
        if (valorStr != "") SetCorMouseSobreOn(PIGCriaCorString(valorStr));

        valorStr = atrib.GetString(PIG_STR_CORDESABILITADO,"");
        if (valorStr != "") SetCorDesabilitadoOn(PIGCriaCorString(valorStr));
    }

    static CPIGBotaoOnOff LeParametros(int idComponente,CPIGAtributos atrib){
        CPIGBotaoOnOff *resp;

        if (atrib.GetString(PIG_STR_NOMEARQ,"")!=""){
            resp = new CPIGBotaoOnOff(idComponente,atrib.GetInt(PIG_STR_ALTURA,0),atrib.GetInt(PIG_STR_LARGURA,0),
                       atrib.GetString(PIG_STR_NOMEARQ,""),atrib.GetInt(PIG_STR_RETIRAFUNDO,1),atrib.GetInt(PIG_STR_JANELA,0));
        }else{
            resp = new CPIGBotaoOnOff(idComponente,atrib.GetInt(PIG_STR_ALTURA,0),atrib.GetInt(PIG_STR_LARGURA,0),atrib.GetInt(PIG_STR_JANELA,0));
        }

        resp->ProcessaAtributos(atrib);

        return *resp;
    }

    void AjustaFrame(){
        int corAtual;
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

        coresBasicas[0] = coresBasicas[corAtual];
        if (imagemPropria){
            MudaFrameAtual(corAtual);
        }
    }

    PIGEstadoEvento OnAction()override{
        SetAcionado(!acionado);
        return CPIGComponente::OnAction();
    }

public:

    CPIGBotaoOnOff(int idComponente, int alt, int larg, string nomeArq, int retiraFundo=1, int janela=0)
    :CPIGBotao(idComponente,alt,larg,nomeArq,retiraFundo,janela){
        CriaFramesAutomaticosPorLinha(1,2,3);
        MudaFrameAtual(1); //frame de estado normal do botao
        tipo = PIG_BOTAOONOFF;
    }

    CPIGBotaoOnOff(int idComponente, int alt, int larg, int janela=0)
    :CPIGBotao(idComponente,alt,larg,janela){
        IniciaCoresBasicas();
        tipo = PIG_BOTAOONOFF;
    }

    CPIGBotaoOnOff(int idComponente,CPIGAtributos atrib):CPIGBotaoOnOff(LeParametros(idComponente,atrib)){}

    inline void SetCorNormalOff(PIGCor cor){
        coresBasicas[1] = cor;
    }

    inline void SetCorMouseSobreOff(PIGCor cor){
        coresBasicas[2] = cor;
    }

    inline void SetCorDesabilitadoOff(PIGCor cor){
        coresBasicas[3] = cor;
    }

    inline void SetCorNormalOn(PIGCor cor){
        coresBasicas[4] = cor;
    }

    inline void SetCorMouseSobreOn(PIGCor cor){
        coresBasicas[5] = cor;
    }

    inline void SetCorDesabilitadoOn(PIGCor cor){
        coresBasicas[6] = cor;
    }
};
typedef CPIGBotaoOnOff *PIGBotaoOnOff;
#endif // _CPIGBOTAOONOFF_
