class CPigCaixaTexto: public CPigComponente{

private:

    int OnMouseOn(){}
    int OnMouseOff(){}

    bool cursorExibido;
    int maxCaracteres;
    bool somenteNumeros;
    PIG_Cor corCursor;
    Timer timer;

    //desenha o cursor
    void DesenhaCursor(){
        if (estado==COMPONENTE_EDITANDO){
            if (cursorExibido){
                DesenhaLinhaSimples(xCursor,yCursor,xCursor,yCursor+GetTamanhoFonte(fonteTexto),corCursor,idJanela);
            }
            if (timer&&timer->GetTempoDecorrido()>1){
                cursorExibido = !cursorExibido;
                timer->Reinicia(false);
            }
        }
    }

    //trata os eventos de mouse possíveis
    int EventosMouse(PIG_Evento evento,SDL_Point p){
        if (evento.mouse.acao == MOUSE_PRESSIONADO){
            if (evento.mouse.botao == MOUSE_ESQUERDO)
                return TrataMouseBotaoEsquerdo(p);
            else if (evento.mouse.botao == MOUSE_DIREITO)
                return TrataMouseBotaoDireito(evento,p);
        }else if (evento.mouse.acao == MOUSE_RODINHA)
            return TrataMouseRodinha(evento);
    }

    //verifica se o evento ocorre dentro da área do componente
    int TrataEventoMouse(PIG_Evento evento){
        SDL_Point p;
        CMouse::PegaXY(p.x,p.y);
        SDL_Rect r = {x+margemHorEsq,y,larg-(margemHorEsq + margemHorDir),alt};

        if (SDL_PointInRect(&p,&r)){
            return EventosMouse(evento,p);
        }
        return 0;
    }

    //trata teclas de movimentação do cursor
    virtual int TrataTeclasEspeciais(PIG_Evento evento){
        switch (evento.teclado.tecla){
            case TECLA_BACKSPACE:
                RetiraTextoBackSpace();return 1;
            case TECLA_DELETE:
                RetiraTextoDelete();return 1;
            case TECLA_DIREITA:
                AvancaCursor();return 1;
            case TECLA_ESQUERDA:
                VoltaCursor();return 1;
            case TECLA_CIMA:
                SobeCursor();return 1;
            case TECLA_BAIXO:
                DesceCursor();return 1;
            case TECLA_ENTER:
                PulaLinha();return 1;
        }
        return 0;
    }

    //trata os diversos tipos de eventos de teclado que podem ocorrer
    int TrataEventoTeclado(PIG_Evento evento){
        if (evento.teclado.acao==TECLA_EDICAO) return 1;
        if (evento.teclado.acao==TECLA_INPUT){//caracteres normais
            if (AdicionaTexto((char*)ConverteString(evento.teclado.texto).c_str())){
                if (audioComponente>=0) PlayAudio(audioComponente);
                return 1;
            }
            return 0;
        }

        if (evento.teclado.acao==TECLA_PRESSIONADA){//teclas especiais
            TrataTeclasEspeciais(evento);
            return 1;
        }
        return 0;
    }


protected:

    std::string texto;
    int fonteTexto;
    int posCursor;
    int xBase,xCursor,yCursor,yBase;
    int xBaseOriginal,yBaseOriginal;
    int margemHorEsq,margemHorDir,margemVertCima,margemVertBaixo;

    virtual void DesenhaElementosEspecificos() =0;//pure virtual, porque cada classe derivada vai desenhar coisas diferentes

    virtual void AjustaAlinhamento() =0;//pure virtual, porque cada classe derivada vai fazer ajustes diferentes

    //posiciona o cursor no eixo X (necessário, pois pode haver texto "escondido" à esquerda)
    void AjustaBaseTextoEixoX(int largParcial){
        while(xCursor>x+larg-margemHorDir){
            xBase-=5;
            xCursor = xBase + largParcial;
        }
        while(xCursor < x+margemHorEsq){
            xBase+=5;
            xCursor = xBase + largParcial;
        }
    }

    //posiciona o cursor uma posição à frente
    int AvancaCursor(){
        if (posCursor>=texto.size()) return 0;//não tem caracter na frente do cursor
        posCursor++;
        AjustaAlinhamento();
        return 1;
    }

    //posiciona o cursor uma posição atrás
    int VoltaCursor(){
        if (posCursor==0) return 0;//não tem caractere atrés do cursor
        posCursor--;
        AjustaAlinhamento();
        return 1;
    }

    //reira um caracter com a tecla backspace
    int RetiraTextoBackSpace(){
        if (texto.size()==0||posCursor==0) return 0;//não tem caractere atrés do cursor

        texto.erase(posCursor-1,1);//retira o caracter imediatamente atrás do cursor e retrocede com ele
        VoltaCursor();

        if (audioComponente>=0) PlayAudio(audioComponente);
        return 1;
    }

    //retira um caracter com a tecla delete
    int RetiraTextoDelete(){
        if (texto.size()==0||posCursor>=texto.size()) return 0;//não tem caracter na frente do cursor

        texto.erase(posCursor,1);//retira o caracter imediatamente a frente do cursor

        if (audioComponente>=0) PlayAudio(audioComponente);
        return 1;
    }

    virtual int SobeCursor() = 0;

    virtual int DesceCursor() = 0;

    virtual int PulaLinha() = 0;

    virtual std::string GetTextoVisivel() =0;//pure virtual, porque cada classe derivada vai retornar um texto de forma diferente

