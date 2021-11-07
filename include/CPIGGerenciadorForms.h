#ifndef _CPIGGerenciadorForms_
#define _CPIGGerenciadorForms_

#include "CPIGForm.h"

class CPIGGerenciadorForms{

private:

    static CPIGRepositorio<PIGForm> *forms;

public:

    static void Inicia(){
        forms = new CPIGRepositorio<PIGForm>(PIG_MAX_FORMS,"forms");
    }

    static void Encerra(){
        delete forms;
    }

    static PIGForm GetForm(int idForm){
        return forms->GetElemento(idForm);
    }

    static PIGForm GetFormComponente(int idComponente){
        return GetForm(idComponente / PIG_MAX_COMPONENTES);
    }
    template <class T>
    static T GetComponente(int idComponente){
        PIGForm f = GetFormComponente(idComponente);
        return f->GetComponente<T>(idComponente);
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
