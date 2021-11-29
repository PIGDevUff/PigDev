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

class CPIGForm: public CPIGComponente{

private:

    int totalComponentes;
    int componenteComFoco,componenteMouseOver;
    PIGComponente componentes[PIG_MAX_COMPONENTES];

    PIGEstadoEvento TrataEventoMouse(PIGEvento evento){
        componenteMouseOver = -1;
        for(int i=0;i<totalComponentes;i++){
            PIGEstadoEvento aux = componentes[i]->TrataEventoMouse(evento);
            if(aux == PIG_TRATADO){
                if (componenteComFoco!=-1 && componenteComFoco!=i){     //se já tem um outro componente com foco, ele vai perder o foco
                    componentes[componenteComFoco]->SetFoco(false);
                }
                componenteComFoco = i;                                //anota que terá o foco
                componenteMouseOver = i;                              //anota que tem MouseOver
                componentes[componenteComFoco]->SetFoco(true);        //faz o componente em questăo ganhar foco
                return aux;
            }else if (aux == PIG_MOUSEOVER){
                componenteMouseOver = i;
            }
        }
        if (evento.mouse.acao==PIG_MOUSE_PRESSIONADO&&evento.mouse.botao==PIG_MOUSE_ESQUERDO&&componenteComFoco!=-1){  //se já tem um componente com foco, ele vai perder o foco
            componentes[componenteComFoco]->SetFoco(false);
            componenteComFoco = -1;
        }
        return PIG_NAOSELECIONADO;
    }

    PIGEstadoEvento TrataEventoTeclado(PIGEvento evento){
        if(componenteComFoco!=-1){
            return componentes[componenteComFoco]->TrataEventoTeclado(evento);
        }

        PIGEstadoEvento resp = PIG_NAOSELECIONADO;

        for(int i=0;i<totalComponentes;i++){
            PIGEstadoEvento aux = componentes[i]->TrataEventoTeclado(evento);
            if (aux!=PIG_NAOSELECIONADO)
                resp = aux;
        }
        return resp;
    }

    void IniciaBase(){
        coresBasicas[0] = PRETO;
        totalComponentes = 0;
        componenteComFoco = componenteMouseOver = -1;
        for(int i=0;i<PIG_MAX_COMPONENTES;i++)
            componentes[i] = NULL;
        tipo = PIG_FORM;
    }

    static PIGTipoComponente GetTipoComponente(string tipo){
        transform(tipo.begin(), tipo.end(), tipo.begin(), ::toupper);
        if (tipo=="BOTAOCLICK") return PIG_BOTAOCLICK;
        if (tipo=="BOTAOONOFF") return PIG_BOTAOONOFF;
        if (tipo=="CAMPOTEXTO") return PIG_CAMPOTEXTO;
        if (tipo=="AREADETEXTO") return PIG_AREADETEXTO;
        if (tipo=="CHECKBOX") return PIG_CHECKBOX;
        if (tipo=="RADIOBOX") return PIG_RADIOBOX;
        if (tipo=="LISTBOX") return PIG_LISTBOX;
        if (tipo=="DROPDOWN") return PIG_DROPDOWN;
        if (tipo=="GAUGEBAR") return PIG_GAUGEBAR;
        if (tipo=="GAUGECIRCULAR") return PIG_GAUGECIRCULAR;
        if (tipo=="SLIDEBAR") return PIG_SLIDEBAR;
        printf("componente <%s> invalido lido da linha da parametros!!!\n",tipo.c_str());
        return (PIGTipoComponente)-1;
    }

