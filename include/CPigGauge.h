//Opcao 2
class CPigGaugeMaquinaDeEstados: public CPigComponente{

private:

    Timer timer;
    std::vector <SDL_Rect> listaFrames;
    std::vector <int> sequenciaFrames;
    int frameAtual;

    void DefineEstado(PIG_EstadoComponente estadoComponente){}
    int OnMouseOn(){return 0;}
    int OnMouseOff(){return 0;}
    int TrataEvento(PIG_Evento evento){return 0;}

public:

    CPigGaugeMaquinaDeEstados(int idComponente,int px, int py,int altura,int largura,std::string imgGauge,int retiraFundo=1,int janela=0):
        CPigComponente(idComponente,px,py,altura,largura,imgGauge,retiraFundo,janela){
            timer = new CTimer(false);
            frameAtual = 0;
    }

    void AvancaEtapa(){
        frameAtual = (frameAtual + 1) % sequenciaFrames.size();
        DefineFrame(listaFrames[sequenciaFrames[frameAtual]]);
    }

    void SetSequenciaFrames(std::vector <int> sequencia){
        sequenciaFrames = sequencia;
        frameAtual = 0;
        DefineFrame(listaFrames[sequenciaFrames[frameAtual]]);
    }

    void AvancaEtapaTimer(float tempoEmSegundos){

        if (timer->GetTempoDecorrido()> tempoEmSegundos){
            AvancaEtapa();
            timer->Reinicia(false);
        }

    }

    int Desenha(){

        SDL_RenderCopyEx(renderer, text, &frame,&dest,-angulo,&pivoRelativo,flip);
        DesenhaLabel();

        return 1;
    }

    void CriaFrame(int px,int py,int altura,int largura){
        SDL_Rect r = {px,py,largura,altura};
        listaFrames.push_back(r);
    }

};

//Opcao 3
typedef enum {GAUGE_CIMA_BAIXO,GAUGE_BAIXO_CIMA,GAUGE_ESQ_DIR,GAUGE_DIR_ESQ} PIG_GaugeCrescimentoBarra;

class CPigGauge1: public CPigComponente{

private:

    SDL_Rect frameBarra;
    float delta,porcentagemConcluida;
    float valorMax,valorMin,valorAtual;
    PIG_GaugeCrescimentoBarra orientacaoCrescimento;

    int largAtualBarra,altAtualBarra;
    int xBarra,yBarra;
    int margemHorEsq,margemHorDir,margemVertCima,margemVertBaixo;

    void DefineEstado(PIG_EstadoComponente estadoComponente){}
    int OnMouseOn(){return 0;}
    int OnMouseOff(){return 0;}
    int TrataEvento(PIG_Evento evento){return 0;}

    void AjustaOrientacaoBarra(float porcentagemConcluida){

        int largBarra = larg - (margemHorDir + margemHorEsq);
        int altBarra = alt - (margemVertBaixo + margemVertCima);

        switch(orientacaoCrescimento){

        case GAUGE_DIR_ESQ:{
            largAtualBarra = (porcentagemConcluida/100.0)*largBarra;
            altAtualBarra = altBarra;
            xBarra = x + margemHorEsq + largBarra - largAtualBarra;
            yBarra = y + margemVertBaixo;
        }break;

        case GAUGE_ESQ_DIR:{
            largAtualBarra = (porcentagemConcluida/100.0)*largBarra;
            altAtualBarra = altBarra;
            xBarra = x + margemHorEsq;
            yBarra = y + margemVertBaixo;
        }break;

        case GAUGE_CIMA_BAIXO:{
            largAtualBarra = largBarra;
            altAtualBarra = (porcentagemConcluida/100.0)*altBarra;
            xBarra = x + margemHorEsq;
            yBarra = y + margemVertBaixo + altBarra - altAtualBarra;
        }break;

        case GAUGE_BAIXO_CIMA:{
            largAtualBarra = largBarra;
            altAtualBarra = (porcentagemConcluida/100.0)*altBarra;
            xBarra = x + margemHorEsq;
            yBarra = y + margemVertBaixo;
        }break;

        }

    }

    void DesenhaBarra(){
        SDL_RenderCopyEx(renderer, text, &frameBarra,&dest,-angulo,&pivoRelativo,flip);
    }

public:

