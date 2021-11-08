#ifndef _CPIGBOTAO_
#define _CPIGBOTAO_

#include "CPIGComponente.h"

class CPIGBotao: public CPIGComponente{

protected:

    int tecla;

    void SetFoco(bool valor){
        temFoco = valor;
    }

    void SetAcionado(bool valor){
        if (acionado&&!valor)
            Desloca(-offX,+offY);
        else if (!acionado&&valor)
            Desloca(offX,-offY);
        acionado = valor;
        AjustaFrame();
    }

    void SetMouseOver(bool valor){
        mouseOver = valor;
        AjustaFrame();
    }

    virtual void AjustaFrame()=0;

    CPIGBotao(int idComponente,int px, int py, int alt,int larg,std::string nomeArq, int retiraFundo=1,int janela=0):
        CPIGComponente(idComponente,px,py,alt,larg,nomeArq,retiraFundo,janela){
            tecla = PIG_TECLA_ENTER;//sem tecla de atalho
            SetPosicaoPadraoLabel(PIG_COMPONENTE_CENTRO_CENTRO);
        }

    CPIGBotao(int idComponente,int px, int py, int alt,int larg,int janela=0):
        CPIGComponente(idComponente,px,py,alt,larg,janela){
            tecla = PIG_TECLA_ENTER;//sem tecla de atalho
            SetPosicaoPadraoLabel(PIG_COMPONENTE_CENTRO_CENTRO);
        }

    //CPIGBotao(int idComponente,std::string nomeArqParam):CPIGBotao(LeParametros(idComponente,nomeArqParam)){}

    virtual ~CPIGBotao(){}

public:

    int TrataEventoMouse(PIG_Evento evento){
        SDL_Point p = GetPosicaoMouse();

        //printf("mouse %d,%d\n",p.x,p.y);
        ChecaMouseOver(p);

        if (mouseOver){
            //printf("over\n");
            if (!habilitado) return PIG_SELECIONADO_DESABILITADO;
            if (!visivel) return PIG_SELECIONADO_INVISIVEL;
            if(evento.mouse.acao==PIG_MOUSE_PRESSIONADO && evento.mouse.botao == PIG_MOUSE_ESQUERDO) return OnAction();
            return PIG_SELECIONADO_MOUSEOVER;
        }

        return PIG_NAO_SELECIONADO;
    }

    virtual int TrataEventoTeclado(PIG_Evento evento)=0;

    void DefineAtalho(int teclaAtalho){
        tecla = teclaAtalho;
    }

    void SetHabilitado(bool valor){
        habilitado = valor;
        AjustaFrame();
    }

    int Desenha(){
        if (visivel==false) return 0;

        if (text)
            CPIGSprite::Desenha();
        else CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetangulo((int)pos.x,(int)pos.y,alt,larg,coresBasicas[corAtual]);

        DesenhaLabel();

        EscreveHint();

        return 1;
    }

};

typedef CPIGBotao *PIGBotao;
#endif // _CPIGBOTAO_
