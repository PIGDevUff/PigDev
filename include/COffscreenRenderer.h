#include "CPilhaCoordenada.h"
#define PIG_MAX_CAMADAS_OFFSCREEN 50

typedef struct{
    SDL_Surface *surf;
    SDL_Renderer *render;
}Layer;

class COffscreenRenderer{

private:

Layer layers[PIG_MAX_CAMADAS_OFFSCREEN];
int qtdLayers,maxLayers;

int alt,larg,depth;
double px,py;
double ang;
PIG_Cor corAtual;
PIG_Cor (*userFunctionPintarArea)(int, int, int, int, PIG_Cor,PIG_Cor);

public:

    SDL_Renderer *GetRenderer(int layer=0){
        return layers[layer].render;
    }

    SDL_Surface *GetSurface(int layer=0){
        //SDL_RenderReadPixels(render, NULL, SDL_PIXELFORMAT_ARGB8888, surface->pixels, surface->pitch);
        return layers[layer].surf;
    }

    int GetAltura(){
        return alt;
    }

    int GetLargura(){
        return larg;
    }

    int GetDepth(){
        return depth;
    }

    void SetCorTransparente(int layer, bool transparencia, PIG_Cor cor){
        SDL_SetColorKey(layers[layer].surf,transparencia,SDL_MapRGBA(layers[layer].surf->format,cor.r,cor.g,cor.b,cor.a));
    }

    void MergeSurface(int layerSuperior, int layerInferior, SDL_BlendMode modo){
        SDL_SetSurfaceBlendMode(layers[layerInferior].surf,modo);
        //SDL_SetSurfaceBlendMode(layers[layerSuperior].surf,modo);
        SDL_BlitSurface(layers[layerSuperior].surf,NULL,layers[layerInferior].surf,NULL);
    }

    Layer CriaLayer(){
        Layer l;
        l.surf = SDL_CreateRGBSurfaceWithFormat(0, larg, alt, depth, SDL_PIXELFORMAT_RGBA32);
        //SDL_SetSurfaceBlendMode(l.surf,SDL_BLENDMODE_BLEND);
        l.render = SDL_CreateSoftwareRenderer(l.surf);
        SDL_RenderClear(l.render);
        qtdLayers++;
        return l;
    }

    void LimpaLayer(int layer, PIG_Cor cor){
        SDL_SetRenderDrawColor(layers[layer].render,cor.r,cor.g,cor.b,cor.a);
        //SDL_RenderDrawRect(layers[layer].render,NULL);
        SDL_RenderClear(layers[layer].render);
    }

    COffscreenRenderer(int altura,int largura,int qtdMaxCamadas=1){
        alt = altura;
        larg=largura;
        depth = 32; //32 bits por pixel
        maxLayers = qtdMaxCamadas;
        qtdLayers=0;
        for (int i=0;i<maxLayers;i++)
            layers[i] = CriaLayer();

        userFunctionPintarArea = NULL;

        px = py = 1;
        ang = 0;
        corAtual = BRANCO;
    }

    void DesenhaCirculo(int raio, PIG_Cor cor, double angFinal,bool horario,int layer=0){
        if (angFinal==0) return;
        int fator=horario?1:-1;
        int x = larg/2;
        int y = alt/2;
        SDL_Point pontos[361];
        pontos[0].x = x+ceil(raio*cos(0*M_PI/180));
        pontos[0].y = y+fator*ceil(raio*sin(0*M_PI/180));
        //printf("y %d %d\n",y,pontos[0].y);
        SDL_SetRenderDrawColor(layers[layer].render,cor.r,cor.g,cor.b,cor.a);
        for (int i=1;i<=angFinal;i++){
            pontos[i].x = x+ceil(raio*cos(i*M_PI/180));
            pontos[i].y = y+fator*ceil(raio*sin(i*M_PI/180));
        }
        SDL_RenderDrawLines(layers[layer].render,(const SDL_Point*)&pontos,angFinal+1);
        if (angFinal<360){
            SDL_RenderDrawLine(layers[layer].render,x,y,pontos[0].x,pontos[0].y);
            SDL_RenderDrawLine(layers[layer].render,x,y,pontos[(int)angFinal].x,pontos[(int)angFinal].y);
        }
        x+=pontos[1].x;
        y+=pontos[1].y;

        PintarArea(pontos[0].x-1,pontos[0].y-2*fator,cor,NULL,layer);
        //printf("%f %d,%d\n",angFinal,pontos[0].x-1,pontos[0].y+1);
    }

