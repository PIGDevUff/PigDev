#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "SDL_net.h"
#include "SDL_mixer.h"

#include "PIGTipos.h"
#include "PIGFuncoesBasicas.h"
#include "CPIGErros.h"

#include "CPIGRepositorio.h"
#include "CPIGGerenciadorTimers.h"
#include "CPIGAssetLoader.h"
#include "CPIGOffscreenRenderer.h"
#include "CPIGGerenciadorAudios.h"
#include "CPIGGerenciadorJanelas.h"
#include "CPIGGerenciadorSockets.h"
#include "CPIGGerenciadorFontes.h"
#include "CPIGGerenciadorSprites.h"
#include "CPIGGerenciadorGDP.h"
#ifdef PIGCOMVIDEO
#include "CPIGGerenciadorVideos.h"
#endif
#include "CPIGGerenciadorControles.h"
#include "CPIGGerenciadorForms.h"
#include "CPIGGerenciadorTelas.h"

#include "CPIGJogo.h"


/********************************
/ Variáveis Globais
/********************************/
PIGJogo jogo=NULL;

/********************************
A funçăo CriaJogo() é responsável pela criaçăo da janela do jogo e pelos componentes audio-visuais.
Ela deve ser chamada antes de qualquer outra funçăo da biblioteca PIG.h. Năo é possível criar dois
jogos no mesmo progama. Logo, somente a primeira chamada terá efeito. A janela padrăo da aplicaçăo terá o tamanho definido pelas constantes PIG_ALT_TELA e PIG_LARG_TELA
definidas no arquivo PIGTipos.h, exceto se forem passados outros valores.
Parâmetros:
nomeJanela (entrada, passagem por referęncia*): indica o nome que a janela do jogo mostrará no seu título.
É utilizado o operador * apenas por se tratar de um parâmetro string. O valor do parâmetro năo é alterado dentro da funçăo.
cursorProprio (entrada, passagem por valor): indica se o jogo utilizará cursores (ponteiros) próprios para o mouse ou utilizará o cursor padrăo.
altura (entrada, passagem por valor năo-obrigatório): indica a altura em pixels da janela principal do jogo.
largura (entrada, passagem por valor năo-obrigatório): indica a largura em pixels da janela principal do jogo.
********************************/
/**
 *  \brief Cria o jogo.
 *
 *  \param nomeJanela   Título da janela do jogo.
 *  \param cursorProrio Se diferente de zero, indica que o usuário definirá cursores
 *  \param altura       Altura da tela do jogo
 *  \param largura      Largura da tela do jogo
 *
 *
 *  \sa FinalizaJogo()
 */
void CriaJogo(const char *nomeJanela,int cursorProprio=0,int altura=PIG_ALT_TELA,int largura=PIG_LARG_TELA){
    if (jogo==NULL){
        jogo = new CPIGJogo(nomeJanela,cursorProprio,altura,largura);
        CPIGAssetLoader::Inicia();
        CPIGMouse::Inicia(cursorProprio);
        CPIGGerenciadorSprites::Inicia();
        CPIGGerenciadorGDP::Inicia();
        CPIGGerenciadorFontes::Inicia();
        CPIGGerenciadorTimers::Inicia();
        CPIGGerenciadorAudios::Inicia();
        CPIGGerenciadorControles::Inicia();
        CPIGGerenciadorSockets::Inicia();
        #ifdef PIGCOMVIDEO
        CPIGGerenciadorVideos::Inicia();
        #endif
        CPIGGerenciadorForms::Inicia();
        CPIGGerenciadorTelas::Inicia();
    }
}


/********************************
A funçăo SetValorIntJogo() é responsável incorporar ao jogo um atributo inteiro.
Parâmetros:
indice (entrada, passagem por valor): relaciona um número inteiro ao atributo.
valor (entrada, passagem por valor): valor do atributo inteiro a ser associado ao jogo.
********************************/
void SetValorIntJogo(int indice,int valor){
    jogo->SetValorInt(indice,valor);
}

/********************************
A funçăo SetValorFloatJogo() é responsável incorporar ao jogo um atributo float.
Parâmetros:
indice (entrada, passagem por valor): relaciona um número inteiro ao atributo.
valor (entrada, passagem por valor): valor do atributo float a ser associado ao jogo.
********************************/
void SetValorFloatJogo(int indice,float valor){
    jogo->SetValorFloat(indice,valor);
}

/********************************
A funçăo SetValorIntJogo() é responsável incorporar ao jogo um atributo inteiro.
Parâmetros:
indice (entrada, passagem por valor): relaciona um número inteiro ao atributo.
valor (entrada, passagem por referęncia): valor do atributo string a ser associado ao jogo.
********************************/
void SetValorStringJogo(int indice,char *valor){
    jogo->SetValorString(indice,valor);
}

/********************************
A funçăo SetValorIntJogo() é responsável incorporar ao jogo um atributo inteiro.
Parâmetros:
indice (entrada, passagem por referęncia): relaciona uma string ao atributo.
valor (entrada, passagem por valor): valor do atributo inteiro a ser associado ao jogo.
********************************/
void SetValorIntJogo(char *indice,int valor){
    jogo->SetValorInt(indice,valor);
}

/********************************
A funçăo SetValorFloatJogo() é responsável incorporar ao jogo um atributo float.
Parâmetros:
indice (entrada, passagem por referęncia): relaciona uma string ao atributo.
valor (entrada, passagem por valor): valor do atributo float a ser associado ao jogo.
********************************/
void SetValorFloatJogo(char *indice,float valor){
    jogo->SetValorFloat(indice,valor);
}

/********************************
A funçăo SetValorIntJogo() é responsável incorporar ao jogo um atributo inteiro.
Parâmetros:
indice (entrada, passagem por referęncia): relaciona uma string ao atributo.
valor (entrada, passagem por referęncia): valor do atributo string a ser associado ao jogo.
********************************/
void SetValorStringJogo(char *indice,char *valor){
    jogo->SetValorString(indice,valor);
}

/********************************
A funçăo GetValorIntJogo() é responsável recuperar o valor de um atributo inteiro relacionado ao jogo.
Parâmetros:
indice (entrada, passagem por valor): indica o número do atributo que se deseja recuperar.
valor (saída, passagem por referęncia): indica o valor do atributo, se a funçăo retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo năo existir, a funçăo retorna o valor 0 (zero).
********************************/
int GetValorIntJogo(int indice,int *valor){
    return jogo->GetValorInt(indice,*valor);
}

/********************************
A funçăo GetValorFloatJogo() é responsável recuperar o valor de um atributo float relacionado ao jogo.
Parâmetros:
indice (entrada, passagem por valor): indica o número do atributo que se deseja recuperar.
valor (saída, passagem por referęncia): indica o valor do atributo, se a funçăo retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo năo existir, a funçăo retorna o valor 0 (zero).
********************************/
int GetValorFloatJogo(int indice,float *valor){
    return jogo->GetValorFloat(indice,*valor);
}

/********************************
A funçăo GetValorStringJogo() é responsável recuperar o valor de um atributo string relacionado ao jogo.
Parâmetros:
indice (entrada, passagem por valor): indica o número do atributo que se deseja recuperar.
valor (saída, passagem por referęncia): indica o valor do atributo, se a funçăo retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo năo existir, a funçăo retorna o valor 0 (zero).
********************************/
int GetValorStringJogo(int indice,char *valor){
    std::string str;
    bool resp = jogo->GetValorString(indice,str);
    strcpy(valor,str.c_str());
    return resp;
}

/********************************
A funçăo GetValorIntJogo() é responsável recuperar o valor de um atributo inteiro relacionado ao jogo.
Parâmetros:
indice (entrada, passagem por referęncia): indica o nome do atributo que se deseja recuperar.
valor (saída, passagem por referęncia): indica o valor do atributo, se a funçăo retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo năo existir, a funçăo retorna o valor 0 (zero).
********************************/
int GetValorIntJogo(char *indice,int *valor){
    return jogo->GetValorInt(indice,*valor);
}

/********************************
A funçăo GetValorFloatJogo() é responsável recuperar o valor de um atributo float relacionado ao jogo.
Parâmetros:
indice (entrada, passagem por valor): indica o nome do atributo que se deseja recuperar.
valor (saída, passagem por referęncia): indica o valor do atributo, se a funçăo retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo năo existir, a funçăo retorna o valor 0 (zero).
********************************/
int GetValorFloatJogo(char *indice,float *valor){
    return jogo->GetValorFloat(indice,*valor);
}

/********************************
A funçăo GetValorStringJogo() é responsável recuperar o valor de um atributo string relacionado ao jogo.
Parâmetros:
indice (entrada, passagem por valor): indica o nome do atributo que se deseja recuperar.
valor (saída, passagem por referęncia): indica o valor do atributo, se a funçăo retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo năo existir, a funçăo retorna o valor 0 (zero).
********************************/
int GetValorStringJogo(char *indice,char *valor){
    std::string str;
    bool resp = jogo->GetValorString(indice,str);
    strcpy(valor,str.c_str());
    return resp;
}

/********************************
A funçăo GetEstadoJogo() indica o estado do jogo. Este estado é apenas um valor inteiro
que pode ser usado para indicar uma fase do jogo, ou a vez de algum jogador por exemplo.
Retorno:
inteiro indicando o valor do estado do jogo.
********************************/
//int GetEstadoJogo(){
//    return jogo->GetEstado();
//}

/********************************
A funçăo SetEstadoJogo() atribui um novo valor ao estado do jogo. Este estado é apenas um valor inteiro
que pode ser usado para indicar uma fase do jogo, ou a vez de algum jogador por exemplo.
Parâmetro:
estado (entrada, passagem por valor): indica o novo estado do jogo;
********************************/
//void SetEstadoJogo(int estado){
//    jogo->SetEstado(estado);
//}

/********************************
A funçăo DefineFundoJanela() permite escolher um arquivo de imagem como fundo (background) de uma janela que será automaticamente desenhado a cada nova etapa de desenho na tela.
Parâmetros:
nomeArquivoImagem (entrada, passagem por referęncia*): indica o caminho relativo ou absoluto do arquivo de imagem que será utilizado como fundo do jogo.
É utilizado o operador * apenas por se tratar de um parâmetro string. O valor do parâmetro năo é alterado dentro da funçăo.
idJanela (entrada, passagem por valor năo-obrigatorio): indica de qual janela é a imagem.
********************************/
void DefineFundo(char *nomeArquivoImagem,int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->DefineFundo(nomeArquivoImagem);
}

/********************************
A funçăo GetTeclado() faz um mapeamento entre o teclado físico a uma variável do tipo PIG_Teclado que funciona como um vetor de variáveis lógicas,
sendo cada posiçăo do vetor relativo a uma tecla física.
Uma lista das possíveis teclas e seus código pode ser vista no arquivo Tipos_PIG.h.
Retorno:
O valor de retorno da funçăo é um vetor de números inteiros que indicam se uma determinada tecla (índice do vetor) foi
pressionada (valor diferente de 0,zero) ou năo (valor igual a zero).
********************************/
PIG_Teclado GetTeclado(){
    return jogo->PegaTeclado();
}

/********************************
A funçăo GetEvento() indica se houve algum tipo de evento desde a última vez que a funçăo foi chamada.
Um evento pode ser uma tecla pressionada, um clique do mouse ou outra coisa relacionada ŕ tela do jogo.
Maiores informaçőe podem ser vistas no arquivo PIGTipos.h
Retorno:
O valor de retorno é um struct contendo o tipo de evento ocorrido e vários outros structs com informaçőes específicas.
********************************/
PIG_Evento GetEvento(){
    return jogo->PegaEvento();
}

/********************************
A funçăo IniciaDesenho() é responsável por preparar a janela do jogo para que os objetos gráficos
possam ser mostrados, além de desenhar a imagem de fundo do jogo, caso tenha sido definida.
Deve ser chamada repetidamente a cada novo quadro (frame) a ser desenhado.
Parâmetros:
idJanela (entrada, passagem por valor năo-obrigatório): indica qual janela deve preparar a renderizaçăo. O valor (-1) indica que todas as janelas devem ser preparadas.
********************************/
void IniciaDesenho(int idJanela=-1){
    jogo->IniciaDesenho(idJanela);
}

/********************************
A funçăo EncerraDesenho() é responsável por encerrar o desenho que foi criado, mostrando na janela do jogo.
Deve ser chamado sempre ao final do loop principal do jogo.
Parâmetros:
idJanela (entrada, passagem por valor năo-obrigatório): indica qual janela deve preparar a renderizaçăo. O valor (-1) indica que todas as janelas devem ser exibidas.
********************************/
void EncerraDesenho(int idJanela=-1){
    CPIGMouse::Desenha();
    jogo->EncerraDesenho(idJanela);
}

/********************************
A funçăo SalvaTela() é responsável por criar um arquivo Bitmap, contendo uma cópia de uma janela do jogo naquele momento.
Parâmetros:
nomeArquivoBMP (entrada, passagem por referęncia*): indica o nome do arquivo Bitmap que será salvo. O valor do parâmetro deve conter a extensăo ".bmp".
É utilizado o operador * apenas por se tratar de um parâmetro string. O valor do parâmetro năo é alterado dentro da funçăo.
idJanela (entrada, passagem por valor năo-obrigatório): indica qual janela deve ter a imagem salva.
********************************/
void SalvaTela(char *nomeArquivoBMP,int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->SaveScreenshot(nomeArquivoBMP,true);
}

/********************************
A funçăo JogoRodando() é reponsável por retornar se o jogo ainda está ativo ou năo.
O jogo será encerrado se a janela do jogo for fechada, por exemplo.
Retorno:
inteiro que indica se o jogo ainda está sendo executado (valor diferente de zero) ou năo (valor igual a 0, zero).
********************************/
int JogoRodando(){
    return jogo->GetRodando();
}

/********************************
A funçăo Espera() "congela" a tela do jogo por alguns milissegundos, impedindo que qualquer outro comando seja executado enquanto isso.
Parâmetros:
tempo (entrada, passagem por valor): indica a quantidade de milissegundos durante a qual o jogo será pausado.
********************************/
void Espera(int tempo){
    SDL_Delay(tempo);
}

/********************************
A funçăo FinalizaJogo() é responsável por encerrar com a PIG. Após tudo o jogo ser executado
a funçăo deve ser chamada e ela irá realizar a liberaçăo de memória dos elementos criados pela PIG.
********************************/
void FinalizaJogo(){
    CPIGGerenciadorControles::Encerra();
    CPIGGerenciadorFontes::Encerra();
    CPIGGerenciadorAudios::Encerra();
    #ifdef PIGCOMVIDEO
    CPIGGerenciadorVideos::Encerra();
    #endif
    CPIGGerenciadorSockets::Encerra();
    CPIGGerenciadorForms::Encerra();
    CPIGGerenciadorTelas::Encerra();
    CPIGGerenciadorSprites::Encerra();
    CPIGGerenciadorGDP::Encerra();
    CPIGGerenciadorTimers::Encerra();
    CPIGMouse::Encerra();
    CPIGAssetLoader::Encerra();
    delete jogo;
}

/********************************
A funçăo GetFPS() é responsável por calcular o valor do Frames Per Seconds (FPS), que representa a quantidade de
frames (quadros) desenhados por segundo pela PIG.
Retorno:
float que indica a média de quadros desenhados por segundo.
********************************/
float GetFPS(){
    return jogo->GetFPS();
}

/********************************
A funçăo CarregaCursor() é responsável por armazenar um novo cursor para o mouse, dado pelo arquivo de imagem indicado.
O arquivo deve ser uma imagem com 32 pixels de altura orbigatoriamente.
Parâmetro:
nomeArquivoCursor (entrada, passagem por referęncia*): indica o nome do arquivo de imagem que será utilziado como cursor do mouse.
É utilizado o operador * apenas por se tratar de um parâmetro string. O valor do parâmetro năo é alterado dentro da funçăo.
********************************/
void CarregaCursor(char *nomeArquivoCursor, int idJanela=0){
    CPIGMouse::CarregaCursor(nomeArquivoCursor,idJanela);
}

/********************************
A funçăo CriaFrameCursor() é responsável por delimitar a área do arquivo de imagem para um cursor específico.
Idealmente, a altura e largura informadas devem ter tamanho igual a 32 pixels (para năo haver perda de qualidade na exibiçăo do cursor).
Parâmetro:
idFrame (entrada, passagem por valor): número inteiro associado ao cursor (área do arquivo de imagem) em questăo.
xBitmap (entrada, passagem por valor): indica a posiçăo de eixo X onde começa o frame.
yBitmap (entrada, passagem por valor): indica a posiçăo de eixo Y onde começa o frame. Neste caso, o eixo Y aumenta para baixo.
altura (entrada, passagem por valor): altura em pixels do frame.
largura (entrada, passagem por valor): largura em pixels do frame.
********************************/
void CriaFrameCursor(int idFrame, int xBitmap, int yBitmap, int altura, int largura){
    CPIGMouse::CriaFrameCursor(idFrame,xBitmap,yBitmap,altura,largura);
}

/********************************
A funçăo CarregaFramesPorLinhaCursor() é responsável por subdividir o arquivo de imagem em linhas (de mesmo tamanho) e colunas (de mesmo tamanho).
Cada subdivisăo representará um frame que será automaticamente criado para o cursor do mouse, com numeraçăo incremental a partir do parâmetro "frameInicial".
Ao final das "qtdColunas" da primeira linha, a definiçăo dos frames continua na linha inferior.
A funçăo pode ser utilizada em spritesheets regulares.
Parâmetros:
frameInicial (entrada, passagem por valor): numeraçăo do primeiro frame a ser criado pela funçăo. Os demais frames terăo numeraçăo consecutiva.
qtdLinhas (entrada, passagem por valor): quantidade de linhas na qual o arquivo de imagem será dividido.
qtdColunas (entrada, passagem por valor): quantidade de colunas na qual o arquivo de imagem será dividido.
********************************/
void CarregaFramesPorLinhaCursor(int frameInicial, int qtdLinhas, int qtdColunas){
    CPIGMouse::CarregaFramesPorLinha(frameInicial,qtdLinhas,qtdColunas);
}

/********************************
A funçăo CarregaFramesPorColunaCursor() é responsável por subdividir o arquivo de imagem em linhas (de mesmo tamanho) e colunas (de mesmo tamanho).
Cada subdivisăo representará um frame que será automaticamente criado para o cursor do mouse, com numeraçăo incremental a partir do parâmetro "frameInicial".
Ao final das "qtdLinhas" da primeira coluna, a definiçăo dos frames continua na coluna seguinte.
A funçăo pode ser utilizada em spritesheets regulares.
Parâmetros:
frameInicial (entrada, passagem por valor): numeraçăo do primeiro frame a ser criado pela funçăo. Os demais frames terăo numeraçăo consecutiva.
qtdLinhas (entrada, passagem por valor): quantidade de linhas na qual o arquivo de imagem será dividido.
qtdColunas (entrada, passagem por valor): quantidade de colunas na qual o arquivo de imagem será dividido.
********************************/
void CarregaFramesPorColunaCursor(int frameInicial, int qtdLinhas, int qtdColunas){
    CPIGMouse::CarregaFramesPorColuna(frameInicial,qtdLinhas,qtdColunas);
}

/********************************
A funçăo MudaCursor() é responsável por alterar o cursor atual do mouse por outro já definido (funçăo DefineFrameCursor).
Parâmetro:
idFrame (entrada, passagem por valor): informa o identificador de um cursor (frame) já criado.
Retorno:
Se o identifador informado năo corresponder a um frame já criado, o valor de retorno é igual a 0. Caso contrário, é igual a 1.
********************************/
int MudaCursor(int idFrame){
    return CPIGMouse::MudaCursor(idFrame);
}


/********************************
A funçăo GetEstadoBotaoMouse() é responsável por recuperar o eatado atual de um dos botoes (PIG_MOUSE_DIREITO, PIG_MOUSE_CENTRAL ou PIG_MOUSE_RODINHA) do mouse.
O valor retornado pode ser PIG_MOUSE_PRESSIONADO ou PIG_MOUSE_LIBERADO.
Retorno:
inteiro que indica a o estado atual do botăo do mouse solicitado.
********************************/
int GetEstadoBotaoMouse(int botao){
    return CPIGMouse::GetEstadoBotao(botao);
}

/********************************
A funçăo ExecutaBackground() é responsável por executar uma funçăo em bckground, ou seja, fora do fluxo principal de execuçăo do programa.
Essa execuçăo é feita por outra Thread, com suporte do Sistema Operacional
Parâmetros:
dados (entrada, passagem por referęncia): ponteiro genérico para qualquer tipo de dado a ser utilizado na funçăo.
********************************/
void ExecutaBackground(PIG_FuncaoBackground funcao,void *dados){
    SDL_CreateThread(funcao,"",dados);
}


/********************************
Seçăo de tratamento de janelas
********************************/

/********************************
A funçăo GetQtdJanela() é responsável por calcular quantas janelas estăo criadas pelo jogo, incluindo as que estăo minimizadas ou escondidas.
Retono:
inteiro que representa a quantidade de janelas ainda abertas pelo jogo, incluindo as que estăo minimizadas ou escondidas.
********************************/
int GetQtdJanelas(){
    return CPIGGerenciadorJanelas::GetQtdJanelas();
}

/********************************
A funçăo CriaJanela() é responsável por criar e exibir uma nova janela para a aplicaçăo. O identificador numérico da nova janela é retornado como parâmetro.
Se năo foi possível criar a janela, o valor de retorno será -1. Existe um limite máximo de janela que podem ser criadas. Esse limite é dado pelo parâmetro MAX_JANELAS configurado na Tipos_PIG.h.
O valor da janela original (padrăo) é sempre igual a 0 (zero). Para se desenhar qualquer coisa nas janelas adicionais, é preciso criar objetos, animaçőes, geradores de partículas e fontes
especificando-se a janela na qual estes elementos serăo renderizados. Ao utilizar-se janelas adicionais, também é possível estipular individualmente quais janelas serăo preparadas e mostradas, utilizando o
número da janela nas chamadas das funçőes IniciaDesenho e EncerraDesenho. Caso năo seja especificado o número, todas as janelas săo preparadas e mostradas, respectivamente.
Parâmetros:
nomeJanela (entrada, passagem por referęncia*): indica o nome que a nova janela mostrará no seu título.
É utilizado o operador * apenas por se tratar de um parâmetro string. O valor do parâmetro năo é alterado dentro da funçăo.
altura (entrada, passagem por valor năo-obrigatório): indica a altura em pixels da janela a ser criada.
largura (entrada, passagem por valor năo-obrigatório): indica a largura em pixels da janela a ser criada.
Retorno
inteiro que representa o número de identificaçăo dessa janela. esse número deve ser utilizado sempre que um comando deva ser executado para uma janela específica.
A janela padrăo da aplicaçăo possui sempre o número 0 (zero).
********************************/
int CriaJanela(char *nomeJanela,int altura=PIG_ALT_TELA,int largura=PIG_LARG_TELA){
    return CPIGGerenciadorJanelas::CriaJanela(nomeJanela,altura,largura);
}

/********************************
A funçăo FechaJanela() é responsável por fechar uma janela. As renderizaçőes nessa janela que ocorrerem posteriormente năo terăo qualquer efeito.
A janela fechada vai deixar de gerar eventos, mas năo poderpa ser reaberta. O efeito de reabrir um janela pode ser obtido com os comandos EscondeJanela() e ExibeJanela().
Parâmetros:
idJanela (entrada, passagem por valor): indica o número da janela a ser fechada.
********************************/
void FechaJanela(int idJanela){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->Fecha();
}

/********************************
A funçăo EscondeJanela() é responsável por fazer a janela deixar de ser visível, mas năo a fecha de forma definitiva.
A janela poderá ser reaberta com a funçăo ExibeJanela().
Parâmetros:
idJanela (entrada, passagem por valor): indica o número da janela a ser oculta.
********************************/
void EscondeJanela(int idJanela){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->Esconde();
}

/********************************
A funçăo ExibeJanela() é responsável por fazer a janela voltar a ser visível, mas năo faz automaticamente a janela ter o foco para gerar eventos.
A janela poderá ser reaberta com foca por meio da funçăo GanhaFocoJanela().
Parâmetros:
idJanela (entrada, passagem por valor): indica o número da janela a ser reexibida sem foco.
********************************/
void ExibeJanela(int idJanela){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->Exibe();
}

/********************************
A funçăo GanhaFocoJanela() é responsável por fazer a janela voltar a ser visível e automaticamente voltar a ter o foco para gerar eventos.
Parâmetros:
idJanela (entrada, passagem por valor): indica o número da janela a ser reexibida com foco.
********************************/
void GanhaFocoJanela(int idJanela){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->GanhaFoco();
}

/********************************
A funçăo GetAlturaJanela() é responsável por recuperar a altura da janela em pixels.
Parâmetros:
idJanela (entrada, passagem por valor năo-obrigatório): indica o número da janela a ser consultada.
Retorno:
inteiro que representa a altura da janela em pixels.
********************************/
int *GetAlturaJanela(int idJanela=0){
    return CPIGGerenciadorJanelas::GetJanela(idJanela)->GetAltura();
}

/********************************
A funçăo GetLarguraJanela() é responsável por recuperar a largura da janela em pixels.
Parâmetros:
idJanela (entrada, passagem por valor năo-obrigatório): indica o número da janela a ser consultada.
Retorno:
inteiro que representa a largura da janela em pixels.
********************************/
int GetLarguraJanela(int idJanela=0){
    return CPIGGerenciadorJanelas::GetJanela(idJanela)->GetLargura();
}


/********************************
A funçăo SetTamanhoJanela() é responsável por definir o tamanho para a janela.
Parâmetros:
altura (entrada, passagem por valor): indica a quantidade de linhas da janela (em pixels).
largura (entrada, passagem por valor): indica a quantidade de colunas da janela (em pixels).
idJanela (entrada, passagem por valor năo-obrigatório): indica o número da janela a ser alterada.
********************************/
void SetTamanhoJanela(int altura, int largura,int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->SetTamanho(altura,largura);
}

/********************************
A funçăo SetAfastamentoCamera() é responsável por afastar ou aproximar a câmera dos objetos da tela, em um eixo perpendicular.
O valor de afastamento deve variar entre PIG_AFASTAMENTO_MINIMO (0.1) e PIG_AFASTAMENTO_MAXIMO (100).
Quanto maior for o valor, mais "afastada" estará a câmera dos objetos. O valor padrăo é 1.0.
Parâmetros:
afastamento (entrada, passagem por valor): indica o afastamento da câmera em relaçăo ao plano representado pela tela.
idJanela (entrada, passagem por valor năo-obrigatório): indica o número da janela a ser alterada.
Retorno:
O valor retornado é igual ao afastamento após a execuçăo da funçăo.
********************************/
double SetAfastamentoCamera(double afastamento,int idJanela=0){
    return CPIGGerenciadorJanelas::GetJanela(idJanela)->SetAfastamento(afastamento);
}

/********************************
A funçăo GetAfastamentoCamera() recupera o valor atual de afastamento da câmera.
O valor de afastamento deve variar entre PIG_AFASTAMENTO_MINIMO (0.1) e PIG_AFASTAMENTO_MAXIMO (100).
Quanto maior for o valor, mais "afastada" estará a câmera dos objetos. O valor padrăo é 1.0.
Parâmetros:
idJanela (entrada, passagem por valor năo-obrigatório): indica o número da janela a ser alterada.
Retorno:
O valor retornado é igual ao afastamento atual da câmera.
********************************/
double GetAfastamentoCamera(int idJanela=0){
    return CPIGGerenciadorJanelas::GetJanela(idJanela)->GetAfastamento();
}

/********************************
A funçăo MoveCamera() é responsável por reposicionar a câmera no cenário. O ponto de referęncia é o canto inferior esquerdo da tela.
Todos os objetos serăo automaticamente recolocados na tela conforme a posiçăo da câmera.
Parâmetros:
posicaoX (entrada, passagem por valor): indica a posiçăo no eixo X onde a câmera ficará.
posicaoY (entrada, passagem por valor): indica a posiçăo no eixo Y onde a câmera ficará.
idJanela (entrada, passagem por valor năo-obrigatório): indica o número da janela a ser alterada.
********************************/
void MoveCamera(int posicaoX, int posicaoY, int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->MoveCamera(posicaoX,posicaoY);
}

/********************************
A funçăo DeslocaCamera() é responsável por deslocar a câmera em relaçăo ŕ sua posiçăo atual.
Parâmetros:
deltaX (entrada, passagem por valor): valor a ser somado ou subtraído na componente X da posiçăo da câmera.
deltaY (entrada, passagem por valor): valor a ser somado ou subtraído na componente Y da posiçăo da câmera.
idJanela (entrada, passagem por valor năo-obrigatório): indica o número da janela a ser alterada.
********************************/
void DeslocaCamera(int deltaX, int deltaY, int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->DeslocaCamera(deltaX,deltaY);
}

/********************************
A funçăo GetXYCamera() é responsável recuperar o valor da posiçăo (X,Y) da câmera de acordo com o sistema de coordenadas do jogo.
Parâmetros:
posicaoX (saída, passagem por referencia): indica a posicao no eixo X da câmera.
posicaoY (saída, passagem por referencia): indica a posicao no eixo Y da câmera.
idJanela (entrada, passagem por valor năo-obrigatório): indica o número da janela.
********************************/
void GetXYCamera(int *posicaoX, int *posicaoY, int idJanela=0){
    SDL_Point p = CPIGGerenciadorJanelas::GetJanela(idJanela)->GetPosicaoCamera();
    *posicaoX = p.x;
    *posicaoY = p.y;
}

/********************************
A funçăo PreparaCameraMovel() é responsável utilizar a câmera movel relativa ŕ janela em questăo.
A câmera móvel está sujeita ŕ movimentaçőes e ajuste de zoom (afastamento). Todas as renderizaçőes posteriores estarăo sujeitas a essas transformaçőes.
Parâmetros:
idJanela (entrada, passagem por valor năo-obrigatório): indica o número da janela.
********************************/
void PreparaCameraMovel(int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->PreparaCameraMovel();
}

/********************************
A funçăo PreparaCameraFixa() é responsável utilizar a câmera fixa relativa ŕ janela em questăo.
A câmera fixa năo está sujeita ŕ movimentaçőes e ajuste de zoom (afastamento). Todas as renderizaçőes posteriores serăo feitas utilizando o sistema de coordenadas da tela.
Parâmetros:
idJanela (entrada, passagem por valor năo-obrigatório): indica o número da janela.
********************************/
void PreparaCameraFixa(int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->PreparaCameraFixa();
}

/********************************
A funçăo ConverteCoordenadaDaTelaParaMundo() transforma uma coordenada da tela para uma coordenada do cenário, de acordo com o afastamento e a posiçăo da câmera e do sistema de coordenadas do jogo.
Parâmetros:
telaX (entrada, passagem por valor): indica a componente X da coordenada da tela em questăo.
telaY (entrada, passagem por valor): indica a componente Y da coordenada da tela em questăo.
mundoX (saída, passagem por referencia): indica a componente X da coordenada do cenário.
mundoY (saída, passagem por referencia): indica a componente Y da coordenada do cenário.
idJanela (entrada, passagem por valor năo-obrigatório): indica o número da janela.
********************************/
void ConverteCoordenadaDaTelaParaMundo(int telaX, int telaY, int *mundoX, int *mundoY, int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->ConverteCoordenadaScreenWorld(telaX, telaY, *mundoX, *mundoY);
}

/********************************
A funçăo ConverteCoordenadaDoMundoParaTela() transforma uma coordenada do cenário para uma coordenada da tela, de acordo com o afastamento e a posiçăo da câmera e do sistema de coordenadas do jogo.
Parâmetros:
mundoX (entrada, passagem por valor): indica a componente X da coordenada do cenário em questăo.
mundoY (entrada, passagem por valor): indica a componente Y da coordenada do cenário em questăo.
telaX (saída, passagem por referencia): indica a componente X da coordenada da tela.
telaY (saída, passagem por referencia): indica a componente Y da coordenada da tela.
idJanela (entrada, passagem por valor năo-obrigatório): indica o número da janela.
********************************/
void ConverteCoordenadaDoMundoParaTela(int mundoX, int mundoY, int *telaX, int *telaY, int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->ConverteCoordenadaWorldScreen(mundoX, mundoY, *telaX, *telaY);
}

/********************************
A funçăo GetTituloJanela() é responsável por recuperar o título (caption) atual da janela.
Parâmetros:
tituloJanela (saída, passagem por referęncia): armazena o título da janela que foi recuperado.
idJanela (entrada, passagem por valor năo-obrigatório): indica o número da janela a ser consultada.
********************************/
void GetTituloJanela(char *tituloJanela,int idJanela=0){
    strcpy(tituloJanela,CPIGGerenciadorJanelas::GetJanela(idJanela)->GetTitulo().c_str());
}

/********************************
A funçăo SetTituloJanela() é responsável por definir um novo título (caption) para a janela.
Parâmetros:
novoTitulo (entrada, passagem por referęncia*): indica o novo título para a janela.
É utilizado o operador * apenas por se tratar de um parâmetro string. O valor do parâmetro năo é alterada dentro da funçăo.
idJanela (entrada, passagem por valor năo-obrigatório): indica o número da janela a ser alterada.
********************************/
void SetTituloJanela(char *novoTitulo,int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->SetTitulo(novoTitulo);
}

/********************************
A funçăo GetCorFundoJanela() é responsável por recuperar uma cor de fundo para a janela indicada. A cor de fundo será utilizada como background automático quando a janela for preparada para renderizaçőes.
Parâmetros:
idJanela (entrada, passagem por valor năo-obrigatório): indica o número da janela a ser alterada.
Retorno
cor contendo os componentes RGBA da cor utilizada para pintar automaticamente o fundo da janela.
********************************/
PIG_Cor GetCorFundoJanela(int idJanela=0){
    return CPIGGerenciadorJanelas::GetJanela(idJanela)->GetCorFundo();
}

/********************************
A funçăo SetCorFundoJanela() é responsável por definir uma cor de fundo para a janela indicada. A cor de fundo será utilizada como background automático quando a janela for preparada para renderizaçőes.
Parâmetros:
cor (entrada, passagem por valor): indica a cor para o fundo da janela.
idJanela (entrada, passagem por valor năo-obrigatório): indica o número da janela a ser alterada.
********************************/
void SetCorFundoJanela(PIG_Cor cor,int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->SetCorFundo(cor);
}

/********************************
A funçăo GetOpacidadeJanela() é responsável por recuperar o nível de opacidade de uma janela. A opacidade pode variar entre 1.0 (totalmente opaca) e 0 (totalmente transparente).
Parâmetros:
idJanela (entrada, passagem por valor năo-obrigatório): indica o número da janela a ser alterada.
Retorno:
número real que indica o nível de opacidade da janela, variando entre 1.0 e 0.
********************************/
float GetOpacidadeJanela(int idJanela=0){
    return CPIGGerenciadorJanelas::GetJanela(idJanela)->GetOpacidade();
}

/********************************
A funçăo SetOpacidadeJanela() é responsável por definir o nível de opacidade de uma janela. A opacidade pode variar entre 1.0 (totalmente opaca) e 0 (totalmente transparente).
Parâmetros:
nivelOpacidade (entrada, passagem por valor): indica o nível de opacidade da janela, variando entre 1.0 e 0.
idJanela (entrada, passagem por valor năo-obrigatório): indica o número da janela a ser alterada.
********************************/
void SetOpacidadeJanela(float nivelOpacidade,int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->SetOpacidade(nivelOpacidade);
}

/********************************
A funçăo SetPosicaoJanela() é responsável por definir a posiçăo de um janela na tela correspondente. A tela normalmente utiliza um sistema de coordenadas, cujo ponto (0,0) é o canto superior esquerdo.
Parâmetros:
posicaoX (entrada, passagem por valor): indica o valor no eixo X (horizontal) da esquerda para direita.
posicaoY (entrada, passagem por valor): indica o valor no eixo Y (vertical), normalmente de cima para baixo.
idJanela (entrada, passagem por valor năo-obrigatório): indica o número da janela a ser reposicionada.
********************************/
void SetPosicaoJanela(int posicaoX,int posicaoY,int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->SetPosicao(posicaoX,posicaoY);
}

/********************************
A funçăo SetPosicaoJanela() é responsável por recuperar a posiçăo de um janela na tela correspondente. A tela normalmente utiliza um sistema de coordenadas, cujo ponto (0,0) é o canto superior esquerdo.
Parâmetros:
posicaoX (saída, passagem por referęncia): indica o valor no eixo X (horizontal) da esquerda para direita.
posicaoY (saida, passagem por referęncia): indica o valor no eixo Y (vertical), normalmente de cima para baixo.
idJanela (entrada, passagem por valor năo-obrigatório): indica o número da janela a ser reposicionada.
********************************/
void GetPosicaoJanela(int *posicaoX,int *posicaoY,int idJanela=0){
    SDL_Point p = CPIGGerenciadorJanelas::GetJanela(idJanela)->GetXY();
    *posicaoX = p.x;
    *posicaoY = p.y;
}

/********************************
A funçăo SetBordaJanela() é responsável por definir se uma janela possuirá ou năo bordas visíveis. O valor de 0 (zero) indica ausęncia de borda, enquanto valores diferentes de zero indicam presença de borda.
Parâmetros:
valor (entrada, passagem por valor): indica se a janela possui borda (valor diferente de zero) ou năo (valor igual a zero).
idJanela (entrada, passagem por valor năo-obrigatório): indica o número da janela a ser reposicionada.
********************************/
void SetBordaJanela(int valor,int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->SetBorda(valor);
}

/********************************
A funçăo SetModoJanela() é responsável por definir o modo de exibiçăo de uma janela. A janela pode ser exibida em tręs diferentes modos: PIG_JANELA_NORMAL, que é o modo padrăo onde a janela ocupa o espaço da tela definido por sua altura e largura atual;
PIG_JANELA_TELACHEIA_DISPLAY, que é o modo no qual a janela fica em tela cheia com a resoluçăo idęntica ŕ da tela; PIG_JANELA_TELACHEIA, que é o modo onde a janela fica em tela cheia, mas com a resoluçăo atual mantida.
A tela cheia năo é acionada automaticamente com a combinçăo ALT+ENTER, é preciso executar o comando específico.
Parâmetros:
modo (entrada, passagem por valor): indica qual dos tręs modos (PIG_JANELA_NORMAL, PIG_JANELA_TELACHEIA, PIG_JANELA_TELACHEIA_DISPLAY) deve ser usado para exibir a janela.
idJanela (entrada, passagem por valor năo-obrigatório): indica o número da janela a ser reposicionada.
********************************/
void SetModoJanela(int modo,int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->SetModo(modo);
}

/********************************
A funçăo GetModoJanela() é responsável por recuperar o modo de exibiçăo de uma janela. A janela pode ser exibida em tręs diferentes modos: PIG_JANELA_NORMAL, que é o modo padrăo onde a janela ocupa o espaço da tela definido por sua altura e largura atual;
PIG_JANELA_TELACHEIA_DISPLAY, que é o modo no qual a janela fica em tela cheia com a resoluçăo idęntica ŕ da tela; PIG_JANELA_TELACHEIA, que é o modo onde a janela fica em tela cheia, mas com a resoluçăo atual mantida.
A tela cheia năo é acionada automaticamente com a combinaçăo ALT+ENTER, é preciso executar o comando específico.
Parâmetros:
idJanela (entrada, passagem por valor năo-obrigatório): indica o número da janela a ser reposicionada.
Retorno:
inteiro que indica qual dos tręs modos (PIG_JANELA_NORMAL, PIG_JANELA_TELACHEIA, PIG_JANELA_TELACHEIA_DISPLAY) está sendo usado para exibir a janela.
********************************/
int GetModoJanela(int idJanela=0){
    return CPIGGerenciadorJanelas::GetJanela(idJanela)->GetModo();
}


/********************************
Seçăo de controle de jogo
********************************/

/********************************
A funçăo BotaoPressionadoControle() é responsável por verificar se um determinado botăo do controle está ou năo pressionado.
Parâmetros:
idControle (entrada, passagem por valor): indica qual controle está sendo verificado.
botao (entrada, passagem por valor): indica qual botao está sendo verificado.
retono:
inteiro que representa se o botăo está pressionado (valor diferente de zero) ou está livre (valor igual a zero).
********************************/
int BotaoPressionadoControle(int idControle,int botao){
    return CPIGGerenciadorControles::GetControle(idControle)->BotaoPressionado(botao);
}

/********************************
A funçăo EixoAcionadoControle() é responsável por verificar o nível de acionamento de um eixo do controle. Essa funçăo pode ser utilizada
tanto para eixos analógicos, cujos valores săo de -32768 a 32767, ou gatilhos, cujos valores săo de 0 a 32767.
Parâmetros:
idControle (entrada, passagem por valor): indica qual controle está sendo verificado.
eixo (entrada, passagem por valor): indica qual eixo está sendo verificado.
retono:
inteiro que representa o nível de acionamento do eixo. Pode ser um valor negativo (eixos analógicos) ou valores positivos (eixos analógicos e gatilhos).
********************************/
int EixoAcionadoControle(int idControle,int eixo){
    return CPIGGerenciadorControles::GetControle(idControle)->EixoAcionado(eixo);
}

/********************************
A funçăo EixoAcionadoPercentualControle() é responsável por verificar o nível percentual de acionamento de um eixo do controle. Essa funçăo pode ser utilizada
tanto para eixos analógicos, cujos valores săo de -1.0 a 1.0, ou gatilhos, cujos valores săo de 0 a 1.0.
Parâmetros:
idControle (entrada, passagem por valor): indica qual controle está sendo verificado.
eixo (entrada, passagem por valor): indica qual eixo está sendo verificado.
retono:
número real que representa o nível percentual de acionamento do eixo. Pode ser um valor negativo (eixos analógicos) ou valores positivos (eixos analógicos e gatilhos).
********************************/
float EixoAcionadoPercentualControle(int idControle,int eixo){
    return CPIGGerenciadorControles::GetControle(idControle)->EixoAcionadoPercentual(eixo);
}

/********************************
A funçăo GetQtdEixosControle() é responsável por calcular quantos eixos e gatilhos estăo disponíveis no controle.
Parâmetros:
idControle (entrada, passagem por valor): indica qual controle está sendo verificado.
retono:
inteiro que representa a quantidade de eixos e gatilhos.
********************************/
int GetQtdEixosControle(int idControle){
    return CPIGGerenciadorControles::GetControle(idControle)->GetQtdEixos();
}

/********************************
A funçăo GetQtdBotoesControle() é responsável por calcular quantos botőes digitais (incluindo os direcionais) estăo disponíveis no controle.
Parâmetros:
idControle (entrada, passagem por valor): indica qual controle está sendo verificado.
retono:
inteiro que representa a quantidade de botőes digitais (incluindo os direcionais).
********************************/
int GetQtdBotoesControle(int idControle){
    return CPIGGerenciadorControles::GetControle(idControle)->GetQtdBotoes();
}

/********************************
A funçăo GetNomeControle() é responsável recuperar o nome com o qual o controle foi registrado no sistema.
Parâmetros:
idControle (entrada, passagem por valor): indica qual controle está sendo verificado.
nomeControle (saída, passagem por referęncia): armazena a string contendo o nome que foi recuperada para o controle.
********************************/
void GetNomeControle(int idControle,char *nomeControle){
    strcpy(nomeControle,CPIGGerenciadorControles::GetControle(idControle)->GetNome().c_str());
}


/********************************
Seçăo de elementos geométricos
********************************/

/********************************
A funçăo DesenhaLinhasSimples() é responsável por desenhar uma única linha, cujo início é o ponto (x1,y1) e o fim é o ponto (x2,y2).
Parâmetros:
pontoX1 (entrada, passagem por valor): inteiro que indica o início da linha no eixo X.
pontoY1 (entrada, passagem por valor): inteiro que indica o início da linha no eixo Y.
pontoX2 (entrada, passagem por valor): inteiro que indica o fim da linha no eixo X.
pontoY2 (entrada, passagem por valor): inteiro que indica o fim da linha no eixo Y.
cor (entrada, passagem por valor): indica a cor no sistema RGB para o desenho da linha.
idJanela (entrada, passagem por valor năo-obrigatório): indica o número da janela onde a linha será desenhada.
********************************/
void DesenhaLinhaSimples(int pontoX1,int pontoY1,int pontoX2,int pontoY2, PIG_Cor cor, int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaLinhaSimples(pontoX1,pontoY1,pontoX2,pontoY2,cor);
}

/********************************
A funçăo DesenhaLinhasDisjuntas() é responsável por desenhar linhas separadamente, ou seja, os ponto iniciais de cada linha estăo nas posiçőes pares e
os pontos finais estăo nas posiçőes ímpares. Assim, os vetores precisam ter tamanho qtdPontos*2.
Parâmetros:
pontosX (entrada, passagem por referęncia): vetor de inteiros, de tamanho qtdPontos*2, contendo os valores X (inicias e finais) de cada linha.
pontosY (entrada, passagem por referęncia): vetor de inteiros, de tamanho qtdPontos*2, contendo os valores Y (inicias e finais) de cada linha.
qtdPontos (entrada, passagem por valor): quantidade de linhas a serem desenhadas.
cor (entrada, passagem por valor): indica a cor no sistema RGB para o desenho das linhas.
idJanela (entrada, passagem por valor năo-obrigatório): indica o número da janela onde as linhas serăo desenhadas.
********************************/
void DesenhaLinhasDisjuntas(int pontosX[],int pontosY[],int qtdPontos, PIG_Cor cor, int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaLinhasDisjuntas(pontosX,pontosY,qtdPontos,cor);
}

/********************************
A funçăo DesenhaLinhasSequencia() é responsável por desenhar linhas em sequęncia, ou seja, o ponto final da primeira linha
corresponde ao ponto inicial da segunda linha.
Parâmetros:
pontosX (entrada, passagem por referęncia): vetor de inteiros, de tamanho qtdPontos+1, contendo os valores X de cada linha da sequęncia.
pontosY (entrada, passagem por referęncia): vetor de inteiros, de tamanho qtdPontos+1, contendo os valores Y de cada linha da sequęncia.
qtdPontos (entrada, passagem por valor): quantidade de linhas a serem desenhadas.
cor (entrada, passagem por valor): indica a cor no sistema RGB para o desenho das linhas.
idJanela (entrada, passagem por valor năo-obrigatório): indica o número da janela onde as linhas serăo desenhadas.
********************************/
void DesenhaLinhasSequencia(int pontosX[],int pontosY[],int qtdPontos, PIG_Cor cor, int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaLinhasSequencia(pontosX,pontosY,qtdPontos,cor);
}

/********************************
A funçăo DesenhaRetangulo() é responsável por desenhar um retângulo com preenchimento sólido na tela em uma posiçăo desejada pelo usuário.
O mesmo pode ser colocado em qualquer lugar do campo de visăo da tela.
Parâmetros:
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usuário deseja colocar o retângulo.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usuário deseja colocar o retângulo.
altura (entrada, passagem por valor): Valor onde o usuário irá fornecer o número correspondente em pixels ŕ altura desse retângulo.
largura (entrada, passagem por valor): Valor onde o usuário irá fornecer o número correspondente em pixels ŕ largura desse retângulo.
cor (entrada, passagem por valor): indica a cor no sistema RGB para o desenho do retângulo.
idJanela (entrada, passagem por valor năo-obrigatório): indica o número da janela onde o retângulo será desenhado.
********************************/
void DesenhaRetangulo(int posicaoX, int posicaoY, int altura, int largura, PIG_Cor cor, int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetangulo(posicaoX,posicaoY,altura,largura,cor);
}

/********************************
A funçăo DesenhaRetanguloVazado() é responsável por desenhar um retângulo sem preenchimento na tela em uma posiçăo desejada pelo usuário.
O mesmo pode ser colocado em qualquer lugar do campo de visăo da tela.
Parâmetros:
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usuário deseja colocar o retângulo.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usuário deseja colocar o retângulo.
altura (entrada, passagem por valor): Valor onde o usuário irá fornecer o número correspondente em pixels ŕ altura desse retângulo.
largura (entrada, passagem por valor): Valor onde o usuário irá fornecer o número correspondente em pixels ŕ largura desse retângulo.
cor (entrada, passagem por valor): indica a cor no sistema RGB para a borda do retângulo.
idJanela (entrada, passagem por valor năo-obrigatório): indica o número da janela onde o retângulo será desenhado.
********************************/
void DesenhaRetanguloVazado(int posicaoX, int posicaoY, int altura, int largura, PIG_Cor cor, int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetanguloVazado(posicaoX,posicaoY,altura,largura,cor);
}

/********************************
A funçăo DesenhaPoligono() é responsável por desenhar na janela um polígono de preenchimento sólido com o número de lados indicados. Os dois primeiros parâmetros indicam as coordenadas
de cada um dos vértices do polígono.
AVISO: essa funçăo utiliza o renderizador offscreen para gerar o polígono e posteriormente o renderiza na janela em questăo; isto pode fazer o FPS da aplicaçăo diminuir consideravelmente.
Parâmetros:
pontosX (entrada, passagem por referęncia): vetor de inteiros, de tamanho qtdPontos, contendo as coordenadas X de cada vértice do polígono.
pontosY (entrada, passagem por referęncia): vetor de inteiros, de tamanho qtdPontos, contendo as coordenadas Y de cada vértice do polígono.
qtdPontos (entrada, passagem por valor): quantidade de lados do polígono.
cor (entrada, passagem por valor): indica a cor no sistema RGB para o desenho do polígono.
idJanela (entrada, passagem por valor năo-obrigatório): indica o número da janela onde o polígono será desenhado.
********************************/
void DesenhaPoligono(int pontosX[],int pontosY[],int qtdPontos, PIG_Cor cor, int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaPoligono(pontosX,pontosY,qtdPontos,cor);
}


/********************************
Seçăo de desenho Offscreen
********************************/

/********************************
A funçăo PreparaOffScreenRenderer() serve para criar um novo bitmap offscreen que servirá de área
de desenho para outras funçőes que utilizem este bitmap.
Parâmetros:
altura (entrada, passagem por valor): indica a altura em pixels do novo bitmap.
largura (entrada, passagem por valor): indica a largura em pixels do novo bitmap.
********************************/
void PreparaOffScreenRenderer(int altura,int largura){
    jogo->PreparaOffScreenRenderer(altura,largura);
}

/********************************
A funçăo SalvaOffScreenBMP() serve para efetivamente salvar a imagem offscreen como um arquivo do sistema operacional.
A imagem offscreen continuará existindo em memória e açőes subsequentes ainda poderăo ser feitas. Para "limpar" a imagem
deve-se utilizar a funçăo PintaFundoOffScreen().
Parâmetros:
nomeArquivoBMP (entrada, passagem por referęncia*): indica com que nome a imagem offscreen será salva. O valor do parâmetro deve conter a extensăo ".bmp".
É utilizado o operador * apenas por se tratar de um parâmetro string. O valor do parâmetro năo é alterado dentro da funçăo.
********************************/
void SalvaOffScreenBMP(char *nomeArquivoBMP){
    jogo->GetOffScreenRender()->SalvarImagemBMP(nomeArquivoBMP);
}

/********************************
A funçăo SalvaOffScreenPNG() serve para efetivamente salvar a imagem offscreen como um arquivo do sistema operacional.
A imagem offscreen continuará existindo em memória e açőes subsequentes ainda poderăo ser feitas. Para "limpar" a imagem
deve-se utilizar a funçăo PintaFundoOffScreen().
Parâmetros:
nomeArquivoPNG (entrada, passagem por referęncia*): indica com que nome a imagem offscreen será salva. O valor do parâmetro deve conter a extensăo ".png".
É utilizado o operador * apenas por se tratar de um parâmetro string. O valor do parâmetro năo é alterado dentro da funçăo.
********************************/
void SalvaOffScreenPNG(char *nomeArquivoPNG){
    jogo->GetOffScreenRender()->SalvarImagemPNG(nomeArquivoPNG);
}

/********************************
A funçăo PintaAreaOffScreen() serve para mudar a cor de uma área contígua de pixels da mesma cor.
A funcionalidade é semelhante ŕ ferramenta "balde" dos editores de imagem. A área será pintada a partir do
ponto (posicaoX,posicaoY) de acordo com o sistema de coordenadas da PIG. A funçăo de pintura padrăo pode ser
substituída por outra funçăo customizada qualquer com o comando DefineFuncaoPintarAreaOffscreen().
Parâmetros:
posicaoX (entrada, passagem por valor): indica o ponto no eixo X para começar a pintar a área contígua de pixels.
posicaoY (entrada, passagem por valor): indica o ponto no eixo Y para começar a pintar a área contígua de pixels.
cor (entrada, passagem por valor): indica a cor que deve ser usada durante a pintura da área contígua de pixels.
ponteiro (entrada, passagem por referęncia): ponteiro para qualquer tipo de estrutura a ser usada na funçăo customizada de pintura da área.
********************************/
void PintaAreaOffScreen(int posicaoX,int posicaoY,PIG_Cor cor,void *ponteiro=NULL){
    jogo->GetOffScreenRender()->PintarArea(posicaoX,posicaoY,cor,ponteiro);
}

/********************************
A funçăo DefineFuncaoPintarAreaOffScreen() permite substituir a funçăo padrăo de pintura por outra funçăo customizada que deve ser passada como parâmetro.
A funçăo de pintura deve ser definida de forma que receba 4 parâmetros inteiros (respectivamente, a posiçăo x e y do pixel que deve ser pintado e as
dimensőes - altura e largura - da imagem offscreen) e 2 cores (a cor atual do pixel e a cor que deveria ser usada para pintá-lo). A funçăo deve também retornar
o valor de uma cor, que será a cor efetivamente utilizada para pintar o pixel em questăo. A funçăo, portanto, deve definir para cada ponto solicitado qual a cor
final daquele ponto.
Parâmetros:
funcao (entrada, passagem por referęncia): nome da funçăo customizada para pintar uma área no renderizador offscreen.
********************************/
void DefineFuncaoPintarAreaOffscreen(PIG_Cor (*funcao)(int,int,int,int,PIG_Cor,PIG_Cor)){
    jogo->GetOffScreenRender()->DefineFuncaoPintarArea(funcao);
}

/********************************
A funçăo MoveCanetaOffScreen() reposiciona a caneta do renderizador offscreen em algum outro ponto da imagem.
Parâmetros:
novoX (entrada, passagem por valor): nova posiçăo no eixo X na qual a caneta será reposicionada. O tipo de parâmetro é double mas será convertido para int, dentro da funçăo.
novoY (entrada, passagem por valor): nova posiçăo no eixo Y na qual a caneta será reposicionada. O tipo de parâmetro é dpuble mas será convertido para int, dentro da funçăo.
********************************/
void MoveCanetaOffscreen(double novoX,double novoY){
    jogo->GetOffScreenRender()->MoveCanetaPara(novoX,novoY);
}

/********************************
A funçăo AvancaCanetaOffScreen() cria uma linha no renderizador offscreen na direçăo e sentido nos quais a canete está orientada.
Parâmetros:
distancia (entrada, passagem por valor): distância a ser percorrida pela caneta. O tipo de parâmetro é double para permitir que o cálculo da distância seja feito livremente.
********************************/
void AvancaCanetaOffscreen(double distancia){
    jogo->GetOffScreenRender()->AvancaCaneta(distancia);
}

/********************************
A funçăo MudaCorCanetaOffScreen() modifica a cor a ser utilizada pela caneta do renderizador offscreen daqui por diante. Desenhos feitos anteriormente permancem com a cor com a qual foram feitos.
Parâmetros:
novaCor (entrada, passagem por valor): valor da nova cor a ser utilizada pela caneta do renderizador offscreen.
********************************/
void MudaCorCanetaOffscreen(PIG_Cor novaCor){
    jogo->GetOffScreenRender()->MudaCorAtualCaneta(novaCor);
}

/********************************
A funçăo GiraCanetaHorarioOffScreen() gira a caneta do renderizador offscreen. A caneta passa a ter uma nova direçăo e sentido. Se o comando AvancaCanetaOffscreen() for executado posteriormente,
esses novos valores de direçăo e sentido serăo utilizados para que o ponto final do traço seja calculado.
Parâmetros:
angulo (entrada, passagem por valor): valor do ângulo (sentido horário, em radianos) pelo qual a caneta será redirecionada.
********************************/
void GiraCanetaHorarioOffscreen(double angulo){
    jogo->GetOffScreenRender()->GiraCanetaHorario(angulo);
}

/********************************
A funçăo GiraCanetaAntiHorarioOffScreen() gira a caneta do renderizador offscreen. A caneta passa a ter uma nova direçăo e sentido. Se o comando AvancaCanetaOffscreen() for executado posteriormente,
esses novos valores de direçăo e sentido serăo utilizados para que o ponto final do traço seja calculado.
Parâmetros:
angulo (entrada, passagem por valor): valor do ângulo (sentido anti-horário, em radianos) pelo qual a caneta será redirecionada.
********************************/
void GiraCanetaAntiHorarioOffscreen(double angulo){
    jogo->GetOffScreenRender()->GiraCanetaAntiHorario(angulo);
}

/********************************
A funçăo GiraCanetaAnguloFixoOffScreen() gira a caneta do renderizador offscreen. A caneta passa a ter uma nova direçăo e sentido. Se o comando AvancaCanetaOffscreen() for executado posteriormente,
esses novos valores de direçăo e sentido serăo utilizados para que o ponto final do traço seja calculado.
Parâmetros:
angulo (entrada, passagem por valor): valor do ângulo usando como referęncia o ângulo 0 do círculo trigonométrico.
********************************/
void GiraCanetaAnguloFixoOffscreen(double angulo){
    jogo->GetOffScreenRender()->GiraAnguloFixo(angulo);
}

/********************************
A funçăo GetAnguloAtualOffScreen() recupera o ângulo atual que está sendo usado pela caneta do renderizador offscreen.
Retorno:
número real que representa o valor do ângulo atual, tendo como referęncia o ângulo 0 do círculo trigonométrico.
********************************/
double GetAnguloAtualOffscreen(){
    return jogo->GetOffScreenRender()->GetAngAtual();
}

/********************************
A funçăo GetXCanetaOffScreen() recupera a posiçăo no eixo X na qual está posicionada atualmente a caneta do renderizador offscreen.
Retorno:
inteiro que representa a posiçăo atual da caneta no eixo X.
********************************/
int GetXCanetaOffscreen(){
    return jogo->GetOffScreenRender()->GetXCaneta();
}

/********************************
A funçăo GetYCanetaOffScreen() recupera a posiçăo no eixo Y na qual está posicionada atualmente a caneta do renderizador offscreen.
Retorno:
inteiro que representa a posiçăo atual da caneta no eixo Y.
********************************/
int GetYCanetaOffscreen(){
    return jogo->GetOffScreenRender()->GetYCaneta();
}

/********************************
A funçăo PintaFundoOffScreen() serve para "limpar" o bitmap offscreen, mudando completamente para cor indicada.
Parâmetros:
cor (entrada, passagem por valor): indica a cor que deve ser usada durante a pintura completa do bitmap offscreen.
********************************/
void PintaFundoOffScreen(PIG_Cor cor){
    jogo->GetOffScreenRender()->PintarFundo(cor);
}

/********************************
A funçăo DesenhaRetanguloOffScreen() é responsável por desenhar um retângulo cem preenchimento sólido no bitmap offscreen em uma posiçăo desejada pelo usuário.
O sistema de coordenadas é o mesmo da tela, com o eixo Y aumentando para cima.
Parâmetros:
posicaoX (entrada, passagem por valor): Valor da coordenada X onde o usuário deseja colocar o retângulo.
posicaoY (entrada, passagem por valor): Valor da coordenada Y onde o usuário deseja colocar o retângulo.
altura (entrada, passagem por valor): Valor onde o usuário irá fornecer o número correspondente em pixels ŕ altura desse retângulo.
largura (entrada, passagem por valor): Valor onde o usuário irá fornecer o número correspondente em pixels ŕ largura desse retângulo.
cor (entrada, passagem por valor): indica a cor no sistema RGB para o preenchimento do retângulo.
********************************/
void DesenhaRetanguloOffScreen(int x1,int y1,int altura,int largura,PIG_Cor cor){
    jogo->GetOffScreenRender()->DesenharRetangulo(x1,y1,altura,largura,cor);
}

/********************************
A funçăo DesenhaRetanguloVazadoOffScreen() é responsável por desenhar um retângulo sem preenchimento no bitmap offscreen em uma posiçăo desejada pelo usuário.
O sistema de coordenadas é o mesmo da tela, com o eixo Y aumentando para cima.
Parâmetros:
posicaoX (entrada, passagem por valor): Valor da coordenada X onde o usuário deseja colocar o retângulo.
posicaoY (entrada, passagem por valor): Valor da coordenada Y onde o usuário deseja colocar o retângulo.
altura (entrada, passagem por valor): Valor onde o usuário irá fornecer o número correspondente em pixels ŕ altura desse retângulo.
largura (entrada, passagem por valor): Valor onde o usuário irá fornecer o número correspondente em pixels ŕ largura desse retângulo.
cor (entrada, passagem por valor): indica a cor no sistema RGB para a borda do retângulo.
********************************/
void DesenhaRetanguloVazadoOffScreen(int x1,int y1,int altura,int largura,PIG_Cor cor){
    jogo->GetOffScreenRender()->DesenharRetanguloVazado(x1,y1,altura,largura,cor);
}

/********************************
A funçăo DesenhaLinhasSimplesOffScreen() é responsável por desenhar no bitmap offscreen uma única linha, cuja início é o ponto (x1,y1) e o fim é o ponto (x2,y2).
Parâmetros:
pontoX1 (entrada, passagem por valor): inteiro que indica o início da linha no eixo X.
pontoY1 (entrada, passagem por valor): inteiro que indica o início da linha no eixo Y.
pontoX2 (entrada, passagem por valor): inteiro que indica o fim da linha no eixo X.
pontoY2 (entrada, passagem por valor): inteiro que indica o fim da linha no eixo Y.
cor (entrada, passagem por valor): indica a cor no sistema RGB para o desenho das linhas.
********************************/
void DesenhaLinhaSimplesOffScreen(int x1,int y1,int x2,int y2,PIG_Cor cor){
    jogo->GetOffScreenRender()->DesenharLinha(x1,y1,x2,y2,cor);
}

/********************************
A funçăo DesenhaLinhasDisjuntasOffScreen() é responsável por desenhar no bitmap offscreen linhas separadamente, ou seja, os ponto iniciais de cada linha estăo nas posiçőes pares e
os pontos finais estăo nas posiçőes ímpares. Assim, os vetores precisam ter tamanho qtdPontos*2.
Parâmetros:
pontosX (entrada, passagem por referęncia): vetor de inteiros, de tamanho qtdPontos*2, contendo os valores X (inicias e finais) de cada linha.
pontosY (entrada, passagem por referęncia): vetor de inteiros, de tamanho qtdPontos*2, contendo os valores Y (inicias e finais) de cada linha.
qtdPontos (entrada, passagem por valor): quantidade de linhas a serem desenhadas.
cor (entrada, passagem por valor): indica a cor no sistema RGB para o desenho das linhas.
********************************/
void DesenhaLinhasDisjuntasOffScreen(int pontosX[],int pontosY[],int qtdPontos, PIG_Cor cor){
    jogo->GetOffScreenRender()->DesenhaLinhasDisjuntas(pontosX,pontosY,qtdPontos,cor);
}

/********************************
A funçăo DesenhaLinhasSequenciaOffScreen() é responsável por desenhar no bitmap offscreen linhas em sequęncia, ou seja, o ponto final da primeira linha
corresponde ao ponto inicial da segunda linha.
Parâmetros:
pontosX (entrada, passagem por referęncia): vetor de inteiros, de tamanho qtdPontos+1, contendo os valores X de cada linha da sequęncia.
pontosY (entrada, passagem por referęncia): vetor de inteiros, de tamanho qtdPontos+1, contendo os valores Y de cada linha da sequęncia.
qtdPontos (entrada, passagem por valor): quantidade de linhas a serem desenhadas.
cor (entrada, passagem por valor): indica a cor no sistema RGB para o desenho das linhas.
********************************/
void DesenhaLinhasSequenciaOffScreen(int pontosX[],int pontosY[],int qtdPontos, PIG_Cor cor){
    jogo->GetOffScreenRender()->DesenhaLinhasSequencia(pontosX,pontosY,qtdPontos,cor);
}


///escrever

/********************************
Seçăo de fontes
********************************/

/********************************
A funçăo CriaFonteNormal() é responsável por disponibilizar uma nova fonte com preenchimento sólido.
Parâmetros:
nome (entrada, passagem por referęncia): nome do arquivo que contém a fonte (normalmente com extensăo ttf).
tamanho (entrada, passagem por valor): tamanho da fonte, que normalmente representa a altura média (em pixels) dos caracteres da fonte.
corLetra (entrada, passagem por valor): representa a cor de preenchimento da fonte.
contorno (entrada, passagem por valor): representa a espessura do contorno que fonte terá. Caso năo seja desejado um contorno, basta utilizar um valor 0.
corContorno (entrada, passagem por valor): representa a cor do contorno da fonte.
estilo (entrada, passagem por valor): representa o estilo da fonte. Pode ser uma combinaçăo binária de: PIG_ESTILO_NEGRITO, para negrito; PIG_ESTILO_SUBLINHADO, para sublinhado; PIG_ESTILO_ITALICO, para itálico;
PIG_ESTILO_CORTADO, para uma linha horizontal ŕ meia-altura. Caso nenhum estilo seja desejado, pode ser omitido ou usado PIG_ESTILO_NORMAL.
idJanela (entrada, passagem por valor năo-obrigatório): indica qual janela vai receber a fonte. Uma fonte só pode ser usada na janela na qual foi criada.
retono:
inteiro que representa a ideintificaçăo única da fonte. Futuras referęncia a esta fonte devem idenitificá-las pelo número.
********************************/
int CriaFonteNormal(char *nome,int tamanho,PIG_Cor corLetra,int contorno,PIG_Cor corContorno,PIG_Estilo estilo=PIG_ESTILO_NORMAL,int idJanela=0){
    return CPIGGerenciadorFontes::CriaFonteNormal(nome,tamanho,estilo,corLetra,contorno,corContorno,idJanela);
}

/********************************
A funçăo CriaFonteNormal() é responsável por disponibilizar uma nova fonte com preenchimento sólido.
Parâmetros:
nome (entrada, passagem por referęncia): nome do arquivo que contém a fonte (normalmente com extensăo ttf).
tamanho (entrada, passagem por valor): tamanho da fonte, que normalmente representa a altura média (em pixels) dos caracteres da fonte.
corLetra (entrada, passagem por valor): representa a cor de preenchimento da fonte. Caso a cor năo seja informada, será utilizada a cor padrăo (BRANCO).
estilo (entrada, passagem por valor): representa o estilo da fonte. Pode ser uma combinaçăo binária de: PIG_ESTILO_NEGRITO, para negrito; PIG_ESTILO_SUBLINHADO, para sublinhado; PIG_ESTILO_ITALICO, para itálico;
PIG_ESTILO_CORTADO, para uma linha horizontal ŕ meia-altura. Caso nenhum estilo seja desejado, pode ser omitido ou usado PIG_ESTILO_NORMAL.
idJanela (entrada, passagem por valor năo-obrigatório): indica qual janela vai receber a fonte. Uma fonte só pode ser usada na janela na qual foi criada.
retono:
inteiro que representa a ideintificaçăo única da fonte. Futuras referęncia a esta fonte devem idenitificá-las pelo número.
********************************/
int CriaFonteNormal(char *nome,int tamanho,PIG_Cor corLetra=PIG_FONTE_PADRAO_COR,PIG_Estilo estilo=PIG_ESTILO_NORMAL,int idJanela=0){
    return CPIGGerenciadorFontes::CriaFonteNormal(nome,tamanho,estilo,corLetra,idJanela);
}

/********************************
A funçăo CriaFonteDinamica() é responsável por disponibilizar uma nova fonte dinâmica com preenchimento sólido. As fontes dinâmicas săo capazes
de escrever strings com diferentes formataçőes (negrito, itálico, sublinhado, cortado) e cores nas letras. A string a ser utilizada pela fonte
pode conter ou năo os marcadores de formtaçăo. Caso năo contenham, será utilizada uma letra branca, sem formataçăo.
Parâmetros:
nome (entrada, passagem por referęncia): nome do arquivo que contém a fonte (normalmente com extensăo ttf).
tamanho (entrada, passagem por valor): tamanho da fonte, que normalmente representa a altura média (em pixels) dos caracteres da fonte.
idJanela (entrada, passagem por valor năo-obrigatório): indica qual janela vai receber a fonte. Uma fonte só pode ser usada na janela na qual foi criada.
retono:
inteiro que representa a ideintificaçăo única da fonte. Futuras referęncia a esta fonte devem idenitificá-las pelo número.
********************************/
int CriaFonteDinamica(char *nome,int tamanho,int idJanela=0){
    return CPIGGerenciadorFontes::CriaFonteDinamica(nome,tamanho,idJanela);
}

/********************************
A funçăo CriaFonteFundo() é responsável por disponibilizar uma nova fonte com preenchimento de um bitmap específico.
Parâmetros:
nome (entrada, passagem por referęncia): nome do arquivo que contém a fonte (normalmente com extensăo ttf).
tamanho (entrada, passagem por valor): tamanho da fonte, que normalmente representa a altura média (em pixels) dos caracteres da fonte.
arquivoFundo (entrada, passagem por referęncia): indica o nome do arquivo de imagem que servirá de fundo para a fonte.
contorno (entrada, passagem por valor): representa a espessura do contorno que fonte terá. Caso năo seja desejado um contorno, basta utilizar um valor 0.
corContorno (entrada, passagem por valor): representa a cor do contorno da fonte.
estilo (entrada, passagem por valor): representa o estilo da fonte. Pode ser uma combinaçăo binária de: PIG_ESTILO_NEGRITO, para negrito; PIG_ESTILO_SUBLINHADO, para sublinhado; PIG_ESTILO_ITALICO, para itálico;
PIG_ESTILO_CORTADO, para uma linha horizontal ŕ meia-altura. Caso nenhum estilo seja desejado, pode ser omitido ou usado PIG_ESTILO_NORMAL.
idJanela (entrada, passagem por valor năo-obrigatório): indica qual janela vai receber a fonte. Uma fonte só pode ser usada na janela na qual foi criada.
retono:
inteiro que representa a ideintificaçăo única da fonte. Futuras referęncia a esta fonte devem idenitificá-las pelo número.
********************************/
int CriaFonteFundo(char *nome,int tamanho,char *arquivoFundo,int contorno,PIG_Cor corContorno,PIG_Estilo estilo=PIG_ESTILO_NORMAL,int idJanela=0){
    return CPIGGerenciadorFontes::CriaFonteFundo(nome,tamanho,estilo,arquivoFundo,contorno,corContorno,idJanela);
}

/********************************
A funçăo CriaFonteFundo() é responsável por disponibilizar uma nova fonte com preenchimento de um bitmap específico.
Parâmetros:
nome (entrada, passagem por referęncia): nome do arquivo que contém a fonte (normalmente com extensăo ttf).
tamanho (entrada, passagem por valor): tamanho da fonte, que normalmente representa a altura média (em pixels) dos caracteres da fonte.
arquivoFundo (entrada, passagem por referęncia): indica o nome do arquivo de imagem que servirá de fundo para a fonte.
estilo (entrada, passagem por valor): representa o estilo da fonte. Pode ser uma combinaçăo binária de: PIG_ESTILO_NEGRITO, para negrito; PIG_ESTILO_SUBLINHADO, para sublinhado; PIG_ESTILO_ITALICO, para itálico;
PIG_ESTILO_CORTADO, para uma linha horizontal ŕ meia-altura. Caso nenhum estilo seja desejado, pode ser omitido ou usado PIG_ESTILO_NORMAL.
idJanela (entrada, passagem por valor năo-obrigatório): indica qual janela vai receber a fonte. Uma fonte só pode ser usada na janela na qual foi criada.
retono:
inteiro que representa a ideintificaçăo única da fonte. Futuras referęncia a esta fonte devem idenitificá-las pelo número.
********************************/
int CriaFonteFundo(char *nome,int tamanho,char *arquivoFundo,PIG_Estilo estilo=PIG_ESTILO_NORMAL,int idJanela=0){
    return CPIGGerenciadorFontes::CriaFonteFundo(nome,tamanho,estilo,arquivoFundo,idJanela);
}


/********************************
A funçăo CriaFonteNormalOffscreen() é responsável por disponibilizar uma nova fonte com preenchimento sólido.
Parâmetros:
nome (entrada, passagem por referęncia): nome do arquivo que contém a fonte (normalmente com extensăo ttf).
tamanho (entrada, passagem por valor): tamanho da fonte, que normalmente representa a altura média (em pixels) dos caracteres da fonte.
corLetra (entrada, passagem por valor): representa a cor de preenchimento da fonte.
contorno (entrada, passagem por valor): representa a espessura do contorno que fonte terá. Caso năo seja desejado um contorno, basta utilizar um valor 0.
corContorno (entrada, passagem por valor): representa a cor do contorno da fonte.
estilo (entrada, passagem por valor): representa o estilo da fonte. Pode ser uma combinaçăo binária de: PIG_ESTILO_NEGRITO, para negrito; PIG_ESTILO_SUBLINHADO, para sublinhado; PIG_ESTILO_ITALICO, para itálico;
PIG_ESTILO_CORTADO, para uma linha horizontal ŕ meia-altura. Caso nenhum estilo seja desejado, pode ser omitido ou usado PIG_ESTILO_NORMAL.
retono:
inteiro que representa a ideintificaçăo única da fonte. Futuras referęncia a esta fonte devem idenitificá-las pelo número.
********************************/
int CriaFonteNormalOffscreen(char *nome,int tamanho,PIG_Cor corLetra,int contorno,PIG_Cor corContorno,PIG_Estilo estilo=PIG_ESTILO_NORMAL){
    return CPIGGerenciadorFontes::CriaFonteNormalOffScreen(nome,tamanho,estilo,corLetra,contorno,corContorno,jogo->GetOffScreenRender(),0);
}

/********************************
A funçăo CriaFonteNormalOffscreen() é responsável por disponibilizar uma nova fonte com preenchimento sólido.
Parâmetros:
nome (entrada, passagem por referęncia): nome do arquivo que contém a fonte (normalmente com extensăo ttf).
tamanho (entrada, passagem por valor): tamanho da fonte, que normalmente representa a altura média (em pixels) dos caracteres da fonte.
corLetra (entrada, passagem por valor): representa a cor de preenchimento da fonte. Caso a cor năo seja informada, será utilizada a cor padrăo (BRANCO).
estilo (entrada, passagem por valor): representa o estilo da fonte. Pode ser uma combinaçăo binária de: PIG_ESTILO_NEGRITO, para negrito; PIG_ESTILO_SUBLINHADO, para sublinhado; PIG_ESTILO_ITALICO, para itálico;
PIG_ESTILO_CORTADO, para uma linha horizontal ŕ meia-altura. Caso nenhum estilo seja desejado, pode ser omitido ou usado PIG_ESTILO_NORMAL.
retono:
inteiro que representa a ideintificaçăo única da fonte. Futuras referęncia a esta fonte devem idenitificá-las pelo número.
********************************/
int CriaFonteNormalOffscreen(char *nome,int tamanho,PIG_Cor corLetra=PIG_FONTE_PADRAO_COR,PIG_Estilo estilo=PIG_ESTILO_NORMAL){
    return CPIGGerenciadorFontes::CriaFonteNormalOffScreen(nome,tamanho,estilo,jogo->GetOffScreenRender(),corLetra,0);
}


/********************************
A funçăo CriaFonteFundoOffscreen() é responsável por disponibilizar uma nova fonte com preenchimento de um bitmap específico.
Parâmetros:
nome (entrada, passagem por referęncia): nome do arquivo que contém a fonte (normalmente com extensăo ttf).
tamanho (entrada, passagem por valor): tamanho da fonte, que normalmente representa a altura média (em pixels) dos caracteres da fonte.
arquivoFundo (entrada, passagem por referęncia): indica o nome do arquivo de imagem que servirá de fundo para a fonte.
contorno (entrada, passagem por valor): representa a espessura do contorno que fonte terá. Caso năo seja desejado um contorno, basta utilizar um valor 0.
corContorno (entrada, passagem por valor): representa a cor do contorno da fonte.
estilo (entrada, passagem por valor): representa o estilo da fonte. Pode ser uma combinaçăo binária de: PIG_ESTILO_NEGRITO, para negrito; PIG_ESTILO_SUBLINHADO, para sublinhado; PIG_ESTILO_ITALICO, para itálico;
PIG_ESTILO_CORTADO, para uma linha horizontal ŕ meia-altura. Caso nenhum estilo seja desejado, pode ser omitido ou usado PIG_ESTILO_NORMAL.
retono:
inteiro que representa a ideintificaçăo única da fonte. Futuras referęncia a esta fonte devem idenitificá-las pelo número.
********************************/
int CriaFonteFundoOffscreen(char *nome,int tamanho,char *arquivoFundo,int contorno,PIG_Cor corContorno,PIG_Estilo estilo=PIG_ESTILO_NORMAL){
    return CPIGGerenciadorFontes::CriaFonteFundoOffScreen(nome,tamanho,estilo,arquivoFundo,contorno,corContorno,jogo->GetOffScreenRender(),0);
}

/********************************
A funçăo CriaFonteFundoOffscreen() é responsável por disponibilizar uma nova fonte com preenchimento de um bitmap específico.
Parâmetros:
nome (entrada, passagem por referęncia): nome do arquivo que contém a fonte (normalmente com extensăo ttf).
tamanho (entrada, passagem por valor): tamanho da fonte, que normalmente representa a altura média (em pixels) dos caracteres da fonte.
arquivoFundo (entrada, passagem por referęncia): indica o nome do arquivo de imagem que servirá de fundo para a fonte.
estilo (entrada, passagem por valor): representa o estilo da fonte. Pode ser uma combinaçăo binária de: PIG_ESTILO_NEGRITO, para negrito; PIG_ESTILO_SUBLINHADO, para sublinhado; PIG_ESTILO_ITALICO, para itálico;
PIG_ESTILO_CORTADO, para uma linha horizontal ŕ meia-altura. Caso nenhum estilo seja desejado, pode ser omitido ou usado PIG_ESTILO_NORMAL.
retono:
inteiro que representa a ideintificaçăo única da fonte. Futuras referęncia a esta fonte devem idenitificá-las pelo número.
********************************/
int CriaFonteFundoOffscreen(char *nome,int tamanho,char *arquivoFundo,PIG_Estilo estilo=PIG_ESTILO_NORMAL){
    return CPIGGerenciadorFontes::CriaFonteFundoOffScreen(nome,tamanho,estilo,arquivoFundo,jogo->GetOffScreenRender(),0);
}

/********************************
A funçăo CalculaLarguraPixels() é responsável por realizar a soma das larguras de cada letra da string informada.
Parâmetros:
str (entrada, passagem por referęncia): string a ser escrita na tela.
numFonte (entrada, passagem por valor): número da fonte a ser utilizada. Caso o usuário năo deseje uma fonte especial, será utilizada a fonte padrăo (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
retorno:
inteiro que representa o total de pixels (no eixo x) necessários para escrever a string.
********************************/
int CalculaLarguraPixels(char *str,int numFonte=0){
    return CPIGGerenciadorFontes::GetFonte(numFonte)->GetLarguraPixelsString(str);
}

/********************************
A funçăo EscreverDireita() é responsável por exibir uma string na tela de jogo, com alinhamento ŕ direita do valor de X.
Parâmetros:
str (entrada, passagem por referęncia): string a ser escrita na tela.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usuário deseja começar a escrever a string.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usuário deseja começar a escrever a string.
cor (entrada, passagem por valor): cor a ser aplicada ŕ fonte no momento da escrita. Essa cor é misturada ŕ cor original da fonte, se essa tiver sido informada na criaçăo da fonte.
numFonte (entrada, passagem por valor): número da fonte a ser utilizada. Caso o usuário năo deseje uma fonte especial, será utilizada a fonte padrăo (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
angulo (entrada, passagem por valor): ângulo, em graus, para a rotaçăo da string.
********************************/
void EscreverDireita(char *str,int posicaoX,int posicaoY,PIG_Cor cor=BRANCO,int numFonte=0,float angulo=0){
    CPIGGerenciadorFontes::GetFonte(numFonte)->Escreve(str,posicaoX,posicaoY,cor,PIG_TEXTO_DIREITA,angulo);
}

/********************************
A funçăo EscreverEsquerda() é responsável por exibir uma string na tela de jogo, com alinhamento ŕ esquerda do valor de X.
Parâmetros:
str (entrada, passagem por referęncia): string a ser escrita na tela.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usuário deseja começar a escrever a string.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usuário deseja começar a escrever a string.
cor (entrada, passagem por valor): cor a ser aplicada ŕ fonte no momento da escrita. Essa cor é misturada ŕ cor original da fonte, se essa tiver sido informada na criaçăo da fonte.
numFonte (entrada, passagem por valor): número da fonte a ser utilizada. Caso o usuário năo deseje uma fonte especial, será utilizada a fonte padrăo (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
angulo (entrada, passagem por valor): ângulo, em graus, para a rotaçăo da string.
********************************/
void EscreverEsquerda(char *str,int posicaoX,int posicaoY,PIG_Cor cor=BRANCO,int numFonte=0,float angulo=0){
    CPIGGerenciadorFontes::GetFonte(numFonte)->Escreve(str,posicaoX,posicaoY,cor,PIG_TEXTO_ESQUERDA,angulo);
}

/********************************
A funçăo EscreverCentralizada() é responsável por exibir uma string na tela de jogo, com alinhamento em relaçăo ao valor de X.
Parâmetros:
str (entrada, passagem por referęncia): string a ser escrita na tela.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usuário deseja começar a escrever a string.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usuário deseja começar a escrever a string.
cor (entrada, passagem por valor): cor a ser aplicada ŕ fonte no momento da escrita. Essa cor é misturada ŕ cor original da fonte, se essa tiver sido informada na criaçăo da fonte.
numFonte (entrada, passagem por valor): número da fonte a ser utilizada. Caso o usuário năo deseje uma fonte especial, será utilizada a fonte padrăo (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
angulo (entrada, passagem por valor): ângulo, em graus, para a rotaçăo da string.
********************************/
void EscreverCentralizada(char *str,int posicaoX,int posicaoY,PIG_Cor cor=BRANCO,int numFonte=0,float angulo=0){
    CPIGGerenciadorFontes::GetFonte(numFonte)->Escreve(str,posicaoX,posicaoY,cor,PIG_TEXTO_CENTRO,angulo);
}

/********************************
A funçăo EscreverLongaEsquerda() é responsável por exibir uma string longa na tela de jogo, com alinhamento ŕ esquerda do valor de X.
A string se expande palavra por palavra até a largura máxima definida (maxLarg). Se ainda houver palavras, elas serăo escritas na linha abaixo,
tendo um espaçamento entre as linhas (espacoEntreLinhas) também definido por parâmetro.
Parâmetros:
str (entrada, passagem por referęncia): string a ser escrita na tela.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usuário deseja começar a escrever a string.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usuário deseja começar a escrever a string.
largMax (entrada, passagem por valor): largura máxima em pixels que pode ser utilizada para escrever as palavras em cada linha do texto. ao atingir esse limite, as palavras seguintes săo escritas na linha abaixo.
espacoEntreLinhas (entrada, passagem por valor): distância em pixels entre o valor Y de uma linha e o valor Y da linha abaixo.
cor (entrada, passagem por valor): cor a ser aplicada ŕ fonte no momento da escrita. Essa cor é misturada ŕ cor original da fonte, se essa tiver sido informada na criaçăo da fonte.
numFonte (entrada, passagem por valor): número da fonte a ser utilizada. Caso o usuário năo deseje uma fonte especial, será utilizada a fonte padrăo (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
angulo (entrada, passagem por valor): ângulo, em graus, para a rotaçăo das strings.
********************************/
void EscreverLongaEsquerda(char *str,int posicaoX,int posicaoY,int largMax,int espacoEntreLinhas,PIG_Cor cor=BRANCO,int numFonte=0,float angulo=0){
    CPIGGerenciadorFontes::GetFonte(numFonte)->EscreveLonga(str,posicaoX,posicaoY,largMax,espacoEntreLinhas,cor,PIG_TEXTO_ESQUERDA,angulo);
}

/********************************
A funçăo EscreverLongaDireita() é responsável por exibir uma string longa na tela de jogo, com alinhamento ŕ direita do valor de X.
A string se expande palavra por palavra até a largura máxima definida (maxLarg). Se ainda houver palavras, elas serăo escritas na linha abaixo,
tendo um espaçamento entre as linhas (espacoEntreLinhas) também definido por parâmetro.
Parâmetros:
str (entrada, passagem por referęncia): string a ser escrita na tela.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usuário deseja começar a escrever a string.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usuário deseja começar a escrever a string.
largMax (entrada, passagem por valor): largura máxima em pixels que pode ser utilizada para escrever as palavras em cada linha do texto. ao atingir esse limite, as palavras seguintes săo escritas na linha abaixo.
espacoEntreLinhas (entrada, passagem por valor): distância em pixels entre o valor Y de uma linha e o valor Y da linha abaixo.
cor (entrada, passagem por valor): cor a ser aplicada ŕ fonte no momento da escrita. Essa cor é misturada ŕ cor original da fonte, se essa tiver sido informada na criaçăo da fonte.
numFonte (entrada, passagem por valor): número da fonte a ser utilizada. Caso o usuário năo deseje uma fonte especial, será utilizada a fonte padrăo (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
angulo (entrada, passagem por valor): ângulo, em graus, para a rotaçăo das strings.
********************************/
void EscreverLongaDireita(char *str,int posicaoX,int posicaoY,int largMax,int espacoEntreLinhas,PIG_Cor cor=BRANCO,int numFonte=0,float angulo=0){
    CPIGGerenciadorFontes::GetFonte(numFonte)->EscreveLonga(str,posicaoX,posicaoY,largMax,espacoEntreLinhas,cor,PIG_TEXTO_DIREITA,angulo);
}

/********************************
A funçăo EscreverLongaCentralizada() é responsável por exibir uma string longa na tela de jogo, com alinhamento em relaçăo ao valor de X.
A string se expande palavra por palavra até a largura máxima definida (maxLarg). Se ainda houver palavras, elas serăo escritas na linha abaixo,
tendo um espaçamento entre as linhas (espacoEntreLinhas) também definido por parâmetro.
Parâmetros:
str (entrada, passagem por referęncia): string a ser escrita na tela.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usuário deseja começar a escrever a string.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usuário deseja começar a escrever a string.
largMax (entrada, passagem por valor): largura máxima em pixels que pode ser utilizada para escrever as palavras em cada linha do texto. ao atingir esse limite, as palavras seguintes săo escritas na linha abaixo.
espacoEntreLinhas (entrada, passagem por valor): distância em pixels entre o valor Y de uma linha e o valor Y da linha abaixo.
cor (entrada, passagem por valor): cor a ser aplicada ŕ fonte no momento da escrita. Essa cor é misturada ŕ cor original da fonte, se essa tiver sido informada na criaçăo da fonte.
numFonte (entrada, passagem por valor): número da fonte a ser utilizada. Caso o usuário năo deseje uma fonte especial, será utilizada a fonte padrăo (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
angulo (entrada, passagem por valor): ângulo, em graus, para a rotaçăo das strings.
********************************/
void EscreverLongaCentralizada(char *str,int posicaoX,int posicaoY,int largMax,int espacoEntreLinhas,PIG_Cor cor=BRANCO,int numFonte=0,float angulo=0){
    CPIGGerenciadorFontes::GetFonte(numFonte)->EscreveLonga(str,posicaoX,posicaoY,largMax,espacoEntreLinhas,cor,PIG_TEXTO_CENTRO,angulo);
}

/********************************
A funçăo EscreverInteiroEsquerda() é responsável por exibir um número inteiro na tela de jogo, com alinhamento ŕ esquerda em relaçăo ao valor de X.
Parâmetros:
valor (entrada, passagem por referęncia): número inteiro a ser escrito na tela.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usuário deseja começar a escrever o número.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usuário deseja começar a escrever o número.
cor (entrada, passagem por valor): cor a ser aplicada ŕ fonte no momento da escrita. Essa cor é misturada ŕ cor original da fonte, se essa tiver sido informada na criaçăo da fonte.
numFonte (entrada, passagem por valor): número da fonte a ser utilizada. Caso o usuário năo deseje uma fonte especial, será utilizada a fonte padrăo (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
angulo (entrada, passagem por valor): ângulo, em graus, para a rotaçăo do número inteiro.
********************************/
void EscreveInteiroEsquerda(int valor, int x, int y,PIG_Cor cor=BRANCO, int numFonte=0,float angulo=0){
    std::stringstream str;
    str<<valor;
    CPIGGerenciadorFontes::GetFonte(numFonte)->Escreve(str.str(),x,y,cor,PIG_TEXTO_ESQUERDA,angulo);
}

/********************************
A funçăo EscreverInteiroDireita() é responsável por exibir um número inteiro na tela de jogo, com alinhamento ŕ direita em relaçăo ao valor de X.
Parâmetros:
valor (entrada, passagem por referęncia): número inteiro a ser escrito na tela.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usuário deseja começar a escrever o número.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usuário deseja começar a escrever o número.
cor (entrada, passagem por valor): cor a ser aplicada ŕ fonte no momento da escrita. Essa cor é misturada ŕ cor original da fonte, se essa tiver sido informada na criaçăo da fonte.
numFonte (entrada, passagem por valor): número da fonte a ser utilizada. Caso o usuário năo deseje uma fonte especial, será utilizada a fonte padrăo (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
angulo (entrada, passagem por valor): ângulo, em graus, para a rotaçăo do número inteiro.
********************************/
void EscreveInteiroDireita(int valor, int x, int y,PIG_Cor cor=BRANCO, int numFonte=0,float angulo=0){
    std::stringstream str;
    str<<valor;
    CPIGGerenciadorFontes::GetFonte(numFonte)->Escreve(str.str(),x,y,cor,PIG_TEXTO_DIREITA,angulo);
}

/********************************
A funçăo EscreverInteiroCentralizado() é responsável por exibir um número inteiro na tela de jogo, com alinhamento em relaçăo ao valor de X.
Parâmetros:
valor (entrada, passagem por referęncia): número inteiro a ser escrito na tela.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usuário deseja começar a escrever o número.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usuário deseja começar a escrever o número.
cor (entrada, passagem por valor): cor a ser aplicada ŕ fonte no momento da escrita. Essa cor é misturada ŕ cor original da fonte, se essa tiver sido informada na criaçăo da fonte.
numFonte (entrada, passagem por valor): número da fonte a ser utilizada. Caso o usuário năo deseje uma fonte especial, será utilizada a fonte padrăo (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
angulo (entrada, passagem por valor): ângulo, em graus, para a rotaçăo do número inteiro.
********************************/
void EscreveInteiroCentralizado(int valor, int x, int y,PIG_Cor cor=BRANCO, int numFonte=0,float angulo=0){
    std::stringstream str;
    str<<valor;
    CPIGGerenciadorFontes::GetFonte(numFonte)->Escreve(str.str(),x,y,cor,PIG_TEXTO_CENTRO,angulo);
}

/********************************
A funçăo EscreverDoubleEsquerda() é responsável por exibir um número real na tela de jogo, com alinhamento ŕ esquerda em relaçăo ao valor de X.
Parâmetros:
valor (entrada, passagem por referęncia): número inteiro a ser escrito na tela.
casas (entrada, passagem por referęncia): número de casas decimais a ser usado na escrita.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usuário deseja começar a escrever o número.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usuário deseja começar a escrever o número.
cor (entrada, passagem por valor): cor a ser aplicada ŕ fonte no momento da escrita. Essa cor é misturada ŕ cor original da fonte, se essa tiver sido informada na criaçăo da fonte.
numFonte (entrada, passagem por valor): número da fonte a ser utilizada. Caso o usuário năo deseje uma fonte especial, será utilizada a fonte padrăo (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
angulo (entrada, passagem por valor): ângulo, em graus, para a rotaçăo do número real.
********************************/
void EscreveDoubleEsquerda(double valor, int casas, int x, int y,PIG_Cor cor=BRANCO, int numFonte=0,float angulo=0){
    std::stringstream str;
    str.setf(std::ios_base::fixed, std::ios_base::floatfield);
    str<<std::setprecision(casas)<<valor;
    CPIGGerenciadorFontes::GetFonte(numFonte)->Escreve(str.str(),x,y,cor,PIG_TEXTO_ESQUERDA,angulo);
}

/********************************
A funçăo EscreverDoubleDireita() é responsável por exibir um número real na tela de jogo, com alinhamento ŕ direita em relaçăo ao valor de X.
Parâmetros:
valor (entrada, passagem por referęncia): número inteiro a ser escrito na tela.
casas (entrada, passagem por referęncia): número de casas decimais a ser usado na escrita.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usuário deseja começar a escrever o número.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usuário deseja começar a escrever o número.
cor (entrada, passagem por valor): cor a ser aplicada ŕ fonte no momento da escrita. Essa cor é misturada ŕ cor original da fonte, se essa tiver sido informada na criaçăo da fonte.
numFonte (entrada, passagem por valor): número da fonte a ser utilizada. Caso o usuário năo deseje uma fonte especial, será utilizada a fonte padrăo (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
angulo (entrada, passagem por valor): ângulo, em graus, para a rotaçăo do número real.
********************************/
void EscreveDoubleDireita(double valor, int casas, int x, int y,PIG_Cor cor=BRANCO, int numFonte=0,float angulo=0){
    std::stringstream str;
    str.setf(std::ios_base::fixed, std::ios_base::floatfield);
    str<<std::setprecision(casas)<<valor;
    CPIGGerenciadorFontes::GetFonte(numFonte)->Escreve(str.str(),x,y,cor,PIG_TEXTO_DIREITA,angulo);
}

/********************************
A funçăo EscreverDoubleCentralizado() é responsável por exibir um número real na tela de jogo, com alinhamento em relaçăo ao valor de X.
Parâmetros:
valor (entrada, passagem por referęncia): número inteiro a ser escrito na tela.
casas (entrada, passagem por referęncia): número de casas decimais a ser usado na escrita.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usuário deseja começar a escrever o número.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usuário deseja começar a escrever o número.
cor (entrada, passagem por valor): cor a ser aplicada ŕ fonte no momento da escrita. Essa cor é misturada ŕ cor original da fonte, se essa tiver sido informada na criaçăo da fonte.
numFonte (entrada, passagem por valor): número da fonte a ser utilizada. Caso o usuário năo deseje uma fonte especial, será utilizada a fonte padrăo (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
angulo (entrada, passagem por valor): ângulo, em graus, para a rotaçăo do número real.
********************************/
void EscreveDoubleCentralizado(double valor, int casas, int x, int y,PIG_Cor cor=BRANCO, int numFonte=0,float angulo=0){
    std::stringstream str;
    str.setf(std::ios_base::fixed, std::ios_base::floatfield);
    str<<std::setprecision(casas)<<valor;
    CPIGGerenciadorFontes::GetFonte(numFonte)->Escreve(str.str(),x,y,cor,PIG_TEXTO_CENTRO,angulo);
}

/********************************
A funçăo GetMetricas() recupera as principais métricas de uma letra em um estilo específico.
As métricas incluem as posiçőes mínimas e máximas nos eixos X e Y, onde a letra é desenhada.
Se a fonte năo for dinâmica, qualquer valor de estilo passado será descartado e será utilizado o estilo indicado na criaçăo da fonte.
Parâmetros:
letra (entrada, passagem por valor): caractere cuja largura será calculada.
estilo (entrada, passagem por valor): estilo desejado no cálculo da largura. O valor só será utilizado em fontes dinâmicas. Em fontes năo-dinâmicas, o valor de estilo será o mesmo do informado na criaçăo da fonte.
numFonte (entrada, passagem por valor): número da fonte a ser utilizada. Caso o usuário năo deseje uma fonte especial, será utilizada a fonte padrăo (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
retorno:
struct que representa as métricas principais ao escrever a letra.
********************************/
PIG_Metricas_Fonte GetMetricas(char letra, PIG_Estilo estilo=PIG_ESTILO_NORMAL,int numFonte=0){
    return CPIGGerenciadorFontes::GetFonte(numFonte)->GetMetricasLetra(letra,estilo);
}

/********************************
A funçăo CalculaLarguraLetra() é responsável por calcular a largura específica de uma letra com um estilo.
Se a fonte năo for dinâmica, qualquer valor de estilo passado será descartado e será utilizado o estilo indicado na criaçăo da fonte.
Parâmetros:
letra (entrada, passagem por valor): caractere cuja largura será calculada.
estilo (entrada, passagem por valor): estilo desejado no cálculo da largura. O valor só será utilizado em fontes dinâmicas. Em fontes năo-dinâmicas, o valor de estilo será o mesmo do informado na criaçăo da fonte.
numFonte (entrada, passagem por valor): número da fonte a ser utilizada. Caso o usuário năo deseje uma fonte especial, será utilizada a fonte padrăo (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
retorno:
inteiro que representa o total de pixels (no eixo x) necessários para escrever a letra.
********************************/
int GetLarguraLetra(char letra,PIG_Estilo estilo=PIG_ESTILO_NORMAL,int numFonte = 0){
    return CPIGGerenciadorFontes::GetFonte(numFonte)->GetLarguraLetra(letra,estilo);
}

/********************************
A funçăo GetTamanhoBaseFonte() é responsável por recuperar o tamanho da fonte informado na criaçăo da mesma.
Parâmetros:
numFonte (entrada, passagem por valor): número da fonte a ser utilizada. Caso o usuário năo deseje uma fonte especial, será utilizada a fonte padrăo (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
retorno:
inteiro que representa o tamanho base da fonte, ou seja, a quantidade de pixels no eixo Y para desenhar qualquer caractere da fonte (exceto vogais maiúsuclas acentuadas: Á, É, Í, Ó, Ú.
********************************/
int GetTamanhoBaseFonte(int numFonte = 0){
    return CPIGGerenciadorFontes::GetFonte(numFonte)->GetTamanhoBaseFonte();
}

/********************************
A funçăo GetFonteDescent() calcula a quantidade de pixels que podem ser utilizados por partes de letras que fiquem abaixo da linha horizontal de base da fonte.
Essa parte inferior é usada para desenhar a cedilha, a parte inferior da letra 'g', 'q', 'y', por exemplo.
Parâmetros:
numFonte (entrada, passagem por valor): número da fonte a ser utilizada. Caso o usuário năo deseje uma fonte especial, será utilizada a fonte padrăo (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
retorno:
inteiro que representa o total de pixels abaixo da linha horizontal de base da fonte.
********************************/
int GetFonteDescent(int numFonte=0){
    return CPIGGerenciadorFontes::GetFonte(numFonte)->GetFonteDescent();
}

/********************************
A funçăo GetFonteAscent() calcula a quantidade de pixels necessários acima da linha horizontal de base da fonte. Essa medida exclui os pixels utilizados
nas partes inferiores das letras 'g', 'q', 'y', por exemplo. Também năo săo considerados acentos em vogais maiúsculas como 'Á', 'Ó', 'É', por exemplo.
Parâmetros:
numFonte (entrada, passagem por valor): número da fonte a ser utilizada. Caso o usuário năo deseje uma fonte especial, será utilizada a fonte padrăo (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
retorno:
inteiro que representa o total de pixels acima da linha horizontal de base da fonte.
********************************/
int GetFonteAscent(int numFonte=0){
    return CPIGGerenciadorFontes::GetFonte(numFonte)->GetFonteAscent();
}

/********************************
A funçăo GetFonteLineSkip() calcula a quantidade de pixels necessários para um espaçamento vertical ideal, ou seja, para que duas frases possam
ser escritas sem se sobreporem verticalmente.
Parâmetros:
numFonte (entrada, passagem por valor): número da fonte a ser utilizada. Caso o usuário năo deseje uma fonte especial, será utilizada a fonte padrăo (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
retorno:
inteiro que representa o espaçamento vertical ideal para que duas frases năo se sobreponham verticalmente.
********************************/
int GetFonteLineSkip(int numFonte=0){
    return CPIGGerenciadorFontes::GetFonte(numFonte)->GetLineSkip();
}

/********************************
A funçăo SubstituiCaractere() substitui a imagem original de um caractere por um frame de um imagem personalizada de um arquivo de imagem. O frame é definido
pelos parâmetros x, y, altura e largura, de acordo com o sistema de coordenadas dos arquivos de imagem digital (eixo Y crescendo para baixo). O frame especificado
será desenhado na tela toda vez que o caractere original for passado dentro de uma string. O frame terá a mesma altura padrăo da fote original, mas pdoerá ter uma largura
personalizada por meio do parâmetro largNova.
Parâmetros:
caractere (entrada, passagem por valor): caractere (ou número inteiro) que será substituído e năo será mais desenhado posteriormente.
nomeArquivo (entrada, passagem por referęncia): nome do arquivo contendo o frame desejado.
largNova: (entrada, passagem por valor): largura nova a ser utilizada para desenhar o frame na tela. Năo é obrigatoriamente o mesmo valor do parâmetro "larg".
x (entrada, passagem por valor): coordenada X do arquivo de imagem, onde começa o frame desejado.
y (entrada, passagem por valor): coordenada Y do arquivo de imagem, onde começa o frame desejado (sistema de coordenada com eixo Y crescendo para baixo).
altura (entrada, passagem por valor): altura do frame desejado.
largura (entrada, passagem por valor): largura do frame desejado.
numFonte (entrada, passagem por valor): número da fonte a ser utilizada. Caso o usuário năo deseje uma fonte especial, será utilizada a fonte padrăo (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
retorno:
inteiro que representa o espaçamento vertical ideal para que duas frases năo se sobreponham verticalmente.
********************************/
void SubstituiCaractere(char caractere, char *nomeArquivo, int largNova, int x, int y, int altura,int largura,int numFonte=0){
    CPIGGerenciadorFontes::GetFonte(numFonte)->SubstituiGlyph(nomeArquivo,caractere,largNova,x,y,altura,largura);
}



/********************************
Seçăo de sprites
********************************/

/********************************
A funçăo CriaSprite() é responsável por criar um sprite. Qualquer sprite que for necessário,
pode ser criado através dessa funçăo. O sprite ainda năo será desenhado, apenas criado dentro do jogo.
Parâmetros:
nomeArquivo (entrada, passagem por referęncia): string que informa o nome do arquivo da imagem do sprite a ser criado.
retiraFundo (entrada, passagem por valor): inteiro que indica se o fundo da imagem deve ser retirado ou năo ao ler o arquivo em questăo. O valor padrăo é 1, indicando que o fundo deve ser retirado.
corFundo (entrada, passagem por referęncia năo-obrigatório): indica se há uma cor específica para ser considerada como cor de fundo da imagem. Caso, o valor seja NULL, mas o parâmetro retiraFundo seja diferente de 0, o pixel (0,0) da imagem será considerado como cor de fundo.
idJanela (entrada, passagem por valor năo-obrigatório): indica qual janela vai receber o sprite.
Retorno:
inteiro que representa o identificador único do sprite. Todas as operaçőes subsequentes com este sprite deverăo receber este identificador como parâmetro.
********************************/
int CriaSprite(char* nomeArquivo,int retiraFundo=1,PIG_Cor *corFundo=NULL, int idJanela=0){
    return CPIGGerenciadorSprites::CriaSprite(nomeArquivo,retiraFundo,corFundo,idJanela);
}

/********************************
A funçăo CriaSprite() é responsável por criar um sprite. Qualquer sprite que for necessário,
pode ser criado através dessa funçăo. O sprite ainda năo será desenhado, apenas criado dentro do jogo.
Parâmetros:
idSprite(entrada, passagem por valor): identificador do sprite original que será copiado.
retiraFundo (entrada, passagem por valor): inteiro que indica se o fundo da imagem deve ser retirado ou năo ao ler o arquivo em questăo. O valor padrăo é 1, indicando que o fundo deve ser retirado.
corFundo (entrada, passagem por referęncia năo-obrigatório): indica se há uma cor específica para ser considerada como cor de fundo da imagem. Caso, o valor seja NULL, mas o parâmetro retiraFundo seja diferente de 0, o pixel (0,0) da imagem será considerado como cor de fundo.
idJanela (entrada, passagem por valor năo-obrigatório): indica qual janela vai receber o sprite.
Retorno:
inteiro que representa o identificador único do sprite. Todas as operaçőes subsequentes com este sprite deverăo receber este identificador como parâmetro.
********************************/
int CriaSprite(int idSprite,int retiraFundo=1,PIG_Cor *corFundo=NULL, int idJanela=0){
    return CPIGGerenciadorSprites::CriaSprite(idSprite,retiraFundo,corFundo,idJanela);
}

/********************************
A funçăo CriaSpriteOffScreen() é responsável por criar um sprite a partir da imagem que está sendo montanda pelo
renderizador Offscreen. O renderizador precisa ter sido preparado anteriormente.
Parâmetros:
retiraFundo (entrada, passagem por valor): inteiro que indica se o fundo da imagem deve ser retirado ou năo ao ler o arquivo em questăo. O valor padrăo é 1, indicando que o fundo deve ser retirado.
corFundo (entrada, passagem por referęncia năo-obrigatório): indica se há uma cor específica para ser considerada como cor de fundo da imagem. Caso, o valor seja NULL, mas o parâmetro retiraFundo seja diferente de 0, o pixel (0,0) da imagem será considerado como cor de fundo.
Retorno:
inteiro que representa o identificador único do sprite. Todas as operaçőes subsequentes com este sprite deverăo receber este identificador como parâmetro.
********************************/
int CriaSpriteOffScreen(int retiraFundo=1,PIG_Cor *corFundo=NULL){
    return CPIGGerenciadorSprites::CriaSpriteOffScreen(jogo->GetOffScreenRender(),retiraFundo,corFundo);
}

/********************************
A funçăo DestroiSprite() é responsável por eliminar o sprite em questăo do jogo.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite a ser excluído.
********************************/
void DestroiSprite(int idSprite){
    CPIGGerenciadorSprites::DestroiSprite(idSprite);
}

/********************************
A funçăo CarregaArquivoFramesSprite() é responsável por ler de arquivo texto os frames de um sprite.
Cada linha do arquivo texto deve conter 5 números inteiros: o número do frame, a posiçăo do frame no eixo X do arquivo de imagem,
a posiçăo do frame no eixo Y do arquivo de imagem, a altura do frame e a largura do frame (todas as unidades em pixels).
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
nomeArq (entrada, passagem por referęncia): nome do arquivo texto contendo os frames.
********************************/
void CarregaArquivoFramesSprite(int idSprite, char *nomeArq){
    CPIGGerenciadorSprites::GetSprite(idSprite)->CarregaArquivoFrames(nomeArq);
}

/********************************
A funçăo CarregaFramesPorLinhaSprite() é responsável por subdividir o arquivo de imagem em linhas (de mesmo tamanho) e colunas (de mesmo tamanho).
Cada subdivisăo representará um frame que será automaticamente criado para a animaçăo, com numeraçăo incremental a partir do parâmetro "frameInicial".
Ao final das "qtdColunas" da primeira linha, a definiçăo dos frames continua na linha inferior.
A funçăo pode ser utilizada em spritesheets regulares.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
frameInicial (entrada, passagem por valor): numeraçăo do primeiro frame a ser criado pela funçăo. Os demais frames terăo numeraçăo consecutiva.
qtdLinhas (entrada, passagem por valor): quantidade de linhas na qual o arquivo de imagem será dividido.
qtdColunas (entrada, passagem por valor): quantidade de colunas na qual o arquivo de imagem será dividido.
********************************/
void CarregaFramesPorLinhaSprite(int idSprite, int frameInicial, int qtdLinhas, int qtdColunas){
    CPIGGerenciadorSprites::GetSprite(idSprite)->CriaFramesAutomaticosPorLinha(frameInicial,qtdLinhas,qtdColunas);
}

/********************************
A funçăo CarregaFramesPorColunaSprite() é responsável por subdividir o arquivo de imagem em linhas (de mesmo tamanho) e colunas (de mesmo tamanho).
Cada subdivisăo representará um frame que será automaticamente criado para a animaçăo, com numeraçăo incremental a partir do parâmetro "frameInicial".
Ao final das "qtdLinhas" da primeira coluna, a definiçăo dos frames continua na coluna seguinte.
A funçăo pode ser utilizada em spritesheets regulares.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
frameInicial (entrada, passagem por valor): numeraçăo do primeiro frame a ser criado pela funçăo. Os demais frames terăo numeraçăo consecutiva.
qtdLinhas (entrada, passagem por valor): quantidade de linhas na qual o arquivo de imagem será dividido.
qtdColunas (entrada, passagem por valor): quantidade de colunas na qual o arquivo de imagem será dividido.
********************************/
void CarregaFramesPorColunaSprite(int idSprite, int frameInicial, int qtdLinhas, int qtdColunas){
    CPIGGerenciadorSprites::GetSprite(idSprite)->CriaFramesAutomaticosPorColuna(frameInicial,qtdLinhas,qtdColunas);
}

/********************************
A funçăo GetXYSprite() é responsável recuperar o valor da posiçăo (X,Y) do sprite de acordo com o sistema de coordenadas do jogo.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
posicaoX (saída, passagem por referencia): indica a posicao no eixo X do sprite.
posicaoY (saída, passagem por referencia): indica a posicao no eixo Y do sprite.
********************************/
void GetXYSprite(int idSprite,int *posicaoX,int *posicaoY){
    PIGPonto2D p = CPIGGerenciadorSprites::GetSprite(idSprite)->GetXY();
    *posicaoX = p.x;
    *posicaoY = p.y;
}

/********************************
A funçăo MoveSprite() é responsável por movimentar um determinado sprite para uma nova posiçăo informada.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite a ser movido.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usuário deseja reposicionar o sprite.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usuário deseja reposicionar o sprite.
********************************/
void MoveSprite(int idSprite,int posicaoX,int posicaoY){
    CPIGGerenciadorSprites::GetSprite(idSprite)->Move(posicaoX,posicaoY);
}

/********************************
A funçăo DeslocaSprite() é responsável por deslocar um determinado sprite em relaçăo ŕ sua posiçăo atual.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite a ser movido.
deltaX (entrada, passagem por valor): valor a ser somado ou subtraído na componente X da posiçăo do sprite.
deltaY (entrada, passagem por valor): valor a ser somado ou subtraído na componente Y da posiçăo do sprite.
********************************/
void DeslocaSprite(int idSprite,int deltaX,int deltaY){
    CPIGGerenciadorSprites::GetSprite(idSprite)->Desloca(deltaX,deltaY);
}

/********************************
A funçăo SetAnguloSprite() é responsável pela angulaçăo de determinado sprite. A angulaçăo é calculada em sentido
horário a partir do eixo X (0 graus). O sprite será desenhado com a angulaçăo informada no próximo comando
DesenhaSprite(). A detecçăo de colisăo năo funciona com sprites fora da angulaçăo padrăo (0 graus).
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
angulo (entrada, passagem por valor): valor para indicar a angulaçăo do sprite em graus.
********************************/
void SetAnguloSprite(int idSprite, float angulo){
    CPIGGerenciadorSprites::GetSprite(idSprite)->SetAngulo(angulo);
}

/********************************
A funçăo GetAnguloSprite() é responsável por recuperar o ângulo de rotaçăo de determinado sprite. A angulaçăo é calculada em sentido
horário a partir do eixo X (0 graus). O sprite será desenhado com a angulaçăo informada no próximo comando
DesenhaSprite(). A detecçăo de colisăo năo funciona com sprites fora da angulaçăo padrăo (0 graus).
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
Retorno:
Retorna o valor do ângulo em graus.
********************************/
float GetAnguloSprite(int idSprite){
    return CPIGGerenciadorSprites::GetSprite(idSprite)->GetAngulo();
}

/********************************
A funçăo SetPivoAbsolutoSprite() define um ponto (X,Y) em relaçăo ao ponto (0,0) do sprite, sobre o qual o sprite será
rotacionado quando a funçăo SetAnguloSprite() for executada.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
posicaoX (entrada, passagem por valor): Valor da coordenada X do pivô em relaçăo ao ponto (0,0) do sprite.
posicaoY (entrada, passagem por valor): Valor da coordenada Y do pivô em relaçăo ao ponto (0,0) do sprite.
********************************/
void SetPivoAbsolutoSprite(int idSprite,int posicaoX,int posicaoY){
    CPIGGerenciadorSprites::GetSprite(idSprite)->SetPivoAbsoluto({(double)posicaoX,(double)posicaoY});
}

/********************************
A funçăo SetPivoProporcionalSprite() define um ponto (X,Y) proporcional ao tamanho do sprite, sobre o qual o sprite será
rotacionado quando a funçăo SetAnguloSprite() for executada.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
relX (entrada, passagem por valor): porcentagem da largura do sprite onde ficará o pivô.
relY (entrada, passagem por valor): porcentagem da altura do sprite onde ficará o pivô.
********************************/
void SetPivoProporcionalSprite(int idSprite,float relX,float relY){
    CPIGGerenciadorSprites::GetSprite(idSprite)->SetPivoProporcional({relX,relY});
}

/********************************
A funçăo GetPivoSprite() define um ponto (X,Y) em relaçăo ao ponto (0,0) do sprite, sobre o qual o sprite será
rotacionado quando a funçăo SetAnguloSprite() for executada.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
posicaoX (saída, passagem por referęncia): Valor da coordenada X do pivô em relaçăo ao ponto (0,0) do sprite.
posicaoY (saída, passagem por referęncia): Valor da coordenada Y do pivô em relaçăo ao ponto (0,0) do sprite.
********************************/
void GetPivoSprite(int idSprite,int *posicaoX,int *posicaoY){
    PIGPonto2D p = CPIGGerenciadorSprites::GetSprite(idSprite)->GetPivo();
    *posicaoX = p.x;
    *posicaoY = p.y;
}

/********************************
A funçăo SetFlipSprite() é responsável por virar o sprite, invertendo-o em alguma direçăo. O sprite somente será
desenhado na nova orientaçăo no próximo comando DesenhaSprite().
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite a ser virado.
valor (entrada, passagem por valor): valor do tipo de Flip. Pode ser FLIP_NENHUM (nenhum tipo de inversăo),
PIG_FLIP_HORIZONTAL (inverte da esquerda para a direita), PIG_FLIP_VERTICAL (inverte de cima para baixo),
ou PIG_FLIP_HORIZ_VERT (inverte da esquerda para direita e de cima para baixo).
********************************/
void SetFlipSprite(int idSprite,PIG_Flip valor){
    CPIGGerenciadorSprites::GetSprite(idSprite)->SetFlip(valor);
}

/********************************
A funçăo GetFlipSprite() é responsável por recuperar o valor da manipulaçăo causada pela funçăo SetFlipSprite().
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite a ser virado.
Retorno:
inteiro que indica o tipo de Flip. Pode ser PIG_FLIP_NENHUM (nenhum tipo de inversăo),
PIG_FLIP_HORIZONTAL (inverte da esquerda para a direita), PIG_FLIP_VERTICAL (inverte de cima para baixo),
ou PIG_FLIP_HORIZ_VERT (inverte da esquerda para direita e de cima para baixo).
********************************/
PIG_Flip GetFlipSprite(int idSprite){
    return CPIGGerenciadorSprites::GetSprite(idSprite)->GetFlip();
}

/********************************
A funçăo SetDimensoesSprite() é responsável por delimitar a altura e a largura do sprite que será desenhado na tela,
independentemente do tamanho original do arquivo de imagem.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
altura (entrada, passagem por valor): altura em pixels.
largura (entrada, passagem por valor): largura em pixels.
********************************/
void SetDimensoesSprite(int idSprite, int altura, int largura){
    CPIGGerenciadorSprites::GetSprite(idSprite)->SetDimensoes(altura,largura);
}

/********************************
A funçăo GetDimensoesSprite() é responsável por recuperar a altura e a largura da área a ser usada
para desenhar o sprite na tela. Em outras palavras, representa o tamanho atual do sprite.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
altura (saída, passagem por referęncia): altura atual em pixels do sprite.
largura (saída, passagem por referęncia): largura atual em pixels do sprite.
********************************/
void GetDimensoesSprite(int idSprite, int *altura, int *largura){
    CPIGGerenciadorSprites::GetSprite(idSprite)->GetDimensoes(*altura,*largura);
}

/********************************
A funçăo GetDimensoesOriginaisSprite() é responsável por recuperar a altura e a largura originais da imagem
que foi usada para criar o sprite. Qualquer utilizaçăo da funçăo SetDimensoesSprite() é ignorada para
o cálculo desta funçăo.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
altura (saída, passagem por referęncia): altura original em pixels do sprite.
largura (saída, passagem por referęncia): largura original em pixels do sprite.
********************************/
void GetDimensoesOriginaisSprite(int idSprite, int *altura, int *largura){
    CPIGGerenciadorSprites::GetSprite(idSprite)->GetDimensoesOriginais(*altura,*largura);
}

/********************************
A funçăo RestauraDimensoesOriginaisSprite() é responsável por restaurar o sprite com o tamanho original da image.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
********************************/
void RestauraDimensoesOriginaisSprite(int idSprite, int altura, int largura){
    CPIGGerenciadorSprites::GetSprite(idSprite)->RestauraDimensoesOriginais();
}

/********************************
A funçăo CriaFrameSprite() é responsável por delimitar o posicionamento dos pixels do arquivo de imagem que serăo
utilizados para representar o sprite na tela. Desta forma, nem toda a imagem será automaticamente utilizada para
representar o sprite. O sistema de coordenadas deve ser o padrăo dos arquivos de imagem, com o eixo Y aumentando para baixo.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite a ser desenhado.
idFrame (entrada, passagem por valor): identificador do frame a ser criado.
xBitmap (entrada, passagem por valor): indica a posiçăo de eixo X onde começa o frame.
yBitmap (entrada, passagem por valor): indica a posiçăo de eixo Y onde começa o frame. Neste caso, o eixo Y aumenta para baixo.
altura (entrada, passagem por valor): altura em pixels do frame.
largura (entrada, passagem por valor): largura em pixels do frame.
********************************/
void CriaFrameSprite(int idSprite, int idFrame, int xBitmap, int yBitmap, int altura, int largura){
    CPIGGerenciadorSprites::GetSprite(idSprite)->DefineFrame(idFrame, {xBitmap,yBitmap,largura,altura});
}

/********************************
A funçăo MudaFrameSprite() é responsável por modificar o frame (já definido pela funçăo DefineFrameSprite) de um sprite
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
idFrame (entrada, passagem por valor): identificador do frame já criado.
Retorno:
Se o identifador do frame informado năo corresponder a um frame já criado, o valor de retorno é igual a 0. Caso contrário, é igual a 1.
********************************/
int MudaFrameSprite(int idSprite, int idFrame){
    return CPIGGerenciadorSprites::GetSprite(idSprite)->MudaFrameAtual(idFrame);
}

/********************************
A funçăo GetFrameAtualSprite() recupera o valor do frame atual exibido no sprite.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
Retorno:
Número do frame atual do sprite.
********************************/
int GetFrameAtualSprite(int idSprite){
    return CPIGGerenciadorSprites::GetSprite(idSprite)->GetFrameAtual();
}

/********************************
A funçăo SetColoracaoSprite() é responsável por mesclar uma determinada cor com os pixels do arquivo de imagem.
Após a modificaçăo, todos os desenhos deste sprite serăo mostrados já com a mesclagem definida.
Para voltar ao padrăo original de pixels, deve-se chamar a funçăo, passando a cor branca (255,255,255).
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite a ser desenhado.
cor (entrada,passagem por valor): cor do sistema RGB utilizada para mesclagem com o arquivo de imagem
********************************/
void SetColoracaoSprite(int idSprite, PIG_Cor cor){
    CPIGGerenciadorSprites::GetSprite(idSprite)->SetColoracao(cor);
}

/********************************
A funçăo SetOpacidadeSprite() é responsável por modificar o nível de opacidade do sprite.
O nível de opacidade varia de 0-255, sendo 0 totalmente transparente e 255 totalmente opaco.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
valor (entrada,passagem por valor): nível de opacidade do sprite na faixa 0-255.
********************************/
void SetOpacidadeSprite(int idSprite,int valor){
    CPIGGerenciadorSprites::GetSprite(idSprite)->SetOpacidade(valor);
}

/********************************
A funçăo GetOpacidadeSprite() é responsável por recuperar o nível de opacidade de determinado sprite.
O nível de opacidade varia de 0-255, sendo 0 totalmente transparente e 255 totalmente opaco.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
Retorno:
Retorna o nível de opacidade do sprite na faixa 0-255.
********************************/
int GetOpacidadeSprite(int idSprite){
    return CPIGGerenciadorSprites::GetSprite(idSprite)->GetOpacidade();
}

/********************************
A funçăo DesenhaSprite() é responsável por desenhar um sprite na tela. O sprite será desenhado de acordo com todas as definiçőes
de posiçăo e ângulo informado até o momento. Além disso, se o sprite estiver virado (flipping), isso também será levado em consideraçăo.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite a ser desenhado.
********************************/
void DesenhaSprite(int idSprite){
    CPIGGerenciadorSprites::GetSprite(idSprite)->Desenha();
}

/********************************
A funçăo DesenhaSpriteOffScreen() é responsável por desenhar um sprite no Renderizador Offscreen. O sprite será desenhado de acordo com todas as definiçőes
de posiçăo e ângulo informado até o momento. Além disso, se o sprite estiver virado (flipping), isso também será levado em consideraçăo.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite a ser desenhado.
********************************/
void DesenhaSpriteOffScreen(int idSprite){
    CPIGGerenciadorSprites::GetSprite(idSprite)->DesenhaOffScreen(jogo->GetOffScreenRender());
}

/********************************
A funçăo DesenhaSprite() é responsável por desenhar um sprite na tela. O sprite será desenhado contendo toda a imagem, na posiçăo indica.
Năo será aplicada nenhuma modificaçăo, como ângulo, coloraçăo, ou opacidade, por exemplo.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite a ser desenhado.
********************************/
void DesenhaSpriteSimples(char *nomeArq,int x, int y, int retiraFundo=1,int idJanela=0){
    CPIGGerenciadorSprites::DesenhaSprite(nomeArq, x, y, retiraFundo,idJanela);
}

/********************************
A funçăo InsereTransicaoSprite() é responsável por criar e inserir uma nova transiçăo ao final de sequęncia de transiçőes do sprite.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
tempo (entrada, passagem por valor): duracao (em segundos) da transiçăo.
deltaX (entrada, passagem por valor): diferença da posiçăo no eixo X em relaçăo ŕ posiçăo do sprite no início da transiçăo.
deltaY (entrada, passagem por valor): diferença da posiçăo no eixo Y em relaçăo ŕ posiçăo do sprite no início da transiçăo.
deltaAltura (entrada, passagem por valor): diferença da altura do sprite em relaçăo ao início da transiçăo.
deltaLargura (entrada, passagem por valor): diferença da largura do sprite em relaçăo ao início da transiçăo.
deltaAngulo (entrada, passagem por valor): diferença de ângulo (em graus) do sprite em relaçăo ao início da transiçăo.
corFinal (entrada, passagem por valor): coloraçăo do sprite ao final da transiçăo.
deltaOpacidade (entrada, passagem por valor): diferença do nível de opacidade do sprite em relaçăo ao início da transiçăo.
********************************/
void InsereTransicaoSprite(int idSprite,double tempo,int deltaX,int deltaY,int deltaAltura,int deltaLargura,double deltaAngulo,PIG_Cor corFinal,int deltaOpacidade){
    CPIGGerenciadorSprites::GetSprite(idSprite)->InsereTransicao(tempo,{deltaX,deltaY,deltaAltura,deltaLargura,deltaAngulo,corFinal,deltaOpacidade});
}

/********************************
A funçăo ExecutandoTransicaoSprite() retorna a informaçăo sobre a execuçăo (neste momento) de transiçőes do sprite.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
Retorno:
inteiro que indica se o sprite está executando alguma transiçăo no momento (valor diferente de 0) ou năo (valor igual a 0).
********************************/
int ExecutandoTransicaoSprite(int idSprite){
    return CPIGGerenciadorSprites::GetSprite(idSprite)->ExecutandoTransicao();
}

/********************************
A funçăo LeArquivoTransicaoSprite() é responsável por ler, criar e inserir as transiçőes para um sprite, provenientes de um arquivo texto.
Cada linha do arquivo texto corresponde a uma transiçăo (em ordem) e deve possuir 11 valores:
1) um double representando a duracao (em segundos) da transiçăo.
2) um inteiro repreentando a diferença da posiçăo no eixo X em relaçăo ŕ posiçăo do sprite no início da transiçăo.
3) um inteiro repreentando a diferença da posiçăo no eixo Y em relaçăo ŕ posiçăo do sprite no início da transiçăo.
4) um inteiro repreentando a diferença da altura do sprite em relaçăo ao início da transiçăo.
5) um inteiro repreentando a diferença da largura do sprite em relaçăo ao início da transiçăo.
6) um double repreentando a diferença de ângulo (em graus) do sprite em relaçăo ao início da transiçăo.
7) um inteiro repreentando a componente R (vermelho) da coloraçăo do sprite ao final da transiçăo.
8) um inteiro repreentando a componente G (verde) da coloraçăo do sprite ao final da transiçăo.
9) um inteiro repreentando a componente B (azul) da coloraçăo do sprite ao final da transiçăo.
10) um inteiro repreentando a componente A (canal alfa) da coloraçăo do sprite ao final da transiçăo.
11) um inteiro repreentando a diferença do nível de opacidade do sprite em relaçăo ao início da transiçăo.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
nomeArq (entrada, passagem por referęncia): nome com extensăo do arquivo texto contendo as transiçőes.
********************************/
void LeArquivoTransicaoSprite(int idSprite,char *nomeArq){
    CPIGGerenciadorSprites::GetSprite(idSprite)->LeTransicoes(nomeArq);
}

/********************************
A funçăo IniciaAutomacaoSprite() é responsável por iniciar as transiçőes já inseridas no sprite, de acordo como o tipo de transiçăo informada.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
********************************/
void IniciaAutomacaoSprite(int idSprite){
    CPIGGerenciadorSprites::GetSprite(idSprite)->IniciaAutomacao();
}

/********************************
A funçăo TrataAutomacaoSprite() é responsável por calcular o estado da transiçăo corrente do sprite e aplicar essas modificaçăo a ela.
A funçăo deve ser chamada a cada frame, para ter resultados mais precisos.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
********************************/
void TrataAutomacaoSprite(int idSprite){
    CPIGGerenciadorSprites::GetSprite(idSprite)->TrataAutomacao();
}

/********************************
A funçăo PausaAutomacaoSprite() é responsável por pausar as transições e ações associadas a um sprite.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
********************************/
void PausaAutomacaoSprite(int idSprite){
    CPIGGerenciadorSprites::GetSprite(idSprite)->PausaAutomacao();
}

/********************************
A funçăo DespausaAutomacaoSprite() é responsável por despausar as transições e ações associadas a um sprite.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
********************************/
void DespausaAutomacaoSprite(int idSprite){
    CPIGGerenciadorSprites::GetSprite(idSprite)->DespausaAutomacao();
}

/********************************
A funçăo DefineTipoTransicaoSprite() é responsável por determinar como a sequęncia de transiçőes será executada.
É possível fazę-la uma única vez (PIG_TRANSICAO_NORMAL), em loop (PIG_TRANSICAO_LOOP) ou indo até o final da sequęncia e retornando, em vai-vém (PIG_TRANSICAO_VAIVEM).
A funçăo deve ser chamada a cada frame, para ter resultados mais precisos.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
********************************/
void DefineTipoTransicaoSprite(int idSprite,PIG_TipoTransicao valor){
    CPIGGerenciadorSprites::GetSprite(idSprite)->DefineTipoTransicao(valor);
}

/********************************
A funçăo LimpaTransicoesSprite() é responsável por remover a sequęncia de transiçőes do sprite.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
********************************/
void LimpaTransicoesSprite(int idSprite){
    CPIGGerenciadorSprites::GetSprite(idSprite)->LimpaTransicoes();
}

/********************************
A funçăo InsereAcaoSprite() é responsável por inserir na linha de tempo de automaçăo do sprite uma açăo a ser executada.
A açăo é composta por uma funçăo "acao" que será executada quando a linha de tempo atingir o parâmetro "tempo" e será repetida a cada "repeticao" segundos.
A açăo pode armazenar um ponteiro genérico "param" que será utilizado na chamada da funçăo.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
tempo (entrada, passagem por valor): tempo (em segundos) da primeira chamada da funçăo.
repeticao (entrada, passagem por valor): tempo (em segundos) entre a chamada anterior e a próxima. O valor -1 indica que a funçăo năo será repetida.
param (entrada, passagem por referęncia): ponteiro genérico para um valor que será utilizado na chamada da funçăo.
********************************/
void InsereAcaoSprite(int idSprite,double tempo,double repeticao,PIG_FuncaoSimples acao,void *param){
    CPIGGerenciadorSprites::GetSprite(idSprite)->InsereAcao(tempo,repeticao,acao,param);
}

/********************************
A funçăo LimpaAcoesSprite() é responsável por remover as ações restantes associadas ao sprite.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
********************************/
void LimpaAcoesSprite(int idSprite){
    CPIGGerenciadorSprites::GetSprite(idSprite)->LimpaAcoes();
}


/********************************
Seçăo de objetos
********************************/

/********************************
A funçăo CriaObjeto() é responsável por criar um objeto. Qualquer objeto que for necessário,
pode ser criado através dessa funçăo. O objeto ainda năo será desenhado, apenas criado dentro do jogo.
Parâmetros:
nomeArquivo (entrada, passagem por referęncia): string que informa o nome do arquivo da imagem do objeto a ser criado.
retiraFundo (entrada, passagem por valor): inteiro que indica se o fundo da imagem deve ser retirado ou năo ao ler o arquivo em questăo. O valor padrăo é 1, indicando que o fundo deve ser retirado.
corFundo (entrada, passagem por referęncia năo-obrigatório): indica se há uma cor específica para ser considerada como cor de fundo da imagem. Caso, o valor seja NULL, mas o parâmetro retiraFundo seja diferente de 0, o pixel (0,0) da imagem será considerado como cor de fundo.
idJanela (entrada, passagem por valor năo-obrigatório): indica qual janela vai receber o objeto.
Retorno:
inteiro que representa o identificador único do objeto. Todas as operaçőes subsequentes com este objeto deverăo receber este identificador como parâmetro.
********************************/
int CriaObjeto(char* nomeArquivo,int retiraFundo=1,PIG_Cor *corFundo=NULL, int idJanela=0){
    return CPIGGerenciadorSprites::CriaObjeto(nomeArquivo,retiraFundo,corFundo,idJanela);
}

/********************************
A funçăo CriaObjeto() é responsável por criar um objeto. Qualquer objeto que for necessário,
pode ser criado através dessa funçăo. O objeto ainda năo será desenhado, apenas criado dentro do jogo.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto original que será copiado.
retiraFundo (entrada, passagem por valor): inteiro que indica se o fundo da imagem deve ser retirado ou năo ao ler o arquivo em questăo. O valor padrăo é 1, indicando que o fundo deve ser retirado.
corFundo (entrada, passagem por referęncia năo-obrigatório): indica se há uma cor específica para ser considerada como cor de fundo da imagem. Caso, o valor seja NULL, mas o parâmetro retiraFundo seja diferente de 0, o pixel (0,0) da imagem será considerado como cor de fundo.
idJanela (entrada, passagem por valor năo-obrigatório): indica qual janela vai receber o objeto.
Retorno:
inteiro que representa o identificador único do objeto. Todas as operaçőes subsequentes com este objeto deverăo receber este identificador como parâmetro.
********************************/
int CriaObjeto(int idObjeto,int retiraFundo=1,PIG_Cor *corFundo=NULL, int idJanela=0){
    return CPIGGerenciadorSprites::CriaObjeto(idObjeto,retiraFundo,corFundo,idJanela);
}

/********************************
A funçăo CriaObjetoOffScreen() é responsável por criar um objeto a partir da imagem que está sendo montanda pelo
renderizador Offscreen. O renderizador precisa ter sido preparado anteriormente.
Parâmetros:
retiraFundo (entrada, passagem por valor): inteiro que indica se o fundo da imagem deve ser retirado ou năo ao ler o arquivo em questăo. O valor padrăo é 1, indicando que o fundo deve ser retirado.
corFundo (entrada, passagem por referęncia năo-obrigatório): indica se há uma cor específica para ser considerada como cor de fundo da imagem. Caso, o valor seja NULL, mas o parâmetro retiraFundo seja diferente de 0, o pixel (0,0) da imagem será considerado como cor de fundo.
Retorno:
inteiro que representa o identificador único do objeto. Todas as operaçőes subsequentes com este objeto deverăo receber este identificador como parâmetro.
********************************/
int CriaObjetoOffScreen(int retiraFundo=1,PIG_Cor *corFundo=NULL, int idJanela=0){
    return CPIGGerenciadorSprites::CriaObjetoOffScreen(jogo->GetOffScreenRender(),retiraFundo,corFundo,idJanela);
}

/********************************
A funçăo GetFrameAtualObjeto() recupera o valor do frame atual exibido no objeto.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
Retorno:
Número do frame atual do objeto.
********************************/
int GetFrameAtualObjeto(int idObjeto){
    return CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetFrameAtual();
}

/********************************
A funçăo DestroiObjeto() é responsável por eliminar o objeto em questăo do jogo.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto a ser excluído.
********************************/
void DestroiObjeto(int idObjeto){
    CPIGGerenciadorSprites::DestroiObjeto(idObjeto);
}

/********************************
A funçăo SetValorIntObjeto() é responsável incorporar a um objeto um atributo inteiro.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por valor): relaciona um número inteiro ao atributo.
valor (entrada, passagem por valor): valor do atributo inteiro a ser associado ao objeto.
********************************/
void SetValorIntObjeto(int idObjeto,int indice,int valor){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetValorInt(indice,valor);
}

/********************************
A funçăo SetValorFloatObjeto() é responsável incorporar a um objeto um atributo float.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por valor): relaciona um número inteiro ao atributo.
valor (entrada, passagem por valor): valor do atributo float a ser associado ao objeto.
********************************/
void SetValorFloatObjeto(int idObjeto,int indice,float valor){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetValorFloat(indice,valor);
}

/********************************
A funçăo SetValorIntObjeto() é responsável incorporar a um objeto um atributo inteiro.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por valor): relaciona um número inteiro ao atributo.
valor (entrada, passagem por referęncia): valor do atributo string a ser associado ao objeto.
********************************/
void SetValorStringObjeto(int idObjeto,int indice,char *valor){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetValorString(indice,valor);
}

/********************************
A funçăo SetValorIntObjeto() é responsável incorporar a um objeto um atributo inteiro.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por referęncia): relaciona uma string ao atributo.
valor (entrada, passagem por valor): valor do atributo inteiro a ser associado ao objeto.
********************************/
void SetValorIntObjeto(int idObjeto,char *indice,int valor){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetValorInt(indice,valor);
}

/********************************
A funçăo SetValorFloatObjeto() é responsável incorporar a um objeto um atributo float.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por referęncia): relaciona uma string ao atributo.
valor (entrada, passagem por valor): valor do atributo float a ser associado ao objeto.
********************************/
void SetValorFloatObjeto(int idObjeto,char *indice,float valor){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetValorFloat(indice,valor);
}

/********************************
A funçăo SetValorIntObjeto() é responsável incorporar a um objeto um atributo inteiro.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por referęncia): relaciona uma string ao atributo.
valor (entrada, passagem por referęncia): valor do atributo string a ser associado ao objeto.
********************************/
void SetValorStringObjeto(int idObjeto,char *indice,char *valor){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetValorString(indice,valor);
}

/********************************
A funçăo GetValorIntObjeto() é responsável recuperar o valor de um atributo inteiro relacionado a um objeto.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por valor): indica o número do atributo que se deseja recuperar.
valor (saída, passagem por referęncia): indica o valor do atributo, se a funçăo retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo năo existir, a funçăo retorna o valor 0 (zero).
********************************/
int GetValorIntObjeto(int idObjeto,int indice,int *valor){
    return CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetValorInt(indice,*valor);
}

/********************************
A funçăo GetValorFloatObjeto() é responsável recuperar o valor de um atributo float relacionado a um objeto.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por valor): indica o número do atributo que se deseja recuperar.
valor (saída, passagem por referęncia): indica o valor do atributo, se a funçăo retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo năo existir, a funçăo retorna o valor 0 (zero).
********************************/
int GetValorFloatObjeto(int idObjeto,int indice,float *valor){
    return CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetValorFloat(indice,*valor);
}

/********************************
A funçăo GetValorStringObjeto() é responsável recuperar o valor de um atributo string relacionado a um objeto.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por valor): indica o número do atributo que se deseja recuperar.
valor (saída, passagem por referęncia): indica o valor do atributo, se a funçăo retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo năo existir, a funçăo retorna o valor 0 (zero).
********************************/
int GetValorStringObjeto(int idObjeto,int indice,char *valor){
    std::string str;
    bool resp = CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetValorString(indice,str);
    strcpy(valor,str.c_str());
    return resp;
}

/********************************
A funçăo GetValorIntObjeto() é responsável recuperar o valor de um atributo inteiro relacionado a um objeto.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por referęncia): indica o nome do atributo que se deseja recuperar.
valor (saída, passagem por referęncia): indica o valor do atributo, se a funçăo retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo năo existir, a funçăo retorna o valor 0 (zero).
********************************/
int GetValorIntObjeto(int idObjeto,char *indice,int *valor){
    return CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetValorInt(indice,*valor);
}

/********************************
A funçăo GetValorFloatObjeto() é responsável recuperar o valor de um atributo float relacionado a um objeto.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por valor): indica o nome do atributo que se deseja recuperar.
valor (saída, passagem por referęncia): indica o valor do atributo, se a funçăo retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo năo existir, a funçăo retorna o valor 0 (zero).
********************************/
int GetValorFloatObjeto(int idObjeto,char *indice,float *valor){
    return CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetValorFloat(indice,*valor);
}

/********************************
A funçăo GetValorStringObjeto() é responsável recuperar o valor de um atributo string relacionado a um objeto.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por valor): indica o nome do atributo que se deseja recuperar.
valor (saída, passagem por referęncia): indica o valor do atributo, se a funçăo retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo năo existir, a funçăo retorna o valor 0 (zero).
********************************/
int GetValorStringObjeto(int idObjeto,char *indice,char *valor){
    std::string str;
    bool resp = CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetValorString(indice,str);
    strcpy(valor,str.c_str());
    return resp;
}

/********************************
A funçăo GetXYObjeto() é responsável recuperar o valor da posiçăo (X,Y) do objeto de acordo com o sistema de coordenadas do jogo.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
posicaoX (saída, passagem por referencia): indica a posicao no eixo X do objeto.
posicaoY (saída, passagem por referencia): indica a posicao no eixo Y do objeto.
********************************/
void GetXYObjeto(int idObjeto,int *posicaoX,int *posicaoY){
    PIGPonto2D p = CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetXY();
    *posicaoX = p.x;
    *posicaoY = p.y;
}

/********************************
A funçăo MoveObjeto() é responsável por movimentar um determinado objeto para uma nova posiçăo informada.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto a ser movido.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usuário deseja reposicionar o objeto.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usuário deseja reposicionar o objeto.
********************************/
void MoveObjeto(int idObjeto,int posicaoX,int posicaoY){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->Move(posicaoX,posicaoY);
}

/********************************
A funçăo DeslocaObjeto() é responsável por deslocar um determinado objeto em relaçăo ŕ sua posiçăo atual.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto a ser movido.
deltaX (entrada, passagem por valor): valor a ser somado ou subtraído na componente X da posiçăo do objeto.
deltaY (entrada, passagem por valor): valor a ser somado ou subtraído na componente Y da posiçăo do objeto.
********************************/
void DeslocaObjeto(int idObjeto,int deltaX,int deltaY){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->Desloca(deltaX,deltaY);
}

/********************************
A funçăo SetAnguloObjeto() é responsável pela angulaçăo de determinado objeto. A angulaçăo é calculada em sentido
horário a partir do eixo X (0 graus). O objeto será desenhado com a angulaçăo informada no próximo comando
DesenhaObjeto(). A detecçăo de colisăo năo funciona com objetos fora da angulaçăo padrăo (0 graus).
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
angulo (entrada, passagem por valor): valor para indicar a angulaçăo do objeto em graus.
********************************/
void SetAnguloObjeto(int idObjeto, float angulo){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetAngulo(angulo);
}

/********************************
A funçăo GetAnguloObjeto() é responsável por recuperar o ângulo de rotaçăo de determinado objeto. A angulaçăo é calculada em sentido
horário a partir do eixo X (0 graus). O objeto será desenhado com a angulaçăo informada no próximo comando
DesenhaObjeto(). A detecçăo de colisăo năo funciona com objetos fora da angulaçăo padrăo (0 graus).
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
Retorno:
Retorna o valor do ângulo em graus.
********************************/
float GetAnguloObjeto(int idObjeto){
    return CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetAngulo();
}

/********************************
A funçăo SetPivoAbsolutoObjeto() define um ponto (X,Y) em relaçăo ao ponto (0,0) do objeto, sobre o qual o objeto será
rotacionado quando a funçăo SetAnguloObjeto() for executada.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
posicaoX (entrada, passagem por valor): Valor da coordenada X do pivô em relaçăo ao ponto (0,0) do objeto.
posicaoY (entrada, passagem por valor): Valor da coordenada Y do pivô em relaçăo ao ponto (0,0) do objeto.
********************************/
void SetPivoAbsolutoObjeto(int idObjeto,int posicaoX,int posicaoY){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetPivoAbsoluto({(double)posicaoX,(double)posicaoY});
}

/********************************
A funçăo SetPivoProporcionalObjeto() define um ponto (X,Y) proporcional ao tamanho do objeto, sobre o qual o objeto será
rotacionado quando a funçăo SetAnguloObjeto() for executada.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
relX (entrada, passagem por valor): porcentagem da largura do objeto onde ficará o pivô.
relY (entrada, passagem por valor): porcentagem da altura do objeto onde ficará o pivô.
********************************/
void SetPivoProporcionalObjeto(int idObjeto,float relX,float relY){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetPivoProporcional({relX,relY});
}

/********************************
A funçăo GetPivoObjeto() define um ponto (X,Y) em relaçăo ao ponto (0,0) do objeto, sobre o qual o objeto será
rotacionado quando a funçăo SetAnguloObjeto() for executada.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
posicaoX (saída, passagem por referęncia): Valor da coordenada X do pivô em relaçăo ao ponto (0,0) do objeto.
posicaoY (saída, passagem por referęncia): Valor da coordenada Y do pivô em relaçăo ao ponto (0,0) do objeto.
********************************/
void GetPivoObjeto(int idObjeto,int *posicaoX,int *posicaoY){
    PIGPonto2D p = CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetPivo();
    *posicaoX = p.x;
    *posicaoY = p.y;
}

/********************************
A funçăo SetFlipObjeto() é responsável por virar o objeto, invertendo-o em alguma direçăo. O objeto somente será
desenhado na nova orientaçăo no próximo comando DesenhaObjeto().
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto a ser virado.
valor (entrada, passagem por valor): valor do tipo de Flip. Pode ser PIG_FLIP_NENHUM (nenhum tipo de inversăo),
PIG_FLIP_HORIZONTAL (inverte da esquerda para a direita), PIG_FLIP_VERTICAL (inverte de cima para baixo),
ou PIG_FLIP_HORIZ_VERT (inverte da esquerda para direita e de cima para baixo).
********************************/
void SetFlipObjeto(int idObjeto,PIG_Flip valor){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetFlip(valor);
}

/********************************
A funçăo GetFlipObjeto() é responsável por recuperar o valor da manipulaçăo causada pela funçăo SetFlipObjeto().
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto a ser virado.
Retorno:
inteiro que indica o tipo de Flip. Pode ser PIG_FLIP_NENHUM (nenhum tipo de inversăo),
PIG_FLIP_HORIZONTAL (inverte da esquerda para a direita), PIG_FLIP_VERTICAL (inverte de cima para baixo),
ou PIG_FLIP_HORIZ_VERT (inverte da esquerda para direita e de cima para baixo).
********************************/
PIG_Flip GetFlipObjeto(int idObjeto){
    return CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetFlip();
}

/********************************
A funçăo SetDimensoesObjeto() é responsável por delimitar a altura e a largura do objeto que será desenhado na tela,
independentemente do tamanho original do arquivo de imagem.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
altura (entrada, passagem por valor): altura em pixels.
largura (entrada, passagem por valor): largura em pixels.
********************************/
void SetDimensoesObjeto(int idObjeto, int altura, int largura){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetDimensoes(altura,largura);
}

/********************************
A funçăo GetDimensoesObjeto() é responsável por recuperar a altura e a largura da área a ser usada
para desenhar o objeto na tela. Em outras palavras, representa o tamanho atual do objeto.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
altura (saída, passagem por referęncia): altura atual em pixels do objeto.
largura (saída, passagem por referęncia): largura atual em pixels do objeto.
********************************/
void GetDimensoesObjeto(int idObjeto, int *altura, int *largura){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetDimensoes(*altura,*largura);
}

/********************************
A funçăo GetDimensoesOriginaisObjeto() é responsável por recuperar a altura e a largura originais da imagem
que foi usada para criar o objeto. Qualquer utilizaçăo da funçăo SetDimensoesObjeto() é ignorada para
o cálculo desta funçăo.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
altura (saída, passagem por referęncia): altura original em pixels do objeto.
largura (saída, passagem por referęncia): largura original em pixels do objeto.
********************************/
void GetDimensoesOriginaisObjeto(int idObjeto, int *altura, int *largura){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetDimensoesOriginais(*altura,*largura);
}

/********************************
A funçăo RestauraDimensoesOriginaisObjeto() é responsável por restaurar o objeto com o tamanho original da imagem.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
********************************/
void RestauraDimensoesOriginaisObjeto(int idObjeto, int altura, int largura){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->RestauraDimensoesOriginais();
}


/********************************
A funçăo CriaFrameObjeto() é responsável por delimitar o posicionamento dos pixels do arquivo de imagem que serăo
utilizados para representar o objeto na tela. Desta forma, nem toda a imagem será automaticamente utilizada para
representar o objeto. O sistema de coordenadas deve ser o padrăo dos arquivos de imagem, com o eixo Y aumentando para baixo.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto a ser desenhado.
idFrame (entrada, passagem por valor): identificador do frame a ser criado.
xBitmap (entrada, passagem por valor): indica a posiçăo de eixo X onde começa o frame.
yBitmap (entrada, passagem por valor): indica a posiçăo de eixo Y onde começa o frame. Neste caso, o eixo Y aumenta para baixo.
altura (entrada, passagem por valor): altura em pixels do frame.
largura (entrada, passagem por valor): largura em pixels do frame.
********************************/
void CriaFrameObjeto(int idObjeto, int idFrame, int xBitmap, int yBitmap, int altura, int largura){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->DefineFrame(idFrame, {xBitmap,yBitmap,largura,largura});
}


/********************************
A funçăo CarregaArquivoFramesObjeto() é responsável por ler de arquivo texto os frames de um objeto.
Cada linha do arquivo texto deve conter 5 números inteiros: o número do frame, a posiçăo do frame no eixo X do arquivo de imagem,
a posiçăo do frame no eixo Y do arquivo de imagem, a altura do frame e a largura do frame (todas as unidades em pixels).
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
nomeArq (entrada, passagem por referęncia): nome do arquivo texto contendo os frames.
********************************/
void CarregaArquivoFramesObjeto(int idObjeto, char *nomeArq){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->CarregaArquivoFrames(nomeArq);
}

/********************************
A funçăo CarregaFramesPorLinhaObjeto() é responsável por subdividir o arquivo de imagem em linhas (de mesmo tamanho) e colunas (de mesmo tamanho).
Cada subdivisăo representará um frame que será automaticamente criado para a animaçăo, com numeraçăo incremental a partir do parâmetro "frameInicial".
Ao final das "qtdColunas" da primeira linha, a definiçăo dos frames continua na linha inferior.
A funçăo pode ser utilizada em spritesheets regulares.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
frameInicial (entrada, passagem por valor): numeraçăo do primeiro frame a ser criado pela funçăo. Os demais frames terăo numeraçăo consecutiva.
qtdLinhas (entrada, passagem por valor): quantidade de linhas na qual o arquivo de imagem será dividido.
qtdColunas (entrada, passagem por valor): quantidade de colunas na qual o arquivo de imagem será dividido.
********************************/
void CarregaFramesPorLinhaObjeto(int idObjeto, int frameInicial, int qtdLinhas, int qtdColunas){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->CriaFramesAutomaticosPorLinha(frameInicial,qtdLinhas,qtdColunas);
}

/********************************
A funçăo CarregaFramesPorColunaObjeto() é responsável por subdividir o arquivo de imagem em linhas (de mesmo tamanho) e colunas (de mesmo tamanho).
Cada subdivisăo representará um frame que será automaticamente criado para a animaçăo, com numeraçăo incremental a partir do parâmetro "frameInicial".
Ao final das "qtdLinhas" da primeira coluna, a definiçăo dos frames continua na coluna seguinte.
A funçăo pode ser utilizada em spritesheets regulares.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
frameInicial (entrada, passagem por valor): numeraçăo do primeiro frame a ser criado pela funçăo. Os demais frames terăo numeraçăo consecutiva.
qtdLinhas (entrada, passagem por valor): quantidade de linhas na qual o arquivo de imagem será dividido.
qtdColunas (entrada, passagem por valor): quantidade de colunas na qual o arquivo de imagem será dividido.
********************************/
void CarregaFramesPorColunaObjeto(int idObjeto, int frameInicial, int qtdLinhas, int qtdColunas){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->CriaFramesAutomaticosPorColuna(frameInicial,qtdLinhas,qtdColunas);
}

/********************************
A funçăo MudaFrameObjeto() é responsável por modificar o frame (já definido pela funçăo DefineFrameObjeto) de um objeto
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
idFrame (entrada, passagem por valor): identificador do frame já criado.
Retorno:
Se o identifador do frame informado năo corresponder a um frame já criado, o valor de retorno é igual a 0. Caso contrário, é igual a 1.
********************************/
int MudaFrameObjeto(int idObjeto, int idFrame){
    return CPIGGerenciadorSprites::GetObjeto(idObjeto)->MudaFrameAtual(idFrame);
}

/********************************
A funçăo SetColoracaoObjeto() é responsável por mesclar uma determinada cor com os pixels do arquivo de imagem.
Após a modificaçăo, todos os desenhos deste objeto serăo mostrados já com a mesclagem definida.
Para voltar ao padrăo original de pixels, deve-se chamar a funçăo, passando a cor branca (255,255,255).
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto a ser desenhado.
cor (entrada,passagem por valor): cor do sistema RGB utilizada para mesclagem com o arquivo de imagem
********************************/
void SetColoracaoObjeto(int idObjeto, PIG_Cor cor){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetColoracao(cor);
}

/********************************
A funçăo SetOpacidadeObjeto() é responsável por modificar o nível de opacidade do objeto.
O nível de opacidade varia de 0-255, sendo 0 totalmente transparente e 255 totalmente opaco.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
valor (entrada,passagem por valor): nível de opacidade do objeto na faixa 0-255.
********************************/
void SetOpacidadeObjeto(int idObjeto,int valor){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetOpacidade(valor);
}

/********************************
A funçăo GetOpacidadeObjeto() é responsável por recuperar o nível de opacidade de determinado objeto.
O nível de opacidade varia de 0-255, sendo 0 totalmente transparente e 255 totalmente opaco.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
Retorno:
Retorna o nível de opacidade do objeto na faixa 0-255.
********************************/
int GetOpacidadeObjeto(int idObjeto){
    return CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetOpacidade();
}

/********************************
A funçăo DesenhaObjeto() é responsável por desenhar um objeto na tela. O objeto será desenhado de acordo com todas as definiçőes
de posiçăo e ângulo informado até o momento. Além disso, se o objeto estiver virado (flipping), isso também será levado em consideraçăo.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto a ser desenhado.
********************************/
void DesenhaObjeto(int idObjeto){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->Desenha();
}

/********************************
A funçăo DesenhaObjetoOffScreen() é responsável por desenhar um objeto no Renderizador Offscreen. O objeto será desenhado de acordo com todas as definiçőes
de posiçăo e ângulo informado até o momento. Além disso, se o objeto estiver virado (flipping), isso também será levado em consideraçăo.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto a ser desenhado.
offScreen (entrada, passagem por valor): indica se o objeto deve ser desenhado no Renderizador Offscreen.
********************************/
void DesenhaObjetoOffScreen(int idObjeto){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->DesenhaOffScreen(jogo->GetOffScreenRender());
}

/********************************
A funçăo TestaColisaoObjetos() é responsável por testar se dois objetos se colidiram ou năo, ao passar
os identificadores dos objetos por parâmetro.
Parâmetros:
idObjeto1 (entrada, passagem por valor): identificador do primeiro objeto.
idObjeto2 (entrada, passagem por valor): identificador do segundo objeto.
Retorno:
Inteiro indicando se houve colisăo (valor diferente de zero) ou năo (valor igual a 0, zero).
********************************/
int TestaColisaoObjetos(int idObjeto1,int idObjeto2){
    return CPIGGerenciadorSprites::GetObjeto(idObjeto1)->Colisao(CPIGGerenciadorSprites::GetObjeto(idObjeto2))
           &&CPIGGerenciadorSprites::GetObjeto(idObjeto2)->Colisao(CPIGGerenciadorSprites::GetObjeto(idObjeto1));
}

/********************************
A funçăo DefineAreaColisaoObjeto() é responsável estabelecer um polígono que será utilizado como área de colisăo do objeto com os demais.
Os vetores X e Y deve ter pelo menos qtdPontos elementos.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
pontosX (entrada, passagem por referęncia): vetor de inteiros, de tamanho qtdPontos, contendo os valores X de cada ponto do polígono.
pontosY (entrada, passagem por referęncia): vetor de inteiros, de tamanho qtdPontos, contendo os valores Y de cada ponto do polígono.
qtdPontos (entrada, passagem por valor): quantidade de pontos do polígono.
********************************/
void DefineAreaColisaoObjeto(int idObjeto, int pontosX[], int pontosY[], int qtdPontos) {
    std::vector<PIGPonto2D> vertices;

    for (int i = 0; i < qtdPontos; i++) {
        vertices.push_back({(double)pontosX[i],(double) pontosY[i]});
    }

    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetVertices(vertices);
}

/********************************
A funçăo DefineRaioColisaoObjeto() é responsável por estabelecer um raio, em relaçăo ao pivô do objeto, que será utilizado para teste de colisăo circular deste objeto com os demais.
A definiçăo do raio só será útil se o tipode colisăo deste objeto for circular, definido pela funçăo DefineTipoColisaoObjeto().
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
raio (entrada, passagem por valor): tamanho do raio que formará a área de colisăo deste objeto.
********************************/
void DefineRaioColisaoObjeto(int idObjeto, float raio){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetRaioColisaoCircular(raio);
}

/********************************
A funçăo DefineTipoColisaoObjeto() é responsável por definir o tipod e colisăo que será utilizada por este objeto com os demais.
É possível ter 3 tipos de colisăo: por bouding-box (PIG_COLISAO_OOBB - área de colisăo delimitada pelo ponto X,Y do objeto, sua altura e largura e rotaçăo),
por polígono (PIG_COLISAO_POLIGONO) área de colisăo formada por pontos genéricos) e circular (PIG_COLISAO_CIRCULAR) área de colisăo em forma de círculo, com raio definido a partir do ponto pivô)
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
modo (entrada, passagem por valor): modo de colisăo a ser utilizado por este objeto.
********************************/
void DefineTipoColisaoObjeto(int idObjeto, PIG_ModoColisao modo){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetModoColisao(modo);
}

/********************************
A funçăo GetPixelsObjeto() é responsável por extrair os pixels da imagem que originou o objeto, devolvendo-os como
uma matriz de pixels (PIG_Cor). Mudanças nessa matriz só serăo validadas após a chamada da funçăo AtualizaPixelsObjeto().
O linha 0 corresponde ŕ primeira linha da imagem, ou seja, ŕ linha superior, pois o sistema de coordenadas
das imagens tem o eixo Y aumentando para baixo.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
Retorno:
matriz de pixels (PIG_Cor) da imagem que gerou o objeto. O total de linhas da matriz é dado pela altura original do objeto e o
total de colunas é dado pela largura original do objeto. Ambos os valores podem ser obtidos pela funçăo GetDimensoesOriginaisObjeto().
********************************/
PIG_Cor **GetPixelsObjeto(int idObjeto){
    return CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetPixels();
}

/********************************
A funçăo AtualizaPixelsObjeto() é responsável por efetivar quaisquer mudanças nos pixels do objeto obtidos pela funçăo GetPixelsObjeto().
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
retiraFundo (entrada, passagem por valor): inteiro que indica se o fundo da imagem deve ser retirado ou năo ao ler o arquivo em questăo. O valor padrăo é 1, indicando que o fundo deve ser retirado.
********************************/
void AtualizaPixelsObjeto(int idObjeto,int retiraFundo=1){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->AtualizaPixels(retiraFundo);
}

/********************************
A funçăo InsereTransicaoObjeto() é responsável por criar e inserir uma nova transiçăo ao final de sequęncia de transiçőes do objeto.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
tempo (entrada, passagem por valor): duracao (em segundos) da transiçăo.
deltaX (entrada, passagem por valor): diferença da posiçăo no eixo X em relaçăo ŕ posiçăo do objeto no início da transiçăo.
deltaY (entrada, passagem por valor): diferença da posiçăo no eixo Y em relaçăo ŕ posiçăo do objeto no início da transiçăo.
deltaAltura (entrada, passagem por valor): diferença da altura do objeto em relaçăo ao início da transiçăo.
deltaLargura (entrada, passagem por valor): diferença da largura do objeto em relaçăo ao início da transiçăo.
deltaAngulo (entrada, passagem por valor): diferença de ângulo (em graus) do objeto em relaçăo ao início da transiçăo.
corFinal (entrada, passagem por valor): coloraçăo do objeto ao final da transiçăo.
deltaOpacidade (entrada, passagem por valor): diferença do nível de opacidade do objeto em relaçăo ao início da transiçăo.
********************************/
void InsereTransicaoObjeto(int idObjeto,double tempo,int deltaX,int deltaY,int deltaAltura,int deltaLargura,double deltaAngulo,PIG_Cor corFinal,int deltaOpacidade){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->InsereTransicao(tempo,{deltaX,deltaY,deltaAltura,deltaLargura,deltaAngulo,corFinal,deltaOpacidade});
}

/********************************
A funçăo ExecutandoTransicaoObjeto() retorna a informaçăo sobre a execuçăo (neste momento) de transiçőes do objeto.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
Retorno:
inteiro que indica se o objeto está executando alguma transiçăo no momento (valor diferente de 0) ou năo (valor igual a 0).
********************************/
int ExecutandoTransicaoObjeto(int idObjeto){
    return CPIGGerenciadorSprites::GetObjeto(idObjeto)->ExecutandoTransicao();
}

/********************************
A funçăo LeArquivoTransicaoObjeto() é responsável por ler, criar e inserir as transiçőes para um objeto, provenientes de um arquivo texto.
Cada linha do arquivo texto corresponde a uma transiçăo (em ordem) e deve possuir 11 valores:
1) um double representando a duracao (em segundos) da transiçăo.
2) um inteiro representando a diferença da posiçăo no eixo X em relaçăo ŕ posiçăo do objeto no início da transiçăo.
3) um inteiro representando a diferença da posiçăo no eixo Y em relaçăo ŕ posiçăo do objeto no início da transiçăo.
4) um inteiro representando a diferença da altura do objeto em relaçăo ao início da transiçăo.
5) um inteiro representando a diferença da largura do objeto em relaçăo ao início da transiçăo.
6) um double representando a diferença de ângulo (em graus) do objeto em relaçăo ao início da transiçăo.
7) um inteiro representando a componente R (vermelho) da coloraçăo do objeto ao final da transiçăo.
8) um inteiro representando a componente G (verde) da coloraçăo do objeto ao final da transiçăo.
9) um inteiro representando a componente B (azul) da coloraçăo do objeto ao final da transiçăo.
10) um inteiro representando a componente A (canal alfa) da coloraçăo do objeto ao final da transiçăo.
11) um inteiro representando a diferença do nível de opacidade do objeto em relaçăo ao início da transiçăo.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
nomeArq (entrada, passagem por referęncia): nome com extensăo do arquivo texto contendo as transiçőes.
********************************/
void LeArquivoTransicaoObjeto(int idObjeto,char *nomeArq){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->LeTransicoes(nomeArq);
}

/********************************
A funçăo IniciaAutomacaoObjeto() é responsável por iniciar as transiçőes já inseridas no objeto, de acordo como o tipo de transiçăo informada.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
********************************/
void IniciaAutomacaoObjeto(int idObjeto){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->IniciaAutomacao();
}

/********************************
A funçăo TrataAutomacaoObjeto() é responsável por calcular o estado da transiçăo corrente do objeto e aplicar essas modificaçăo a ela.
A funçăo deve ser chamada a cada frame, para ter resultados mais precisos.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
********************************/
void TrataAutomacaoObjeto(int idObjeto){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->TrataAutomacao();
}

/********************************
A funçăo PausaAutomacaoObjeto() é responsável por pausar as transições e ações associadas a um objeto.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
********************************/
void PausaAutomacaoObjeto(int idObjeto){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->PausaAutomacao();
}

/********************************
A funçăo DespausaAutomacaoObjeto() é responsável por despausar as transições e ações associadas a um objeto.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
********************************/
void DespausaAutomacaoObjeto(int idObjeto){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->DespausaAutomacao();
}

/********************************
A funçăo DefineTipoTransicaoObjeto() é responsável por determinar como a sequęncia de transiçőes será executada.
É possível fazę-la uma única vez (PIG_TRANSICAO_NORMAL), em loop (PIG_TRANSICAO_LOOP) ou indo até o final da sequęncia e retornando, em vai-vém (PIG_TRANSICAO_VAIVEM).
A funçăo deve ser chamada a cada frame, para ter resultados mais precisos.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
********************************/
void DefineTipoTransicaoObjeto(int idObjeto,PIG_TipoTransicao valor){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->DefineTipoTransicao(valor);
}

/********************************
A funçăo LimpaTransicoesObjeto() é responsável por remover a sequęncia de transiçőes do objeto.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
********************************/
void LimpaTransicoesObjeto(int idObjeto){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->LimpaTransicoes();
}

/********************************
A funçăo InsereAcaoObjeto() é responsável por inserir na linha de tempo de automaçăo do objeto uma açăo a ser executada.
A açăo é composta por uma funçăo "acao" que será executada quando a linha de tempo atingir o parâmetro "tempo" e será repetida a cada "repeticao" segundos.
A açăo pode armazenar um ponteiro genérico "param" que será utilizado na chamada da funçăo.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
tempo (entrada, passagem por valor): tempo (em segundos) da primeira chamada da funçăo.
repeticao (entrada, passagem por valor): tempo (em segundos) entre a chamada anterior e a próxima. O valor -1 indica que a funçăo năo será repetida.
param (entrada, passagem por referęncia): ponteiro genérico para um valor que será utilizado na chamada da funçăo.
********************************/
void InsereAcaoObjeto(int idObjeto,double tempo,double repeticao,PIG_FuncaoSimples acao,void *param){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->InsereAcao(tempo,repeticao,acao,param);
}

/********************************
A funçăo LimpaAcoesObjeto() é responsável por remover as ações restantes associadas ao objeto.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
********************************/
void LimpaAcoesObjeto(int idObjeto){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->LimpaAcoes();
}


/********************************
Seçăo de gerador de partículas
********************************/

/********************************
A funçăo CriaGeradorParticulas() cria um novo gerador de partículas (GDP). As partículas em si precisam ser criadas
posteriormente através da funçăo CriaParticula(), passando o identificador do GDP como parâmetro.
Parâmetros:
maxParticulas (entrada, passagem por valor): informa o maior número de partículas que o gerador terá simultaneamente. O maior valor aceito é PIG_MAX_PARTICULAS partículas.
nomeArquivo (entrada, passagem por referęncia): indica o caminho relativo ou absoluto do arquivo de imagem,
que será utilizado para cada partícula do GDP.
audioCriacao (entrada, passagem por valor năo-obrigatório): indica qual audio previamente criado deve ser tocado quando uma partícula for efetivamente criada.
audioEncerramento (entrada, passagem por valor năo-obrigatório): indica qual audio previamente criado deve ser tocado quando uma partícula for destruida por acabar o tempo de vida ou por sair da área de ativaçăo.
retiraFundo (entrada, passagem por valor): inteiro que indica se o fundo da imagem deve ser retirado ou năo ao ler o arquivo em questăo. O valor padrăo é 1, indicando que o fundo deve ser retirado.
corFundo (entrada, passagem por referęncia năo-obrigatório): indica se há uma cor específica para ser considerada como cor de fundo da imagem. Caso, o valor seja NULL, mas o parâmetro retiraFundo seja diferente de 0, o pixel (0,0) da imagem será considerado como cor de fundo.
idJanela (entrada, passagem por valor năo-obrigatório): indica qual janela vai receber o GDP.
********************************/
int CriaGeradorParticulas(int maxParticulas,char* nomeArquivo,int audioCriacao=-1,int audioEncerramento=-1,int retiraFundo=1,PIG_Cor *corFundo=NULL, int idJanela=0){
    return CPIGGerenciadorGDP::CriaGeradorParticulas(maxParticulas,nomeArquivo,audioCriacao,audioEncerramento,retiraFundo,corFundo,idJanela);
}

/********************************
A funçăo CriaGeradorParticulasPorAnimacao() cria um novo gerador de partículas (GDP). As partículas em si precisam ser criadas
posteriormente através da funçăo CriaParticula(), passando o identificador do GDP como parâmetro. As partículas serăo semelhantes a uma animaçăo já criada anteriormente
que é indicada pelo parâmetro idAnimaçăo.
Parâmetros:
maxParticulas (entrada, passagem por valor): informa o maior número de partículas que o gerador terá simultaneamente. O maior valor aceito é PIG_MAX_PARTICULAS partículas.
idAnimacao (entrada, passagem por referęncia): identificador da animaçăo (já criada anteriormente) que será utilizada
para cada partícula do GDP.
audioCriacao (entrada, passagem por valor năo-obrigatório): indica qual audio previamente criado deve ser tocado quando uma partícula for efetivamente criada.
audioEncerramento (entrada, passagem por valor năo-obrigatório): indica qual audio previamente criado deve ser tocado quando uma partícula for destruida por acabar o tempo de vida ou por sair da área de ativaçăo.
retiraFundo (entrada, passagem por valor): inteiro que indica se o fundo da imagem deve ser retirado ou năo ao ler o arquivo em questăo. O valor padrăo é 1, indicando que o fundo deve ser retirado.
corFundo (entrada, passagem por referęncia năo-obrigatório): indica se há uma cor específica para ser considerada como cor de fundo da imagem. Caso, o valor seja NULL, mas o parâmetro retiraFundo seja diferente de 0, o pixel (0,0) da imagem será considerado como cor de fundo.
idJanela (entrada, passagem por valor năo-obrigatório): indica qual janela vai receber o GDP.
********************************/
int CriaGeradorParticulasPorAnimacao(int maxParticulas,int idAnimacao,int audioCriacao=-1,int audioEncerramento=-1,int retiraFundo=1,PIG_Cor *corFundo=NULL,int idJanela=0){
    return CPIGGerenciadorGDP::CriaGeradorParticulas(maxParticulas,CPIGGerenciadorSprites::GetAnimacao(idAnimacao),audioCriacao,audioEncerramento,retiraFundo,corFundo,idJanela);
}

/********************************
A funçăo CriaGeradorParticulasPorObjeto() cria um novo gerador de partículas (GDP). As partículas em si precisam ser criadas
posteriormente através da funçăo CriaParticula(), passando o identificador do GDP como parâmetro. As partículas serăo semelhantes a um objeto já criado anteriormente
que é indicado pelo parâmetro idObjeto.
Parâmetros:
maxParticulas (entrada, passagem por valor): informa o maior número de partículas que o gerador terá simultaneamente. O maior valor aceito é PIG_MAX_PARTICULAS partículas.
idObjeto (entrada, passagem por referęncia): identificador do objeto (já criado anteriormente) que será utilizado
para cada partícula do GDP.
audioCriacao (entrada, passagem por valor năo-obrigatório): indica qual audio previamente criado deve ser tocado quando uma partícula for efetivamente criada.
audioEncerramento (entrada, passagem por valor năo-obrigatório): indica qual audio previamente criado deve ser tocado quando uma partícula for destruida por acabar o tempo de vida ou por sair da área de ativaçăo.
retiraFundo (entrada, passagem por valor): inteiro que indica se o fundo da imagem deve ser retirado ou năo ao ler o arquivo em questăo. O valor padrăo é 1, indicando que o fundo deve ser retirado.
corFundo (entrada, passagem por referęncia năo-obrigatório): indica se há uma cor específica para ser considerada como cor de fundo da imagem. Caso, o valor seja NULL, mas o parâmetro retiraFundo seja diferente de 0, o pixel (0,0) da imagem será considerado como cor de fundo.
idJanela (entrada, passagem por valor năo-obrigatório): indica qual janela vai receber o GDP.
********************************/
int CriaGeradorParticulasPorObjeto(int maxParticulas,int idObjeto,int audioCriacao=-1,int audioEncerramento=-1,int retiraFundo=1,PIG_Cor *corFundo=NULL,int idJanela=0){
    return CPIGGerenciadorGDP::CriaGeradorParticulas(maxParticulas,CPIGGerenciadorSprites::GetObjeto(idObjeto),audioCriacao,audioEncerramento,retiraFundo,corFundo,idJanela);
}

/********************************
A funçăo DestroiGeradorParticulas() encerra um gerador de partículas (GDP). Todas as partículas relacionadas a ele também săo finalizadas
neste momento.
Parâmetros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da funçăo CriaGeradorParticulas().
********************************/
void DestroiGeradorParticulas(int idGerador){
    CPIGGerenciadorGDP::DestroiGeradorParticulas(idGerador);
}

/********************************
A funçăo MoveGeradorParticulas() reposiciona um gerador de partículas (GDP). Na prática, isto significa que as novas partículas que
forem criadas posteriormente terăo esse ponto de origem.
Parâmetros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da funçăo CriaGeradorParticulas().
posicaoX (entrada, passagem por valor): informa a nova posiçăo X do GDP, em relaçăo ao sistema de coordenadas do jogo.
posicaoY (entrada, passagem por valor): informa a nova posiçăo Y do GDP, em relaçăo ao sistema de coordenadas do jogo.
********************************/
void MoveGeradorParticulas(int idGerador,int posicaoX,int posicaoY){
    CPIGGerenciadorGDP::GetGerador(idGerador)->Move(posicaoX,posicaoY);
}

/********************************
A funçăo DeslocaGeradorParticulas() é responsável por deslocar uma determinado gerador de partículas (GDP) em relaçăo ŕ sua posiçăo atual.
Parâmetros:
idGerador (entrada, passagem por valor): identificador do GDP a ser deslocada.
deltaX (entrada, passagem por valor): valor a ser somado ou subtraído na componente X da posiçăo do GDP.
deltaY (entrada, passagem por valor): valor a ser somado ou subtraído na componente Y da posiçăo do GDP.
********************************/
void DeslocaGeradorParticulas(int idGerador,int deltaX,int deltaY){
    CPIGGerenciadorGDP::GetGerador(idGerador)->Desloca(deltaX,deltaY);
}

/*
/********************************
A funçăo MudaDirecaoParticulas() modifica a direçăo na qual as partículas se movimentarăo após serem criadas.
Somente as partículas criadas posteriormente seguirăo a direçăo especificada.
Parâmetros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da funçăo CriaGeradorParticulas().
valorX (entrada, passagem por valor): informa a componente X da direçăo a ser definida para as partículas.
valorY (entrada, passagem por valor): informa a componente Y da direçăo a ser definida para as partículas.
********************************/
//void MudaDirecaoParticulas(int idGerador,int valorX,int valorY){
    //CPIGGerenciadorParticulas::GetGerador(idGerador)->MudaDirecao(valorX,valorY);
//}

/********************************
A funçăo InsereTransicaoParticulas() é responsável por criar e inserir uma nova transiçăo ao final de sequęncia de transiçőes das partículas do gerador.
Parâmetros:
idGerador (entrada, passagem por valor): identificador do gerador.
tempo (entrada, passagem por valor): duracao (em segundos) da transiçăo das partículas.
deltaX (entrada, passagem por valor): diferença da posiçăo no eixo X em relaçăo ŕ posiçăo das partículas no início da transiçăo.
deltaY (entrada, passagem por valor): diferença da posiçăo no eixo Y em relaçăo ŕ posiçăo das partículas no início da transiçăo.
deltaAltura (entrada, passagem por valor): diferença da altura das partículas em relaçăo ao início da transiçăo.
deltaLargura (entrada, passagem por valor): diferença da largura das partículas em relaçăo ao início da transiçăo.
deltaAngulo (entrada, passagem por valor): diferença de ângulo (em graus) das partículas em relaçăo ao início da transiçăo.
corFinal (entrada, passagem por valor): coloraçăo das partículas ao final da transiçăo.
deltaOpacidade (entrada, passagem por valor): diferença do nível de opacidade das partículas em relaçăo ao início da transiçăo.
********************************/
void InsereTransicaoParticulas(int idGerador,double tempo,int deltaX,int deltaY,int deltaAlt,int deltaLarg,double deltaAng,PIG_Cor corFinal, int deltaOpacidade){
    CPIGGerenciadorGDP::GetGerador(idGerador)->InsereTransicao(tempo,{deltaX,deltaY,deltaAlt,deltaLarg,deltaAng,corFinal,deltaOpacidade});
}

/********************************
A funçăo DefineTipoTransicaoParticulas() é responsável por determinar como a sequęncia de transiçőes das partículas do gerador será executada.
É possível fazę-la uma única vez (PIG_TRANSICAO_NORMAL), em loop (PIG_TRANSICAO_LOOP) ou indo até o final da sequęncia e retornando, em vai-vém (PIG_TRANSICAO_VAIVEM).
A funçăo deve ser chamada a cada frame, para ter resultados mais precisos.
Parâmetros:
idGerador (entrada, passagem por valor): identificador do gerador.
********************************/
void DefineTipoTransicaoParticulas(int idGerador,PIG_TipoTransicao valor){
    CPIGGerenciadorGDP::GetGerador(idGerador)->DefineTipoTransicao(valor);
}

/********************************
A funçăo LimpaTransicoesParticulas() é responsável por remover a sequęncia de transiçőes das partículas do gerador.
Parâmetros:
idGerador (entrada, passagem por valor): identificador do gerador de partículas.
********************************/
void LimpaTransicoesParticulas(int idGerador){
    CPIGGerenciadorGDP::GetGerador(idGerador)->LimpaTransicoes();
}

/********************************
A funçăo InsereTransicaoGDP() é responsável por criar e inserir uma nova transiçăo ao final de sequęncia de transiçőes do gerador em si.
Essa transiçăo modifica as características do gerador, que podem se refletir também nas características das partículas que serăo posteriormente criadas usando o próprio gerador como modelo.
Parâmetros:
idGerador (entrada, passagem por valor): identificador do gerador.
tempo (entrada, passagem por valor): duracao (em segundos) da transiçăo do gerador.
deltaX (entrada, passagem por valor): diferença da posiçăo no eixo X em relaçăo ŕ posiçăo do gerador no início da transiçăo.
deltaY (entrada, passagem por valor): diferença da posiçăo no eixo Y em relaçăo ŕ posiçăo do gerador no início da transiçăo.
deltaAltura (entrada, passagem por valor): diferença da altura que o modelo terá em relaçăo ao início da transiçăo.
deltaLargura (entrada, passagem por valor): diferença da largura que o modelo terá em relaçăo ao início da transiçăo.
deltaAngulo (entrada, passagem por valor): diferença de ângulo (em graus) que o modelo terá em relaçăo ao início da transiçăo.
corFinal (entrada, passagem por valor): coloraçăo que o modelo terá ao final da transiçăo.
deltaOpacidade (entrada, passagem por valor): diferença do nível de opacidade que o modelo terá em relaçăo ao início da transiçăo.
********************************/
void InsereTransicaoGDP(int idGerador,double tempo,int deltaX,int deltaY,int deltaAlt,int deltaLarg,double deltaAng,PIG_Cor corFinal, int deltaOpacidade){
    CPIGGerenciadorGDP::GetGerador(idGerador)->InsereTransicaoGDP(tempo,{deltaX,deltaY,deltaAlt,deltaLarg,deltaAng,corFinal,deltaOpacidade});
}

/********************************
A funçăo LeArquivoTransicaoGDP() é responsável por ler, criar e inserir as transiçőes para um gerador, provenientes de um arquivo texto.
Cada linha do arquivo texto corresponde a uma transiçăo (em ordem) e deve possuir 11 valores:
1) um double representando a duracao (em segundos) da transiçăo.
2) um inteiro representando a diferença da posiçăo no eixo X em relaçăo ŕ posiçăo do gerador no início da transiçăo.
3) um inteiro representando a diferença da posiçăo no eixo Y em relaçăo ŕ posiçăo do gerador no início da transiçăo.
4) um inteiro representando a diferença da altura do modelo em relaçăo ao início da transiçăo.
5) um inteiro representando a diferença da largura do modelo em relaçăo ao início da transiçăo.
6) um double representando a diferença de ângulo (em graus) do modelo em relaçăo ao início da transiçăo.
7) um inteiro representando a componente R (vermelho) da coloraçăo do modelo ao final da transiçăo.
8) um inteiro representando a componente G (verde) da coloraçăo do modelo ao final da transiçăo.
9) um inteiro representando a componente B (azul) da coloraçăo do modelo ao final da transiçăo.
10) um inteiro representando a componente A (canal alfa) da coloraçăo do modelo ao final da transiçăo.
11) um inteiro representando a diferença do nível de opacidade do modelo em relaçăo ao início da transiçăo.
Parâmetros:
idGerador (entrada, passagem por valor): identificador do gerador.
nomeArq (entrada, passagem por referęncia): nome com extensăo do arquivo texto contendo as transiçőes.
********************************/
void LeTransicoesGDP(int idGerador,string nomeArq){
    CPIGGerenciadorGDP::GetGerador(idGerador)->LeTransicoesGDP(nomeArq);
}

/********************************
A funçăo IniciaAutomacaoGDP() é responsável por iniciar as transiçőes já inseridas no gerador, de acordo como o tipo de transiçăo informada.
Parâmetros:
idGerador (entrada, passagem por valor): identificador do gerador.
********************************/
void IniciaAutomacaoGDP(int idGerador){
    CPIGGerenciadorGDP::GetGerador(idGerador)->IniciaAutomacaoGDP();
}

/********************************
A funçăo LimpaTransicoesGDP() é responsável por remover a sequęncia de transiçőes do gerador de partículas em si.
Parâmetros:
idGerador (entrada, passagem por valor): identificador do gerador de partículas.
********************************/
void LimpaTransicoesGDP(int idGerador){
    CPIGGerenciadorGDP::GetGerador(idGerador)->LimpaTransicoesGDP();
}

/********************************
A funçăo ExecutandoTransicaoGDP() retorna a informaçăo sobre a execuçăo (neste momento) de transiçőes do gerador.
Parâmetros:
idGerador (entrada, passagem por valor): identificador do gerador.
Retorno:
inteiro que indica se o gerador está executando alguma transiçăo no momento (valor diferente de 0) ou năo (valor igual a 0).
********************************/
bool ExecutandoTransicaoGDP(int idGerador){
    return CPIGGerenciadorGDP::GetGerador(idGerador)->ExecutandoTransicaoGDP();
}

/********************************
A funçăo TrataAutomacaoGDP() é responsável por calcular o estado da transiçăo corrente do gerador e aplicar essas modificaçăo a ela.
A funçăo deve ser chamada a cada frame, para ter resultados mais precisos.
Parâmetros:
idGerador (entrada, passagem por valor): identificador do gerador.
********************************/
void TrataAutomacaoGDP(int idGerador){
    CPIGGerenciadorGDP::GetGerador(idGerador)->TrataAutomacaoGDP();
}

/********************************
A funçăo PausaAutomacaoGDP() é responsável por pausar as transições e ações associadas a um gerador.
Parâmetros:
idGerador (entrada, passagem por valor): identificador do gerador.
********************************/
void PausaAutomacaoGDP(int idGerador){
    CPIGGerenciadorGDP::GetGerador(idGerador)->PausaAutomacao();
}

/********************************
A funçăo DespausaAutomacaoGDP() é responsável por despausar as transições e ações associadas a um gerador.
Parâmetros:
idGerador (entrada, passagem por valor): identificador do gerador.
********************************/
void DespausaAutomacaoGDP(int idGerador){
    CPIGGerenciadorGDP::GetGerador(idGerador)->DespausaAutomacao();
}

/********************************
A funçăo InsereAcaoGDP() é responsável por inserir na linha de tempo de automaçăo do gerador uma açăo a ser executada.
A açăo é composta por uma funçăo "acao" que será executada quando a linha de tempo atingir o parâmetro "tempo" e será repetida a cada "repeticao" segundos.
A açăo pode armazenar um ponteiro genérico "param" que será utilizado na chamada da funçăo.
Parâmetros:
idGerador (entrada, passagem por valor): identificador do gerador.
tempo (entrada, passagem por valor): tempo (em segundos) da primeira chamada da funçăo.
repeticao (entrada, passagem por valor): tempo (em segundos) entre a chamada anterior e a próxima. O valor -1 indica que a funçăo năo será repetida.
param (entrada, passagem por referęncia): ponteiro genérico para um valor que será utilizado na chamada da funçăo.
********************************/
void InsereAcaoGDP(int idGerador,double tempo, double repeticao, PIG_FuncaoSimples acao, void *param){
    CPIGGerenciadorGDP::GetGerador(idGerador)->InsereAcaoGDP(tempo,repeticao,acao,param);
}

/********************************
A funçăo LimpaAcoesGDP() é responsável por remover as ações restantes associadas ao gerador.
Parâmetros:
idGerador (entrada, passagem por valor): identificador do gerador.
********************************/
void LimpaAcoesGDP(int idGerador){
    CPIGGerenciadorGDP::GetGerador(idGerador)->LimpaAcoes();
}

/********************************
A funçăo DefineTipoTransicaoGDP() é responsável por determinar como a sequęncia de transiçőes do gerador de partículas será executada.
É possível fazę-la uma única vez (PIG_TRANSICAO_NORMAL), em loop (PIG_TRANSICAO_LOOP) ou indo até o final da sequęncia e retornando, em vai-vém (PIG_TRANSICAO_VAIVEM).
A funçăo deve ser chamada a cada frame, para ter resultados mais precisos.
Parâmetros:
idGerador (entrada, passagem por valor): identificador do gerador.
********************************/
void DefineTipoTransicaoGDP(int idGerador,PIG_TipoTransicao tipo){
    CPIGGerenciadorGDP::GetGerador(idGerador)->DefineTipoTransicaoGDP(tipo);
}

/********************************
A funçăo SetAnguloParticulas() modifica o ângulo de desenho das partículas após serem criadas.
Somente as partículas criadas posteriormente terăo o ângulo especificada.
Parâmetros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da funçăo CriaGeradorParticulas().
angulo (entrada, passagem por valor): informa o angulo das partículas.
********************************/
void SetAnguloParticulas(int idGerador,double angulo){
    CPIGGerenciadorGDP::GetGerador(idGerador)->SetAngulo(angulo);
}

/********************************
A funçăo MudaCorParticulas() é responsável por mesclar uma determinada cor com os pixels do arquivo de imagem da partícula.
Após a modificaçăo, todos os desenhos desta partícula serăo mostrados já com a mesclagem definida.
Para voltar ao padrăo original de pixels, deve-se chamar a funçăo, passando a cor branca (255,255,255).
Parâmetros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da funçăo CriaGeradorParticulas().
cor (entrada,passagem por valor): cor do sistema RGB utilizada para mesclagem com o arquivo de imagem da partícula.
********************************/
void SetCorParticulas(int idGerador,PIG_Cor cor){
    CPIGGerenciadorGDP::GetGerador(idGerador)->SetColoracao(cor);
}

/********************************
A funçăo SetOpacidadeParticulas() modifica a opacidade das partículas após serem criadas.
Somente as partículas criadas posteriormente terăo a opacidade especificada.
Parâmetros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da funçăo CriaGeradorParticulas().
opacidade (entrada, passagem por valor): informa a opacidade das partículas.
********************************/
void SetOpacidadeParticulas(int idGerador,int opacidade){
    CPIGGerenciadorGDP::GetGerador(idGerador)->SetOpacidade(opacidade);
}

/********************************
A funçăo SetDimensoesParticulas() modifica o tamanho das partículas após serem criadas.
Somente as partículas criadas posteriormente terăo o tamanho definido.
Parâmetros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da funçăo CriaGeradorParticulas().
altura (entrada, passagem por valor): informa a altura da partícula ao ser criada.
largura (entrada, passagem por valor): informa a largura da partícula ao ser criada.
********************************/
void SetDimensoesParticulas(int idGerador,int altura, int largura){
    CPIGGerenciadorGDP::GetGerador(idGerador)->SetDimensoes(altura,largura);
}

/********************************
A funçăo SetPivoAbsolutoParticulas() determina o ponto a ser considerado como pivo da partícula.
Somente as partículas criadas posteriormente terăo o pivô especificado.
Parâmetros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da funçăo CriaGeradorParticulas().
posicaoX (entrada, passagem por valor): Valor da coordenada X do pivô em relaçăo ao ponto (0,0) da partícula.
posicaoY (entrada, passagem por valor): Valor da coordenada Y do pivô em relaçăo ao ponto (0,0) da partícula.
********************************/
void SetPivoAbsolutoParticulas(int idGerador,int posicaoX,int posicaoY){
    CPIGGerenciadorGDP::GetGerador(idGerador)->SetPivoAbsoluto({(double)posicaoX,(double)posicaoY});
}

/********************************
A funçăo SetPivoProporcionalParticula() define um ponto (X,Y) proporcional ao tamanho da partícula, sobre o qual o partícula será
rotacionado quando a funçăo SetAnguloParticula() for executada.
Parâmetros:
idGerador (entrada, passagem por valor): identificador do gerador de partículas.
relX (entrada, passagem por valor): porcentagem da largura da partícula onde ficará o pivô.
relY (entrada, passagem por valor): porcentagem da altura da partícula onde ficará o pivô.
********************************/
void SetPivoProporcionalParticulas(int idGerador,float relX,float relY){
    CPIGGerenciadorGDP::GetGerador(idGerador)->SetPivoProporcional({relX,relY});
}

/********************************
A funçăo CriaParticula() adiciona uma nova partícula ao jogo relacionada com o GDP passado como parâmetro.
A partículas é criada com todas as características (ângulo, cor, tamanho, posiçăo, transiçőes etc) que forem correntes ao gerador neste momento.
Parâmetros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da funçăo CriaGeradorParticulas().
Retorno:
inteiro indicando a quantidade atual de partículas do gerador (valor maior ou igual a zero).
Se a partícula năo tiver sido criada por excesso de partículas ativas, o valor retornado é -1.
********************************/
int CriaParticula(int idGerador){
    return CPIGGerenciadorGDP::GetGerador(idGerador)->CriaParticula();
}

/********************************
A funçăo DefineLimitesParticula() é responsável por definir um espaço no cenário onde a partícula será considerada ativa.
Também é definido um tempo de vida máximo, após o qual a partícula năo será mais considerada ativa.
Parâmetros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da funçăo CriaGeradorParticulas().
minX (entrada, passagem por valor): valor mínimo de X para que a partícula seja considerada ativa
minY (entrada, passagem por valor): valor mínimo de Y para que a partícula seja considerada ativa
maxX (entrada, passagem por valor): valor máximo de X para que a partícula seja considerada ativa
maxY (entrada, passagem por valor): valor máximo de Y para que a partícula seja considerada ativa
maxTempo (entrada, passagem por valor): tempo máximo de vida da partícula
********************************/
void DefineLimitesParticula(int idGerador,int minX,int minY,int maxX,int maxY,double maxTempo){
    return CPIGGerenciadorGDP::GetGerador(idGerador)->DefineLimites({minX,minY,maxX,maxY},maxTempo);
}

/********************************
A funçăo QuantidadeParticulasAtivas() indica quantas partículas do GDP em questăo ainda estăo ativas. As partículas deixam de
ser ativas quando saem da tela do jogo, quando colidem com algum objeto ou quando esgotam seu tempo de vida.
Parâmetros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da funçăo CriaGeradorParticulas().
Retorno:
inteiro que indica o número de partículas ativas.
********************************/
int QuantidadeParticulasAtivas(int idGerador){
    return CPIGGerenciadorGDP::GetGerador(idGerador)->GetQtdAtivas();
}

/********************************
A funçăo DesenhaParticulas() desenha todas as partículas ativas do GDP na posiçăo que estiverem.
Parâmetros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da funçăo CriaGeradorParticulas().
********************************/
void DesenhaParticulas(int idGerador){
    CPIGGerenciadorGDP::GetGerador(idGerador)->Desenha();
}

/********************************
A funçăo TestaColisaoParticulasObjeto() indica se houve colisăo de alguma partícula ativa do GDP com um outro objeto específico, através do seu identificador.
Parâmetros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da funçăo CriaGeradorParticulas().
idObjeto (entrada, passagem por valor): identificador do objeto que pode ter colidido com as partículas do GDP.
Retorno:
inteiro que indica se houve colisăo de alguma partícula ativa do GDP (valor diferente de zero) ou năo (valor igual a 0, zero).
********************************/
int TestaColisaoParticulasObjeto(int idGerador,int idObjeto){
    return CPIGGerenciadorGDP::GetGerador(idGerador)->Colisao(CPIGGerenciadorSprites::GetObjeto(idObjeto));
}

/********************************
A funçăo TestaColisaoParticulasAnimacao() indica se houve colisăo de alguma partícula ativa do GDP com uma outra animçăo específica, através do seu identificador.
Parâmetros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da funçăo CriaGeradorParticulas().
idAnimacao (entrada, passagem por valor): identificador da animaçăo que pode ter colidido com as partículas do GDP.
Retorno:
inteiro que indica se houve colisăo de alguma partícula ativa do GDP (valor diferente de zero) ou năo (valor igual a 0, zero).
********************************/
int TestaColisaoParticulasAnimacao(int idGerador,int idAnimacao){
    return CPIGGerenciadorGDP::GetGerador(idGerador)->Colisao(CPIGGerenciadorSprites::GetAnimacao(idAnimacao));
}


/********************************
Seçăo dos temporizadores
********************************/

/********************************
A funçăo CriaTimer() é responsável por criar um timer (temporizador). Após a criaçăo o tempo decorrido
poderá ser obtido a partir da funçăo TempoDecorrido(), informando o identificador que é passado na resposta.
Parâmetros:
congelado (entrada, passagem por valor): valor lógico que indica se o timer deve ser criado sem iniciar de imediato a contagem de tempo ou năo.
Retorno:
inteiro que identifica o timer criado.
********************************/
int CriaTimer(int congelado=false){
    return CPIGGerenciadorTimers::CriaTimer(congelado);
}

/********************************
A funçăo TempoDecorrido() é responsável por informar o tempo decorrido desde a criaçăo do timer
até a hora em que a funçăo for chamada.
Parâmetros:
idTimer (entrada, passagem por valor): identificador do timer.
Retorno:
número real indicando o tempo (em segundos) desde a criaçăo do timer.
********************************/
double TempoDecorrido(int idTimer){
    return CPIGGerenciadorTimers::GetTimer(idTimer)->GetTempoDecorrido();
}

/********************************
A funçăo PausaTimer() é responsável por realizar uma pausa na contagem do tempo de um timer. Após a despausa,
o timer continuará a contar o tempo normalmente.
Parâmetros:
idTimer (entrada, passagem por valor): identificador do timer.
********************************/
void PausaTimer(int idTimer){
    CPIGGerenciadorTimers::GetTimer(idTimer)->Pausa();
}

/********************************
A funçăo PausaTudo() é responsável por realizar uma pausa na contagem do tempo de todos os timers
criados pela funçăo CriaTimer();
********************************/
void PausaTudo(){
    CPIGGerenciadorTimers::PausaTodos();
}

/********************************
A funçăo DespausaTimer() é responsável por retomar a contagem do tempo de todos os timers após uma pausa.
Parâmetros:
idTimer (entrada, passagem por valor): identificador do timer.
********************************/
void DespausaTimer(int idTimer){
    CPIGGerenciadorTimers::GetTimer(idTimer)->Despausa();
}

/********************************
A funçăo DespausaTudo() é responsável por retomar a contagem do tempo de todos os timers
criados pela funçăo CriaTimer();
********************************/
void DespausaTudo(){
    CPIGGerenciadorTimers::DespausaTodos();
}

/********************************
A funçăo ReiniciaTimer() é responsável por zerar a contagem do tempo de um timer, idependente do tempo já decorrido.
Na prática, é equivalente a encerrer um temporizador e recriá-lo em seguida.
Parâmetros:
idTimer (entrada, passagem por valor): identificador do timer.
congelado (entrada, passagem por valor): valor lógico que indica se o timer deve ser zerado sem iniciar de imediato a contagem de tempo ou năo.
********************************/
void ReiniciaTimer(int idTimer, int congelado=false){
    CPIGGerenciadorTimers::GetTimer(idTimer)->Reinicia(congelado);
}

/********************************
A funçăo DestroiTimer() é responsável por encerrar a utilizaçăo de timer.
Seu identificador năo poderá ser utilizado após a funçăo ser executada.
Parâmetros:
idTimer (entrada, passagem por valor): identificador do timer.
********************************/
void DestroiTimer(int idTimer){
    CPIGGerenciadorTimers::DestroiTimer(idTimer);
}

/********************************
A funçăo AssociaGrupoTimer() é responsável por associar um timer a um grupo específico.
Os timers de um mesmo grupo pode ser tratados simultaneamente
(ex: diversos timers de um prsonagem/objeto podem ser pausados/despausados/reiniciados com uma funçăo só).
Parâmetros:
idTimer (entrada, passagem por valor): identificador do timer.
idGrupo (entrada, passagem por valor): identificador do grupos (qualquer valor entre 0 e PIG_MAX_GRUPOS_TIMERS-1).
Retorno:
número inteiro que indica se o grupo é válido (1) ou năo (0).
********************************/
int AssociaGrupoTimer(int idTimer, int idGrupo){
    return CPIGGerenciadorTimers::AssociaTimerGrupo(idTimer,idGrupo);
}

/********************************
A funçăo DesassociaGrupoTimer() é responsável por desassociar um timer de um grupo específico.
Os timers de um mesmo grupo pode ser tratados simultaneamente
(ex: diversos timers de um prsonagem/objeto podem ser pausados/despausados/reiniciados com uma funçăo só).
Parâmetros:
idTimer (entrada, passagem por valor): identificador do timer.
idGrupo (entrada, passagem por valor): identificador do grupos (qualquer valor entre 0 e PIG_MAX_GRUPOS_TIMERS-1).
Retorno:
número inteiro que indica se o grupo é válido (1) ou năo (0).
********************************/
int DesassociaGrupoTimer(int idTimer, int idGrupo){
    return CPIGGerenciadorTimers::DesassociaTimerGrupo(idTimer,idGrupo);
}

/********************************
A funçăo PausaGrupoTimers() é responsável por pausar todos os timers de um grupo específico.
Os timers de um mesmo grupo pode ser tratados simultaneamente
(ex: diversos timers de um prsonagem/objeto podem ser pausados/despausados/reiniciados com uma funçăo só).
Parâmetros:
idGrupo (entrada, passagem por valor): identificador do grupos (qualquer valor entre 0 e PIG_MAX_GRUPOS_TIMERS-1).
Retorno:
número inteiro que indica se o grupo é inválido (-1) ou quantos timers foram pausados no grupo (maior ou igual a 0).
********************************/
int PausaGrupoTimers(int idGrupo){
    return CPIGGerenciadorTimers::PausaGrupo(idGrupo);
}

/********************************
A funçăo DespausaGrupoTimers() é responsável por despausar todos os timers de um grupo específico.
Os timers de um mesmo grupo pode ser tratados simultaneamente
(ex: diversos timers de um prsonagem/objeto podem ser pausados/despausados/reiniciados com uma funçăo só).
Parâmetros:
idGrupo (entrada, passagem por valor): identificador do grupos (qualquer valor entre 0 e PIG_MAX_GRUPOS_TIMERS-1).
Retorno:
número inteiro que indica se o grupo é inválido (-1) ou quantos timers foram despausados no grupo (maior ou igual a 0).
********************************/
int DespausaGrupoTimers(int idGrupo){
    return CPIGGerenciadorTimers::DespausaGrupo(idGrupo);
}

/********************************
A funçăo ReiniciaGrupoTimers() é responsável por reiniciar todos os timers de um grupo específico.
Os timers de um mesmo grupo pode ser tratados simultaneamente
(ex: diversos timers de um prsonagem/objeto podem ser pausados/despausados/reiniciados com uma funçăo só).
Parâmetros:
idGrupo (entrada, passagem por valor): identificador do grupos (qualquer valor entre 0 e PIG_MAX_GRUPOS_TIMERS-1).
congelado (entrada, passagem por valor): valor lógico que indica se o timer deve ser zerado sem iniciar de imediato a contagem de tempo ou năo.
Retorno:
número inteiro que indica se o grupo é inválido (-1) ou quantos timers foram reiniciados no grupo (maior ou igual a 0).
********************************/
int ReiniciaGrupoTimers(int idGrupo, int congelado=false){
    return CPIGGerenciadorTimers::ReiniciaGrupo(idGrupo,congelado);
}



/********************************
Seçăo das animaçőes
********************************/

/********************************
A funçăo CriaAnimacao() é responsável por criar uma animacao. A animaçăo pode ser considerada um tipo especial
de objeto, capaz de mudar de figura (sprite) dentro de um tempo determinado. Uma sequęncia completa de
sprites é chamada de modo. Uma mesma animaçăo pode apresentar vários modos diferentes.
Para que a animaçăo funcione corretamente, será necessário: definir cada frame (pedaço do arquivo bitmap que contém o sprite desejado),
criar um ou mais modos, inserir os frames criados no modo correspondente e dizer qual modo deverá ser exibido inicialmente.
Tudo isso pode ser feito por outras funçőes que manipulam as animaçőes.
Parâmetros:
nomeArquivo (entrada, passagem por referęncia): string que informa o nome do arquivo da imagem (spritesheet) da animaçăo.
retiraFundo (entrada, passagem por valor): inteiro que indica se o fundo da imagem deve ser retirado ou năo ao ler o arquivo em questăo. O valor padrăo é 1, indicando que o fundo deve ser retirado.
corFundo (entrada, passagem por referęncia năo-obrigatório): indica se há uma cor específica para ser considerada como cor de fundo da imagem. Caso, o valor seja NULL, mas o parâmetro retiraFundo seja diferente de 0, o pixel (0,0) da imagem será considerado como cor de fundo.
idJanela (entrada, passagem por valor năo-obrigatório): indica qual janela vai receber a animaçăo.
Retorno:
inteiro que representa o identificador único da animaçăo. Todas as operaçőes subsequentes com esta animaçăo deverăo receber este identificador como parâmetro.
********************************/
int CriaAnimacao(char* nomeArquivo,int retiraFundo=1,PIG_Cor *corFundo=NULL,int idJanela=0){
    return CPIGGerenciadorSprites::CriaAnimacao(nomeArquivo,retiraFundo,corFundo,idJanela);
}

/********************************
A funçăo CriaAnimacao() é responsável por criar uma animacao a partir de outra já existente. A animaçăo pode ser considerada um tipo especial
de objeto, capaz de mudar de figura (sprite) dentro de um tempo determinado. Uma sequęncia completa de
sprites é chamada de modo. Uma mesma animaçăo pode apresentar vários modos diferentes.
Esta forma de criar uma animaçăo, copia todos os frames e modos de outra animaçăo já existente, evitando assim
que toda esta preparaçăo precise ser feita novamente. O usuário deve ter cuidado de năo destruir a animaçăo
original enquanto as cópias estiverem ativas ou haverá erros de execuçăo. Da mesma forma, năo se deve alterar os
frames ou os modos da cópia, pois pode provocar erros na animaçăo original.
Parâmetros:
idAnimacao (entrada, passagem por valor): indica o identificador da animaçăo original que será copiada.
retiraFundo (entrada, passagem por valor): inteiro que indica se o fundo da imagem deve ser retirado ou năo ao ler o arquivo em questăo. O valor padrăo é 1, indicando que o fundo deve ser retirado.
corFundo (entrada, passagem por referęncia năo-obrigatório): indica se há uma cor específica para ser considerada como cor de fundo da imagem. Caso, o valor seja NULL, mas o parâmetro retiraFundo seja diferente de 0, o pixel (0,0) da imagem será considerado como cor de fundo.
idJanela (entrada, passagem por valor năo-obrigatório): indica qual janela vai receber a animaçăo.
Retorno:
inteiro que representa o identificador único da animaçăo. Todas as operaçőes subsequentes com esta animaçăo deverăo receber este identificador como parâmetro.
********************************/
int CriaAnimacao(int idAnimacao,int retiraFundo=1,PIG_Cor *corFundo=NULL,int idJanela=0){
    return CPIGGerenciadorSprites::CriaAnimacao(CPIGGerenciadorSprites::GetAnimacao(idAnimacao),retiraFundo,corFundo,idJanela);
}

/********************************
A funçăo CriaAnimacaoDeObjeto() é responsável por criar uma animacao a partir de um objeto já existente. A animaçăo pode ser considerada um tipo especial
de objeto, capaz de mudar de figura (sprite) dentro de um tempo determinado. Uma sequęncia completa de
sprites é chamada de modo. Uma mesma animaçăo pode apresentar vários modos diferentes.
Esta forma de criar uma animaçăo, copia todos os frames e modos de outra animaçăo já existente, evitando assim
que toda esta preparaçăo precise ser feita novamente. O usuário deve ter cuidado de năo destruir a animaçăo
original enquanto as cópias estiverem ativas ou haverá erros de execuçăo. Da mesma forma, năo se deve alterar os
frames ou os modos da cópia, pois pode provocar erros na animaçăo original.
Parâmetros:
idObjeto (entrada, passagem por valor): indica o identificador do objeto original que servirá de base para a criaçăo da animaçăo.
retiraFundo (entrada, passagem por valor): inteiro que indica se o fundo da imagem deve ser retirado ou năo ao ler o arquivo em questăo. O valor padrăo é 1, indicando que o fundo deve ser retirado.
corFundo (entrada, passagem por referęncia năo-obrigatório): indica se há uma cor específica para ser considerada como cor de fundo da imagem. Caso, o valor seja NULL, mas o parâmetro retiraFundo seja diferente de 0, o pixel (0,0) da imagem será considerado como cor de fundo.
idJanela (entrada, passagem por valor năo-obrigatório): indica qual janela vai receber a animaçăo.
Retorno:
inteiro que representa o identificador único da animaçăo. Todas as operaçőes subsequentes com esta animaçăo deverăo receber este identificador como parâmetro.
********************************/
int CriaAnimacaoDeObjeto(int idObjeto,int retiraFundo=1,PIG_Cor *corFundo=NULL,int idJanela=0){
    return CPIGGerenciadorSprites::CriaAnimacao(CPIGGerenciadorSprites::GetObjeto(idObjeto),retiraFundo,corFundo,idJanela);
}


/********************************
A funçăo DestroiAnimacao() é responsável por eliminar a animaçăo em questăo do jogo.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animaçăo a ser excluída.
********************************/
void DestroiAnimacao(int idAnimacao){
    CPIGGerenciadorSprites::DestroiSprite(idAnimacao);
}

/********************************
A funçăo CriaFrameAnimacao() é responsável por estabelecar uma parte do sprisheet da animaçăo que contém um sprite específico.
O frame criado deve ser posteriormente inserido em um ou mais modos da animaçăo. O posicionamento do frame
respeita o sistema de coordenadas dos arquivos de imagem, com o eixo Y aumentando para baixo.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animaçăo a ter um novo frame.
codigoFrame (entrada, passagem por valor): numero do frame a ser criado. Pode ser usado qualquer número de 0..MAX_FRAMES-1.
xBitmap (entrada, passagem por valor): indica a posiçăo de eixo X onde começa o frame.
yBitmap (entrada, passagem por valor): indica a posiçăo de eixo Y onde começa o frame. Neste caso, o eixo Y aumenta para baixo.
altura (entrada, passagem por valor): altura em pixels do frame.
largura (entrada, passagem por valor): largura em pixels do frame.
********************************/
void CriaFrameAnimacao(int idAnimacao,int codigoFrame,int xBitmap,int yBitmap,int altura,int largura){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->DefineFrame(codigoFrame,{xBitmap,yBitmap,largura,altura});
}

/********************************
A funçăo CarregaArquivoFramesAnimacao() é responsável por ler de arquivo texto os frames de uma animaçăo.
Cada linha do arquivo texto deve conter 5 números inteiros: o número do frame, a posiçăo do frame no eixo X do arquivo de imagem,
a posiçăo do frame no eixo Y do arquivo de imagem, a altura do frame e a largura do frame (todas as unidades em pixels).
Parâmetros:
idObjeto (entrada, passagem por valor): identificador da animaçăo.
nomeArq (entrada, passagem por referęncia): nome do arquivo texto contendo os frames.
********************************/
void CarregaArquivoFramesAnimacao(int idAnimacao, char *nomeArq){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->CarregaArquivoFrames(nomeArq);
}

/********************************
A funçăo CarregaFramesPorLinhaAnimacao() é responsável por subdividir o arquivo de imagem em linhas (de mesmo tamanho) e colunas (de mesmo tamanho).
Cada subdivisăo representará um frame que será automaticamente criado para a animaçăo, com numeraçăo incremental a partir do parâmetro "frameInicial".
Ao final das "qtdColunas" da primeira linha, a definiçăo dos frames continua na linha inferior.
A funçăo pode ser utilizada em spritesheets regulares.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animaçăo.
frameInicial (entrada, passagem por valor): numeraçăo do primeiro frame a ser criado pela funçăo. Os demais frames terăo numeraçăo consecutiva.
qtdLinhas (entrada, passagem por valor): quantidade de linhas na qual o arquivo de imagem será dividido.
qtdColunas (entrada, passagem por valor): quantidade de colunas na qual o arquivo de imagem será dividido.
********************************/
void CarregaFramesPorLinhaAnimacao(int idAnimacao, int frameInicial, int qtdLinhas, int qtdColunas){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->CriaFramesAutomaticosPorLinha(frameInicial,qtdLinhas,qtdColunas);
}

/********************************
A funçăo CarregaFramesPorColunaAnimacao() é responsável por subdividir o arquivo de imagem em linhas (de mesmo tamanho) e colunas (de mesmo tamanho).
Cada subdivisăo representará um frame que será automaticamente criado para a animaçăo, com numeraçăo incremental a partir do parâmetro "frameInicial".
Ao final das "qtdLinhas" da primeira coluna, a definiçăo dos frames continua na coluna seguinte.
A funçăo pode ser utilizada em spritesheets regulares.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animaçăo.
frameInicial (entrada, passagem por valor): numeraçăo do primeiro frame a ser criado pela funçăo. Os demais frames terăo numeraçăo consecutiva.
qtdLinhas (entrada, passagem por valor): quantidade de linhas na qual o arquivo de imagem será dividido.
qtdColunas (entrada, passagem por valor): quantidade de colunas na qual o arquivo de imagem será dividido.
********************************/
void CarregaFramesPorColunaAnimacao(int idAnimacao, int frameInicial, int qtdLinhas, int qtdColunas){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->CriaFramesAutomaticosPorColuna(frameInicial,qtdLinhas,qtdColunas);
}

/********************************
A funçăo CriaModoAnimacao() é responsável por criar um modo, ou seja, uma sequęncia de sprites.
Após a criaçăo do modo, os frames deve ser inseridos um a um. O modo pode ser criado antes dos frames
e vice-versa, mas os frames só podem ser associados ao modo, após as respectivas criaçőes.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animaçăo a ter um novo modo.
codigoModo (entrada, passagem por valor): numero do modo a ser criado. Pode ser usado qualquer número de 0..MAX_MODOS-1.
loop (entrada, passagem por valor): valor lógico que indica se este modo deve recomeçar do primeiro frame após a execuçăo do último.
********************************/
void CriaModoAnimacao(int idAnimacao,int codigoModo,int loop){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->CriaModo(codigoModo,loop);
}

/********************************
A funçăo InsereFrameAnimacao() é responsável por associar os frames aos modos correspondentes.
Um mesmo frame pode fazer parte de diversos modos.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animaçăo em questăo.
codigoModo (entrada, passagem por valor): numero do modo a ter um frame inserido.
codigoFrame (entrada, passagem por valor): numero do frame a ser inserido no modo.
tempo (entrada, passagem por valor): duraçăo (em segundos) da exibiçăo automática do frame neste modo específico.
idAudio (entrada, passagem por valor năo-obrigatório): identificador do audio (já criado anteriormente) que deve ser tocado quando o frame for exibido. O valor -1 deve ser utilizado se nenhum audio deve ser tocado.
alturaAnimacao (entrada, passagem por valor năo-obrigatório): tamanho em pixels altura da animaçăo quando estiver exibindo este frame. Um valor negativo neste parâmetro ou no próximo (larguraAnimacao) indica que năo haverá alteraçăo de dimensőes da animaçăo.
larguraAnimacao (entrada, passagem por valor năo-obrigatório): tamanho em pixels largura da animaçăo quando estiver exibindo este frame. Um valor negativo neste parâmetro ou no anterior (alturaAnimacao) indica que năo haverá alteraçăo de dimensőes da animaçăo.
********************************/
void InsereFrameAnimacao(int idAnimacao,int codigoModo, int codigoFrame, float tempo, int idAudio=-1, int alturaAnimacao=-1, int larguraAnimacao=-1){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->InsereFrame(codigoModo,codigoFrame,tempo,idAudio,alturaAnimacao,larguraAnimacao);
}


/********************************
A funçăo InsereAudioFrameAnimacao() é responsável por acrescentar um audio a um dos frames.
O audio é tocado assim que o frame é desenhado pela primeira vez.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animaçăo em questăo.
codigoModo (entrada, passagem por valor): número do modo a ter um frame inserido.
indiceFrame (entrada, passagem por valor): índice (posiçăo) do frame no modo em questăo.
idAudio (entrada, passagem por valor năo-obrigatório): identificador do audio (já criado anteriormente) que deve ser tocado quando o frame for exibido. O valor -1 deve ser utilizado se nenhum audio deve ser tocado.
********************************/
void InsereAudioFrameAnimacao(int idAnimacao, int codigoModo, int indiceFrame, int idAudio){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetAudioFrame(codigoModo,indiceFrame,idAudio);
}

/********************************
A funçăo MudaModoAnimacao() é responsável por alterar a animaçăo para um outro modo.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animaçăo em questăo.
codigoModo (entrada, passagem por valor): numero do novo modo.
indiceFrame (entrada, passagem por valor): indica a partir de qual frame o modo deve ser exibido. O valor 0 significa aprtir do primeiro frame.
forcado (entrada, passagem por valor): valor lógico que indica se a mudança de modo deve ser feita forçosamente ou năo. Se năo for forçada, a mudança só ocorrerá se o modo atual já tiver terminado de ser animado.
********************************/
void MudaModoAnimacao(int idAnimacao,int codigoModo,int indiceFrame,int forcado=1){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->MudaModo(codigoModo,indiceFrame,forcado);
}

/********************************
A funçăo GetModoAtualAnimacao() é responsável por recuperar o valor do modo atual da animaçăo.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animaçăo em questăo.
Retorno:
inteiro que representa o modo atual da animaçăo.
********************************/
int GetModoAtualAnimacao(int idAnimacao){
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetModoAtual();
}

/********************************
A funçăo GetFrameAtualAnimacao() recupera o valor do frame atual exibido na animaçăo.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animaçăo.
Retorno:
Número do frame atual da animaçăo.
********************************/
int GetFrameAtualAnimacao(int idAnimacao){
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetFrameAtual();
}

/********************************
A funçăo TestaColisaoAnimacoes() indica se houve colisăo entre duas animaçőes, de forma semelhante aos objetos.
Parâmetros:
idAnimacao1 (entrada, passagem por valor): identificador da primeira animaçăo.
idAnimacao2 (entrada, passagem por valor): identificador da segunda animaçăo.
Retorno:
inteiro que indica se houve colisăo entre as animaçőes.
********************************/
int TestaColisaoAnimacoes(int idAnimacao1,int idAnimacao2){
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao1)->Colisao(CPIGGerenciadorSprites::GetAnimacao(idAnimacao2));
}

/********************************
A funçăo TestaColisaoAnimacaoObjeto() indica se houve colisăo de alguma animacao com algum outro objeto específico, através do seu identificador.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animaçăo que pode ter colidido com o objeto.
idObjeto (entrada, passagem por valor): identificador do objeto que pode ter colidido com a animaçăo.
Retorno:
inteiro que indica se houve colisăo da animaçăo com o objeto.
********************************/
int TestaColisaoAnimacaoObjeto(int idAnimacao,int idObjeto){
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->Colisao(CPIGGerenciadorSprites::GetObjeto(idObjeto));
}


/********************************
A funçăo DefineAreaColisaoObjeto() é responsável estabelecer um polígono que será utilizado como área de colisăo da animaçăo com as demais.
Os vetores X e Y deve ter pelo menos qtdPontos elementos.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animaçăo.
pontosX (entrada, passagem por referęncia): vetor de inteiros, de tamanho qtdPontos, contendo os valores X de cada ponto do polígono.
pontosY (entrada, passagem por referęncia): vetor de inteiros, de tamanho qtdPontos, contendo os valores Y de cada ponto do polígono.
qtdPontos (entrada, passagem por valor): quantidade de pontos da animaçăo.
********************************/
void DefineAreaColisaoAnimacao(int idAnimacao, int pontosX[], int pontosY[], int qtdPontos) {
    std::vector<PIGPonto2D> vertices;

    for (int i = 0; i < qtdPontos; i++) {
        vertices.push_back({(double)pontosX[i], (double)pontosY[i]});
    }

    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetVertices(vertices);
}

/********************************
A funçăo DefineRaioColisaoAnimacao() é responsável por estabelecer um raio, em relaçăo ao pivô da animaçăo, que será utilizado para teste de colisăo circular desta animaçăo com as demais.
A definiçăo do raio só será útil se o tipode colisăo deste objeto for circular, definido pela funçăo DefineTipoColisaoObjeto().
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animaçăo.
raio (entrada, passagem por valor): tamanho do raio que formará a área de colisăo desta animaçăo.
********************************/
void DefineRaioColisaoAnimacao(int idAnimacao, float raio){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetRaioColisaoCircular(raio);
}

/********************************
A funçăo DefineTipoColisaoAnimacao() é responsável por definir o tipod e colisăo que será utilizada por esta animaçăo com as demais.
É possível ter 3 tipos de colisăo: por bouding-box (PIG_COLISAO_OOBB - área de colisăo delimitada pelo ponto X,Y da animaçăo, sua altura e largura e rotaçăo),
por polígono (PIG_COLISAO_POLIGONO) área de colisăo formada por pontos genéricos) e circular (PIG_COLISAO_CIRCULAR) área de colisăo em forma de círculo, com raio definido a partir do ponto pivô)
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animaçăo.
modo (entrada, passagem por valor): modo de colisăo a ser utilizado por esta animaçăo.
********************************/
void DefineTipoColisaoAnimacao(int idAnimacao, PIG_ModoColisao modo){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetModoColisao(modo);
}

/********************************
A funçăo DesenhaAnimacao() é responsável por desenhar uma animaçăo na tela. A animaçăo será desenhada de acordo com o modo atual da animaçăo,
fazendo com que os frames sejam automaticamente ajustados de acordo com o tempo estipulado. Caso o modo atual esteja em loop, o primeiro frame será
desenhado novamente logo após o término do último frame.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animaçăo a ser desenhada.
Retorno:
inteiro que indica se a animaçăo encerrou ou năo. O valor só será diferente de zero, se o modo atual também năo estiver em loop.
********************************/
int DesenhaAnimacao(int idAnimacao){
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->Desenha();
}

/********************************
A funçăo MoveAnimacao() é responsável por movimentar uma determinada animaçăo para uma nova posiçăo informada.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animaçăo a ser movida.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usuário deseja reposicionar a animaçăo.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usuário deseja reposicionar a animaçăo.
********************************/
void MoveAnimacao(int idAnimacao,int x,int y){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->Move(x,y);
}

/********************************
A funçăo DeslocaAnimcao() é responsável por deslocar uma determinada animacao em relaçăo ŕ sua posiçăo atual.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animacao a ser deslocada.
deltaX (entrada, passagem por valor): valor a ser somado ou subtraído na componente X da posiçăo da animaçăo.
deltaY (entrada, passagem por valor): valor a ser somado ou subtraído na componente Y da posiçăo da animaçăo.
********************************/
void DeslocaAnimacao(int idAnimacao,int deltaX,int deltaY){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->Desloca(deltaX,deltaY);
}

/********************************
A funçăo SetLoopModoAnimacao() é responsável por definir a existęncia ou năo de loop em um modo de uma animaçăo.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animacao a ser deslocada.
codigoModo (entrada, passagem por valor): numero do modo em questăo.
loop (entrada, passagem por valor): valor que indica a existęncia (diferente de zero) ou năo (igual a zero) de loop no modo em questăo.
********************************/
void SetLoopModoAnimacao(int idAnimacao,int modo,int loop){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetLoopModo(modo,loop);
}

/********************************
A funçăo SetTempoFrameAnimacao() é responsável por definir uma nova duraçăo para exibiçăo do frame.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animacao a ser deslocada.
codigoModo (entrada, passagem por valor): numero do modo em questăo.
indiceFrame (entrada, passagem por valor): indica a partir de qual frame o modo deve ser exibido. O valor 0 significa aprtir do primeiro frame.
tempo (entrada, passagem por valor): valor que indica a nova duraçăo de exibiçăo do frame, em segundos.
********************************/
void SetTempoFrameAnimacao(int idAnimacao,int modo,int indiceFrame,float tempo){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetTempoFrame(modo,indiceFrame,tempo);
}

/********************************
A funçăo SetAudioFrameAnimacao() é responsável por definir um novo audio a ser executado quando o frame em questăo começar a ser exibido.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animacao a ser deslocada.
codigoModo (entrada, passagem por valor): numero do modo em questăo.
indiceFrame (entrada, passagem por valor): indica a partir de qual frame o modo deve ser exibido. O valor 0 significa aprtir do primeiro frame.
idAudio (entrada, passagem por valor): identificador do audio (já criado) a ser tocado quando o frame começar a ser exibido.
********************************/
void SetAudioFrameAnimacao(int idAnimacao,int modo,int indiceFrame,int idAudio){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetAudioFrame(modo,indiceFrame,idAudio);
}

/********************************
A funçăo GetLoopModoAnimacao() é responsável por recuperar a existęncia ou năo de loop em um modo de uma animaçăo.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animacao a ser deslocada.
codigoModo (entrada, passagem por valor): numero do modo em questăo.
Retorno:
inteiro que indica a existęncia (diferente de zero) ou năo (igual a zero) de loop no modo em questăo.
********************************/
int GetLoopModoAnimacao(int idAnimacao,int modo){
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetLoopModo(modo);
}

/********************************
A funçăo GetAudioFrameAnimacao() é responsável por recuprar o identificador do audio a ser executado quando o frame em questăo começar a ser exibido.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animacao a ser deslocada.
codigoModo (entrada, passagem por valor): numero do modo em questăo.
indiceFrame (entrada, passagem por valor): indica a partir de qual frame o modo deve ser exibido. O valor 0 significa aprtir do primeiro frame.
Retorno:
inteiro que representa o identificador do audio (já criado) a ser tocado quando o frame começar a ser exibido.
********************************/
int GetAudioFrameAnimacao(int idAnimacao,int modo,int indiceFrame){
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetAudioFrame(modo,indiceFrame);
}

/********************************
A funçăo GetTempoFrameAnimacao() é responsável por recuperar a duraçăo da exibiçăo do frame.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animacao a ser deslocada.
codigoModo (entrada, passagem por valor): numero do modo em questăo.
indiceFrame (entrada, passagem por valor): indica a partir de qual frame o modo deve ser exibido. O valor 0 significa aprtir do primeiro frame.
Retorno:
float que indica a nova duraçăo de exibiçăo do frame, em segundos.
********************************/
float GetTempoFrameAnimacao(int idAnimacao,int modo,int indiceFrame){
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetTempoFrame(modo,indiceFrame);
}

/********************************
A funçăo PausaAnimacao() é responsável por pausar a exibiçăo dos frames da animaçăo.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animacao a ser deslocada.
********************************/
void PausaAnimacao(int idAnimacao){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->Pausa();
}

/********************************
A funçăo DespausaAnimacao() é responsável por despausar a exibiçăo dos frames da animaçăo.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animacao a ser deslocada.
********************************/
void DesausaAnimacao(int idAnimacao){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->Despausa();
}

/********************************
A funçăo SetOpacidadeAnimacao() é responsável por modificar o nível de opacidade da animaçăo.
O nível de opacidade varia de 0-255, sendo 0 totalmente transparente e 255 totalmente opaco.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animaçăo.
valor (entrada,passagem por valor): nível de opacidade da animaçăo na faixa 0-255.
********************************/
void SetOpacidadeAnimacao(int idAnimacao,int valor){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetOpacidade(valor);
}

/********************************
A funçăo GetOpacidadeAnimacao() é responsável por recuperar o nível de opacidade da animaçăo.
O nível de opacidade varia de 0-255, sendo 0 totalmente transparente e 255 totalmente opaco.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animaçăo.
Retorno:
Retorna o nível de opacidade da animaçăo na faixa 0-255.
********************************/
int GetOpacidadeAnimacao(int idAnimacao){
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetOpacidade();
}

/********************************
A funçăo SetColoracaoAnimacao() é responsável por mesclar uma determinada cor com os pixels do arquivo de imagem.
Após a modificaçăo, todos os desenhos desta animaçăo serăo mostrados já com a mesclagem definida.
Para voltar ao padrăo original de pixels, deve-se chamar a funçăo, passando a cor branca (255,255,255).
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animaçăo a ser desenhado.
cor (entrada,passagem por valor): cor do sistema RGB utilizada para mesclagem com o arquivo de imagem
********************************/
void SetColoracaoAnimacao(int idAnimacao,PIG_Cor cor){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetColoracao(cor);
}

/********************************
A funçăo SetFlipAnimacao() é responsável por virar a animaçăo, invertendo-a em alguma direçăo. A animaçăo somente será
desenhada na nova orientaçăo no próximo comando DesenhaAnimacao().
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animaçăo a ser virada.
valor (entrada, passagem por valor): valor do tipo de Flip. Pode ser PIG_FLIP_NENHUM (nenhum tipo de inversăo),
PIG_FLIP_HORIZONTAL (inverte da esquerda para a direita), PIG_FLIP_VERTICAL (inverte de cima para baixo),
ou PIG_FLIP_HORIZ_VERT (inverte da esquerda para direita e de cima para baixo).
********************************/
void SetFlipAnimacao(int idAnimacao,PIG_Flip valor){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetFlip(valor);
}

/********************************
A funçăo GetFlipAnimacao() é responsável por recuperar o valor da manipulaçăo causada pela funçăo SetFlipAnimacao().
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animaçăo a ser virada.
Retorno:
inteiro que indica o tipo de Flip. Pode ser PIG_FLIP_NENHUM (nenhum tipo de inversăo),
PIG_FLIP_HORIZONTAL (inverte da esquerda para a direita), PIG_FLIP_VERTICAL (inverte de cima para baixo),
ou PIG_FLIP_HORIZ_VERT (inverte da esquerda para direita e de cima para baixo).
********************************/
PIG_Flip GetFlipAnimacao(int idAnimacao){
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetFlip();
}

/********************************
A funçăo SetAnguloAnimacao() é responsável pela angulaçăo de determinada animacao. A angulaçăo é calculada em sentido
horário a partir do eixo X (0 graus). A animaçăo será desenhada com a angulaçăo informada no próximo comando
DesenhaAnimcao(). A detecçăo de colisăo năo funciona com animaçőes fora da angulaçăo padrăo (0 graus).
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animaçăo.
angulo (entrada, passagem por valor): valor para indicar a angulaçăo da animaçăo em graus.
********************************/
void SetAnguloAnimacao(int idAnimacao, double angulo){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetAngulo(angulo);
}

/********************************
A funçăo GetAnguloAnimacao() é responsável por recuperar o ângulo de rotaçăo de determinada animaçăo. A angulaçăo é calculada em sentido
horário a partir do eixo X (0 graus). A animaçăo será desenhada com a angulaçăo informada no próximo comando
DesenhaAnimacao(). A detecçăo de colisăo năo funciona com animaçőes fora da angulaçăo padrăo (0 graus).
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animaçăo.
Retorno:
Retorna o valor do ângulo em graus.
********************************/
double GetAnguloAnimacao(int idAnimacao){
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetAngulo();
}

/********************************
A funçăo SetPivoAbsolutoAnimacao() define um ponto (X,Y) em relaçăo ao ponto (0,0) da animaçăo, sobre o qual a animaçăo será
rotacionado quando a funçăo SetAnguloAnimacao() for executada.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animaçăo.
posicaoX (entrada, passagem por valor): Valor da coordenada X do pivô em relaçăo ao ponto (0,0) da animaçăo.
posicaoY (entrada, passagem por valor): Valor da coordenada Y do pivô em relaçăo ao ponto (0,0) da animaçăo.
********************************/
void SetPivoAbsolutoAnimacao(int idAnimacao,int posicaoX,int posicaoY){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetPivoAbsoluto({(double)posicaoX,(double)posicaoY});
}

/********************************
A funçăo SetPivoProporcionalAnimacao() define um ponto (X,Y) proporcional ao tamanho da animaçăo, sobre o qual a animaçăo será
rotacionado quando a funçăo SetAnguloAnimacao() for executada.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animaçăo.
relX (entrada, passagem por valor): porcentagem da largura da animaçăo onde ficará o pivô.
relY (entrada, passagem por valor): porcentagem da altura da animaçăo onde ficará o pivô.
********************************/
void SetPivoProporcionalAnimacao(int idAnimacao,float relX,float relY){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetPivoProporcional({relX,relY});
}

/********************************
A funçăo GetPivoAnimacao() define um ponto (X,Y) em relaçăo ao ponto (0,0) da animacao, sobre o qual a animaçăo será
rotacionado quando a funçăo SetAnguloAnimacao() for executada.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animaçăo.
posicaoX (saída, passagem por referęncia): Valor da coordenada X do pivô em relaçăo ao ponto (0,0) da animaçăo.
posicaoY (saída, passagem por referęncia): Valor da coordenada Y do pivô em relaçăo ao ponto (0,0) da animaçăo.
********************************/
void GetPivoAnimacao(int idAnimacao,int *posicaoX,int *posicaoY){
    PIGPonto2D p = CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetPivo();
    *posicaoX = p.x;
    *posicaoY = p.y;
}

/********************************
A funçăo SetDimensoesAnimacao() é responsável por delimitar a altura e a largura da animaçăo que será desenhada na tela,
independentemente do tamanho original do arquivo de imagem.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animaçăo.
altura (entrada, passagem por valor): altura em pixels.
largura (entrada, passagem por valor): largura em pixels.
********************************/
void SetDimensoesAnimacao(int idAnimacao, int altura, int largura){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetDimensoes(altura,largura);
}

/********************************
A funçăo GetDimensoesAnimacao() é responsável por recuperar a altura e a largura da área a ser usada
para desenhar a animaçăo na tela. Em outras palavras, representa o tamanho atual da animaçăo.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador da animaçăo.
altura (saída, passagem por referęncia): altura atual em pixels da animaçăo.
largura (saída, passagem por referęncia): largura atual em pixels da animaçăo.
********************************/
void GetDimensoesAnimacao(int idAnimacao, int *altura, int *largura){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetDimensoes(*altura,*largura);
}

/********************************
A funçăo SetValorIntAnimacao() é responsável incorporar a uma animaçăo um atributo inteiro.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animaçăo.
indice (entrada, passagem por valor): relaciona um número inteiro ao atributo.
valor (entrada, passagem por valor): valor do atributo inteiro a ser associado ŕ animaçăo.
********************************/
void SetValorIntAnimacao(int idAnimacao,int indice,int valor){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetValorInt(indice,valor);
}

/********************************
A funçăo SetValorFloatAnimacao() é responsável incorporar a uma animaçăo um atributo float.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animaçăo.
indice (entrada, passagem por valor): relaciona um número inteiro ao atributo.
valor (entrada, passagem por valor): valor do atributo float a ser associado ŕ animaçăo.
********************************/
void SetValorFloatAnimacao(int idAnimacao,int indice,float valor){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetValorFloat(indice,valor);
}

/********************************
A funçăo SetValorIntAnimacao() é responsável incorporar a uma animaçăo um atributo inteiro.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animaçăo.
indice (entrada, passagem por valor): relaciona um número inteiro ao atributo.
valor (entrada, passagem por referęncia): valor do atributo string a ser associado ŕ animaçăo.
********************************/
void SetValorStringAnimacao(int idAnimacao,int indice,char *valor){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetValorString(indice,valor);
}

/********************************
A funçăo SetValorIntAnimacao() é responsável incorporar a uma animaçăo um atributo inteiro.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animaçăo.
indice (entrada, passagem por referęncia): relaciona uma string ao atributo.
valor (entrada, passagem por valor): valor do atributo inteiro a ser associado ŕ animaçăo.
********************************/
void SetValorIntAnimacao(int idAnimacao,char *indice,int valor){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetValorInt(indice,valor);
}

/********************************
A funçăo SetValorFloatAnimacao() é responsável incorporar a uma animaçăo um atributo float.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animaçăo.
indice (entrada, passagem por referęncia): relaciona uma string ao atributo.
valor (entrada, passagem por valor): valor do atributo float a ser associado ŕ animaçăo.
********************************/
void SetValorFloatAnimacao(int idAnimacao,char *indice,float valor){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetValorFloat(indice,valor);
}

/********************************
A funçăo SetValorIntAnimacao() é responsável incorporar a uma animaçăo um atributo inteiro.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animaçăo.
indice (entrada, passagem por referęncia): relaciona uma string ao atributo.
valor (entrada, passagem por referęncia): valor do atributo string a ser associado ŕ animaçăo.
********************************/
void SetValorStringAnimacao(int idAnimacao,char *indice,char *valor){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetValorString(indice,valor);
}

/********************************
A funçăo GetValorIntAnimacao() é responsável recuperar o valor de um atributo inteiro relacionado a uma animaçăo.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animaçăo.
indice (entrada, passagem por valor): indica o número do atributo que se deseja recuperar.
valor (saída, passagem por referęncia): indica o valor do atributo, se a funçăo retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo năo existir, a funçăo retorna o valor 0 (zero).
********************************/
int GetValorIntAnimacao(int idAnimacao,int indice,int *valor){
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetValorInt(indice,*valor);
}

/********************************
A funçăo GetValorFloatAnimacao() é responsável recuperar o valor de um atributo float relacionado a uma animaçăo.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animaçăo.
indice (entrada, passagem por valor): indica o número do atributo que se deseja recuperar.
valor (saída, passagem por referęncia): indica o valor do atributo, se a funçăo retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo năo existir, a funçăo retorna o valor 0 (zero).
********************************/
int GetValorFloatAnimacao(int idAnimacao,int indice,float *valor){
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetValorFloat(indice,*valor);
}

/********************************
A funçăo GetValorStringAnimacao() é responsável recuperar o valor de um atributo string relacionado a uma animaçăo.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animaçăo.
indice (entrada, passagem por valor): indica o número do atributo que se deseja recuperar.
valor (saída, passagem por referęncia): indica o valor do atributo, se a funçăo retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo năo existir, a funçăo retorna o valor 0 (zero).
********************************/
int GetValorStringAnimacao(int idAnimacao,int indice,char *valor){
    std::string str;
    bool resp = CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetValorString(indice,str);
    strcpy(valor,str.c_str());
    return resp;
}

/********************************
A funçăo GetValorIntAnimacao() é responsável recuperar o valor de um atributo inteiro relacionado a uma animaçăo.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animaçăo.
indice (entrada, passagem por referęncia): indica o nome do atributo que se deseja recuperar.
valor (saída, passagem por referęncia): indica o valor do atributo, se a funçăo retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo năo existir, a funçăo retorna o valor 0 (zero).
********************************/
int GetValorIntAnimacao(int idAnimacao,char *indice,int *valor){
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetValorInt(indice,*valor);
}

/********************************
A funçăo GetValorFloatAnimacao() é responsável recuperar o valor de um atributo float relacionado a uma animaçăo.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animaçăo.
indice (entrada, passagem por valor): indica o nome do atributo que se deseja recuperar.
valor (saída, passagem por referęncia): indica o valor do atributo, se a funçăo retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo năo existir, a funçăo retorna o valor 0 (zero).
********************************/
int GetValorFloatAnimacao(int idAnimacao,char *indice,float *valor){
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetValorFloat(indice,*valor);
}

/********************************
A funçăo GetValorStringAnimacao() é responsável recuperar o valor de um atributo string relacionado a uma animaçăo.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animaçăo.
indice (entrada, passagem por valor): indica o nome do atributo que se deseja recuperar.
valor (saída, passagem por referęncia): indica o valor do atributo, se a funçăo retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo năo existir, a funçăo retorna o valor 0 (zero).
********************************/
int GetValorStringAnimacao(int idAnimacao,char *indice,char *valor){
    std::string str;
    bool resp = CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetValorString(indice,str);
    strcpy(valor,str.c_str());
    return resp;
}

/********************************
A funçăo GetXYAnimacao() é responsável por recuperar o valor da posiçăo (X,Y) da animacao de acordo com o sistema de coordenadas do jogo.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animaçăo.
posicaoX (saída, passagem por referencia): indica a posicao no eixo X da animaçăo.
posicaoY (saída, passagem por referencia): indica a posicao no eixo Y da animaçăo.
********************************/
void GetXYAnimacao(int idAnimacao,int *posicaoX,int *posicaoY){
    PIGPonto2D p = CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetXY();
    *posicaoX = p.x;
    *posicaoY = p.y;
}

/********************************
A funçăo InsereTransicaoAnimacao() é responsável por criar e inserir uma nova transiçăo ao final de sequęncia de transiçőes da animaçăo.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animaçăo.
tempo (entrada, passagem por valor): duracao (em segundos) da transiçăo.
deltaX (entrada, passagem por valor): diferença da posiçăo no eixo X em relaçăo ŕ posiçăo da animaçăo no início da transiçăo.
deltaY (entrada, passagem por valor): diferença da posiçăo no eixo Y em relaçăo ŕ posiçăo da animaçăo no início da transiçăo.
deltaAltura (entrada, passagem por valor): diferença da altura da animaçăo em relaçăo ao início da transiçăo.
deltaLargura (entrada, passagem por valor): diferença da largura da animaçăo em relaçăo ao início da transiçăo.
deltaAngulo (entrada, passagem por valor): diferença de ângulo (em graus) da animaçăo em relaçăo ao início da transiçăo.
corFinal (entrada, passagem por valor): coloraçăo da animaçăo ao final da transiçăo.
deltaOpacidade (entrada, passagem por valor): diferença do nível de opacidade da animaçăo em relaçăo ao início da transiçăo.
********************************/
void InsereTransicaoAnimacao(int idAnimacao,double tempo,int deltaX,int deltaY,int deltaAltura,int deltaLargura,double deltaAngulo,PIG_Cor corFinal,int deltaOpacidade){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->InsereTransicao(tempo,{deltaX,deltaY,deltaAltura,deltaLargura,deltaAngulo,corFinal,deltaOpacidade});
}

/********************************
A funçăo ExecutandoTransicaoAnimacao() retorna a informaçăo sobre a execuçăo (neste momento) de transiçőes da animaçăo.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animaçăo.
Retorno:
inteiro que indica se a animaçăo está executando alguma transiçăo no momento (valor diferente de 0) ou năo (valor igual a 0).
********************************/
int ExecutandoTransicaoAnimacao(int idAnimacao){
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->ExecutandoTransicao();
}

/********************************
A funçăo LeArquivoTransicaoAnimacao() é responsável por ler, criar e inserir as transiçőes para uma animaçăo, provenientes de um arquivo texto.
Cada linha do arquivo texto corresponde a uma transiçăo (em ordem) e deve possuir 11 valores:
1) um double representando a duracao (em segundos) da transiçăo.
2) um inteiro repreentando a diferença da posiçăo no eixo X em relaçăo ŕ posiçăo da animaçăo no início da transiçăo.
3) um inteiro repreentando a diferença da posiçăo no eixo Y em relaçăo ŕ posiçăo da animaçăo no início da transiçăo.
4) um inteiro repreentando a diferença da altura da animaçăo em relaçăo ao início da transiçăo.
5) um inteiro repreentando a diferença da largura da animaçăo em relaçăo ao início da transiçăo.
6) um double repreentando a diferença de ângulo (em graus) da animaçăo em relaçăo ao início da transiçăo.
7) um inteiro repreentando a componente R (vermelho) da coloraçăo da animaçăo ao final da transiçăo.
8) um inteiro repreentando a componente G (verde) da coloraçăo da animaçăo ao final da transiçăo.
9) um inteiro repreentando a componente B (azul) da coloraçăo da animaçăo ao final da transiçăo.
10) um inteiro repreentando a componente A (canal alfa) da coloraçăo da animaçăo ao final da transiçăo.
11) um inteiro repreentando a diferença do nível de opacidade da animaçăo em relaçăo ao início da transiçăo.
Parâmetros:
idSprite (entrada, passagem por valor): identificador da animaçăo.
nomeArq (entrada, passagem por referęncia): nome com extensăo do arquivo texto contendo as transiçőes.
********************************/
void LeArquivoTransicaoAnimacao(int idAnimacao,char *nomeArq){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->LeTransicoes(nomeArq);
}

/********************************
A funçăo IniciaAutomacaoAnimacao() é responsável por iniciar as transiçőes já inseridas na animaçăo, de acordo como o tipo de transiçăo informada.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animaçăo.
********************************/
void IniciaAutomacaoAnimacao(int idAnimacao){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->IniciaAutomacao();
}

/********************************
A funçăo TrataAutomacaoAnimacao() é responsável por calcular o estado da transiçăo corrente da animaçăo e aplicar essas modificaçăo a ela.
A funçăo deve ser chamada a cada frame, para ter resultados mais precisos.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animaçăo.
********************************/
void TrataAutomacaoAnimacao(int idAnimacao){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->TrataAutomacao();
}

/********************************
A funçăo PausaAutomacaoAnimacao() é responsável por pausar as transições e ações associadas a uma animação.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação.
********************************/
void PausaAutomacaoAnimacao(int idAnimacao){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->PausaAutomacao();
}

/********************************
A funçăo DespausaAutomacaoAnimacao() é responsável por despausar as transições e ações associadas a uma animação.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação.
********************************/
void DespausaAutomacaoAnimacao(int idAnimacao){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->DespausaAutomacao();
}

/********************************
A funçăo DefineTipoTransicaoAnimacao() é responsável por determinar como a sequęncia de transiçőes da animaçăo será executada.
É possível fazę-la uma única vez (PIG_TRANSICAO_NORMAL), em loop (PIG_TRANSICAO_LOOP) ou indo até o final da sequęncia e retornando, em vai-vém (PIG_TRANSICAO_VAIVEM).
A funçăo deve ser chamada a cada frame, para ter resultados mais precisos.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animaçăo.
********************************/
void DefineTipoTransicaoAnimacao(int idAnimacao,PIG_TipoTransicao valor){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->DefineTipoTransicao(valor);
}

/********************************
A funçăo LimpaTransicoesAnimacao() é responsável por remover a sequęncia de transiçőes do animaçăo.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animaçăo.
********************************/
void LimpaTransicoesAnimacao(int idAnimacao){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->LimpaTransicoes();
}

/********************************
A funçăo InsereAcaoAnimacao() é responsável por inserir na linha de tempo de automaçăo do animaçăo uma açăo a ser executada.
A açăo é composta por uma funçăo "acao" que será executada quando a linha de tempo atingir o parâmetro "tempo" e será repetida a cada "repeticao" segundos.
A açăo pode armazenar um ponteiro genérico "param" que será utilizado na chamada da funçăo.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animaçăo.
tempo (entrada, passagem por valor): tempo (em segundos) da primeira chamada da funçăo.
repeticao (entrada, passagem por valor): tempo (em segundos) entre a chamada anterior e a próxima. O valor -1 indica que a funçăo năo será repetida.
param (entrada, passagem por referęncia): ponteiro genérico para um valor que será utilizado na chamada da funçăo.
********************************/
void InsereAcaoAnimacao(int idAnimacao,double tempo,double repeticao,PIG_FuncaoSimples acao,void *param){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->InsereAcao(tempo,repeticao,acao,param);
}

/********************************
A funçăo LimpaAcoesAnimacao() é responsável por remover as ações restantes associadas à animação
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação.
********************************/
void LimpaAcoesAnimacao(int idAnimacao){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->LimpaAcoes();
}


/********************************
Seçăo dos áudios
********************************/

/********************************
A funçăo CriaAudio() é responsável por ler e preparar um arquivo de audio.
Os formatos permitidos săo WAVE, AIFF, RIFF, OGG, VOC.
Parâmetros:
nomeArquivo (entrada, passagem por referęncia): string que informa o nome do arquivo de áudio.
nLoops (entrada, passagem por valor): indica o número de repetiçőes do áudio. O valor 0 indica que será tocado apenas uma vez. O valor -1 indica que o audio deve ser tocado indefinidamente.
tempoExecucao (entrada, passage por valor): indica uma quantidade de milissegundos do arquivo de audio que dem ser tocados. O valor de -1 indica que todo o arquivo deve ser tocado.
Retorno:
Retorna o identificador do audio para ser utilizado por outras funçőes.
********************************/
int CriaAudio(char *nomeArquivo,int nLoops,int tempoExecucao=-1){
    return CPIGGerenciadorAudios::CriaAudio(nomeArquivo,nLoops,tempoExecucao);
}

/********************************
A funçăo DestroiAudio() é responsável por eliminar um áudio do jogo.
Parâmetros:
idAudio (entrada, passagem por valor): identificador do áudio a ser excluído.
********************************/
void DestroiAudio(int idAudio){
    CPIGGerenciadorAudios::DestroiAudio(idAudio);
}

/********************************
A funçăo CarregaBackground() é responsável por ler e preparar um arquivo de audio para ser tocado em background.
Apenas um único arquivo de áudio para background é permitido. Os formatos permitidos săo WAVE, MOD, MIDI, OGG, MP3, FLAC.
Parâmetros:
nomeArquivo (entrada, passagem por referęncia): string que informa o nome do arquivo de áudio.
********************************/
void CarregaBackground(char *nomeArquivo){
    CPIGGerenciadorAudios::CarregaBackground(nomeArquivo);
}

/********************************
A funçăo PlayBackground() é responsável por tocar um áudio de background previamente carregado.
Parâmetros:
nVezes (entrada, passagem por valor): indica o número de vezes que o background deve ser executado.
O valor -1 indica que deve ser tocado indefinidamente.
********************************/
void PlayBackground(int nVezes=-1){
    CPIGGerenciadorAudios::PlayBackground(nVezes);
}

/********************************
A funçăo StopBackground() é responsável por parar um áudio de background previamente carregado.
********************************/
void StopBackground(){
    CPIGGerenciadorAudios::StopBackground();
}

/********************************
A funçăo PauseBackground() é responsável por pausar um áudio de background previamente carregado.
********************************/
void PauseBackground(){
    CPIGGerenciadorAudios::PauseBackground();
}

/********************************
A funçăo ResumeBackground() é responsável por continuar a tocar um áudio de background previamente carregado.
********************************/
void ResumeBackground(){
    CPIGGerenciadorAudios::ResumeBackground();
}

/********************************
A funçăo GetStatusBackground() recupera o status do audio de background.
Retorno:
Retorna: o valor do status do áudio de background(AUDIO_TOCANDO, AUDIO_PARADO ou AUDIO_PAUSADO)
********************************/
PIG_StatusAudio GetStatusBackground(){
    return CPIGGerenciadorAudios::GetStatusBackground();
}

/********************************
A funçăo SetVolumeBackground() define o valor do volume do áudio de background.
Parâmetro:
valor (entrada, passagem por valor): valor do novo volume a ser utilizado. Os valores devem ser entre 0 (mudo) e 128 (volume máximo).
********************************/
void SetVolumeBackground(int valor){
    CPIGGerenciadorAudios::SetVolumeBackground(valor);
}

/********************************
A funçăo GetVolumeBackground() recupera o valor do volume do áudio de background.
Retorno:
Retorna o valor do volume do audio de background. Os valores devem ser entre 0 (mudo) e 128 (volume máximo).
********************************/
int GetVolumeBackground(){
    return CPIGGerenciadorAudios::GetVolumeBackground();
}

/********************************
A funçăo SetVolumeBackground() define o valor do volume do áudio em questăo.
Parâmetro:
idAudio (entrada, passagem por valor): identificador do áudio.
volume (entrada, passagem por valor): valor do novo volume a ser utilizado. Os valores devem ser entre 0 (mudo) e 128 (volume máximo).
********************************/
void SetVolume(int idAudio,int volume){
    CPIGGerenciadorAudios::GetAudio(idAudio)->SetVolume(volume);
}

/********************************
A funçăo SetVolumeBackground() recupera o valor do volume do áudio em questăo.
Parâmetro:
idAudio (entrada, passagem por valor): identificador do áudio.
Retorno:
Retorna o valor do volume do audio. Os valores devem ser entre 0 (mudo) e 128 (volume máximo).
********************************/
int GetVolume(int idAudio){
    return CPIGGerenciadorAudios::GetAudio(idAudio)->GetVolume();
}

/********************************
A funçăo SetVolumeBackground() define o valor do volume de todos os áudios.
Parâmetro:
volume (entrada, passagem por valor): valor do novo volume a ser utilizado. Os valores devem ser entre 0 (mudo) e 128 (volume máximo).
********************************/
void SetVolumeTudo(int volume){
    CPIGGerenciadorAudios::SetVolumeTudo(volume);
}

/********************************
A funçăo PlayAudio() é responsável por tocar um áudio previamente criado.
Parâmetro:
idAudio (entrada, passagem por valor): indentificador do áudio.
********************************/
void PlayAudio(int idAudio){
    CPIGGerenciadorAudios::Play(idAudio);
}

/********************************
A funçăo PauseAudio() é responsável por pausar um áudio que esteja tocandoo.
Parâmetro:
idAudio (entrada, passagem por valor): indentificador do áudio.
********************************/
void PauseAudio(int idAudio){
    CPIGGerenciadorAudios::GetAudio(idAudio)->Pause();
}

/********************************
A funçăo ResumeAudio() é responsável por continuar a tocar um áudio pausado.
Parâmetro:
idAudio (entrada, passagem por valor): indentificador do áudio.
********************************/
void ResumeAudio(int idAudio){
    CPIGGerenciadorAudios::GetAudio(idAudio)->Resume();
}

/********************************
A funçăo StopAudio() é responsável por parar um áudio pausado ou tocando.
Parâmetro:
idAudio (entrada, passagem por valor): indentificador do áudio.
********************************/
void StopAudio(int idAudio){
    CPIGGerenciadorAudios::GetAudio(idAudio)->Stop();
}

/********************************
A funçăo GetStatusAudio() recupera o status do audio em questăo.
Parâmetro:
idAudio (entrada, passagem por valor): indentificador do áudio.
Retorno:
Retorna: o valor do status do áudio (AUDIO_TOCANDO, AUDIO_PARADO ou AUDIO_PAUSADO)
********************************/
PIG_StatusAudio GetStatusAudio(int idAudio){
    return CPIGGerenciadorAudios::GetAudio(idAudio)->GetStatus();
}

/********************************
A funçăo ResumeTudoAudio() é responsável por parar todos os áudios pausados ou tocando.
********************************/
void StopTudoAudio(){
    CPIGGerenciadorAudios::StopTudo();
}

/********************************
A funçăo PauseTudoAudio() é responsável por pausar todos os áudios que estiverem tocando.
********************************/
void PauseTudoAudio(){
    CPIGGerenciadorAudios::PauseTudo();
}

/********************************
A funçăo ResumeTudoAudio() é responsável por continuar a tocar todos os áudios pausados.
********************************/
void ResumeTudoAudio(){
    CPIGGerenciadorAudios::ResumeTudo();
}

/********************************
Seçăo dos sockets
********************************/

/********************************
A funçăo CriaSocketCliente() é responsável por abrir uma conexăo TCP com um servidor por meio do seu hostname, que pode ser o nome do computador
em uma rede local ou seu endereço IP, e uma porta. O servidor precisa estar online ou a conexăo năo será estabelecida.
Parâmetros:
hostname (entrada, passagem por valor): nome do computador (servidor) na rede local ou endereço IP
porta (entrada, passagem por valor): número da porta aberta no servidor
maxBytesPacote (entrada, passagem por valor): tamanho máximo de bytes enviados e/ou recebidos de cada vez
Retorno:
Identificador do socket cliente que foi criado.
********************************/
int CriaSocketCliente(char *hostname, int porta, int maxBytesPacote=PIG_MAX_MENSAGEM_REDE_TCP){
    return CPIGGerenciadorSockets::CriaCliente(hostname,porta,maxBytesPacote);
}

/********************************
A funçăo CriaSocketServidor() é responsável por abrir um canal de comunicaçăo para transmissőes entrantes (ingoing).
A criaçăo do socket pode ser impedida por políticas de acesso do firewall instalado.
Parâmetros:
maxClientes (entrada, passagem por valor): número máximo de clientes que poderăo se comunicar concomitantemente com o servidor.
porta (entrada, passagem por valor): número da porta a ser aberta. Deve ser utilizado um valor na faixa 0-65535 que năo esteja sendo utilizado por nenhum outro processo.
maxBytesPacote (entrada, passagem por valor): tamanho máximo de bytes enviados e/ou recebidos de cada vez.
Retorno:
Identificador do socket servidor que foi criado.
********************************/
int CriaSocketServidor(int maxClientes, int porta, int maxBytesPacote=PIG_MAX_MENSAGEM_REDE_TCP){
    return CPIGGerenciadorSockets::CriaServidor(maxClientes,porta,maxBytesPacote);
}

/********************************
A funçăo CriaSocketUDP() é responsável por abrir um canal de comunicaçăo transmissőes de acordo com o protocolo UDP.
O mesmo socket é utilizado para envio e recebimento das informçőes, năo havendo papel de cliente e servidor distintos.
Parâmetros:
porta (entrada, passagem por valor): número da porta a ser aberta. Deve ser utilizado um valor na faixa 0-65535 que năo esteja sendo utilizado por nenhum outro processo.
Retorno:
Identificador do socket UDP que foi criado.
********************************/
int CriaSocketUDP(int porta){
    return CPIGGerenciadorSockets::CriaSocketUDP(porta);
}

/********************************
A funçăo DestroiSocketCliente() é responsável por fechar o socket cliente aberto, impossibilitando novos envios e recebimentos por ele.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket a ser fechado.
********************************/
void DestroiSocketCliente(int idSocket){
    CPIGGerenciadorSockets::DestroiCliente(idSocket);
}

/********************************
A funçăo DestroiSocketServidor() é responsável por fechar o socket servidor aberto, impossibilitando novos envios e recebimentos por ele.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket a ser fechado.
********************************/
void DestroiSocketServidor(int idSocket){
    CPIGGerenciadorSockets::DestroiServidor(idSocket);
}

/********************************
A funçăo DestroiSocketUDP() é responsável por fechar o socket UDP aberto, impossibilitando novos envios e recebimentos por ele.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket a ser fechado.
********************************/
void DestroiSocketUDP(int idSocket){
    CPIGGerenciadorSockets::DestroiSocketUDP(idSocket);
}

/********************************
A funçăo GetAtivoSocketCliente() é responsável por verificar se o socket cliente ainda está ativo e conectado ao servidor ou năo.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro que determina se o socket cliente ainda está ativo e conectado (valor diferente de zero) ou năo (valor zero)
********************************/
int GetAtivoSocketCliente(int idSocket){
    return CPIGGerenciadorSockets::GetCliente(idSocket)->GetAtivo();
}

/********************************
A funçăo GetAtivoSocketServidor() é responsável por verificar se o socket servidor ainda está ativo ou năo.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro que determina se o socket servidor ainda está ativo (valor diferente de zero) ou năo (valor zero)
********************************/
int GetAtivoSocketServidor(int idSocket){
    return CPIGGerenciadorSockets::GetServidor(idSocket)->GetAtivo();
}

/********************************
A funçăo GetAtivoSocketUDP() é responsável por verificar se o socket UDP ainda está ativo ou năo.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro que determina se o socket UDP ainda está ativo (valor diferente de zero) ou năo (valor zero)
********************************/
int GetAtivoSocketUDP(int idSocket){
    return CPIGGerenciadorSockets::GetSocketUDP(idSocket)->GetAtivo();
}

/********************************
A funçăo GetBytesEnviadosSocketCliente() é responsável por recuperar a quantidade de bytes já enviados através do socket cliente desde a sua criaçăo.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica a quantidade de bytes enviados através do socket.
********************************/
long GetBytesEnviadosSocketCliente(int idSocket){
    return CPIGGerenciadorSockets::GetCliente(idSocket)->GetBytesEnviados();
}

/********************************
A funçăo GetBytesRecebidosSocketCliente() é responsável por recuperar a quantidade de bytes já recebidos através do socket cliente desde a sua criaçăo.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica a quantidade de bytes recebidos através do socket.
********************************/
long GetBytesRecebidosSocketCliente(int idSocket){
    return CPIGGerenciadorSockets::GetCliente(idSocket)->GetBytesRecebidos();
}

/********************************
A funçăo GetPacotesEnviadosSocketCliente() é responsável por recuperar a quantidade de pacotes (mensagens) já enviados através do socket cliente desde a sua criaçăo.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica a quantidade de pacotes enviados através do socket.
********************************/
long GetPacotesEnviadosSocketCliente(int idSocket){
    return CPIGGerenciadorSockets::GetCliente(idSocket)->GetPacotesEnviados();
}

/********************************
A funçăo GetPacotesRecebidosSocketCliente() é responsável por recuperar a quantidade de pacotes (mensagens) já recebidos através do socket cliente desde a sua criaçăo.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica a quantidade de pacotes recebidos através do socket.
********************************/
long GetPacotesRecebidosSocketCliente(int idSocket){
    return CPIGGerenciadorSockets::GetCliente(idSocket)->GetPacotesRecebidos();
}

/********************************
A funçăo GetTempoUltimoRecebidoSocketCliente() é responsável por recuperar o momento em que o último pacote foi recebido pelo socket.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica o tempo do recebimento do último pacote pelo socket.
********************************/
long GetTempoUltimoRecebidoSocketCliente(int idSocket){
    return CPIGGerenciadorSockets::GetCliente(idSocket)->GetTempoUltimoRecebido();
}

/********************************
A funçăo GetTempoUltimoEnviadoSocketCliente() é responsável por recuperar o momento em que o último pacote foi enviado pelo socket.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica o tempo do envio do último pacote pelo socket.
********************************/
long GetTempoUltimoEnviadoSocketCliente(int idSocket){
    return CPIGGerenciadorSockets::GetCliente(idSocket)->GetTempoUltimoEnviado();
}

/********************************
A funçăo GetBytesEnviadosSocketServidor() é responsável por recuperar a quantidade de bytes já enviados através do socket cliente desde a sua criaçăo.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica a quantidade de bytes enviados através do socket.
********************************/
long GetBytesEnviadosSocketServidor(int idSocket){
    return CPIGGerenciadorSockets::GetServidor(idSocket)->GetBytesEnviados();
}

/********************************
A funçăo GetBytesRecebidosSocketServidor() é responsável por recuperar a quantidade de bytes já recebidos através do socket cliente desde a sua criaçăo.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica a quantidade de bytes recebidos através do socket.
********************************/
long GetBytesRecebidosSocketServidor(int idSocket){
    return CPIGGerenciadorSockets::GetServidor(idSocket)->GetBytesRecebidos();
}

/********************************
A funçăo GetPacotesEnviadosSocketServidor() é responsável por recuperar a quantidade de pacotes (mensagens) já enviados através do socket cliente desde a sua criaçăo.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica a quantidade de pacotes enviados através do socket.
********************************/
long GetPacotesEnviadosSocketServidor(int idSocket){
    return CPIGGerenciadorSockets::GetCliente(idSocket)->GetPacotesEnviados();
}

/********************************
A funçăo GetPacotesRecebidosSocketServidor() é responsável por recuperar a quantidade de pacotes (mensagens) já recebidos através do socket cliente desde a sua criaçăo.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica a quantidade de pacotes recebidos através do socket.
********************************/
long GetPacotesRecebidosSocketServidor(int idSocket){
    return CPIGGerenciadorSockets::GetCliente(idSocket)->GetPacotesRecebidos();
}

/********************************
A funçăo GetTempoUltimoRecebidoSocketServidor() é responsável por recuperar o momento em que o último pacote foi recebido pelo socket.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica o tempo do recebimento do último pacote pelo socket.
********************************/
long GetTempoUltimoRecebidoSocketServidor(int idSocket){
    return CPIGGerenciadorSockets::GetServidor(idSocket)->GetTempoUltimoRecebido();
}

/********************************
A funçăo GetTempoUltimoEnviadoSocketServidor() é responsável por recuperar o momento em que o último pacote foi enviado pelo socket.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica o tempo do envio do último pacote pelo socket.
********************************/
long GetTempoUltimoEnviadoSocketServidor(int idSocket){
    return CPIGGerenciadorSockets::GetServidor(idSocket)->GetTempoUltimoEnviado();
}

/********************************
A funçăo GetBytesEnviadosSocketUDP() é responsável por recuperar a quantidade de bytes já enviados através do socket cliente desde a sua criaçăo.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica a quantidade de bytes enviados através do socket.
********************************/
long GetBytesEnviadosSocketUDP(int idSocket){
    return CPIGGerenciadorSockets::GetSocketUDP(idSocket)->GetBytesEnviados();
}

/********************************
A funçăo GetBytesRecebidosSocketUDP() é responsável por recuperar a quantidade de bytes já recebidos através do socket cliente desde a sua criaçăo.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica a quantidade de bytes recebidos através do socket.
********************************/
long GetBytesRecebidosSocketUDP(int idSocket){
    return CPIGGerenciadorSockets::GetSocketUDP(idSocket)->GetBytesRecebidos();
}

/********************************
A funçăo GetPacotesEnviadosSocketUDP() é responsável por recuperar a quantidade de pacotes (mensagens) já enviados através do socket cliente desde a sua criaçăo.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica a quantidade de pacotes enviados através do socket.
********************************/
long GetPacotesEnviadosSocketUDP(int idSocket){
    return CPIGGerenciadorSockets::GetSocketUDP(idSocket)->GetPacotesEnviados();
}

/********************************
A funçăo GetPacotesRecebidosSocketUDP() é responsável por recuperar a quantidade de pacotes (mensagens) já recebidos através do socket cliente desde a sua criaçăo.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica a quantidade de pacotes recebidos através do socket.
********************************/
long GetPacotesRecebidosSocketUDP(int idSocket){
    return CPIGGerenciadorSockets::GetSocketUDP(idSocket)->GetPacotesRecebidos();
}

/********************************
A funçăo GetTempoUltimoRecebidoSocketUDP() é responsável por recuperar o momento em que o último pacote foi recebido pelo socket.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica o tempo do recebimento do último pacote pelo socket.
********************************/
long GetTempoUltimoRecebidoSocketUDP(int idSocket){
    return CPIGGerenciadorSockets::GetSocketUDP(idSocket)->GetTempoUltimoRecebido();
}

/********************************
A funçăo GetTempoUltimoEnviadoSocketUDP() é responsável por recuperar o momento em que o último pacote foi enviado pelo socket.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica o tempo do envio do último pacote pelo socket.
********************************/
long GetTempoUltimoEnviadoSocketUDP(int idSocket){
    return CPIGGerenciadorSockets::GetSocketUDP(idSocket)->GetTempoUltimoEnviado();
}

/********************************
A funçăo GetPortaRemotaSocketCliente() é responsável por recuperar o número da porta remota (do servidor) ŕ qual está conectado o socket.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro que indica o número da porta remota (do servidor) ŕ qual está conectado o socket.
********************************/
int GetPortaRemotaSocketCliente(int idSocket){
    return CPIGGerenciadorSockets::GetCliente(idSocket)->GetPortaRemota();
}

/********************************
A funçăo GetPortaLocalSocketServidor() é responsável por recuperar o número da porta local que está sendo utilizada pelo socket servidor.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro que indica o número da porta local do socket servidor.
********************************/
int GetPortaLocalSocketServidor(int idSocket){
    return CPIGGerenciadorSockets::GetServidor(idSocket)->GetPortaLocal();
}

/********************************
A funçăo GetPortaLocalSocketUDP() é responsável por recuperar o número da porta local que está sendo utilizada pelo socket UDP.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro que indica o número da porta local do socket UDP.
********************************/
int GetPortaLocalSocketUDP(int idSocket){
    return CPIGGerenciadorSockets::GetSocketUDP(idSocket)->GetPortaLocal();
}

/********************************
A funçăo GetHostRemotoSocketCliente() é responsável por recuperar o nome do computador (da rede local) ou do endereço IP ao qual está conectado o socket cliente, ou seja, o servidor.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
hostname (saída, passagem por referęncia): nome do computador (da rede local) ou do endereço IP ao qual está conectado o socket cliente.
********************************/
void GetHostRemotoSocketCliente(int idSocket,char *hostname){
    strcpy(hostname,CPIGGerenciadorSockets::GetCliente(idSocket)->GetHostRemoto().c_str());
}

/********************************
A funçăo GetHostLocalSocketCliente() é responsável por recuperar o nome do computador (na rede local) ou do endereço IP da máquina está aberto o socket cliente.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
hostname (saída, passagem por referęncia): nome do computador (na rede local) ou do endereço IP da máquina no qual está aberto o socket cliente.
********************************/
void GetHostLocalSocketCliente(int idSocket,char *hostname){
    strcpy(hostname,CPIGGerenciadorSockets::GetCliente(idSocket)->GetHostLocal().c_str());
}

/********************************
A funçăo GetHostLocalSocketServidor() é responsável por recuperar o nome do computador (na rede local) ou do endereço IP da máquina está aberto o socket servidor.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
hostname (saída, passagem por referęncia): nome do computador (na rede local) ou do endereço IP da máquina no qual está aberto o socket servidor.
********************************/
void GetHostLocalSocketServidor(int idSocket,char *hostname){
    strcpy(hostname,CPIGGerenciadorSockets::GetServidor(idSocket)->GetHostLocal().c_str());
}

/********************************
A funçăo GetHostLocalSocketUDP() é responsável por recuperar o nome do computador (na rede local) ou do endereço IP da máquina está aberto o socket UDP.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
hostname (saída, passagem por referęncia): nome do computador (na rede local) ou do endereço IP da máquina no qual está aberto o socket UDP.
********************************/
void GetHostLocalSocketUDP(int idSocket,char *hostname){
    strcpy(hostname,CPIGGerenciadorSockets::GetSocketUDP(idSocket)->GetHostLocal().c_str());
}

/********************************
A funçăo GetTamanhoPacoteSocketCliente() é responsável por recuperar o tamanho máximo de bytes utilizado pelo socket para envio ou recebimento de mensagens.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro que indica o tamanho máximo, em bytes, das mensagens enviadas ou recebidas pelo socket.
********************************/
int GetTamanhoPacoteSocketCliente(int idSocket){
    return CPIGGerenciadorSockets::GetCliente(idSocket)->GetTamanhoPacote();
}

/********************************
A funçăo GetTamanhoPacoteSocketServidor() é responsável por recuperar o tamanho máximo de bytes utilizado pelo socket para envio ou recebimento de mensagens.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro que indica o tamanho máximo, em bytes, das mensagens enviadas ou recebidas pelo socket.
********************************/
int GetTamanhoPacoteSocketServidor(int idSocket){
    return CPIGGerenciadorSockets::GetServidor(idSocket)->GetTamanhoPacote();
}

/********************************
A funçăo GetMaximoConexoesSocketServidor() é responsável por recuperar a quantidade máxima de conexőes que podem ser estabelecidas pelo socket servidor com outros sockets clientes.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro que indica a quantidade máxima de conexőes concomitantes que podem ser estabelecidas pelo socket servidor com outros sockets clientes.
********************************/
int GetMaximoConexoesSocketServidor(int idSocket){
    return CPIGGerenciadorSockets::GetServidor(idSocket)->GetMaximoConexoes();
}

/********************************
A funçăo GetQuantidadeConexoesSocketServidor() é responsável por recuperar a quantidade de conexőes atualmente abertas pelo socket servidor com outros sockets clientes.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro que indica a quantidade de conexőes atualmente abertas pelo socket servidor com outros sockets clientes.
********************************/
int GetQuantidadeConexoesSocketServidor(int idSocket){
    return CPIGGerenciadorSockets::GetServidor(idSocket)->GetQuantidadeConexoes();
}

/********************************
A funçăo EnviaDadosSocketCliente() é responsável por efetivamente enviar bytes armazenados em memória principal através do socket cliente, para o servidor.
O recebimento de dados através da rede pode ser detectado pela geraçăo de um evento de rede. A mensagem transmitida deve ser recuperada a partir desse evento.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
buffer (entrada, passagem por valor): ponteiro (endereço) para o local da memória onde estăo armazenados os dados a serem transmitidos. Pode ser, inclusive, o nome de uma string ou vetor.
tamanhoBuffer (entrada, passagem por valor): quantidade de bytes que devem ser lidos e transmitidos a partir do endereço indicado no buffer.
Retorno:
Inteiro que indica a quantidade de bytes efetivamente transmitida.
********************************/
int EnviaDadosSocketCliente(int idSocket,void *buffer, int tamanhoBuffer){
    return CPIGGerenciadorSockets::GetCliente(idSocket)->EnviaDados(buffer,tamanhoBuffer);
}

/********************************
A funçăo EnviaDadosSocketServidor() é responsável por efetivamente enviar bytes armazenados em memória principal através do socket servidor, para o cliente.
O recebimento de dados através da rede pode ser detectado pela geraçăo de um evento de rede. A mensagem transmitida deve ser recuperada a partir desse evento.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
buffer (entrada, passagem por valor): ponteiro (endereço) para o local da memória onde estăo armazenados os dados a serem transmitidos. Pode ser, inclusive, o nome de uma string ou vetor.
tamanhoBuffer (entrada, passagem por valor): quantidade de bytes que devem ser lidos e transmitidos a partir do endereço indicado no buffer.
Retorno:
Inteiro que indica a quantidade de bytes efetivamente transmitida.
********************************/
int EnviaDadosSocketServidor(int idSocket,int socketSecundario,void *buffer, int tamanhoBuffer){
    return CPIGGerenciadorSockets::GetServidor(idSocket)->EnviaDados(buffer,tamanhoBuffer,socketSecundario);
}

/********************************
A funçăo EnviaDadosSocketUDP() é responsável por efetivamente enviar bytes armazenados em memória principal através do socket UDP, para outro socket UDP.
O recebimento de dados através da rede pode ser detectado pela geraçăo de um evento de rede. A mensagem transmitida deve ser recuperada a partir desse evento.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
buffer (entrada, passagem por valor): ponteiro (endereço) para o local da memória onde estăo armazenados os dados a serem transmitidos. Pode ser, inclusive, o nome de uma string ou vetor.
tamanhoBuffer (entrada, passagem por valor): quantidade de bytes que devem ser lidos e transmitidos a partir do endereço indicado no buffer.
Retorno:
Inteiro que indica a quantidade de bytes efetivamente transmitida.
********************************/
int EnviaDadosSocketUDP(int idSocket,void *buffer,int tamanhoBuffer, char *hostRemoto, int porta){
    return CPIGGerenciadorSockets::GetSocketUDP(idSocket)->EnviaDados(buffer,tamanhoBuffer,hostRemoto,porta);
}


#ifdef PIGCOMVIDEO

/********************************
Seçăo dos vídeos.
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
Toda a parte de vídeo é considerada experimental e pode năo funcionar dependendo do vídeo,
dos drives instalados, do sistema operacional ou do formato do vídeo.
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
********************************/


/********************************
A funçăo CriaVideo() é responsável por ler e preparar um arquivo de vídeo.
Os formatos permitidos săo AVI, MP4, MOV.
Parâmetros:
nomeArquivo (entrada, passagem por referęncia): string que informa o nome do arquivo de vídeo.
idJanela (entrada, passagem por valor): indica em qual janela o vídeo será exibido.
Retorno:
Retorna o identificador do vídeo para ser utilizado por outras funçőes.
********************************/
int CriaVideo(char *nomeArquivo,int idJanela=0){
    return CPIGGerenciadorVideos::CriaVideo(nomeArquivo,idJanela);
}

/********************************
A funçăo DestroiVideo() é responsável por eliminar um vídeo do jogo.
Parâmetros:
idVideo (entrada, passagem por valor): identificador do vídeo a ser excluído.
********************************/
void DestroiVideo(int idVideo){
    CPIGGerenciadorVideos::DestroiVideo(idVideo);
}

/********************************
A funçăo SetSeekVideo() é responsável por avançar ou retroceder o vídeo instantaneamente.
Parâmetros:
idVideo (entrada, passagem por valor): identificador do vídeo.
incremento (entrada, passagem por valor): quantidade de tempo (em segundos) para o avançao ou retrocesso do vídeo.
********************************/
void SetSeekVideo(int idVideo, double incremento){
    CPIGGerenciadorVideos::GetVideo(idVideo)->SetSeek(incremento);
}

/********************************
A funçăo PlayVideo() é responsável por tocar um vídeo previamente criado.
Parâmetro:
idVideo (entrada, passagem por valor): indentificador do vídeo.
********************************/
void PlayVideo(int idVideo){
    CPIGGerenciadorVideos::GetVideo(idVideo)->Play();
}

/********************************
A funçăo StopVideo() é responsável por parar um vídeo pausado ou tocando.
Parâmetro:
idVideo (entrada, passagem por valor): indentificador do vídeo.
********************************/
void StopVideo(int idVideo){
    CPIGGerenciadorVideos::GetVideo(idVideo)->Stop();
}

/********************************
A funçăo PauseVideo() é responsável por pausar um vídeo que esteja tocando.
Parâmetro:
idVideo (entrada, passagem por valor): indentificador do vídeo.
********************************/
void PauseVideo(int idVideo){
    CPIGGerenciadorVideos::GetVideo(idVideo)->Pause();
}

/********************************
A funçăo ResumeVideo() é responsável por continuar a tocar um vídeo pausado.
Parâmetro:
idVideo (entrada, passagem por valor): indentificador do vídeo.
********************************/
void ResumeVideo(int idVideo){
    CPIGGerenciadorVideos::GetVideo(idVideo)->Resume();
}

/********************************
A funçăo DesenhaVideo() é responsável por desenhar os frames de um vídeo na tela. O vídeo será desenhado de acordo com todas as definiçőes
de posiçăo e ângulo informado até o momento. Além disso, se o vídeo estiver virado (flipping), isso também será levado em consideraçăo, bem como a coloraçăo e a opacidade definidas.
Parâmetro:
idVideo (entrada, passagem por valor): identificador do vídeo a ser desenhado.
********************************/
int DesenhaVideo(int idVideo){
    return CPIGGerenciadorVideos::GetVideo(idVideo)->Desenha();
}

/********************************
A funçăo SetVolumeVideo() é responsável por definir o volume para o vídeo. O valor informado deve ser positivo ou zero (mudo).
Parâmetro:
idVideo (entrada, passagem por valor): indentificador do vídeo.
valor (entrada, passagem por valor): volume a ser definido. Deve ser positivo ou zero (mudo).
********************************/
void SetVolumeVideo(int idVideo, double valor){
    CPIGGerenciadorVideos::GetVideo(idVideo)->SetVolume(valor);
}

/********************************
A funçăo GetVolumeVideo() é responsável por recuperar o valor do volume do vídeo.
Parâmetro:
idVideo (entrada, passagem por valor): indentificador do vídeo.
Retorno:
Nível de volume do vídeo (deve ser sempre um valor positivo).
********************************/
double GetVolumeVideo(int idVideo){
    return CPIGGerenciadorVideos::GetVideo(idVideo)->GetVolume();
}

/********************************
A funçăo GetNomeArquivoVideo() é responsável por recuperar o nome do arquivo que deu origem ao video.
Parâmetro:
idVideo (entrada, passagem por valor): indentificador do vídeo.
nome (saída, passagem por referęncia): nome do arquivo utilizado para criar o video.
********************************/
void GetNomeArquivoVideo(int idVideo, char *nome){
    strcpy(nome,CPIGGerenciadorVideos::GetVideo(idVideo)->GetNomeArquivo().c_str());
}

/********************************
A funçăo GetTempoAtualVideo() é responsável por recuperar o valor (em milissegundo) do tempo de vídeo já exibido, ou seja, o momento atual do vídeo.
Parâmetro:
idVideo (entrada, passagem por valor): indentificador do vídeo.
Retorno:
Total de tempo (em milissegundos) da parte já exibida do vídeo.
********************************/
double GetTempoAtualVideo(int idVideo){
    return CPIGGerenciadorVideos::GetVideo(idVideo)->GetTempoAtual();
}

/********************************
A funçăo GetTempoAtualVideo() é responsável por recuperar uma string contendo a hora, minuto, segundo e milissegundo do frame atual do video.
Parâmetro:
idVideo (entrada, passagem por valor): indentificador do vídeo.
str (saída, passagem por referęncia): posiçăo do frame atual, definido em hora, minuto, segundo e milissegundo.
********************************/
void GetTempoAtualVideo(int idVideo, char *str){
    strcpy(str,CPIGGerenciadorVideos::GetVideo(idVideo)->GetTempoAtualString().c_str());
}

/********************************
A funçăo GetTempoTotalVideo() é responsável por recuperar a druaçăo total do vídeo (em milissegundo).
Parâmetro:
idVideo (entrada, passagem por valor): indentificador do vídeo.
Retorno
Tempo total do vídeo em milissegundos.
********************************/
double GetTempoTotalVideo(int idVideo){
    return CPIGGerenciadorVideos::GetVideo(idVideo)->GetTempoTotal();
}

/********************************
A funçăo GetTempoTotalVideo() é responsável por recuperar uma string contendo a duraçăo do video em hora, minuto, segundo e milissegundo.
Parâmetro:
idVideo (entrada, passagem por valor): indentificador do vídeo.
str (saída, passagem por referęncia): duraçăo do vídeo, definido em hora, minuto, segundo e milissegundo.
********************************/
void GetTempoTotalVideo(int idVideo, char *str){
    strcpy(str,CPIGGerenciadorVideos::GetVideo(idVideo)->GetTempoTotalString().c_str());
}

/********************************
A funçăo GetTempoFrameVideo() é responsável por recuperar a duraçăo esperada para cada frame do video (em milissegundo).
Parâmetro:
idVideo (entrada, passagem por valor): indentificador do vídeo.
Retorno:
Duraçăo esperado de cada frame do vídeo (em milissegundo).
********************************/
double GetTempoFrameVideo(int idVideo){
    return CPIGGerenciadorVideos::GetVideo(idVideo)->GetTempoFrame();
}

/********************************
A funçăo GetFPSVideo() é responsável por recuperar a quantidade de frames do vídeo que deveriam ser exibidos a cada segundo.
Parâmetro:
idVideo (entrada, passagem por valor): indentificador do vídeo.
Retorno:
Quantidade desejada de frames a cada segundo.
********************************/
double GetFPSVideo(int idVideo){
    return CPIGGerenciadorVideos::GetVideo(idVideo)->GetFPS();
}

/********************************
A funçăo SetAnguloVideo() é responsável pela angulaçăo de determinado vídeo. A angulaçăo é calculada em sentido
horário a partir do eixo X (0 graus). O vídeo será desenhado com a angulaçăo informada no próximo comando
DesenhaVideo().
Parâmetros:
idVideo (entrada, passagem por valor): identificador do vídeo.
angulo (entrada, passagem por valor): valor para indicar a angulaçăo do vídeo em graus.
********************************/
void SetAnguloVideo(int idVideo, float angulo){
    CPIGGerenciadorVideos::GetVideo(idVideo)->SetAngulo(angulo);
}

/********************************
A funçăo GetAnguloVideo() é responsável por recuperar o ângulo de rotaçăo de determinado vídeo. A angulaçăo é calculada em sentido
horário a partir do eixo X (0 graus). O vídeo será desenhado com a angulaçăo informada no próximo comando
DesenhaVideo().
idVideo (entrada, passagem por valor): identificador do vídeo.
Retorno:
Retorna o valor do ângulo em graus.
********************************/
double GetAnguloVideo(int idVideo){
    return CPIGGerenciadorVideos::GetVideo(idVideo)->GetAngulo();
}

/********************************
A funçăo SetFlipVideo() é responsável por virar o vídeo, invertendo-o em alguma direçăo. O vídeo somente será
desenhado na nova orientaçăo no próximo comando DesenhaVideo().
Parâmetros:
idVideo (entrada, passagem por valor): identificador do vídeo a ser virado.
valor (entrada, passagem por valor): valor do tipo de Flip. Pode ser FLIP_NENHUM (nenhum tipo de inversăo),
FLIP_HORIZONTAL (inverte da esquerda para a direita), FLIP_VERTICAL (inverte de cima para baixo),
ou FLIP_HORIZ_VERT (inverte da esquerda para direita e de cima para baixo).
********************************/
void SetFlipVideo(int idVideo, PIG_Flip valor){
    CPIGGerenciadorVideos::GetVideo(idVideo)->SetFlip(valor);
}

/********************************
A funçăo GetFlipVideo() é responsável por recuperar o valor da manipulaçăo causada pela funçăo SetFlipVideo().
Parâmetros:
idVideo (entrada, passagem por valor): identificador do vídeo a ser virado.
Retorno:
inteiro que indica o tipo de Flip. Pode ser PIG_FLIP_NENHUM (nenhum tipo de inversăo),
PIG_FLIP_HORIZONTAL (inverte da esquerda para a direita), PIG_FLIP_VERTICAL (inverte de cima para baixo),
ou PIG_FLIP_HORIZ_VERT (inverte da esquerda para direita e de cima para baixo).
********************************/
PIG_Flip GetFlipVideo(int idVideo){
    return CPIGGerenciadorVideos::GetVideo(idVideo)->GetFlip();
}

/********************************
A funçăo SetPivoAbsolutoVideo() define um ponto (X,Y) em relaçăo ao ponto (0,0) do vídeo, sobre o qual o video será
rotacionado quando a funçăo SetAnguloVideo() for executada.
Parâmetros:
idVideo (entrada, passagem por valor): identificador do vídeo.
posicaoX (entrada, passagem por valor): Valor da coordenada X do pivô em relaçăo ao ponto (0,0) do vídeo.
posicaoY (entrada, passagem por valor): Valor da coordenada Y do pivô em relaçăo ao ponto (0,0) do vídeo.
********************************/
void SetPivoAbsolutoVideo(int idVideo, int posicaoX,int posicaoY){
    CPIGGerenciadorVideos::GetVideo(idVideo)->SetPivoAbsoluto({(double)posicaoX,(double)posicaoY});
}

/********************************
A funçăo SetPivoProporcionalVideo() define um ponto relativo (X,Y) em relaçăo ao video (0,0) e ao tamanho do vídeo, sobre o qual o vídeo será
rotacionado quando a funçăo SetAnguloVideo() for executada.
Parâmetros:
idVideo (entrada, passagem por valor): identificador do vídeo.
relX (entrada, passagem por valor): porcentagem da largura do vídeo onde ficará o pivô.
relY (entrada, passagem por valor): porcentagem da altura do vídeo onde ficará o pivô.
********************************/
void SetPivoProporcionalVideo(int idVideo, float relX,float relY){
    CPIGGerenciadorVideos::GetVideo(idVideo)->SetPivoProporcional({relX,relY});
}

/********************************
A funçăo GetPivoVideo() define um ponto (X,Y) em relaçăo ao ponto (0,0) do vídeo, sobre o qual o vídeo será
rotacionado quando a funçăo SetAnguloVideo() for executada.
Parâmetros:
idVideo (entrada, passagem por valor): identificador do vídeo.
posicaoX (saída, passagem por referęncia): Valor da coordenada X do pivô em relaçăo ao ponto (0,0) do vídeo.
posicaoY (saída, passagem por referęncia): Valor da coordenada Y do pivô em relaçăo ao ponto (0,0) do vídeo.
********************************/
void GetPivoVideo(int idVideo, int *posicaoX,int *posicaoY){
    PIGPonto2D p = CPIGGerenciadorVideos::GetVideo(idVideo)->GetPivo();
    *posicaoX = p.x;
    *posicaoY = p.y;
}

/********************************
A funçăo MoveVideo() é responsável por movimentar um determinado vídeo para uma nova posiçăo informada.
Parâmetros:
idVideo (entrada, passagem por valor): identificador do vídeo a ser movido.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usuário deseja reposicionar o vídeo.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usuário deseja reposicionar o vídeo.
********************************/
void MoveVideo(int idVideo,int posicaoX,int posicaoY){
    CPIGGerenciadorVideos::GetVideo(idVideo)->Move(posicaoX,posicaoY);
}

/********************************
A funçăo SetDimensoesVideo() é responsável por delimitar a altura e a largura do vídeo que será desenhado na tela,
independentemente do tamanho original do arquivo.
Parâmetros:
idVideo (entrada, passagem por valor): identificador do vídeo.
altura (entrada, passagem por valor): altura em pixels.
largura (entrada, passagem por valor): largura em pixels.
********************************/
void SetDimensoesVideo(int idVideo, int altura,int largura){
    CPIGGerenciadorVideos::GetVideo(idVideo)->SetDimensoes(altura,largura);
}

/********************************
A funçăo GetDimensoesVideo() é responsável por recuperar a altura e a largura da área a ser usada
para desenhar o vídeo na tela. Em outras palavras, representa o tamanho atual do vídeo.
Parâmetros:
idVideo (entrada, passagem por valor): identificador do vídeo.
altura (saída, passagem por referęncia): altura atual em pixels do vídeo.
largura (saída, passagem por referęncia): largura atual em pixels do vídeo.
********************************/
void GetDimensoesVideo(int idVideo, int *altura, int *largura){
    CPIGGerenciadorVideos::GetVideo(idVideo)->GetDimensoes(*altura,*largura);
}

/********************************
A funçăo GetDimensoesOriginaisVideo() é responsável por recuperar a altura e a largura originais dos frames do vídeo.
Qualquer utilizaçăo da funçăo SetDimensoesVideo() é ignorada para o cálculo desta funçăo.
Parâmetros:
idVideo (entrada, passagem por valor): identificador do vídeo.
altura (saída, passagem por referęncia): altura original em pixels do vídeo.
largura (saída, passagem por referęncia): largura original em pixels do vídeo.
********************************/
void GetDimensoesOriginaisVideo(int idVideo, int *altura, int *largura){
    CPIGGerenciadorVideos::GetVideo(idVideo)->GetResolucao(*altura,*largura);
}

/********************************
A funçăo OcupaJanelaInteiraVideo() é responsável por redimensionar a exibiçăo do video, para que este ocupe todo o tamanho
da janela em que estiver sendo executado.
Parâmetros:
idVideo (entrada, passagem por valor): identificador do vídeo a ser desenhado.
********************************/
void OcupaJanelaInteiraVideo(int idVideo){
    CPIGGerenciadorVideos::GetVideo(idVideo)->OcupaJanelaInteira();
}

/********************************
A funçăo UsaResolucaoOriginalVideo() é responsável por redimensionar a exibiçăo do video, para que este utilize a resoluçăo original
do arquivo de mídia.
Parâmetros:
idVideo (entrada, passagem por valor): identificador do vídeo a ser desenhado.
********************************/
void UsaResolucaoOriginalVideo(int idVideo){
    CPIGGerenciadorVideos::GetVideo(idVideo)->UsaResolucaoOriginal();
}

/********************************
A funçăo SetColoracaoVideo() é responsável por mesclar uma determinada cor com os pixels do frame do vídeo.
Após a modificaçăo, todos os desenhos deste vídeo serăo mostrados já com a mesclagem definida.
Para voltar ao padrăo original de pixels, deve-se chamar a funçăo, passando a cor branca (255,255,255).
Parâmetros:
idVideo (entrada, passagem por valor): identificador do vídeo a ser desenhado.
cor (entrada,passagem por valor): cor do sistema RGB utilizada para mesclagem com o arquivo de vídeo.
********************************/
void SetColoracaoVideo(int idVideo, PIG_Cor cor){
    CPIGGerenciadorVideos::GetVideo(idVideo)->SetColoracao(cor);
}

/********************************
A funçăo SetOpacidadeVideo() é responsável por modificar o nível de opacidade do vídeo.
O nível de opacidade varia de 0-255, sendo 0 totalmente transparente e 255 totalmente opaco.
Parâmetros:
idVideo (entrada, passagem por valor): identificador do vídeo.
valor (entrada,passagem por valor): nível de opacidade do vídeo na faixa 0-255.
********************************/
void SetOpacidadeVideo(int idVideo, int valor){
    CPIGGerenciadorVideos::GetVideo(idVideo)->SetOpacidade(valor);
}

/********************************
A funçăo GetOpacidadeVideo() é responsável por recuperar o nível de opacidade de determinado vídeo.
O nível de opacidade varia de 0-255, sendo 0 totalmente transparente e 255 totalmente opaco.
Parâmetros:
idVideo (entrada, passagem por valor): identificador do vídeo.
Retorno:
Retorna o nível de opacidade do vídeo na faixa 0-255.
********************************/
int GetOpacidadeVideo(int idVideo){
    return CPIGGerenciadorVideos::GetVideo(idVideo)->GetOpacidade();
}

#endif

/*******FORM*********/

int PIG_CriaForm(int xForm, int yForm, int altForm, int largForm,int janela = 0){
    return CPIGGerenciadorForms::CriaForm(xForm,yForm,altForm,largForm,janela);
}

int PIG_Form_TrataEvento(int idForm,PIG_Evento evento){
    return CPIGGerenciadorForms::GetForm(idForm)->TrataEvento(evento);
}

int PIG_Form_Desenha(int idForm){
    return CPIGGerenciadorForms::GetForm(idForm)->Desenha();
}

void PIG_DestroiForm(int idForm){
    CPIGGerenciadorForms::DestroiForm(idForm);
}

/*******COMPONENTES*********/

int PIG_CriaComponentePorParametro(int idForm,PIGTiposComponentes componente,char* parametros){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaComponentePorParametro(componente,parametros);//CPIGGerenciadorForms::CriaComponentePorArquivo(idForm,componente,nomeArquivo);
}

void PIG_Componentes_DefineAcao(int idComponente,PIG_FuncaoSimples funcao,void *parametro){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->DefineAcao(funcao,parametro);
}

void PIG_Componentes_SetLabel(int idComponente,char* novoLabel){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->SetLabel(novoLabel);
}

void PIG_Componentes_SetFonteLabel(int idComponente,int fonte){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->SetFonteLabel(fonte);
}

void PIG_Componentes_SetCorLabel(int idComponente,PIG_Cor cor){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->SetCorLabel(cor);
}

void PIG_Componentes_SetFonteHint(int idComponente,int fonte){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->SetFonteHint(fonte);
}

void PIG_Componentes_SetCorHint(int idComponente,PIG_Cor cor){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->SetCorHint(cor);
}

void PIG_Componentes_SetAudio(int idComponente,int idAudio){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->SetAudio(idAudio);
}

void PIG_Componentes_GetLabel(int idComponente,char *label){
    strcpy(label,(char*)(CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->GetLabel()).c_str());
}

void PIG_Componentes_SetHint(int idComponente,char *hint){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->SetHint(hint);
}

void PIG_Componentes_Move(int idComponente,int x,int y){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->Move(x,y);
}

void PIG_Componentes_SetDimensoes(int idComponente,int altura,int largura){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->SetDimensoes(altura,largura);
}

void PIG_Componentes_SetPosicaoPadraoLabel(int idComponente,PIG_PosicaoComponente pos){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->SetPosicaoPadraoLabel(pos);
}

void PIG_Componentes_SetPosicaoPersonalizadaLabel(int idComponente,int x,int y){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->SetPosicaoPersonalizadaLabel(x,y);
}

void PIG_Componentes_SetPosPadraoExternaComponente(int idComponente,PIG_PosicaoComponente pos,CPIGComponente *componenteAssociado){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->SetPosPadraoExternaComponente(pos,componenteAssociado);
}

void PIG_Componentes_SetPosPadraoComponenteNaTela(int idComponente,PIG_Ancora pos){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->SetPosPadraoComponenteNaTela(pos);
}

void PIG_Componentes_SetHabilitado(int idComponente,int valor){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->SetHabilitado(valor);
}

void PIG_Componentes_SetVisivel(int idComponente,int valor){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->SetVisivel(valor);
}

PIG_Cor PIG_Componentes_GetCorLabel(int idComponente){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->GetCorLabel();
}

void PIG_Componentes_GetHint(int idComponente,char* hint){
    strcpy(hint,(char*)(CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->GetHint()).c_str());
}

int PIG_Componentes_GetFonteHint(int idComponente){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->GetFonteHint();
}

int PIG_Componentes_GetVisivel(int idComponente){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->GetVisivel();
}

int PIG_Componentes_GetHabilitado(int idComponente){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->GetHabilitado();
}

int PIG_Componentes_GetAcionado(int idComponente){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->GetAcionado();
}

int PIG_Componentes_GetMouseOver(int idComponente){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->GetMouseOver();
}

PIG_PosicaoComponente PIG_Componentes_GetPosComponente(int idComponente){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->GetPosComponente();
}

void PIG_Componentes_GetDimensoes(int idComponente,int &altura, int &largura){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->GetDimensoes(altura,largura);
}

void PIG_Componentes_GetDimensoesOriginais(int idComponente,int &altura, int &largura){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->GetDimensoesOriginais(altura,largura);
}

/*******BOTAOCLICK*********/

int PIG_CriaBotaoClick(int idForm,int x,int y,int alt,int larg,char* nomeArq,int retiraFundo = 1){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaBotaoClick(x,y,alt,larg,nomeArq,retiraFundo);
}

int PIG_CriaBotaoClick(int idForm,int x,int y,int alt,int larg){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaBotaoClick(x,y,alt,larg);
}

void PIG_BotaoClick_DefineAtalho(int idComponente,int teclaAtalho){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGBotaoClick>(idComponente)->DefineAtalho(teclaAtalho);
}

void PIG_BotaoClick_DefineTempoRepeticao(int idComponente,double segundos){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGBotaoClick>(idComponente)->DefineTempoRepeticao(segundos);
}

void PIG_BotaoClick_DefineBotaoRepeticao(int idComponente,bool repeticao){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGBotaoClick>(idComponente)->DefineBotaoRepeticao(repeticao);
}

/*******BOTAOONOFF*********/

int PIG_CriaBotaoOnOff(int idForm,int x,int y,int alt,int larg,char* nomeArq,int retiraFundo = 1){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaBotaoOnOff(x,y,alt,larg,nomeArq,retiraFundo);
}

int PIG_CriaBotaoOnOff(int idForm,int x,int y,int alt,int larg){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaBotaoOnOff(x,y,alt,larg);
}

void PIG_BotaoOnOff_DefineAtalho(int idComponente,int teclaAtalho){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGBotaoOnOff>(idComponente)->DefineAtalho(teclaAtalho);
}


/*******AREADETEXTO*********/

int PIG_CriaAreaDeTexto(int idForm,int x, int y, int altura,int largura,char* nomeArq,int maxCars = 200,int retiraFundo=1){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaAreaDeTexto(x,y,altura,largura,nomeArq,maxCars,retiraFundo);
}

int PIG_CriaAreaDeTexto(int idForm,int x, int y, int altura,int largura,int maxCars = 200){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaAreaDeTexto(x,y,altura,largura,maxCars);
}

void PIG_AreaDeTexto_SetFonteTexto(int idComponente,int fonte){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGAreaDeTexto>(idComponente)->SetFonteTexto(fonte);
}

void PIG_AreaDeTexto_SetLinhasAbaixoTexto(int idComponente,bool visivel,PIG_Cor cor = PRETO){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGAreaDeTexto>(idComponente)->SetLinhasAbaixoTexto(visivel,cor);
}

void PIG_AreaDeTexto_SetLargMaxTexto(int idComponente,int largMaxTexto){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGAreaDeTexto>(idComponente)->SetLargMaxTexto(largMaxTexto);
}

void PIG_AreaDeTexto_SetEspacoEntreAsLinhas(int idComponente,int espaco){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGAreaDeTexto>(idComponente)->SetEspacoEntreAsLinhas(espaco);
}

void PIG_AreaDeTexto_SetTexto(int idComponente,char* frase){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGAreaDeTexto>(idComponente)->SetTexto(frase);
}

void PIG_AreaDeTexto_SetMargens(int idComponente,int horEsq,int horDir, int vertBaixo,int vertCima){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGAreaDeTexto>(idComponente)->SetMargens(horEsq,horDir,vertBaixo,vertCima);
}

void PIG_AreaDeTexto_SetCorCursor(int idComponente,PIG_Cor cor){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGAreaDeTexto>(idComponente)->SetCorCursor(cor);
}

vector<string> PIG_AreaDeTexto_GetLinhasTexto(int idComponente){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGAreaDeTexto>(idComponente)->GetLinhasTexto();
}

void PIG_AreaDeTexto_GetTexto(int idComponente,char* texto){
    strcpy(texto,(char*)(CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGAreaDeTexto>(idComponente)->GetTexto()).c_str());
}

/**********CAMPOTEXTO**************/

int PIG_CriaCampoTexto(int idForm,int x, int y, int altura,int largura,char* nomeArq,int maxCars = 200, bool apenasNumeros=false, int retiraFundo=1){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaCampoTextoESenha(x,y,altura,largura,nomeArq,maxCars,apenasNumeros,retiraFundo,false);
}

int PIG_CriaCampoTexto(int idForm,int x, int y, int altura,int largura,int maxCars = 200, bool apenasNumeros=false){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaCampoTextoESenha(x,y,altura,largura,maxCars,apenasNumeros,false);
}

void PIG_CampoTexto_SetMargens(int idComponente,int horEsq,int horDir, int vertBaixo,int vertCima){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGCampoTextoESenha>(idComponente)->SetMargens(horEsq,horDir,vertBaixo,vertCima);
}

void PIG_CampoTexto_SetTexto(int idComponente,char* frase){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGCampoTextoESenha>(idComponente)->SetTexto(frase);
}

void PIG_CampoTexto_SetFonteTexto(int idComponente,int fonte){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGCampoTextoESenha>(idComponente)->SetFonteTexto(fonte);
}

void PIG_CampoTexto_SetCorCursor(int idComponente,PIG_Cor cor){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGCampoTextoESenha>(idComponente)->SetCorCursor(cor);
}

void PIG_CampoTexto_GetTexto(int idComponente,char* texto){
    strcpy(texto,(char*)(CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGCampoTextoESenha>(idComponente)->GetTexto()).c_str());
}

/**********CAMPOSENHA**************/

int PIG_CriaCampoSenha(int idForm,int x, int y, int altura,int largura,char* nomeArq,int maxCars = 200, bool apenasNumeros=false, int retiraFundo=1){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaCampoTextoESenha(x,y,altura,largura,nomeArq,maxCars,apenasNumeros,retiraFundo,true);
}

int PIG_CriaCampoSenha(int idForm,int x, int y, int altura,int largura,int maxCars = 200, bool apenasNumeros=false){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaCampoTextoESenha(x,y,altura,largura,maxCars,apenasNumeros,true);
}

void PIG_CampoSenha_SetMargens(int idComponente,int horEsq,int horDir, int vertBaixo,int vertCima){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGCampoTextoESenha>(idComponente)->SetMargens(horEsq,horDir,vertBaixo,vertCima);
}

void PIG_CampoSenha_SetTexto(int idComponente,char* frase){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGCampoTextoESenha>(idComponente)->SetTexto(frase);
}

void PIG_CampoSenha_SetFonteTexto(int idComponente,int fonte){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGCampoTextoESenha>(idComponente)->SetFonteTexto(fonte);
}

void PIG_CampoSenha_SetCorCursor(int idComponente,PIG_Cor cor){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGCampoTextoESenha>(idComponente)->SetCorCursor(cor);
}

/**********LISTA**************/

int PIG_CriaListBox(int idForm,int x, int y,int larguraTotal,int alturaLinha,int alturaItem,int largItem,char* nomeArq,int retiraFundo=1){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaListBox(x,y,larguraTotal,alturaLinha,alturaItem,largItem,nomeArq,retiraFundo);
}

int PIG_CriaListBox(int idForm,int x, int y,int larguraTotal,int alturaLinha,int alturaItem,int largItem){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaListBox(x,y,larguraTotal,alturaLinha,alturaItem,largItem);
}

void PIG_ListBox_CriaItem(int idComponente,char* texto,char* imagemIcone = "",char *imagemFundo="",char* hintMsg="",bool itemHabilitado = true, int retiraFundoImg = 1){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGListBox>(idComponente)->CriaItem(texto,imagemIcone,imagemFundo,false,itemHabilitado,hintMsg,retiraFundoImg);
}

int PIG_ListBox_SetAcionado(int idComponente,int indice, int marcado){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGListBox>(idComponente)->SetAcionado(indice,marcado);
}

void PIG_ListBox_DefineDimensaoIconeItem(int idComponente,int alturaImagemIcone, int larguraImagemIcone){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGListBox>(idComponente)->DefineDimensaoIconeItem(alturaImagemIcone,larguraImagemIcone);
}

void PIG_ListBox_AlinhaLabelDireita(int idComponente){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGListBox>(idComponente)->AlinhaLabelDireita();
}

void PIG_ListBox_AlinhaLabelEsquerda(int idComponente){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGListBox>(idComponente)->AlinhaLabelEsquerda();
}

void PIG_ListBox_AlinhaLabelCentro(int idComponente){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGListBox>(idComponente)->AlinhaLabelCentro();
}

void PIG_ListBox_AlinhaIconeDireita(int idComponente){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGListBox>(idComponente)->AlinhaIconeDireita();
}

void PIG_ListBox_AlinhaIconeEsquerda(int idComponente){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGListBox>(idComponente)->AlinhaIconeEsquerda();
}

void PIG_ListBox_SetFonteItem(int idComponente,int fonte,int item=-1){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGListBox>(idComponente)->SetFonteItem(fonte,item);
}

int PIG_ListBox_GetAcionadoItem(int idComponente,int item){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGListBox>(idComponente)->GetAcionadoItem(item);
}

void PIG_ListBox_SetAudioItem(int idComponente,int audio, int item=-1){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGListBox>(idComponente)->SetAudioItem(item,audio);
}

int PIG_ListBox_GetHabilitadoItem(int idComponente,int item){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGListBox>(idComponente)->GetHabilitadoItem(item);
}

int PIG_ListBox_SetHabilitadoItem(int idComponente,int item,int valor){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGListBox>(idComponente)->SetHabilitadoItem(item,valor);
}

int PIG_ListBox_GetItemDestaque(int idComponente){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGListBox>(idComponente)->GetItemDestaque();
}

int PIG_ListBox_SetAcionadoItem(int idComponente,int indice,int marcado){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGListBox>(idComponente)->SetAcionadoItem(indice,marcado);
}

void PIG_ListBox_SetCorLabelItem(int idComponente,PIG_Cor cor, int item=-1){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGListBox>(idComponente)->SetCorLabelItem(cor,item);
}

/**********DROPDOWN**************/

int PIG_CriaDropDown(int idForm,int x, int y, int larguraTotal,int alturaLinha,int alturaItem,int larguraItem,char* nomeArq,int retiraFundo=1){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaDropDown(x,y,larguraTotal,alturaLinha,alturaItem,larguraItem,nomeArq,retiraFundo);
}

int PIG_CriaDropDown(int idForm,int x, int y, int larguraTotal,int alturaLinha,int alturaItem,int larguraItem){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaDropDown(x,y,larguraTotal,alturaLinha,alturaItem,larguraItem);
}

void PIG_DropDown_CriaItem(int idComponente,char* texto,char* imagemIcone = "",char *imagemFundo="", char* hintMsg="",bool itemHabilitado = true, int retiraFundoImg = 1){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGDropDown>(idComponente)->CriaItem(texto,imagemIcone,imagemFundo,itemHabilitado,hintMsg,retiraFundoImg);
}

void PIG_DropDown_DefineDimensaoIconeItem(int idComponente,int alturaImagemIcone, int larguraImagemIcone){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGDropDown>(idComponente)->DefineDimensaoIconeItem(alturaImagemIcone,larguraImagemIcone);
}

void PIG_DropDown_AlinhaLabelDireita(int idComponente){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGDropDown>(idComponente)->AlinhaLabelDireita();
}

void PIG_DropDown_AlinhaLabelEsquerda(int idComponente){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGDropDown>(idComponente)->AlinhaLabelEsquerda();
}

void PIG_DropDown_AlinhaLabelCentro(int idComponente){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGDropDown>(idComponente)->AlinhaLabelCentro();
}

void PIG_DropDown_AlinhaIconeDireita(int idComponente){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGDropDown>(idComponente)->AlinhaIconeDireita();
}

void PIG_DropDown_AlinhaIconeEsquerda(int idComponente){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGDropDown>(idComponente)->AlinhaIconeEsquerda();
}

void PIG_DropDown_SetFonteItem(int idComponente,int fonte, int item=-1){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGDropDown>(idComponente)->SetFonteItem(fonte,item);
}

int PIG_DropDown_GetAcionadoItem(int idComponente,int item){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGDropDown>(idComponente)->GetAcionadoItem(item);
}

void PIG_DropDown_SetAudioItem(int idComponente,int audio, int item=-1){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGDropDown>(idComponente)->SetAudioItem(item,audio);
}

int PIG_DropDown_GetHabilitadoItem(int idComponente,int item){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGDropDown>(idComponente)->GetHabilitadoItem(item);
}

int PIG_DropDown_SetHabilitadoItem(int idComponente,int item,int valor){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGDropDown>(idComponente)->SetHabilitadoItem(item,valor);
}

int PIG_DropDown_GetItemDestaque(int idComponente){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGDropDown>(idComponente)->GetItemDestaque();
}

int PIG_DropDown_SetAcionadoItem(int idComponente,int indice,int marcado){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGDropDown>(idComponente)->SetAcionadoItem(indice,marcado);
}

void PIG_DropDown_SetCorLabelItem(int idComponente,PIG_Cor cor, int item=-1){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGDropDown>(idComponente)->SetCorLabelItem(cor,item);
}


/**********RADIOBOX**************/

int PIG_CriaRadioBox(int idForm,int x, int y,int larguraTotal,int alturaLinha, char* imagemItem, int alturaItem, int larguraItem,char* imagemFundo, int retiraFundo=1){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaRadioBox(x,y,larguraTotal,alturaLinha,imagemItem,alturaItem,larguraItem,imagemFundo,retiraFundo);
}

int PIG_CriaRadioBox(int idForm,int x, int y,int larguraTotal,int alturaLinha, char* imagemItem, int alturaItem, int larguraItem){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaRadioBox(x,y,larguraTotal,alturaLinha,imagemItem,alturaItem,larguraItem);
}

void PIG_RadioBox_CriaItem(int idComponente,char* itemLabel, char *imagemFundo="", char* hintMsg="", bool itemHabilitado = true, int retiraFundo=1){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGRadioBox>(idComponente)->CriaItem(itemLabel,imagemFundo,itemHabilitado,hintMsg,retiraFundo);
}

int PIG_RadioBox_GetItemDestaque(int idComponente){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGRadioBox>(idComponente)->GetItemDestaque();
}

int PIG_RadioBox_SetItemMarcado(int idComponente,int item, bool marcado){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGRadioBox>(idComponente)->SetAcionadoItem(item,marcado);
}

int PIG_RadioBox_GetEstadoMarcadoItem(int idComponente,int item){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGRadioBox>(idComponente)->GetAcionadoItem(item);
}

void PIG_RadioBox_SetAudioItem(int idComponente,int item,int audio){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGRadioBox>(idComponente)->SetAudioItem(item,audio);
}

int PIG_RadioBox_GetEstadoHabilitadoItem(int idComponente,int item){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGRadioBox>(idComponente)->GetHabilitadoItem(item);
}

int PIG_RadioBox_SetEstadoHabilitadoItem(int idComponente,int item,bool habilitado){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGRadioBox>(idComponente)->SetHabilitadoItem(item,habilitado);
}

void PIG_RadioBox_SetEstadoHabilitadoItens(int idComponente,bool habilitado){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGRadioBox>(idComponente)->SetHabilitado(habilitado);
}

void PIG_RadioBox_SetFonteItem(int idComponente,int fonte, int item=-1){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGRadioBox>(idComponente)->SetFonteItem(fonte,item);
}

void PIG_RadioBox_SetCorLabelItem(int idComponente,PIG_Cor cor, int item=-1){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGRadioBox>(idComponente)->SetCorLabelItem(cor,item);
}

/**********CHECKBOX**************/

int PIG_CriaCheckBox(int idForm,int x, int y,int larguraTotal,int alturaLinha, char* imagemItem, int alturaItem, int larguraItem,char* imagemFundo, int retiraFundo=1){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaCheckBox(x,y,larguraTotal,alturaLinha,imagemItem,alturaItem,larguraItem,imagemFundo,retiraFundo);
}

int PIG_CriaCheckBox(int idForm,int x, int y,int larguraTotal,int alturaLinha, char* imagemItem, int alturaItem, int larguraItem,int idJanela=0){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaCheckBox(x,y,larguraTotal,alturaLinha,imagemItem,alturaItem,larguraItem);
}

void PIG_CheckBox_CriaItem(int idComponente,char* itemLabel,char *imagemFundo="",char* hintMsg="",bool itemMarcado = false, bool itemHabilitado = true, int retiraFundo=1){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGCheckBox>(idComponente)->CriaItem(itemLabel,imagemFundo,itemMarcado,itemHabilitado,hintMsg,retiraFundo);
}

void PIG_CheckBox_SetMarcadoTodos(int idComponente,bool marcado){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGCheckBox>(idComponente)->SetAcionadoTodos(marcado);
}

int PIG_CheckBox_SetMarcadoItem(int idComponente,int indice,bool marcado){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGCheckBox>(idComponente)->SetAcionadoItem(indice,marcado);
}

std::vector <int> PIG_CheckBox_GetItensMarcados(int idComponente){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGCheckBox>(idComponente)->GetItensMarcados();
}

int PIG_CheckBox_GetMarcadoItem(int idComponente,int item){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGCheckBox>(idComponente)->GetAcionadoItem(item);
}

void PIG_CheckBox_SetAudioItem(int idComponente,int item,int audio){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGCheckBox>(idComponente)->SetAudioItem(item,audio);
}

int PIG_CheckBox_GetHabilitadoItem(int idComponente,int item){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGCheckBox>(idComponente)->GetHabilitadoItem(item);
}

int PIG_CheckBox_SetHabilitadoItem(int idComponente,int item,bool habilitado){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGCheckBox>(idComponente)->SetHabilitadoItem(item,habilitado);
}

void PIG_CheckBox_SetHabilitado(int idComponente,bool habilitado){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGCheckBox>(idComponente)->SetHabilitado(habilitado);
}

void PIG_CheckBox_SetFonteItem(int idComponente,int fonte, int item=-1){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGCheckBox>(idComponente)->SetFonteItem(fonte,item);
}

void PIG_CheckBox_SetCorLabelItem(int idComponente,PIG_Cor cor, int item=-1){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGCheckBox>(idComponente)->SetCorLabelItem(cor,item);
}


/**********GAUGE**************/

int PIG_CriaGaugeBar(int idForm,int x, int y,int altura,int largura,char* imgMoldura,char *imgMarcador="",int retiraFundoMoldura=1,int retiraFundoMarcador=1){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaGaugeBar(x,y,altura,largura,imgMoldura,imgMarcador,retiraFundoMoldura,retiraFundoMarcador);
}

int PIG_CriaGaugeBar(int idForm,int x, int y,int altura,int largura){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaGaugeBar(x,y,altura,largura);
}

void PIG_GaugeBar_SetDelta(int idComponente,float valor){
    CPIGGerenciadorForms::GetComponente<PIGGaugeBar>(idComponente)->SetDelta(valor);
}

void PIG_GaugeBar_AvancaDelta(int idComponente){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGaugeBar>(idComponente)->AvancaDelta();
}

float PIG_GaugeBar_GetPorcentagemConcluida(int idComponente){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGaugeBar>(idComponente)->GetPorcentagemConcluida();
}

void PIG_GaugeBar_MinimizaValor(int idComponente){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGaugeBar>(idComponente)->MinimizaValorAtual();
}

void PIG_GaugeBar_MaximizaValor(int idComponente){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGaugeBar>(idComponente)->MaximizaValorAtual();
}

void PIG_GaugeBar_SetValorMin(int idComponente,double minimo){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGaugeBar>(idComponente)->SetValorMin(minimo);
}

void PIG_GaugeBar_SetValorMax(int idComponente,double maximo){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGaugeBar>(idComponente)->SetValorMax(maximo);
}

void PIG_GaugeBar_AvancaBarra(int idComponente,double valor){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGaugeBar>(idComponente)->AvancaMarcador(valor);
}

void PIG_GaugeBar_SetMargens(int idComponente,int margemEsq,int margemDir,int margemCima, int margemBaixo){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGaugeBar>(idComponente)->SetMargens(margemEsq,margemDir,margemCima,margemBaixo);
}

void PIG_GaugeBar_SetPorcentagemConcluida(int idComponente,double porcentagem){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGaugeBar>(idComponente)->SetPorcentagemConcluida(porcentagem);
}

void PIG_GaugeBar_SetOrientacao(int idComponente,PIG_GaugeCrescimento orientacao){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGaugeBar>(idComponente)->SetOrientacao(orientacao);
}

float PIG_GaugeBar_GetValorMarcadorAtual(int idComponente){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGaugeBar>(idComponente)->GetValorAtual();
}

void PIG_GaugeBar_SetValorMarcadorAtual(int idComponente,double valor){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGaugeBar>(idComponente)->SetValorAtual(valor);
}

void PIG_GaugeBar_SetCorInicial(int idComponente,PIG_Cor cor){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGaugeBar>(idComponente)->SetCorInicial(cor);
}

void PIG_GaugeBar_SetCorFinal(int idComponente,PIG_Cor cor){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGaugeBar>(idComponente)->SetCorFinal(cor);
}

/**********GAUGECIRCULAR**************/

int PIG_CriaGaugeCircular(int idForm,int x, int y,int altura,int largura,int raioInterior){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaGaugeCircular(x,y,altura,largura,raioInterior);
}

void PIG_GaugeCircular_SetDelta(int idComponente,float valor){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGaugeCircular>(idComponente)->SetDelta(valor);
}

void PIG_GaugeCircular_AvancaDelta(int idComponente){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGaugeCircular>(idComponente)->AvancaDelta();
}

float PIG_GaugeCircular_GetPorcentagemConcluida(int idComponente){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGaugeCircular>(idComponente)->GetPorcentagemConcluida();
}

void PIG_GaugeCircular_SetRaioInterno(int idComponente,int valorRaio){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGaugeCircular>(idComponente)->SetRaioInterno(valorRaio);
}

void PIG_GaugeCircular_SetAnguloBase(int idComponente,double novoAng){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGaugeCircular>(idComponente)->SetAnguloBase(novoAng);
}

void PIG_GaugeCircular_SetDeltaAngulo(int idComponente,double novoDelta){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGaugeCircular>(idComponente)->SetDeltaAngulo(novoDelta);
}

void PIG_GaugeCircular_IncrementaValor(int idComponente,double delta){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGaugeCircular>(idComponente)->AvancaMarcador(delta);
}

void PIG_GaugeCircular_MinimizaValor(int idComponente){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGaugeCircular>(idComponente)->MinimizaValorAtual();
}

void PIG_GaugeCircular_MaximizaValor(int idComponente){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGaugeCircular>(idComponente)->MaximizaValorAtual();
}

void PIG_GaugeCircular_SetValorMax(int idComponente,double novoValor){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGaugeCircular>(idComponente)->SetValorMax(novoValor);
}

void PIG_GaugeCircular_SetValorMin(int idComponente,double novoValor){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGaugeCircular>(idComponente)->SetValorMin(novoValor);
}

void PIG_GaugeCircular_SetCorInicial(int idComponente,PIG_Cor cor){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGaugeCircular>(idComponente)->SetCorInicial(cor);
}

void PIG_GaugeCircular_SetCorFinal(int idComponente,PIG_Cor cor){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGaugeCircular>(idComponente)->SetCorFinal(cor);
}

void PIG_GaugeCircular_SetCorInterna(int idComponente,PIG_Cor cor){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGaugeCircular>(idComponente)->SetCorInterna(cor);
}

int PIG_GaugeCircular_GetValor(int idComponente){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGaugeCircular>(idComponente)->GetValorAtual();
}

void PIG_GaugeCircular_GetValorString(int idComponente,char* valor){
    strcpy(valor,(char*)(CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGaugeCircular>(idComponente)->GetStringValorMarcador()).c_str());
}

int PIG_GaugeCircular_GetValorMax(int idComponente){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGaugeCircular>(idComponente)->GetValorMax();
}

int PIG_GaugeCircular_GetValorMin(int idComponente){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGaugeCircular>(idComponente)->GetValorMin();
}

void PIG_GaugeCircular_AtualizaMarcador(int idComponente,int novoValor){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGaugeCircular>(idComponente)->SetValorAtual(novoValor);
}

/**********SLIDEBAR**************/

int PIG_CriaSlideBar(int idForm, int px, int py, int altura, int largura, string imgTrilha, int alturaMarcador, int larguraMarcador, string imgMarcador, int retiraFundoTrilha=1, int retiraFundoMarcador=1,int idJanela=0){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaSlideBar(px,py,altura,largura,imgTrilha,alturaMarcador,larguraMarcador,imgMarcador,retiraFundoTrilha,retiraFundoMarcador,idJanela);
}

int PIG_CriaSlideBar(int idForm, int px, int py, int altura, int largura, int alturaMarcador, int larguraMarcador, int idJanela=0){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaSlideBar(px,py,altura,largura,alturaMarcador,larguraMarcador,idJanela);
}

void PIG_SlideBar_SetDelta(int idComponente,float valor){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGSlideBar>(idComponente)->SetDelta(valor);
}

void PIG_SlideBar_AvancaDelta(int idComponente){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGSlideBar>(idComponente)->AvancaDelta();
}

float PIG_SlideBar_GetPorcentagemConcluida(int idComponente){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGSlideBar>(idComponente)->GetPorcentagemConcluida();
}

void PIG_SlideBar_MinimizaValor(int idComponente){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGSlideBar>(idComponente)->MinimizaValorAtual();
}

void PIG_SlideBar_MaximizaValor(int idComponente){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGSlideBar>(idComponente)->MaximizaValorAtual();
}

void PIG_SlideBar_SetValorMin(int idComponente,double minimo){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGSlideBar>(idComponente)->SetValorMin(minimo);
}

void PIG_SlideBar_SetValorMax(int idComponente,double maximo){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGSlideBar>(idComponente)->SetValorMax(maximo);
}

void PIG_SlideBar_AvancaBarra(int idComponente,double valor){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGSlideBar>(idComponente)->AvancaMarcador(valor);
}

void PIG_SlideBar_SetPorcentagemConcluida(int idComponente,double porcentagem){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGSlideBar>(idComponente)->SetPorcentagemConcluida(porcentagem);
}

void PIG_SlideBar_SetOrientacao(int idComponente,PIG_GaugeCrescimento orientacao){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGSlideBar>(idComponente)->SetOrientacao(orientacao);
}

float PIG_SlideBar_GetValorMarcadorAtual(int idComponente){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGSlideBar>(idComponente)->GetValorAtual();
}

void PIG_SlideBar_SetValorMarcadorAtual(int idComponente,double valor){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGSlideBar>(idComponente)->SetValorAtual(valor);
}

void PIG_SlideBar_SetDeltas(int idComponente,int deltaPadrao, int deltaRodinha, int deltaTeclado){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGSlideBar>(idComponente)->SetDeltas(deltaPadrao,deltaRodinha,deltaTeclado);
}
