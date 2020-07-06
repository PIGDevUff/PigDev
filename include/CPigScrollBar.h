typedef enum{HORIZONTAL,VERTICAL}Pig_Orientacao;

//tipo de função a ser usada em alterações na posição do handle da barra
//o parâmetro int devolverá à função o identificador do botão
//o parâmetro double devolverá à função a porcentagem atual da barra
//o parâmetro void* devolverá à função um parâetro personalizado passado ao método DefineAcao();
typedef int (*AcaoScroll)(int,double,void*);

class CPigScrollBar : public CPigComponente{

    int vMin,vAtual,vMax;
    double porcentagemConcluida;
    Pig_Orientacao orientacao;
    int xOriginal,yOriginal;
    CPigBotao *botao1,*botao2,*handle;
    int largBotoes,largHandle,largUtil;
    int deltaBotao,deltaRodinha,deltaTeclado;
    int comprimento,largura;
    void *param;
    AcaoScroll acao;

    static int AcaoSetas(int idBotao, void* pontObjeto){
        CPigScrollBar *scroll = (CPigScrollBar*) pontObjeto;
        if (idBotao==scroll->id+1)
            scroll->AvancaHandle(scroll->vAtual-scroll->deltaBotao);
        else if (idBotao==scroll->id+2)
            scroll->AvancaHandle(scroll->vAtual+scroll->deltaBotao);
    }

    void TrataClickTrilha(int px,int py){
        if(orientacao == HORIZONTAL) porcentagemConcluida = ( (px - largHandle/2) - x)/(x + largUtil  - x);
        else porcentagemConcluida = ( (py - largHandle/2) - y)/(y + largUtil  - y);

        AvancaHandle(porcentagemConcluida*(vMax - vMin) + vMin);
    }

    void TrataBotoes(PIG_Evento evento){
        if(botao1 && botao2){
            botao1->TrataEvento(evento);
            botao2->TrataEvento(evento);
        }
    }

    void TrataRodinha(PIG_Evento evento){
        if(evento.mouse.acao == MOUSE_RODINHA){
            if(evento.mouse.relY == 1){
                AvancaHandle(vAtual + deltaRodinha);
            }else{
                AvancaHandle(vAtual - deltaRodinha);
            }
        }
    }

    int TrataMouse(PIG_Evento evento){
        SDL_Point p;
        CMouse::PegaXY(p.x,p.y);
        MouseSobre(p.x,p.y);

        if (agoraOn){
            botao1->TrataEvento(evento);
            botao2->TrataEvento(evento);

            if(orientacao == VERTICAL) TrataRodinha(evento);

            if(agoraOn){
                if(evento.mouse.acao == MOUSE_PRESSIONADO){
                    if(evento.mouse.botao == MOUSE_ESQUERDO){
                        if(evento.mouse.cliques == 1){
                            TrataClickTrilha(p.x,p.y);
                            handle->DefineEstado(COMPONENTE_ACIONADO);
                        }
                    }
                }
                if(handle->GetEstado() == COMPONENTE_ACIONADO) TrataClickTrilha(p.x,p.y);
            }

            if(evento.mouse.acao == MOUSE_LIBERADO) handle->DefineEstado(COMPONENTE_NORMAL);
        }
        return 0;
    }

    int TrataTeclado(PIG_Evento evento){
        if(evento.teclado.acao == TECLA_PRESSIONADA){
            if(orientacao == HORIZONTAL){
                if(evento.teclado.tecla== TECLA_DIREITA) AvancaHandle(vAtual + deltaTeclado);
                if(evento.teclado.tecla == TECLA_ESQUERDA) AvancaHandle(vAtual - deltaTeclado);
            }else{
                if(evento.teclado.tecla== TECLA_CIMA) AvancaHandle(vAtual + deltaTeclado);
                if(evento.teclado.tecla == TECLA_BAIXO) AvancaHandle(vAtual - deltaTeclado);
            }
        }
        return EVENTO_TECLADO;
    }

