#include "PIG.h"

PIG_Evento evento;          //evento ser tratado a cada pssada do loop principal
PIG_Teclado meuTeclado;     //variável como mapeamento do teclado

bool souServ;               //indica se é servidor ou cliente
int socket=-1;                 //id do socket utilizado
int socketSecundario=-1;    //id do scoket secundário (host conectado ao servidor)

int botaoEnvia,botaoCliente,botaoServidor;
int campoTexto,areaTexto;

void ConectaCliente(){
    if (socket!=-1) DestroiSocketCliente(socket);
    socket = CriaSocketCliente("127.0.0.1",34444);
    if (socket>=0){
        SetTituloJanela("Cliente");
        PIG_Componentes_SetHabilitado(botaoEnvia,true);
        PIG_Componentes_SetHabilitado(botaoCliente,false);
        PIG_Componentes_SetHabilitado(botaoServidor,false);
    }
}

void DesconectaCliente(){
    if (socket!=-1){
        DestroiSocketCliente(socket);
        socket = -1;
        SetTituloJanela("Meu Jogo");
        PIG_Componentes_SetHabilitado(botaoEnvia,false);
        PIG_Componentes_SetHabilitado(botaoCliente,true);
        PIG_Componentes_SetHabilitado(botaoServidor,true);
    }
}

void ConectaServidor(){
    if (socket!=-1)
        DestroiSocketServidor(socket);
    socket = CriaSocketServidor(20,34444);
    if (socket>=0){
        SetTituloJanela("Servidor");
        PIG_Componentes_SetHabilitado(botaoEnvia,true);
        PIG_Componentes_SetHabilitado(botaoCliente,false);
        PIG_Componentes_SetHabilitado(botaoServidor,false);
    }
}

void DesconectaServidor(){
    if (socket!=-1){
        DestroiSocketServidor(socket);
        socket = -1;
        SetTituloJanela("Meu Jogo");
        PIG_Componentes_SetHabilitado(botaoEnvia,false);
        PIG_Componentes_SetHabilitado(botaoCliente,true);
        PIG_Componentes_SetHabilitado(botaoServidor,true);
    }
}

int escolhe(int id,void *param){
    souServ = (id==botaoServidor);
    if (souServ){
        ConectaServidor();
        printf("Serei servidor\n");
    }else{
        ConectaCliente();
        printf("Serei cliente\n");
    }
}

int acao(int id,void *param){
    string strTexto = PIG_CampoTexto_GetTexto(campoTexto);
    printf("texto do campo <%s>...\n",strTexto.c_str());
    if (souServ){
        if (socketSecundario!=-1){
            printf("Enviando(serv): <%s>\n",strTexto.c_str());
            EnviaDadosSocketServidor(socket,socketSecundario,(void*)strTexto.c_str(),strTexto.size()+1);
        }
    }else{
        printf("Enviando(clie): <%s>\n",strTexto.c_str());
        EnviaDadosSocketCliente(socket,(void*)strTexto.c_str(),strTexto.size()+1);
    }
}

