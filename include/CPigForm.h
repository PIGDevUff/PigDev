#ifndef _PIGFORM_
#define _PIGFORM_

#include "CPigComponente.h"
#include "CPigBotao.h"
#include "CPigScrollBar.h"
#include "CPigCaixaTexto.h"
#include "CPigCampoTextoESenha.h"
#include "CPigAreaDeTexto.h"
#include "CPigItemComponente.h"
#include "CPigListaItemComponente.h"
#include "CPigRadioBox.h"
#include "CPigCheckBox.h"
#include "CPigListBox.h"
#include "CPigDropDown.h"
#include "CPigGauge.h"
#include "CPigGaugeCircular.h"

#define MAX_COMPONENTES 500
#define MAX_FORMS 100

typedef enum{BOTAO,AREADETEXTO,CAMPOTEXTOSENHA,RADIOBOX,CHECKBOX,LISTA,DROPDOWN,GAUGE,GAUGECIRCULAR,SCROLLBAR}tipos_Componentes;

class CPigForm{

private:

    int idJanela,id;
    int x,y,alt,larg;
    int totalComponentes;
    int componenteComFoco;
    PigComponente componentes[MAX_COMPONENTES];

    inline int GetIdComponente(int componente){
        return (id * MAX_COMPONENTES) + componente;
    }

    int TrataMouseComponentes(PIG_Evento evento){
        for(int i=0;i<totalComponentes;i++){
            if(componentes[i]->TrataEventoMouse(evento) == SELECIONADO_TRATADO){
                if (componenteComFoco!=-1 && componenteComFoco!=i){  //se já tem um outro componente com foco, ele vai perder o foco
                    componentes[componenteComFoco]->SetFoco(false);
                }
                componenteComFoco = i;                              //anota que terá o foco
                componentes[componenteComFoco]->SetFoco(true);        //faz o componente em questão ganhar foco
                return 1;
            }
        }
        if (evento.mouse.acao==MOUSE_PRESSIONADO&&evento.mouse.botao==MOUSE_ESQUERDO&&componenteComFoco!=-1){  //se já tem um componente com foco, ele vai perder o foco
            componentes[componenteComFoco]->SetFoco(false);
            componenteComFoco = -1;
        }
        return 0;
    }

    int TrataTecladoComponentes(PIG_Evento evento){
        if(componenteComFoco!=-1){
            componentes[componenteComFoco]->TrataEventoTeclado(evento);
            return 1;
        }
        for(int i=0;i<totalComponentes;i++)
            componentes[i]->TrataEventoTeclado(evento);

        return 2;
    }

public:

    CPigForm(int idForm,int xForm, int yForm, int altForm, int largForm,int janela = 0){
        x = xForm;
        y = yForm;
        alt = altForm;
        larg = largForm;
        idJanela = janela;
        totalComponentes = 0;
        id = idForm;
        componenteComFoco = -1;
        for(int i=0;i<MAX_COMPONENTES;i++)
            componentes[i] = NULL;
    }

    ~CPigForm(){
        for(int i=0;i<totalComponentes;i++)
            delete componentes[i];
    }

    int Desenha(){
        for(int i=0;i<totalComponentes;i++)
            componentes[i]->Desenha();
    }

    int TrataEvento(PIG_Evento evento){

        if(evento.tipoEvento == EVENTO_MOUSE) return TrataMouseComponentes(evento);

        if(evento.tipoEvento == EVENTO_TECLADO) return TrataTecladoComponentes(evento);

        return 0;
    }

    CPigComponente* GetComponente(int idComponente){
        return componentes[idComponente % MAX_COMPONENTES];
    }

    int CriaBotao(int px, int py, int altura,int largura,std::string nomeArq,int retiraFundo = 1){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPigBotao(idComponente,px,py,altura,largura,nomeArq,retiraFundo,idJanela);
        return idComponente;
    }

    int CriaAreaDeTexto(int px, int py, int altura,int largura,std::string nomeArq,int maxCars = 200,int retiraFundo=1){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPigAreaDeTexto(idComponente,px,py,altura,largura,nomeArq,maxCars,retiraFundo,idJanela);
        return idComponente;
    }

