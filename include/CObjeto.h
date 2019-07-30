class CObjeto:public CVisual{

protected:
    std::map<int,int> valoresIntInt;
    std::map<std::string,int> valoresStringInt;
    std::map<int,float> valoresIntFloat;
    std::map<std::string,float> valoresStringFloat;
    std::map<int,std::string> valoresIntString;
    std::map<std::string,std::string> valoresStringString;
    SDL_Point bb[4];
    PIG_Cor **pixels;

    void DesenhaBB(){
        SDL_SetRenderDrawColor(renderer,0,255,0,255);
        SDL_RenderDrawLine(renderer,bb[0].x,altJanela-bb[0].y,bb[1].x,altJanela-bb[1].y);
        SDL_RenderDrawLine(renderer,bb[1].x,altJanela-bb[1].y,bb[2].x,altJanela-bb[2].y);
        SDL_RenderDrawLine(renderer,bb[2].x,altJanela-bb[2].y,bb[3].x,altJanela-bb[3].y);
        SDL_RenderDrawLine(renderer,bb[3].x,altJanela-bb[3].y,bb[0].x,altJanela-bb[0].y);
        SDL_SetRenderDrawColor(renderer,255,0,0,255);
        SDL_RenderDrawRect(renderer,&dest);
    }

    void AtualizaBB(){
        SDL_Point pivoAbs;

        SDL_SetRenderDrawColor(renderer,255,0,0,0);
        pivoAbs.x = pivoRelativo.x + x;
        pivoAbs.y = -pivoRelativo.y + y + alt;    //inverte o eixo Y, pois o pivoRel considera o eixo Y aumentando para baixo
        //printf("PivoRel: %d %d\n",pivoRelativo.x,pivoRelativo.y);
        //printf("PivoRAbs: %d %d\n",pivoAbs.x,pivoAbs.y);
        float angRad = -angulo*M_PI/180.0;
        float seno = sin(angRad);
        float cosseno = cos(angRad);
        //printf("Pivo %d %d  %f\n",pivoObj.x,pivoObj.y,angRad);

        //matriz de rotação
        // ( cos(ang) sin(ang))   (Vx)   (Rx)
        // (-sin(ang) cos(ang)) * (Vy) = (Ry)

        //vetor (Rx,Ry) é a resposta do vetor (Vx,Vy) rotacionado em ang

        bb[0].x = (x-pivoAbs.x)*cosseno+(y-pivoAbs.y)*seno+pivoAbs.x;
        bb[0].y = (y-pivoAbs.y)*cosseno-(x-pivoAbs.x)*seno+pivoAbs.y;
        //printf("bb0: %d %d\n",bb[0].x,bb[0].y);

        bb[1].x = (x+larg-pivoAbs.x)*cosseno+(y-pivoAbs.y)*seno+pivoAbs.x;
        bb[1].y = (y-pivoAbs.y)*cosseno-(x+larg-pivoAbs.x)*seno+pivoAbs.y;
        //printf("bb1: %d %d\n",bb[1].x,bb[1].y);

        bb[2].x = (x+larg-pivoAbs.x)*cosseno+(y+alt-pivoAbs.y)*seno+pivoAbs.x;
        bb[2].y = (y+alt-pivoAbs.y)*cosseno-(x+larg-pivoAbs.x)*seno+pivoAbs.y;
        //printf("bb2: %d %d\n",bb[2].x,bb[2].y);

        bb[3].x = (x-pivoAbs.x)*cosseno+(y+alt-pivoAbs.y)*seno+pivoAbs.x;
        bb[3].y = (y+alt-pivoAbs.y)*cosseno-(x-pivoAbs.x)*seno+pivoAbs.y;
        //printf("bb3: %d %d\n",bb[3].x,bb[3].y);

    }

    void ExtraiPixels(){
        Uint8 *pix8;
        Uint32 *pix32;

        pixels = (PIG_Cor**)malloc(sizeof(PIG_Cor*)*bitmap->h);
        for (int i=0;i<bitmap->h;i++){
            pixels[i] = (PIG_Cor*)calloc(sizeof(PIG_Cor),bitmap->w);
        }

        if (bitmap->format->BytesPerPixel==3){
            for (int h=0;h<bitmap->h;h++){
                pix8 = (Uint8*)bitmap->pixels+(h*bitmap->pitch);
                for (int w=0;w<bitmap->w;w++){
                    if (bitmap->format->format==SDL_PIXELFORMAT_RGB24){
                        pixels[h][w].r = *pix8;pix8++;
                        pixels[h][w].g = *pix8;pix8++;
                        pixels[h][w].b = *pix8;pix8++;
                    }else{
                        pixels[h][w].b = *pix8;pix8++;
                        pixels[h][w].g = *pix8;pix8++;
                        pixels[h][w].r = *pix8;pix8++;
                    }
                    pixels[h][w].a = 255;
                }
            }
        }else if (bitmap->format->BytesPerPixel==4){
            pix32 = (Uint32*)bitmap->pixels;
            for (int h=0;h<bitmap->h;h++){
                for (int w=0;w<bitmap->w;w++){
                    SDL_GetRGBA((Uint32)*pix32,bitmap->format,&(pixels[h][w].r),&(pixels[h][w].g),&(pixels[h][w].b),&(pixels[h][w].a));
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

    CObjeto(char* nomeArquivo,PIG_Cor *corFundo=NULL,int retiraFundo=1,int janela=0):CVisual(nomeArquivo,retiraFundo,corFundo,janela){
        //printf("visual chamado %d\n",retiraFundo);
        AtualizaBB();
        ExtraiPixels();
    }

    CObjeto(OffscreenRenderer offRender,PIG_Cor *corFundo=NULL,int retiraFundo=1,int janela=0):CVisual(offRender,retiraFundo,corFundo,janela){
        AtualizaBB();
        ExtraiPixels();
    }

    CObjeto(CObjeto *objBase,PIG_Cor *corFundo=NULL,int retiraFundo=1,int janela=0):CVisual(objBase,retiraFundo,corFundo,janela){
        AtualizaBB();
        ExtraiPixels();
    }

    ~CObjeto(){
        for (int i=0;i<bitmap->h;i++)
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

    void SetValoresInt(int chave, int valor){
        valoresIntInt[chave]=valor;
    }

    void SetValoresInt(std::string chave, int valor){
        valoresStringInt[chave]=valor;
    }

    void SetValoresFloat(int chave, float valor){
        valoresIntFloat[chave]=valor;
    }

    void SetValoresFloat(std::string chave, float valor){
        valoresStringFloat[chave]=valor;
    }

    void SetValoresString(int chave, std::string valor){
        valoresIntString[chave]=valor;
    }

    void SetValoresString(std::string chave, std::string valor){
        valoresStringString[chave]=valor;
    }

    bool GetValoresInt(int chave, int &valor){
        std::map<int,int>::iterator it;
        it = valoresIntInt.find(chave);
        if (it==valoresIntInt.end()) return false;
        valor = it->second;
        return true;
    }

    bool GetValoresInt(std::string chave, int &valor){
        std::map<std::string,int>::iterator it;
        it = valoresStringInt.find(chave);
        if (it==valoresStringInt.end()) return false;
        valor = it->second;
        return true;
    }

    bool GetValoresFloat(int chave, float &valor){
        std::map<int,float>::iterator it;
        it = valoresIntFloat.find(chave);
        if (it==valoresIntFloat.end()) return false;
        valor = it->second;
        return true;
    }

    bool GetValoresFloat(std::string chave, float &valor){
        std::map<std::string,float>::iterator it;
        it = valoresStringFloat.find(chave);
        if (it==valoresStringFloat.end()) return false;
        valor = it->second;
        return true;
    }

    bool GetValoresString(int chave, std::string &valor){
        std::map<int,std::string>::iterator it;
        it = valoresIntString.find(chave);
        if (it==valoresIntString.end()) return false;
        valor = it->second;
        return true;
    }

    bool GetValoresString(std::string chave, std::string &valor){
        std::map<std::string,std::string>::iterator it;
        it = valoresStringString.find(chave);
        if (it==valoresStringString.end()) return false;
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

    int Desenha(OffscreenRenderer offRender=NULL){
        if (offRender==NULL){
            SDL_RenderCopyEx(renderer, text, &frame,&dest,-angulo,&pivoRelativo,flip);
        }else{
            SDL_Texture *textAux = SDL_CreateTextureFromSurface(offRender->GetRenderer(),bitmap);
            SDL_Rect rectAux = dest;
            rectAux.y = offRender->GetAltura()-alt-y;
            SDL_RenderCopyEx(offRender->GetRenderer(), textAux, &frame,&rectAux,-angulo,&pivoRelativo,flip);
            SDL_DestroyTexture(textAux);
        }
        return 0;
    }

    int Colisao(CObjeto* outro){
        if (x+larg<=outro->dest.x){
            return 0;
        }
        if (x>=outro->x+outro->larg){
            return 0;
        }
        if (y+alt<=outro->y){
            return 0;
        }
        if (y>=outro->y+outro->alt){
            return 0;
        }
        return 1;
    }

    PIG_Cor **GetPixels(){
        return pixels;
    }

    void AtualizaPixels(int retiraFundo=1,int opacidadeObj=255){
        Uint8 *pix8;
        Uint32 *pix32;
        if (bitmap->format->BytesPerPixel==3){
            for (int h=0;h<bitmap->h;h++){
                pix8 = (Uint8*)bitmap->pixels+(h*bitmap->pitch);
                for (int w=0;w<bitmap->w;w++){
                    if (bitmap->format->format==SDL_PIXELFORMAT_RGB24){
                        *pix8 = pixels[h][w].r;pix8++;
                        *pix8 = pixels[h][w].g;pix8++;
                        *pix8 = pixels[h][w].b;pix8++;
                    }else{
                        *pix8 = pixels[h][w].b;pix8++;
                        *pix8 = pixels[h][w].g;pix8++;
                        *pix8 = pixels[h][w].r;pix8++;
                    }
                }
            }
        }else if (bitmap->format->BytesPerPixel==4){
            pix32 = (Uint32*)bitmap->pixels;
            for (int h=0;h<bitmap->h;h++){
                for (int w=0;w<bitmap->w;w++){
                    SDL_GetRGBA((Uint32)*pix32,bitmap->format,&(pixels[h][w].r),&(pixels[h][w].g),&(pixels[h][w].b),&(pixels[h][w].a));
                    pix32++;
                }
            }
        }

        SetOpacidade(opacidadeObj);
        CriaTextura(retiraFundo);
    }
};

typedef CObjeto* Objeto;
