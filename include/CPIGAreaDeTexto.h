#ifndef _CPIGAREADETEXTO_
#define _CPIGAREADETEXTO_

#include "CPIGCaixaTexto.h"
#include "CPIGSlideBar.h"

class CPIGAreaDeTexto: public CPIGCaixaTexto{

private:

    int espacoEntreLinhas;
    bool linhasPauta;
    PIGSlideBar slideVertical;
    bool slideVerticalAtivado;
    int tamPadraoSlide;
    vector<string> linhas;

    void ProcessaAtributos(CPIGAtributos atrib)override{
        CPIGCaixaTexto::ProcessaAtributos(atrib);

        int valorInt = atrib.GetInt("espacoEntreLinhas",0);
        if (valorInt > 0) SetEspacoEntreAsLinhas(valorInt);

        valorInt = atrib.GetInt("linhasVisiveis",0);
        if (valorInt != 0) SetLinhasAbaixoTexto(valorInt);

        string valorStr = atrib.GetString("corLinhas","");
        if (valorStr != "") SetCorLinhas(PIGCriaCorString(valorStr));
    }

    static CPIGAreaDeTexto LeParametros(int idComponente, CPIGAtributos atrib){
        CPIGAreaDeTexto *resp;

        if (atrib.GetString("nomeArq","")!=""){
            resp = new CPIGAreaDeTexto(idComponente,atrib.GetInt("altura",0),atrib.GetInt("largura",0),
                        atrib.GetString("nomeArq",""),atrib.GetInt("maxCaracters",200),
                        atrib.GetInt("retiraFundo",1),atrib.GetInt("janela",0));
        }else{
            resp = new CPIGAreaDeTexto(idComponente,atrib.GetInt("altura",0),atrib.GetInt("largura",0),
                        atrib.GetInt("maxCaracters",200),atrib.GetInt("janela",0));
        }

        resp->ProcessaAtributos(atrib);

        return *resp;
    }

    //Recupera todo o texto da área
    inline string GetTextoVisivel(){
        return GetTexto();
    }

    int GetLarguraLinhaMaior(){
        int tamMaior = 0;
        int temp = 0;
        for(string linha : linhas){
            temp = CPIGGerenciadorFontes::GetFonte(fonteTexto)->GetLarguraPixelsString(linha);
            tamMaior = (temp > tamMaior) ? (temp):(tamMaior);
        }
        return tamMaior;
    }

    void AjustaSlideVerticalPeloCursor(){
        int alturaTotalTexto = linhas.size()*(espacoEntreLinhas+altLetra);

        slideVerticalAtivado = alturaTotalTexto>(alt-margemCima+margemBaixo);

        //printf("vett ativado %d\n",slideVerticalAtivado);
        if (slideVerticalAtivado){
            slideVertical->SetValorMax(alturaTotalTexto-(alt-margemCima-margemBaixo));
            int deltaY=0;
            if (yCursor<pos.y+margemBaixo){
                deltaY = pos.y+margemBaixo-yCursor;
                //printf("posy %d marg %d yC %d",(int)pos.y,margemVertBaixo,yCursor);
            }else if (yCursor+altLetra>pos.y+alt-margemCima){
                deltaY = (pos.y+alt-margemCima) - (yCursor+altLetra);
                //printf("posy %d alt %d marg %d yC %d",(int)pos.y,alt,margemVertCima,yCursor+altLetra);
            }
            //printf(" deltaY %d\n",deltaY);
            yCursor += deltaY;
            yTexto += deltaY;
            slideVertical->AvancaMarcador(deltaY);
        }
    }

    //Desenha um contorno baseado nas dimensoes reais da área(somando a área em si e a scroll bar)
    //void DesenhaMarcacaoMargem(){
    //    CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetanguloVazado(pos.x+margemHorEsq,pos.y+margemVertBaixo,alt-margemVertBaixo-margemVertCima-1,larg-margemHorDir-margemHorEsq,coresBasicas[2]);
    //}

    void IniciaPosicaoTexto(){
        yTexto = pos.y + alt-altLetra-margemCima;
        xTexto = pos.x + margemEsq;
    }

