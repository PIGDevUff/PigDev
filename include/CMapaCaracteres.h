typedef enum {CPIG_TEXTO_ESQUERDA,CPIG_TEXTO_DIREITA,CPIG_TEXTO_CENTRO} PIG_PosTexto;

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
        std::string strAtual = "";

        for (int i=0;i<texto.size();i++){

            if (delim.find(texto[i]) != std::string::npos){//achou delimitadores
                resp.push_back(strAtual);

                strAtual = texto[i];
                if (texto[i]!='\n'){
                    resp.push_back(strAtual);
                    strAtual = "";
                }

            }else strAtual += texto[i];
        }

        if (strAtual!=""){
            resp.push_back(strAtual);
        }
        return resp;
    }
/* //Versao Antiga//
    std::vector<std::string> SeparaPalavras(std::string texto,std::string delim){
        std::vector<std::string> resp;
        int indice;

        std::string strAtual = "";
        for (int i=0;i<texto.size();i++){
            //strAtual += texto[i];

            indice = delim.find(texto[i]);
            if (indice != std::string::npos){//achou delimitadores
                resp.push_back(strAtual);
                //strAtual.Print();

                if (texto[i]!='\n'){
                    strAtual = texto[i];
                    resp.push_back(strAtual);
                }
                strAtual = "";
            }else strAtual += texto[i];
        }
        if (strAtual!=""){
            resp.push_back(strAtual);
        }
        return resp;
    }
    */
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

    int GetLarguraLetra(Uint16 letra, int estilo=0){
        Uint16 aux = letra;
        aux = aux % 256;
        if(estiloFixo>=0)
            estilo = estiloFixo;
        return larguraLetra[estilo][aux-PRIMEIRO_CAR];
    }

    std::vector<std::string> ExtraiLinhas(std::string texto, int largMax, std::string delim=PigDelimitadores){
        std::vector<std::string> resp;
        if (texto=="") return resp;

        std::vector<std::string> palavras = SeparaPalavras(texto,delim);
        std::string linhaAtual = "";   //linha atual (que está sendo montada) contém pelo menos a primeira palavra
        int tamanhoAtual = 0;

        for (std::string palavra : palavras){
            int largPalavra = GetLarguraPixelsString(palavra);

            if (palavra[0]=='\n'){//se existe uma quebra de linha forçada
                resp.push_back(linhaAtual);
                linhaAtual = "";
                tamanhoAtual = 0;
            }

            if (tamanhoAtual + largPalavra > largMax && linhaAtual!=""){//a palavra estouraria a largura máxima se fosse agregada                if (ttttt==0){
                resp.push_back(linhaAtual); //coloca a linha que está montada no vetor de linhas
                linhaAtual = palavra; //a palavra que estouraria o limite começa a próxima linha
                tamanhoAtual = largPalavra;
            }else{//não estourou o limite
                linhaAtual += palavra;
                tamanhoAtual += largPalavra;
            }
        }

        if (linhaAtual != ""){
            resp.push_back(linhaAtual); //pega a linha que sobrou do processamento (última linha que não foi quebrada)
        }

        palavras.clear();
        return resp;
    }

    /*std::vector<std::string> ExtraiLinhas(std::string texto, int largMax, std::string delim=PigDelimitadores){
        std::vector<std::string> resp;
        if (texto=="") return resp;

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

            if (palavra.size()>0&&palavra[palavra.size()-1]=='\n'){//se existe uma quebra de linha forçada
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

    virtual void Escreve(std::string texto,int x,int y,PIG_PosTexto pos=CPIG_TEXTO_ESQUERDA,float ang=0){
        if (texto=="") return;
        int larguraPixels = GetLarguraPixelsString(texto);
        int delta=0;
        switch(pos){
        case CPIG_TEXTO_ESQUERDA:
            break;
        case CPIG_TEXTO_DIREITA:
            x -= larguraPixels; delta = larguraPixels;break;
        case CPIG_TEXTO_CENTRO:
            x -= larguraPixels/2; delta = larguraPixels/2;break;
        }

        SDL_Rect rectDestino;
        rectDestino.x = x;

        int altJanela = CGerenciadorJanelas::GetJanela(janela)->GetAltura();
        SDL_Point ponto = {delta,tamFonte};
        Uint16 aux;

        for (int i=0;i<texto.size();i++){
            aux = texto[i];
            aux = aux % 256;//UTF16 string, retirando só o byte que interessa
            if (aux-PRIMEIRO_CAR<0) continue;
            //printf("aux: %d  %d",aux,aux-PRIMEIRO_CAR);

            rectDestino.w = larguraLetra[estiloFixo][aux-PRIMEIRO_CAR];
            rectDestino.h = tamFonte+alturaExtra[estiloFixo][aux-PRIMEIRO_CAR];
            rectDestino.y = altJanela-y-rectDestino.h;

            SDL_RenderCopyEx(render,glyphsT[estiloFixo][aux-PRIMEIRO_CAR],NULL,&rectDestino,-ang,&ponto,FLIP_NENHUM);

            rectDestino.x += rectDestino.w;
            ponto.x -= rectDestino.w;
        }

    }

    virtual void EscreveLonga(std::string texto,int x,int y,int largMax,int espacoEntreLinhas,PIG_PosTexto pos=CPIG_TEXTO_ESQUERDA,float angulo=0){
        if (texto=="") return;
        std::vector<std::string> linhas = ExtraiLinhas(texto,largMax);
        int yTotal=y;
        for (int k=0;k<linhas.size();k++){
            Escreve(linhas[k],x,yTotal,pos,angulo);
            yTotal -= espacoEntreLinhas;
        }
    }

    SDL_Surface *GetGlyph(Uint16 *emoji, PIG_Cor cor=BRANCO){
        return TTF_RenderUNICODE_Blended(font,emoji,cor);
    }
};

typedef CMapaCaracteres* MapaCaracteres;
std::string CMapaCaracteres::PigDelimitadores = " \n";
