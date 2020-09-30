/********************************
Versão 0.7.2 da Biblioteca PIG.h
********************************/

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "SDL_net.h"
#include "Tipos_PIG.h"
#include "PIGFuncoesBasicas.h"
#include "CPIGErros.h"
#include "CPoolNumeros.h"
#include "SDL_mixer.h"
#include "CGerenciadorJanelas.h"
#include "CGerenciadorSockets.h"
#include "CAssetLoader.h"
#include "COffscreenRenderer.h"
#include "CGerenciadorFontes.h"
#include "CVisual.h"
#include "CPIGLabel.h"
#include "CMouse.h"
#include "CGerenciadorObjetos.h"
#include "CGerenciadorTimers.h"
#include "CGerenciadorVideos.h"
#include "CGerenciadorAudios.h"
#include "CGerenciadorAnimacoes.h"
#include "CGerenciadorParticulas.h"
#include "CGerenciadorControles.h"
#include "CGerenciadorForms.h"
#include "CJogo.h"
//#include "PIGFuncoesForm.h"

/********************************
/ Variáveis Globais
/********************************/
Jogo jogo=NULL;

/********************************
A função CriaJogo() é responsável pela criação da janela do jogo e pelos componentes audio-visuais.
Ela deve ser chamada antes de qualquer outra função da biblioteca PIG.h. Não é possível criar dois
jogos no mesmo progama. Logo, somente a primeira chamada terá efeito. A janela padrão da aplicação terá o tamanho definido pelas constantes ALT_TELA e LARG_TELA
definidas no arquivo Tipos.PIG.h, exceto se forem passados outros valores.
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
void CriaJogo(char *nomeJanela,int cursorProprio=0,int altura=ALT_TELA,int largura=LARG_TELA){
    if (jogo==NULL){
        jogo = new CJogo(nomeJanela,cursorProprio,altura,largura);
        CAssetLoader::Inicia();
        CMouse::Inicia(cursorProprio);
        CGerenciadorFontes::Inicia();
        CGerenciadorTimers::Inicia();
        CGerenciadorAudios::Inicia();
        CGerenciadorObjetos::Inicia();
        CGerenciadorParticulas::Inicia();
        CGerenciadorAnimacoes::Inicia();
        CGerenciadorControles::Inicia();
        CGerenciadorSockets::Inicia();
        CGerenciadorVideos::Inicia();
        CGerenciadorForms::Inicia();
    }
}

/********************************
A função GetEstadoJogo() indica o estado do jogo. Este estado é apenas um valor inteiro
que pode ser usado para indicar uma fase do jogo, ou a vez de algum jogador por exemplo.
Retorno:
inteiro indicando o valor do estado do jogo.
********************************/
int GetEstadoJogo(){
    return jogo->GetEstado();
}

/********************************
A função SetEstadoJogo() atribui um novo valor ao estado do jogo. Este estado é apenas um valor inteiro
que pode ser usado para indicar uma fase do jogo, ou a vez de algum jogador por exemplo.
Parâmetro:
estado (entrada, passagem por valor): indica o novo estado do jogo;
********************************/
void SetEstadoJogo(int estado){
    jogo->SetEstado(estado);
}

/********************************
A função DefineFundoJanela() permite escolher um arquivo de imagem como fundo (background) de uma janela que será automaticamente desenhado a cada nova etapa de desenho na tela.
Parâmetros:
nomeArquivoImagem (entrada, passagem por referência*): indica o caminho relativo ou absoluto do arquivo de imagem que será utilizado como fundo do jogo.
É utilizado o operador * apenas por se tratar de um parâmetro string. O valor do parâmetro não é alterado dentro da função.
idJanela (entrada, passagem por valor não-obrigatorio): indica de qual janela é a imagem.
********************************/
void DefineFundo(char *nomeArquivoImagem,int idJanela=0){
    CGerenciadorJanelas::DefineFundo(nomeArquivoImagem,idJanela);
}

/********************************
A função GetTeclado() faz um mapeamento entre o teclado físico a uma variável do tipo PIG_Teclado que funciona como um vetor de variáveis lógicas,
sendo cada posição do vetor relativo a uma tecla física.
Uma lista das possíveis teclas e seus código pode ser vista no arquivo Tipos_PIG.h.
Retorno:
O valor de retorno da função é um vetor de números inteiros que indicam se uma determinada tecla (índice do vetor) foi
pressionada (valor diferente de 0,zero) ou não (valor igual a zero).
********************************/
PIG_Teclado GetTeclado(){
    return jogo->PegaTeclado();
}

/********************************
A função GetEvento() indica se houve algum tipo de evento desde a última vez que a função foi chamada.
Um evento pode ser uma tecla pressionada, um clique do mouse ou outra coisa relacionada à tela do jogo.
Maiores informaçõe podem ser vistas no arquivo Tipo_PIG.h
Retorno:
O valor de retorno é um struct contendo o tipo de evento ocorrido e vários outros structs com informações específicas.
********************************/
PIG_Evento GetEvento(){
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
    CMouse::Desenha();
    jogo->EncerraDesenho(idJanela);
}

