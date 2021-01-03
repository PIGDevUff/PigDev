#ifndef _CPIGGERENCIADORSPRITES_
#define _CPIGGERENCIADORSPRITES_

#include "CPIGSprite.h"
#include "CPIGObjeto.h"
#include "CPIGAnimacao.h"

class CPIGGerenciadorSprites{

private:
    static std::unordered_map<std::string,PIGSprite> spritesSimples;

    static int totalSprites;
    static PIGPoolNumeros numSprites;
    static PIGSprite sprites[MAX_SPRITES];

public:

    static PIGSprite GetSprite(int idSprite){
        if (idSprite<0||idSprite>=MAX_SPRITES||sprites[idSprite]==NULL) throw CPIGErroIndice(idSprite,"sprites");
        return sprites[idSprite];
    }

    static PIGObjeto GetObjeto(int idObjeto){
        PIGObjeto obj = (PIGObjeto)GetSprite(idObjeto);
        if (obj==NULL) throw CPIGErroIndice(idObjeto,"objetos");
        else return obj;
    }

    static PIGAnimacao GetAnimacao(int idAnimacao){
        PIGAnimacao anima = (PIGAnimacao)GetSprite(idAnimacao);
        if (anima==NULL) throw CPIGErroIndice(idAnimacao,"animacoes");
        else return anima;
    }

    static void Inicia(SDL_Renderer *renderer=NULL){
        totalSprites = 0;
        for (int i=0;i<MAX_SPRITES;i++)
            sprites[i] = NULL;
        numSprites = new CPIGPoolNumeros(MAX_SPRITES);
    }

    static void Encerra(){
        for (int i=0;i<MAX_SPRITES;i++){
            if (sprites[i]) delete sprites[i];
        }
        delete numSprites;

        for(std::unordered_map<std::string,PIGSprite>::iterator it = spritesSimples.begin(); it != spritesSimples.end(); ++it) {
            delete it->second;
        }
    }

    static int CriaSprite(std::string nomeArquivoBMP,int retiraFundo=1,PIG_Cor *corFundo=NULL,int idJanela=0){
        int resp = numSprites->RetiraLivre();
        sprites[resp] = new CPIGSprite(nomeArquivoBMP,retiraFundo,corFundo,idJanela);
        totalSprites++;
        return resp;
    }

    static int CriaSprite(int idSpriteBase,int retiraFundo=1,PIG_Cor *corFundo=NULL,int idJanela=0){
        int resp = numSprites->RetiraLivre();
        sprites[resp] = new CPIGSprite(GetSprite(idSpriteBase),retiraFundo,corFundo,idJanela);
        totalSprites++;
        return resp;
    }

    static int CriaObjeto(std::string nomeArquivoBMP,PIG_Cor *corFundo=NULL,int retiraFundo=1,int idJanela=0){
        int resp = numSprites->RetiraLivre();
        sprites[resp] = new CPIGObjeto(nomeArquivoBMP,corFundo,retiraFundo,idJanela);
        totalSprites++;
        return resp;
    }

    static int CriaObjeto(int idObjetoBase,int retiraFundo=1,PIG_Cor *corFundo=NULL,int idJanela=0){
        int resp = numSprites->RetiraLivre();
        sprites[resp] = new CPIGObjeto(GetObjeto(idObjetoBase),corFundo,retiraFundo,idJanela);
        totalSprites++;
        return resp;
    }

    static int CriaObjetoOffScreen(PIGOffscreenRenderer offRenderer,PIG_Cor *corFundo=NULL,int retiraFundo=1,int idJanela=0){
        int resp = numSprites->RetiraLivre();
        sprites[resp] = new CPIGObjeto(offRenderer,corFundo,retiraFundo,idJanela);
        totalSprites++;
        return resp;
    }

    static int CriaAnimacao(std::string nomeArquivoBMP,PIG_Cor *corFundo=NULL,int retiraFundo=1,int idJanela=0){
        int resp = numSprites->RetiraLivre();
        sprites[resp] = new CPIGAnimacao(nomeArquivoBMP,0,corFundo,retiraFundo,idJanela);
        totalSprites++;
        return resp;
    }

