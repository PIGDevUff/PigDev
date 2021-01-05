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

/*static std::vector<int> posLivresClientes;
static std::unordered_map<int,PIGClienteTCP> clientes;
static std::unordered_map<int,PIGClienteTCP>::iterator itCliente;

static std::vector<int> posLivresServidores;
static std::unordered_map<int,PIGServidorTCP> servidores;
static std::unordered_map<int,PIGServidorTCP>::iterator itServidor;

static std::vector<int> posLivresUDP;
static std::unordered_map<int,PIGSocketUDP> socketsUDP;
static std::unordered_map<int,PIGSocketUDP>::iterator itUDP;

/*static int totalClientes;
static PIGPoolNumeros numClientes;
static PIGClienteTCP clientes[MAX_SOCKETS_CLIENTES_TCP];
static int totalServidores;
static PIGPoolNumeros numServidores;
static PIGServidorTCP servidores[MAX_SOCKETS_SERVIDORES_TCP];
static int totalSocketsUDP;
static PIGPoolNumeros numSocketsUDP;
static PIGSocketUDP socketsUDP[MAX_SOCKETS_UDP];
*/
public:

static void Inicia(){
    /*totalClientes = 0;
    for (int i=0;i<MAX_SOCKETS_CLIENTES_TCP;i++)
        clientes[i] = NULL;
    numClientes = new CPIGPoolNumeros(MAX_SOCKETS_CLIENTES_TCP);

    totalServidores = 0;
    for (int i=0;i<MAX_SOCKETS_SERVIDORES_TCP;i++)
        servidores[i] = NULL;
    numServidores = new CPIGPoolNumeros(MAX_SOCKETS_SERVIDORES_TCP);

    totalSocketsUDP = 0;
    for (int i=0;i<MAX_SOCKETS_UDP;i++)
        socketsUDP[i] = NULL;
    numSocketsUDP = new CPIGPoolNumeros(MAX_SOCKETS_UDP);*/
    /*for (int i=0;i<MAX_SOCKETS_CLIENTES_TCP;i++)
        posLivresClientes.push_back(i);
    for (int i=0;i<MAX_SOCKETS_SERVIDORES_TCP;i++)
        posLivresServidores.push_back(i);
    for (int i=0;i<MAX_SOCKETS_UDP;i++)
        posLivresUDP.push_back(i);*/
    clientes = new CPIGRepositorio<PIGClienteTCP>(MAX_SOCKETS_CLIENTES_TCP,"clientesTCP");
    servidores = new CPIGRepositorio<PIGServidorTCP>(MAX_SOCKETS_SERVIDORES_TCP,"servidoresTCP");
    socketsUDP = new CPIGRepositorio<PIGSocketUDP>(MAX_SOCKETS_UDP,"socketsUDP");
}

