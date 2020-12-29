#ifndef _CPigRadioBox_
#define _CPigRadioBox_

#include "CPigListaItemComponente.h"

class CPigRadioBox: public CPigListaItemComponente{

protected:
    std::string arqImagemIcone;

    void SetFoco(bool valor){
        temFoco = valor;
    }

    void SetAcionado(bool valor){
    }

    void SetMouseOver(bool valor){
        mouseOver = valor;
    }

    /*static void AjustaFrame(PigItemComponente item){
        int itemAlt,itemLarg;
        PIGSprite icone = item->GetIcone();
        icone->GetDimensoesOriginais(itemAlt,itemLarg);
        int largFrame = itemLarg/6;
        SDL_Rect r={0,0,largFrame,itemAlt};
        if (item->GetHabilitado()==false){
            if (item->GetAcionado()) r.x = 3*largFrame;
            else r.x = 2*largFrame;
        }else if (item->GetMouseOver()){
            if (item->GetAcionado()) r.x = 5*largFrame;
            else r.x = 4*largFrame;
        }else{
            if (item->GetAcionado()) r.x = largFrame;
            else r.x = 0;
        }
        icone->DefineFrame(r);
    }*/

    static void AjustaFrame(PigItemComponente item){
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
        PIGSprite icone = item->GetIcone();
        icone->MudaFrameAtual(resp);
    }

public:

    CPigRadioBox(int idComponente, int posX, int posY, int larguraTotal,int alturaLinha, int alturaMaxima,std::string imgIcone, int alturaIcone, int larguraIcone,std::string imgFundo, int retiraFundo=1,int janela = 0):
        CPigListaItemComponente(idComponente,posX,posY,larguraTotal,alturaLinha,alturaMaxima,imgFundo,retiraFundo,janela){
            arqImagemIcone = imgIcone;
        }

    CPigRadioBox(std::string nomeArqParam):CPigRadioBox(LeArquivoParametros(nomeArqParam)){}

    static CPigRadioBox LeArquivoParametros(std::string nomeArqParam){
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

        return CPigRadioBox(idComponente,px,py,larguraTotal,alturaLinha,alturaMaxima,imgItem,alturaItem,larguraItem,imgFundo,retiraFundo,janela);
    }

    void CriaItem(std::string itemLabel, std::string arqImagemFundo="",bool itemHabilitado = true, int audio=-1, std::string hintMsg="", int retiraFundo=1){
        int yItem = y+alt-(altBaseLista)*(itens.size()+1);
        CPigListaItemComponente::CriaItem(yItem,itemLabel,arqImagemIcone,arqImagemFundo,false,itemHabilitado,audioComponente,hintMsg,retiraFundo);
        itens[itens.size()-1]->DefineFuncaoAjusteFrame(AjustaFrame);
        PIGSprite icone = itens[itens.size()-1]->GetIcone();
        icone->CriaFramesAutomaticos(1,1,6);
        icone->MudaFrameAtual(1);
    }

    int Desenha(){
        if (visivel==false) return 0;

        if (text){//se tiver imagem de fundo
            //SDL_RenderCopyEx(renderer,text,NULL,&dest,-angulo,NULL,flip);
            CPigSprite::Desenha();
        }
        DesenhaLabel();

        for (PigItemComponente i: itens)
            i->Desenha();

        return 1;
    }

    int TrataEventoMouse(PIG_Evento evento){
        int resp = -1;
        bool mouseOverAntes = mouseOver;
        //PigCamera cam = CGerenciadorJanelas::GetJanela(idJanela)->GetCamera();
        if (ChecaMouseOver(CMouse::PegaXYWorld())>0){
            for (int i=0;i<itens.size();i++){
                if(itens[i]->TrataEventoMouse(evento) == PIG_SELECIONADO_TRATADO){
                    if (itens[i]->GetAcionado())
                        resp = i;
                    printf("%d trat\n",i);
                }else
                    printf("%d nao trat\n",i);
            }
            SetAcionadoItem(resp,resp!=-1);
            if (resp>0)
                return PIG_SELECIONADO_TRATADO;
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


};

typedef CPigRadioBox *PigRadioBox;
#endif // _CPigRadioBox_
