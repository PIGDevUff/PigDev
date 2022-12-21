#ifndef _CPIGGERENCIADORCONTROLES_
#define _CPIGGERENCIADORCONTROLES_

#include "CPIGControle.h"
#include "CPIGRepositorio.h"

class CPIGGerenciadorControles: public CPIGRepositorio<PIGControle>{

public:

    CPIGGerenciadorControles():CPIGRepositorio<PIGControle>(PIG_MAX_CONTROLES,"CPIGControle"){
        SDL_InitSubSystem(SDL_INIT_JOYSTICK);

        for(int i = 0; i < SDL_NumJoysticks(); ++i) {
            Insere(new CPIGControle(i));
        }
    }
};
CPIGGerenciadorControles pigGerControles;
#endif // _CPIGGERENCIADORCONTROLES_