    CPigGauge1(int idComponente,int px, int py,int altura,int largura,std::string imgGauge,int retiraFundo=1,int janela=0):
        CPigComponente(idComponente,px,py,altura,largura,imgGauge,retiraFundo,janela){

            margemHorEsq = margemHorDir = margemVertCima = margemVertBaixo = 0;
            valorMin = valorAtual = 0;
            valorMax = 100;
            largAtualBarra = 0;
            altAtualBarra = 0;
            orientacaoCrescimento = GAUGE_ESQ_DIR;
            xBarra = px;
            yBarra = py;
            delta = 0;
            AvancaBarra(100);
    }

    void SetValorMinMax(int minimo,int maximo){

        if(minimo <= maximo){
            valorMax = maximo;
            valorMin = valorAtual = minimo;
            AvancaBarra(0);
        }

    }

    void SetMargens(int horEsquerda,int horDireita,int vertCima,int vertBaixo){

        margemHorEsq = horEsquerda;
        margemHorDir = horDireita;
        margemVertCima = vertCima;
        margemVertBaixo = vertBaixo;

    }

    void AvancaBarra(float valor){
        valorAtual += valor;

        if(valorAtual > valorMax){
            porcentagemConcluida = 100.0;
            valorAtual = valorMax;
        }else{
            porcentagemConcluida = (100.0 * (valorAtual - valorMin))/(valorMax - valorMin);
        }

        AjustaOrientacaoBarra(porcentagemConcluida);
    }

    /*** Opção 1 ***/

    void SetFrameBarra(int px,int py,int altura,int largura){
        SDL_Rect r = {px,py,largura,altura};
        frameBarra = r;
    }

    void SetFrameBase(int px,int py,int altura,int largura){
        SDL_Rect r = {px,py,largura,altura};
        DefineFrame(r);
    }

    /***Opção 2

    void SetFrameBarra(int px,int py){
        SDL_Rect r = {px,py,larg,alt};
        frameBarra = r;
    }

    void SetFrameBase(int px,int py){
        SDL_Rect r = {px,py,larg,alt};
        DefineFrame(r);
    }
    *******/


    void SetPorcentagemConcluida(float porcentagem){
        if(porcentagem >= 0 && porcentagem <=100){
            valorAtual = valorMin + ( (valorMax - valorMin) * (porcentagem/100) );
            AvancaBarra(0);
        }
    }

    void SetDelta(float valor){
        delta = valor;
    }

    void AvancaDelta(){
        AvancaBarra(delta);
    }

    std::string GetPorcentagemConcluidaString(int precisao = 3){

        std::stringstream str;
        str << std::setprecision(precisao);
        str << porcentagemConcluida;
        return str.str();

    }

    float GetPorcentagemConcluida(){
        return porcentagemConcluida;
    }

    void SetOrientacaoBarra(PIG_GaugeCrescimentoBarra orientacao){
        orientacaoCrescimento = orientacao;
    }

    int Desenha(){

        SDL_RenderCopyEx(renderer, text, &frame,&dest,-angulo,&pivoRelativo,flip);

        SDL_Rect r={xBarra,altJanela-yBarra-altAtualBarra,largAtualBarra,altAtualBarra};
        SDL_RenderSetClipRect(renderer,&r);

        DesenhaBarra();

        SDL_RenderSetClipRect(renderer,NULL);

        DesenhaLabel();

        return 1;
    }

    float GetValorBarraAtual(){
        return valorAtual;
    }

    void SetValorBarraAtual(float valor){
        if(valor >=valorMin && valor <=valorMax){
            valorAtual = valor;
            AvancaBarra(0);
        }
    }

    void ZeraValor(){
        valorAtual = valorMin;
        AvancaBarra(0);
    }

};

class CPigGauge2: public CPigComponente{

private:

    SDL_Rect frameBarra,frameBase;
    double delta,porcentagemConcluida;
    double valorMax,valorMin,valorAtual;
    int xBarra,yBarra,altBarra,largBarra;
    PIG_GaugeCrescimentoBarra orientacaoCrescimento;

