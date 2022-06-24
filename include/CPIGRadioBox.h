#ifndef _CPIGRADIOBOX_
#define _CPIGRADIOBOX_

#include "CPIGListaItemComponente.h"

class CPIGRadioBox: public CPIGListaItemComponente{

protected:

    int itemDestaque;
    string arqImagemIcone;

    virtual void ProcessaAtributos(CPIGAtributos atrib)override{
        CPIGListaItemComponente::ProcessaAtributos(atrib);
    }

    static CPIGRadioBox LeParametros(int idComponente, CPIGAtributos atrib){
        CPIGRadioBox *resp;

        if (atrib.GetString("nomeArq","")!=""){
            resp = new CPIGRadioBox(idComponente,atrib.GetInt("largura",0),atrib.GetInt("alturaLinha",0),
                          atrib.GetString("nomeArqIcone",""),atrib.GetInt("alturaIcone",0),atrib.GetInt("larguraIcone",0),
                          atrib.GetString("nomeArq",""),atrib.GetInt("retiraFundo",1),atrib.GetInt("janela",0));
        }else{
            resp = new CPIGRadioBox(idComponente,atrib.GetInt("largura",0),atrib.GetInt("alturaLinha",0),
                          atrib.GetString("nomeArqIcone",""),atrib.GetInt("alturaIcone",0),atrib.GetInt("larguraIcone",0),atrib.GetInt("janela",0));
        }

        resp->ProcessaAtributos(atrib);

        return *resp;
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
            itemDestaque = -1;
            tipo = PIG_RADIOBOX;
        }

    CPIGRadioBox(int idComponente, int larguraTotal, int alturaLinha, string imgIcone, int alturaIcone, int larguraIcone, int janela = 0):
        CPIGListaItemComponente(idComponente,larguraTotal,alturaLinha,janela){
            arqImagemIcone = imgIcone;
            itemDestaque = -1;
            tipo = PIG_RADIOBOX;
        }

    CPIGRadioBox(int idComponente,CPIGAtributos atrib):CPIGRadioBox(LeParametros(idComponente,atrib)){}

    virtual ~CPIGRadioBox(){}

    int GetItemDestaque(){
        return itemDestaque;
    }

    int SetAcionadoItem(int indice, bool valor)override{
        int resp = CPIGListaItemComponente::SetAcionadoApenasItem(indice,valor);
        if (resp) itemDestaque = indice;
        return resp;
    }

    void CriaItem(string itemLabel, string arqImagemFundoItem="", bool itemHabilitado = true, string hintMsg="", int retiraFundo=1, int retiraFundoIcone=1){
        CPIGListaItemComponente::SetDimensoes(alt+altBaseLista,larg); //aumenta o tamanho do componente para comportar o novo item
        DeslocaItens(0,altBaseLista);//desloca todos os itens para cima, pois o novo item vai entrar abaixo dos outros

        int yItem = pos.y+margemBaixo;
        PIGItemComponente item = CPIGListaItemComponente::CriaItem(yItem,itemLabel,arqImagemIcone,arqImagemFundoItem,false,itemHabilitado,hintMsg,retiraFundo,retiraFundoIcone);
        item->DefineFuncaoAjusteFrame(AjustaFrame);
        item->GetIcone()->CriaFramesAutomaticosPorLinha(1,1,6);
        AjustaFrame(item);
    }

    void CriaItem(CPIGAtributos atrib){
        CPIGListaItemComponente::SetDimensoes(alt+altBaseLista,larg); //aumenta o tamanho do componente para comportar o novo item
        DeslocaItens(0,altBaseLista);//desloca todos os itens para cima, pois o novo item vai entrar abaixo dos outros

        int yItem = pos.y+margemBaixo;
        PIGItemComponente item = CPIGListaItemComponente::CriaItem(yItem,atrib.GetString("label",""),arqImagemIcone,atrib.GetString("nomeArq",""),
                                                                   false,atrib.GetInt("habilitado",1),atrib.GetString("hint",""),atrib.GetInt("retiraFundo",1),atrib.GetInt("retiraFundoIcone",1));
        item->DefineFuncaoAjusteFrame(AjustaFrame);
        item->GetIcone()->CriaFramesAutomaticosPorLinha(1,1,6);
        AjustaFrame(item);
    }

    int Desenha()override{
        if (visivel==false) return 0;

        CPIGGerenciadorJanelas::GetJanela(idJanela)->BloqueiaArea(pos.x,pos.y,alt,larg);

        if (imagemPropria)//se tiver imagem de fundo
            CPIGSprite::Desenha();
        else CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetangulo((int)pos.x,(int)pos.y,alt,larg,coresBasicas[0]);

        for (PIGItemComponente i: itens)
            i->Desenha();

        CPIGGerenciadorJanelas::GetJanela(idJanela)->DesbloqueiaArea();

        return CPIGComponente::Desenha();
    }

    PIGEstadoEvento TrataEventoMouse(PIGEvento evento)override{
        if (!habilitado) return PIG_COMPONENTE_DESABILITADO;
        if (!visivel) return PIG_COMPONENTE_INVISIVEL;

        int resp = itemDestaque;
        bool mouseOverAntes = mouseOver;

        if (ChecaMouseOver(GetPosicaoMouse())>0){
            for (unsigned int i=0;i<itens.size();i++){
                if (itens[i]->TrataEventoMouse(evento) == PIG_COMPONENTE_TRATADO){
                    if (itens[i]->GetAcionado())
                        resp = i;

                    SetAcionadoApenasItem(resp,resp!=-1);
                    itemDestaque = resp;
                    OnAction();
                    break;
                }
            }

            if (resp>0)
                return PIG_COMPONENTE_TRATADO;
            else return PIG_COMPONENTE_MOUSEOVER;
        }else if (mouseOverAntes){               //mouse estava antes, mas saiu
            for (PIGItemComponente i: itens){
                i->SetMouseOver(false);
            }
        }

        return PIG_COMPONENTE_NAOTRATADO;
    }

    void SetDimensoes(int altura, int largura)override{
        CPIGComponente::SetDimensoes(itens.size()*altBaseLista,largura);

        for(PIGItemComponente i : itens){
            i->SetDimensoes(altIcone,largura);
        }

        Move(pos.x,pos.y);
    }

    virtual void SetMargens(int mEsq, int mDir, int mCima, int mBaixo)override{
        CPIGListaItemComponente::SetMargens(mEsq,mDir,mCima,mBaixo);
        alt = altBaseLista*itens.size()+margemBaixo+margemCima;
    }

};

typedef CPIGRadioBox *PIGRadioBox;
#endif // _CPIGRADIOBOX_
