//tipo de função a ser usada no acionamento do botao
//o parâmetro int devolverá à função o identificador do botão
//o parâmetro void* devolverá à função um parâetro personalizado passado ao método DefineAcao();
typedef int (*AcaoBotao)(int,void*);

class CPigBotao: public CPigComponente{

private:
    int tecla;

protected:

    int largFrame;
    AcaoBotao acao;
    void *param;
    Timer timer;
    bool botaoRepeticao;
    double tempoRepeticao;

    void SetHabilitado(bool valor){
        habilitado = valor;
        AjustaFrame();
    }

    void SetFoco(bool valor){
        temFoco = valor;
    }

    void SetAcionado(bool valor){
        acionado = valor;
        AjustaFrame();
    }

    void SetMouseOver(bool valor){
        mouseOver = valor;
        AjustaFrame();
    }

    void AjustaFrame(){
        if (visivel==false) return;
        SDL_Rect r={0,0,largFrame,altOriginal};
        if (habilitado==false){
            r.x = 3*largFrame;
        }else{
            if (acionado){
                r.x = 2*largFrame;
            }else if (mouseOver){
                r.x = largFrame;
            }
        }
        DefineFrame(r);
    }

    void TrataTimer(){
        if (timer->GetTempoDecorrido()>=tempoRepeticao){
            if (botaoRepeticao&&mouseOver&&CMouse::GetEstadoBotaoEsquerdo()==MOUSE_PRESSIONADO){
                OnMouseClick();
            }else{
                SetAcionado(false);
            }
        }
    }

    int OnMouseClick(){
        SetAcionado(true);
        timer->Reinicia(false);
        if (acao) acao(id,param);//rever se NULL é necessário
        if (audioComponente>=0) CGerenciadorAudios::Play(audioComponente);
        return PIG_SELECIONADO_TRATADO;
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
            SetHabilitado(true);//para forçar o frame correto
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

    int TrataEventoMouse(PIG_Evento evento){
        ChecaMouseOver(CMouse::PegaXY());

        if (mouseOver){
            if (habilitado==false) return PIG_SELECIONADO_DESABILITADO;
            if (visivel==false) return PIG_SELECIONADO_INVISIVEL;
            if(evento.mouse.acao==MOUSE_PRESSIONADO && evento.mouse.botao == MOUSE_ESQUERDO) return OnMouseClick();
            return PIG_SELECIONADO_MOUSEOVER;
        }

        return PIG_NAO_SELECIONADO;
    }

    int TrataEventoTeclado(PIG_Evento evento){
        if (evento.teclado.acao==TECLA_PRESSIONADA && evento.teclado.tecla==tecla)
            if (timer->GetTempoDecorrido()>tempoRepeticao) return OnMouseClick();

        return 0;
    }

    void DefineAtalho(int teclaAtalho){
        tecla = teclaAtalho;
    }

    void DefineTempoRepeticao(double segundos){
        tempoRepeticao = segundos;
    }

    void DefineBotaoRepeticao(bool repeticao){
        botaoRepeticao = repeticao;
    }

    int TrataEvento(PIG_Evento evento){
        if (evento.tipoEvento == EVENTO_MOUSE)    return TrataEventoMouse(evento);
        if (evento.tipoEvento == EVENTO_TECLADO) return TrataEventoTeclado(evento);

        return PIG_NAO_SELECIONADO;
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
