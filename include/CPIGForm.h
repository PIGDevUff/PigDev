#ifndef _CPIGFORM_
#define _CPIGFORM_

#include "CPIGComponente.h"
#include "CPIGBotaoClick.h"
#include "CPIGBotaoOnOff.h"
#include "CPIGCampoTextoESenha.h"
#include "CPIGAreaDeTexto.h"
#include "CPIGRadioBox.h"
#include "CPIGCheckBox.h"
#include "CPIGListBox.h"
#include "CPIGDropDown.h"
#include "CPIGSlideBar.h"
#include "CPIGGaugeBar.h"
#include "CPIGGaugeCircular.h"

typedef enum{PIG_BOTAOCLICK,PIG_BOTAOONOFF,PIG_AREADETEXTO,PIG_CAMPOTEXTOSENHA,PIG_RADIOBOX,PIG_CHECKBOX,PIG_LISTBOX,PIG_DROPDOWN,PIG_GAUGEBAR,PIG_GAUGECIRCULAR,PIG_SLIDEBAR}PIGTiposComponentes;

class CPIGForm{

private:

    int idJanela,id;
    SDL_Point pos;
    int alt,larg;
    int totalComponentes;
    int componenteComFoco,componenteMouseOver;
    PIGComponente componentes[PIG_MAX_COMPONENTES];

    int TrataMouseComponentes(PIG_Evento evento){
        componenteMouseOver = -1;
        for(int i=0;i<totalComponentes;i++){
            int aux = componentes[i]->TrataEventoMouse(evento);
            if(aux == PIG_SELECIONADO_TRATADO){
                if (componenteComFoco!=-1 && componenteComFoco!=i){  //se já tem um outro componente com foco, ele vai perder o foco
                    componentes[componenteComFoco]->SetFoco(false);
                }
                componenteComFoco = i;                                //anota que terá o foco
                componenteMouseOver = i;                              //anota que tem MouseOver
                componentes[componenteComFoco]->SetFoco(true);        //faz o componente em questão ganhar foco
                return 1;
            }else if (aux == PIG_SELECIONADO_MOUSEOVER){
                componenteMouseOver = i;
            }
        }
        if (evento.mouse.acao==PIG_MOUSE_PRESSIONADO&&evento.mouse.botao==PIG_MOUSE_ESQUERDO&&componenteComFoco!=-1){  //se já tem um componente com foco, ele vai perder o foco
            componentes[componenteComFoco]->SetFoco(false);
            componenteComFoco = -1;
        }
        return 0;
    }

    int TrataTecladoComponentes(PIG_Evento evento){
        if(componenteComFoco!=-1){
            return componentes[componenteComFoco]->TrataEventoTeclado(evento);
        }
        for(int i=0;i<totalComponentes;i++){
            componentes[i]->TrataEventoTeclado(evento);
        }
        return PIG_NAO_SELECIONADO;
    }

    void IniciaBase(int idForm, int px, int py, int altura, int largura,int janela){
        id = idForm;
        pos = {px,py};
        alt = altura;
        larg = largura;
        idJanela = janela;
        totalComponentes = 0;
        componenteComFoco = componenteMouseOver = -1;
        for(int i=0;i<PIG_MAX_COMPONENTES;i++)
            componentes[i] = NULL;
    }

    static PIGTiposComponentes GetTipoComponente(string tipo){
        transform(tipo.begin(), tipo.end(), tipo.begin(), ::toupper);
        if (tipo=="BOTAOCLICK") return PIG_BOTAOCLICK;
        if (tipo=="BOTAOONOFF") return PIG_BOTAOONOFF;
        if (tipo=="CAMPOTEXTOSENHA") return PIG_CAMPOTEXTOSENHA;
        if (tipo=="AREATEXTO") return PIG_AREADETEXTO;
        if (tipo=="CHECKBOX") return PIG_CHECKBOX;
        if (tipo=="RADIOBOX") return PIG_RADIOBOX;
        if (tipo=="LISTBOX") return PIG_LISTBOX;
        if (tipo=="DROPDOWN") return PIG_DROPDOWN;
        if (tipo=="GAUGEBAR") return PIG_GAUGEBAR;
        if (tipo=="GAUGECIRCULAR") return PIG_GAUGECIRCULAR;
        if (tipo=="SLIDEBAR") return PIG_SLIDEBAR;
        printf("componente <%s> invalido lido da linha da parametros!!!\n");
        return (PIGTiposComponentes)-1;
    }

public:

    CPIGForm(int idForm, int xForm, int yForm, int altForm, int largForm, int janela = 0){
        IniciaBase(idForm,xForm,yForm,altForm,largForm,janela);
    }

