class CPigGaugeCircular:public CPigComponente{

protected:
    void SetFoco(bool valor){
        temFoco = valor;
    }

    void SetAcionado(bool valor){
        acionado = valor;
    }

    void SetMouseOver(bool valor){
        mouseOver = valor;
    }

    void SetHabilitado(bool valor){
        habilitado = valor;
    }

private:

    double angBase,deltaAng;
    int raioInterno;
    PIG_Cor corInicial,corFinal,corFundo;
    OffscreenRenderer off;
    bool crescimentoHorario;
    int valor,valorMin,valorMax;
    double porcentagemConcluida;
    SDL_Texture *textGauge;
    //void DefineEstado(PIG_EstadoComponente estadoComponente){}
    //int OnMouseOn(){return 0;}
    //int OnMouseOff(){return 0;}
    //int TrataEvento(PIG_Evento evento){return 0;}

public:

    CPigGaugeCircular(int idComponente,int px, int py,int altura,int largura,int raioInterior,int janela=0):
        CPigComponente(idComponente,px,py,altura,largura,janela){

        angBase = 0;
        deltaAng = 360;
        raioInterno = raioInterior;
        valor = 0;
        valorMin = 0;
        valorMax = 100;
        porcentagemConcluida = 0.0;
        corInicial = corFinal = LARANJA;
        corFundo = PRETO;
        off = new COffscreenRenderer(altura,largura,3);

        Move(px,py);
        SetPivo(larg/2,alt/2);
        textGauge = NULL;
        AtualizaTextura();
        crescimentoHorario=true;
    }

    CPigGaugeCircular(int idComponente,int px, int py,int altura,int largura,int raioInterior,std::string nomeArq,int retiraFundo=1,int janela=0):
        CPigComponente(idComponente,px,py,altura,largura,nomeArq,retiraFundo,janela){

        angBase = 0;
        deltaAng = 360;
        raioInterno = raioInterior;
        valor = 0;
        valorMin = 0;
        valorMax = 100;
        porcentagemConcluida = 0.0;
        corInicial = corFinal = LARANJA;
        corFundo = PRETO;
        off = new COffscreenRenderer(altura,largura,3);

        Move(px,py);
        SetPivo(larg/2,alt/2);
        textGauge = NULL;
        AtualizaTextura();
        crescimentoHorario=true;
    }

    CPigGaugeCircular(std::string nomeArqParam):CPigGaugeCircular(LeArquivoParametros(nomeArqParam)){}

    CPigGaugeCircular LeArquivoParametros(std::string nomeArqParam){

        std::ifstream arquivo;
        int idComponente,px,py,altura,largura,raioInterior,retiraFundo = 0,janela = 0;

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
            if(palavra == "raioInterior") arquivo >> raioInterior;
            if(palavra == "largura") arquivo >> largura;
            if(palavra == "nomeArq") arquivo >> nomeArq;
            if(palavra == "retiraFundo") arquivo >> retiraFundo;
            if(palavra == "janela") arquivo >> janela;
        }
        arquivo.close();

