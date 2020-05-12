class CMapaCaracteres{

#define TOTALESTILOS 32

protected:

    int **alturaLetra;
    int **larguraLetra;
    int janela;
    int estiloFixo;

    SDL_Renderer *render;
    SDL_Texture ***glyphsT;
    TTF_Font *font;

    std::string nome;
    int tamFonte;

    std::string TrataRetornoSeparaPalavraCaracterEspecial(int posAtual,int &posAnt,std::string txt,std::string Retorno){
        std::string aux;

        if(posAtual == posAnt){
            posAnt+=1;
            return Retorno;
        }

        aux.assign(txt,posAnt,posAtual - posAnt);
        posAnt = posAtual;
        return aux;

   }

    virtual std::string SeparaPalavra(int &posAnt,std::string txt){

        if(posAnt == txt.size()) return "";

        for(int i = posAnt;i<txt.size();i++){
            if(txt[i] == '\n') return TrataRetornoSeparaPalavraCaracterEspecial(i,posAnt,txt,"\n");
            if(txt[i] == ' ') return TrataRetornoSeparaPalavraCaracterEspecial(i,posAnt,txt," ");
        }

        std::string aux;
        aux.assign(txt,posAnt,txt.size() - posAnt);
        posAnt = txt.size();
        return aux;

    }

    //funcao que desenha o outline na fonte que está sendo produzida(o render precisa estar direcionado para a textura em questão)
    void FazOutline(Uint16 letra, int nivelOutline, PIG_Cor corOutline){
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
        alturaLetra[estilo] = (int*)malloc(sizeof(int*)*(ULTIMO_CAR-PRIMEIRO_CAR));

        for (Uint16 letra=PRIMEIRO_CAR;letra<ULTIMO_CAR;letra++){
            SDL_Surface *surf = TTF_RenderGlyph_Blended(font,letra,corFonte);//superficie gerada com a forna da letra simples
            SDL_Texture *textLetra = SDL_CreateTextureFromSurface(render,surf);//textura com a forma da letra da letra simples

            larguraLetra[estilo][letra-PRIMEIRO_CAR] = surf->w;//largura da letra com o estilo específico
            alturaLetra[estilo][letra-PRIMEIRO_CAR] = surf->h;//altura da letra com o estilo específico

            //cria uma textura renderizavel para aplicar as camadas (forma da letra, depois imagem de fundo)
            glyphsT[estilo][letra-PRIMEIRO_CAR] = SDL_CreateTexture(render,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,larguraLetra[estilo][letra-PRIMEIRO_CAR],alturaLetra[estilo][letra-PRIMEIRO_CAR]);
            SDL_SetRenderTarget(render, glyphsT[estilo][letra-PRIMEIRO_CAR]);//textura de destino

            SDL_SetTextureAlphaMod(textLetra,255);
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

    void IniciaBase(char *nomeFonte,int tamanhoFonte,int idJanela,PIG_Estilo estilo){
        nome.assign(nomeFonte);
        tamFonte = tamanhoFonte;
        janela = idJanela;
        estiloFixo = estilo;

        render = CGerenciadorJanelas::GetJanela(idJanela)->GetRenderer();
        font = TTF_OpenFont( nome.c_str(), tamanhoFonte );
        if (font==NULL)
            printf("Erro: arquivo de fonte (%s) nao localizado\n",nomeFonte);

        alturaLetra = (int**)malloc(sizeof(int)*(TOTALESTILOS));
        larguraLetra = (int**)malloc(sizeof(int)*(TOTALESTILOS));
        glyphsT = (SDL_Texture***) malloc(sizeof(SDL_Texture**)*(TOTALESTILOS));
        for (int i=0;i<TOTALESTILOS;i++){
            alturaLetra[i] = NULL;
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
        for (int i=0;i<TOTALESTILOS;i++){
            if (glyphsT[i]){
                free(alturaLetra[i]);
                free(larguraLetra[i]);
                for (Uint16 j=PRIMEIRO_CAR;j<ULTIMO_CAR;j++){
                    SDL_DestroyTexture(glyphsT[i][j-PRIMEIRO_CAR]);
                }
                free(glyphsT[i]);
            }
        }
        free(glyphsT);
        free(larguraLetra);
        free(alturaLetra);
    }

    std::vector<std::string> ExtraiLinhasString(std::string texto,int largMax){
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
    }

    virtual int GetLarguraPixelsString(std::string str){
        int resp=0;
        Uint16 aux;

        for (int i=0;i<str.size();i++){
            aux = str[i];
            aux = aux % 256;
            if(str[i] != '\n')
                resp += larguraLetra[estiloFixo][aux-PRIMEIRO_CAR];
        }

        return resp;
    }

    virtual void EscreveStringCentralizado(std::string str,int x,int y,float ang=0){
        int larguraPixels = GetLarguraPixelsString(str);
        EscreveStringEsquerda(str,x-larguraPixels/2,y,ang,larguraPixels/2);
    }

    virtual void EscreveStringEsquerda(std::string str,int x,int y,float ang=0,int delta=0){
        SDL_Rect rectDestino;
        rectDestino.x = x;
        rectDestino.y = CGerenciadorJanelas::GetJanela(janela)->GetAltura()-y-tamFonte;

        SDL_Point ponto = {delta,tamFonte};
        Uint16 aux;

        for (int i=0;i<str.size();i++){
            aux = str[i];
            aux = aux % 256;//UTF16 string, retirando só o byte que interessa

            rectDestino.w = larguraLetra[estiloFixo][aux-PRIMEIRO_CAR];
            rectDestino.h = alturaLetra[estiloFixo][aux-PRIMEIRO_CAR];

            SDL_RenderCopyEx(render,glyphsT[estiloFixo][aux-PRIMEIRO_CAR],NULL,&rectDestino,-ang,&ponto,FLIP_NENHUM);

            rectDestino.x += rectDestino.w;
            ponto.x -= rectDestino.w;
        }
    }

    virtual void EscreveStringDireita(std::string str,int x,int y,float ang=0){
        int larguraPixels = GetLarguraPixelsString(str);
        EscreveStringEsquerda(str,x-larguraPixels,y,ang,larguraPixels);
    }


    int GetAlturaLetra(char letra, int estilo=0){
        Uint16 aux = letra;
        aux = aux % 256;
        if(estiloFixo>=0)
            estilo = estiloFixo;
        return alturaLetra[estiloFixo][aux-PRIMEIRO_CAR];
    }

    int GetLarguraLetra(char letra, int estilo=0){
        Uint16 aux = letra;
        aux = aux % 256;
        if(estiloFixo>=0)
            estilo = estiloFixo;
        return larguraLetra[estilo][aux-PRIMEIRO_CAR];
    }

    int GetTamanhoFonte(){
        return tamFonte;
    }


    virtual void EscreveStringLongaCentralizado(std::string texto,int x,int y,int largMax,int espacoEntreLinhas){
        std::vector<std::string> linhas = ExtraiLinhasString(texto,largMax);
        int yTotal=y;
        for (int k=0;k<linhas.size();k++){
            int larguraPixels = GetLarguraPixelsString((char*)linhas[k].c_str());
            EscreveStringEsquerda((char*)linhas[k].c_str(),x-larguraPixels/2,yTotal);
            yTotal -= espacoEntreLinhas;
        }
    }

    virtual void EscreveStringLongaEsquerda(std::string texto,int x,int y,int largMax,int espacoEntreLinhas){
        std::vector<std::string> linhas = ExtraiLinhasString(texto,largMax);
        int yTotal=y;
        for (int k=0;k<linhas.size();k++){
            int larguraPixels = GetLarguraPixelsString((char*)linhas[k].c_str());
            EscreveStringEsquerda((char*)linhas[k].c_str(),x,yTotal);
            yTotal -= espacoEntreLinhas;
        }

        /*int estilo = estiloFixo>=0?estiloFixo:ESTILO_NORMAL;//se a fonte é dinâmica usa o estilo padrão
        SDL_Rect rectDestino;
        int linhaAtual =0;
        std::vector<std::string> linhas = ExtraiLinhasString(texto,largMax);

        int altBase = CGerenciadorJanelas::GetJanela(janela)->GetAltura()-y-tamFonte;

        for (int k=0;k<linhas.size();k++){

            rectDestino.x = x;
            rectDestino.y = altBase;

            Uint16 aux;

            for (int i=0;i<linhas[k].size();i++){

                if(linhas[k][i] != '\n'){

                    aux = linhas[k][i];
                    aux = aux % 256;

                    rectDestino.y = altBase + (espacoEntreLinhas*linhaAtual);

                    rectDestino.w = larguraLetra[estilo][aux-PRIMEIRO_CAR];
                    rectDestino.h = alturaLetra[estilo][aux-PRIMEIRO_CAR];

                    SDL_RenderCopy(render,glyphsT[estilo][aux-PRIMEIRO_CAR],NULL,&rectDestino);

                    rectDestino.x += rectDestino.w;
                }

            }

            linhaAtual++;
        }*/
    }

    virtual void EscreveStringLongaDireita(std::string texto,int x,int y,int largMax,int espacoEntreLinhas){
        std::vector<std::string> linhas = ExtraiLinhasString(texto,largMax);
        int yTotal=y;
        for (int k=0;k<linhas.size();k++){
            int larguraPixels = GetLarguraPixelsString((char*)linhas[k].c_str());
            EscreveStringEsquerda((char*)linhas[k].c_str(),x-larguraPixels,yTotal);
            yTotal -= espacoEntreLinhas;
        }
    }


    SDL_Surface *GetGlyph(char *emoji){
        return TTF_RenderUTF8_Solid(font,emoji,{255,0,0,255});
    }
};

typedef CMapaCaracteres* MapaCaracteres;
