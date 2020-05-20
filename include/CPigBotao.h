typedef int (*AcaoBotao)(int,void*);

class CPigImagemSecundaria : public CPigComponente{

private:

    virtual int TrataEvento(PIG_Evento evento){return 0;}
    virtual void DefineEstado(PIG_EstadoComponente estadoComponente){};
    virtual int OnMouseOn(){return 0;};
    virtual int OnMouseOff(){return 0;};

public:

    CPigImagemSecundaria(int idComponente,int px,int py, int alt, int larg, char *nomeArq,int retiraFundo=1,int janela=0):
        CPigComponente(idComponente,px,py,alt,larg,nomeArq,retiraFundo,janela){
    }

    int Desenha(){
        SDL_RenderCopyEx(renderer, text, &frame,&dest,-angulo,&pivoRelativo,flip);
    }

};

class CPigBotao: public CPigComponente{

private:

    char *texto;
    int tecla;
    int largFrame;
    int fonteTexto;
    int xImgSecundaria,yImgSecundaria;
    CPigImagemSecundaria *imgSecundaria;
    PIG_PosicaoComponente posTexto;
    PIG_PosicaoComponente posImagem;
    AcaoBotao acao;
    void *param;
    Timer timer;

    int TrataMouse(int acao){
        SDL_Point p;
        CMouse::PegaXY(p.x,p.y);
        MouseSobre(p.x,p.y);

        if(agoraOn)
            if (acao==MOUSE_PRESSIONADO) return OnMouseClick();

        return 0;
    }

    int TrataTeclado(PIG_Evento evento){
        if (evento.teclado.acao==TECLA_PRESSIONADA)
            if (evento.teclado.tecla==tecla)return OnMouseClick();

        return 0;
    }

    void TrataTimer(){

        if (timer->GetTempoDecorrido()<0.2){
            DefineEstado(COMPONENTE_ACIONADO);
        }else{
            delete timer;
            timer = NULL;
            if (agoraOn) DefineEstado(COMPONENTE_MOUSEOVER);
            else DefineEstado(COMPONENTE_NORMAL);
        }

    }

    int OnMouseClick(){
        DefineEstado(COMPONENTE_ACIONADO);
        if (timer) delete timer;
        timer = new CTimer(false);
        if (acao) acao(id,param);//rever se NULL é necessário
        if (audioComponente>=0) PlayAudio(audioComponente);
        return 1;
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

    void IniciaBase(){

        tecla = -1;//sem tecla de atalho
        timer = NULL;//sem timer para "soltar" o botão
        acao = NULL;//não tem ação registrada
        param = NULL;//não tem parâmetro associado à ação
        posTexto = COMPONENTE_CENTRO;
        SetPosicaoPadraoLabel(posTexto);
        imgSecundaria = NULL;
        posImagem = COMPONENTE_ESQUERDA;
        texto = "";
        fonteTexto = 0;
    }

    void DesenhaTexto(){
        if (texto!=NULL && strcmp(texto,"")) {
            switch(posTexto){
            case COMPONENTE_ESQUERDA:
                EscreverEsquerda(texto,x,y,fonteTexto);
                break;
            case COMPONENTE_DIREITA:
                EscreverDireita(texto,x+larg,y,fonteTexto);
                break;
            case COMPONENTE_CENTRO:
                EscreverCentralizada(texto,x+larg/2,y+(alt-20)/2,fonteTexto);
                break;
            }
        }
    }

public:

    CPigBotao(int idComponente,int px, int py, int alt,int larg,char *nomeArq, int retiraFundo=1,int janela=0):
        CPigComponente(idComponente,px,py,alt,larg,nomeArq,retiraFundo,janela){
        IniciaBase();
        largFrame = largOriginal/4;//a imgem deve ter 4 frames (normal,mouse_over,acionado,desabilitado)
        DefineEstado(COMPONENTE_NORMAL); //começa normal

    }

    CPigBotao(int idComponente,int px, int py, int alt,int larg,int janela=0):
        CPigComponente(idComponente,px,py,alt,larg,janela){
            IniciaBase();
    }

    ~CPigBotao(){
        if (timer) delete timer;
        if(imgSecundaria) delete imgSecundaria;
    }

    void SetTexto(char *novoTexto){
        if (texto)
            free(texto);
        if (novoTexto){
            texto = (char*) malloc(strlen(novoTexto));
            strcpy(texto,novoTexto);
        }
    }

    void GetTexto(char *buffer){

        strcpy(buffer,texto);

    }

    void SetFonteTexto(int fonte){

        fonteTexto = fonte;

    }

    int SetPosPadraoImagemSecundaria(PIG_PosicaoComponente posDaImagem){

        if(imgSecundaria==NULL) return 0;

        int altura,largura;
        imgSecundaria->GetDimensoes(altura,largura);
        posImagem = posDaImagem;

        if(posImagem == COMPONENTE_ESQUERDA) imgSecundaria->Move(x,y);

        if(posImagem == COMPONENTE_DIREITA) imgSecundaria->Move(x + larg - largura,y);

        if(posImagem == COMPONENTE_POSICAO_PERSONALIZADA) imgSecundaria->Move(xImgSecundaria,yImgSecundaria);

        return 1;

    }

    int SetPosicaoPadraoTexto(PIG_PosicaoComponente pos){
        posTexto = pos;
        return 1;
    }

    int CriaImagemSecundaria(int altura,int largura,char *nomeArq,PIG_PosicaoComponente posDaImagem = COMPONENTE_ESQUERDA,int retiraFundo = 1){

        if(imgSecundaria!=NULL) delete imgSecundaria;
        imgSecundaria = NULL;

        if(nomeArq !=NULL && nomeArq !=""){

            imgSecundaria = new CPigImagemSecundaria(id+1,x,y,altura,largura,nomeArq,retiraFundo,idJanela);
            return SetPosPadraoImagemSecundaria(posDaImagem);

        }

        return 0;
    }

    void Move(int nx,int ny){

        CVisual::Move(nx,ny);
        SetPosicaoPadraoLabel(posLabel);
        if(imgSecundaria!=NULL)SetPosPadraoImagemSecundaria(posImagem);

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

        if (estado == COMPONENTE_DESABILITADO || estado == COMPONENTE_INVISIVEL) return -1;

        if (evento.tipoEvento == EVENTO_MOUSE) return TrataMouse(evento.mouse.acao);

        if (evento.tipoEvento == EVENTO_TECLADO) return TrataTeclado(evento);

        return 0;
    }

    CPigImagemSecundaria *GetImagemSecundaria(){

        return imgSecundaria;

    }

    PIG_PosicaoComponente GetPosImagemSecundaria(){

        return posImagem;

    }

    int Desenha(){

        if (estado==COMPONENTE_INVISIVEL) return 0;

        if (timer) TrataTimer();

        SDL_RenderCopyEx(renderer, text, &frame,&dest,-angulo,&pivoRelativo,flip);

        if(imgSecundaria !=NULL) imgSecundaria->Desenha();
        DesenhaLabel();
        DesenhaTexto();

        return 1;
    }


};

typedef CPigBotao *PigBotao;
