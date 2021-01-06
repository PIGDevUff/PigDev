#ifndef _CPIGGerenciadorForms_
#define _CPIGGerenciadorForms_

#include "CPIGForm.h"

class CPIGGerenciadorForms{

private:

    static CPIGRepositorio<PIGForm> *forms;

public:

    static void Inicia(){
        forms = new CPIGRepositorio<PIGForm>(MAX_FORMS,"forms");
    }

    static void Encerra(){
        delete forms;
    }

    static PIGForm GetForm(int idForm){
        return forms->GetElemento(idForm);
    }

    static PIGForm GetFormComponente(int idComponente){
        return GetForm(idComponente / MAX_COMPONENTES);
    }

    static int CriaForm(int x,int y,int altura,int largura,int janela = 0){
        int resp = forms->ProxID();
        return forms->Insere(new CPIGForm(resp,x,y,altura,largura,janela));
    }

    static void DestroiForm(int idForm){
        forms->Remove(idForm);
    }

};
CPIGRepositorio<PIGForm> *CPIGGerenciadorForms::forms;
#endif // _CPIGGERENCIADORFORM_
