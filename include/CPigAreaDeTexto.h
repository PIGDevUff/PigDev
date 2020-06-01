#include <iostream>

class CPigAreaDeTexto: public CPigCaixaTexto{

private:

    int largMax;
    int espacoEntreLinhas;
    bool linhasPauta;
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
        std::string aux;

        linhas = CGerenciadorFontes::ExtraiLinhasString(textoBase,largMax,fonteTexto);

        xBase = xBaseOriginal;
        yBase = yBaseOriginal;

        int linhaPos = GetLinhaDeUmaPos(posCursor);
        int posInicial = GetPosInicialDeUmaLinha(linhaPos);

        aux.assign(textoBase,posInicial,posCursor - posInicial);

        yCursor = yBase - ( (espacoEntreLinhas + altLetra)*GetLinhaDeUmaPos(posCursor));
        xCursor = xBase + CGerenciadorFontes::GetLarguraPixels(aux,fonteTexto);

        AjustaBaseTextoEixoX(CGerenciadorFontes::GetLarguraPixels(aux,fonteTexto));

        AjustaBaseTextoEixoY();
    }

    //desenha o texto e as linhas (se for o caso)
    void DesenhaElementosEspecificos()override{
        CGerenciadorFontes::EscreverLonga(texto,xBase,yBase,largMax,(espacoEntreLinhas + altLetra),fonteTexto,CPIG_TEXTO_ESQUERDA);
        if(linhasPauta) DesenhaLinhasHorizontais();
        if(marcarMargem) DesenhaMarcacaoMargem();
    }

    //
    void AjustaBaseTextoEixoY(){
        while(yCursor < y + margemVertBaixo){
            yBase+=5;
            yCursor = yBase - ( (espacoEntreLinhas + altLetra) * GetLinhaDeUmaPos(posCursor));
        }
        while(yCursor > y + alt - margemVertCima){
            yBase-=5;
            yCursor = yBase - ( (espacoEntreLinhas + altLetra) * GetLinhaDeUmaPos(posCursor));
        }
    }

    //trata o evento do botao esquerdo
    int TrataMouseBotaoEsquerdo(SDL_Point p,int inicioLinha = 0)override{
        TrataMouseBotaoEsquerdoESobeDesceCursor(p,GetPosInicialDeUmaLinha(GetLinhaComMouseEmCima()),GetLinhaComMouseEmCima());
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

        if (texto[posCursor-1]=='\n'){//se o cursor parou depois do fim da linha forçada pelo '\n', escreve antes deste caracter terminador
            posCursor--;
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
                if( yBase < yBaseOriginal + ( (espacoEntreLinhas + altLetra)*(linhas.size()-1))){
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
    void DesenhaMarcacaoMargem(){
        CGerenciadorJanelas::DesenhaLinhaSimples(x+margemHorEsq,y+margemVertBaixo,x+ margemHorEsq,y+alt-margemVertCima,BRANCO);
        CGerenciadorJanelas::DesenhaLinhaSimples(x+larg-margemHorDir-1,y+margemVertBaixo,x+larg-margemHorDir-1,y+alt-margemVertCima,BRANCO);

        CGerenciadorJanelas::DesenhaLinhaSimples(x+margemHorEsq,y+alt-margemVertCima,x+larg-margemHorDir,y+alt-margemVertCima,BRANCO);
        CGerenciadorJanelas::DesenhaLinhaSimples(x+margemHorEsq,y+margemVertBaixo,x+larg-margemHorDir,y+margemVertBaixo,BRANCO);
    }

    //
    void DesenhaLinhasHorizontais(){
        int yLinha = yBase;
        int xLinha = x+margemHorEsq;
        int i=0;

        while(yLinha >= y + margemVertBaixo){
            CGerenciadorJanelas::DesenhaLinhaSimples(xLinha,yLinha,xLinha+larg-margemHorDir,yLinha,corLinhasTexto);
            i++;
            yLinha = yBase - ((espacoEntreLinhas + altLetra) *i);
        }
    }

    int TrataMouseBotaoDireito(PIG_Evento evento,SDL_Point p){return 1;}//não usa o botão direito

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

public:

    CPigAreaDeTexto(int idComponente,int px, int py, int alt,int larg,std::string nomeArq,int maxCars = 200, bool apenasNumeros=false, int retiraFundo=1,int janela=0,int largMaxTexto =200,bool linhasAbaixoTexto = false,bool marcarMargens = false):
        CPigCaixaTexto(idComponente,px,py,alt,larg,nomeArq,maxCars,apenasNumeros,retiraFundo,janela){ // A altura é um vetor, mas eu preciso dela, entao eu acabei colocando como o tamanho da fonte, qualquer coisa só mudar aqui
        espacoEntreLinhas = 0;
        yBaseOriginal = y+alt-margemVertCima-altLetra;
        xBaseOriginal = x+margemHorEsq;
        yBase = yBaseOriginal;
        xBase = xBaseOriginal;
        xCursor = xBase;
        yCursor = yBase;
        largMax = largMaxTexto;
        linhasPauta = linhasAbaixoTexto;
        corLinhasTexto = PRETO;
        marcarMargem = marcarMargens;
        AjustaAlinhamento();
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

    //define a cor da linhas horizontais
    void SetCorLinhasHorizontais(PIG_Cor cor){
        corLinhasTexto = cor;
    }

    //define a largura máxima do texto
    void SetLargMaxTexto(int largMaxTexto){
        largMax = largMaxTexto;
        AjustaAlinhamento();
    }

    //define o espaçamento entre as linhas
    void SetEspacoEntreAsLinhas(int espaco){
        espacoEntreLinhas = espaco;
    }

    int SetTexto(std::string frase)override{
        CPigCaixaTexto::SetTexto(frase);
        AjustaAlinhamento();
    }

    void SetFonteTexto(int fonte) override{
        CPigCaixaTexto::SetFonteTexto(fonte);
        AjustaAlinhamento();
    }

    //recupera o texto separado em linhas
    std::vector<std::string> GetLinhasTexto(){
        return linhas;
    }

};

typedef CPigAreaDeTexto *PigAreaDeTexto;
