typedef int (*AcaoBotao)(int,void*);

class CPigBotao: public CPigComponente{

private:

int tecla;
int largFrame;
Timer timer;
AcaoBotao acao;
void *param;

int TrataMouse(int acao){
    if (acao==MOUSE_PRESSIONADO){
        if (agoraOn){
            OnMouseClick();
            return 1;
        }
    }
    return 0;
}

int TrataTeclado(PIG_Evento evento){
    if (evento.teclado.acao==TECLA_PRESSIONADA){
        if (evento.teclado.tecla==tecla){
            OnMouseClick();
            return 1;
        }
    }
    return 0;
}

int OnMouseOn(){
    if (estado==COMPONENTE_DESABILITADO) return 0;
    DefineEstado(COMPONENTE_MOUSEOVER);
    return 1;
}

int OnMouseOff(){
    if (estado==COMPONENTE_DESABILITADO) return 0;
    DefineEstado(COMPONENTE_NORMAL);
    return 1;
}

int OnMouseClick(){
    DefineEstado(COMPONENTE_ACIONADO);
    if (timer) delete timer;
    timer = new CTimer(false);
    if (acao) acao(id,param);//rever se NULL é necessário
    if (audioComponente>=0) PlayAudio(audioComponente);
}

public:

CPigBotao(int idComponente,int px, int py, int alt,int larg,char *nomeArq, int retiraFundo=1,int janela=0):
    CPigComponente(idComponente,px,py,alt,larg,nomeArq,retiraFundo,janela){
    label = NULL;//sem mensagem nem hint
    tecla = -1;//sem tecla de atalho
    largFrame = largOriginal/4;//a imgem deve ter 4 frames (normal,mouse_over,acionado,desabilitado)
    timer = NULL;//sem timer para "soltar" o botão
    acao = NULL;//não tem ação registrada
    param = NULL;//não tem parâmetro associado à ação
    SetPosicaoPadraoLabel(COMPONENTE_CENTRO);
    DefineEstado(COMPONENTE_NORMAL); //começa normal
}

~CPigBotao(){
    if (timer)
        delete timer;
}

void DefineAcao(AcaoBotao funcao,void *parametro){
    acao = funcao;
    param = parametro;
}

void DefineAtalho(int teclaAtalho){
    tecla = teclaAtalho;
}

void DefineCursor(PIG_EstadoComponente estado, int indiceMouse){
    //mouse[estado]=indiceMouse;
}

void DefineEstado(PIG_EstadoComponente estadoComponente){
    SDL_Rect r={0,0,largFrame,altOriginal};
    estado = estadoComponente;
    switch(estado){
    case COMPONENTE_NORMAL:
        break;
    case COMPONENTE_MOUSEOVER:
        r.x += largFrame;
        break;
    case COMPONENTE_ACIONADO:
        r.x += 2*largFrame;
        break;
    case COMPONENTE_DESABILITADO:
        r.x += 3*largFrame;
        break;
    }
    DefineFrame(r);
}

int TrataEvento(PIG_Evento evento){
    if (estado==COMPONENTE_DESABILITADO||estado==COMPONENTE_INVISIVEL)
        return -1;
    if (evento.tipoEvento==EVENTO_MOUSE){
        return TrataMouse(evento.mouse.acao);
    }else if (evento.tipoEvento==EVENTO_TECLADO){
        return TrataTeclado(evento);
    }
}

int Desenha(){
    if (estado==COMPONENTE_INVISIVEL) return 0;
    if (timer){
        if (timer->GetTempoDecorrido()<0.2){
            DefineEstado(COMPONENTE_ACIONADO);
        }else{
            delete timer;
            timer = NULL;
            if (agoraOn) DefineEstado(COMPONENTE_MOUSEOVER);
            else DefineEstado(COMPONENTE_NORMAL);
        }
    }

    SDL_RenderCopyEx(renderer, text, &frame,&dest,-angulo,&pivoRelativo,flip);
    DesenhaLabel();

    //int mx,my;
    //CMouse::PegaXY(mx,my);
    //EscreveHint(mx,my);

    return 1;
}

};

typedef CPigBotao *PigBotao;
