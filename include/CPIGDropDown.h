#ifndef _CPIGDROPDOWN_
#define _CPIGDROPDOWN_

#include "CPIGListaItemComponente.h"

class CPIGDropDown: public CPIGListaItemComponente{

private:

    int altImagem,largImagem;
    bool recolhida;

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
        SDL_Rect r={pos.x,0,larg,0};
        if (recolhida){
            r.y = pos.y;
            r.h = altBaseLista;
        }else{
            r.y = pos.y-(itens.size())*altBaseLista;
            r.h = (itens.size()+1)*altBaseLista;
        }
        SetMouseOver(SDL_PointInRect(&pMouse,&r));

        return mouseOver;
    }

    void DesenhaItemDestaque(){
        //SDL_Rect rectAux = dest;
        //rectAux.h = altBaseLista;
        if (text){//se tiver imagem de fundo
            //SDL_RenderCopyEx(renderer,text,NULL,&rectAux,-angulo,NULL,flip);
            dest.h=altBaseLista;
            CPIGSprite::Desenha();
        }
        if (itemDestaque>=0){                       //desenha o item no cabeçalho do dropdown
            PIGPonto2D pItem = itens[itemDestaque]->GetXY();
            itens[itemDestaque]->Move(pItem.x,pos.y);     //move o item para o ponto do cabeçalho
            itens[itemDestaque]->Desenha();         //desenha o item no cabeçalho
            itens[itemDestaque]->Move(pItem.x,pItem.y); //devolve o item para a posição normal (onde também deverá ser desenhado)
        }
    }

public:

    CPIGDropDown(int idComponente,int px, int py,int larguraTotal, int alturaLinha, int alturaMaxima,int alturaItem=0, int larguraItem=0,std::string nomeArqFundo="",int retiraFundo=1,int janela=0):
        CPIGListaItemComponente(idComponente,px,py,larguraTotal,alturaLinha,alturaLinha,nomeArqFundo,retiraFundo,janela){
            altImagem = alturaItem;
            largImagem = larguraItem;
            SetRecolhida(true);
    }

    CPIGDropDown(std::string nomeArqParam):CPIGDropDown(LeArquivoParametros(nomeArqParam)){}

    static CPIGDropDown LeArquivoParametros(std::string nomeArqParam){

        std::ifstream arquivo;
        int idComponente,px,py,alturaItem,larguraItem,larguraTotal,alturaLinha,alturaMaxima,retiraFundo=1,janela=0;
        std::string imgFundo = "",variavel;

        arquivo.open(nomeArqParam);

        if(!arquivo.is_open()) throw CPIGErroArquivo(nomeArqParam);
        //formato "x valor"
        while(!arquivo.eof()){
           arquivo >> variavel;
            if(variavel == "idComponente") arquivo >> idComponente;
            if(variavel == "px") arquivo >> px;
            if(variavel == "py") arquivo >> py;
            if(variavel == "larguraTotal") arquivo >> larguraTotal;
            if(variavel == "alturaItem") arquivo >> alturaItem;
            if(variavel == "larguraItem") arquivo >> larguraItem;
            if(variavel == "imgFundo") arquivo >> imgFundo;
            if(variavel == "alturaLinha") arquivo >> alturaLinha;
            if(variavel == "alturaMaxima") arquivo >> alturaMaxima;
            if(variavel == "retiraFundo") arquivo >> retiraFundo;
            if(variavel == "janela") arquivo >> janela;
        }

        arquivo.close();

       // std::cout<<idComponente<<" "<<px<<" "<<py<<" "<<altura<<" "<<largura<<" "<<nomeArq<<" "<<retiraFundo<<" "<<janela<<std::endl;

        //if(imgItem == "") throw CPIGErroParametro("imgItem",imgItem);

        return CPIGDropDown(idComponente,px,py,larguraTotal,alturaLinha,alturaMaxima,alturaItem,larguraItem,imgFundo,retiraFundo,janela);

    }

    void CriaItem(std::string itemLabel, std::string arqImagemIcone="",std::string arqImagemFundoItem="", bool itemHabilitado = true, int audio=-1, std::string hintMsg="", int retiraFundo=1){
        int yItem=pos.y-(itens.size()+1)*altBaseLista;
        CPIGListaItemComponente::CriaItem(yItem,itemLabel,arqImagemIcone,arqImagemFundoItem,false,itemHabilitado,audioComponente,hintMsg,retiraFundo);
    }

    int Desenha(){
        if (visivel==false) return 0;

        DesenhaLabel();

        if (recolhida){
            DesenhaItemDestaque();
        }else{
            //SDL_Rect r = dest;
            //r.h = (itens.size()+1)*altBaseLista;
            //r.y = dest.y;
            //SDL_RenderSetClipRect(renderer,&r);
            dest.h = (itens.size()+1)*altBaseLista;
            frameAtual=0;
            CPIGSprite::Desenha();

            //SDL_RenderCopyEx(renderer,text,NULL,&r,-angulo,NULL,flip);

            for (PIGItemComponente i: itens)
                i->Desenha();
            //SDL_RenderSetClipRect(renderer,NULL);
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
        int posY;

        for(int i=0;i<itens.size();i++){
            posY = (pos.y + alt) - (altBaseLista*(i+1)) - altImagem;
            itens[i]->Move(pos.x,posY);
        }

    }

};

typedef CPIGDropDown *PIGDropDown;
#endif // _CPIGDROPDOWN_
