#ifndef _CPIGClienteTCP_
#define _CPIGClienteTCP_

#include "CPIGSocketTCP.h"

class CPIGClienteTCP:public CPIGSocketTCP{

private:

SDL_Thread *thread;

void CriaEventoMensagem(PIGTipoMensagemRede tipoMensagem, const void *buffer, int tamanhoDados){
    PIGInfoEventoRede *infoRede = (PIGInfoEventoRede*) malloc(sizeof(PIGInfoEventoRede));
    infoRede->tipoMensagem = tipoMensagem;
    infoRede->idSocket = id;
    infoRede->idSecundario = -1;
    memcpy(infoRede->mensagem,buffer,tamanhoDados);
    strcpy(infoRede->host,GetHostRemoto().c_str());
    infoRede->porta = GetPortaRemota();
    SDL_Event event;
    event.type = SDL_USEREVENT;
    event.user.code = PIG_EVENTO_REDE;
    event.user.data1 = infoRede;
    SDL_PushEvent(&event);
}

public:

CPIGClienteTCP(int idSocket, string host, int porta, int maxBytesPacote):CPIGSocketTCP(idSocket,host,porta,maxBytesPacote){
    if (!ativo){
        printf("Erro: Cliente TCP nao esta ativo\n");
        return;
    }

    socketSet = SDLNet_AllocSocketSet(1);
    if(socketSet) {
        SDLNet_TCP_AddSocket(socketSet,socket);
        thread = SDL_CreateThread(thread_code,"",this);
    }else{
        ativo = false;
        printf("Erro de alocacao de SocketSet (cliente): %s\n", SDLNet_GetError());
    }
}

virtual ~CPIGClienteTCP(){
    ativo = false;
    SDL_Delay(20);//esperar a thread encerrar
}

static int thread_code(void *data){
    CPIGClienteTCP *cliente = (CPIGClienteTCP*)data;
    if (cliente==NULL){
        printf("Thread receive sem acesso aos dados do objeto cliente!!!\n");
        return -1;
    }
    while (cliente->ativo){
        int pronto = SDLNet_CheckSockets(cliente->socketSet,PIG_DELAY_CHECK_TCP_CLIENTE);
        if (pronto){
            //printf("Chegou mensagem para o cliente\n");
            uint8_t buffer[PIG_MAX_MENSAGEM_REDE_TCP];
            int bytes = cliente->RecebeDados(buffer);
            if (bytes>0){
                cliente->CriaEventoMensagem(PIG_REDE_MENSAGEM_TCP,buffer,bytes);
            }else{//não tem atividade
                cliente->CriaEventoMensagem(PIG_REDE_DESCONEXAO,"",1);
                cliente->ativo = false;
                break;
            }
        }
    }

    return 0;
}

};

typedef CPIGClienteTCP *PIGClienteTCP;
#endif // _CPIGClienteTCP_