    static CPIGForm LeArquivo(int idForm, string nomeArqTexto){
        CPIGForm *resp = NULL;

        ifstream arq(nomeArqTexto);
        string linha;
        if (!arq.is_open())
            printf("Erro abrir arquivo <%s> para construir form\n",nomeArqTexto.c_str());
        else{
            getline(arq,linha);

            CPIGAtributos atrib = CPIGAtributos::GetAtributos(linha);
            if (atrib.GetString("nomeArq","")!=""){
                resp = new CPIGForm(idForm,atrib.GetInt("altura",0),atrib.GetInt("largura",0),
                                        atrib.GetString("nomeArq",""),atrib.GetInt("retiraFundo",1),atrib.GetInt("janela",0));
            }else{
                resp = new CPIGForm(idForm,atrib.GetInt("altura",0),atrib.GetInt("largura",0),
                                        atrib.GetInt("janela",0));
            }

            while (arq.eof()==false){
                getline(arq,linha);
                if (linha[0]!='#')
                    resp->CriaComponentePorParametro(linha);
            }

            arq.close();
        }

        return *resp;
    }

    PIGTipoComponente GetTipo(){
        return PIG_FORM;
    }


public:

    CPIGForm(int idForm, int altForm, int largForm, int janela = 0):
        CPIGComponente(idForm,altForm,largForm,janela){
            IniciaBase();
    }

    CPIGForm(int idForm, int altForm, int largForm, string nomeArq, int retiraFundo=1, int janela = 0):
        CPIGComponente(idForm,altForm,largForm,nomeArq,retiraFundo,janela){
            IniciaBase();
    }

    CPIGForm(int idForm, string nomeArqTexto):CPIGForm(LeArquivo(idForm,nomeArqTexto)){}


    virtual ~CPIGForm(){
        for(int i=0;i<totalComponentes;i++){
            delete componentes[i];
        }
    }

    int GetIdComponente(string label){
        for(int i=0;i<totalComponentes;i++){
            if (componentes[i]->GetLabel()==label)
                return componentes[i]->GetId();
        }
        return -1;
    }

    inline int GetIdComponente(int componente){
        return (id * PIG_MAX_COMPONENTES) + componente;
    }

    int Desenha(){
        if (visivel==false) return 0;

        if (text)
            CPIGSprite::Desenha();
        else CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetangulo((int)pos.x,(int)pos.y,alt,larg,coresBasicas[0]);

        //desenha primeiro os componentes fora do mouse
        for(int i=0;i<totalComponentes;i++){
            if (i!=componenteMouseOver)
                componentes[i]->Desenha();
        }
        //desenha o componente sob o mouse para que o hint fique por cima dos demais
        if (componenteMouseOver!=-1)
            componentes[componenteMouseOver]->Desenha();

        lab->Desenha();

        return CPIGComponente::Desenha();
    }

    int TrataEvento(PIGEvento evento){
        if(evento.tipoEvento == PIG_EVENTO_MOUSE) return TrataEventoMouse(evento);
        if(evento.tipoEvento == PIG_EVENTO_TECLADO) return TrataEventoTeclado(evento);
        return 0;
    }

    PIGComponente GetComponente(int idComponente){
        if (componentes[idComponente % PIG_MAX_COMPONENTES]==NULL) throw CPIGErroIndice(idComponente,"componentes");
        return componentes[idComponente % PIG_MAX_COMPONENTES];
    }

    template <class T>
    T GetComponente(int idComponente){
        T comp = (T) componentes[idComponente % PIG_MAX_COMPONENTES];
        if (comp==NULL) throw CPIGErroIndice(idComponente,"componentes");
        return comp;
    }

    int CriaBotaoClick(int altura, int largura, string nomeArq, int retiraFundo=1){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPIGBotaoClick(idComponente,altura,largura,nomeArq,retiraFundo,idJanela);
        return idComponente;
    }

    int CriaBotaoClick(int altura, int largura){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPIGBotaoClick(idComponente,altura,largura,idJanela);
        return idComponente;
    }

    int CriaBotaoOnOff(int altura, int largura, string nomeArq, int retiraFundo=1){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPIGBotaoOnOff(idComponente,altura,largura,nomeArq,retiraFundo,idJanela);
        return idComponente;
    }