static void Encerra(){
    /*for (int i=0;i<MAX_SOCKETS_CLIENTES_TCP;i++){
        if (clientes[i]) delete clientes[i];
    }
    delete numClientes;

    for (int i=0;i<MAX_SOCKETS_SERVIDORES_TCP;i++){
        if (servidores[i]) delete servidores[i];
    }
    delete numServidores;

    for (int i=0;i<MAX_SOCKETS_UDP;i++){
        if (socketsUDP[i]) delete socketsUDP[i];
    }
    delete numSocketsUDP;*/
    /*for(itCliente = clientes.begin(); itCliente != clientes.end(); ++itCliente) {
        delete itCliente->second;
    }

    for(itServidor = servidores.begin(); itServidor != servidores.end(); ++itServidor) {
        delete itServidor->second;
    }

    for(itUDP = socketsUDP.begin(); itUDP != socketsUDP.end(); ++itUDP) {
        delete itUDP->second;
    }*/
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



/*static bool GetAtivoCliente(int idSocket){
    return clientes[idSocket]->GetAtivo();
}

static bool GetAtivoServidor(int idSocket){
    return servidores[idSocket]->GetAtivo();
}

static bool GetAtivoSocketUDP(int idSocket){
    return socketsUDP[idSocket]->GetAtivo();
}

static long GetBytesEnviadosCliente(int idSocket){
    return clientes[idSocket]->GetBytesEnviados();
}

static long GetBytesRecebidosCliente(int idSocket){
    return clientes[idSocket]->GetBytesRecebidos();
}

static long GetPacotesEnviadosCliente(int idSocket){
    return clientes[idSocket]->GetPacotesEnviados();
}

static long GetPacotesRecebidosCliente(int idSocket){
    return clientes[idSocket]->GetPacotesRecebidos();
}

static long GetTempoUltimoRecebidoCliente(int idSocket){
    return clientes[idSocket]->GetTempoUltimoRecebido();
}

static long GetTempoUltimoEnviadoCliente(int idSocket){
    return clientes[idSocket]->GetTempoUltimoEnviado();
}

static long GetBytesEnviadosServidor(int idSocket){
    return servidores[idSocket]->GetBytesEnviados();
}

static long GetBytesRecebidosServidor(int idSocket){
    return servidores[idSocket]->GetBytesRecebidos();
}

static long GetPacotesEnviadosServidor(int idSocket){
    return servidores[idSocket]->GetPacotesEnviados();
}

static long GetPacotesRecebidosServidor(int idSocket){
    return servidores[idSocket]->GetPacotesRecebidos();
}

static long GetTempoUltimoRecebidoServidor(int idSocket){
    return servidores[idSocket]->GetTempoUltimoRecebido();
}

static long GetTempoUltimoEnviadoServidor(int idSocket){
    return servidores[idSocket]->GetTempoUltimoEnviado();
}

static long GetBytesEnviadosSocketUDP(int idSocket){
    return socketsUDP[idSocket]->GetBytesEnviados();
}

static long GetBytesRecebidosSocketUDP(int idSocket){
    return socketsUDP[idSocket]->GetBytesRecebidos();
}

static long GetPacotesEnviadosSocketUDP(int idSocket){
    return socketsUDP[idSocket]->GetPacotesEnviados();
}

static long GetPacotesRecebidosSocketUDP(int idSocket){
    return socketsUDP[idSocket]->GetPacotesRecebidos();
}

static long GetTempoUltimoRecebidoSocketUDP(int idSocket){
    return socketsUDP[idSocket]->GetTempoUltimoRecebido();
}

static long GetTempoUltimoEnviadoSocketUDP(int idSocket){
    return socketsUDP[idSocket]->GetTempoUltimoEnviado();
}

static int GetPortaRemotaCliente(int idSocket){
    return clientes[idSocket]->GetPortaRemota();
}

static int GetPortaLocalServidor(int idSocket){
    return servidores[idSocket]->GetPortaLocal();
}

static int GetPortaLocalSocketUDP(int idSocket){
    return socketsUDP[idSocket]->GetPortaLocal();
}

static std::string GetHostRemotoCliente(int idSocket){
    return clientes[idSocket]->GetHostRemoto();
}

static std::string GetHostLocalCliente(int idSocket){
    return clientes[idSocket]->GetHostLocal();
}

static std::string GetHostLocalServidor(int idSocket){
    return servidores[idSocket]->GetHostLocal();
}

static std::string GetHostLocalSocketUDP(int idSocket){
    return socketsUDP[idSocket]->GetHostLocal();
}

static int GetTamanhoPacoteCliente(int idSocket){
    return clientes[idSocket]->GetTamanhoPacote();
}

static int GetTamanhoPacoteServidor(int idSocket){
    return servidores[idSocket]->GetTamanhoPacote();
}

static int GetMaximoConexoesServidor(int idSocket){
    return servidores[idSocket]->GetMaximoConexoes();
}

static int GetQuantidadeConexoes(int idSocket){
    return servidores[idSocket]->GetQuantidadeConexoes();
}

static int EnviaDadosCliente(int idSocket,void *buffer, int tamanhoBuffer){
    return clientes[idSocket]->EnviaDados(buffer,tamanhoBuffer);
}

static int EnviaDadosServidor(int idSocket,int socketSecundario,void *buffer, int tamanhoBuffer){
    return servidores[idSocket]->EnviaDados(buffer,tamanhoBuffer,socketSecundario);
}

static int EnviaDadosSocketUDP(int idSocket,void *buffer,int tamanhoBuffer, std::string hostRemoto, int porta){
    return socketsUDP[idSocket]->EnviaDados(buffer,tamanhoBuffer,hostRemoto,porta);
}*/

};

/*std::vector<int> CPIGGerenciadorSockets::posLivresClientes;
std::unordered_map<int,PIGClienteTCP> CPIGGerenciadorSockets::clientes;
std::unordered_map<int,PIGClienteTCP>::iterator CPIGGerenciadorSockets::itCliente;

std::vector<int> CPIGGerenciadorSockets::posLivresServidores;
std::unordered_map<int,PIGServidorTCP> CPIGGerenciadorSockets::servidores;
std::unordered_map<int,PIGServidorTCP>::iterator CPIGGerenciadorSockets::itServidor;

std::vector<int> CPIGGerenciadorSockets::posLivresUDP;
std::unordered_map<int,PIGSocketUDP> CPIGGerenciadorSockets::socketsUDP;
std::unordered_map<int,PIGSocketUDP>::iterator CPIGGerenciadorSockets::itUDP;
*/
/*int CPIGGerenciadorSockets::totalClientes;
PIGPoolNumeros CPIGGerenciadorSockets::numClientes;
PIGClienteTCP CPIGGerenciadorSockets::clientes[MAX_SOCKETS_CLIENTES_TCP];
int CPIGGerenciadorSockets::totalServidores;
PIGPoolNumeros CPIGGerenciadorSockets::numServidores;
PIGServidorTCP CPIGGerenciadorSockets::servidores[MAX_SOCKETS_SERVIDORES_TCP];
int CPIGGerenciadorSockets::totalSocketsUDP;
PIGPoolNumeros CPIGGerenciadorSockets::numSocketsUDP;
PIGSocketUDP CPIGGerenciadorSockets::socketsUDP[MAX_SOCKETS_UDP];*/
CPIGRepositorio<PIGClienteTCP> *CPIGGerenciadorSockets::clientes;
CPIGRepositorio<PIGServidorTCP> *CPIGGerenciadorSockets::servidores;
CPIGRepositorio<PIGSocketUDP> *CPIGGerenciadorSockets::socketsUDP;
#endif // _CPIGGERENCIADORSOCKETS_
