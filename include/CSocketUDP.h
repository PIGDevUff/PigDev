class CSocketUDP{

private:

int portaLocal;
char hostLocal[TAMANHO_MAXIMO_HOSTNAME];
int id;
int ativo;
long tempoPacoteRecebido;
long qtdPacotesRecebidos;
long qtdBytesRecebidos;
long tempoPacoteEnviado;
long qtdPacotesEnviados;
long qtdBytesEnviados;
UDPsocket socket;
UDPpacket *pacoteEnvio, *pacoteRecebimento;
SDL_Thread *thread;

void CriaEventoMensagem(PIG_TipoMensagemRede tipoMensagem, UDPpacket *pacoteRecebido){
    InfoEventoRede *infoRede = (InfoEventoRede*) malloc(sizeof(InfoEventoRede));
    infoRede->tipoMensagem = tipoMensagem;
    infoRede->idSocket = id;
    infoRede->idSecundario = -1;
    memcpy(infoRede->mensagem,pacoteRecebido->data,pacoteRecebido->len);
    strcpy(infoRede->host,SDLNet_ResolveIP(&(pacoteRecebido->address)));
    infoRede->porta = PIGTroca2Bytes(pacoteRecebido->address.port);
    SDL_Event event;
    event.type = SDL_USEREVENT;
    event.user.code = EVENTO_REDE;
    event.user.data1 = infoRede;
    SDL_PushEvent(&event);
    tempoPacoteRecebido = clock();
    qtdPacotesRecebidos++;
    qtdBytesRecebidos += pacoteRecebido->len;
}

public:

CSocketUDP(int idSocket,int porta){
    id = idSocket;
    portaLocal = porta;
    thread = NULL;
    pacoteEnvio = pacoteRecebimento = NULL;

    tempoPacoteRecebido = -1;
    qtdPacotesRecebidos = 0;
    qtdBytesRecebidos = 0;
    tempoPacoteEnviado = -1;
    qtdPacotesEnviados = 0;
    qtdBytesEnviados = 0;

    IPaddress ipAux;
    SDLNet_ResolveHost(&ipAux,getenv("COMPUTERNAME"),portaLocal);
    Uint8 *part = (Uint8*)&(ipAux.host);
    sprintf(hostLocal,"%d.%d.%d.%d",(int)part[0],(int)part[1],(int)part[2],(int)part[3]);

    socket = SDLNet_UDP_Open(portaLocal);
    ativo = socket!=NULL;
    if (!ativo){
        printf("Erro na criacao do socket UDP: %s\n",SDLNet_GetError());
        return;
    }

    pacoteEnvio = SDLNet_AllocPacket(TAMANHO_PACOTE_UDP);
    pacoteRecebimento = SDLNet_AllocPacket(TAMANHO_PACOTE_UDP);
    ativo = pacoteEnvio!=NULL && pacoteRecebimento!=NULL;
    if (!ativo){
        printf("Erro na criacao de pacotes UDP: %s\n",SDLNet_GetError());
    }else thread = SDL_CreateThread(thread_code,"",this);
}

~CSocketUDP(){
    if (thread)
        SDL_DetachThread(thread);
    if (pacoteEnvio)
        free(pacoteEnvio);
    if (pacoteRecebimento)
        free(pacoteRecebimento);
}

bool EnviaDados(const void *buffer, int tamanhoBuffer, std::string host, int porta){
    if (!ativo) return false;
    if (tamanhoBuffer>TAMANHO_PACOTE_UDP) return false;

    IPaddress ipRemoto;
    //printf("Vou dar send para %s na porta %u\n",host,porta);
    if ( SDLNet_ResolveHost(&ipRemoto, host.c_str(), porta) == -1 ){
        printf("Erro de resolucao de host UDP: %s\n",SDLNet_GetError());
        return false;
    }

    pacoteEnvio->address.host = ipRemoto.host;
    pacoteEnvio->address.port = ipRemoto.port;

    memcpy(pacoteEnvio->data, buffer,tamanhoBuffer);
    pacoteEnvio->len = tamanhoBuffer;

    if (SDLNet_UDP_Send(socket, -1, pacoteEnvio) == 0){
        printf("Erro no envio do pacote UDP: %s\n",SDLNet_GetError());
        return false;
    }

    tempoPacoteEnviado = clock();
    qtdPacotesEnviados++;
    qtdBytesEnviados += pacoteEnvio->len;

    return true;
}

int GetId(){
    return id;
}

bool GetAtivo(){
    return ativo;
}

int GetPortaLocal(){
    return portaLocal;
}

std::string GetHostLocal(){
    return hostLocal;
}

long GetBytesEnviados(){
    return qtdBytesEnviados;
}

long GetBytesRecebidos(){
    return qtdBytesRecebidos;
}

long GetPacotesEnviados(){
    return qtdPacotesEnviados;
}

long GetPacotesRecebidos(){
    return qtdPacotesRecebidos;
}

long GetTempoUltimoRecebido(){
    return tempoPacoteRecebido;
}

long GetTempoUltimoEnviado(){
    return tempoPacoteEnviado;
}

static int thread_code(void *data){
    CSocketUDP *socketUDP = (CSocketUDP*) data;
    while (true){
        if (SDLNet_UDP_Recv(socketUDP->socket, socketUDP->pacoteRecebimento)){
            socketUDP->CriaEventoMensagem(REDE_MENSAGEM_UDP,socketUDP->pacoteRecebimento);
        }
        SDL_Delay(DELAY_CHECK_UDP);
    }
}

};

typedef CSocketUDP *SocketUDP;
