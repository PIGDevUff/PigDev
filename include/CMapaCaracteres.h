class CMapaCaracteres{

protected:

    static std::string PigDelimitadores;

    int **alturaExtra;
    int **larguraLetra;
    int janela;
    int fontDescent;
    int estiloFixo;

    SDL_Renderer *render;
    SDL_Texture ***glyphsT;
    TTF_Font *font;

    std::string nome;
    int tamFonte;

    std::vector<std::string> SeparaPalavras(std::string texto,std::string delim){
        std::vector<std::string> resp;
        int indice;

        std::string strAtual;
        for (int i=0;i<texto.size();i++){
            strAtual += texto[i];

            indice = delim.find(texto[i]);
            if (indice != std::string::npos){//achou delimitadores
                resp.push_back(strAtual);
                //strAtual.Print();
                strAtual = "";
            }
        }
        if (strAtual!=""){
            resp.push_back(strAtual);
        }
        return resp;
    }

    //versão antiga usada pelo David
    /*std::string TrataRetornoSeparaPalavraCaracterEspecial(int posAtual,int &posAnt,std::string txt,std::string Retorno){
        std::string aux;

        if(posAtual == posAnt){
            posAnt+=1;
            return Retorno;
        }

        aux.assign(txt,posAnt,posAtual - posAnt);
        posAnt = posAtual;
        return aux;
    }*/

    //versão antiga usada pelo David
    /*virtual std::string SeparaPalavra(int &posAnt,std::string txt){

        if(posAnt == txt.size()) return "";

        for(int i = posAnt;i<txt.size();i++){
            if(txt[i] == '\n') return TrataRetornoSeparaPalavraCaracterEspecial(i,posAnt,txt,"\n");
            if(txt[i] == ' ') return TrataRetornoSeparaPalavraCaracterEspecial(i,posAnt,txt," ");
        }

        std::string aux;
        aux.assign(txt,posAnt,txt.size() - posAnt);
        posAnt = txt.size();
        return aux;

    }*/

    //funcao que desenha o outline na fonte que está sendo produzida(o render precisa estar direcionado para a textura em questão)
    void FazOutline(Uint16 letra, int nivelOutline,PIG_Cor corOutline){
        TTF_SetFontOutline(font,nivelOutline);
        SDL_Surface *out = TTF_RenderGlyph_Blended(font,letra,corOutline);
        SDL_Texture *text = SDL_CreateTextureFromSurface(render,out);
        SDL_RenderCopy(render,text, NULL, NULL);
        SDL_DestroyTexture(text);
        SDL_FreeSurface(out);
        TTF_SetFontOutline(font,0);
    }

    //cria o conjunto de glifos das letras com as características fornecidas
    void CriaLetras(PIG_Estilo estilo, int nivelOutline, PIG_Cor corOutline, SDL_Texture *textFundo,  PIG_Cor corFonte=BRANCO){
        TTF_SetFontStyle(font,estilo);

        glyphsT[estilo] = (SDL_Texture**) malloc(sizeof(SDL_Texture*)*(ULTIMO_CAR-PRIMEIRO_CAR));
        larguraLetra[estilo] = (int*)malloc(sizeof(int*)*(ULTIMO_CAR-PRIMEIRO_CAR));
        alturaExtra[estilo] = (int*)malloc(sizeof(int*)*(ULTIMO_CAR-PRIMEIRO_CAR));

        for (Uint16 letra=PRIMEIRO_CAR;letra<ULTIMO_CAR;letra++){
            SDL_Surface *surf = TTF_RenderGlyph_Blended(font,letra,corFonte);//superficie gerada com a forna da letra simples
            SDL_Texture *textLetra = SDL_CreateTextureFromSurface(render,surf);//textura com a forma da letra da letra simples

            larguraLetra[estilo][letra-PRIMEIRO_CAR] = surf->w;//largura da letra com o estilo específico
            alturaExtra[estilo][letra-PRIMEIRO_CAR] = surf->h-tamFonte;//qtd de pixels a mais na altura, para letras maiúsculas acentudadas como Á, Ó, É...

            //cria uma textura renderizavel para aplicar as camadas (forma da letra, depois imagem de fundo)                                                        larguraLetra[estilo][letra-PRIMEIRO_CAR],tamFonte+alturaLetra[estilo][letra-PRIMEIRO_CAR]);
            glyphsT[estilo][letra-PRIMEIRO_CAR] = SDL_CreateTexture(render,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,surf->w,surf->h);

            SDL_SetRenderTarget(render, glyphsT[estilo][letra-PRIMEIRO_CAR]);//textura de destino

            //SDL_SetTextureAlphaMod(textLetra,255);
            SDL_SetTextureBlendMode(glyphsT[estilo][letra-PRIMEIRO_CAR],SDL_BLENDMODE_BLEND);
            SDL_RenderCopy(render,textLetra,NULL,NULL); //renderiza a letra na tetxura de destino

            if (textFundo){
                SDL_SetTextureBlendMode(textFundo,SDL_BLENDMODE_MOD);
                //SDL_SetTextureBlendMode(glyphsT[estilo][letra-PRIMEIRO_CAR],SDL_BLENDMODE_BLEND);
                SDL_RenderCopy(render,textFundo,NULL,NULL); //renderiza a textura de fundo por cima
            }

            if (nivelOutline>0)//faz o outline da letra, se houver
                FazOutline(letra,nivelOutline,corOutline);

            //SDL_SetRenderDrawColor(render,255,0,0,255);
            //SDL_Rect rect = {0,0,surf->w,surf->h};

            //SDL_RenderDrawRect(render,&rect);

            SDL_DestroyTexture(textLetra);
            SDL_FreeSurface(surf);
        }

    }

    //inicia os atributos da classe
    void IniciaBase(char *nomeFonte,int tamanhoFonte,int idJanela,PIG_Estilo estilo){
        nome.assign(nomeFonte);
        tamFonte = tamanhoFonte;
        janela = idJanela;
        estiloFixo = estilo;

        render = CGerenciadorJanelas::GetJanela(idJanela)->GetRenderer();
        font = TTF_OpenFont( nome.c_str(), tamanhoFonte );
        fontDescent = TTF_FontDescent(font);
        if (font==NULL)
            printf("Erro: arquivo de fonte (%s) nao localizado\n",nomeFonte);

        alturaExtra = (int**)malloc(sizeof(int)*(PIG_TOTALESTILOS));
        larguraLetra = (int**)malloc(sizeof(int)*(PIG_TOTALESTILOS));
        glyphsT = (SDL_Texture***) malloc(sizeof(SDL_Texture**)*(PIG_TOTALESTILOS));
        for (int i=0;i<PIG_TOTALESTILOS;i++){
            alturaExtra[i] = NULL;
            larguraLetra[i] = NULL;
            glyphsT[i] = NULL;
        }
    }

    CMapaCaracteres(){}

public:

    CMapaCaracteres(char *nomeFonte,int tamanhoFonte,int estilo, char *nomeFundo,int outline,PIG_Cor corOutline, int idJanela){
        IniciaBase(nomeFonte,tamanhoFonte,idJanela, estilo);

        SDL_Surface *fundo = IMG_Load(nomeFundo);//carrega a imagem de fundo
        SDL_Texture *textFundo = SDL_CreateTextureFromSurface(render,fundo);
        SDL_FreeSurface(fundo);

        CriaLetras(estilo, outline, corOutline, textFundo);

        SDL_SetRenderTarget(render, NULL);

        SDL_DestroyTexture(textFundo);
    }

    CMapaCaracteres(char *nomeFonte,int tamanhoFonte,int estilo, PIG_Cor corFonte,int outline,PIG_Cor corOutline, int idJanela){
        IniciaBase(nomeFonte,tamanhoFonte,idJanela, estilo);

        CriaLetras(estilo, outline, corOutline, NULL, corFonte);

        SDL_SetRenderTarget(render, NULL);
    }

    ~CMapaCaracteres(){
        TTF_CloseFont(font);
        for (int i=0;i<PIG_TOTALESTILOS;i++){
            if (glyphsT[i]){
                free(alturaExtra[i]);
                free(larguraLetra[i]);
                for (Uint16 j=PRIMEIRO_CAR;j<ULTIMO_CAR;j++){
                    SDL_DestroyTexture(glyphsT[i][j-PRIMEIRO_CAR]);
                }
                free(glyphsT[i]);
            }
        }
        free(glyphsT);
        free(larguraLetra);
        free(alturaExtra);
    }

    int GetFonteDescent(){
        return -fontDescent;//o valor armazenada fica negativo; a resposta é dada com valor positivo
    }

    int GetFonteAscent(){
        return TTF_FontAscent(font); //quantidade base de pixels acima da linha base da letra (não inclui acento de vogais maiúsculas)
    }

    PIG_Metricas_Fonte GetMetricasLetra(Uint16 letra, int estilo=0){
        PIG_Metricas_Fonte metrica;
        int xMin,xMax,yMin,yMax,adv;
        if(estiloFixo>=0)
            estilo = estiloFixo;

        TTF_SetFontStyle(font,estilo);
        letra = letra%256;
        TTF_GlyphMetrics(font,letra,&xMin,&xMax,&yMin,&yMax,&adv);

        metrica.descent = -yMin;
        metrica.ascent = yMax;
        metrica.altura = yMax-yMin;
        metrica.recuo = xMin;
        metrica.avanco = xMax;
        metrica.largura = xMax-xMin;
        return metrica;
    }

    int GetTamanhoBaseFonte(){
        return tamFonte;
    }

    int GetLineSkip(){
        return TTF_FontLineSkip(font);
    }

    /*int GetAlturaTotalLetra(Uint16 letra, int estilo=0){
        Uint16 aux = letra;
        aux = aux % 256;
        if(estiloFixo>=0)
            estilo = estiloFixo;
        return tamFonte+alturaExtra[estilo][aux-PRIMEIRO_CAR];
    }*/

    int GetLarguraLetra(Uint16 letra, int estilo=0){
        Uint16 aux = letra;
        aux = aux % 256;
        if(estiloFixo>=0)
            estilo = estiloFixo;
        return larguraLetra[estilo][aux-PRIMEIRO_CAR];
    }

    std::vector<std::string> ExtraiLinhas(std::string texto, int largMax, std::string delim=PigDelimitadores){
        std::vector<std::string> resp;
        std::vector<std::string> palavras = SeparaPalavras(texto,delim);

        std::string linhaAtual = palavras[0];   //linha atual (que está sendo montada) contém pelo menos a primeira palavra
        int tamanhoAtual = GetLarguraPixelsString(linhaAtual);

        for (int i=1;i<palavras.size();i++){
            std::string palavra = palavras[i];   //pega a próxima palavra
            int largPalavra = GetLarguraPixelsString(palavra);

            if (tamanhoAtual + largPalavra > largMax){//a palavra estouraria a largura máxima se fosse agregada                if (ttttt==0){
                resp.push_back(linhaAtual); //coloca a linha que está montada no vetor de linhas
                linhaAtual = palavra; //a palavra que estouraria o limite começa a próxima linha
                tamanhoAtual = largPalavra;
            }else{//não estourou o limite
                linhaAtual += palavra;
                tamanhoAtual += largPalavra;
            }

            if (palavra[palavra.size()-1]=='\n'){//se existe uma quebra de linha forçada
                resp.push_back(linhaAtual);

                //i++;
                if (++i<palavras.size()){
                    linhaAtual = palavras[i]; //começa uma nova linha com a p´roxima palavra
                }else linhaAtual = "";
            }
        }

        if (linhaAtual != ""){
            resp.push_back(linhaAtual); //pega a linha que sobrou do processamento (última linha que não foi quebrada)
        }

        palavras.clear();
        return resp;
    }

    //versão antiga usada pelo David
    /*std::vector<std::string> ExtraiLinhasString(std::string texto,int largMax){
        std::vector<std::string> linhas;
        std::string linhaAtual("");
        std::string linhaMaior("");
        std::string palavra = "";
        int posAnt=0;

        const std::string QUEBRALINHA = "\n";

        palavra = SeparaPalavra(posAnt,texto);

        while (palavra != ""){

            linhaMaior = linhaAtual + palavra;

            if(palavra == QUEBRALINHA){
                linhas.push_back(linhaAtual);
                linhaAtual = QUEBRALINHA;
            }else{

                if (GetLarguraPixelsString((char*)linhaMaior.c_str()) >largMax){

                    if(linhaAtual == QUEBRALINHA){
                        linhas.push_back(linhaMaior);
                        linhaAtual ="";
                    }else{
                        if(linhaAtual!=""){
                            linhas.push_back(linhaAtual);
                        }
                        linhaAtual = palavra;
                    }

                }else{
                    linhaAtual = linhaMaior;
                }
            }
            palavra = SeparaPalavra(posAnt,texto);
        }
        linhas.push_back(linhaAtual);
        return linhas;
    }*/

    virtual int GetLarguraPixelsString(std::string texto){
        int resp=0;
        Uint16 aux;

        for (int i=0;i<texto.size();i++){
            aux = texto[i];
            aux = aux % 256;
            if(texto[i] != '\n')
                resp += larguraLetra[estiloFixo][aux-PRIMEIRO_CAR];
        }

        return resp;
    }

    virtual void EscreveStringCentralizado(std::string texto,int x,int y,float ang=0){
        int larguraPixels = GetLarguraPixelsString(texto);
        EscreveStringEsquerda(texto,x-larguraPixels/2,y,ang,larguraPixels/2);
    }

    virtual void EscreveStringEsquerda(std::string texto,int x,int y,float ang=0,int delta=0){
        SDL_Rect rectDestino;
        rectDestino.x = x;
        //rectDestino.y = CGerenciadorJanelas::GetJanela(janela)->GetAltura()-y-tamFonte+fontDescent;

        SDL_Point ponto = {delta,tamFonte};
        Uint16 aux;

        for (int i=0;i<texto.size();i++){
            aux = texto[i];
            aux = aux % 256;//UTF16 string, retirando só o byte que interessa

            rectDestino.w = larguraLetra[estiloFixo][aux-PRIMEIRO_CAR];
            rectDestino.h = tamFonte+alturaExtra[estiloFixo][aux-PRIMEIRO_CAR];
            rectDestino.y = CGerenciadorJanelas::GetJanela(janela)->GetAltura()-y-rectDestino.h;

            SDL_RenderCopyEx(render,glyphsT[estiloFixo][aux-PRIMEIRO_CAR],NULL,&rectDestino,-ang,&ponto,FLIP_NENHUM);

            rectDestino.x += rectDestino.w;
            ponto.x -= rectDestino.w;
        }
    }

    virtual void EscreveStringDireita(std::string texto,int x,int y,float ang=0){
        int larguraPixels = GetLarguraPixelsString(texto);
        EscreveStringEsquerda(texto,x-larguraPixels,y,ang,larguraPixels);
    }

    virtual void EscreveStringLongaCentralizado(std::string texto,int x,int y,int largMax,int espacoEntreLinhas,float angulo=0){
        std::vector<std::string> linhas = ExtraiLinhas(texto,largMax);
        int yTotal=y;
        for (int k=0;k<linhas.size();k++){
            int larguraPixels = GetLarguraPixelsString((char*)linhas[k].c_str());
            EscreveStringEsquerda((char*)linhas[k].c_str(),x-larguraPixels/2,yTotal,angulo);
            yTotal -= espacoEntreLinhas;
        }
    }

    virtual void EscreveStringLongaEsquerda(std::string texto,int x,int y,int largMax,int espacoEntreLinhas,float angulo=0){
        std::vector<std::string> linhas = ExtraiLinhas(texto,largMax);
        int yTotal=y;
        for (int k=0;k<linhas.size();k++){
            int larguraPixels = GetLarguraPixelsString((char*)linhas[k].c_str());
            EscreveStringEsquerda((char*)linhas[k].c_str(),x,yTotal,angulo);
            yTotal -= espacoEntreLinhas;
        }
    }

    virtual void EscreveStringLongaDireita(std::string texto,int x,int y,int largMax,int espacoEntreLinhas,float angulo=0){
        std::vector<std::string> linhas = ExtraiLinhas(texto,largMax);
        int yTotal=y;
        for (int k=0;k<linhas.size();k++){
            int larguraPixels = GetLarguraPixelsString((char*)linhas[k].c_str());
            EscreveStringEsquerda((char*)linhas[k].c_str(),x-larguraPixels,yTotal,angulo);
            yTotal -= espacoEntreLinhas;
        }
    }

    void EscreveInteiroEsquerda(int valor, int x, int y, float angulo=0,int delta=0){
        EscreveStringEsquerda(std::to_string(valor),x,y,angulo,delta);
    }

    void EscreveInteiroCentralizado(int valor, int x, int y, float angulo=0){
        EscreveStringCentralizado(std::to_string(valor),x,y,angulo);
    }

    void EscreveInteiroDireita(int valor, int x, int y, float angulo=0){
        EscreveStringDireita(std::to_string(valor),x,y,angulo);
    }

    void EscreveDoubleEsquerda(double valor, int casas, int x, int y, float angulo=0,int delta=0){
        char str[100]="";
        char aux[20]="";
        sprintf(aux,"%%.%df",casas);
        sprintf(str,aux,valor);
        EscreveStringEsquerda(str,x,y,angulo,delta);
    }

    void EscreveDoubleCentralizado(double valor, int casas, int x, int y, float angulo=0){
        char str[100]="";
        char aux[20]="";
        sprintf(aux,"%%.%df",casas);
        sprintf(str,aux,valor);
        EscreveStringCentralizado(str,x,y,angulo);
    }

    void EscreveDoubleDireita(double valor, int casas, int x, int y, float angulo=0){
        char str[100]="";
        char aux[20]="";
        sprintf(aux,"%%.%df",casas);
        sprintf(str,aux,valor);
        EscreveStringDireita(str,x,y,angulo);
    }


    SDL_Surface *GetGlyph(Uint16 *emoji, PIG_Cor cor=BRANCO){
        return TTF_RenderUNICODE_Blended(font,emoji,cor);
    }
};

typedef CMapaCaracteres* MapaCaracteres;
std::string CMapaCaracteres::PigDelimitadores = " \n";
