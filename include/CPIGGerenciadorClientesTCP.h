#ifndef _CPIGGERENCIADORCLIENTESTCP_
#define _CPIGGERENCIADORCLIENTESTCP_

#include "SDL_net.h"

#include "CPIGClienteTCP.h"
#include "CPIGRepositorio.h"

class CPIGGerenciadorClientesTCP: public CPIGRepositorio<PIGClienteTCP>{

public:

    CPIGGerenciadorClientesTCP():CPIGRepositorio<PIGClienteTCP>(PIG_MAX_SOCKETS_CLIENTES_TCP,"CPIGClienteTCP"){
        SDLNet_Init();
    }

    ~CPIGGerenciadorClientesTCP(){
        SDLNet_Quit();
    }

    inline int CriaCliente(string hostname, int porta, int maxBytesPacote=PIG_MAX_MENSAGEM_REDE_TCP){
        int resp = ProxID();
        PIGClienteTCP cliente = new CPIGClienteTCP(resp,hostname,porta,maxBytesPacote);
        if (cliente->GetAtivo()){
            Insere(cliente);
            return resp;
        }else{
            printf("ERRO: detectei o erro clienteTCP id %d\n",resp);
            delete cliente;
            return -1;
        }
    }
};
CPIGGerenciadorClientesTCP pigGerClientesTCP;
#endif // _CPIGGERENCIADORCLIENTESTCP_
