#ifndef _CPIGLISTAITEMCOMPONENTE_
#define _CPIGLISTAITEMCOMPONENTE_

#include "CPIGItemComponente.h"

class CPIGListaItemComponente: public CPIGComponente{

protected:

    int altBaseLista;                     //espaço vertical entre os itens
    PIGPosicaoComponente posIcones,posLabels;
    vector<PIGItemComponente> itens;
    int altIcone,largIcone;                           //altura e largura das imagens dos itens

    static PIGPosicaoComponente GetAlinhamento(string alinhamento){
        transform(alinhamento.begin(), alinhamento.end(), alinhamento.begin(), ::toupper);
        if (alinhamento=="ESQ_CENTRO") return PIG_POSICAO_ESQ_CENTRO;
        if (alinhamento=="DIR_CENTRO") return PIG_POSICAO_DIR_CENTRO;
        if (alinhamento=="CENTRO_CENTRO") return PIG_POSICAO_CENTRO_CENTRO;
        return PIG_POSICAO_ESQ_CENTRO;
    }

    void IniciaCoresBasicas(){
        coresBasicas[0] = CINZA;
        coresBasicas[1] = AZUL;
    }

    virtual void ProcessaAtributos(CPIGAtributos atrib)override{
        CPIGComponente::ProcessaAtributos(atrib);

        string valorStr = atrib.GetString("alinhamentoLabels","");
        if (valorStr!="") AlinhaLabelItens(GetAlinhamento(valorStr));

        valorStr = atrib.GetString("alinhamentoIcones","");
        if (valorStr!="") AlinhaIcones(GetAlinhamento(valorStr));
    }

    void IniciaBase(int alturaLinha){
        SetPosicaoPadraoLabel(PIG_POSICAO_CIMA_CENTRO);//posiçăo padrăo do label
        altBaseLista = alturaLinha;
        altIcone = largIcone = alturaLinha;
        posIcones = PIG_POSICAO_ESQ_CENTRO;//só pode ser posicionamento à esquerda ou à direita
        IniciaCoresBasicas();
    }

    PIGItemComponente CriaItem(int yItem, string itemLabel, string arqImagemIcone="", string arqImagemFundo="", bool itemMarcado = false, bool itemHabilitado = true, string hintMsg="", int retiraFundo=1, int retiraFundoIcone=1){
        PIGItemComponente item;
        if (arqImagemFundo==""){
            if (arqImagemIcone==""){
                item = new CPIGItemComponente(itens.size(),itemLabel,larg-(margemEsq+margemDir),altBaseLista,retiraFundo,idJanela);
            }else{
                item = new CPIGItemComponente(itens.size(),altIcone,largIcone,arqImagemIcone,itemLabel,larg-(margemEsq+margemDir),altBaseLista,retiraFundoIcone,idJanela);
            }
        }else{
            if (arqImagemIcone==""){
                item = new CPIGItemComponente(itens.size(),arqImagemFundo,itemLabel,larg-(margemEsq+margemDir),altBaseLista,retiraFundo,idJanela);
            }else{
                item = new CPIGItemComponente(itens.size(),altIcone,largIcone,arqImagemIcone,arqImagemFundo,itemLabel,larg-(margemEsq+margemDir),altBaseLista,retiraFundo,retiraFundoIcone,idJanela);
            }
        }
        item->Move(pos.x+margemEsq,yItem);
        item->SetHint(hintMsg);
        item->SetAudio(audioComponente);
        item->SetAcionado(itemMarcado);
        item->SetHabilitado(itemHabilitado);
        //item->SetMargens(margemEsq,margemDir,margemCima,margemBaixo);
        item->AlinhaIcone(posIcones);
        item->AlinhaLabel(posLabels);

        itens.push_back(item);
        return item;
    }

    void DeslocaItens(double dx, double dy){
        for(unsigned int i=0;i<itens.size();i++)
            itens[i]->Desloca(dx, dy);
    }

    CPIGListaItemComponente(int idComponente, int larguraTotal, int alturaLinha, string nomeArqFundoLista, int retiraFundo=1, int janela = 0):
        CPIGComponente(idComponente,0,larguraTotal,nomeArqFundoLista,retiraFundo,janela){
        IniciaBase(alturaLinha);
    }

