#ifndef _CGERENCIADORSPRITES_
#define _CGERENCIADORSPRITES_

#include "CPigSprite.h"

class CGerenciadorSprites{

private:

static std::unordered_map<std::string,PIGSprite> spritesSimples;
static int totalSprites;
static PoolNumeros numSprites;
static PIGSprite sprites[MAX_OBJETOS];

public:


static void Inicia(){

}

static void Encerra(){
    Limpa();
}


static void Limpa(){
    for(std::unordered_map<std::string,PIGSprite>::iterator it = spritesSimples.begin(); it != spritesSimples.end(); ++it) {
        delete it->second;
    }
}

static void Desenha(std::string nomeArq,int x,int y,int retiraFundo=1, int idJanela=0){
    PIGSprite sprite = NULL;
    std::unordered_map<std::string, PIGSprite>::iterator it = spritesSimples.find(nomeArq);
    if (it == spritesSimples.end()){//não achou
        sprite = new CPigSprite(nomeArq,retiraFundo,NULL,idJanela);
        spritesSimples[nomeArq]=sprite;
    }else{
        sprite = it->second;
    }
    if (sprite){
        sprite->Move(x,y);
        sprite->Desenha();
    }
}

inline static PIGSprite GetSprite(int idSprite){
        if (idSprite<0||idSprite>=MAX_OBJETOS||sprites[idSprite]==NULL) throw CPigErroIndice(idSprite,"sprites");
        return sprites[idSprite];
    }

    static int CriaSprite(std::string nomeArquivoBMP,PIG_Cor *corFundo=NULL,int retiraFundo=1,int idJanela=0){
        int resp = numSprites->RetiraLivre();
        sprites[resp] = new CPigSprite(nomeArquivoBMP,retiraFundo,corFundo,idJanela);
        totalSprites++;
        return resp;
    }

    static int CriaSpriteOffScreen(OffscreenRenderer offRenderer,PIG_Cor *corFundo=NULL,int retiraFundo=1,int idJanela=0){
        int resp = numSprites->RetiraLivre();
        sprites[resp] = new CPigSprite(offRenderer,retiraFundo,corFundo,idJanela);
        totalSprites++;
        return resp;
    }

    static void DestroiSprite(int idSprite){
        if (idSprite<0||idSprite>=MAX_OBJETOS||sprites[idSprite]==NULL) throw CPigErroIndice(idSprite,"sprites");
        numSprites->DevolveUsado(idSprite);
        delete sprites[idSprite];
        totalSprites--;
        sprites[idSprite] = NULL;
    }

    inline static void GetPosicaoXY(int idSprite, int *x, int *y){
        GetSprite(idSprite)->GetXY(*x,*y);
    }

    inline static void Move(int idSprite, int x, int y){
        GetSprite(idSprite)->Move(x,y);
    }

    inline static void Desloca(int idSprite, int dx, int dy){
        GetSprite(idSprite)->Desloca(dx,dy);
    }

    inline static void SetAngulo(int idSprite, float angulo){
        GetSprite(idSprite)->SetAngulo(angulo);
    }

    inline static float GetAngulo(int idSprite){
        return GetSprite(idSprite)->GetAngulo();
    }

    inline static void SetPivo(int idSprite, int x, int y){
        GetSprite(idSprite)->SetPivo(x,y);
    }

    inline static void SetPivo(int idSprite, float relX, float relY){
        GetSprite(idSprite)->SetPivo(relX,relY);
    }

    inline static void GetPivo(int idSprite, int &x,int &y){
        SDL_Point p = GetSprite(idSprite)->GetPivo();
        x = p.x;
        y = p.y;
    }

    inline static void SetFlip(int idSprite, PIG_Flip valor){
        GetSprite(idSprite)->SetFlip(valor);
    }

    inline static PIG_Flip GetFlip(int idSprite){
        return GetSprite(idSprite)->GetFlip();
    }

    inline static void SetDimensoes(int idSprite, int altura, int largura){
        GetSprite(idSprite)->SetDimensoes(altura,largura);
    }

    inline static void GetDimensoes(int idSprite, int *altura, int *largura){
        GetSprite(idSprite)->GetDimensoes(*altura,*largura);
    }

    inline static void GetDimensoesOriginais(int idSprite, int *altura, int *largura){
        GetSprite(idSprite)->GetDimensoesOriginais(*altura,*largura);
    }

    inline static void CriaFrame(int idSprite, int idFrame, int xBitmap, int yBitmap,int altura,int largura){
        SDL_Rect r;
        r.x = xBitmap;
        r.y = yBitmap;
        r.h = altura;
        r.w = largura;
        GetSprite(idSprite)->DefineFrame(idFrame,r);
    }

    inline static int MudaFrame(int idSprite, int idFrame){
        return GetSprite(idSprite)->MudaFrameAtual(idFrame);
    }

    inline static void SetColoracao(int idSprite, PIG_Cor cor){
        GetSprite(idSprite)->SetColoracao(cor);
    }

    inline static void SetOpacidade(int idSprite, int valor){
        GetSprite(idSprite)->SetOpacidade(valor);
    }

    inline static int GetOpacidade(int idSprite){
        return GetSprite(idSprite)->GetOpacidade();
    }

    inline static void Desenha(int idSprite,OffscreenRenderer offRender=NULL){
        GetSprite(idSprite)->Desenha(offRender);
    }

    inline static PIG_Cor **GetPixels(int idSprite){
        return GetSprite(idSprite)->GetPixels();
    }

    inline static void AtualizaPixels(int idSprite,int retiraFundo=1){
        GetSprite(idSprite)->AtualizaPixels(retiraFundo);
    }

};
std::unordered_map<std::string,PIGSprite> CGerenciadorSprites::spritesSimples;
int CGerenciadorSprites::totalSprites;
PoolNumeros CGerenciadorSprites::numSprites;
PIGSprite CGerenciadorSprites::sprites[MAX_OBJETOS];

#endif // _CGERENCIADORSPRITES_
