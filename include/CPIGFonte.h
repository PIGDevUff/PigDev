#ifndef _CMAPACARACTERES_
#define _CMAPACARACTERES_

typedef enum {PIG_TEXTO_ESQUERDA,PIG_TEXTO_DIREITA,PIG_TEXTO_CENTRO} PIGPosTexto;

class CPIGFonte{

protected:

    static string delimitadores;

    int **alturaExtra,**larguraLetra;
    int idJanela;
    int fontDescent;
    int estiloFixo;

    SDL_Renderer *render;
    SDL_Texture ***glyphsT;
    TTF_Font *font;

    string nome;
    int tamFonte;

    inline static Uint16 ConvChar(Uint16 letra){
        if (letra>6500) letra+=64;
        return letra % 256;
    }

    //converte cada caractere da string no índice correpondente do vetor de glifos
    vector<int> Converte(string original){
        vector<int> resp;
        Uint16 aux;
        for (unsigned int i=0;i<original.size();i++){
            aux = original[i];                          //esse caractere pode ter 2 bytes
            if (aux==65475) continue;                   //ignora certos símbolos
            aux = ConvChar(aux);                        //descobre o valor ASCII
            //if (aux-PIG_PRIMEIRO_CAR<0) continue;
            resp.push_back(aux);                        //converte para o índice do vetor
        }
        return resp;
    }

    //pega a altura da janela ou do renderizador
    int GetAlturaAtualJanela(){
        if (idJanela>=0)
            return CPIGGerenciadorJanelas::GetJanela(idJanela)->GetAltura();
        else{
            int w,h;
            SDL_GetRendererOutputSize(render,&w,&h);
            return h;
        }
    }

    //cria o conjunto de glifos das letras com as características fornecidas
    void CriaLetrasSurface(PIGEstilo estilo, int nivelOutline, PIGCor corOutline, SDL_Surface *fundo,  PIGCor corFonte=BRANCO){
        TTF_SetFontStyle(font,estilo);

        glyphsT[estilo] = (SDL_Texture**) malloc(sizeof(SDL_Texture*)*(PIG_ULTIMO_CAR-PIG_PRIMEIRO_CAR));
        larguraLetra[estilo] = (int*)malloc(sizeof(int)*(PIG_ULTIMO_CAR-PIG_PRIMEIRO_CAR));
        alturaExtra[estilo] = (int*)malloc(sizeof(int)*(PIG_ULTIMO_CAR-PIG_PRIMEIRO_CAR));

        for (Uint16 letra=PIG_PRIMEIRO_CAR;letra<PIG_ULTIMO_CAR;letra++){
            SDL_Surface *surf = TTF_RenderGlyph_Blended(font,letra,corFonte);//superficie gerada com a forna da letra simples

            if (fundo){
                SDL_BlitScaled(fundo,NULL,surf,NULL);
            }

            larguraLetra[estilo][letra-PIG_PRIMEIRO_CAR] = surf->w;//largura da letra com o estilo específico
            alturaExtra[estilo][letra-PIG_PRIMEIRO_CAR] = surf->h-tamFonte;//qtd de pixels a mais na altura, para letras maiúsculas acentudadas como Á, Ó, É...

            if (nivelOutline>0){//faz o outline da letra, se houver
                TTF_SetFontOutline(font,nivelOutline);
                SDL_Surface *out = TTF_RenderGlyph_Blended(font,letra,corOutline);
                SDL_BlitSurface(out,NULL,surf,NULL);
                SDL_FreeSurface(out);
                TTF_SetFontOutline(font,0);
            }

            //char nome[50];
            //sprintf(nome,"%d.bmp",letra);
            //SDL_SaveBMP(surf,nome);

            //SDL_SetColorKey(surf,1,SDL_MapRGBA(surf->format,0,0,0,255));
            glyphsT[estilo][letra-PIG_PRIMEIRO_CAR] = SDL_CreateTextureFromSurface(render,surf);

            SDL_FreeSurface(surf);
        }

    }

