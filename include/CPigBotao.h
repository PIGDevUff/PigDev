//tipo de função a ser usada no acionamento do botao
//o parâmetro int devolverá à função o identificador do botão
//o parâmetro void* devolverá à função um parâetro personalizado passado ao método DefineAcao();
typedef int (*AcaoBotao)(int,void*);

class CPigBotao: public CPigComponente{

private:

    int tecla;
    int largFrame;
    AcaoBotao acao;
    void *param;
    Timer timer;
    bool botaoRepeticao;
    double tempoRepeticao;

    void TrataTimer(){
        if (timer->GetTempoDecorrido()>=tempoRepeticao){
            if (estado==COMPONENTE_ACIONADO){
                if (agoraOn){
                    if (botaoRepeticao&&CMouse::GetEstadoBotaoEsquerdo()==MOUSE_PRESSIONADO){
                        OnMouseClick();
                    }else DefineEstado(COMPONENTE_MOUSEOVER);
                }else DefineEstado(COMPONENTE_NORMAL);
            }
        }
    }

    int OnMouseClick(){
        DefineEstado(COMPONENTE_ACIONADO);
        timer->Reinicia(false);
        if (acao) acao(id,param);//rever se NULL é necessário
        if (audioComponente>=0) CGerenciadorAudios::Play(audioComponente);
        return SELECIONADO_TRATADO;
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

    CPigBotao LeArquivoParametros(std::string nomeArqParam){

        std::ifstream arquivo;
        int idComponente,px,py,altura,largura,retiraFundo = 0,janela = 0;

        std::string nomeArq = "",palavra;

        arquivo.open(nomeArqParam);
        //if(!arquivo.is_open()) printf("falha ler arquivo\n");
        //formato "x valor"
        while(!arquivo.eof()){
            arquivo >> palavra;
            if(palavra == "idComponente") arquivo >> idComponente;
            if(palavra == "px") arquivo >> px;
            if(palavra == "py") arquivo >> py;
            if(palavra == "altura") arquivo >> altura;
            if(palavra == "largura") arquivo >> largura;
            if(palavra == "nomeArq") arquivo >> nomeArq;
            if(palavra == "retiraFundo") arquivo >> retiraFundo;
            if(palavra == "janela") arquivo >> janela;
        }
        arquivo.close();

       // std::cout<<idComponente<<" "<<px<<" "<<py<<" "<<altura<<" "<<largura<<" "<<nomeArq<<" "<<retiraFundo<<" "<<janela<<std::endl;

        return CPigBotao(idComponente,px,py,altura,largura,nomeArq,retiraFundo,janela);
    }

public:

    CPigBotao(int idComponente,int px, int py, int alt,int larg,std::string nomeArq, int retiraFundo=1,int janela=0):
        CPigComponente(idComponente,px,py,alt,larg,nomeArq,retiraFundo,janela){
            tecla = TECLA_ENTER;//sem tecla de atalho
            acao = NULL;//não tem ação registrada
            param = NULL;//não tem parâmetro associado à ação
            largFrame = largOriginal/4;
            DefineEstado(COMPONENTE_NORMAL);
            tempoRepeticao = 0.2;
            botaoRepeticao = false;
            SetPosicaoPadraoLabel(PIG_COMPONENTE_CENTRO_CENTRO);
            timer = new CTimer(false);
        }

    CPigBotao(std::string nomeArqParam):CPigBotao(LeArquivoParametros(nomeArqParam)){}

    ~CPigBotao(){
        delete timer;
    }

    void DefineAcao(AcaoBotao funcao,void *parametro){
        acao = funcao;
        param = parametro;
    }

    int TrataEventoMouse(PIG_Evento evento)override{
        SDL_Point p;
        CMouse::PegaXY(p.x,p.y);
        MouseSobre(p.x,p.y);

        if (agoraOn && evento.mouse.acao==MOUSE_PRESSIONADO){
            if (habilitado==false) return SELECIONADO_DESABILITADO;
            if (visivel==false) return SELECIONADO_INVISIVEL;
            if(evento.mouse.botao == MOUSE_ESQUERDO) return OnMouseClick();
        }

        return NAO_SELECIONADO;
    }

    int TrataEventoTeclado(PIG_Evento evento)override{
        if (evento.teclado.acao==TECLA_PRESSIONADA && evento.teclado.tecla==tecla)
            if (timer->GetTempoDecorrido()>tempoRepeticao) return OnMouseClick();

        return 0;
    }


    void DefineAtalho(int teclaAtalho){
        tecla = teclaAtalho;
    }

    void DefineCursor(PIG_EstadoComponente estado, int indiceMouse){
        //mouse[estado]=indiceMouse;
    }

    void DefineTempoRepeticao(double segundos){
        tempoRepeticao = segundos;
    }

    void DefineBotaoRepeticao(bool repeticao){
        botaoRepeticao = repeticao;
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
//NAO_SELECIONADO,SELECIONADO_INVISIVEL,SELECIONADO_DESABILITADO,SELECIONADO_TRATADO
    int TrataEvento(PIG_Evento evento){
        SDL_Point p;
        CMouse::PegaXY(p.x,p.y);
        MouseSobre(p.x,p.y);

        if(evento.tipoEvento == EVENTO_MOUSE && agoraOn){
            return TrataEventoMouse(evento);
        }
        if (evento.tipoEvento == EVENTO_TECLADO) return TrataEventoTeclado(evento);

        return NAO_SELECIONADO;
    }

    int Desenha(){

        if (visivel==false) return 0;

        TrataTimer();

        SDL_RenderCopyEx(renderer, text, &frame,&dest,-angulo,&pivoRelativo,flip);

        DesenhaLabel();
        EscreveHint();

        return 1;
    }

};

typedef CPigBotao *PigBotao;
