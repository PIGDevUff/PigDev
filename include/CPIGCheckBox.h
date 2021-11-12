#ifndef _CPIGCHECKBOX_
#define _CPIGCHECKBOX_

#include "CPIGListaItemComponente.h"

class CPIGCheckBox: public CPIGListaItemComponente{

protected:

    string arqImagemIcone;

    virtual void ProcessaAtributos(CPIGAtributos atrib)override{
        CPIGComponente::ProcessaAtributos(atrib);
    }

    static CPIGCheckBox LeParametros(int idComponente,CPIGAtributos atrib){
        CPIGCheckBox *resp;

        if (atrib.GetString("nomeArq","")!=""){
            resp = new CPIGCheckBox(idComponente,atrib.GetInt("px",0),atrib.GetInt("py",0),atrib.GetInt("largura",0),atrib.GetInt("alturaLinha",0),
                          atrib.GetString("nomeArqItem",""),atrib.GetInt("alturaItem",0),atrib.GetInt("larguraItem",0),
                          atrib.GetString("nomeArq",""),atrib.GetInt("retiraFundo",1),atrib.GetInt("janela",0));
        }else{
            resp = new CPIGCheckBox(idComponente,atrib.GetInt("px",0),atrib.GetInt("py",0),atrib.GetInt("largura",0),atrib.GetInt("alturaLinha",0),
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

    CPIGCheckBox(int idComponente, int posX, int posY, int larguraTotal, int alturaLinha, string imgIcone, int alturaIcone, int larguraIcone, string imgFundo, int retiraFundo=1, int janela = 0):
        CPIGListaItemComponente(idComponente,posX,posY,larguraTotal,alturaLinha,imgFundo,retiraFundo,janela){
            arqImagemIcone = imgIcone;
        }

    CPIGCheckBox(int idComponente, int posX, int posY, int larguraTotal, int alturaLinha, string imgIcone, int alturaIcone, int larguraIcone, int janela = 0):
        CPIGListaItemComponente(idComponente,posX,posY,larguraTotal,alturaLinha,janela){
            arqImagemIcone = imgIcone;
        }

    CPIGCheckBox(int idComponente,CPIGAtributos atrib):CPIGCheckBox(LeParametros(idComponente,atrib)){}

    virtual ~CPIGCheckBox(){}

    void CriaItem(string itemLabel, string arqImagemFundoItem="", bool itemMarcado = false, bool itemHabilitado = true, string hintMsg="", int retiraFundo=1){
        int yItem = pos.y+alt-(altBaseLista)*(itens.size()+1);
        CPIGListaItemComponente::CriaItem(yItem,itemLabel,arqImagemIcone,arqImagemFundoItem,itemMarcado,itemHabilitado,hintMsg,retiraFundo);
        itens[itens.size()-1]->DefineFuncaoAjusteFrame(AjustaFrame);
        PIGSprite icone = itens[itens.size()-1]->GetIcone();
        icone->CriaFramesAutomaticosPorLinha(1,1,6);
        icone->MudaFrameAtual(1);
    }

    int Desenha(){
        if (visivel==false) return -1;

        DesenhaLabel();

        CPIGGerenciadorJanelas::GetJanela(idJanela)->BloqueiaArea(pos.x,pos.y,alt,larg);
        if (text)//se tiver imagem de fundo
            CPIGSprite::Desenha();
        else CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetangulo((int)pos.x,(int)pos.y,alt,larg,coresBasicas[corAtual]);

        for (PIGItemComponente i: itens)
            i->Desenha();

        CPIGGerenciadorJanelas::GetJanela(idJanela)->DesbloqueiaArea();

        return 1;
    }

    int TrataEventoMouse(PIGEvento evento){
        int resp = 0;
        bool mouseOverAntes = mouseOver;

        SDL_Point p = GetPosicaoMouse();

        if (ChecaMouseOver(p)>0){
            for (unsigned int i=0;i<itens.size();i++){
                if (itens[i]->TrataEventoMouse(evento) == PIG_SELECIONADO_TRATADO){
                    resp = 1;
                    OnAction();
                }
            }
            if (resp) return PIG_SELECIONADO_TRATADO;
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

    vector <int> GetItensMarcados(){
        vector <int> resp;
        for(unsigned int i=0;i<itens.size();i++)
            if(itens[i]->GetAcionado())resp.push_back(i);

        return resp;
    }

    void SetDimensoes(int altura, int largura)override{
        CPIGComponente::SetDimensoes(itens.size()*altBaseLista,largura);

        for(PIGItemComponente i : itens){
            i->SetDimensoes(altIcone,largura);
        }

        Move(pos.x,pos.y);
    }

};

typedef CPIGCheckBox *PIGCheckBox;
#endif // _CPIGCheckBox_
