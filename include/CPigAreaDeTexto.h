#include <iostream>

class CPigAreaDeTexto: public CPigCaixaTexto{

private:

    int largMaxTexto;
    int espacoEntreLinhas;
    int altLetra;
    bool linhasAbaixoTexto;
    bool marcarMargem;
    std::vector<std::string> linhas;

    PIG_Cor corLinhasTexto;

    //recupera o texto todo da área
    inline std::string GetTextoVisivel(){
        return GetTexto();
    }

    //ajusta o alinhamento do texto dentro da área
    void AjustaAlinhamento() override{
        std::string textoBase = GetTextoVisivel();
        linhas = ExtraiLinhasString(textoBase,largMaxTexto,fonteTexto);
        std::string aux;

        xBase = xBaseOriginal;
        yBase = yBaseOriginal;

        aux.assign(textoBase,GetPosInicialDeUmaLinha(GetLinhaDeUmaPos(posCursor)),posCursor - GetPosInicialDeUmaLinha(GetLinhaDeUmaPos(posCursor)));
        yCursor = yBase - ( espacoEntreLinhas*GetLinhaDeUmaPos(posCursor));

        xCursor = xBase + CalculaLarguraPixels((char*)aux.c_str(),fonteTexto);

        AjustaBaseTextoEixoX(CalculaLarguraPixels((char*)aux.c_str(),fonteTexto));
    }

    //desenha o texto e as linhas (se for o caso)
    void DesenhaElementosEspecificos()override{
        EscreverLongaEsquerda((char*)texto.c_str(),xBase,yBase,largMaxTexto,espacoEntreLinhas,fonteTexto);
        if(linhasAbaixoTexto) DesenhaLinhasHorizontais();
        if(marcarMargem) DesenhaMarcacaoMargem();
    }

    //
    void AjustaBaseTextoEixoY(int largParcial){
        while(yCursor < y + margemVertBaixo){
            yBase+=5;
            yCursor = yBase - ( espacoEntreLinhas * GetLinhaDeUmaPos(posCursor));
        }
        while(yCursor > y +alt - margemVertCima){
            yBase-=5;
            yCursor = yBase - ( espacoEntreLinhas * GetLinhaDeUmaPos(posCursor));
        }
    }

    //trata o evento do botao esquerdo
    int TrataMouseBotaoEsquerdo(SDL_Point p,int inicioLinha = 0)override{

        TrataMouseBotaoEsquerdoESobeDesceCursor(p,GetPosInicialDeUmaLinha(GetLinhaComMouseEmCima()),GetLinhaComMouseEmCima());
    }

    //Trata evento botao esquerdo e sobe e desce o cursor pelas setas
    int TrataMouseBotaoEsquerdoESobeDesceCursor(SDL_Point p,int inicioLinha = 0,int linha = 0){
        int delta = p.x-xBase;

        if(delta < CalculaLarguraPixels((char*)linhas[linha].c_str(),fonteTexto)){
            CPigCaixaTexto::TrataMouseBotaoEsquerdo(p,inicioLinha);
        }else{
            posCursor = inicioLinha + linhas[linha].size();
        }

        AjustaAlinhamento();
        if (estado==COMPONENTE_NORMAL)
            DefineEstado(COMPONENTE_EDITANDO);

        return 1;
    }

    //trata o evento da rodinha
    int TrataMouseRodinha(PIG_Evento evento){
        if(evento.mouse.acao == MOUSE_RODINHA){
            if(evento.mouse.relY >0){
                if(yBaseOriginal < yBase){
                    yBase-=10;
                    yCursor-=10;
                }
            }

            if(evento.mouse.relY <0){
                if( yBase < yBaseOriginal + ( espacoEntreLinhas*(linhas.size()-1))){
                    yBase+=10;
                    yCursor+=10;
                }
            }

            return 2;
        }
    }

    //
    int GetLinhaComMouseEmCima(){
        SDL_Point p;
        CMouse::PegaXY(p.x,p.y);
        int yLinha=0;

        for(int i=0;i<linhas.size();i++){

            yLinha = yBase - (espacoEntreLinhas*i);
            if(p.y > yLinha && p.y <(yLinha + espacoEntreLinhas) ){
                return i;
            }
        }

        return (linhas.size()-1);
    }

