#ifndef _CPIGAREADETEXTO_
#define _CPIGAREADETEXTO_

#include "CPIGCaixaTexto.h"

class CPIGAreaDeTexto: public CPIGCaixaTexto{

private:

    int largMax;
    int espacoEntreLinhas;
    bool linhasPauta;
    CPIGScrollBar *scrollVertical,*scrollHorizontal;
    bool scrollVerticalAtivado,scrollHorizontalAtivado;
    int xOriginal,yOriginal;

    std::vector<std::string> linhas;

    PIG_Cor corLinhasTexto;

    //Recupera todo o texto da área
    inline std::string GetTextoVisivel(){
        return GetTexto();
    }

    void AjustaVisaoScrollVertical(){
        int valorAtual = scrollVertical->GetValorAtual();
        if(valorAtual!=yBase){
            yBase = valorAtual;
            scrollVertical->SetValorMinMax(yBaseOriginal,yBaseOriginal + ((espacoEntreLinhas + altLetra)*(linhas.size()-1)));
            scrollVertical->SetValorAtual(yBase);
            yCursor = yBase - ( (espacoEntreLinhas + altLetra) * GetLinhaDeUmaPos(posCursor));
        }
    }

    void AjustaVisaoScrollHorizontal(){
        int valorAtual = scrollHorizontal->GetValorAtual();
        if(xBase != valorAtual){
            xBase = valorAtual;
            std::string aux;
            int posInicial = GetPosInicialDeUmaLinha(GetLinhaDeUmaPos(posCursor));
            scrollHorizontal->SetValorMinMax(xBaseOriginal - GetLarguraLinhaMaior() + (larg - (margemHorDir+margemHorEsq)),xBaseOriginal);
            scrollHorizontal->SetValorAtual(xBase);
            aux.assign(GetTextoVisivel(),posInicial,posCursor - posInicial);
            xCursor = xBase + CPIGGerenciadorFontes::GetFonte(fonteTexto)->GetLarguraPixelsString(aux);
        }
    }

    //Verifica se é necessário acionar a ScrollBarVertical quando o texto é modificado
    void AcionaScrollBarVertical(){
        scrollVerticalAtivado = ((espacoEntreLinhas + altLetra)*(linhas.size())) > (alt - (margemVertBaixo+margemVertCima));
        scrollVertical->SetVisivel(scrollVerticalAtivado);
    }

    //Verifica se é necessário acionar a ScrollBarHorizontal quando o texto é modificado
    void AcionaScrollBarHorizontal(){
        scrollHorizontalAtivado = GetLarguraLinhaMaior() > (larg - (margemHorDir+margemHorEsq));
        scrollHorizontal->SetVisivel(scrollHorizontalAtivado);
    }

    int GetLarguraLinhaMaior(){
        int tamMaior = 0;
        int temp = 0;
        for(std::string linha : linhas){
            temp = CPIGGerenciadorFontes::GetFonte(fonteTexto)->GetLarguraPixelsString(linha);
            tamMaior = (temp > tamMaior) ? (temp):(tamMaior);
        }
        return tamMaior;
    }

    //Desenha um contorno baseado nas dimensoes reais da área(somando a área em si e a scroll bar)
    void DesenhaMarcacaoMargem(){
        CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaLinhaSimples(pos.x+margemHorEsq,pos.y+margemVertBaixo,pos.x+ margemHorEsq,pos.y+alt-margemVertCima,BRANCO);
        CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaLinhaSimples(pos.x+larg-margemHorDir,pos.y+margemVertBaixo,pos.x+larg-margemHorDir,pos.y+alt-margemVertCima,BRANCO);

        CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaLinhaSimples(pos.x+margemHorEsq,pos.y+alt-margemVertCima,pos.x+larg-margemHorDir,pos.y+alt-margemVertCima,BRANCO);
        CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaLinhaSimples(pos.x+margemHorEsq,pos.y+margemVertBaixo,pos.x+larg-margemHorDir,pos.y+margemVertBaixo,BRANCO);
    }

