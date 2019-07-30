class CControle{

private:

int id;
SDL_GameController *ctrl;
SDL_Joystick *joy;
int qtdEixos,qtdBotoes;
char nome[50];

public:


CControle(int idControle){
    if (SDL_IsGameController(idControle)) {
        printf("Index \'%i\' is a compatible controller, named \'%s\'\n", idControle, SDL_GameControllerNameForIndex(idControle));
        ctrl = SDL_GameControllerOpen(idControle);
        joy = SDL_GameControllerGetJoystick(ctrl);
        id = idControle;
        qtdEixos = SDL_JoystickNumAxes(joy);
        qtdBotoes = SDL_JoystickNumButtons(joy);
        strcpy(nome,SDL_JoystickName(joy));
        printf("Axes: %d\n",qtdEixos);
        printf("Botoes: %d\n",qtdBotoes);
        printf("Nome: %s\n",nome);
    } else {
        printf("Index \'%i\' is not a compatible controller.\n", idControle);
    }
}

~CControle(){
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

void GetNome(char *nomeControle){
    strcpy(nomeControle,nome);
}

};

typedef CControle *Controle;
