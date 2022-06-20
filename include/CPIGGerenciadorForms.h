#ifndef _CPIGGERENCIADORFORMS_
#define _CPIGGERENCIADORFORMS_

#include "CPIGForm.h"

class CPIGGerenciadorForms{

private:

    static CPIGRepositorio<PIGForm> *forms;

public:

    inline static void Inicia(){
        forms = new CPIGRepositorio<PIGForm>(PIG_MAX_FORMS,"forms");
    }

    inline static void Encerra(){
        delete forms;
    }

    inline static PIGForm GetForm(int idForm){
        return forms->GetElemento(idForm);
    }

    inline static PIGForm GetFormComponente(int idComponente){
        return GetForm(idComponente / PIG_MAX_COMPONENTES);
    }

    template <class T>
    inline static T GetComponente(int idComponente){
        PIGForm f = GetFormComponente(idComponente);
        return f->GetComponente<T>(idComponente);
    }

    inline static int CriaForm(int altura, int largura, int janela = 0){
        int resp = forms->ProxID();
        return forms->Insere(new CPIGForm(resp,altura,largura,janela));
    }

    inline static int InsereForm(PIGForm form){
        return forms->Insere(form);
    }

    inline static int CriaForm(int altura, int largura, string nomeArq, int retiraFundo=1, int janela = 0){
        int resp = forms->ProxID();
        return forms->Insere(new CPIGForm(resp,altura,largura,nomeArq,retiraFundo,janela));
    }

    inline static int CriaForm(string nomeArqTexto){
        int resp = forms->ProxID();
        return forms->Insere(new CPIGForm(resp,nomeArqTexto));
    }

    inline static void DestroiForm(int idForm){
        forms->Remove(idForm);
    }

};
CPIGRepositorio<PIGForm> *CPIGGerenciadorForms::forms;
#endif // _CPIGGERENCIADORFORMS_
