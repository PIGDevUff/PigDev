#include "CPilhaCoordenada.h"

class COffscreenRenderer{

private:

SDL_Renderer *render;
SDL_Surface *surface;
int alt,larg,depth;
double px,py;
double ang;
PIG_Cor corAtual;
PIG_Cor (*userFunctionPintarArea)(int, int, int, int, PIG_Cor,PIG_Cor);

public:

    SDL_Renderer *GetRenderer(){
        return render;
    }

    SDL_Surface *GetSurface(){
        //SDL_RenderReadPixels(render, NULL, SDL_PIXELFORMAT_ARGB8888, surface->pixels, surface->pitch);
        return surface;
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

    COffscreenRenderer(int altura,int largura){
        alt = altura;
        larg=largura;
        depth = 32; //32 bits por pixel
        surface = SDL_CreateRGBSurface(0, largura, altura, depth, 0,0,0,0);//0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
        render = SDL_CreateSoftwareRenderer(surface);
        SDL_RenderClear( render );

        userFunctionPintarArea = NULL;

        px = py = 1;
        ang = 0;
        corAtual = BRANCO;
    }

    void PintarFundo(SDL_Color cor){
        SDL_SetRenderDrawColor(render,cor.r,cor.g,cor.b,cor.a);
        SDL_RenderClear( render );
    }

    void PintarArea(int px,int py,PIG_Cor cor,void *ponteiro){
        if (!(px>=0&&py>=0&&px<larg&&py<alt)) return;

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

    void DesenharLinha(int x1,int y1,int x2,int y2,PIG_Cor cor){
        SDL_SetRenderDrawColor(render,cor.r,cor.g,cor.b,cor.a);
        SDL_RenderDrawLine(render,x1,alt-y1-1,x2,alt-y2-1);
    }

    void DesenharRetangulo(int x,int y,int altura,int largura,PIG_Cor cor){
        SDL_Rect r={x,alt-y-altura-1,largura,altura};

        SDL_SetRenderDrawColor(render,cor.r,cor.g,cor.b,cor.a);
        SDL_RenderFillRect(render,&r);
    }

    void DesenharRetanguloVazado(int x,int y,int altura,int largura,PIG_Cor cor){
        SDL_Rect r={x,alt-y-altura-1,largura,altura};

        SDL_SetRenderDrawColor(render,cor.r,cor.g,cor.b,cor.a);
        SDL_RenderDrawRect(render,&r);
    }

    void CarregaPixelsSurface(){
        SDL_RenderReadPixels(render, NULL, SDL_PIXELFORMAT_ARGB8888, surface->pixels, surface->pitch);
    }

    void SalvarImagemBMP(char *nomearq){
        SDL_SaveBMP(surface, nomearq);
    }

    void SalvarImagemPNG(char *nomearq){
        IMG_SavePNG(surface, nomearq);
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

    void AvancaCaneta(double distancia){
        double nx = px + cos(ang*M_PI/180.0)*distancia;
        double ny = py + sin(ang*M_PI/180.0)*distancia;
        DesenharLinha(px,py,nx,ny,corAtual);
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
        SDL_DestroyRenderer(render);
        SDL_FreeSurface(surface);
    }

};

typedef COffscreenRenderer* OffscreenRenderer;