    int CriaBotaoOnOff(int altura, int largura){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPIGBotaoOnOff(idComponente,altura,largura,idJanela);
        return idComponente;
    }

    int CriaAreaDeTexto(int altura, int largura, string nomeArq, int maxCars=200, int retiraFundo=1){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPIGAreaDeTexto(idComponente,altura,largura,nomeArq,maxCars,retiraFundo,idJanela);
        return idComponente;
    }

    int CriaAreaDeTexto(int altura, int largura, int maxCars=200){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPIGAreaDeTexto(idComponente,altura,largura,maxCars,idJanela);
        return idComponente;
    }

    int CriaCampoTextoESenha(int altura, int largura, string nomeArq, int maxCars=200, bool apenasNumeros=false, int retiraFundo=1, bool campoSenha=false){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPIGCampoTextoESenha(idComponente,altura,largura,nomeArq,maxCars,apenasNumeros,campoSenha,retiraFundo,idJanela);
        return idComponente;
    }

    int CriaCampoTextoESenha(int altura, int largura, int maxCars=200, bool apenasNumeros=false, bool campoSenha=false){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPIGCampoTextoESenha(idComponente,altura,largura,maxCars,apenasNumeros,campoSenha,idJanela);
        return idComponente;
    }

    int CriaListBox(int larguraTotal, int alturaLinha, int altItem, int largItem, string nomeArq, int retiraFundo=1){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPIGListBox(idComponente,larguraTotal,alturaLinha,altItem,largItem,nomeArq,retiraFundo,idJanela);
        return idComponente;
    }

    int CriaListBox(int larguraTotal, int alturaLinha, int altItem, int largItem){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPIGListBox(idComponente,larguraTotal,alturaLinha,altItem,largItem,idJanela);
        return idComponente;
    }

    int CriaDropDown(int larguraTotal, int alturaLinha, int altItem, int largItem, string nomeArq, int retiraFundo=1){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPIGDropDown(idComponente,larguraTotal,alturaLinha,altItem,largItem,nomeArq,retiraFundo,idJanela);
        return idComponente;
    }

    int CriaDropDown(int larguraTotal, int alturaLinha, int altItem, int largItem){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPIGDropDown(idComponente,larguraTotal,alturaLinha,altItem,largItem,idJanela);
        return idComponente;
    }

    int CriaGaugeBar(int altura, int largura, string imgMoldura, string imgMarcador="", int retiraFundoMoldura=1, int retiraFundoMarcador=1){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPIGGaugeBar(idComponente,altura,largura,imgMoldura,imgMarcador,retiraFundoMoldura,retiraFundoMarcador,idJanela);
        return idComponente;
    }

    int CriaGaugeBar(int altura, int largura){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPIGGaugeBar(idComponente,altura,largura,idJanela);
        return idComponente;
    }

    int CriaRadioBox(int larguraTotal, int alturaLinha, string imagemItem, int alturaItem, int larguraItem, string imagemFundo, int retiraFundo=1){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPIGRadioBox(idComponente,larguraTotal,alturaLinha,imagemItem,alturaItem,larguraItem,imagemFundo,retiraFundo,idJanela);
        return idComponente;
    }

    int CriaRadioBox(int larguraTotal, int alturaLinha, string imagemItem, int alturaItem, int larguraItem){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPIGRadioBox(idComponente,larguraTotal,alturaLinha,imagemItem,alturaItem,larguraItem,idJanela);
        return idComponente;
    }

    int CriaCheckBox(int larguraTotal, int alturaLinha, string imagemItem, int alturaItem, int larguraItem, string imagemFundo, int retiraFundo=1){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPIGCheckBox(idComponente,larguraTotal,alturaLinha,imagemItem,alturaItem,larguraItem,imagemFundo,retiraFundo,idJanela);
        return idComponente;
    }