    void DesenhaCirculo(int raioInterno, int raioExterno, PIG_Cor cor, double angFinal,bool horario,int layer=0){
        if (angFinal==0) return;
        int fator=horario?1:-1;
        int x = larg/2;
        int y = alt/2;
        SDL_Point pontosExt[361],pontosInt[361];
        pontosExt[0].x = x+ceil(raioExterno*cos(0*M_PI/180));
        pontosExt[0].y = y+fator*ceil(raioExterno*sin(0*M_PI/180));
        pontosInt[0].x = x+ceil(raioInterno*cos(0*M_PI/180));
        pontosInt[0].y = y+fator*ceil(raioInterno*sin(0*M_PI/180));
        //printf("y %d %d\n",y,pontos[0].y);
        for (int i=1;i<=angFinal;i++){
            pontosExt[i].x = x+ceil(raioExterno*cos(i*M_PI/180));
            pontosExt[i].y = y+fator*ceil(raioExterno*sin(i*M_PI/180));
            pontosInt[i].x = x+ceil(raioInterno*cos(i*M_PI/180));
            pontosInt[i].y = y+fator*ceil(raioInterno*sin(i*M_PI/180));
        }

        SDL_SetRenderDrawColor(layers[layer].render,cor.r,cor.g,cor.b,cor.a);
        SDL_RenderDrawLines(layers[layer].render,(const SDL_Point*)&pontosExt,angFinal+1);
        SDL_RenderDrawLines(layers[layer].render,(const SDL_Point*)&pontosInt,angFinal+1);
        if (angFinal<360){
            SDL_RenderDrawLine(layers[layer].render,pontosInt[0].x,pontosInt[0].y,pontosExt[0].x,pontosExt[0].y);
            SDL_RenderDrawLine(layers[layer].render,pontosInt[(int)angFinal].x,pontosInt[(int)angFinal].y,pontosExt[(int)angFinal].x,pontosExt[(int)angFinal].y);
        }
        SalvarImagemPNG("antes.png");
        PintarArea((pontosExt[0].x+pontosInt[0].x)/2-1,(pontosExt[0].y+pontosInt[0].y)/2-2*fator,cor,NULL,layer);
    }

    void PintarFundo(SDL_Color cor,int layer=0){
        SDL_SetRenderDrawColor(layers[layer].render,cor.r,cor.g,cor.b,cor.a);
        SDL_RenderClear( layers[layer].render );
    }

    void PintarArea(int px,int py,PIG_Cor cor,void *ponteiro,int layer=0){
        if (!(px>=0&&py>=0&&px<larg&&py<alt)) return;
        SDL_Surface *surface = layers[layer].surf;
        SDL_LockSurface(surface);
        Uint32 *pBase = (Uint32*) surface->pixels;
        pBase += (px+(alt-py-1)*larg);
        Uint32 corBase = *pBase;

        Uint32 color = SDL_MapRGBA((const SDL_PixelFormat*) &surface->format->format,cor.r,cor.g,cor.b,cor.a);
        if (color==corBase) return;

        CPilhaCoordenada *pilha = new CPilhaCoordenada();
        pilha->Empilha(px,py);
        int x,y;
        Uint32 *p;
        while (pilha->Desempilha(x,y)){
            if (x>=0&&y>=0&&x<larg&&y<alt){
                p = (Uint32*) surface->pixels;
                p += (x+(alt-y-1)*larg);

                if ( (*p)==corBase){

                    if (userFunctionPintarArea){
                        PIG_Cor corAtual;
                        SDL_GetRGBA(corBase,(const SDL_PixelFormat*) &surface->format->format,&(corAtual.r),&(corAtual.g),&(corAtual.b),&(corAtual.a));
                        cor = userFunctionPintarArea(x,y,alt,larg,corAtual,cor);
                        color = SDL_MapRGBA((const SDL_PixelFormat*) &surface->format->format,cor.r,cor.g,cor.b,cor.a);
                    }

                    *p = color;     //muda efetivamente a cor
                    pilha->Empilha(x+1,y+0);
                    pilha->Empilha(x+0,y+1);
                    pilha->Empilha(x-1,y+0);
                    pilha->Empilha(x+0,y-1);
                }
            }
        }

        delete pilha;
        SDL_UnlockSurface(surface);
    }

