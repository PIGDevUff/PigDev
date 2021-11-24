#ifndef _CPIGLISTAITEMCOMPONENTE_
#define _CPIGLISTAITEMCOMPONENTE_

#include "CPIGItemComponente.h"

class CPIGListaItemComponente: public CPIGComponente{

protected:

    int altBaseLista;                     //espaço vertical entre os itens
    PIGPosicaoComponente posIcones,posLabels;
    vector<PIGItemComponente> itens;
    int itemDestaque;
    int altIcone,largIcone;                           //altura e largura das imagens dos itens

    void IniciaCoresBasicas(){
        coresBasicas[0] = CINZA;
        coresBasicas[1] = AZUL;
    }

    virtual void ProcessaAtributos(CPIGAtributos atrib)override{
        CPIGComponente::ProcessaAtributos(atrib);

        int larguraIcone = 0;
        int alturaIcone = 0;

        larguraIcone = atrib.GetInt("larguraIcone",largIcone);
        alturaIcone = atrib.GetInt("alturaIcone",altIcone);

        if (larguraIcone != largIcone || alturaIcone != altIcone)
            SetDimensoesIcone(alturaIcone,larguraIcone);
    }

    void IniciaBase(int alturaLinha){
        SetPosicaoPadraoLabel(PIG_COMPONENTE_CIMA_CENTRO);//posição padrão do label
        altBaseLista = alturaLinha;
        altIcone = largIcone = alturaLinha;
        posIcones = PIG_COMPONENTE_DIR_CENTRO;//só pode ser posicionamento à esquerda ou à direita
        itemDestaque = -1;
        IniciaCoresBasicas();
    }

    void CriaItem(int yItem, string itemLabel, string arqImagemIcone="", string arqImagemFundo="", bool itemMarcado = false, bool itemHabilitado = true, string hintMsg="", int retiraFundo=1, int retiraFundoIcone=1){
        PIGItemComponente item;
        if (arqImagemFundo==""){
            if (arqImagemIcone==""){
                item = new CPIGItemComponente(itens.size(),itemLabel,larg,altBaseLista,retiraFundo,idJanela);
            }else{
                item = new CPIGItemComponente(itens.size(),altIcone,largIcone,arqImagemIcone,itemLabel,larg,altBaseLista,retiraFundoIcone,idJanela);
            }
        }else{
            if (arqImagemIcone==""){
                item = new CPIGItemComponente(itens.size(),arqImagemFundo,itemLabel,larg,altBaseLista,retiraFundo,idJanela);
            }else{
                item = new CPIGItemComponente(itens.size(),altIcone,largIcone,arqImagemIcone,arqImagemFundo,itemLabel,larg,altBaseLista,retiraFundo,retiraFundoIcone,idJanela);
            }
        }
        item->Move(pos.x,yItem);
        item->SetHint(hintMsg);
        item->SetAudio(audioComponente);
        item->SetAcionado(itemMarcado);
        item->SetHabilitado(itemHabilitado);
        itens.push_back(item);
    }

    void DeslocaItens(double dx, double dy){
        for(unsigned int i=0;i<itens.size();i++)
            itens[i]->Desloca(dx, dy);
    }

public:

    CPIGListaItemComponente(int idComponente, int larguraTotal, int alturaLinha, string nomeArqFundoLista, int retiraFundo=1, int janela = 0):
        CPIGComponente(idComponente,0,larguraTotal,nomeArqFundoLista,retiraFundo,janela){
        IniciaBase(alturaLinha);
    }

    CPIGListaItemComponente(int idComponente, int larguraTotal, int alturaLinha, int janela = 0):
        CPIGComponente(idComponente,0,larguraTotal,janela){
        IniciaBase(alturaLinha);
    }

    ~CPIGListaItemComponente(){
        for (PIGItemComponente i: itens)
            delete i;
        itens.clear();
    }

    void SetDimensoesIcone(int alturaIcone, int larguraIcone){
        for (unsigned int i=0;i<itens.size();i++){
            itens[i]->SetDimensoesIcone(alturaIcone,larguraIcone);
        }
    }
    void AlinhaLabelDireita(){
        if (posLabels!=PIG_COMPONENTE_DIR_CENTRO){//se os labels estão à direita do botões, inverte
            for (PIGItemComponente i: itens)
                i->AlinhaLabelDireita();
            posLabels = PIG_COMPONENTE_DIR_CENTRO;
        }
    }

