/********************************
Principais definições utilizadas pela PIG
********************************/

#include "SDL.h"

#define PIG_ALT_TELA                    600
#define PIG_LARG_TELA                   800

#define PIG_AFASTAMENTO_MINIMO          0.1
#define PIG_AFASTAMENTO_MAXIMO          100.0

#define PIG_MAX_JANELAS                 4
#define PIG_JANELA_TELACHEIA            SDL_WINDOW_FULLSCREEN
#define PIG_JANELA_TELACHEIA_DISPLAY    SDL_WINDOW_FULLSCREEN_DESKTOP
#define PIG_JANELA_NORMAL               0
#ifdef __linux__
#define PIG_JANELA_INICIAL              2
#elif _WIN32
#define PIG_JANELA_INICIAL              1
#else
#define PIG_JANELA_INICIAL              1
#endif

#ifdef _WIN32
    #include "direct.h"
    #define CHDIR _chdir
#else
    #include "unistd.h"
    #define CHDIR chdir
#endif

#define PIG_FF_REFRESH_EVENT            3333
#define PIG_FF_QUIT_EVENT               2222
#define PIG_FF_ALLOC_EVENT              1111

#define PIG_MAX_CURSORES                30
#define PIG_MAX_FONTES                  100
#define PIG_PRIMEIRO_CAR                11
#define PIG_ULTIMO_CAR                  256
#define PIG_MAX_LABELS                  10000

#define PIG_FREQ_AUDIO_PADRAO           22050
#define PIG_QTD_CANAIS_PADRAO           128
#define PIG_TAMANHO_CHUNK               4096
#define PIG_AUDIO_BACKGROUND            -1
#define PIG_MAX_AUDIOS                  2000
#define PIG_VOLUME_PADRAO               64

#define PIG_MAX_SPRITES                 5000
#define PIG_MAX_OBJETOS                 2000
#define PIG_MAX_ANIMACOES               1000

#define PIG_MAX_MODOS                   50

#define PIG_MAX_TIMERS                  50000
#define PIG_MAX_GRUPOS_TIMERS           100

#define PIG_MAX_GERADORPARTICULAS       100
#define PIG_MAX_PARTICULAS              1000

#define PIG_MAX_CAMADAS_OFFSCREEN       50

#define PIG_MAX_CONTROLES               5

#define PIG_MAX_SOCKETS_CLIENTES_TCP    10
#define PIG_MAX_SOCKETS_SERVIDORES_TCP  5
#define PIG_MAX_SOCKETS_UDP             100

#define PIG_MAX_VIDEOS                  10

#define PIG_MAX_COMPONENTES             500
#define PIG_MAX_CARS_CAIXATEXTO         200
#define PIG_MAX_FORMS                   100

#define PIG_MAX_TELAS                   2000
#define PIG_TEMPO_SAIDA_TELA_PADRAO     0.5
#define PIG_MULTITHREAD_TELAS           1

#define PIG_INTERVALO_FPS               1.0

#define PIG_SHARE_BITMAP
#define PIG_SHARE_AUDIO


#ifdef PIG_DEBUG
#define PIG_EXECUTA_SE_DEBUG(x) x;
#else
#define PIG_EXECUTA_SE_DEBUG(x)
#endif


typedef struct{
    double x,y;
}PIGPonto2D;


/********************************
O tipo PIGCor é um struct formado por 4 campos: r,g,b,a correspondendo aos valores de vermelho, verde, azul e alfa (transparência) do pixel
********************************/
typedef __declspec(deprecated("PIG_Cor nao deve mais ser usado. Utilize PIGCor.")) SDL_Color PIG_Cor;
typedef SDL_Color PIGCor;

#define BRANCO          ((SDL_Color){255,255,255,255})
#define PRETO           ((SDL_Color){0,0,0,255})
#define AZUL            ((SDL_Color){0,0,255,255})
#define VERMELHO        ((SDL_Color){255,0,0,255})
#define VERDE           ((SDL_Color){0,255,0,255})
#define AMARELO         ((SDL_Color){255,255,0,255})
#define ROXO            ((SDL_Color){255,0,255,255})
#define LARANJA         ((SDL_Color){255,128,0,255})
#define CIANO           ((SDL_Color){0,255,255,255})
#define CINZA           ((SDL_Color){128,128,128,255})