    int CriaCampoTextoESenha(int px, int py, int altura,int largura,std::string nomeArq,int maxCars = 200, bool apenasNumeros=false, int retiraFundo=1,bool campoSenha = false){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPigCampoTextoESenha(idComponente,px,py,altura,largura,nomeArq,maxCars,apenasNumeros,retiraFundo,idJanela,campoSenha);
        return idComponente;
    }

    int CriaListBox(int px, int py,int larguraTotal, int alturaLinha, int alturaMaxima,int altItem, int largItem,std::string nomeArq,int retiraFundo=1){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPigListBox(idComponente,px,py,larguraTotal,alturaLinha,alturaMaxima,altItem,largItem,nomeArq,retiraFundo,idJanela);
        return idComponente;
    }

    int CriaDropDown(int px, int py, int larguraTotal,int alturaLinha, int alturaMaxima, int altItem, int largItem, std::string nomeArq,int retiraFundo=1){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPigDropDown(idComponente,px,py,larguraTotal,alturaLinha,alturaMaxima,altItem,largItem,nomeArq,retiraFundo,idJanela);
        return idComponente;
    }

    int CriaGauge(int px, int py,int altura,int largura,std::string imgGauge,int retiraFundo=1){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPigGauge(idComponente,px,py,altura,largura,imgGauge,retiraFundo,idJanela);
        return idComponente;
    }

    int CriaRadioBox(int px, int py, int larguraTotal,int alturaLinha, int alturaMaxima,std::string imagemItem, int alturaItem,int larguraItem, std::string imagemFundo, int retiraFundo=1){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPigRadioBox(idComponente,px,py,larguraTotal,alturaLinha,alturaMaxima,imagemItem,alturaItem,larguraItem,imagemFundo,retiraFundo,idJanela);
        return idComponente;
    }

    int CriaCheckBox(int px, int py, int larguraTotal,int alturaLinha, int alturaMaxima, std::string imagemItem, int alturaItem, int larguraItem, std::string imagemFundo, int retiraFundo=1){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPigCheckBox(idComponente,px,py,larguraTotal,alturaLinha,alturaMaxima,imagemItem,alturaItem,larguraItem,imagemFundo,retiraFundo,idJanela);
        return idComponente;
    }

    int CriaGaugeCircular(int px, int py,int altura,int largura,int raioInterior,std::string nomeArq,int retiraFundo=1){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPigGaugeCircular(idComponente,px,py,altura,largura,raioInterior,nomeArq,retiraFundo,idJanela);
        return idComponente;
    }

    int CriaComponentePorArquivo(tipos_Componentes componente,std::string nomeArquivo){
        int idComponente = GetIdComponente(totalComponentes);
        switch(componente){
            case BOTAO: componentes[totalComponentes++] = new CPigBotao(nomeArquivo);break;
            case AREADETEXTO: componentes[totalComponentes++] = new CPigAreaDeTexto(nomeArquivo);break;
            case CAMPOTEXTOSENHA: componentes[totalComponentes++] = new CPigCampoTextoESenha(nomeArquivo);break;
            //case RADIOBOX: componentes[totalComponentes++] = new CPigRadioBox(nomeArquivo);break;
            case CHECKBOX: componentes[totalComponentes++] = new CPigCheckBox(nomeArquivo);break;
            //case LISTA: componentes[totalComponentes++] = new CPigLista(nomeArquivo);break;
            //case DROPDOWN: componentes[totalComponentes++] = new CPigDropDown(nomeArquivo);break;
            case GAUGE: componentes[totalComponentes++] = new CPigGauge(nomeArquivo);break;
            case SCROLLBAR: componentes[totalComponentes++] = new CPigScrollBar(nomeArquivo);break;
            case GAUGECIRCULAR: componentes[totalComponentes++] = new CPigGaugeCircular(nomeArquivo);break;
        }
        return idComponente;
    }

};

#endif // _PIGFORM_
