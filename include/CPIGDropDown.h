#ifndef _CPIGDROPDOWN_
#define _CPIGDROPDOWN_

#include "CPIGListaItemComponente.h"

class CPIGDropDown: public CPIGListaItemComponente{

private:

    bool recolhida;

    CPIGDropDown LeParametros(int idComponente,string parametros){
        CPIGAtributos atrib = CPIGComponente::GetAtributos(parametros);

        CPIGDropDown resp(idComponente,atrib.GetInt("px",0),atrib.GetInt("py",0),atrib.GetInt("largura",0),
                          atrib.GetInt("alturaLinha",0),
                          atrib.GetInt("alturaItem",0),atrib.GetInt("larguraItem",0),
                          atrib.GetString("nomeArq",""),atrib.GetInt("retiraFundo",1),atrib.GetInt("janela",0));

        return resp;
    }

    void SetFoco(bool valor)override{
        temFoco = valor;
        if (!temFoco){
            SetRecolhida(true);
        }
    }

    void SetAcionado(bool valor){
    }

    void SetMouseOver(bool valor){
        mouseOver = valor;
    }

    void SetRecolhida(bool valor){
        recolhida = valor;
    }

    int ChecaMouseOver(SDL_Point pMouse)override{
        SDL_Rect r={(int)pos.x,0,larg,0};
        if (recolhida){
            r.y = (int)pos.y;
            r.h = altBaseLista;
        }else{
            r.y = ((int)pos.y)-(itens.size())*altBaseLista;
            r.h = (itens.size()+1)*altBaseLista;
        }
        SetMouseOver(SDL_PointInRect(&pMouse,&r));

        return mouseOver;
    }

    void DesenhaItemDestaque(){
        CPIGImagem::SetDimensoes(altBaseLista,larg);
        CPIGImagem::Desenha();

        if (itemDestaque>=0){                       //desenha o item no cabeçalho do dropdown
            PIGPonto2D pItem = itens[itemDestaque]->GetXY();
            itens[itemDestaque]->Move(pItem.x,pos.y);     //move o item para o ponto do cabeçalho
            itens[itemDestaque]->Desenha();         //desenha o item no cabeçalho
            itens[itemDestaque]->Move(pItem.x,pItem.y); //devolve o item para a posiçăo normal (onde também deverá ser desenhado)
        }
    }

    void DesenhaListaItens(){
        pos.y -= altBaseLista*itens.size();         //ajusta a posição para o fundo ser desenhado por trás da lista
        CPIGImagem::SetDimensoes(altBaseLista*itens.size(),larg); //ajusta a dimensão para ficar do tamanho da lista aberta
        CPIGImagem::Desenha();                      //desenha a lista aberta

        pos.y += altBaseLista*itens.size();         //volta à posição normal

        for (PIGItemComponente i: itens)            //desenha os itens individualmente
            i->Desenha();

    }

public:

    CPIGDropDown(int idComponente,int px, int py,int larguraTotal, int alturaLinha,int alturaItem=0, int larguraItem=0,std::string nomeArqFundo="",int retiraFundo=1,int janela=0):
        CPIGListaItemComponente(idComponente,px,py,larguraTotal,alturaLinha,nomeArqFundo,retiraFundo,janela){
            SetRecolhida(true);
    }

    CPIGDropDown(int idComponente,string parametros):CPIGDropDown(LeParametros(idComponente,parametros)){}

    void CriaItem(std::string itemLabel, std::string arqImagemIcone="",std::string arqImagemFundoItem="", bool itemHabilitado = true, std::string hintMsg="", int retiraFundo=1){
        int yItem=pos.y-(itens.size()+1)*altBaseLista;
        CPIGListaItemComponente::CriaItem(yItem,itemLabel,arqImagemIcone,arqImagemFundoItem,false,itemHabilitado,hintMsg,retiraFundo);
    }

    int Desenha(){
        if (visivel==false) return 0;

        DesenhaLabel();

        CPIGImagem::Desenha();

        if (recolhida){
            DesenhaItemDestaque();
        }else{
            DesenhaListaItens();
        }

        return 1;
    }

    int TrataEventoMouse(PIG_Evento evento){
        int resp = -1;
        bool mouseOverAntes = mouseOver;
        SDL_Point p = GetPosicaoMouse();

        if (ChecaMouseOver(p)){

            if (!habilitado) return PIG_SELECIONADO_DESABILITADO;
            if (!visivel) return PIG_SELECIONADO_INVISIVEL;

            if (!recolhida){        //se o dropdown está exibindo os itens, é preciso tratá-los individualmente
                for (int i=0;i<itens.size();i++){
                    if(itens[i]->TrataEventoMouse(evento) == PIG_SELECIONADO_TRATADO){
                        if (itens[i]->GetAcionado()){
                            resp = i;
                        }
                        OnAction();
                    }
                }
                SetAcionadoItem(resp,resp!=-1);

                if (evento.mouse.acao == PIG_MOUSE_PRESSIONADO && evento.mouse.botao == PIG_MOUSE_ESQUERDO){
                    SetRecolhida(!recolhida);
                }

                if (resp>=0) return PIG_SELECIONADO_TRATADO;
                else return PIG_SELECIONADO_MOUSEOVER;
            }
            if (evento.mouse.acao == PIG_MOUSE_PRESSIONADO && evento.mouse.botao == PIG_MOUSE_ESQUERDO){
                SetRecolhida(!recolhida);
                return PIG_SELECIONADO_TRATADO;
            }
        }else if (mouseOverAntes){               //mouse estava antes, mas saiu
            for (int i=0;i<itens.size();i++){
                itens[i]->SetMouseOver(false);
            }
        }

        return PIG_NAO_SELECIONADO;
    }

    int TrataEventoTeclado(PIG_Evento evento){
        return 0;
    }

    void Move(double nx,double ny){
        CPIGImagem::Move(nx,ny);
        SetPosicaoPadraoLabel(posLabel);
        int posY;

        for(int i=0;i<itens.size();i++){
            posY = pos.y - altBaseLista*(i+1);
            itens[i]->Move(pos.x,posY);
        }
    }

};

typedef CPIGDropDown *PIGDropDown;
#endif // _CPIGDROPDOWN_