/********************************
O PIGTipoEvento é uma enumeração que contém os seguintes possíveis valores:
PIG_EVENTO_NULO: indica que não houve evento desde a última chamada da função GetEvento()
PIG_EVENTO_GERAL: (não implementado)
PIG_EVENTO_JANELA: indica algum possível evento relacionado à janela de jogo (redimensionamento, movimento, perda ou ganho de foco etc)
PIG_EVENTO_TECLADO: indica algum possível evento relacionado ao teclado do computador (tecla pressionada ou liberada, texto digitado ou editado etc)
PIG_EVENTO_MOUSE: indica algum posspivel evento relacionado ao mouse do compuatdor (botão pressionado ou liberado, movimentação, uso da rodinha etc)
PIG_EVENTO_AUDIO: indica o final da execução de algum tipo de audio (efeito ou background)
PIG_EVENTO_CONTROLADOR: indica algum possível evento relacionado aos botões ou eixos do controlador
PIG_EVENTO_USUARIO: (não implementado)
********************************/
typedef enum PIGTipoEvento{PIG_EVENTO_NULO,
                            PIG_EVENTO_GERAL,
                            PIG_EVENTO_JANELA,
                            PIG_EVENTO_TECLADO,
                            PIG_EVENTO_MOUSE,
                            PIG_EVENTO_AUDIO,
                            PIG_EVENTO_CONTROLADOR,
                            PIG_EVENTO_VIDEO,
                            PIG_EVENTO_REDE,
                            PIG_EVENTO_USUARIO}
                PIGTipoEvento;

/********************************
O PIGInfoEventoMouse é um struct contendo informações específicas sobre o evento de mouse:
acao: código que representa o evento específico (os possíveis valores podem ser vistos abaixo do struct)
posX: a posição no eixo X (nas coordenadas da tela) do ponteiro do mouse no momento de ocorrência do evento
posY: a posição no eixo Y (nas coordenadas do tela) do ponteiro do mouse no momento de ocorrência do evento
worldX: a posição no eixo X (nas coordenadas do mundo) do ponteiro do mouse no momento de ocorrência do evento
worldY: a posição no eixo Y (nas coordenadas do mundo) do ponteiro do mouse no momento de ocorrência do evento
botao: indica qual dos possíveis três botões foi pressionado ou liberado
cliques: indica a quantidade de cliques a que se refere o evento (1=clique simples, 2=clique duplo, ...)
relX: indica o deslocamento no eixo X quando há uma movimentação de mouse; adicionalmente, representa o deslocamento da rodinha no eixo X (não usado)
relX: indica o deslocamento no eixo Y quando há uma movimentação de mouse; adicionalmente, representa o deslocamento da rodinha no eixo Y
********************************/
typedef struct PIGInfoEventoMouse{
    int acao;
    int posX,posY;
    int worldX,worldY;
    int botao;
    int cliques;
    int relX,relY;
    int numeroJanela;
}PIGInfoEventoMouse;
#define PIG_MOUSE_PRESSIONADO       SDL_MOUSEBUTTONDOWN
#define PIG_MOUSE_LIBERADO          SDL_MOUSEBUTTONUP
#define PIG_MOUSE_MOVIDO            SDL_MOUSEMOTION
#define PIG_MOUSE_RODINHA           SDL_MOUSEWHEEL
#define PIG_MOUSE_DIREITO           SDL_BUTTON_RIGHT
#define PIG_MOUSE_ESQUERDO          SDL_BUTTON_LEFT
#define PIG_MOUSE_CENTRAL           SDL_BUTTON_MIDDLE

