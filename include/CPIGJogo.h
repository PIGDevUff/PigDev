#ifndef _CPIGJOGO_
#define _CPIGJOGO_

#include "CPIGAtributos.h"
#include "CPIGMouse.h"
#include "CPIGOffscreenRenderer.h"

class CPIGJogo: public CPIGAtributos{

private:

    PIGEvento ultimoEvento;
    PIGTeclado teclado;
    bool rodando;
    string diretorioAtual;
    PIGOffscreenRenderer offRenderer;

public:

    CPIGJogo():CPIGAtributos(){
        if (SDL_WasInit(0) > 0){
            cout<<"O jogo ja foi inicializado anteriormente!!!"<<endl;
        }else{
            if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
                cout<<"A SDL nao pode ser iniciaizada!!! Erro: "<<SDL_GetError()<<endl;
            }else{
                rodando = true;
                teclado = SDL_GetKeyboardState(NULL);
                offRenderer = NULL;
                diretorioAtual = PIGGetDiretorioAtual();
            }
        }
    }

    virtual ~CPIGJogo(){
        if (offRenderer) delete offRenderer;
    }

    PIGEvento PegaEvento(){
        SDL_Event event;

        int resp = SDL_PollEvent(&event);
        if (resp){
            if (event.type==SDL_QUIT)
                rodando = false;
            //if (event.type) printf("Tipo: %d\n",event.type);
            switch(event.type){
            case SDL_QUIT:
                rodando = false; break;

            case SDL_USEREVENT:
                if (event.user.code==PIG_EVENTO_AUDIO){
                    ultimoEvento.tipoEvento = PIG_EVENTO_AUDIO;
                    ultimoEvento.audio.audioId = *((int*)event.user.data1);
                }else if (event.user.code==PIG_EVENTO_REDE){
                    ultimoEvento.tipoEvento = PIG_EVENTO_REDE;
                    ultimoEvento.rede = *((PIGInfoEventoRede*)event.user.data1);
                }
                free(event.user.data1);
                break;

            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
                ultimoEvento.tipoEvento = PIG_EVENTO_MOUSE;
                ultimoEvento.mouse.acao = event.type; //MOUSE_PRESSIONADO(SDL_MOUSEBUTTODOWN) ou MOUSELIBERADO(SDL_MOUSEBUTTONUP);
                ultimoEvento.mouse.botao= event.button.button;
                ultimoEvento.mouse.numeroJanela = event.window.windowID-PIG_JANELA_INICIAL;
                ultimoEvento.mouse.cliques = event.button.clicks;
                //ultimoEvento.mouse.posX = event.button.x;
                SDL_GetMouseState(&ultimoEvento.mouse.posX,&ultimoEvento.mouse.posY);
                //ultimoEvento.mouse.posY = CGerenciadorJanelas::GetAltura(ultimoEvento.mouse.numeroJanela) - event.button.y-1;
                ultimoEvento.mouse.posY = pigGerJanelas.GetElemento(ultimoEvento.mouse.numeroJanela)->GetAltura() - ultimoEvento.mouse.posY-1;
                //CGerenciadorJanelas::GetJanela(ultimoEvento.mouse.numeroJanela)->GetCamera()->ConverteCoordenadaWorldScreen(ultimoEvento.mouse.posX,ultimoEvento.mouse.posY,&ultimoEvento.mouse.worldX,&ultimoEvento.mouse.worldY);
                pigMouse.ProcessaEvento(ultimoEvento);
                break;

            case SDL_MOUSEMOTION:
                ultimoEvento.tipoEvento = PIG_EVENTO_MOUSE;
                ultimoEvento.mouse.acao = PIG_MOUSE_MOVIDO;
                ultimoEvento.mouse.numeroJanela = event.window.windowID-PIG_JANELA_INICIAL;
                SDL_GetMouseState(&ultimoEvento.mouse.posX,&ultimoEvento.mouse.posY);
                //ultimoEvento.mouse.posX = event.motion.x;
                ultimoEvento.mouse.posY = pigGerJanelas.GetElemento(ultimoEvento.mouse.numeroJanela)->GetAltura() - ultimoEvento.mouse.posY-1;
                ultimoEvento.mouse.relX = event.motion.xrel;
                ultimoEvento.mouse.relY = -event.motion.yrel;
                //printf("%d\n",ultimoEvento.mouse.numeroJanela);
                //CGerenciadorJanelas::GetJanela(ultimoEvento.mouse.numeroJanela)->GetCamera()->ConverteCoordenadaScreenWorld(ultimoEvento.mouse.posX,ultimoEvento.mouse.posY,&ultimoEvento.mouse.worldX,&ultimoEvento.mouse.worldY);
                //int mx,my;
                //SDL_GetMouseState(&ultimoEvento.mouse.posX,&ultimoEvento.mouse.posY);
                //printf("y %d  my %d\n",event.motion.y,my);
                pigMouse.ProcessaEvento(ultimoEvento);
                //CMouse::Move(ultimoEvento.mouse.posX, ultimoEvento.mouse.posY);
                break;

            case SDL_MOUSEWHEEL:
                ultimoEvento.tipoEvento = PIG_EVENTO_MOUSE;
                ultimoEvento.mouse.acao = PIG_MOUSE_RODINHA;
                ultimoEvento.mouse.numeroJanela = event.window.windowID-PIG_JANELA_INICIAL;
                ultimoEvento.mouse.relX = event.wheel.x;
                ultimoEvento.mouse.relY = event.wheel.y;
                pigMouse.ProcessaEvento(ultimoEvento);
                break;

            case SDL_KEYDOWN:
            case SDL_KEYUP:
                ultimoEvento.tipoEvento = PIG_EVENTO_TECLADO;
                ultimoEvento.teclado.acao = event.type; //TECLA_PRESSIONADA(SDL_KEYDOWN) ou TECLA_LIBERADA(SDL_KEYUP);
                ultimoEvento.teclado.tecla = event.key.keysym.scancode;
                ultimoEvento.teclado.repeticao = event.key.repeat;
                break;

            case SDL_TEXTEDITING:
                ultimoEvento.tipoEvento = PIG_EVENTO_TECLADO;
                ultimoEvento.teclado.acao = PIG_TECLA_EDICAO;
                ultimoEvento.teclado.inicio = event.edit.start;
                ultimoEvento.teclado.tamanhoSelecao = event.edit.length;
                strcpy(ultimoEvento.teclado.texto,event.edit.text);
                break;

            case SDL_TEXTINPUT:
                ultimoEvento.tipoEvento = PIG_EVENTO_TECLADO;
                ultimoEvento.teclado.acao = PIG_TECLA_INPUT;
                strcpy(ultimoEvento.teclado.texto,event.edit.text);
                break;

            case SDL_WINDOWEVENT:
                if (event.window.event==PIG_JANELA_FECHADA){
                    pigGerJanelas.GetElemento(event.window.windowID-PIG_JANELA_INICIAL)->Fecha();
                }
                ultimoEvento.tipoEvento = PIG_EVENTO_JANELA;
                ultimoEvento.janela.acao = event.window.event;
                ultimoEvento.janela.numeroJanela = event.window.windowID-PIG_JANELA_INICIAL;
                ultimoEvento.janela.dado1 = event.window.data1;
                ultimoEvento.janela.dado2 = event.window.data2;
                break;

            case SDL_CONTROLLERBUTTONDOWN:
            case SDL_CONTROLLERBUTTONUP:
                ultimoEvento.tipoEvento = PIG_EVENTO_CONTROLADOR;
                ultimoEvento.controlador.acao = event.type; //CONTROLADOR_BOTAO_PRESSIONADO(SDL_CONTROLLERBUTTONDOWN) ou CONTROLADOR_BOTAO_LIBERADO(SDL_CONTROLLERBUTTONUP);
                ultimoEvento.controlador.botao = event.cbutton.button;
                ultimoEvento.controlador.idControlador = event.cdevice.which;
                SDL_PollEvent(&event);
                break;

            case SDL_CONTROLLERAXISMOTION:
            //case SDL_JOYAXISMOTION:
                ultimoEvento.tipoEvento = PIG_EVENTO_CONTROLADOR;
                ultimoEvento.controlador.acao = PIG_CONTROLADOR_EIXO_MOVIDO;
                ultimoEvento.controlador.eixo = event.caxis.axis;
                ultimoEvento.controlador.valor = event.caxis.value;
                ultimoEvento.controlador.percentualEixo = 1.0f*ultimoEvento.controlador.valor/(1<<15);
                ultimoEvento.controlador.idControlador = event.cdevice.which;
                SDL_PollEvent(&event);
                break;
            /*default:
                    if (event.type){
                        printf("Evento: %d\n",event.type);
                    }
            */
            }
        }else ultimoEvento.tipoEvento = PIG_EVENTO_NULO;

        return ultimoEvento;
    }

    inline PIGTeclado PegaTeclado(){
        return teclado;
    }

    inline void IniciaInputTextoTela(){
        SDL_StartTextInput();
    }

    inline void EncerraInputTextoTela(){
        SDL_StopTextInput();
    }

    inline bool GetRodando(){
        return rodando;
    }

    string GetDiretorioAtual(){
        return diretorioAtual;
    }

    inline void PreparaOffScreenRenderer(int altura, int largura){
        if (offRenderer) delete offRenderer;
        offRenderer = new CPIGOffscreenRenderer(altura,largura);
    }

    inline PIGOffscreenRenderer GetOffScreenRender(){
        if (offRenderer==NULL) throw CPIGErroPonteiro("OffScreenRenderer(Necessario definir primeiro o tamanho do renderizador)");
        return offRenderer;
    }

};
CPIGJogo pigJogo;
#endif // _CPIGJOGO_
