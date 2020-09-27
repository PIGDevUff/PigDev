#ifndef _CMAPACARACTERES_
#define _CMAPACARACTERES_

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

    //cria o conjunto de glifos das letras com as características fornecidas
    void CriaLetrasSurface(PIG_Estilo estilo, int nivelOutline, PIG_Cor corOutline, SDL_Surface *fundo,  PIG_Cor corFonte=BRANCO){
        TTF_SetFontStyle(font,estilo);

        glyphsT[estilo] = (SDL_Texture**) malloc(sizeof(SDL_Texture*)*(ULTIMO_CAR-PRIMEIRO_CAR));
        larguraLetra[estilo] = (int*)malloc(sizeof(int*)*(ULTIMO_CAR-PRIMEIRO_CAR));
        alturaExtra[estilo] = (int*)malloc(sizeof(int*)*(ULTIMO_CAR-PRIMEIRO_CAR));

        for (Uint16 letra=PRIMEIRO_CAR;letra<ULTIMO_CAR;letra++){
            SDL_Surface *surf = TTF_RenderGlyph_Blended(font,letra,corFonte);//superficie gerada com a forna da letra simples

            if (fundo){
                SDL_BlitScaled(fundo,NULL,surf,NULL);
            }

            larguraLetra[estilo][letra-PRIMEIRO_CAR] = surf->w;//largura da letra com o estilo específico
            alturaExtra[estilo][letra-PRIMEIRO_CAR] = surf->h-tamFonte;//qtd de pixels a mais na altura, para letras maiúsculas acentudadas como Á, Ó, É...

            if (nivelOutline>0){//faz o outline da letra, se houver
                TTF_SetFontOutline(font,nivelOutline);
                SDL_Surface *out = TTF_RenderGlyph_Blended(font,letra,corOutline);
                SDL_BlitSurface(out,NULL,surf,NULL);
                SDL_FreeSurface(out);
                TTF_SetFontOutline(font,0);
            }

            //SDL_SetColorKey(surf,1,SDL_MapRGBA(surf->format,0,0,0,255));
            glyphsT[estilo][letra-PRIMEIRO_CAR] = SDL_CreateTextureFromSurface(render,surf);

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


public:

    CMapaCaracteres(char *nomeFonte,int tamanhoFonte,int estilo, char *nomeFundo, int idJanela){
        IniciaBase(nomeFonte,tamanhoFonte,idJanela, estilo);

        SDL_Surface *fundo = IMG_Load(nomeFundo);//carrega a imagem de fundo
        SDL_SetSurfaceBlendMode(fundo,SDL_BLENDMODE_MOD);
        CriaLetrasSurface(estilo, 0,BRANCO, fundo);
        SDL_FreeSurface(fundo);
    }

    CMapaCaracteres(char *nomeFonte,int tamanhoFonte,int estilo, char *nomeFundo,int outline,PIG_Cor corOutline, int idJanela){
        IniciaBase(nomeFonte,tamanhoFonte,idJanela, estilo);

        SDL_Surface *fundo = IMG_Load(nomeFundo);//carrega a imagem de fundo
        SDL_SetSurfaceBlendMode(fundo,SDL_BLENDMODE_MOD);
        CriaLetrasSurface(estilo, outline, corOutline, fundo);
    }

    CMapaCaracteres(char *nomeFonte,int tamanhoFonte,int estilo, PIG_Cor corFonte,int outline,PIG_Cor corOutline, int idJanela){
        IniciaBase(nomeFonte,tamanhoFonte,idJanela, estilo);

        CriaLetrasSurface(estilo, outline, corOutline, NULL);//, corFonte);

        SDL_SetRenderTarget(render, NULL);
    }

    CMapaCaracteres(char *nomeFonte,int tamanhoFonte,int estilo, PIG_Cor corFonte, int idJanela){
        IniciaBase(nomeFonte,tamanhoFonte,idJanela, estilo);

        CriaLetrasSurface(estilo, 0, BRANCO, NULL);//, corFonte);

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

    void SubstituiGlyph(std::string nomeArq,uint16_t glyph, int largNova, int x, int y, int alt, int larg){
        glyph = glyph%256;
        if (glyph<PRIMEIRO_CAR||glyph>=ULTIMO_CAR) throw CPigErroIndice(glyph,"caracter");//se o indice do glyph antigo não existe

        int h;
        SDL_Surface *surfExtra;

        #ifdef SHARE_BITMAP
        surfExtra = CAssetLoader::LoadImage(nomeArq);
        #else
        surfExtra = IMG_Load(nomeArq.c_str()); //tenta ler o arquivo de imagem indicado
        #endif // SHARE_BITMAP

        if (surfExtra==NULL) throw CPigErroArquivo(nomeArq); //se não for possível lança um erro

        SDL_Rect r = {x,y,larg,alt};//pega somente a área do novo glyph

        for (int estilo=0;estilo<PIG_TOTALESTILOS;estilo++){
            if (estiloFixo>=0&&estilo!=estiloFixo) continue;

            SDL_QueryTexture(glyphsT[estilo][glyph-PRIMEIRO_CAR],NULL,NULL,NULL,&h); //pega a altura do caracter que será substituído
            SDL_Surface *surfAux = SDL_CreateRGBSurfaceWithFormat(0,largNova,h,32,SDL_PIXELFORMAT_RGBA32);//cria uma superfície com o tamanho adequado

            SDL_BlitScaled(surfExtra,&r,surfAux,NULL);//copia somente a área desejada para uma superfície auxiliar
            SDL_DestroyTexture(glyphsT[estilo][glyph-PRIMEIRO_CAR]);//libera a memória do glyph antigo
            larguraLetra[estilo][glyph-PRIMEIRO_CAR] = largNova;//atualiza a largura do glyph novo (valor do parâmetro)


            glyphsT[estilo][glyph-PRIMEIRO_CAR] = SDL_CreateTextureFromSurface(render,surfAux); //cria o gylph novo
            SDL_FreeSurface(surfAux);
        }
    }

    int GetFonteDescent(){
        return -fontDescent;//o valor armazenado fica negativo; a resposta é dada com valor positivo
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

        std::vector<std::string> palavras = PIGSeparaPalavras(texto,delim);
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

    virtual void Escreve(std::string texto,int x,int y,PIG_Cor corFonte=BRANCO,PIG_PosTexto pos=CPIG_TEXTO_ESQUERDA,float ang=0,int alvoTextura=0){
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

            SDL_SetTextureColorMod(glyphsT[estiloFixo][aux-PRIMEIRO_CAR],corFonte.r,corFonte.g,corFonte.b);

            if (alvoTextura)    //caso esteja sendo escrito em textura (label), é preciso ajustar o modo
                SDL_SetTextureBlendMode(glyphsT[estiloFixo][aux-PRIMEIRO_CAR], SDL_BLENDMODE_NONE);
            else SDL_SetTextureBlendMode(glyphsT[estiloFixo][aux-PRIMEIRO_CAR], SDL_BLENDMODE_BLEND);

            rectDestino.w = larguraLetra[estiloFixo][aux-PRIMEIRO_CAR];
            rectDestino.h = tamFonte+alturaExtra[estiloFixo][aux-PRIMEIRO_CAR];
            rectDestino.y = altJanela-y-rectDestino.h;

            //printf("%d %d %d %d\n",rectDestino.x,rectDestino.y,rectDestino.h,rectDestino.w);

            SDL_RenderCopyEx(render,glyphsT[estiloFixo][aux-PRIMEIRO_CAR],NULL,&rectDestino,-ang,&ponto,FLIP_NENHUM);

            rectDestino.x += rectDestino.w;
            ponto.x -= rectDestino.w;
        }

    }

    virtual void EscreveLonga(std::string texto,int x,int y,int largMax,int espacoEntreLinhas,PIG_Cor corFonte=BRANCO,PIG_PosTexto pos=CPIG_TEXTO_ESQUERDA,float angulo=0){
        if (texto=="") return;
        std::vector<std::string> linhas = ExtraiLinhas(texto,largMax);
        int yTotal=y;
        for (int k=0;k<linhas.size();k++){
            Escreve(linhas[k],x,yTotal,corFonte,pos,angulo);
            yTotal -= espacoEntreLinhas;
        }
    }

    virtual void Escreve(std::string texto,SDL_Texture *textura,PIG_Cor cor){
        SDL_SetRenderTarget(render,textura);
        SDL_SetRenderDrawColor(render,0,0,0,0);
        int altJanela = CGerenciadorJanelas::GetJanela(janela)->GetAltura();
        //SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND);
        /*switch(op1){
        case 0: SDL_SetTextureBlendMode(textura, SDL_BLENDMODE_ADD);break;
        case 1: SDL_SetTextureBlendMode(textura, SDL_BLENDMODE_NONE);break;
        case 2: SDL_SetTextureBlendMode(textura, SDL_BLENDMODE_MOD);break;
        case 3: SDL_SetTextureBlendMode(textura, SDL_BLENDMODE_BLEND);break;
        case 4: SDL_SetTextureBlendMode(textura, SDL_BLENDMODE_ADD);break;
        }*/
        SDL_SetTextureBlendMode(textura, SDL_BLENDMODE_BLEND);
        SDL_SetTextureColorMod(textura,cor.r,cor.g,cor.b);
        //SDL_SetTextureAlphaMod(textura, 255);
        Escreve(texto,0,altJanela-tamFonte+fontDescent,cor,CPIG_TEXTO_ESQUERDA,0,1);
        //SDL_SetTextureBlendMode(textura, SDL_BLENDMODE_ADD);
        //SDL_SetTextureAlphaMod(textura, 255);
        SDL_SetRenderTarget(render, NULL);
    }


    SDL_Surface *GetGlyph(Uint16 *emoji, PIG_Cor cor=BRANCO){
        return TTF_RenderUNICODE_Blended(font,emoji,cor);
    }
};

typedef CMapaCaracteres* MapaCaracteres;
std::string CMapaCaracteres::PigDelimitadores = " \n";

#endif // _CMAPACARACTERES_