/********************************
O PIGInfoEventoJanela é um struct contendo informações específicas sobre o evento de janela:
acao: código que representa o evento específico (os possíveis valores podem ser vistos abaixo do struct)
dado1,dado2: indicam em conjunto a informação específica do evento, podendo representar o ponto (X,Y), em relação ao monitor,
para o qual a janela foi movida ou o novo tamanho da janela após uma alteração de dimensões na mesma
********************************/
typedef struct PIGInfoEventoJanela{
    int acao;
    int numeroJanela;
    int dado1,dado2;
}PIGInfoEventoJanela;
#define PIG_JANELA_EXIBIDA          SDL_WINDOWEVENT_SHOWN
#define PIG_JANELA_OCULTA           SDL_WINDOWEVENT_HIDDEN
#define PIG_JANELA_EXPOSTA          SDL_WINDOWEVENT_EXPOSED
#define PIG_JANELA_MOVIDA           SDL_WINDOWEVENT_MOVED
#define PIG_JANELA_REDIMENSIONADA   SDL_WINDOWEVENT_RESIZED
#define PIG_JANELA_ALTERADA         SDL_WINDOWEVENT_SIZE_CHANGED
#define PIG_JANELA_MINIMIZADA       SDL_WINDOWEVENT_MINIMIZED
#define PIG_JANELA_MAXIMIZADA       SDL_WINDOWEVENT_MAXIMIZED
#define PIG_JANELA_RESTAURADA       SDL_WINDOWEVENT_RESTORED
#define PIG_JANELA_MOUSEDENTRO      SDL_WINDOWEVENT_ENTER
#define PIG_JANELA_MOUSEFORA        SDL_WINDOWEVENT_LEAVE
#define PIG_JANELA_GANHAFOCO        SDL_WINDOWEVENT_FOCUS_GAINED
#define PIG_JANELA_PERDEFOCO        SDL_WINDOWEVENT_FOCUS_LOST
#define PIG_JANELA_FECHADA          SDL_WINDOWEVENT_CLOSE

/********************************
O PIGInfoEventoTeclado é um struct contendo informações específicas sobre o evento de teclado:
acao: código que representa o evento específico (os possíveis valores podem ser vistos abaixo do struct)
tecla: código que representa a tecla pressionada ou liberada. Os possíveis valores pdoem ser vistos no final deste arquivo.
repeticao: indica se está havendo repetição no acionamento desta tecla ou não
texto: indica o que está sendo inserido
inicio: indica a posição virtual da parte selecionada do texto a ser editado
tamanhoSelecao: indica o tamanho (quantidade de caracteres) da seleção do texto a ser editado
********************************/
typedef struct PIGInfoEventoTeclado{
    int acao;
    int tecla;
    int repeticao;
    char texto[32];
    int inicio,tamanhoSelecao;
}PIGInfoEventoTeclado;
#define PIG_TECLA_PRESSIONADA       SDL_KEYDOWN
#define PIG_TECLA_LIBERADA          SDL_KEYUP
#define PIG_TECLA_EDICAO            SDL_TEXTEDITING
#define PIG_TECLA_INPUT             SDL_TEXTINPUT

/********************************
O PIGInfoEventoAudio é um struct contendo informações específicas sobre o evento de audio (encerramento de audio):
audioId: id do audio que se encerrou (se o valor for igual a PIG_AUDIO_BACKGROUND, indica que o audio de background se encerrou)
********************************/
typedef struct PIGInfoEventoAudio{
    int audioId;
}PIGInfoEventoAudio;

/********************************
O PIGStatusAudio é uma enumeração que contém os seguintes possíveis valores:
PIG_AUDIO_PARADO: indica que o audio não está tocando nem pausado
PIG_AUDIO_TOCANDO: indica que o audio está tocando
PIG_AUDIO_PAUSADO: indica que o audio está pausado
********************************/
typedef enum PIGStatusAudio{PIG_AUDIO_PARADO,
                            PIG_AUDIO_TOCANDO,
                            PIG_AUDIO_PAUSADO}
                PIGStatusAudio;

/********************************
O PIGStatusVideo é uma enumeração que contém os seguintes possíveis valores:
PIG_VIDEO_PARADO: indica que o video não está tocando nem pausado
PIG_VIDEO_TOCANDO: indica que o video está tocando
PIG_VIDEO_PAUSADO: indica que o video está pausado
********************************/
typedef enum PIGStatusVideo{PIG_VIDEO_PARADO,
                            PIG_VIDEO_TOCANDO,
                            PIG_VIDEO_PAUSADO}
                PIGStatusVideo;