    void AlinhaLabelEsquerda(){
        if (posLabels!=PIG_COMPONENTE_ESQ_CENTRO){//se os labels estão à direita do botões, inverte
            for (PIGItemComponente i: itens)
                i->AlinhaLabelEsquerda();
            posLabels = PIG_COMPONENTE_ESQ_CENTRO;
        }
    }

    void AlinhaLabelCentro(){
        if (posLabels!=PIG_COMPONENTE_CENTRO_CENTRO){//se os labels estão à direita do botões, inverte
            for (PIGItemComponente i: itens)
                i->AlinhaLabelCentro();
            posLabels = PIG_COMPONENTE_CENTRO_CENTRO;
        }
    }

    void AlinhaIconeDireita(){
        if (posIcones==PIG_COMPONENTE_ESQ_CENTRO){//se os labels estão à direita do botões, inverte
            for (PIGItemComponente i: itens)
                i->AlinhaIconeDireita();
            posIcones = PIG_COMPONENTE_DIR_CENTRO;
        }
    }

    void AlinhaIconeEsquerda(){
        if (posIcones!=PIG_COMPONENTE_DIR_CENTRO){//se os labels estão à direita do botões, inverte
            for (PIGItemComponente i: itens)
                i->AlinhaIconeEsquerda();
            posIcones = PIG_COMPONENTE_ESQ_CENTRO;
        }
    }

    virtual int Desenha()=0;

    int GetAcionadoItem(int item){
        if (item<0||item>=itens.size()) return -1;
        return itens[item]->GetAcionado();
    }

    void SetAudioItem(int audio, int idItem=-1){
        if (idItem==-1){
            for(PIGItemComponente item :itens) item->SetAudio(audio);
        }else if (idItem>=0&&idItem<itens.size()){
            itens[idItem]->SetAudio(audio);
        }
    }

    void SetCorLabelItem(PIGCor cor, int idItem=-1){
        if (idItem==-1){
            for(PIGItemComponente item :itens) item->SetCorLabel(cor);
        }else if (idItem>=0&&idItem<itens.size()){
            itens[idItem]->SetCorLabel(cor);
        }
    }

    void SetCorFundoItem(PIGCor cor, int idItem=-1){
        if (idItem==-1){
            for(PIGItemComponente item :itens) item->SetCorFundo(cor);
        }else if (idItem>=0&&idItem<itens.size()){
            itens[idItem]->SetCorFundo(cor);
        }
    }

    void SetFonteItem(int fonte, int idItem=-1){
        if (idItem==-1){
            for(PIGItemComponente item :itens) item->SetFonteLabel(fonte);
        }else if (idItem>=0&&idItem<itens.size()){
            itens[idItem]->SetFonteLabel(fonte);
        }
    }

    int GetHabilitadoItem(int item){
        if (item<0||item>=itens.size()) return -1;
        return itens[item]->GetHabilitado();
    }

    int SetHabilitadoItem(int item, bool valor){
        if (item<0||item>=itens.size()) return -1;
        itens[item]->SetHabilitado(valor);
        return 1;
    }

    void SetHabilitado(bool valor) override{
        habilitado = valor;
        for(PIGItemComponente i: itens)
            i->SetHabilitado(habilitado);
    }

    void SetVisivel(bool valor) override{
        visivel = valor;
        for(PIGItemComponente i: itens)
            i->SetVisivel(visivel);
    }

    void SetFonteHint(int fonte) override{
        for (PIGItemComponente i: itens)
            i->SetFonteHint(fonte);
    }

    void SetAudio(int audio) override{
        audioComponente = audio;
        for (PIGItemComponente i: itens)
            i->SetAudio(audio);
    }

    int GetItemDestaque(){
        return itemDestaque;
    }

    int SetAcionadoItem(int indice, bool marcado){
        if (indice<0||indice>=itens.size()) return 0;
        if (marcado){
            itemDestaque = indice;
            for (PIGItemComponente i: itens)
                i->SetAcionado(false);
        }
        itens[indice]->SetAcionado(marcado);
        return 1;
    }

    void Move(double nx, double ny)override{
        double dx = nx-pos.x;
        double dy = ny-pos.y;

        CPIGComponente::Desloca(dx,dy);
        PosicionaLabel();

        DeslocaItens(dx,dy);

        AlinhaLabelEsquerda();
    }

};
typedef CPIGListaItemComponente *PIGListaComponente;
#endif //_CPIGLISTAITEMCOMPONENTE_
