#ifndef _CPIGLISTBOX_
#define _CPIGLISTBOX_

#include "CPIGListaItemComponente.h"

class CPIGListBox: public CPIGListaItemComponente{

protected:

    CPIGListBox LeParametros(int idComponente,string parametros){
        CPIGAtributos atrib = CPIGComponente::GetAtributos(parametros);

        CPIGListBox resp(idComponente,atrib.GetInt("px",0),atrib.GetInt("py",0),atrib.GetInt("largura",0),
                          atrib.GetInt("alturaLinha",0),
                          atrib.GetInt("alturaItem",0),atrib.GetInt("larguraItem",0),
                          atrib.GetString("nomeArq",""),atrib.GetInt("retiraFundo",1),atrib.GetInt("janela",0));

        return resp;
    }

    void SetFoco(bool valor){
        temFoco = valor;
    }

    void SetAcionado(bool valor){
    }

    void SetMouseOver(bool valor){
        mouseOver = valor;
    }

    void SetHabilitado(bool valor){
        habilitado = valor;
        for(int i=0;i<itens.size();i++){
            itens[i]->SetHabilitado(valor);
        }
    }

private:

    void DesenhaRetanguloMarcacado(){
        if(itemDestaque !=-1){
            PIGPonto2D p = itens[itemDestaque]->GetXY();
            PIGDesenhaRetanguloVazado(p.x,p.y,altBaseLista,larg,AZUL);
        }
    }

public:

    CPIGListBox(int idComponente,int px, int py,int larguraTotal, int alturaLinha, int alturaItem=0, int larguraItem=0,std::string nomeArqFundo="",int retiraFundo=1,int janela=0):
        CPIGListaItemComponente(idComponente,px,py,larguraTotal,alturaLinha,nomeArqFundo,retiraFundo,janela){
    }

    CPIGListBox(int idComponente,std::string parametros):CPIGListBox(LeParametros(idComponente,parametros)){}

    ~CPIGListBox(){
        for (PIGItemComponente x: itens) delete x;
    }

    int TrataEventoTeclado(PIG_Evento evento)override{
        if(!temFoco||!habilitado||!visivel) return 0;

        if(evento.teclado.acao == PIG_TECLA_PRESSIONADA){
            if(evento.teclado.tecla == PIG_TECLA_CIMA && evento.teclado.repeticao == 0){
                itemDestaque = (itemDestaque + itens.size()-1) %itens.size();
                OnAction();
            }

            if(evento.teclado.tecla == PIG_TECLA_BAIXO && evento.teclado.repeticao == 0){
                itemDestaque = (itemDestaque + 1) % itens.size();
                OnAction();
            }
        }
        return 1;
    }

    int TrataEventoMouse(PIG_Evento evento){
        int resp = -1;
        bool mouseOverAntes = mouseOver;

        SDL_Point p = GetPosicaoMouse();

        if (ChecaMouseOver(p)>0){
            for (int i=0;i<itens.size();i++){
                int aux = itens[i]->TrataEventoMouse(evento);
                if(aux == PIG_SELECIONADO_TRATADO){
                    if (itens[i]->GetAcionado())
                        resp = i;
                    SetHint(itens[i]->GetHint());
                    SetFonteHint(itens[i]->GetFonteHint());
                    OnAction();
                }
            }
            SetAcionado(resp,resp!=-1);
        }else if (mouseOverAntes){               //mouse estava antes, mas saiu
            for (int i=0;i<itens.size();i++){
                itens[i]->SetMouseOver(false);
            }
        }

        return resp>=0?PIG_SELECIONADO_TRATADO:PIG_NAO_SELECIONADO;
    }

    void CriaItem(std::string itemLabel, std::string arqImagemIcone="", std::string arqImagemFundoItem="",bool itemMarcado = false, bool itemHabilitado = true, std::string hintMsg="", int retiraFundo=1){
        int yItem = pos.y+alt-(altBaseLista)*(itens.size()+1);
        CPIGListaItemComponente::CriaItem(yItem,itemLabel,arqImagemIcone,arqImagemFundoItem,itemMarcado,itemHabilitado,hintMsg,retiraFundo);
    }

    int Desenha(){
        if (visivel==false) return 0;

        DesenhaLabel();

        CPIGImagem::Desenha();

        DesenhaRetanguloMarcacado();

        for (PIGItemComponente i: itens)
            i->Desenha();

        return 1;
    }

    int SetAcionado(int indice, bool marcado){
        if (indice<0||indice>=itens.size()) return 0;
        if (marcado){
            itemDestaque = indice;
            for (PIGItemComponente i: itens) i->SetAcionado(false);
        }
        itens[indice]->SetAcionado(marcado);
        return 1;
    }


};
typedef CPIGListBox* PIGListBox;
#endif // _CPIGLISTBOX_