/********************************
O PIGInfoEventoControlador é um struct contendo informações específicas sobre o evento de controlador (joystick):
acao: código que representa o evento específico (os possíveis valores podem ser vistos abaixo do struct)
eixo: qual dos eixos digital ou analágico, vertical ou horizontal) foi acionado
valor:
botao: qual dos botões digitais foi acionado
pecentualEixo: qual o valor percentual do eixo acionado
idControlador: qual dos controladores gerou o evento
********************************/
typedef struct PIGInfoEventoControlador{
    int acao;
    int eixo;
    int valor;
    int botao;
    float percentualEixo;
    int idControlador;
}PIGInfoEventoControlador;
#define PIG_CONTROLADOR_EIXO_MOVIDO         SDL_CONTROLLERAXISMOTION
#define PIG_CONTROLADOR_BOTAO_PRESSIONADO   SDL_CONTROLLERBUTTONDOWN
#define PIG_CONTROLADOR_BOTAO_LIBERADO      SDL_CONTROLLERBUTTONUP
#define PIG_CONTROLADOR_EIXOX_DIREITO       SDL_CONTROLLER_AXIS_RIGHTX
#define PIG_CONTROLADOR_EIXOY_DIREITO       SDL_CONTROLLER_AXIS_RIGHTY
#define PIG_CONTROLADOR_EIXOX_ESQUERDO      SDL_CONTROLLER_AXIS_LEFTX
#define PIG_CONTROLADOR_EIXOY_ESQUERDO      SDL_CONTROLLER_AXIS_LEFTY
#define PIG_CONTROLADOR_EIXOZ_DIREITO       SDL_CONTROLLER_AXIS_TRIGGERRIGHT
#define PIG_CONTROLADOR_EIXOZ_ESQUERDO      SDL_CONTROLLER_AXIS_TRIGGERLEFT

#define PIG_MAX_MENSAGEM_REDE_TCP           2048
#define PIG_TAMANHO_PACOTE_UDP              1024
#define PIG_TAMANHO_MAXIMO_HOSTNAME         50
#define PIG_DELAY_CHECK_TCP_SERVIDOR        1
#define PIG_DELAY_CHECK_TCP_CLIENTE         1
#define PIG_DELAY_CHECK_UDP                 1
typedef enum PIGTipoMensagemRede{PIG_REDE_CONEXAO,
                            PIG_REDE_MENSAGEM_TCP,
                            PIG_REDE_MENSAGEM_UDP,
                            PIG_REDE_DESCONEXAO}
                PIGTipoMensagemRede;

typedef struct PIGInfoEventoRede{
    uint8_t mensagem[PIG_MAX_MENSAGEM_REDE_TCP];
    int idSocket;
    int idSecundario;
    char host[PIG_TAMANHO_MAXIMO_HOSTNAME];
    int32_t porta;
    PIGTipoMensagemRede tipoMensagem;
}PIGInfoEventoRede;

typedef struct PIGInfoEventoVideo{
    int acao;
}PIGInfoEventoVideo;

typedef struct PIGEvento{
    PIGTipoEvento tipoEvento;
    PIGInfoEventoMouse mouse;
    PIGInfoEventoJanela janela;
    PIGInfoEventoAudio audio;
    PIGInfoEventoTeclado teclado;
    PIGInfoEventoControlador controlador;
    //InfoEventoVideo video;
    PIGInfoEventoRede rede;
}PIGEvento;
typedef __declspec(deprecated("PIG_Evento nao deve mais ser usado. Utilize PIGEvento.")) PIGEvento PIG_Evento;


//Tipo de callback genérica utilizada em diversos locais
typedef int (*PIGFuncaoSimples)(int, void*);
typedef int (*PIGFuncaoEvento)(int, PIGEvento, void*);
typedef int (*PIGFuncaoBackground)(void*);
typedef PIGCor (*PIGFuncaoPintarArea)(int, int, int, int, PIGCor, PIGCor);

//#define PIG_Teclado                 const Uint8*
typedef const Uint8* PIGTeclado;
typedef __declspec(deprecated("PIG_Teclado nao deve mais ser usado. Utilize PIGTeclado.")) PIGTeclado PIG_Teclado;


//Seção de flips de objetos
//#define PIG_Flip                    SDL_RendererFlip
typedef SDL_RendererFlip PIGFlip;
typedef __declspec(deprecated("PIG_Flip nao deve mais ser usado. Utilize PIGFlip.")) PIGFlip PIG_Flip;

#define PIG_FLIP_NENHUM             SDL_FLIP_NONE
#define PIG_FLIP_HORIZONTAL         SDL_FLIP_HORIZONTAL
#define PIG_FLIP_VERTICAL           SDL_FLIP_VERTICAL
#define PIG_FLIP_HORIZ_VERT         (PIG_Flip)(PIG_FLIP_HORIZONTAL|PIG_FLIP_VERTICAL)

