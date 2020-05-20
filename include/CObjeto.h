#include <algorithm>
#include <cmath>
class CObjeto : public CVisual
{

protected:
    std::map<int, int> valoresIntInt;
    std::map<std::string, int> valoresStringInt;
    std::map<int, float> valoresIntFloat;
    std::map<std::string, float> valoresStringFloat;
    std::map<int, std::string> valoresIntString;
    std::map<std::string, std::string> valoresStringString;
    SDL_Point bb[4];
    PIG_Cor **pixels;

    void DesenhaBB()
    {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);//retângulo verde para o OOBB (com ângulo)
        SDL_RenderDrawLine(renderer, bb[0].x, altJanela - bb[0].y, bb[1].x, altJanela - bb[1].y);
        SDL_RenderDrawLine(renderer, bb[1].x, altJanela - bb[1].y, bb[2].x, altJanela - bb[2].y);
        SDL_RenderDrawLine(renderer, bb[2].x, altJanela - bb[2].y, bb[3].x, altJanela - bb[3].y);
        SDL_RenderDrawLine(renderer, bb[3].x, altJanela - bb[3].y, bb[0].x, altJanela - bb[0].y);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &dest);//retângulo vermelhor para o AABB (sem ângulo)
        //printf("%d,%d,%d,%d\n",dest.x,dest.y,dest.w,dest.h);
    }

    void AtualizaBB()
    {
        SDL_Point pivoAbs;

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
        pivoAbs.x = pivoRelativo.x + x;
        pivoAbs.y = -pivoRelativo.y + y + alt; //inverte o eixo Y, pois o pivoRel considera o eixo Y aumentando para baixo
        //printf("PivoRel: %d %d\n",pivoRelativo.x,pivoRelativo.y);
        //printf("PivoRAbs: %d %d\n",pivoAbs.x,pivoAbs.y);
        float angRad = -angulo * M_PI / 180.0;
        float seno = sin(angRad);
        float cosseno = cos(angRad);
        //printf("Pivo %d %d  %f\n",pivoObj.x,pivoObj.y,angRad);

        //matriz de rota��o
        // ( cos(ang) sin(ang))   (Vx)   (Rx)
        // (-sin(ang) cos(ang)) * (Vy) = (Ry)

        //vetor (Rx,Ry) � a resposta do vetor (Vx,Vy) rotacionado em ang

        bb[0].x = (x - pivoAbs.x) * cosseno + (y - pivoAbs.y) * seno + pivoAbs.x;
        bb[0].y = (y - pivoAbs.y) * cosseno - (x - pivoAbs.x) * seno + pivoAbs.y;
        //printf("bb0: %d %d\n",bb[0].x,bb[0].y);

        bb[1].x = (x + larg - pivoAbs.x) * cosseno + (y - pivoAbs.y) * seno + pivoAbs.x;
        bb[1].y = (y - pivoAbs.y) * cosseno - (x + larg - pivoAbs.x) * seno + pivoAbs.y;
        //printf("bb1: %d %d\n",bb[1].x,bb[1].y);

        bb[2].x = (x + larg - pivoAbs.x) * cosseno + (y + alt - pivoAbs.y) * seno + pivoAbs.x;
        bb[2].y = (y + alt - pivoAbs.y) * cosseno - (x + larg - pivoAbs.x) * seno + pivoAbs.y;
        //printf("bb2: %d %d\n",bb[2].x,bb[2].y);

        bb[3].x = (x - pivoAbs.x) * cosseno + (y + alt - pivoAbs.y) * seno + pivoAbs.x;
        bb[3].y = (y + alt - pivoAbs.y) * cosseno - (x - pivoAbs.x) * seno + pivoAbs.y;
        //printf("bb3: %d %d\n",bb[3].x,bb[3].y);
    }

    void ExtraiPixels()
    {
        Uint8 *pix8;
        Uint32 *pix32;

        pixels = (PIG_Cor **)malloc(sizeof(PIG_Cor *) * bitmap->h);
        for (int i = 0; i < bitmap->h; i++)
        {
            pixels[i] = (PIG_Cor *)calloc(sizeof(PIG_Cor), bitmap->w);
        }

        if (bitmap->format->BytesPerPixel == 3)
        {
            for (int h = 0; h < bitmap->h; h++)
            {
                pix8 = (Uint8 *)bitmap->pixels + (h * bitmap->pitch);
                for (int w = 0; w < bitmap->w; w++)
                {
                    if (bitmap->format->format == SDL_PIXELFORMAT_RGB24)
                    {
                        pixels[h][w].r = *pix8;
                        pix8++;
                        pixels[h][w].g = *pix8;
                        pix8++;
                        pixels[h][w].b = *pix8;
                        pix8++;
                    }
                    else
                    {
                        pixels[h][w].b = *pix8;
                        pix8++;
                        pixels[h][w].g = *pix8;
                        pix8++;
                        pixels[h][w].r = *pix8;
                        pix8++;
                    }
                    pixels[h][w].a = 255;
                }
            }
        }
        else if (bitmap->format->BytesPerPixel == 4)
        {
            pix32 = (Uint32 *)bitmap->pixels;
            for (int h = 0; h < bitmap->h; h++)
            {
                for (int w = 0; w < bitmap->w; w++)
                {
                    SDL_GetRGBA((Uint32)*pix32, bitmap->format, &(pixels[h][w].r), &(pixels[h][w].g), &(pixels[h][w].b), &(pixels[h][w].a));
                    pix32++;
                }
            }
        }
    }

    /*void CriaTextura(int retiraFundo){
        if (retiraFundo){
            Uint8 red, green, blue, alpha;
            Uint32 *pixel = (Uint32*)bitmap->pixels;
            SDL_GetRGBA(*pixel,bitmap->format,&red,&green,&blue,&alpha);
            SDL_SetColorKey( bitmap, SDL_TRUE, SDL_MapRGBA(bitmap->format, red, green, blue,alpha) );
        }


        if (text) SDL_DestroyTexture(text);
        text = SDL_CreateTextureFromSurface(renderer, bitmap);

        //SDL_SetTextureAlphaMod(text,opacidade);
    }

    void Inicia(char *nomeArquivo,int janela,int posx,int posy, int retiraFundo, int opacidadeObj){
        strcpy(nomeImagem,nomeArquivo);
        idJanela = janela;
        altJanela = CGerenciadorJanelas::GetJanela(idJanela)->GetAltura();
        renderer = CGerenciadorJanelas::GetJanela(idJanela)->GetRenderer();

        x = posx;
        y = posy;
        angulo = 0;
        opacidade = opacidadeObj;

        flip = SDL_FLIP_NONE;

        altOriginal = alt = bitmap->h;
        largOriginal = larg = bitmap->w;

        pivoRelativo.x = 0;
        pivoRelativo.y = alt;
        AtualizaBB();

        dest.x = x;
        dest.y = altJanela-y-alt;
        dest.h = alt;
        dest.w = larg;

        frame.x = frame.y = 0;
        frame.h = alt;
        frame.w = larg;

        text = NULL;
        ExtraiPixels();
        CriaTextura(retiraFundo);
    }*/

