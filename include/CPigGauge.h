#ifndef _CPigGauge_
#define _CPigGauge_

typedef enum {GAUGE_CIMA_BAIXO,GAUGE_BAIXO_CIMA,GAUGE_ESQ_DIR,GAUGE_DIR_ESQ} PIG_GaugeCrescimentoBarra;

class CPigGauge: public CPigComponente{

private:

    SDL_Rect frameBarra,frameBase;
    double delta,porcentagemConcluida;
    double valorMax,valorMin,valorAtual;
    int xBarra,yBarra,altBarra,largBarra;
    PIG_GaugeCrescimentoBarra orientacaoCrescimento;

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

public:

    CPigGauge(int idComponente,int px, int py,int altura,int largura,std::string imgGauge,int retiraFundo=1,int janela=0):
        CPigComponente(idComponente,px,py,altura,largura,imgGauge,retiraFundo,janela){
            valorMin = valorAtual = 0;
            valorMax = 100;
            porcentagemConcluida = 0;
            orientacaoCrescimento = GAUGE_ESQ_DIR;
            xBarra = 0;
            yBarra = 0;
            delta = 0;
    }

    CPigGauge(std::string nomeArqParam):CPigGauge(LeArquivoParametros(nomeArqParam)){}

    static CPigGauge LeArquivoParametros(std::string nomeArqParam){

        std::ifstream arquivo;
        int idComponente,px,py,altura,largura,retiraFundo=1,janela=0;
        std::string imgGauge = "",variavel;

        arquivo.open(nomeArqParam);

        if(!arquivo.is_open()) throw CPigErroArquivo(nomeArqParam);
        //formato "x valor"
        while(!arquivo.eof()){
           arquivo >> variavel;
            if(variavel == "idComponente") arquivo >> idComponente;
            if(variavel == "px") arquivo >> px;
            if(variavel == "py") arquivo >> py;
            if(variavel == "altura") arquivo >> altura;
            if(variavel == "largura") arquivo >> largura;
            if(variavel == "imgGauge") arquivo >> imgGauge;
            if(variavel == "retiraFundo") arquivo >> retiraFundo;
            if(variavel == "janela") arquivo >> janela;
        }

        arquivo.close();

        if(imgGauge == "") throw CPigErroParametro("imgGauge",nomeArqParam);

       // std::cout<<idComponente<<" "<<px<<" "<<py<<" "<<altura<<" "<<largura<<" "<<nomeArq<<" "<<retiraFundo<<" "<<janela<<std::endl;
        return CPigGauge(idComponente,px,py,altura,largura,imgGauge,retiraFundo,janela);

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

    void SetFrames(SDL_Rect fBase,SDL_Rect fBarra){
        frameBase = fBase;
        frameBarra = fBarra;
    }

    virtual int VerificaSeComponenteEstaSelecionado(PIG_Evento evento){
        return 2;
    }

    void SetDistanciaXYBarra(int dx,int dy){
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

        //base
        SDL_RenderCopyEx(renderer, text, &frameBase,&dest,-angulo,&pivoRelativo,flip);

        //definir o valor de r, de acordo com a orientação da barra
        SDL_Rect clip = GeraClip(aux);
        SDL_RenderSetClipRect(renderer,&clip);

        SDL_RenderCopyEx(renderer, text, &frameBarra,&aux,-angulo,&pivoRelativo,flip);

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

    int TrataEventoMouse(PIG_Evento evento){
        return 0;
    }

    int TrataEventoTeclado(PIG_Evento evento){
        return 0;
    }

};
typedef CPigGauge *PigGauge;
#endif // _CPigGauge_