//Seção de estilos

//#define PIG_Estilo                  int
typedef __declspec(deprecated("PIG_Estilo nao deve mais ser usado. Utilize PIGEvento.")) int PIG_Estilo;
typedef int PIGEstilo;
#define PIG_TOTALESTILOS            16
#define PIG_FONTE_PADRAO_NOME       "..//fontes//arial.ttf"
#define PIG_FONTE_PADRAO_TAM        36
#define PIG_FONTE_PADRAO_COR        BRANCO

#define PIG_ESTILO_NORMAL           TTF_STYLE_NORMAL
#define PIG_ESTILO_NEGRITO          TTF_STYLE_BOLD
#define PIG_ESTILO_ITALICO          TTF_STYLE_ITALIC
#define PIG_ESTILO_SUBLINHADO       TTF_STYLE_UNDERLINE
#define PIG_ESTILO_CORTADO          TTF_STYLE_STRIKETHROUGH

#define PIG_SIMBOLO_NEGRITO         '*'
#define PIG_SIMBOLO_ITALICO         '~'
#define PIG_SIMBOLO_SUBLINHADO      '_'
#define PIG_SIMBOLO_CORTADO         '#'

typedef struct PIGMetricasFonte{
    int ascent;         //quantidade de pixels acima da linha horizontal de base da letra (sempre positivo)
    int descent;        //quantidade de pixels abaixo da linha horizontal de base da letra (sempre positivo)
    int altura;         //total de pixels na altura (soma dos dois campos anteriores)
    int recuo;          //quantidade pixels entre a linha vertical de base e o primeiro pixel do eixo X da letra (pode ser negativo)
    int avanco;         //quantidade de pixels entre a linha vertical de base e o último pixel do eixo X da letra (sempre positivo)
    int largura;        //total de pixels na largura (diferença dos dois anteriores)
}PIGMetricasFonte;

//Seção de teclas

#define PIG_TECLA_UNKNOWN           0

#define PIG_TECLA_ENTER             SDL_SCANCODE_RETURN
#define PIG_TECLA_ESC               SDL_SCANCODE_ESCAPE
#define PIG_TECLA_BACKSPACE         SDL_SCANCODE_BACKSPACE
#define PIG_TECLA_TAB               SDL_SCANCODE_TAB
#define PIG_TECLA_BARRAESPACO       SDL_SCANCODE_SPACE
#define PIG_TECLA_EXCLAMACAO        SDL_SCANCODE_EXCLAIM
#define PIG_TECLA_ASPASDUPLAS       SDL_SCANCODE_QUOTEDBL
#define PIG_TECLA_HASH              SDL_SCANCODE_HASH
#define PIG_TECLA_PORCENTO          SDL_SCANCODE_PERCENT
#define PIG_TECLA_CIFRAO            SDL_SCANCODE_DOLLAR
#define PIG_TECLA_ECOMERCIAL        SDL_SCANCODE_AMPERSAND
#define PIG_TECLA_ASPASIMPLES       SDL_SCANCODE_QUOTE
#define PIG_TECLA_ABREPARENTESES    SDL_SCANCODE_LEFTPAREN
#define PIG_TECLA_FECHAPARENTESES   SDL_SCANCODE_RIGHTPAREN
#define PIG_TECLA_ASTERISCO         SDL_SCANCODE_ASTERISK
#define PIG_TECLA_MAIS              SDL_SCANCODE_PLUS
#define PIG_TECLA_VIRGULA           SDL_SCANCODE_COMMA
#define PIG_TECLA_MENOS             SDL_SCANCODE_MINUS
#define PIG_TECLA_PONTO             SDL_SCANCODE_PERIOD
#define PIG_TECLA_BARRA             SDL_SCANCODE_SLASH
#define PIG_TECLA_0                 SDL_SCANCODE_0
#define PIG_TECLA_1                 SDL_SCANCODE_1
#define PIG_TECLA_2                 SDL_SCANCODE_2
#define PIG_TECLA_3                 SDL_SCANCODE_3
#define PIG_TECLA_4                 SDL_SCANCODE_4
#define PIG_TECLA_5                 SDL_SCANCODE_5
#define PIG_TECLA_6                 SDL_SCANCODE_6
#define PIG_TECLA_7                 SDL_SCANCODE_7
#define PIG_TECLA_8                 SDL_SCANCODE_8
#define PIG_TECLA_9                 SDL_SCANCODE_9
#define PIG_TECLA_DOISPONTOS        SDL_SCANCODE_COLON
#define PIG_TECLA_PONTOEVIRGULA     SDL_SCANCODE_SEMICOLON
#define PIG_TECLA_MENORQUE          SDL_SCANCODE_LESS
#define PIG_TECLA_IGUAL             SDL_SCANCODE_EQUALS
#define PIG_TECLA_MAIORQUE          SDL_SCANCODE_GREATER
#define PIG_TECLA_INTERROGACAO      SDL_SCANCODE_QUESTION
#define PIG_TECLA_ARROBA            SDL_SCANCODE_AT

