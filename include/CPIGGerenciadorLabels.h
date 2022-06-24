#ifndef _CPIGGERENCIADORLABELS_
#define _CPIGGERENCIADORLABELS_

#include "CPIGLabel.h"

class CPIGGerenciadorLabels{

private:

    static CPIGRepositorio<PIGLabel> *labels;

public:

    inline static PIGLabel GetLabel(int idLabel){
        return labels->GetElemento(idLabel);
    }

    inline static void Inicia(){
        labels = new CPIGRepositorio<PIGLabel>(PIG_MAX_LABELS,"labels");
    }

    inline static void Encerra(){
        delete labels;
    }

    inline static int CriaLabel(string texto, PIGCor cor, int numFonte, int idJanela=0){
        return labels->Insere(new CPIGLabel(texto,cor,numFonte,idJanela));
    }

    inline static int InsereLabel(PIGLabel label){
        return labels->Insere(label);
    }

    inline static void DestroiLabel(int idLabel){
        labels->Remove(idLabel);
    }
};

CPIGRepositorio<PIGLabel> *CPIGGerenciadorLabels::labels;
#endif //_CPIGGERENCIADORLABELS_
