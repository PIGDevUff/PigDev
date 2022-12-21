#ifndef _CPIGGERENCIADORSOCKETSUDP_
#define _CPIGGERENCIADORSOCKETSUDP_

#include "SDL_net.h"

#include "CPIGSocketUDP.h"
#include "CPIGRepositorio.h"

class CPIGGerenciadorSocketsUDP: public CPIGRepositorio<PIGSocketUDP>{

public:

    CPIGGerenciadorSocketsUDP():CPIGRepositorio<PIGSocketUDP>(PIG_MAX_SOCKETS_UDP,"CPIGSocketUDP"){
        SDLNet_Init();
    }

    ~CPIGGerenciadorSocketsUDP(){
        SDLNet_Quit();
    }

    inline int CriaSocketUDP(int porta){
        int resp = ProxID();
        PIGSocketUDP socketUDP = new CPIGSocketUDP(resp,porta);
        if (socketUDP->GetAtivo()){
            Insere(socketUDP);
            return resp;
        }else{
            printf("ERRO: detectei o erro socketUDP id %d\n",resp);
            delete socketUDP;
            return -1;
        }
    }

};
CPIGGerenciadorSocketsUDP pigGerSocketsUDP;
#endif // _CPIGGERENCIADORSOCKETSUDP_