/********************************
A função SalvaTela() é responsável por criar um arquivo Bitmap, contendo uma cópia de uma janela do jogo naquele momento.
Parâmetros:
nomeArquivoBMP (entrada, passagem por referência*): indica o nome do arquivo Bitmap que será salvo. O valor do parâmetro deve conter a extensão ".bmp".
É utilizado o operador * apenas por se tratar de um parâmetro string. O valor do parâmetro não é alterado dentro da função.
idJanela (entrada, passagem por valor não-obrigatório): indica qual janela deve ter a imagem salva.
********************************/
void SalvaTela(char *nomeArquivoBMP,int idJanela=0){
    CGerenciadorJanelas::SaveScreenshotBMP(nomeArquivoBMP,idJanela);
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
    CGerenciadorControles::Encerra();
    CGerenciadorFontes::Encerra();
    CGerenciadorAnimacoes::Encerra();
    CGerenciadorParticulas::Encerra();
    CGerenciadorObjetos::Encerra();
    CGerenciadorTimers::Encerra();
    CGerenciadorVideos::Encerra();
    CGerenciadorSockets::Encerra();
    CGerenciadorForms::Encerra();
    if (jogo->cursorPadrao==0)
        CMouse::Encerra();
    CAssetLoader::Encerra();
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
indice (entrada, passagem por valor): informa um índice para este novo cursor. Se o índice já estiver sendo utilizado,
o cursor antigo é removido. O valor deve estar entre 0..MAX_CURSORES-1.
nomeArquivoCursor (entrada, passagem por referência*): indica o nome do arquivo de imagem que será utilziado como cursor do mouse.
É utilizado o operador * apenas por se tratar de um parâmetro string. O valor do parâmetro não é alterado dentro da função.
********************************/
void CarregaCursor(int indice,char *nomeArquivoCursor){
    CMouse::CarregaCursor(indice,nomeArquivoCursor);
}

/********************************
A função MudaCursor() é responsável por alterar o cursor atual do mouse por outro já carregado.
Parâmetro:
indice (entrada, passagem por valor): informa um índice para este novo cursor que já deve ter sido
carregado anteriormente e deve estar no intervalo 0..MAX_CURSORES-1.
********************************/
void MudaCursor(int indice){
    CMouse::MudaCursor(indice);
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
    return CGerenciadorJanelas::GetQtdJanelas();
}

/********************************
A função CriaJanela() é responsável por criar e exibir uma nova janela para a aplicação. O identificador numérico da nova janela é retornado como parâmetro.
Se não foi possível criar a janela, o valor de retorno será -1. Existe um limite máximo de janela que podem ser criadas. Esse limite é dado pelo parâmetro MAX_JANELAS configurado na Tipos_PIG.h.
O valor da janela original (padrão) é sempre igual a 0 (zero). Para se desenhar qualquer coisa nas janelas adicionais, é preciso criar objetos, animações, geradores de partículas e fontes
especificando-se a janela na qual estes elementos serão renderizados. Ao utilizar-se janelas adicionais, também é possível estipular individualmente quais janelas serão preparadas e mostradas, utilizando o
número da janela nas chamadas das funções IniciaDesenho e EncerraDesenho. Caso não seja especificado o número, todas as janelas são preparadas e mostradas, respectivamente.
Parâmetros:
nomeJanela (entrada, passagem por referência*): indica o nome que a nova janela mostrará no seu título.
É utilizado o operador * apenas por se tratar de um parâmetro string. O valor do parâmetro não é alterado dentro da função.
altura (entrada, passagem por valor não-obrigatório): indica a altura em pixels da janela a ser criada.
largura (entrada, passagem por valor não-obrigatório): indica a largura em pixels da janela a ser criada.
Retorno
inteiro que representa o número de identificação dessa janela. esse número deve ser utilizado sempre que um comando deva ser executado para uma janela específica.
A janela padrão da aplicação possui sempre o número 0 (zero).
********************************/
int CriaJanela(char *nomeJanela,int altura=ALT_TELA,int largura=LARG_TELA){
    return CGerenciadorJanelas::CriaJanela(nomeJanela,altura,largura);
}

/********************************
A função FechaJanela() é responsável por fechar uma janela. As renderizações nessa janela que ocorrerem posteriormente não terão qualquer efeito.
A janela fechada vai deixar de gerar eventos, mas não poderpa ser reaberta. O efeito de reabrir um janela pode ser obtido com os comandos EscondeJanela() e ExibeJanela().
Parâmetros:
idJanela (entrada, passagem por valor): indica o número da janela a ser fechada.
********************************/
void FechaJanela(int idJanela){
    CGerenciadorJanelas::FechaJanela(idJanela);
}

/********************************
A função EscondeJanela() é responsável por fazer a janela deixar de ser visível, mas não a fecha de forma definitiva.
A janela poderá ser reaberta com a função ExibeJanela().
Parâmetros:
idJanela (entrada, passagem por valor): indica o número da janela a ser oculta.
********************************/
void EscondeJanela(int idJanela){
    CGerenciadorJanelas::EscondeJanela(idJanela);
}

/********************************
A função ExibeJanela() é responsável por fazer a janela voltar a ser visível, mas não faz automaticamente a janela ter o foco para gerar eventos.
A janela poderá ser reaberta com foca por meio da função GanhaFocoJanela().
Parâmetros:
idJanela (entrada, passagem por valor): indica o número da janela a ser reexibida sem foco.
********************************/
void ExibeJanela(int idJanela){
    CGerenciadorJanelas::ExibeJanela(idJanela);
}

/********************************
A função GanhaFocoJanela() é responsável por fazer a janela voltar a ser visível e automaticamente voltar a ter o foco para gerar eventos.
Parâmetros:
idJanela (entrada, passagem por valor): indica o número da janela a ser reexibida com foco.
********************************/
void GanhaFocoJanela(int idJanela){
    CGerenciadorJanelas::GanhaFocoJanela(idJanela);
}

/********************************
A função GetAlturaJanela() é responsável por recuperar a altura da janela em pixels.
Parâmetros:
idJanela (entrada, passagem por valor não-obrigatório): indica o número da janela a ser consultada.
Retorno:
inteiro que representa a altura da janela em pixels.
********************************/
int GetAlturaJanela(int idJanela=0){
    return CGerenciadorJanelas::GetAltura(idJanela);
}

/********************************
A função GetLarguraJanela() é responsável por recuperar a largura da janela em pixels.
Parâmetros:
idJanela (entrada, passagem por valor não-obrigatório): indica o número da janela a ser consultada.
Retorno:
inteiro que representa a largura da janela em pixels.
********************************/
int GetLarguraJanela(int idJanela=0){
    return CGerenciadorJanelas::GetLargura(idJanela);
}

/********************************
A função SetTamanhoJanela() é responsável por definir o tamanho para a janela.
Parâmetros:
altura (entrada, passagem por valor): indica a quantidade de linhas da janela (em pixels).
largura (entrada, passagem por valor): indica a quantidade de colunas da janela (em pixels).
idJanela (entrada, passagem por valor não-obrigatório): indica o número da janela a ser alterada.
********************************/
void SetTamanhoJanela(int altura, int largura,int idJanela=0){
    CGerenciadorJanelas::SetTamanho(altura,largura,idJanela);
}

/********************************
A função GetTituloJanela() é responsável por recuperar o título (caption) atual da janela.
Parâmetros:
tituloJanela (saída, passagem por referência): armazena o título da janela que foi recuperado.
idJanela (entrada, passagem por valor não-obrigatório): indica o número da janela a ser consultada.
********************************/
void GetTituloJanela(char *tituloJanela,int idJanela=0){
    std::string resp = CGerenciadorJanelas::GetTitulo(idJanela);
    strcpy(tituloJanela,resp.c_str());
}

/********************************
A função SetTituloJanela() é responsável por definir um novo título (caption) para a janela.
Parâmetros:
novoTitulo (entrada, passagem por referência*): indica o novo título para a janela.
É utilizado o operador * apenas por se tratar de um parâmetro string. O valor do parâmetro não é alterada dentro da função.
idJanela (entrada, passagem por valor não-obrigatório): indica o número da janela a ser alterada.
********************************/
void SetTituloJanela(char *novoTitulo,int idJanela=0){
    CGerenciadorJanelas::SetTitulo(novoTitulo,idJanela);
}

/********************************
A função GetCorFundoJanela() é responsável por recuperar uma cor de fundo para a janela indicada. A cor de fundo será utilizada como background automático quando a janela for preparada para renderizações.
Parâmetros:
idJanela (entrada, passagem por valor não-obrigatório): indica o número da janela a ser alterada.
Retorno
cor contendo os componentes RGBA da cor utilizada para pintar automaticamente o fundo da janela.
********************************/
PIG_Cor GetCorFundoJanela(int idJanela=0){
    return CGerenciadorJanelas::GetCorFundo(idJanela);
}

/********************************
A função SetCorFundoJanela() é responsável por definir uma cor de fundo para a janela indicada. A cor de fundo será utilizada como background automático quando a janela for preparada para renderizações.
Parâmetros:
cor (entrada, passagem por valor): indica a cor para o fundo da janela.
idJanela (entrada, passagem por valor não-obrigatório): indica o número da janela a ser alterada.
********************************/
void SetCorFundoJanela(PIG_Cor cor,int idJanela=0){
    CGerenciadorJanelas::SetCorFundo(cor,idJanela);
}

/********************************
A função GetOpacidadeJanela() é responsável por recuperar o nível de opacidade de uma janela. A opacidade pode variar entre 1.0 (totalmente opaca) e 0 (totalmente transparente).
Parâmetros:
idJanela (entrada, passagem por valor não-obrigatório): indica o número da janela a ser alterada.
Retorno:
número real que indica o nível de opacidade da janela, variando entre 1.0 e 0.
********************************/
float GetOpacidadeJanela(int idJanela=0){
    return CGerenciadorJanelas::GetOpacidade(idJanela);
}

/********************************
A função SetOpacidadeJanela() é responsável por definir o nível de opacidade de uma janela. A opacidade pode variar entre 1.0 (totalmente opaca) e 0 (totalmente transparente).
Parâmetros:
nivelOpacidade (entrada, passagem por valor): indica o nível de opacidade da janela, variando entre 1.0 e 0.
idJanela (entrada, passagem por valor não-obrigatório): indica o número da janela a ser alterada.
********************************/
void SetOpacidadeJanela(float nivelOpacidade,int idJanela=0){
    CGerenciadorJanelas::SetOpacidade(nivelOpacidade,idJanela);
}

/********************************
A função SetPosicaoJanela() é responsável por definir a posição de um janela na tela correspondente. A tela normalmente utiliza um sistema de coordenadas, cujo ponto (0,0) é o canto superior esquerdo.
Parâmetros:
posicaoX (entrada, passagem por valor): indica o valor no eixo X (horizontal) da esquerda para direita.
posicaoY (entrada, passagem por valor): indica o valor no eixo Y (vertical), normalmente de cima para baixo.
idJanela (entrada, passagem por valor não-obrigatório): indica o número da janela a ser reposicionada.
********************************/
void SetPosicaoJanela(int posicaoX,int posicaoY,int idJanela=0){
    CGerenciadorJanelas::SetPosicao(posicaoX,posicaoY,idJanela);
}

/********************************
A função SetPosicaoJanela() é responsável por recuperar a posição de um janela na tela correspondente. A tela normalmente utiliza um sistema de coordenadas, cujo ponto (0,0) é o canto superior esquerdo.
Parâmetros:
posicaoX (saída, passagem por referência): indica o valor no eixo X (horizontal) da esquerda para direita.
posicaoY (saida, passagem por referência): indica o valor no eixo Y (vertical), normalmente de cima para baixo.
idJanela (entrada, passagem por valor não-obrigatório): indica o número da janela a ser reposicionada.
********************************/
void GetPosicaoJanela(int *posicaoX,int *posicaoY,int idJanela=0){
    CGerenciadorJanelas::GetPosicao(posicaoX,posicaoY,idJanela);
}

/********************************
A função SetBordaJanela() é responsável por definir se uma janela possuirá ou não bordas visíveis. O valor de 0 (zero) indica ausência de borda, enquanto valores diferentes de zero indicam presença de borda.
Parâmetros:
valor (entrada, passagem por valor): indica se a janela possui borda (valor diferente de zero) ou não (valor igual a zero).
idJanela (entrada, passagem por valor não-obrigatório): indica o número da janela a ser reposicionada.
********************************/
void SetBordaJanela(int valor,int idJanela=0){
    CGerenciadorJanelas::SetBorda(valor,idJanela);
}

/********************************
A função SetModoJanela() é responsável por definir o modo de exibição de uma janela. A janela pode ser exibida em três diferentes modos: JANELA_NORMAL, que é o modo padrão onde a janela ocupa o espaço da tela definido por sua altura e largura atual;
JANELA_TELACHEIA_DISPLAY, que é o modo no qual a janela fica em tela cheia com a resolução idêntica à da tela; JANELA_TELACHEIA, que é o modo onde a janela fica em tela cheia, mas com a resolução atual mantida.
A tela cheia não é acionada automaticamente com a combinção ALT+ENTER, é preciso executar o comando específico.
Parâmetros:
modo (entrada, passagem por valor): indica qual dos três modos (JANELA_NORMAL, JANELA_TELACHEIA, JANELA_TELACHEIA_DISPLAY) deve ser usado para exibir a janela.
idJanela (entrada, passagem por valor não-obrigatório): indica o número da janela a ser reposicionada.
********************************/
void SetModoJanela(int modo,int idJanela=0){
    CGerenciadorJanelas::SetModo(modo,idJanela);
}

/********************************
A função GetModoJanela() é responsável por recuperar o modo de exibição de uma janela. A janela pode ser exibida em três diferentes modos: JANELA_NORMAL, que é o modo padrão onde a janela ocupa o espaço da tela definido por sua altura e largura atual;
JANELA_TELACHEIA_DISPLAY, que é o modo no qual a janela fica em tela cheia com a resolução idêntica à da tela; JANELA_TELACHEIA, que é o modo onde a janela fica em tela cheia, mas com a resolução atual mantida.
A tela cheia não é acionada automaticamente com a combinção ALT+ENTER, é preciso executar o comando específico.
Parâmetros:
idJanela (entrada, passagem por valor não-obrigatório): indica o número da janela a ser reposicionada.
Retorno:
inteiro que indica qual dos três modos (JANELA_NORMAL, JANELA_TELACHEIA, JANELA_TELACHEIA_DISPLAY) está sendo usado para exibir a janela.
********************************/
int GetModoJanela(int idJanela=0){
    return CGerenciadorJanelas::GetModo(idJanela);
}


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
int BotaoPressionadoControle(int idControle,int botao){
    return CGerenciadorControles::BotaoPressionado(idControle,botao);
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
int EixoAcionadoControle(int idControle,int eixo){
    return CGerenciadorControles::EixoAcionado(idControle,eixo);
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
float EixoAcionadoPercentualControle(int idControle,int eixo){
    return CGerenciadorControles::EixoAcionadoPercentual(idControle,eixo);
}

/********************************
A função GetQtdEixosControle() é responsável por calcular quantos eixos e gatilhos estão disponíveis no controle.
Parâmetros:
idControle (entrada, passagem por valor): indica qual controle está sendo verificado.
retono:
inteiro que representa a quantidade de eixos e gatilhos.
********************************/
int GetQtdEixosControle(int idControle){
    return CGerenciadorControles::GetQtdEixos(idControle);
}

/********************************
A função GetQtdBotoesControle() é responsável por calcular quantos botões digitais (incluindo os direcionais) estão disponíveis no controle.
Parâmetros:
idControle (entrada, passagem por valor): indica qual controle está sendo verificado.
retono:
inteiro que representa a quantidade de botões digitais (incluindo os direcionais).
********************************/
int GetQtdBotoesControle(int idControle){
    return CGerenciadorControles::GetQtdBotoes(idControle);
}

/********************************
A função GetNomeControle() é responsável recuperar o nome com o qual o controle foi registrado no sistema.
Parâmetros:
idControle (entrada, passagem por valor): indica qual controle está sendo verificado.
nomeControle (saída, passagem por referência): armazena a string contendo o nome que foi recuperada para o controle.
********************************/
void GetNomeControle(int idControle,char *nomeControle){
    CGerenciadorControles::GetNome(idControle,nomeControle);
}


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
cor (entrada, passagem por valor): indica a cor no sistema RGB para o desenho da linha;
idJanela (entrada, passagem por valor não-obrigatório): indica o número da janela onde a linha será desenhada.
********************************/
void DesenhaLinhaSimples(int pontoX1,int pontoY1,int pontoX2,int pontoY2, PIG_Cor cor, int idJanela=0){
    CGerenciadorJanelas::DesenhaLinhaSimples(pontoX1,pontoY1,pontoX2,pontoY2,cor,idJanela);
}

/********************************
A função DesenhaLinhasDisjuntas() é responsável por desenhar linhas separadamente, ou seja, os ponto iniciais de cada linha estão nas posições pares e
os pontos finais estão nas posições ímpares. Assim, os vetores precisam ter tamanho qtd*2.
Parâmetros:
pontosX (entrada, passagem por referência): vetor de inteiros, de tamanho qtd*2, contendo os valores X (inicias e finais) de cada linha.
pontosY (entrada, passagem por referência): vetor de inteiros, de tamanho qtd*2, contendo os valores Y (inicias e finais) de cada linha.
qtd (entrada, passagem por valor): quantidade de linhas a serem desenhadas.
cor (entrada, passagem por valor): indica a cor no sistema RGB para o desenho das linhas;
idJanela (entrada, passagem por valor não-obrigatório): indica o número da janela onde as linhas serão desenhadas.
********************************/
void DesenhaLinhasDisjuntas(int *pontosX,int *pontosY,int qtd, PIG_Cor cor, int idJanela=0){
    CGerenciadorJanelas::DesenhaLinhasDisjuntas(pontosX,pontosY,qtd,cor,idJanela);
}

/********************************
A função DesenhaLinhasSequencia() é responsável por desenhar linhas em sequência, ou seja, o ponto final da primeira linha
corresponde ao ponto inicial da segunda linha.
Parâmetros:
pontosX (entrada, passagem por referência): vetor de inteiros, de tamanho qtd+1, contendo os valores X de cada linha da sequência.
pontosY (entrada, passagem por referência): vetor de inteiros, de tamanho qtd+1, contendo os valores Y de cada linha da sequência.
qtd (entrada, passagem por valor): quantidade de linhas a serem desenhadas.
cor (entrada, passagem por valor): indica a cor no sistema RGB para o desenho das linhas;
idJanela (entrada, passagem por valor não-obrigatório): indica o número da janela onde as linhas serão desenhadas.
********************************/
void DesenhaLinhasSequencia(int *pontosX,int *pontosY,int qtd, PIG_Cor cor, int idJanela=0){
    CGerenciadorJanelas::DesenhaLinhasSequencia(pontosX,pontosY,qtd,cor,idJanela);
}

/********************************
A função DesenhaRetangulo() é responsável por desenhar um retângulo com preenchimento sólido na tela em uma posição desejada pelo usuário.
O mesmo pode ser colocado em qualquer lugar do campo de visão da tela.
Parâmetros:
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usuário deseja colocar o retângulo.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usuário deseja colocar o retângulo.
altura (entrada, passagem por valor): Valor onde o usuário irá fornecer o número correspondente em pixels à altura desse retângulo.
largura (entrada, passagem por valor): Valor onde o usuário irá fornecer o número correspondente em pixels à largura desse retângulo.
cor (entrada, passagem por valor): indica a cor no sistema RGB para o desenho do retângulo;
idJanela (entrada, passagem por valor não-obrigatório): indica o número da janela onde o retângulo será desenhado.
********************************/
void DesenhaRetangulo(int posicaoX, int posicaoY, int altura, int largura, PIG_Cor cor, int idJanela=0){
    CGerenciadorJanelas::DesenhaRetangulo(posicaoX,posicaoY,altura,largura,cor,idJanela);
}

/********************************
A função DesenhaRetanguloVazado() é responsável por desenhar um retângulo sem preenchimento na tela em uma posição desejada pelo usuário.
O mesmo pode ser colocado em qualquer lugar do campo de visão da tela.
Parâmetros:
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usuário deseja colocar o retângulo.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usuário deseja colocar o retângulo.
altura (entrada, passagem por valor): Valor onde o usuário irá fornecer o número correspondente em pixels à altura desse retângulo.
largura (entrada, passagem por valor): Valor onde o usuário irá fornecer o número correspondente em pixels à largura desse retângulo.
cor (entrada, passagem por valor): indica a cor no sistema RGB para a borda do retângulo;
idJanela (entrada, passagem por valor não-obrigatório): indica o número da janela onde o retângulo será desenhado.
********************************/
void DesenhaRetanguloVazado(int posicaoX, int posicaoY, int altura, int largura, PIG_Cor cor, int idJanela=0){
    CGerenciadorJanelas::DesenhaRetanguloVazado(posicaoX,posicaoY,altura,largura,cor,idJanela);
}

/********************************
A função DesenhaPoligono() é responsável por desenhar na janela um polígono de preenchimento sólido com o número de lados indicados. Os dois primeiros parâmetros indicam as coordenadas
de cada um dos vértices do polígono.
AVISO: essa função utiliza o renderizador offscreen para gerar o polígono e posterior o renderiza na janela em questão; isto pode fazer o FPS da aplicação diminuir consideravelmente.
Parâmetros:
pontosX (entrada, passagem por referência): vetor de inteiros, de tamanho qtd, contendo as coordenadas X de cada vértice do polígono.
pontosY (entrada, passagem por referência): vetor de inteiros, de tamanho qtd, contendo as coordenadas Y de cada vértice do polígono.
qtd (entrada, passagem por valor): quantidade de lados do polígono.
cor (entrada, passagem por valor): indica a cor no sistema RGB para o desenho do polígono;
idJanela (entrada, passagem por valor não-obrigatório): indica o número da janela onde o polígono será desenhado.
********************************/
void DesenhaPoligono(int *pontosX,int *pontosY,int qtd, PIG_Cor cor, int idJanela=0){
    jogo->PintarPoligono(pontosX,pontosY,qtd,cor,idJanela);
}


/********************************
Seção de desenho Offscreen
********************************/

/********************************
A função PreparaOffScreenRenderer() serve para criar um novo bitmap offscreen que servirá de área
de desenho para outras funções que utilizem este bitmap.
Parâmetros:
altura (entrada, passagem por valor): indica a altura em pixels do novo bitmap.
largura (entrada, passagem por valor): indica a largura em pixels do novo bitmap.
********************************/
void PreparaOffScreenRenderer(int altura,int largura){
    jogo->PreparaOffScreenRenderer(altura,largura);
}

/********************************
A função SalvaOffScreenBMP() serve para efetivamente salvar a imagem offscreen como um arquivo do sistema operacional.
A imagem offscreen continuará existindo em memória e ações subsequentes ainda poderão ser feitas. Para "limpar" a imagem
deve-se utilizar a função PintaFundoOffScreen().
Parâmetros:
nomeArquivoBMP (entrada, passagem por referência*): indica com que nome a imagem offscreen será salva. O valor do parâmetro deve conter a extensão ".bmp".
É utilizado o operador * apenas por se tratar de um parâmetro string. O valor do parâmetro não é alterado dentro da função.
********************************/
void SalvaOffScreenBMP(char *nomeArquivoBMP){
    jogo->SalvaOffScreenBMP(nomeArquivoBMP);
}

/********************************
A função SalvaOffScreenPNG() serve para efetivamente salvar a imagem offscreen como um arquivo do sistema operacional.
A imagem offscreen continuará existindo em memória e ações subsequentes ainda poderão ser feitas. Para "limpar" a imagem
deve-se utilizar a função PintaFundoOffScreen().
Parâmetros:
nomeArquivoPNG (entrada, passagem por referência*): indica com que nome a imagem offscreen será salva. O valor do parâmetro deve conter a extensão ".png".
É utilizado o operador * apenas por se tratar de um parâmetro string. O valor do parâmetro não é alterado dentro da função.
********************************/
void SalvaOffScreenPNG(char *nomeArquivoPNG){
    jogo->SalvaOffScreenPNG(nomeArquivoPNG);
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
ponteiro (entrada, passagem por referência): ponteiro para qualquer tipo de estrutura a ser usada na função customizada de pintura da área.
********************************/
void PintaAreaOffScreen(int posicaoX,int posicaoY,PIG_Cor cor,void *ponteiro=NULL){
    jogo->PintaAreaOffScreen(posicaoX,posicaoY,cor,ponteiro);
}

/********************************
A função DefineFuncaoPintarAreaOffScreen() permite substituir a função padrão de pintura por outra função customizada que deve ser passada como parâmetro.
A função de pintura deve ser definida de forma que receba 4 parâmetros inteiros (respectivamente, a posição x e y do pixel que deve ser pintado e as
dimensões - altura e largura - da imagem offscreen) e 2 cores (a cor atual do pixel e a cor que deveria ser usada para pintá-lo). A função deve também retornar
o valor de uma cor, que será a cor efetivamente utilizada para pintar o pixel em questão. A função, portanto, deve definir para cada ponto solicitado qual a cor
final daquele ponto.
Parâmetros:
funcao (entrada, passagem por referência): nome da função customizada para pintar uma área no renderizador offscreen.
********************************/
void DefineFuncaoPintarAreaOffscreen(PIG_Cor (*funcao)(int,int,int,int,PIG_Cor,PIG_Cor)){
    jogo->DefineFuncaoPintarArea(funcao);
}

/********************************
A função MoveCanetaOffScreen() reposiciona a caneta do renderizador offscreen em algum outro ponto da imagem.
Parâmetros:
novoX (entrada, passagem por valor): nova posição no eixo X na qual a caneta será reposicionada. O tipo de parâmetro é double mas será convertido para int, dentro da função.
novoY (entrada, passagem por valor): nova posição no eixo Y na qual a caneta será reposicionada. O tipo de parâmetro é dpuble mas será convertido para int, dentro da função.
********************************/
void MoveCanetaOffscreen(double novoX,double novoY){
    jogo->MoveCanetaOffscreen(novoX,novoY);
}

/********************************
A função AvancaCanetaOffScreen() cria uma linha no renderizador offscreen na direção e sentido nos quais a canete está orientada.
Parâmetros:
distancia (entrada, passagem por valor): distância a ser percorrida pela caneta. O tipo de parâmetro é double para permitir que o cálculo da distância seja feito livremente.
********************************/
void AvancaCanetaOffscreen(double distancia){
    jogo->AvancaCanetaOffscreen(distancia);
}

/********************************
A função MudaCorCanetaOffScreen() modifica a cor a ser utilizada pela caneta do renderizador offscreen daqui por diante. Desenhos feitos anteriormente permancem com a cor com a qual foram feitos.
Parâmetros:
novaCor (entrada, passagem por valor): valor da nova cor a ser utilizada pela caneta do renderizador offscreen.
********************************/
void MudaCorCanetaOffscreen(PIG_Cor novaCor){
    jogo->MudaCorCanetaOffscreen(novaCor);
}

/********************************
A função GiraCanetaHorarioOffScreen() gira a caneta do renderizador offscreen. A caneta passa a ter uma nova direção e sentido. Se o comando AvancaCanetaOffscreen() for executado posteriormente,
esses novos valores de direção e sentido serão utilizados para que o ponto final do traço seja calculado.
Parâmetros:
angulo (entrada, passagem por valor): valor do ângulo (sentido horário, em radianos) pelo qual a caneta será redirecionada.
********************************/
void GiraCanetaHorarioOffscreen(double angulo){
    jogo->GiraCanetaHorarioOffscreen(angulo);
}

/********************************
A função GiraCanetaAntiHorarioOffScreen() gira a caneta do renderizador offscreen. A caneta passa a ter uma nova direção e sentido. Se o comando AvancaCanetaOffscreen() for executado posteriormente,
esses novos valores de direção e sentido serão utilizados para que o ponto final do traço seja calculado.
Parâmetros:
angulo (entrada, passagem por valor): valor do ângulo (sentido anti-horário, em radianos) pelo qual a caneta será redirecionada.
********************************/
void GiraCanetaAntiHorarioOffscreen(double angulo){
    jogo->GiraCanetaAntiHorarioOffscreen(angulo);
}

/********************************
A função GiraCanetaAnguloFixoOffScreen() gira a caneta do renderizador offscreen. A caneta passa a ter uma nova direção e sentido. Se o comando AvancaCanetaOffscreen() for executado posteriormente,
esses novos valores de direção e sentido serão utilizados para que o ponto final do traço seja calculado.
Parâmetros:
angulo (entrada, passagem por valor): valor do ângulo usando como referência o ângulo 0 do círculo trigonométrico.
********************************/
void GiraCanetaAnguloFixoOffscreen(double angulo){
    jogo->GiraCanetaAnguloFixoOffscreen(angulo);
}

/********************************
A função GetAnguloAtualOffScreen() recupera o ângulo atual que está sendo usado pela caneta do renderizador offscreen.
Retorno:
número real que representa o valor do ângulo atual, tendo como referência o ângulo 0 do círculo trigonométrico.
********************************/
double GetAnguloAtualOffscreen(){
    return jogo->GetAngAtual();
}

/********************************
A função GetXCanetaOffScreen() recupera a posição no eixo X na qual está posicionada atualmente a caneta do renderizador offscreen.
Retorno:
inteiro que representa a posição atual da caneta no eixo X.
********************************/
int GetXCanetaOffscreen(){
    return jogo->GetXCaneta();
}

/********************************
A função GetYCanetaOffScreen() recupera a posição no eixo Y na qual está posicionada atualmente a caneta do renderizador offscreen.
Retorno:
inteiro que representa a posição atual da caneta no eixo Y.
********************************/
int GetYCanetaOffscreen(){
    return jogo->GetYCaneta();
}

/********************************
A função PintaFundoOffScreen() serve para "limpar" o bitmap offscreen, mudando completamente para cor indicada.
Parâmetros:
cor (entrada, passagem por valor): indica a cor que deve ser usada durante a pintura completa do bitmap offscreen.
********************************/
void PintaFundoOffScreen(PIG_Cor cor){
    jogo->PintaFundoOffScreen(cor);
}

/********************************
A função DesenhaRetanguloOffScreen() é responsável por desenhar um retângulo cem preenchimento sólido no bitmap offscreen em uma posição desejada pelo usuário.
O sistema de coordenadas é o mesmo da tela, com o eixo Y aumentando para cima.
Parâmetros:
posicaoX (entrada, passagem por valor): Valor da coordenada X onde o usuário deseja colocar o retângulo.
posicaoY (entrada, passagem por valor): Valor da coordenada Y onde o usuário deseja colocar o retângulo.
altura (entrada, passagem por valor): Valor onde o usuário irá fornecer o número correspondente em pixels à altura desse retângulo.
largura (entrada, passagem por valor): Valor onde o usuário irá fornecer o número correspondente em pixels à largura desse retângulo.
cor (entrada, passagem por valor): indica a cor no sistema RGB para o preenchimento do retângulo;
********************************/
void DesenhaRetanguloOffScreen(int x1,int y1,int altura,int largura,PIG_Cor cor){
    jogo->DesenhaRetanguloOffScreen(x1,y1,altura,largura,cor);
}

/********************************
A função DesenhaRetanguloVazadoOffScreen() é responsável por desenhar um retângulo sem preenchimento no bitmap offscreen em uma posição desejada pelo usuário.
O sistema de coordenadas é o mesmo da tela, com o eixo Y aumentando para cima.
Parâmetros:
posicaoX (entrada, passagem por valor): Valor da coordenada X onde o usuário deseja colocar o retângulo.
posicaoY (entrada, passagem por valor): Valor da coordenada Y onde o usuário deseja colocar o retângulo.
altura (entrada, passagem por valor): Valor onde o usuário irá fornecer o número correspondente em pixels à altura desse retângulo.
largura (entrada, passagem por valor): Valor onde o usuário irá fornecer o número correspondente em pixels à largura desse retângulo.
cor (entrada, passagem por valor): indica a cor no sistema RGB para a borda do retângulo;
********************************/
void DesenhaRetanguloVazadoOffScreen(int x1,int y1,int altura,int largura,PIG_Cor cor){
    jogo->DesenhaRetanguloVazadoOffScreen(x1,y1,altura,largura,cor);
}

/********************************
A função DesenhaLinhasSimplesOffScreen() é responsável por desenhar no bitmap offscreen uma única linha, cuja início é o ponto (x1,y1) e o fim é o ponto (x2,y2).
Parâmetros:
pontoX1 (entrada, passagem por valor): inteiro que indica o início da linha no eixo X.
pontoY1 (entrada, passagem por valor): inteiro que indica o início da linha no eixo Y.
pontoX2 (entrada, passagem por valor): inteiro que indica o fim da linha no eixo X.
pontoY2 (entrada, passagem por valor): inteiro que indica o fim da linha no eixo Y.
cor (entrada, passagem por valor): indica a cor no sistema RGB para o desenho das linhas;
********************************/
void DesenhaLinhaSimplesOffScreen(int x1,int y1,int x2,int y2,PIG_Cor cor){
    jogo->DesenhaLinhaOffScreen(x1,y1,x2,y2,cor);
}


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
estilo (entrada, passagem por valor): representa o estilo da fonte. Pode ser uma combinação binária de: ESTILO_NEGRITO, para negrito; ESTILO_SUBLINHADO, para sublinhado; ESTILO_ITALICO, para itálico;
ESTILO_CORTADO, para uma linha horizontal à meia-altura. Caso nenhum estilo seja desejado, pode ser omitido ou usado ESTILO_NORMAL.
idJanela (entrada, passagem por valor não-obrigatório): indica qual janela vai receber a fonte. Uma fonte só pode ser usada na janela na qual foi criada.
retono:
inteiro que representa a ideintificação única da fonte. Futuras referência a esta fonte devem idenitificá-las pelo número.
********************************/
int CriaFonteNormal(char *nome,int tamanho,PIG_Cor corLetra,int contorno,PIG_Cor corContorno,PIG_Estilo estilo=ESTILO_NORMAL,int idJanela=0){
    return CGerenciadorFontes::CriaFonteNormal(nome,tamanho,estilo,corLetra,contorno,corContorno,idJanela);
}

/********************************
A função CriaFonteNormal() é responsável por disponibilizar uma nova fonte com preenchimento sólido.
Parâmetros:
nome (entrada, passagem por referência): nome do arquivo que contém a fonte (normalmente com extensão ttf).
tamanho (entrada, passagem por valor): tamanho da fonte, que normalmente representa a altura média (em pixels) dos caracteres da fonte.
corLetra (entrada, passagem por valor): representa a cor de preenchimento da fonte. Caso a cor não seja informada, será utilizada a cor padrão (BRANCO).
estilo (entrada, passagem por valor): representa o estilo da fonte. Pode ser uma combinação binária de: ESTILO_NEGRITO, para negrito; ESTILO_SUBLINHADO, para sublinhado; ESTILO_ITALICO, para itálico;
ESTILO_CORTADO, para uma linha horizontal à meia-altura. Caso nenhum estilo seja desejado, pode ser omitido ou usado ESTILO_NORMAL.
idJanela (entrada, passagem por valor não-obrigatório): indica qual janela vai receber a fonte. Uma fonte só pode ser usada na janela na qual foi criada.
retono:
inteiro que representa a ideintificação única da fonte. Futuras referência a esta fonte devem idenitificá-las pelo número.
********************************/
int CriaFonteNormal(char *nome,int tamanho,PIG_Cor corLetra=PIG_FONTE_PADRAO_COR,PIG_Estilo estilo=ESTILO_NORMAL,int idJanela=0){
    return CGerenciadorFontes::CriaFonteNormal(nome,tamanho,estilo,corLetra,idJanela);
}

/********************************
A função CriaFonteDinamica() é responsável por disponibilizar uma nova fonte dinâmica com preenchimento sólido. As fontes dinâmicas são capazes
de escrever strings com diferentes formatações (negrito, itálico, sublinhado, cortado) e cores nas letras. A string a ser utilizada pela fonte
pode conter ou não os marcadores de formtação. Caso não contenham, será utilizada uma letra branca, sem formatação.
Parâmetros:
nome (entrada, passagem por referência): nome do arquivo que contém a fonte (normalmente com extensão ttf).
tamanho (entrada, passagem por valor): tamanho da fonte, que normalmente representa a altura média (em pixels) dos caracteres da fonte.
idJanela (entrada, passagem por valor não-obrigatório): indica qual janela vai receber a fonte. Uma fonte só pode ser usada na janela na qual foi criada.
retono:
inteiro que representa a ideintificação única da fonte. Futuras referência a esta fonte devem idenitificá-las pelo número.
********************************/
int CriaFonteDinamica(char *nome,int tamanho,int idJanela=0){
    return CGerenciadorFontes::CriaFonteDinamica(nome,tamanho,idJanela);
}

/********************************
A função CriaFonteFundo() é responsável por disponibilizar uma nova fonte com preenchimento de um bitmap específico.
Parâmetros:
nome (entrada, passagem por referência): nome do arquivo que contém a fonte (normalmente com extensão ttf).
tamanho (entrada, passagem por valor): tamanho da fonte, que normalmente representa a altura média (em pixels) dos caracteres da fonte.
arquivoFundo (entrada, passagem por referência): indica o nome do arquivo de imagem que servirá de fundo para a fonte.
contorno (entrada, passagem por valor): representa a espessura do contorno que fonte terá. Caso não seja desejado um contorno, basta utilizar um valor 0.
corContorno (entrada, passagem por valor): representa a cor do contorno da fonte.
estilo (entrada, passagem por valor): representa o estilo da fonte. Pode ser uma combinação binária de: ESTILO_NEGRITO, para negrito; ESTILO_SUBLINHADO, para sublinhado; ESTILO_ITALICO, para itálico;
ESTILO_CORTADO, para uma linha horizontal à meia-altura. Caso nenhum estilo seja desejado, pode ser omitido ou usado ESTILO_NORMAL.
idJanela (entrada, passagem por valor não-obrigatório): indica qual janela vai receber a fonte. Uma fonte só pode ser usada na janela na qual foi criada.
retono:
inteiro que representa a ideintificação única da fonte. Futuras referência a esta fonte devem idenitificá-las pelo número.
********************************/
int CriaFonteFundo(char *nome,int tamanho,char *arquivoFundo,int contorno,PIG_Cor corContorno,PIG_Estilo estilo=ESTILO_NORMAL,int idJanela=0){
    return CGerenciadorFontes::CriaFonteFundo(nome,tamanho,estilo,arquivoFundo,contorno,corContorno,idJanela);
}

/********************************
A função CriaFonteFundo() é responsável por disponibilizar uma nova fonte com preenchimento de um bitmap específico.
Parâmetros:
nome (entrada, passagem por referência): nome do arquivo que contém a fonte (normalmente com extensão ttf).
tamanho (entrada, passagem por valor): tamanho da fonte, que normalmente representa a altura média (em pixels) dos caracteres da fonte.
arquivoFundo (entrada, passagem por referência): indica o nome do arquivo de imagem que servirá de fundo para a fonte.
estilo (entrada, passagem por valor): representa o estilo da fonte. Pode ser uma combinação binária de: ESTILO_NEGRITO, para negrito; ESTILO_SUBLINHADO, para sublinhado; ESTILO_ITALICO, para itálico;
ESTILO_CORTADO, para uma linha horizontal à meia-altura. Caso nenhum estilo seja desejado, pode ser omitido ou usado ESTILO_NORMAL.
idJanela (entrada, passagem por valor não-obrigatório): indica qual janela vai receber a fonte. Uma fonte só pode ser usada na janela na qual foi criada.
retono:
inteiro que representa a ideintificação única da fonte. Futuras referência a esta fonte devem idenitificá-las pelo número.
********************************/
int CriaFonteFundo(char *nome,int tamanho,char *arquivoFundo,PIG_Estilo estilo=ESTILO_NORMAL,int idJanela=0){
    return CGerenciadorFontes::CriaFonteFundo(nome,tamanho,estilo,arquivoFundo,idJanela);
}

/********************************
A função CalculaLarguraPixels() é responsável por realizar a soma das larguras de cada letra da string informada.
Parâmetros:
str (entrada, passagem por referência): string a ser escrita na tela.
numFonte (entrada, passagem por valor): número da fonte a ser utilizada. Caso o usuário não deseje uma fonte especial, será utilizada a fonte padrão (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
retorno:
inteiro que representa o total de pixels (no eixo x) necessários para escrever a string.
********************************/
int CalculaLarguraPixels(char *str,int numFonte=0){
    return CGerenciadorFontes::GetLarguraPixels(str,numFonte);
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
void EscreverDireita(char *str,int posicaoX,int posicaoY,PIG_Cor cor=BRANCO,int numFonte=0,float angulo=0){
    CGerenciadorFontes::EscreverString(str,posicaoX,posicaoY,numFonte,cor,CPIG_TEXTO_DIREITA,angulo);
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
void EscreverEsquerda(char *str,int posicaoX,int posicaoY,PIG_Cor cor=BRANCO,int numFonte=0,float angulo=0){
    CGerenciadorFontes::EscreverString(str,posicaoX,posicaoY,numFonte,cor,CPIG_TEXTO_ESQUERDA,angulo);
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
void EscreverCentralizada(char *str,int posicaoX,int posicaoY,PIG_Cor cor=BRANCO,int numFonte=0,float angulo=0){
    CGerenciadorFontes::EscreverString(str,posicaoX,posicaoY,numFonte,cor,CPIG_TEXTO_CENTRO,angulo);
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
void EscreverLongaEsquerda(char *str,int posicaoX,int posicaoY,int largMax,int espacoEntreLinhas,PIG_Cor cor=BRANCO,int numFonte=0,float angulo=0){
    CGerenciadorFontes::EscreverLonga(str,posicaoX,posicaoY,largMax,espacoEntreLinhas,numFonte,cor,CPIG_TEXTO_ESQUERDA,angulo);
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
void EscreverLongaDireita(char *str,int posicaoX,int posicaoY,int largMax,int espacoEntreLinhas,PIG_Cor cor=BRANCO,int numFonte=0,float angulo=0){
    CGerenciadorFontes::EscreverLonga(str,posicaoX,posicaoY,largMax,espacoEntreLinhas,numFonte,cor,CPIG_TEXTO_DIREITA,angulo);
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
void EscreverLongaCentralizada(char *str,int posicaoX,int posicaoY,int largMax,int espacoEntreLinhas,PIG_Cor cor=BRANCO,int numFonte=0,float angulo=0){
    CGerenciadorFontes::EscreverLonga(str,posicaoX,posicaoY,largMax,espacoEntreLinhas,numFonte,cor,CPIG_TEXTO_CENTRO,angulo);
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
void EscreveInteiroEsquerda(int valor, int x, int y,PIG_Cor cor=BRANCO, int numFonte=0,float angulo=0){
    CGerenciadorFontes::EscreverInteiro(valor,x,y,numFonte,cor,CPIG_TEXTO_ESQUERDA,angulo);
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
void EscreveInteiroDireita(int valor, int x, int y,PIG_Cor cor=BRANCO, int numFonte=0,float angulo=0){
    CGerenciadorFontes::EscreverInteiro(valor,x,y,numFonte,cor,CPIG_TEXTO_DIREITA,angulo);
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
void EscreveInteiroCentralizado(int valor, int x, int y,PIG_Cor cor=BRANCO, int numFonte=0,float angulo=0){
    CGerenciadorFontes::EscreverInteiro(valor,x,y,numFonte,cor,CPIG_TEXTO_CENTRO,angulo);
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
void EscreveDoubleEsquerda(double valor, int casas, int x, int y,PIG_Cor cor=BRANCO, int numFonte=0,float angulo=0){
    CGerenciadorFontes::EscreverReal(valor,x,y,numFonte,casas,cor,CPIG_TEXTO_ESQUERDA,angulo);
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
void EscreveDoubleDireita(double valor, int casas, int x, int y,PIG_Cor cor=BRANCO, int numFonte=0,float angulo=0){
    CGerenciadorFontes::EscreverReal(valor,x,y,numFonte,casas,cor,CPIG_TEXTO_DIREITA,angulo);
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
void EscreveDoubleCentralizado(double valor, int casas, int x, int y,PIG_Cor cor=BRANCO, int numFonte=0,float angulo=0){
    CGerenciadorFontes::EscreverReal(valor,x,y,numFonte,casas,cor,CPIG_TEXTO_CENTRO,angulo);
}

/********************************
A função GetMetricas() recupera as principais métricas de uma letra em um estilo específico.
As métricas incluem as posições mínimas e máximas nos eixos X e Y, onde a letra é desenhada.
Se a fonte não for dinâmica, qualquer valor de estilo passado será descartado e será utilizado o estilo indicado na criação da fonte.
Parâmetros:
letra (entrada, passagem por valor): caractere cuja largura será calculada.
estilo (entrada, passagem por valor): estilo desejado no cálculo da largura. O valor só será utilizado em fontes dinâmicas. Em fontes não-dinâmicas, o valor de estilo será o mesmo do informado na criação da fonte.
numFonte (entrada, passagem por valor): número da fonte a ser utilizada. Caso o usuário não deseje uma fonte especial, será utilizada a fonte padrão (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
retorno:
struct que representa as métricas principais ao escrever a letra.
********************************/
PIG_Metricas_Fonte GetMetricas(char letra, PIG_Estilo estilo=ESTILO_NORMAL,int numFonte=0){
    return CGerenciadorFontes::GetMetricas(letra,numFonte,estilo);
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
int GetLarguraLetra(char letra,PIG_Estilo estilo=ESTILO_NORMAL,int numFonte = 0){
    return CGerenciadorFontes::GetLarguraLetra(letra,numFonte,estilo);
}

/********************************
A função GetTamanhoBaseFonte() é responsável por recuperar o tamanho da fonte informado na criação da mesma.
Parâmetros:
numFonte (entrada, passagem por valor): número da fonte a ser utilizada. Caso o usuário não deseje uma fonte especial, será utilizada a fonte padrão (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
retorno:
inteiro que representa o tamanho base da fonte, ou seja, a quantidade de pixels no eixo Y para desenhar qualquer caractere da fonte (exceto vogais maiúsuclas acentuadas: Á, É, Í, Ó, Ú.
********************************/
int GetTamanhoBaseFonte(int numFonte = 0){
    return CGerenciadorFontes::GetTamanhoBaseFonte(numFonte);
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
    return CGerenciadorFontes::GetFonteDescent(numFonte);
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
    return CGerenciadorFontes::GetFonteAscent(numFonte);
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
    return CGerenciadorFontes::GetLineSkip(numFonte);
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
void SubstituiCaractere(char caractere, char *nomeArquivo, int largNova, int x, int y, int altura,int largura,int numFonte=0){
    CGerenciadorFontes::SubstituiCaracter(caractere,nomeArquivo,largNova,x,y,altura,largura,numFonte);
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
opacidade (entrada,passagem por valor): nível de opacidade do objeto na faixa 0-255. O valor padrão é 255, indicando nível máximo de opacidade.
idJanela (entrada, passagem por valor não-obrigatório): indica qual janela vai receber o objeto.
Retorno:
inteiro que representa o identificador único do objeto. Todas as operações subsequentes com este objeto deverão receber este identificador como parâmetro.
********************************/
int CriaObjeto(char* nomeArquivo,PIG_Cor *corFundo=NULL,int retiraFundo=1, int idJanela=0){
    return CGerenciadorObjetos::CriaObjeto(nomeArquivo,corFundo,retiraFundo,idJanela);
}

/********************************
A função CriaObjetoOffScreen() é responsável por criar um objeto a partir da imagem que está sendo montanda pelo
renderizador Offscreen. O renderizador precisa ter sido preparado anteriormente.
Parâmetros:
retiraFundo (entrada, passagem por valor): inteiro que indica se o fundo da imagem deve ser retirado ou não ao ler o arquivo em questão. O valor padrão é 1, indicando que o fundo deve ser retirado.
opacidade (entrada,passagem por valor): nível de opacidade do objeto na faixa 0-255. O valor padrão é 255, indicando nível máximo de opacidade.
Retorno:
inteiro que representa o identificador único do objeto. Todas as operações subsequentes com este objeto deverão receber este identificador como parâmetro.
********************************/
int CriaObjetoOffScreen(PIG_Cor *corFundo=NULL,int retiraFundo=1){
    return CGerenciadorObjetos::CriaObjetoOffScreen(jogo->offRenderer,corFundo,retiraFundo);
}


/********************************
A função DestroiObjeto() é responsável por eliminar o objeto em questão do jogo.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto a ser excluído.
********************************/
void DestroiObjeto(int idObjeto){
    CGerenciadorObjetos::DestroiObjeto(idObjeto);
}

/********************************
A função SetValorIntObjeto() é responsável incorporar a um objeto um atributo inteiro.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por valor): relaciona um número inteiro ao atributo.
valor (entrada, passagem por valor): valor do atributo inteiro a ser associado ao objeto.
********************************/
void SetValorIntObjeto(int idObjeto,int indice,int valor){
    CGerenciadorObjetos::SetValorIntObjeto(idObjeto,indice,valor);
}

/********************************
A função SetValorFloatObjeto() é responsável incorporar a um objeto um atributo float.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por valor): relaciona um número inteiro ao atributo.
valor (entrada, passagem por valor): valor do atributo float a ser associado ao objeto.
********************************/
void SetValorFloatObjeto(int idObjeto,int indice,float valor){
    CGerenciadorObjetos::SetValorFloatObjeto(idObjeto,indice,valor);
}

/********************************
A função SetValorIntObjeto() é responsável incorporar a um objeto um atributo inteiro.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por valor): relaciona um número inteiro ao atributo.
valor (entrada, passagem por referência): valor do atributo string a ser associado ao objeto.
********************************/
void SetValorStringObjeto(int idObjeto,int indice,char *valor){
    CGerenciadorObjetos::SetValorStringObjeto(idObjeto,indice,valor);
}

/********************************
A função SetValorIntObjeto() é responsável incorporar a um objeto um atributo inteiro.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por referência): relaciona uma string ao atributo.
valor (entrada, passagem por valor): valor do atributo inteiro a ser associado ao objeto.
********************************/
void SetValorIntObjeto(int idObjeto,char *indice,int valor){
    CGerenciadorObjetos::SetValorIntObjeto(idObjeto,indice,valor);
}

/********************************
A função SetValorFloatObjeto() é responsável incorporar a um objeto um atributo float.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por referência): relaciona uma string ao atributo.
valor (entrada, passagem por valor): valor do atributo float a ser associado ao objeto.
********************************/
void SetValorFloatObjeto(int idObjeto,char *indice,float valor){
    CGerenciadorObjetos::SetValorFloatObjeto(idObjeto,indice,valor);
}

/********************************
A função SetValorIntObjeto() é responsável incorporar a um objeto um atributo inteiro.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por referência): relaciona uma string ao atributo.
valor (entrada, passagem por referência): valor do atributo string a ser associado ao objeto.
********************************/
void SetValorStringObjeto(int idObjeto,char *indice,char *valor){
    CGerenciadorObjetos::SetValorStringObjeto(idObjeto,indice,valor);
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
int GetValorIntObjeto(int idObjeto,int indice,int *valor){
    return CGerenciadorObjetos::GetValorIntObjeto(idObjeto,indice,valor);
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
int GetValorFloatObjeto(int idObjeto,int indice,float *valor){
    return CGerenciadorObjetos::GetValorFloatObjeto(idObjeto,indice,valor);
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
int GetValorStringObjeto(int idObjeto,int indice,char *valor){
    return CGerenciadorObjetos::GetValorStringObjeto(idObjeto,indice,valor);
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
int GetValorIntObjeto(int idObjeto,char *indice,int *valor){
    return CGerenciadorObjetos::GetValorIntObjeto(idObjeto,indice,valor);
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
int GetValorFloatObjeto(int idObjeto,char *indice,float *valor){
    return CGerenciadorObjetos::GetValorFloatObjeto(idObjeto,indice,valor);
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
int GetValorStringObjeto(int idObjeto,char *indice,char *valor){
    return CGerenciadorObjetos::GetValorStringObjeto(idObjeto,indice,valor);
}

/********************************
A função GetXYObjeto() é responsável recuperar o valor da posição (X,Y) do objeto de acordo com o sistema de coordenadas do jogo.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
posicaoX (saída, passagem por referencia): indica a posicao no eixo X do objeto.
posicaoY (saída, passagem por referencia): indica a posicao no eixo Y do objeto.
********************************/
void GetXYObjeto(int idObjeto,int *posicaoX,int *posicaoY){
    CGerenciadorObjetos::GetPosicaoXY(idObjeto,posicaoX,posicaoY);
}

/********************************
A função MoveObjeto() é responsável por movimentar um determinado objeto para uma nova posição informada.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto a ser movido.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usuário deseja reposicionar o objeto.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usuário deseja reposicionar o objeto.
********************************/
void MoveObjeto(int idObjeto,int posicaoX,int posicaoY){
    CGerenciadorObjetos::Move(idObjeto,posicaoX,posicaoY);
}

/********************************
A função DeslocaObjeto() é responsável por deslocar um determinado objeto em relação à sua posição atual.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto a ser movido.
deltaX (entrada, passagem por valor): valor a ser somado ou subtraído na componente X da posição do objeto.
deltaY (entrada, passagem por valor): valor a ser somado ou subtraído na componente Y da posição do objeto.
********************************/
void DeslocaObjeto(int idObjeto,int deltaX,int deltaY){
    CGerenciadorObjetos::Desloca(idObjeto,deltaX,deltaY);
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
    CGerenciadorObjetos::SetAngulo(idObjeto,angulo);
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
    return CGerenciadorObjetos::GetAngulo(idObjeto);
}

/********************************
A função SetPivoObjeto() define um ponto (X,Y) em relação ao ponto (0,0) do objeto, sobre o qual o objeto será
rotacionado quando a função SetAnguloObjeto() for executada.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
posicaoX (entrada, passagem por valor): Valor da coordenada X do pivô em relação ao ponto (0,0) do objeto.
posicaoY (entrada, passagem por valor): Valor da coordenada Y do pivô em relação ao ponto (0,0) do objeto.
********************************/
void SetPivoObjeto(int idObjeto,int posicaoX,int posicaoY){
    CGerenciadorObjetos::SetPivo(idObjeto,posicaoX,posicaoY);
}

/********************************
A função SetPivoObjeto() define um ponto relativo (X,Y) em relação ao ponto (0,0) e ao tamanho do objeto, sobre o qual o objeto será
rotacionado quando a função SetAnguloObjeto() for executada.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
relX (entrada, passagem por valor): porcentagem da largura do objeto onde ficará o pivô.
relY (entrada, passagem por valor): porcentagem da altura do objeto onde ficará o pivô.
********************************/
void SetPivoObjeto(int idObjeto,float relX,float relY){
    CGerenciadorObjetos::SetPivo(idObjeto,relX,relY);
}

/********************************
A função GetPivoObjeto() define um ponto (X,Y) em relação ao ponto (0,0) do objeto, sobre o qual o objeto será
rotacionado quando a função SetAnguloObjeto() for executada.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
posicaoX (saída, passagem por referência): Valor da coordenada X do pivô em relação ao ponto (0,0) do objeto.
posicaoY (saída, passagem por referência): Valor da coordenada Y do pivô em relação ao ponto (0,0) do objeto.
********************************/
void GetPivoObjeto(int idObjeto,int *posicaoX,int *posicaoY){
    CGerenciadorObjetos::GetPivo(idObjeto,posicaoX,posicaoY);
}

/********************************
A função SetFlipObjeto() é responsável por virar o objeto, invertendo-o em alguma direção. O objeto somente será
desenhado na nova orientação no próximo comando DesenhaObjeto().
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto a ser virado.
valor (entrada, passagem por valor): valor do tipo de Flip. Pode ser FLIP_NENHUM (nenhum tipo de inversão),
FLIP_HORIZONTAL (inverte da esquerda para a direita), FLIP_VERTICAL (inverte de cima para baixo),
ou FLIP_HORIZ_VERT (inverte da esquerda para direita e de cima para baixo).
********************************/
void SetFlipObjeto(int idObjeto,PIG_Flip valor){
    CGerenciadorObjetos::SetFlip(idObjeto,valor);
}

/********************************
A função GetFlipObjeto() é responsável por recuperar o valor da manipulação causada pela função SetFlipObjeto().
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto a ser virado.
Retorno:
inteiro que indica o tipo de Flip. Pode ser FLIP_NENHUM (nenhum tipo de inversão),
FLIP_HORIZONTAL (inverte da esquerda para a direita), FLIP_VERTICAL (inverte de cima para baixo),
ou FLIP_HORIZ_VERT (inverte da esquerda para direita e de cima para baixo).
********************************/
PIG_Flip GetFlipObjeto(int idObjeto){
    return CGerenciadorObjetos::GetFlip(idObjeto);
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
    CGerenciadorObjetos::SetDimensoes(idObjeto,altura,largura);
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
    CGerenciadorObjetos::GetDimensoes(idObjeto,altura,largura);
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
    CGerenciadorObjetos::GetDimensoesOriginais(idObjeto,altura,largura);
}

/********************************
A função DefineFrameObjeto() é responsável por delimitar o posicionamento dos pixels do arquivo de imagem que serão
utilizados para representar o objeto na tela. Desta forma, nem toda a imagem será automaticamente utilizada para
representar o objeto. O sistema de coordenadas deve ser o padrão dos arquivos de imagem, com o eixo Y aumentando para baixo.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto a ser desenhado.
xBitmap (entrada, passagem por valor): indica a posição de eixo X onde começa o frame.
yBitmap (entrada, passagem por valor): indica a posição de eixo Y onde começa o frame. Neste caso, o eixo Y aumenta para baixo.
altura (entrada, passagem por valor): altura em pixels do frame.
largura (entrada, passagem por valor): largura em pixels do frame.
********************************/
void DefineFrameObjeto(int idObjeto, int xBitmap, int yBitmap, int altura, int largura){
    CGerenciadorObjetos::CriaFrame(idObjeto,xBitmap,yBitmap,altura,largura);
}

/********************************
A função SetColoracaoObjeto() é responsável por mesclar uma determinada cor com os pixels do arquivo de imagem.
Após a modificação, todos os desenhos deste objeto serão mostrados já com a mesclagem definida.
Para voltar ao padrão original de pixels, deve-se chamar a função, passando a cor branca (255,255,255).
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto a ser desenhado.
cor (entrada,passagem por valor): cor do sistema RGB utilizada para mesclagem com o arquivo de imagem
********************************/
void SetColoracaoObjeto(int idObjeto, PIG_Cor cor){
    CGerenciadorObjetos::SetColoracao(idObjeto,cor);
}

/********************************
A função SetOpacidadeObjeto() é responsável por modificar o nível de opacidade do objeto.
O nível de opacidade varia de 0-255, sendo 0 totalmente transparente e 255 totalmente opaco.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
valor (entrada,passagem por valor): nível de opacidade do objeto na faixa 0-255.
********************************/
void SetOpacidadeObjeto(int idObjeto,int valor){
    CGerenciadorObjetos::SetOpacidade(idObjeto,valor);
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
    return CGerenciadorObjetos::GetOpacidade(idObjeto);
}

/********************************
A função DesenhaObjeto() é responsável por desenhar um objeto na tela ou no Renderizador Offscreen. O objeto será desenhado de acordo com todas as definições
de posição e ângulo informado até o momento. Além disso, se o objeto estiver virado (flipping), isso também será levado em consideração.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto a ser desenhado.
offScreen (entrada, passagem por valor): indica se o objeto deve ser desenhado no Renderizador Offscreen.
********************************/
void DesenhaObjeto(int idObjeto,int offScreen=0){
    if (offScreen==0)
    CGerenciadorObjetos::Desenha(idObjeto,NULL);
    else CGerenciadorObjetos::Desenha(idObjeto,jogo->offRenderer);
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
//int TestaColisaoObjetos(int idObjeto1,int idObjeto2){
//    return CGerenciadorObjetos::TestaColisao(idObjeto1,idObjeto2)&&CGerenciadorObjetos::TestaColisao(idObjeto2,idObjeto1);
//}

int TestaColisaoObjetos(int idObjeto1,int idObjeto2){
    if (CGerenciadorObjetos::TestaColisao(idObjeto1, idObjeto2))
        return true;//CGerenciadorObjetos::TestaColisaoPoligono(idObjeto1, idObjeto1);
    return false;
}

void DefineAreaColisao(int id_objeto, int* x, int* y, int quantidadePontos) {
    CGerenciadorObjetos::DefineAreaColisao(id_objeto, x, y, quantidadePontos);
}


/********************************
A função GetPixelsObjeto() é responsável por extrair os pixels da imagem que originou o objeto, devolvendo-os como
uma matriz de pixels (PIG_Cor). Mudanças nessa matriz só serão validadas após a chamada da função AtualizaPixelsObjeto().
O linha 0 corresponde à primeira linha da imagem, ou seja, à linha superior, pois o sistema de coordenadas
das imagens tem o eixo Y aumentando para baixo.
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
Retorno:
matriz de pixels (PIG_Cor) da imagem que gerou o objeto. O total de linhas da matriz é dado pela altura original do objeto e o
total de colunas é dado pela largura original do objeto. Ambos os valores podem ser obtidos pela função GetDimensoesOriginaisObjeto().
********************************/
PIG_Cor **GetPixelsObjeto(int idObjeto){
    return CGerenciadorObjetos::GetPixels(idObjeto);
}

/********************************
A função AtualizaPixelsObjeto() é responsável por efetivar quaisquer mudanças nos pixels do objeto obtidos pela função GetPixelsObjeto().
Parâmetros:
idObjeto (entrada, passagem por valor): identificador do objeto.
retiraFundo (entrada, passagem por valor): inteiro que indica se o fundo da imagem deve ser retirado ou não ao ler o arquivo em questão. O valor padrão é 1, indicando que o fundo deve ser retirado.
********************************/
void AtualizaPixelsObjeto(int idObjeto,int retiraFundo=1){
    CGerenciadorObjetos::AtualizaPixels(idObjeto,retiraFundo);
}

/********************************
Seção de gerador de partículas
********************************/

/********************************
A função CriaGeradorParticulas() cria um novo gerador de partículas (GDP). As partículas em si precisam ser criadas
posteriormente através da função CriaParticula(), passando o identificador do GDP como parâmetro.
Parâmetros:
maxParticulas (entrada, passagem por valor): informa o maior número de partículas que o gerador terá simultaneamente. O maior valor aceito é 1000 partículas.
nomeArquivo (entrada, passagem por referência): indica o caminho relativo ou absoluto do arquivo de imagem,
que será utilizado para cada partícula do GDP.
audioCriacao (entrada, passagem por valor não-obrigatório): indica qual audio previamente criado deve ser tocado quando uma partícula for efetivamente criada.
audioEncerramento (entrada, passagem por valor não-obrigatório): indica qual audio previamente criado deve ser tocado quando uma partícula for destruida por acabar o tempo de vida ou por sair da área de ativação.
idJanela (entrada, passagem por valor não-obrigatório): indica qual janela vai receber o GDP.
********************************/
int CriaGeradorParticulas(int maxParticulas,char* nomeArquivo,int audioCriacao=-1,int audioEncerramento=-1,int idJanela=0){
    return CGerenciadorParticulas::CriaGeradorParticulas(maxParticulas,nomeArquivo,audioCriacao,audioEncerramento,idJanela);
}

/********************************
A função CriaGeradorParticulasPorAnimacao() cria um novo gerador de partículas (GDP). As partículas em si precisam ser criadas
posteriormente através da função CriaParticula(), passando o identificador do GDP como parâmetro. As partículas serão semelhantes a uma animação já criada anteriormente
que é indicada pelo parâmetro idAnimação.
Parâmetros:
maxParticulas (entrada, passagem por valor): informa o maior número de partículas que o gerador terá simultaneamente. O maior valor aceito é 1000 partículas.
idAnimacao (entrada, passagem por referência): identificador da animação (já criada anteriormente) que será utilizada
para cada partícula do GDP.
audioCriacao (entrada, passagem por valor não-obrigatório): indica qual audio previamente criado deve ser tocado quando uma partícula for efetivamente criada.
audioEncerramento (entrada, passagem por valor não-obrigatório): indica qual audio previamente criado deve ser tocado quando uma partícula for destruida por acabar o tempo de vida ou por sair da área de ativação.
idJanela (entrada, passagem por valor não-obrigatório): indica qual janela vai receber o GDP.
********************************/
int CriaGeradorParticulasPorAnimacao(int maxParticulas,int idAnimacao,int audioCriacao=-1,int audioEncerramento=-1,int idJanela=0){
    return CGerenciadorParticulas::CriaGeradorParticulas(maxParticulas,CGerenciadorAnimacoes::GetAnimacao(idAnimacao),audioCriacao,audioEncerramento,idJanela);
}

/********************************
A função CriaGeradorParticulasPorObjeto() cria um novo gerador de partículas (GDP). As partículas em si precisam ser criadas
posteriormente através da função CriaParticula(), passando o identificador do GDP como parâmetro. As partículas serão semelhantes a um objeto já criado anteriormente
que é indicado pelo parâmetro idObjeto.
Parâmetros:
maxParticulas (entrada, passagem por valor): informa o maior número de partículas que o gerador terá simultaneamente. O maior valor aceito é 1000 partículas.
idObjeto (entrada, passagem por referência): identificador do objeto (já criado anteriormente) que será utilizado
para cada partícula do GDP.
audioCriacao (entrada, passagem por valor não-obrigatório): indica qual audio previamente criado deve ser tocado quando uma partícula for efetivamente criada.
audioEncerramento (entrada, passagem por valor não-obrigatório): indica qual audio previamente criado deve ser tocado quando uma partícula for destruida por acabar o tempo de vida ou por sair da área de ativação.
idJanela (entrada, passagem por valor não-obrigatório): indica qual janela vai receber o GDP.
********************************/
int CriaGeradorParticulasPorObjeto(int maxParticulas,int idObjeto,int audioCriacao=-1,int audioEncerramento=-1,int idJanela=0){
    return CGerenciadorParticulas::CriaGeradorParticulas(maxParticulas,CGerenciadorObjetos::GetObjeto(idObjeto),audioCriacao,audioEncerramento,idJanela);
}

/********************************
A função DestroiGeradorParticulas() encerra um gerador de partículas (GDP). Todas as partículas relacionadas a ele também são finalizadas
neste momento.
Parâmetros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da função CriaGeradorParticulas().
********************************/
void DestroiGeradorParticulas(int idGerador){
    CGerenciadorParticulas::DestroiGeradorParticulas(idGerador);
}

/********************************
A função MoveGeradorParticulas() reposiciona um gerador de partículas (GDP). Na prática, isto significa que as novas partículas que
forem criadas posteriormente terão esse ponto de origem.
Parâmetros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da função CriaGeradorParticulas().
posicaoX (entrada, passagem por valor): informa a nova posição X do GDP, em relação ao sistema de coordenadas do jogo.
posicaoY (entrada, passagem por valor): informa a nova posição Y do GDP, em relação ao sistema de coordenadas do jogo.
********************************/
void MoveGeradorParticulas(int idGerador,int posicaoX,int posicaoY){
    CGerenciadorParticulas::Move(idGerador,posicaoX,posicaoY);
}

/********************************
A função DeslocaGeradorParticulas() é responsável por deslocar uma determinado gerador de partículas (GDP) em relação à sua posição atual.
Parâmetros:
idGerador (entrada, passagem por valor): identificador do GDP a ser deslocada.
deltaX (entrada, passagem por valor): valor a ser somado ou subtraído na componente X da posição do GDP.
deltaY (entrada, passagem por valor): valor a ser somado ou subtraído na componente Y da posição do GDP.
********************************/
void DeslocaGeradorParticulas(int idGerador,int deltaX,int deltaY){
    CGerenciadorParticulas::Desloca(idGerador,deltaX,deltaY);
}

/********************************
A função MudaDirecaoParticulas() modifica a direção na qual as partículas se movimentarão após serem criadas.
Somente as partículas criadas posteriormente seguirão a direção especificada.
Parâmetros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da função CriaGeradorParticulas().
valorX (entrada, passagem por valor): informa a componente X da direção a ser definida para as partículas.
valorY (entrada, passagem por valor): informa a componente Y da direção a ser definida para as partículas.
********************************/
void MudaDirecaoParticulas(int idGerador,int valorX,int valorY){
    CGerenciadorParticulas::MudaDirecaoParticulas(idGerador,valorX,valorY);
}

/********************************
A função MudaRotacaoParticulas() modifica a velocidade angular das partículas após serem criadas.
Somente as partículas criadas posteriormente seguirão a velocidade angular especificada.
Parâmetros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da função CriaGeradorParticulas().
angPerSec (entrada, passagem por valor): informa a velocidade em graus por segundo.
********************************/
void MudaRotacaoParticulas(int idGerador,float grausPerSec){
    CGerenciadorParticulas::MudaRotacaoParticulas(idGerador,grausPerSec);
}

/********************************
A função MudaCorParticulas() é responsável por mesclar uma determinada cor com os pixels do arquivo de imagem da partícula.
Após a modificação, todos os desenhos desta partícula serão mostrados já com a mesclagem definida.
Para voltar ao padrão original de pixels, deve-se chamar a função, passando a cor branca (255,255,255).
Parâmetros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da função CriaGeradorParticulas().
cor (entrada,passagem por valor): cor do sistema RGB utilizada para mesclagem com o arquivo de imagem da partícula.
********************************/
void MudaCorParticulas(int idGerador,PIG_Cor cor){
    CGerenciadorParticulas::MudaCorParticulas(idGerador,cor);
}

/********************************
A função MudaEscalaParticulas() modifica o tamanho das partículas após serem criadas, durante o seu tempo de vida.
Somente as partículas criadas posteriormente seguirão a velocidade angular especificada.
Parâmetros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da função CriaGeradorParticulas().
escalaInicial (entrada, passagem por valor): informa a escala da partícula ao ser criada.
escalaFinal (entrada, passagem por valor): informa a escala da partícula ao final do seu tempo de vida.
********************************/
void MudaEscalaParticulas(int idGerador,float escalaInicial,float escalaFinal){
    CGerenciadorParticulas::MudaEscalaParticulas(idGerador,escalaInicial,escalaFinal);
}

/********************************
A função SetPivoParticulas() determina o ponto a ser considerado como pivo da partícula.
Somente as partículas criadas posteriormente seguirão a velocidade angular especificada.
Parâmetros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da função CriaGeradorParticulas().
posicaoX (entrada, passagem por valor): Valor da coordenada X do pivô em relação ao ponto (0,0) da partícula.
posicaoY (entrada, passagem por valor): Valor da coordenada Y do pivô em relação ao ponto (0,0) da partícula.
********************************/
void SetPivoParticulas(int idGerador,int posicaoX,int posicaoY){
    CGerenciadorParticulas::MudaEscalaParticulas(idGerador,posicaoX,posicaoY);
}

/********************************
A função CriaParticula() adiciona uma nova partícula ao jogo relacionada com o GDP passado como parâmetro.
Parâmetros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da função CriaGeradorParticulas().
fadingOut (entrada, passagem por valor): valor lógico que indica se a partícula deve esmaecer ao longo do tempo.
minX (entrada, passagem por valor): valor mínimo de X para que a partícula seja considerada ativa
minY (entrada, passagem por valor): valor mínimo de Y para que a partícula seja considerada ativa
maxX (entrada, passagem por valor): valor máximo de X para que a partícula seja considerada ativa
maxY (entrada, passagem por valor): valor máximo de Y para que a partícula seja considerada ativa
maxTempo (entrada, passagem por valor): tempo de vida da partícula
Retorno:
inteiro indicando se a partícula foi criada (valor maior ou igual a zero) ou não (valor menor do que zero).
A partícula não será criada se já houver o número máximo de partículas ativas.
********************************/
int CriaParticula(int idGerador,int fadingOut=0,int minX=-50,int minY=-50,int maxX=LARG_TELA+50,int maxY=ALT_TELA+50,float maxTempo=999999.9){
    return CGerenciadorParticulas::CriaParticula(idGerador,fadingOut,minX,minY,maxX,maxY,maxTempo);
}

/********************************
A função MoveParticulas() faz com que todas as partícula ativas do GDP em questão se movimentem de acordo com as componentes
X e Y passadas na função MudaDirecaoParticulas(). As partículas que saírem da tela de jogo ou aqueles que já existerm a mais de 10000 segundos
serão consideradas inativas e deixarão de existir.
Parâmetros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da função CriaGeradorParticulas().
********************************/
void MoveParticulas(int idGerador){
    CGerenciadorParticulas::MoveParticulas(idGerador);
}

/********************************
A função QuantidadeParticulasAtivas() indica quantas partículas do GDP em questão ainda estão ativas. As partículas deixam de
ser ativas quando saem da tela do jogo, quando colidem com algum objeto ou depois de 10000 segundos de vida.
Parâmetros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da função CriaGeradorParticulas().
Retorno:
inteiro que indica o número de partículas ativas.
********************************/
int QuantidadeParticulasAtivas(int idGerador){
    return CGerenciadorParticulas::GetQtdAtivas(idGerador);
}

/********************************
A função DesenhaParticulas() desenha todas as partículas ativas do GDP na posição que estiverem.
Parâmetros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da função CriaGeradorParticulas().
********************************/
void DesenhaParticulas(int idGerador){
    CGerenciadorParticulas::Desenha(idGerador);
}

/********************************
A função ColisaoParticulasObjeto() indica se houve colisão de alguma partícula ativa do GDP com um outro objeto específico, através do seu identificador.
Parâmetros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da função CriaGeradorParticulas().
idObjeto (entrada, passagem por valor): identificador do objeto que pode ter colidido com as partículas do GDP.
Retorno:
inteiro que indica se houve colisão de alguma partícula ativa do GDP (valor diferente de zero) ou não (valor igual a 0, zero).
********************************/
int ColisaoParticulasObjeto(int idGerador,int idObjeto){
    Objeto obj = CGerenciadorObjetos::GetObjeto(idObjeto);
    return CGerenciadorParticulas::Colisao(idGerador,obj);
}

/********************************
A função ColisaoParticulasAnimacao() indica se houve colisão de alguma partícula ativa do GDP com uma outra animção específica, através do seu identificador.
Parâmetros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da função CriaGeradorParticulas().
idAnimacao (entrada, passagem por valor): identificador da animação que pode ter colidido com as partículas do GDP.
Retorno:
inteiro que indica se houve colisão de alguma partícula ativa do GDP (valor diferente de zero) ou não (valor igual a 0, zero).
********************************/
int ColisaoParticulasAnimacao(int idGerador,int idAnimacao){
    Animacao anima = CGerenciadorAnimacoes::GetAnimacao(idAnimacao);
    return CGerenciadorParticulas::Colisao(idGerador,anima);
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
    return CGerenciadorTimers::CriaTimer(congelado);
}

/********************************
A função TempoDecorrido() é responsável por informar o tempo decorrido desde a criação do timer
até a hora em que a função for chamada.
Parâmetros:
idTimer (entrada, passagem por valor): identificador do timer.
Retorno:
número real indicando o tempo (em segundos) desde a criação do timer.
********************************/
float TempoDecorrido(int idTimer){
    return CGerenciadorTimers::GetTempoDecorrido(idTimer);
}

/********************************
A função PausaTimer() é responsável por realizar uma pausa na contagem do tempo de um timer. Após a despausa,
o timer continuará a contar o tempo normalmente.
Parâmetros:
idTimer (entrada, passagem por valor): identificador do timer.
********************************/
void PausaTimer(int idTimer){
    CGerenciadorTimers::PausaTimer(idTimer);
}

/********************************
A função PausaTudo() é responsável por realizar uma pausa na contagem do tempo de todos os timers
criados pela função CriaTimer();
********************************/
void PausaTudo(){
    CGerenciadorTimers::PausaTodos();
}

/********************************
A função DespausaTimer() é responsável por retomar a contagem do tempo de um timer após uma pausa.
Parâmetros:
idTimer (entrada, passagem por valor): identificador do timer.
********************************/
void DespausaTimer(int idTimer){
    CGerenciadorTimers::DespausaTimer(idTimer);
}

/********************************
A função DespausaTudo() é responsável por retomar a contagem do tempo de todos os timers
criados pela função CriaTimer();
********************************/
void DespausaTudo(){
    CGerenciadorTimers::DespausaTodos();
}

/********************************
A função ReiniciaTimer() é responsável por zerar a contagem do tempo de um timer, idependente do tempo já decorrido.
Na prática, é equivalente a encerrer um temporizador e recriá-lo em seguida.
Parâmetros:
idTimer (entrada, passagem por valor): identificador do timer.
congelado (entrada, passagem por valor): valor lógico que indica se o timer deve ser reiniciado sem iniciar de imediato a contagem de tempo ou não.
********************************/
void ReiniciaTimer(int idTimer, int congelado=false){
    CGerenciadorTimers::ReiniciaTimer(idTimer,congelado);
}

/********************************
A função DestroiTimer() é responsável por encerrar a utilização de timer.
Seu identificador não poderá ser utilizado após a função ser executada.
Parâmetros:
idTimer (entrada, passagem por valor): identificador do timer.
********************************/
void DestroiTimer(int idTimer){
    CGerenciadorTimers::DestroiTimer(idTimer);
}

/********************************
Seção das animações
********************************/

/********************************
A função CriaAnimacao() é responsável por criar uma animacao. A animação pode ser considerada um tipo especial
de objeto, capaz de mudar de figura (sprite) dentro de um tempo determinado. Uma sequência completa de
sprites é chamada de modo. Uma mesma animção pode apresentar vários modos diferentes.
Para que a animação funcione corretamente, será necessário: definir cada frame (pedaço do arquivo bitmap que contém o sprite desejado),
criar um ou mais modos, inserir os frames criados no modo correspondente e dizer qual modo deverá ser exibido inicialmente.
Tudo isso pode ser feito por outras funções que manipulam as animações.
Parâmetros:
nomeArquivo (entrada, passagem por referência): string que informa o nome do arquivo da imagem (spritesheet) da animação.
retiraFundo (entrada, passagem por valor): inteiro que indica se o fundo da imagem deve ser retirado ou não ao ler o arquivo em questão. O valor padrão é 1, indicando que o fundo deve ser retirado.
opacidade (entrada,passagem por valor): nível de opacidade do objeto na faixa 0-255. O valor padrão é 255, indicando nível máximo de opacidade.
idJanela (entrada, passagem por valor não-obrigatório): indica qual janela vai receber a animação.
Retorno:
inteiro que representa o identificador único da animação. Todas as operações subsequentes com esta animação deverão receber este identificador como parâmetro.
********************************/
int CriaAnimacao(char* nomeArquivo,PIG_Cor *corFundo=NULL,int retiraFundo=1,int idJanela=0){
    return CGerenciadorAnimacoes::CriaAnimacao(nomeArquivo,corFundo,retiraFundo,idJanela);
}

/********************************
A função CriaAnimacao() é responsável por criar uma animacao. A animação pode ser considerada um tipo especial
de objeto, capaz de mudar de figura (sprite) dentro de um tempo determinado. Uma sequência completa de
sprites é chamada de modo. Uma mesma animção pode apresentar vários modos diferentes.
Esta forma de criar uma animação, copia todos os frames e modos de outra animação já existente, evitando assim
que toda esta preparação precise ser feita novamente. O usuário deve ter cuidado de não destruir a animação
original enquanto as cópias estiverem ativas ou haverá erros de execução. Da mesma forma, não se deve alterar os
frames ou os modos da cópia, pois pode provocar erros na animação original.
Parâmetros:
idAnimacao (entrada, passagem por valor): indica o identificador da animação original que será copiada.
Retorno:
inteiro que representa o identificador único da animação. Todas as operações subsequentes com esta animação deverão receber este identificador como parâmetro.
********************************/
int CriaAnimacao(int idAnimacao){
    return CGerenciadorAnimacoes::CriaAnimacao(idAnimacao);
}

/********************************
A função DestroiAnimacao() é responsável por eliminar a animação em questão do jogo.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação a ser excluída.
********************************/
void DestroiAnimacao(int idAnimacao){
    CGerenciadorAnimacoes::DestroiAnimacao(idAnimacao);
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
void CriaFrameAnimacao(int idAnimacao,int codigoFrame,int xBitmap,int yBitmap,int altura,int largura){
    CGerenciadorAnimacoes::CriaFrame(idAnimacao,codigoFrame,xBitmap,yBitmap,altura,largura);
}

/********************************
A função CriaModoAnimacao() é responsável por criar um modo, ou seja, uma sequência de sprites.
Após a criação do modo, os frames deve ser inseridos um a um. O modo pode ser criado antes dos frames
e vice-versa, mas os frames só podem ser associados ao modo, após as respectivas criações.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação a ter um novo modo.
codigoModo (entrada, passagem por valor): numero do modo a ser criado. Pode ser usado qualquer número de 0..MAX_MODOS-1.
loop (entrada, passagem por valor): valor lógico que indica se este modo deve recomeçar do primeiro frame após a execução do último.
********************************/
void CriaModoAnimacao(int idAnimacao,int codigoModo,int loop){
    CGerenciadorAnimacoes::CriaModo(idAnimacao,codigoModo,loop);
}

/********************************
A função InsereFrameAnimacao() é responsável por associar os frames aos modos correspondentes. Um mesmo
frame pode fazer parte de diversos modos, mas cada modo deve ter no máximo MAX_FRAMES_MODO-1 frames.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação em questão.
codigoModo (entrada, passagem por valor): numero do modo a ter um frame inserido.
codigoFrame (entrada, passagem por valor): numero do frame a ser inserido no modo.
tempo (entrada, passagem por valor): duração (em segundos) da exibição automática do frame neste modo específico.
idAudio (entrada, passagem por valor não-obrigatório): identificador do audio (já criado anteriormente) que deve ser tocado quando o frame for exibido. O valor -1 deve ser utilizado se nenhum audio deve ser tocado.
********************************/
void InsereFrameAnimacao(int idAnimacao,int codigoModo, int codigoFrame, float tempo, int idAudio=-1){
    CGerenciadorAnimacoes::InsereFrame(idAnimacao,codigoModo,codigoFrame,tempo,idAudio);
}

/********************************
A função MudaModoAnimacao() é responsável por alterar a animação para um outro modo.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação em questão.
codigoModo (entrada, passagem por valor): numero do novo modo.
indiceFrame (entrada, passagem por valor): indica a partir de qual frame o modo deve ser exibido. O valor 0 significa aprtir do primeiro frame.
forcado (entrada, passagem por valor): valor lógico que indica se a mudança de modo deve ser feita forçosamente ou não. Se não for forçada, a mudança só ocorrerá se o modo atual já tiver terminado de ser animado.
********************************/
void MudaModoAnimacao(int idAnimacao,int codigoModo,int indiceFrame,int forcado=1){
    CGerenciadorAnimacoes::MudaModo(idAnimacao,codigoModo,indiceFrame,forcado);
}

/********************************
A função ColisaoAnimacoes() indica se houve colisão entre duas animações, de forma semelhante aos objetos.
Parâmetros:
idAnimacao1 (entrada, passagem por valor): identificador da primeira animação.
idAnimacao2 (entrada, passagem por valor): identificador da segunda animação.
Retorno:
inteiro que indica se houve colisão entre as animações.
********************************/
int ColisaoAnimacoes(int idAnimacao1,int idAnimacao2){
    return CGerenciadorAnimacoes::ColisaoAnimacoes(idAnimacao1,idAnimacao2);
}

/********************************
A função ColisaoAnimacaoObjeto() indica se houve colisão de alguma animacao com algum outro objeto específico, através do seu identificador.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação que pode ter colidido com o objeto.
idObjeto (entrada, passagem por valor): identificador do objeto que pode ter colidido com a animação.
Retorno:
inteiro que indica se houve colisão da animação com o objeto.
********************************/
int ColisaoAnimacaoObjeto(int idAnimacao,int idObjeto){
    Objeto obj = CGerenciadorObjetos::GetObjeto(idObjeto);
    return CGerenciadorAnimacoes::ColisaoObjeto(idAnimacao,obj);
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
    return CGerenciadorAnimacoes::Desenha(idAnimacao);
}

/********************************
A função MoveAnimacao() é responsável por movimentar uma determinada animação para uma nova posição informada.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação a ser movida.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usuário deseja reposicionar a animação.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usuário deseja reposicionar a animação.
********************************/
void MoveAnimacao(int idAnimacao,int x,int y){
    CGerenciadorAnimacoes::Move(idAnimacao,x,y);
}

/********************************
A função DeslocaAnimcao() é responsável por deslocar uma determinada animacao em relação à sua posição atual.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animacao a ser deslocada.
deltaX (entrada, passagem por valor): valor a ser somado ou subtraído na componente X da posição da animação.
deltaY (entrada, passagem por valor): valor a ser somado ou subtraído na componente Y da posição da animação.
********************************/
void DeslocaAnimacao(int idAnimacao,int deltaX,int deltaY){
    CGerenciadorAnimacoes::Desloca(idAnimacao,deltaX,deltaY);
}

/********************************
A função SetOpacidadeAnimacao() é responsável por modificar o nível de opacidade da animação.
O nível de opacidade varia de 0-255, sendo 0 totalmente transparente e 255 totalmente opaco.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação.
valor (entrada,passagem por valor): nível de opacidade da animação na faixa 0-255.
********************************/
void SetOpacidadeAnimacao(int idAnimacao,int valor){
    CGerenciadorAnimacoes::SetOpacidade(idAnimacao,valor);
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
    return CGerenciadorAnimacoes::GetOpacidade(idAnimacao);
}


/********************************
A função SetColoracaoAnimacao() é responsável por mesclar uma determinada cor com os pixels do arquivo de imagem.
Após a modificação, todos os desenhos desta animação serão mostrados já com a mesclagem definida.
Para voltar ao padrão original de pixels, deve-se chamar a função, passando a cor branca (255,255,255).
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação a ser desenhado.
cor (entrada,passagem por valor): cor do sistema RGB utilizada para mesclagem com o arquivo de imagem
********************************/
void SetColoracaoAnimacao(int idAnimacao,PIG_Cor cor){
    CGerenciadorAnimacoes::SetColoracao(idAnimacao,cor);
}

/********************************
A função SetFlipAnimacao() é responsável por virar a animação, invertendo-a em alguma direção. A animação somente será
desenhada na nova orientação no próximo comando DesenhaAnimacao().
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação a ser virada.
valor (entrada, passagem por valor): valor do tipo de Flip. Pode ser FLIP_NENHUM (nenhum tipo de inversão),
FLIP_HORIZONTAL (inverte da esquerda para a direita), FLIP_VERTICAL (inverte de cima para baixo),
ou FLIP_HORIZ_VERT (inverte da esquerda para direita e de cima para baixo).
********************************/
void SetFlipAnimacao(int idAnimacao,PIG_Flip valor){
    CGerenciadorAnimacoes::SetFlip(idAnimacao,valor);
}

/********************************
A função GetFlipAnimacao() é responsável por recuperar o valor da manipulação causada pela função SetFlipAnimacao().
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação a ser virada.
Retorno:
inteiro que indica o tipo de Flip. Pode ser FLIP_NENHUM (nenhum tipo de inversão),
FLIP_HORIZONTAL (inverte da esquerda para a direita), FLIP_VERTICAL (inverte de cima para baixo),
ou FLIP_HORIZ_VERT (inverte da esquerda para direita e de cima para baixo).
********************************/
PIG_Flip GetFlipAnimacao(int idAnimacao){
    return CGerenciadorAnimacoes::GetFlip(idAnimacao);
}

/********************************
A função SetAnguloAnimacao() é responsável pela angulação de determinada animacao. A angulação é calculada em sentido
horário a partir do eixo X (0 graus). A animação será desenhada com a angulação informada no próximo comando
DesenhaAnimcao(). A detecção de colisão não funciona com animações fora da angulação padrão (0 graus).
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação.
angulo (entrada, passagem por valor): valor para indicar a angulação da animação em graus.
********************************/
void SetAnguloAnimacao(int idAnimacao, float angulo){
    CGerenciadorAnimacoes::SetAngulo(idAnimacao,angulo);
}

/********************************
A função GetAnguloAnimacao() é responsável por recuperar o ângulo de rotação de determinada animação. A angulação é calculada em sentido
horário a partir do eixo X (0 graus). A animação será desenhada com a angulação informada no próximo comando
DesenhaAnimacao(). A detecção de colisão não funciona com animações fora da angulação padrão (0 graus).
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação.
Retorno:
Retorna o valor do ângulo em graus.
********************************/
float GetAnguloAnimacao(int idAnimacao){
    return CGerenciadorAnimacoes::GetAngulo(idAnimacao);
}

/********************************
A função SetPivoAnimacao() define um ponto (X,Y) em relação ao ponto (0,0) da animação, sobre o qual a animação será
rotacionado quando a função SetAnguloAnimacao() for executada.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação.
posicaoX (entrada, passagem por valor): Valor da coordenada X do pivô em relação ao ponto (0,0) da animação.
posicaoY (entrada, passagem por valor): Valor da coordenada Y do pivô em relação ao ponto (0,0) da animação.
********************************/
void SetPivoAnimacao(int idAnimacao,int posicaoX,int posicaoY){
    CGerenciadorAnimacoes::SetPivo(idAnimacao,posicaoX,posicaoY);
}

/********************************
A função GetPivoAnimacao() define um ponto (X,Y) em relação ao ponto (0,0) da animacao, sobre o qual a animação será
rotacionado quando a função SetAnguloAnimacao() for executada.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação.
posicaoX (saída, passagem por referência): Valor da coordenada X do pivô em relação ao ponto (0,0) da animação.
posicaoY (saída, passagem por referência): Valor da coordenada Y do pivô em relação ao ponto (0,0) da animação.
********************************/
void GetPivoAnimacao(int idAnimacao,int *posicaoX,int *posicaoY){
    CGerenciadorAnimacoes::GetPivo(idAnimacao,posicaoX,posicaoY);
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
    CGerenciadorAnimacoes::SetDimensoes(idAnimacao,altura,largura);
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
    CGerenciadorAnimacoes::GetDimensoes(idAnimacao,altura,largura);
}

/********************************
A função SetValorIntAnimacao() é responsável incorporar a uma animação um atributo inteiro.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação.
indice (entrada, passagem por valor): relaciona um número inteiro ao atributo.
valor (entrada, passagem por valor): valor do atributo inteiro a ser associado à animação.
********************************/
void SetValorIntAnimacao(int idAnimacao,int indice,int valor){
    CGerenciadorAnimacoes::SetValorIntAnimacao(idAnimacao,indice,valor);
}

/********************************
A função SetValorFloatAnimacao() é responsável incorporar a uma animação um atributo float.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação.
indice (entrada, passagem por valor): relaciona um número inteiro ao atributo.
valor (entrada, passagem por valor): valor do atributo float a ser associado à animação.
********************************/
void SetValorFloatAnimacao(int idAnimacao,int indice,float valor){
    CGerenciadorAnimacoes::SetValorFloatAnimacao(idAnimacao,indice,valor);
}

/********************************
A função SetValorIntAnimacao() é responsável incorporar a uma animação um atributo inteiro.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação.
indice (entrada, passagem por valor): relaciona um número inteiro ao atributo.
valor (entrada, passagem por referência): valor do atributo string a ser associado à animação.
********************************/
void SetValorStringAnimacao(int idAnimacao,int indice,char *valor){
    CGerenciadorAnimacoes::SetValorStringAnimacao(idAnimacao,indice,valor);
}

/********************************
A função SetValorIntAnimacao() é responsável incorporar a uma animação um atributo inteiro.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação.
indice (entrada, passagem por referência): relaciona uma string ao atributo.
valor (entrada, passagem por valor): valor do atributo inteiro a ser associado à animação.
********************************/
void SetValorIntAnimacao(int idAnimacao,char *indice,int valor){
    CGerenciadorAnimacoes::SetValorIntAnimacao(idAnimacao,indice,valor);
}

/********************************
A função SetValorFloatAnimacao() é responsável incorporar a uma animação um atributo float.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação.
indice (entrada, passagem por referência): relaciona uma string ao atributo.
valor (entrada, passagem por valor): valor do atributo float a ser associado à animação.
********************************/
void SetValorFloatAnimacao(int idAnimacao,char *indice,float valor){
    CGerenciadorAnimacoes::SetValorFloatAnimacao(idAnimacao,indice,valor);
}

/********************************
A função SetValorIntAnimacao() é responsável incorporar a uma animação um atributo inteiro.
Parâmetros:
idAnimacao (entrada, passagem por valor): identificador da animação.
indice (entrada, passagem por referência): relaciona uma string ao atributo.
valor (entrada, passagem por referência): valor do atributo string a ser associado à animação.
********************************/
void SetValorStringAnimacao(int idAnimacao,char *indice,char *valor){
    CGerenciadorAnimacoes::SetValorStringAnimacao(idAnimacao,indice,valor);
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
int GetValorIntAnimacao(int idAnimacao,int indice,int *valor){
    return CGerenciadorAnimacoes::GetValorIntAnimacao(idAnimacao,indice,valor);
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
int GetValorFloatAnimacao(int idAnimacao,int indice,float *valor){
    return CGerenciadorAnimacoes::GetValorFloatAnimacao(idAnimacao,indice,valor);
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
int GetValorStringAnimacao(int idAnimacao,int indice,char *valor){
    std::string str;
    bool resp = CGerenciadorAnimacoes::GetValorStringAnimacao(idAnimacao,indice,str);
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
int GetValorIntAnimacao(int idAnimacao,char *indice,int *valor){
    return CGerenciadorAnimacoes::GetValorIntAnimacao(idAnimacao,indice,valor);
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
int GetValorFloatAnimacao(int idAnimacao,char *indice,float *valor){
    return CGerenciadorAnimacoes::GetValorFloatAnimacao(idAnimacao,indice,valor);
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
int GetValorStringAnimacao(int idAnimacao,char *indice,char *valor){
    std::string str;
    bool resp = CGerenciadorAnimacoes::GetValorStringAnimacao(idAnimacao,indice,str);
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
void GetXYAnimacao(int idAnimacao,int *posicaoX,int *posicaoY){
    return CGerenciadorAnimacoes::GetPosicaoXY(idAnimacao,posicaoX,posicaoY);
}


/********************************
Seção dos áudios
********************************/

/********************************
A função CriaAudio() é responsável por ler e preparar um arquivo de audio.
Os formatos permitidos são WAVE, AIFF, RIFF, OGG, VOC.
Parâmetros:
nomeArquivo (entrada, passagem por referência): string que informa o nome do arquivo de áudio.
nLoops (entrada, passagem por valor): indica o número de repetições do áudio. O valor 0 indica que será tocado apenas uma vez. O valor -1 indica que o audio deve ser tocado indefinidamente.
tempoExecucao (entrada, passage por valor): indica uma quantidade de milissegundos do arquivo de audio que dem ser tocados. O valor de -1 indica que todo o arquivo deve ser tocado.
Retorno:
Retorna o identificador do audio para ser utilizado por outras funções.
********************************/
int CriaAudio(char *nomeArquivo,int nLoops,int tempoExecucao=-1){
    return CGerenciadorAudios::CriaAudio(nomeArquivo,nLoops,tempoExecucao);
}

/********************************
A função DestroiAudio() é responsável por eliminar um áudio do jogo.
Parâmetros:
idAudio (entrada, passagem por valor): identificador do áudio a ser excluído.
********************************/
void DestroiAudio(int idAudio){
    CGerenciadorAudios::DestroiAudio(idAudio);
}

/********************************
A função CarregaBackground() é responsável por ler e preparar um arquivo de audio para ser tocado em background.
Apenas um único arquivo de áudio para background é permitido. Os formatos permitidos são WAVE, MOD, MIDI, OGG, MP3, FLAC.
Parâmetros:
nomeArquivo (entrada, passagem por referência): string que informa o nome do arquivo de áudio.
********************************/
void CarregaBackground(char *nomeArquivo){
    CGerenciadorAudios::CarregaBackground(nomeArquivo);
}

/********************************
A função PlayBackground() é responsável por tocar um áudio de background previamente carregado.
Parâmetros:
nVezes (entrada, passagem por valor): indica o número de vezes que o background deve ser executado.
O valor -1 indica que deve ser tocado indefinidamente.
********************************/
void PlayBackground(int nVezes=-1){
    CGerenciadorAudios::PlayBackground(nVezes);
}

/********************************
A função StopBackground() é responsável por parar um áudio de background previamente carregado.
********************************/
void StopBackground(){
    CGerenciadorAudios::StopBackground();
}

/********************************
A função PauseBackground() é responsável por pausar um áudio de background previamente carregado.
********************************/
void PauseBackground(){
    CGerenciadorAudios::PauseBackground();
}

/********************************
A função ResumeBackground() é responsável por continuar a tocar um áudio de background previamente carregado.
********************************/
void ResumeBackground(){
    CGerenciadorAudios::ResumeBackground();
}

/********************************
A função GetStatusBackground() recupera o status do audio de background.
Retorno:
Retorna: o valor do status do áudio de background(AUDIO_TOCANDO, AUDIO_PARADO ou AUDIO_PAUSADO)
********************************/
PIG_StatusAudio GetStatusBackground(){
    return CGerenciadorAudios::GetStatusBackground();
}

/********************************
A função SetVolumeBackground() define o valor do volume do áudio de background.
Parâmetro:
valor (entrada, passagem por valor): valor do novo volume a ser utilizado. Os valores devem ser entre 0 (mudo) e 128 (volume máximo).
********************************/
void SetVolumeBackground(int valor){
    CGerenciadorAudios::SetVolumeBackground(valor);
}

/********************************
A função GetVolumeBackground() recupera o valor do volume do áudio de background.
Retorno:
Retorna o valor do volume do audio de background. Os valores devem ser entre 0 (mudo) e 128 (volume máximo).
********************************/
int GetVolumeBackground(){
    return CGerenciadorAudios::GetVolumeBackground();
}

/********************************
A função SetVolumeBackground() define o valor do volume do áudio em questão.
Parâmetro:
idAudio (entrada, passagem por valor): identificador do áudio.
volume (entrada, passagem por valor): valor do novo volume a ser utilizado. Os valores devem ser entre 0 (mudo) e 128 (volume máximo).
********************************/
void SetVolume(int idAudio,int volume){
    CGerenciadorAudios::SetVolume(idAudio,volume);
}

/********************************
A função SetVolumeBackground() recupera o valor do volume do áudio em questão.
Parâmetro:
idAudio (entrada, passagem por valor): identificador do áudio.
Retorno:
Retorna o valor do volume do audio. Os valores devem ser entre 0 (mudo) e 128 (volume máximo).
********************************/
int GetVolume(int idAudio){
    return CGerenciadorAudios::GetVolume(idAudio);
}

/********************************
A função SetVolumeBackground() define o valor do volume de todos os áudios.
Parâmetro:
volume (entrada, passagem por valor): valor do novo volume a ser utilizado. Os valores devem ser entre 0 (mudo) e 128 (volume máximo).
********************************/
void SetVolumeTudo(int volume){
    CGerenciadorAudios::SetVolumeTudo(volume);
}

/********************************
A função PlayAudio() é responsável por tocar um áudio previamente criado.
Parâmetro:
idAudio (entrada, passagem por valor): indentificador do áudio.
********************************/
void PlayAudio(int idAudio){
    CGerenciadorAudios::Play(idAudio);
}

/********************************
A função PauseAudio() é responsável por pausar um áudio que esteja tocandoo.
Parâmetro:
idAudio (entrada, passagem por valor): indentificador do áudio.
********************************/
void PauseAudio(int idAudio){
    CGerenciadorAudios::Pause(idAudio);
}

/********************************
A função ResumeAudio() é responsável por continuar a tocar um áudio pausado.
Parâmetro:
idAudio (entrada, passagem por valor): indentificador do áudio.
********************************/
void ResumeAudio(int idAudio){
    CGerenciadorAudios::Resume(idAudio);
}

/********************************
A função StopAudio() é responsável por parar um áudio pausado ou tocando.
Parâmetro:
idAudio (entrada, passagem por valor): indentificador do áudio.
********************************/
void StopAudio(int idAudio){
    CGerenciadorAudios::Stop(idAudio);
}

/********************************
A função GetStatusAudio() recupera o status do audio em questão.
Parâmetro:
idAudio (entrada, passagem por valor): indentificador do áudio.
Retorno:
Retorna: o valor do status do áudio (AUDIO_TOCANDO, AUDIO_PARADO ou AUDIO_PAUSADO)
********************************/
PIG_StatusAudio GetStatusAudio(int idAudio){
    return CGerenciadorAudios::GetStatus(idAudio);
}

/********************************
A função ResumeTudoAudio() é responsável por parar todos os áudios pausados ou tocando.
********************************/
void StopTudoAudio(){
    CGerenciadorAudios::StopTudo();
}

/********************************
A função PauseTudoAudio() é responsável por pausar todos os áudios que estiverem tocando.
********************************/
void PauseTudoAudio(){
    CGerenciadorAudios::PauseTudo();
}

/********************************
A função ResumeTudoAudio() é responsável por continuar a tocar todos os áudios pausados.
********************************/
void ResumeTudoAudio(){
    CGerenciadorAudios::ResumeTudo();
}

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
int CriaSocketCliente(char *hostname, int porta, int maxBytesPacote=MAX_MENSAGEM_REDE_TCP){
    return CGerenciadorSockets::CriaCliente(hostname,porta,maxBytesPacote);
}

/********************************
A função CriaSocketServidor() é responsável por abrir um canal de comunicação para transmissões entrantes (ingoing).
A criação do socket pode ser impedida por políticas de acesso do firewall instalado.
Parâmetros:
maxClientes (entrada, passagem por valor): número máximo de clientes que poderão se comunicar concomitantemente com o servidor.
porta (entrada, passagem por valor): número da porta a ser aberta. Deve ser utilizado um valor na faixa 0-65535 que não esteja sendo utilizado por nenhum outro processo.
maxBytesPacote (entrada, passagem por valor): tamanho máximo de bytes enviados e/ou recebidos de cada vez.
Retorno:
Identificador do socket servidor que foi criado.
********************************/
int CriaSocketServidor(int maxClientes, int porta, int maxBytesPacote=MAX_MENSAGEM_REDE_TCP){
    return CGerenciadorSockets::CriaServidor(maxClientes,porta,maxBytesPacote);
}

/********************************
A função CriaSocketUDP() é responsável por abrir um canal de comunicação transmissões de acordo com o protocolo UDP.
O mesmo socket é utilizado para envio e recebimento das informções, não havendo papel de cliente e servidor distintos.
Parâmetros:
porta (entrada, passagem por valor): número da porta a ser aberta. Deve ser utilizado um valor na faixa 0-65535 que não esteja sendo utilizado por nenhum outro processo.
Retorno:
Identificador do socket UDP que foi criado.
********************************/
int CriaSocketUDP(int porta){
    return CGerenciadorSockets::CriaSocketUDP(porta);
}

/********************************
A função DestroiSocketCliente() é responsável por fechar o socket cliente aberto, impossibilitando novos envios e recebimentos por ele.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket a ser fechado.
********************************/
void DestroiSocketCliente(int idSocket){
    CGerenciadorSockets::DestroiCliente(idSocket);
}

/********************************
A função DestroiSocketServidor() é responsável por fechar o socket servidor aberto, impossibilitando novos envios e recebimentos por ele.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket a ser fechado.
********************************/
void DestroiSocketServidor(int idSocket){
    CGerenciadorSockets::DestroiServidor(idSocket);
}

/********************************
A função DestroiSocketUDP() é responsável por fechar o socket UDP aberto, impossibilitando novos envios e recebimentos por ele.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket a ser fechado.
********************************/
void DestroiSocketUDP(int idSocket){
    CGerenciadorSockets::DestroiSocketUDP(idSocket);
}

/********************************
A função GetAtivoSocketCliente() é responsável por verificar se o socket cliente ainda está ativo e conectado ao servidor ou não.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro que determina se o socket cliente ainda está ativo e conectado (valor diferente de zero) ou não (valor zero)
********************************/
int GetAtivoSocketCliente(int idSocket){
    return CGerenciadorSockets::GetAtivoCliente(idSocket);
}

/********************************
A função GetAtivoSocketServidor() é responsável por verificar se o socket servidor ainda está ativo ou não.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro que determina se o socket servidor ainda está ativo (valor diferente de zero) ou não (valor zero)
********************************/
int GetAtivoSocketServidor(int idSocket){
    return CGerenciadorSockets::GetAtivoServidor(idSocket);
}

/********************************
A função GetAtivoSocketUDP() é responsável por verificar se o socket UDP ainda está ativo ou não.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro que determina se o socket UDP ainda está ativo (valor diferente de zero) ou não (valor zero)
********************************/
int GetAtivoSocketUDP(int idSocket){
    return CGerenciadorSockets::GetAtivoSocketUDP(idSocket);
}

/********************************
A função GetBytesEnviadosSocketCliente() é responsável por recuperar a quantidade de bytes já enviados através do socket cliente desde a sua criação.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica a quantidade de bytes enviados através do socket.
********************************/
long GetBytesEnviadosSocketCliente(int idSocket){
    return CGerenciadorSockets::GetBytesEnviadosCliente(idSocket);
}

/********************************
A função GetBytesRecebidosSocketCliente() é responsável por recuperar a quantidade de bytes já recebidos através do socket cliente desde a sua criação.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica a quantidade de bytes recebidos através do socket.
********************************/
long GetBytesRecebidosSocketCliente(int idSocket){
    return CGerenciadorSockets::GetBytesRecebidosCliente(idSocket);
}

/********************************
A função GetPacotesEnviadosSocketCliente() é responsável por recuperar a quantidade de pacotes (mensagens) já enviados através do socket cliente desde a sua criação.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica a quantidade de pacotes enviados através do socket.
********************************/
long GetPacotesEnviadosSocketCliente(int idSocket){
    return CGerenciadorSockets::GetPacotesEnviadosCliente(idSocket);
}

/********************************
A função GetPacotesRecebidosSocketCliente() é responsável por recuperar a quantidade de pacotes (mensagens) já recebidos através do socket cliente desde a sua criação.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica a quantidade de pacotes recebidos através do socket.
********************************/
long GetPacotesRecebidosSocketCliente(int idSocket){
    return CGerenciadorSockets::GetPacotesRecebidosCliente(idSocket);
}

/********************************
A função GetTempoUltimoRecebidoSocketCliente() é responsável por recuperar o momento em que o último pacote foi recebido pelo socket.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica o tempo do recebimento do último pacote pelo socket.
********************************/
long GetTempoUltimoRecebidoSocketCliente(int idSocket){
    return CGerenciadorSockets::GetTempoUltimoRecebidoCliente(idSocket);
}

/********************************
A função GetTempoUltimoEnviadoSocketCliente() é responsável por recuperar o momento em que o último pacote foi enviado pelo socket.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica o tempo do envio do último pacote pelo socket.
********************************/
long GetTempoUltimoEnviadoSocketCliente(int idSocket){
    return CGerenciadorSockets::GetTempoUltimoEnviadoCliente(idSocket);
}

/********************************
A função GetBytesEnviadosSocketServidor() é responsável por recuperar a quantidade de bytes já enviados através do socket cliente desde a sua criação.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica a quantidade de bytes enviados através do socket.
********************************/
long GetBytesEnviadosSocketServidor(int idSocket){
    return CGerenciadorSockets::GetBytesEnviadosServidor(idSocket);
}

/********************************
A função GetBytesRecebidosSocketServidor() é responsável por recuperar a quantidade de bytes já recebidos através do socket cliente desde a sua criação.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica a quantidade de bytes recebidos através do socket.
********************************/
long GetBytesRecebidosSocketServidor(int idSocket){
    return CGerenciadorSockets::GetBytesRecebidosServidor(idSocket);
}

/********************************
A função GetPacotesEnviadosSocketServidor() é responsável por recuperar a quantidade de pacotes (mensagens) já enviados através do socket cliente desde a sua criação.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica a quantidade de pacotes enviados através do socket.
********************************/
long GetPacotesEnviadosSocketServidor(int idSocket){
    return CGerenciadorSockets::GetPacotesEnviadosCliente(idSocket);
}

/********************************
A função GetPacotesRecebidosSocketServidor() é responsável por recuperar a quantidade de pacotes (mensagens) já recebidos através do socket cliente desde a sua criação.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica a quantidade de pacotes recebidos através do socket.
********************************/
long GetPacotesRecebidosSocketServidor(int idSocket){
    return CGerenciadorSockets::GetPacotesRecebidosCliente(idSocket);
}

/********************************
A função GetTempoUltimoRecebidoSocketServidor() é responsável por recuperar o momento em que o último pacote foi recebido pelo socket.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica o tempo do recebimento do último pacote pelo socket.
********************************/
long GetTempoUltimoRecebidoSocketServidor(int idSocket){
    return CGerenciadorSockets::GetTempoUltimoRecebidoServidor(idSocket);
}

/********************************
A função GetTempoUltimoEnviadoSocketServidor() é responsável por recuperar o momento em que o último pacote foi enviado pelo socket.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica o tempo do envio do último pacote pelo socket.
********************************/
long GetTempoUltimoEnviadoSocketServidor(int idSocket){
    return CGerenciadorSockets::GetTempoUltimoEnviadoServidor(idSocket);
}

/********************************
A função GetBytesEnviadosSocketUDP() é responsável por recuperar a quantidade de bytes já enviados através do socket cliente desde a sua criação.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica a quantidade de bytes enviados através do socket.
********************************/
long GetBytesEnviadosSocketUDP(int idSocket){
    return CGerenciadorSockets::GetBytesEnviadosSocketUDP(idSocket);
}

/********************************
A função GetBytesRecebidosSocketUDP() é responsável por recuperar a quantidade de bytes já recebidos através do socket cliente desde a sua criação.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica a quantidade de bytes recebidos através do socket.
********************************/
long GetBytesRecebidosSocketUDP(int idSocket){
    return CGerenciadorSockets::GetBytesRecebidosSocketUDP(idSocket);
}

/********************************
A função GetPacotesEnviadosSocketUDP() é responsável por recuperar a quantidade de pacotes (mensagens) já enviados através do socket cliente desde a sua criação.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica a quantidade de pacotes enviados através do socket.
********************************/
long GetPacotesEnviadosSocketUDP(int idSocket){
    return CGerenciadorSockets::GetPacotesEnviadosSocketUDP(idSocket);
}

/********************************
A função GetPacotesRecebidosSocketUDP() é responsável por recuperar a quantidade de pacotes (mensagens) já recebidos através do socket cliente desde a sua criação.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica a quantidade de pacotes recebidos através do socket.
********************************/
long GetPacotesRecebidosSocketUDP(int idSocket){
    return CGerenciadorSockets::GetPacotesRecebidosSocketUDP(idSocket);
}

/********************************
A função GetTempoUltimoRecebidoSocketUDP() é responsável por recuperar o momento em que o último pacote foi recebido pelo socket.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica o tempo do recebimento do último pacote pelo socket.
********************************/
long GetTempoUltimoRecebidoSocketUDP(int idSocket){
    return CGerenciadorSockets::GetTempoUltimoRecebidoSocketUDP(idSocket);
}

/********************************
A função GetTempoUltimoEnviadoSocketUDP() é responsável por recuperar o momento em que o último pacote foi enviado pelo socket.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica o tempo do envio do último pacote pelo socket.
********************************/
long GetTempoUltimoEnviadoSocketUDP(int idSocket){
    return CGerenciadorSockets::GetTempoUltimoEnviadoSocketUDP(idSocket);
}

/********************************
A função GetPortaRemotaSocketCliente() é responsável por recuperar o número da porta remota (do servidor) à qual está conectado o socket.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro que indica o número da porta remota (do servidor) à qual está conectado o socket.
********************************/
int GetPortaRemotaSocketCliente(int idSocket){
    return CGerenciadorSockets::GetPortaRemotaCliente(idSocket);
}

/********************************
A função GetPortaLocalSocketServidor() é responsável por recuperar o número da porta local que está sendo utilizada pelo socket servidor.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro que indica o número da porta local do socket servidor.
********************************/
int GetPortaLocalSocketServidor(int idSocket){
    return CGerenciadorSockets::GetPortaLocalServidor(idSocket);
}

/********************************
A função GetPortaLocalSocketUDP() é responsável por recuperar o número da porta local que está sendo utilizada pelo socket UDP.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro que indica o número da porta local do socket UDP.
********************************/
int GetPortaLocalSocketUDP(int idSocket){
    return CGerenciadorSockets::GetPortaLocalSocketUDP(idSocket);
}

/********************************
A função GetHostRemotoSocketCliente() é responsável por recuperar o nome do computador (da rede local) ou do endereço IP ao qual está conectado o socket cliente, ou seja, o servidor.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
hostname (saída, passagem por referência): nome do computador (da rede local) ou do endereço IP ao qual está conectado o socket cliente.
********************************/
void GetHostRemotoSocketCliente(int idSocket,char *hostname){
    std::string resp = CGerenciadorSockets::GetHostRemotoCliente(idSocket);
    strcpy(hostname,resp.c_str());
}

/********************************
A função GetHostLocalSocketCliente() é responsável por recuperar o nome do computador (na rede local) ou do endereço IP da máquina está aberto o socket cliente.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
hostname (saída, passagem por referência): nome do computador (na rede local) ou do endereço IP da máquina no qual está aberto o socket cliente.
********************************/
void GetHostLocalSocketCliente(int idSocket,char *hostname){
    std::string resp = CGerenciadorSockets::GetHostLocalCliente(idSocket);
    strcpy(hostname,resp.c_str());
}

/********************************
A função GetHostLocalSocketServidor() é responsável por recuperar o nome do computador (na rede local) ou do endereço IP da máquina está aberto o socket servidor.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
hostname (saída, passagem por referência): nome do computador (na rede local) ou do endereço IP da máquina no qual está aberto o socket servidor.
********************************/
void GetHostLocalSocketServidor(int idSocket,char *hostname){
    std::string resp = CGerenciadorSockets::GetHostLocalServidor(idSocket);
    strcpy(hostname,resp.c_str());
}

/********************************
A função GetHostLocalSocketUDP() é responsável por recuperar o nome do computador (na rede local) ou do endereço IP da máquina está aberto o socket UDP.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
hostname (saída, passagem por referência): nome do computador (na rede local) ou do endereço IP da máquina no qual está aberto o socket UDP.
********************************/
void GetHostLocalSocketUDP(int idSocket,char *hostname){
    std::string resp = CGerenciadorSockets::GetHostLocalSocketUDP(idSocket);
    strcpy(hostname,resp.c_str());
}

/********************************
A função GetTamanhoPacoteSocketCliente() é responsável por recuperar o tamanho máximo de bytes utilizado pelo socket para envio ou recebimento de mensagens.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro que indica o tamanho máximo, em bytes, das mensagens enviadas ou recebidas pelo socket.
********************************/
int GetTamanhoPacoteSocketCliente(int idSocket){
    return CGerenciadorSockets::GetTamanhoPacoteCliente(idSocket);
}

/********************************
A função GetTamanhoPacoteSocketServidor() é responsável por recuperar o tamanho máximo de bytes utilizado pelo socket para envio ou recebimento de mensagens.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro que indica o tamanho máximo, em bytes, das mensagens enviadas ou recebidas pelo socket.
********************************/
int GetTamanhoPacoteSocketServidor(int idSocket){
    return CGerenciadorSockets::GetTamanhoPacoteServidor(idSocket);
}

/********************************
A função GetMaximoConexoesSocketServidor() é responsável por recuperar a quantidade máxima de conexões que podem ser estabelecidas pelo socket servidor com outros sockets clientes.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro que indica a quantidade máxima de conexões concomitantes que podem ser estabelecidas pelo socket servidor com outros sockets clientes.
********************************/
int GetMaximoConexoesSocketServidor(int idSocket){
    return CGerenciadorSockets::GetMaximoConexoesServidor(idSocket);
}

/********************************
A função GetQuantidadeConexoesSocketServidor() é responsável por recuperar a quantidade de conexões atualmente abertas pelo socket servidor com outros sockets clientes.
Parâmetros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro que indica a quantidade de conexões atualmente abertas pelo socket servidor com outros sockets clientes.
********************************/
int GetQuantidadeConexoesSocketServidor(int idSocket){
    return CGerenciadorSockets::GetQuantidadeConexoes(idSocket);
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
int EnviaDadosSocketCliente(int idSocket,void *buffer, int tamanhoBuffer){
    return CGerenciadorSockets::EnviaDadosCliente(idSocket,buffer,tamanhoBuffer);
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
int EnviaDadosSocketServidor(int idSocket,int socketSecundario,void *buffer, int tamanhoBuffer){
    return CGerenciadorSockets::EnviaDadosServidor(idSocket,socketSecundario,buffer,tamanhoBuffer);
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
int EnviaDadosSocketUDP(int idSocket,void *buffer,int tamanhoBuffer, char *hostRemoto, int porta){
    return CGerenciadorSockets::EnviaDadosSocketUDP(idSocket,buffer,tamanhoBuffer,hostRemoto,porta);
}

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
Retorna o identificador do vídeo para ser utilizado por outras funções.
********************************/
int CriaVideo(char *nomeArquivo,int idJanela=0){
    return CGerenciadorVideos::CriaVideo(nomeArquivo,idJanela);
}

/********************************
A função DestroiVideo() é responsável por eliminar um vídeo do jogo.
Parâmetros:
idVideo (entrada, passagem por valor): identificador do vídeo a ser excluído.
********************************/
void DestroiVideo(int idVideo){
    CGerenciadorVideos::DestroiVideo(idVideo);
}

/********************************
A função SetSeekVideo() é responsável por avançar ou retroceder o vídeo instantaneamente.
Parâmetros:
idVideo (entrada, passagem por valor): identificador do vídeo.
incremento (entrada, passagem por valor): quantidade de tempo (em segundos) para o avançao ou retrocesso do vídeo.
********************************/
void SetSeekVideo(int idVideo, double incremento){
    CGerenciadorVideos::SetSeek(idVideo,incremento);
}

/********************************
A função PlayVideo() é responsável por tocar um vídeo previamente criado.
Parâmetro:
idVideo (entrada, passagem por valor): indentificador do vídeo.
********************************/
void PlayVideo(int idVideo){
    CGerenciadorVideos::Play(idVideo);
}

/********************************
A função StopVideo() é responsável por parar um vídeo pausado ou tocando.
Parâmetro:
idVideo (entrada, passagem por valor): indentificador do vídeo.
********************************/
void StopVideo(int idVideo){
    CGerenciadorVideos::Stop(idVideo);
}

/********************************
A função PauseVideo() é responsável por pausar um vídeo que esteja tocando.
Parâmetro:
idVideo (entrada, passagem por valor): indentificador do vídeo.
********************************/
void PauseVideo(int idVideo){
    CGerenciadorVideos::Pause(idVideo);
}

/********************************
A função ResumeVideo() é responsável por continuar a tocar um vídeo pausado.
Parâmetro:
idVideo (entrada, passagem por valor): indentificador do vídeo.
********************************/
void ResumeVideo(int idVideo){
    CGerenciadorVideos::Resume(idVideo);
}

/********************************
A função DesenhaVideo() é responsável por desenhar os frames de um vídeo na tela. O vídeo será desenhado de acordo com todas as definições
de posição e ângulo informado até o momento. Além disso, se o vídeo estiver virado (flipping), isso também será levado em consideração, bem como a coloração e a opacidade definidas.
Parâmetro:
idVideo (entrada, passagem por valor): identificador do vídeo a ser desenhado.
********************************/
int DesenhaVideo(int idVideo){
    CGerenciadorVideos::Desenha(idVideo);
}

/********************************
A função SetVolumeVideo() é responsável por definir o volume para o vídeo. O valor informado deve ser positivo ou zero (mudo).
Parâmetro:
idVideo (entrada, passagem por valor): indentificador do vídeo.
valor (entrada, passagem por valor): volume a ser definido. Deve ser positivo ou zero (mudo).
********************************/
void SetVolumeVideo(int idVideo, double valor){
    CGerenciadorVideos::SetVolume(idVideo,valor);
}

/********************************
A função GetVolumeVideo() é responsável por recuperar o valor do volume do vídeo.
Parâmetro:
idVideo (entrada, passagem por valor): indentificador do vídeo.
Retorno:
Nível de volume do vídeo (deve ser sempre um valor positivo).
********************************/
double GetVolumeVideo(int idVideo){
    return CGerenciadorVideos::GetVolume(idVideo);
}

/********************************
A função GetNomeArquivoVideo() é responsável por recuperar o nome do arquivo que deu origem ao video.
Parâmetro:
idVideo (entrada, passagem por valor): indentificador do vídeo.
nome (saída, passagem por referência): nome do arquivo utilizado para criar o video.
********************************/
void GetNomeArquivoVideo(int idVideo, char *nome){
    std::string resp = CGerenciadorVideos::GetNomeArquivo(idVideo);
    strcpy(nome,resp.c_str());
}

/********************************
A função GetTempoAtualVideo() é responsável por recuperar o valor (em milissegundo) do tempo de vídeo já exibido, ou seja, o momento atual do vídeo.
Parâmetro:
idVideo (entrada, passagem por valor): indentificador do vídeo.
Retorno:
Total de tempo (em milissegundos) da parte já exibida do vídeo.
********************************/
double GetTempoAtualVideo(int idVideo){
    return CGerenciadorVideos::GetTempoAtual(idVideo);
}

/********************************
A função GetTempoAtualVideo() é responsável por recuperar uma string contendo a hora, minuto, segundo e milissegundo do frame atual do video.
Parâmetro:
idVideo (entrada, passagem por valor): indentificador do vídeo.
str (saída, passagem por referência): posição do frame atual, definido em hora, minuto, segundo e milissegundo.
********************************/
void GetTempoAtualVideo(int idVideo, char *str){
    std::string resp = CGerenciadorVideos::GetTempoAtualString(idVideo);
    strcpy(str,resp.c_str());
}

/********************************
A função GetTempoTotalVideo() é responsável por recuperar a druação total do vídeo (em milissegundo).
Parâmetro:
idVideo (entrada, passagem por valor): indentificador do vídeo.
Retorno
Tempo total do vídeo em milissegundos.
********************************/
double GetTempoTotalVideo(int idVideo){
    return CGerenciadorVideos::GetTempoTotal(idVideo);
}

/********************************
A função GetTempoTotalVideo() é responsável por recuperar uma string contendo a duração do video em hora, minuto, segundo e milissegundo.
Parâmetro:
idVideo (entrada, passagem por valor): indentificador do vídeo.
str (saída, passagem por referência): duração do vídeo, definido em hora, minuto, segundo e milissegundo.
********************************/
void GetTempoTotalVideo(int idVideo, char *str){
    std::string resp = CGerenciadorVideos::GetTempoTotalString(idVideo);
    strcpy(str,resp.c_str());
}

/********************************
A função GetTempoFrameVideo() é responsável por recuperar a duração esperada para cada frame do video (em milissegundo).
Parâmetro:
idVideo (entrada, passagem por valor): indentificador do vídeo.
Retorno:
Duração esperado de cada frame do vídeo (em milissegundo).
********************************/
double GetTempoFrameVideo(int idVideo){
    return CGerenciadorVideos::GetTempoFrame(idVideo);
}

/********************************
A função GetFPSVideo() é responsável por recuperar a quantidade de frames do vídeo que deveriam ser exibidos a cada segundo.
Parâmetro:
idVideo (entrada, passagem por valor): indentificador do vídeo.
Retorno:
Quantidade desejada de frames a cada segundo.
********************************/
double GetFPSVideo(int idVideo){
    return CGerenciadorVideos::GetFPS(idVideo);
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
    CGerenciadorVideos::SetAngulo(idVideo,angulo);
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
    return CGerenciadorVideos::GetAngulo(idVideo);
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
void SetFlipVideo(int idVideo, PIG_Flip valor){
    CGerenciadorVideos::SetFlip(idVideo,valor);
}

/********************************
A função GetFlipVideo() é responsável por recuperar o valor da manipulação causada pela função SetFlipVideo().
Parâmetros:
idVideo (entrada, passagem por valor): identificador do vídeo a ser virado.
Retorno:
inteiro que indica o tipo de Flip. Pode ser FLIP_NENHUM (nenhum tipo de inversão),
FLIP_HORIZONTAL (inverte da esquerda para a direita), FLIP_VERTICAL (inverte de cima para baixo),
ou FLIP_HORIZ_VERT (inverte da esquerda para direita e de cima para baixo).
********************************/
PIG_Flip GetFlipVideo(int idVideo){
    return CGerenciadorVideos::GetFlip(idVideo);
}

/********************************
A função SetPivoVideo() define um ponto (X,Y) em relação ao ponto (0,0) do vídeo, sobre o qual o video será
rotacionado quando a função SetAnguloVideo() for executada.
Parâmetros:
idVideo (entrada, passagem por valor): identificador do vídeo.
posicaoX (entrada, passagem por valor): Valor da coordenada X do pivô em relação ao ponto (0,0) do vídeo.
posicaoY (entrada, passagem por valor): Valor da coordenada Y do pivô em relação ao ponto (0,0) do vídeo.
********************************/
void SetPivoVideo(int idVideo, int posicaoX,int posicaoY){
    CGerenciadorVideos::SetPivo(idVideo,posicaoX,posicaoY);
}

/********************************
A função SetPivoObjeto() define um ponto relativo (X,Y) em relação ao video (0,0) e ao tamanho do vídeo, sobre o qual o vídeo será
rotacionado quando a função SetAnguloVideo() for executada.
Parâmetros:
idVideo (entrada, passagem por valor): identificador do vídeo.
relX (entrada, passagem por valor): porcentagem da largura do vídeo onde ficará o pivô.
relY (entrada, passagem por valor): porcentagem da altura do vídeo onde ficará o pivô.
********************************/
void SetPivoVideo(int idVideo, float relX,float relY){
    CGerenciadorVideos::SetPivo(idVideo,relX,relY);
}

/********************************
A função GetPivoVideo() define um ponto (X,Y) em relação ao ponto (0,0) do vídeo, sobre o qual o vídeo será
rotacionado quando a função SetAnguloVideo() for executada.
Parâmetros:
idVideo (entrada, passagem por valor): identificador do vídeo.
posicaoX (saída, passagem por referência): Valor da coordenada X do pivô em relação ao ponto (0,0) do vídeo.
posicaoY (saída, passagem por referência): Valor da coordenada Y do pivô em relação ao ponto (0,0) do vídeo.
********************************/
void GetPivoVideo(int idVideo, int *posicaoX,int *posicaoY){
    CGerenciadorVideos::GetPivo(idVideo,*posicaoX,*posicaoY);
}

/********************************
A função MoveVideo() é responsável por movimentar um determinado vídeo para uma nova posição informada.
Parâmetros:
idVideo (entrada, passagem por valor): identificador do vídeo a ser movido.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usuário deseja reposicionar o vídeo.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usuário deseja reposicionar o vídeo.
********************************/
void MoveVideo(int idVideo,int posicaoX,int posicaoY){
    CGerenciadorVideos::Move(idVideo,posicaoX,posicaoY);
}

/********************************
A função SetDimensoesVideo() é responsável por delimitar a altura e a largura do vídeo que será desenhado na tela,
independentemente do tamanho original do arquivo.
Parâmetros:
idVideo (entrada, passagem por valor): identificador do vídeo.
altura (entrada, passagem por valor): altura em pixels.
largura (entrada, passagem por valor): largura em pixels.
********************************/
void SetDimensoesVideo(int idVideo, int altura,int largura){
    CGerenciadorVideos::SetDimensoes(idVideo,altura,largura);
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
    CGerenciadorVideos::GetDimensoes(idVideo,*altura,*largura);
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
    CGerenciadorVideos::GetDimensoesOriginais(idVideo,*altura,*largura);
}

/********************************
A função OcupaJanelaInteiraVideo() é responsável por redimensionar a exibição do video, para que este ocupe todo o tamanho
da janela em que estiver sendo executado.
Parâmetros:
idVideo (entrada, passagem por valor): identificador do vídeo a ser desenhado.
********************************/
void OcupaJanelaInteiraVideo(int idVideo){
    CGerenciadorVideos::OcupaJanelaInteira(idVideo);
}

/********************************
A função UsaResolucaoOriginalVideo() é responsável por redimensionar a exibição do video, para que este utilize a resolução original
do arquivo de mídia.
Parâmetros:
idVideo (entrada, passagem por valor): identificador do vídeo a ser desenhado.
********************************/
void UsaResolucaoOriginalVideo(int idVideo){
    CGerenciadorVideos::UsaResolucaoOriginal(idVideo);
}


/********************************
A função SetColoracaoVideo() é responsável por mesclar uma determinada cor com os pixels do frame do vídeo.
Após a modificação, todos os desenhos deste vídeo serão mostrados já com a mesclagem definida.
Para voltar ao padrão original de pixels, deve-se chamar a função, passando a cor branca (255,255,255).
Parâmetros:
idVideo (entrada, passagem por valor): identificador do vídeo a ser desenhado.
cor (entrada,passagem por valor): cor do sistema RGB utilizada para mesclagem com o arquivo de vídeo.
********************************/
void SetColoracaoVideo(int idVideo, PIG_Cor cor){
    CGerenciadorVideos::SetColoracao(idVideo,cor);
}

/********************************
A função SetOpacidadeVideo() é responsável por modificar o nível de opacidade do vídeo.
O nível de opacidade varia de 0-255, sendo 0 totalmente transparente e 255 totalmente opaco.
Parâmetros:
idVideo (entrada, passagem por valor): identificador do vídeo.
valor (entrada,passagem por valor): nível de opacidade do vídeo na faixa 0-255.
********************************/
void SetOpacidadeVideo(int idVideo, int valor){
    CGerenciadorVideos::SetOpacidade(idVideo,valor);
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
    return CGerenciadorVideos::GetOpacidade(idVideo);
}




/*******FORM*********/

int PIG_CriaForm(int xForm, int yForm, int altForm, int largForm,int janela = 0){
    return CGerenciadorForms::CriaForm(xForm,yForm,altForm,largForm,janela);
}

int PIG_Form_TrataEvento(int idForm,PIG_Evento evento){
    return CGerenciadorForms::TrataEvento(idForm,evento);
}

int PIG_Form_Desenha(int idForm){
    return CGerenciadorForms::Desenha(idForm);
}

/*******COMPONENTES*********/

int PIG_CriaComponentePorArquivo(int idForm,tipos_Componentes componente,char* nomeArquivo){
    return CGerenciadorForms::CriaComponentePorArquivo(idForm,componente,nomeArquivo);
}

void PIG_Componentes_SetLabel(int idComponente,char* novoLabel){
    CGerenciadorForms::GetComponente(idComponente)->SetLabel(novoLabel);
}

void PIG_Componentes_SetFonteLabel(int idComponente,int fonte){
    CGerenciadorForms::GetComponente(idComponente)->SetFonteLabel(fonte);
}

void PIG_Componentes_SetCorLabel(int idComponente,PIG_Cor cor){
    CGerenciadorForms::GetComponente(idComponente)->SetCorLabel(cor);
}

void PIG_Componentes_SetFonteHint(int idComponente,int fonte){
    CGerenciadorForms::GetComponente(idComponente)->SetFonteHint(fonte);
}

void PIG_Componentes_SetCorHint(int idComponente,PIG_Cor cor){
    CGerenciadorForms::GetComponente(idComponente)->SetCorHint(cor);
}

void PIG_Componentes_SetAudio(int idComponente,int idAudio){
    CGerenciadorForms::GetComponente(idComponente)->SetAudio(idAudio);
}

void PIG_Componentes_GetLabel(int idComponente,char *label){
    strcpy(label,(char*)(CGerenciadorForms::GetComponente(idComponente)->GetLabel()).c_str());
}

void PIG_Componentes_SetHint(int idComponente,char *hint){
    CGerenciadorForms::GetComponente(idComponente)->SetHint(hint);
}

void PIG_Componentes_Move(int idComponente,int x,int y){
    CGerenciadorForms::GetComponente(idComponente)->Move(x,y);
}

void PIG_Componentes_SetDimensoes(int idComponente,int altura,int largura){
    CGerenciadorForms::GetComponente(idComponente)->SetDimensoes(altura,largura);
}

void PIG_Componentes_SetPosicaoPadraoLabel(int idComponente,PIG_PosicaoComponente pos){
    CGerenciadorForms::GetComponente(idComponente)->SetPosicaoPadraoLabel(pos);
}

void PIG_Componentes_SetPosicaoPersonalizadaLabel(int idComponente,int x,int y){
    CGerenciadorForms::GetComponente(idComponente)->SetPosicaoPersonalizadaLabel(x,y);
}

void PIG_Componentes_SetPosPadraoExternaComponente(int idComponente,PIG_PosicaoComponente pos,CPigComponente *componenteAssociado){
    CGerenciadorForms::GetComponente(idComponente)->SetPosPadraoExternaComponente(pos,componenteAssociado);
}

void PIG_Componentes_SetPosPadraoComponenteNaTela(int idComponente,PIG_Ancora pos){
    CGerenciadorForms::GetComponente(idComponente)->SetPosPadraoComponenteNaTela(pos);
}

/*******BOTAO*********/

int PIG_CriaBotao(int idForm,int x,int y,int alt,int larg,char* nomeArq,int retiraFundo = 1){
    return CGerenciadorForms::CriaBotao(idForm,x,y,alt,larg,nomeArq,retiraFundo);
}

void PIG_Botao_DefineAcao(int idComponente,AcaoBotao funcao,void *parametro){
    ((CPigBotao*)CGerenciadorForms::GetComponente(idComponente))->DefineAcao(funcao,parametro);
}

void PIG_Botao_DefineAtalho(int idComponente,int teclaAtalho){
    ((CPigBotao*)CGerenciadorForms::GetComponente(idComponente))->DefineAtalho(teclaAtalho);
}

void PIG_Botao_DefineTempoRepeticao(int idComponente,double segundos){
    ((CPigBotao*)CGerenciadorForms::GetComponente(idComponente))->DefineTempoRepeticao(segundos);
}

void PIG_Botao_DefineBotaoRepeticao(int idComponente,bool repeticao){
    ((CPigBotao*)CGerenciadorForms::GetComponente(idComponente))->DefineBotaoRepeticao(repeticao);
}

/*******AREADETEXTO*********/

int PIG_CriaAreaDeTexto(int idForm,int x, int y, int altura,int largura,char* nomeArq,int maxCars = 200,int retiraFundo=1){
    return CGerenciadorForms::CriaAreaDeTexto(idForm,x,y,altura,largura,nomeArq,maxCars,retiraFundo);
}

void PIG_AreaDeTexto_SetScrollBarVertical(int idComponente,int larguraTotal,int comprimentoTotal,int larguraHandle,char* imgHandle,char* imgTrilha,int retiraFundoHandle=1,int retiraFundoTrilha=1){
    ((PigAreaDeTexto)CGerenciadorForms::GetComponente(idComponente))->SetScrollBarVertical(larguraTotal,comprimentoTotal,larguraHandle,imgHandle,imgTrilha,retiraFundoHandle,retiraFundoTrilha);
}

void PIG_AreaDeTexto_SetScrollBarHorizontal(int idComponente,int larguraTotal,int comprimentoTotal,int larguraHandle,char* imgHandle,char* imgTrilha,int retiraFundoHandle=1,int retiraFundoTrilha=1){
    ((PigAreaDeTexto)CGerenciadorForms::GetComponente(idComponente))->SetScrollBarHorizontal(larguraTotal,comprimentoTotal,larguraHandle,imgHandle,imgTrilha,retiraFundoHandle,retiraFundoTrilha);
}

void PIG_AreaDeTexto_SetBotoesScrollBarVertical(int idComponente,int larguraBotoes,char* imgBotao1,char* imgBotao2,int retiraFundoB1 = 1,int retiraFundoB2 = 1){
    ((PigAreaDeTexto)CGerenciadorForms::GetComponente(idComponente))->SetBotoesScrollBarVertical(larguraBotoes,imgBotao1,imgBotao2,retiraFundoB1,retiraFundoB2);
}

void PIG_AreaDeTexto_SetBotoesScrollBarHorizontal(int idComponente,int larguraBotoes,char* imgBotao1,char* imgBotao2,int retiraFundoB1 = 1,int retiraFundoB2 = 1){
    ((PigAreaDeTexto)CGerenciadorForms::GetComponente(idComponente))->SetBotoesScrollBarVertical(larguraBotoes,imgBotao1,imgBotao2,retiraFundoB1,retiraFundoB2);
}

void PIG_AreaDeTexto_SetPosPadraoScrollHorizontal(int idComponente,PIG_PosicaoComponente pos){
    ((PigAreaDeTexto)CGerenciadorForms::GetComponente(idComponente))->SetPosPadraoScrollHorizontal(pos);
}

void PIG_AreaDeTexto_SetPosPadraoScrollVertical(int idComponente,PIG_PosicaoComponente pos){
    ((PigAreaDeTexto)CGerenciadorForms::GetComponente(idComponente))->SetPosPadraoScrollVertical(pos);
}

void PIG_AreaDeTexto_MoveScrollBarHorizontal(int idComponente,int x,int y){
    ((PigAreaDeTexto)CGerenciadorForms::GetComponente(idComponente))->MoveScrollBarHorizontal(x,y);
}

void PIG_AreaDeTexto_MoveScrollBarVertical(int idComponente,int x,int y){
    ((PigAreaDeTexto)CGerenciadorForms::GetComponente(idComponente))->MoveScrollBarVertical(x,y);
}

void PIG_AreaDeTexto_SetFonteTexto(int idComponente,int fonte){
    ((PigAreaDeTexto)CGerenciadorForms::GetComponente(idComponente))->SetFonteTexto(fonte);
}

void PIG_AreaDeTexto_SetLinhasAbaixoTexto(int idComponente,bool visivel,PIG_Cor cor = PRETO){
    ((PigAreaDeTexto)CGerenciadorForms::GetComponente(idComponente))->SetLinhasAbaixoTexto(visivel,cor);
}

void PIG_AreaDeTexto_SetLargMaxTexto(int idComponente,int largMaxTexto){
    ((PigAreaDeTexto)CGerenciadorForms::GetComponente(idComponente))->SetLargMaxTexto(largMaxTexto);
}

void PIG_AreaDeTexto_SetEspacoEntreAsLinhas(int idComponente,int espaco){
    ((PigAreaDeTexto)CGerenciadorForms::GetComponente(idComponente))->SetEspacoEntreAsLinhas(espaco);
}

void PIG_AreaDeTexto_SetTexto(int idComponente,char* frase){
    ((PigAreaDeTexto)CGerenciadorForms::GetComponente(idComponente))->SetTexto(frase);
}

void PIG_AreaDeTexto_SetMargens(int idComponente,int horEsq,int horDir, int vertBaixo,int vertCima){
    ((PigAreaDeTexto)CGerenciadorForms::GetComponente(idComponente))->SetMargens(horEsq,horDir,vertBaixo,vertCima);
}

void PIG_AreaDeTexto_SetCorCursor(int idComponente,PIG_Cor cor){
    ((PigAreaDeTexto)CGerenciadorForms::GetComponente(idComponente))->SetCorCursor(cor);
}

std::vector<std::string> PIG_AreaDeTexto_GetLinhasTexto(int idComponente){
    ((PigAreaDeTexto)CGerenciadorForms::GetComponente(idComponente))->GetLinhasTexto();
}

/**********CAMPOTEXTO**************/

int PIG_CriaCampoTexto(int idForm,int x, int y, int altura,int largura,char* nomeArq,int maxCars = 200, bool apenasNumeros=false, int retiraFundo=1){
    return CGerenciadorForms::CriaCampoTextoESenha(idForm,x,y,altura,largura,nomeArq,maxCars,apenasNumeros,retiraFundo,false);
}

void PIG_CampoTexto_SetMargens(int idComponente,int horEsq,int horDir, int vertBaixo,int vertCima){
    ((PigCampoTextoESenha)CGerenciadorForms::GetComponente(idComponente))->SetMargens(horEsq,horDir,vertBaixo,vertCima);
}

void PIG_CampoTexto_SetTexto(int idComponente,char* frase){
    ((PigCampoTextoESenha)CGerenciadorForms::GetComponente(idComponente))->SetTexto(frase);
}

void PIG_CampoTexto_SetFonteTexto(int idComponente,int fonte){
    ((PigCampoTextoESenha)CGerenciadorForms::GetComponente(idComponente))->SetFonteTexto(fonte);
}

void PIG_CampoTexto_SetCorCursor(int idComponente,PIG_Cor cor){
    ((PigCampoTextoESenha)CGerenciadorForms::GetComponente(idComponente))->SetCorCursor(cor);
}

/**********CAMPOSENHA**************/

int PIG_CriaCampoSenha(int idForm,int x, int y, int altura,int largura,char* nomeArq,int maxCars = 200, bool apenasNumeros=false, int retiraFundo=1){
    return CGerenciadorForms::CriaCampoTextoESenha(idForm,x,y,altura,largura,nomeArq,maxCars,apenasNumeros,retiraFundo,true);
}

void PIG_CampoSenha_SetMargens(int idComponente,int horEsq,int horDir, int vertBaixo,int vertCima){
    ((PigCampoTextoESenha)CGerenciadorForms::GetComponente(idComponente))->SetMargens(horEsq,horDir,vertBaixo,vertCima);
}

void PIG_CampoSenha_SetTexto(int idComponente,char* frase){
    ((PigCampoTextoESenha)CGerenciadorForms::GetComponente(idComponente))->SetTexto(frase);
}

void PIG_CampoSenha_SetFonteTexto(int idComponente,int fonte){
    ((PigCampoTextoESenha)CGerenciadorForms::GetComponente(idComponente))->SetFonteTexto(fonte);
}

void PIG_CampoSenha_SetCorCursor(int idComponente,PIG_Cor cor){
    ((PigCampoTextoESenha)CGerenciadorForms::GetComponente(idComponente))->SetCorCursor(cor);
}

/**********LISTA**************/

int PIG_CriaListBox(int idForm,int x, int y,int larguraTotal,int alturaLinha,int alturaMaxima,int alturaItem,int largItem,char* nomeArq,int retiraFundo=1){
    return CGerenciadorForms::CriaListBox(idForm,x,y,larguraTotal,alturaLinha,alturaMaxima,alturaItem,largItem,nomeArq,retiraFundo);
}

int PIG_ListBox_CriaItem(int idComponente,char* texto,char* imagemIcone = "",char *imagemFundo="",char* hintMsg="",bool itemHabilitado = true, int audio=-1,int retiraFundoImg = 1){
    ((PigListBox)CGerenciadorForms::GetComponente(idComponente))->CriaItem(texto,imagemIcone,imagemFundo,false,itemHabilitado,audio,hintMsg,retiraFundoImg);
}

/**********DROPDOWN**************/

int PIG_CriaDropDown(int idForm,int x, int y, int larguraTotal,int alturaLinha,int alturaMaxima,int alturaItem,int larguraItem,char* nomeArq,int retiraFundo=1){
    return CGerenciadorForms::CriaDropDown(idForm,x,y,larguraTotal,alturaLinha,alturaMaxima,alturaItem,larguraItem,nomeArq,retiraFundo);
}

int PIG_DropDown_CriaItem(int idComponente,char* texto,char* imagemIcone = "",char *imagemFundo="", char* hintMsg="",bool itemHabilitado = true, int audio=-1,int retiraFundoImg = 1){
    ((PigDropDown)CGerenciadorForms::GetComponente(idComponente))->CriaItem(texto,imagemIcone,imagemFundo,itemHabilitado,audio,hintMsg,retiraFundoImg);
}

/**********GAUGE**************/

int PIG_CriaGauge(int idForm,int x, int y,int altura,int largura,char* imgGauge,int retiraFundo=1){
    return CGerenciadorForms::CriaGauge(idForm,x,y,altura,largura,imgGauge,retiraFundo);
}

void PIG_Gauge_SetFrames(int idComponente,SDL_Rect fBase,SDL_Rect fBarra){
    ((PigGauge)CGerenciadorForms::GetComponente(idComponente))->SetFrames(fBase,fBarra);
}

void PIG_Gauge_SetDelta(int idComponente,float valor){
    ((PigGauge)CGerenciadorForms::GetComponente(idComponente))->SetDelta(valor);
}

void PIG_Gauge_AvancaDelta(int idComponente){
    ((PigGauge)CGerenciadorForms::GetComponente(idComponente))->AvancaDelta();
}

float PIG_Gauge_GetPorcentagemConcluida(int idComponente){
    return ((PigGauge)CGerenciadorForms::GetComponente(idComponente))->GetPorcentagemConcluida();
}

void PIG_Gauge_ZeraValor(int idComponente){
    ((PigGauge)CGerenciadorForms::GetComponente(idComponente))->ZeraValor();
}

/**********GAUGECIRCULAR**************/

int PIG_CriaGaugeCircular(int idForm,int x, int y,int altura,int largura,int raioInterior,char* imgGauge,int retiraFundo=1){
    return CGerenciadorForms::CriaGaugeCircular(idForm,x,y,altura,largura,raioInterior,imgGauge,retiraFundo);
}

/**********RADIOBOX**************/

int PIG_CriaRadioBox(int idForm,int x, int y,int larguraTotal,int alturaLinha, int alturaMaxima,char* imagemItem, int alturaItem, int larguraItem,char* imagemFundo, int retiraFundo=1){
    return CGerenciadorForms::CriaRadioBox(idForm,x,y,larguraTotal,alturaLinha,alturaMaxima,imagemItem,alturaItem,larguraItem,imagemFundo,retiraFundo);
}

void PIG_RadioBox_CriaItem(int idComponente,char* itemLabel, char *imagemFundo="", char* hintMsg="", bool itemHabilitado = true, int audio=-1, int retiraFundo=1){
    ((PigRadioBox)CGerenciadorForms::GetComponente(idComponente))->CriaItem(itemLabel,imagemFundo,itemHabilitado,audio,hintMsg,retiraFundo);
}

int PIG_RadioBox_GetItemDestaque(int idComponente){
    return ((PigRadioBox)CGerenciadorForms::GetComponente(idComponente))->GetItemDestaque();
}

int PIG_RadioBox_SetItemMarcado(int idComponente,int item, bool marcado){
    return ((PigRadioBox)CGerenciadorForms::GetComponente(idComponente))->SetAcionadoItem(item,marcado);
}

int PIG_RadioBox_GetEstadoMarcadoItem(int idComponente,int item){
    return ((PigRadioBox)CGerenciadorForms::GetComponente(idComponente))->GetAcionadoItem(item);
}

int PIG_RadioBox_SetAudioItem(int idComponente,int item,int audio){
    return ((PigRadioBox)CGerenciadorForms::GetComponente(idComponente))->SetAudioItem(item,audio);
}

int PIG_RadioBox_GetEstadoHabilitadoItem(int idComponente,int item){
    return ((PigRadioBox)CGerenciadorForms::GetComponente(idComponente))->GetHabilitadoItem(item);
}

int PIG_RadioBox_SetEstadoHabilitadoItem(int idComponente,int item,bool habilitado){
    return ((PigRadioBox)CGerenciadorForms::GetComponente(idComponente))->SetHabilitadoItem(item,habilitado);
}

void PIG_RadioBox_SetEstadoHabilitadoItens(int idComponente,bool habilitado){
    return ((PigRadioBox)CGerenciadorForms::GetComponente(idComponente))->SetHabilitado(habilitado);
}

/**********CHECKBOX**************/

int PIG_CriaCheckBox(int idForm,int x, int y,int larguraTotal,int alturaLinha, int alturaMaxima,char* imagemItem, int alturaItem, int larguraItem,char* imagemFundo, int retiraFundo=1, int idJanela=0){
    return CGerenciadorForms::CriaCheckBox(idForm,x,y,larguraTotal,alturaLinha,alturaMaxima,imagemItem,alturaItem,larguraItem,imagemFundo,retiraFundo);
}

void PIG_CheckBox_CriaItem(int idComponente,char* itemLabel,char *imagemFundo="",char* hintMsg="",bool itemMarcado = false, bool itemHabilitado = true, int audio=-1,  int retiraFundo=1){
    ((PigCheckBox)CGerenciadorForms::GetComponente(idComponente))->CriaItem(itemLabel,imagemFundo,itemMarcado,itemHabilitado,audio,hintMsg,retiraFundo);
}

void PIG_CheckBox_SetMarcadoTodos(int idComponente,bool marcado){
    ((PigCheckBox)CGerenciadorForms::GetComponente(idComponente))->SetAcionadoTodos(marcado);
}

int PIG_CheckBox_SetMarcadoItem(int idComponente,int indice,bool marcado){
    return ((PigCheckBox)CGerenciadorForms::GetComponente(idComponente))->SetAcionadoItem(indice,marcado);
}

std::vector <int> PIG_CheckBox_GetItensMarcados(int idComponente){
    return ((PigCheckBox)CGerenciadorForms::GetComponente(idComponente))->GetItensMarcados();
}

int PIG_CheckBox_GetMarcadoItem(int idComponente,int item){
    return ((PigCheckBox)CGerenciadorForms::GetComponente(idComponente))->GetAcionadoItem(item);
}

int PIG_CheckBox_SetAudioItem(int idComponente,int item,int audio){
    return ((PigCheckBox)CGerenciadorForms::GetComponente(idComponente))->SetAudioItem(item,audio);
}

int PIG_CheckBox_GetHabilitadoItem(int idComponente,int item){
    return ((PigCheckBox)CGerenciadorForms::GetComponente(idComponente))->GetHabilitadoItem(item);
}

int PIG_CheckBox_SetHabilitadoItem(int idComponente,int item,bool habilitado){
    return ((PigCheckBox)CGerenciadorForms::GetComponente(idComponente))->SetHabilitadoItem(item,habilitado);
}

void PIG_CheckBox_SetHabilitado(int idComponente,bool habilitado){
    return ((PigCheckBox)CGerenciadorForms::GetComponente(idComponente))->SetHabilitado(habilitado);
}

/********************************/
