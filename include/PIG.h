#include "PIGTipos.h"
#include "PIGFuncoesBasicas.h"
#include "CPIGErros.h"

#include "CPIGRepositorio.h"
#include "CPIGGerenciadorTimers.h"
#include "CPIGAssetLoader.h"
#include "CPIGOffscreenRenderer.h"
#include "CPIGGerenciadorJanelas.h"
#include "CPIGGerenciadorFontes.h"
#include "CPIGGerenciadorLabels.h"
#ifdef PIGCOMAUDIO
#include "CPIGGerenciadorAudios.h"
#endif
#include "CPIGGerenciadorSprites.h"
#include "CPIGGerenciadorGDP.h"
#ifdef PIGCOMREDE
#include "CPIGGerenciadorSockets.h"
#endif
#ifdef PIGCOMVIDEO
#include "CPIGGerenciadorVideos.h"
#endif
#ifdef PIGCOMCONTROLE
#include "CPIGGerenciadorControles.h"
#endif
#ifdef PIGCOMFORM
#include "CPIGGerenciadorForms.h"
#endif
#ifdef PIGCOMTELA
#include "CPIGGerenciadorTelas.h"
#endif

#include "CPIGJogo.h"


/********************************
/ Variáveis Globais
/********************************/
PIGJogo jogo=NULL;

/********************************
A função CriaJogo() é responsável pela criação da janela do jogo e pelos componentes audio-visuais.
Ela deve ser chamada antes de qualquer outra função da biblioteca PIG.h. Não é possível criar dois
jogos no mesmo progama. Logo, somente a primeira chamada terá efeito. A janela padrão da aplicação terá o tamanho definido pelas constantes PIG_ALT_TELA e PIG_LARG_TELA
definidas no arquivo PIGTipos.h, exceto se forem passados outros valores.
Parâmetros:
nomeJanela (entrada, passagem por referência*): indica o nome que a janela do jogo mostrará no seu título.
É utilizado o operador * apenas por se tratar de um parâmetro string. O valor do parâmetro não é alterado dentro da função.
cursorProprio (entrada, passagem por valor): indica se o jogo utilizará cursores (ponteiros) próprios para o mouse ou utilizará o cursor padrão.
altura (entrada, passagem por valor não-obrigatório): indica a altura em pixels da janela principal do jogo.
largura (entrada, passagem por valor não-obrigatório): indica a largura em pixels da janela principal do jogo.
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
void CriaJogo(const char *nomeJanela, int cursorProprio=0, int altura=PIG_ALT_TELA, int largura=PIG_LARG_TELA){
    if (jogo==NULL){
        jogo = new CPIGJogo(nomeJanela,cursorProprio,altura,largura);
    }
}

/********************************
A função SetValorIntJogo() é responsável incorporar ao jogo um atributo inteiro.
Parâmetros:
indice (entrada, passagem por valor): relaciona um número inteiro ao atributo.
valor (entrada, passagem por valor): valor do atributo inteiro a ser associado ao jogo.
********************************/
void SetValorIntJogo(int indice, int valor){
    jogo->SetValorInt(indice,valor);
}

/********************************
A função SetValorFloatJogo() é responsável incorporar ao jogo um atributo float.
Parâmetros:
indice (entrada, passagem por valor): relaciona um número inteiro ao atributo.
valor (entrada, passagem por valor): valor do atributo float a ser associado ao jogo.
********************************/
void SetValorFloatJogo(int indice, float valor){
    jogo->SetValorFloat(indice,valor);
}

/********************************
A função SetValorIntJogo() é responsável incorporar ao jogo um atributo inteiro.
Parâmetros:
indice (entrada, passagem por valor): relaciona um número inteiro ao atributo.
valor (entrada, passagem por referência): valor do atributo string a ser associado ao jogo.
********************************/
void SetValorStringJogo(int indice, char *valor){
    jogo->SetValorString(indice,valor);
}

/********************************
A função SetValorIntJogo() é responsável incorporar ao jogo um atributo inteiro.
Parâmetros:
indice (entrada, passagem por referência): relaciona uma string ao atributo.
valor (entrada, passagem por valor): valor do atributo inteiro a ser associado ao jogo.
********************************/
void SetValorIntJogo(char *indice, int valor){
    jogo->SetValorInt(indice,valor);
}

/********************************
A função SetValorFloatJogo() é responsável incorporar ao jogo um atributo float.
Parâmetros:
indice (entrada, passagem por referência): relaciona uma string ao atributo.
valor (entrada, passagem por valor): valor do atributo float a ser associado ao jogo.
********************************/
void SetValorFloatJogo(char *indice, float valor){
    jogo->SetValorFloat(indice,valor);
}

/********************************
A função SetValorIntJogo() é responsável incorporar ao jogo um atributo inteiro.
Parâmetros:
indice (entrada, passagem por referência): relaciona uma string ao atributo.
valor (entrada, passagem por referência): valor do atributo string a ser associado ao jogo.
********************************/
void SetValorStringJogo(char *indice, char *valor){
    jogo->SetValorString(indice,valor);
}

/********************************
A função GetValorIntJogo() é responsável recuperar o valor de um atributo inteiro relacionado ao jogo.
Parâmetros:
indice (entrada, passagem por valor): indica o número do atributo que se deseja recuperar.
valor (saída, passagem por referência): indica o valor do atributo, se a função retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo não existir, a função retorna o valor 0 (zero).
********************************/
int GetValorIntJogo(int indice, int *valor){
    return jogo->GetValorInt(indice,*valor);
}

/********************************
A função GetValorFloatJogo() é responsável recuperar o valor de um atributo float relacionado ao jogo.
Parâmetros:
indice (entrada, passagem por valor): indica o número do atributo que se deseja recuperar.
valor (saída, passagem por referência): indica o valor do atributo, se a função retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo não existir, a função retorna o valor 0 (zero).
********************************/
int GetValorFloatJogo(int indice, float *valor){
    return jogo->GetValorFloat(indice,*valor);
}

/********************************
A função GetValorStringJogo() é responsável recuperar o valor de um atributo string relacionado ao jogo.
Parâmetros:
indice (entrada, passagem por valor): indica o número do atributo que se deseja recuperar.
valor (saída, passagem por referência): indica o valor do atributo, se a função retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo não existir, a função retorna o valor 0 (zero).
********************************/
int GetValorStringJogo(int indice, char *valor){
    string str;
    bool resp = jogo->GetValorString(indice,str);
    strcpy(valor,str.c_str());
    return resp;
}

/********************************
A função GetValorIntJogo() é responsável recuperar o valor de um atributo inteiro relacionado ao jogo.
Parâmetros:
indice (entrada, passagem por referência): indica o nome do atributo que se deseja recuperar.
valor (saída, passagem por referência): indica o valor do atributo, se a função retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo não existir, a função retorna o valor 0 (zero).
********************************/
int GetValorIntJogo(char *indice, int *valor){
    return jogo->GetValorInt(indice,*valor);
}

/********************************
A função GetValorFloatJogo() é responsável recuperar o valor de um atributo float relacionado ao jogo.
Parâmetros:
indice (entrada, passagem por valor): indica o nome do atributo que se deseja recuperar.
valor (saída, passagem por referência): indica o valor do atributo, se a função retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo não existir, a função retorna o valor 0 (zero).
********************************/
int GetValorFloatJogo(char *indice, float *valor){
    return jogo->GetValorFloat(indice,*valor);
}

/********************************
A função GetValorStringJogo() é responsável recuperar o valor de um atributo string relacionado ao jogo.
Parâmetros:
indice (entrada, passagem por valor): indica o nome do atributo que se deseja recuperar.
valor (saída, passagem por referência): indica o valor do atributo, se a função retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo não existir, a função retorna o valor 0 (zero).
********************************/
int GetValorStringJogo(char *indice, char *valor){
    string str;
    bool resp = jogo->GetValorString(indice,str);
    strcpy(valor,str.c_str());
    return resp;
}

/********************************
A função GetEstadoJogo() indica o estado do jogo. Este estado é apenas um valor inteiro
que pode ser usado para indicar uma fase do jogo, ou a vez de algum jogador por exemplo.
Retorno:
inteiro indicando o valor do estado do jogo.
********************************/
//int GetEstadoJogo(){
//    return jogo->GetEstado();
//}

/********************************
A função SetEstadoJogo() atribui um novo valor ao estado do jogo. Este estado é apenas um valor inteiro
que pode ser usado para indicar uma fase do jogo, ou a vez de algum jogador por exemplo.
Parâmetro:
estado (entrada, passagem por valor): indica o novo estado do jogo;
********************************/
//void SetEstadoJogo(int estado){
//    jogo->SetEstado(estado);
//}

/********************************
A função DefineFundoJanela() permite escolher um arquivo de imagem como fundo (background) de uma janela que será automaticamente desenhado a cada nova etapa de desenho na tela.
Parâmetros:
nomeArquivoImagem (entrada, passagem por referência*): indica o caminho relativo ou absoluto do arquivo de imagem que será utilizado como fundo do jogo.
É utilizado o operador * apenas por se tratar de um parâmetro string. O valor do parâmetro não é alterado dentro da função.
idJanela (entrada, passagem por valor não-obrigatorio): indica de qual janela é a imagem.
********************************/
void DefineFundo(char *nomeArquivoImagem, int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->DefineFundo(nomeArquivoImagem);
}

/********************************
A função GetTeclado() faz um mapeamento entre o teclado físico a uma variável do tipo PIG_Teclado que funciona como um vetor de variáveis lógicas,
sendo cada posição do vetor relativo a uma tecla física.
Uma lista das possíveis teclas e seus código pode ser vista no arquivo Tipos_PIG.h.
Retorno:
O valor de retorno da função é um vetor de números inteiros que indicam se uma determinada tecla (índice do vetor) foi
pressionada (valor diferente de 0,zero) ou não (valor igual a zero).
********************************/
PIGTeclado GetTeclado(){
    return jogo->PegaTeclado();
}

/********************************
A função GetEvento() indica se houve algum tipo de evento desde a última vez que a função foi chamada.
Um evento pode ser uma tecla pressionada, um clique do mouse ou outra coisa relacionada à tela do jogo.
Maiores informaçőe podem ser vistas no arquivo PIGTipos.h
Retorno:
O valor de retorno é um struct contendo o tipo de evento ocorrido e vários outros structs com informaçőes específicas.
********************************/
PIGEvento GetEvento(){
    return jogo->PegaEvento();
}

/********************************
A função IniciaDesenho() é responsável por preparar a janela do jogo para que os objetos gráficos
possam ser mostrados, além de desenhar a imagem de fundo do jogo, caso tenha sido definida.
Deve ser chamada repetidamente a cada novo quadro (frame) a ser desenhado.
Parâmetros:
idJanela (entrada, passagem por valor não-obrigatório): indica qual janela deve preparar a renderização. O valor (-1) indica que todas as janelas devem ser preparadas.
********************************/
void IniciaDesenho(int idJanela=-1){
    jogo->IniciaDesenho(idJanela);
}

/********************************
A função EncerraDesenho() é responsável por encerrar o desenho que foi criado, mostrando na janela do jogo.
Deve ser chamado sempre ao final do loop principal do jogo.
Parâmetros:
idJanela (entrada, passagem por valor não-obrigatório): indica qual janela deve preparar a renderização. O valor (-1) indica que todas as janelas devem ser exibidas.
********************************/
void EncerraDesenho(int idJanela=-1){
    CPIGMouse::Desenha();
    jogo->EncerraDesenho(idJanela);
}

/********************************
A função SalvaTela() é responsável por criar um arquivo Bitmap, contendo uma cópia de uma janela do jogo naquele momento.
Parâmetros:
nomeArquivoBMP (entrada, passagem por referência*): indica o nome do arquivo Bitmap que será salvo. O valor do parâmetro deve conter a extensão ".bmp".
É utilizado o operador * apenas por se tratar de um parâmetro string. O valor do parâmetro não é alterado dentro da função.
idJanela (entrada, passagem por valor não-obrigatório): indica qual janela deve ter a imagem salva.
********************************/
void SalvaTela(char *nomeArquivoBMP, int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->SaveScreenshot(nomeArquivoBMP,true);
}

/********************************
A função JogoRodando() é reponsável por retornar se o jogo ainda está ativo ou não.
O jogo será encerrado se a janela do jogo for fechada, por exemplo.
Retorno:
inteiro que indica se o jogo ainda está sendo executado (valor diferente de zero) ou não (valor igual a 0, zero).
********************************/
int JogoRodando(){
    return jogo->GetRodando();
}

/********************************
A função Espera() "congela" a tela do jogo por alguns milissegundos, impedindo que qualquer outro comando seja executado enquanto isso.
Parâmetros:
tempo (entrada, passagem por valor): indica a quantidade de milissegundos durante a qual o jogo será pausado.
********************************/
void Espera(int tempo){
    SDL_Delay(tempo);
}

/********************************
A função FinalizaJogo() é responsável por encerrar com a PIG. Após tudo o jogo ser executado
a função deve ser chamada e ela irá realizar a liberação de memória dos elementos criados pela PIG.
********************************/
void FinalizaJogo(){
    delete jogo;
}

/********************************
A função GetFPS() é responsável por calcular o valor do Frames Per Seconds (FPS), que representa a quantidade de
frames (quadros) desenhados por segundo pela PIG.
Retorno:
float que indica a média de quadros desenhados por segundo.
********************************/
float GetFPS(){
    return jogo->GetFPS();
}

/********************************
A função CarregaCursor() é responsável por armazenar um novo cursor para o mouse, dado pelo arquivo de imagem indicado.
O arquivo deve ser uma imagem com 32 pixels de altura orbigatoriamente.
Parâmetro:
nomeArquivoCursor (entrada, passagem por referência*): indica o nome do arquivo de imagem que será utilziado como cursor do mouse.
É utilizado o operador * apenas por se tratar de um parâmetro string. O valor do parâmetro não é alterado dentro da função.
********************************/
void CarregaCursor(char *nomeArquivoCursor, int idJanela=0){
    CPIGMouse::CarregaCursor(nomeArquivoCursor,idJanela);
}

/********************************
A função CriaFrameCursor() é responsável por delimitar a área do arquivo de imagem para um cursor específico.
Idealmente, a altura e largura informadas devem ter tamanho igual a 32 pixels (para não haver perda de qualidade na exibição do cursor).
Parâmetro:
idFrame (entrada, passagem por valor): número inteiro associado ao cursor (área do arquivo de imagem) em questão.
xBitmap (entrada, passagem por valor): indica a posição de eixo X onde começa o frame.
yBitmap (entrada, passagem por valor): indica a posição de eixo Y onde começa o frame. Neste caso, o eixo Y aumenta para baixo.
altura (entrada, passagem por valor): altura em pixels do frame.
largura (entrada, passagem por valor): largura em pixels do frame.
********************************/
void CriaFrameCursor(int idFrame, int xBitmap, int yBitmap, int altura, int largura){
    CPIGMouse::CriaFrameCursor(idFrame,xBitmap,yBitmap,altura,largura);
}

/********************************
A função CarregaFramesPorLinhaCursor() é responsável por subdividir o arquivo de imagem em linhas (de mesmo tamanho) e colunas (de mesmo tamanho).
Cada subdivisão representará um frame que será automaticamente criado para o cursor do mouse, com numeração incremental a partir do parâmetro "frameInicial".
Ao final das "qtdColunas" da primeira linha, a definição dos frames continua na linha inferior.
A função pode ser utilizada em spritesheets regulares.
Parâmetros:
frameInicial (entrada, passagem por valor): numeração do primeiro frame a ser criado pela função. Os demais frames terão numeração consecutiva.
qtdLinhas (entrada, passagem por valor): quantidade de linhas na qual o arquivo de imagem será dividido.
qtdColunas (entrada, passagem por valor): quantidade de colunas na qual o arquivo de imagem será dividido.
********************************/
void CarregaFramesPorLinhaCursor(int frameInicial, int qtdLinhas, int qtdColunas){
    CPIGMouse::CarregaFramesPorLinha(frameInicial,qtdLinhas,qtdColunas);
}

/********************************
A função CarregaFramesPorColunaCursor() é responsável por subdividir o arquivo de imagem em linhas (de mesmo tamanho) e colunas (de mesmo tamanho).
Cada subdivisão representará um frame que será automaticamente criado para o cursor do mouse, com numeração incremental a partir do parâmetro "frameInicial".
Ao final das "qtdLinhas" da primeira coluna, a definição dos frames continua na coluna seguinte.
A função pode ser utilizada em spritesheets regulares.
Parâmetros:
frameInicial (entrada, passagem por valor): numeração do primeiro frame a ser criado pela função. Os demais frames terão numeração consecutiva.
qtdLinhas (entrada, passagem por valor): quantidade de linhas na qual o arquivo de imagem será dividido.
qtdColunas (entrada, passagem por valor): quantidade de colunas na qual o arquivo de imagem será dividido.
********************************/
void CarregaFramesPorColunaCursor(int frameInicial, int qtdLinhas, int qtdColunas){
    CPIGMouse::CarregaFramesPorColuna(frameInicial,qtdLinhas,qtdColunas);
}

/********************************
A função MudaCursor() é responsável por alterar o cursor atual do mouse por outro já definido (função DefineFrameCursor).
Parâmetro:
idFrame (entrada, passagem por valor): informa o identificador de um cursor (frame) já criado.
Retorno:
Se o identifador informado não corresponder a um frame já criado, o valor de retorno é igual a 0. Caso contrário, é igual a 1.
********************************/
int MudaCursor(int idFrame){
    return CPIGMouse::MudaCursor(idFrame);
}


/********************************
A função GetEstadoBotaoMouse() é responsável por recuperar o eatado atual de um dos botoes (PIG_MOUSE_DIREITO, PIG_MOUSE_CENTRAL ou PIG_MOUSE_RODINHA) do mouse.
O valor retornado pode ser PIG_MOUSE_PRESSIONADO ou PIG_MOUSE_LIBERADO.
Retorno:
inteiro que indica a o estado atual do botão do mouse solicitado.
********************************/
int GetEstadoBotaoMouse(int botao){
    return CPIGMouse::GetEstadoBotao(botao);
}

/********************************
A função ExecutaBackground() é responsável por executar uma função em bckground, ou seja, fora do fluxo principal de execução do programa.
Essa execução é feita por outra Thread, com suporte do Sistema Operacional
Parâmetros:
dados (entrada, passagem por referência): ponteiro genérico para qualquer tipo de dado a ser utilizado na função.
********************************/
void ExecutaBackground(PIGFuncaoBackground funcao, void *dados){
    SDL_CreateThread(funcao,"",dados);
}


/********************************
Seção de tratamento de janelas
********************************/

/********************************
A função GetQtdJanela() é responsável por calcular quantas janelas estão criadas pelo jogo, incluindo as que estão minimizadas ou escondidas.
Retono:
inteiro que representa a quantidade de janelas ainda abertas pelo jogo, incluindo as que estão minimizadas ou escondidas.
********************************/
int GetQtdJanelas(){
    return CPIGGerenciadorJanelas::GetQtdJanelas();
}

/********************************
A função CriaJanela() é responsável por criar e exibir uma nova janela para a aplicação. O identificador numérico da nova janela é retornado como parâmetro.
Se não foi possível criar a janela, o valor de retorno será -1. Existe um limite máximo de janela que podem ser criadas. Esse limite é dado pelo parâmetro MAX_JANELAS configurado na Tipos_PIG.h.
O valor da janela original (padrão) é sempre igual a 0 (zero). Para se desenhar qualquer coisa nas janelas adicionais, é preciso criar objetos, animaçőes, geradores de partículas e fontes
especificando-se a janela na qual estes elementos serão renderizados. Ao utilizar-se janelas adicionais, também é possível estipular individualmente quais janelas serão preparadas e mostradas, utilizando o
número da janela nas chamadas das funçőes IniciaDesenho e EncerraDesenho. Caso não seja especificado o número, todas as janelas são preparadas e mostradas, respectivamente.
Parâmetros:
nomeJanela (entrada, passagem por referência*): indica o nome que a nova janela mostrará no seu título.
É utilizado o operador * apenas por se tratar de um parâmetro string. O valor do parâmetro não é alterado dentro da função.
altura (entrada, passagem por valor não-obrigatório): indica a altura em pixels da janela a ser criada.
largura (entrada, passagem por valor não-obrigatório): indica a largura em pixels da janela a ser criada.
Retorno
inteiro que representa o número de identificação dessa janela. esse número deve ser utilizado sempre que um comando deva ser executado para uma janela específica.
A janela padrão da aplicação possui sempre o número 0 (zero).
********************************/
int CriaJanela(char *nomeJanela, int altura=PIG_ALT_TELA, int largura=PIG_LARG_TELA){
    return CPIGGerenciadorJanelas::CriaJanela(nomeJanela,altura,largura);
}

/********************************
A função FechaJanela() é responsável por fechar uma janela. As renderizaçőes nessa janela que ocorrerem posteriormente não terão qualquer efeito.
A janela fechada vai deixar de gerar eventos, mas não poderpa ser reaberta. O efeito de reabrir um janela pode ser obtido com os comandos EscondeJanela() e ExibeJanela().
Parâmetros:
idJanela (entrada, passagem por valor): indica o número da janela a ser fechada.
********************************/
void FechaJanela(int idJanela){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->Fecha();
}

/********************************
A função EscondeJanela() é responsável por fazer a janela deixar de ser visível, mas não a fecha de forma definitiva.
A janela poderá ser reaberta com a função ExibeJanela().
Parâmetros:
idJanela (entrada, passagem por valor): indica o número da janela a ser oculta.
********************************/
void EscondeJanela(int idJanela){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->Esconde();
}

/********************************
A função ExibeJanela() é responsável por fazer a janela voltar a ser visível, mas não faz automaticamente a janela ter o foco para gerar eventos.
A janela poderá ser reaberta com foca por meio da função GanhaFocoJanela().
Parâmetros:
idJanela (entrada, passagem por valor): indica o número da janela a ser reexibida sem foco.
********************************/
void ExibeJanela(int idJanela){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->Exibe();
}

/********************************
A função GanhaFocoJanela() é responsável por fazer a janela voltar a ser visível e automaticamente voltar a ter o foco para gerar eventos.
Parâmetros:
idJanela (entrada, passagem por valor): indica o número da janela a ser reexibida com foco.
********************************/
void GanhaFocoJanela(int idJanela){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->GanhaFoco();
}

/********************************
A função GetAlturaJanela() é responsável por recuperar a altura da janela em pixels.
Parâmetros:
idJanela (entrada, passagem por valor não-obrigatório): indica o número da janela a ser consultada.
Retorno:
inteiro que representa a altura da janela em pixels.
********************************/
int GetAlturaJanela(int idJanela=0){
    return CPIGGerenciadorJanelas::GetJanela(idJanela)->GetAltura();
}

/********************************
A função GetLarguraJanela() é responsável por recuperar a largura da janela em pixels.
Parâmetros:
idJanela (entrada, passagem por valor não-obrigatório): indica o número da janela a ser consultada.
Retorno:
inteiro que representa a largura da janela em pixels.
********************************/
int GetLarguraJanela(int idJanela=0){
    return CPIGGerenciadorJanelas::GetJanela(idJanela)->GetLargura();
}


/********************************
A função SetTamanhoJanela() é responsável por definir o tamanho para a janela.
Parâmetros:
altura (entrada, passagem por valor): indica a quantidade de linhas da janela (em pixels).
largura (entrada, passagem por valor): indica a quantidade de colunas da janela (em pixels).
idJanela (entrada, passagem por valor não-obrigatório): indica o número da janela a ser alterada.
********************************/
void SetTamanhoJanela(int altura, int largura,int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->SetTamanho(altura,largura);
}

/********************************
A função SetAfastamentoCamera() é responsável por afastar ou aproximar a câmera dos objetos da tela, em um eixo perpendicular.
O valor de afastamento deve variar entre PIG_AFASTAMENTO_MINIMO (0.1) e PIG_AFASTAMENTO_MAXIMO (100).
Quanto maior for o valor, mais "afastada" estará a câmera dos objetos. O valor padrão é 1.0.
Parâmetros:
afastamento (entrada, passagem por valor): indica o afastamento da câmera em relação ao plano representado pela tela.
idJanela (entrada, passagem por valor não-obrigatório): indica o número da janela a ser alterada.
Retorno:
O valor retornado é igual ao afastamento após a execução da função.
********************************/
double SetAfastamentoCamera(double afastamento, int idJanela=0){
    return CPIGGerenciadorJanelas::GetJanela(idJanela)->SetAfastamento(afastamento);
}

/********************************
A função GetAfastamentoCamera() recupera o valor atual de afastamento da câmera.
O valor de afastamento deve variar entre PIG_AFASTAMENTO_MINIMO (0.1) e PIG_AFASTAMENTO_MAXIMO (100).
Quanto maior for o valor, mais "afastada" estará a câmera dos objetos. O valor padrão é 1.0.
Parâmetros:
idJanela (entrada, passagem por valor não-obrigatório): indica o número da janela a ser alterada.
Retorno:
O valor retornado é igual ao afastamento atual da câmera.
********************************/
double GetAfastamentoCamera(int idJanela=0){
    return CPIGGerenciadorJanelas::GetJanela(idJanela)->GetAfastamento();
}

/********************************
A função MoveCamera() é responsável por reposicionar a câmera no cenário. O ponto de referência é o canto inferior esquerdo da tela.
Todos os objetos serão automaticamente recolocados na tela conforme a posição da câmera.
Parâmetros:
posicaoX (entrada, passagem por valor): indica a posição no eixo X onde a câmera ficará.
posicaoY (entrada, passagem por valor): indica a posição no eixo Y onde a câmera ficará.
idJanela (entrada, passagem por valor não-obrigatório): indica o número da janela a ser alterada.
********************************/
void MoveCamera(int posicaoX, int posicaoY, int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->MoveCamera(posicaoX,posicaoY);
}

/********************************
A função DeslocaCamera() é responsável por deslocar a câmera em relação à sua posição atual.
Parâmetros:
deltaX (entrada, passagem por valor): valor a ser somado ou subtraído na componente X da posição da câmera.
deltaY (entrada, passagem por valor): valor a ser somado ou subtraído na componente Y da posição da câmera.
idJanela (entrada, passagem por valor não-obrigatório): indica o número da janela a ser alterada.
********************************/
void DeslocaCamera(int deltaX, int deltaY, int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->DeslocaCamera(deltaX,deltaY);
}

/********************************
A função GetXYCamera() é responsável recuperar o valor da posição (X,Y) da câmera de acordo com o sistema de coordenadas do jogo.
Parâmetros:
posicaoX (saída, passagem por referencia): indica a posicao no eixo X da câmera.
posicaoY (saída, passagem por referencia): indica a posicao no eixo Y da câmera.
idJanela (entrada, passagem por valor não-obrigatório): indica o número da janela.
********************************/
void GetXYCamera(int *posicaoX, int *posicaoY, int idJanela=0){
    SDL_Point p = CPIGGerenciadorJanelas::GetJanela(idJanela)->GetPosicaoCamera();
    *posicaoX = p.x;
    *posicaoY = p.y;
}

/********************************
A função PreparaCameraMovel() é responsável utilizar a câmera movel relativa à janela em questão.
A câmera móvel está sujeita à movimentaçőes e ajuste de zoom (afastamento). Todas as renderizaçőes posteriores estarão sujeitas a essas transformaçőes.
Parâmetros:
idJanela (entrada, passagem por valor não-obrigatório): indica o número da janela.
********************************/
void PreparaCameraMovel(int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->PreparaCameraMovel();
}

/********************************
A função PreparaCameraFixa() é responsável utilizar a câmera fixa relativa à janela em questão.
A câmera fixa não está sujeita à movimentaçőes e ajuste de zoom (afastamento). Todas as renderizaçőes posteriores serão feitas utilizando o sistema de coordenadas da tela.
Parâmetros:
idJanela (entrada, passagem por valor não-obrigatório): indica o número da janela.
********************************/
void PreparaCameraFixa(int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->PreparaCameraFixa();
}

/********************************
A função ConverteCoordenadaDaTelaParaMundo() transforma uma coordenada da tela para uma coordenada do cenário, de acordo com o afastamento e a posição da câmera e do sistema de coordenadas do jogo.
Parâmetros:
telaX (entrada, passagem por valor): indica a componente X da coordenada da tela em questão.
telaY (entrada, passagem por valor): indica a componente Y da coordenada da tela em questão.
mundoX (saída, passagem por referencia): indica a componente X da coordenada do cenário.
mundoY (saída, passagem por referencia): indica a componente Y da coordenada do cenário.
idJanela (entrada, passagem por valor não-obrigatório): indica o número da janela.
********************************/
void ConverteCoordenadaDaTelaParaMundo(int telaX, int telaY, int *mundoX, int *mundoY, int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->ConverteCoordenadaScreenWorld(telaX, telaY, *mundoX, *mundoY);
}

/********************************
A função ConverteCoordenadaDoMundoParaTela() transforma uma coordenada do cenário para uma coordenada da tela, de acordo com o afastamento e a posição da câmera e do sistema de coordenadas do jogo.
Parâmetros:
mundoX (entrada, passagem por valor): indica a componente X da coordenada do cenário em questão.
mundoY (entrada, passagem por valor): indica a componente Y da coordenada do cenário em questão.
telaX (saída, passagem por referencia): indica a componente X da coordenada da tela.
telaY (saída, passagem por referencia): indica a componente Y da coordenada da tela.
idJanela (entrada, passagem por valor não-obrigatório): indica o número da janela.
********************************/
void ConverteCoordenadaDoMundoParaTela(int mundoX, int mundoY, int *telaX, int *telaY, int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->ConverteCoordenadaWorldScreen(mundoX, mundoY, *telaX, *telaY);
}

/********************************
A função GetTituloJanela() é responsável por recuperar o título (caption) atual da janela.
Parâmetros:
tituloJanela (saída, passagem por referência): armazena o título da janela que foi recuperado.
idJanela (entrada, passagem por valor não-obrigatório): indica o número da janela a ser consultada.
********************************/
void GetTituloJanela(char *tituloJanela, int idJanela=0){
    strcpy(tituloJanela,CPIGGerenciadorJanelas::GetJanela(idJanela)->GetTitulo().c_str());
}

/********************************
A função SetTituloJanela() é responsável por definir um novo título (caption) para a janela.
Parâmetros:
novoTitulo (entrada, passagem por referência*): indica o novo título para a janela.
É utilizado o operador * apenas por se tratar de um parâmetro string. O valor do parâmetro não é alterada dentro da função.
idJanela (entrada, passagem por valor não-obrigatório): indica o número da janela a ser alterada.
********************************/
void SetTituloJanela(char *novoTitulo, int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->SetTitulo(novoTitulo);
}

/********************************
A função GetCorFundoJanela() é responsável por recuperar uma cor de fundo para a janela indicada. A cor de fundo será utilizada como background automático quando a janela for preparada para renderizaçőes.
Parâmetros:
idJanela (entrada, passagem por valor não-obrigatório): indica o número da janela a ser alterada.
Retorno
cor contendo os componentes RGBA da cor utilizada para pintar automaticamente o fundo da janela.
********************************/
PIGCor GetCorFundoJanela(int idJanela=0){
    return CPIGGerenciadorJanelas::GetJanela(idJanela)->GetCorFundo();
}

/********************************
A função SetCorFundoJanela() é responsável por definir uma cor de fundo para a janela indicada. A cor de fundo será utilizada como background automático quando a janela for preparada para renderizaçőes.
Parâmetros:
cor (entrada, passagem por valor): indica a cor para o fundo da janela.
idJanela (entrada, passagem por valor não-obrigatório): indica o número da janela a ser alterada.
********************************/
void SetCorFundoJanela(PIGCor cor, int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->SetCorFundo(cor);
}

/********************************
A função GetOpacidadeJanela() é responsável por recuperar o nível de opacidade de uma janela. A opacidade pode variar entre 1.0 (totalmente opaca) e 0 (totalmente transparente).
Parâmetros:
idJanela (entrada, passagem por valor não-obrigatório): indica o número da janela a ser alterada.
Retorno:
número real que indica o nível de opacidade da janela, variando entre 1.0 e 0.
********************************/
float GetOpacidadeJanela(int idJanela=0){
    return CPIGGerenciadorJanelas::GetJanela(idJanela)->GetOpacidade();
}

/********************************
A função SetOpacidadeJanela() é responsável por definir o nível de opacidade de uma janela. A opacidade pode variar entre 1.0 (totalmente opaca) e 0 (totalmente transparente).
Parâmetros:
nivelOpacidade (entrada, passagem por valor): indica o nível de opacidade da janela, variando entre 1.0 e 0.
idJanela (entrada, passagem por valor não-obrigatório): indica o número da janela a ser alterada.
********************************/
void SetOpacidadeJanela(float nivelOpacidade, int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->SetOpacidade(nivelOpacidade);
}

/********************************
A função SetPosicaoJanela() é responsável por definir a posição de um janela na tela correspondente. A tela normalmente utiliza um sistema de coordenadas, cujo ponto (0,0) é o canto superior esquerdo.
Parâmetros:
posicaoX (entrada, passagem por valor): indica o valor no eixo X (horizontal) da esquerda para direita.
posicaoY (entrada, passagem por valor): indica o valor no eixo Y (vertical), normalmente de cima para baixo.
idJanela (entrada, passagem por valor não-obrigatório): indica o número da janela a ser reposicionada.
********************************/
void SetPosicaoJanela(int posicaoX, int posicaoY, int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->SetPosicao(posicaoX,posicaoY);
}

/********************************
A função SetPosicaoJanela() é responsável por recuperar a posição de um janela na tela correspondente. A tela normalmente utiliza um sistema de coordenadas, cujo ponto (0,0) é o canto superior esquerdo.
Parâmetros:
posicaoX (saída, passagem por referência): indica o valor no eixo X (horizontal) da esquerda para direita.
posicaoY (saida, passagem por referência): indica o valor no eixo Y (vertical), normalmente de cima para baixo.
idJanela (entrada, passagem por valor não-obrigatório): indica o número da janela a ser reposicionada.
********************************/
void GetPosicaoJanela(int *posicaoX, int *posicaoY, int idJanela=0){
    SDL_Point p = CPIGGerenciadorJanelas::GetJanela(idJanela)->GetXY();
    *posicaoX = p.x;
    *posicaoY = p.y;
}

/********************************
A função SetBordaJanela() é responsável por definir se uma janela possuirá ou não bordas visíveis. O valor de 0 (zero) indica ausência de borda, enquanto valores diferentes de zero indicam presença de borda.
Parâmetros:
valor (entrada, passagem por valor): indica se a janela possui borda (valor diferente de zero) ou não (valor igual a zero).
idJanela (entrada, passagem por valor não-obrigatório): indica o número da janela a ser reposicionada.
********************************/
void SetBordaJanela(int valor, int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->SetBorda(valor);
}

/********************************
A função SetModoJanela() é responsável por definir o modo de exibição de uma janela. A janela pode ser exibida em três diferentes modos: PIG_JANELA_NORMAL, que é o modo padrão onde a janela ocupa o espaço da tela definido por sua altura e largura atual;
PIG_JANELA_TELACHEIA_DISPLAY, que é o modo no qual a janela fica em tela cheia com a resolução idêntica à da tela; PIG_JANELA_TELACHEIA, que é o modo onde a janela fica em tela cheia, mas com a resolução atual mantida.
A tela cheia não é acionada automaticamente com a combinção ALT+ENTER, é preciso executar o comando específico.
Parâmetros:
modo (entrada, passagem por valor): indica qual dos três modos (PIG_JANELA_NORMAL, PIG_JANELA_TELACHEIA, PIG_JANELA_TELACHEIA_DISPLAY) deve ser usado para exibir a janela.
idJanela (entrada, passagem por valor não-obrigatório): indica o número da janela a ser reposicionada.
********************************/
void SetModoJanela(int modo, int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->SetModo(modo);
}

/********************************
A função GetModoJanela() é responsável por recuperar o modo de exibição de uma janela. A janela pode ser exibida em três diferentes modos: PIG_JANELA_NORMAL, que é o modo padrão onde a janela ocupa o espaço da tela definido por sua altura e largura atual;
PIG_JANELA_TELACHEIA_DISPLAY, que é o modo no qual a janela fica em tela cheia com a resolução idêntica à da tela; PIG_JANELA_TELACHEIA, que é o modo onde a janela fica em tela cheia, mas com a resolução atual mantida.
A tela cheia não é acionada automaticamente com a combinação ALT+ENTER, é preciso executar o comando específico.
Parâmetros:
idJanela (entrada, passagem por valor não-obrigatório): indica o número da janela a ser reposicionada.
Retorno:
inteiro que indica qual dos três modos (PIG_JANELA_NORMAL, PIG_JANELA_TELACHEIA, PIG_JANELA_TELACHEIA_DISPLAY) está sendo usado para exibir a janela.
********************************/
int GetModoJanela(int idJanela=0){
    return CPIGGerenciadorJanelas::GetJanela(idJanela)->GetModo();
}

#ifdef PIGCOMCONTROLE

/********************************
Seção de controle de jogo
********************************/

/********************************
A função BotaoPressionadoControle() é responsável por verificar se um determinado botão do controle está ou não pressionado.
Parâmetros:
idControle (entrada, passagem por valor): indica qual controle está sendo verificado.
botao (entrada, passagem por valor): indica qual botao está sendo verificado.
retono:
inteiro que representa se o botão está pressionado (valor diferente de zero) ou está livre (valor igual a zero).
********************************/
int BotaoPressionadoControle(int idControle, int botao){
    return CPIGGerenciadorControles::GetControle(idControle)->BotaoPressionado(botao);
}

/********************************
A função EixoAcionadoControle() é responsável por verificar o nível de acionamento de um eixo do controle. Essa função pode ser utilizada
tanto para eixos analógicos, cujos valores são de -32768 a 32767, ou gatilhos, cujos valores são de 0 a 32767.
Parâmetros:
idControle (entrada, passagem por valor): indica qual controle está sendo verificado.
eixo (entrada, passagem por valor): indica qual eixo está sendo verificado.
retono:
inteiro que representa o nível de acionamento do eixo. Pode ser um valor negativo (eixos analógicos) ou valores positivos (eixos analógicos e gatilhos).
********************************/
int EixoAcionadoControle(int idControle, int eixo){
    return CPIGGerenciadorControles::GetControle(idControle)->EixoAcionado(eixo);
}

/********************************
A função EixoAcionadoPercentualControle() é responsável por verificar o nível percentual de acionamento de um eixo do controle. Essa função pode ser utilizada
tanto para eixos analógicos, cujos valores são de -1.0 a 1.0, ou gatilhos, cujos valores são de 0 a 1.0.
Parâmetros:
idControle (entrada, passagem por valor): indica qual controle está sendo verificado.
eixo (entrada, passagem por valor): indica qual eixo está sendo verificado.
retono:
número real que representa o nível percentual de acionamento do eixo. Pode ser um valor negativo (eixos analógicos) ou valores positivos (eixos analógicos e gatilhos).
********************************/
float EixoAcionadoPercentualControle(int idControle, int eixo){
    return CPIGGerenciadorControles::GetControle(idControle)->EixoAcionadoPercentual(eixo);
}

/********************************
A função GetQtdEixosControle() é responsável por calcular quantos eixos e gatilhos estão disponíveis no controle.
Parâmetros:
idControle (entrada, passagem por valor): indica qual controle está sendo verificado.
retono:
inteiro que representa a quantidade de eixos e gatilhos.
********************************/
int GetQtdEixosControle(int idControle){
    return CPIGGerenciadorControles::GetControle(idControle)->GetQtdEixos();
}

/********************************
A função GetQtdBotoesControle() é responsável por calcular quantos botőes digitais (incluindo os direcionais) estão disponíveis no controle.
Parâmetros:
idControle (entrada, passagem por valor): indica qual controle está sendo verificado.
retono:
inteiro que representa a quantidade de botőes digitais (incluindo os direcionais).
********************************/
int GetQtdBotoesControle(int idControle){
    return CPIGGerenciadorControles::GetControle(idControle)->GetQtdBotoes();
}

/********************************
A função GetNomeControle() é responsável recuperar o nome com o qual o controle foi registrado no sistema.
Parâmetros:
idControle (entrada, passagem por valor): indica qual controle está sendo verificado.
nomeControle (saída, passagem por referência): armazena a string contendo o nome que foi recuperada para o controle.
********************************/
void GetNomeControle(int idControle, char *nomeControle){
    strcpy(nomeControle,CPIGGerenciadorControles::GetControle(idControle)->GetNome().c_str());
}

#endif // PIGCOMCONTROLE


/********************************
Seção de elementos geométricos
********************************/

/********************************
A função DesenhaLinhasSimples() é responsável por desenhar uma única linha, cujo início é o ponto (x1,y1) e o fim é o ponto (x2,y2).
Parâmetros:
pontoX1 (entrada, passagem por valor): inteiro que indica o início da linha no eixo X.
pontoY1 (entrada, passagem por valor): inteiro que indica o início da linha no eixo Y.
pontoX2 (entrada, passagem por valor): inteiro que indica o fim da linha no eixo X.
pontoY2 (entrada, passagem por valor): inteiro que indica o fim da linha no eixo Y.
cor (entrada, passagem por valor): indica a cor no sistema RGB para o desenho da linha.
idJanela (entrada, passagem por valor não-obrigatório): indica o número da janela onde a linha será desenhada.
********************************/
void DesenhaLinhaSimples(int pontoX1 ,int pontoY1, int pontoX2, int pontoY2, PIGCor cor, int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaLinhaSimples(pontoX1,pontoY1,pontoX2,pontoY2,cor);
}

/********************************
A função DesenhaLinhasDisjuntas() é responsável por desenhar linhas separadamente, ou seja, os ponto iniciais de cada linha estão nas posiçőes pares e
os pontos finais estão nas posiçőes ímpares. Assim, os vetores precisam ter tamanho qtdPontos*2.
Parâmetros:
pontosX (entrada, passagem por referência): vetor de inteiros, de tamanho qtdPontos*2, contendo os valores X (inicias e finais) de cada linha.
pontosY (entrada, passagem por referência): vetor de inteiros, de tamanho qtdPontos*2, contendo os valores Y (inicias e finais) de cada linha.
qtdPontos (entrada, passagem por valor): quantidade de linhas a serem desenhadas.
cor (entrada, passagem por valor): indica a cor no sistema RGB para o desenho das linhas.
idJanela (entrada, passagem por valor não-obrigatório): indica o número da janela onde as linhas serão desenhadas.
********************************/
void DesenhaLinhasDisjuntas(int pontosX[], int pontosY[], int qtdPontos, PIGCor cor, int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaLinhasDisjuntas(pontosX,pontosY,qtdPontos,cor);
}

/********************************
A função DesenhaLinhasSequencia() é responsável por desenhar linhas em sequência, ou seja, o ponto final da primeira linha
corresponde ao ponto inicial da segunda linha.
Parâmetros:
pontosX (entrada, passagem por referência): vetor de inteiros, de tamanho qtdPontos+1, contendo os valores X de cada linha da sequência.
pontosY (entrada, passagem por referência): vetor de inteiros, de tamanho qtdPontos+1, contendo os valores Y de cada linha da sequência.
qtdPontos (entrada, passagem por valor): quantidade de linhas a serem desenhadas.
cor (entrada, passagem por valor): indica a cor no sistema RGB para o desenho das linhas.
idJanela (entrada, passagem por valor não-obrigatório): indica o número da janela onde as linhas serão desenhadas.
********************************/
void DesenhaLinhasSequencia(int pontosX[], int pontosY[], int qtdPontos, PIGCor cor, int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaLinhasSequencia(pontosX,pontosY,qtdPontos,cor);
}

/********************************
A função DesenhaRetangulo() é responsável por desenhar um retângulo com preenchimento sólido na tela em uma posição desejada pelo usuário.
O mesmo pode ser colocado em qualquer lugar do campo de visão da tela.
Parâmetros:
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usuário deseja colocar o retângulo.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usuário deseja colocar o retângulo.
altura (entrada, passagem por valor): Valor onde o usuário irá fornecer o número correspondente em pixels à altura desse retângulo.
largura (entrada, passagem por valor): Valor onde o usuário irá fornecer o número correspondente em pixels à largura desse retângulo.
cor (entrada, passagem por valor): indica a cor no sistema RGB para o desenho do retângulo.
idJanela (entrada, passagem por valor não-obrigatório): indica o número da janela onde o retângulo será desenhado.
********************************/
void DesenhaRetangulo(int posicaoX, int posicaoY, int altura, int largura, PIGCor cor, int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetangulo(posicaoX,posicaoY,altura,largura,cor);
}

/********************************
A função DesenhaRetanguloVazado() é responsável por desenhar um retângulo sem preenchimento na tela em uma posição desejada pelo usuário.
O mesmo pode ser colocado em qualquer lugar do campo de visão da tela.
Parâmetros:
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usuário deseja colocar o retângulo.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usuário deseja colocar o retângulo.
altura (entrada, passagem por valor): Valor onde o usuário irá fornecer o número correspondente em pixels à altura desse retângulo.
largura (entrada, passagem por valor): Valor onde o usuário irá fornecer o número correspondente em pixels à largura desse retângulo.
cor (entrada, passagem por valor): indica a cor no sistema RGB para a borda do retângulo.
idJanela (entrada, passagem por valor não-obrigatório): indica o número da janela onde o retângulo será desenhado.
********************************/
void DesenhaRetanguloVazado(int posicaoX, int posicaoY, int altura, int largura, PIGCor cor, int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetanguloVazado(posicaoX,posicaoY,altura,largura,cor);
}

/********************************
A função DesenhaPoligono() é responsável por desenhar na janela um polígono de preenchimento sólido com o número de lados indicados. Os dois primeiros parâmetros indicam as coordenadas
de cada um dos vértices do polígono.
AVISO: essa função utiliza o renderizador offscreen para gerar o polígono e posteriormente o renderiza na janela em questão; isto pode fazer o FPS da aplicação diminuir consideravelmente.
Parâmetros:
pontosX (entrada, passagem por referência): vetor de inteiros, de tamanho qtdPontos, contendo as coordenadas X de cada vértice do polígono.
pontosY (entrada, passagem por referência): vetor de inteiros, de tamanho qtdPontos, contendo as coordenadas Y de cada vértice do polígono.
qtdPontos (entrada, passagem por valor): quantidade de lados do polígono.
cor (entrada, passagem por valor): indica a cor no sistema RGB para o desenho do polígono.
idJanela (entrada, passagem por valor não-obrigatório): indica o número da janela onde o polígono será desenhado.
********************************/
void DesenhaPoligono(int pontosX[], int pontosY[], int qtdPontos, PIGCor cor, int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaPoligono(pontosX,pontosY,qtdPontos,cor);
}


/********************************
Seção de desenho Offscreen
********************************/

/********************************
A função PreparaOffScreenRenderer() serve para criar um novo bitmap offscreen que servirá de área
de desenho para outras funçőes que utilizem este bitmap.
Parâmetros:
altura (entrada, passagem por valor): indica a altura em pixels do novo bitmap.
largura (entrada, passagem por valor): indica a largura em pixels do novo bitmap.
********************************/
void PreparaOffScreenRenderer(int altura, int largura){
    jogo->PreparaOffScreenRenderer(altura,largura);
}

/********************************
A função SalvaOffScreenBMP() serve para efetivamente salvar a imagem offscreen como um arquivo do sistema operacional.
A imagem offscreen continuará existindo em memória e açőes subsequentes ainda poderão ser feitas. Para "limpar" a imagem
deve-se utilizar a função PintaFundoOffScreen().
Parâmetros:
nomeArquivoBMP (entrada, passagem por referência*): indica com que nome a imagem offscreen será salva. O valor do parâmetro deve conter a extensão ".bmp".
É utilizado o operador * apenas por se tratar de um parâmetro string. O valor do parâmetro não é alterado dentro da função.
********************************/
void SalvaOffScreenBMP(char *nomeArquivoBMP){
    jogo->GetOffScreenRender()->SalvarImagemBMP(nomeArquivoBMP);
}

/********************************
A função SalvaOffScreenPNG() serve para efetivamente salvar a imagem offscreen como um arquivo do sistema operacional.
A imagem offscreen continuará existindo em memória e açőes subsequentes ainda poderão ser feitas. Para "limpar" a imagem
deve-se utilizar a função PintaFundoOffScreen().
Parâmetros:
nomeArquivoPNG (entrada, passagem por referência*): indica com que nome a imagem offscreen será salva. O valor do parâmetro deve conter a extensão ".png".
É utilizado o operador * apenas por se tratar de um parâmetro string. O valor do parâmetro não é alterado dentro da função.
********************************/
void SalvaOffScreenPNG(char *nomeArquivoPNG){
    jogo->GetOffScreenRender()->SalvarImagemPNG(nomeArquivoPNG);
}

/********************************
A função PintaAreaOffScreen() serve para mudar a cor de uma área contígua de pixels da mesma cor.
A funcionalidade é semelhante à ferramenta "balde" dos editores de imagem. A área será pintada a partir do
ponto (posicaoX,posicaoY) de acordo com o sistema de coordenadas da PIG. A função de pintura padrão pode ser
substituída por outra função customizada qualquer com o comando DefineFuncaoPintarAreaOffscreen().
Parâmetros:
posicaoX (entrada, passagem por valor): indica o ponto no eixo X para começar a pintar a área contígua de pixels.
posicaoY (entrada, passagem por valor): indica o ponto no eixo Y para começar a pintar a área contígua de pixels.
cor (entrada, passagem por valor): indica a cor que deve ser usada durante a pintura da área contígua de pixels.
********************************/
void PintaAreaOffScreen(int posicaoX, int posicaoY, PIGCor cor){
    jogo->GetOffScreenRender()->PintarArea(posicaoX,posicaoY,cor);
}

/********************************
A função DefineFuncaoPintarAreaOffScreen() permite substituir a função padrão de pintura por outra função customizada que deve ser passada como parâmetro.
A função de pintura deve ser definida de forma que receba 4 parâmetros inteiros (respectivamente, a posição x e y do pixel que deve ser pintado e as
dimensőes - altura e largura - da imagem offscreen) e 2 cores (a cor atual do pixel e a cor que deveria ser usada para pintá-lo). A função deve também retornar
o valor de uma cor, que será a cor efetivamente utilizada para pintar o pixel em questão. A função, portanto, deve definir para cada ponto solicitado qual a cor
final daquele ponto.
Parâmetros:
funcao (entrada, passagem por referência): nome da função customizada para pintar uma área no renderizador offscreen.
********************************/
void DefineFuncaoPintarAreaOffscreen(PIGFuncaoPintarArea funcao){
    jogo->GetOffScreenRender()->DefineFuncaoPintarArea(funcao);
}

/********************************
A função MoveCanetaOffScreen() reposiciona a caneta do renderizador offscreen em algum outro ponto da imagem.
Parâmetros:
novoX (entrada, passagem por valor): nova posição no eixo X na qual a caneta será reposicionada. O tipo de parâmetro é double mas será convertido para int, dentro da função.
novoY (entrada, passagem por valor): nova posição no eixo Y na qual a caneta será reposicionada. O tipo de parâmetro é double mas será convertido para int, dentro da função.
********************************/
void MoveCanetaOffscreen(double novoX, double novoY){
    jogo->GetOffScreenRender()->MoveCanetaPara(novoX,novoY);
}

/********************************
A função AvancaCanetaOffScreen() cria uma linha no renderizador offscreen na direção e sentido nos quais a caneta está orientada.
Parâmetros:
distancia (entrada, passagem por valor): distância a ser percorrida pela caneta. O tipo de parâmetro é double para permitir que o cálculo da distância seja feito livremente.
********************************/
void AvancaCanetaOffscreen(double distancia){
    jogo->GetOffScreenRender()->AvancaCaneta(distancia);
}

/********************************
A função MudaCorCanetaOffScreen() modifica a cor a ser utilizada pela caneta do renderizador offscreen daqui por diante. Desenhos feitos anteriormente permancem com a cor com a qual foram feitos.
Parâmetros:
novaCor (entrada, passagem por valor): valor da nova cor a ser utilizada pela caneta do renderizador offscreen.
********************************/
void MudaCorCanetaOffscreen(PIGCor novaCor){
    jogo->GetOffScreenRender()->MudaCorAtualCaneta(novaCor);
}

/********************************
A função GiraCanetaHorarioOffScreen() gira a caneta do renderizador offscreen. A caneta passa a ter uma nova direção e sentido. Se o comando AvancaCanetaOffscreen() for executado posteriormente,
esses novos valores de direção e sentido serão utilizados para que o ponto final do traço seja calculado.
Parâmetros:
angulo (entrada, passagem por valor): valor do ângulo (sentido horário, em radianos) pelo qual a caneta será redirecionada.
********************************/
void GiraCanetaHorarioOffscreen(double angulo){
    jogo->GetOffScreenRender()->GiraCanetaHorario(angulo);
}

/********************************
A função GiraCanetaAntiHorarioOffScreen() gira a caneta do renderizador offscreen. A caneta passa a ter uma nova direção e sentido. Se o comando AvancaCanetaOffscreen() for executado posteriormente,
esses novos valores de direção e sentido serão utilizados para que o ponto final do traço seja calculado.
Parâmetros:
angulo (entrada, passagem por valor): valor do ângulo (sentido anti-horário, em radianos) pelo qual a caneta será redirecionada.
********************************/
void GiraCanetaAntiHorarioOffscreen(double angulo){
    jogo->GetOffScreenRender()->GiraCanetaAntiHorario(angulo);
}

/********************************
A função GiraCanetaAnguloFixoOffScreen() gira a caneta do renderizador offscreen. A caneta passa a ter uma nova direção e sentido. Se o comando AvancaCanetaOffscreen() for executado posteriormente,
esses novos valores de direção e sentido serão utilizados para que o ponto final do traço seja calculado.
Parâmetros:
angulo (entrada, passagem por valor): valor do ângulo usando como referência o ângulo 0 do círculo trigonométrico.
********************************/
void GiraCanetaAnguloFixoOffscreen(double angulo){
    jogo->GetOffScreenRender()->GiraAnguloFixo(angulo);
}

/********************************
A função GetAnguloAtualOffScreen() recupera o ângulo atual que está sendo usado pela caneta do renderizador offscreen.
Retorno:
número real que representa o valor do ângulo atual, tendo como referência o ângulo 0 do círculo trigonométrico.
********************************/
double GetAnguloAtualOffscreen(){
    return jogo->GetOffScreenRender()->GetAngAtual();
}

/********************************
A função GetXCanetaOffScreen() recupera a posição no eixo X na qual está posicionada atualmente a caneta do renderizador offscreen.
Retorno:
inteiro que representa a posição atual da caneta no eixo X.
********************************/
int GetXCanetaOffscreen(){
    return jogo->GetOffScreenRender()->GetXCaneta();
}

/********************************
A função GetYCanetaOffScreen() recupera a posição no eixo Y na qual está posicionada atualmente a caneta do renderizador offscreen.
Retorno:
inteiro que representa a posição atual da caneta no eixo Y.
********************************/
int GetYCanetaOffscreen(){
    return jogo->GetOffScreenRender()->GetYCaneta();
}

/********************************
A função PintaFundoOffScreen() serve para "limpar" o bitmap offscreen, mudando completamente para cor indicada.
Parâmetros:
cor (entrada, passagem por valor): indica a cor que deve ser usada durante a pintura completa do bitmap offscreen.
********************************/
void PintaFundoOffScreen(PIGCor cor){
    jogo->GetOffScreenRender()->PintarFundo(cor);
}

/********************************
A função DesenhaRetanguloOffScreen() é responsável por desenhar um retângulo cem preenchimento sólido no bitmap offscreen em uma posição desejada pelo usuário.
O sistema de coordenadas é o mesmo da tela, com o eixo Y aumentando para cima.
Parâmetros:
posicaoX (entrada, passagem por valor): Valor da coordenada X onde o usuário deseja colocar o retângulo.
posicaoY (entrada, passagem por valor): Valor da coordenada Y onde o usuário deseja colocar o retângulo.
altura (entrada, passagem por valor): Valor onde o usuário irá fornecer o número correspondente em pixels à altura desse retângulo.
largura (entrada, passagem por valor): Valor onde o usuário irá fornecer o número correspondente em pixels à largura desse retângulo.
cor (entrada, passagem por valor): indica a cor no sistema RGB para o preenchimento do retângulo.
********************************/
void DesenhaRetanguloOffScreen(int x1, int y1, int altura, int largura, PIGCor cor){
    jogo->GetOffScreenRender()->DesenharRetangulo(x1,y1,altura,largura,cor);
}

/********************************
A função DesenhaRetanguloVazadoOffScreen() é responsável por desenhar um retângulo sem preenchimento no bitmap offscreen em uma posição desejada pelo usuário.
O sistema de coordenadas é o mesmo da tela, com o eixo Y aumentando para cima.
Parâmetros:
posicaoX (entrada, passagem por valor): Valor da coordenada X onde o usuário deseja colocar o retângulo.
posicaoY (entrada, passagem por valor): Valor da coordenada Y onde o usuário deseja colocar o retângulo.
altura (entrada, passagem por valor): Valor onde o usuário irá fornecer o número correspondente em pixels à altura desse retângulo.
largura (entrada, passagem por valor): Valor onde o usuário irá fornecer o número correspondente em pixels à largura desse retângulo.
cor (entrada, passagem por valor): indica a cor no sistema RGB para a borda do retângulo.
********************************/
void DesenhaRetanguloVazadoOffScreen(int x1, int y1, int altura, int largura, PIGCor cor){
    jogo->GetOffScreenRender()->DesenharRetanguloVazado(x1,y1,altura,largura,cor);
}

/********************************
A função DesenhaLinhasSimplesOffScreen() é responsável por desenhar no bitmap offscreen uma única linha, cuja início é o ponto (x1,y1) e o fim é o ponto (x2,y2).
Parâmetros:
pontoX1 (entrada, passagem por valor): inteiro que indica o início da linha no eixo X.
pontoY1 (entrada, passagem por valor): inteiro que indica o início da linha no eixo Y.
pontoX2 (entrada, passagem por valor): inteiro que indica o fim da linha no eixo X.
pontoY2 (entrada, passagem por valor): inteiro que indica o fim da linha no eixo Y.
cor (entrada, passagem por valor): indica a cor no sistema RGB para o desenho das linhas.
********************************/
void DesenhaLinhaSimplesOffScreen(int x1, int y1, int x2, int y2, PIGCor cor){
    jogo->GetOffScreenRender()->DesenharLinha(x1,y1,x2,y2,cor);
}

/********************************
A função DesenhaLinhasDisjuntasOffScreen() é responsável por desenhar no bitmap offscreen linhas separadamente, ou seja, os ponto iniciais de cada linha estão nas posiçőes pares e
os pontos finais estão nas posiçőes ímpares. Assim, os vetores precisam ter tamanho qtdPontos*2.
Parâmetros:
pontosX (entrada, passagem por referência): vetor de inteiros, de tamanho qtdPontos*2, contendo os valores X (inicias e finais) de cada linha.
pontosY (entrada, passagem por referência): vetor de inteiros, de tamanho qtdPontos*2, contendo os valores Y (inicias e finais) de cada linha.
qtdPontos (entrada, passagem por valor): quantidade de linhas a serem desenhadas.
cor (entrada, passagem por valor): indica a cor no sistema RGB para o desenho das linhas.
********************************/
void DesenhaLinhasDisjuntasOffScreen(int pontosX[], int pontosY[], int qtdPontos, PIGCor cor){
    jogo->GetOffScreenRender()->DesenhaLinhasDisjuntas(pontosX,pontosY,qtdPontos,cor);
}

/********************************
A função DesenhaLinhasSequenciaOffScreen() é responsável por desenhar no bitmap offscreen linhas em sequência, ou seja, o ponto final da primeira linha
corresponde ao ponto inicial da segunda linha.
Parâmetros:
pontosX (entrada, passagem por referência): vetor de inteiros, de tamanho qtdPontos+1, contendo os valores X de cada linha da sequência.
pontosY (entrada, passagem por referência): vetor de inteiros, de tamanho qtdPontos+1, contendo os valores Y de cada linha da sequência.
qtdPontos (entrada, passagem por valor): quantidade de linhas a serem desenhadas.
cor (entrada, passagem por valor): indica a cor no sistema RGB para o desenho das linhas.
********************************/
void DesenhaLinhasSequenciaOffScreen(int pontosX[], int pontosY[], int qtdPontos, PIGCor cor){
    jogo->GetOffScreenRender()->DesenhaLinhasSequencia(pontosX,pontosY,qtdPontos,cor);
}


///escrever

/********************************
Seção de fontes
********************************/

/********************************
A função CriaFonteNormal() é responsável por disponibilizar uma nova fonte com preenchimento sólido.
Parâmetros:
nome (entrada, passagem por referência): nome do arquivo que contém a fonte (normalmente com extensão ttf).
tamanho (entrada, passagem por valor): tamanho da fonte, que normalmente representa a altura média (em pixels) dos caracteres da fonte.
corLetra (entrada, passagem por valor): representa a cor de preenchimento da fonte.
contorno (entrada, passagem por valor): representa a espessura do contorno que fonte terá. Caso não seja desejado um contorno, basta utilizar um valor 0.
corContorno (entrada, passagem por valor): representa a cor do contorno da fonte.
estilo (entrada, passagem por valor): representa o estilo da fonte. Pode ser uma combinação binária de: PIG_ESTILO_NEGRITO, para negrito; PIG_ESTILO_SUBLINHADO, para sublinhado; PIG_ESTILO_ITALICO, para itálico;
PIG_ESTILO_CORTADO, para uma linha horizontal à meia-altura. Caso nenhum estilo seja desejado, pode ser omitido ou usado PIG_ESTILO_NORMAL.
idJanela (entrada, passagem por valor não-obrigatório): indica qual janela vai receber a fonte. Uma fonte só pode ser usada na janela na qual foi criada.
retono:
inteiro que representa a ideintificação única da fonte. Futuras referência a esta fonte devem idenitificá-las pelo número.
********************************/
int CriaFonteNormal(char *nome, int tamanho, PIGCor corLetra, int contorno, PIGCor corContorno, PIGEstilo estilo=PIG_ESTILO_NORMAL, int idJanela=0){
    return CPIGGerenciadorFontes::CriaFonteNormal(nome,tamanho,estilo,corLetra,contorno,corContorno,idJanela);
}

/********************************
A função CriaFonteNormal() é responsável por disponibilizar uma nova fonte com preenchimento sólido.
Parâmetros:
nome (entrada, passagem por referência): nome do arquivo que contém a fonte (normalmente com extensão ttf).
tamanho (entrada, passagem por valor): tamanho da fonte, que normalmente representa a altura média (em pixels) dos caracteres da fonte.
corLetra (entrada, passagem por valor): representa a cor de preenchimento da fonte. Caso a cor não seja informada, será utilizada a cor padrão (BRANCO).
estilo (entrada, passagem por valor): representa o estilo da fonte. Pode ser uma combinação binária de: PIG_ESTILO_NEGRITO, para negrito; PIG_ESTILO_SUBLINHADO, para sublinhado; PIG_ESTILO_ITALICO, para itálico;
PIG_ESTILO_CORTADO, para uma linha horizontal à meia-altura. Caso nenhum estilo seja desejado, pode ser omitido ou usado PIG_ESTILO_NORMAL.
idJanela (entrada, passagem por valor não-obrigatório): indica qual janela vai receber a fonte. Uma fonte só pode ser usada na janela na qual foi criada.
retono:
inteiro que representa a ideintificação única da fonte. Futuras referência a esta fonte devem idenitificá-las pelo número.
********************************/
int CriaFonteNormal(char *nome, int tamanho, PIGCor corLetra=BRANCO, PIGEstilo estilo=PIG_ESTILO_NORMAL, int idJanela=0){
    return CPIGGerenciadorFontes::CriaFonteNormal(nome,tamanho,estilo,corLetra,idJanela);
}

/********************************
A função CriaFonteDinamica() é responsável por disponibilizar uma nova fonte dinâmica com preenchimento sólido. As fontes dinâmicas são capazes
de escrever strings com diferentes formataçőes (negrito, itálico, sublinhado, cortado) e cores nas letras. A string a ser utilizada pela fonte
pode conter ou não os marcadores de formtação. Caso não contenham, será utilizada uma letra branca, sem formatação.
Parâmetros:
nome (entrada, passagem por referência): nome do arquivo que contém a fonte (normalmente com extensão ttf).
tamanho (entrada, passagem por valor): tamanho da fonte, que normalmente representa a altura média (em pixels) dos caracteres da fonte.
idJanela (entrada, passagem por valor não-obrigatório): indica qual janela vai receber a fonte. Uma fonte só pode ser usada na janela na qual foi criada.
retono:
inteiro que representa a ideintificação única da fonte. Futuras referência a esta fonte devem idenitificá-las pelo número.
********************************/
int CriaFonteDinamica(char *nome, int tamanho, int idJanela=0){
    return CPIGGerenciadorFontes::CriaFonteDinamica(nome,tamanho,idJanela);
}

/********************************
A função CriaFonteFundo() é responsável por disponibilizar uma nova fonte com preenchimento de um bitmap específico.
Parâmetros:
nome (entrada, passagem por referência): nome do arquivo que contém a fonte (normalmente com extensão ttf).
tamanho (entrada, passagem por valor): tamanho da fonte, que normalmente representa a altura média (em pixels) dos caracteres da fonte.
arquivoFundo (entrada, passagem por referência): indica o nome do arquivo de imagem que servirá de fundo para a fonte.
contorno (entrada, passagem por valor): representa a espessura do contorno que fonte terá. Caso não seja desejado um contorno, basta utilizar um valor 0.
corContorno (entrada, passagem por valor): representa a cor do contorno da fonte.
estilo (entrada, passagem por valor): representa o estilo da fonte. Pode ser uma combinação binária de: PIG_ESTILO_NEGRITO, para negrito; PIG_ESTILO_SUBLINHADO, para sublinhado; PIG_ESTILO_ITALICO, para itálico;
PIG_ESTILO_CORTADO, para uma linha horizontal à meia-altura. Caso nenhum estilo seja desejado, pode ser omitido ou usado PIG_ESTILO_NORMAL.
idJanela (entrada, passagem por valor não-obrigatório): indica qual janela vai receber a fonte. Uma fonte só pode ser usada na janela na qual foi criada.
retono:
inteiro que representa a ideintificação única da fonte. Futuras referência a esta fonte devem idenitificá-las pelo número.
********************************/
int CriaFonteFundo(char *nome, int tamanho, char *arquivoFundo, int contorno, PIGCor corContorno, PIGEstilo estilo=PIG_ESTILO_NORMAL, int idJanela=0){
    return CPIGGerenciadorFontes::CriaFonteFundo(nome,tamanho,estilo,arquivoFundo,contorno,corContorno,idJanela);
}

/********************************
A função CriaFonteFundo() é responsável por disponibilizar uma nova fonte com preenchimento de um bitmap específico.
Parâmetros:
nome (entrada, passagem por referência): nome do arquivo que contém a fonte (normalmente com extensão ttf).
tamanho (entrada, passagem por valor): tamanho da fonte, que normalmente representa a altura média (em pixels) dos caracteres da fonte.
arquivoFundo (entrada, passagem por referência): indica o nome do arquivo de imagem que servirá de fundo para a fonte.
estilo (entrada, passagem por valor): representa o estilo da fonte. Pode ser uma combinação binária de: PIG_ESTILO_NEGRITO, para negrito; PIG_ESTILO_SUBLINHADO, para sublinhado; PIG_ESTILO_ITALICO, para itálico;
PIG_ESTILO_CORTADO, para uma linha horizontal à meia-altura. Caso nenhum estilo seja desejado, pode ser omitido ou usado PIG_ESTILO_NORMAL.
idJanela (entrada, passagem por valor não-obrigatório): indica qual janela vai receber a fonte. Uma fonte só pode ser usada na janela na qual foi criada.
retono:
inteiro que representa a ideintificação única da fonte. Futuras referência a esta fonte devem idenitificá-las pelo número.
********************************/
int CriaFonteFundo(char *nome, int tamanho, char *arquivoFundo, PIGEstilo estilo=PIG_ESTILO_NORMAL, int idJanela=0){
    return CPIGGerenciadorFontes::CriaFonteFundo(nome,tamanho,estilo,arquivoFundo,idJanela);
}


/********************************
A função CriaFonteNormalOffscreen() é responsável por disponibilizar uma nova fonte com preenchimento sólido.
Parâmetros:
nome (entrada, passagem por referência): nome do arquivo que contém a fonte (normalmente com extensão ttf).
tamanho (entrada, passagem por valor): tamanho da fonte, que normalmente representa a altura média (em pixels) dos caracteres da fonte.
corLetra (entrada, passagem por valor): representa a cor de preenchimento da fonte.
contorno (entrada, passagem por valor): representa a espessura do contorno que fonte terá. Caso não seja desejado um contorno, basta utilizar um valor 0.
corContorno (entrada, passagem por valor): representa a cor do contorno da fonte.
estilo (entrada, passagem por valor): representa o estilo da fonte. Pode ser uma combinação binária de: PIG_ESTILO_NEGRITO, para negrito; PIG_ESTILO_SUBLINHADO, para sublinhado; PIG_ESTILO_ITALICO, para itálico;
PIG_ESTILO_CORTADO, para uma linha horizontal à meia-altura. Caso nenhum estilo seja desejado, pode ser omitido ou usado PIG_ESTILO_NORMAL.
retono:
inteiro que representa a ideintificação única da fonte. Futuras referência a esta fonte devem idenitificá-las pelo número.
********************************/
int CriaFonteNormalOffscreen(char *nome, int tamanho, PIGCor corLetra, int contorno, PIGCor corContorno, PIGEstilo estilo=PIG_ESTILO_NORMAL){
    return CPIGGerenciadorFontes::CriaFonteNormalOffScreen(nome,tamanho,estilo,corLetra,contorno,corContorno,jogo->GetOffScreenRender(),0);
}

/********************************
A função CriaFonteNormalOffscreen() é responsável por disponibilizar uma nova fonte com preenchimento sólido.
Parâmetros:
nome (entrada, passagem por referência): nome do arquivo que contém a fonte (normalmente com extensão ttf).
tamanho (entrada, passagem por valor): tamanho da fonte, que normalmente representa a altura média (em pixels) dos caracteres da fonte.
corLetra (entrada, passagem por valor): representa a cor de preenchimento da fonte. Caso a cor não seja informada, será utilizada a cor padrão (BRANCO).
estilo (entrada, passagem por valor): representa o estilo da fonte. Pode ser uma combinação binária de: PIG_ESTILO_NEGRITO, para negrito; PIG_ESTILO_SUBLINHADO, para sublinhado; PIG_ESTILO_ITALICO, para itálico;
PIG_ESTILO_CORTADO, para uma linha horizontal à meia-altura. Caso nenhum estilo seja desejado, pode ser omitido ou usado PIG_ESTILO_NORMAL.
retono:
inteiro que representa a ideintificação única da fonte. Futuras referência a esta fonte devem idenitificá-las pelo número.
********************************/
int CriaFonteNormalOffscreen(char *nome, int tamanho, PIGCor corLetra=BRANCO, PIGEstilo estilo=PIG_ESTILO_NORMAL){
    return CPIGGerenciadorFontes::CriaFonteNormalOffScreen(nome,tamanho,estilo,jogo->GetOffScreenRender(),corLetra,0);
}


/********************************
A função CriaFonteFundoOffscreen() é responsável por disponibilizar uma nova fonte com preenchimento de um bitmap específico.
Parâmetros:
nome (entrada, passagem por referência): nome do arquivo que contém a fonte (normalmente com extensão ttf).
tamanho (entrada, passagem por valor): tamanho da fonte, que normalmente representa a altura média (em pixels) dos caracteres da fonte.
arquivoFundo (entrada, passagem por referência): indica o nome do arquivo de imagem que servirá de fundo para a fonte.
contorno (entrada, passagem por valor): representa a espessura do contorno que fonte terá. Caso não seja desejado um contorno, basta utilizar um valor 0.
corContorno (entrada, passagem por valor): representa a cor do contorno da fonte.
estilo (entrada, passagem por valor): representa o estilo da fonte. Pode ser uma combinação binária de: PIG_ESTILO_NEGRITO, para negrito; PIG_ESTILO_SUBLINHADO, para sublinhado; PIG_ESTILO_ITALICO, para itálico;
PIG_ESTILO_CORTADO, para uma linha horizontal à meia-altura. Caso nenhum estilo seja desejado, pode ser omitido ou usado PIG_ESTILO_NORMAL.
retono:
inteiro que representa a ideintificação única da fonte. Futuras referência a esta fonte devem idenitificá-las pelo número.
********************************/
int CriaFonteFundoOffscreen(char *nome, int tamanho, char *arquivoFundo, int contorno, PIGCor corContorno, PIGEstilo estilo=PIG_ESTILO_NORMAL){
    return CPIGGerenciadorFontes::CriaFonteFundoOffScreen(nome,tamanho,estilo,arquivoFundo,contorno,corContorno,jogo->GetOffScreenRender(),0);
}

/********************************
A função CriaFonteFundoOffscreen() é responsável por disponibilizar uma nova fonte com preenchimento de um bitmap específico.
Parâmetros:
nome (entrada, passagem por referência): nome do arquivo que contém a fonte (normalmente com extensão ttf).
tamanho (entrada, passagem por valor): tamanho da fonte, que normalmente representa a altura média (em pixels) dos caracteres da fonte.
arquivoFundo (entrada, passagem por referência): indica o nome do arquivo de imagem que servirá de fundo para a fonte.
estilo (entrada, passagem por valor): representa o estilo da fonte. Pode ser uma combinação binária de: PIG_ESTILO_NEGRITO, para negrito; PIG_ESTILO_SUBLINHADO, para sublinhado; PIG_ESTILO_ITALICO, para itálico;
PIG_ESTILO_CORTADO, para uma linha horizontal à meia-altura. Caso nenhum estilo seja desejado, pode ser omitido ou usado PIG_ESTILO_NORMAL.
retono:
inteiro que representa a ideintificação única da fonte. Futuras referência a esta fonte devem idenitificá-las pelo número.
********************************/
int CriaFonteFundoOffscreen(char *nome, int tamanho, char *arquivoFundo, PIGEstilo estilo=PIG_ESTILO_NORMAL){
    return CPIGGerenciadorFontes::CriaFonteFundoOffScreen(nome,tamanho,estilo,arquivoFundo,jogo->GetOffScreenRender(),0);
}

/********************************
A função CalculaLarguraPixels() é responsável por realizar a soma das larguras de cada letra da string informada.
Parâmetros:
str (entrada, passagem por referência): string a ser escrita na tela.
numFonte (entrada, passagem por valor): número da fonte a ser utilizada. Caso o usuário não deseje uma fonte especial, será utilizada a fonte padrão (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
retorno:
inteiro que representa o total de pixels (no eixo x) necessários para escrever a string.
********************************/
int CalculaLarguraPixels(char *str, int numFonte=0){
    return CPIGGerenciadorFontes::GetFonte(numFonte)->GetLarguraPixelsString(str);
}

/********************************
A função EscreverDireita() é responsável por exibir uma string na tela de jogo, com alinhamento à direita do valor de X.
Parâmetros:
str (entrada, passagem por referência): string a ser escrita na tela.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usuário deseja começar a escrever a string.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usuário deseja começar a escrever a string.
cor (entrada, passagem por valor): cor a ser aplicada à fonte no momento da escrita. Essa cor é misturada à cor original da fonte, se essa tiver sido informada na criação da fonte.
numFonte (entrada, passagem por valor): número da fonte a ser utilizada. Caso o usuário não deseje uma fonte especial, será utilizada a fonte padrão (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
angulo (entrada, passagem por valor): ângulo, em graus, para a rotação da string.
********************************/
void EscreverDireita(char *str,int posicaoX, int posicaoY, PIGCor cor=BRANCO, int numFonte=0, float angulo=0){
    CPIGGerenciadorFontes::GetFonte(numFonte)->Escreve(str,posicaoX,posicaoY,cor,PIG_TEXTO_DIREITA,angulo);
}

/********************************
A função EscreverEsquerda() é responsável por exibir uma string na tela de jogo, com alinhamento à esquerda do valor de X.
Parâmetros:
str (entrada, passagem por referência): string a ser escrita na tela.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usuário deseja começar a escrever a string.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usuário deseja começar a escrever a string.
cor (entrada, passagem por valor): cor a ser aplicada à fonte no momento da escrita. Essa cor é misturada à cor original da fonte, se essa tiver sido informada na criação da fonte.
numFonte (entrada, passagem por valor): número da fonte a ser utilizada. Caso o usuário não deseje uma fonte especial, será utilizada a fonte padrão (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
angulo (entrada, passagem por valor): ângulo, em graus, para a rotação da string.
********************************/
void EscreverEsquerda(char *str, int posicaoX, int posicaoY, PIGCor cor=BRANCO, int numFonte=0,float angulo=0){
    CPIGGerenciadorFontes::GetFonte(numFonte)->Escreve(str,posicaoX,posicaoY,cor,PIG_TEXTO_ESQUERDA,angulo);
}

/********************************
A função EscreverCentralizada() é responsável por exibir uma string na tela de jogo, com alinhamento em relação ao valor de X.
Parâmetros:
str (entrada, passagem por referência): string a ser escrita na tela.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usuário deseja começar a escrever a string.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usuário deseja começar a escrever a string.
cor (entrada, passagem por valor): cor a ser aplicada à fonte no momento da escrita. Essa cor é misturada à cor original da fonte, se essa tiver sido informada na criação da fonte.
numFonte (entrada, passagem por valor): número da fonte a ser utilizada. Caso o usuário não deseje uma fonte especial, será utilizada a fonte padrão (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
angulo (entrada, passagem por valor): ângulo, em graus, para a rotação da string.
********************************/
void EscreverCentralizada(char *str, int posicaoX, int posicaoY, PIGCor cor=BRANCO, int numFonte=0, float angulo=0){
    CPIGGerenciadorFontes::GetFonte(numFonte)->Escreve(str,posicaoX,posicaoY,cor,PIG_TEXTO_CENTRO,angulo);
}

/********************************
A função EscreverLongaEsquerda() é responsável por exibir uma string longa na tela de jogo, com alinhamento à esquerda do valor de X.
A string se expande palavra por palavra até a largura máxima definida (maxLarg). Se ainda houver palavras, elas serão escritas na linha abaixo,
tendo um espaçamento entre as linhas (espacoEntreLinhas) também definido por parâmetro.
Parâmetros:
str (entrada, passagem por referência): string a ser escrita na tela.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usuário deseja começar a escrever a string.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usuário deseja começar a escrever a string.
largMax (entrada, passagem por valor): largura máxima em pixels que pode ser utilizada para escrever as palavras em cada linha do texto. ao atingir esse limite, as palavras seguintes são escritas na linha abaixo.
espacoEntreLinhas (entrada, passagem por valor): distância em pixels entre o valor Y de uma linha e o valor Y da linha abaixo.
cor (entrada, passagem por valor): cor a ser aplicada à fonte no momento da escrita. Essa cor é misturada à cor original da fonte, se essa tiver sido informada na criação da fonte.
numFonte (entrada, passagem por valor): número da fonte a ser utilizada. Caso o usuário não deseje uma fonte especial, será utilizada a fonte padrão (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
angulo (entrada, passagem por valor): ângulo, em graus, para a rotação das strings.
********************************/
void EscreverLongaEsquerda(char *str, int posicaoX, int posicaoY, int largMax, int espacoEntreLinhas, PIGCor cor=BRANCO, int numFonte=0, float angulo=0){
    CPIGGerenciadorFontes::GetFonte(numFonte)->EscreveLonga(str,posicaoX,posicaoY,largMax,espacoEntreLinhas,cor,PIG_TEXTO_ESQUERDA,angulo);
}

/********************************
A função EscreverLongaDireita() é responsável por exibir uma string longa na tela de jogo, com alinhamento à direita do valor de X.
A string se expande palavra por palavra até a largura máxima definida (maxLarg). Se ainda houver palavras, elas serão escritas na linha abaixo,
tendo um espaçamento entre as linhas (espacoEntreLinhas) também definido por parâmetro.
Parâmetros:
str (entrada, passagem por referência): string a ser escrita na tela.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usuário deseja começar a escrever a string.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usuário deseja começar a escrever a string.
largMax (entrada, passagem por valor): largura máxima em pixels que pode ser utilizada para escrever as palavras em cada linha do texto. ao atingir esse limite, as palavras seguintes são escritas na linha abaixo.
espacoEntreLinhas (entrada, passagem por valor): distância em pixels entre o valor Y de uma linha e o valor Y da linha abaixo.
cor (entrada, passagem por valor): cor a ser aplicada à fonte no momento da escrita. Essa cor é misturada à cor original da fonte, se essa tiver sido informada na criação da fonte.
numFonte (entrada, passagem por valor): número da fonte a ser utilizada. Caso o usuário não deseje uma fonte especial, será utilizada a fonte padrão (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
angulo (entrada, passagem por valor): ângulo, em graus, para a rotação das strings.
********************************/
void EscreverLongaDireita(char *str, int posicaoX, int posicaoY, int largMax, int espacoEntreLinhas, PIGCor cor=BRANCO, int numFonte=0, float angulo=0){
    CPIGGerenciadorFontes::GetFonte(numFonte)->EscreveLonga(str,posicaoX,posicaoY,largMax,espacoEntreLinhas,cor,PIG_TEXTO_DIREITA,angulo);
}

/********************************
A função EscreverLongaCentralizada() é responsável por exibir uma string longa na tela de jogo, com alinhamento em relação ao valor de X.
A string se expande palavra por palavra até a largura máxima definida (maxLarg). Se ainda houver palavras, elas serão escritas na linha abaixo,
tendo um espaçamento entre as linhas (espacoEntreLinhas) também definido por parâmetro.
Parâmetros:
str (entrada, passagem por referência): string a ser escrita na tela.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usuário deseja começar a escrever a string.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usuário deseja começar a escrever a string.
largMax (entrada, passagem por valor): largura máxima em pixels que pode ser utilizada para escrever as palavras em cada linha do texto. ao atingir esse limite, as palavras seguintes são escritas na linha abaixo.
espacoEntreLinhas (entrada, passagem por valor): distância em pixels entre o valor Y de uma linha e o valor Y da linha abaixo.
cor (entrada, passagem por valor): cor a ser aplicada à fonte no momento da escrita. Essa cor é misturada à cor original da fonte, se essa tiver sido informada na criação da fonte.
numFonte (entrada, passagem por valor): número da fonte a ser utilizada. Caso o usuário não deseje uma fonte especial, será utilizada a fonte padrão (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
angulo (entrada, passagem por valor): ângulo, em graus, para a rotação das strings.
********************************/
void EscreverLongaCentralizada(char *str, int posicaoX, int posicaoY, int largMax, int espacoEntreLinhas, PIGCor cor=BRANCO, int numFonte=0, float angulo=0){
    CPIGGerenciadorFontes::GetFonte(numFonte)->EscreveLonga(str,posicaoX,posicaoY,largMax,espacoEntreLinhas,cor,PIG_TEXTO_CENTRO,angulo);
}

/********************************
A função EscreverInteiroEsquerda() é responsável por exibir um número inteiro na tela de jogo, com alinhamento à esquerda em relação ao valor de X.
Parâmetros:
valor (entrada, passagem por referência): número inteiro a ser escrito na tela.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usuário deseja começar a escrever o número.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usuário deseja começar a escrever o número.
cor (entrada, passagem por valor): cor a ser aplicada à fonte no momento da escrita. Essa cor é misturada à cor original da fonte, se essa tiver sido informada na criação da fonte.
numFonte (entrada, passagem por valor): número da fonte a ser utilizada. Caso o usuário não deseje uma fonte especial, será utilizada a fonte padrão (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
angulo (entrada, passagem por valor): ângulo, em graus, para a rotação do número inteiro.
********************************/
void EscreveInteiroEsquerda(int valor, int x, int y, PIGCor cor=BRANCO, int numFonte=0, float angulo=0){
    stringstream str;
    str<<valor;
    CPIGGerenciadorFontes::GetFonte(numFonte)->Escreve(str.str(),x,y,cor,PIG_TEXTO_ESQUERDA,angulo);
}

/********************************
A função EscreverInteiroDireita() é responsável por exibir um número inteiro na tela de jogo, com alinhamento à direita em relação ao valor de X.
Parâmetros:
valor (entrada, passagem por referência): número inteiro a ser escrito na tela.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usuário deseja começar a escrever o número.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usuário deseja começar a escrever o número.
cor (entrada, passagem por valor): cor a ser aplicada à fonte no momento da escrita. Essa cor é misturada à cor original da fonte, se essa tiver sido informada na criação da fonte.
numFonte (entrada, passagem por valor): número da fonte a ser utilizada. Caso o usuário não deseje uma fonte especial, será utilizada a fonte padrão (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
angulo (entrada, passagem por valor): ângulo, em graus, para a rotação do número inteiro.
********************************/
void EscreveInteiroDireita(int valor, int x, int y, PIGCor cor=BRANCO, int numFonte=0, float angulo=0){
    stringstream str;
    str<<valor;
    CPIGGerenciadorFontes::GetFonte(numFonte)->Escreve(str.str(),x,y,cor,PIG_TEXTO_DIREITA,angulo);
}

/********************************
A função EscreverInteiroCentralizado() é responsável por exibir um número inteiro na tela de jogo, com alinhamento em relação ao valor de X.
Parâmetros:
valor (entrada, passagem por referência): número inteiro a ser escrito na tela.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usuário deseja começar a escrever o número.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usuário deseja começar a escrever o número.
cor (entrada, passagem por valor): cor a ser aplicada à fonte no momento da escrita. Essa cor é misturada à cor original da fonte, se essa tiver sido informada na criação da fonte.
numFonte (entrada, passagem por valor): número da fonte a ser utilizada. Caso o usuário não deseje uma fonte especial, será utilizada a fonte padrão (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
angulo (entrada, passagem por valor): ângulo, em graus, para a rotação do número inteiro.
********************************/
void EscreveInteiroCentralizado(int valor, int x, int y, PIGCor cor=BRANCO, int numFonte=0, float angulo=0){
    stringstream str;
    str<<valor;
    CPIGGerenciadorFontes::GetFonte(numFonte)->Escreve(str.str(),x,y,cor,PIG_TEXTO_CENTRO,angulo);
}

/********************************
A função EscreverDoubleEsquerda() é responsável por exibir um número real na tela de jogo, com alinhamento à esquerda em relação ao valor de X.
Parâmetros:
valor (entrada, passagem por referência): número inteiro a ser escrito na tela.
casas (entrada, passagem por referência): número de casas decimais a ser usado na escrita.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usuário deseja começar a escrever o número.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usuário deseja começar a escrever o número.
cor (entrada, passagem por valor): cor a ser aplicada à fonte no momento da escrita. Essa cor é misturada à cor original da fonte, se essa tiver sido informada na criação da fonte.
numFonte (entrada, passagem por valor): número da fonte a ser utilizada. Caso o usuário não deseje uma fonte especial, será utilizada a fonte padrão (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
angulo (entrada, passagem por valor): ângulo, em graus, para a rotação do número real.
********************************/
void EscreveDoubleEsquerda(double valor, int casas, int x, int y, PIGCor cor=BRANCO, int numFonte=0, float angulo=0){
    stringstream str;
    str.setf(std::ios_base::fixed, std::ios_base::floatfield);
    str<<std::setprecision(casas)<<valor;
    CPIGGerenciadorFontes::GetFonte(numFonte)->Escreve(str.str(),x,y,cor,PIG_TEXTO_ESQUERDA,angulo);
}

/********************************
A função EscreverDoubleDireita() é responsável por exibir um número real na tela de jogo, com alinhamento à direita em relação ao valor de X.
Parâmetros:
valor (entrada, passagem por referência): número inteiro a ser escrito na tela.
casas (entrada, passagem por referência): número de casas decimais a ser usado na escrita.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usuário deseja começar a escrever o número.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usuário deseja começar a escrever o número.
cor (entrada, passagem por valor): cor a ser aplicada à fonte no momento da escrita. Essa cor é misturada à cor original da fonte, se essa tiver sido informada na criação da fonte.
numFonte (entrada, passagem por valor): número da fonte a ser utilizada. Caso o usuário não deseje uma fonte especial, será utilizada a fonte padrão (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
angulo (entrada, passagem por valor): ângulo, em graus, para a rotação do número real.
********************************/
void EscreveDoubleDireita(double valor, int casas, int x, int y, PIGCor cor=BRANCO, int numFonte=0, float angulo=0){
    stringstream str;
    str.setf(std::ios_base::fixed, std::ios_base::floatfield);
    str<<std::setprecision(casas)<<valor;
    CPIGGerenciadorFontes::GetFonte(numFonte)->Escreve(str.str(),x,y,cor,PIG_TEXTO_DIREITA,angulo);
}

/********************************
A função EscreverDoubleCentralizado() é responsável por exibir um número real na tela de jogo, com alinhamento em relação ao valor de X.
Parâmetros:
valor (entrada, passagem por referência): número inteiro a ser escrito na tela.
casas (entrada, passagem por referência): número de casas decimais a ser usado na escrita.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usuário deseja começar a escrever o número.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usuário deseja começar a escrever o número.
cor (entrada, passagem por valor): cor a ser aplicada à fonte no momento da escrita. Essa cor é misturada à cor original da fonte, se essa tiver sido informada na criação da fonte.
numFonte (entrada, passagem por valor): número da fonte a ser utilizada. Caso o usuário não deseje uma fonte especial, será utilizada a fonte padrão (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
angulo (entrada, passagem por valor): ângulo, em graus, para a rotação do número real.
********************************/
void EscreveDoubleCentralizado(double valor, int casas, int x, int y, PIGCor cor=BRANCO, int numFonte=0, float angulo=0){
    stringstream str;
    str.setf(std::ios_base::fixed, std::ios_base::floatfield);
    str<<std::setprecision(casas)<<valor;
    CPIGGerenciadorFontes::GetFonte(numFonte)->Escreve(str.str(),x,y,cor,PIG_TEXTO_CENTRO,angulo);
}

/********************************
A função GetMetricas() recupera as principais métricas de uma letra em um estilo específico.
As métricas incluem as posiçőes mínimas e máximas nos eixos X e Y, onde a letra é desenhada.
Se a fonte não for dinâmica, qualquer valor de estilo passado será descartado e será utilizado o estilo indicado na criação da fonte.
Parâmetros:
letra (entrada, passagem por valor): caractere cuja largura será calculada.
estilo (entrada, passagem por valor): estilo desejado no cálculo da largura. O valor só será utilizado em fontes dinâmicas. Em fontes não-dinâmicas, o valor de estilo será o mesmo do informado na criação da fonte.
numFonte (entrada, passagem por valor): número da fonte a ser utilizada. Caso o usuário não deseje uma fonte especial, será utilizada a fonte padrão (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
retorno:
struct que representa as métricas principais ao escrever a letra.
********************************/
PIGMetricasFonte GetMetricas(char letra, PIGEstilo estilo=PIG_ESTILO_NORMAL, int numFonte=0){
    return CPIGGerenciadorFontes::GetFonte(numFonte)->GetMetricasLetra(letra,estilo);
}

/********************************
A função CalculaLarguraLetra() é responsável por calcular a largura específica de uma letra com um estilo.
Se a fonte não for dinâmica, qualquer valor de estilo passado será descartado e será utilizado o estilo indicado na criação da fonte.
Parâmetros:
letra (entrada, passagem por valor): caractere cuja largura será calculada.
estilo (entrada, passagem por valor): estilo desejado no cálculo da largura. O valor só será utilizado em fontes dinâmicas. Em fontes não-dinâmicas, o valor de estilo será o mesmo do informado na criação da fonte.
numFonte (entrada, passagem por valor): número da fonte a ser utilizada. Caso o usuário não deseje uma fonte especial, será utilizada a fonte padrão (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
retorno:
inteiro que representa o total de pixels (no eixo x) necessários para escrever a letra.
********************************/
int GetLarguraLetra(char letra, PIGEstilo estilo=PIG_ESTILO_NORMAL, int numFonte=0){
    return CPIGGerenciadorFontes::GetFonte(numFonte)->GetLarguraLetra(letra,estilo);
}

/********************************
A função GetTamanhoBaseFonte() é responsável por recuperar o tamanho da fonte informado na criação da mesma.
Parâmetros:
numFonte (entrada, passagem por valor): número da fonte a ser utilizada. Caso o usuário não deseje uma fonte especial, será utilizada a fonte padrão (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
retorno:
inteiro que representa o tamanho base da fonte, ou seja, a quantidade de pixels no eixo Y para desenhar qualquer caractere da fonte (exceto vogais maiúsuclas acentuadas: Á, É, Í, Ó, Ú.
********************************/
int GetTamanhoBaseFonte(int numFonte=0){
    return CPIGGerenciadorFontes::GetFonte(numFonte)->GetTamanhoBaseFonte();
}

/********************************
A função GetFonteDescent() calcula a quantidade de pixels que podem ser utilizados por partes de letras que fiquem abaixo da linha horizontal de base da fonte.
Essa parte inferior é usada para desenhar a cedilha, a parte inferior da letra 'g', 'q', 'y', por exemplo.
Parâmetros:
numFonte (entrada, passagem por valor): número da fonte a ser utilizada. Caso o usuário não deseje uma fonte especial, será utilizada a fonte padrão (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
retorno:
inteiro que representa o total de pixels abaixo da linha horizontal de base da fonte.
********************************/
int GetFonteDescent(int numFonte=0){
    return CPIGGerenciadorFontes::GetFonte(numFonte)->GetFonteDescent();
}

/********************************
A função GetFonteAscent() calcula a quantidade de pixels necessários acima da linha horizontal de base da fonte. Essa medida exclui os pixels utilizados
nas partes inferiores das letras 'g', 'q', 'y', por exemplo. Também não são considerados acentos em vogais maiúsculas como 'Á', 'Ó', 'É', por exemplo.
Parâmetros:
numFonte (entrada, passagem por valor): número da fonte a ser utilizada. Caso o usuário não deseje uma fonte especial, será utilizada a fonte padrão (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
retorno:
inteiro que representa o total de pixels acima da linha horizontal de base da fonte.
********************************/
int GetFonteAscent(int numFonte=0){
    return CPIGGerenciadorFontes::GetFonte(numFonte)->GetFonteAscent();
}

/********************************
A função GetFonteLineSkip() calcula a quantidade de pixels necessários para um espaçamento vertical ideal, ou seja, para que duas frases possam
ser escritas sem se sobreporem verticalmente.
Parâmetros:
numFonte (entrada, passagem por valor): número da fonte a ser utilizada. Caso o usuário não deseje uma fonte especial, será utilizada a fonte padrão (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
retorno:
inteiro que representa o espaçamento vertical ideal para que duas frases não se sobreponham verticalmente.
********************************/
int GetFonteLineSkip(int numFonte=0){
    return CPIGGerenciadorFontes::GetFonte(numFonte)->GetLineSkip();
}

/********************************
A função SubstituiCaractere() substitui a imagem original de um caractere por um frame de um imagem personalizada de um arquivo de imagem. O frame é definido
pelos parâmetros x, y, altura e largura, de acordo com o sistema de coordenadas dos arquivos de imagem digital (eixo Y crescendo para baixo). O frame especificado
será desenhado na tela toda vez que o caractere original for passado dentro de uma string. O frame terá a mesma altura padrão da fote original, mas pdoerá ter uma largura
personalizada por meio do parâmetro largNova.
Parâmetros:
caractere (entrada, passagem por valor): caractere (ou número inteiro) que será substituído e não será mais desenhado posteriormente.
nomeArquivo (entrada, passagem por referência): nome do arquivo contendo o frame desejado.
largNova: (entrada, passagem por valor): largura nova a ser utilizada para desenhar o frame na tela. Não é obrigatoriamente o mesmo valor do parâmetro "larg".
x (entrada, passagem por valor): coordenada X do arquivo de imagem, onde começa o frame desejado.
y (entrada, passagem por valor): coordenada Y do arquivo de imagem, onde começa o frame desejado (sistema de coordenada com eixo Y crescendo para baixo).
altura (entrada, passagem por valor): altura do frame desejado.
largura (entrada, passagem por valor): largura do frame desejado.
numFonte (entrada, passagem por valor): número da fonte a ser utilizada. Caso o usuário não deseje uma fonte especial, será utilizada a fonte padrão (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
retorno:
inteiro que representa o espaçamento vertical ideal para que duas frases não se sobreponham verticalmente.
********************************/
void SubstituiCaractere(char caractere, char *nomeArquivo, int largNova, int x, int y, int altura, int largura, int numFonte=0){
    CPIGGerenciadorFontes::GetFonte(numFonte)->SubstituiGlyph(nomeArquivo,caractere,largNova,x,y,altura,largura);
}




/********************************
Seção de Labels
********************************/

/********************************
A função CriaLabel() é responsável por criar um label. Qualquer label que for necessário,
pode ser criado através dessa função. O label ainda não será desenhado, apenas criado dentro do jogo.
Parâmetros:
texto (entrada, passagem por referência): string que informa o nome texto que será desenhado na tela.
corFonte (entrada, passagem por referência não-obrigatório): indica se há uma cor específica para ser considerada como cor da fonte.
numFonte (entrada, passagem por referência não-obrigatório): indica o número da fonte (já criada) que será utilizada no label.
idJanela (entrada, passagem por valor não-obrigatório): indica qual janela vai receber o label.
Retorno:
inteiro que representa o identificador único do label. Todas as operaçőes subsequentes com este label deverão receber este identificador como parâmetro.
********************************/
int CriaLabel(char* texto, PIGCor corFonte=BRANCO, int numFonte=0, int idJanela=0){
    return CPIGGerenciadorLabels::CriaLabel(texto,corFonte,numFonte,idJanela);
}

/********************************
A função DestroiLabel() é responsável por eliminar o label em questão do jogo.
Parâmetros:
idLabel (entrada, passagem por valor): identificador do label a ser excluído.
********************************/
void DestroiLabel(int idLabel){
    CPIGGerenciadorLabels::DestroiLabel(idLabel);
}

/********************************
A função SetTextoLabel() é responsável por alterar o texto de um label.
Parâmetros:
idLabel (entrada, passagem por valor): identificador do label.
texto (entrada, passagem por referência): indica o novo texto do label.
********************************/
void SetTextoLabel(int idLabel, char *texto){
    CPIGGerenciadorLabels::GetLabel(idLabel)->SetTexto(texto);
}

/********************************
A função GetTextoLabel() é responsável por recuperar o texto de um label.
Parâmetros:
idLabel (entrada, passagem por valor): identificador do label a ser movido.
texto (saída, passagem por referência): texto atual do label.
********************************/
void GetTextoLabel(int idLabel, char *texto){
    strcpy(texto,CPIGGerenciadorLabels::GetLabel(idLabel)->GetTexto().c_str());
}

/********************************
A função GetXYLabel() é responsável recuperar o valor da posição (X,Y) do label de acordo com o sistema de coordenadas do jogo.
Parâmetros:
idLabel (entrada, passagem por valor): identificador do label.
posicaoX (saída, passagem por referencia): indica a posicao no eixo X do label.
posicaoY (saída, passagem por referencia): indica a posicao no eixo Y do label.
********************************/
void GetXYLabel(int idLabel, int *posicaoX, int *posicaoY){
    PIGPonto2D p = CPIGGerenciadorLabels::GetLabel(idLabel)->GetXY();
    *posicaoX = p.x;
    *posicaoY = p.y;
}

/********************************
A função MoveLabel() é responsável por movimentar um determinado label para uma nova posição informada.
Parâmetros:
idLabel (entrada, passagem por valor): identificador do label a ser movido.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usuário deseja reposicionar o label.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usuário deseja reposicionar o label.
********************************/
void MoveLabel(int idLabel, int posicaoX, int posicaoY){
    CPIGGerenciadorLabels::GetLabel(idLabel)->Move(posicaoX,posicaoY);
}

/********************************
A função DeslocaLabel() é responsável por deslocar um determinado label em relação à sua posição atual.
Parâmetros:
idLabel (entrada, passagem por valor): identificador do label a ser movido.
deltaX (entrada, passagem por valor): valor a ser somado ou subtraído na componente X da posição do label.
deltaY (entrada, passagem por valor): valor a ser somado ou subtraído na componente Y da posição do label.
********************************/
void DeslocaLabel(int idLabel, int deltaX, int deltaY){
    CPIGGerenciadorLabels::GetLabel(idLabel)->Desloca(deltaX,deltaY);
}

/********************************
A função SetAnguloLabel() é responsável pela angulação de determinado label. A angulação é calculada em sentido
horário a partir do eixo X (0 graus). O label será desenhado com a angulação informada no próximo comando
DesenhaLabel().
Parâmetros:
idLabel (entrada, passagem por valor): identificador do label.
angulo (entrada, passagem por valor): valor para indicar a angulação do label em graus.
********************************/
void SetAnguloLabel(int idLabel, float angulo){
    CPIGGerenciadorLabels::GetLabel(idLabel)->SetAngulo(angulo);
}

/********************************
A função GetAnguloLabel() é responsável por recuperar o ângulo de rotação de determinado label. A angulação é calculada em sentido
horário a partir do eixo X (0 graus). O label será desenhado com a angulação informada no próximo comando
DesenhaLabel().
Parâmetros:
idLabel (entrada, passagem por valor): identificador do label.
Retorno:
Retorna o valor do ângulo em graus.
********************************/
float GetAnguloLabel(int idLabel){
    return CPIGGerenciadorLabels::GetLabel(idLabel)->GetAngulo();
}

/********************************
A função SetPivoAbsolutoLabel() define um ponto (X,Y) em relação ao ponto (0,0) do label, sobre o qual o label será
rotacionado quando a função SetAnguloLabel() for executada.
Parâmetros:
idLabel (entrada, passagem por valor): identificador do label.
posicaoX (entrada, passagem por valor): Valor da coordenada X do pivô em relação ao ponto (0,0) do label.
posicaoY (entrada, passagem por valor): Valor da coordenada Y do pivô em relação ao ponto (0,0) do label.
********************************/
void SetPivoAbsolutoLabel(int idLabel, int posicaoX, int posicaoY){
    CPIGGerenciadorLabels::GetLabel(idLabel)->SetPivoAbsoluto({(double)posicaoX,(double)posicaoY});
}

/********************************
A função SetPivoProporcionalLabel() define um ponto (X,Y) proporcional ao tamanho do label, sobre o qual o label será
rotacionado quando a função SetAnguloLabel() for executada.
Parâmetros:
idLabel (entrada, passagem por valor): identificador do label.
relX (entrada, passagem por valor): porcentagem da largura do label onde ficará o pivô.
relY (entrada, passagem por valor): porcentagem da altura do label onde ficará o pivô.
********************************/
void SetPivoProporcionalLabel(int idLabel, float relX, float relY){
    CPIGGerenciadorLabels::GetLabel(idLabel)->SetPivoProporcional({relX,relY});
}

/********************************
A função GetPivoLabel() define um ponto (X,Y) em relação ao ponto (0,0) do label, sobre o qual o label será
rotacionado quando a função SetAnguloLabel() for executada.
Parâmetros:
idLabel (entrada, passagem por valor): identificador do label.
posicaoX (saída, passagem por referência): Valor da coordenada X do pivô em relação ao ponto (0,0) do label.
posicaoY (saída, passagem por referência): Valor da coordenada Y do pivô em relação ao ponto (0,0) do label.
********************************/
void GetPivoLabel(int idLabel, int *posicaoX, int *posicaoY){
    PIGPonto2D p = CPIGGerenciadorLabels::GetLabel(idLabel)->GetPivo();
    *posicaoX = p.x;
    *posicaoY = p.y;
}

/********************************
A função SetFlipLabel() é responsável por virar o label, invertendo-o em alguma direção. O label somente será
desenhado na nova orientação no próximo comando DesenhaLabel().
Parâmetros:
idLabel (entrada, passagem por valor): identificador do label a ser virado.
valor (entrada, passagem por valor): valor do tipo de Flip. Pode ser FLIP_NENHUM (nenhum tipo de inversão),
PIG_FLIP_HORIZONTAL (inverte da esquerda para a direita), PIG_FLIP_VERTICAL (inverte de cima para baixo),
ou PIG_FLIP_HORIZ_VERT (inverte da esquerda para direita e de cima para baixo).
********************************/
void SetFlipLabel(int idLabel, PIGFlip valor){
    CPIGGerenciadorLabels::GetLabel(idLabel)->SetFlip(valor);
}

/********************************
A função GetFlipLabel() é responsável por recuperar o valor da manipulação causada pela função SetFlipLabel().
Parâmetros:
idLabel (entrada, passagem por valor): identificador do label a ser virado.
Retorno:
inteiro que indica o tipo de Flip. Pode ser PIG_FLIP_NENHUM (nenhum tipo de inversão),
PIG_FLIP_HORIZONTAL (inverte da esquerda para a direita), PIG_FLIP_VERTICAL (inverte de cima para baixo),
ou PIG_FLIP_HORIZ_VERT (inverte da esquerda para direita e de cima para baixo).
********************************/
PIGFlip GetFlipLabel(int idLabel){
    return CPIGGerenciadorLabels::GetLabel(idLabel)->GetFlip();
}

/********************************
A função GetDimensoesLabel() é responsável por recuperar a altura e a largura da área a ser usada
para desenhar o label na tela. Em outras palavras, representa o tamanho atual do label.
Parâmetros:
idLabel (entrada, passagem por valor): identificador do label.
altura (saída, passagem por referência): altura atual em pixels do label.
largura (saída, passagem por referência): largura atual em pixels do label.
********************************/
void GetDimensoesLabel(int idLabel, int *altura, int *largura){
    CPIGGerenciadorLabels::GetLabel(idLabel)->GetDimensoes(*altura,*largura);
}

/********************************
A função SetCorFonteLabel() é responsável por definir a cor da fonte do label.
Parâmetros:
idLabel (entrada, passagem por valor): identificador do label a ser desenhado.
cor (entrada,passagem por valor): cor do sistema RGB utilizada para a fonte do label.
********************************/
void SetCorFonteLabel(int idLabel, PIGCor cor){
    CPIGGerenciadorLabels::GetLabel(idLabel)->SetCorFonte(cor);
}

/********************************
A função GetCorFonteLabel() é responsável por recuperar a cor da fonte utilizada no label
Parâmetros:
idLabel (entrada, passagem por valor): identificador do label a ser desenhado.
Retorno:
PIGCor que indica a cor utilizada pela fonte do label.
********************************/
PIGCor GetCorFonteLabel(int idLabel){
    return CPIGGerenciadorLabels::GetLabel(idLabel)->GetCorFonte();
}

/********************************
A função SetNumeroFonteLabel() é responsável por modificar a fonte utilizada pelo label. O número da fonte deve corresponder ao identificador de uma fonte já criada anteriormente.
Parâmetros:
idLabel (entrada, passagem por valor): identificador do label a ser desenhado.
numFonte (entrada,passagem por valor): identificador da fonte a ser utilizada.
********************************/
void SetNumeroFonteLabel(int idLabel, int numFonte){
    CPIGGerenciadorLabels::GetLabel(idLabel)->SetFonte(numFonte);
}

/********************************
A função GetNumeroFonteLabel() é responsável por recuperar o identificador da fonte utilizada pelo label.
Parâmetros:
idLabel (entrada, passagem por valor): identificador do label a ser desenhado.
Retorno:
inteiro com o valor do identificador da fonte utilizada no label.
********************************/
int GetNumeroFonteLabel(int idLabel){
    return CPIGGerenciadorLabels::GetLabel(idLabel)->GetFonte();
}

/********************************
A função SetOpacidadeLabel() é responsável por modificar o nível de opacidade do label.
O nível de opacidade varia de 0-255, sendo 0 totalmente transparente e 255 totalmente opaco.
Parâmetros:
idLabel (entrada, passagem por valor): identificador do label.
valor (entrada,passagem por valor): nível de opacidade do label na faixa 0-255.
********************************/
void SetOpacidadeLabel(int idLabel, int valor){
    CPIGGerenciadorLabels::GetLabel(idLabel)->SetOpacidade(valor);
}

/********************************
A função GetOpacidadeLabel() é responsável por recuperar o nível de opacidade de determinado label.
O nível de opacidade varia de 0-255, sendo 0 totalmente transparente e 255 totalmente opaco.
Parâmetros:
idLabel (entrada, passagem por valor): identificador do label.
Retorno:
Retorna o nível de opacidade do label na faixa 0-255.
********************************/
int GetOpacidadeLabel(int idLabel){
    return CPIGGerenciadorLabels::GetLabel(idLabel)->GetOpacidade();
}

/********************************
A função DesenhaLabel() é responsável por desenhar um label na tela. O label será desenhado de acordo com todas as definiçőes
de posição e ângulo informado até o momento. Além disso, se o label estiver virado (flipping), isso também será levado em consideração.
Parâmetros:
idLabel (entrada, passagem por valor): identificador do label a ser desenhado.
********************************/
void DesenhaLabel(int idLabel){
    CPIGGerenciadorLabels::GetLabel(idLabel)->Desenha();
}


/********************************
Seção de sprites
********************************/

/********************************
A função CriaSprite() é responsável por criar um sprite. Qualquer sprite que for necessário,
pode ser criado através dessa função. O sprite ainda não será desenhado, apenas criado dentro do jogo.
Parâmetros:
nomeArquivo (entrada, passagem por referência): string que informa o nome do arquivo da imagem do sprite a ser criado.
retiraFundo (entrada, passagem por valor): inteiro que indica se o fundo da imagem deve ser retirado ou não ao ler o arquivo em questão. O valor padrão é 1, indicando que o fundo deve ser retirado.
corFundo (entrada, passagem por referência não-obrigatório): indica se há uma cor específica para ser considerada como cor de fundo da imagem. Caso, o valor seja NULL, mas o parâmetro retiraFundo seja diferente de 0, o pixel (0,0) da imagem será considerado como cor de fundo.
idJanela (entrada, passagem por valor não-obrigatório): indica qual janela vai receber o sprite.
Retorno:
inteiro que representa o identificador único do sprite. Todas as operaçőes subsequentes com este sprite deverão receber este identificador como parâmetro.
********************************/
int CriaSprite(char* nomeArquivo, int retiraFundo=1, PIGCor *corFundo=NULL, int idJanela=0){
    return CPIGGerenciadorSprites::CriaSprite(nomeArquivo,retiraFundo,corFundo,idJanela);
}

/********************************
A função CriaSprite() é responsável por criar um sprite. Qualquer sprite que for necessário,
pode ser criado através dessa função. O sprite ainda não será desenhado, apenas criado dentro do jogo.
Parâmetros:
idSprite(entrada, passagem por valor): identificador do sprite original que será copiado.
retiraFundo (entrada, passagem por valor): inteiro que indica se o fundo da imagem deve ser retirado ou não ao ler o arquivo em questão. O valor padrão é 1, indicando que o fundo deve ser retirado.
corFundo (entrada, passagem por referência não-obrigatório): indica se há uma cor específica para ser considerada como cor de fundo da imagem. Caso, o valor seja NULL, mas o parâmetro retiraFundo seja diferente de 0, o pixel (0,0) da imagem será considerado como cor de fundo.
idJanela (entrada, passagem por valor não-obrigatório): indica qual janela vai receber o sprite.
Retorno:
inteiro que representa o identificador único do sprite. Todas as operaçőes subsequentes com este sprite deverão receber este identificador como parâmetro.
********************************/
int CriaSprite(int idSprite, int retiraFundo=1, PIGCor *corFundo=NULL, int idJanela=0){
    return CPIGGerenciadorSprites::CriaSprite(idSprite,retiraFundo,corFundo,idJanela);
}

/********************************
A função CriaSpriteOffScreen() é responsável por criar um sprite a partir da imagem que está sendo montanda pelo
renderizador Offscreen. O renderizador precisa ter sido preparado anteriormente.
Parâmetros:
retiraFundo (entrada, passagem por valor): inteiro que indica se o fundo da imagem deve ser retirado ou não ao ler o arquivo em questão. O valor padrão é 1, indicando que o fundo deve ser retirado.
corFundo (entrada, passagem por referência não-obrigatório): indica se há uma cor específica para ser considerada como cor de fundo da imagem. Caso, o valor seja NULL, mas o parâmetro retiraFundo seja diferente de 0, o pixel (0,0) da imagem será considerado como cor de fundo.
Retorno:
inteiro que representa o identificador único do sprite. Todas as operaçőes subsequentes com este sprite deverão receber este identificador como parâmetro.
********************************/
int CriaSpriteOffScreen(int retiraFundo=1, PIGCor *corFundo=NULL){
    return CPIGGerenciadorSprites::CriaSpriteOffScreen(jogo->GetOffScreenRender(),retiraFundo,corFundo);
}

/********************************
A função DestroiSprite() é responsável por eliminar o sprite em questão do jogo.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite a ser excluído.
********************************/
void DestroiSprite(int idSprite){
    CPIGGerenciadorSprites::DestroiSprite(idSprite);
}

/********************************
A função CarregaArquivoFramesSprite() é responsável por ler de arquivo texto os frames de um sprite.
Cada linha do arquivo texto deve conter 5 números inteiros: o número do frame, a posição do frame no eixo X do arquivo de imagem,
a posição do frame no eixo Y do arquivo de imagem, a altura do frame e a largura do frame (todas as unidades em pixels).
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
nomeArq (entrada, passagem por referência): nome do arquivo texto contendo os frames.
********************************/
void CarregaArquivoFramesSprite(int idSprite, char *nomeArq){
    CPIGGerenciadorSprites::GetSprite(idSprite)->CarregaArquivoFrames(nomeArq);
}

/********************************
A função CarregaFramesPorLinhaSprite() é responsável por subdividir o arquivo de imagem em linhas (de mesmo tamanho) e colunas (de mesmo tamanho).
Cada subdivisão representará um frame que será automaticamente criado para a animação, com numeração incremental a partir do parâmetro "frameInicial".
Ao final das "qtdColunas" da primeira linha, a definição dos frames continua na linha inferior.
A função pode ser utilizada em spritesheets regulares.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
frameInicial (entrada, passagem por valor): numeração do primeiro frame a ser criado pela função. Os demais frames terão numeração consecutiva.
qtdLinhas (entrada, passagem por valor): quantidade de linhas na qual o arquivo de imagem será dividido.
qtdColunas (entrada, passagem por valor): quantidade de colunas na qual o arquivo de imagem será dividido.
********************************/
void CarregaFramesPorLinhaSprite(int idSprite, int frameInicial, int qtdLinhas, int qtdColunas){
    CPIGGerenciadorSprites::GetSprite(idSprite)->CriaFramesAutomaticosPorLinha(frameInicial,qtdLinhas,qtdColunas);
}

/********************************
A função CarregaFramesPorColunaSprite() é responsável por subdividir o arquivo de imagem em linhas (de mesmo tamanho) e colunas (de mesmo tamanho).
Cada subdivisão representará um frame que será automaticamente criado para a animação, com numeração incremental a partir do parâmetro "frameInicial".
Ao final das "qtdLinhas" da primeira coluna, a definição dos frames continua na coluna seguinte.
A função pode ser utilizada em spritesheets regulares.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
frameInicial (entrada, passagem por valor): numeração do primeiro frame a ser criado pela função. Os demais frames terão numeração consecutiva.
qtdLinhas (entrada, passagem por valor): quantidade de linhas na qual o arquivo de imagem será dividido.
qtdColunas (entrada, passagem por valor): quantidade de colunas na qual o arquivo de imagem será dividido.
********************************/
void CarregaFramesPorColunaSprite(int idSprite, int frameInicial, int qtdLinhas, int qtdColunas){
    CPIGGerenciadorSprites::GetSprite(idSprite)->CriaFramesAutomaticosPorColuna(frameInicial,qtdLinhas,qtdColunas);
}

/********************************
A função GetXYSprite() é responsável recuperar o valor da posição (X,Y) do sprite de acordo com o sistema de coordenadas do jogo.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
posicaoX (saída, passagem por referencia): indica a posicao no eixo X do sprite.
posicaoY (saída, passagem por referencia): indica a posicao no eixo Y do sprite.
********************************/
void GetXYSprite(int idSprite, int *posicaoX, int *posicaoY){
    PIGPonto2D p = CPIGGerenciadorSprites::GetSprite(idSprite)->GetXY();
    *posicaoX = p.x;
    *posicaoY = p.y;
}

/********************************
A função MoveSprite() é responsável por movimentar um determinado sprite para uma nova posição informada.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite a ser movido.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usuário deseja reposicionar o sprite.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usuário deseja reposicionar o sprite.
********************************/
void MoveSprite(int idSprite, int posicaoX, int posicaoY){
    CPIGGerenciadorSprites::GetSprite(idSprite)->Move(posicaoX,posicaoY);
}

/********************************
A função DeslocaSprite() é responsável por deslocar um determinado sprite em relação à sua posição atual.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite a ser movido.
deltaX (entrada, passagem por valor): valor a ser somado ou subtraído na componente X da posição do sprite.
deltaY (entrada, passagem por valor): valor a ser somado ou subtraído na componente Y da posição do sprite.
********************************/
void DeslocaSprite(int idSprite, int deltaX, int deltaY){
    CPIGGerenciadorSprites::GetSprite(idSprite)->Desloca(deltaX,deltaY);
}

/********************************
A função SetAnguloSprite() é responsável pela angulação de determinado sprite. A angulação é calculada em sentido
horário a partir do eixo X (0 graus). O sprite será desenhado com a angulação informada no próximo comando
DesenhaSprite().
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
angulo (entrada, passagem por valor): valor para indicar a angulação do sprite em graus.
********************************/
void SetAnguloSprite(int idSprite, float angulo){
    CPIGGerenciadorSprites::GetSprite(idSprite)->SetAngulo(angulo);
}

/********************************
A função GetAnguloSprite() é responsável por recuperar o ângulo de rotação de determinado sprite. A angulação é calculada em sentido
horário a partir do eixo X (0 graus). O sprite será desenhado com a angulação informada no próximo comando
DesenhaSprite().
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
Retorno:
Retorna o valor do ângulo em graus.
********************************/
float GetAnguloSprite(int idSprite){
    return CPIGGerenciadorSprites::GetSprite(idSprite)->GetAngulo();
}

/********************************
A função SetPivoAbsolutoSprite() define um ponto (X,Y) em relação ao ponto (0,0) do sprite, sobre o qual o sprite será
rotacionado quando a função SetAnguloSprite() for executada.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
posicaoX (entrada, passagem por valor): Valor da coordenada X do pivô em relação ao ponto (0,0) do sprite.
posicaoY (entrada, passagem por valor): Valor da coordenada Y do pivô em relação ao ponto (0,0) do sprite.
********************************/
void SetPivoAbsolutoSprite(int idSprite, int posicaoX, int posicaoY){
    CPIGGerenciadorSprites::GetSprite(idSprite)->SetPivoAbsoluto({(double)posicaoX,(double)posicaoY});
}

/********************************
A função SetPivoProporcionalSprite() define um ponto (X,Y) proporcional ao tamanho do sprite, sobre o qual o sprite será
rotacionado quando a função SetAnguloSprite() for executada.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
relX (entrada, passagem por valor): porcentagem da largura do sprite onde ficará o pivô.
relY (entrada, passagem por valor): porcentagem da altura do sprite onde ficará o pivô.
********************************/
void SetPivoProporcionalSprite(int idSprite, float relX, float relY){
    CPIGGerenciadorSprites::GetSprite(idSprite)->SetPivoProporcional({relX,relY});
}

/********************************
A função GetPivoSprite() define um ponto (X,Y) em relação ao ponto (0,0) do sprite, sobre o qual o sprite será
rotacionado quando a função SetAnguloSprite() for executada.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
posicaoX (saída, passagem por referência): Valor da coordenada X do pivô em relação ao ponto (0,0) do sprite.
posicaoY (saída, passagem por referência): Valor da coordenada Y do pivô em relação ao ponto (0,0) do sprite.
********************************/
void GetPivoSprite(int idSprite, int *posicaoX, int *posicaoY){
    PIGPonto2D p = CPIGGerenciadorSprites::GetSprite(idSprite)->GetPivo();
    *posicaoX = p.x;
    *posicaoY = p.y;
}

/********************************
A função SetFlipSprite() é responsável por virar o sprite, invertendo-o em alguma direção. O sprite somente será
desenhado na nova orientação no próximo comando DesenhaSprite().
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite a ser virado.
valor (entrada, passagem por valor): valor do tipo de Flip. Pode ser FLIP_NENHUM (nenhum tipo de inversão),
PIG_FLIP_HORIZONTAL (inverte da esquerda para a direita), PIG_FLIP_VERTICAL (inverte de cima para baixo),
ou PIG_FLIP_HORIZ_VERT (inverte da esquerda para direita e de cima para baixo).
********************************/
void SetFlipSprite(int idSprite, PIGFlip valor){
    CPIGGerenciadorSprites::GetSprite(idSprite)->SetFlip(valor);
}

/********************************
A função GetFlipSprite() é responsável por recuperar o valor da manipulação causada pela função SetFlipSprite().
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite a ser virado.
Retorno:
inteiro que indica o tipo de Flip. Pode ser PIG_FLIP_NENHUM (nenhum tipo de inversão),
PIG_FLIP_HORIZONTAL (inverte da esquerda para a direita), PIG_FLIP_VERTICAL (inverte de cima para baixo),
ou PIG_FLIP_HORIZ_VERT (inverte da esquerda para direita e de cima para baixo).
********************************/
PIGFlip GetFlipSprite(int idSprite){
    return CPIGGerenciadorSprites::GetSprite(idSprite)->GetFlip();
}

/********************************
A função SetDimensoesSprite() é responsável por delimitar a altura e a largura do sprite que será desenhado na tela,
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
A função GetDimensoesSprite() é responsável por recuperar a altura e a largura da área a ser usada
para desenhar o sprite na tela. Em outras palavras, representa o tamanho atual do sprite.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
altura (saída, passagem por referência): altura atual em pixels do sprite.
largura (saída, passagem por referência): largura atual em pixels do sprite.
********************************/
void GetDimensoesSprite(int idSprite, int *altura, int *largura){
    CPIGGerenciadorSprites::GetSprite(idSprite)->GetDimensoes(*altura,*largura);
}

/********************************
A função GetDimensoesOriginaisSprite() é responsável por recuperar a altura e a largura originais da imagem
que foi usada para criar o sprite. Qualquer utilização da função SetDimensoesSprite() é ignorada para
o cálculo desta função.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
altura (saída, passagem por referência): altura original em pixels do sprite.
largura (saída, passagem por referência): largura original em pixels do sprite.
********************************/
void GetDimensoesOriginaisSprite(int idSprite, int *altura, int *largura){
    CPIGGerenciadorSprites::GetSprite(idSprite)->GetDimensoesOriginais(*altura,*largura);
}

/********************************
A função RestauraDimensoesOriginaisSprite() é responsável por restaurar o sprite com o tamanho original da image.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
********************************/
void RestauraDimensoesOriginaisSprite(int idSprite, int altura, int largura){
    CPIGGerenciadorSprites::GetSprite(idSprite)->RestauraDimensoesOriginais();
}

/********************************
A função CriaFrameSprite() é responsável por delimitar o posicionamento dos pixels do arquivo de imagem que serão
utilizados para representar o sprite na tela. Desta forma, nem toda a imagem será automaticamente utilizada para
representar o sprite. O sistema de coordenadas deve ser o padrão dos arquivos de imagem, com o eixo Y aumentando para baixo.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite a ser desenhado.
idFrame (entrada, passagem por valor): identificador do frame a ser criado.
xBitmap (entrada, passagem por valor): indica a posição de eixo X onde começa o frame.
yBitmap (entrada, passagem por valor): indica a posição de eixo Y onde começa o frame. Neste caso, o eixo Y aumenta para baixo.
altura (entrada, passagem por valor): altura em pixels do frame.
largura (entrada, passagem por valor): largura em pixels do frame.
********************************/
void CriaFrameSprite(int idSprite, int idFrame, int xBitmap, int yBitmap, int altura, int largura){
    CPIGGerenciadorSprites::GetSprite(idSprite)->DefineFrame(idFrame, {xBitmap,yBitmap,largura,altura});
}

/********************************
A função MudaFrameSprite() é responsável por modificar o frame (já definido pela função DefineFrameSprite) de um sprite
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
idFrame (entrada, passagem por valor): identificador do frame já criado.
Retorno:
Se o identifador do frame informado não corresponder a um frame já criado, o valor de retorno é igual a 0. Caso contrário, é igual a 1.
********************************/
int MudaFrameSprite(int idSprite, int idFrame){
    return CPIGGerenciadorSprites::GetSprite(idSprite)->MudaFrameAtual(idFrame);
}

/********************************
A função GetFrameAtualSprite() recupera o valor do frame atual exibido no sprite.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
Retorno:
Número do frame atual do sprite.
********************************/
int GetFrameAtualSprite(int idSprite){
    return CPIGGerenciadorSprites::GetSprite(idSprite)->GetFrameAtual();
}

/********************************
A função SetColoracaoSprite() é responsável por mesclar uma determinada cor com os pixels do arquivo de imagem.
Após a modificação, todos os desenhos deste sprite serão mostrados já com a mesclagem definida.
Para voltar ao padrão original de pixels, deve-se chamar a função, passando a cor branca (255,255,255,255).
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite a ser desenhado.
cor (entrada,passagem por valor): cor do sistema RGB utilizada para mesclagem com o arquivo de imagem
********************************/
void SetColoracaoSprite(int idSprite, PIGCor cor){
    CPIGGerenciadorSprites::GetSprite(idSprite)->SetColoracao(cor);
}

/********************************
A função SetOpacidadeSprite() é responsável por modificar o nível de opacidade do sprite.
O nível de opacidade varia de 0-255, sendo 0 totalmente transparente e 255 totalmente opaco.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
valor (entrada,passagem por valor): nível de opacidade do sprite na faixa 0-255.
********************************/
void SetOpacidadeSprite(int idSprite, int valor){
    CPIGGerenciadorSprites::GetSprite(idSprite)->SetOpacidade(valor);
}

/********************************
A função GetOpacidadeSprite() é responsável por recuperar o nível de opacidade de determinado sprite.
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
A função DesenhaSprite() é responsável por desenhar um sprite na tela. O sprite será desenhado de acordo com todas as definiçőes
de posição e ângulo informado até o momento. Além disso, se o sprite estiver virado (flipping), isso também será levado em consideração.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite a ser desenhado.
********************************/
void DesenhaSprite(int idSprite){
    CPIGGerenciadorSprites::GetSprite(idSprite)->Desenha();
}

/********************************
A função DesenhaSpriteOffScreen() é responsável por desenhar um sprite no Renderizador Offscreen. O sprite será desenhado de acordo com todas as definiçőes
de posição e ângulo informado até o momento. Além disso, se o sprite estiver virado (flipping), isso também será levado em consideração.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite a ser desenhado.
********************************/
void DesenhaSpriteOffScreen(int idSprite){
    CPIGGerenciadorSprites::GetSprite(idSprite)->DesenhaOffScreen(jogo->GetOffScreenRender());
}

/********************************
A função DesenhaSpriteSimples() é responsável por desenhar um sprite na tela, a partir do nome do arquivo apenas. O sprite será desenhado contendo toda a imagem, na posição indica.
Não será aplicada nenhuma modificação, como ângulo, coloração, ou opacidade, por exemplo.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite a ser desenhado.
********************************/
void DesenhaSpriteSimples(char *nomeArq, int x, int y, int retiraFundo=1, int idJanela=0){
    CPIGGerenciadorSprites::DesenhaSprite(nomeArq, x, y, retiraFundo,idJanela);
}

/********************************
A função InsereTransicaoSprite() é responsável por criar e inserir uma nova transição ao final de sequência de transiçőes do sprite.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
tempo (entrada, passagem por valor): duracao (em segundos) da transição.
deltaX (entrada, passagem por valor): diferença da posição no eixo X em relação à posição do sprite no início da transição.
deltaY (entrada, passagem por valor): diferença da posição no eixo Y em relação à posição do sprite no início da transição.
deltaAltura (entrada, passagem por valor): diferença da altura do sprite em relação ao início da transição.
deltaLargura (entrada, passagem por valor): diferença da largura do sprite em relação ao início da transição.
deltaAngulo (entrada, passagem por valor): diferença de ângulo (em graus) do sprite em relação ao início da transição.
corFinal (entrada, passagem por valor): coloração do sprite ao final da transição.
deltaOpacidade (entrada, passagem por valor): diferença do nível de opacidade do sprite em relação ao início da transição.
********************************/
void InsereTransicaoSprite(int idSprite, double tempo, int deltaX, int deltaY, int deltaAltura, int deltaLargura, double deltaAngulo, PIGCor corFinal, int deltaOpacidade){
    CPIGGerenciadorSprites::GetSprite(idSprite)->InsereTransicao(tempo,{deltaX,deltaY,deltaAltura,deltaLargura,deltaAngulo,corFinal,deltaOpacidade});
}

/********************************
A função ExecutandoTransicaoSprite() retorna a informação sobre a execução (neste momento) de transiçőes do sprite.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
Retorno:
inteiro que indica se o sprite está executando alguma transição no momento (valor diferente de 0) ou não (valor igual a 0).
********************************/
int ExecutandoTransicaoSprite(int idSprite){
    return CPIGGerenciadorSprites::GetSprite(idSprite)->ExecutandoTransicao();
}

/********************************
A função LeArquivoTransicaoSprite() é responsável por ler, criar e inserir as transiçőes para um sprite, provenientes de um arquivo texto.
Cada linha do arquivo texto corresponde a uma transição (em ordem) e deve possuir 11 valores:
1) um double representando a duracao (em segundos) da transição.
2) um inteiro repreentando a diferença da posição no eixo X em relação à posição do sprite no início da transição.
3) um inteiro repreentando a diferença da posição no eixo Y em relação à posição do sprite no início da transição.
4) um inteiro repreentando a diferença da altura do sprite em relação ao início da transição.
5) um inteiro repreentando a diferença da largura do sprite em relação ao início da transição.
6) um double repreentando a diferença de ângulo (em graus) do sprite em relação ao início da transição.
7) um inteiro repreentando a componente R (vermelho) da coloração do sprite ao final da transição.
8) um inteiro repreentando a componente G (verde) da coloração do sprite ao final da transição.
9) um inteiro repreentando a componente B (azul) da coloração do sprite ao final da transição.
10) um inteiro repreentando a componente A (canal alfa) da coloração do sprite ao final da transição.
11) um inteiro repreentando a diferença do nível de opacidade do sprite em relação ao início da transição.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
nomeArq (entrada, passagem por referência): nome com extensão do arquivo texto contendo as transiçőes.
********************************/
void LeArquivoTransicaoSprite(int idSprite, char *nomeArq){
    CPIGGerenciadorSprites::GetSprite(idSprite)->LeTransicoes(nomeArq);
}

/********************************
A função IniciaAutomacaoSprite() é responsável por iniciar as transiçőes já inseridas no sprite, de acordo como o tipo de transição informada.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
********************************/
void IniciaAutomacaoSprite(int idSprite){
    CPIGGerenciadorSprites::GetSprite(idSprite)->IniciaAutomacao();
}

/********************************
A função TrataAutomacaoSprite() é responsável por calcular o estado da transição corrente do sprite e aplicar essas modificação a ela.
A função deve ser chamada a cada frame, para ter resultados mais precisos.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
********************************/
void TrataAutomacaoSprite(int idSprite){
    CPIGGerenciadorSprites::GetSprite(idSprite)->TrataAutomacao();
}

/********************************
A função PausaAutomacaoSprite() é responsável por pausar as transiçőes e açőes associadas a um sprite.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
********************************/
void PausaAutomacaoSprite(int idSprite){
    CPIGGerenciadorSprites::GetSprite(idSprite)->PausaAutomacao();
}

/********************************
A função DespausaAutomacaoSprite() é responsável por despausar as transiçőes e açőes associadas a um sprite.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
********************************/
void DespausaAutomacaoSprite(int idSprite){
    CPIGGerenciadorSprites::GetSprite(idSprite)->DespausaAutomacao();
}

/********************************
A função DefineTipoTransicaoSprite() é responsável por determinar como a sequência de transiçőes será executada.
É possível fazê-la uma única vez (PIG_TRANSICAO_NORMAL), em loop (PIG_TRANSICAO_LOOP) ou indo até o final da sequência e retornando, em vai-vém (PIG_TRANSICAO_VAIVEM).
A função deve ser chamada a cada frame, para ter resultados mais precisos.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
********************************/
void DefineTipoTransicaoSprite(int idSprite, PIGTipoTransicao valor){
    CPIGGerenciadorSprites::GetSprite(idSprite)->DefineTipoTransicao(valor);
}

/********************************
A função LimpaTransicoesSprite() é responsável por remover a sequência de transiçőes do sprite.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
********************************/
void LimpaTransicoesSprite(int idSprite){
    CPIGGerenciadorSprites::GetSprite(idSprite)->LimpaTransicoes();
}

/********************************
A função InsereAcaoSprite() é responsável por inserir na linha de tempo de automação do sprite uma ação a ser executada.
A ação é composta por uma função "acao" que será executada quando a linha de tempo atingir o parâmetro "tempo" e será repetida a cada "repeticao" segundos.
A ação pode armazenar um ponteiro genérico "param" que será utilizado na chamada da função.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
tempo (entrada, passagem por valor): tempo (em segundos) da primeira chamada da função.
repeticao (entrada, passagem por valor): tempo (em segundos) entre a chamada anterior e a próxima. O valor -1 indica que a função não será repetida.
param (entrada, passagem por referência): ponteiro genérico para um valor que será utilizado na chamada da função.
********************************/
void InsereAcaoSprite(int idSprite, double tempo, double repeticao, PIGFuncaoSimples acao, void *param){
    CPIGGerenciadorSprites::GetSprite(idSprite)->InsereAcao(tempo,repeticao,acao,param);
}

/********************************
A função LimpaAcoesSprite() é responsável por remover as açőes restantes associadas ao sprite.
Parâmetros:
idSprite (entrada, passagem por valor): identificador do sprite.
********************************/
void LimpaAcoesSprite(int idSprite){
    CPIGGerenciadorSprites::GetSprite(idSprite)->LimpaAcoes();
}


/********************************
Seção de objetos
********************************/

/********************************
A função CriaObjeto() é responsável por criar um objeto. Qualquer objeto que for necessário,
pode ser criado através dessa função. O objeto ainda não será desenhado, apenas criado dentro do jogo.
Parâmetros:
nomeArquivo (entrada, passagem por referência): string que informa o nome do arquivo da imagem do objeto a ser criado.
retiraFundo (entrada, passagem por valor): inteiro que indica se o fundo da imagem deve ser retirado ou não ao ler o arquivo em questão. O valor padrão é 1, indicando que o fundo deve ser retirado.
corFundo (entrada, passagem por referência não-obrigatório): indica se há uma cor específica para ser considerada como cor de fundo da imagem. Caso, o valor seja NULL, mas o parâmetro retiraFundo seja diferente de 0, o pixel (0,0) da imagem será considerado como cor de fundo.
idJanela (entrada, passagem por valor não-obrigatório): indica qual janela vai receber o objeto.
Retorno:
inteiro que representa o identificador único do objeto. Todas as operaçőes subsequentes com este objeto deverão receber este identificador como parâmetro.
********************************/
int CriaObjeto(char* nomeArquivo, int retiraFundo=1, PIGCor *corFundo=NULL, int idJanela=0){
    return CPIGGerenciadorSprites::CriaObjeto(nomeArquivo,retiraFundo,corFundo,idJanela);
}

/********************************
A função CriaObjeto() é responsável por criar um objeto. Qualquer objeto que for necessário,
pode ser criado através dessa função. O objeto ainda não será desenhado, apenas criado dentro do jogo.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto original que será copiado.
retiraFundo (entrada, passagem por valor): inteiro que indica se o fundo da imagem deve ser retirado ou não ao ler o arquivo em questão. O valor padrão é 1, indicando que o fundo deve ser retirado.
corFundo (entrada, passagem por referência não-obrigatório): indica se há uma cor específica para ser considerada como cor de fundo da imagem. Caso, o valor seja NULL, mas o parâmetro retiraFundo seja diferente de 0, o pixel (0,0) da imagem será considerado como cor de fundo.
idJanela (entrada, passagem por valor não-obrigatório): indica qual janela vai receber o objeto.
Retorno:
inteiro que representa o identificador único do objeto. Todas as operaçőes subsequentes com este objeto deverão receber este identificador como parâmetro.
********************************/
int CriaObjeto(int idObjeto, int retiraFundo=1, PIGCor *corFundo=NULL, int idJanela=0){
    return CPIGGerenciadorSprites::CriaObjeto(idObjeto,retiraFundo,corFundo,idJanela);
}

/********************************
A função CriaObjetoOffScreen() é responsável por criar um objeto a partir da imagem que está sendo montanda pelo
renderizador Offscreen. O renderizador precisa ter sido preparado anteriormente.
Parâmetros:
retiraFundo (entrada, passagem por valor): inteiro que indica se o fundo da imagem deve ser retirado ou não ao ler o arquivo em questão. O valor padrão é 1, indicando que o fundo deve ser retirado.
corFundo (entrada, passagem por referência não-obrigatório): indica se há uma cor específica para ser considerada como cor de fundo da imagem. Caso, o valor seja NULL, mas o parâmetro retiraFundo seja diferente de 0, o pixel (0,0) da imagem será considerado como cor de fundo.
Retorno:
inteiro que representa o identificador único do objeto. Todas as operaçőes subsequentes com este objeto deverão receber este identificador como parâmetro.
********************************/
int CriaObjetoOffScreen(int retiraFundo=1, PIGCor *corFundo=NULL, int idJanela=0){
    return CPIGGerenciadorSprites::CriaObjetoOffScreen(jogo->GetOffScreenRender(),retiraFundo,corFundo,idJanela);
}

/********************************
A função GetFrameAtualObjeto() recupera o valor do frame atual exibido no objeto.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
Retorno:
Número do frame atual do objeto.
********************************/
int GetFrameAtualObjeto(int idObjeto){
    return CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetFrameAtual();
}

/********************************
A função DestroiObjeto() é responsável por eliminar o objeto em questão do jogo.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto a ser excluído.
********************************/
void DestroiObjeto(int idObjeto){
    CPIGGerenciadorSprites::DestroiObjeto(idObjeto);
}

/********************************
A função SetValorIntObjeto() é responsável incorporar a um objeto um atributo inteiro.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por valor): relaciona um número inteiro ao atributo.
valor (entrada, passagem por valor): valor do atributo inteiro a ser associado ao objeto.
********************************/
void SetValorIntObjeto(int idObjeto, int indice, int valor){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetValorInt(indice,valor);
}

/********************************
A função SetValorFloatObjeto() é responsável incorporar a um objeto um atributo float.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por valor): relaciona um número inteiro ao atributo.
valor (entrada, passagem por valor): valor do atributo float a ser associado ao objeto.
********************************/
void SetValorFloatObjeto(int idObjeto, int indice, float valor){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetValorFloat(indice,valor);
}

/********************************
A função SetValorIntObjeto() é responsável incorporar a um objeto um atributo inteiro.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por valor): relaciona um número inteiro ao atributo.
valor (entrada, passagem por referência): valor do atributo string a ser associado ao objeto.
********************************/
void SetValorStringObjeto(int idObjeto, int indice, char *valor){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetValorString(indice,valor);
}

/********************************
A função SetValorIntObjeto() é responsável incorporar a um objeto um atributo inteiro.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por referência): relaciona uma string ao atributo.
valor (entrada, passagem por valor): valor do atributo inteiro a ser associado ao objeto.
********************************/
void SetValorIntObjeto(int idObjeto, char *indice, int valor){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetValorInt(indice,valor);
}

/********************************
A função SetValorFloatObjeto() é responsável incorporar a um objeto um atributo float.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por referência): relaciona uma string ao atributo.
valor (entrada, passagem por valor): valor do atributo float a ser associado ao objeto.
********************************/
void SetValorFloatObjeto(int idObjeto, char *indice, float valor){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetValorFloat(indice,valor);
}

/********************************
A função SetValorIntObjeto() é responsável incorporar a um objeto um atributo inteiro.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por referência): relaciona uma string ao atributo.
valor (entrada, passagem por referência): valor do atributo string a ser associado ao objeto.
********************************/
void SetValorStringObjeto(int idObjeto, char *indice, char *valor){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetValorString(indice,valor);
}

/********************************
A função GetValorIntObjeto() é responsável recuperar o valor de um atributo inteiro relacionado a um objeto.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por valor): indica o número do atributo que se deseja recuperar.
valor (saída, passagem por referência): indica o valor do atributo, se a função retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo não existir, a função retorna o valor 0 (zero).
********************************/
int GetValorIntObjeto(int idObjeto, int indice, int *valor){
    return CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetValorInt(indice,*valor);
}

/********************************
A função GetValorFloatObjeto() é responsável recuperar o valor de um atributo float relacionado a um objeto.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por valor): indica o número do atributo que se deseja recuperar.
valor (saída, passagem por referência): indica o valor do atributo, se a função retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo não existir, a função retorna o valor 0 (zero).
********************************/
int GetValorFloatObjeto(int idObjeto, int indice, float *valor){
    return CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetValorFloat(indice,*valor);
}

/********************************
A função GetValorStringObjeto() é responsável recuperar o valor de um atributo string relacionado a um objeto.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por valor): indica o número do atributo que se deseja recuperar.
valor (saída, passagem por referência): indica o valor do atributo, se a função retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo não existir, a função retorna o valor 0 (zero).
********************************/
int GetValorStringObjeto(int idObjeto, int indice, char *valor){
    string str;
    bool resp = CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetValorString(indice,str);
    strcpy(valor,str.c_str());
    return resp;
}

/********************************
A função GetValorIntObjeto() é responsável recuperar o valor de um atributo inteiro relacionado a um objeto.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por referência): indica o nome do atributo que se deseja recuperar.
valor (saída, passagem por referência): indica o valor do atributo, se a função retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo não existir, a função retorna o valor 0 (zero).
********************************/
int GetValorIntObjeto(int idObjeto, char *indice, int *valor){
    return CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetValorInt(indice,*valor);
}

/********************************
A função GetValorFloatObjeto() é responsável recuperar o valor de um atributo float relacionado a um objeto.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por valor): indica o nome do atributo que se deseja recuperar.
valor (saída, passagem por referência): indica o valor do atributo, se a função retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo não existir, a função retorna o valor 0 (zero).
********************************/
int GetValorFloatObjeto(int idObjeto, char *indice, float *valor){
    return CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetValorFloat(indice,*valor);
}

/********************************
A função GetValorStringObjeto() é responsável recuperar o valor de um atributo string relacionado a um objeto.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por valor): indica o nome do atributo que se deseja recuperar.
valor (saída, passagem por referência): indica o valor do atributo, se a função retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo não existir, a função retorna o valor 0 (zero).
********************************/
int GetValorStringObjeto(int idObjeto, char *indice, char *valor){
    string str;
    bool resp = CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetValorString(indice,str);
    strcpy(valor,str.c_str());
    return resp;
}

/********************************
A função GetXYObjeto() é responsável recuperar o valor da posição (X,Y) do objeto de acordo com o sistema de coordenadas do jogo.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
posicaoX (saída, passagem por referencia): indica a posicao no eixo X do objeto.
posicaoY (saída, passagem por referencia): indica a posicao no eixo Y do objeto.
********************************/
void GetXYObjeto(int idObjeto, int *posicaoX, int *posicaoY){
    PIGPonto2D p = CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetXY();
    *posicaoX = p.x;
    *posicaoY = p.y;
}

/********************************
A função MoveObjeto() é responsável por movimentar um determinado objeto para uma nova posição informada.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto a ser movido.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usuário deseja reposicionar o objeto.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usuário deseja reposicionar o objeto.
********************************/
void MoveObjeto(int idObjeto, int posicaoX, int posicaoY){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->Move(posicaoX,posicaoY);
}

/********************************
A função DeslocaObjeto() é responsável por deslocar um determinado objeto em relação à sua posição atual.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto a ser movido.
deltaX (entrada, passagem por valor): valor a ser somado ou subtraído na componente X da posição do objeto.
deltaY (entrada, passagem por valor): valor a ser somado ou subtraído na componente Y da posição do objeto.
********************************/
void DeslocaObjeto(int idObjeto, int deltaX, int deltaY){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->Desloca(deltaX,deltaY);
}

/********************************
A função SetAnguloObjeto() é responsável pela angulação de determinado objeto. A angulação é calculada em sentido
horário a partir do eixo X (0 graus). O objeto será desenhado com a angulação informada no próximo comando
DesenhaObjeto(). A detecção de colisão não funciona com objetos fora da angulação padrão (0 graus).
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
angulo (entrada, passagem por valor): valor para indicar a angulação do objeto em graus.
********************************/
void SetAnguloObjeto(int idObjeto, float angulo){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetAngulo(angulo);
}

/********************************
A função GetAnguloObjeto() é responsável por recuperar o ângulo de rotação de determinado objeto. A angulação é calculada em sentido
horário a partir do eixo X (0 graus). O objeto será desenhado com a angulação informada no próximo comando
DesenhaObjeto(). A detecção de colisão não funciona com objetos fora da angulação padrão (0 graus).
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
Retorno:
Retorna o valor do ângulo em graus.
********************************/
float GetAnguloObjeto(int idObjeto){
    return CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetAngulo();
}

/********************************
A função SetPivoAbsolutoObjeto() define um ponto (X,Y) em relação ao ponto (0,0) do objeto, sobre o qual o objeto será
rotacionado quando a função SetAnguloObjeto() for executada.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
posicaoX (entrada, passagem por valor): Valor da coordenada X do pivô em relação ao ponto (0,0) do objeto.
posicaoY (entrada, passagem por valor): Valor da coordenada Y do pivô em relação ao ponto (0,0) do objeto.
********************************/
void SetPivoAbsolutoObjeto(int idObjeto, int posicaoX, int posicaoY){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetPivoAbsoluto({(double)posicaoX,(double)posicaoY});
}

/********************************
A função SetPivoProporcionalObjeto() define um ponto (X,Y) proporcional ao tamanho do objeto, sobre o qual o objeto será
rotacionado quando a função SetAnguloObjeto() for executada.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
relX (entrada, passagem por valor): porcentagem da largura do objeto onde ficará o pivô.
relY (entrada, passagem por valor): porcentagem da altura do objeto onde ficará o pivô.
********************************/
void SetPivoProporcionalObjeto(int idObjeto, float relX, float relY){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetPivoProporcional({relX,relY});
}

/********************************
A função GetPivoObjeto() define um ponto (X,Y) em relação ao ponto (0,0) do objeto, sobre o qual o objeto será
rotacionado quando a função SetAnguloObjeto() for executada.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
posicaoX (saída, passagem por referência): Valor da coordenada X do pivô em relação ao ponto (0,0) do objeto.
posicaoY (saída, passagem por referência): Valor da coordenada Y do pivô em relação ao ponto (0,0) do objeto.
********************************/
void GetPivoObjeto(int idObjeto, int *posicaoX, int *posicaoY){
    PIGPonto2D p = CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetPivo();
    *posicaoX = p.x;
    *posicaoY = p.y;
}

/********************************
A função SetFlipObjeto() é responsável por virar o objeto, invertendo-o em alguma direção. O objeto somente será
desenhado na nova orientação no próximo comando DesenhaObjeto().
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto a ser virado.
valor (entrada, passagem por valor): valor do tipo de Flip. Pode ser PIG_FLIP_NENHUM (nenhum tipo de inversão),
PIG_FLIP_HORIZONTAL (inverte da esquerda para a direita), PIG_FLIP_VERTICAL (inverte de cima para baixo),
ou PIG_FLIP_HORIZ_VERT (inverte da esquerda para direita e de cima para baixo).
********************************/
void SetFlipObjeto(int idObjeto, PIGFlip valor){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetFlip(valor);
}

/********************************
A função GetFlipObjeto() é responsável por recuperar o valor da manipulação causada pela função SetFlipObjeto().
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto a ser virado.
Retorno:
inteiro que indica o tipo de Flip. Pode ser PIG_FLIP_NENHUM (nenhum tipo de inversão),
PIG_FLIP_HORIZONTAL (inverte da esquerda para a direita), PIG_FLIP_VERTICAL (inverte de cima para baixo),
ou PIG_FLIP_HORIZ_VERT (inverte da esquerda para direita e de cima para baixo).
********************************/
PIGFlip GetFlipObjeto(int idObjeto){
    return CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetFlip();
}

/********************************
A função SetDimensoesObjeto() é responsável por delimitar a altura e a largura do objeto que será desenhado na tela,
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
A função GetDimensoesObjeto() é responsável por recuperar a altura e a largura da área a ser usada
para desenhar o objeto na tela. Em outras palavras, representa o tamanho atual do objeto.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
altura (saída, passagem por referência): altura atual em pixels do objeto.
largura (saída, passagem por referência): largura atual em pixels do objeto.
********************************/
void GetDimensoesObjeto(int idObjeto, int *altura, int *largura){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetDimensoes(*altura,*largura);
}

/********************************
A função GetDimensoesOriginaisObjeto() é responsável por recuperar a altura e a largura originais da imagem
que foi usada para criar o objeto. Qualquer utilização da função SetDimensoesObjeto() é ignorada para
o cálculo desta função.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
altura (saída, passagem por referência): altura original em pixels do objeto.
largura (saída, passagem por referência): largura original em pixels do objeto.
********************************/
void GetDimensoesOriginaisObjeto(int idObjeto, int *altura, int *largura){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetDimensoesOriginais(*altura,*largura);
}

/********************************
A função RestauraDimensoesOriginaisObjeto() é responsável por restaurar o objeto com o tamanho original da imagem.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
********************************/
void RestauraDimensoesOriginaisObjeto(int idObjeto, int altura, int largura){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->RestauraDimensoesOriginais();
}

/********************************
A função CriaFrameObjeto() é responsável por delimitar o posicionamento dos pixels do arquivo de imagem que serão
utilizados para representar o objeto na tela. Desta forma, nem toda a imagem será automaticamente utilizada para
representar o objeto. O sistema de coordenadas deve ser o padrão dos arquivos de imagem, com o eixo Y aumentando para baixo.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto a ser desenhado.
idFrame (entrada, passagem por valor): identificador do frame a ser criado.
xBitmap (entrada, passagem por valor): indica a posição de eixo X onde começa o frame.
yBitmap (entrada, passagem por valor): indica a posição de eixo Y onde começa o frame. Neste caso, o eixo Y aumenta para baixo.
altura (entrada, passagem por valor): altura em pixels do frame.
largura (entrada, passagem por valor): largura em pixels do frame.
********************************/
void CriaFrameObjeto(int idObjeto, int idFrame, int xBitmap, int yBitmap, int altura, int largura){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->DefineFrame(idFrame, {xBitmap,yBitmap,largura,largura});
}


/********************************
A função CarregaArquivoFramesObjeto() é responsável por ler de arquivo texto os frames de um objeto.
Cada linha do arquivo texto deve conter 5 números inteiros: o número do frame, a posição do frame no eixo X do arquivo de imagem,
a posição do frame no eixo Y do arquivo de imagem, a altura do frame e a largura do frame (todas as unidades em pixels).
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
nomeArq (entrada, passagem por referência): nome do arquivo texto contendo os frames.
********************************/
void CarregaArquivoFramesObjeto(int idObjeto, char *nomeArq){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->CarregaArquivoFrames(nomeArq);
}

/********************************
A função CarregaFramesPorLinhaObjeto() é responsável por subdividir o arquivo de imagem em linhas (de mesmo tamanho) e colunas (de mesmo tamanho).
Cada subdivisão representará um frame que será automaticamente criado para a animação, com numeração incremental a partir do parâmetro "frameInicial".
Ao final das "qtdColunas" da primeira linha, a definição dos frames continua na linha inferior.
A função pode ser utilizada em spritesheets regulares.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
frameInicial (entrada, passagem por valor): numeração do primeiro frame a ser criado pela função. Os demais frames terão numeração consecutiva.
qtdLinhas (entrada, passagem por valor): quantidade de linhas na qual o arquivo de imagem será dividido.
qtdColunas (entrada, passagem por valor): quantidade de colunas na qual o arquivo de imagem será dividido.
********************************/
void CarregaFramesPorLinhaObjeto(int idObjeto, int frameInicial, int qtdLinhas, int qtdColunas){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->CriaFramesAutomaticosPorLinha(frameInicial,qtdLinhas,qtdColunas);
}

/********************************
A função CarregaFramesPorColunaObjeto() é responsável por subdividir o arquivo de imagem em linhas (de mesmo tamanho) e colunas (de mesmo tamanho).
Cada subdivisão representará um frame que será automaticamente criado para a animação, com numeração incremental a partir do parâmetro "frameInicial".
Ao final das "qtdLinhas" da primeira coluna, a definição dos frames continua na coluna seguinte.
A função pode ser utilizada em spritesheets regulares.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
frameInicial (entrada, passagem por valor): numeração do primeiro frame a ser criado pela função. Os demais frames terão numeração consecutiva.
qtdLinhas (entrada, passagem por valor): quantidade de linhas na qual o arquivo de imagem será dividido.
qtdColunas (entrada, passagem por valor): quantidade de colunas na qual o arquivo de imagem será dividido.
********************************/
void CarregaFramesPorColunaObjeto(int idObjeto, int frameInicial, int qtdLinhas, int qtdColunas){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->CriaFramesAutomaticosPorColuna(frameInicial,qtdLinhas,qtdColunas);
}

/********************************
A função MudaFrameObjeto() é responsável por modificar o frame (já definido pela função DefineFrameObjeto) de um objeto
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
idFrame (entrada, passagem por valor): identificador do frame já criado.
Retorno:
Se o identifador do frame informado não corresponder a um frame já criado, o valor de retorno é igual a 0. Caso contrário, é igual a 1.
********************************/
int MudaFrameObjeto(int idObjeto, int idFrame){
    return CPIGGerenciadorSprites::GetObjeto(idObjeto)->MudaFrameAtual(idFrame);
}

/********************************
A função SetColoracaoObjeto() é responsável por mesclar uma determinada cor com os pixels do arquivo de imagem.
Após a modificação, todos os desenhos deste objeto serão mostrados já com a mesclagem definida.
Para voltar ao padrão original de pixels, deve-se chamar a função, passando a cor branca (255,255,255,255).
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto a ser desenhado.
cor (entrada,passagem por valor): cor do sistema RGB utilizada para mesclagem com o arquivo de imagem
********************************/
void SetColoracaoObjeto(int idObjeto, PIGCor cor){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetColoracao(cor);
}

/********************************
A função SetOpacidadeObjeto() é responsável por modificar o nível de opacidade do objeto.
O nível de opacidade varia de 0-255, sendo 0 totalmente transparente e 255 totalmente opaco.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
valor (entrada,passagem por valor): nível de opacidade do objeto na faixa 0-255.
********************************/
void SetOpacidadeObjeto(int idObjeto,int valor){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetOpacidade(valor);
}

/********************************
A função GetOpacidadeObjeto() é responsável por recuperar o nível de opacidade de determinado objeto.
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
A função DesenhaObjeto() é responsável por desenhar um objeto na tela. O objeto será desenhado de acordo com todas as definiçőes
de posição e ângulo informado até o momento. Além disso, se o objeto estiver virado (flipping), isso também será levado em consideração.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto a ser desenhado.
********************************/
void DesenhaObjeto(int idObjeto){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->Desenha();
}

/********************************
A função DesenhaObjetoOffScreen() é responsável por desenhar um objeto no Renderizador Offscreen. O objeto será desenhado de acordo com todas as definiçőes
de posição e ângulo informado até o momento. Além disso, se o objeto estiver virado (flipping), isso também será levado em consideração.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto a ser desenhado.
offScreen (entrada, passagem por valor): indica se o objeto deve ser desenhado no Renderizador Offscreen.
********************************/
void DesenhaObjetoOffScreen(int idObjeto){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->DesenhaOffScreen(jogo->GetOffScreenRender());
}

/********************************
A função TestaColisaoObjetos() é responsável por testar se dois objetos se colidiram ou não, ao passar
os identificadores dos objetos por parâmetro.
Parâmetros:
idObjeto1 (entrada, passagem por valor): identificador do primeiro objeto.
idObjeto2 (entrada, passagem por valor): identificador do segundo objeto.
Retorno:
Inteiro indicando se houve colisão (valor diferente de zero) ou não (valor igual a 0, zero).
********************************/
int TestaColisaoObjetos(int idObjeto1, int idObjeto2){
    return CPIGGerenciadorSprites::GetObjeto(idObjeto1)->Colisao(CPIGGerenciadorSprites::GetObjeto(idObjeto2))
           &&CPIGGerenciadorSprites::GetObjeto(idObjeto2)->Colisao(CPIGGerenciadorSprites::GetObjeto(idObjeto1));
}

/********************************
A função DefineAreaColisaoObjeto() é responsável estabelecer um polígono que será utilizado como área de colisão do objeto com os demais.
Os vetores X e Y deve ter pelo menos qtdPontos elementos.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
pontosX (entrada, passagem por referência): vetor de inteiros, de tamanho qtdPontos, contendo os valores X de cada ponto do polígono.
pontosY (entrada, passagem por referência): vetor de inteiros, de tamanho qtdPontos, contendo os valores Y de cada ponto do polígono.
qtdPontos (entrada, passagem por valor): quantidade de pontos do polígono.
********************************/
void DefineAreaColisaoObjeto(int idObjeto, int pontosX[], int pontosY[], int qtdPontos) {
    vector<PIGPonto2D> vertices;

    for (int i = 0; i < qtdPontos; i++) {
        vertices.push_back({(double)pontosX[i],(double) pontosY[i]});
    }

    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetVertices(vertices);
}

/********************************
A função DefineRaioColisaoObjeto() é responsável por estabelecer um raio, em relação ao pivô do objeto, que será utilizado para teste de colisão circular deste objeto com os demais.
A definição do raio só será útil se o tipode colisão deste objeto for circular, definido pela função DefineTipoColisaoObjeto().
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
raio (entrada, passagem por valor): tamanho do raio que formará a área de colisão deste objeto.
********************************/
void DefineRaioColisaoObjeto(int idObjeto, float raio){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetRaioColisaoCircular(raio);
}

/********************************
A função DefineTipoColisaoObjeto() é responsável por definir o tipod e colisão que será utilizada por este objeto com os demais.
É possível ter 3 tipos de colisão: por bouding-box (PIG_COLISAO_OOBB - área de colisão delimitada pelo ponto X,Y do objeto, sua altura e largura e rotação),
por polígono (PIG_COLISAO_POLIGONO) área de colisão formada por pontos genéricos) e circular (PIG_COLISAO_CIRCULAR) área de colisão em forma de círculo, com raio definido a partir do ponto pivô)
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
modo (entrada, passagem por valor): modo de colisão a ser utilizado por este objeto.
********************************/
void DefineTipoColisaoObjeto(int idObjeto, PIGModoColisao modo){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetModoColisao(modo);
}

/********************************
A função GetPixelsObjeto() é responsável por extrair os pixels da imagem que originou o objeto, devolvendo-os como
uma matriz de pixels (PIGCor). Mudanças nessa matriz só serão validadas após a chamada da função AtualizaPixelsObjeto().
O linha 0 corresponde à primeira linha da imagem, ou seja, à linha superior, pois o sistema de coordenadas
das imagens tem o eixo Y aumentando para baixo.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
Retorno:
matriz de pixels (PIGCor) da imagem que gerou o objeto. O total de linhas da matriz é dado pela altura original do objeto e o
total de colunas é dado pela largura original do objeto. Ambos os valores podem ser obtidos pela função GetDimensoesOriginaisObjeto().
********************************/
PIGCor **GetPixelsObjeto(int idObjeto){
    return CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetPixels();
}

/********************************
A função AtualizaPixelsObjeto() é responsável por efetivar quaisquer mudanças nos pixels do objeto obtidos pela função GetPixelsObjeto().
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
retiraFundo (entrada, passagem por valor): inteiro que indica se o fundo da imagem deve ser retirado ou não ao ler o arquivo em questão. O valor padrão é 1, indicando que o fundo deve ser retirado.
********************************/
void AtualizaPixelsObjeto(int idObjeto, int retiraFundo=1){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->AtualizaPixels(retiraFundo);
}

/********************************
A função InsereTransicaoObjeto() é responsável por criar e inserir uma nova transição ao final de sequência de transiçőes do objeto.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
tempo (entrada, passagem por valor): duracao (em segundos) da transição.
deltaX (entrada, passagem por valor): diferença da posição no eixo X em relação à posição do objeto no início da transição.
deltaY (entrada, passagem por valor): diferença da posição no eixo Y em relação à posição do objeto no início da transição.
deltaAltura (entrada, passagem por valor): diferença da altura do objeto em relação ao início da transição.
deltaLargura (entrada, passagem por valor): diferença da largura do objeto em relação ao início da transição.
deltaAngulo (entrada, passagem por valor): diferença de ângulo (em graus) do objeto em relação ao início da transição.
corFinal (entrada, passagem por valor): coloração do objeto ao final da transição.
deltaOpacidade (entrada, passagem por valor): diferença do nível de opacidade do objeto em relação ao início da transição.
********************************/
void InsereTransicaoObjeto(int idObjeto, double tempo, int deltaX, int deltaY, int deltaAltura, int deltaLargura, double deltaAngulo, PIGCor corFinal, int deltaOpacidade){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->InsereTransicao(tempo,{deltaX,deltaY,deltaAltura,deltaLargura,deltaAngulo,corFinal,deltaOpacidade});
}

/********************************
A função ExecutandoTransicaoObjeto() retorna a informação sobre a execução (neste momento) de transiçőes do objeto.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
Retorno:
inteiro que indica se o objeto está executando alguma transição no momento (valor diferente de 0) ou não (valor igual a 0).
********************************/
int ExecutandoTransicaoObjeto(int idObjeto){
    return CPIGGerenciadorSprites::GetObjeto(idObjeto)->ExecutandoTransicao();
}

/********************************
A função LeArquivoTransicaoObjeto() é responsável por ler, criar e inserir as transiçőes para um objeto, provenientes de um arquivo texto.
Cada linha do arquivo texto corresponde a uma transição (em ordem) e deve possuir 11 valores:
1) um double representando a duracao (em segundos) da transição.
2) um inteiro representando a diferença da posição no eixo X em relação à posição do objeto no início da transição.
3) um inteiro representando a diferença da posição no eixo Y em relação à posição do objeto no início da transição.
4) um inteiro representando a diferença da altura do objeto em relação ao início da transição.
5) um inteiro representando a diferença da largura do objeto em relação ao início da transição.
6) um double representando a diferença de ângulo (em graus) do objeto em relação ao início da transição.
7) um inteiro representando a componente R (vermelho) da coloração do objeto ao final da transição.
8) um inteiro representando a componente G (verde) da coloração do objeto ao final da transição.
9) um inteiro representando a componente B (azul) da coloração do objeto ao final da transição.
10) um inteiro representando a componente A (canal alfa) da coloração do objeto ao final da transição.
11) um inteiro representando a diferença do nível de opacidade do objeto em relação ao início da transição.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
nomeArq (entrada, passagem por referência): nome com extensão do arquivo texto contendo as transiçőes.
********************************/
void LeArquivoTransicaoObjeto(int idObjeto, char *nomeArq){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->LeTransicoes(nomeArq);
}

/********************************
A função IniciaAutomacaoObjeto() é responsável por iniciar as transiçőes já inseridas no objeto, de acordo como o tipo de transição informada.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
********************************/
void IniciaAutomacaoObjeto(int idObjeto){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->IniciaAutomacao();
}

/********************************
A função TrataAutomacaoObjeto() é responsável por calcular o estado da transição corrente do objeto e aplicar essas modificação a ela.
A função deve ser chamada a cada frame, para ter resultados mais precisos.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
********************************/
void TrataAutomacaoObjeto(int idObjeto){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->TrataAutomacao();
}

/********************************
A função PausaAutomacaoObjeto() é responsável por pausar as transiçőes e açőes associadas a um objeto.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
********************************/
void PausaAutomacaoObjeto(int idObjeto){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->PausaAutomacao();
}

/********************************
A função DespausaAutomacaoObjeto() é responsável por despausar as transiçőes e açőes associadas a um objeto.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
********************************/
void DespausaAutomacaoObjeto(int idObjeto){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->DespausaAutomacao();
}

/********************************
A função DefineTipoTransicaoObjeto() é responsável por determinar como a sequência de transiçőes será executada.
É possível fazê-la uma única vez (PIG_TRANSICAO_NORMAL), em loop (PIG_TRANSICAO_LOOP) ou indo até o final da sequência e retornando, em vai-vém (PIG_TRANSICAO_VAIVEM).
A função deve ser chamada a cada frame, para ter resultados mais precisos.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
********************************/
void DefineTipoTransicaoObjeto(int idObjeto, PIGTipoTransicao valor){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->DefineTipoTransicao(valor);
}

/********************************
A função LimpaTransicoesObjeto() é responsável por remover a sequência de transiçőes do objeto.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
********************************/
void LimpaTransicoesObjeto(int idObjeto){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->LimpaTransicoes();
}

/********************************
A função InsereAcaoObjeto() é responsável por inserir na linha de tempo de automação do objeto uma ação a ser executada.
A ação é composta por uma função "acao" que será executada quando a linha de tempo atingir o parâmetro "tempo" e será repetida a cada "repeticao" segundos.
A ação pode armazenar um ponteiro genérico "param" que será utilizado na chamada da função.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
tempo (entrada, passagem por valor): tempo (em segundos) da primeira chamada da função.
repeticao (entrada, passagem por valor): tempo (em segundos) entre a chamada anterior e a próxima. O valor -1 indica que a função não será repetida.
param (entrada, passagem por referência): ponteiro genérico para um valor que será utilizado na chamada da função.
********************************/
void InsereAcaoObjeto(int idObjeto, double tempo, double repeticao, PIGFuncaoSimples acao, void *param){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->InsereAcao(tempo,repeticao,acao,param);
}

/********************************
A função LimpaAcoesObjeto() é responsável por remover as açőes restantes associadas ao objeto.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
********************************/
void LimpaAcoesObjeto(int idObjeto){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->LimpaAcoes();
}


/********************************
Seção de gerador de partículas
********************************/

/********************************
A função CriaGeradorParticulas() cria um novo gerador de partículas (GDP). As partículas em si precisam ser criadas
posteriormente através da função CriaParticula(), passando o identificador do GDP como parâmetro.
Parâmetros:
maxParticulas (entrada, passagem por valor): informa o maior número de partículas que o gerador terá simultaneamente. O maior valor aceito é PIG_MAX_PARTICULAS partículas.
nomeArquivo (entrada, passagem por referência): indica o caminho relativo ou absoluto do arquivo de imagem,
que será utilizado para cada partícula do GDP.
audioCriacao (entrada, passagem por valor não-obrigatório): indica qual audio previamente criado deve ser tocado quando uma partícula for efetivamente criada.
audioEncerramento (entrada, passagem por valor não-obrigatório): indica qual audio previamente criado deve ser tocado quando uma partícula for destruida por acabar o tempo de vida ou por sair da área de ativação.
retiraFundo (entrada, passagem por valor): inteiro que indica se o fundo da imagem deve ser retirado ou não ao ler o arquivo em questão. O valor padrão é 1, indicando que o fundo deve ser retirado.
corFundo (entrada, passagem por referência não-obrigatório): indica se há uma cor específica para ser considerada como cor de fundo da imagem. Caso, o valor seja NULL, mas o parâmetro retiraFundo seja diferente de 0, o pixel (0,0) da imagem será considerado como cor de fundo.
idJanela (entrada, passagem por valor não-obrigatório): indica qual janela vai receber o GDP.
********************************/
int CriaGeradorParticulas(int maxParticulas, char* nomeArquivo, int audioCriacao=-1, int audioEncerramento=-1, int retiraFundo=1, PIGCor *corFundo=NULL, int idJanela=0){
    return CPIGGerenciadorGDP::CriaGeradorParticulas(maxParticulas,nomeArquivo,audioCriacao,audioEncerramento,retiraFundo,corFundo,idJanela);
}

/********************************
A função CriaGeradorParticulasPorAnimacao() cria um novo gerador de partículas (GDP). As partículas em si precisam ser criadas
posteriormente através da função CriaParticula(), passando o identificador do GDP como parâmetro. As partículas serão semelhantes a uma animação já criada anteriormente
que é indicada pelo parâmetro idAnimação.
Parâmetros:
maxParticulas (entrada, passagem por valor): informa o maior número de partículas que o gerador terá simultaneamente. O maior valor aceito é PIG_MAX_PARTICULAS partículas.
idAnimacao (entrada, passagem por referência): identificador da animação (já criada anteriormente) que será utilizada
para cada partícula do GDP.
audioCriacao (entrada, passagem por valor não-obrigatório): indica qual audio previamente criado deve ser tocado quando uma partícula for efetivamente criada.
audioEncerramento (entrada, passagem por valor não-obrigatório): indica qual audio previamente criado deve ser tocado quando uma partícula for destruida por acabar o tempo de vida ou por sair da área de ativação.
retiraFundo (entrada, passagem por valor): inteiro que indica se o fundo da imagem deve ser retirado ou não ao ler o arquivo em questão. O valor padrão é 1, indicando que o fundo deve ser retirado.
corFundo (entrada, passagem por referência não-obrigatório): indica se há uma cor específica para ser considerada como cor de fundo da imagem. Caso, o valor seja NULL, mas o parâmetro retiraFundo seja diferente de 0, o pixel (0,0) da imagem será considerado como cor de fundo.
idJanela (entrada, passagem por valor não-obrigatório): indica qual janela vai receber o GDP.
********************************/
int CriaGeradorParticulasPorAnimacao(int maxParticulas, int idAnimacao, int audioCriacao=-1, int audioEncerramento=-1, int retiraFundo=1, PIGCor *corFundo=NULL, int idJanela=0){
    return CPIGGerenciadorGDP::CriaGeradorParticulas(maxParticulas,CPIGGerenciadorSprites::GetAnimacao(idAnimacao),audioCriacao,audioEncerramento,retiraFundo,corFundo,idJanela);
}

/********************************
A função CriaGeradorParticulasPorObjeto() cria um novo gerador de partículas (GDP). As partículas em si precisam ser criadas
posteriormente através da função CriaParticula(), passando o identificador do GDP como parâmetro. As partículas serão semelhantes a um objeto já criado anteriormente
que é indicado pelo parâmetro idObjeto.
Parâmetros:
maxParticulas (entrada, passagem por valor): informa o maior número de partículas que o gerador terá simultaneamente. O maior valor aceito é PIG_MAX_PARTICULAS partículas.
idObjeto (entrada, passagem por referência): identificador do objeto (já criado anteriormente) que será utilizado
para cada partícula do GDP.
audioCriacao (entrada, passagem por valor não-obrigatório): indica qual audio previamente criado deve ser tocado quando uma partícula for efetivamente criada.
audioEncerramento (entrada, passagem por valor não-obrigatório): indica qual audio previamente criado deve ser tocado quando uma partícula for destruida por acabar o tempo de vida ou por sair da área de ativação.
retiraFundo (entrada, passagem por valor): inteiro que indica se o fundo da imagem deve ser retirado ou não ao ler o arquivo em questão. O valor padrão é 1, indicando que o fundo deve ser retirado.
corFundo (entrada, passagem por referência não-obrigatório): indica se há uma cor específica para ser considerada como cor de fundo da imagem. Caso, o valor seja NULL, mas o parâmetro retiraFundo seja diferente de 0, o pixel (0,0) da imagem será considerado como cor de fundo.
idJanela (entrada, passagem por valor não-obrigatório): indica qual janela vai receber o GDP.
********************************/
int CriaGeradorParticulasPorObjeto(int maxParticulas, int idObjeto, int audioCriacao=-1, int audioEncerramento=-1, int retiraFundo=1, PIGCor *corFundo=NULL, int idJanela=0){
    return CPIGGerenciadorGDP::CriaGeradorParticulas(maxParticulas,CPIGGerenciadorSprites::GetObjeto(idObjeto),audioCriacao,audioEncerramento,retiraFundo,corFundo,idJanela);
}

/********************************
A função DestroiGeradorParticulas() encerra um gerador de partículas (GDP). Todas as partículas relacionadas a ele também são finalizadas
neste momento.
Parâmetros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da função CriaGeradorParticulas().
********************************/
void DestroiGeradorParticulas(int idGerador){
    CPIGGerenciadorGDP::DestroiGeradorParticulas(idGerador);
}

/********************************
A função MoveGeradorParticulas() reposiciona um gerador de partículas (GDP). Na prática, isto significa que as novas partículas que
forem criadas posteriormente terão esse ponto de origem.
Parâmetros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da função CriaGeradorParticulas().
posicaoX (entrada, passagem por valor): informa a nova posição X do GDP, em relação ao sistema de coordenadas do jogo.
posicaoY (entrada, passagem por valor): informa a nova posição Y do GDP, em relação ao sistema de coordenadas do jogo.
********************************/
void MoveGeradorParticulas(int idGerador, int posicaoX, int posicaoY){
    CPIGGerenciadorGDP::GetGerador(idGerador)->Move(posicaoX,posicaoY);
}

/********************************
A função DeslocaGeradorParticulas() é responsável por deslocar uma determinado gerador de partículas (GDP) em relação à sua posição atual.
Parâmetros:
idGerador (entrada, passagem por valor): identificador do GDP a ser deslocada.
deltaX (entrada, passagem por valor): valor a ser somado ou subtraído na componente X da posição do GDP.
deltaY (entrada, passagem por valor): valor a ser somado ou subtraído na componente Y da posição do GDP.
********************************/
void DeslocaGeradorParticulas(int idGerador, int deltaX, int deltaY){
    CPIGGerenciadorGDP::GetGerador(idGerador)->Desloca(deltaX,deltaY);
}

/*
/********************************
A função MudaDirecaoParticulas() modifica a direção na qual as partículas se movimentarão após serem criadas.
Somente as partículas criadas posteriormente seguirão a direção especificada.
Parâmetros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da função CriaGeradorParticulas().
valorX (entrada, passagem por valor): informa a componente X da direção a ser definida para as partículas.
valorY (entrada, passagem por valor): informa a componente Y da direção a ser definida para as partículas.
********************************/
//void MudaDirecaoParticulas(int idGerador,int valorX,int valorY){
    //CPIGGerenciadorParticulas::GetGerador(idGerador)->MudaDirecao(valorX,valorY);
//}

/********************************
A função InsereTransicaoParticulas() é responsável por criar e inserir uma nova transição ao final de sequência de transiçőes das partículas do gerador.
Parâmetros:
idGerador (entrada, passagem por valor): identificador do gerador.
tempo (entrada, passagem por valor): duracao (em segundos) da transição das partículas.
deltaX (entrada, passagem por valor): diferença da posição no eixo X em relação à posição das partículas no início da transição.
deltaY (entrada, passagem por valor): diferença da posição no eixo Y em relação à posição das partículas no início da transição.
deltaAltura (entrada, passagem por valor): diferença da altura das partículas em relação ao início da transição.
deltaLargura (entrada, passagem por valor): diferença da largura das partículas em relação ao início da transição.
deltaAngulo (entrada, passagem por valor): diferença de ângulo (em graus) das partículas em relação ao início da transição.
corFinal (entrada, passagem por valor): coloração das partículas ao final da transição.
deltaOpacidade (entrada, passagem por valor): diferença do nível de opacidade das partículas em relação ao início da transição.
********************************/
void InsereTransicaoParticulas(int idGerador, double tempo, int deltaX, int deltaY, int deltaAlt, int deltaLarg, double deltaAng, PIGCor corFinal, int deltaOpacidade){
    CPIGGerenciadorGDP::GetGerador(idGerador)->InsereTransicao(tempo,{deltaX,deltaY,deltaAlt,deltaLarg,deltaAng,corFinal,deltaOpacidade});
}

/********************************
A função DefineTipoTransicaoParticulas() é responsável por determinar como a sequência de transiçőes das partículas do gerador será executada.
É possível fazê-la uma única vez (PIG_TRANSICAO_NORMAL), em loop (PIG_TRANSICAO_LOOP) ou indo até o final da sequência e retornando, em vai-vém (PIG_TRANSICAO_VAIVEM).
A função deve ser chamada a cada frame, para ter resultados mais precisos.
Parâmetros:
idGerador (entrada, passagem por valor): identificador do gerador.
********************************/
void DefineTipoTransicaoParticulas(int idGerador, PIGTipoTransicao valor){
    CPIGGerenciadorGDP::GetGerador(idGerador)->DefineTipoTransicao(valor);
}

/********************************
A função LimpaTransicoesParticulas() é responsável por remover a sequência de transiçőes das partículas do gerador.
Parâmetros:
idGerador (entrada, passagem por valor): identificador do gerador de partículas.
********************************/
void LimpaTransicoesParticulas(int idGerador){
    CPIGGerenciadorGDP::GetGerador(idGerador)->LimpaTransicoes();
}

/********************************
A função InsereTransicaoGDP() é responsável por criar e inserir uma nova transição ao final de sequência de transiçőes do gerador em si.
Essa transição modifica as características do gerador, que podem se refletir também nas características das partículas que serão posteriormente criadas usando o próprio gerador como modelo.
Parâmetros:
idGerador (entrada, passagem por valor): identificador do gerador.
tempo (entrada, passagem por valor): duracao (em segundos) da transição do gerador.
deltaX (entrada, passagem por valor): diferença da posição no eixo X em relação à posição do gerador no início da transição.
deltaY (entrada, passagem por valor): diferença da posição no eixo Y em relação à posição do gerador no início da transição.
deltaAltura (entrada, passagem por valor): diferença da altura que o modelo terá em relação ao início da transição.
deltaLargura (entrada, passagem por valor): diferença da largura que o modelo terá em relação ao início da transição.
deltaAngulo (entrada, passagem por valor): diferença de ângulo (em graus) que o modelo terá em relação ao início da transição.
corFinal (entrada, passagem por valor): coloração que o modelo terá ao final da transição.
deltaOpacidade (entrada, passagem por valor): diferença do nível de opacidade que o modelo terá em relação ao início da transição.
********************************/
void InsereTransicaoGDP(int idGerador, double tempo, int deltaX, int deltaY, int deltaAlt, int deltaLarg, double deltaAng, PIGCor corFinal, int deltaOpacidade){
    CPIGGerenciadorGDP::GetGerador(idGerador)->InsereTransicaoGDP(tempo,{deltaX,deltaY,deltaAlt,deltaLarg,deltaAng,corFinal,deltaOpacidade});
}

/********************************
A função LeArquivoTransicaoGDP() é responsável por ler, criar e inserir as transiçőes para um gerador, provenientes de um arquivo texto.
Cada linha do arquivo texto corresponde a uma transição (em ordem) e deve possuir 11 valores:
1) um double representando a duracao (em segundos) da transição.
2) um inteiro representando a diferença da posição no eixo X em relação à posição do gerador no início da transição.
3) um inteiro representando a diferença da posição no eixo Y em relação à posição do gerador no início da transição.
4) um inteiro representando a diferença da altura do modelo em relação ao início da transição.
5) um inteiro representando a diferença da largura do modelo em relação ao início da transição.
6) um double representando a diferença de ângulo (em graus) do modelo em relação ao início da transição.
7) um inteiro representando a componente R (vermelho) da coloração do modelo ao final da transição.
8) um inteiro representando a componente G (verde) da coloração do modelo ao final da transição.
9) um inteiro representando a componente B (azul) da coloração do modelo ao final da transição.
10) um inteiro representando a componente A (canal alfa) da coloração do modelo ao final da transição.
11) um inteiro representando a diferença do nível de opacidade do modelo em relação ao início da transição.
Parâmetros:
idGerador (entrada, passagem por valor): identificador do gerador.
nomeArq (entrada, passagem por referência): nome com extensão do arquivo texto contendo as transiçőes.
********************************/
void LeTransicoesGDP(int idGerador, string nomeArq){
    CPIGGerenciadorGDP::GetGerador(idGerador)->LeTransicoesGDP(nomeArq);
}

/********************************
A função IniciaAutomacaoGDP() é responsável por iniciar as transiçőes já inseridas no gerador, de acordo como o tipo de transição informada.
Parâmetros:
idGerador (entrada, passagem por valor): identificador do gerador.
********************************/
void IniciaAutomacaoGDP(int idGerador){
    CPIGGerenciadorGDP::GetGerador(idGerador)->IniciaAutomacaoGDP();
}

/********************************
A função LimpaTransicoesGDP() é responsável por remover a sequência de transiçőes do gerador de partículas em si.
Parâmetros:
idGerador (entrada, passagem por valor): identificador do gerador de partículas.
********************************/
void LimpaTransicoesGDP(int idGerador){
    CPIGGerenciadorGDP::GetGerador(idGerador)->LimpaTransicoesGDP();
}

/********************************
A função ExecutandoTransicaoGDP() retorna a informação sobre a execução (neste momento) de transiçőes do gerador.
Parâmetros:
idGerador (entrada, passagem por valor): identificador do gerador.
Retorno:
inteiro que indica se o gerador está executando alguma transição no momento (valor diferente de 0) ou não (valor igual a 0).
********************************/
bool ExecutandoTransicaoGDP(int idGerador){
    return CPIGGerenciadorGDP::GetGerador(idGerador)->ExecutandoTransicaoGDP();
}

/********************************
A função TrataAutomacaoGDP() é responsável por calcular o estado da transição corrente do gerador e aplicar essas modificação a ela.
A função deve ser chamada a cada frame, para ter resultados mais precisos.
Parâmetros:
idGerador (entrada, passagem por valor): identificador do gerador.
********************************/
void TrataAutomacaoGDP(int idGerador){
    CPIGGerenciadorGDP::GetGerador(idGerador)->TrataAutomacaoGDP();
}

/********************************
A função PausaAutomacaoGDP() é responsável por pausar as transiçőes e açőes associadas a um gerador.
Parâmetros:
idGerador (entrada, passagem por valor): identificador do gerador.
********************************/
void PausaAutomacaoGDP(int idGerador){
    CPIGGerenciadorGDP::GetGerador(idGerador)->PausaAutomacao();
}

/********************************
A função DespausaAutomacaoGDP() é responsável por despausar as transiçőes e açőes associadas a um gerador.
Parâmetros:
idGerador (entrada, passagem por valor): identificador do gerador.
********************************/
void DespausaAutomacaoGDP(int idGerador){
    CPIGGerenciadorGDP::GetGerador(idGerador)->DespausaAutomacao();
}

/********************************
A função InsereAcaoGDP() é responsável por inserir na linha de tempo de automação do gerador uma ação a ser executada.
A ação é composta por uma função "acao" que será executada quando a linha de tempo atingir o parâmetro "tempo" e será repetida a cada "repeticao" segundos.
A ação pode armazenar um ponteiro genérico "param" que será utilizado na chamada da função.
Parâmetros:
idGerador (entrada, passagem por valor): identificador do gerador.
tempo (entrada, passagem por valor): tempo (em segundos) da primeira chamada da função.
repeticao (entrada, passagem por valor): tempo (em segundos) entre a chamada anterior e a próxima. O valor -1 indica que a função não será repetida.
param (entrada, passagem por referência): ponteiro genérico para um valor que será utilizado na chamada da função.
********************************/
void InsereAcaoGDP(int idGerador, double tempo, double repeticao, PIGFuncaoSimples acao, void *param){
    CPIGGerenciadorGDP::GetGerador(idGerador)->InsereAcaoGDP(tempo,repeticao,acao,param);
}

/********************************
A função LimpaAcoesGDP() é responsável por remover as açőes restantes associadas ao gerador.
Parâmetros:
idGerador (entrada, passagem por valor): identificador do gerador.
********************************/
void LimpaAcoesGDP(int idGerador){
    CPIGGerenciadorGDP::GetGerador(idGerador)->LimpaAcoes();
}

/********************************
A função DefineTipoTransicaoGDP() é responsável por determinar como a sequência de transiçőes do gerador de partículas será executada.
É possível fazê-la uma única vez (PIG_TRANSICAO_NORMAL), em loop (PIG_TRANSICAO_LOOP) ou indo até o final da sequência e retornando, em vai-vém (PIG_TRANSICAO_VAIVEM).
A função deve ser chamada a cada frame, para ter resultados mais precisos.
Parâmetros:
idGerador (entrada, passagem por valor): identificador do gerador.
********************************/
void DefineTipoTransicaoGDP(int idGerador, PIGTipoTransicao tipo){
    CPIGGerenciadorGDP::GetGerador(idGerador)->DefineTipoTransicaoGDP(tipo);
}

/********************************
A função SetAnguloParticulas() modifica o ângulo de desenho das partículas após serem criadas.
Somente as partículas criadas posteriormente terão o ângulo especificada.
Parâmetros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da função CriaGeradorParticulas().
angulo (entrada, passagem por valor): informa o angulo das partículas.
********************************/
void SetAnguloParticulas(int idGerador, double angulo){
    CPIGGerenciadorGDP::GetGerador(idGerador)->SetAngulo(angulo);
}

/********************************
A função MudaCorParticulas() é responsável por mesclar uma determinada cor com os pixels do arquivo de imagem da partícula.
Após a modificação, todos os desenhos desta partícula serão mostrados já com a mesclagem definida.
Para voltar ao padrão original de pixels, deve-se chamar a função, passando a cor branca (255,255,255,255).
Parâmetros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da função CriaGeradorParticulas().
cor (entrada,passagem por valor): cor do sistema RGB utilizada para mesclagem com o arquivo de imagem da partícula.
********************************/
void SetCorParticulas(int idGerador, PIGCor cor){
    CPIGGerenciadorGDP::GetGerador(idGerador)->SetColoracao(cor);
}

/********************************
A função SetOpacidadeParticulas() modifica a opacidade das partículas após serem criadas.
Somente as partículas criadas posteriormente terão a opacidade especificada.
Parâmetros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da função CriaGeradorParticulas().
opacidade (entrada, passagem por valor): informa a opacidade das partículas.
********************************/
void SetOpacidadeParticulas(int idGerador, int opacidade){
    CPIGGerenciadorGDP::GetGerador(idGerador)->SetOpacidade(opacidade);
}

/********************************
A função SetDimensoesParticulas() modifica o tamanho das partículas após serem criadas.
Somente as partículas criadas posteriormente terão o tamanho definido.
Parâmetros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da função CriaGeradorParticulas().
altura (entrada, passagem por valor): informa a altura da partícula ao ser criada.
largura (entrada, passagem por valor): informa a largura da partícula ao ser criada.
********************************/
void SetDimensoesParticulas(int idGerador, int altura, int largura){
    CPIGGerenciadorGDP::GetGerador(idGerador)->SetDimensoes(altura,largura);
}

/********************************
A função SetPivoAbsolutoParticulas() determina o ponto a ser considerado como pivo da partícula.
Somente as partículas criadas posteriormente terão o pivô especificado.
Parâmetros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da função CriaGeradorParticulas().
posicaoX (entrada, passagem por valor): Valor da coordenada X do pivô em relação ao ponto (0,0) da partícula.
posicaoY (entrada, passagem por valor): Valor da coordenada Y do pivô em relação ao ponto (0,0) da partícula.
********************************/
void SetPivoAbsolutoParticulas(int idGerador, int posicaoX, int posicaoY){
    CPIGGerenciadorGDP::GetGerador(idGerador)->SetPivoAbsoluto({(double)posicaoX,(double)posicaoY});
}

/********************************
A função SetPivoProporcionalParticula() define um ponto (X,Y) proporcional ao tamanho da partícula, sobre o qual o partícula será
rotacionado quando a função SetAnguloParticula() for executada.
Parâmetros:
idGerador (entrada, passagem por valor): identificador do gerador de partículas.
relX (entrada, passagem por valor): porcentagem da largura da partícula onde ficará o pivô.
relY (entrada, passagem por valor): porcentagem da altura da partícula onde ficará o pivô.
********************************/
void SetPivoProporcionalParticulas(int idGerador, float relX, float relY){
    CPIGGerenciadorGDP::GetGerador(idGerador)->SetPivoProporcional({relX,relY});
}

/********************************
A função CriaParticula() adiciona uma nova partícula ao jogo relacionada com o GDP passado como parâmetro.
A partículas é criada com todas as características (ângulo, cor, tamanho, posição, transiçőes etc) que forem correntes ao gerador neste momento.
Parâmetros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da função CriaGeradorParticulas().
Retorno:
inteiro indicando a quantidade atual de partículas do gerador (valor maior ou igual a zero).
Se a partícula não tiver sido criada por excesso de partículas ativas, o valor retornado é -1.
********************************/
int CriaParticula(int idGerador){
    return CPIGGerenciadorGDP::GetGerador(idGerador)->CriaParticula();
}

/********************************
A função DefineLimitesParticula() é responsável por definir um espaço no cenário onde a partícula será considerada ativa.
Também é definido um tempo de vida máximo, após o qual a partícula não será mais considerada ativa.
Parâmetros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da função CriaGeradorParticulas().
minX (entrada, passagem por valor): valor mínimo de X para que a partícula seja considerada ativa
minY (entrada, passagem por valor): valor mínimo de Y para que a partícula seja considerada ativa
maxX (entrada, passagem por valor): valor máximo de X para que a partícula seja considerada ativa
maxY (entrada, passagem por valor): valor máximo de Y para que a partícula seja considerada ativa
maxTempo (entrada, passagem por valor): tempo máximo de vida da partícula
********************************/
void DefineLimitesParticula(int idGerador, int minX, int minY, int maxX, int maxY, double maxTempo){
    return CPIGGerenciadorGDP::GetGerador(idGerador)->DefineLimites({minX,minY,maxX,maxY},maxTempo);
}

/********************************
A função QuantidadeParticulasAtivas() indica quantas partículas do GDP em questão ainda estão ativas. As partículas deixam de
ser ativas quando saem da tela do jogo, quando colidem com algum objeto ou quando esgotam seu tempo de vida.
Parâmetros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da função CriaGeradorParticulas().
Retorno:
inteiro que indica o número de partículas ativas.
********************************/
int QuantidadeParticulasAtivas(int idGerador){
    return CPIGGerenciadorGDP::GetGerador(idGerador)->GetQtdAtivas();
}

/********************************
A função DesenhaParticulas() desenha todas as partículas ativas do GDP na posição que estiverem.
Parâmetros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da função CriaGeradorParticulas().
********************************/
void DesenhaParticulas(int idGerador){
    CPIGGerenciadorGDP::GetGerador(idGerador)->Desenha();
}

/********************************
A função TestaColisaoParticulasObjeto() indica se houve colisão de alguma partícula ativa do GDP com um outro objeto específico, através do seu identificador.
Parâmetros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da função CriaGeradorParticulas().
idObjeto (entrada, passagem por valor): identificador do objeto que pode ter colidido com as partículas do GDP.
Retorno:
inteiro que indica se houve colisão de alguma partícula ativa do GDP (valor diferente de zero) ou não (valor igual a 0, zero).
********************************/
int TestaColisaoParticulasObjeto(int idGerador, int idObjeto){
    return CPIGGerenciadorGDP::GetGerador(idGerador)->Colisao(CPIGGerenciadorSprites::GetObjeto(idObjeto));
}

/********************************
A função TestaColisaoParticulasAnimacao() indica se houve colisão de alguma partícula ativa do GDP com uma outra animção específica, através do seu identificador.
Parâmetros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da função CriaGeradorParticulas().
idAnimacao (entrada, passagem por valor): identificador da animação que pode ter colidido com as partículas do GDP.
Retorno:
inteiro que indica se houve colisão de alguma partícula ativa do GDP (valor diferente de zero) ou não (valor igual a 0, zero).
********************************/
int TestaColisaoParticulasAnimacao(int idGerador, int idAnimacao){
    return CPIGGerenciadorGDP::GetGerador(idGerador)->Colisao(CPIGGerenciadorSprites::GetAnimacao(idAnimacao));
}


/********************************
Seção dos temporizadores
********************************/

/********************************
A função CriaTimer() é responsável por criar um timer (temporizador). Após a criação o tempo decorrido
poderá ser obtido a partir da função TempoDecorrido(), informando o identificador que é passado na resposta.
Parâmetros:
congelado (entrada, passagem por valor): valor lógico que indica se o timer deve ser criado sem iniciar de imediato a contagem de tempo ou não.
Retorno:
inteiro que identifica o timer criado.
********************************/
int CriaTimer(int congelado=false){
    return CPIGGerenciadorTimers::CriaTimer(congelado);
}

/********************************
A função TempoDecorrido() é responsável por informar o tempo decorrido desde a criação do timer
até a hora em que a função for chamada.
Parâmetros:
idTimer (entrada, passagem por valor): identificador do timer.
Retorno:
número real indicando o tempo (em segundos) desde a criação do timer.
********************************/
double TempoDecorrido(int idTimer){
    return CPIGGerenciadorTimers::GetTimer(idTimer)->GetTempoDecorrido();
}

/********************************
A função PausaTimer() é responsável por realizar uma pausa na contagem do tempo de um timer. Após a despausa,
o timer continuará a contar o tempo normalmente.
Parâmetros:
idTimer (entrada, passagem por valor): identificador do timer.
********************************/
void PausaTimer(int idTimer){
    CPIGGerenciadorTimers::GetTimer(idTimer)->Pausa();
}

/********************************
A função PausaTudo() é responsável por realizar uma pausa na contagem do tempo de todos os timers
criados pela função CriaTimer();
********************************/
void PausaTudo(){
    CPIGGerenciadorTimers::PausaTodos();
}

/********************************
A função DespausaTimer() é responsável por retomar a contagem do tempo de todos os timers após uma pausa.
Parâmetros:
idTimer (entrada, passagem por valor): identificador do timer.
********************************/
void DespausaTimer(int idTimer){
    CPIGGerenciadorTimers::GetTimer(idTimer)->Despausa();
}

/********************************
A função DespausaTudo() é responsável por retomar a contagem do tempo de todos os timers
criados pela função CriaTimer();
********************************/
void DespausaTudo(){
    CPIGGerenciadorTimers::DespausaTodos();
}

/********************************
A função ReiniciaTimer() é responsável por zerar a contagem do tempo de um timer, idependente do tempo já decorrido.
Na prática, é equivalente a encerrer um temporizador e recriá-lo em seguida.
Parâmetros:
idTimer (entrada, passagem por valor): identificador do timer.
congelado (entrada, passagem por valor): valor lógico que indica se o timer deve ser zerado sem iniciar de imediato a contagem de tempo ou não.
********************************/
void ReiniciaTimer(int idTimer, int congelado=false){
    CPIGGerenciadorTimers::GetTimer(idTimer)->Reinicia(congelado);
}

/********************************
A função DestroiTimer() é responsável por encerrar a utilização de timer.
Seu identificador não poderá ser utilizado após a função ser executada.
Parâmetros:
idTimer (entrada, passagem por valor): identificador do timer.
********************************/
void DestroiTimer(int idTimer){
    CPIGGerenciadorTimers::DestroiTimer(idTimer);
}

/********************************
A função AssociaGrupoTimer() é responsável por associar um timer a um grupo específico.
Os timers de um mesmo grupo pode ser tratados simultaneamente
(ex: diversos timers de um prsonagem/objeto podem ser pausados/despausados/reiniciados com uma função só).
Parâmetros:
idTimer (entrada, passagem por valor): identificador do timer.
idGrupo (entrada, passagem por valor): identificador do grupos (qualquer valor entre 0 e PIG_MAX_GRUPOS_TIMERS-1).
Retorno:
número inteiro que indica se o grupo é válido (1) ou não (0).
********************************/
int AssociaGrupoTimer(int idTimer, int idGrupo){
    return CPIGGerenciadorTimers::AssociaTimerGrupo(idTimer,idGrupo);
}

/********************************
A função DesassociaGrupoTimer() é responsável por desassociar um timer de um grupo específico.
Os timers de um mesmo grupo pode ser tratados simultaneamente
(ex: diversos timers de um prsonagem/objeto podem ser pausados/despausados/reiniciados com uma função só).
Parâmetros:
idTimer (entrada, passagem por valor): identificador do timer.
idGrupo (entrada, passagem por valor): identificador do grupos (qualquer valor entre 0 e PIG_MAX_GRUPOS_TIMERS-1).
Retorno:
número inteiro que indica se o grupo é válido (1) ou não (0).
********************************/
int DesassociaGrupoTimer(int idTimer, int idGrupo){
    return CPIGGerenciadorTimers::DesassociaTimerGrupo(idTimer,idGrupo);
}

/********************************
A função PausaGrupoTimers() é responsável por pausar todos os timers de um grupo específico.
Os timers de um mesmo grupo pode ser tratados simultaneamente
(ex: diversos timers de um prsonagem/objeto podem ser pausados/despausados/reiniciados com uma função só).
Parâmetros:
idGrupo (entrada, passagem por valor): identificador do grupos (qualquer valor entre 0 e PIG_MAX_GRUPOS_TIMERS-1).
Retorno:
número inteiro que indica se o grupo é inválido (-1) ou quantos timers foram pausados no grupo (maior ou igual a 0).
********************************/
int PausaGrupoTimers(int idGrupo){
    return CPIGGerenciadorTimers::PausaGrupo(idGrupo);
}

/********************************
A função DespausaGrupoTimers() é responsável por despausar todos os timers de um grupo específico.
Os timers de um mesmo grupo pode ser tratados simultaneamente
(ex: diversos timers de um prsonagem/objeto podem ser pausados/despausados/reiniciados com uma função só).
Parâmetros:
idGrupo (entrada, passagem por valor): identificador do grupos (qualquer valor entre 0 e PIG_MAX_GRUPOS_TIMERS-1).
Retorno:
número inteiro que indica se o grupo é inválido (-1) ou quantos timers foram despausados no grupo (maior ou igual a 0).
********************************/
int DespausaGrupoTimers(int idGrupo){
    return CPIGGerenciadorTimers::DespausaGrupo(idGrupo);
}

/********************************
A função ReiniciaGrupoTimers() é responsável por reiniciar todos os timers de um grupo específico.
Os timers de um mesmo grupo pode ser tratados simultaneamente
(ex: diversos timers de um prsonagem/objeto podem ser pausados/despausados/reiniciados com uma função só).
Parâmetros:
idGrupo (entrada, passagem por valor): identificador do grupos (qualquer valor entre 0 e PIG_MAX_GRUPOS_TIMERS-1).
congelado (entrada, passagem por valor): valor lógico que indica se o timer deve ser zerado sem iniciar de imediato a contagem de tempo ou não.
Retorno:
número inteiro que indica se o grupo é inválido (-1) ou quantos timers foram reiniciados no grupo (maior ou igual a 0).
********************************/
int ReiniciaGrupoTimers(int idGrupo, int congelado=false){
    return CPIGGerenciadorTimers::ReiniciaGrupo(idGrupo,congelado);
}



/********************************
Seção das animaçőes
********************************/

/********************************
A função CriaAnimacao() é responsável por criar uma animacao. A animação pode ser considerada um tipo especial
de objeto, capaz de mudar de figura (sprite) dentro de um tempo determinado. Uma sequência completa de
sprites é chamada de modo. Uma mesma animação pode apresentar vários modos diferentes.
Para que a animação funcione corretamente, será necessário: definir cada frame (pedaço do arquivo bitmap que contém o sprite desejado),
criar um ou mais modos, inserir os frames criados no modo correspondente e dizer qual modo deverá ser exibido inicialmente.
Tudo isso pode ser feito por outras funçőes que manipulam as animaçőes.
Parâmetros:
nomeArquivo (entrada, passagem por referência): string que informa o nome do arquivo da imagem (spritesheet) da animação.
retiraFundo (entrada, passagem por valor): inteiro que indica se o fundo da imagem deve ser retirado ou não ao ler o arquivo em questão. O valor padrão é 1, indicando que o fundo deve ser retirado.
corFundo (entrada, passagem por referência não-obrigatório): indica se há uma cor específica para ser considerada como cor de fundo da imagem. Caso, o valor seja NULL, mas o parâmetro retiraFundo seja diferente de 0, o pixel (0,0) da imagem será considerado como cor de fundo.
idJanela (entrada, passagem por valor não-obrigatório): indica qual janela vai receber a animação.
Retorno:
inteiro que representa o identificador único da animação. Todas as operaçőes subsequentes com esta animação deverão receber este identificador como parâmetro.
********************************/
int CriaAnimacao(char* nomeArquivo, int retiraFundo=1, PIGCor *corFundo=NULL, int idJanela=0){
    return CPIGGerenciadorSprites::CriaAnimacao(nomeArquivo,retiraFundo,corFundo,idJanela);
}

/********************************
A função CriaAnimacao() é responsável por criar uma animacao a partir de outra já existente. A animação pode ser considerada um tipo especial
de objeto, capaz de mudar de figura (sprite) dentro de um tempo determinado. Uma sequência completa de
sprites é chamada de modo. Uma mesma animação pode apresentar vários modos diferentes.
Esta forma de criar uma animação, copia todos os frames e modos de outra animação já existente, evitando assim
que toda esta preparação precise ser feita novamente. O usuário deve ter cuidado de não destruir a animação
original enquanto as cópias estiverem ativas ou haverá erros de execução. Da mesma forma, não se deve alterar os
frames ou os modos da cópia, pois pode provocar erros na animação original.
Parâmetros:
idAnimacao (entrada, passagem por valor): indica o identificador da animação original que será copiada.
retiraFundo (entrada, passagem por valor): inteiro que indica se o fundo da imagem deve ser retirado ou não ao ler o arquivo em questão. O valor padrão é 1, indicando que o fundo deve ser retirado.
corFundo (entrada, passagem por referência não-obrigatório): indica se há uma cor específica para ser considerada como cor de fundo da imagem. Caso, o valor seja NULL, mas o parâmetro retiraFundo seja diferente de 0, o pixel (0,0) da imagem será considerado como cor de fundo.
idJanela (entrada, passagem por valor não-obrigatório): indica qual janela vai receber a animação.
Retorno:
inteiro que representa o identificador único da animação. Todas as operaçőes subsequentes com esta animação deverão receber este identificador como parâmetro.
********************************/
int CriaAnimacao(int idAnimacao, int retiraFundo=1, PIGCor *corFundo=NULL, int idJanela=0){
    return CPIGGerenciadorSprites::CriaAnimacao(CPIGGerenciadorSprites::GetAnimacao(idAnimacao),retiraFundo,corFundo,idJanela);
}

/********************************
A função CriaAnimacaoDeObjeto() é responsável por criar uma animacao a partir de um objeto já existente. A animação pode ser considerada um tipo especial
de objeto, capaz de mudar de figura (sprite) dentro de um tempo determinado. Uma sequência completa de
sprites é chamada de modo. Uma mesma animação pode apresentar vários modos diferentes.
Esta forma de criar uma animação, copia todos os frames e modos de outra animação já existente, evitando assim
que toda esta preparação precise ser feita novamente. O usuário deve ter cuidado de não destruir a animação
original enquanto as cópias estiverem ativas ou haverá erros de execução. Da mesma forma, não se deve alterar os
frames ou os modos da cópia, pois pode provocar erros na animação original.
Parâmetros:
idObjeto (entrada, passagem por valor): indica o identificador do objeto original que servirá de base para a criação da animação.
retiraFundo (entrada, passagem por valor): inteiro que indica se o fundo da imagem deve ser retirado ou não ao ler o arquivo em questão. O valor padrão é 1, indicando que o fundo deve ser retirado.
corFundo (entrada, passagem por referência não-obrigatório): indica se há uma cor específica para ser considerada como cor de fundo da imagem. Caso, o valor seja NULL, mas o parâmetro retiraFundo seja diferente de 0, o pixel (0,0) da imagem será considerado como cor de fundo.
idJanela (entrada, passagem por valor não-obrigatório): indica qual janela vai receber a animação.
Retorno:
inteiro que representa o identificador único da animação. Todas as operaçőes subsequentes com esta animação deverão receber este identificador como parâmetro.
********************************/
int CriaAnimacaoDeObjeto(int idObjeto, int retiraFundo=1, PIGCor *corFundo=NULL, int idJanela=0){
    return CPIGGerenciadorSprites::CriaAnimacao(CPIGGerenciadorSprites::GetObjeto(idObjeto),retiraFundo,corFundo,idJanela);
}


/********************************
A função DestroiAnimacao() é responsável por eliminar a animação em questão do jogo.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação a ser excluída.
********************************/
void DestroiAnimacao(int idAnimacao){
    CPIGGerenciadorSprites::DestroiSprite(idAnimacao);
}

/********************************
A função CriaFrameAnimacao() é responsável por estabelecar uma parte do sprisheet da animação que contém um sprite específico.
O frame criado deve ser posteriormente inserido em um ou mais modos da animação. O posicionamento do frame
respeita o sistema de coordenadas dos arquivos de imagem, com o eixo Y aumentando para baixo.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação a ter um novo frame.
codigoFrame (entrada, passagem por valor): numero do frame a ser criado. Pode ser usado qualquer número de 0..MAX_FRAMES-1.
xBitmap (entrada, passagem por valor): indica a posição de eixo X onde começa o frame.
yBitmap (entrada, passagem por valor): indica a posição de eixo Y onde começa o frame. Neste caso, o eixo Y aumenta para baixo.
altura (entrada, passagem por valor): altura em pixels do frame.
largura (entrada, passagem por valor): largura em pixels do frame.
********************************/
void CriaFrameAnimacao(int idAnimacao, int codigoFrame, int xBitmap, int yBitmap, int altura, int largura){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->DefineFrame(codigoFrame,{xBitmap,yBitmap,largura,altura});
}

/********************************
A função CarregaArquivoFramesAnimacao() é responsável por ler de arquivo texto os frames de uma animação.
Cada linha do arquivo texto deve conter 5 números inteiros: o número do frame, a posição do frame no eixo X do arquivo de imagem,
a posição do frame no eixo Y do arquivo de imagem, a altura do frame e a largura do frame (todas as unidades em pixels).
Parâmetros:
idObjeto (entrada, passagem por valor): identificador da animação.
nomeArq (entrada, passagem por referência): nome do arquivo texto contendo os frames.
********************************/
void CarregaArquivoFramesAnimacao(int idAnimacao, char *nomeArq){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->CarregaArquivoFrames(nomeArq);
}

/********************************
A função CarregaFramesPorLinhaAnimacao() é responsável por subdividir o arquivo de imagem em linhas (de mesmo tamanho) e colunas (de mesmo tamanho).
Cada subdivisão representará um frame que será automaticamente criado para a animação, com numeração incremental a partir do parâmetro "frameInicial".
Ao final das "qtdColunas" da primeira linha, a definição dos frames continua na linha inferior.
A função pode ser utilizada em spritesheets regulares.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação.
frameInicial (entrada, passagem por valor): numeração do primeiro frame a ser criado pela função. Os demais frames terão numeração consecutiva.
qtdLinhas (entrada, passagem por valor): quantidade de linhas na qual o arquivo de imagem será dividido.
qtdColunas (entrada, passagem por valor): quantidade de colunas na qual o arquivo de imagem será dividido.
********************************/
void CarregaFramesPorLinhaAnimacao(int idAnimacao, int frameInicial, int qtdLinhas, int qtdColunas){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->CriaFramesAutomaticosPorLinha(frameInicial,qtdLinhas,qtdColunas);
}

/********************************
A função CarregaFramesPorColunaAnimacao() é responsável por subdividir o arquivo de imagem em linhas (de mesmo tamanho) e colunas (de mesmo tamanho).
Cada subdivisão representará um frame que será automaticamente criado para a animação, com numeração incremental a partir do parâmetro "frameInicial".
Ao final das "qtdLinhas" da primeira coluna, a definição dos frames continua na coluna seguinte.
A função pode ser utilizada em spritesheets regulares.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação.
frameInicial (entrada, passagem por valor): numeração do primeiro frame a ser criado pela função. Os demais frames terão numeração consecutiva.
qtdLinhas (entrada, passagem por valor): quantidade de linhas na qual o arquivo de imagem será dividido.
qtdColunas (entrada, passagem por valor): quantidade de colunas na qual o arquivo de imagem será dividido.
********************************/
void CarregaFramesPorColunaAnimacao(int idAnimacao, int frameInicial, int qtdLinhas, int qtdColunas){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->CriaFramesAutomaticosPorColuna(frameInicial,qtdLinhas,qtdColunas);
}

/********************************
A função CriaModoAnimacao() é responsável por criar um modo, ou seja, uma sequência de sprites.
Após a criação do modo, os frames deve ser inseridos um a um. O modo pode ser criado antes dos frames
e vice-versa, mas os frames só podem ser associados ao modo, após as respectivas criaçőes.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação a ter um novo modo.
codigoModo (entrada, passagem por valor): numero do modo a ser criado. Pode ser usado qualquer número de 0..MAX_MODOS-1.
loop (entrada, passagem por valor): valor lógico que indica se este modo deve recomeçar do primeiro frame após a execução do último.
********************************/
void CriaModoAnimacao(int idAnimacao, int codigoModo, int loop){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->CriaModo(codigoModo,loop);
}

/********************************
A função InsereFrameAnimacao() é responsável por associar os frames aos modos correspondentes.
Um mesmo frame pode fazer parte de diversos modos.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação em questão.
codigoModo (entrada, passagem por valor): numero do modo a ter um frame inserido.
codigoFrame (entrada, passagem por valor): numero do frame a ser inserido no modo.
tempo (entrada, passagem por valor): duração (em segundos) da exibição automática do frame neste modo específico.
idAudio (entrada, passagem por valor não-obrigatório): identificador do audio (já criado anteriormente) que deve ser tocado quando o frame for exibido. O valor -1 deve ser utilizado se nenhum audio deve ser tocado.
alturaAnimacao (entrada, passagem por valor não-obrigatório): tamanho em pixels altura da animação quando estiver exibindo este frame. Um valor negativo neste parâmetro ou no próximo (larguraAnimacao) indica que não haverá alteração de dimensőes da animação.
larguraAnimacao (entrada, passagem por valor não-obrigatório): tamanho em pixels largura da animação quando estiver exibindo este frame. Um valor negativo neste parâmetro ou no anterior (alturaAnimacao) indica que não haverá alteração de dimensőes da animação.
********************************/
void InsereFrameAnimacao(int idAnimacao, int codigoModo, int codigoFrame, float tempo, int idAudio=-1, int alturaAnimacao=-1, int larguraAnimacao=-1){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->InsereFrame(codigoModo,codigoFrame,tempo,idAudio,alturaAnimacao,larguraAnimacao);
}


/********************************
A função InsereAudioFrameAnimacao() é responsável por acrescentar um audio a um dos frames.
O audio é tocado assim que o frame é desenhado pela primeira vez.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação em questão.
codigoModo (entrada, passagem por valor): número do modo a ter um frame inserido.
indiceFrame (entrada, passagem por valor): índice (posição) do frame no modo em questão.
idAudio (entrada, passagem por valor não-obrigatório): identificador do audio (já criado anteriormente) que deve ser tocado quando o frame for exibido. O valor -1 deve ser utilizado se nenhum audio deve ser tocado.
********************************/
void InsereAudioFrameAnimacao(int idAnimacao, int codigoModo, int indiceFrame, int idAudio){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetAudioFrame(codigoModo,indiceFrame,idAudio);
}

/********************************
A função MudaModoAnimacao() é responsável por alterar a animação para um outro modo.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação em questão.
codigoModo (entrada, passagem por valor): numero do novo modo.
indiceFrame (entrada, passagem por valor): indica a partir de qual frame o modo deve ser exibido. O valor 0 significa aprtir do primeiro frame.
forcado (entrada, passagem por valor): valor lógico que indica se a mudança de modo deve ser feita forçosamente ou não. Se não for forçada, a mudança só ocorrerá se o modo atual já tiver terminado de ser animado.
********************************/
void MudaModoAnimacao(int idAnimacao, int codigoModo, int indiceFrame, int forcado=1){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->MudaModo(codigoModo,indiceFrame,forcado);
}

/********************************
A função GetModoAtualAnimacao() é responsável por recuperar o valor do modo atual da animação.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação em questão.
Retorno:
inteiro que representa o modo atual da animação.
********************************/
int GetModoAtualAnimacao(int idAnimacao){
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetModoAtual();
}

/********************************
A função GetFrameAtualAnimacao() recupera o valor do frame atual exibido na animação.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação.
Retorno:
Número do frame atual da animação.
********************************/
int GetFrameAtualAnimacao(int idAnimacao){
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetFrameAtual();
}

/********************************
A função TestaColisaoAnimacoes() indica se houve colisão entre duas animaçőes, de forma semelhante aos objetos.
Parâmetros:
idAnimacao1 (entrada, passagem por valor): identificador da primeira animação.
idAnimacao2 (entrada, passagem por valor): identificador da segunda animação.
Retorno:
inteiro que indica se houve colisão entre as animaçőes.
********************************/
int TestaColisaoAnimacoes(int idAnimacao1, int idAnimacao2){
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao1)->Colisao(CPIGGerenciadorSprites::GetAnimacao(idAnimacao2));
}

/********************************
A função TestaColisaoAnimacaoObjeto() indica se houve colisão de alguma animacao com algum outro objeto específico, através do seu identificador.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação que pode ter colidido com o objeto.
idObjeto (entrada, passagem por valor): identificador do objeto que pode ter colidido com a animação.
Retorno:
inteiro que indica se houve colisão da animação com o objeto.
********************************/
int TestaColisaoAnimacaoObjeto(int idAnimacao, int idObjeto){
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->Colisao(CPIGGerenciadorSprites::GetObjeto(idObjeto));
}


/********************************
A função DefineAreaColisaoObjeto() é responsável estabelecer um polígono que será utilizado como área de colisão da animação com as demais.
Os vetores X e Y deve ter pelo menos qtdPontos elementos.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação.
pontosX (entrada, passagem por referência): vetor de inteiros, de tamanho qtdPontos, contendo os valores X de cada ponto do polígono.
pontosY (entrada, passagem por referência): vetor de inteiros, de tamanho qtdPontos, contendo os valores Y de cada ponto do polígono.
qtdPontos (entrada, passagem por valor): quantidade de pontos da animação.
********************************/
void DefineAreaColisaoAnimacao(int idAnimacao, int pontosX[], int pontosY[], int qtdPontos) {
    vector<PIGPonto2D> vertices;

    for (int i = 0; i < qtdPontos; i++) {
        vertices.push_back({(double)pontosX[i], (double)pontosY[i]});
    }

    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetVertices(vertices);
}

/********************************
A função DefineRaioColisaoAnimacao() é responsável por estabelecer um raio, em relação ao pivô da animação, que será utilizado para teste de colisão circular desta animação com as demais.
A definição do raio só será útil se o tipode colisão deste objeto for circular, definido pela função DefineTipoColisaoObjeto().
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação.
raio (entrada, passagem por valor): tamanho do raio que formará a área de colisão desta animação.
********************************/
void DefineRaioColisaoAnimacao(int idAnimacao, float raio){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetRaioColisaoCircular(raio);
}

/********************************
A função DefineTipoColisaoAnimacao() é responsável por definir o tipod e colisão que será utilizada por esta animação com as demais.
É possível ter 3 tipos de colisão: por bouding-box (PIG_COLISAO_OOBB - área de colisão delimitada pelo ponto X,Y da animação, sua altura e largura e rotação),
por polígono (PIG_COLISAO_POLIGONO) área de colisão formada por pontos genéricos) e circular (PIG_COLISAO_CIRCULAR) área de colisão em forma de círculo, com raio definido a partir do ponto pivô)
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação.
modo (entrada, passagem por valor): modo de colisão a ser utilizado por esta animação.
********************************/
void DefineTipoColisaoAnimacao(int idAnimacao, PIGModoColisao modo){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetModoColisao(modo);
}

/********************************
A função DesenhaAnimacao() é responsável por desenhar uma animação na tela. A animação será desenhada de acordo com o modo atual da animação,
fazendo com que os frames sejam automaticamente ajustados de acordo com o tempo estipulado. Caso o modo atual esteja em loop, o primeiro frame será
desenhado novamente logo após o término do último frame.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação a ser desenhada.
Retorno:
inteiro que indica se a animação encerrou ou não. O valor só será diferente de zero, se o modo atual também não estiver em loop.
********************************/
int DesenhaAnimacao(int idAnimacao){
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->Desenha();
}

/********************************
A função MoveAnimacao() é responsável por movimentar uma determinada animação para uma nova posição informada.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação a ser movida.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usuário deseja reposicionar a animação.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usuário deseja reposicionar a animação.
********************************/
void MoveAnimacao(int idAnimacao, int x, int y){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->Move(x,y);
}

/********************************
A função DeslocaAnimcao() é responsável por deslocar uma determinada animacao em relação à sua posição atual.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animacao a ser deslocada.
deltaX (entrada, passagem por valor): valor a ser somado ou subtraído na componente X da posição da animação.
deltaY (entrada, passagem por valor): valor a ser somado ou subtraído na componente Y da posição da animação.
********************************/
void DeslocaAnimacao(int idAnimacao, int deltaX, int deltaY){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->Desloca(deltaX,deltaY);
}

/********************************
A função SetLoopModoAnimacao() é responsável por definir a existência ou não de loop em um modo de uma animação.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animacao a ser deslocada.
codigoModo (entrada, passagem por valor): numero do modo em questão.
loop (entrada, passagem por valor): valor que indica a existência (diferente de zero) ou não (igual a zero) de loop no modo em questão.
********************************/
void SetLoopModoAnimacao(int idAnimacao, int modo, int loop){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetLoopModo(modo,loop);
}

/********************************
A função SetTempoFrameAnimacao() é responsável por definir uma nova duração para exibição do frame.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animacao a ser deslocada.
codigoModo (entrada, passagem por valor): numero do modo em questão.
indiceFrame (entrada, passagem por valor): indica a partir de qual frame o modo deve ser exibido. O valor 0 significa aprtir do primeiro frame.
tempo (entrada, passagem por valor): valor que indica a nova duração de exibição do frame, em segundos.
********************************/
void SetTempoFrameAnimacao(int idAnimacao, int modo, int indiceFrame, float tempo){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetTempoFrame(modo,indiceFrame,tempo);
}

/********************************
A função SetAudioFrameAnimacao() é responsável por definir um novo audio a ser executado quando o frame em questão começar a ser exibido.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animacao a ser deslocada.
codigoModo (entrada, passagem por valor): numero do modo em questão.
indiceFrame (entrada, passagem por valor): indica a partir de qual frame o modo deve ser exibido. O valor 0 significa aprtir do primeiro frame.
idAudio (entrada, passagem por valor): identificador do audio (já criado) a ser tocado quando o frame começar a ser exibido.
********************************/
void SetAudioFrameAnimacao(int idAnimacao, int modo, int indiceFrame, int idAudio){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetAudioFrame(modo,indiceFrame,idAudio);
}

/********************************
A função GetLoopModoAnimacao() é responsável por recuperar a existência ou não de loop em um modo de uma animação.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animacao a ser deslocada.
codigoModo (entrada, passagem por valor): numero do modo em questão.
Retorno:
inteiro que indica a existência (diferente de zero) ou não (igual a zero) de loop no modo em questão.
********************************/
int GetLoopModoAnimacao(int idAnimacao, int modo){
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetLoopModo(modo);
}

/********************************
A função GetAudioFrameAnimacao() é responsável por recuprar o identificador do audio a ser executado quando o frame em questão começar a ser exibido.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animacao a ser deslocada.
codigoModo (entrada, passagem por valor): numero do modo em questão.
indiceFrame (entrada, passagem por valor): indica a partir de qual frame o modo deve ser exibido. O valor 0 significa aprtir do primeiro frame.
Retorno:
inteiro que representa o identificador do audio (já criado) a ser tocado quando o frame começar a ser exibido.
********************************/
int GetAudioFrameAnimacao(int idAnimacao, int modo, int indiceFrame){
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetAudioFrame(modo,indiceFrame);
}

/********************************
A função GetTempoFrameAnimacao() é responsável por recuperar a duração da exibição do frame.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animacao a ser deslocada.
codigoModo (entrada, passagem por valor): numero do modo em questão.
indiceFrame (entrada, passagem por valor): indica a partir de qual frame o modo deve ser exibido. O valor 0 significa aprtir do primeiro frame.
Retorno:
float que indica a nova duração de exibição do frame, em segundos.
********************************/
float GetTempoFrameAnimacao(int idAnimacao, int modo, int indiceFrame){
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetTempoFrame(modo,indiceFrame);
}

/********************************
A função PausaAnimacao() é responsável por pausar a exibição dos frames da animação.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animacao a ser deslocada.
********************************/
void PausaAnimacao(int idAnimacao){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->Pausa();
}

/********************************
A função DespausaAnimacao() é responsável por despausar a exibição dos frames da animação.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animacao a ser deslocada.
********************************/
void DesausaAnimacao(int idAnimacao){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->Despausa();
}

/********************************
A função SetOpacidadeAnimacao() é responsável por modificar o nível de opacidade da animação.
O nível de opacidade varia de 0-255, sendo 0 totalmente transparente e 255 totalmente opaco.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação.
valor (entrada,passagem por valor): nível de opacidade da animação na faixa 0-255.
********************************/
void SetOpacidadeAnimacao(int idAnimacao, int valor){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetOpacidade(valor);
}

/********************************
A função GetOpacidadeAnimacao() é responsável por recuperar o nível de opacidade da animação.
O nível de opacidade varia de 0-255, sendo 0 totalmente transparente e 255 totalmente opaco.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação.
Retorno:
Retorna o nível de opacidade da animação na faixa 0-255.
********************************/
int GetOpacidadeAnimacao(int idAnimacao){
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetOpacidade();
}

/********************************
A função SetColoracaoAnimacao() é responsável por mesclar uma determinada cor com os pixels do arquivo de imagem.
Após a modificação, todos os desenhos desta animação serão mostrados já com a mesclagem definida.
Para voltar ao padrão original de pixels, deve-se chamar a função, passando a cor branca (255,255,255,255).
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação a ser desenhado.
cor (entrada,passagem por valor): cor do sistema RGB utilizada para mesclagem com o arquivo de imagem
********************************/
void SetColoracaoAnimacao(int idAnimacao, PIGCor cor){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetColoracao(cor);
}

/********************************
A função SetFlipAnimacao() é responsável por virar a animação, invertendo-a em alguma direção. A animação somente será
desenhada na nova orientação no próximo comando DesenhaAnimacao().
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação a ser virada.
valor (entrada, passagem por valor): valor do tipo de Flip. Pode ser PIG_FLIP_NENHUM (nenhum tipo de inversão),
PIG_FLIP_HORIZONTAL (inverte da esquerda para a direita), PIG_FLIP_VERTICAL (inverte de cima para baixo),
ou PIG_FLIP_HORIZ_VERT (inverte da esquerda para direita e de cima para baixo).
********************************/
void SetFlipAnimacao(int idAnimacao, PIGFlip valor){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetFlip(valor);
}

/********************************
A função GetFlipAnimacao() é responsável por recuperar o valor da manipulação causada pela função SetFlipAnimacao().
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação a ser virada.
Retorno:
inteiro que indica o tipo de Flip. Pode ser PIG_FLIP_NENHUM (nenhum tipo de inversão),
PIG_FLIP_HORIZONTAL (inverte da esquerda para a direita), PIG_FLIP_VERTICAL (inverte de cima para baixo),
ou PIG_FLIP_HORIZ_VERT (inverte da esquerda para direita e de cima para baixo).
********************************/
PIGFlip GetFlipAnimacao(int idAnimacao){
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetFlip();
}

/********************************
A função SetAnguloAnimacao() é responsável pela angulação de determinada animacao. A angulação é calculada em sentido
horário a partir do eixo X (0 graus). A animação será desenhada com a angulação informada no próximo comando
DesenhaAnimcao(). A detecção de colisão não funciona com animaçőes fora da angulação padrão (0 graus).
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação.
angulo (entrada, passagem por valor): valor para indicar a angulação da animação em graus.
********************************/
void SetAnguloAnimacao(int idAnimacao, double angulo){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetAngulo(angulo);
}

/********************************
A função GetAnguloAnimacao() é responsável por recuperar o ângulo de rotação de determinada animação. A angulação é calculada em sentido
horário a partir do eixo X (0 graus). A animação será desenhada com a angulação informada no próximo comando
DesenhaAnimacao(). A detecção de colisão não funciona com animaçőes fora da angulação padrão (0 graus).
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação.
Retorno:
Retorna o valor do ângulo em graus.
********************************/
double GetAnguloAnimacao(int idAnimacao){
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetAngulo();
}

/********************************
A função SetPivoAbsolutoAnimacao() define um ponto (X,Y) em relação ao ponto (0,0) da animação, sobre o qual a animação será
rotacionado quando a função SetAnguloAnimacao() for executada.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação.
posicaoX (entrada, passagem por valor): Valor da coordenada X do pivô em relação ao ponto (0,0) da animação.
posicaoY (entrada, passagem por valor): Valor da coordenada Y do pivô em relação ao ponto (0,0) da animação.
********************************/
void SetPivoAbsolutoAnimacao(int idAnimacao, int posicaoX, int posicaoY){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetPivoAbsoluto({(double)posicaoX,(double)posicaoY});
}

/********************************
A função SetPivoProporcionalAnimacao() define um ponto (X,Y) proporcional ao tamanho da animação, sobre o qual a animação será
rotacionado quando a função SetAnguloAnimacao() for executada.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação.
relX (entrada, passagem por valor): porcentagem da largura da animação onde ficará o pivô.
relY (entrada, passagem por valor): porcentagem da altura da animação onde ficará o pivô.
********************************/
void SetPivoProporcionalAnimacao(int idAnimacao, float relX, float relY){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetPivoProporcional({relX,relY});
}

/********************************
A função GetPivoAnimacao() define um ponto (X,Y) em relação ao ponto (0,0) da animacao, sobre o qual a animação será
rotacionado quando a função SetAnguloAnimacao() for executada.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação.
posicaoX (saída, passagem por referência): Valor da coordenada X do pivô em relação ao ponto (0,0) da animação.
posicaoY (saída, passagem por referência): Valor da coordenada Y do pivô em relação ao ponto (0,0) da animação.
********************************/
void GetPivoAnimacao(int idAnimacao, int *posicaoX, int *posicaoY){
    PIGPonto2D p = CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetPivo();
    *posicaoX = p.x;
    *posicaoY = p.y;
}

/********************************
A função SetDimensoesAnimacao() é responsável por delimitar a altura e a largura da animação que será desenhada na tela,
independentemente do tamanho original do arquivo de imagem.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação.
altura (entrada, passagem por valor): altura em pixels.
largura (entrada, passagem por valor): largura em pixels.
********************************/
void SetDimensoesAnimacao(int idAnimacao, int altura, int largura){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetDimensoes(altura,largura);
}

/********************************
A função GetDimensoesAnimacao() é responsável por recuperar a altura e a largura da área a ser usada
para desenhar a animação na tela. Em outras palavras, representa o tamanho atual da animação.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador da animação.
altura (saída, passagem por referência): altura atual em pixels da animação.
largura (saída, passagem por referência): largura atual em pixels da animação.
********************************/
void GetDimensoesAnimacao(int idAnimacao, int *altura, int *largura){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetDimensoes(*altura,*largura);
}

/********************************
A função SetValorIntAnimacao() é responsável incorporar a uma animação um atributo inteiro.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação.
indice (entrada, passagem por valor): relaciona um número inteiro ao atributo.
valor (entrada, passagem por valor): valor do atributo inteiro a ser associado à animação.
********************************/
void SetValorIntAnimacao(int idAnimacao, int indice, int valor){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetValorInt(indice,valor);
}

/********************************
A função SetValorFloatAnimacao() é responsável incorporar a uma animação um atributo float.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação.
indice (entrada, passagem por valor): relaciona um número inteiro ao atributo.
valor (entrada, passagem por valor): valor do atributo float a ser associado à animação.
********************************/
void SetValorFloatAnimacao(int idAnimacao, int indice, float valor){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetValorFloat(indice,valor);
}

/********************************
A função SetValorIntAnimacao() é responsável incorporar a uma animação um atributo inteiro.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação.
indice (entrada, passagem por valor): relaciona um número inteiro ao atributo.
valor (entrada, passagem por referência): valor do atributo string a ser associado à animação.
********************************/
void SetValorStringAnimacao(int idAnimacao, int indice, char *valor){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetValorString(indice,valor);
}

/********************************
A função SetValorIntAnimacao() é responsável incorporar a uma animação um atributo inteiro.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação.
indice (entrada, passagem por referência): relaciona uma string ao atributo.
valor (entrada, passagem por valor): valor do atributo inteiro a ser associado à animação.
********************************/
void SetValorIntAnimacao(int idAnimacao, char *indice, int valor){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetValorInt(indice,valor);
}

/********************************
A função SetValorFloatAnimacao() é responsável incorporar a uma animação um atributo float.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação.
indice (entrada, passagem por referência): relaciona uma string ao atributo.
valor (entrada, passagem por valor): valor do atributo float a ser associado à animação.
********************************/
void SetValorFloatAnimacao(int idAnimacao, char *indice, float valor){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetValorFloat(indice,valor);
}

/********************************
A função SetValorIntAnimacao() é responsável incorporar a uma animação um atributo inteiro.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação.
indice (entrada, passagem por referência): relaciona uma string ao atributo.
valor (entrada, passagem por referência): valor do atributo string a ser associado à animação.
********************************/
void SetValorStringAnimacao(int idAnimacao, char *indice, char *valor){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetValorString(indice,valor);
}

/********************************
A função GetValorIntAnimacao() é responsável recuperar o valor de um atributo inteiro relacionado a uma animação.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação.
indice (entrada, passagem por valor): indica o número do atributo que se deseja recuperar.
valor (saída, passagem por referência): indica o valor do atributo, se a função retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo não existir, a função retorna o valor 0 (zero).
********************************/
int GetValorIntAnimacao(int idAnimacao, int indice, int *valor){
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetValorInt(indice,*valor);
}

/********************************
A função GetValorFloatAnimacao() é responsável recuperar o valor de um atributo float relacionado a uma animação.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação.
indice (entrada, passagem por valor): indica o número do atributo que se deseja recuperar.
valor (saída, passagem por referência): indica o valor do atributo, se a função retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo não existir, a função retorna o valor 0 (zero).
********************************/
int GetValorFloatAnimacao(int idAnimacao, int indice, float *valor){
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetValorFloat(indice,*valor);
}

/********************************
A função GetValorStringAnimacao() é responsável recuperar o valor de um atributo string relacionado a uma animação.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação.
indice (entrada, passagem por valor): indica o número do atributo que se deseja recuperar.
valor (saída, passagem por referência): indica o valor do atributo, se a função retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo não existir, a função retorna o valor 0 (zero).
********************************/
int GetValorStringAnimacao(int idAnimacao, int indice, char *valor){
    string str;
    bool resp = CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetValorString(indice,str);
    strcpy(valor,str.c_str());
    return resp;
}

/********************************
A função GetValorIntAnimacao() é responsável recuperar o valor de um atributo inteiro relacionado a uma animação.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação.
indice (entrada, passagem por referência): indica o nome do atributo que se deseja recuperar.
valor (saída, passagem por referência): indica o valor do atributo, se a função retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo não existir, a função retorna o valor 0 (zero).
********************************/
int GetValorIntAnimacao(int idAnimacao, char *indice, int *valor){
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetValorInt(indice,*valor);
}

/********************************
A função GetValorFloatAnimacao() é responsável recuperar o valor de um atributo float relacionado a uma animação.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação.
indice (entrada, passagem por valor): indica o nome do atributo que se deseja recuperar.
valor (saída, passagem por referência): indica o valor do atributo, se a função retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo não existir, a função retorna o valor 0 (zero).
********************************/
int GetValorFloatAnimacao(int idAnimacao, char *indice, float *valor){
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetValorFloat(indice,*valor);
}

/********************************
A função GetValorStringAnimacao() é responsável recuperar o valor de um atributo string relacionado a uma animação.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação.
indice (entrada, passagem por valor): indica o nome do atributo que se deseja recuperar.
valor (saída, passagem por referência): indica o valor do atributo, se a função retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo não existir, a função retorna o valor 0 (zero).
********************************/
int GetValorStringAnimacao(int idAnimacao, char *indice, char *valor){
    string str;
    bool resp = CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetValorString(indice,str);
    strcpy(valor,str.c_str());
    return resp;
}

/********************************
A função GetXYAnimacao() é responsável por recuperar o valor da posição (X,Y) da animacao de acordo com o sistema de coordenadas do jogo.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação.
posicaoX (saída, passagem por referencia): indica a posicao no eixo X da animação.
posicaoY (saída, passagem por referencia): indica a posicao no eixo Y da animação.
********************************/
void GetXYAnimacao(int idAnimacao, int *posicaoX, int *posicaoY){
    PIGPonto2D p = CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetXY();
    *posicaoX = p.x;
    *posicaoY = p.y;
}

/********************************
A função InsereTransicaoAnimacao() é responsável por criar e inserir uma nova transição ao final de sequência de transiçőes da animação.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação.
tempo (entrada, passagem por valor): duracao (em segundos) da transição.
deltaX (entrada, passagem por valor): diferença da posição no eixo X em relação à posição da animação no início da transição.
deltaY (entrada, passagem por valor): diferença da posição no eixo Y em relação à posição da animação no início da transição.
deltaAltura (entrada, passagem por valor): diferença da altura da animação em relação ao início da transição.
deltaLargura (entrada, passagem por valor): diferença da largura da animação em relação ao início da transição.
deltaAngulo (entrada, passagem por valor): diferença de ângulo (em graus) da animação em relação ao início da transição.
corFinal (entrada, passagem por valor): coloração da animação ao final da transição.
deltaOpacidade (entrada, passagem por valor): diferença do nível de opacidade da animação em relação ao início da transição.
********************************/
void InsereTransicaoAnimacao(int idAnimacao, double tempo, int deltaX, int deltaY, int deltaAltura, int deltaLargura, double deltaAngulo, PIGCor corFinal, int deltaOpacidade){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->InsereTransicao(tempo,{deltaX,deltaY,deltaAltura,deltaLargura,deltaAngulo,corFinal,deltaOpacidade});
}

/********************************
A função ExecutandoTransicaoAnimacao() retorna a informação sobre a execução (neste momento) de transiçőes da animação.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação.
Retorno:
inteiro que indica se a animação está executando alguma transição no momento (valor diferente de 0) ou não (valor igual a 0).
********************************/
int ExecutandoTransicaoAnimacao(int idAnimacao){
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->ExecutandoTransicao();
}

/********************************
A função LeArquivoTransicaoAnimacao() é responsável por ler, criar e inserir as transiçőes para uma animação, provenientes de um arquivo texto.
Cada linha do arquivo texto corresponde a uma transição (em ordem) e deve possuir 11 valores:
1) um double representando a duracao (em segundos) da transição.
2) um inteiro repreentando a diferença da posição no eixo X em relação à posição da animação no início da transição.
3) um inteiro repreentando a diferença da posição no eixo Y em relação à posição da animação no início da transição.
4) um inteiro repreentando a diferença da altura da animação em relação ao início da transição.
5) um inteiro repreentando a diferença da largura da animação em relação ao início da transição.
6) um double repreentando a diferença de ângulo (em graus) da animação em relação ao início da transição.
7) um inteiro repreentando a componente R (vermelho) da coloração da animação ao final da transição.
8) um inteiro repreentando a componente G (verde) da coloração da animação ao final da transição.
9) um inteiro repreentando a componente B (azul) da coloração da animação ao final da transição.
10) um inteiro repreentando a componente A (canal alfa) da coloração da animação ao final da transição.
11) um inteiro repreentando a diferença do nível de opacidade da animação em relação ao início da transição.
Parâmetros:
idSprite (entrada, passagem por valor): identificador da animação.
nomeArq (entrada, passagem por referência): nome com extensão do arquivo texto contendo as transiçőes.
********************************/
void LeArquivoTransicaoAnimacao(int idAnimacao, char *nomeArq){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->LeTransicoes(nomeArq);
}

/********************************
A função IniciaAutomacaoAnimacao() é responsável por iniciar as transiçőes já inseridas na animação, de acordo como o tipo de transição informada.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação.
********************************/
void IniciaAutomacaoAnimacao(int idAnimacao){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->IniciaAutomacao();
}

/********************************
A função TrataAutomacaoAnimacao() é responsável por calcular o estado da transição corrente da animação e aplicar essas modificação a ela.
A função deve ser chamada a cada frame, para ter resultados mais precisos.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação.
********************************/
void TrataAutomacaoAnimacao(int idAnimacao){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->TrataAutomacao();
}

/********************************
A função PausaAutomacaoAnimacao() é responsável por pausar as transiçőes e açőes associadas a uma animação.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação.
********************************/
void PausaAutomacaoAnimacao(int idAnimacao){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->PausaAutomacao();
}

/********************************
A função DespausaAutomacaoAnimacao() é responsável por despausar as transiçőes e açőes associadas a uma animação.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação.
********************************/
void DespausaAutomacaoAnimacao(int idAnimacao){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->DespausaAutomacao();
}

/********************************
A função DefineTipoTransicaoAnimacao() é responsável por determinar como a sequência de transiçőes da animação será executada.
É possível fazê-la uma única vez (PIG_TRANSICAO_NORMAL), em loop (PIG_TRANSICAO_LOOP) ou indo até o final da sequência e retornando, em vai-vém (PIG_TRANSICAO_VAIVEM).
A função deve ser chamada a cada frame, para ter resultados mais precisos.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação.
********************************/
void DefineTipoTransicaoAnimacao(int idAnimacao, PIGTipoTransicao valor){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->DefineTipoTransicao(valor);
}

/********************************
A função LimpaTransicoesAnimacao() é responsável por remover a sequência de transiçőes do animação.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação.
********************************/
void LimpaTransicoesAnimacao(int idAnimacao){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->LimpaTransicoes();
}

/********************************
A função InsereAcaoAnimacao() é responsável por inserir na linha de tempo de automação do animação uma ação a ser executada.
A ação é composta por uma função "acao" que será executada quando a linha de tempo atingir o parâmetro "tempo" e será repetida a cada "repeticao" segundos.
A ação pode armazenar um ponteiro genérico "param" que será utilizado na chamada da função.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação.
tempo (entrada, passagem por valor): tempo (em segundos) da primeira chamada da função.
repeticao (entrada, passagem por valor): tempo (em segundos) entre a chamada anterior e a próxima. O valor -1 indica que a função não será repetida.
param (entrada, passagem por referência): ponteiro genérico para um valor que será utilizado na chamada da função.
********************************/
void InsereAcaoAnimacao(int idAnimacao, double tempo, double repeticao, PIGFuncaoSimples acao, void *param){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->InsereAcao(tempo,repeticao,acao,param);
}

/********************************
A função LimpaAcoesAnimacao() é responsável por remover as açőes restantes associadas à animação
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação.
********************************/
void LimpaAcoesAnimacao(int idAnimacao){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->LimpaAcoes();
}

#ifdef PIGCOMAUDIO
/********************************
Seção dos áudios
********************************/

/********************************
A função CriaAudio() é responsável por ler e preparar um arquivo de audio.
Os formatos permitidos são WAVE, AIFF, RIFF, OGG, VOC.
Parâmetros:
nomeArquivo (entrada, passagem por referência): string que informa o nome do arquivo de áudio.
nLoops (entrada, passagem por valor): indica o número de repetiçőes do áudio. O valor 0 indica que será tocado apenas uma vez. O valor -1 indica que o audio deve ser tocado indefinidamente.
tempoExecucao (entrada, passage por valor): indica uma quantidade de milissegundos do arquivo de audio que dem ser tocados. O valor de -1 indica que todo o arquivo deve ser tocado.
Retorno:
Retorna o identificador do audio para ser utilizado por outras funçőes.
********************************/
int CriaAudio(char *nomeArquivo, int nLoops, int tempoExecucao=-1){
    return CPIGGerenciadorAudios::CriaAudio(nomeArquivo,nLoops,tempoExecucao);
}

/********************************
A função DestroiAudio() é responsável por eliminar um áudio do jogo.
Parâmetros:
idAudio (entrada, passagem por valor): identificador do áudio a ser excluído.
********************************/
void DestroiAudio(int idAudio){
    CPIGGerenciadorAudios::DestroiAudio(idAudio);
}

/********************************
A função CarregaBackground() é responsável por ler e preparar um arquivo de audio para ser tocado em background.
Apenas um único arquivo de áudio para background é permitido. Os formatos permitidos são WAVE, MOD, MIDI, OGG, MP3, FLAC.
Parâmetros:
nomeArquivo (entrada, passagem por referência): string que informa o nome do arquivo de áudio.
********************************/
void CarregaBackground(char *nomeArquivo){
    CPIGGerenciadorAudios::CarregaBackground(nomeArquivo);
}

/********************************
A função PlayBackground() é responsável por tocar um áudio de background previamente carregado.
Parâmetros:
nVezes (entrada, passagem por valor): indica o número de vezes que o background deve ser executado.
O valor -1 indica que deve ser tocado indefinidamente.
********************************/
void PlayBackground(int nVezes=-1){
    CPIGGerenciadorAudios::PlayBackground(nVezes);
}

/********************************
A função StopBackground() é responsável por parar um áudio de background previamente carregado.
********************************/
void StopBackground(){
    CPIGGerenciadorAudios::StopBackground();
}

/********************************
A função PauseBackground() é responsável por pausar um áudio de background previamente carregado.
********************************/
void PauseBackground(){
    CPIGGerenciadorAudios::PauseBackground();
}

/********************************
A função ResumeBackground() é responsável por continuar a tocar um áudio de background previamente carregado.
********************************/
void ResumeBackground(){
    CPIGGerenciadorAudios::ResumeBackground();
}

/********************************
A função GetStatusBackground() recupera o status do audio de background.
Retorno:
Retorna: o valor do status do áudio de background(PIG_AUDIO_TOCANDO, PIG_AUDIO_PARADO ou PIG_AUDIO_PAUSADO)
********************************/
PIGStatusAudio GetStatusBackground(){
    return CPIGGerenciadorAudios::GetStatusBackground();
}

/********************************
A função SetVolumeBackground() define o valor do volume do áudio de background.
Parâmetro:
valor (entrada, passagem por valor): valor do novo volume a ser utilizado. Os valores devem ser entre 0 (mudo) e 128 (volume máximo).
********************************/
void SetVolumeBackground(int valor){
    CPIGGerenciadorAudios::SetVolumeBackground(valor);
}

/********************************
A função GetVolumeBackground() recupera o valor do volume do áudio de background.
Retorno:
Retorna o valor do volume do audio de background. Os valores devem ser entre 0 (mudo) e 128 (volume máximo).
********************************/
int GetVolumeBackground(){
    return CPIGGerenciadorAudios::GetVolumeBackground();
}

/********************************
A função SetVolumeBackground() define o valor do volume do áudio em questão.
Parâmetro:
idAudio (entrada, passagem por valor): identificador do áudio.
volume (entrada, passagem por valor): valor do novo volume a ser utilizado. Os valores devem ser entre 0 (mudo) e 128 (volume máximo).
********************************/
void SetVolume(int idAudio, int volume){
    CPIGGerenciadorAudios::GetAudio(idAudio)->SetVolume(volume);
}

/********************************
A função SetVolumeBackground() recupera o valor do volume do áudio em questão.
Parâmetro:
idAudio (entrada, passagem por valor): identificador do áudio.
Retorno:
Retorna o valor do volume do audio. Os valores devem ser entre 0 (mudo) e 128 (volume máximo).
********************************/
int GetVolume(int idAudio){
    return CPIGGerenciadorAudios::GetAudio(idAudio)->GetVolume();
}

/********************************
A função SetVolumeBackground() define o valor do volume de todos os áudios.
Parâmetro:
volume (entrada, passagem por valor): valor do novo volume a ser utilizado. Os valores devem ser entre 0 (mudo) e 128 (volume máximo).
********************************/
void SetVolumeTudo(int volume){
    CPIGGerenciadorAudios::SetVolumeTudo(volume);
}

/********************************
A função PlayAudio() é responsável por tocar um áudio previamente criado.
Parâmetro:
idAudio (entrada, passagem por valor): indentificador do áudio.
********************************/
void PlayAudio(int idAudio){
    CPIGGerenciadorAudios::Play(idAudio);
}

/********************************
A função PauseAudio() é responsável por pausar um áudio que esteja tocandoo.
Parâmetro:
idAudio (entrada, passagem por valor): indentificador do áudio.
********************************/
void PauseAudio(int idAudio){
    CPIGGerenciadorAudios::GetAudio(idAudio)->Pause();
}

/********************************
A função ResumeAudio() é responsável por continuar a tocar um áudio pausado.
Parâmetro:
idAudio (entrada, passagem por valor): indentificador do áudio.
********************************/
void ResumeAudio(int idAudio){
    CPIGGerenciadorAudios::GetAudio(idAudio)->Resume();
}

/********************************
A função StopAudio() é responsável por parar um áudio pausado ou tocando.
Parâmetro:
idAudio (entrada, passagem por valor): indentificador do áudio.
********************************/
void StopAudio(int idAudio){
    CPIGGerenciadorAudios::GetAudio(idAudio)->Stop();
}

/********************************
A função GetStatusAudio() recupera o status do audio em questão.
Parâmetro:
idAudio (entrada, passagem por valor): indentificador do áudio.
Retorno:
Retorna: o valor do status do áudio (PIG_AUDIO_TOCANDO, PIG_AUDIO_PARADO ou PIG_AUDIO_PAUSADO)
********************************/
PIGStatusAudio GetStatusAudio(int idAudio){
    return CPIGGerenciadorAudios::GetAudio(idAudio)->GetStatus();
}

/********************************
A função ResumeTudoAudio() é responsável por parar todos os áudios pausados ou tocando.
********************************/
void StopTudoAudio(){
    CPIGGerenciadorAudios::StopTudo();
}

/********************************
A função PauseTudoAudio() é responsável por pausar todos os áudios que estiverem tocando.
********************************/
void PauseTudoAudio(){
    CPIGGerenciadorAudios::PauseTudo();
}

/********************************
A função ResumeTudoAudio() é responsável por continuar a tocar todos os áudios pausados.
********************************/
void ResumeTudoAudio(){
    CPIGGerenciadorAudios::ResumeTudo();
}

#endif PIGCOMAUDIO

#ifdef PIGCOMREDE

/********************************
Seção dos sockets
********************************/

/********************************
A função CriaSocketCliente() é responsável por abrir uma conexão TCP com um servidor por meio do seu hostname, que pode ser o nome do computador
em uma rede local ou seu endereço IP, e uma porta. O servidor precisa estar online ou a conexão não será estabelecida.
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
A função CriaSocketServidor() é responsável por abrir um canal de comunicação para transmissőes entrantes (ingoing).
A criação do socket pode ser impedida por políticas de acesso do firewall instalado.
Parâmetros:
maxClientes (entrada, passagem por valor): número máximo de clientes que poderão se comunicar concomitantemente com o servidor.
porta (entrada, passagem por valor): número da porta a ser aberta. Deve ser utilizado um valor na faixa 0-65535 que não esteja sendo utilizado por nenhum outro processo.
maxBytesPacote (entrada, passagem por valor): tamanho máximo de bytes enviados e/ou recebidos de cada vez.
Retorno:
Identificador do socket servidor que foi criado.
********************************/
int CriaSocketServidor(int maxClientes, int porta, int maxBytesPacote=PIG_MAX_MENSAGEM_REDE_TCP){
    return CPIGGerenciadorSockets::CriaServidor(maxClientes,porta,maxBytesPacote);
}

/********************************
A função CriaSocketUDP() é responsável por abrir um canal de comunicação transmissőes de acordo com o protocolo UDP.
O mesmo socket é utilizado para envio e recebimento das informçőes, não havendo papel de cliente e servidor distintos.
Parâmetros:
porta (entrada, passagem por valor): número da porta a ser aberta. Deve ser utilizado um valor na faixa 0-65535 que não esteja sendo utilizado por nenhum outro processo.
Retorno:
Identificador do socket UDP que foi criado.
********************************/
int CriaSocketUDP(int porta){
    return CPIGGerenciadorSockets::CriaSocketUDP(porta);
}

/********************************
A função DestroiSocketCliente() é responsável por fechar o socket cliente aberto, impossibilitando novos envios e recebimentos por ele.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket a ser fechado.
********************************/
void DestroiSocketCliente(int idSocket){
    CPIGGerenciadorSockets::DestroiCliente(idSocket);
}

/********************************
A função DestroiSocketServidor() é responsável por fechar o socket servidor aberto, impossibilitando novos envios e recebimentos por ele.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket a ser fechado.
********************************/
void DestroiSocketServidor(int idSocket){
    CPIGGerenciadorSockets::DestroiServidor(idSocket);
}

/********************************
A função DestroiSocketUDP() é responsável por fechar o socket UDP aberto, impossibilitando novos envios e recebimentos por ele.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket a ser fechado.
********************************/
void DestroiSocketUDP(int idSocket){
    CPIGGerenciadorSockets::DestroiSocketUDP(idSocket);
}

/********************************
A função GetAtivoSocketCliente() é responsável por verificar se o socket cliente ainda está ativo e conectado ao servidor ou não.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro que determina se o socket cliente ainda está ativo e conectado (valor diferente de zero) ou não (valor zero)
********************************/
int GetAtivoSocketCliente(int idSocket){
    return CPIGGerenciadorSockets::GetCliente(idSocket)->GetAtivo();
}

/********************************
A função GetAtivoSocketServidor() é responsável por verificar se o socket servidor ainda está ativo ou não.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro que determina se o socket servidor ainda está ativo (valor diferente de zero) ou não (valor zero)
********************************/
int GetAtivoSocketServidor(int idSocket){
    return CPIGGerenciadorSockets::GetServidor(idSocket)->GetAtivo();
}

/********************************
A função GetAtivoSocketUDP() é responsável por verificar se o socket UDP ainda está ativo ou não.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro que determina se o socket UDP ainda está ativo (valor diferente de zero) ou não (valor zero)
********************************/
int GetAtivoSocketUDP(int idSocket){
    return CPIGGerenciadorSockets::GetSocketUDP(idSocket)->GetAtivo();
}

/********************************
A função GetBytesEnviadosSocketCliente() é responsável por recuperar a quantidade de bytes já enviados através do socket cliente desde a sua criação.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica a quantidade de bytes enviados através do socket.
********************************/
long GetBytesEnviadosSocketCliente(int idSocket){
    return CPIGGerenciadorSockets::GetCliente(idSocket)->GetBytesEnviados();
}

/********************************
A função GetBytesRecebidosSocketCliente() é responsável por recuperar a quantidade de bytes já recebidos através do socket cliente desde a sua criação.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica a quantidade de bytes recebidos através do socket.
********************************/
long GetBytesRecebidosSocketCliente(int idSocket){
    return CPIGGerenciadorSockets::GetCliente(idSocket)->GetBytesRecebidos();
}

/********************************
A função GetPacotesEnviadosSocketCliente() é responsável por recuperar a quantidade de pacotes (mensagens) já enviados através do socket cliente desde a sua criação.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica a quantidade de pacotes enviados através do socket.
********************************/
long GetPacotesEnviadosSocketCliente(int idSocket){
    return CPIGGerenciadorSockets::GetCliente(idSocket)->GetPacotesEnviados();
}

/********************************
A função GetPacotesRecebidosSocketCliente() é responsável por recuperar a quantidade de pacotes (mensagens) já recebidos através do socket cliente desde a sua criação.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica a quantidade de pacotes recebidos através do socket.
********************************/
long GetPacotesRecebidosSocketCliente(int idSocket){
    return CPIGGerenciadorSockets::GetCliente(idSocket)->GetPacotesRecebidos();
}

/********************************
A função GetTempoUltimoRecebidoSocketCliente() é responsável por recuperar o momento em que o último pacote foi recebido pelo socket.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica o tempo do recebimento do último pacote pelo socket.
********************************/
long GetTempoUltimoRecebidoSocketCliente(int idSocket){
    return CPIGGerenciadorSockets::GetCliente(idSocket)->GetTempoUltimoRecebido();
}

/********************************
A função GetTempoUltimoEnviadoSocketCliente() é responsável por recuperar o momento em que o último pacote foi enviado pelo socket.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica o tempo do envio do último pacote pelo socket.
********************************/
long GetTempoUltimoEnviadoSocketCliente(int idSocket){
    return CPIGGerenciadorSockets::GetCliente(idSocket)->GetTempoUltimoEnviado();
}

/********************************
A função GetBytesEnviadosSocketServidor() é responsável por recuperar a quantidade de bytes já enviados através do socket cliente desde a sua criação.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica a quantidade de bytes enviados através do socket.
********************************/
long GetBytesEnviadosSocketServidor(int idSocket){
    return CPIGGerenciadorSockets::GetServidor(idSocket)->GetBytesEnviados();
}

/********************************
A função GetBytesRecebidosSocketServidor() é responsável por recuperar a quantidade de bytes já recebidos através do socket cliente desde a sua criação.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica a quantidade de bytes recebidos através do socket.
********************************/
long GetBytesRecebidosSocketServidor(int idSocket){
    return CPIGGerenciadorSockets::GetServidor(idSocket)->GetBytesRecebidos();
}

/********************************
A função GetPacotesEnviadosSocketServidor() é responsável por recuperar a quantidade de pacotes (mensagens) já enviados através do socket cliente desde a sua criação.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica a quantidade de pacotes enviados através do socket.
********************************/
long GetPacotesEnviadosSocketServidor(int idSocket){
    return CPIGGerenciadorSockets::GetCliente(idSocket)->GetPacotesEnviados();
}

/********************************
A função GetPacotesRecebidosSocketServidor() é responsável por recuperar a quantidade de pacotes (mensagens) já recebidos através do socket cliente desde a sua criação.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica a quantidade de pacotes recebidos através do socket.
********************************/
long GetPacotesRecebidosSocketServidor(int idSocket){
    return CPIGGerenciadorSockets::GetCliente(idSocket)->GetPacotesRecebidos();
}

/********************************
A função GetTempoUltimoRecebidoSocketServidor() é responsável por recuperar o momento em que o último pacote foi recebido pelo socket.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica o tempo do recebimento do último pacote pelo socket.
********************************/
long GetTempoUltimoRecebidoSocketServidor(int idSocket){
    return CPIGGerenciadorSockets::GetServidor(idSocket)->GetTempoUltimoRecebido();
}

/********************************
A função GetTempoUltimoEnviadoSocketServidor() é responsável por recuperar o momento em que o último pacote foi enviado pelo socket.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica o tempo do envio do último pacote pelo socket.
********************************/
long GetTempoUltimoEnviadoSocketServidor(int idSocket){
    return CPIGGerenciadorSockets::GetServidor(idSocket)->GetTempoUltimoEnviado();
}

/********************************
A função GetBytesEnviadosSocketUDP() é responsável por recuperar a quantidade de bytes já enviados através do socket cliente desde a sua criação.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica a quantidade de bytes enviados através do socket.
********************************/
long GetBytesEnviadosSocketUDP(int idSocket){
    return CPIGGerenciadorSockets::GetSocketUDP(idSocket)->GetBytesEnviados();
}

/********************************
A função GetBytesRecebidosSocketUDP() é responsável por recuperar a quantidade de bytes já recebidos através do socket cliente desde a sua criação.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica a quantidade de bytes recebidos através do socket.
********************************/
long GetBytesRecebidosSocketUDP(int idSocket){
    return CPIGGerenciadorSockets::GetSocketUDP(idSocket)->GetBytesRecebidos();
}

/********************************
A função GetPacotesEnviadosSocketUDP() é responsável por recuperar a quantidade de pacotes (mensagens) já enviados através do socket cliente desde a sua criação.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica a quantidade de pacotes enviados através do socket.
********************************/
long GetPacotesEnviadosSocketUDP(int idSocket){
    return CPIGGerenciadorSockets::GetSocketUDP(idSocket)->GetPacotesEnviados();
}

/********************************
A função GetPacotesRecebidosSocketUDP() é responsável por recuperar a quantidade de pacotes (mensagens) já recebidos através do socket cliente desde a sua criação.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica a quantidade de pacotes recebidos através do socket.
********************************/
long GetPacotesRecebidosSocketUDP(int idSocket){
    return CPIGGerenciadorSockets::GetSocketUDP(idSocket)->GetPacotesRecebidos();
}

/********************************
A função GetTempoUltimoRecebidoSocketUDP() é responsável por recuperar o momento em que o último pacote foi recebido pelo socket.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica o tempo do recebimento do último pacote pelo socket.
********************************/
long GetTempoUltimoRecebidoSocketUDP(int idSocket){
    return CPIGGerenciadorSockets::GetSocketUDP(idSocket)->GetTempoUltimoRecebido();
}

/********************************
A função GetTempoUltimoEnviadoSocketUDP() é responsável por recuperar o momento em que o último pacote foi enviado pelo socket.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica o tempo do envio do último pacote pelo socket.
********************************/
long GetTempoUltimoEnviadoSocketUDP(int idSocket){
    return CPIGGerenciadorSockets::GetSocketUDP(idSocket)->GetTempoUltimoEnviado();
}

/********************************
A função GetPortaRemotaSocketCliente() é responsável por recuperar o número da porta remota (do servidor) à qual está conectado o socket.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro que indica o número da porta remota (do servidor) à qual está conectado o socket.
********************************/
int GetPortaRemotaSocketCliente(int idSocket){
    return CPIGGerenciadorSockets::GetCliente(idSocket)->GetPortaRemota();
}

/********************************
A função GetPortaLocalSocketServidor() é responsável por recuperar o número da porta local que está sendo utilizada pelo socket servidor.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro que indica o número da porta local do socket servidor.
********************************/
int GetPortaLocalSocketServidor(int idSocket){
    return CPIGGerenciadorSockets::GetServidor(idSocket)->GetPortaLocal();
}

/********************************
A função GetPortaLocalSocketUDP() é responsável por recuperar o número da porta local que está sendo utilizada pelo socket UDP.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro que indica o número da porta local do socket UDP.
********************************/
int GetPortaLocalSocketUDP(int idSocket){
    return CPIGGerenciadorSockets::GetSocketUDP(idSocket)->GetPortaLocal();
}

/********************************
A função GetHostRemotoSocketCliente() é responsável por recuperar o nome do computador (da rede local) ou do endereço IP ao qual está conectado o socket cliente, ou seja, o servidor.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
hostname (saída, passagem por referência): nome do computador (da rede local) ou do endereço IP ao qual está conectado o socket cliente.
********************************/
void GetHostRemotoSocketCliente(int idSocket, char *hostname){
    strcpy(hostname,CPIGGerenciadorSockets::GetCliente(idSocket)->GetHostRemoto().c_str());
}

/********************************
A função GetHostLocalSocketCliente() é responsável por recuperar o nome do computador (na rede local) ou do endereço IP da máquina está aberto o socket cliente.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
hostname (saída, passagem por referência): nome do computador (na rede local) ou do endereço IP da máquina no qual está aberto o socket cliente.
********************************/
void GetHostLocalSocketCliente(int idSocket, char *hostname){
    strcpy(hostname,CPIGGerenciadorSockets::GetCliente(idSocket)->GetHostLocal().c_str());
}

/********************************
A função GetHostLocalSocketServidor() é responsável por recuperar o nome do computador (na rede local) ou do endereço IP da máquina está aberto o socket servidor.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
hostname (saída, passagem por referência): nome do computador (na rede local) ou do endereço IP da máquina no qual está aberto o socket servidor.
********************************/
void GetHostLocalSocketServidor(int idSocket, char *hostname){
    strcpy(hostname,CPIGGerenciadorSockets::GetServidor(idSocket)->GetHostLocal().c_str());
}

/********************************
A função GetHostLocalSocketUDP() é responsável por recuperar o nome do computador (na rede local) ou do endereço IP da máquina está aberto o socket UDP.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
hostname (saída, passagem por referência): nome do computador (na rede local) ou do endereço IP da máquina no qual está aberto o socket UDP.
********************************/
void GetHostLocalSocketUDP(int idSocket, char *hostname){
    strcpy(hostname,CPIGGerenciadorSockets::GetSocketUDP(idSocket)->GetHostLocal().c_str());
}

/********************************
A função GetTamanhoPacoteSocketCliente() é responsável por recuperar o tamanho máximo de bytes utilizado pelo socket para envio ou recebimento de mensagens.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro que indica o tamanho máximo, em bytes, das mensagens enviadas ou recebidas pelo socket.
********************************/
int GetTamanhoPacoteSocketCliente(int idSocket){
    return CPIGGerenciadorSockets::GetCliente(idSocket)->GetTamanhoPacote();
}

/********************************
A função GetTamanhoPacoteSocketServidor() é responsável por recuperar o tamanho máximo de bytes utilizado pelo socket para envio ou recebimento de mensagens.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro que indica o tamanho máximo, em bytes, das mensagens enviadas ou recebidas pelo socket.
********************************/
int GetTamanhoPacoteSocketServidor(int idSocket){
    return CPIGGerenciadorSockets::GetServidor(idSocket)->GetTamanhoPacote();
}

/********************************
A função GetMaximoConexoesSocketServidor() é responsável por recuperar a quantidade máxima de conexőes que podem ser estabelecidas pelo socket servidor com outros sockets clientes.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro que indica a quantidade máxima de conexőes concomitantes que podem ser estabelecidas pelo socket servidor com outros sockets clientes.
********************************/
int GetMaximoConexoesSocketServidor(int idSocket){
    return CPIGGerenciadorSockets::GetServidor(idSocket)->GetMaximoConexoes();
}

/********************************
A função GetQuantidadeConexoesSocketServidor() é responsável por recuperar a quantidade de conexőes atualmente abertas pelo socket servidor com outros sockets clientes.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro que indica a quantidade de conexőes atualmente abertas pelo socket servidor com outros sockets clientes.
********************************/
int GetQuantidadeConexoesSocketServidor(int idSocket){
    return CPIGGerenciadorSockets::GetServidor(idSocket)->GetQuantidadeConexoes();
}

/********************************
A função EnviaDadosSocketCliente() é responsável por efetivamente enviar bytes armazenados em memória principal através do socket cliente, para o servidor.
O recebimento de dados através da rede pode ser detectado pela geração de um evento de rede. A mensagem transmitida deve ser recuperada a partir desse evento.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
buffer (entrada, passagem por valor): ponteiro (endereço) para o local da memória onde estão armazenados os dados a serem transmitidos. Pode ser, inclusive, o nome de uma string ou vetor.
tamanhoBuffer (entrada, passagem por valor): quantidade de bytes que devem ser lidos e transmitidos a partir do endereço indicado no buffer.
Retorno:
Inteiro que indica a quantidade de bytes efetivamente transmitida.
********************************/
int EnviaDadosSocketCliente(int idSocket, void *buffer, int tamanhoBuffer){
    return CPIGGerenciadorSockets::GetCliente(idSocket)->EnviaDados(buffer,tamanhoBuffer);
}

/********************************
A função EnviaDadosSocketServidor() é responsável por efetivamente enviar bytes armazenados em memória principal através do socket servidor, para o cliente.
O recebimento de dados através da rede pode ser detectado pela geração de um evento de rede. A mensagem transmitida deve ser recuperada a partir desse evento.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
buffer (entrada, passagem por valor): ponteiro (endereço) para o local da memória onde estão armazenados os dados a serem transmitidos. Pode ser, inclusive, o nome de uma string ou vetor.
tamanhoBuffer (entrada, passagem por valor): quantidade de bytes que devem ser lidos e transmitidos a partir do endereço indicado no buffer.
Retorno:
Inteiro que indica a quantidade de bytes efetivamente transmitida.
********************************/
int EnviaDadosSocketServidor(int idSocket, int socketSecundario, void *buffer, int tamanhoBuffer){
    return CPIGGerenciadorSockets::GetServidor(idSocket)->EnviaDados(buffer,tamanhoBuffer,socketSecundario);
}

/********************************
A função EnviaDadosSocketUDP() é responsável por efetivamente enviar bytes armazenados em memória principal através do socket UDP, para outro socket UDP.
O recebimento de dados através da rede pode ser detectado pela geração de um evento de rede. A mensagem transmitida deve ser recuperada a partir desse evento.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
buffer (entrada, passagem por valor): ponteiro (endereço) para o local da memória onde estão armazenados os dados a serem transmitidos. Pode ser, inclusive, o nome de uma string ou vetor.
tamanhoBuffer (entrada, passagem por valor): quantidade de bytes que devem ser lidos e transmitidos a partir do endereço indicado no buffer.
Retorno:
Inteiro que indica a quantidade de bytes efetivamente transmitida.
********************************/
int EnviaDadosSocketUDP(int idSocket, void *buffer, int tamanhoBuffer, char *hostRemoto, int porta){
    return CPIGGerenciadorSockets::GetSocketUDP(idSocket)->EnviaDados(buffer,tamanhoBuffer,hostRemoto,porta);
}

#endif //PIGCOMREDE

#ifdef PIGCOMVIDEO

/********************************
Seção dos vídeos.
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
Toda a parte de vídeo é considerada experimental e pode não funcionar dependendo do vídeo,
dos drives instalados, do sistema operacional ou do formato do vídeo.
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
********************************/


/********************************
A função CriaVideo() é responsável por ler e preparar um arquivo de vídeo.
Os formatos permitidos são AVI, MP4, MOV.
Parâmetros:
nomeArquivo (entrada, passagem por referência): string que informa o nome do arquivo de vídeo.
idJanela (entrada, passagem por valor): indica em qual janela o vídeo será exibido.
Retorno:
Retorna o identificador do vídeo para ser utilizado por outras funçőes.
********************************/
int CriaVideo(char *nomeArquivo, int idJanela=0){
    return CPIGGerenciadorVideos::CriaVideo(nomeArquivo,idJanela);
}

/********************************
A função DestroiVideo() é responsável por eliminar um vídeo do jogo.
Parâmetros:
idVideo (entrada, passagem por valor): identificador do vídeo a ser excluído.
********************************/
void DestroiVideo(int idVideo){
    CPIGGerenciadorVideos::DestroiVideo(idVideo);
}

/********************************
A função SetSeekVideo() é responsável por avançar ou retroceder o vídeo instantaneamente.
Parâmetros:
idVideo (entrada, passagem por valor): identificador do vídeo.
incremento (entrada, passagem por valor): quantidade de tempo (em segundos) para o avançao ou retrocesso do vídeo.
********************************/
void SetSeekVideo(int idVideo, double incremento){
    CPIGGerenciadorVideos::GetVideo(idVideo)->SetSeek(incremento);
}

/********************************
A função PlayVideo() é responsável por tocar um vídeo previamente criado.
Parâmetro:
idVideo (entrada, passagem por valor): indentificador do vídeo.
********************************/
void PlayVideo(int idVideo){
    CPIGGerenciadorVideos::GetVideo(idVideo)->Play();
}

/********************************
A função StopVideo() é responsável por parar um vídeo pausado ou tocando.
Parâmetro:
idVideo (entrada, passagem por valor): indentificador do vídeo.
********************************/
void StopVideo(int idVideo){
    CPIGGerenciadorVideos::GetVideo(idVideo)->Stop();
}

/********************************
A função PauseVideo() é responsável por pausar um vídeo que esteja tocando.
Parâmetro:
idVideo (entrada, passagem por valor): indentificador do vídeo.
********************************/
void PauseVideo(int idVideo){
    CPIGGerenciadorVideos::GetVideo(idVideo)->Pause();
}

/********************************
A função ResumeVideo() é responsável por continuar a tocar um vídeo pausado.
Parâmetro:
idVideo (entrada, passagem por valor): indentificador do vídeo.
********************************/
void ResumeVideo(int idVideo){
    CPIGGerenciadorVideos::GetVideo(idVideo)->Resume();
}

/********************************
A função DesenhaVideo() é responsável por desenhar os frames de um vídeo na tela. O vídeo será desenhado de acordo com todas as definiçőes
de posição e ângulo informado até o momento. Além disso, se o vídeo estiver virado (flipping), isso também será levado em consideração, bem como a coloração e a opacidade definidas.
Parâmetro:
idVideo (entrada, passagem por valor): identificador do vídeo a ser desenhado.
********************************/
int DesenhaVideo(int idVideo){
    return CPIGGerenciadorVideos::GetVideo(idVideo)->Desenha();
}

/********************************
A função SetVolumeVideo() é responsável por definir o volume para o vídeo. O valor informado deve ser positivo ou zero (mudo).
Parâmetro:
idVideo (entrada, passagem por valor): indentificador do vídeo.
valor (entrada, passagem por valor): volume a ser definido. Deve ser positivo ou zero (mudo).
********************************/
void SetVolumeVideo(int idVideo, double valor){
    CPIGGerenciadorVideos::GetVideo(idVideo)->SetVolume(valor);
}

/********************************
A função GetVolumeVideo() é responsável por recuperar o valor do volume do vídeo.
Parâmetro:
idVideo (entrada, passagem por valor): indentificador do vídeo.
Retorno:
Nível de volume do vídeo (deve ser sempre um valor positivo).
********************************/
double GetVolumeVideo(int idVideo){
    return CPIGGerenciadorVideos::GetVideo(idVideo)->GetVolume();
}

/********************************
A função GetNomeArquivoVideo() é responsável por recuperar o nome do arquivo que deu origem ao video.
Parâmetro:
idVideo (entrada, passagem por valor): indentificador do vídeo.
nome (saída, passagem por referência): nome do arquivo utilizado para criar o video.
********************************/
void GetNomeArquivoVideo(int idVideo, char *nome){
    strcpy(nome,CPIGGerenciadorVideos::GetVideo(idVideo)->GetNomeArquivo().c_str());
}

/********************************
A função GetTempoAtualVideo() é responsável por recuperar o valor (em milissegundo) do tempo de vídeo já exibido, ou seja, o momento atual do vídeo.
Parâmetro:
idVideo (entrada, passagem por valor): indentificador do vídeo.
Retorno:
Total de tempo (em milissegundos) da parte já exibida do vídeo.
********************************/
double GetTempoAtualVideo(int idVideo){
    return CPIGGerenciadorVideos::GetVideo(idVideo)->GetTempoAtual();
}

/********************************
A função GetTempoAtualVideo() é responsável por recuperar uma string contendo a hora, minuto, segundo e milissegundo do frame atual do video.
Parâmetro:
idVideo (entrada, passagem por valor): indentificador do vídeo.
str (saída, passagem por referência): posição do frame atual, definido em hora, minuto, segundo e milissegundo.
********************************/
void GetTempoAtualVideo(int idVideo, char *str){
    strcpy(str,CPIGGerenciadorVideos::GetVideo(idVideo)->GetTempoAtualString().c_str());
}

/********************************
A função GetTempoTotalVideo() é responsável por recuperar a druação total do vídeo (em milissegundo).
Parâmetro:
idVideo (entrada, passagem por valor): indentificador do vídeo.
Retorno
Tempo total do vídeo em milissegundos.
********************************/
double GetTempoTotalVideo(int idVideo){
    return CPIGGerenciadorVideos::GetVideo(idVideo)->GetTempoTotal();
}

/********************************
A função GetTempoTotalVideo() é responsável por recuperar uma string contendo a duração do video em hora, minuto, segundo e milissegundo.
Parâmetro:
idVideo (entrada, passagem por valor): indentificador do vídeo.
str (saída, passagem por referência): duração do vídeo, definido em hora, minuto, segundo e milissegundo.
********************************/
void GetTempoTotalVideo(int idVideo, char *str){
    strcpy(str,CPIGGerenciadorVideos::GetVideo(idVideo)->GetTempoTotalString().c_str());
}

/********************************
A função GetTempoFrameVideo() é responsável por recuperar a duração esperada para cada frame do video (em milissegundo).
Parâmetro:
idVideo (entrada, passagem por valor): indentificador do vídeo.
Retorno:
Duração esperado de cada frame do vídeo (em milissegundo).
********************************/
double GetTempoFrameVideo(int idVideo){
    return CPIGGerenciadorVideos::GetVideo(idVideo)->GetTempoFrame();
}

/********************************
A função GetFPSVideo() é responsável por recuperar a quantidade de frames do vídeo que deveriam ser exibidos a cada segundo.
Parâmetro:
idVideo (entrada, passagem por valor): indentificador do vídeo.
Retorno:
Quantidade desejada de frames a cada segundo.
********************************/
double GetFPSVideo(int idVideo){
    return CPIGGerenciadorVideos::GetVideo(idVideo)->GetFPS();
}

/********************************
A função SetAnguloVideo() é responsável pela angulação de determinado vídeo. A angulação é calculada em sentido
horário a partir do eixo X (0 graus). O vídeo será desenhado com a angulação informada no próximo comando
DesenhaVideo().
Parâmetros:
idVideo (entrada, passagem por valor): identificador do vídeo.
angulo (entrada, passagem por valor): valor para indicar a angulação do vídeo em graus.
********************************/
void SetAnguloVideo(int idVideo, float angulo){
    CPIGGerenciadorVideos::GetVideo(idVideo)->SetAngulo(angulo);
}

/********************************
A função GetAnguloVideo() é responsável por recuperar o ângulo de rotação de determinado vídeo. A angulação é calculada em sentido
horário a partir do eixo X (0 graus). O vídeo será desenhado com a angulação informada no próximo comando
DesenhaVideo().
idVideo (entrada, passagem por valor): identificador do vídeo.
Retorno:
Retorna o valor do ângulo em graus.
********************************/
double GetAnguloVideo(int idVideo){
    return CPIGGerenciadorVideos::GetVideo(idVideo)->GetAngulo();
}

/********************************
A função SetFlipVideo() é responsável por virar o vídeo, invertendo-o em alguma direção. O vídeo somente será
desenhado na nova orientação no próximo comando DesenhaVideo().
Parâmetros:
idVideo (entrada, passagem por valor): identificador do vídeo a ser virado.
valor (entrada, passagem por valor): valor do tipo de Flip. Pode ser FLIP_NENHUM (nenhum tipo de inversão),
FLIP_HORIZONTAL (inverte da esquerda para a direita), FLIP_VERTICAL (inverte de cima para baixo),
ou FLIP_HORIZ_VERT (inverte da esquerda para direita e de cima para baixo).
********************************/
void SetFlipVideo(int idVideo, PIGFlip valor){
    CPIGGerenciadorVideos::GetVideo(idVideo)->SetFlip(valor);
}

/********************************
A função GetFlipVideo() é responsável por recuperar o valor da manipulação causada pela função SetFlipVideo().
Parâmetros:
idVideo (entrada, passagem por valor): identificador do vídeo a ser virado.
Retorno:
inteiro que indica o tipo de Flip. Pode ser PIG_FLIP_NENHUM (nenhum tipo de inversão),
PIG_FLIP_HORIZONTAL (inverte da esquerda para a direita), PIG_FLIP_VERTICAL (inverte de cima para baixo),
ou PIG_FLIP_HORIZ_VERT (inverte da esquerda para direita e de cima para baixo).
********************************/
PIGFlip GetFlipVideo(int idVideo){
    return CPIGGerenciadorVideos::GetVideo(idVideo)->GetFlip();
}

/********************************
A função SetPivoAbsolutoVideo() define um ponto (X,Y) em relação ao ponto (0,0) do vídeo, sobre o qual o video será
rotacionado quando a função SetAnguloVideo() for executada.
Parâmetros:
idVideo (entrada, passagem por valor): identificador do vídeo.
posicaoX (entrada, passagem por valor): Valor da coordenada X do pivô em relação ao ponto (0,0) do vídeo.
posicaoY (entrada, passagem por valor): Valor da coordenada Y do pivô em relação ao ponto (0,0) do vídeo.
********************************/
void SetPivoAbsolutoVideo(int idVideo, int posicaoX, int posicaoY){
    CPIGGerenciadorVideos::GetVideo(idVideo)->SetPivoAbsoluto({(double)posicaoX,(double)posicaoY});
}

/********************************
A função SetPivoProporcionalVideo() define um ponto relativo (X,Y) em relação ao video (0,0) e ao tamanho do vídeo, sobre o qual o vídeo será
rotacionado quando a função SetAnguloVideo() for executada.
Parâmetros:
idVideo (entrada, passagem por valor): identificador do vídeo.
relX (entrada, passagem por valor): porcentagem da largura do vídeo onde ficará o pivô.
relY (entrada, passagem por valor): porcentagem da altura do vídeo onde ficará o pivô.
********************************/
void SetPivoProporcionalVideo(int idVideo, float relX, float relY){
    CPIGGerenciadorVideos::GetVideo(idVideo)->SetPivoProporcional({relX,relY});
}

/********************************
A função GetPivoVideo() define um ponto (X,Y) em relação ao ponto (0,0) do vídeo, sobre o qual o vídeo será
rotacionado quando a função SetAnguloVideo() for executada.
Parâmetros:
idVideo (entrada, passagem por valor): identificador do vídeo.
posicaoX (saída, passagem por referência): Valor da coordenada X do pivô em relação ao ponto (0,0) do vídeo.
posicaoY (saída, passagem por referência): Valor da coordenada Y do pivô em relação ao ponto (0,0) do vídeo.
********************************/
void GetPivoVideo(int idVideo, int *posicaoX, int *posicaoY){
    PIGPonto2D p = CPIGGerenciadorVideos::GetVideo(idVideo)->GetPivo();
    *posicaoX = p.x;
    *posicaoY = p.y;
}

/********************************
A função MoveVideo() é responsável por movimentar um determinado vídeo para uma nova posição informada.
Parâmetros:
idVideo (entrada, passagem por valor): identificador do vídeo a ser movido.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usuário deseja reposicionar o vídeo.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usuário deseja reposicionar o vídeo.
********************************/
void MoveVideo(int idVideo, int posicaoX, int posicaoY){
    CPIGGerenciadorVideos::GetVideo(idVideo)->Move(posicaoX,posicaoY);
}

/********************************
A função SetDimensoesVideo() é responsável por delimitar a altura e a largura do vídeo que será desenhado na tela,
independentemente do tamanho original do arquivo.
Parâmetros:
idVideo (entrada, passagem por valor): identificador do vídeo.
altura (entrada, passagem por valor): altura em pixels.
largura (entrada, passagem por valor): largura em pixels.
********************************/
void SetDimensoesVideo(int idVideo, int altura, int largura){
    CPIGGerenciadorVideos::GetVideo(idVideo)->SetDimensoes(altura,largura);
}

/********************************
A função GetDimensoesVideo() é responsável por recuperar a altura e a largura da área a ser usada
para desenhar o vídeo na tela. Em outras palavras, representa o tamanho atual do vídeo.
Parâmetros:
idVideo (entrada, passagem por valor): identificador do vídeo.
altura (saída, passagem por referência): altura atual em pixels do vídeo.
largura (saída, passagem por referência): largura atual em pixels do vídeo.
********************************/
void GetDimensoesVideo(int idVideo, int *altura, int *largura){
    CPIGGerenciadorVideos::GetVideo(idVideo)->GetDimensoes(*altura,*largura);
}

/********************************
A função GetDimensoesOriginaisVideo() é responsável por recuperar a altura e a largura originais dos frames do vídeo.
Qualquer utilização da função SetDimensoesVideo() é ignorada para o cálculo desta função.
Parâmetros:
idVideo (entrada, passagem por valor): identificador do vídeo.
altura (saída, passagem por referência): altura original em pixels do vídeo.
largura (saída, passagem por referência): largura original em pixels do vídeo.
********************************/
void GetDimensoesOriginaisVideo(int idVideo, int *altura, int *largura){
    CPIGGerenciadorVideos::GetVideo(idVideo)->GetResolucao(*altura,*largura);
}

/********************************
A função OcupaJanelaInteiraVideo() é responsável por redimensionar a exibição do video, para que este ocupe todo o tamanho
da janela em que estiver sendo executado.
Parâmetros:
idVideo (entrada, passagem por valor): identificador do vídeo a ser desenhado.
********************************/
void OcupaJanelaInteiraVideo(int idVideo){
    CPIGGerenciadorVideos::GetVideo(idVideo)->OcupaJanelaInteira();
}

/********************************
A função UsaResolucaoOriginalVideo() é responsável por redimensionar a exibição do video, para que este utilize a resolução original
do arquivo de mídia.
Parâmetros:
idVideo (entrada, passagem por valor): identificador do vídeo a ser desenhado.
********************************/
void UsaResolucaoOriginalVideo(int idVideo){
    CPIGGerenciadorVideos::GetVideo(idVideo)->UsaResolucaoOriginal();
}

/********************************
A função SetColoracaoVideo() é responsável por mesclar uma determinada cor com os pixels do frame do vídeo.
Após a modificação, todos os desenhos deste vídeo serão mostrados já com a mesclagem definida.
Para voltar ao padrão original de pixels, deve-se chamar a função, passando a cor branca (255,255,255,255).
Parâmetros:
idVideo (entrada, passagem por valor): identificador do vídeo a ser desenhado.
cor (entrada,passagem por valor): cor do sistema RGB utilizada para mesclagem com o arquivo de vídeo.
********************************/
void SetColoracaoVideo(int idVideo, PIGCor cor){
    CPIGGerenciadorVideos::GetVideo(idVideo)->SetColoracao(cor);
}

/********************************
A função SetOpacidadeVideo() é responsável por modificar o nível de opacidade do vídeo.
O nível de opacidade varia de 0-255, sendo 0 totalmente transparente e 255 totalmente opaco.
Parâmetros:
idVideo (entrada, passagem por valor): identificador do vídeo.
valor (entrada,passagem por valor): nível de opacidade do vídeo na faixa 0-255.
********************************/
void SetOpacidadeVideo(int idVideo, int valor){
    CPIGGerenciadorVideos::GetVideo(idVideo)->SetOpacidade(valor);
}

/********************************
A função GetOpacidadeVideo() é responsável por recuperar o nível de opacidade de determinado vídeo.
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


#ifdef PIGCOMFORM


/*******FORM*********/


/********************************
A função PIGCriaForm() é responsável por criar um formulário que conterá diversos componentes como: botőes, radiobox, checkbox, slidebar etc.
Com essa chamada, o formulário não terá nenhuma imagem de fundo, mas poderá ter uma cor substituindo essa imagem.
Parâmetros:
altura (entrada, passagem por valor): altura do formulário em pixels.
largura (entrada, passagem por valor): largura do formulário em pixels.
idJanela (entrada, passagem por valor não-obrigatório): indica em qual janela vai ser criado o formulário.
Retorno:
inteiro contendo o identificador do formulário que foi criado. Esse identificador deve ser utilizado para criar os componentes
contidos nesse formulário.
********************************/
int PIGCriaForm(int altura, int largura, int idJanela=0){
    return CPIGGerenciadorForms::CriaForm(altura,largura,idJanela);
}

/********************************
A função PIGCriaForm() é responsável por criar um formulário que conterá diversos componentes como: botőes, radiobox, checkbox, slidebar etc.
Com essa chamada, o formulário terá uma imagem de fundo.
Parâmetros:
posicaoX (entrada, passagem por valor): posição, no eixo X, do canto inferior esquerdo do formulário.
posicaoY (entrada, passagem por valor): posição, no eixo Y, do canto inferior esquerdo do formulário.
altura (entrada, passagem por valor): altura do formulário em pixels.
largura (entrada, passagem por valor): largura do formulário em pixels.
nomeArquivo (entrada, passagem por parâmetro*): nome do arquivo de imagem que servirá de fundo para o formulário.
retiraFundo (entrada, passagem por valor não-obrigatório): inteiro que indica se o fundo da imagem deve ser retirado ou não ao ler o arquivo em questão. O valor padrão é 1, indicando que o fundo deve ser retirado.
idJanela (entrada, passagem por valor não-obrigatório): indica em qual janela vai ser criado o formulário.
Retorno:
inteiro contendo o identificador do formulário que foi criado. Esse identificador deve ser utilizado para criar os componentes
contidos nesse formulário.
********************************/
int PIGCriaForm(int altura, int largura, char *nomeArquivo, int retiraFundo=1, int idJanela=0){
    return CPIGGerenciadorForms::CriaForm(altura,largura,nomeArquivo,retiraFundo,idJanela);
}

/********************************
A função PIGCriaForm() é responsável por criar um formulário que conterá diversos componentes como: botőes, radiobox, checkbox, slidebar etc.
Com essa chamada, o formulário e os componentes serão cirados confrome os parâmetros existentes dentro de um arquivo de texto.
Parâmetros:
nomeArqTexto (entrada, passagem por parâmetro*): nome do arquivo de texto que contém as características do formulário e dos componentes.
Retorno:
inteiro contendo o identificador do formulário que foi criado. Esse identificador deve ser utilizado para criar os componentes
contidos nesse formulário.
********************************/
int PIGCriaForm(char *nomeArqTexto){
    return CPIGGerenciadorForms::CriaForm(nomeArqTexto);
}

/********************************
A função PIGFormTrataEvento() é responsável por tratar eventos de mouse e de teclado relacionados aos componentes existentes dentro do formulário em questão.
Parâmetros:
idForm (entrada, passagem por parâmetro): identificador do formulário em questão.
PIGEvento (entrada, passagem por valor): evento a ser tratado pelo formulário.
Retorno:
inteiro indicando que o evento foi tratado por alum componente do formula´rio (PIG_SELECIONADO_TRATADO) ou não foi tratado por nenhum componente (PIG_NAO_SELECIONADO).
********************************/
int PIGFormTrataEvento(int idForm, PIGEvento evento){
    return CPIGGerenciadorForms::GetForm(idForm)->TrataEvento(evento);
}

/********************************
A função PIGFormDesenha() é responsável por desenhar o formulário e todos os seus componentes.
Parâmetros:
idForm (entrada, passagem por parâmetro*: identificador do formulário em questão.
Retorno:
inteiro se houve o desenho do formulário e dos componentes ou não.
********************************/
int PIGFormDesenha(int idForm){
    return CPIGGerenciadorForms::GetForm(idForm)->Desenha();
}

/********************************
A função PIGFormMove() é responsável por mover o formulário e todos os seus componentes.
Parâmetros:
idForm (entrada, passagem por parâmetro*: identificador do formulário em questão.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usuário deseja reposicionar o formulário.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usuário deseja reposicionar o formulário.
********************************/
void PIGFormMove(int idForm, int posicaoX, int posicaoY){
    CPIGGerenciadorForms::GetForm(idForm)->Move(posicaoX,posicaoY);
}

/********************************
A função PIGDestroiForm() é responsável por liberar a memória do formulário e de todos os componentes envolvidos.
Parâmetros:
idForm (entrada, passagem por parâmetro): identificador do formulário em questão.
********************************/
void PIGDestroiForm(int idForm){
    CPIGGerenciadorForms::DestroiForm(idForm);
}

/********************************
A função PIGFormGetIdPorComponente() é responsável por recuperar o identificador do formulário que possui o componente passado como parâmetro.
Parâmetros:
idComponente (entrada, passagem por parâmetro): identificador do componente em questão.
Retorno:
inteiro que representa o identificador do formulário que possui o componente em questão.
********************************/
int PIGFormGetIdPorComponente(int idComponente){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetId();
}

/********************************
A função PIGFormGetIdComponenteLabel() é responsável por recuperar o identificador do componente que possui o label informado.
Parâmetros:
idForm (entrada, passagem por parâmetro): identificador do formulário que possui o componente.
label (entrada, passagem por referência): label a ser procurado no formulário.
Retorno:
inteiro que representa o identificador do componente que possui o label (se encontrado) ou -1, se não encontrado.
********************************/
int PIGFormGetIdComponenteLabel(int idForm, char *label){
    return CPIGGerenciadorForms::GetForm(idForm)->GetIdComponente(label);
}

/********************************
A função PIGFormGetIdComponenteIndice() é responsável por recuperar o identificador do componente que possui o índice (ordem de criação) informado.
Parâmetros:
idForm (entrada, passagem por parâmetro): identificador do formulário que possui o componente.
indice (entrada, passagem por referência): índice (ordem de criação) do componente a ser procurado no formulário.
Retorno:
inteiro que representa o identificador do componente que possui o índice.
********************************/
int PIGFormGetIdComponenteIndice(int idForm, int indice){
    return CPIGGerenciadorForms::GetForm(idForm)->GetIdComponente(indice);
}

/*******COMPONENTES*********/

int PIGCriaComponentePorParametro(int idForm, char* parametros){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaComponentePorParametro(parametros);
}

void PIGComponentesDefineAcao(int idComponente, PIGFuncaoSimples funcao, void *parametro){
    CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->DefineAcao(funcao,parametro);
}

void PIGComponentesSetLabel(int idComponente, char* novoLabel){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->SetLabel(novoLabel);
}

void PIGComponentesGetLabel(int idComponente, char *label){
    strcpy(label,(char*)(CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->GetLabel()).c_str());
}

void PIGComponentesSetFonteLabel(int idComponente, int fonte){
    CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->SetFonteLabel(fonte);
}

int PIGComponentesGetFonteLabel(int idComponente){
    return CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->GetFonteLabel();
}

void PIGComponentesSetCorLabel(int idComponente, PIGCor cor){
    CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->SetCorLabel(cor);
}

PIGCor PIGComponentesGetCorLabel(int idComponente){
    return CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->GetCorLabel();
}

void PIGComponentesSetHint(int idComponente, char *hint){
    CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->SetHint(hint);
}

void PIGComponentesGetHint(int idComponente, char* hint){
    strcpy(hint,(char*)(CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->GetHint()).c_str());
}

void PIGComponentesSetFonteHint(int idComponente, int fonte){
    CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->SetFonteHint(fonte);
}

int PIGComponentesGetFonteHint(int idComponente){
    return CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->GetFonteHint();
}

void PIGComponentesSetCorHint(int idComponente, PIGCor cor){
    CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->SetCorHint(cor);
}

PIGCor PIGComponentesGetCorHint(int idComponente){
    return CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->GetCorHint();
}

void PIGComponentesSetAudio(int idComponente, int idAudio){
    CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->SetAudio(idAudio);
}

int PIGComponentesGetAudio(int idComponente){
    return CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->GetAudio();
}

void PIGComponentesMove(int idComponente, int posicaoX, int posicaoY){
    CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->Move(posicaoX,posicaoY);
}

void PIGComponentesGetXY(int idComponente, int *posicaoX, int *posicaoY){
    PIGPonto2D p = CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->GetXY();
    *posicaoX = p.x;
    *posicaoY = p.y;
}

void PIGComponentesDesloca(int idComponente, int x, int y){
    CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->Desloca(x,y);
}

void PIGComponentesSetDimensoes(int idComponente, int altura, int largura){
    CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->SetDimensoes(altura,largura);
}

void PIGComponentesGetDimensoes(int idComponente, int *altura, int *largura){
    CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->GetDimensoes(*altura,*largura);
}

void PIGComponentesSetPosicaoPadraoLabel(int idComponente, PIGPosicaoComponente pos){
    CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->SetPosicaoPadraoLabel(pos);
}

void PIGComponentesSetPosicaoPersonalizadaLabel(int idComponente, int x, int y){
    CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->SetPosicaoPersonalizadaLabel(x,y);
}

void PIGComponentesSetHabilitado(int idComponente, int valor){
    CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->SetHabilitado(valor);
}

int PIGComponentesGetHabilitado(int idComponente){
    return CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->GetHabilitado();
}

void PIGComponentesSetVisivel(int idComponente, int valor){
    CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->SetVisivel(valor);
}

int PIGComponentesGetVisivel(int idComponente){
    return CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->GetVisivel();
}

int PIGComponentesGetAcionado(int idComponente){
    return CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->GetAcionado();
}

int PIGComponentesGetMouseOver(int idComponente){
    return CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->GetMouseOver();
}

PIGTipoComponente PIGComponenteGetTipo(int idComponente){
    return CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->GetTipo();
}

void PIGComponentesSetMargens(int idComponente, int margemEsq, int margemDir, int margemBaixo, int margemCima){
    CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->SetMargens(margemEsq,margemDir,margemBaixo,margemCima);
}

/*******BOTAOCLICK*********/

int PIGCriaBotaoClick(int idForm, int altura, int largura, char* nomeArq, int retiraFundo=1){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaBotaoClick(altura,largura,nomeArq,retiraFundo);
}

int PIGCriaBotaoClick(int idForm, int altura, int largura){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaBotaoClick(altura,largura);
}

void PIGBotaoClickDefineAtalho(int idComponente, int teclaAtalho){
    CPIGGerenciadorForms::GetComponente<PIGBotaoClick>(idComponente)->DefineAtalho(teclaAtalho);
}

void PIGBotaoClickDefineTempoRepeticao(int idComponente, double segundos){
    CPIGGerenciadorForms::GetComponente<PIGBotaoClick>(idComponente)->DefineTempoRepeticao(segundos);
}

void PIGBotaoClickDefineTempoAcionamento(int idComponente, double segundos){
    CPIGGerenciadorForms::GetComponente<PIGBotaoClick>(idComponente)->DefineTempoAcionamento(segundos);
}

/*******BOTAOONOFF*********/

int PIGCriaBotaoOnOff(int idForm, int altura, int largura, char* nomeArq, int retiraFundo = 1){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaBotaoOnOff(altura,largura,nomeArq,retiraFundo);
}

int PIGCriaBotaoOnOff(int idForm, int altura, int largura){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaBotaoOnOff(altura,largura);
}

void PIGBotaoOnOffDefineAtalho(int idComponente, int teclaAtalho){
    CPIGGerenciadorForms::GetComponente<PIGBotaoOnOff>(idComponente)->DefineAtalho(teclaAtalho);
}


/*******AREADETEXTO*********/

int PIGCriaAreaDeTexto(int idForm, int altura, int largura, char* nomeArq, int maxCars=200, int retiraFundo=1){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaAreaDeTexto(altura,largura,nomeArq,maxCars,retiraFundo);
}

int PIGCriaAreaDeTexto(int idForm, int altura, int largura, int maxCars=200){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaAreaDeTexto(altura,largura,maxCars);
}

void PIGAreaDeTextoSetFonteTexto(int idComponente, int fonte){
    CPIGGerenciadorForms::GetComponente<PIGAreaDeTexto>(idComponente)->SetFonteTexto(fonte);
}

void PIGAreaDeTextoSetLinhasAbaixoTexto(int idComponente, int visivel){
    CPIGGerenciadorForms::GetComponente<PIGAreaDeTexto>(idComponente)->SetLinhasAbaixoTexto(visivel);
}

void PIGAreaDeTextoSetEspacoEntreAsLinhas(int idComponente, int espaco){
    CPIGGerenciadorForms::GetComponente<PIGAreaDeTexto>(idComponente)->SetEspacoEntreAsLinhas(espaco);
}

void PIGAreaDeTextoSetTexto(int idComponente, char* frase){
    CPIGGerenciadorForms::GetComponente<PIGAreaDeTexto>(idComponente)->SetTexto(frase);
}

void PIGAreaDeTextoSetCorCursor(int idComponente, PIGCor cor){
    CPIGGerenciadorForms::GetComponente<PIGAreaDeTexto>(idComponente)->SetCorCursor(cor);
}

vector<string> PIGAreaDeTextoGetLinhasTexto(int idComponente){
    return CPIGGerenciadorForms::GetComponente<PIGAreaDeTexto>(idComponente)->GetLinhasTexto();
}

void PIGAreaDeTextoGetTexto(int idComponente, char* texto){
    strcpy(texto,(char*)(CPIGGerenciadorForms::GetComponente<PIGAreaDeTexto>(idComponente)->GetTexto()).c_str());
}

/**********CAMPOTEXTO**************/

int PIGCriaCampoTexto(int idForm, int altura, int largura, char* nomeArq, int maxCars=200, int apenasNumeros=0, int senha=0, int retiraFundo=1){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaCampoTextoESenha(altura,largura,nomeArq,maxCars,apenasNumeros,retiraFundo,senha);
}

int PIGCriaCampoTexto(int idForm, int altura, int largura, int maxCars=200, int apenasNumeros=0, int senha=0){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaCampoTextoESenha(altura,largura,maxCars,apenasNumeros,senha);
}

void PIGCampoTextoSetTexto(int idComponente, char* frase){
    CPIGGerenciadorForms::GetComponente<PIGCampoTextoESenha>(idComponente)->SetTexto(frase);
}

void PIGCampoTextoSetFonteTexto(int idComponente, int fonte){
    CPIGGerenciadorForms::GetComponente<PIGCampoTextoESenha>(idComponente)->SetFonteTexto(fonte);
}

void PIGCampoTextoSetCorCursor(int idComponente, PIGCor cor){
    CPIGGerenciadorForms::GetComponente<PIGCampoTextoESenha>(idComponente)->SetCorCursor(cor);
}

void PIGCampoTextoSetCorTexto(int idComponente, PIGCor cor){
    CPIGGerenciadorForms::GetComponente<PIGCampoTextoESenha>(idComponente)->SetCorFonte(cor);
}

void PIGCampoTextoSetCorFundo(int idComponente, PIGCor cor){
    CPIGGerenciadorForms::GetComponente<PIGCampoTextoESenha>(idComponente)->SetCorFundo(cor);
}

void PIGCampoTextoSetMascara(int idComponente, char mascara){
    CPIGGerenciadorForms::GetComponente<PIGCampoTextoESenha>(idComponente)->SetMascara(mascara);
}

void PIGCampoTextoGetTexto(int idComponente, char* texto){
    strcpy(texto,(char*)(CPIGGerenciadorForms::GetComponente<PIGCampoTextoESenha>(idComponente)->GetTexto()).c_str());
}

/**********CAMPOSENHA**************/

/*int PIGCriaCampoSenha(int idForm, int altura, int largura, char* nomeArq, int maxCars = 200, bool apenasNumeros=false, int retiraFundo=1){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaCampoTextoESenha(altura,largura,nomeArq,maxCars,apenasNumeros,retiraFundo,true);
}

int PIGCriaCampoSenha(int idForm, int altura, int largura, int maxCars = 200, bool apenasNumeros=false){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaCampoTextoESenha(altura,largura,maxCars,apenasNumeros,true);
}

void PIGCampoSenhaSetTexto(int idComponente, char* frase){
    CPIGGerenciadorForms::GetComponente<PIGCampoTextoESenha>(idComponente)->SetTexto(frase);
}

void PIGCampoSenhaSetFonteTexto(int idComponente, int fonte){
    CPIGGerenciadorForms::GetComponente<PIGCampoTextoESenha>(idComponente)->SetFonteTexto(fonte);
}

void PIGCampoSenhaSetCorCursor(int idComponente, PIGCor cor){
    CPIGGerenciadorForms::GetComponente<PIGCampoTextoESenha>(idComponente)->SetCorCursor(cor);
}*/

/**********LISTA**************/

int PIGCriaListBox(int idForm, int larguraTotal, int alturaLinha, int alturaItem, int largItem, char* nomeArq, int retiraFundo=1){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaListBox(larguraTotal,alturaLinha,alturaItem,largItem,nomeArq,retiraFundo);
}

int PIGCriaListBox(int idForm, int larguraTotal, int alturaLinha, int alturaItem, int largItem){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaListBox(larguraTotal,alturaLinha,alturaItem,largItem);
}

void PIGListBoxCriaItem(int idComponente, char* texto, char *imagemIcone = "", char *imagemFundo="", char *hintMsg="", int itemHabilitado=0, int retiraFundoImg=1, int retiraFundoIcone=1){
    CPIGGerenciadorForms::GetComponente<PIGListBox>(idComponente)->CriaItem(texto,imagemIcone,imagemFundo,false,itemHabilitado,hintMsg,retiraFundoImg,retiraFundoIcone);
}

int PIGListBoxSetMarcadoItem(int idComponente, int indice, int marcado){
    return CPIGGerenciadorForms::GetComponente<PIGListBox>(idComponente)->SetAcionadoItem(indice,marcado);
}

int PIGListBoxGetMarcadoItem(int idComponente, int indice){
    return CPIGGerenciadorForms::GetComponente<PIGListBox>(idComponente)->GetAcionadoItem(indice);
}

int PIGListBoxGetHabilitadoItem(int idComponente, int item){
    return CPIGGerenciadorForms::GetComponente<PIGDropDown>(idComponente)->GetHabilitadoItem(item);
}

int PIGListBoxSetHabilitadoItem(int idComponente, int item, int habilitado){
    return CPIGGerenciadorForms::GetComponente<PIGDropDown>(idComponente)->SetHabilitadoItem(item,habilitado);
}

void PIGListBoxSetFonteItem(int idComponente, int fonte, int item=-1){
    CPIGGerenciadorForms::GetComponente<PIGListBox>(idComponente)->SetFonteItem(fonte,item);
}

void PIGListBoxSetAudioItem(int idComponente, int audio, int item=-1){
    CPIGGerenciadorForms::GetComponente<PIGListBox>(idComponente)->SetAudioItem(item,audio);
}

void PIGListBoxSetCorLabelItem(int idComponente, PIGCor cor, int item=-1){
    CPIGGerenciadorForms::GetComponente<PIGListBox>(idComponente)->SetCorLabelItem(cor,item);
}

void PIGListBoxAlinhaLabelDireita(int idComponente){
    CPIGGerenciadorForms::GetComponente<PIGListBox>(idComponente)->AlinhaLabelItens(PIG_POSICAO_DIR_CENTRO);
}

void PIGListBoxAlinhaLabelEsquerda(int idComponente){
    CPIGGerenciadorForms::GetComponente<PIGListBox>(idComponente)->AlinhaLabelItens(PIG_POSICAO_ESQ_CENTRO);
}

void PIGListBoxAlinhaLabelCentro(int idComponente){
    CPIGGerenciadorForms::GetComponente<PIGListBox>(idComponente)->AlinhaLabelItens(PIG_POSICAO_CENTRO_CENTRO);
}

void PIGListBoxAlinhaIconeDireita(int idComponente){
    CPIGGerenciadorForms::GetComponente<PIGListBox>(idComponente)->AlinhaIcones(PIG_POSICAO_DIR_CENTRO);
}

void PIGListBoxAlinhaIconeEsquerda(int idComponente){
    CPIGGerenciadorForms::GetComponente<PIGListBox>(idComponente)->AlinhaIcones(PIG_POSICAO_ESQ_CENTRO);
}

void PIGListBoxDefineDimensaoIconeItem(int idComponente, int alturaIcone, int larguraIcone){
    CPIGGerenciadorForms::GetComponente<PIGListBox>(idComponente)->SetDimensoesIcone(alturaIcone,larguraIcone);
}

void PIGListBoxGetLabelItem(int idComponente, int indice, char *label){
    strcpy(label,CPIGGerenciadorForms::GetComponente<PIGListBox>(idComponente)->GetLabelItem(indice).c_str());
}

int PIGListBoxGetItemDestaque(int idComponente){
    return CPIGGerenciadorForms::GetComponente<PIGListBox>(idComponente)->GetItemDestaque();
}


/**********DROPDOWN**************/

int PIGCriaDropDown(int idForm, int larguraTotal, int alturaLinha, int alturaItem, int larguraItem, char* nomeArq, int retiraFundo=1){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaDropDown(larguraTotal,alturaLinha,alturaItem,larguraItem,nomeArq,retiraFundo);
}

int PIGCriaDropDown(int idForm, int larguraTotal, int alturaLinha, int alturaItem, int larguraItem){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaDropDown(larguraTotal,alturaLinha,alturaItem,larguraItem);
}

void PIGDropDownCriaItem(int idComponente, char* texto, char* imagemIcone = "", char *imagemFundo="", char* hintMsg="", int itemHabilitado=1, int retiraFundoImg=1, int retiraFundoIcone=1){
    CPIGGerenciadorForms::GetComponente<PIGDropDown>(idComponente)->CriaItem(texto,imagemIcone,imagemFundo,itemHabilitado,hintMsg,retiraFundoImg,retiraFundoIcone);
}

int PIGDropDownSetMarcadoItem(int idComponente, int indice, int marcado){
    return CPIGGerenciadorForms::GetComponente<PIGDropDown>(idComponente)->SetAcionadoItem(indice,marcado);
}

int PIGDropDownGetMarcadoItem(int idComponente, int indice){
    return CPIGGerenciadorForms::GetComponente<PIGDropDown>(idComponente)->GetAcionadoItem(indice);
}

int PIGDropDownGetHabilitadoItem(int idComponente, int item){
    return CPIGGerenciadorForms::GetComponente<PIGDropDown>(idComponente)->GetHabilitadoItem(item);
}

int PIGDropDownSetHabilitadoItem(int idComponente, int item, int habilitado){
    return CPIGGerenciadorForms::GetComponente<PIGDropDown>(idComponente)->SetHabilitadoItem(item,habilitado);
}

void PIGDropDownSetFonteItem(int idComponente, int fonte, int item=-1){
    CPIGGerenciadorForms::GetComponente<PIGDropDown>(idComponente)->SetFonteItem(fonte,item);
}

void PIGDropDownSetAudioItem(int idComponente, int audio, int item=-1){
    CPIGGerenciadorForms::GetComponente<PIGDropDown>(idComponente)->SetAudioItem(item,audio);
}

void PIGDropDownSetCorLabelItem(int idComponente,PIGCor cor, int item=-1){
    CPIGGerenciadorForms::GetComponente<PIGDropDown>(idComponente)->SetCorLabelItem(cor,item);
}

void PIGDropDownAlinhaLabelDireita(int idComponente){
    CPIGGerenciadorForms::GetComponente<PIGDropDown>(idComponente)->AlinhaLabelItens(PIG_POSICAO_DIR_CENTRO);
}

void PIGDropDownAlinhaLabelEsquerda(int idComponente){
    CPIGGerenciadorForms::GetComponente<PIGDropDown>(idComponente)->AlinhaLabelItens(PIG_POSICAO_ESQ_CENTRO);
}

void PIGDropDownAlinhaLabelCentro(int idComponente){
    CPIGGerenciadorForms::GetComponente<PIGDropDown>(idComponente)->AlinhaLabelItens(PIG_POSICAO_CENTRO_CENTRO);
}

void PIGDropDownAlinhaIconeDireita(int idComponente){
    CPIGGerenciadorForms::GetComponente<PIGDropDown>(idComponente)->AlinhaIcones(PIG_POSICAO_DIR_CENTRO);
}

void PIGDropDownAlinhaIconeEsquerda(int idComponente){
    CPIGGerenciadorForms::GetComponente<PIGDropDown>(idComponente)->AlinhaIcones(PIG_POSICAO_ESQ_CENTRO);
}

void PIGDropDownDefineDimensaoIconeItem(int idComponente, int alturaIcone, int larguraIcone){
    CPIGGerenciadorForms::GetComponente<PIGDropDown>(idComponente)->SetDimensoesIcone(alturaIcone,larguraIcone);
}

void PIGDropDownGetLabelItem(int idComponente, int indice, char *label){
    strcpy(label,CPIGGerenciadorForms::GetComponente<PIGDropDown>(idComponente)->GetLabelItem(indice).c_str());
}

int PIGDropDownGetItemDestaque(int idComponente){
    return CPIGGerenciadorForms::GetComponente<PIGDropDown>(idComponente)->GetItemDestaque();
}




/**********RADIOBOX**************/

int PIGCriaRadioBox(int idForm, int larguraTotal, int alturaLinha, char* imagemItem, int alturaItem, int larguraItem, char* imagemFundo, int retiraFundo=1){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaRadioBox(larguraTotal,alturaLinha,imagemItem,alturaItem,larguraItem,imagemFundo,retiraFundo);
}

int PIGCriaRadioBox(int idForm, int larguraTotal, int alturaLinha, char* imagemItem, int alturaItem, int larguraItem){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaRadioBox(larguraTotal,alturaLinha,imagemItem,alturaItem,larguraItem);
}

void PIGRadioBoxCriaItem(int idComponente, char* itemLabel, char *imagemFundo="", char *hintMsg="", int itemHabilitado=1, int retiraFundo=1, int retiraFundoIcone=1){
    CPIGGerenciadorForms::GetComponente<PIGRadioBox>(idComponente)->CriaItem(itemLabel,imagemFundo,itemHabilitado,hintMsg,retiraFundo,retiraFundoIcone);
}

int PIGRadioBoxSetMarcadoItem(int idComponente, int indice, int marcado){
    return CPIGGerenciadorForms::GetComponente<PIGRadioBox>(idComponente)->SetAcionadoItem(indice,marcado);
}

int PIGRadioBoxGetMarcadoItem(int idComponente, int indice){
    return CPIGGerenciadorForms::GetComponente<PIGRadioBox>(idComponente)->GetAcionadoItem(indice);
}

int PIGRadioBoxGetHabilitadoItem(int idComponente, int item){
    return CPIGGerenciadorForms::GetComponente<PIGRadioBox>(idComponente)->GetHabilitadoItem(item);
}

int PIGRadioBoxSetHabilitadoItem(int idComponente, int item, int habilitado){
    return CPIGGerenciadorForms::GetComponente<PIGRadioBox>(idComponente)->SetHabilitadoItem(item,habilitado);
}

void PIGRadioBoxSetAudioItem(int idComponente, int item, int audio){
    CPIGGerenciadorForms::GetComponente<PIGRadioBox>(idComponente)->SetAudioItem(item,audio);
}

void PIGRadioBoxSetFonteItem(int idComponente, int fonte, int item=-1){
    CPIGGerenciadorForms::GetComponente<PIGRadioBox>(idComponente)->SetFonteItem(fonte,item);
}

void PIGRadioBoxSetCorLabelItem(int idComponente, PIGCor cor, int item=-1){
    CPIGGerenciadorForms::GetComponente<PIGRadioBox>(idComponente)->SetCorLabelItem(cor,item);
}

void PIGRadioBoxAlinhaLabelDireita(int idComponente){
    CPIGGerenciadorForms::GetComponente<PIGRadioBox>(idComponente)->AlinhaLabelItens(PIG_POSICAO_DIR_CENTRO);
}

void PIGRadioBoxAlinhaLabelEsquerda(int idComponente){
    CPIGGerenciadorForms::GetComponente<PIGRadioBox>(idComponente)->AlinhaLabelItens(PIG_POSICAO_ESQ_CENTRO);
}

void PIGRadioBoxAlinhaLabelCentro(int idComponente){
    CPIGGerenciadorForms::GetComponente<PIGRadioBox>(idComponente)->AlinhaLabelItens(PIG_POSICAO_CENTRO_CENTRO);
}

void PIGRadioBoxAlinhaIconeDireita(int idComponente){
    CPIGGerenciadorForms::GetComponente<PIGRadioBox>(idComponente)->AlinhaIcones(PIG_POSICAO_DIR_CENTRO);
}

void PIGRadioBoxAlinhaIconeEsquerda(int idComponente){
    CPIGGerenciadorForms::GetComponente<PIGRadioBox>(idComponente)->AlinhaIcones(PIG_POSICAO_ESQ_CENTRO);
}

void PIGRadioBoxDefineDimensaoIconeItem(int idComponente, int alturaIcone, int larguraIcone){
    CPIGGerenciadorForms::GetComponente<PIGRadioBox>(idComponente)->SetDimensoesIcone(alturaIcone,larguraIcone);
}

int PIGRadioBoxGetItemDestaque(int idComponente){
    return CPIGGerenciadorForms::GetComponente<PIGRadioBox>(idComponente)->GetItemDestaque();
}

void PIGRadioBoxGetLabelItem(int idComponente, int indice, char *label){
    strcpy(label,CPIGGerenciadorForms::GetComponente<PIGRadioBox>(idComponente)->GetLabelItem(indice).c_str());
}

/**********CHECKBOX**************/

int PIGCriaCheckBox(int idForm, int larguraTotal, int alturaLinha, char* imagemItem, int alturaItem, int larguraItem, char* imagemFundo, int retiraFundo=1){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaCheckBox(larguraTotal,alturaLinha,imagemItem,alturaItem,larguraItem,imagemFundo,retiraFundo);
}

int PIGCriaCheckBox(int idForm, int larguraTotal, int alturaLinha, char* imagemItem, int alturaItem, int larguraItem, int idJanela=0){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaCheckBox(larguraTotal,alturaLinha,imagemItem,alturaItem,larguraItem);
}

void PIGCheckBoxCriaItem(int idComponente, char* itemLabel, char *imagemFundo="", char* hintMsg="", int itemMarcado=0, int itemHabilitado=1, int retiraFundo=1, int retiraFundoIcone=1){
    CPIGGerenciadorForms::GetComponente<PIGCheckBox>(idComponente)->CriaItem(itemLabel,imagemFundo,itemMarcado,itemHabilitado,hintMsg,retiraFundo,retiraFundoIcone);
}

int PIGCheckBoxSetMarcadoItem(int idComponente, int indice, int marcado){
    return CPIGGerenciadorForms::GetComponente<PIGCheckBox>(idComponente)->SetAcionadoItem(indice,marcado);
}

int PIGCheckBoxGetMarcadoItem(int idComponente, int indice){
    return CPIGGerenciadorForms::GetComponente<PIGCheckBox>(idComponente)->GetAcionadoItem(indice);
}

int PIGCheckBoxGetHabilitadoItem(int idComponente, int item){
    return CPIGGerenciadorForms::GetComponente<PIGCheckBox>(idComponente)->GetHabilitadoItem(item);
}

int PIGCheckBoxSetHabilitadoItem(int idComponente, int item, int habilitado){
    return CPIGGerenciadorForms::GetComponente<PIGCheckBox>(idComponente)->SetHabilitadoItem(item,habilitado);
}

void PIGCheckBoxSetAudioItem(int idComponente, int item, int audio){
    CPIGGerenciadorForms::GetComponente<PIGCheckBox>(idComponente)->SetAudioItem(item,audio);
}

void PIGCheckBoxSetFonteItem(int idComponente, int fonte, int item=-1){
    CPIGGerenciadorForms::GetComponente<PIGCheckBox>(idComponente)->SetFonteItem(fonte,item);
}

void PIGCheckBoxSetCorLabelItem(int idComponente, PIGCor cor, int item=-1){
    CPIGGerenciadorForms::GetComponente<PIGCheckBox>(idComponente)->SetCorLabelItem(cor,item);
}

void PIGCheckBoxAlinhaLabelDireita(int idComponente){
    CPIGGerenciadorForms::GetComponente<PIGCheckBox>(idComponente)->AlinhaLabelItens(PIG_POSICAO_DIR_CENTRO);
}

void PIGCheckBoxAlinhaLabelEsquerda(int idComponente){
    CPIGGerenciadorForms::GetComponente<PIGCheckBox>(idComponente)->AlinhaLabelItens(PIG_POSICAO_ESQ_CENTRO);
}

void PIGCheckBoxAlinhaLabelCentro(int idComponente){
    CPIGGerenciadorForms::GetComponente<PIGCheckBox>(idComponente)->AlinhaLabelItens(PIG_POSICAO_CENTRO_CENTRO);
}

void PIGCheckBoxAlinhaIconeDireita(int idComponente){
    CPIGGerenciadorForms::GetComponente<PIGCheckBox>(idComponente)->AlinhaIcones(PIG_POSICAO_DIR_CENTRO);
}

void PIGCheckBoxAlinhaIconeEsquerda(int idComponente){
    CPIGGerenciadorForms::GetComponente<PIGCheckBox>(idComponente)->AlinhaIcones(PIG_POSICAO_ESQ_CENTRO);
}

void PIGCheckBoxDefineDimensaoIconeItem(int idComponente, int alturaIcone, int larguraIcone){
    CPIGGerenciadorForms::GetComponente<PIGCheckBox>(idComponente)->SetDimensoesIcone(alturaIcone,larguraIcone);
}

void PIGCheckBoxSetMarcadoTodos(int idComponente, int marcado){
    CPIGGerenciadorForms::GetComponente<PIGCheckBox>(idComponente)->SetAcionadoTodos(marcado);
}

void PIGCheckBoxGetLabelItem(int idComponente, int indice, char *label){
    strcpy(label,CPIGGerenciadorForms::GetComponente<PIGCheckBox>(idComponente)->GetLabelItem(indice).c_str());
}

vector<int> PIGCheckBoxGetItensMarcados(int idComponente){
    return CPIGGerenciadorForms::GetComponente<PIGCheckBox>(idComponente)->GetItensMarcados();
}




/**********GAUGE**************/

int PIGCriaGaugeBar(int idForm, int altura, int largura, char* imgMoldura, char *imgMarcador="", int retiraFundoMoldura=1, int retiraFundoMarcador=1){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaGaugeBar(altura,largura,imgMoldura,imgMarcador,retiraFundoMoldura,retiraFundoMarcador);
}

int PIGCriaGaugeBar(int idForm, int altura, int largura){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaGaugeBar(altura,largura);
}

void PIGGaugeBarSetDelta(int idComponente, double valor){
    CPIGGerenciadorForms::GetComponente<PIGGaugeBar>(idComponente)->SetDelta(valor);
}

void PIGGaugeBarAvancaDelta(int idComponente){
    CPIGGerenciadorForms::GetComponente<PIGGaugeBar>(idComponente)->AvancaDelta();
}

double PIGGaugeBarGetPorcentagemConcluida(int idComponente){
    return CPIGGerenciadorForms::GetComponente<PIGGaugeBar>(idComponente)->GetPorcentagemConcluida();
}

void PIGGaugeBarSetPorcentagemConcluida(int idComponente, double porcentagem){
    CPIGGerenciadorForms::GetComponente<PIGGaugeBar>(idComponente)->SetPorcentagemConcluida(porcentagem);
}

void PIGGaugeBarMinimizaValor(int idComponente){
    CPIGGerenciadorForms::GetComponente<PIGGaugeBar>(idComponente)->MinimizaValorAtual();
}

void PIGGaugeBarMaximizaValor(int idComponente){
    CPIGGerenciadorForms::GetComponente<PIGGaugeBar>(idComponente)->MaximizaValorAtual();
}

void PIGGaugeBarSetValorMin(int idComponente, double minimo){
    CPIGGerenciadorForms::GetComponente<PIGGaugeBar>(idComponente)->SetValorMin(minimo);
}

void PIGGaugeBarSetValorMax(int idComponente, double maximo){
    CPIGGerenciadorForms::GetComponente<PIGGaugeBar>(idComponente)->SetValorMax(maximo);
}

double PIGGaugeBarGetValorAtual(int idComponente){
    return CPIGGerenciadorForms::GetComponente<PIGGaugeBar>(idComponente)->GetValorAtual();
}

void PIGGaugeBarSetValorAtual(int idComponente, double valor){
    CPIGGerenciadorForms::GetComponente<PIGGaugeBar>(idComponente)->SetValorAtual(valor);
}

void PIGGaugeBarAvancaBarra(int idComponente, double valor){
    CPIGGerenciadorForms::GetComponente<PIGGaugeBar>(idComponente)->AvancaMarcador(valor);
}

int PIGGaugeBarGetValorMax(int idComponente){
    return CPIGGerenciadorForms::GetComponente<PIGGaugeBar>(idComponente)->GetValorMax();
}

int PIGGaugeBarGetValorMin(int idComponente){
    return CPIGGerenciadorForms::GetComponente<PIGGaugeBar>(idComponente)->GetValorMin();
}

void PIGGaugeBarSetOrientacao(int idComponente, PIGGaugeCrescimento orientacao){
    CPIGGerenciadorForms::GetComponente<PIGGaugeBar>(idComponente)->SetOrientacao(orientacao);
}

void PIGGaugeBarSetMarcadorFrente(int idComponente, int frente){
    CPIGGerenciadorForms::GetComponente<PIGGaugeBar>(idComponente)->SetMarcadorFrente(frente);
}

void PIGGaugeBarSetCorInicial(int idComponente, PIGCor cor){
    CPIGGerenciadorForms::GetComponente<PIGGaugeBar>(idComponente)->SetCorInicial(cor);
}

void PIGGaugeBarSetCorFinal(int idComponente, PIGCor cor){
    CPIGGerenciadorForms::GetComponente<PIGGaugeBar>(idComponente)->SetCorFinal(cor);
}

void PIGGaugeBarSetCorTrilha(int idComponente, PIGCor cor){
    CPIGGerenciadorForms::GetComponente<PIGGaugeBar>(idComponente)->SetCorTrilha(cor);
}


/**********GAUGECIRCULAR**************/

int PIGCriaGaugeCircular(int idForm, int altura, int largura){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaGaugeCircular(altura,largura);
}

int PIGCriaGaugeCircular(int idForm, int altura, int largura, string imgTrilha, int alturaMarcador, int larguraMarcador, string imgMarcador, int retiraFundoTrilha=1, int retiraFundoMarcador=1){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaGaugeCircular(altura,largura,imgTrilha,alturaMarcador,larguraMarcador,imgMarcador,retiraFundoTrilha,retiraFundoMarcador);
}

void PIGGaugeCircularSetDelta(int idComponente, double valor){
    CPIGGerenciadorForms::GetComponente<PIGGaugeCircular>(idComponente)->SetDelta(valor);
}

void PIGGaugeCircularAvancaDelta(int idComponente){
    CPIGGerenciadorForms::GetComponente<PIGGaugeCircular>(idComponente)->AvancaDelta();
}

double PIGGaugeCircularGetPorcentagemConcluida(int idComponente){
    return CPIGGerenciadorForms::GetComponente<PIGGaugeCircular>(idComponente)->GetPorcentagemConcluida();
}

void PIGGaugeCircularSetPorcentagemConcluida(int idComponente, double porcentagem){
    CPIGGerenciadorForms::GetComponente<PIGGaugeCircular>(idComponente)->SetPorcentagemConcluida(porcentagem);
}

void PIGGaugeCircularMinimizaValor(int idComponente){
    CPIGGerenciadorForms::GetComponente<PIGGaugeCircular>(idComponente)->MinimizaValorAtual();
}

void PIGGaugeCircularMaximizaValor(int idComponente){
    CPIGGerenciadorForms::GetComponente<PIGGaugeCircular>(idComponente)->MaximizaValorAtual();
}

void PIGGaugeCircularSetValorMax(int idComponente, double novoValor){
    CPIGGerenciadorForms::GetComponente<PIGGaugeCircular>(idComponente)->SetValorMax(novoValor);
}

void PIGGaugeCircularSetValorMin(int idComponente, double novoValor){
    CPIGGerenciadorForms::GetComponente<PIGGaugeCircular>(idComponente)->SetValorMin(novoValor);
}

int PIGGaugeCircularGetValorAtual(int idComponente){
    return CPIGGerenciadorForms::GetComponente<PIGGaugeCircular>(idComponente)->GetValorAtual();
}

void PIGGaugeCircularSetValorAtual(int idComponente, int novoValor){
    CPIGGerenciadorForms::GetComponente<PIGGaugeCircular>(idComponente)->SetValorAtual(novoValor);
}

void PIGGaugeCircularAvancaBarra(int idComponente, double valor){
    CPIGGerenciadorForms::GetComponente<PIGGaugeCircular>(idComponente)->AvancaMarcador(valor);
}

int PIGGaugeCircularGetValorMax(int idComponente){
    return CPIGGerenciadorForms::GetComponente<PIGGaugeCircular>(idComponente)->GetValorMax();
}

int PIGGaugeCircularGetValorMin(int idComponente){
    return CPIGGerenciadorForms::GetComponente<PIGGaugeCircular>(idComponente)->GetValorMin();
}

void PIGGaugeCircularSetOrientacao(int idComponente, PIGGaugeCrescimento orientacao){
    CPIGGerenciadorForms::GetComponente<PIGGaugeCircular>(idComponente)->SetOrientacao(orientacao);
}

void PIGGaugeCircularSetMarcadorFrente(int idComponente, int frente){
    CPIGGerenciadorForms::GetComponente<PIGGaugeCircular>(idComponente)->SetMarcadorFrente(frente);
}

void PIGGaugeCircularSetCorInicial(int idComponente, PIGCor cor){
    CPIGGerenciadorForms::GetComponente<PIGGaugeCircular>(idComponente)->SetCorInicial(cor);
}

void PIGGaugeCircularSetCorFinal(int idComponente, PIGCor cor){
    CPIGGerenciadorForms::GetComponente<PIGGaugeCircular>(idComponente)->SetCorFinal(cor);
}

void PIGGaugeCircularSetCorTrilha(int idComponente, PIGCor cor){
    CPIGGerenciadorForms::GetComponente<PIGGaugeCircular>(idComponente)->SetCorTrilha(cor);
}

void PIGGaugeCircularSetRaioInterno(int idComponente, int valorRaio){
    CPIGGerenciadorForms::GetComponente<PIGGaugeCircular>(idComponente)->SetRaioInterno(valorRaio);
}

void PIGGaugeCircularSetAnguloBase(int idComponente, double novoAng){
    CPIGGerenciadorForms::GetComponente<PIGGaugeCircular>(idComponente)->SetAnguloBase(novoAng);
}

void PIGGaugeCircularSetDeltaAngulo(int idComponente, double novoDelta){
    CPIGGerenciadorForms::GetComponente<PIGGaugeCircular>(idComponente)->SetDeltaAngulo(novoDelta);
}





/**********SLIDEBAR**************/

int PIGCriaSlideBar(int idForm, int altura, int largura, string imgTrilha, int alturaMarcador, int larguraMarcador, string imgMarcador, int retiraFundoTrilha=1, int retiraFundoMarcador=1){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaSlideBar(altura,largura,imgTrilha,alturaMarcador,larguraMarcador,imgMarcador,retiraFundoTrilha,retiraFundoMarcador);
}

int PIGCriaSlideBar(int idForm, int altura, int largura, int alturaMarcador, int larguraMarcador){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaSlideBar(altura,largura,alturaMarcador,larguraMarcador);
}

void PIGSlideBarSetDelta(int idComponente, double valor){
    CPIGGerenciadorForms::GetComponente<PIGSlideBar>(idComponente)->SetDelta(valor);
}

void PIGSlideBarAvancaDelta(int idComponente){
    CPIGGerenciadorForms::GetComponente<PIGSlideBar>(idComponente)->AvancaDelta();
}

double PIGSlideBarGetPorcentagemConcluida(int idComponente){
    return CPIGGerenciadorForms::GetComponente<PIGSlideBar>(idComponente)->GetPorcentagemConcluida();
}

void PIGSlideBarSetPorcentagemConcluida(int idComponente, double porcentagem){
    CPIGGerenciadorForms::GetComponente<PIGSlideBar>(idComponente)->SetPorcentagemConcluida(porcentagem);
}

void PIGSlideBarMinimizaValor(int idComponente){
    CPIGGerenciadorForms::GetComponente<PIGSlideBar>(idComponente)->MinimizaValorAtual();
}

void PIGSlideBarMaximizaValor(int idComponente){
    CPIGGerenciadorForms::GetComponente<PIGSlideBar>(idComponente)->MaximizaValorAtual();
}

void PIGSlideBarSetValorMin(int idComponente, double minimo){
    CPIGGerenciadorForms::GetComponente<PIGSlideBar>(idComponente)->SetValorMin(minimo);
}

void PIGSlideBarSetValorMax(int idComponente, double maximo){
    CPIGGerenciadorForms::GetComponente<PIGSlideBar>(idComponente)->SetValorMax(maximo);
}

double PIGSlideBarGetValorAtual(int idComponente){
    return CPIGGerenciadorForms::GetComponente<PIGSlideBar>(idComponente)->GetValorAtual();
}

void PIGSlideBarSetValorAtual(int idComponente, double valor){
    CPIGGerenciadorForms::GetComponente<PIGSlideBar>(idComponente)->SetValorAtual(valor);
}

void PIGSlideBarAvancaBarra(int idComponente, double valor){
    CPIGGerenciadorForms::GetComponente<PIGSlideBar>(idComponente)->AvancaMarcador(valor);
}

int PIGSlideBarGetValorMax(int idComponente){
    return CPIGGerenciadorForms::GetComponente<PIGSlideBar>(idComponente)->GetValorMax();
}

int PIGSlideBarGetValorMin(int idComponente){
    return CPIGGerenciadorForms::GetComponente<PIGSlideBar>(idComponente)->GetValorMin();
}

void PIGSlideBarSetOrientacao(int idComponente, PIGGaugeCrescimento orientacao){
    CPIGGerenciadorForms::GetComponente<PIGSlideBar>(idComponente)->SetOrientacao(orientacao);
}

void PIGSlideBarSetMarcadorFrente(int idComponente, int frente){
    CPIGGerenciadorForms::GetComponente<PIGSlideBar>(idComponente)->SetMarcadorFrente(frente);
}

void PIGSlideBarSetCorInicial(int idComponente, PIGCor cor){
    CPIGGerenciadorForms::GetComponente<PIGSlideBar>(idComponente)->SetCorInicial(cor);
}

void PIGSlideBarSetCorFinal(int idComponente, PIGCor cor){
    CPIGGerenciadorForms::GetComponente<PIGSlideBar>(idComponente)->SetCorFinal(cor);
}

void PIGSlideBarSetCorTrilha(int idComponente, PIGCor cor){
    CPIGGerenciadorForms::GetComponente<PIGSlideBar>(idComponente)->SetCorTrilha(cor);
}

void PIGSlideBarSetDeltas(int idComponente, int deltaPadrao, int deltaRodinha, int deltaTeclado){
    CPIGGerenciadorForms::GetComponente<PIGSlideBar>(idComponente)->SetDeltas(deltaPadrao,deltaRodinha,deltaTeclado);
}

#endif // PIGCOMFORM

#ifdef PIGCOMTELA

void PIGCriaTela(int idTela, int backgroundCriar=0, int backgroundCarregar=0, char *nomeArqCarregamento="", int janela=0){
    CPIGGerenciadorTelas::CriaTela(idTela,backgroundCriar,backgroundCarregar,nomeArqCarregamento,janela);
}

void PIGDestroiTela(int idTela){
    CPIGGerenciadorTelas::DestroiTela(idTela);
}

void PIGDefineComportamentoTela(int idTela, void *dados, PIGFuncaoSimples criar, PIGFuncaoSimples destruir, PIGFuncaoSimples carregar, PIGFuncaoSimples descarregar, PIGFuncaoSimples atualizar, PIGFuncaoSimples desenhar, PIGFuncaoEvento tratarEvento){
    CPIGGerenciadorTelas::SetComportamento(idTela,dados,criar,destruir,carregar,descarregar,atualizar,desenhar,tratarEvento);
}

void PIGTrataEventoTelaAtual(PIGEvento evento){
    CPIGGerenciadorTelas::TrataEvento(evento);
}

int PIGAtualizaTelaAtual(){
    return CPIGGerenciadorTelas::Atualiza();
}

int PIGDesenhaTelaAtual(){
    return CPIGGerenciadorTelas::Desenha();
}

void PIGMudaTelaAtual(int idTela, double tempoSaida=PIG_TEMPO_SAIDA_TELA_PADRAO, bool destroiDescarregar=false){
    CPIGGerenciadorTelas::PreparaMudancaTela(idTela,tempoSaida,destroiDescarregar);
}

void PIGSetDadosGeraisTelas(void *param){
    CPIGGerenciadorTelas::SetDadosGerais(param);
}

void *PIGGetDadosGeraisTelas(){
    return CPIGGerenciadorTelas::GetDadosGerais();
}

PIGEstadoTela PIGGetEstadoTela(int idTela){
    return CPIGGerenciadorTelas::GetEstadoTela(idTela);
}
#endif // PIGCOMTELA