    int CriaCheckBox(int larguraTotal, int alturaLinha, string imagemItem, int alturaItem, int larguraItem){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPIGCheckBox(idComponente,larguraTotal,alturaLinha,imagemItem,alturaItem,larguraItem,idJanela);
        return idComponente;
    }

    int CriaGaugeCircular(int altura, int largura){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPIGGaugeCircular(idComponente,altura,largura,idJanela);
        return idComponente;
    }

    int CriaGaugeCircular(int altura, int largura, string imgTrilha, int alturaMarcador, int larguraMarcador, string imgMarcador, int retiraFundoTrilha=1, int retiraFundoMarcador=1){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPIGGaugeCircular(idComponente,altura,largura,imgTrilha,alturaMarcador,larguraMarcador, imgMarcador, retiraFundoTrilha, retiraFundoMarcador, idJanela);
        return idComponente;
    }

    int CriaSlideBar(int altura, int largura, string imgTrilha, int alturaMarcador, int larguraMarcador, string imgMarcador, int retiraFundoTrilha=1, int retiraFundoMarcador=1){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPIGSlideBar(idComponente,altura,largura,imgTrilha,alturaMarcador,larguraMarcador,imgMarcador,retiraFundoTrilha,retiraFundoMarcador,idJanela);
        return idComponente;
    }

    int CriaSlideBar(int altura, int largura, int alturaMarcador, int larguraMarcador){
        int idComponente = GetIdComponente(totalComponentes);
        componentes[totalComponentes++] = new CPIGSlideBar(idComponente,altura,largura,alturaMarcador,larguraMarcador,idJanela);
        return idComponente;
    }

    void SetFoco(bool valor){
        temFoco = valor;
    }

    void SetAcionado(bool valor){
        acionado = valor;
    }

    void SetMouseOver(bool valor){
        mouseOver = valor;
    }

    void SetHabilitado(bool valor){
        habilitado = valor;
    }

    int CriaComponentePorParametro(string parametros){
        int idComponente = GetIdComponente(totalComponentes);
        //printf("parametros: %s\n",parametros.c_str());
        CPIGAtributos atrib = CPIGAtributos::GetAtributos(parametros);
        int componente = GetTipoComponente(atrib.GetString("tipo",""));

        switch(componente){
            case PIG_BOTAOCLICK: componentes[totalComponentes++] = new CPIGBotaoClick(idComponente,atrib);break;
            case PIG_BOTAOONOFF: componentes[totalComponentes++] = new CPIGBotaoOnOff(idComponente,atrib);break;
            case PIG_AREADETEXTO: componentes[totalComponentes++] = new CPIGAreaDeTexto(idComponente,atrib);break;
            case PIG_CAMPOTEXTO: componentes[totalComponentes++] = new CPIGCampoTextoESenha(idComponente,atrib);break;
            case PIG_RADIOBOX: componentes[totalComponentes++] = new CPIGRadioBox(idComponente,atrib);break;
            case PIG_CHECKBOX: componentes[totalComponentes++] = new CPIGCheckBox(idComponente,atrib);break;
            case PIG_LISTBOX: componentes[totalComponentes++] = new CPIGListBox(idComponente,atrib);break;
            case PIG_DROPDOWN: componentes[totalComponentes++] = new CPIGDropDown(idComponente,atrib);break;
            case PIG_GAUGEBAR: componentes[totalComponentes++] = new CPIGGaugeBar(idComponente,atrib);break;
            case PIG_SLIDEBAR: componentes[totalComponentes++] = new CPIGSlideBar(idComponente,atrib);break;
            case PIG_GAUGECIRCULAR: componentes[totalComponentes++] = new CPIGGaugeCircular(idComponente,atrib);break;
        }
        //printf("id comp %d %d\n",idComponente,totalComponentes);
        return idComponente;
    }

};
typedef CPIGForm *PIGForm;
#endif // _CPIGFORM_