int main( int argc, char* args[] ){
    CriaJogo("Meu Jogo",1);

    meuTeclado = GetTeclado();

    int x = 0;
    int y = 0;
    int y2 = y + 300;
    int alt = 50;
    int larg = 200;
    int altAreatexto = 300;

    CarregaCursor("./imgs_ships//s3.png");
    CarregaFramesPorLinhaCursor(1,4,5);
    int id=1;
    MudaCursor(id);

    int fonte = CriaFonteNormal("..//fontes//arial.ttf",20,VERDE,0,PRETO);

    int Form1 = PIG_CriaForm(0,0,ALT_TELA,LARG_TELA);

    campoTexto = PIG_CriaCampoTexto(Form1,x + 2*larg,y+alt+50,alt,larg,"fundo3.png",200,false,0);
    PIG_Componentes_SetLabel(campoTexto,"Mensagem");
    PIG_Componentes_SetFonteLabel(campoTexto,fonte);
    PIG_Componentes_SetPosicaoPadraoLabel(campoTexto,PIG_COMPONENTE_CIMA_CENTRO);

    botaoEnvia = PIG_CriaBotao(Form1,x+2*larg,y,alt,larg,"..//imagens//bot2.png");
    PIG_Componentes_SetLabel(botaoEnvia,"Enviar");
    PIG_Botao_DefineAcao(botaoEnvia,acao,NULL);
    PIG_Componentes_SetHabilitado(botaoEnvia,false);

    botaoCliente = PIG_CriaBotao(Form1,x, 400,alt,larg,"..//imagens//bot2.png");
    PIG_Componentes_SetLabel(botaoCliente,"Cliente");
    PIG_Botao_DefineAcao(botaoCliente,escolhe,NULL);
    //PIG_Componentes_SetHint(botao1,"Botao 1");
    botaoServidor = PIG_CriaBotao(Form1,x+larg, 400,alt,larg,"..//imagens//bot2.png");
    PIG_Componentes_SetLabel(botaoServidor,"Servidor");
    PIG_Botao_DefineAcao(botaoServidor,escolhe,NULL);
    //PIG_Componentes_SetCorHint(botao2,ROXO);
    //PIG_Componentes_SetHint(botao2,"Botao 2");

    areaTexto = PIG_CriaAreaDeTexto(Form1,100 + 300,160+10,300,200,"fundo3.png",200,0);
    PIG_Componentes_SetLabel(areaTexto,"AreaDeTexto");
    PIG_Componentes_SetPosicaoPadraoLabel(areaTexto,PIG_COMPONENTE_CIMA_CENTRO);
    //PIG_Componentes_SetHint(areaTexto1,"Area de texto");
    PIG_AreaDeTexto_SetCorCursor(areaTexto,VERMELHO);

    int t = CriaTimer();

    while(JogoRodando()){

        if (TempoDecorrido(t)>0.5){
            MudaCursor((id++ % 20)+1);
            ReiniciaTimer(t);
        }
        evento = GetEvento();
        if (evento.tipoEvento==EVENTO_REDE)
            printf("evento rede (%d)\n",evento.rede.tipoMensagem);
        if (evento.tipoEvento==EVENTO_REDE&&evento.rede.tipoMensagem==REDE_CONEXAO){
            printf("chegou conexao\n");
            if (souServ){
                socketSecundario = evento.rede.idSecundario;
                printf("Cliente conectado com sucesso (socketSecundario %d)\n!!",socketSecundario);
            }else{
                printf("Conectado ao servidor!!\n");
            }
        }else if (evento.tipoEvento==EVENTO_REDE&&evento.rede.tipoMensagem==REDE_DESCONEXAO){
            if (souServ){
                //DesconectaServidor();
                printf("Cliente desconectado com sucesso!!\n");
            }else{
                DesconectaCliente();
                printf("Desconectado ao servidor!!\n");
            }
        }else if (evento.tipoEvento==EVENTO_REDE&&evento.rede.tipoMensagem==REDE_MENSAGEM_TCP){
            printf("chegou: <%s>\n",(char*)evento.rede.mensagem);
            string textoArea = PIG_AreaDeTexto_GetTexto(areaTexto);
            //printf("texto atual <%s> (%s)\n",textoArea.c_str(),evento.rede.mensagem);
            std::string texto((char*)evento.rede.mensagem);

            //printf("texto atual <%s>\n",texto.c_str());
            string completa(textoArea+texto+'\n');
            PIG_AreaDeTexto_SetTexto(areaTexto,(char*)completa.c_str());
            printf("texto atualizado\n");
        }


        PIG_Form_TrataEvento(Form1,evento);

        IniciaDesenho();

        PIG_Form_Desenha(Form1);


        EncerraDesenho();

    }

    //o jogo será encerrado
    FinalizaJogo();

    return 0;
}
