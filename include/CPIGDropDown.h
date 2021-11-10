#ifndef _CPIGDROPDOWN_
#define _CPIGDROPDOWN_

#include "CPIGListaItemComponente.h"

class CPIGDropDown: public CPIGListaItemComponente{

private:

    bool recolhida;

    static CPIGDropDown LeParametros(int idComponente, CPIGAtributos atrib){
        CPIGDropDown *resp;

        if (atrib.GetString("nomeArq","")!=""){
            resp = new CPIGDropDown(idComponente,atrib.GetInt("px",0),atrib.GetInt("py",0),atrib.GetInt("largura",0),atrib.GetInt("alturaLinha",0),
                          atrib.GetInt("alturaItem",0),atrib.GetInt("larguraItem",0),
                          atrib.GetString("nomeArq",""),atrib.GetInt("retiraFundo",1),atrib.GetInt("janela",0));
        }else{
            resp = new CPIGDropDown(idComponente,atrib.GetInt("px",0),atrib.GetInt("py",0),atrib.GetInt("largura",0),atrib.GetInt("alturaLinha",0),
                          atrib.GetInt("alturaItem",0),atrib.GetInt("larguraItem",0),atrib.GetInt("janela",0));
        }

        resp->ProcessaAtributosGerais(atrib);

        return *resp;
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
            r.y = ((int)pos.y)+alt-altBaseLista;
            r.h = altBaseLista;
        }else{
            r.y = ((int)pos.y)-altBaseLista;
            r.h = (itens.size()+1)*altBaseLista;
        }
        SetMouseOver(SDL_PointInRect(&pMouse,&r));

        return mouseOver;
    }

    void DesenhaItemDestaque(){
        CPIGGerenciadorJanelas::GetJanela(idJanela)->BloqueiaArea((int)pos.x,((int)pos.y)+alt-altBaseLista,altBaseLista,larg);
        if (text){//se tiver imagem de fundo
            dest.h=altBaseLista;
            CPIGSprite::Desenha();
        }else CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetangulo((int)pos.x,((int)pos.y)+alt-altBaseLista,altBaseLista,larg,coresBasicas[corAtual]);

        if (itemDestaque>=0){                       //desenha o item no cabeçalho do dropdown
            PIGPonto2D pItem = itens[itemDestaque]->GetXY();
            itens[itemDestaque]->Move(pItem.x,pos.y+alt-altBaseLista);     //move o item para o ponto do cabeçalho
            //printf("%.0f, %0.f\n",pItem.x,pos.y);
            itens[itemDestaque]->Desenha();         //desenha o item no cabeçalho
            itens[itemDestaque]->Move(pItem.x,pItem.y); //devolve o item para a posição normal (onde também deverá ser desenhado)
        }
        CPIGGerenciadorJanelas::GetJanela(idJanela)->DesbloqueiaArea();
    }

    void DesenhaListaItens(){
        CPIGGerenciadorJanelas::GetJanela(idJanela)->BloqueiaArea((int)pos.x,((int)pos.y)-altBaseLista,(itens.size()+1)*altBaseLista,larg);
        if (text){
            frameAtual=0;
            dest.h = (itens.size()+1)*altBaseLista;
            CPIGSprite::Desenha();
        }else CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetangulo((int)pos.x,(int)pos.y-altBaseLista,(itens.size()+1)*altBaseLista,larg,coresBasicas[corAtual]);

        for (PIGItemComponente i: itens)
            i->Desenha();

        CPIGGerenciadorJanelas::GetJanela(idJanela)->DesbloqueiaArea();
    }

public:

    CPIGDropDown(int idComponente,int px, int py,int larguraTotal, int alturaLinha, int alturaItem=0, int larguraItem=0, string nomeArqFundo="", int retiraFundo=1, int janela=0):
        CPIGListaItemComponente(idComponente,px,py,larguraTotal,alturaLinha,nomeArqFundo,retiraFundo,janela){
            SetRecolhida(true);
    }

    CPIGDropDown(int idComponente,int px, int py,int larguraTotal, int alturaLinha, int alturaItem=0, int larguraItem=0,int janela=0):
        CPIGListaItemComponente(idComponente,px,py,larguraTotal,alturaLinha,janela){
            SetRecolhida(true);
    }

    CPIGDropDown(int idComponente,CPIGAtributos atrib):CPIGDropDown(LeParametros(idComponente,atrib)){}

    void CriaItem(string itemLabel, string arqImagemIcone="", string arqImagemFundoItem="", bool itemHabilitado = true, string hintMsg="", int retiraFundo=1){
        int yItem = pos.y+alt-(altBaseLista)*(itens.size()+2);
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

    int TrataEventoMouse(PIGEvento evento){
        int resp = -1;
        bool mouseOverAntes = mouseOver;
        SDL_Point p = GetPosicaoMouse();

        if (ChecaMouseOver(p)){

            if (!habilitado) return PIG_SELECIONADO_DESABILITADO;
            if (!visivel) return PIG_SELECIONADO_INVISIVEL;

            if (!recolhida){        //se o dropdown está exibindo os itens, é preciso tratá-los individualmente
                for (unsigned int i=0;i<itens.size();i++){
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
            for (unsigned int i=0;i<itens.size();i++){
                itens[i]->SetMouseOver(false);
            }
        }

        return PIG_NAO_SELECIONADO;
    }

    int TrataEventoTeclado(PIGEvento evento){
        return 0;
    }

    void Move(double nx, double ny){
        CPIGSprite::Move(nx,ny);
        SetPosicaoPadraoLabel(posLabel);

        for(unsigned int i=0;i<itens.size();i++){
            int posY = pos.y - altBaseLista*(i+1);
            itens[i]->Move(pos.x,posY);
        }
    }

};

typedef CPIGDropDown *PIGDropDown;
#endif // _CPIGDROPDOWN_