    //Volta a base e o cursor para o início
    void ResetaValoresBase(){
        yCursor = yBase = yBaseOriginal = pos.y + alt-altLetra-margemVertCima;
        xCursor = xBase = xBaseOriginal = pos.x + margemHorEsq;
        AjustaAlinhamento();
    }

    //Serve no caso em que o y do cursor fica fora da área visível
    void AjustaBaseTextoEixoY(){
        while(yCursor < pos.y + margemVertBaixo){
            yBase+=1;
            yCursor+=1;
        }
        while(yCursor > pos.y + alt - altLetra - margemVertCima){
            yBase-=1;
            yCursor-=1;
        }
    }

    //Ajusta o alinhamento do texto quando ocorre alguma modificação
    void AjustaAlinhamento() override{
        std::string textoBase = GetTextoVisivel();
        std::string aux;

        linhas = CPIGGerenciadorFontes::GetFonte(fonteTexto)->ExtraiLinhas(textoBase,largMax);

        int linhaPos = GetLinhaDeUmaPos(posCursor);
        int posInicial = GetPosInicialDeUmaLinha(linhaPos);

        aux.assign(textoBase,posInicial,posCursor - posInicial);

        yCursor = yBase - ( (espacoEntreLinhas + altLetra)*GetLinhaDeUmaPos(posCursor));
        xCursor = xBase + CPIGGerenciadorFontes::GetFonte(fonteTexto)->GetLarguraPixelsString(aux);

        if(scrollVertical) AcionaScrollBarVertical();
        if(scrollHorizontal) AcionaScrollBarHorizontal();

        AjustaBaseTextoEixoX(CPIGGerenciadorFontes::GetFonte(fonteTexto)->GetLarguraPixelsString(aux));
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
            if(delta < CPIGGerenciadorFontes::GetFonte(fonteTexto)->GetLarguraPixelsString(linhas[linha])){
                CPIGCaixaTexto::TrataMouseBotaoEsquerdo(p,inicioLinha);
            }else{
                posCursor = inicioLinha + linhas[linha].size();
            }
        }

        AjustaAlinhamento();