    //
    int GetPosInicialDeUmaLinha(int linha){
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
    void DesenhaMarcacaoMargem(){
        DesenhaLinhaSimples(x+margemHorEsq,y+margemVertBaixo,x+ margemHorEsq,y+alt-margemVertCima,BRANCO);
        DesenhaLinhaSimples(x+larg-margemHorDir-1,y+margemVertBaixo,x+larg-margemHorDir-1,y+alt-margemVertCima,BRANCO);

        DesenhaLinhaSimples(x+margemHorEsq,y+alt-margemVertCima,x+larg-margemHorDir,y+alt-margemVertCima,BRANCO);
        DesenhaLinhaSimples(x+margemHorEsq,y+margemVertBaixo,x+larg-margemHorDir,y+margemVertBaixo,BRANCO);
    }

    //
    void DesenhaLinhasHorizontais(){
        int yLinha = yBase;
        int xLinha = x+margemHorEsq;
        int i=0;

        while(yLinha >= y + margemVertBaixo){
            DesenhaLinhaSimples(xLinha,yLinha,xLinha+larg-margemHorDir,yLinha,corLinhasTexto);
            i++;
            yLinha = yBase - (espacoEntreLinhas *i);
        }
    }

    int TrataMouseBotaoDireito(PIG_Evento evento,SDL_Point p){return 1;}//não usa o botão direito

public:

    CPigAreaDeTexto(int idComponente,int px, int py, int alt,int larg,char *nomeArq,int fonteDoTexto = 0,int fonteDoLabel = 0,int maxCars  = 200, bool apenasNumeros=false, int retiraFundo=1,int janela=0,int EspacoEntreLinhas =50,int LargMaxTexto =200,bool LinhasAbaixoTexto = false,bool marcarMargens = false):
        CPigCaixaTexto(idComponente,px,py,alt,larg,nomeArq,fonteDoTexto,fonteDoLabel,maxCars,apenasNumeros,retiraFundo,janela){
        margemHorEsq = margemHorDir = margemVertCima = margemVertBaixo = 60;
        altLetra = GetTamanhoFonte(fonteTexto); // A altura é um vetor, mas eu preciso dela, entao eu acabei colocando como o tamanho da fonte, qualquer coisa só mudar aqui
        espacoEntreLinhas = EspacoEntreLinhas + altLetra;
        yBaseOriginal = y+alt-margemVertCima-altLetra;
        xBaseOriginal = x+margemHorEsq;
        yBase = yBaseOriginal;
        xBase = xBaseOriginal;
        xCursor = xBase;
        yCursor = yBase;
        largMaxTexto = LargMaxTexto;
        linhasAbaixoTexto = LinhasAbaixoTexto;
        corLinhasTexto = PRETO;
        marcarMargem = marcarMargens;
    }

    //define as margens da áre de texto
    void SetMargens(int horEsq,int horDir, int vertBaixo,int vertCima){
        margemVertCima = vertCima;
        margemVertBaixo = vertBaixo;
        margemHorDir = horDir;
        margemHorEsq = horEsq;
        yBaseOriginal = y+alt-margemVertCima-altLetra;
        xBaseOriginal = x+margemHorEsq;
        AjustaAlinhamento();
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

    //define a cor da linhas horizontais
    void SetCorLinhasHorizontais(PIG_Cor cor){
        corLinhasTexto = cor;
    }

    //define a largura máxima do texto
    void SetLargMaxTexto(int largMax){
        largMaxTexto = largMax;
    }

    //define o espaçamento entre as linhas
    void SetEspacoEntreAsLinhas(int espaco){
        espacoEntreLinhas = espaco + altLetra;
    }

    //recupera o texto separado em linhas
    std::vector<std::string> GetLinhasTexto(){
        return linhas;
    }


};

typedef CPigAreaDeTexto *PigAreaDeTexto;
