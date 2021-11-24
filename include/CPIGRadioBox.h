#ifndef _CPIGRADIOBOX_
#define _CPIGRADIOBOX_

#include "CPIGListaItemComponente.h"

class CPIGRadioBox: public CPIGListaItemComponente{

protected:

    string arqImagemIcone;

    virtual void ProcessaAtributos(CPIGAtributos atrib)override{
        CPIGListaItemComponente::ProcessaAtributos(atrib);
    }

    static CPIGRadioBox LeParametros(int idComponente,CPIGAtributos atrib){
        CPIGRadioBox *resp;

        if (atrib.GetString("nomeArq","")!=""){
            resp = new CPIGRadioBox(idComponente,atrib.GetInt("largura",0),atrib.GetInt("alturaLinha",0),
                          atrib.GetString("nomeArqItem",""),atrib.GetInt("alturaItem",0),atrib.GetInt("larguraItem",0),
                          atrib.GetString("nomeArq",""),atrib.GetInt("retiraFundo",1),atrib.GetInt("janela",0));
        }else{
            resp = new CPIGRadioBox(idComponente,atrib.GetInt("largura",0),atrib.GetInt("alturaLinha",0),
                          atrib.GetString("nomeArqItem",""),atrib.GetInt("alturaItem",0),atrib.GetInt("larguraItem",0),atrib.GetInt("janela",0));
        }

        resp->ProcessaAtributos(atrib);

        return *resp;
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
            if (item->GetAcionado()) resp = 6;
            else resp = 5;
        }else if (item->GetMouseOver()){
            if (item->GetAcionado()) resp = 4;
            else resp = 3;
        }else{
            if (item->GetAcionado()) resp = 2;
            else resp = 1;
        }
        item->GetIcone()->MudaFrameAtual(resp);
    }

public:

    CPIGRadioBox(int idComponente, int larguraTotal, int alturaLinha, string imgIcone, int alturaIcone, int larguraIcone, string imgFundo, int retiraFundo=1, int janela = 0):
        CPIGListaItemComponente(idComponente,larguraTotal,alturaLinha,imgFundo,retiraFundo,janela){
            arqImagemIcone = imgIcone;
        }

    CPIGRadioBox(int idComponente, int larguraTotal, int alturaLinha, string imgIcone, int alturaIcone, int larguraIcone, int janela = 0):
        CPIGListaItemComponente(idComponente,larguraTotal,alturaLinha,janela){
            arqImagemIcone = imgIcone;
        }

    CPIGRadioBox(int idComponente,CPIGAtributos atrib):CPIGRadioBox(LeParametros(idComponente,atrib)){}

    virtual ~CPIGRadioBox(){}

    void CriaItem(string itemLabel, string arqImagemFundoItem="", bool itemHabilitado = true, string hintMsg="", int retiraFundo=1, int retiraFundoIcone=1){
        int yItem = pos.y+alt-(altBaseLista)*(itens.size()+1);
        CPIGListaItemComponente::CriaItem(yItem,itemLabel,arqImagemIcone,arqImagemFundoItem,false,itemHabilitado,hintMsg,retiraFundo,retiraFundoIcone);
        itens[itens.size()-1]->DefineFuncaoAjusteFrame(AjustaFrame);
        PIGSprite icone = itens[itens.size()-1]->GetIcone();
        icone->CriaFramesAutomaticosPorLinha(1,1,6);
        //icone->MudaFrameAtual(1);
        AjustaFrame(itens[itens.size()-1]);
    }

    int Desenha()override{
        if (visivel==false) return 0;

        DesenhaLabel();

        CPIGGerenciadorJanelas::GetJanela(idJanela)->BloqueiaArea(pos.x,pos.y,alt,larg);

        if (text)//se tiver imagem de fundo
            CPIGSprite::Desenha();
        else CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetangulo((int)pos.x,(int)pos.y,alt,larg,coresBasicas[0]);

        for (PIGItemComponente i: itens)
            i->Desenha();

        CPIGGerenciadorJanelas::GetJanela(idJanela)->DesbloqueiaArea();

        return 1;
    }

    int TrataEventoMouse(PIGEvento evento){
        int resp = -1;
        bool mouseOverAntes = mouseOver;

        SDL_Point p = GetPosicaoMouse();

        if (ChecaMouseOver(p)>0){
            for (unsigned int i=0;i<itens.size();i++){
                if (itens[i]->TrataEventoMouse(evento) == PIG_SELECIONADO_TRATADO){
                    if (itens[i]->GetAcionado())
                        resp = i;
                    OnAction();
                }
            }
            SetAcionadoItem(resp,resp!=-1);
            if (resp>0)
                return PIG_SELECIONADO_TRATADO;
            else return PIG_SELECIONADO_MOUSEOVER;
        }else if (mouseOverAntes){               //mouse estava antes, mas saiu
            for (unsigned int i=0;i<itens.size();i++){
                itens[i]->SetMouseOver(false);
            }
        }

        return PIG_NAO_SELECIONADO;
    }

    int TrataEventoTeclado(PIGEvento evento){
        return 0;
    }

    void SetDimensoes(int altura, int largura)override{
        CPIGComponente::SetDimensoes(itens.size()*altBaseLista,largura);

        for(PIGItemComponente i : itens){
            i->SetDimensoes(altIcone,largura);
        }

        Move(pos.x,pos.y);
    }

};

typedef CPIGRadioBox *PIGRadioBox;
#endif // _CPIGRADIOBOX_
