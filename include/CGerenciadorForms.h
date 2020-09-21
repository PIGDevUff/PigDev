#include "CPigForm.h"

class CGerenciadorForms{

private:

    static int totalForms;
    static PoolNumeros numForms;
    static CPigForm* forms[MAX_FORMS];

    static CPigForm* GetForm(int id){
        return forms[id];
    }

    static CPigForm* GetFormComponente(int idComponente){
        return forms[idComponente / MAX_COMPONENTES];
    }

public:

    static void Inicia(){
        totalForms = 0;
        for (int i=0;i<MAX_FORMS;i++)
            forms[i] = NULL;
        numForms = new CPoolNumeros(MAX_FORMS);
    }

    static void Encerra(){
        for (int i=0;i<MAX_FORMS;i++)
            if(forms[i]) delete forms[i];
    }

    static int CriaForm(int x,int y,int altura,int largura,int janela = 0){
        int posForm = numForms->RetiraLivre();
        forms[posForm] = new CPigForm(posForm,x,y,altura,largura,janela);
        totalForms++;
        return posForm;
    }

    static int Desenha(int idForm){
        GetForm(idForm)->Desenha();
    }

    static int TrataEvento(int idForm,PIG_Evento evento){
        return GetForm(idForm)->TrataEvento(evento);
    }

    static CPigComponente* GetComponente(int idComponente){
        CPigForm *form = GetFormComponente(idComponente);
        if(form) return form->GetComponente(idComponente);
        return NULL;
    }

    static int CriaBotao(int idForm,int x,int y,int altura,int largura,std::string nomeArq,int retiraFundo = 1){
        return GetForm(idForm)->CriaBotao(x,y,altura,largura,nomeArq,retiraFundo);
    }

    static int CriaAreaDeTexto(int idForm,int x, int y, int altura,int largura,std::string nomeArq,int maxCars = 200,int retiraFundo=1){
        return GetForm(idForm)->CriaAreaDeTexto(x,y,altura,largura,nomeArq,maxCars,retiraFundo);
    }

    static int CriaCampoTextoESenha(int idForm,int x, int y, int altura,int largura,std::string nomeArq,int maxCars = 200, bool apenasNumeros=false, int retiraFundo=1,bool campoSenha = false){
        return GetForm(idForm)->CriaCampoTextoESenha(x,y,altura,largura,nomeArq,maxCars,apenasNumeros,retiraFundo,campoSenha);
    }

    static int CriaListBox(int idForm,int x, int y,int larguraTotal,int alturaLinha, int alturaMaxima,int alturaItem,int larguraItem,std::string nomeArq,int retiraFundo=1){
        return GetForm(idForm)->CriaListBox(x,y,larguraTotal,alturaLinha,alturaMaxima,alturaItem,larguraItem,nomeArq,retiraFundo);
    }

    static int CriaDropDown(int idForm,int x, int y, int larguraTotal, int alturaLinha,int alturaMaxima,int alturaItem,int larguraItem,std::string nomeArq,int retiraFundo=1){
        return GetForm(idForm)->CriaDropDown(x,y,larguraTotal,alturaLinha,alturaMaxima,alturaItem,larguraItem,nomeArq,retiraFundo);
    }

    static int CriaGauge(int idForm,int x, int y,int altura,int largura,std::string imgGauge,int retiraFundo=1){
        return GetForm(idForm)->CriaGauge(x,y,altura,largura,imgGauge,retiraFundo);
    }

    static int CriaRadioBox(int idForm,int x, int y,int larguraTotal,int alturaLinha, int alturaMaxima,std::string imagemItem, int alturaItem, int larguraItem,std::string imagemFundo, int retiraFundo=1){
        return GetForm(idForm)->CriaRadioBox(x,y,larguraTotal,alturaLinha,alturaMaxima,imagemItem,alturaItem,larguraItem,imagemFundo,retiraFundo);
    }

    static int CriaCheckBox(int idForm,int x, int y,int larguraTotal,int alturaLinha, int alturaMaxima, std::string imagemItem, int alturaItem, int larguraItem,std::string imagemFundo,int retiraFundo=1){
        return GetForm(idForm)->CriaCheckBox(x,y,larguraTotal,alturaLinha,alturaMaxima,imagemItem,alturaItem,larguraItem,imagemFundo,retiraFundo);
    }

    static int CriaGaugeCircular(int idForm,int x,int y,int altura,int largura,int raioInterior,std::string nomeArq,int retiraFundo = 1){
        return GetForm(idForm)->CriaGaugeCircular(x,y,altura,largura,raioInterior,nomeArq,retiraFundo);
    }

    static int CriaComponentePorArquivo(int idForm,tipos_Componentes componente,std::string nomeArquivo){
        return GetForm(idForm)->CriaComponentePorArquivo(componente,nomeArquivo);
    }

};

int CGerenciadorForms::totalForms;
PoolNumeros CGerenciadorForms::numForms;
CPigForm* CGerenciadorForms::forms[MAX_FORMS];