    void AjustaHandle(){
        if(orientacao == HORIZONTAL){
            handle->Move(xOriginal+largBotoes +porcentagemConcluida*largUtil,yOriginal);
        }else{
            handle->Move(xOriginal,yOriginal + largBotoes+porcentagemConcluida*largUtil);
        }
    }

    void AjustaOrientacao(){
        if(orientacao == HORIZONTAL){
            SetDimensoes(largura,comprimento - (2*largBotoes));
            Move(xOriginal+largBotoes,yOriginal);
            if(botao1 && botao2){
                botao1->Move(xOriginal,yOriginal);
                botao2->Move(xOriginal + comprimento - largBotoes,yOriginal);
            }
            handle->Move(xOriginal+largBotoes +porcentagemConcluida*largUtil,yOriginal);
        }else{
            SetDimensoes(comprimento - (2*largBotoes),largura);
            Move(xOriginal,yOriginal+largBotoes);
            if(botao1 && botao2){
                botao1->Move(xOriginal,yOriginal);
                botao2->Move(xOriginal,yOriginal + comprimento - largBotoes);
            }
            handle->Move(xOriginal,yOriginal + largBotoes+porcentagemConcluida*largUtil);
        }
    }

    //Recebe um valor e move o handle de forma proporcional
    int AvancaHandle(int novoValor){
        vAtual = PIGLimitaValor(novoValor,vMin,vMax);
        porcentagemConcluida = (1.0 * (vAtual - vMin))/(vMax - vMin);
        AjustaHandle();
        if (acao) acao(id,porcentagemConcluida,param);
    }

    void DesabilitaComponentes(){
        if(botao1 && botao2){
            botao1->DefineEstado(COMPONENTE_DESABILITADO);
            botao2->DefineEstado(COMPONENTE_DESABILITADO);
        }
        handle->DefineEstado(COMPONENTE_DESABILITADO);
    }

    int OnMouseOn(){return 0;}
    int OnMouseOff(){return 0;}

public:

    CPigScrollBar(int idComponente,int px, int py,int larguraTotal,int comprimentoTotal,int larguraHandle,std::string imgHandle,std::string imgTrilha,int retiraFundoHandle=1,int retiraFundoTrilha=1,int janela=0):
        CPigComponente(idComponente,px,py,larguraTotal,comprimentoTotal,imgTrilha,retiraFundoTrilha,janela){
            botao1 = botao2 = NULL;
            vMin = vAtual = 0;
            vMax = 100;
            porcentagemConcluida = 0;
            orientacao = HORIZONTAL;
            xOriginal = x;
            yOriginal = y;
            comprimento = comprimentoTotal;
            largura = larguraTotal;
            largBotoes = 0;
            deltaBotao = 1;
            deltaTeclado = deltaRodinha = 10;
            largHandle = larguraHandle;
            handle = new CPigBotao(0,x + largBotoes,y,largura,largHandle,imgHandle,retiraFundoHandle,idJanela);
            largUtil = comprimento - (2*largBotoes) - largHandle;
            DefineEstado(COMPONENTE_NORMAL);
            acao = NULL;
            param = NULL;
            AjustaOrientacao();
    }

    CPigScrollBar(std::string nomeArqParam):CPigScrollBar(LeArquivoParametros(nomeArqParam)){}

    ~CPigScrollBar(){
        if (botao1) delete botao1;
        if (botao2) delete botao2;
        delete handle;
    }

