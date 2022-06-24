#ifndef _CPIGCHECKBOX_
#define _CPIGCHECKBOX_

#include "CPIGListaItemComponente.h"

class CPIGCheckBox: public CPIGListaItemComponente{

protected:

    string arqImagemIcone;

    virtual void ProcessaAtributos(CPIGAtributos atrib)override{
        CPIGListaItemComponente::ProcessaAtributos(atrib);
    }

    static CPIGCheckBox LeParametros(int idComponente, CPIGAtributos atrib){
        CPIGCheckBox *resp;

        if (atrib.GetString("nomeArq","")!=""){
            resp = new CPIGCheckBox(idComponente,atrib.GetInt("largura",0),atrib.GetInt("alturaLinha",0),
                          atrib.GetString("nomeArqIcone",""),atrib.GetInt("alturaIcone",0),atrib.GetInt("larguraIcone",0),
                          atrib.GetString("nomeArq",""),atrib.GetInt("retiraFundo",1),atrib.GetInt("janela",0));
        }else{
            resp = new CPIGCheckBox(idComponente,atrib.GetInt("largura",0),atrib.GetInt("alturaLinha",0),
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

    CPIGCheckBox(int idComponente, int larguraTotal, int alturaLinha, string imgIcone, int alturaIcone, int larguraIcone, string imgFundo, int retiraFundo=1, int janela=0):
        CPIGListaItemComponente(idComponente,larguraTotal,alturaLinha,imgFundo,retiraFundo,janela){
            arqImagemIcone = imgIcone;
            tipo = PIG_CHECKBOX;
        }

    CPIGCheckBox(int idComponente, int larguraTotal, int alturaLinha, string imgIcone, int alturaIcone, int larguraIcone, int janela=0):
        CPIGListaItemComponente(idComponente,larguraTotal,alturaLinha,janela){
            arqImagemIcone = imgIcone;
            tipo = PIG_CHECKBOX;
        }

    CPIGCheckBox(int idComponente,CPIGAtributos atrib):CPIGCheckBox(LeParametros(idComponente,atrib)){}

    virtual ~CPIGCheckBox(){}

    void CriaItem(string itemLabel, string arqImagemFundoItem="", bool itemMarcado = false, bool itemHabilitado = true, string hintMsg="", int retiraFundo=1, int retiraFundoIcone=1){
        CPIGListaItemComponente::SetDimensoes(alt+altBaseLista,larg); //aumenta o tamanho do componente para comportar o novo item
        DeslocaItens(0,altBaseLista);//desloca todos os itens para cima, pois o novo item vai entrar abaixo dos outros

        int yItem = pos.y+margemBaixo;
        PIGItemComponente item = CPIGListaItemComponente::CriaItem(yItem,itemLabel,arqImagemIcone,arqImagemFundoItem,itemMarcado,itemHabilitado,hintMsg,retiraFundo,retiraFundoIcone);
        item->DefineFuncaoAjusteFrame(AjustaFrame);
        item->GetIcone()->CriaFramesAutomaticosPorLinha(1,1,6);
        AjustaFrame(item);
    }

    void CriaItem(CPIGAtributos atrib){
        CPIGListaItemComponente::SetDimensoes(alt+altBaseLista,larg); //aumenta o tamanho do componente para comportar o novo item
        DeslocaItens(0,altBaseLista);//desloca todos os itens para cima, pois o novo item vai entrar abaixo dos outros

        int yItem = pos.y+margemBaixo;
        PIGItemComponente item = CPIGListaItemComponente::CriaItem(yItem,atrib.GetString("label",""),arqImagemIcone,atrib.GetString("nomeArq",""),
                                                                   atrib.GetInt("acionado",0),atrib.GetInt("habilitado",1),atrib.GetString("hint",""),atrib.GetInt("retiraFundo",1),atrib.GetInt("retiraFundoIcone",1));
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

        int resp = 0;
        bool mouseOverAntes = mouseOver;

        if (ChecaMouseOver(GetPosicaoMouse())>0){
            for (PIGItemComponente i: itens){
                if (i->TrataEventoMouse(evento) == PIG_COMPONENTE_TRATADO){
                    resp = 1;
                    OnAction();
                }
            }
            if (resp) return PIG_COMPONENTE_TRATADO;
            else return PIG_COMPONENTE_MOUSEOVER;
        }else if (mouseOverAntes){               //mouse estava antes, mas saiu
            for (PIGItemComponente i: itens){
                i->SetMouseOver(false);
            }
        }
        return PIG_COMPONENTE_NAOTRATADO;
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
            if(itens[i]->GetAcionado()) resp.push_back(i);

        return resp;
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

typedef CPIGCheckBox *PIGCheckBox;
#endif // _CPIGCheckBox_
