#ifndef _CPIGGERENCIADORLABELS_
#define _CPIGGERENCIADORLABELS_

#include "CPIGLabel.h"
#include "CPIGRepositorio.h"

class CPIGGerenciadorLabels:public CPIGRepositorio<PIGLabel>{

public:

    CPIGGerenciadorLabels():CPIGRepositorio(PIG_MAX_LABELS,"CPIGLabel"){}

    inline int CriaLabel(string texto, PIGCor cor, int idFonte, int idJanela=0){
        return Insere(new CPIGLabel(texto,cor,idFonte,idJanela));
    }

};
CPIGGerenciadorLabels pigGerLabels;
#endif //_CPIGGERENCIADORLABELS_