    static CPigScrollBar LeArquivoParametros(std::string nomeArqParam){

        std::ifstream arquivo;
        int idComponente,px,py,larguraTotal,larguraHandle,comprimentoTotal,retiraFundoHandle=1,retiraFundoTrilha=1,janela=0;
        std::string imgHandle = "",imgTrilha = "",variavel;

        arquivo.open(nomeArqParam);

        if(!arquivo.is_open()) throw CPigErroArquivo(nomeArqParam);
        //formato "x valor"
        while(!arquivo.eof()){
           arquivo >> variavel;
            if(variavel == "idComponente") arquivo >> idComponente;
            if(variavel == "px") arquivo >> px;
            if(variavel == "py") arquivo >> py;
            if(variavel == "larguraTotal") arquivo >> larguraTotal;
            if(variavel == "larguraHandle") arquivo >> larguraHandle;
            if(variavel == "comprimentoTotal") arquivo >> comprimentoTotal;
            if(variavel == "imgHandle") arquivo >> imgHandle;
            if(variavel == "imgTrilha") arquivo >> imgTrilha;
            if(variavel == "retiraFundoHandle") arquivo >> retiraFundoHandle;
            if(variavel == "retiraFundoTrilha") arquivo >> retiraFundoTrilha;
            if(variavel == "janela") arquivo >> janela;
        }

        arquivo.close();

        if(imgHandle == "") throw CPigErroParametro("imgHandle",nomeArqParam);
        if(imgTrilha == "") throw CPigErroParametro("imgTrilha",nomeArqParam);

       // std::cout<<idComponente<<" "<<px<<" "<<py<<" "<<altura<<" "<<largura<<" "<<nomeArq<<" "<<retiraFundo<<" "<<janela<<std::endl;
        return CPigScrollBar(idComponente,px,py,larguraTotal,comprimentoTotal,larguraHandle,imgHandle,imgTrilha,retiraFundoHandle,retiraFundoTrilha,janela);
    }

    void SetBotoes(int larguraBotoes,std::string imgBotao1,std::string imgBotao2,int retiraFundoB1 = 1,int retiraFundoB2 = 1){
        if (botao1==NULL){
            botao1 = new CPigBotao(id + 1,xOriginal,yOriginal,largura,larguraBotoes,imgBotao1,retiraFundoB1,idJanela);
            botao2 = new CPigBotao(id + 2,xOriginal,yOriginal,largura,larguraBotoes,imgBotao2,retiraFundoB2,idJanela);
            botao1->DefineAcao(AcaoSetas,this);
            botao2->DefineAcao(AcaoSetas,this);
            botao1->DefineBotaoRepeticao(true);
            botao2->DefineBotaoRepeticao(true);
            botao1->DefineTempoRepeticao(0.01);
            botao2->DefineTempoRepeticao(0.01);
            largBotoes = larguraBotoes;
            largUtil = comprimento - (2*largBotoes) - largHandle;
            if(estado == COMPONENTE_DESABILITADO) DesabilitaComponentes();
            AjustaOrientacao();
        }
    }

    void SetOrientacao(Pig_Orientacao novaOrientacao){
        orientacao = novaOrientacao;
        AjustaOrientacao();
    }

    int TrataEvento(PIG_Evento evento){

        if(estado == COMPONENTE_DESABILITADO || estado == COMPONENTE_INVISIVEL) return -1;

        handle->TrataEvento(evento);
        TrataBotoes(evento);

        if(evento.tipoEvento == EVENTO_NULO) return EVENTO_NULO;
        if(evento.tipoEvento == EVENTO_TECLADO) return TrataTeclado(evento);
        if(evento.tipoEvento == EVENTO_MOUSE) return TrataMouse(evento);

        return EVENTO_GERAL;
    }

    void SetDeltaBotao(int delta){
        deltaBotao = delta;
    }

    void SetDeltaRodinha(int delta){
        deltaRodinha = delta;
    }

    void SetDeltaTeclado(int delta){
        deltaTeclado = delta;
    }

    void DefineEstado(PIG_EstadoComponente estadoComponente){
        estado = estadoComponente;
        if(estado == COMPONENTE_DESABILITADO) DesabilitaComponentes();
    }

    int Desenha(){
        if(estado == COMPONENTE_INVISIVEL) return -1;

        SDL_RenderCopyEx(renderer, text, &frame,&dest,-angulo,&pivoRelativo,flip);

        if(botao1 && botao2){
            botao1->Desenha();
            botao2->Desenha();
        }
        handle->Desenha();
        return 0;
    }

    int GetValorAtual(){
        return vAtual;
    }

    void SetValorMinMax(int minimo,int maximo){
        vMin = minimo;
        vMax = maximo;
        vAtual = PIGLimitaValor(vAtual, vMin,vMax);
        AvancaHandle(vAtual);
    }

};