    //adiciona um texto (caracter ou string) na posição indicada pelo cursor (se possível)
    int AdicionaTexto(char *frase){
        if (texto.size()+strlen(frase)>maxCaracteres) return 0;//ultrapassa o limite máximo de carcteres
        if (somenteNumeros&&!SomenteNumeros(frase)) return 0;//não é número

        texto.insert(posCursor,frase);

        AvancaCursor();
        return 1;
    }

    //converte caracteres especiais, como acentos por exemplo
    std::string ConverteString(char *str){
        std::string resp(str);
        if (strlen(str)>1){
            if ((uint8_t)str[0]==195){
                resp = str[1]+64;
            }else if ((uint8_t)str[0]==194){
                resp = str[1];
            }

        }
        return resp;
    }

    virtual int TrataMouseBotaoDireito(PIG_Evento evento,SDL_Point p) =0; //cada classe vai poder definir o que fazer com o botão direito

    virtual int TrataMouseRodinha(PIG_Evento evento) =0; //cada classe vai poder definir o que fazer com a rodinha

    //o botao esquerdo faz com que a edição do trexto comece ou que o cursor seja reposicionado
    virtual int TrataMouseBotaoEsquerdo(SDL_Point p,int inicioLinha = 0){
        int delta = p.x-xBase;
        int largParcial = 0;
        int largUltimaLetra = 0;
        std::string textoBase = GetTextoVisivel();

        for (int i=inicioLinha;i<=textoBase.size();i++){
            std::string aux;

            aux.assign(textoBase,inicioLinha,i - inicioLinha);

            largParcial += CalculaLarguraPixels((char*)aux.c_str(),fonteTexto);

            if (delta<largParcial-largUltimaLetra){
                posCursor = i-1;
                AjustaAlinhamento();
                return 1;
            }

            largUltimaLetra = largParcial;
        }

        posCursor = texto.size();

        AjustaAlinhamento();
        if (estado==COMPONENTE_NORMAL)
            DefineEstado(COMPONENTE_EDITANDO);

        return 1;
    }


public:

    CPigCaixaTexto(int idComponente,int px, int py, int alt,int larg,char *nomeArq,int fonteDoTexto = 0,int fonteDoLabel = 0,int maxCars = 200,bool apenasNumeros=false,int retiraFundo=1,int janela=0):
        CPigComponente(idComponente,px,py,alt,larg,nomeArq,retiraFundo,janela){
        margemHorEsq = margemHorDir = margemVertCima = margemVertBaixo = 30;
        posLabel = COMPONENTE_ESQUERDA;//posição padrão do label
        fonteLabel = fonteDoLabel;
        fonteTexto = fonteDoTexto;//fonte padrão
        posCursor = 0;//cursor no início do texto
        cursorExibido = true;
        timer = NULL;//o timer só será criado quando estiver editando
        estado = COMPONENTE_NORMAL;
        maxCaracteres = maxCars;
        texto="";
        label="";
        somenteNumeros = apenasNumeros;
        corCursor = PRETO;
    }

    ~CPigCaixaTexto(){
        if (timer) delete timer;
    }

    //desenha o componente completo
    int Desenha() override{
        //imagem de fundo
        SDL_RenderCopyEx(renderer, text, &frame,&dest,-angulo,&pivoRelativo,flip);

        //SDL_Rect r={x+margemHor-2,altJanela-y-alt,larg-2*(margemHor-2),alt};
        SDL_Rect r={x+margemHorEsq,altJanela-y-alt+margemVertCima,larg-(margemHorEsq+margemHorDir),alt-(margemVertBaixo+margemVertCima)+1};
        SDL_RenderSetClipRect(renderer,&r);

        DesenhaElementosEspecificos();//cada classe derivada pode desenhar elementos específicos
        DesenhaCursor();//desenha o cursor (se estiver em edição)

        //desbloqueia o desenho fora da area do componente
        SDL_RenderSetClipRect(renderer,NULL);

        DesenhaLabel();
        return 1;
    }

    virtual void SetMargens(int horEsq,int horDir, int vertBaixo,int vertCima) =0;//cada classe derivada vai definir as margens de forma diferente

    //define o texto a ser mostrado no componente
    int SetTexto(std::string frase){
        texto = frase;
        posCursor=0;
        return 1;
    }

    //recupera o texto armazenado no componente
    std::string GetTexto(){
        return texto;
    }

    //trata eventos relativos ao componente
    int TrataEvento(PIG_Evento evento) override{
        if (evento.tipoEvento==EVENTO_MOUSE){
            return TrataEventoMouse(evento);
        }else if (evento.tipoEvento==EVENTO_TECLADO){
            return TrataEventoTeclado(evento);
        }
    }

    //define a cor do cursor
    void SetCorCursor(PIG_Cor cor){
        corCursor = cor;
    }

    //define o estado do componente
    void DefineEstado(PIG_EstadoComponente estadoComponente){
        estado = estadoComponente;
        if (estado==COMPONENTE_EDITANDO){
            timer = new CTimer(false);
            SDL_StartTextInput();
        }else if (estado==COMPONENTE_NORMAL){
            SDL_StopTextInput();
            if (timer) delete timer;
        }
    }

    //reposiciona o componente
    void Move(int nx, int ny){
        CPigComponente::Move(nx,ny);
        AjustaAlinhamento();
    }

};

typedef CPigCaixaTexto *PigCaixaTexto;