#define PIG_TECLA_ABRECOLCHETE      SDL_SCANCODE_LEFTBRACKET
#define PIG_TECLA_CONTRABARRA       SDL_SCANCODE_BACKSLASH
#define PIG_TECLA_FECHACOLCHETE     SDL_SCANCODE_RIGHTBRACKET
#define PIG_TECLA_CIRCUNFLEXO       SDL_SCANCODE_CARET
#define PIG_TECLA_TRAVESSAO         SDL_SCANCODE_UNDERSCORE
#define PIG_TECLA_GRAVE             SDL_SCANCODE_BACKQUOTE
#define PIG_TECLA_a                 SDL_SCANCODE_A
#define PIG_TECLA_b                 SDL_SCANCODE_B
#define PIG_TECLA_c                 SDL_SCANCODE_C
#define PIG_TECLA_d                 SDL_SCANCODE_D
#define PIG_TECLA_e                 SDL_SCANCODE_E
#define PIG_TECLA_f                 SDL_SCANCODE_F
#define PIG_TECLA_g                 SDL_SCANCODE_G
#define PIG_TECLA_h                 SDL_SCANCODE_H
#define PIG_TECLA_i                 SDL_SCANCODE_I
#define PIG_TECLA_j                 SDL_SCANCODE_J
#define PIG_TECLA_k                 SDL_SCANCODE_K
#define PIG_TECLA_l                 SDL_SCANCODE_L
#define PIG_TECLA_m                 SDL_SCANCODE_M
#define PIG_TECLA_n                 SDL_SCANCODE_N
#define PIG_TECLA_o                 SDL_SCANCODE_O
#define PIG_TECLA_p                 SDL_SCANCODE_P
#define PIG_TECLA_q                 SDL_SCANCODE_Q
#define PIG_TECLA_r                 SDL_SCANCODE_R
#define PIG_TECLA_s                 SDL_SCANCODE_S
#define PIG_TECLA_t                 SDL_SCANCODE_T
#define PIG_TECLA_u                 SDL_SCANCODE_U
#define PIG_TECLA_v                 SDL_SCANCODE_V
#define PIG_TECLA_w                 SDL_SCANCODE_W
#define PIG_TECLA_x                 SDL_SCANCODE_X
#define PIG_TECLA_y                 SDL_SCANCODE_Y
#define PIG_TECLA_z                 SDL_SCANCODE_Z

#define PIG_TECLA_CAPSLOCK          SDL_SCANCODE_CAPSLOCK

#define PIG_TECLA_F1                SDL_SCANCODE_F1
#define PIG_TECLA_F2                SDL_SCANCODE_F2
#define PIG_TECLA_F3                SDL_SCANCODE_F3
#define PIG_TECLA_F4                SDL_SCANCODE_F4
#define PIG_TECLA_F5                SDL_SCANCODE_F5
#define PIG_TECLA_F6                SDL_SCANCODE_F6
#define PIG_TECLA_F7                SDL_SCANCODE_F7
#define PIG_TECLA_F8                SDL_SCANCODE_F8
#define PIG_TECLA_F9                SDL_SCANCODE_F9
#define PIG_TECLA_F10               SDL_SCANCODE_F10
#define PIG_TECLA_F11               SDL_SCANCODE_F11
#define PIG_TECLA_F12               SDL_SCANCODE_F12

