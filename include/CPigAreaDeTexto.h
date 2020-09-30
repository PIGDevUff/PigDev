#ifndef _CPigAreaDeTexto_
#define _CPigAreaDeTexto_

#include "CPigCaixaTexto.h"

class CPigAreaDeTexto: public CPigCaixaTexto{

private:

    int largMax;
    int espacoEntreLinhas;
    bool linhasPauta;
    CPigScrollBar *scrollVertical,*scrollHorizontal;
    bool scrollVerticalAtivado,scrollHorizontalAtivado;
    int xOriginal,yOriginal;
    int largReal,altReal;

    std::vector<std::string> linhas;

    PIG_Cor corLinhasTexto;

    //Recupera todo o texto da área
    inline std::string GetTextoVisivel(){
        return GetTexto();
    }

    void TrataScrollBarVertical(PIG_Evento evento){
        scrollVertical->TrataEvento(evento);

        int valorAtual = scrollVertical->GetValorAtual();
        if(valorAtual!=yBase){
            yBase = valorAtual;
            scrollVertical->SetValorMinMax(yBaseOriginal,yBaseOriginal + ((espacoEntreLinhas + altLetra)*(linhas.size()-1)));
            scrollVertical->SetValorAtual(yBase);
            yCursor = yBase - ( (espacoEntreLinhas + altLetra) * GetLinhaDeUmaPos(posCursor));
        }
    }

    void TrataScrollBarHorizontal(PIG_Evento evento){
        scrollHorizontal->TrataEvento(evento);

        int valorAtual = scrollHorizontal->GetValorAtual();
        if(xBase != valorAtual){
            xBase = valorAtual;
            std::string aux;
            int posInicial = GetPosInicialDeUmaLinha(GetLinhaDeUmaPos(posCursor));
            scrollHorizontal->SetValorMinMax(xBaseOriginal - GetLarguraLinhaMaior() + (larg - (margemHorDir+margemHorEsq)),xBaseOriginal);
            scrollHorizontal->SetValorAtual(xBase);
            aux.assign(GetTextoVisivel(),posInicial,posCursor - posInicial);
            xCursor = xBase + CGerenciadorFontes::GetLarguraPixels(aux,fonteTexto);
        }
    }

    //Verifica se é necessário acionar a ScrollBarVertical quando o texto é modificado
    void AcionaScrollBarVertical(){
        //int temp;
        scrollVerticalAtivado = ((espacoEntreLinhas + altLetra)*(linhas.size())) > (alt - (margemVertBaixo+margemVertCima));
        scrollVertical->SetVisivel(scrollVerticalAtivado);
        //if(!scrollVerticalAtivado) scrollVertical->DefineEstado(COMPONENTE_INVISIVEL);
        //else scrollVertical->DefineEstado(COMPONENTE_NORMAL);
    }

    //Verifica se é necessário acionar a ScrollBarHorizontal quando o texto é modificado
    void AcionaScrollBarHorizontal(){
        //int temp;
        scrollHorizontalAtivado = GetLarguraLinhaMaior() > (larg - (margemHorDir+margemHorEsq));
        scrollHorizontal->SetVisivel(scrollHorizontalAtivado);
        //if(!scrollHorizontalAtivado) scrollHorizontal->DefineEstado(COMPONENTE_INVISIVEL);
        //else scrollHorizontal->DefineEstado(COMPONENTE_NORMAL);
    }

    int GetLarguraLinhaMaior(){
        int tamMaior = 0;
        int temp = 0;
        for(std::string linha : linhas){
            temp = CGerenciadorFontes::GetLarguraPixels(linha,fonteTexto);
            tamMaior = (temp > tamMaior) ? (temp):(tamMaior);
        }
        return tamMaior;
    }

