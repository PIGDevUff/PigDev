#ifndef _CPigListBox_
#define _CPigListBox_

#include "CPigListaItemComponente.h"

class CPigListBox: public CPigListaItemComponente{

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
            int posX,posY;
            itens[itemDestaque]->GetXY(posX,posY);
            CGerenciadorJanelas::DesenhaRetanguloVazado(x,posY,altBaseLista,larg,AZUL,idJanela);
        }
    }

public:

    CPigListBox(int idComponente,int px, int py,int larguraTotal, int alturaLinha, int alturaMaxima,int alturaItem=0, int larguraItem=0,std::string nomeArqFundo="",int retiraFundo=1,int janela=0):
        CPigListaItemComponente(idComponente,px,py,larguraTotal,alturaLinha,alturaMaxima,nomeArqFundo,retiraFundo,janela){
            altImagem = alturaItem;
            largImagem = larguraItem;
    }

    CPigListBox(std::string nomeArqParam):CPigListBox(LeArquivoParametros(nomeArqParam)){}

    ~CPigListBox(){
        for (PigItemComponente x: itens) delete x;
    }

    static CPigListBox LeArquivoParametros(std::string nomeArqParam){

        std::ifstream arquivo;
        int idComponente,px,py,altura = 0,largura,alturaItens,larguraItens,alturaLinha,alturaMaxima,retiraFundo = 0,janela = 0;

        std::string nomeArq = "",variavel;

        arquivo.open(nomeArqParam);
        if(!arquivo.is_open()) throw CPigErroArquivo(nomeArqParam);
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

        if(nomeArq == "") throw CPigErroParametro("nomeArq",nomeArqParam);

        return CPigListBox(idComponente,px,py,largura,alturaLinha,alturaMaxima,alturaItens,larguraItens,nomeArq,retiraFundo,janela);
    }

    int TrataEventoTeclado(PIG_Evento evento)override{
        if(!temFoco||!habilitado||!visivel) return 0;

        if(evento.teclado.acao == TECLA_PRESSIONADA){
            if(evento.teclado.tecla == TECLA_CIMA && evento.teclado.repeticao == 0){
                itemDestaque--;
                if(itemDestaque<0) itemDestaque = itens.size()-1;
            }

            if(evento.teclado.tecla == TECLA_BAIXO && evento.teclado.repeticao == 0)
                itemDestaque = (itemDestaque + 1) % itens.size();
        }
        return 1;
    }

    int TrataEventoMouse(PIG_Evento evento){
        int resp = -1;
        bool mouseOverAntes = mouseOver;
        if (ChecaMouseOver(CMouse::PegaXY())>0){
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
        int yItem = y+alt-(altBaseLista)*(itens.size()+1);
        CPigListaItemComponente::CriaItem(yItem,itemLabel,arqImagemIcone,arqImagemFundoItem,itemMarcado,itemHabilitado,audio,hintMsg,retiraFundo);
    }

    void Move(int nx,int ny){
        CPigVisual::Move(nx,ny);
        int posY;

        for(int i=0;i<itens.size();i++){
            posY = (y + alt) - (altBaseLista*(i+1));
            itens[i]->Move(x,posY);
        }

    }

    int Desenha(){
        if (visivel==false) return 0;

        if (text){//se tiver imagem de fundo
            SDL_RenderCopyEx(renderer,text,NULL,&dest,-angulo,NULL,flip);
        }
        DesenhaLabel();

        for (PigItemComponente i: itens)
            i->Desenha();

        DesenhaRetanguloMarcacao();

        return 1;
    }

    int SetAcionado(int indice, bool marcado){
        if (indice<0||indice>=itens.size()) return 0;
        if (marcado){
            itemDestaque = indice;
            for (PigItemComponente i: itens) i->SetAcionado(false);
        }
        itens[indice]->SetAcionado(marcado);
        return 1;
    }

};
typedef CPigListBox* PigListBox;
#endif // _CPigListBox_
