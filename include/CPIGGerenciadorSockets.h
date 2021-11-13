#ifndef _CPIGGERENCIADORSOCLETS_
#define _CPIGGERENCIADORSOCKETS_

#include "CPIGClienteTCP.h"
#include "CPIGServidorTCP.h"
#include "CPIGSocketUDP.h"

class CPIGGerenciadorSockets{

private:

static CPIGRepositorio<PIGClienteTCP> *clientes;
static CPIGRepositorio<PIGServidorTCP> *servidores;
static CPIGRepositorio<PIGSocketUDP> *socketsUDP;

public:

static void Inicia(){
    clientes = new CPIGRepositorio<PIGClienteTCP>(PIG_MAX_SOCKETS_CLIENTES_TCP,"clientesTCP");
    servidores = new CPIGRepositorio<PIGServidorTCP>(PIG_MAX_SOCKETS_SERVIDORES_TCP,"servidoresTCP");
    socketsUDP = new CPIGRepositorio<PIGSocketUDP>(PIG_MAX_SOCKETS_UDP,"socketsUDP");
}

static void Encerra(){
    delete clientes;
    delete servidores;
    delete socketsUDP;
}

static int CriaCliente(string hostname, int porta, int maxBytesPacote=PIG_MAX_MENSAGEM_REDE_TCP){
    int resp = clientes->ProxID();
    PIGClienteTCP cliente = new CPIGClienteTCP(resp,hostname,porta,maxBytesPacote);
    if (cliente->GetAtivo()){
        clientes->Insere(cliente);
        return resp;
    }else{
        printf("detectei o erro clienteTCP id %d\n",resp);
        delete cliente;
        return -1;
    }
}

static int CriaServidor(int maxClientes, int porta, int maxBytesPacote=PIG_MAX_MENSAGEM_REDE_TCP){
    int resp = servidores->ProxID();
    PIGServidorTCP servidor = new CPIGServidorTCP(resp,maxClientes,porta,maxBytesPacote);
    if (servidor->GetAtivo()){
        servidores->Insere(servidor);
        return resp;
    }else{
        printf("detectei o erro servidorTCP id %d\n",resp);
        delete servidor;
        return -1;
    }
}

static int CriaSocketUDP(int porta){
    int resp = servidores->ProxID();
    PIGSocketUDP socketUDP = new CPIGSocketUDP(resp,porta);
    if (socketUDP->GetAtivo()){
        socketsUDP->Insere(socketUDP);
        return resp;
    }else{
        printf("detectei o erro socketUDP id %d\n",resp);
        delete socketUDP;
        return -1;
    }
}

static void DestroiCliente(int idSocket){
    clientes->Remove(idSocket);
}

static void DestroiServidor(int idSocket){
    servidores->Remove(idSocket);
}

static void DestroiSocketUDP(int idSocket){
    socketsUDP->Remove(idSocket);
}

inline static PIGClienteTCP GetCliente(int idSocket){
    return clientes->GetElemento(idSocket);
}

inline static PIGServidorTCP GetServidor(int idSocket){
    return servidores->GetElemento(idSocket);
}

inline static PIGSocketUDP GetSocketUDP(int idSocket){
    return socketsUDP->GetElemento(idSocket);
}

};

CPIGRepositorio<PIGClienteTCP> *CPIGGerenciadorSockets::clientes;
CPIGRepositorio<PIGServidorTCP> *CPIGGerenciadorSockets::servidores;
CPIGRepositorio<PIGSocketUDP> *CPIGGerenciadorSockets::socketsUDP;
#endif // _CPIGGERENCIADORSOCKETS_
