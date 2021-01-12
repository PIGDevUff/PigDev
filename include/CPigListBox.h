#ifndef _CPIGLISTBOX_
#define _CPIGLISTBOX_

#include "CPIGListaItemComponente.h"

class CPIGListBox: public CPIGListaItemComponente{

protected:
    int altImagem,largImagem;

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

    void DesenhaRetanguloMarcacao(){
        if(itemDestaque !=-1){
            //int posX,posY;
            SDL_Point p = itens[itemDestaque]->GetXY();
            CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetanguloVazado(p.x,p.y,altBaseLista,larg,AZUL);
        }
    }

public:

    CPIGListBox(int idComponente,int px, int py,int larguraTotal, int alturaLinha, int alturaMaxima,int alturaItem=0, int larguraItem=0,std::string nomeArqFundo="",int retiraFundo=1,int janela=0):
        CPIGListaItemComponente(idComponente,px,py,larguraTotal,alturaLinha,alturaMaxima,nomeArqFundo,retiraFundo,janela){
            altImagem = alturaItem;
            largImagem = larguraItem;
    }

    CPIGListBox(std::string nomeArqParam):CPIGListBox(LeArquivoParametros(nomeArqParam)){}

    ~CPIGListBox(){
        for (PIGItemComponente x: itens) delete x;
    }

    static CPIGListBox LeArquivoParametros(std::string nomeArqParam){

        std::ifstream arquivo;
        int idComponente,px,py,altura = 0,largura,alturaItens,larguraItens,alturaLinha,alturaMaxima,retiraFundo = 0,janela = 0;

        std::string nomeArq = "",variavel;

        arquivo.open(nomeArqParam);
        if(!arquivo.is_open()) throw CPIGErroArquivo(nomeArqParam);
        //formato "x valor"
        while(!arquivo.eof()){
           arquivo >> variavel;
            if(variavel == "idComponente") arquivo >> idComponente;
            if(variavel == "px") arquivo >> px;
            if(variavel == "py") arquivo >> py;
            if(variavel == "altura") arquivo >> altura;
            if(variavel == "largura") arquivo >> largura;
            if(variavel == "alturaItens") arquivo >> alturaItens;
            if(variavel == "larguraItens") arquivo >> larguraItens;
            if(variavel == "nomeArq") arquivo >> nomeArq;
            if(variavel == "alturaLinha") arquivo >> alturaLinha;
            if(variavel == "alturaMaxima") arquivo >> alturaMaxima;
            if(variavel == "retiraFundo") arquivo >> retiraFundo;
            if(variavel == "janela") arquivo >> janela;
        }
        arquivo.close();
       // std::cout<<idComponente<<" "<<px<<" "<<py<<" "<<altura<<" "<<largura<<" "<<nomeArq<<" "<<retiraFundo<<" "<<janela<<std::endl;

        if(nomeArq == "") throw CPIGErroParametro("nomeArq",nomeArqParam);

        return CPIGListBox(idComponente,px,py,largura,alturaLinha,alturaMaxima,alturaItens,larguraItens,nomeArq,retiraFundo,janela);
    }

    int TrataEventoTeclado(PIG_Evento evento)override{
        if(!temFoco||!habilitado||!visivel) return 0;

        if(evento.teclado.acao == PIG_TECLA_PRESSIONADA){
            if(evento.teclado.tecla == PIG_TECLA_CIMA && evento.teclado.repeticao == 0){
                itemDestaque--;
                if(itemDestaque<0) itemDestaque = itens.size()-1;
            }

            if(evento.teclado.tecla == PIG_TECLA_BAIXO && evento.teclado.repeticao == 0)
                itemDestaque = (itemDestaque + 1) % itens.size();
        }
        return 1;
    }

    int TrataEventoMouse(PIG_Evento evento){
        int resp = -1;
        bool mouseOverAntes = mouseOver;

        if (ChecaMouseOver(CPIGMouse::PegaXYWorld())>0){
            for (int i=0;i<itens.size();i++){
                int aux = itens[i]->TrataEventoMouse(evento);
                if(aux == PIG_SELECIONADO_TRATADO){
                    if (itens[i]->GetAcionado())
                        resp = i;
                    SetHint(itens[i]->GetHint());
                    SetFonteHint(itens[i]->GetFonteHint());
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

    void CriaItem(std::string itemLabel, std::string arqImagemIcone="", std::string arqImagemFundoItem="",bool itemMarcado = false, bool itemHabilitado = true, int audio=-1, std::string hintMsg="", int retiraFundo=1){
        int yItem = pos.y+alt-(altBaseLista)*(itens.size()+1);
        CPIGListaItemComponente::CriaItem(yItem,itemLabel,arqImagemIcone,arqImagemFundoItem,itemMarcado,itemHabilitado,audio,hintMsg,retiraFundo);
    }

    void Move(int nx,int ny){
        CPIGSprite::Move(nx,ny);
        int posY;

        for(int i=0;i<itens.size();i++){
            posY = (pos.y + alt) - (altBaseLista*(i+1));
            itens[i]->Move(pos.x,posY);
        }

    }

    int Desenha(){
        if (visivel==false) return 0;

        if (text){//se tiver imagem de fundo
            CPIGSprite::Desenha();//SDL_RenderCopyEx(renderer,text,NULL,&dest,-angulo,NULL,flip);
        }
        DesenhaLabel();

        for (PIGItemComponente i: itens)
            i->Desenha();

        DesenhaRetanguloMarcacao();

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
