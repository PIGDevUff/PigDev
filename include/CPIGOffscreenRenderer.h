#ifndef _COFFSCREENRENDERER_
#define _COFFSCREENRENDERER_

typedef struct{
    SDL_Surface *surf;
    SDL_Renderer *render;
}PIGLayer;

class CPIGOffscreenRenderer{

private:

PIGLayer layers[PIG_MAX_CAMADAS_OFFSCREEN];
int qtdLayers,maxLayers;

int alt,larg,depth;
double px,py;
double ang;
PIGCor corAtual;
PIGFuncaoPintarArea userFunctionPintarArea;

public:

    inline SDL_Renderer *GetRenderer(int layer=0){
        return layers[layer].render;
    }

    inline SDL_Surface *GetSurface(int layer=0){
        return layers[layer].surf;
    }

    inline int GetAltura(){
        return alt;
    }

    inline int GetLargura(){
        return larg;
    }

    inline int GetDepth(){
        return depth;
    }

    inline void SetCorTransparente(int layer, bool transparencia, PIGCor cor){
        SDL_SetColorKey(layers[layer].surf,transparencia,SDL_MapRGBA(layers[layer].surf->format,cor.r,cor.g,cor.b,cor.a));
    }

    inline void MergeSurface(int layerSuperior, int layerInferior, SDL_BlendMode modo){
        SDL_SetSurfaceBlendMode(layers[layerInferior].surf,modo);
        SDL_BlitSurface(layers[layerSuperior].surf,NULL,layers[layerInferior].surf,NULL);
    }

    inline PIGLayer CriaLayer(){
        PIGLayer l;
        l.surf = SDL_CreateRGBSurfaceWithFormat(0, larg, alt, depth, SDL_PIXELFORMAT_RGBA32);
        l.render = SDL_CreateSoftwareRenderer(l.surf);
        SDL_RenderClear(l.render);
        qtdLayers++;
        return l;
    }

    inline void LimpaLayer(int layer, PIGCor cor){
        SDL_SetRenderDrawColor(layers[layer].render,cor.r,cor.g,cor.b,cor.a);
        SDL_RenderClear(layers[layer].render);
    }

    CPIGOffscreenRenderer(int altura, int largura, int qtdMaxCamadas=10){
        alt = altura;
        larg=largura;
        depth = 32; //32 bits por pixel
        maxLayers = qtdMaxCamadas;
        qtdLayers = 0;
        for (int i=0;i<maxLayers;i++)
            layers[i] = CriaLayer();

        userFunctionPintarArea = NULL;

        px = py = 1;
        ang = 0;
        corAtual = BRANCO;
    }

    void DesenhaCirculoFinal(int raio, PIGCor corFundo, PIGCor corCirculo, double angInicial, double angFinal, int layer=0){
        int xm = larg/2;
        int ym = alt/2;
        SDL_Point p1,p2;
        LimpaLayer(layer,corCirculo);
        DesenhaCirculoFatia(xm,ym,raio,corFundo,angInicial,angFinal,p1,p2,layer);
        if (angFinal-angInicial<360&&angFinal-angInicial>0){
            SDL_RenderDrawLine(layers[layer].render,p1.x,p1.y,xm,ym);
            SDL_RenderDrawLine(layers[layer].render,p2.x,p2.y,xm,ym);
        }
        PintarArea(0,0,corFundo,layer);
    }