    //inicia os atributos da classe
    void IniciaBase(string nomeFonte, int tamanhoFonte, PIGEstilo estilo, int janela, SDL_Renderer *renderer=NULL){
        nome = nomeFonte;
        tamFonte = tamanhoFonte;
        estiloFixo = estilo;

        idJanela = janela;
        if (idJanela>=0)
            render = CPIGGerenciadorJanelas::GetJanela(idJanela)->GetRenderer();
        else render = renderer;

        font = TTF_OpenFont(nome.c_str(), tamanhoFonte);

        if (font==NULL){
            printf("Erro: arquivo de fonte (%s) nao localizado\n",nomeFonte.c_str());
            exit(-1);
        }

        fontDescent = TTF_FontDescent(font);

        alturaExtra = (int**)malloc(sizeof(int*)*(PIG_TOTALESTILOS));
        larguraLetra = (int**)malloc(sizeof(int*)*(PIG_TOTALESTILOS));
        glyphsT = (SDL_Texture***) malloc(sizeof(SDL_Texture**)*(PIG_TOTALESTILOS));
        for (int i=0;i<PIG_TOTALESTILOS;i++){
            alturaExtra[i] = NULL;
            larguraLetra[i] = NULL;
            glyphsT[i] = NULL;
        }
    }


public:

    CPIGFonte(string nomeFonte, int tamanhoFonte, PIGEstilo estilo, string nomeFundo, int janela=0, SDL_Renderer *renderer=NULL){
        IniciaBase(nomeFonte,tamanhoFonte,estilo,janela,renderer);

        SDL_Surface *fundo = IMG_Load(nomeFundo.c_str());//carrega a imagem de fundo
        SDL_SetSurfaceBlendMode(fundo,SDL_BLENDMODE_MOD);
        CriaLetrasSurface(estilo, 0,BRANCO, fundo);
        SDL_FreeSurface(fundo);
    }

    CPIGFonte(string nomeFonte, int tamanhoFonte, PIGEstilo estilo, string nomeFundo, int outline, PIGCor corOutline, int janela=0, SDL_Renderer *renderer=NULL){
        IniciaBase(nomeFonte,tamanhoFonte,estilo,janela,renderer);

        SDL_Surface *fundo = IMG_Load(nomeFundo.c_str());//carrega a imagem de fundo
        SDL_SetSurfaceBlendMode(fundo,SDL_BLENDMODE_MOD);
        CriaLetrasSurface(estilo, outline, corOutline, fundo);
    }

    CPIGFonte(string nomeFonte, int tamanhoFonte, PIGEstilo estilo, PIGCor corFonte, int outline, PIGCor corOutline, int janela=0, SDL_Renderer *renderer=NULL){
        IniciaBase(nomeFonte,tamanhoFonte,estilo,janela,renderer);

        CriaLetrasSurface(estilo, outline, corOutline, NULL);//, corFonte);

        SDL_SetRenderTarget(render, NULL);
    }

    CPIGFonte(string nomeFonte, int tamanhoFonte, PIGEstilo estilo, PIGCor corFonte, int janela=0, SDL_Renderer *renderer=NULL){
        IniciaBase(nomeFonte,tamanhoFonte,estilo,janela,renderer);

        CriaLetrasSurface(estilo, 0, BRANCO, NULL);//, corFonte);

        SDL_SetRenderTarget(render, NULL);
    }

    virtual ~CPIGFonte(){
        TTF_CloseFont(font);
        for (int i=0;i<PIG_TOTALESTILOS;i++){
            if (glyphsT[i]){
                free(alturaExtra[i]);
                free(larguraLetra[i]);
                for (Uint16 j=PIG_PRIMEIRO_CAR;j<PIG_ULTIMO_CAR;j++){
                    SDL_DestroyTexture(glyphsT[i][j-PIG_PRIMEIRO_CAR]);
                }
                free(glyphsT[i]);
            }
        }
        free(glyphsT);
        free(larguraLetra);
        free(alturaExtra);
    }