    static int CriaAnimacao(int idAnimacaoBase,PIG_Cor *corFundo=NULL,int retiraFundo=1,int idJanela=0){
        int resp = numSprites->RetiraLivre();
        sprites[resp] = new CPIGAnimacao(GetAnimacao(idAnimacaoBase),0,corFundo,retiraFundo,idJanela);
        totalSprites++;
        return resp;
    }

    static void DestroiSprite(int idSprite){
        PIGSprite sprite = GetSprite(idSprite);
        numSprites->DevolveUsado(idSprite);
        delete sprite;
        totalSprites--;
        sprites[idSprite] = NULL;
    }

    static void DestroiObjeto(int idObjeto){
        PIGObjeto objeto = GetObjeto(idObjeto);
        numSprites->DevolveUsado(idObjeto);
        delete objeto;
        totalSprites--;
        sprites[idObjeto] = NULL;
    }

    static void DestroiAnimacao(int idAnimacao){
        PIGAnimacao anima = GetAnimacao(idAnimacao);
        numSprites->DevolveUsado(idAnimacao);
        delete anima;
        totalSprites--;
        sprites[idAnimacao] = NULL;
    }

    static void DesenhaSprite(std::string nomeArq,int x,int y,int retiraFundo=1, int idJanela=0){
        PIGSprite sprite = NULL;
        std::unordered_map<std::string, PIGSprite>::iterator it = spritesSimples.find(nomeArq);
        if (it == spritesSimples.end()){//não achou
            sprite = new CPIGSprite(nomeArq,retiraFundo,NULL,idJanela);
            spritesSimples[nomeArq]=sprite;
        }else{
            sprite = it->second;
        }
        if (sprite){
            sprite->Move(x,y);
            sprite->Desenha();
        }
    }