    void DesenhaCirculoFatia(int centroX, int centroY, int raio, PIGCor cor, double angInicial, double angFinal, SDL_Point &iniP, SDL_Point &fimP, int layer=0){
        if (angFinal==0) return;
        int ra = raio;
        int x = -raio, y = 0, err = 2-2*raio; /* II. Quadrant */
        vector<SDL_Point> q1,q2,q3,q4;
        vector<double> ang1,ang2,ang3,ang4;
        iniP.x = -1;

        //printf("angInicial %f angFinal %f\n",angInicial,angFinal);

        SDL_SetRenderDrawColor(layers[layer].render,cor.r,cor.g,cor.b,cor.a);

        do {
            SDL_Point p = {centroX-x,centroY-y};
            q1.push_back(p);
            double a = atan(1.*y/-x)*180/M_PI;
            ang1.push_back(a);

            p = {centroX-y,centroY+x};
            q2.push_back(p);
            a = 180+atan(1.*x/y)*180/M_PI;
            ang2.push_back(a);

            p = {centroX+x,centroY+y};
            q3.push_back(p);
            a = atan(1.*-y/x)*180/M_PI+180;
            ang3.push_back(a);

            p = {centroX+y,centroY-x};
            q4.push_back(p);
            if(x==-ra)
                a=270;
            else a = 360+atan(1.*-x/-y)*180/M_PI;
            ang4.push_back(a);

            raio = err;
            if (raio <= y) err += ++y*2+1;           /* e_xy+e_y < 0 */
            if (raio > x || err > y) err += ++x*2+1; /* e_xy+e_x > 0 or no 2nd y-step */
        }while (x < 0);

        //FILE *arq = fopen("angs.txt","w");
        //fprintf(arq,"%f %f\n",angInicial,angFinal);

        for (unsigned int i=0;i<q1.size();i++){
            if ((ang1[i]>=angInicial&&ang1[i]<=angFinal)||(ang1[i]+360>=angInicial&&ang1[i]+360<=angFinal)){
                if (iniP.x==-1&&ang1[i]>=angInicial)
                    iniP = q1[i];
                SDL_RenderDrawPoint(layers[layer].render,q1[i].x,q1[i].y);
                //fprintf(arq,"%f %d %d\n",ang1[i],q1[i].x,q1[i].y);
                if (angFinal<=360)
                    fimP = q1[i];
                else if (ang1[i]<=angInicial)
                    fimP = q1[i];
            }
        }
        for (unsigned int i=0;i<q1.size();i++){
            if ((ang2[i]>=angInicial&&ang2[i]<=angFinal)||(ang2[i]+360>=angInicial&&ang2[i]+360<=angFinal)){
                if (iniP.x==-1&&ang2[i]>=angInicial)
                    iniP = q2[i];
                SDL_RenderDrawPoint(layers[layer].render,q2[i].x,q2[i].y);
                //fprintf(arq,"%f %d %d\n",ang2[i],q2[i].x,q2[i].y);
                if (angFinal<=360)
                    fimP = q2[i];
                else if (ang2[i]<=angInicial)
                    fimP = q2[i];
            }
        }
        for (unsigned int i=0;i<q1.size();i++){
            if ((ang3[i]>=angInicial&&ang3[i]<=angFinal)||(ang3[i]+360>=angInicial&&ang3[i]+360<=angFinal)){
                if (iniP.x==-1&&ang3[i]>=angInicial)
                    iniP = q3[i];
                SDL_RenderDrawPoint(layers[layer].render,q3[i].x,q3[i].y);
                //fprintf(arq,"%f %d %d\n",ang3[i],q3[i].x,q3[i].y);
                if (angFinal<=360)
                    fimP = q3[i];
                else if (ang3[i]<=angInicial)
                    fimP = q3[i];
            }
        }
        for (unsigned int i=0;i<q1.size();i++){
            if ((ang4[i]>=angInicial&&ang4[i]<=angFinal)||(ang4[i]+360>=angInicial&&ang4[i]+360<=angFinal)){
                if (iniP.x==-1&&ang4[i]>=angInicial)
                    iniP = q4[i];
                SDL_RenderDrawPoint(layers[layer].render,q4[i].x,q4[i].y);
                //fprintf(arq,"%f %d %d\n",ang4[i],q4[i].x,q4[i].y);
                if (angFinal<=360)
                    fimP = q4[i];
                else if (ang4[i]<=angInicial)
                    fimP = q4[i];
            }
        }
        //fclose(arq);
        //if (angInicial==90&&angFinal==270)
        //system("pause");
   }

    inline void PintarFundo(PIGCor cor, int layer=0){
        SDL_SetRenderDrawColor(layers[layer].render,cor.r,cor.g,cor.b,cor.a);
        SDL_RenderClear( layers[layer].render );
    }

    void PintarArea(int px, int py, PIGCor cor, int layer=0){
        if (!(px>=0&&py>=0&&px<larg&&py<alt)) return;
        SDL_Surface *surface = layers[layer].surf;
        SDL_LockSurface(surface);
        Uint32 *pBase = (Uint32*) surface->pixels;
        pBase += (px+(alt-py-1)*larg);
        Uint32 corBase = *pBase;

        Uint32 color = SDL_MapRGBA((const SDL_PixelFormat*) &surface->format->format,cor.r,cor.g,cor.b,cor.a);
        if (color==corBase) return;

        SDL_Point elemento;
        vector<SDL_Point> pilha;
        pilha.push_back({px,py});
        Uint32 *p;

        while (pilha.size()>0){
            elemento = pilha.back();
            pilha.pop_back();
            if (elemento.x>=0&&elemento.y>=0&&elemento.x<larg&&elemento.y<alt){
                p = (Uint32*) surface->pixels;
                p += (elemento.x+(alt-elemento.y-1)*larg);

                if ( (*p)==corBase){

                    if (userFunctionPintarArea){
                        PIGCor corAtual;
                        SDL_GetRGBA(corBase,(const SDL_PixelFormat*) &surface->format->format,&(corAtual.r),&(corAtual.g),&(corAtual.b),&(corAtual.a));
                        cor = userFunctionPintarArea(elemento.x,elemento.y,alt,larg,corAtual,cor);
                        color = SDL_MapRGBA((const SDL_PixelFormat*) &surface->format->format,cor.r,cor.g,cor.b,cor.a);
                    }

                    *p = color;     //muda efetivamente a cor
                    pilha.push_back({elemento.x+1,elemento.y+0});
                    pilha.push_back({elemento.x+0,elemento.y+1});
                    pilha.push_back({elemento.x-1,elemento.y+0});
                    pilha.push_back({elemento.x+0,elemento.y-1});
                }
            }
        }

        SDL_UnlockSurface(surface);
    }

