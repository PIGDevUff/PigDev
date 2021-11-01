#ifndef _CPIGCHECKBOX_
#define _CPIGCHECKBOX_

#include "CPIGListaItemComponente.h"

class CPIGCheckBox: public CPIGListaItemComponente{

protected:
    std::string arqImagemIcone;

    CPIGCheckBox LeParametros(int idComponente,string parametros){
        CPIGAtributos atrib = CPIGComponente::GetAtributos(parametros);

        CPIGCheckBox resp(idComponente,atrib.GetInt("px",0),atrib.GetInt("py",0),atrib.GetInt("largura",0),
                          atrib.GetInt("alturaLinha",0),
                          atrib.GetString("nomeArqItem",0),atrib.GetInt("alturaItem",0),atrib.GetInt("larguraItem",0),
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

    static void AjustaFrame(PIGItemComponente item){
        int resp;
        if (item->GetHabilitado()==false){
            if (item->GetAcionado()) resp = 4;
            else resp = 3;
        }else if (item->GetMouseOver()){
            if (item->GetAcionado()) resp = 6;
            else resp = 5;
        }else{
            if (item->GetAcionado()) resp = 2;
            else resp = 1;
        }
        item->GetIcone()->MudaFrameAtual(resp);
    }

public:

    CPIGCheckBox(int idComponente, int posX, int posY, int larguraTotal,int alturaLinha,std::string imgIcone, int alturaIcone, int larguraIcone,std::string imgFundo, int retiraFundo=1,int janela = 0):
        CPIGListaItemComponente(idComponente,posX,posY,larguraTotal,alturaLinha,imgFundo,retiraFundo,janela){
            arqImagemIcone = imgIcone;
        }

    CPIGCheckBox(int idComponente,string parametros):CPIGCheckBox(LeParametros(idComponente,parametros)){}

    void CriaItem(std::string itemLabel, std::string arqImagemFundoItem="", bool itemMarcado = false, bool itemHabilitado = true, std::string hintMsg="", int retiraFundo=1){
        int yItem = pos.y+alt-(altBaseLista)*(itens.size()+1);
        CPIGListaItemComponente::CriaItem(yItem,itemLabel,arqImagemIcone,arqImagemFundoItem,itemMarcado,itemHabilitado,hintMsg,retiraFundo);
        itens[itens.size()-1]->DefineFuncaoAjusteFrame(AjustaFrame);
        PIGSprite icone = itens[itens.size()-1]->GetIcone();
        icone->CriaFramesAutomaticosPorLinha(1,1,6);
        icone->MudaFrameAtual(1);
    }

    int Desenha(){
        if (visivel==false) return 0;

        DesenhaLabel();

        SDL_Rect r = {(int)pos.x,*altJanela-((int)pos.y)-alt,larg,alt};
        SDL_RenderSetClipRect(renderer,&r);

        if (text)//se tiver imagem de fundo
            CPIGSprite::Desenha();

        for (PIGItemComponente i: itens)
            i->Desenha();

        SDL_RenderSetClipRect(renderer,NULL);

        return 1;
    }

    int TrataEventoMouse(PIG_Evento evento){
        int resp = 0;
        bool mouseOverAntes = mouseOver;

        SDL_Point p;
        if (CPIGGerenciadorJanelas::GetJanela(idJanela)->GetUsandoCameraFixa())
            p = CPIGMouse::PegaXYTela();
        else p = CPIGMouse::PegaXYWorld();

        if (ChecaMouseOver(p)>0){
            for (int i=0;i<itens.size();i++){
                if (itens[i]->TrataEventoMouse(evento) == PIG_SELECIONADO_TRATADO)
                    resp = 1;

            }
            if (resp) return PIG_SELECIONADO_TRATADO;
            else return PIG_SELECIONADO_MOUSEOVER;
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

    void SetAcionadoTodos(bool marcado){
        for (PIGItemComponente i: itens){
            i->SetAcionado(marcado);
        }
    }

    int SetAcionadoItem(int indice, bool marcado){
        if (indice<0||indice>=itens.size()) return -1;
        itens[indice]->SetAcionado(marcado);
        return 1;
    }

    std::vector <int> GetItensMarcados(){
        std::vector <int> resp;
        for(int i=0;i<itens.size();i++)
            if(itens[i]->GetAcionado())resp.push_back(i);

        return resp;
    }

    void SetDimensoes(int altura,int largura)override{
        CPIGComponente::SetDimensoes(itens.size()*altBaseLista,largura);

        for(PIGItemComponente i : itens){
            i->SetDimensoes(altIcone,largura);
        }

        Move(pos.x,pos.y);
    }

};

typedef CPIGCheckBox *PIGCheckBox;
#endif // _CPIGCheckBox_