        return CPigGaugeCircular(idComponente,px,py,altura,largura,raioInterior,nomeArq,retiraFundo,janela);
    }

    ~CPigGaugeCircular(){
        delete off;
    }

    void SetRaioInterno(int valorRaio){
        if (valorRaio<0||valorRaio>0.9*larg/2) return;

        raioInterno = valorRaio;
        AtualizaTextura();
    }

    void SetAnguloBase(double novoAng){
        angBase = novoAng;
        AtualizaTextura();
    }

    void SetDeltaAngulo(double novoDelta){
        deltaAng = novoDelta;
        AtualizaTextura();
    }

    void IncrementaValor(int delta){
        valor = PIGLimitaValor(valor+delta, valorMin,valorMax);
        porcentagemConcluida = 1.*(valor-valorMin)/(valorMax-valorMin);
        AtualizaTextura();
    }

    void SetValorMax(int novoValor){
        if (novoValor<=valorMin)return;
        valorMax = novoValor;
        if (valor>valorMax) valor = valorMax;
        porcentagemConcluida = 1.*(valor-valorMin)/(valorMax-valorMin);
        AtualizaTextura();
    }

    void SetValorMin(int novoValor){
        if (novoValor>=valorMax) return;
        valorMin = novoValor;
        if (valor<valorMin) valor=valorMin;
        porcentagemConcluida = 1.*(valor-valorMin)/(valorMax-valorMin);
        AtualizaTextura();
    }

    void SetCorInicial(PIG_Cor cor){
        corInicial = cor;
        AtualizaTextura();
    }

    void SetCorFinal(PIG_Cor cor){
        corFinal = cor;
        AtualizaTextura();
    }

    void SetCorFundo(PIG_Cor cor){
        corFundo = cor;
        AtualizaTextura();
    }

    int GetValor(){
        return valor;
    }

    std::string GetValorString(){
        std::stringstream ss;
        ss <<valor;
        return ss.str();
    }

    int GetValorMax(){
        return valorMax;
    }

    int GetValorMin(){
        return valorMin;
    }

    void AtualizaValor(int novoValor){
        if (valor==novoValor) return;
        valor = novoValor;
        AtualizaTextura();
    }

    void AtualizaTextura(){
        PIG_Cor corBarra = MixCor(corInicial,corFinal,porcentagemConcluida);//cor da barra mizada entre a cor inicial e a final
        PIG_Cor opcoes[4] = {VERDE,AZUL,ROXO,LARANJA}; //4 cores quaisquer
        PIG_Cor croma1, croma2; //cores usada como cromakey para transparencias (não podem ser nem a cor da barra, nem a cor do fundo)

        //escolha das cores
        int i=0;
        croma1=opcoes[i];
        while (PIGCoresIguais(croma1,corBarra)||PIGCoresIguais(croma1,corFundo)){//não pode ser a cor da barra nem do fundo
            croma1=opcoes[++i];
        }
        croma2=opcoes[i];
        while (PIGCoresIguais(croma2,corBarra)||PIGCoresIguais(croma2,corFundo)||PIGCoresIguais(croma2,croma1)){//não pode ser a cor da barra, nem do fundo, nem a cor croma1
            croma2=opcoes[++i];
        }

        //circulo interno para criar efeito de coroa circular
        off->DesenhaCirculoFinal(raioInterno,croma2,croma1,0,360.0,2);
        off->SetCorTransparente(2,true,croma2);
        //off->SalvarImagemPNG("interno.png",2);

        //circulo com a barra na cor desejada
        off->DesenhaCirculoFinal(larg/2-2,croma1,corBarra,angBase,porcentagemConcluida*(deltaAng)+angBase,0);
        off->SetCorTransparente(0,true,croma1);
        //off->SalvarImagemPNG("barra.png",0);

        //criculo com o fundo na cor de fundo
        off->DesenhaCirculoFinal(larg/2-2,croma1,corFundo,angBase,angBase+deltaAng,1);
        off->SetCorTransparente(1,true,croma1);
        //off->SalvarImagemPNG("fundo.png",1);

        //mistura o circulo interno com a barra
        off->MergeSurface(2,0,SDL_BLENDMODE_NONE);
        //off->SalvarImagemPNG("circ20.png",0);

        //mistura o circulo interno com o fundo
        off->MergeSurface(2,1,SDL_BLENDMODE_NONE);
        //off->SalvarImagemPNG("circ21.png",1);

        //sobre a barra em cima do fundo
        off->MergeSurface(0,1,SDL_BLENDMODE_NONE);
        //off->SalvarImagemPNG("circ01.png",1);

        if (textGauge) SDL_DestroyTexture(textGauge);
        textGauge = SDL_CreateTextureFromSurface(renderer,off->GetSurface(1));
        //bitmap = off->GetSurface(1);
        //CriaTextura(1);
    }

    int Desenha(){
        SDL_RenderCopyEx(renderer,text,NULL,&dest,-angulo,&pivoRelativo,flip);
        SDL_RenderCopyEx(renderer,textGauge,NULL,&dest,-angulo,&pivoRelativo,flip);

        DesenhaLabel();
        EscreveHint();
    }

    int TrataEventoMouse(PIG_Evento evento){
        return 0;
    }

    int TrataEventoTeclado(PIG_Evento evento){
        return 0;
    }

};

typedef CPigGaugeCircular *PigGaugeCircular;
