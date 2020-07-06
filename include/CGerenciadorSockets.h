
#include "CSocketTCP.h"
#include "CClienteTCP.h"
#include "CServidorTCP.h"
#include "CSocketUDP.h"

class CGerenciadorSockets{

private:

static int totalClientes;
static PoolNumeros numClientes;
static ClienteTCP clientes[MAX_SOCKETS_CLIENTES_TCP];
static int totalServidores;
static PoolNumeros numServidores;
static ServidorTCP servidores[MAX_SOCKETS_SERVIDORES_TCP];
static int totalSocketsUDP;
static PoolNumeros numSocketsUDP;
static SocketUDP socketsUDP[MAX_SOCKETS_UDP];

public:

static void Inicia(){
    totalClientes = 0;
    for (int i=0;i<MAX_SOCKETS_CLIENTES_TCP;i++)
        clientes[i] = NULL;
    numClientes = new CPoolNumeros(MAX_SOCKETS_CLIENTES_TCP);

    totalServidores = 0;
    for (int i=0;i<MAX_SOCKETS_SERVIDORES_TCP;i++)
        servidores[i] = NULL;
    numServidores = new CPoolNumeros(MAX_SOCKETS_SERVIDORES_TCP);

    totalSocketsUDP = 0;
    for (int i=0;i<MAX_SOCKETS_UDP;i++)
        socketsUDP[i] = NULL;
    numSocketsUDP = new CPoolNumeros(MAX_SOCKETS_UDP);
}

static void Encerra(){
    for (int i=0;i<MAX_SOCKETS_CLIENTES_TCP;i++){
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
    delete numSocketsUDP;
}

static int CriaCliente(std::string hostname, int porta, int maxBytesPacote=MAX_MENSAGEM_REDE_TCP){
    int resp = numClientes->RetiraLivre();
    clientes[resp] = new CClienteTCP(resp,hostname,porta,maxBytesPacote);
    totalClientes++;
    return resp;
}

static int CriaServidor(int maxClientes, int porta, int maxBytesPacote=MAX_MENSAGEM_REDE_TCP){
    int resp = numServidores->RetiraLivre();
    servidores[resp] = new CServidorTCP(resp,maxClientes,porta,maxBytesPacote);
    totalServidores++;
    return resp;
}

static int CriaSocketUDP(int porta){
    int resp = numSocketsUDP->RetiraLivre();
    socketsUDP[resp] = new CSocketUDP(resp,porta);
    totalSocketsUDP++;
    return resp;
}

static void DestroiCliente(int idSocket){
    numClientes->DevolveUsado(idSocket);
    delete clientes[idSocket];
    totalClientes--;
    clientes[idSocket] = NULL;
}

static void DestroiServidor(int idSocket){
    numServidores->DevolveUsado(idSocket);
    delete servidores[idSocket];
    totalServidores--;
    servidores[idSocket] = NULL;
}

static void DestroiSocketUDP(int idSocket){
    numSocketsUDP->DevolveUsado(idSocket);
    delete socketsUDP[idSocket];
    totalSocketsUDP--;
    socketsUDP[idSocket] = NULL;
}

static bool GetAtivoCliente(int idSocket){
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
}

};

int CGerenciadorSockets::totalClientes;
PoolNumeros CGerenciadorSockets::numClientes;
ClienteTCP CGerenciadorSockets::clientes[MAX_SOCKETS_CLIENTES_TCP];
int CGerenciadorSockets::totalServidores;
PoolNumeros CGerenciadorSockets::numServidores;
ServidorTCP CGerenciadorSockets::servidores[MAX_SOCKETS_SERVIDORES_TCP];
int CGerenciadorSockets::totalSocketsUDP;
PoolNumeros CGerenciadorSockets::numSocketsUDP;
SocketUDP CGerenciadorSockets::socketsUDP[MAX_SOCKETS_UDP];
