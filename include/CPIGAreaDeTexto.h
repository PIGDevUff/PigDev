#ifndef _CPIGAREADETEXTO_
#define _CPIGAREADETEXTO_

#include "CPIGCaixaTexto.h"
#include "CPIGSlideBar.h"

class CPIGAreaDeTexto: public CPIGCaixaTexto{

private:

    int largMax;
    int espacoEntreLinhas;
    bool linhasPauta;
    PIGSlideBar slideVertical,slideHorizontal;
    bool slideVerticalAtivado,slideHorizontalAtivado;
    std::vector<std::string> linhas;
    PIG_Cor corLinhasPauta;

    CPIGAreaDeTexto LeParametros(int idComponente,string parametros){
        CPIGAtributos atrib = CPIGComponente::GetAtributos(parametros);

        CPIGAreaDeTexto resp(idComponente,atrib.GetInt("px",0),atrib.GetInt("py",0),atrib.GetInt("altura",0),atrib.GetInt("largura",0),
                        atrib.GetString("nomeArq",""),atrib.GetInt("maxCaracters",200),
                        atrib.GetInt("retiraFundo",1),atrib.GetInt("janela",0));

        return resp;
    }

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

    //Recupera todo o texto da área
    inline std::string GetTextoVisivel(){
        return GetTexto();
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

    void AjustaSlideVerticalPeloCursor(){
        int alturaTotalTexto = linhas.size()*(espacoEntreLinhas+altLetra);

        if ( alturaTotalTexto>(alt-margemVertCima+margemVertBaixo)){
            if (slideVerticalAtivado==false){
                slideVerticalAtivado = true;
                SetMargens(margemHorEsq,margemHorDir+20,margemVertBaixo,margemVertCima);
                SetLargMaxTexto(larg-margemHorDir-margemHorEsq);
            }
        }else slideVerticalAtivado = false;

        //printf("vett ativado %d\n",slideVerticalAtivado);
        if (slideVerticalAtivado){
            slideVertical->SetValorMax(alturaTotalTexto-(alt-margemVertCima-margemVertBaixo));
            int deltaY=0;
            if (yCursor<pos.y+margemVertBaixo){
                deltaY = pos.y+margemVertBaixo-yCursor;
                //printf("posy %d marg %d yC %d",(int)pos.y,margemVertBaixo,yCursor);
            }else if (yCursor+altLetra>pos.y+alt-margemVertCima){
                deltaY = (pos.y+alt-margemVertCima) - (yCursor+altLetra);
                //printf("posy %d alt %d marg %d yC %d",(int)pos.y,alt,margemVertCima,yCursor+altLetra);
            }
            //printf(" deltaY %d\n",deltaY);
            yCursor += deltaY;
            yTexto += deltaY;
            slideVertical->AvancaMarcador(deltaY);
        }
    }

    //Desenha um contorno baseado nas dimensoes reais da área(somando a área em si e a scroll bar)
    void DesenhaMarcacaoMargem(){
        PIGDesenhaRetanguloVazado(pos.x+margemHorEsq,pos.y+margemVertBaixo,alt-margemVertBaixo-margemVertCima-1,larg-margemHorDir-margemHorEsq,corLinhasPauta);
    }

    void IniciaPosicaoTexto(){
        yTexto = pos.y + alt-altLetra-margemVertCima;
        xTexto = pos.x + margemHorEsq;
    }

    //Ajusta o alinhamento do texto quando ocorre alguma modificaçăo
    void AjustaPosicaoTextoCursor()override{
        std::string textoBase = GetTextoVisivel();
        std::string aux;

        linhas = CPIGGerenciadorFontes::GetFonte(fonteTexto)->ExtraiLinhas(textoBase,largMax);

        int linhaPos = GetLinhaDeUmaPos(posCursor);
        int posInicial = GetPosInicialDeUmaLinha(linhaPos);

        aux.assign(textoBase,posInicial,posCursor - posInicial);

        //posição inicial do texto
        IniciaPosicaoTexto();

        if (slideVerticalAtivado){
            yTexto += slideVertical->GetValorAtual();
        }

        //definir a posição do cursor
        yCursor = yTexto - ( (espacoEntreLinhas + altLetra)*GetLinhaDeUmaPos(posCursor));                //descobrindo em qual das linhas o cursor está
        xCursor = xTexto + CPIGGerenciadorFontes::GetFonte(fonteTexto)->GetLarguraPixelsString(aux);     //descobrindo em qual posição horizontal o cursor está

    }

    int PosicionaCursorLinha(int linha, int xLinha){
        if (linha<0||(linhas.size()>0&&linha>=linhas.size()))
            return PIG_NAO_SELECIONADO;

        int posInicial = GetPosInicialDeUmaLinha(linha);
        //printf("posInicial %d\n",posInicial);

        posCursor = posInicial;
        if (linhas.size()>0)
            posCursor += CalculaPosicaoCursor(linhas[linha],xLinha);
        //printf("posCursor %d\n",posCursor);
        AjustaPosicaoTextoCursor();
        AjustaSlideVerticalPeloCursor();
        return PIG_SELECIONADO_TRATADO;
    }

    //trata o evento do botao esquerdo
    int TrataMouseBotaoEsquerdo(SDL_Point p,int inicioLinha = 0)override{
        //printf("viu tratar esq\n");
        int linha = GetLinhaPonto(p);
        //printf("linha %d\n",linha);
        return PosicionaCursorLinha(linha,p.x);
    }

    //retorna o número da linha a partir de um ponto
    int GetLinhaPonto(SDL_Point p){
        if (linhas.size()==0) return 0;

        int deltaLinha=yTexto+altLetra+espacoEntreLinhas-p.y;

        int resp = deltaLinha / (altLetra+espacoEntreLinhas);
        //printf("deltaY %d div %d resp %d\n",deltaLinha,(altLetra+espacoEntreLinhas),resp);

        if (resp>=linhas.size())
            resp = linhas.size()-1;
        return resp;
    }

    //retorna a posição da string texto, na qual uma linha inicia
    int GetPosInicialDeUmaLinha(int linha){
        if (linhas.size()==0) return 0;
        if (linha>=linhas.size()) return texto.size();

        int resp = 0;
        for(int i=0;i<linha;i++){
            resp += linhas[i].size();
        }

        return resp;
    }

    //retorna em que linha está qualquer uma das posições da string texto
    int GetLinhaDeUmaPos(int pos){
        if (linhas.size()==0) return 0;
        int qntPosicoes = 0;

        for(int i=0;i<linhas.size();i++){
            qntPosicoes+=linhas[i].size();

            if(qntPosicoes >= pos){
                return i;
            }
        }

        return 0;
    }

    //
    void DesenhaLinhasHorizontais(){
        int yLinha = yTexto;
        int xLinha = pos.x+margemHorEsq;

        while(yLinha >= pos.y+margemVertBaixo){
            PIGDesenhaLinhaSimples(xLinha,yLinha,xLinha+larg-margemHorDir,yLinha,corLinhasPauta);
            yLinha -= (espacoEntreLinhas + altLetra);
        }
    }

    //move o cursor uma linha para cima
    int SobeCursor(){
        int linhaCursor = GetLinhaDeUmaPos(posCursor);

        if(linhaCursor > 0){
            return PosicionaCursorLinha(linhaCursor-1,xCursor);//posiciona na linha acima, o mais próximo possível no eixo x de onde estava na linha de baixo
        }
        return 0;
    }

    //move o cursor uma linha para baixo
    int DesceCursor(){
        int linhaCursor = GetLinhaDeUmaPos(posCursor);

        if(linhaCursor < linhas.size()-1 ){
            return PosicionaCursorLinha(linhaCursor+1,xCursor);//posiciona na linha abaixo, o mais próximo possível no eixo x de onde estava na linha de baixo
        }
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
        AjustaSlideVerticalPeloCursor();
        return 1;
    };



public:

    CPIGAreaDeTexto(int idComponente,int px, int py, int altura,int largura,std::string nomeArq,int maxCars = 200,int retiraFundo=1,int janela=0):
        CPIGCaixaTexto(idComponente,px,py,altura,largura,nomeArq,maxCars,false,retiraFundo,janela){ // A altura é um vetor, mas eu preciso dela, entao eu acabei colocando como o tamanho da fonte, qualquer coisa só mudar aqui
            espacoEntreLinhas = 0;
            largMax = largura;
            linhasPauta = false;
            corLinhasPauta = PRETO;
            slideHorizontalAtivado = slideVerticalAtivado = false;
            slideHorizontal = new CPIGSlideBar(idComponente+1,px,py,20,largura,"moldura2.png",20,20,"marcador.png",0,0);

            slideVertical = new CPIGSlideBar(idComponente+2,px+largura-20,py,altura,20,"moldura3.png",20,20,"marcador.png",0,0);
            slideVertical->SetOrientacao(PIG_GAUGE_CIMA_BAIXO);
            AjustaPosicaoTextoCursor();
        }

    CPIGAreaDeTexto(int idComponente,string parametros):CPIGAreaDeTexto(LeParametros(idComponente,parametros)){}

    ~CPIGAreaDeTexto(){
        linhas.clear();
        delete slideVertical;
        delete slideHorizontal;
    }

    void Move(double nx,double ny)override{
        CPIGCaixaTexto::Move(nx,ny);
        int dx = nx-pos.x;
        int dy = ny-pos.y;
        slideVertical->Desloca(dx,dy);
        slideHorizontal->Desloca(dx,dy);
    }

    void SetDimensoes(int altura,int largura)override{
        CPIGImagem::SetDimensoes(altura,largura);
        PosicionaLabel();
        AjustaPosicaoTextoCursor();
        AjustaSlideVerticalPeloCursor();
    }

    int Desenha() override{
        //imagem de fundo
        CPIGImagem::Desenha();

        PIGPreparaStencil();

        PIGDesenhaRetangulo(pos.x+margemHorEsq-1,pos.y+margemVertBaixo,alt-margemVertBaixo-margemVertCima,larg-margemHorEsq-margemHorDir+1,VERDE);

        PIGFixaStencil();

        //DesenhaMarcacaoMargem();

        //printf("texto: <%s> xbase\n",GetTextoVisivel().c_str(),xTexto);
        CPIGGerenciadorFontes::GetFonte(fonteTexto)->EscreveLonga(texto,xTexto,yTexto,largMax,(espacoEntreLinhas + altLetra),true,AZUL,PIG_TEXTO_ESQUERDA);
        DesenhaCursor();//desenha o cursor (se estiver em ediçăo)

        PIGLiberaStencil();

        DesenhaLabel();

        if(linhasPauta) DesenhaLinhasHorizontais();

        if(slideVerticalAtivado) slideVertical->Desenha();

        if(slideHorizontalAtivado) slideHorizontal->Desenha();

        EscreveHint();

        return 1;
    }

    void SetFonteTexto(int fonte) override{
        CPIGCaixaTexto::SetFonteTexto(fonte);
        AjustaPosicaoTextoCursor();
        AjustaSlideVerticalPeloCursor();
    }

    //define a cor da linhas horizontais
    void SetLinhasAbaixoTexto(bool visivel,PIG_Cor cor = PRETO){
        corLinhasPauta = cor;
        linhasPauta = visivel;
    }

    //define a largura máxima do texto
    void SetLargMaxTexto(int largMaxTexto){
        largMax = largMaxTexto;
        AjustaPosicaoTextoCursor();
        AjustaSlideVerticalPeloCursor();
    }

    int TrataEventoMouse(PIG_Evento evento){
        SDL_Point p = GetPosicaoMouse();
        ChecaMouseOver(p);

        if(slideVerticalAtivado){
            int resp = slideVertical->TrataEventoMouse(evento);
            if (resp==PIG_SELECIONADO_TRATADO){
                //printf("cliquei vert\n");
                AjustaPosicaoTextoCursor();
                return resp;
            }
        }

        //if(scrollHorizontalAtivado) scrollHorizontal->TrataEventoMouse(evento);

        if(mouseOver){
            if(!habilitado) return PIG_SELECIONADO_DESABILITADO;
            if(!visivel) return PIG_SELECIONADO_INVISIVEL;
            if (evento.mouse.acao == PIG_MOUSE_PRESSIONADO && evento.mouse.botao == PIG_MOUSE_ESQUERDO) return TrataMouseBotaoEsquerdo(p);
            return PIG_SELECIONADO_MOUSEOVER;
        }

        return PIG_NAO_SELECIONADO;
    }


    //define o espaçamento entre as linhas
    void SetEspacoEntreAsLinhas(int espaco){
        espacoEntreLinhas = espaco;
        AjustaPosicaoTextoCursor();
        AjustaSlideVerticalPeloCursor();
    }

    int SetTexto(std::string frase)override{
        CPIGCaixaTexto::SetTexto(frase);
        AjustaPosicaoTextoCursor();
        AjustaSlideVerticalPeloCursor();
    }

    int AdicionaTexto(string frase)override{
        CPIGCaixaTexto::AdicionaTexto(frase);
        AjustaSlideVerticalPeloCursor();
        AjustaPosicaoTextoCursor();

    }

    //recupera o texto separado em linhas
    std::vector<std::string> GetLinhasTexto(){
        return linhas;
    }

};

typedef CPIGAreaDeTexto *PIGAreaDeTexto;

#endif // _CPIGAREADETEXTO_