    //Desenha um contorno baseado nas dimensoes reais da área(somando a área em si e a scroll bar)
    void DesenhaMarcacaoMargem(){
        CGerenciadorJanelas::DesenhaLinhaSimples(x+margemHorEsq,y+margemVertBaixo,x+ margemHorEsq,y+alt-margemVertCima,BRANCO,idJanela);
        CGerenciadorJanelas::DesenhaLinhaSimples(x+larg-margemHorDir,y+margemVertBaixo,x+larg-margemHorDir,y+alt-margemVertCima,BRANCO,idJanela);

        CGerenciadorJanelas::DesenhaLinhaSimples(x+margemHorEsq,y+alt-margemVertCima,x+larg-margemHorDir,y+alt-margemVertCima,BRANCO,idJanela);
        CGerenciadorJanelas::DesenhaLinhaSimples(x+margemHorEsq,y+margemVertBaixo,x+larg-margemHorDir,y+margemVertBaixo,BRANCO,idJanela);
    }

    //Volta a base e o cursor para o início
    void ResetaValoresBase(){
        yCursor = yBase = yBaseOriginal = y+alt-altLetra-margemVertCima;
        xCursor = xBase = xBaseOriginal = x + margemHorEsq;
        AjustaAlinhamento();
    }

    //Serve no caso em que o y do cursor fica fora da área visível
    void AjustaBaseTextoEixoY(){
        while(yCursor < y + margemVertBaixo){
            yBase+=1;
            yCursor+=1;
        }
        while(yCursor > y + alt - altLetra - margemVertCima){
            yBase-=1;
            yCursor-=1;
        }
    }

    //Ajusta o alinhamento do texto quando ocorre alguma modificação
    void AjustaAlinhamento() override{
        std::string textoBase = GetTextoVisivel();
        std::string aux;

        linhas = CGerenciadorFontes::ExtraiLinhasString(textoBase,largMax,fonteTexto);

        int linhaPos = GetLinhaDeUmaPos(posCursor);
        int posInicial = GetPosInicialDeUmaLinha(linhaPos);

        aux.assign(textoBase,posInicial,posCursor - posInicial);

        yCursor = yBase - ( (espacoEntreLinhas + altLetra)*GetLinhaDeUmaPos(posCursor));
        xCursor = xBase + CGerenciadorFontes::GetLarguraPixels(aux,fonteTexto);

        if(scrollVertical) AcionaScrollBarVertical();
        if(scrollHorizontal) AcionaScrollBarHorizontal();

        AjustaBaseTextoEixoX(CGerenciadorFontes::GetLarguraPixels(aux,fonteTexto));
        AjustaBaseTextoEixoY();

        if(scrollHorizontalAtivado) scrollHorizontal->SetValorAtual(xBase);
        if(scrollVerticalAtivado) scrollVertical->SetValorAtual(yBase);

    }

    //trata o evento do botao esquerdo
    int TrataMouseBotaoEsquerdo(SDL_Point p,int inicioLinha = 0)override{
        int posInicial = GetPosInicialDeUmaLinha(GetLinhaComMouseEmCima());
        int linha = GetLinhaComMouseEmCima();
        //printf("pos %d linha %d\n",posInicial,linha);
        return TrataMouseBotaoEsquerdoESobeDesceCursor(p,posInicial,linha);
    }

    //Trata evento botao esquerdo e sobe e desce o cursor pelas setas
    int TrataMouseBotaoEsquerdoESobeDesceCursor(SDL_Point p,int inicioLinha = 0,int linha = 0){
        int delta = p.x-xBase;

        if(linha!=-1){
            if(delta < CGerenciadorFontes::GetLarguraPixels(linhas[linha],fonteTexto)){
                CPigCaixaTexto::TrataMouseBotaoEsquerdo(p,inicioLinha);
            }else{
                posCursor = inicioLinha + linhas[linha].size();
            }
        }

        AjustaAlinhamento();

        return PIG_SELECIONADO_TRATADO;
    }

    //
    int GetLinhaComMouseEmCima(){
        SDL_Point p;
        CMouse::PegaXY(p.x,p.y);
        int yLinha=0;

        for(int i=0;i<linhas.size();i++){

            yLinha = yBase - ((espacoEntreLinhas + altLetra)*i);
            if(p.y > yLinha && p.y <(yLinha + (espacoEntreLinhas + altLetra)) ){
                return i;
            }
        }
        return linhas.size()-1;
    }