    //Ajusta o alinhamento do texto quando ocorre alguma modificaçăo
    void AjustaPosicaoTextoCursor()override{
        string textoBase = GetTextoVisivel();
        string aux;

        linhas = CPIGGerenciadorFontes::GetFonte(fonteTexto)->ExtraiLinhas(textoBase,larg-(margemEsq+margemDir));

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

    PIGEstadoEvento PosicionaCursorLinha(int linha, int xLinha){
        if (linha<0||(linhas.size()>0&&linha>=linhas.size()))
            return PIG_COMPONENTE_NAOTRATADO;

        int posInicial = GetPosInicialDeUmaLinha(linha);
        //printf("posInicial %d\n",posInicial);

        posCursor = posInicial;
        if (linhas.size()>0)
            posCursor += CalculaPosicaoCursor(linhas[linha],xLinha);
        //printf("posCursor %d\n",posCursor);

        AjustaPosicaoTextoCursor();
        AjustaSlideVerticalPeloCursor();
        return PIG_COMPONENTE_TRATADO;
    }

    inline int MouseSobreSlide(SDL_Point p){
        return (p.x>pos.x+larg&&p.x<pos.x+larg+tamPadraoSlide&&p.y>pos.y&&p.y<pos.y+alt);
    }

    //trata o evento do botao esquerdo
    PIGEstadoEvento TrataMouseBotaoEsquerdo(SDL_Point p, int inicioLinha=0)override{
        int linha = GetLinhaPonto(p);
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
    int GetPosInicialDeUmaLinha(unsigned int linha){
        if (linhas.size()==0) return 0;
        if (linha>=linhas.size()) return texto.size();

        int resp = 0;
        for(unsigned int i=0;i<linha;i++){
            resp += linhas[i].size();
        }

        return resp;
    }

    //retorna em que linha está qualquer uma das posições da string texto
    int GetLinhaDeUmaPos(int pos){
        if (linhas.size()==0) return 0;
        int qntPosicoes = 0;

        for(unsigned int i=0;i<linhas.size();i++){
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
        int xLinha = pos.x+margemEsq;

        while(yLinha >= pos.y+margemBaixo){
            CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaLinhaSimples(xLinha,yLinha,xLinha+larg-margemDir,yLinha,coresBasicas[2]);
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
        string aux = "";
        string auxB = "";

        aux.assign(texto,0,posCursor);
        auxB += aux;
        auxB += '\n';
        aux.assign(texto,posCursor,texto.size() - posCursor);
        auxB +=aux;

        texto = auxB;
        AvancaCursor();
        AjustaSlideVerticalPeloCursor();
        return 1;
    }

    void IniciaBase(){
        espacoEntreLinhas = 0;
        linhasPauta = false;
        slideVerticalAtivado = false;
        tamPadraoSlide = 20;

        slideVertical = new CPIGSlideBar(id+2,alt,tamPadraoSlide,tamPadraoSlide,tamPadraoSlide,idJanela);
        slideVertical->Move(((int)pos.x)+larg,(int)pos.y);
        slideVertical->SetOrientacao(PIG_GAUGE_CIMA_BAIXO);
        AjustaPosicaoTextoCursor();
        CPIGCaixaTexto::IniciaCoresBasicas();
        coresBasicas[3] = AZUL;
        tipo = PIG_AREADETEXTO;
    }

public:

    CPIGAreaDeTexto(int idComponente, int altura, int largura, string nomeArq, int maxCars=PIG_MAX_CARS_CAIXATEXTO, int retiraFundo=1, int janela=0):
        CPIGCaixaTexto(idComponente,altura,largura,nomeArq,maxCars,retiraFundo,janela){
            IniciaBase();
        }

    CPIGAreaDeTexto(int idComponente, int altura, int largura, int maxCars=PIG_MAX_CARS_CAIXATEXTO, int janela=0):
        CPIGCaixaTexto(idComponente,altura,largura,maxCars,janela){
            IniciaBase();
        }

    CPIGAreaDeTexto(int idComponente,CPIGAtributos atrib):CPIGAreaDeTexto(LeParametros(idComponente,atrib)){}

    virtual ~CPIGAreaDeTexto(){
        linhas.clear();
        delete slideVertical;
    }

    void Move(double nx,double ny)override{
        int dx = nx-pos.x;
        int dy = ny-pos.y;
        Desloca(dx,dy);
    }

    void Desloca(double dx,double dy)override{
        CPIGCaixaTexto::Desloca(dx,dy);
        slideVertical->Desloca(dx,dy);
    }

    void SetDimensoes(int altura,int largura)override{
        CPIGSprite::SetDimensoes(altura,largura);
        slideVertical->Move(((int)pos.x)+largura,(int)pos.y);
        slideVertical->SetDimensoes(altura,tamPadraoSlide);
        PosicionaLabel();
        AjustaPosicaoTextoCursor();
        AjustaSlideVerticalPeloCursor();
    }

    int Desenha() override{
        if (!visivel) return 0;

        //imagem de fundo
        if (imagemPropria)
            CPIGSprite::Desenha();
        else CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetangulo((int)pos.x,(int)pos.y,alt,larg,coresBasicas[0]);

        //DesenhaMarcacaoMargem();
        CPIGGerenciadorJanelas::GetJanela(idJanela)->BloqueiaArea(pos.x+margemEsq,pos.y+margemBaixo,alt-(margemBaixo+margemCima),larg-(margemEsq+margemDir));

        DesenhaCursor();//desenha o cursor (se estiver em ediçăo)
        CPIGGerenciadorFontes::GetFonte(fonteTexto)->EscreveLonga(texto,xTexto,yTexto,larg-(margemEsq+margemDir),(espacoEntreLinhas + altLetra),coresBasicas[1],PIG_TEXTO_ESQUERDA);

        //desbloqueia o desenho fora da area do componente
        CPIGGerenciadorJanelas::GetJanela(idJanela)->DesbloqueiaArea();

        if(linhasPauta) DesenhaLinhasHorizontais();

        if(slideVerticalAtivado) slideVertical->Desenha();

        return CPIGComponente::Desenha();
    }

    void SetFonteTexto(int fonte) override{
        CPIGCaixaTexto::SetFonteTexto(fonte);
        AjustaPosicaoTextoCursor();
        AjustaSlideVerticalPeloCursor();
    }

    //define se as linhas horizontais serao visiveis
    void SetLinhasAbaixoTexto(bool visivel){
        linhasPauta = visivel;
    }

    //define a cor da linhas horizontais
    void SetCorLinhas(PIGCor cor){
        coresBasicas[3] = cor;
    }

    PIGEstadoEvento TrataEventoMouse(PIGEvento evento)override{
        if (!habilitado) return PIG_COMPONENTE_DESABILITADO;
        if (!visivel) return PIG_COMPONENTE_INVISIVEL;

        SDL_Point p = GetPosicaoMouse();
        ChecaMouseOver(p);

        if(slideVerticalAtivado&&MouseSobreSlide(p)){
            ((PIGComponente)slideVertical)->SetFoco(true);
            PIGEstadoEvento resp = slideVertical->TrataEventoMouse(evento);
            ((PIGComponente)slideVertical)->SetFoco(false);
            if (resp==PIG_COMPONENTE_TRATADO){
                AjustaPosicaoTextoCursor();
                return resp;
            }else if (evento.tipoEvento==PIG_EVENTO_MOUSE&&evento.mouse.acao==PIG_MOUSE_RODINHA){
                if (evento.mouse.relY>0)
                    SobeCursor();
                else if (evento.mouse.relY<0)
                    DesceCursor();
                return PIG_COMPONENTE_TRATADO;
            }
        }

        if(mouseOver){
            if (evento.mouse.acao == PIG_MOUSE_PRESSIONADO && evento.mouse.botao == PIG_MOUSE_ESQUERDO)
                return TrataMouseBotaoEsquerdo(p);
            return PIG_COMPONENTE_MOUSEOVER;
        }

        return PIG_COMPONENTE_NAOTRATADO;
    }


    //define o espaçamento entre as linhas
    void SetEspacoEntreAsLinhas(int espaco){
        espacoEntreLinhas = espaco;
        AjustaPosicaoTextoCursor();
        AjustaSlideVerticalPeloCursor();
    }

    int SetTexto(string frase)override{
        CPIGCaixaTexto::SetTexto(frase);
        AjustaPosicaoTextoCursor();
        AjustaSlideVerticalPeloCursor();
        return texto.size();
    }

    int AdicionaTexto(string frase)override{
        CPIGCaixaTexto::AdicionaTexto(frase);
        AjustaSlideVerticalPeloCursor();
        AjustaPosicaoTextoCursor();
        return texto.size();
    }

    //recupera o texto separado em linhas
    vector<string> GetLinhasTexto(){
        return linhas;
    }

};

typedef CPIGAreaDeTexto *PIGAreaDeTexto;
#endif // _CPIGAREADETEXTO_
