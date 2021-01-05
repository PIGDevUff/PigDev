#ifndef _CPIGGerenciadorForms_
#define _CPIGGerenciadorForms_

#include "CPIGForm.h"

class CPIGGerenciadorForms{

private:

    /*static int totalForms;
    static PIGPoolNumeros numForms;
    static PIGForm forms[MAX_FORMS];*/
    /*static std::vector<int> posLivres;
    static std::unordered_map<int,PIGForm> forms;
    static std::unordered_map<int,PIGForm>::iterator it;*/

    static CPIGRepositorio<PIGForm> *forms;

public:

    static void Inicia(){
        /*totalForms = 0;
        for (int i=0;i<MAX_FORMS;i++)
            forms[i] = NULL;
        numForms = new CPIGPoolNumeros(MAX_FORMS);*/
        //for (int i=0;i<MAX_TIMERS;i++)
        //    posLivres.push_back(i);
        forms = new CPIGRepositorio<PIGForm>(MAX_FORMS,"forms");
    }

    static void Encerra(){
        /*for (int i=0;i<MAX_FORMS;i++)
            if(forms[i]) delete forms[i];*/
        //for(it = forms.begin(); it != forms.end(); ++it) {
        //    delete it->second;
        //}
        delete forms;
    }

    static PIGForm GetForm(int idForm){
        /*if (idForm<0||idForm>=MAX_FORMS||forms[idForm]==NULL) throw CPIGErroIndice(idForm,"forms");
        return forms[idForm];*/
        /*it = forms.find(idForm);
        if (it==forms.end()) throw CPIGErroIndice(idForm,"forms");
        return it->second;*/
        forms->GetElemento(idForm);
    }

    static PIGForm GetFormComponente(int idComponente){
        return GetForm(idComponente / MAX_COMPONENTES);
        /*int idForm = idComponente / MAX_COMPONENTES;
        if (idForm>=MAX_FORMS||forms[idForm]==NULL) throw CPIGErroIndice(idComponente,"forms");
        return forms[idForm];*/
    }

    static int CriaForm(int x,int y,int altura,int largura,int janela = 0){
        /*int posForm = numForms->RetiraLivre();
        forms[posForm] = new CPIGForm(posForm,x,y,altura,largura,janela);
        totalForms++;
        return posForm;*/
        /*int resp = posLivres[0];
        posLivres.erase(posLivres.begin());
        forms[resp] = new CPIGForm(resp,x,y,altura,largura,janela);
        return resp;*/
        int resp = forms->ProxID();
        forms->Insere(new CPIGForm(resp,x,y,altura,largura,janela));
    }

    static void DestroiForm(int idForm){
        /*PIGForm form = GetForm(idForm);
        numForms->DevolveUsado(idForm);
        delete form;
        totalForms--;
        forms[idForm] = NULL;*/
        /*PIGForm form = GetForm(idForm);
        delete form;
        forms.erase(idForm);*/
        forms->Remove(idForm);
    }

};
CPIGRepositorio<PIGForm> *CPIGGerenciadorForms::forms;
/*std::vector<int> CPIGGerenciadorForms::posLivres;
std::unordered_map<int,PIGForm> CPIGGerenciadorForms::forms;
std::unordered_map<int,PIGForm>::iterator CPIGGerenciadorForms::it;
*/
//int CPIGGerenciadorForms::totalForms;
//PIGPoolNumeros CPIGGerenciadorForms::numForms;
//CPIGForm* CPIGGerenciadorForms::forms[MAX_FORMS];

#endif // _CPIGGERENCIADORFORM_
