#ifndef _CPIGGERENCIADORSPRITES_
#define _CPIGGERENCIADORSPRITES_

#include "CPIGSprite.h"
#include "CPIGObjeto.h"
#include "CPIGAnimacao.h"

class CPIGGerenciadorSprites{

private:
    static std::unordered_map<std::string,int> spritesSimples;
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
        sprites = new CPIGRepositorio<PIGSprite>(MAX_SPRITES,"sprites");
        objetos = new CPIGRepositorio<PIGObjeto>(MAX_OBJETOS,"objetos");
        animacoes = new CPIGRepositorio<PIGAnimacao>(MAX_ANIMACOES,"animacoes");
    }

    static void Encerra(){
        delete sprites;
        delete objetos;
        delete animacoes;
    }

    static int CriaSprite(std::string nomeArquivoBMP,int retiraFundo=1,PIG_Cor *corFundo=NULL,int idJanela=0){
        return sprites->Insere(new CPIGSprite(nomeArquivoBMP,retiraFundo,corFundo,idJanela));
    }

    static int CriaSprite(int idSpriteBase,int retiraFundo=1,PIG_Cor *corFundo=NULL,int idJanela=0){
        return sprites->Insere(new CPIGSprite(GetSprite(idSpriteBase),retiraFundo,corFundo,idJanela));
    }

    static int CriaObjeto(std::string nomeArquivoBMP,PIG_Cor *corFundo=NULL,int retiraFundo=1,int idJanela=0){
        return objetos->Insere(new CPIGObjeto(nomeArquivoBMP,corFundo,retiraFundo,idJanela));
    }

    static int CriaObjeto(int idObjetoBase,int retiraFundo=1,PIG_Cor *corFundo=NULL,int idJanela=0){
        return objetos->Insere(new CPIGObjeto(GetObjeto(idObjetoBase),corFundo,retiraFundo,idJanela));
    }

    static int CriaObjetoOffScreen(PIGOffscreenRenderer offRenderer,PIG_Cor *corFundo=NULL,int retiraFundo=1,int idJanela=0){
        return objetos->Insere(new CPIGObjeto(offRenderer,corFundo,retiraFundo,idJanela));
    }

    static int CriaAnimacao(std::string nomeArquivoBMP,PIG_Cor *corFundo=NULL,int retiraFundo=1,int idJanela=0){
        return animacoes->Insere(new CPIGAnimacao(nomeArquivoBMP,0,corFundo,retiraFundo,idJanela));
    }

    static int CriaAnimacao(int idAnimacaoBase,PIG_Cor *corFundo=NULL,int retiraFundo=1,int idJanela=0){
        return animacoes->Insere(new CPIGAnimacao(GetAnimacao(idAnimacaoBase),0,corFundo,retiraFundo,idJanela));
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

    static void DesenhaSprite(std::string nomeArq,int x,int y,int retiraFundo=1, int idJanela=0){
        int id;
        std::unordered_map<std::string, int>::iterator it = spritesSimples.find(nomeArq);
        if (it == spritesSimples.end()){//não achou
            id = sprites->Insere(new CPIGSprite(nomeArq,retiraFundo,NULL,idJanela));
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
std::unordered_map<std::string,int> CPIGGerenciadorSprites::spritesSimples;
CPIGRepositorio<PIGSprite> *CPIGGerenciadorSprites::sprites;
CPIGRepositorio<PIGObjeto> *CPIGGerenciadorSprites::objetos;
CPIGRepositorio<PIGAnimacao> *CPIGGerenciadorSprites::animacoes;
#endif //_CPIGGERENCIADORSPRITES_