    void SubstituiGlyph(string nomeArq, uint16_t glyph, int largNova, int x, int y, int alt, int larg){
        glyph = ConvChar(glyph);
        if (glyph<PIG_PRIMEIRO_CAR||glyph>=PIG_ULTIMO_CAR) throw CPIGErroIndice(glyph,"caracter");//se o indice do glyph antigo năo existe

        int h;
        SDL_Surface *surfExtra;

        #ifdef SHARE_BITMAP
        surfExtra = CPIGAssetLoader::LoadImage(nomeArq);
        #else
        surfExtra = IMG_Load(nomeArq.c_str()); //tenta ler o arquivo de imagem indicado
        #endif // SHARE_BITMAP

        if (surfExtra==NULL) throw CPIGErroArquivo(nomeArq); //se năo for possível lança um erro

        SDL_Rect r = {x,y,larg,alt};//pega somente a área do novo glyph

        for (int estilo=0;estilo<PIG_TOTALESTILOS;estilo++){
            if (estiloFixo>=0&&estilo!=estiloFixo) continue;

            SDL_QueryTexture(glyphsT[estilo][glyph-PIG_PRIMEIRO_CAR],NULL,NULL,NULL,&h); //pega a altura do caracter que será substituído
            SDL_Surface *surfAux = SDL_CreateRGBSurfaceWithFormat(0,largNova,h,32,SDL_PIXELFORMAT_RGBA32);//cria uma superfície com o tamanho adequado

            SDL_BlitScaled(surfExtra,&r,surfAux,NULL);//copia somente a área desejada para uma superfície auxiliar
            SDL_DestroyTexture(glyphsT[estilo][glyph-PIG_PRIMEIRO_CAR]);//libera a memória do glyph antigo
            larguraLetra[estilo][glyph-PIG_PRIMEIRO_CAR] = largNova;//atualiza a largura do glyph novo (valor do parâmetro)

            glyphsT[estilo][glyph-PIG_PRIMEIRO_CAR] = SDL_CreateTextureFromSurface(render,surfAux); //cria o gylph novo
            SDL_FreeSurface(surfAux);
        }
    }

    int GetFonteDescent(){
        return -fontDescent;//o valor armazenado fica negativo; a resposta é dada com valor positivo
    }

    int GetFonteAscent(){
        return TTF_FontAscent(font); //quantidade base de pixels acima da linha base da letra (năo inclui acento de vogais maiúsculas)
    }

    PIGMetricasFonte GetMetricasLetra(Uint16 letra, int estilo=0){
        PIGMetricasFonte metrica;
        int xMin,xMax,yMin,yMax,adv;
        if(estiloFixo>=0)
            estilo = estiloFixo;

        TTF_SetFontStyle(font,estilo);

        letra = ConvChar(letra);
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
        Uint16 aux = ConvChar(letra);
        if (aux-PIG_PRIMEIRO_CAR<0) return 0;
        if (estiloFixo>=0)
            estilo = estiloFixo;

        return larguraLetra[estilo][aux-PIG_PRIMEIRO_CAR];
    }

    vector<string> ExtraiLinhas(string texto, int largMax, string delim=delimitadores){
        vector<string> resp;
        if (texto=="") return resp;

        vector<string> palavras = PIGSeparaPalavras(texto,delim);
        string linhaAtual = "";   //linha atual (que está sendo montada) contém pelo menos a primeira palavra
        int tamanhoAtual = 0;

        for (string palavra : palavras){
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
            }else{//năo estourou o limite
                linhaAtual += palavra;
                tamanhoAtual += largPalavra;
            }
        }

        if (linhaAtual != ""){
            resp.push_back(linhaAtual); //pega a linha que sobrou do processamento (última linha que năo foi quebrada)
        }

