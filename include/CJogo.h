class CJogo{

private:

    PIG_Evento ultimoEvento;
    PIG_Teclado teclado;
    int contFPS,lastFPS;
    Timer timerFPS;
    int estado;
    int rodando;
    std::string diretorioAtual;

public:

    OffscreenRenderer offRenderer;
    int cursorPadrao;

    CJogo(char *nome,int cursor=0,int altura=ALT_TELA,int largura=LARG_TELA){
        rodando = true;
        teclado = SDL_GetKeyboardState(NULL);
        estado = 0;
        contFPS = lastFPS = 0;
        timerFPS = new CTimer(false);
        offRenderer = NULL;
        cursorPadrao = cursor;

        diretorioAtual = PIGGetDiretorioAtual();
        //printf("path: %s\n",diretorioAtual);//exibir a pasta original da PIG


		//SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS,"1");
        if( SDL_Init( SDL_INIT_EVERYTHING) < 0 ){
            printf( "Nao foi possivel iniciar o SDL! SDL_Error: %s\n", SDL_GetError() );
        }else{
            CGerenciadorJanelas::Inicia(nome,altura,largura);
        }

        // Initialize the joystick subsystem
        SDL_InitSubSystem(SDL_INIT_JOYSTICK);

        SDLNet_Init();
    }

    ~CJogo(){

        SDLNet_Quit();

        delete timerFPS;
        if (offRenderer) delete offRenderer;

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
            case SDL_MOUSEBUTTONUP:
                ultimoEvento.tipoEvento = EVENTO_MOUSE;
                ultimoEvento.mouse.acao = event.type; //MOUSE_PRESSIONADO(SDL_MOUSEBUTTODOWN) ou MOUSELIBERADO(SDL_MOUSEBUTTONUP);
                ultimoEvento.mouse.botao= event.button.button;
                ultimoEvento.mouse.numeroJanela = event.window.windowID-JANELA_INICIAL;
                ultimoEvento.mouse.cliques = event.button.clicks;
                ultimoEvento.mouse.posX = event.button.x;
                ultimoEvento.mouse.posY = CGerenciadorJanelas::GetAltura(ultimoEvento.mouse.numeroJanela) - event.button.y-1;
                CMouse::ProcessaEvento(ultimoEvento);
                break;
           /*case SDL_MOUSEBUTTONUP:
                ultimoEvento.tipoEvento = EVENTO_MOUSE;
                ultimoEvento.mouse.acao = MOUSE_LIBERADO;
                ultimoEvento.mouse.botao= event.button.button;
                ultimoEvento.mouse.numeroJanela = event.window.windowID-JANELA_INICIAL;
                ultimoEvento.mouse.cliques = event.button.clicks;
                ultimoEvento.mouse.posX = event.button.x;
                ultimoEvento.mouse.posY = CGerenciadorJanelas::GetAltura(ultimoEvento.mouse.numeroJanela) - event.button.y-1;
                CMouse::ProcessaEvento(ultimoEvento);
                break;
            */
            case SDL_MOUSEMOTION:
                ultimoEvento.tipoEvento = EVENTO_MOUSE;
                ultimoEvento.mouse.acao = MOUSE_MOVIDO;
                ultimoEvento.mouse.numeroJanela = event.window.windowID-JANELA_INICIAL;
                ultimoEvento.mouse.posX = event.motion.x;
                ultimoEvento.mouse.posY = CGerenciadorJanelas::GetAltura(ultimoEvento.mouse.numeroJanela) - event.motion.y-1;
                ultimoEvento.mouse.relX = event.motion.xrel;
                ultimoEvento.mouse.relY = -event.motion.yrel;
                CMouse::ProcessaEvento(ultimoEvento);
                //CMouse::Move(ultimoEvento.mouse.posX, ultimoEvento.mouse.posY);
                break;
            case SDL_MOUSEWHEEL:
                ultimoEvento.tipoEvento = EVENTO_MOUSE;
                ultimoEvento.mouse.acao = MOUSE_RODINHA;
                ultimoEvento.mouse.numeroJanela = event.window.windowID-JANELA_INICIAL;
                ultimoEvento.mouse.relX = event.wheel.x;
                ultimoEvento.mouse.relY = event.wheel.y;
                CMouse::ProcessaEvento(ultimoEvento);
                break;
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                ultimoEvento.tipoEvento = EVENTO_TECLADO;
                ultimoEvento.teclado.acao = event.type; //TECLA_PRESSIONADA(SDL_KEYDOWN) ou TECLA_LIBERADA(SDL_KEYUP);
                ultimoEvento.teclado.tecla = event.key.keysym.scancode;
                ultimoEvento.teclado.repeticao = event.key.repeat;
                break;
            /*case SDL_KEYUP:
                ultimoEvento.tipoEvento = EVENTO_TECLADO;
                ultimoEvento.teclado.acao = TECLA_LIBERADA;
                ultimoEvento.teclado.tecla = event.key.keysym.scancode;
                ultimoEvento.teclado.repeticao = event.key.repeat;
                break;
            */
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
            case SDL_CONTROLLERBUTTONUP:
                ultimoEvento.tipoEvento = EVENTO_CONTROLADOR;
                ultimoEvento.controlador.acao = event.type; //CONTROLADOR_BOTAO_PRESSIONADO(SDL_CONTROLLERBUTTONDOWN) ou CONTROLADOR_BOTAO_LIBERADO(SDL_CONTROLLERBUTTONUP);
                ultimoEvento.controlador.botao = event.cbutton.button;
                ultimoEvento.controlador.idControlador = event.cdevice.which;
                SDL_PollEvent(&event);
                break;
            /*case SDL_CONTROLLERBUTTONUP:
                ultimoEvento.tipoEvento = EVENTO_CONTROLADOR;
                ultimoEvento.controlador.acao = CONTROLADOR_BOTAO_LIBERADO;
                ultimoEvento.controlador.botao = event.cbutton.button;
                ultimoEvento.controlador.idControlador = event.cdevice.which;
                SDL_PollEvent(&event);
                break;
            */
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
        if (timerFPS->GetTempoDecorrido()>PIG_INTERVALO_FPS){
            lastFPS=contFPS;
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

    inline float GetFPS(){
        return lastFPS/PIG_INTERVALO_FPS;
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

        //calcula o bounding-box do poligono
        for (int i=0;i<lados;i++){
            if (px[i]<minX) minX = px[i];
            if (py[i]<minY) minY = py[i];
            if (px[i]>maxX) maxX = px[i];
            if (py[i]>maxY) maxY = py[i];
            cx += px[i]; //centro do poligono
            cy += py[i]; //centro do poligono
        }
        cx /= lados; //centro do poligono
        cy /= lados; //centro do poligono

        int alt = maxY-minY+1;  //altura absoluta do poligono
        int larg = maxX-minX+1; //altura absoluta do poligono

        OffscreenRenderer off = new COffscreenRenderer(alt,larg); //ajustado extamente com a altura e largura

        if (PIGCoresIguais(cor,PRETO)){
            off->PintarFundo(BRANCO);
        }else off->PintarFundo(PRETO);

        for (int i=0;i<lados;i++)
            off->DesenharLinha(px[i]-minX,py[i]-minY,px[(i+1)%lados]-minX,py[(i+1)%lados]-minY,cor);

        off->PintarArea(cx-minX,cy-minY,cor,NULL);

        SDL_Surface *surf = off->GetSurface();
        if (PIGCoresIguais(cor,PRETO)){
            SDL_SetColorKey( surf, SDL_TRUE, SDL_MapRGBA(surf->format, 255, 255, 255, 255) );
        }else SDL_SetColorKey( surf, SDL_TRUE, SDL_MapRGBA(surf->format, 0, 0, 0, 255) );

        SDL_Renderer *renderer = CGerenciadorJanelas::GetJanela(idJanela)->GetRenderer();
        SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, surf);
        SDL_Rect r;
        r.h = alt;
        r.w = larg;
        r.x = minX;
        r.y = CGerenciadorJanelas::GetAltura(idJanela)-minY-alt;
        //printf("%d,%d %d,%d\n",r.x,r.y,r.h,r.w);
        SDL_RenderCopy(renderer,text,NULL,&r);
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
