#ifndef _CPIGSERVIDORTCP_
#define _CPIGSERVIDORTCP_

#include "CPIGSocketTCP.h"

class CPIGServidorTCP:public CPIGSocketTCP{

private:

SDLNet_SocketSet clienteSet;
int maxConexoes;
bool ativo;
//int qtdConexoes;
//PIGSocketTCP *clientesTCP;
int portaLocal;
SDL_Thread *threadAccept,*threadReceive;
//PIGPoolNumeros pool;

std::vector<int> posLivres;
std::unordered_map<int,PIGSocketTCP> clientesTCP;
std::unordered_map<int,PIGSocketTCP>::iterator it;

void CriaEventoMensagem(PIG_TipoMensagemRede tipoMensagem, const void *buffer, int tamanhoDados, int indiceSlot){
    InfoEventoRede *infoRede = (InfoEventoRede*) malloc(sizeof(InfoEventoRede));
    infoRede->tipoMensagem = tipoMensagem;
    infoRede->idSocket = id;
    infoRede->idSecundario = indiceSlot;
    memcpy(infoRede->mensagem,buffer,tamanhoDados);
    strcpy(infoRede->host,clientesTCP[indiceSlot]->GetHostRemoto().c_str());
    infoRede->porta = clientesTCP[indiceSlot]->GetPortaRemota();
    SDL_Event event;
    event.type = SDL_USEREVENT;
    event.user.code = EVENTO_REDE;
    event.user.data1 = infoRede;
    SDL_PushEvent(&event);
}

void RegistraBytesRecebidos(int qtdBytes){
    if (!ativo) return;
    tempoPacoteRecebido = clock();
    qtdPacotesRecebidos++;
    qtdBytesRecebidos += qtdBytes;
}

void RegistraBytesEnviados(int qtdBytes){
    if (!ativo) return;
    tempoPacoteEnviado = clock();
    qtdPacotesEnviados++;
    qtdBytesEnviados += qtdBytes;
}

void InicializaValoresBasicos(int valorId,int maxBytesPacote){
    qtdPacotesRecebidos = 0;
    qtdBytesRecebidos = 0;
    qtdPacotesEnviados = 0;
    qtdBytesEnviados = 0;
    tempoPacoteRecebido = -1;
    tempoPacoteEnviado = -1;
    tamPacote = maxBytesPacote;
    socketSet = NULL;
    id = valorId;
}

PIGSocketTCP GetCliente(int indice){
    it = clientesTCP.find(indice);
    if (it==clientesTCP.end()) throw CPIGErroIndice(indice,"ClienteTCPdoServidor");
    return it->second;
}

int AbreConexao(){
    /*int num = RetiraLivre();
    clientesTCP[num] = new CPIGSocketTCP(-num,socket,tamPacote,clienteSet);//-num apenas para indicar que se trata de um socket criado pelo servidor
    CriaEventoMensagem(REDE_CONEXAO,"",1,num);
    qtdConexoes++;*/
    int resp = posLivres[0];
    posLivres.erase(posLivres.begin());
    clientesTCP[resp] = new CPIGSocketTCP(-resp,socket,tamPacote,clienteSet);//-num apenas para indicar que se trata de um socket criado pelo servidor
    return resp;
}

void FechaConexao(int indice){
    CriaEventoMensagem(REDE_DESCONEXAO,"",1,indice);
    /*delete clientesTCP[indice];
    clientesTCP[indice] = NULL;
    DevolveUsado(indice);
    qtdConexoes--;*/
    PIGSocketTCP cliente = GetCliente(indice);
    delete cliente;
    clientesTCP.erase(indice);
}

public:

CPIGServidorTCP(int idSocket, int maximoConexoes, int porta, int maxBytesPacote):CPIGSocketTCP(idSocket,"",porta,maxBytesPacote){
    if (!ativo){
        printf("Erro: Servidor TCP nao esta ativo\n");
        return;
    }

    ativo = true;
    IPaddress ip;


    //qtdConexoes = 0;
    //pool = new CPIGPoolNumeros(maxConexoes);

    portaLocal = porta;

    //SDLNet_ResolveHost(&ip,getenv("COMPUTERNAME"),portaLocal);
    //Uint8 *part = (Uint8*)&(ip.host);
    //sprintf(hostLocal,"%d.%d.%d.%d",(int)part[0],(int)part[1],(int)part[2],(int)part[3]);

    SDLNet_ResolveHost(&ip,NULL,portaLocal);

    /*clientesTCP = (PIGSocketTCP*) malloc(maxConexoes*sizeof(PIGSocketTCP));
    for (int i=0;i<maxConexoes;i++)
        clientesTCP[i] = NULL;
*/
    maxConexoes = maximoConexoes;
    for (int i=0;i<maxConexoes;i++)
        posLivres.push_back(i);

    clienteSet = SDLNet_AllocSocketSet(maxConexoes);
    socketSet = SDLNet_AllocSocketSet(1);

    if(socketSet&&clienteSet) {
        SDLNet_TCP_AddSocket(socketSet,socket);
        threadAccept = SDL_CreateThread(accept_code,"",this);
        threadReceive = SDL_CreateThread(receive_code,"",this);
    }else{
        printf("Erro de alocacao de SocketSet (servidor): %s\n", SDLNet_GetError());
        ativo = false;
    }
}

~CPIGServidorTCP(){
    //qtdConexoes=-1;//marca que as threads devem encerrar
    ativo = false;
    SDL_Delay(20);//espera pelo encerramento das threads

    /*for (int i=0;i<maxConexoes;i++){
        if (clientesTCP[i])
            delete clientesTCP[i];
    }*/
    //delete pool;
    for(it = clientesTCP.begin(); it != clientesTCP.end(); ++it) {
        delete it->second;
    }

    if (clienteSet)
        SDLNet_FreeSocketSet(clienteSet);


}

int GetPortaLocal(){
    return portaLocal;
}

int GetMaximoConexoes(){
    return maxConexoes;
}

int GetQuantidadeConexoes(){
    return clientesTCP.size();
}

int EnviaDados(const void *buffer,int tamanhoBuffer,int indiceSlot){
    //if (!clientesTCP) return -1;
    //if (!clientesTCP[indiceSlot]) return -2;
    it = clientesTCP.find(indiceSlot);
    if (it==clientesTCP.end()) return -2;//throw CPIGErroIndice(indiceSlot,"socketServidor");
    return it->second->EnviaDados(buffer,tamanhoBuffer);
    //return clientesTCP[indiceSlot]->EnviaDados(buffer,tamanhoBuffer);
}



static int accept_code(void *data){
    CPIGServidorTCP *servidor = (CPIGServidorTCP*)data;
    if (servidor==NULL){
        printf("Thread accept sem acesso aos dados do objeto servidor!!!\n");
        return -1;
    }
    //printf("Vou comecar ciclo de accept\n");
    //while (servidor->qtdConexoes>=0){//sinalização de encerramento da thread
    while (servidor->ativo){//sinalização de encerramento da thread
        //printf("Checando...\n");
        int pronto = SDLNet_CheckSockets(servidor->socketSet,1);
        if (pronto>0){
            //printf("Chegou novo cidadao\n");
            if (servidor->clientesTCP.size()==servidor->maxConexoes){
                PIGSocketTCP clienteTemp = new CPIGSocketTCP(-99999,servidor->socket,servidor->tamPacote,servidor->clienteSet);
                //clienteTemp->EnviaMensagem("Servidor cheio! Desconectado!!!\n");
                delete clienteTemp;
            }else{
                /*int num = servidor->pool->RetiraLivre();
                servidor->clientesTCP[num] = new CPIGSocketTCP(-num,servidor->socket,servidor->tamPacote,servidor->clienteSet);//-num apenas para indicar que se trata de um socket criado pelo servidor
                servidor->CriaEventoMensagem(REDE_CONEXAO,"",1,num);
                servidor->qtdConexoes++;*/
                servidor->AbreConexao();
            }
        }
    }
    return 0;
}

static int receive_code(void *data){
    CPIGServidorTCP *servidor = (CPIGServidorTCP*)data;
    if (servidor==NULL){
        printf("Thread receive sem acesso aos dados do objeto servidor!!!\n");
        return -1;
    }

    //while (servidor->qtdConexoes>=0){//sinalização de encerramento da thread
    while (servidor->ativo){//sinalização de encerramento da thread
        int prontos = SDLNet_CheckSockets(servidor->clienteSet,DELAY_CHECK_TCP_SERVIDOR);
        int indice=0;
        while (prontos>0&&indice<servidor->maxConexoes){
            uint8_t buffer[MAX_MENSAGEM_REDE_TCP];
            if (servidor->clientesTCP[indice]){
                int bytes = servidor->clientesTCP[indice]->RecebeDados(buffer);
                //printf("Bytes %d do cliente %d\n",bytes,indice);
                if (bytes<=0){//nao tem atividade
                    /*servidor->CriaEventoMensagem(REDE_DESCONEXAO,"",1,indice);
                    delete servidor->clientesTCP[indice];
                    servidor->clientesTCP[indice] = NULL;
                    servidor->pool->DevolveUsado(indice);
                    servidor->qtdConexoes--;*/
                    servidor->FechaConexao(indice);
                    prontos--;
                }else if (bytes>0){
                    servidor->CriaEventoMensagem(REDE_MENSAGEM_TCP,buffer,bytes,indice);
                    prontos--;
                }
            }
            indice++;
        }
    }
    return 0;
}

};

typedef CPIGServidorTCP *PIGServidorTCP;
#endif // _CPIGSERVIDORTCP_