    CPIGListaItemComponente(int idComponente, int larguraTotal, int alturaLinha, int janela = 0):
        CPIGComponente(idComponente,0,larguraTotal,janela){
        IniciaBase(alturaLinha);
    }

    virtual ~CPIGListaItemComponente(){
        for (PIGItemComponente i: itens)
            delete i;
        itens.clear();
    }

public:

    virtual void CriaItem(CPIGAtributos atrib)=0;

    void SetDimensoesIcone(int alturaIcone, int larguraIcone){
        for (unsigned int i=0;i<itens.size();i++){
            itens[i]->SetDimensoesIcone(alturaIcone,larguraIcone);
        }
    }

    void AlinhaLabelItens(PIGPosicaoComponente valor){
        if (posLabels!=valor){//se os labels estăo ŕ direita do botőes, inverte
            posLabels = valor;
            for (PIGItemComponente i: itens)
                i->AlinhaLabel(posLabels);
        }
    }

    void AlinhaIcones(PIGPosicaoComponente valor){
        if (posIcones!=valor){//se os labels estăo à direita do botőes, inverte
            posIcones = valor;
            for (PIGItemComponente i: itens)
                i->AlinhaIcone(posIcones);
        }
    }

    int GetAcionadoItem(int indice){
        if (indice<0||indice>=itens.size()) return -1;
        return itens[indice]->GetAcionado();
    }

    virtual int SetAcionadoItem(int indice, bool valor){
        if (indice<0||indice>=itens.size()) return 0;
        itens[indice]->SetAcionado(valor);
        return 1;
    }

    int SetAcionadoApenasItem(int indice, bool valor){
        if (indice<0||indice>=itens.size()) return 0;
        if (valor){
            for (PIGItemComponente i: itens)
                i->SetAcionado(false);
        }
        itens[indice]->SetAcionado(valor);
        return 1;
    }

    void SetAudioItem(int audio, int indice=-1){
        if (indice==-1){
            for(PIGItemComponente item :itens) item->SetAudio(audio);
        }else if (indice>=0&&indice<itens.size()){
            itens[indice]->SetAudio(audio);
        }
    }

    void SetCorLabelItem(PIGCor cor, int indice=-1){
        if (indice==-1){
            for(PIGItemComponente item :itens) item->SetCorLabel(cor);
        }else if (indice>=0&&indice<itens.size()){
            itens[indice]->SetCorLabel(cor);
        }
    }

    void SetCorFundoItem(PIGCor cor, int indice=-1){
        if (indice==-1){
            for(PIGItemComponente item :itens) item->SetCorFundo(cor);
        }else if (indice>=0&&indice<itens.size()){
            itens[indice]->SetCorFundo(cor);
        }
    }

    void SetFonteItem(int fonte, int indice=-1){
        if (indice==-1){
            for(PIGItemComponente item :itens) item->SetFonteLabel(fonte);
        }else if (indice>=0&&indice<itens.size()){
            itens[indice]->SetFonteLabel(fonte);
        }
    }

    int GetHabilitadoItem(int indice){
        if (indice<0||indice>=itens.size()) return -1;
        return itens[indice]->GetHabilitado();
    }

    int SetHabilitadoItem(int indice, bool valor){
        if (indice<0||indice>=itens.size()) return -1;
        itens[indice]->SetHabilitado(valor);
        return 1;
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

    void SetHabilitado(bool valor)override{
        CPIGComponente::SetHabilitado(valor);
        for (PIGItemComponente i: itens)
            i->SetHabilitadoLista(habilitado);
    }

    string GetLabelItem(int indice){
        if (indice<0||indice>=itens.size()) return "";
        return itens[indice]->GetLabel();
    }

    void Move(double nx, double ny)override{
        double dx = nx-pos.x;
        double dy = ny-pos.y;

        CPIGComponente::Desloca(dx,dy);
        PosicionaLabel();

        DeslocaItens(dx,dy);
    }

};
typedef CPIGListaItemComponente *PIGListaComponente;
#endif //_CPIGLISTAITEMCOMPONENTE_
