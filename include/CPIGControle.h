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
            id = idControle;
            cout<<"Controle da posicao "<<id<<" compativel!"<<endl;
            ctrl = SDL_GameControllerOpen(id);
            joy = SDL_GameControllerGetJoystick(ctrl);
            qtdEixos = SDL_JoystickNumAxes(joy);
            qtdBotoes = SDL_JoystickNumButtons(joy);
            nome.assign(SDL_JoystickName(joy));
            cout<<"Eixos: "<<qtdEixos<<endl;
            cout<<"Botoes: "<<qtdBotoes<<endl;
            cout<<"Nome: "<<nome<<endl;
        } else {
            cout<<"Controle da posicao "<<id<<" incompativel!!"<<endl;
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