#define PIG_TECLA_PRINTSCREEN       SDL_SCANCODE_PRINTSCREEN
#define PIG_TECLA_SCROLLLOCK        SDL_SCANCODE_SCROLLLOCK
#define PIG_TECLA_PAUSE             SDL_SCANCODE_PAUSE
#define PIG_TECLA_INSERT            SDL_SCANCODE_INSERT
#define PIG_TECLA_HOME              SDL_SCANCODE_HOME
#define PIG_TECLA_PAGEUP            SDL_SCANCODE_PAGEUP
#define PIG_TECLA_DELETE            SDL_SCANCODE_DELETE
#define PIG_TECLA_END               SDL_SCANCODE_END
#define PIG_TECLA_PAGEDOWN          SDL_SCANCODE_PAGEDOWN
#define PIG_TECLA_DIREITA           SDL_SCANCODE_RIGHT
#define PIG_TECLA_ESQUERDA          SDL_SCANCODE_LEFT
#define PIG_TECLA_BAIXO             SDL_SCANCODE_DOWN
#define PIG_TECLA_CIMA              SDL_SCANCODE_UP

#define PIG_TECLA_NUMLOCKCLEAR      SDL_SCANCODE_NUMLOCKCLEAR
#define PIG_TECLA_KP_DIVISAO        SDL_SCANCODE_KP_DIVIDE
#define PIG_TECLA_KP_MULTIPLICAO    SDL_SCANCODE_KP_MULTIPLY
#define PIG_TECLA_KP_MENOS          SDL_SCANCODE_KP_MINUS
#define PIG_TECLA_KP_MAIS           SDL_SCANCODE_KP_PLUS
#define PIG_TECLA_KP_ENTER          SDL_SCANCODE_KP_ENTER
#define PIG_TECLA_KP_1              SDL_SCANCODE_KP_1
#define PIG_TECLA_KP_2              SDL_SCANCODE_KP_2
#define PIG_TECLA_KP_3              SDL_SCANCODE_KP_3
#define PIG_TECLA_KP_4              SDL_SCANCODE_KP_4
#define PIG_TECLA_KP_5              SDL_SCANCODE_KP_5
#define PIG_TECLA_KP_6              SDL_SCANCODE_KP_6
#define PIG_TECLA_KP_7              SDL_SCANCODE_KP_7
#define PIG_TECLA_KP_8              SDL_SCANCODE_KP_8
#define PIG_TECLA_KP_9              SDL_SCANCODE_KP_9
#define PIG_TECLA_KP_0              SDL_SCANCODE_KP_0
#define PIG_TECLA_KP_PONTO          SDL_SCANCODE_KP_PERIOD

#define PIG_TECLA_APPLICATION       SDL_SCANCODE_APPLICATION
#define PIG_TECLA_POWER             SDL_SCANCODE_POWER
#define PIG_TECLA_KP_IGUAL          SDL_SCANCODE_KP_EQUALS
#define PIG_TECLA_KP_VIRGULA        SDL_SCANCODE_KP_COMMA

#define PIG_TECLA_KP_MEMADD         SDL_SCANCODE_KP_MEMADD
#define PIG_TECLA_KP_MEMSUBTRACT    SDL_SCANCODE_KP_MEMSUBTRACT
#define PIG_TECLA_KP_MEMMULTIPLY    SDL_SCANCODE_KP_MEMMULTIPLY
#define PIG_TECLA_KP_MEMDIVIDE      SDL_SCANCODE_KP_MEMDIVIDE
#define PIG_TECLA_KP_PLUSMINUS      SDL_SCANCODE_KP_PLUSMINUS

#define PIG_TECLA_CTRLESQUERDO      SDL_SCANCODE_LCTRL
#define PIG_TECLA_SHIFTESQUERDO     SDL_SCANCODE_LSHIFT
#define PIG_TECLA_ALTESQUERDO       SDL_SCANCODE_LALT
#define PIG_TECLA_LGUI              SDL_SCANCODE_LGUI
#define PIG_TECLA_CTRLDIREITO       SDL_SCANCODE_RCTRL
#define PIG_TECLA_SHIFTDIREITO      SDL_SCANCODE_RSHIFT
#define PIG_TECLA_ALTDIREITO        SDL_SCANCODE_RALT
#define PIG_TECLA_RGUI              SDL_SCANCODE_RGUI