    CPIGForm(int idForm, string nomeArqTexto){
        IniciaBase(idForm,0,0,0,0,0);

        ifstream arq(nomeArqTexto);
        string linha,variavel;
        if (!arq.is_open())
            printf("Erro abrir arquivo <%s> para construir form\n",nomeArqTexto.c_str());
        else{
            getline(arq,linha);

            CPIGAtributos atribForm = CPIGComponente::GetAtributos(linha);
            pos.x = atribForm.GetInt("px",0);
            pos.y = atribForm.GetInt("py",0);
            alt = atribForm.GetInt("altura",0);
            larg = atribForm.GetInt("largura",0);
            idJanela = atribForm.GetInt("janela",0);
            //printf("processada primeira linha %d,%d %d,%d %d\n",(int)pos.x,(int)pos.y,alt,larg,idJanela);

            while (arq.eof()==false){
                arq >> variavel;
                getline(arq,linha);

                CriaComponentePorParametro(GetTipoComponente(variavel),linha);
            }

            arq.close();
        }
    }

    ~CPIGForm(){
        for(int i=0;i<totalComponentes;i++){
            delete componentes[i];
        }
    }

    inline int GetIdComponente(int componente){
        return (id * PIG_MAX_COMPONENTES) + componente;
    }

    int Desenha(){
        //desenha primeiro os componentes fora do mouse
        for(int i=0;i<totalComponentes;i++){
            if (i!=componenteMouseOver)
                componentes[i]->Desenha();
        }
        //desenha o componente sob o mouse para que o hint fique por cima dos demais
        if (componenteMouseOver!=-1)
            componentes[componenteMouseOver]->Desenha();

        return 1;
    }

    int TrataEvento(PIG_Evento evento){

        if(evento.tipoEvento == PIG_EVENTO_MOUSE) return TrataMouseComponentes(evento);

        if(evento.tipoEvento == PIG_EVENTO_TECLADO) return TrataTecladoComponentes(evento);

        return 0;
    }

    PIGComponente GetComponente(int idComponente){
        //printf("vou tentar pegar o compo %d\n",idComponente);
        if (componentes[idComponente % PIG_MAX_COMPONENTES]==NULL) throw CPIGErroIndice(idComponente,"componentes");
        //printf("devolvendo %d\n",idComponente);
        return componentes[idComponente % PIG_MAX_COMPONENTES];
    }

    template <class T>
    T GetComponente(int idComponente){
        T comp = (T) componentes[idComponente % PIG_MAX_COMPONENTES];
        if (comp==NULL) throw CPIGErroIndice(idComponente,"componentes");
        return comp;
    }

    int CriaBotaoClick(int px, int py, int altura,int largura,std::string nomeArq,int retiraFundo = 1){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPIGBotaoClick(idComponente,px,py,altura,largura,nomeArq,retiraFundo,idJanela);
        return idComponente;
    }

    int CriaBotaoClick(int px, int py, int altura,int largura){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPIGBotaoClick(idComponente,px,py,altura,largura,idJanela);
        return idComponente;
    }

    int CriaBotaoOnOff(int px, int py, int altura,int largura,std::string nomeArq,int retiraFundo = 1){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPIGBotaoOnOff(idComponente,px,py,altura,largura,nomeArq,retiraFundo,idJanela);
        return idComponente;
    }

    int CriaBotaoOnOff(int px, int py, int altura,int largura){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPIGBotaoOnOff(idComponente,px,py,altura,largura,idJanela);
        return idComponente;
    }

    int CriaAreaDeTexto(int px, int py, int altura,int largura,std::string nomeArq,int maxCars = 200,int retiraFundo=1){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPIGAreaDeTexto(idComponente,px,py,altura,largura,nomeArq,maxCars,retiraFundo,idJanela);
        return idComponente;
    }

    int CriaAreaDeTexto(int px, int py, int altura,int largura,int maxCars = 200){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPIGAreaDeTexto(idComponente,px,py,altura,largura,maxCars,idJanela);
        return idComponente;
    }

    int CriaCampoTextoESenha(int px, int py, int altura,int largura,std::string nomeArq,int maxCars = 200, bool apenasNumeros=false, int retiraFundo=1,bool campoSenha = false){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPIGCampoTextoESenha(idComponente,px,py,altura,largura,nomeArq,maxCars,apenasNumeros,campoSenha,retiraFundo,idJanela);
        return idComponente;
    }

    int CriaCampoTextoESenha(int px, int py, int altura,int largura,int maxCars = 200, bool apenasNumeros=false, bool campoSenha = false){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPIGCampoTextoESenha(idComponente,px,py,altura,largura,maxCars,apenasNumeros,campoSenha,idJanela);
        return idComponente;
    }

    int CriaListBox(int px, int py,int larguraTotal, int alturaLinha, int altItem, int largItem,std::string nomeArq,int retiraFundo=1){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPIGListBox(idComponente,px,py,larguraTotal,alturaLinha,altItem,largItem,nomeArq,retiraFundo,idJanela);
        return idComponente;
    }

    int CriaListBox(int px, int py,int larguraTotal, int alturaLinha, int altItem, int largItem){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPIGListBox(idComponente,px,py,larguraTotal,alturaLinha,altItem,largItem,idJanela);
        return idComponente;
    }

    int CriaDropDown(int px, int py, int larguraTotal,int alturaLinha, int altItem, int largItem, std::string nomeArq,int retiraFundo=1){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPIGDropDown(idComponente,px,py,larguraTotal,alturaLinha,altItem,largItem,nomeArq,retiraFundo,idJanela);
        return idComponente;
    }

