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

    static PIGSprite GetSprite(int idSprite){
        return sprites->GetElemento(idSprite);
    }

    static PIGObjeto GetObjeto(int idObjeto){
        return objetos->GetElemento(idObjeto);
    }

    static PIGAnimacao GetAnimacao(int idAnimacao){
        return animacoes->GetElemento(idAnimacao);
    }

    static void Inicia(){
        sprites = new CPIGRepositorio<PIGSprite>(PIG_MAX_SPRITES,"sprites");
        objetos = new CPIGRepositorio<PIGObjeto>(PIG_MAX_OBJETOS,"objetos");
        animacoes = new CPIGRepositorio<PIGAnimacao>(PIG_MAX_ANIMACOES,"animacoes");
    }

    static void Encerra(){
        delete sprites;
        delete objetos;
        delete animacoes;
    }

    static int CriaSprite(string nomeArquivoBMP, int retiraFundo=1, PIGCor *corFundo=NULL, int idJanela=0){
        int id = sprites->ProxID();
        return sprites->Insere(new CPIGSprite(id,nomeArquivoBMP,retiraFundo,corFundo,idJanela));
    }

    static int CriaSprite(int idSpriteBase, int retiraFundo=1, PIGCor *corFundo=NULL, int idJanela=0){
        int id = sprites->ProxID();
        return sprites->Insere(new CPIGSprite(id,GetSprite(idSpriteBase),retiraFundo,corFundo,idJanela));
    }

    static int CriaSpriteOffScreen(PIGOffscreenRenderer offRenderer, int retiraFundo=1, PIGCor *corFundo=NULL, int idJanela=0){
        int id = sprites->ProxID();
        return sprites->Insere(new CPIGSprite(id,offRenderer,retiraFundo,corFundo,idJanela));
    }

    static int CriaObjeto(string nomeArquivoBMP, int retiraFundo=1, PIGCor *corFundo=NULL,int idJanela=0){
        int id = objetos->ProxID();
        return objetos->Insere(new CPIGObjeto(id,nomeArquivoBMP,retiraFundo,corFundo,idJanela));
    }

    static int CriaObjeto(int idObjetoBase, int retiraFundo=1, PIGCor *corFundo=NULL, int idJanela=0){
        int id = objetos->ProxID();
        return objetos->Insere(new CPIGObjeto(id,GetObjeto(idObjetoBase),retiraFundo,corFundo,idJanela));
    }

    static int CriaObjetoOffScreen(PIGOffscreenRenderer offRenderer, int retiraFundo=1, PIGCor *corFundo=NULL, int idJanela=0){
        int id = objetos->ProxID();
        return objetos->Insere(new CPIGObjeto(id,offRenderer,retiraFundo,corFundo,idJanela));
    }

    static int CriaAnimacao(string nomeArquivoBMP, int retiraFundo=1, PIGCor *corFundo=NULL, int idJanela=0){
        int id = animacoes->ProxID();
        return animacoes->Insere(new CPIGAnimacao(id,nomeArquivoBMP,retiraFundo,corFundo,idJanela));
    }

    static int CriaAnimacao(PIGAnimacao animaBase, int retiraFundo=1, PIGCor *corFundo=NULL, int idJanela=0){
        int id = animacoes->ProxID();
        return animacoes->Insere(new CPIGAnimacao(id,animaBase,retiraFundo,corFundo,idJanela));
    }

    static int CriaAnimacao(PIGObjeto objetoBase, int retiraFundo=1, PIGCor *corFundo=NULL, int idJanela=0){
        int id = animacoes->ProxID();
        return animacoes->Insere(new CPIGAnimacao(id,objetoBase,retiraFundo,corFundo,idJanela));
    }

    static int GetProxIndiceSprite(){
        return sprites->ProxID();
    }

    static int InsereSprite(PIGSprite spriteBase){
        return sprites->Insere(spriteBase);
    }

    static int GetProxIndiceObjeto(){
        return objetos->ProxID();
    }

    static int InsereObjeto(PIGObjeto objBase){
        return objetos->Insere(objBase);
    }

    static int GetProxIndiceAnimacao(){
        return animacoes->ProxID();
    }

    static int InsereAnimacao(PIGAnimacao animaBase){
        return animacoes->Insere(animaBase);
    }

    static void DestroiSprite(int idSprite){
        sprites->Remove(idSprite);
    }

    static void DestroiObjeto(int idObjeto){
        objetos->Remove(idObjeto);
    }

    static void DestroiAnimacao(int idAnimacao){
        animacoes->Remove(idAnimacao);
    }

    static void DesenhaSprite(string nomeArq, int x, int y, int retiraFundo=1, int idJanela=0){
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
