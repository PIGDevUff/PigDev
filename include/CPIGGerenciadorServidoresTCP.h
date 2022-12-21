#ifndef _CPIGGERENCIADORSERVIDORESTCP_
#define _CPIGGERENCIADORSERVIDORESTCP_

#include "SDL_net.h"

#include "CPIGServidorTCP.h"
#include "CPIGRepositorio.h"

class CPIGGerenciadorServidoresTCP: public CPIGRepositorio<PIGServidorTCP>{

public:

    CPIGGerenciadorServidoresTCP():CPIGRepositorio<PIGServidorTCP>(PIG_MAX_SOCKETS_SERVIDORES_TCP,"CPIGServidorTCP"){
        SDLNet_Init();
    }

    ~CPIGGerenciadorServidoresTCP(){
        SDLNet_Quit();
    }

    inline int CriaServidor(int maxClientes, int porta, int maxBytesPacote=PIG_MAX_MENSAGEM_REDE_TCP){
        int resp = ProxID();
        PIGServidorTCP servidor = new CPIGServidorTCP(resp,maxClientes,porta,maxBytesPacote);
        if (servidor->GetAtivo()){
            Insere(servidor);
            return resp;
        }else{
            printf("ERRO: detectei o erro servidorTCP id %d\n",resp);
            delete servidor;
            return -1;
        }
    }
};
CPIGGerenciadorServidoresTCP pigGerServidoresTCP;
#endif // _CPIGGERENCIADORSERVIDORESTCP_