    int CriaDropDown(int px, int py, int larguraTotal,int alturaLinha, int altItem, int largItem){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPIGDropDown(idComponente,px,py,larguraTotal,alturaLinha,altItem,largItem,idJanela);
        return idComponente;
    }

    int CriaGaugeBar(int px, int py,int altura,int largura,std::string imgMoldura,std::string imgMarcador="",int retiraFundoMoldura=1,int retiraFundoMarcador=1){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPIGGaugeBar(idComponente,px,py,altura,largura,imgMoldura,imgMarcador,retiraFundoMoldura,retiraFundoMarcador,idJanela);
        return idComponente;
    }

    int CriaGaugeBar(int px, int py,int altura,int largura){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPIGGaugeBar(idComponente,px,py,altura,largura,idJanela);
        return idComponente;
    }

    int CriaRadioBox(int px, int py, int larguraTotal,int alturaLinha, std::string imagemItem, int alturaItem,int larguraItem, std::string imagemFundo, int retiraFundo=1){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPIGRadioBox(idComponente,px,py,larguraTotal,alturaLinha,imagemItem,alturaItem,larguraItem,imagemFundo,retiraFundo,idJanela);
        return idComponente;
    }

    int CriaRadioBox(int px, int py, int larguraTotal,int alturaLinha, std::string imagemItem, int alturaItem,int larguraItem){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPIGRadioBox(idComponente,px,py,larguraTotal,alturaLinha,imagemItem,alturaItem,larguraItem,idJanela);
        return idComponente;
    }

    int CriaCheckBox(int px, int py, int larguraTotal,int alturaLinha, std::string imagemItem, int alturaItem, int larguraItem, std::string imagemFundo, int retiraFundo=1){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPIGCheckBox(idComponente,px,py,larguraTotal,alturaLinha,imagemItem,alturaItem,larguraItem,imagemFundo,retiraFundo,idJanela);
        return idComponente;
    }

    int CriaCheckBox(int px, int py, int larguraTotal,int alturaLinha, std::string imagemItem, int alturaItem, int larguraItem){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPIGCheckBox(idComponente,px,py,larguraTotal,alturaLinha,imagemItem,alturaItem,larguraItem,idJanela);
        return idComponente;
    }

    int CriaGaugeCircular(int px, int py,int altura,int largura,int raioInterior,int idJanela=0){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPIGGaugeCircular(idComponente,px,py,altura,largura,raioInterior,idJanela);
        return idComponente;
    }

    int CriaSlideBar(int px, int py, int altura, int largura, string imgTrilha, int alturaMarcador, int larguraMarcador, string imgMarcador,int retiraFundoTrilha=1, int retiraFundoMarcador=1,int idJanela=0){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPIGSlideBar(idComponente,px,py,altura,largura,imgTrilha,alturaMarcador,larguraMarcador,imgMarcador,retiraFundoTrilha,retiraFundoMarcador,idJanela);
        return idComponente;
    }

    int CriaSlideBar(int px, int py, int altura, int largura, int alturaMarcador, int larguraMarcador, int idJanela=0){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPIGSlideBar(idComponente,px,py,altura,largura,alturaMarcador,larguraMarcador,idJanela);
        return idComponente;
    }

    int CriaComponentePorParametro(PIGTiposComponentes componente,string parametros){
        int idComponente = GetIdComponente(totalComponentes);
        //printf("parametros: %s\n",parametros.c_str());
        switch(componente){
            case PIG_BOTAOCLICK: componentes[totalComponentes++] = new CPIGBotaoClick(idComponente,parametros);break;
            case PIG_BOTAOONOFF: componentes[totalComponentes++] = new CPIGBotaoOnOff(idComponente,parametros);break;
            case PIG_AREADETEXTO: componentes[totalComponentes++] = new CPIGAreaDeTexto(idComponente,parametros);break;
            case PIG_CAMPOTEXTOSENHA: componentes[totalComponentes++] = new CPIGCampoTextoESenha(idComponente,parametros);break;
            case PIG_RADIOBOX: componentes[totalComponentes++] = new CPIGRadioBox(idComponente,parametros);break;
            case PIG_CHECKBOX: componentes[totalComponentes++] = new CPIGCheckBox(idComponente,parametros);break;
            case PIG_LISTBOX: componentes[totalComponentes++] = new CPIGListBox(idComponente,parametros);break;
            case PIG_DROPDOWN: componentes[totalComponentes++] = new CPIGDropDown(idComponente,parametros);break;
            case PIG_GAUGEBAR: componentes[totalComponentes++] = new CPIGGaugeBar(idComponente,parametros);break;
            case PIG_SLIDEBAR: componentes[totalComponentes++] = new CPIGSlideBar(idComponente,parametros);break;
            case PIG_GAUGECIRCULAR: componentes[totalComponentes++] = new CPIGGaugeCircular(idComponente,parametros);break;
        }
        //printf("id comp %d %d\n",idComponente,totalComponentes);
        return idComponente;
    }

};
typedef CPIGForm *PIGForm;
#endif // _CPIGFORM_