    //
    int GetPosInicialDeUmaLinha(int linha){
        if (linhas.size()==0) return 0;
        int posPercorridas = 0;

        for(int i=0;i<linhas.size();i++){
            if(linha == i){
                return posPercorridas;
            }

            posPercorridas += linhas[i].size();
        }

        return posPercorridas - linhas[linhas.size()-1].size();
    }

    //
    int GetLinhaDeUmaPos(int pos){
        if (linhas.size()==0) return 0;
        int qntLinhas = 0;

        for(int i=0;i<linhas.size();i++){
            qntLinhas+=linhas[i].size();

            if(qntLinhas >= pos){
                return i;
            }
        }

        return 0;
    }

    //
    void DesenhaLinhasHorizontais(){
        int yLinha = yBase;
        int xLinha = x;
        int i=0;

        while(yLinha >= y){
            CGerenciadorJanelas::DesenhaLinhaSimples(xLinha,yLinha,xLinha+larg,yLinha,corLinhasTexto);
            i++;
            yLinha = yBase - ((espacoEntreLinhas + altLetra) *i);
        }
    }

    //move o cursor uma linha para cima
    int SobeCursor(){
        SDL_Point p;
        p.x = xCursor;
        p.y = yCursor;
        int total =0;

        int linhaCursor = GetLinhaDeUmaPos(posCursor);

        if(linhaCursor > 0) return TrataMouseBotaoEsquerdoESobeDesceCursor(p,GetPosInicialDeUmaLinha(linhaCursor-1),linhaCursor-1);

        return 0;
    }

    //move o cursor uma linha para baixo
    int DesceCursor(){
        SDL_Point p;
        p.x = xCursor;
        p.y = yCursor;

        int linhaCursor = GetLinhaDeUmaPos(posCursor);

        if(linhaCursor < linhas.size()-1 ) return TrataMouseBotaoEsquerdoESobeDesceCursor(p,GetPosInicialDeUmaLinha(linhaCursor+1),linhaCursor+1);

        return 0;
    }

    //PulaLinha com Enter
    int PulaLinha(){
        std::string aux = "";
        std::string auxB = "";

        aux.assign(texto,0,posCursor);
        auxB += aux;
        auxB += '\n';
        aux.assign(texto,posCursor,texto.size() - posCursor);
        auxB +=aux;

        texto = auxB;
        AvancaCursor();

    };

    void SetHabilitado(bool valor){
        habilitado = valor;
    }

    void SetAcionado(bool valor){
        acionado = valor;
    }

    void SetMouseOver(bool valor){
        mouseOver = valor;
    }

    void SetFoco(bool valor) override{
        temFoco = valor;
        if (temFoco) SDL_StartTextInput();
        else SDL_StopTextInput();
    }

public:

    CPigAreaDeTexto(int idComponente,int px, int py, int altura,int largura,std::string nomeArq,int maxCars = 200,int retiraFundo=1,int janela=0):
        CPigCaixaTexto(idComponente,px,py,altura,largura,nomeArq,maxCars,false,retiraFundo,janela){ // A altura é um vetor, mas eu preciso dela, entao eu acabei colocando como o tamanho da fonte, qualquer coisa só mudar aqui
            espacoEntreLinhas = 0;
            yCursor = yBase = yBaseOriginal = y+altura-altLetra - margemVertCima;
            xCursor = xBase = xBaseOriginal = x + margemHorEsq;
            largMax = largura;
            linhasPauta = false;
            corLinhasTexto = PRETO;
            scrollHorizontalAtivado = scrollVerticalAtivado = false;
            scrollHorizontal = scrollVertical = NULL;
            largReal = larg;
            altReal = alt;
            xOriginal = x;
            yOriginal = y;
            AjustaAlinhamento();
        }

    CPigAreaDeTexto(std::string nomeArqParam):CPigAreaDeTexto(LeArquivoParametros(nomeArqParam)){}

    ~CPigAreaDeTexto(){
        linhas.clear();
    }