        palavras.clear();
        return resp;
    }

    virtual int GetLarguraPixelsString(string texto){
        int resp=0;
        vector<int> conv = Converte(texto);

        for (int aux:conv){
            if (aux-PIG_PRIMEIRO_CAR>=0)
                resp += larguraLetra[estiloFixo][aux-PIG_PRIMEIRO_CAR];
        }

        return resp;
    }

    virtual void Escreve(string texto, int x, int y, PIGCor corFonte=BRANCO, PIGPosTexto pos=PIG_TEXTO_ESQUERDA, float ang=0, int alvoTextura=0){
        if (texto=="") return;
        string strs(texto.c_str());//precisa fazer p converter os formatos de strings "texto" que podem ser diferentes

        int larguraPixels = GetLarguraPixelsString(strs);
        int delta=0;
        switch(pos){
        case PIG_TEXTO_ESQUERDA:
            break;
        case PIG_TEXTO_DIREITA:
            x -= larguraPixels; delta = larguraPixels;break;
        case PIG_TEXTO_CENTRO:
            x -= larguraPixels/2; delta = larguraPixels/2;break;
        }

        SDL_Rect rectDestino;
        rectDestino.x = x;

        int altJanela = GetAlturaAtualJanela();

        SDL_Point ponto = {delta,tamFonte};

        vector<int> conv = Converte(strs);

        for (int aux:conv){
            int indice = aux - PIG_PRIMEIRO_CAR;
            if (indice<0) continue;

            SDL_SetTextureColorMod(glyphsT[estiloFixo][indice],corFonte.r,corFonte.g,corFonte.b);

            if (alvoTextura)    //caso esteja sendo escrito em textura (label), é preciso ajustar o modo
                SDL_SetTextureBlendMode(glyphsT[estiloFixo][indice], SDL_BLENDMODE_NONE);
            else SDL_SetTextureBlendMode(glyphsT[estiloFixo][indice], SDL_BLENDMODE_BLEND);

            rectDestino.w = larguraLetra[estiloFixo][indice];
            rectDestino.h = tamFonte+alturaExtra[estiloFixo][indice];
            rectDestino.y = altJanela-y-rectDestino.h;

            //printf("%d %d %d %d\n",rectDestino.x,rectDestino.y,rectDestino.h,rectDestino.w);

            SDL_Rect enquadrado = rectDestino;
            if (idJanela>=0)
                CPIGGerenciadorJanelas::GetJanela(idJanela)->ConverteCoordenadaWorldScreen(enquadrado.x,enquadrado.y,enquadrado.x,enquadrado.y);

            SDL_RenderCopyEx(render,glyphsT[estiloFixo][indice],NULL,&enquadrado,-ang,&ponto,PIG_FLIP_NENHUM);

            rectDestino.x += rectDestino.w;
            ponto.x -= rectDestino.w;
        }

    }

    virtual void EscreveLonga(string texto, int x, int y, int largMax, int espacoEntreLinhas, PIGCor corFonte=BRANCO, PIGPosTexto pos=PIG_TEXTO_ESQUERDA, float angulo=0){
        if (texto=="") return;
        vector<string> linhas = ExtraiLinhas(texto,largMax);
        int yTotal=y;
        for (string str:linhas){
            Escreve(str,x,yTotal,corFonte,pos,angulo);
            yTotal -= espacoEntreLinhas;
        }
    }

    virtual void Escreve(string texto, SDL_Texture *textura, PIGCor cor){
        if (this_thread::get_id()!=PIG_MAIN_THREAD_ID)
            CPIGGerenciadorJanelas::GetJanela(idJanela)->TravaRenderer();

        if (SDL_SetRenderTarget(render,textura)==0){
            SDL_SetRenderDrawColor(render,0,0,0,0);
            int altJanela = GetAlturaAtualJanela();

            SDL_SetTextureBlendMode(textura, SDL_BLENDMODE_BLEND);
            SDL_SetTextureColorMod(textura,cor.r,cor.g,cor.b);

            Escreve(texto,0,altJanela-tamFonte+fontDescent,cor,PIG_TEXTO_ESQUERDA,0,1);
            //SDL_SetRenderDrawColor(render,255,0,0,255);
            //SDL_RenderDrawRect(render,NULL);
            SDL_SetRenderTarget(render, NULL);
        }

        if (this_thread::get_id()!=PIG_MAIN_THREAD_ID)
            CPIGGerenciadorJanelas::GetJanela(idJanela)->TravaRenderer();
    }


    SDL_Surface *GetGlyph(Uint16 *emoji, PIGCor cor=BRANCO){
        return TTF_RenderUNICODE_Blended(font,emoji,cor);
    }
};

typedef CPIGFonte* PIGFonte;
string CPIGFonte::delimitadores = " \n";

#endif // _CMAPACARACTERES_