public:
    int vertices[4][2];

    CObjeto(char *nomeArquivo, PIG_Cor *corFundo = NULL, int retiraFundo = 1, int janela = 0) : CVisual(nomeArquivo, retiraFundo, corFundo, janela)
    {
        //printf("visual chamado %d\n",retiraFundo);
        AtualizaBB();
        ExtraiPixels();
    }

    CObjeto(OffscreenRenderer offRender, PIG_Cor *corFundo = NULL, int retiraFundo = 1, int janela = 0) : CVisual(offRender, retiraFundo, corFundo, janela)
    {
        AtualizaBB();
        ExtraiPixels();
    }

    CObjeto(CObjeto *objBase, PIG_Cor *corFundo = NULL, int retiraFundo = 1, int janela = 0) : CVisual(objBase, retiraFundo, corFundo, janela)
    {
        AtualizaBB();
        ExtraiPixels();
        SetDimensoes(objBase->alt, objBase->larg);
    }

    ~CObjeto()
    {
        for (int i = 0; i < bitmap->h; i++)
            free(pixels[i]);
        free(pixels);

        /*if (text) SDL_DestroyTexture(text);

        if (strcmp(nomeImagem,"")==0){
            SDL_FreeSurface(bitmap);
        }else{
            #ifdef SHARE_BITMAP
            CAssetLoader::FreeImage(nomeImagem);
            #else
            SDL_FreeSurface(bitmap);
            #endif
        }*/
    }

    /*int GetIdJanela(){
        return idJanela;
    }*/

    void SetValoresInt(int chave, int valor)
    {
        valoresIntInt[chave] = valor;
    }

    void SetValoresInt(std::string chave, int valor)
    {
        valoresStringInt[chave] = valor;
    }

    void SetValoresFloat(int chave, float valor)
    {
        valoresIntFloat[chave] = valor;
    }

    void SetValoresFloat(std::string chave, float valor)
    {
        valoresStringFloat[chave] = valor;
    }

    void SetValoresString(int chave, std::string valor)
    {
        valoresIntString[chave] = valor;
    }

    void SetValoresString(std::string chave, std::string valor)
    {
        valoresStringString[chave] = valor;
    }

    bool GetValoresInt(int chave, int &valor)
    {
        std::map<int, int>::iterator it;
        it = valoresIntInt.find(chave);
        if (it == valoresIntInt.end())
            return false;
        valor = it->second;
        return true;
    }

    bool GetValoresInt(std::string chave, int &valor)
    {
        std::map<std::string, int>::iterator it;
        it = valoresStringInt.find(chave);
        if (it == valoresStringInt.end())
            return false;
        valor = it->second;
        return true;
    }

    bool GetValoresFloat(int chave, float &valor)
    {
        std::map<int, float>::iterator it;
        it = valoresIntFloat.find(chave);
        if (it == valoresIntFloat.end())
            return false;
        valor = it->second;
        return true;
    }

    bool GetValoresFloat(std::string chave, float &valor)
    {
        std::map<std::string, float>::iterator it;
        it = valoresStringFloat.find(chave);
        if (it == valoresStringFloat.end())
            return false;
        valor = it->second;
        return true;
    }

    bool GetValoresString(int chave, std::string &valor)
    {
        std::map<int, std::string>::iterator it;
        it = valoresIntString.find(chave);
        if (it == valoresIntString.end())
            return false;
        valor = it->second;
        return true;
    }

    bool GetValoresString(std::string chave, std::string &valor)
    {
        std::map<std::string, std::string>::iterator it;
        it = valoresStringString.find(chave);
        if (it == valoresStringString.end())
            return false;
        valor = it->second;
        return true;
    }

    /*void DefineFrame(SDL_Rect r){
        frame = r;
    }*/

    /*void GetXY(int &x,int &y){
        x = this->x;
        y = this->y;
    }

    void SetColoracao(PIG_Cor cor){
        coloracao = cor;
        SDL_SetTextureColorMod(text,cor.r,cor.g,cor.b);
    }*/

    //virtual void Move(int nx,int ny){
        //CVisual::Move(nx,ny);
        //AtualizaBB();
    //}

    int Desenha(OffscreenRenderer offRender = NULL)
    {
        if (offRender == NULL)
        {
            SDL_RenderCopyEx(renderer, text, &frame, &dest, -angulo, &pivoRelativo, flip);
            DesenhaBB();
        }
        else
        {
            SDL_Texture *textAux = SDL_CreateTextureFromSurface(offRender->GetRenderer(), bitmap);
            SDL_Rect rectAux = dest;
            rectAux.y = offRender->GetAltura() - alt - y;
            SDL_RenderCopyEx(offRender->GetRenderer(), textAux, &frame, &rectAux, -angulo, &pivoRelativo, flip);
            SDL_DestroyTexture(textAux);
        }
        return 0;
    }

    void SetAngulo(float a) override{
        angulo = a;
        AtualizaBB();
    }

    int arredonda(float valor)
    {
        int resultado = (int)valor;
        if (valor - resultado >= 0.5)
            return valor + 1;
        return valor;
    }

    void calculaVertice2s()
    {
        /*vertices[0][0] = x;
        vertices[0][1] = y;
        vertices[1][0] = arredonda(x + larg * cos(angulo * M_PI / 180));
        vertices[1][1] = arredonda(y + larg * sin(angulo * M_PI / 180));
        vertices[2][0] = arredonda(x + (larg * cos(angulo * M_PI / 180)) - (alt * sin(angulo * M_PI / 180)));
        vertices[2][1] = arredonda(y + (larg * sin(angulo * M_PI / 180)) + (alt * cos(angulo * M_PI / 180)));
        vertices[3][0] = arredonda(x - (alt * sin(angulo * M_PI / 180)));
        vertices[3][1] = arredonda(y + (alt * cos(angulo * M_PI / 180)));

        if (vertices[1][1] == vertices[0][1])
        {
            for (int i = 1; i < 4; i++)
            {
                std::swap(vertices[i][0], vertices[0][0]);
                std::swap(vertices[i][1], vertices[0][1]);
            }
        }*/
        for(int i=0;i<4;i++){
            vertices[i][0] = bb[i].x;
            vertices[i][1] = bb[i].y;
        }
    }

    double projecaoY(double coefAngular, SDL_Point p)
    {
        if (std::isinf(coefAngular))
            return (double)p.y;
        return coefAngular * (-p.x) + p.y;
    }

    double projecaoX(double coefAngular, SDL_Point p)
    {
        if (std::isinf(coefAngular))
            return (double)p.x;

        return (-p.y + (coefAngular * p.x)) / coefAngular;
    }

    double  min(double  vetor[4])
    {
        double  menor = vetor[0];
        for (int i = 1; i < 4; i++)
            if (vetor[i] < menor)
                menor = vetor[i];
        return menor;
    }

    double  max(double  vetor[4])
    {
        double  maior = vetor[0];
        for (int i = 1; i < 4; i++)
            if (vetor[i] > maior)
                maior = vetor[i];
        return maior;
    }

    SDL_Point GetBB(int i)
    {
        return bb[i];
    }

    int Colisao(CObjeto *outro)
    {
        AtualizaBB();

        // caso em q o angulo é 0
        // caso em que o vetor que vai de bb[0] para bb[1] é paralelo ao eixo X, ou seja, nao ira existir uma "projecao" no eixo X
        // os pontos sao trocados para que seja usado o antigo bb[3] para bb[0]
        if (bb[1].y == bb[0].y)
        {
            for (int i = 1; i < 4; i++)
            {
                std::swap(bb[i].x, bb[0].x);
                std::swap(bb[i].y, bb[0].y);
            }
        }

        // projecao dos vetores no eixo X deste objeto
        double projecaoAB = projecaoX((double)(bb[1].y - bb[0].y) / (double)(bb[1].x - bb[0].x), bb[0]);
        double projecaoCD = projecaoX((double)(bb[3].y - bb[2].y) / (double)(bb[3].x - bb[2].x), bb[2]);

        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        SDL_RenderDrawLine(renderer,(int)projecaoAB,300,(int)projecaoCD,300);

        // projecao dos pontos(com o angulo dos anteriores) no eixo X do outro objeto
        double projecao[4];
        for (int i = 0; i < 4; i++)
            projecao[i] = projecaoX((double)(bb[1].y - bb[0].y) / (double)(bb[1].x - bb[0].x), outro->GetBB(i));

        double menorA = (projecaoAB < projecaoCD) ? projecaoAB : projecaoCD;
        double maiorA = (projecaoAB > projecaoCD) ? projecaoAB : projecaoCD;
        double menorB = min(projecao);
        double maiorB = max(projecao);

        if (!(menorA < maiorB && maiorA > menorB))
            return false;

        // projecao dos vetores no eixo Y deste objeto
        projecaoAB = projecaoY((double )(bb[2].y - bb[1].y) / (double )(bb[2].x - bb[1].x), bb[1]);
        projecaoCD = projecaoY((double )(bb[0].y - bb[3].y) / (double )(bb[0].x - bb[3].x), bb[3]);

        // projecao dos pontos(com o angulo dos anteriores) no eixo Y do outro objeto
        for (int i = 0; i < 4; i++)
            projecao[i] = projecaoY((double )(bb[2].y - bb[1].y) / (double )(bb[2].x - bb[1].x), outro->GetBB(i));

        menorA = (projecaoAB < projecaoCD) ? projecaoAB : projecaoCD;
        maiorA = (projecaoAB > projecaoCD) ? projecaoAB : projecaoCD;
        menorB = min(projecao);
        maiorB = max(projecao);

        return (menorA < maiorB && maiorA > menorB);
    }

    /*int Colisao2(CObjeto *outro)
    {
        calculaVertices();
        outro->calculaVertices();

        // for (int i = 0; i < 4; i++)
        // {
        //     printf("%c(x, y) - %d %d\n", 'A' + i, vertices[i][0], vertices[i][1]);
        // }
        // printf("\n\n\n");

        // printf("%f\n\n\n", (float)(vertices[1][1] - vertices[0][1]) / (float)(vertices[1][0] - vertices[0][0]));

        // projecao dos vetores no eixo X deste objeto
        float projecaoAB = projecaoX((float)(vertices[1][1] - vertices[0][1]) / (float)(vertices[1][0] - vertices[0][0]), vertices[0]);
        float projecaoCD = projecaoX((float)(vertices[3][1] - vertices[2][1]) / (float)(vertices[3][0] - vertices[2][0]), vertices[2]);

        // printf("projAB: %f p: (%d, %d) | projCD: %f p: (%d, %d) \n\n\n", projecaoAB, vertices[0][0], vertices[0][1], projecaoCD, vertices[2][0], vertices[2][1]);

        // projecao dos pontos(com o angulo dos anteriores) no eixo X do outro objeto
        float projecao[4];
        for (int i = 0; i < 4; i++)
        {
            projecao[i] = projecaoX((float)(vertices[1][1] - vertices[0][1]) / (float)(vertices[1][0] - vertices[0][0]), outro->vertices[i]);
            // printf("%c - %f (%d, %d)\n\n\n", 'A' + i, projecao[i], outro->vertices[i][0], outro->vertices[i][1]);
        }

        float menorA = (projecaoAB < projecaoCD) ? projecaoAB : projecaoCD;
        float maiorA = (projecaoAB > projecaoCD) ? projecaoAB : projecaoCD;
        float menorB = min(projecao);
        float maiorB = max(projecao);

        if (!(menorA < maiorB && maiorA > menorB))
            return false;

        projecaoAB = projecaoY((float)(vertices[2][1] - vertices[1][1]) / (float)(vertices[2][0] - vertices[1][0]), vertices[1]);
        projecaoCD = projecaoY((float)(vertices[0][1] - vertices[3][1]) / (float)(vertices[0][0] - vertices[3][0]), vertices[3]);

        // printf("projAB: %f p: (%d, %d) | projCD: %f p: (%d, %d) \n\n\n", projecaoAB, vertices[1][0], vertices[1][1], projecaoCD, vertices[3][0], vertices[3][1]);

        // projecao dos pontos(com o angulo dos anteriores) no eixo X do outro objeto
        for (int i = 0; i < 4; i++)
        {
            projecao[i] = projecaoY((float)(vertices[2][1] - vertices[1][1]) / (float)(vertices[2][0] - vertices[1][0]), outro->vertices[i]);
            // printf("%c - %f (%d, %d)\n\n\n", 'A' + i, projecao[i], outro->vertices[i][0], outro->vertices[i][1]);
        }

        menorA = (projecaoAB < projecaoCD) ? projecaoAB : projecaoCD;
        maiorA = (projecaoAB > projecaoCD) ? projecaoAB : projecaoCD;
        menorB = min(projecao);
        maiorB = max(projecao);

        return (menorA < maiorB && maiorA > menorB);
    }*/

    PIG_Cor **GetPixels()
    {
        return pixels;
    }

    void AtualizaPixels(int retiraFundo = 1, int opacidadeObj = 255)
    {
        Uint8 *pix8;
        Uint32 *pix32;
        if (bitmap->format->BytesPerPixel == 3)
        {
            for (int h = 0; h < bitmap->h; h++)
            {
                pix8 = (Uint8 *)bitmap->pixels + (h * bitmap->pitch);
                for (int w = 0; w < bitmap->w; w++)
                {
                    if (bitmap->format->format == SDL_PIXELFORMAT_RGB24)
                    {
                        *pix8 = pixels[h][w].r;
                        pix8++;
                        *pix8 = pixels[h][w].g;
                        pix8++;
                        *pix8 = pixels[h][w].b;
                        pix8++;
                    }
                    else
                    {
                        *pix8 = pixels[h][w].b;
                        pix8++;
                        *pix8 = pixels[h][w].g;
                        pix8++;
                        *pix8 = pixels[h][w].r;
                        pix8++;
                    }
                }
            }
        }
        else if (bitmap->format->BytesPerPixel == 4)
        {
            pix32 = (Uint32 *)bitmap->pixels;
            for (int h = 0; h < bitmap->h; h++)
            {
                for (int w = 0; w < bitmap->w; w++)
                {
                    SDL_GetRGBA((Uint32)*pix32, bitmap->format, &(pixels[h][w].r), &(pixels[h][w].g), &(pixels[h][w].b), &(pixels[h][w].a));
                    pix32++;
                }
            }
        }

        SetOpacidade(opacidadeObj);
        CriaTextura(retiraFundo);
    }

    void Move(int nx,int ny)override{
        x = nx;
        y = ny;
        dest.x = x;
        dest.y = altJanela-alt-y;
        AtualizaBB();
    }
};

typedef CObjeto *Objeto;