    void DesenharLinha(int x1,int y1,int x2,int y2,PIG_Cor cor,int layer=0){
        SDL_SetRenderDrawColor(layers[layer].render,cor.r,cor.g,cor.b,cor.a);
        SDL_RenderDrawLine(layers[layer].render,x1,alt-y1-1,x2,alt-y2-1);
    }

    void DesenharRetangulo(int x,int y,int altura,int largura,PIG_Cor cor,int layer=0){
        SDL_Rect r={x,alt-y-altura-1,largura,altura};

        SDL_SetRenderDrawColor(layers[layer].render,cor.r,cor.g,cor.b,cor.a);
        SDL_RenderFillRect(layers[layer].render,&r);
    }

    void DesenharRetanguloVazado(int x,int y,int altura,int largura,PIG_Cor cor,int layer=0){
        SDL_Rect r={x,alt-y-altura-1,largura,altura};

        SDL_SetRenderDrawColor(layers[layer].render,cor.r,cor.g,cor.b,cor.a);
        SDL_RenderDrawRect(layers[layer].render,&r);
    }

    void CarregaPixelsSurface(int layer=0){
        SDL_RenderReadPixels(layers[layer].render, NULL, SDL_PIXELFORMAT_ARGB8888, layers[layer].surf->pixels, layers[layer].surf->pitch);
    }

    void SalvarImagemBMP(char *nomearq,int layer=0){
        SDL_SaveBMP(layers[layer].surf, nomearq);
    }

    void SalvarImagemPNG(char *nomearq,int layer=0){
        IMG_SavePNG(layers[layer].surf, nomearq);
    }

    void DefineFuncaoPintarArea(PIG_Cor (*funcao)(int, int, int, int, PIG_Cor,PIG_Cor)){
        userFunctionPintarArea = funcao;
    }

    void MoveCanetaPara(double nx,double ny){
        px = nx;
        py = ny;
    }

    void GiraCanetaHorario(double angulo){
        ang -= angulo;
    }

    void GiraCanetaAntiHorario(double angulo){
        ang += angulo;
    }

    void GiraAnguloFixo(double angulo){
        ang = angulo;
    }

    double GetAngAtual(){
        return ang;
    }

    void AvancaCaneta(double distancia,int layer=0){
        double nx = px + cos(ang*M_PI/180.0)*distancia;
        double ny = py + sin(ang*M_PI/180.0)*distancia;
        DesenharLinha(px,py,nx,ny,corAtual,layer);
        //printf("%d %d %d %d\n",px,py,nx,ny);
        px = nx;
        py = ny;
    }

    void MudaCorAtualCaneta(PIG_Cor novaCor){
        corAtual = novaCor;
    }

    double GetXCaneta(){
        return px;
    }

    double GetYCaneta(){
        return py;
    }

    ~COffscreenRenderer(){
        for (int i=0;i<maxLayers;i++){
            SDL_DestroyRenderer(layers[i].render);
            SDL_FreeSurface(layers[i].surf);
        }
    }

};

typedef COffscreenRenderer* OffscreenRenderer;
