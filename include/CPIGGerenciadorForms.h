#ifndef _CPIGGERENCIADORFORMS_
#define _CPIGGERENCIADORFORMS_

#include "CPIGForm.h"
#include "CPIGRepositorio.h"

class CPIGGerenciadorForms: public CPIGRepositorio<PIGForm>{

public:

    CPIGGerenciadorForms():CPIGRepositorio<PIGForm>(PIG_MAX_FORMS,"CPIGForm"){}

    inline PIGForm GetFormComponente(int idComponente){
        return GetElemento(idComponente / PIG_MAX_COMPONENTES);
    }

    template <class T>
    inline T GetComponente(int idComponente){
        PIGForm f = GetFormComponente(idComponente);
        return f->GetComponente<T>(idComponente);
    }

    inline int CriaForm(int altura, int largura, int janela = 0){
        return Insere(new CPIGForm(ProxID(),altura,largura,janela));
    }

    inline int CriaForm(int altura, int largura, string nomeArq, int retiraFundo=1, int janela = 0){
        return Insere(new CPIGForm(ProxID(),altura,largura,nomeArq,retiraFundo,janela));
    }

    inline int CriaForm(string nomeArqTexto){
        return Insere(new CPIGForm(ProxID(),nomeArqTexto));
    }
};
CPIGGerenciadorForms pigGerForms;
#endif // _CPIGGERENCIADORFORMS_
