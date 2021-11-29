#ifndef _CPIGDROPDOWN_
#define _CPIGDROPDOWN_

#include "CPIGListaItemComponente.h"

class CPIGDropDown: public CPIGListaItemComponente{

private:

    bool recolhida;
    int itemDestaque;

    void ProcessaAtributos(CPIGAtributos atrib)override{
        CPIGListaItemComponente::ProcessaAtributos(atrib);
    }

    static CPIGDropDown LeParametros(int idComponente, CPIGAtributos atrib){
        CPIGDropDown *resp;

        if (atrib.GetString("nomeArq","")!=""){
            resp = new CPIGDropDown(idComponente,atrib.GetInt("largura",0),atrib.GetInt("alturaLinha",0),
                          atrib.GetInt("alturaItem",0),atrib.GetInt("larguraItem",0),
                          atrib.GetString("nomeArq",""),atrib.GetInt("retiraFundo",1),atrib.GetInt("janela",0));
        }else{
            resp = new CPIGDropDown(idComponente,atrib.GetInt("largura",0),atrib.GetInt("alturaLinha",0),
                          atrib.GetInt("alturaItem",0),atrib.GetInt("larguraItem",0),atrib.GetInt("janela",0));
        }

        resp->ProcessaAtributos(atrib);

        return *resp;
    }

    void SetFoco(bool valor)override{
        temFoco = valor;
        if (!temFoco){
            SetRecolhida(true);
        }
    }

    void SetRecolhida(bool valor){
        recolhida = valor;
    }

    int ChecaMouseOver(SDL_Point pMouse)override{
        SDL_Rect r={(int)pos.x,pos.y,larg,altBaseLista};
        if (!recolhida){
            r.y -= altBaseLista*itens.size();
            r.h += itens.size()*altBaseLista;
        }
        SetMouseOver(SDL_PointInRect(&pMouse,&r));

        return mouseOver;
    }

    void DesenhaItemDestaque(){
        CPIGGerenciadorJanelas::GetJanela(idJanela)->BloqueiaArea((int)pos.x,((int)pos.y),altBaseLista,larg);
        if (text){//se tiver imagem de fundo
            dest.h=altBaseLista;
            CPIGSprite::Desenha();
        }else CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetangulo((int)pos.x,(int)pos.y,altBaseLista,larg,coresBasicas[0]);

        if (itemDestaque>=0){                       //desenha o item no cabeçalho do dropdown
            PIGPonto2D pItem = itens[itemDestaque]->GetXY();
            itens[itemDestaque]->Move(pItem.x,pos.y);     //move o item para o ponto do cabeçalho
            //printf("%.0f, %0.f\n",pItem.x,pos.y);
            itens[itemDestaque]->Desenha();         //desenha o item no cabeçalho
            itens[itemDestaque]->Move(pItem.x,pItem.y); //devolve o item para a posiçăo normal (onde também deverá ser desenhado)
        }
        CPIGGerenciadorJanelas::GetJanela(idJanela)->DesbloqueiaArea();
    }

    void DesenhaListaItens(){
        CPIGGerenciadorJanelas::GetJanela(idJanela)->BloqueiaArea((int)pos.x,((int)pos.y)-(itens.size())*altBaseLista,(itens.size()+1)*altBaseLista,larg);
        if (text){
            frameAtual=0;
            dest.y = *altJanela-pos.y-altBaseLista;
            dest.h = (itens.size()+1)*altBaseLista;
            CPIGSprite::Desenha();
        }else CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetangulo((int)pos.x,(int)pos.y-altBaseLista*itens.size(),(itens.size()+1)*altBaseLista,larg,coresBasicas[0]);

        for (PIGItemComponente i: itens)
            i->Desenha();

        CPIGGerenciadorJanelas::GetJanela(idJanela)->DesbloqueiaArea();
    }

public:

    CPIGDropDown(int idComponente, int larguraTotal, int alturaLinha, int alturaItem=0, int larguraItem=0, string nomeArqFundo="", int retiraFundo=1, int janela=0):
        CPIGListaItemComponente(idComponente,larguraTotal,alturaLinha,nomeArqFundo,retiraFundo,janela){
            SetRecolhida(true);
            itemDestaque = -1;
            tipo = PIG_DROPDOWN;
    }

    CPIGDropDown(int idComponente, int larguraTotal, int alturaLinha, int alturaItem=0, int larguraItem=0, int janela=0):
        CPIGListaItemComponente(idComponente,larguraTotal,alturaLinha,janela){
            SetRecolhida(true);
            itemDestaque = -1;
            tipo = PIG_DROPDOWN;
    }

    CPIGDropDown(int idComponente,CPIGAtributos atrib):CPIGDropDown(LeParametros(idComponente,atrib)){}

    virtual ~CPIGDropDown(){}

    int GetItemDestaque(){
        return itemDestaque;
    }

    int SetAcionadoItem(int indice, bool valor)override{
        int resp = CPIGListaItemComponente::SetAcionadoApenasItem(indice,valor);
        if (resp) itemDestaque = indice;
        return resp;
    }

    void CriaItem(string itemLabel, string arqImagemIcone="", string arqImagemFundoItem="", bool itemHabilitado = true, string hintMsg="", int retiraFundo=1, int retiraFundoIcone=1){

        int yItem = pos.y-altBaseLista*(itens.size()+1);
        CPIGListaItemComponente::CriaItem(yItem,itemLabel,arqImagemIcone,arqImagemFundoItem,false,itemHabilitado,hintMsg,retiraFundo,retiraFundoIcone);

        if (recolhida){
            SetDimensoes(altBaseLista,larg);
        }else{
            SetDimensoes(altBaseLista*(itens.size()+1),larg);
        }
    }

    int Desenha(){
        if (visivel==false) return 0;

        if (recolhida){
            DesenhaItemDestaque();
        }else{
            DesenhaListaItens();
        }

        return CPIGComponente::Desenha();
    }

    PIGEstadoEvento TrataEventoMouse(PIGEvento evento)override{
        if (!habilitado) return PIG_DESABILITADO;
        if (!visivel) return PIG_INVISIVEL;

        int resp = itemDestaque;
        bool mouseOverAntes = mouseOver;
        SDL_Point p = GetPosicaoMouse();

        if (ChecaMouseOver(p)){

            if (!recolhida){        //se o dropdown está exibindo os itens, é preciso tratá-los individualmente
                for (unsigned int i=0;i<itens.size();i++){
                    if(itens[i]->TrataEventoMouse(evento) == PIG_TRATADO){
                        if (itens[i]->GetAcionado())
                            resp = i;

                        SetAcionadoApenasItem(resp,resp!=-1);
                        itemDestaque = resp;
                        OnAction();
                        break;
                    }
                }

                if (evento.mouse.acao == PIG_MOUSE_PRESSIONADO && evento.mouse.botao == PIG_MOUSE_ESQUERDO){
                    SetRecolhida(!recolhida);
                }

                if (resp>=0) return PIG_TRATADO;
                else return PIG_MOUSEOVER;
            }
            if (evento.mouse.acao == PIG_MOUSE_PRESSIONADO && evento.mouse.botao == PIG_MOUSE_ESQUERDO){
                SetRecolhida(!recolhida);
                return PIG_TRATADO;
            }
        }else if (mouseOverAntes){               //mouse estava antes, mas saiu
            for (unsigned int i=0;i<itens.size();i++){
                itens[i]->SetMouseOver(false);
            }
        }

        return PIG_NAOSELECIONADO;
    }

};

typedef CPIGDropDown *PIGDropDown;
#endif // _CPIGDROPDOWN_
