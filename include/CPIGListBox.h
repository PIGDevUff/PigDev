#ifndef _CPIGLISTBOX_
#define _CPIGLISTBOX_

#include "CPIGListaItemComponente.h"

class CPIGListBox: public CPIGListaItemComponente{

protected:

    int itemDestaque;

    virtual void ProcessaAtributos(CPIGAtributos atrib)override{
        CPIGListaItemComponente::ProcessaAtributos(atrib);

        string valorStr = atrib.GetString("corDestaque","");
        if (valorStr != "") SetCorDestaque(PIGCriaCorString(valorStr));
    }

    static CPIGListBox LeParametros(int idComponente, CPIGAtributos atrib){
        CPIGListBox *resp;

        if (atrib.GetString("nomeArq","")!=""){
            resp = new CPIGListBox(idComponente,atrib.GetInt("largura",0),atrib.GetInt("alturaLinha",0),
                          atrib.GetInt("alturaItem",0),atrib.GetInt("larguraItem",0),
                          atrib.GetString("nomeArq",""),atrib.GetInt("retiraFundo",1),atrib.GetInt("janela",0));
        }else{
            resp = new CPIGListBox(idComponente,atrib.GetInt("largura",0),atrib.GetInt("alturaLinha",0),
                          atrib.GetInt("alturaItem",0),atrib.GetInt("larguraItem",0),atrib.GetInt("janela",0));
        }

        resp->ProcessaAtributos(atrib);

        return *resp;
    }

private:

    void DesenhaRetanguloMarcacao(){
        if(itemDestaque !=-1){
            PIGPonto2D p = itens[itemDestaque]->GetXY();
            CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetanguloVazado(p.x+margemEsq,p.y+margemBaixo,altBaseLista-(margemCima+margemBaixo),larg-(margemDir+margemEsq),coresBasicas[1]);
        }
    }

public:

    CPIGListBox(int idComponente, int larguraTotal, int alturaLinha, int alturaItem=0, int larguraItem=0, string nomeArqFundo="", int retiraFundo=1, int janela=0):
        CPIGListaItemComponente(idComponente,larguraTotal,alturaLinha,nomeArqFundo,retiraFundo,janela){
            itemDestaque = -1;
            tipo = PIG_LISTBOX;
    }

    CPIGListBox(int idComponente, int larguraTotal, int alturaLinha, int alturaItem=0, int larguraItem=0, int janela=0):
        CPIGListaItemComponente(idComponente,larguraTotal,alturaLinha,janela){
            itemDestaque = -1;
            tipo = PIG_LISTBOX;
    }

    CPIGListBox(int idComponente,CPIGAtributos atrib):CPIGListBox(LeParametros(idComponente,atrib)){}

    virtual ~CPIGListBox(){}

    int GetItemDestaque(){
        return itemDestaque;
    }

    int SetAcionadoItem(int indice, bool valor)override{
        int resp = CPIGListaItemComponente::SetAcionadoApenasItem(indice,valor);
        if (resp) itemDestaque = indice;
        return resp;
    }

    PIGEstadoEvento TrataEventoTeclado(PIGEvento evento)override{
        if (!temFoco) return PIG_SEMFOCO;
        if (!habilitado) return PIG_DESABILITADO;
        if (!visivel) return PIG_INVISIVEL;

        if(evento.teclado.acao == PIG_TECLA_PRESSIONADA){
            if(evento.teclado.tecla == PIG_TECLA_CIMA && evento.teclado.repeticao == 0){
                itemDestaque--;
                if(itemDestaque<0) itemDestaque = itens.size()-1;
            }

            if(evento.teclado.tecla == PIG_TECLA_BAIXO && evento.teclado.repeticao == 0)
                itemDestaque = (itemDestaque + 1) % itens.size();
        }
        return PIG_TRATADO;
    }

    PIGEstadoEvento TrataEventoMouse(PIGEvento evento)override{
        if (!habilitado) return PIG_DESABILITADO;
        if (!visivel) return PIG_INVISIVEL;

        int resp = itemDestaque;
        bool mouseOverAntes = mouseOver;

        if (ChecaMouseOver(GetPosicaoMouse())>0){
            for (unsigned int i=0;i<itens.size();i++){
                int aux = itens[i]->TrataEventoMouse(evento);
                if(aux == PIG_TRATADO){
                    if (itens[i]->GetAcionado())
                        resp = i;
                    //SetHint(itens[i]->GetHint());
                    //SetFonteHint(itens[i]->GetFonteHint());
                    SetAcionadoApenasItem(resp,resp!=-1);
                    itemDestaque = resp;
                    OnAction();
                    break;
                }
            }
            if (resp>0)
                return PIG_TRATADO;
            else return PIG_MOUSEOVER;
            //SetAcionadoItem(resp,resp!=-1);
        }else if (mouseOverAntes){               //mouse estava antes, mas saiu
            for (unsigned int i=0;i<itens.size();i++){
                itens[i]->SetMouseOver(false);
            }
        }

        return PIG_NAOSELECIONADO;
    }

    void CriaItem(string itemLabel, string arqImagemIcone="", string arqImagemFundoItem="", bool itemMarcado = false, bool itemHabilitado = true, string hintMsg="", int retiraFundo=1, int retiraFundoIcone=1){
        CPIGListaItemComponente::SetDimensoes(alt+altBaseLista,larg); //aumenta o tamanho do componente para comportar o novo item
        DeslocaItens(0,altBaseLista);//desloca todos os itens para cima, pois o novo item vai entrar abaixo dos outros

        int yItem = pos.y;
        CPIGListaItemComponente::CriaItem(yItem,itemLabel,arqImagemIcone,arqImagemFundoItem,itemMarcado,itemHabilitado,hintMsg,retiraFundo,retiraFundoIcone);
    }

    int Desenha(){
        if (visivel==false) return 0;

        CPIGGerenciadorJanelas::GetJanela(idJanela)->BloqueiaArea(pos.x,pos.y,alt,larg);

        if (text)//se tiver imagem de fundo
            CPIGSprite::Desenha();
        else CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetangulo((int)pos.x,(int)pos.y,alt,larg,coresBasicas[0]);

        for (PIGItemComponente i: itens)
            i->Desenha();

        DesenhaRetanguloMarcacao();

        CPIGGerenciadorJanelas::GetJanela(idJanela)->DesbloqueiaArea();

        return CPIGComponente::Desenha();
    }

    void SetCorDestaque(PIGCor cor){
        coresBasicas[1] = cor;
    }

};
typedef CPIGListBox* PIGListBox;
#endif // _CPIGLISTBOX_
