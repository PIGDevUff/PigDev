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
        SDL_Rect rectAux = dest;
        rectAux.h = altBaseLista;
        SDL_RenderSetClipRect(renderer,&rectAux);
        if (text){//se tiver imagem de fundo
            dest.h=altBaseLista;
            CPIGSprite::Desenha();
        }
        if (itemDestaque>=0){                       //desenha o item no cabeçalho do dropdown
            PIGPonto2D pItem = itens[itemDestaque]->GetXY();
            itens[itemDestaque]->Move(pItem.x,pos.y);     //move o item para o ponto do cabeçalho
            itens[itemDestaque]->Desenha();         //desenha o item no cabeçalho
            itens[itemDestaque]->Move(pItem.x,pItem.y); //devolve o item para a posição normal (onde também deverá ser desenhado)
        }
        SDL_RenderSetClipRect(renderer,NULL);
    }

    void DesenhaListaItens(){
        SDL_Rect r = dest;

        SDL_RenderSetClipRect(renderer,&r);
        dest.h = (itens.size()+1)*altBaseLista;
        frameAtual=0;
        CPIGSprite::Desenha();

        for (PIGItemComponente i: itens)
            i->Desenha();

        SDL_RenderSetClipRect(renderer,NULL);
    }

public:

    CPIGDropDown(int idComponente,int px, int py,int larguraTotal, int alturaLinha, int alturaItem=0, int larguraItem=0,std::string nomeArqFundo="",int retiraFundo=1,int janela=0):
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
        SDL_Point p;
        if (CPIGGerenciadorJanelas::GetJanela(idJanela)->GetUsandoCameraFixa())
            p = CPIGMouse::PegaXYTela();
        else p = CPIGMouse::PegaXYWorld();
        if (ChecaMouseOver(p)){

            if (!habilitado) return PIG_SELECIONADO_DESABILITADO;
            if (!visivel) return PIG_SELECIONADO_INVISIVEL;

            if (!recolhida){        //se o dropdown está exibindo os itens, é preciso tratá-los individualmente
                for (int i=0;i<itens.size();i++){
                    if(itens[i]->TrataEventoMouse(evento) == PIG_SELECIONADO_TRATADO){
                        if (itens[i]->GetAcionado()){
                            resp = i;
                        }
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
        CPIGSprite::Move(nx,ny);
        SetPosicaoPadraoLabel(posLabel);

        for(int i=0;i<itens.size();i++){
            int posY = pos.y - altBaseLista*(i+1);
            itens[i]->Move(pos.x,posY);
        }
    }

};

typedef CPIGDropDown *PIGDropDown;
#endif // _CPIGDROPDOWN_
