class CClienteTCP:public CSocketTCP{

private:

SDL_Thread *thread;

void CriaEventoMensagem(PIG_TipoMensagemRede tipoMensagem, const void *buffer, int tamanhoDados){
    InfoEventoRede *infoRede = (InfoEventoRede*) malloc(sizeof(InfoEventoRede));
    infoRede->tipoMensagem = tipoMensagem;
    infoRede->idSocket = id;
    infoRede->idSecundario = -1;
    memcpy(infoRede->mensagem,buffer,tamanhoDados);
    strcpy(infoRede->host,GetHostRemoto().c_str());
    infoRede->porta = GetPortaRemota();
    SDL_Event event;
    event.type = SDL_USEREVENT;
    event.user.code = EVENTO_REDE;
    event.user.data1 = infoRede;
    SDL_PushEvent(&event);
}

public:

CClienteTCP(int idSocket,std::string host, int porta, int maxBytesPacote):CSocketTCP(idSocket,host,porta,maxBytesPacote){
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

~CClienteTCP(){
    ativo = false;
    SDL_Delay(20);//esperar a thread encerrar
}

static int thread_code(void *data){
    CClienteTCP *cliente = (CClienteTCP*)data;
    if (cliente==NULL){
        printf("Thread receive sem acesso aos dados do objeto cliente!!!\n");
        return -1;
    }
    while (cliente->ativo){
        int pronto = SDLNet_CheckSockets(cliente->socketSet,DELAY_CHECK_TCP_CLIENTE);
        if (pronto){
            //printf("Chegou mensagem para o cliente\n");
            uint8_t buffer[MAX_MENSAGEM_REDE_TCP];
            int bytes = cliente->RecebeDados(buffer);
            if (bytes>0){
                cliente->CriaEventoMensagem(REDE_MENSAGEM_TCP,buffer,bytes);
            }else{//não tem atividade
                cliente->CriaEventoMensagem(REDE_DESCONEXAO,"",1);
                cliente->ativo = false;
                break;
            }
        }
    }

    return 0;
}

};

typedef CClienteTCP *ClienteTCP;