    static CPigAreaDeTexto LeArquivoParametros(std::string nomeArqParam){

        std::ifstream arquivo;
        int idComponente,px,py,altura,largura,maxCars = 200,retiraFundo=1,janela=0;
        std::string nomeArq = "",variavel;

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
            if(variavel == "nomeArq") arquivo >> nomeArq;
            if(variavel == "retiraFundo") arquivo >> retiraFundo;
            if(variavel == "maxCars") arquivo >> maxCars;
            if(variavel == "janela") arquivo >> janela;
        }

        arquivo.close();

        if(nomeArq == "") throw CPigErroParametro("nomeArq",nomeArqParam);

       // std::cout<<idComponente<<" "<<px<<" "<<py<<" "<<altura<<" "<<largura<<" "<<nomeArq<<" "<<retiraFundo<<" "<<janela<<std::endl;
        return CPigAreaDeTexto(idComponente,px,py,altura,largura,nomeArq,maxCars,retiraFundo,janela);

    }

    void SetScrollBarVertical(int larguraTotal,int comprimentoTotal,int larguraHandle,std::string imgHandle,std::string imgTrilha,int retiraFundoHandle=1,int retiraFundoTrilha=1){
        scrollVertical = new CPigScrollBar(id + 1,x + larg,y,larguraTotal,comprimentoTotal,larguraHandle,imgHandle,imgTrilha,retiraFundoHandle,retiraFundoTrilha,idJanela);
        scrollVertical->SetOrientacao(VERTICAL);
        int posYUltLinha = yBase - ((espacoEntreLinhas + altLetra)*linhas.size());
        scrollVertical->SetValorMinMax(yBase,posYUltLinha);
        scrollVertical->MudaOrientacaoCrescimento();
        scrollVertical->SetSetasAtivadas(false);
        scrollVerticalAtivado = false;
        scrollVertical->SetVisivel(false);
        SetPosPadraoScrollVertical(PIG_COMPONENTE_DIR_CENTRO);
    }

    int SetBotoesScrollBarVertical(int larguraBotoes,std::string imgBotao1,std::string imgBotao2,int retiraFundoB1 = 1,int retiraFundoB2 = 1){
        if(!scrollVertical) return -1;
        scrollVertical->SetBotoes(larguraBotoes,imgBotao1,imgBotao2,retiraFundoB1,retiraFundoB2);
        return 1;
    }

    void SetScrollBarHorizontal(int larguraTotal,int comprimentoTotal,int larguraHandle,std::string imgHandle,std::string imgTrilha,int retiraFundoHandle=1,int retiraFundoTrilha=1){
        scrollHorizontal = new CPigScrollBar(id + 1,x,y - larguraTotal,larguraTotal,comprimentoTotal,larguraHandle,imgHandle,imgTrilha,retiraFundoHandle,retiraFundoTrilha,idJanela);
        int maiorTamLinha = GetLarguraLinhaMaior();
        scrollHorizontal->SetValorMinMax(xBaseOriginal,xBaseOriginal + maiorTamLinha);
        scrollHorizontal->MudaOrientacaoCrescimento();
        scrollHorizontal->SetSetasAtivadas(false);
        scrollHorizontalAtivado = false;
        scrollHorizontal->SetVisivel(false);
        //scrollHorizontal->DefineEstado(COMPONENTE_INVISIVEL);
        SetPosPadraoScrollHorizontal(PIG_COMPONENTE_BAIXO_CENTRO);
    }

    int SetBotoesScrollBarHorizontal(int larguraBotoes,std::string imgBotao1,std::string imgBotao2,int retiraFundoB1 = 1,int retiraFundoB2 = 1){
        if(!scrollHorizontal) return -1;
        scrollHorizontal->SetBotoes(larguraBotoes,imgBotao1,imgBotao2,retiraFundoB1,retiraFundoB2);
        return 1;
    }

    void SetPosPadraoScrollHorizontal(PIG_PosicaoComponente pos){
        scrollHorizontal->SetPosPadraoExternaComponente(pos,this);
    }

    void SetPosPadraoScrollVertical(PIG_PosicaoComponente pos){
        scrollVertical->SetPosPadraoExternaComponente(pos,this);
    }

    void Move(int px,int py){
        CPigVisual::Move(px,py);
        xOriginal = px;
        yOriginal = py;
        if(scrollHorizontal) scrollHorizontal->SetPosPadraoExternaComponente(scrollHorizontal->GetPosComponente(),this);
        if(scrollVertical) scrollVertical->SetPosPadraoExternaComponente(scrollVertical->GetPosComponente(),this);
        ResetaValoresBase();
    }

    void MoveScrollBarHorizontal(int px,int py){
        if(scrollHorizontal) scrollHorizontal->Move(px,py);
    }

    void MoveScrollBarVertical(int px,int py){
        if(scrollVertical) scrollVertical->Move(px,py);
    }

    void SetDimensoes(int altura,int largura){
        CPigVisual::SetDimensoes(altura,largura);
        largReal = largura;
        altReal = altura;
        ResetaValoresBase();
    }

    int Desenha() override{
        //imagem de fundo
        SDL_RenderCopyEx(renderer, text, &frame,&dest,-angulo,&pivoRelativo,flip);

        DesenhaMarcacaoMargem();

        if(scrollVertical) scrollVertical->Desenha();
        if(scrollHorizontal) scrollHorizontal->Desenha();

        SDL_Rect r={x+margemHorEsq,altJanela-y-alt+margemVertCima,larg-(margemHorEsq+margemHorDir),alt-(margemVertBaixo+margemVertCima)};
        SDL_RenderSetClipRect(renderer,&r);

        DesenhaCursor();//desenha o cursor (se estiver em edição)
        CGerenciadorFontes::EscreverLonga(texto,xBase,yBase,largMax,(espacoEntreLinhas + altLetra),fonteTexto,BRANCO,CPIG_TEXTO_ESQUERDA);
        if(linhasPauta) DesenhaLinhasHorizontais();

        //desbloqueia o desenho fora da area do componente
        SDL_RenderSetClipRect(renderer,NULL);

        DesenhaLabel();
        EscreveHint();

        return 1;
    }

    void SetFonteTexto(int fonte) override{
        CPigCaixaTexto::SetFonteTexto(fonte);
        ResetaValoresBase();
    }

    //define a cor da linhas horizontais
    void SetLinhasAbaixoTexto(bool visivel,PIG_Cor cor = PRETO){
        corLinhasTexto = cor;
        linhasPauta = visivel;
    }

    //define a largura máxima do texto
    void SetLargMaxTexto(int largMaxTexto){
        largMax = largMaxTexto;
        AjustaAlinhamento();
    }

    int TrataEventoMouse(PIG_Evento evento){
        SDL_Point p = CMouse::PegaXY();
        ChecaMouseOver(p);

        if(mouseOver){
            if(habilitado==false) return PIG_SELECIONADO_DESABILITADO;
            if(visivel==false) return PIG_SELECIONADO_INVISIVEL;
            if(scrollVerticalAtivado) TrataScrollBarVertical(evento);
            if(scrollHorizontalAtivado) TrataScrollBarHorizontal(evento);
            if (evento.mouse.acao == MOUSE_PRESSIONADO && evento.mouse.botao == MOUSE_ESQUERDO) return TrataMouseBotaoEsquerdo(p);
            return PIG_SELECIONADO_MOUSEOVER;
        }
        return PIG_NAO_SELECIONADO;
    }

    //define o espaçamento entre as linhas
    void SetEspacoEntreAsLinhas(int espaco){
        espacoEntreLinhas = espaco;
    }

    int SetTexto(std::string frase)override{
        CPigCaixaTexto::SetTexto(frase);
        AjustaAlinhamento();
    }

    void SetMargens(int horEsq,int horDir, int vertBaixo,int vertCima){
        margemVertCima = vertCima;
        margemVertBaixo = vertBaixo;
        margemHorDir = horDir;
        margemHorEsq = horEsq;
        ResetaValoresBase();
        AjustaAlinhamento();
    }

    //recupera o texto separado em linhas
    std::vector<std::string> GetLinhasTexto(){
        return linhas;
    }

};

typedef CPigAreaDeTexto *PigAreaDeTexto;

#endif // _CPigAreaDeTexto_
