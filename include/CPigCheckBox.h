#ifndef _CPigCheckBox_
#define _CPigCheckBox_

#include "CPigListaItemComponente.h"

class CPigCheckBox: public CPigListaItemComponente{

protected:
    std::string arqIcone;

    void SetFoco(bool valor){
        temFoco = valor;
    }

    void SetAcionado(bool valor){
    }

    void SetMouseOver(bool valor){
        mouseOver = valor;
    }

    static void AjustaFrame(PigItemComponente item){
        int resp;
        if (item->GetHabilitado()==false){
            if (item->GetAcionado()) resp = 3;
            else resp = 2;
        }else if (item->GetMouseOver()){
            if (item->GetAcionado()) resp = 5;
            else resp = 4;
        }else{
            if (item->GetAcionado()) resp = 1;
            else resp = 0;
        }
        item->GetIcone()->MudaFrameAtual(resp);
    }

public:

    CPigCheckBox(int idComponente, int posX, int posY, int larguraTotal,int alturaLinha,int alturaMaxima,std::string imgIcone, int alturaIcone, int larguraIcone,std::string imgFundo, int retiraFundo=1,int janela = 0):
        CPigListaItemComponente(idComponente,posX,posY,larguraTotal,alturaLinha,alturaMaxima,imgFundo,retiraFundo,janela){
            arqIcone = imgIcone;
        }

    CPigCheckBox(std::string nomeArqParam):CPigCheckBox(LeArquivoParametros(nomeArqParam)){}

    static CPigCheckBox LeArquivoParametros(std::string nomeArqParam){

        std::ifstream arquivo;
        int idComponente,px,py,alturaItem,larguraItem,larguraTotal,alturaLinha,alturaMaxima,retiraFundo=1,janela=0;
        std::string imgFundo = "",imgItem = "",variavel;

        arquivo.open(nomeArqParam);

        if(!arquivo.is_open()) throw CPigErroArquivo(nomeArqParam);
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
            if(variavel == "imgItem") arquivo >> imgItem;
            if(variavel == "alturaLinha") arquivo >> alturaLinha;
            if(variavel == "alturaMaxima") arquivo >> alturaMaxima;
            if(variavel == "retiraFundo") arquivo >> retiraFundo;
            if(variavel == "janela") arquivo >> janela;
        }

        arquivo.close();

       // std::cout<<idComponente<<" "<<px<<" "<<py<<" "<<altura<<" "<<largura<<" "<<nomeArq<<" "<<retiraFundo<<" "<<janela<<std::endl;

        if(imgItem == "") throw CPigErroParametro("imgItem",imgItem);

        return CPigCheckBox(idComponente,px,py,larguraTotal,alturaLinha,alturaMaxima,imgItem,alturaItem,larguraItem,imgFundo);

    }

    void CriaItem(std::string itemLabel, std::string arqImagemFundoItem="", bool itemMarcado = false, bool itemHabilitado = true, int audio=-1, std::string hintMsg="", int retiraFundo=1){
        int yItem = y+alt-(altBaseLista)*(itens.size()+1);
        CPigListaItemComponente::CriaItem(yItem,itemLabel,arqIcone,arqImagemFundoItem,itemMarcado,itemHabilitado,audio,hintMsg,retiraFundo);
        PIGSprite icone = itens[itens.size()-1]->GetIcone();
        icone->CriaFramesAutomaticosPorLinha(1,1,6);
        icone->MudaFrameAtual(1);
    }

    int Desenha(){
        if (visivel==false) return 0;

        if (text){//se tiver imagem de fundo
            CPigSprite::Desenha();
        }
        DesenhaLabel();

        for (PigItemComponente i: itens)
            i->Desenha();

        return 1;
    }

    int TrataEventoMouse(PIG_Evento evento){
        int resp = 0;
        bool mouseOverAntes = mouseOver;

        if (ChecaMouseOver(CMouse::PegaXYWorld())>0){
            for (int i=0;i<itens.size();i++){
                if (itens[i]->TrataEventoMouse(evento) == PIG_SELECIONADO_TRATADO)
                    resp = 1;
            }
            if (resp) return PIG_SELECIONADO_TRATADO;
            else return PIG_SELECIONADO_MOUSEOVER;
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

    void SetAcionadoTodos(bool marcado){
        for (PigItemComponente i: itens){
            i->SetAcionado(marcado);
        }
    }

    int SetAcionadoItem(int indice, bool marcado){
        if (indice<0||indice>=itens.size()) return -1;
        itens[indice]->SetAcionado(marcado);
        return 1;
    }

    std::vector <int> GetItensMarcados(){
        std::vector <int> resp;
        for(int i=0;i<itens.size();i++)
            if(itens[i]->GetAcionado())resp.push_back(i);

        return resp;

    }

};

typedef CPigCheckBox *PigCheckBox;
#endif // _CPigCheckBox_