    inline void DesenharLinha(int x1, int y1, int x2, int y2, PIGCor cor, int layer=0){
        SDL_SetRenderDrawColor(layers[layer].render,cor.r,cor.g,cor.b,cor.a);
        SDL_RenderDrawLine(layers[layer].render,x1,alt-y1-1,x2,alt-y2-1);
    }

    void DesenhaLinhasDisjuntas(int x[], int y[], int qtd, PIGCor cor, int layer=0){
        SDL_SetRenderDrawColor(layers[layer].render,cor.r,cor.g,cor.b,255);
        for (int k=0;k<qtd;k+=2){
            SDL_RenderDrawLine(layers[layer].render,x[k],alt-y[k],x[k+1],alt-y[k+1]);
            //SDL_RenderDrawLine(renderer,x[k]-camera->GetX(),altura-y[k]+camera->GetY(),x[k+1]-camera->GetX(),altura-y[k+1]+camera->GetY());
        }
    }

    void DesenhaLinhasSequencia(int x[], int y[], int qtd, PIGCor cor, int layer=0){
        SDL_SetRenderDrawColor(layers[layer].render,cor.r,cor.g,cor.b,255);
        for (int k=0;k<qtd-1;k++){
            SDL_RenderDrawLine(layers[layer].render,x[k],alt-y[k],x[k+1],alt-y[k+1]);
            //SDL_RenderDrawLine(renderer,x[k]-camera->GetX(),altura-y[k]+camera->GetY(),x[k+1]-camera->GetX(),altura-y[k+1]+camera->GetY());
        }
    }

    void DesenharRetangulo(int x, int y, int altura, int largura, PIGCor cor, int layer=0){
        SDL_Rect r={x,alt-y-altura-1,largura,altura};

        SDL_SetRenderDrawColor(layers[layer].render,cor.r,cor.g,cor.b,cor.a);
        SDL_RenderFillRect(layers[layer].render,&r);
    }

    void DesenharRetanguloVazado(int x, int y, int altura, int largura, PIGCor cor, int layer=0){
        SDL_Rect r={x,alt-y-altura-1,largura,altura};

        SDL_SetRenderDrawColor(layers[layer].render,cor.r,cor.g,cor.b,cor.a);
        SDL_RenderDrawRect(layers[layer].render,&r);
    }

    inline void CarregaPixelsSurface(int layer=0){
        SDL_RenderReadPixels(layers[layer].render, NULL, SDL_PIXELFORMAT_ARGB8888, layers[layer].surf->pixels, layers[layer].surf->pitch);
    }

    inline void SalvarImagemBMP(char *nomearq, int layer=0){
        SDL_SaveBMP(layers[layer].surf, nomearq);
    }

    inline void SalvarImagemPNG(char *nomearq, int layer=0){
        IMG_SavePNG(layers[layer].surf, nomearq);
    }

    inline void DefineFuncaoPintarArea(PIGFuncaoPintarArea funcao){
        userFunctionPintarArea = funcao;
    }

    inline void MoveCanetaPara(double nx,double ny){
        px = nx;
        py = ny;
    }

    inline void GiraCanetaHorario(double angulo){
        ang -= angulo;
    }

    inline void GiraCanetaAntiHorario(double angulo){
        ang += angulo;
    }

    inline void GiraAnguloFixo(double angulo){
        ang = angulo;
    }

    inline double GetAngAtual(){
        return ang;
    }

    inline void AvancaCaneta(double distancia, int layer=0){
        double nx = px + cos(ang*M_PI/180.0)*distancia;
        double ny = py + sin(ang*M_PI/180.0)*distancia;
        DesenharLinha(px,py,nx,ny,corAtual,layer);
        px = nx;
        py = ny;
    }

    inline void MudaCorAtualCaneta(PIGCor novaCor){
        corAtual = novaCor;
    }

    inline double GetXCaneta(){
        return px;
    }

    inline double GetYCaneta(){
        return py;
    }

    inline  PIGLayer *GetLayer(int indice){
        if (indice<qtdLayers){
            return &layers[indice];
        }else throw CPIGErroIndice(indice,"layer do renderizador offscreen");
    }

    ~CPIGOffscreenRenderer(){
        for (int i=0;i<maxLayers;i++){
            SDL_DestroyRenderer(layers[i].render);
            SDL_FreeSurface(layers[i].surf);
        }
    }

};

typedef CPIGOffscreenRenderer* PIGOffscreenRenderer;
#endif // _CPIGOFFSCREENRENDERER_
