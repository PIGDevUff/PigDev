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
    clientes = new CPIGRepositorio<PIGClienteTCP>(MAX_SOCKETS_CLIENTES_TCP,"clientesTCP");
    servidores = new CPIGRepositorio<PIGServidorTCP>(MAX_SOCKETS_SERVIDORES_TCP,"servidoresTCP");
    socketsUDP = new CPIGRepositorio<PIGSocketUDP>(MAX_SOCKETS_UDP,"socketsUDP");
}

static void Encerra(){
    delete clientes;
    delete servidores;
    delete socketsUDP;
}

static int CriaCliente(std::string hostname, int porta, int maxBytesPacote=MAX_MENSAGEM_REDE_TCP){
    /*int resp = numClientes->RetiraLivre();
    clientes[resp] = new CPIGClienteTCP(resp,hostname,porta,maxBytesPacote);
    totalClientes++;
    return resp;*/
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
    /*int resp = posLivresClientes[0];
    posLivresClientes.erase(posLivresClientes.begin());
    clientes[resp] = new CPIGClienteTCP(resp,hostname,porta,maxBytesPacote);
    if (clientes[resp]->GetAtivo())
        return resp;
    else{

        DestroiCliente(resp);
        return -1;
    }*/
}

static int CriaServidor(int maxClientes, int porta, int maxBytesPacote=MAX_MENSAGEM_REDE_TCP){
    /*int resp = numServidores->RetiraLivre();
    servidores[resp] = new CPIGServidorTCP(resp,maxClientes,porta,maxBytesPacote);
    totalServidores++;
    return resp;*/
    /*int resp = posLivresServidores[0];
    posLivresServidores.erase(posLivresServidores.begin());
    servidores[resp] = new CPIGServidorTCP(resp,maxClientes,porta,maxBytesPacote);
    return resp;*/

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
    /*int resp = numSocketsUDP->RetiraLivre();
    socketsUDP[resp] = new CPIGSocketUDP(resp,porta);
    totalSocketsUDP++;
    return resp;*/
    /*int resp = posLivresUDP[0];
    posLivresUDP.erase(posLivresUDP.begin());
    socketsUDP[resp] = new CPIGSocketUDP(resp,porta);
    return resp;*/
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
    /*numClientes->DevolveUsado(idSocket);
    delete clientes[idSocket];
    totalClientes--;
    clientes[idSocket] = NULL;*/
    //posLivresClientes.push_b()
    /*PIGClienteTCP socket = GetCliente(idSocket);
    delete socket;
    clientes.erase(idSocket);*/
    clientes->Remove(idSocket);
}

static void DestroiServidor(int idSocket){
    /*numServidores->DevolveUsado(idSocket);
    delete servidores[idSocket];
    totalServidores--;
    servidores[idSocket] = NULL;*/
    //PIGServidorTCP socket = GetServidor(idSocket);
    //delete socket;
    //servidores.erase(idSocket);
    servidores->Remove(idSocket);
}

static void DestroiSocketUDP(int idSocket){
    /*numSocketsUDP->DevolveUsado(idSocket);
    delete socketsUDP[idSocket];
    totalSocketsUDP--;
    socketsUDP[idSocket] = NULL;*/
    //PIGSocketUDP socket = GetSocketUDP(idSocket);
    //delete socket;
    //socketsUDP.erase(idSocket);
    socketsUDP->Remove(idSocket);
}

inline static PIGClienteTCP GetCliente(int idSocket){
    /*if (idAudio<0||idAudio>=MAX_AUDIOS||audios[idAudio]==NULL) throw CPIGErroIndice(idAudio,"audios");
    return audios[idAudio];*/
    /*itCliente = clientes.find(idSocket);
    if (itCliente==clientes.end()) throw CPIGErroIndice(idSocket,"clientesTCP");
    return itCliente->second;*/
    return clientes->GetElemento(idSocket);
}

inline static PIGServidorTCP GetServidor(int idSocket){
    /*if (idAudio<0||idAudio>=MAX_AUDIOS||audios[idAudio]==NULL) throw CPIGErroIndice(idAudio,"audios");
    return audios[idAudio];*/
    /*itServidor = servidores.find(idSocket);
    if (itServidor==servidores.end()) throw CPIGErroIndice(idSocket,"servidoresTCP");
    return itServidor->second;*/
    return servidores->GetElemento(idSocket);
}


inline static PIGSocketUDP GetSocketUDP(int idSocket){
    /*if (idAudio<0||idAudio>=MAX_AUDIOS||audios[idAudio]==NULL) throw CPIGErroIndice(idAudio,"audios");
    return audios[idAudio];*/
    /*itUDP = socketsUDP.find(idSocket);
    if (itUDP==socketsUDP.end()) throw CPIGErroIndice(idSocket,"socketUDP");
    return itUDP->second;*/
    return socketsUDP->GetElemento(idSocket);
}

};

CPIGRepositorio<PIGClienteTCP> *CPIGGerenciadorSockets::clientes;
CPIGRepositorio<PIGServidorTCP> *CPIGGerenciadorSockets::servidores;
CPIGRepositorio<PIGSocketUDP> *CPIGGerenciadorSockets::socketsUDP;
#endif // _CPIGGERENCIADORSOCKETS_