    /*inline static void Move(int idSprite,int px,int py){
        GetSprite(idSprite)->Move(px,py);
    }

    inline static void Desloca(int idSprite,int dx,int dy){
        GetSprite(idSprite)->Desloca(dx,dy);
    }

    inline static void GetPosicaoXY(int idSprite, int *x,int *y){
        GetSprite(idSprite)->GetXY(*x,*y);
    }

    inline static int DesenhaSprite(int idSprite){
        return GetSprite(idSprite)->Desenha();
    }

    inline static void CriaFrame(int idSprite,int codFrame,int x,int y,int altura,int largura){
        GetSprite(idSprite)->DefineFrame(codFrame,{x,y,altura,largura});
    }

    inline static void CriaModo(int idSprite,int idModo, int loop){
        GetAnimacao(idSprite)->CriaModo(idModo,loop);
    }

    inline static void InsereFrame(int idSprite, int idModo,int idFrame, float delayFrame,int idAudio){
        GetAnimacao(idSprite)->InsereFrame(idModo,idFrame,delayFrame,idAudio);
    }

    inline static int GetModo(int idSprite){
        return GetAnimacao(idSprite)->GetModoAtual();
    }

    inline static void MudaModo(int idSprite,int idModo,int indiceFrame,int forcado){
        GetAnimacao(idSprite)->MudaModo(idModo,indiceFrame,forcado);
    }

    inline static void SetOpacidade(int idSprite,int valor){
        GetSprite(idSprite)->SetOpacidade(valor);
    }

    inline static int GetOpacidade(int idSprite){
        return GetSprite(idSprite)->GetOpacidade();
    }

    inline static void SetColoracao(int idSprite,PIG_Cor cor){
        GetSprite(idSprite)->SetColoracao(cor);
    }

    inline static void SetPivo(int idSprite,int x,int y){
        GetSprite(idSprite)->SetPivo(x,y);
    }

    inline static void GetPivo(int idSprite,int &x,int &y){
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

    inline static void SetAngulo(int idSprite,float valor){
        GetSprite(idSprite)->SetAngulo(valor);
    }

    inline static float GetAngulo(int idSprite){
        return GetSprite(idSprite)->GetAngulo();
    }

    inline static int ColisaoAnimacoes(int idSprite1,int idSprite2){
        return GetAnimacao(idSprite1)->Colisao(GetObjeto(idSprite2));
    }

    inline static int ColisaoObjetos(int idSprite,Objeto obj){
        return GetObjeto(idSprite)->Colisao(obj);
    }

    inline static void SetDimensoes(int idSprite,int altura,int largura){
        GetSprite(idSprite)->SetDimensoes(altura,largura);
    }

    inline static void GetDimensoes(int idSprite,int *altura,int *largura){
        GetSprite(idSprite)->GetDimensoes(*altura,*largura);
    }

    inline static void SetValorIntSprite(int idSprite, int chave, int valor){
        GetObjeto(idSprite)->SetValoresInt(chave,valor);
    }

    inline static void SetValorIntSprite(int idSprite, std::string chave, int valor){
        GetObjeto(idSprite)->SetValoresInt(chave,valor);
    }

    inline static void SetValorFloatSprite(int idSprite, int chave, float valor){
        GetObjeto(idSprite)->SetValoresFloat(chave,valor);
    }

    inline static void SetValorFloatSprite(int idSprite, std::string chave, float valor){
        GetObjeto(idSprite)->SetValoresFloat(chave,valor);
    }

    inline static void SetValorStringSprite(int idSprite, int chave, std::string valor){
        GetObjeto(idSprite)->SetValoresString(chave,valor);
    }

    inline static void SetValorStringSprite(int idSprite, std::string chave, std::string valor){
        GetObjeto(idSprite)->SetValoresString(chave,valor);
    }

    inline static bool GetValorIntSprite(int idSprite, int indice, int *valor){
        return GetObjeto(idSprite)->GetValoresInt(indice,*valor);
    }

    inline static bool GetValorFloatSprite(int idSprite, int indice, float *valor){
        return GetObjeto(idSprite)->GetValoresFloat(indice,*valor);
    }

    inline static bool GetValorStringSprite(int idSprite, int indice, std::string &valor){
        return GetObjeto(idSprite)->GetValoresString(indice,valor);
    }

    inline static bool GetValorIntSprite(int idSprite, std::string indice, int *valor){
        return GetObjeto(idSprite)->GetValoresInt(indice,*valor);
    }

    inline static bool GetValorFloatSprite(int idSprite, std::string indice, float *valor){
        return GetObjeto(idSprite)->GetValoresFloat(indice,*valor);
    }

    inline static bool GetValorStringSprite(int idSprite, std::string indice, std::string &valor){
        return GetObjeto(idSprite)->GetValoresString(indice,valor);
    }

    inline static void PausaAnimacao(int idSprite){
        GetAnimacao(idSprite)->Pausa();
    }

    inline static void DespausaAnimacao(int idSprite){
        GetAnimacao(idSprite)->Despausa();
    }

    inline static void SetTempoFrameSprite(int idSprite, int idModo, int indiceFrame, double tempo){
        GetAnimacao(idSprite)->SetTempoFrame(idModo,indiceFrame,tempo);
    }

    inline static void SetAudioFrameSprite(int idSprite, int idModo, int indiceFrame, int idAudio){
        GetAnimacao(idSprite)->SetAudioFrame(idModo,indiceFrame,idAudio);
    }

    inline static void SetLoopModoSprite(int idSprite, int idModo, bool loop){
        GetAnimacao(idSprite)->SetLoopModo(idModo,loop);
    }

    inline static double GetTempoFrameSprite(int idSprite, int idModo, int indiceFrame){
        return GetAnimacao(idSprite)->GetTempoFrame(idModo,indiceFrame);
    }

    inline static bool GetLoopModoSprite(int idSprite, int idModo){
        return GetAnimacao(idSprite)->GetLoopModo(idModo);
    }

    inline static int GetAudioFrameSprite(int idSprite, int idModo, int indiceFrame){
        return GetAnimacao(idSprite)->GetAudioFrame(idModo,indiceFrame);
    }
    */
};
std::unordered_map<std::string,PIGSprite> CPIGGerenciadorSprites::spritesSimples;
PIGPoolNumeros CPIGGerenciadorSprites::numSprites;
int CPIGGerenciadorSprites::totalSprites;
PIGSprite CPIGGerenciadorSprites::sprites[MAX_SPRITES];

#endif //_CPIGGERENCIADORSPRITES_
