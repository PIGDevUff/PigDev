#ifndef _CPIGBOTAO_
#define _CPIGBOTAO_

#include "CPIGComponente.h"

class CPIGBotao: public CPIGComponente{

protected:

    int tecla;

    virtual void ProcessaAtributos(CPIGAtributos atrib)override{
        CPIGComponente::ProcessaAtributos(atrib);
    }

    void SetAcionado(bool valor)override{
        if (acionado&&!valor){
            Desloca(-margemEsq,margemCima);
            //SetDimensoes(alt-(margemCima+margemBaixo),larg-(margemEsq+margemDir));
        }else if (!acionado&&valor){
            Desloca(margemEsq,-margemCima);
            //SetDimensoes(alt+(margemCima+margemBaixo),larg+(margemEsq+margemDir));
        }
        CPIGComponente::SetAcionado(valor);
        AjustaFrame();
    }

    void SetMouseOver(bool valor)override{
        CPIGComponente::SetMouseOver(valor);
        AjustaFrame();
    }

    void SetHabilitado(bool valor)override{
        CPIGComponente::SetHabilitado(valor);
        AjustaFrame();
    }

    virtual void AjustaFrame()=0;

    CPIGBotao(int idComponente, int alt, int larg, string nomeArq, int retiraFundo=1, int janela=0):
        CPIGComponente(idComponente,alt,larg,nomeArq,retiraFundo,janela){
            tecla = PIG_TECLA_ENTER;//sem tecla de atalho
            SetPosicaoPadraoLabel(PIG_POSICAO_CENTRO_CENTRO);
        }

    CPIGBotao(int idComponente, int alt, int larg, int janela=0):
        CPIGComponente(idComponente,alt,larg,janela){
            tecla = PIG_TECLA_ENTER;//sem tecla de atalho
            SetPosicaoPadraoLabel(PIG_POSICAO_CENTRO_CENTRO);
        }

    virtual ~CPIGBotao(){}

public:

    PIGEstadoEvento TrataEventoMouse(PIGEvento evento)override{
        if (!habilitado) return PIG_COMPONENTE_DESABILITADO;
        if (!visivel) return PIG_COMPONENTE_INVISIVEL;

        ChecaMouseOver(GetPosicaoMouse());

        if (mouseOver){
            if(evento.mouse.acao==PIG_MOUSE_PRESSIONADO && evento.mouse.botao == PIG_MOUSE_ESQUERDO)
                return OnAction();
            return PIG_COMPONENTE_MOUSEOVER;
        }

        return PIG_COMPONENTE_NAOTRATADO;
    }

    PIGEstadoEvento TrataEventoTeclado(PIGEvento evento)override{
        if (!habilitado) return PIG_COMPONENTE_DESABILITADO;
        if (!visivel) return PIG_COMPONENTE_INVISIVEL;

        if (evento.teclado.acao==PIG_TECLA_PRESSIONADA && evento.teclado.tecla==tecla){
            return OnAction();
        }
        return PIG_COMPONENTE_NAOTRATADO;
    }

    void DefineAtalho(int teclaAtalho){
        tecla = teclaAtalho;
    }

    int Desenha()override{
        if (visivel==false) return 0;

        CPIGGerenciadorJanelas::GetJanela(idJanela)->BloqueiaArea(pos.x,pos.y,alt,larg);

        if (imagemPropria)
            CPIGSprite::Desenha();
        else CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetangulo((int)pos.x,(int)pos.y,alt,larg,coresBasicas[0]);

        CPIGGerenciadorJanelas::GetJanela(idJanela)->DesbloqueiaArea();

        return CPIGComponente::Desenha();
    }

};

typedef CPIGBotao *PIGBotao;
#endif // _CPIGBOTAO_