    void DefineEstado(PIG_EstadoComponente estadoComponente){}
    int OnMouseOn(){return 0;}
    int OnMouseOff(){return 0;}
    int TrataEvento(PIG_Evento evento){return 0;}

    SDL_Rect GeraClip(SDL_Rect barra){
        SDL_Rect resp = barra;
        switch(orientacaoCrescimento){
        case GAUGE_DIR_ESQ:
            resp.x += (1-porcentagemConcluida/100.0)*barra.w;
            break;
        case GAUGE_ESQ_DIR:
            resp.w = (porcentagemConcluida/100.0)*barra.w;
            break;
        case GAUGE_CIMA_BAIXO:
            resp.h = (porcentagemConcluida/100.0)*barra.h;
            break;
        case GAUGE_BAIXO_CIMA:
            resp.y += (1-porcentagemConcluida/100.0)*barra.h;
            break;
        }

        //printf("%d %d %d %d %f\n",resp.x,resp.y,resp.w,resp.h,porcentagemConcluida);
        return resp;
    }

public:

    CPigGauge2(int idComponente,int px, int py,int altura,int largura,std::string imgGauge,int retiraFundo=1,int janela=0):
        CPigComponente(idComponente,px,py,altura,largura,imgGauge,retiraFundo,janela){
            valorMin = valorAtual = 0;
            valorMax = 100;
            porcentagemConcluida = 0;
            orientacaoCrescimento = GAUGE_ESQ_DIR;
            xBarra = 0;
            yBarra = 0;
            delta = 0;
    }

    void SetValorMinMax(int minimo,int maximo){
        if(minimo <= maximo){
            valorMax = maximo;
            valorMin = valorAtual = minimo;
            AvancaBarra(0);
        }
    }

    void AvancaBarra(float valor){
        valorAtual += valor;

        if(valorAtual > valorMax){
            porcentagemConcluida = 100.0;
            valorAtual = valorMax;
        }else{
            porcentagemConcluida = (100.0 * (valorAtual - valorMin))/(valorMax - valorMin);
        }

        //AjustaOrientacaoBarra(porcentagemConcluida);
    }

    void SetFrameBarra(SDL_Rect r){
        frameBarra = r;
    }

    void SetFrameBase(SDL_Rect r){
        frameBase = r;
    }

    void SetDXDY(int dx,int dy){
        xBarra = dx;
        yBarra = dy;
    }

    void SetPorcentagemConcluida(float porcentagem){
        if(porcentagem >= 0 && porcentagem <=100){
            valorAtual = valorMin + ( (valorMax - valorMin) * (porcentagem/100) );
            AvancaBarra(0);
        }
    }

    void SetDelta(float valor){
        delta = valor;
    }

    void AvancaDelta(){
        AvancaBarra(delta);
    }

    float GetPorcentagemConcluida(){
        return porcentagemConcluida;
    }

    void SetOrientacaoBarra(PIG_GaugeCrescimentoBarra orientacao){
        orientacaoCrescimento = orientacao;
    }


    int Desenha(){
        double scalaX = (1.*dest.w/frameBase.w);
        double scalaY = (1.*dest.h/frameBase.h);

        SDL_Rect aux;
        aux.h = ceil(scalaY*frameBarra.h);
        aux.w = ceil(scalaX*frameBarra.w);
        aux.x = dest.x+xBarra*scalaX;
        aux.y = dest.y+yBarra*scalaY;

        //definir o valor de r, de acordo com a orientação da barra
        SDL_Rect clip = GeraClip(aux);
        SDL_RenderSetClipRect(renderer,&clip);

        SDL_RenderCopyEx(renderer, text, &frameBarra,&aux,-angulo,&pivoRelativo,flip);

        SDL_RenderSetClipRect(renderer,NULL);

        //base
        SDL_RenderCopyEx(renderer, text, &frameBase,&dest,-angulo,&pivoRelativo,flip);

        DesenhaLabel();
        return 1;
    }

    float GetValorBarraAtual(){
        return valorAtual;
    }

    void SetValorBarraAtual(float valor){
        if(valor >=valorMin && valor <=valorMax){
            valorAtual = valor;
            AvancaBarra(0);
        }
    }

    void ZeraValor(){
        valorAtual = valorMin;
        AvancaBarra(0);
    }

};