        return PIG_SELECIONADO_TRATADO;
    }

    //
    int GetLinhaComMouseEmCima(){
        int yLinha=0;
        SDL_Point p;
        if (CPIGGerenciadorJanelas::GetJanela(idJanela)->GetUsandoCameraFixa())
            p = CPIGMouse::PegaXYTela();
        else p = CPIGMouse::PegaXYWorld();

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
        int xLinha = pos.x;
        int i=0;

        while(yLinha >= pos.y){
            CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaLinhaSimples(xLinha,yLinha,xLinha+larg,yLinha,corLinhasTexto);
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
        return 1;
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

    CPIGAreaDeTexto(int idComponente,int px, int py, int altura,int largura,std::string nomeArq,int maxCars = 200,int retiraFundo=1,int janela=0):
        CPIGCaixaTexto(idComponente,px,py,altura,largura,nomeArq,maxCars,false,retiraFundo,janela){ // A altura é um vetor, mas eu preciso dela, entao eu acabei colocando como o tamanho da fonte, qualquer coisa só mudar aqui
            espacoEntreLinhas = 0;
            yCursor = yBase = yBaseOriginal = pos.y + altura-altLetra - margemVertCima;
            xCursor = xBase = xBaseOriginal = pos.x + margemHorEsq;
            largMax = largura;
            linhasPauta = false;
            corLinhasTexto = PRETO;
            scrollHorizontalAtivado = scrollVerticalAtivado = false;
            scrollHorizontal = scrollVertical = NULL;
            xOriginal = pos.x;
            yOriginal = pos.y;
            AjustaAlinhamento();
        }

    CPIGAreaDeTexto(std::string nomeArqParam):CPIGAreaDeTexto(LeArquivoParametros(nomeArqParam)){}

    ~CPIGAreaDeTexto(){
        linhas.clear();
    }

    static CPIGAreaDeTexto LeArquivoParametros(std::string nomeArqParam){

        std::ifstream arquivo;
        int idComponente,px,py,altura,largura,maxCars = 200,retiraFundo=1,janela=0;
        std::string nomeArq = "",variavel;

        arquivo.open(nomeArqParam);

        if(!arquivo.is_open()) throw CPIGErroArquivo(nomeArqParam);
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

        if(nomeArq == "") throw CPIGErroParametro("nomeArq",nomeArqParam);

       // std::cout<<idComponente<<" "<<px<<" "<<py<<" "<<altura<<" "<<largura<<" "<<nomeArq<<" "<<retiraFundo<<" "<<janela<<std::endl;
        return CPIGAreaDeTexto(idComponente,px,py,altura,largura,nomeArq,maxCars,retiraFundo,janela);

    }

    void SetScrollBarVertical(int larguraTotal,int comprimentoTotal,int larguraHandle,std::string imgHandle,std::string imgTrilha,int retiraFundoHandle=1,int retiraFundoTrilha=1){
        scrollVertical = new CPIGScrollBar(id + 1,pos.x + larg,pos.y,larguraTotal,comprimentoTotal,larguraHandle,imgHandle,imgTrilha,retiraFundoHandle,retiraFundoTrilha,idJanela);
        scrollVertical->SetOrientacao(PIG_VERTICAL);
        int posYUltLinha = yBase - ((espacoEntreLinhas + altLetra)*linhas.size());
        scrollVertical->SetValorMinMax(yBase,posYUltLinha);
        scrollVertical->MudaOrientacaoCrescimento();
        scrollVerticalAtivado = false;
        scrollVertical->SetVisivel(false);
        SetPosPadraoScrollVertical(PIG_COMPONENTE_DIR_CENTRO);
        scrollVertical->SetAreaDeAcaoScroll(pos.x,pos.y,alt,larg);
    }

    void SetScrollBarHorizontal(int larguraTotal,int comprimentoTotal,int larguraHandle,std::string imgHandle,std::string imgTrilha,int retiraFundoHandle=1,int retiraFundoTrilha=1){
        scrollHorizontal = new CPIGScrollBar(id + 1,pos.x,pos.y - larguraTotal,larguraTotal,comprimentoTotal,larguraHandle,imgHandle,imgTrilha,retiraFundoHandle,retiraFundoTrilha,idJanela);
        int maiorTamLinha = GetLarguraLinhaMaior();
        scrollHorizontal->SetValorMinMax(xBaseOriginal,xBaseOriginal + maiorTamLinha);
        scrollHorizontal->MudaOrientacaoCrescimento();
        scrollHorizontalAtivado = false;
        scrollHorizontal->SetVisivel(false);
        SetPosPadraoScrollHorizontal(PIG_COMPONENTE_BAIXO_CENTRO);
        scrollHorizontal->SetAreaDeAcaoScroll(pos.x,pos.y,alt,larg);
    }

    int SetBotoesScrollBarVertical(int larguraBotoes,std::string imgBotao1,std::string imgBotao2,int retiraFundoB1 = 1,int retiraFundoB2 = 1){
        if(!scrollVertical) return -1;
        scrollVertical->SetBotoes(larguraBotoes,imgBotao1,imgBotao2,retiraFundoB1,retiraFundoB2);
        return 1;
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
        CPIGSprite::Move(px,py);
        xOriginal = px;
        yOriginal = py;
        if(scrollHorizontal){
            scrollHorizontal->SetPosPadraoExternaComponente(scrollHorizontal->GetPosComponente(),this);
            scrollHorizontal->SetAreaDeAcaoScroll(pos.x,pos.y,larg,alt);
        }
        if(scrollVertical){
            scrollVertical->SetPosPadraoExternaComponente(scrollVertical->GetPosComponente(),this);
            scrollVertical->SetAreaDeAcaoScroll(pos.x,pos.y,larg,alt);
        }
        ResetaValoresBase();
    }

    void MoveScrollBarHorizontal(int px,int py){
        if(scrollHorizontal) scrollHorizontal->Move(px,py);
    }

    void MoveScrollBarVertical(int px,int py){
        if(scrollVertical) scrollVertical->Move(px,py);
    }

    void SetDimensoes(int altura,int largura)override{
        CPIGSprite::SetDimensoes(altura,largura);
        PosicionaLabel();
        if(scrollHorizontal){
            scrollHorizontal->SetPosPadraoExternaComponente(scrollHorizontal->GetPosComponente(),this);
            scrollHorizontal->SetAreaDeAcaoScroll(pos.x,pos.y,larg,alt);
        }
        if(scrollVertical){
            scrollVertical->SetPosPadraoExternaComponente(scrollVertical->GetPosComponente(),this);
            scrollVertical->SetAreaDeAcaoScroll(pos.x,pos.y,larg,alt);
        }
        ResetaValoresBase();
    }

    int Desenha() override{
        //imagem de fundo

        CPIGSprite::Desenha();//SDL_RenderCopyEx(renderer, text, &frames[frameAtual],&dest,-angulo,&pivoRelativo,flip);

        DesenhaMarcacaoMargem();

        if(scrollVerticalAtivado){
            AjustaVisaoScrollVertical();
            scrollVertical->Desenha();
        }
        if(scrollHorizontalAtivado){
            AjustaVisaoScrollHorizontal();
            scrollHorizontal->Desenha();
        }

        DesenhaLabel();

        SDL_Rect r={(int)pos.x+margemHorEsq,*altJanela-((int)pos.y)-alt+margemVertCima,larg-(margemHorEsq+margemHorDir),alt-(margemVertBaixo+margemVertCima)};
        CPIGGerenciadorJanelas::GetJanela(idJanela)->ConverteCoordenadaWorldScreen(r.x,r.y,r.x,r.y);

        SDL_RenderSetClipRect(renderer,&r);

        DesenhaCursor();//desenha o cursor (se estiver em edição)
        CPIGGerenciadorFontes::GetFonte(fonteTexto)->EscreveLonga(texto,xBase,yBase,largMax,(espacoEntreLinhas + altLetra),BRANCO,PIG_TEXTO_ESQUERDA);
        if(linhasPauta) DesenhaLinhasHorizontais();

        //desbloqueia o desenho fora da area do componente
        SDL_RenderSetClipRect(renderer,NULL);

        EscreveHint();

        return 1;
    }

    void SetFonteTexto(int fonte) override{
        CPIGCaixaTexto::SetFonteTexto(fonte);
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
        SDL_Point p = CPIGMouse::PegaXYWorld();
        ChecaMouseOver(p);

        if(scrollVerticalAtivado) scrollVertical->TrataEventoMouse(evento);
        if(scrollHorizontalAtivado) scrollHorizontal->TrataEventoMouse(evento);

        if(mouseOver){
            if(!habilitado) return PIG_SELECIONADO_DESABILITADO;
            if(!visivel) return PIG_SELECIONADO_INVISIVEL;
            if (evento.mouse.acao == PIG_MOUSE_PRESSIONADO && evento.mouse.botao == PIG_MOUSE_ESQUERDO) return TrataMouseBotaoEsquerdo(p);
            return PIG_SELECIONADO_MOUSEOVER;
        }

        return PIG_NAO_SELECIONADO;
    }

    int TrataEventoTeclado(PIG_Evento evento)override{
        return CPIGCaixaTexto::TrataEventoTeclado(evento);
    }

    //define o espaçamento entre as linhas
    void SetEspacoEntreAsLinhas(int espaco){
        espacoEntreLinhas = espaco;
    }

    int SetTexto(std::string frase)override{
        CPIGCaixaTexto::SetTexto(frase);
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

typedef CPIGAreaDeTexto *PIGAreaDeTexto;

#endif // _CPIGAREADETEXTO_
