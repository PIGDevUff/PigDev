#ifndef _CPIGGERENCIADORSPRITES_
#define _CPIGGERENCIADORSPRITES_

#include "CPIGSprite.h"
#include "CPIGObjeto.h"
#include "CPIGAnimacao.h"

class CPIGGerenciadorSprites{

private:
    static unordered_map<string,int> spritesSimples;
    static CPIGRepositorio<PIGSprite> *sprites;
    static CPIGRepositorio<PIGObjeto> *objetos;
    static CPIGRepositorio<PIGAnimacao> *animacoes;

public:

    inline static PIGSprite GetSprite(int idSprite){
        return sprites->GetElemento(idSprite);
    }

    inline static PIGObjeto GetObjeto(int idObjeto){
        return objetos->GetElemento(idObjeto);
    }

    inline static PIGAnimacao GetAnimacao(int idAnimacao){
        return animacoes->GetElemento(idAnimacao);
    }

    inline static void Inicia(){
        sprites = new CPIGRepositorio<PIGSprite>(PIG_MAX_SPRITES,"sprites");
        objetos = new CPIGRepositorio<PIGObjeto>(PIG_MAX_OBJETOS,"objetos");
        animacoes = new CPIGRepositorio<PIGAnimacao>(PIG_MAX_ANIMACOES,"animacoes");
    }

    inline static void Encerra(){
        delete sprites;
        delete objetos;
        delete animacoes;
    }

    inline static int CriaSprite(string nomeArquivoBMP, int retiraFundo=1, PIGCor *corFundo=NULL, int idJanela=0){
        int id = sprites->ProxID();
        return sprites->Insere(new CPIGSprite(id,nomeArquivoBMP,retiraFundo,corFundo,idJanela));
    }

    inline static int CriaSprite(int idSpriteBase, int retiraFundo=1, PIGCor *corFundo=NULL, int idJanela=0){
        int id = sprites->ProxID();
        return sprites->Insere(new CPIGSprite(id,GetSprite(idSpriteBase),retiraFundo,corFundo,idJanela));
    }

    inline static int CriaSpriteOffScreen(PIGOffscreenRenderer offRenderer, int retiraFundo=1, PIGCor *corFundo=NULL, int idJanela=0){
        int id = sprites->ProxID();
        return sprites->Insere(new CPIGSprite(id,offRenderer,retiraFundo,corFundo,idJanela));
    }

    inline static int InsereSprite(PIGSprite sprite){
        return sprites->Insere(sprite);
    }

    inline static int CriaObjeto(string nomeArquivoBMP, int retiraFundo=1, PIGCor *corFundo=NULL,int idJanela=0){
        int id = objetos->ProxID();
        return objetos->Insere(new CPIGObjeto(id,nomeArquivoBMP,retiraFundo,corFundo,idJanela));
    }

    inline static int CriaObjeto(int idObjetoBase, int retiraFundo=1, PIGCor *corFundo=NULL, int idJanela=0){
        int id = objetos->ProxID();
        return objetos->Insere(new CPIGObjeto(id,GetObjeto(idObjetoBase),retiraFundo,corFundo,idJanela));
    }

    inline static int CriaObjetoOffScreen(PIGOffscreenRenderer offRenderer, int retiraFundo=1, PIGCor *corFundo=NULL, int idJanela=0){
        int id = objetos->ProxID();
        return objetos->Insere(new CPIGObjeto(id,offRenderer,retiraFundo,corFundo,idJanela));
    }

    inline static int InsereObjeto(PIGObjeto objeto){
        return objetos->Insere(objeto);
    }

    inline static int CriaAnimacao(string nomeArquivoBMP, int retiraFundo=1, PIGCor *corFundo=NULL, int idJanela=0){
        int id = animacoes->ProxID();
        return animacoes->Insere(new CPIGAnimacao(id,nomeArquivoBMP,retiraFundo,corFundo,idJanela));
    }

    inline static int CriaAnimacao(PIGAnimacao animaBase, int retiraFundo=1, PIGCor *corFundo=NULL, int idJanela=0){
        int id = animacoes->ProxID();
        return animacoes->Insere(new CPIGAnimacao(id,animaBase,retiraFundo,corFundo,idJanela));
    }

    inline static int CriaAnimacao(PIGObjeto objetoBase, int retiraFundo=1, PIGCor *corFundo=NULL, int idJanela=0){
        int id = animacoes->ProxID();
        return animacoes->Insere(new CPIGAnimacao(id,objetoBase,retiraFundo,corFundo,idJanela));
    }

    inline static int InsereAnimacao(PIGAnimacao animacao){
        return animacoes->Insere(animacao);
    }

    inline static int GetProxIndiceSprite(){
        return sprites->ProxID();
    }

    inline static int GetProxIndiceObjeto(){
        return objetos->ProxID();
    }

    inline static int GetProxIndiceAnimacao(){
        return animacoes->ProxID();
    }

    inline static void DestroiSprite(int idSprite){
        sprites->Remove(idSprite);
    }

    inline static void DestroiObjeto(int idObjeto){
        objetos->Remove(idObjeto);
    }

    inline static void DestroiAnimacao(int idAnimacao){
        animacoes->Remove(idAnimacao);
    }

    inline static void DesenhaSprite(string nomeArq, int x, int y, int retiraFundo=1, int idJanela=0){
        int id;
        unordered_map<string, int>::iterator it = spritesSimples.find(nomeArq);
        if (it == spritesSimples.end()){//não achou
            int next = sprites->ProxID();
            id = sprites->Insere(new CPIGSprite(next,nomeArq,retiraFundo,NULL,idJanela));
            spritesSimples[nomeArq] = id;
        }else{
            id = it->second;
        }
        PIGSprite sprite = sprites->GetElemento(id);
        if (sprite){
            sprite->Move(x,y);
            sprite->Desenha();
        }
    }

};
unordered_map<string,int> CPIGGerenciadorSprites::spritesSimples;
CPIGRepositorio<PIGSprite> *CPIGGerenciadorSprites::sprites;
CPIGRepositorio<PIGObjeto> *CPIGGerenciadorSprites::objetos;
CPIGRepositorio<PIGAnimacao> *CPIGGerenciadorSprites::animacoes;
#endif //_CPIGGERENCIADORSPRITES_
