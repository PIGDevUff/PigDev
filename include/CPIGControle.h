#ifndef _CPIGCONTROLE_
#define _CPIGCONTROLE_

class CPIGControle{

private:

    int id;
    SDL_GameController *ctrl;
    SDL_Joystick *joy;
    int qtdEixos,qtdBotoes;
    string nome;

public:

    CPIGControle(int idControle){
        if (SDL_IsGameController(idControle)) {
            printf("Controle da posicao \'%d\' compativel\n", idControle);
            ctrl = SDL_GameControllerOpen(idControle);
            joy = SDL_GameControllerGetJoystick(ctrl);
            id = idControle;
            qtdEixos = SDL_JoystickNumAxes(joy);
            qtdBotoes = SDL_JoystickNumButtons(joy);
            nome.assign(SDL_JoystickName(joy));
            printf("Eixos: %d\n",qtdEixos);
            printf("Botoes: %d\n",qtdBotoes);
            printf("Nome: %s\n",nome.c_str());
        } else {
            printf("Controle da posicao \'%d\' incompativel\n", idControle);
        }
    }

    ~CPIGControle(){
        SDL_GameControllerClose(ctrl);
    }

    int BotaoPressionado(int botao){
        return SDL_GameControllerGetButton(ctrl,(SDL_GameControllerButton)botao);
    }

    int EixoAcionado(int eixo){
        return SDL_GameControllerGetAxis(ctrl,(SDL_GameControllerAxis)eixo);
    }

    float EixoAcionadoPercentual(int eixo){
        return SDL_GameControllerGetAxis(ctrl,(SDL_GameControllerAxis)eixo)/32768.0f;
    }

    int GetQtdEixos(){
        return qtdEixos;
    }

    int GetQtdBotoes(){
        return qtdBotoes;
    }

    string GetNome(){
        return nome;
    }

};

typedef CPIGControle *PIGControle;
#endif // _CPIGCONTROLE_
