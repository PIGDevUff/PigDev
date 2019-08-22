class CJogo{

private:

    PIG_Evento ultimoEvento;
    PIG_Teclado teclado;
    int contFPS;
    Timer timerFPS;
    int fontesUsadas;
    MapaCaracteres fontes[MAX_FONTES];
    int estado;
    int rodando;
    char *diretorioAtual;

void GetDiretorioAtual(){
    diretorioAtual = SDL_GetBasePath();
    if (!diretorioAtual)
        diretorioAtual = SDL_strdup("./");
    /*char *base_path = SDL_GetBasePath();
    if (base_path) {
        diretorioAtual = base_path;
    } else {
        diretorioAtual = SDL_strdup("./");
    }*/
    CHDIR(diretorioAtual);
}

public:

    OffscreenRenderer offRenderer;
    int cursorPadrao;

    CJogo(char *nome,int cursor=0,int altura=ALT_TELA,int largura=LARG_TELA){
        rodando = true;
        teclado = SDL_GetKeyboardState(NULL);
        estado = 0;
        contFPS = 0;
        timerFPS = new CTimer(false);
        offRenderer = NULL;
        cursorPadrao = cursor;

        GetDiretorioAtual();
        printf("path: %s\n",diretorioAtual);


		//SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS,"1");
        if( SDL_Init( SDL_INIT_EVERYTHING) < 0 ){
            printf( "Nao foi possivel iniciar o SDL! SDL_Error: %s\n", SDL_GetError() );
        }else{
            CGerenciadorJanelas::Inicia(nome,altura,largura);
        }

        // Initialize the joystick subsystem
        SDL_InitSubSystem(SDL_INIT_JOYSTICK);

        TTF_Init();

        //inicializa o vetor contendo as fontes a serem usadas no jogo
        for (int i=0;i<MAX_FONTES;i++)
            fontes[i] = NULL;

        //criação da fonte padrão da PIG (fonte com identificador 0)
        fontes[0] = new CMapaCaracteres("..//fontes//arial.ttf",CGerenciadorJanelas::GetJanela(0)->GetRenderer(),CGerenciadorJanelas::GetJanela(0)->GetAltura(),36,ESTILO_NORMAL,BRANCO,0,BRANCO);
        fontesUsadas = 1;

        SDLNet_Init();
    }

    ~CJogo(){
        free(diretorioAtual);

        SDLNet_Quit();

        delete timerFPS;
        if (offRenderer) delete offRenderer;

        for (int i=0;i<MAX_FONTES;i++)
            if (fontes[i]) delete fontes[i];
        TTF_Quit();

        CGerenciadorJanelas::Encerra();
    }

    PIG_Evento PegaEvento(){
        SDL_Event event;
        int resp;
        //if (despausa)
        //    resp = SDL_PeepEvents(&event,1,SDL_GETEVENT,EVENTO_VIDEO,EVENTO_VIDEO);
        //else

        resp =SDL_PollEvent(&event);
        if (resp){
            if (event.type==SDL_QUIT)
                rodando = false;
            //if (event.type) printf("Tipo: %d\n",event.type);
            switch(event.type){
            /*case FF_ALLOC_EVENT:
            case FF_REFRESH_EVENT:
            case FF_QUIT_EVENT:
                ultimoEvento.tipoEvento = EVENTO_VIDEO;
                ultimoEvento.video.acao = event.type;
                //PlayerAV *player = (Player) event.user.data1;
                //player->TrataEvento(ultimoEvento);
                break;
            */
            case SDL_USEREVENT:
                if (event.user.code==EVENTO_AUDIO){
                    ultimoEvento.tipoEvento = EVENTO_AUDIO;
                    ultimoEvento.audio.audioId = *((int*)event.user.data1);
                }else if (event.user.code==EVENTO_REDE){
                    ultimoEvento.tipoEvento = EVENTO_REDE;
                    ultimoEvento.rede = *((InfoEventoRede*)event.user.data1);
                    free(event.user.data1);
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                ultimoEvento.tipoEvento = EVENTO_MOUSE;
                ultimoEvento.mouse.acao = MOUSE_PRESSIONADO;
                ultimoEvento.mouse.botao= event.button.button;
                ultimoEvento.mouse.numeroJanela = event.window.windowID-JANELA_INICIAL;
                ultimoEvento.mouse.cliques = event.button.clicks;
                ultimoEvento.mouse.posX = event.button.x;
                ultimoEvento.mouse.posY = CGerenciadorJanelas::GetAltura(ultimoEvento.mouse.numeroJanela) - event.button.y;
                break;
            case SDL_MOUSEBUTTONUP:
                ultimoEvento.tipoEvento = EVENTO_MOUSE;
                ultimoEvento.mouse.acao = MOUSE_LIBERADO;
                ultimoEvento.mouse.botao= event.button.button;
                ultimoEvento.mouse.numeroJanela = event.window.windowID-JANELA_INICIAL;
                ultimoEvento.mouse.cliques = event.button.clicks;
                ultimoEvento.mouse.posX = event.button.x;
                ultimoEvento.mouse.posY = CGerenciadorJanelas::GetAltura(ultimoEvento.mouse.numeroJanela) - event.button.y;
                break;
            case SDL_MOUSEMOTION:
                ultimoEvento.tipoEvento = EVENTO_MOUSE;
                ultimoEvento.mouse.acao = MOUSE_MOVIDO;
                ultimoEvento.mouse.numeroJanela = event.window.windowID-JANELA_INICIAL;
                ultimoEvento.mouse.posX = event.motion.x;
                ultimoEvento.mouse.posY = CGerenciadorJanelas::GetAltura(ultimoEvento.mouse.numeroJanela) - event.motion.y-1;
                ultimoEvento.mouse.relX = event.motion.xrel;
                ultimoEvento.mouse.relY = -event.motion.yrel;
                //if (cursorPadrao!=0)
                    CMouse::Move(ultimoEvento.mouse.posX,ultimoEvento.mouse.posY-33);//CGerenciadorJanelas::GetAltura(ultimoEvento.mouse.numeroJanela)-ultimoEvento.mouse.posY);
                break;
            case SDL_MOUSEWHEEL:
                ultimoEvento.tipoEvento = EVENTO_MOUSE;
                ultimoEvento.mouse.acao = MOUSE_RODINHA;
                ultimoEvento.mouse.numeroJanela = event.window.windowID-JANELA_INICIAL;
                ultimoEvento.mouse.relX = event.wheel.x;
                ultimoEvento.mouse.relY = event.wheel.y;
                break;
            case SDL_KEYDOWN:
                ultimoEvento.tipoEvento = EVENTO_TECLADO;
                ultimoEvento.teclado.acao = TECLA_PRESSIONADA;
                ultimoEvento.teclado.tecla = event.key.keysym.scancode;
                ultimoEvento.teclado.repeticao = event.key.repeat;
                break;
            case SDL_KEYUP:
                ultimoEvento.tipoEvento = EVENTO_TECLADO;
                ultimoEvento.teclado.acao = TECLA_LIBERADA;
                ultimoEvento.teclado.tecla = event.key.keysym.scancode;
                ultimoEvento.teclado.repeticao = event.key.repeat;
                break;
            case SDL_TEXTEDITING:
                ultimoEvento.tipoEvento = EVENTO_TECLADO;
                ultimoEvento.teclado.acao = TECLA_EDICAO;
                ultimoEvento.teclado.inicio = event.edit.start;
                ultimoEvento.teclado.tamanhoSelecao = event.edit.length;
                strcpy(ultimoEvento.teclado.texto,event.edit.text);
                break;
            case SDL_TEXTINPUT:
                ultimoEvento.tipoEvento = EVENTO_TECLADO;
                ultimoEvento.teclado.acao = TECLA_INPUT;
                strcpy(ultimoEvento.teclado.texto,event.edit.text);
                break;
            case SDL_WINDOWEVENT:
                if (event.window.event==JANELA_FECHADA){
                    CGerenciadorJanelas::GetJanela(event.window.windowID-JANELA_INICIAL)->Fecha();
                }
                ultimoEvento.tipoEvento = EVENTO_JANELA;
                ultimoEvento.janela.acao = event.window.event;
                ultimoEvento.janela.numeroJanela = event.window.windowID-JANELA_INICIAL;
                ultimoEvento.janela.dado1 = event.window.data1;
                ultimoEvento.janela.dado2 = event.window.data2;
                break;
            case SDL_CONTROLLERBUTTONDOWN:
            //case SDL_JOYAXISMOTION:
                ultimoEvento.tipoEvento = EVENTO_CONTROLADOR;
                ultimoEvento.controlador.acao = CONTROLADOR_BOTAO_PRESSIONADO;
                ultimoEvento.controlador.botao = event.cbutton.button;
                ultimoEvento.controlador.idControlador = event.cdevice.which;
                SDL_PollEvent(&event);
                break;
            case SDL_CONTROLLERBUTTONUP:
            //case SDL_JOYAXISMOTION:
                ultimoEvento.tipoEvento = EVENTO_CONTROLADOR;
                ultimoEvento.controlador.acao = CONTROLADOR_BOTAO_LIBERADO;
                ultimoEvento.controlador.botao = event.cbutton.button;
                ultimoEvento.controlador.idControlador = event.cdevice.which;
                SDL_PollEvent(&event);
                break;

            case SDL_CONTROLLERAXISMOTION:
            //case SDL_JOYAXISMOTION:
                ultimoEvento.tipoEvento = EVENTO_CONTROLADOR;
                ultimoEvento.controlador.acao = CONTROLADOR_EIXO_MOVIDO;
                ultimoEvento.controlador.eixo = event.caxis.axis;
                ultimoEvento.controlador.valor = event.caxis.value;
                ultimoEvento.controlador.percentualEixo = 1.0f*ultimoEvento.controlador.valor/(1<<15);
                ultimoEvento.controlador.idControlador = event.cdevice.which;
                SDL_PollEvent(&event);
                break;
            /*default:
                    if (event.type){
                        printf("Evento: %d\n",event.type);
                    }
            */
            }
        }else ultimoEvento.tipoEvento = EVENTO_NULO;
        return ultimoEvento;
    }

    void DefineFuncaoPintarArea(PIG_Cor (*funcao)(int,int,int,int,PIG_Cor,PIG_Cor)){
        if (offRenderer)
            offRenderer->DefineFuncaoPintarArea(funcao);
    }

    inline PIG_Teclado PegaTeclado(){
        return teclado;
    }

    void IniciaInputTextoTela(){
        SDL_StartTextInput();
    }

    void EncerraInputTextoTela(){
        SDL_StopTextInput();
    }

    void IniciaDesenho(int idJanela=-1){
        CGerenciadorJanelas::IniciaDesenho(idJanela);
    }

    void EncerraDesenho(int idJanela=-1){
        CGerenciadorJanelas::EncerraDesenho(idJanela);

        //int off;
        //unsigned int frameTime = SDL_GetTicks();
        /*SDL_Surface* saveSurface = NULL;
        SDL_Surface* infoSurface = NULL;
        infoSurface = NULL;//SDL_GetWindowSurface(window);
        if (infoSurface != NULL) {
            int pitch = infoSurface->format->BytesPerPixel;

            unsigned char * pixels = new unsigned char[infoSurface->w * infoSurface->h * infoSurface->format->BytesPerPixel];
            if (pixels != 0) {

                if (SDL_RenderReadPixels(renderer, &infoSurface->clip_rect, infoSurface->format->format, pixels, infoSurface->w * infoSurface->format->BytesPerPixel) == 0) {
                    /*for (int i=0;i<infoSurface->h;i+=4){
                        for (int j=0;j<infoSurface->w;j+=4){
                            off = (i*infoSurface->w+j)*4;

                            for (int k=0;k<4;k++){
                                pixels[off+4+k]=pixels[off+k];
                                pixels[off+8+k]=pixels[off+k];
                                pixels[off+12+k]=pixels[off+k];
                                pixels[off+infoSurface->w*4+k]=pixels[off+k];
                                pixels[off+infoSurface->w*4+4+k]=pixels[off+k];
                                pixels[off+infoSurface->w*4+8+k]=pixels[off+k];
                                pixels[off+infoSurface->w*4+12+k]=pixels[off+k];
                                pixels[off+infoSurface->w*8+k]=pixels[off+k];
                                pixels[off+infoSurface->w*8+4+k]=pixels[off+k];
                                pixels[off+infoSurface->w*8+8+k]=pixels[off+k];
                                pixels[off+infoSurface->w*8+12+k]=pixels[off+k];
                                pixels[off+infoSurface->w*12+k]=pixels[off+k];
                                pixels[off+infoSurface->w*12+4+k]=pixels[off+k];
                                pixels[off+infoSurface->w*12+8+k]=pixels[off+k];
                                pixels[off+infoSurface->w*12+12+k]=pixels[off+k];
                            }
                        }
                    }

                    //saveSurface = SDL_CreateRGBSurfaceFrom(pixels, infoSurface->w, infoSurface->h, infoSurface->format->BitsPerPixel, infoSurface->w * infoSurface->format->BytesPerPixel, infoSurface->format->Rmask, infoSurface->format->Gmask, infoSurface->format->Bmask, infoSurface->format->Amask);
                    //SDL_Texture *t= SDL_CreateTextureFromSurface(renderer,saveSurface);
                    //SDL_Texture *t = SDL_CreateTexture(renderer,
                    //                                   infoSurface->format->format,SDL_TEXTUREACCESS_STREAMING,LARG_TELA,ALT_TELA);
                    //SDL_UpdateTexture(t,NULL,pixels,pitch*infoSurface->w);
                    SDL_RenderCopy(renderer,t,NULL,NULL);
                    SDL_DestroyTexture(t);
                    //SDL_FreeSurface(saveSurface);
                }

            }
            delete[] pixels;
            SDL_FreeSurface(infoSurface);
        }*/
        //SDL_RenderPresent(renderer);

        contFPS++;
        if (timerFPS->GetTempoDecorrido()>1.0){
            contFPS=0;
            timerFPS->Reinicia(false);
        }
    }

    int GetEstado(){
        return estado;
    }

    int GetRodando(){
        return rodando;
    }

    void SetEstado(int valor){
        estado = valor;
    }

    Janela GetJanela(int indice){
        return CGerenciadorJanelas::GetJanela(indice);
    }

    void DesenhaRetangulo(int x, int y, int altura, int largura, PIG_Cor cor, int idJanela=0){
        SDL_Rect rect;
        rect.x = x;
        rect.y = CGerenciadorJanelas::GetAltura(idJanela)-(y+altura);
        rect.h = altura;
        rect.w = largura;

        SDL_SetRenderDrawColor(CGerenciadorJanelas::GetJanela(idJanela)->GetRenderer(), cor.r,cor.g,cor.b,cor.a);
        SDL_RenderFillRect(CGerenciadorJanelas::GetJanela(idJanela)->GetRenderer(),&rect);
    }

    void DesenhaRetanguloVazado(int x, int y, int altura, int largura, PIG_Cor cor,int idJanela=0){
        SDL_Rect rect;
        rect.x = x;
        rect.y = CGerenciadorJanelas::GetAltura(idJanela)-(y+altura);
        rect.h = altura;
        rect.w = largura;


        SDL_SetRenderDrawColor(CGerenciadorJanelas::GetJanela(idJanela)->GetRenderer(), cor.r,cor.g,cor.b,cor.a);
        SDL_RenderDrawRect(CGerenciadorJanelas::GetJanela(idJanela)->GetRenderer(),&rect);
    }

    void DesenhaLinhaSimples(int x1,int y1,int x2,int y2,PIG_Cor cor,int idJanela=0){
        SDL_SetRenderDrawColor(CGerenciadorJanelas::GetJanela(idJanela)->GetRenderer(),cor.r,cor.g,cor.b,255);
        SDL_RenderDrawLine(CGerenciadorJanelas::GetJanela(idJanela)->GetRenderer(),x1,CGerenciadorJanelas::GetAltura(idJanela)-y1,x2,CGerenciadorJanelas::GetAltura(idJanela)-y2);
    }

    void DesenhaLinhasDisjuntas(int *x,int *y,int qtd,PIG_Cor cor,int idJanela=0){
        SDL_Renderer *renderer = CGerenciadorJanelas::GetJanela(idJanela)->GetRenderer();

        SDL_SetRenderDrawColor(renderer,cor.r,cor.g,cor.b,255);
        for (int k=0;k<qtd*2;k+=2){
            SDL_RenderDrawLine(renderer,x[k],CGerenciadorJanelas::GetAltura(idJanela)-y[k],x[k+1],CGerenciadorJanelas::GetAltura(idJanela)-y[k+1]);
        }
    }

    void DesenhaLinhasSequencia(int *x,int *y,int qtd,PIG_Cor cor,int idJanela=0){
        SDL_Renderer *renderer = CGerenciadorJanelas::GetJanela(idJanela)->GetRenderer();

        SDL_SetRenderDrawColor(renderer,cor.r,cor.g,cor.b,255);
        for (int k=0;k<qtd-1;k++){
            SDL_RenderDrawLine(renderer,x[k],CGerenciadorJanelas::GetAltura(idJanela)-y[k],x[k+1],CGerenciadorJanelas::GetAltura(idJanela)-y[k+1]);
        }
    }

    int CriaFonteFundo(char *nome,int tamanho,int estilo,char *arquivoFundo,int contorno,PIG_Cor corContorno,int idJanela=0){
        int aux = fontesUsadas;
        fontes[fontesUsadas] = new CMapaCaracteres(nome,CGerenciadorJanelas::GetJanela(idJanela)->GetRenderer(),CGerenciadorJanelas::GetJanela(idJanela)->GetAltura(),tamanho,estilo,arquivoFundo,contorno,corContorno);
        fontesUsadas++;
        return aux;
    }

    int CriaFonteNormal(char *nome,int tamanho,int estilo,PIG_Cor corLetra,int contorno,PIG_Cor corContorno,int idJanela=0){
        int aux = fontesUsadas;
        fontes[fontesUsadas] = new CMapaCaracteres(nome,CGerenciadorJanelas::GetJanela(idJanela)->GetRenderer(),CGerenciadorJanelas::GetJanela(idJanela)->GetAltura(),tamanho,estilo,corLetra,contorno,corContorno);
        fontesUsadas++;
        return aux;
    }

    inline int GetLarguraPixels(char *str,int numFonte=0){
        return fontes[numFonte]->GetLarguraPixelsString(str);
    }

    inline void EscreverCentralizada(char *str,int x,int y,int numFonte=0){
        fontes[numFonte]->EscreveStringCentralizado(str,x,y);
    }

    inline void EscreverDireita(char *str,int x,int y,int numFonte=0){
        fontes[numFonte]->EscreveStringDireita(str,x,y);
    }

    inline void EscreverEsquerda(char *str,int x,int y,int numFonte=0){
        fontes[numFonte]->EscreveStringEsquerda(str,x,y);
    }

    inline void EscreverLongaCentralizada(char *str,int x,int y,int largMax,int espacoEntreLinhas,int numFonte=0){
        std::string texto(str);
        fontes[numFonte]->EscreveStringLongaCentralizado(texto,x,y,largMax,espacoEntreLinhas);
    }

    inline void EscreverLongaDireita(char *str,int x,int y,int largMax,int espacoEntreLinhas,int numFonte=0){
        std::string texto(str);
        fontes[numFonte]->EscreveStringLongaDireita(texto,x,y,largMax,espacoEntreLinhas);
    }

    inline void EscreverLongaEsquerda(char *str,int x,int y,int largMax,int espacoEntreLinhas,int numFonte=0){
        std::string texto(str);
        fontes[numFonte]->EscreveStringLongaEsquerda(texto,x,y,largMax,espacoEntreLinhas);
    }

    SDL_Surface *GetGlyph(char *ch,int numFonte=0){
        return fontes[numFonte]->GetGlyph(ch);
    }

    void GetPixel(int x,int y,int *r,int *g,int *b,int idJanela=0) {
        int altTela = CGerenciadorJanelas::GetAltura(idJanela);
        int largTela = CGerenciadorJanelas::GetLargura(idJanela);

        if (x<0 || x>=largTela  ||y<0 ||y>=altTela) return;

        SDL_Surface* infoSurface = SDL_GetWindowSurface(CGerenciadorJanelas::GetJanela(idJanela)->GetWindow());
        if (infoSurface != NULL) {
            unsigned char * pixels = new unsigned char[infoSurface->w * infoSurface->h * infoSurface->format->BytesPerPixel];
            if (pixels != 0) {
                if (SDL_RenderReadPixels(CGerenciadorJanelas::GetJanela(idJanela)->GetRenderer(), &infoSurface->clip_rect, infoSurface->format->format, pixels, infoSurface->w * infoSurface->format->BytesPerPixel) == 0) {
                    Uint8 mr,mg,mb;
                    Uint32 *p = (Uint32*) pixels;
                    p += (x+(altTela-y)*largTela);
                    SDL_GetRGB(*p,(const SDL_PixelFormat*) &infoSurface->format->format,&mr,&mg,&mb);
                    *r = mr;
                    *g = mg;
                    *b = mb;
                }
                delete[] pixels;
            }
            SDL_FreeSurface(infoSurface);
        }
    }

    inline float GetFPS(){
        return contFPS/timerFPS->GetTempoDecorrido();
    }

    void PreparaOffScreenRenderer(int altura,int largura){
        if (offRenderer) delete offRenderer;
        offRenderer = new COffscreenRenderer(altura,largura);
    }

    inline void SalvaOffScreenBMP(char *nomeArquivo){
        if (offRenderer)
            offRenderer->SalvarImagemBMP(nomeArquivo);
    }

    inline void SalvaOffScreenPNG(char *nomeArquivo){
        if (offRenderer)
            offRenderer->SalvarImagemPNG(nomeArquivo);
    }

    inline int GetXCaneta(){
        if (offRenderer)
            return offRenderer->GetXCaneta();
        return 0;
    }

    inline int GetYCaneta(){
        if (offRenderer)
            return offRenderer->GetYCaneta();
        return 0;
    }

    inline void PintaAreaOffScreen(int px,int py,PIG_Cor cor,void *ponteiro){
        if (offRenderer)
            offRenderer->PintarArea(px,py,cor,ponteiro);
    }

    inline void PintarPoligono(int px[],int py[],int lados,PIG_Cor cor,int idJanela=0){
        int minX=99999,maxX=-1,minY=99999,maxY=-1;
        int cx=0,cy=0;

        for (int i=0;i<lados;i++){
            if (px[i]<minX)
                minX = px[i];
            if (py[i]<minY)
                minY = py[i];
            if (px[i]>maxX)
                maxX = px[i];
            if (py[i]>maxY)
                maxY = py[i];
            cx += px[i];
            cy += py[i];
        }
        cx /= lados;
        cy /= lados;

        int alt = maxY-minY+1;
        int larg = maxX-minX+1;

        OffscreenRenderer off = new COffscreenRenderer(alt,larg);

        if (CORESIGUAIS(cor,PRETO)){
            off->PintarFundo(BRANCO);
        }else off->PintarFundo(PRETO);

        for (int i=0;i<lados;i++){
            off->DesenharLinha(px[i]-minX,py[i]-minY,px[(i+1)%lados]-minX,py[(i+1)%lados]-minY,cor);
        }

        SDL_Surface *surf = off->GetSurface();
        SDL_LockSurface(surf);

        Uint32 color = SDL_MapRGBA((const SDL_PixelFormat*) &surf->format->format,cor.r,cor.g,cor.b,cor.a);

        CPilhaCoordenada *pilha = new CPilhaCoordenada();
        pilha->Empilha(cx-minX,cy-minY);
        int x,y;
        Uint32 *p;
        while (pilha->Desempilha(x,y)){

            if (x>=0&&y>=0&&x<larg&&y<alt){
                p = (Uint32*) surf->pixels;
                p += (x+(alt-y-1)*larg);

                if ( *p != color){
                    *p = color;     //muda efetivamente a cor
                    pilha->Empilha(x+1,y+0);
                    pilha->Empilha(x+0,y+1);
                    pilha->Empilha(x-1,y+0);
                    pilha->Empilha(x+0,y-1);
                }
            }
        }

        delete pilha;
        SDL_UnlockSurface(surf);

        if (CORESIGUAIS(cor,PRETO)){
            SDL_SetColorKey( surf, SDL_TRUE, SDL_MapRGBA(surf->format, 255, 255, 255, 255) );
        }else SDL_SetColorKey( surf, SDL_TRUE, SDL_MapRGBA(surf->format, 0, 0, 0, 255) );

        SDL_Texture *text = SDL_CreateTextureFromSurface(CGerenciadorJanelas::GetJanela(idJanela)->GetRenderer(), surf);
        SDL_Rect r;
        r.h = alt;
        r.w = larg;
        r.x = minX;
        r.y = CGerenciadorJanelas::GetAltura(idJanela)-minY;
        SDL_RenderCopy(CGerenciadorJanelas::GetJanela(idJanela)->GetRenderer(),text,NULL,&r);
        SDL_DestroyTexture(text);
        delete off;
    }

    inline void PintaFundoOffScreen(PIG_Cor cor){
        if (offRenderer)
            offRenderer->PintarFundo(cor);
    }

    inline void DesenhaRetanguloOffScreen(int x1,int y1,int altura,int largura,PIG_Cor cor){
        if (offRenderer)
            offRenderer->DesenharRetangulo(x1,y1,altura,largura,cor);
    }

    inline void DesenhaRetanguloVazadoOffScreen(int x1,int y1,int altura,int largura,PIG_Cor cor){
        if (offRenderer)
            offRenderer->DesenharRetanguloVazado(x1,y1,altura,largura,cor);
    }

    inline void DesenhaLinhaOffScreen(int x1,int y1,int x2,int y2,PIG_Cor cor){
        if (offRenderer)
            offRenderer->DesenharLinha(x1,y1,x2,y2,cor);
    }

    inline void MoveCanetaOffscreen(double nx,double ny){
        if (offRenderer)
            offRenderer->MoveCanetaPara(nx,ny);
    }

    inline void AvancaCanetaOffscreen(double distancia){
        if (offRenderer)
            offRenderer->AvancaCaneta(distancia);
    }

    inline void MudaCorCanetaOffscreen(PIG_Cor novaCor){
        if (offRenderer)
            offRenderer->MudaCorAtualCaneta(novaCor);
    }

    inline void GiraCanetaHorarioOffscreen(double angulo){
        if (offRenderer)
            offRenderer->GiraCanetaHorario(angulo);
    }

    inline void GiraCanetaAntiHorarioOffscreen(double angulo){
        if (offRenderer)
            offRenderer->GiraCanetaAntiHorario(angulo);
    }

    inline void GiraCanetaAnguloFixoOffscreen(double angulo){
        if (offRenderer)
            offRenderer->GiraAnguloFixo(angulo);
    }

    inline double GetAngAtual(){
        if (offRenderer)
            return offRenderer->GetAngAtual();
        else return 0.0;
    }

};

typedef CJogo* Jogo;
