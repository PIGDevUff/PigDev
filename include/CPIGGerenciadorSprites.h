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
    /*static std::vector<int> posLivres;
    static std::unordered_map<int,PIGSprite> sprites;
    static std::unordered_map<int,PIGSprite>::iterator it;*/

public:

    static PIGSprite GetSprite(int idSprite){
        /*it = sprites.find(idSprite);
        if (it==sprites.end()) throw CPIGErroIndice(idSprite,"sprites");
        return it->second;*/
        return sprites->GetElemento(idSprite);
    }

    static PIGObjeto GetObjeto(int idObjeto){
        /*PIGObjeto obj = (PIGObjeto)GetSprite(idObjeto);
        if (obj==NULL) throw CPIGErroIndice(idObjeto,"objetos");
        else return obj;*/
        return objetos->GetElemento(idObjeto);
    }

    static PIGAnimacao GetAnimacao(int idAnimacao){
        /*PIGAnimacao anima = (PIGAnimacao)GetSprite(idAnimacao);
        if (anima==NULL) throw CPIGErroIndice(idAnimacao,"animacoes");
        else return anima;*/
        return animacoes->GetElemento(idAnimacao);
    }

    static void Inicia(){
        /*for (int i=0;i<MAX_SPRITES;i++)
            posLivres.push_back(i);*/
        sprites = new CPIGRepositorio<PIGSprite>(MAX_SPRITES,"sprites");
        objetos = new CPIGRepositorio<PIGObjeto>(MAX_OBJETOS,"objetos");
        animacoes = new CPIGRepositorio<PIGAnimacao>(MAX_ANIMACOES,"animacoes");
    }

    static void Encerra(){
        /*for(it = sprites.begin(); it != sprites.end(); ++it) {
            delete it->second;
        }*/
        delete sprites;
        delete objetos;
        delete animacoes;
    }

    static int CriaSprite(std::string nomeArquivoBMP,int retiraFundo=1,PIG_Cor *corFundo=NULL,int idJanela=0){
        /*int resp = posLivres[0];
        posLivres.erase(posLivres.begin());
        sprites[resp] = new CPIGSprite(nomeArquivoBMP,retiraFundo,corFundo,idJanela);
        return resp;*/
        sprites->Insere(new CPIGSprite(nomeArquivoBMP,retiraFundo,corFundo,idJanela));
    }

    static int CriaSprite(int idSpriteBase,int retiraFundo=1,PIG_Cor *corFundo=NULL,int idJanela=0){
        /*int resp = posLivres[0];
        posLivres.erase(posLivres.begin());
        sprites[resp] = new CPIGSprite(GetSprite(idSpriteBase),retiraFundo,corFundo,idJanela);
        return resp;*/
        sprites->Insere(new CPIGSprite(GetSprite(idSpriteBase),retiraFundo,corFundo,idJanela));
    }

    static int CriaObjeto(std::string nomeArquivoBMP,PIG_Cor *corFundo=NULL,int retiraFundo=1,int idJanela=0){
        /*int resp = posLivres[0];
        posLivres.erase(posLivres.begin());
        sprites[resp] = new CPIGObjeto(nomeArquivoBMP,corFundo,retiraFundo,idJanela);
        return resp;*/
        sprites->Insere(new CPIGObjeto(nomeArquivoBMP,corFundo,retiraFundo,idJanela));
    }

    static int CriaObjeto(int idObjetoBase,int retiraFundo=1,PIG_Cor *corFundo=NULL,int idJanela=0){
        /*int resp = posLivres[0];
        posLivres.erase(posLivres.begin());
        sprites[resp] = new CPIGObjeto(GetObjeto(idObjetoBase),corFundo,retiraFundo,idJanela);
        return resp;*/
        objetos->Insere(new CPIGObjeto(GetObjeto(idObjetoBase),corFundo,retiraFundo,idJanela));
    }

    static int CriaObjetoOffScreen(PIGOffscreenRenderer offRenderer,PIG_Cor *corFundo=NULL,int retiraFundo=1,int idJanela=0){
        /*int resp = posLivres[0];
        posLivres.erase(posLivres.begin());
        sprites[resp] = new CPIGObjeto(offRenderer,corFundo,retiraFundo,idJanela);
        return resp;*/
        objetos->Insere(new CPIGObjeto(offRenderer,corFundo,retiraFundo,idJanela));
    }

    static int CriaAnimacao(std::string nomeArquivoBMP,PIG_Cor *corFundo=NULL,int retiraFundo=1,int idJanela=0){
        /*int resp = posLivres[0];
        posLivres.erase(posLivres.begin());
        sprites[resp] = new CPIGAnimacao(nomeArquivoBMP,0,corFundo,retiraFundo,idJanela);
        return resp;*/
        animacoes->Insere(new CPIGAnimacao(nomeArquivoBMP,0,corFundo,retiraFundo,idJanela));
    }

    static int CriaAnimacao(int idAnimacaoBase,PIG_Cor *corFundo=NULL,int retiraFundo=1,int idJanela=0){
        /*int resp = posLivres[0];
        posLivres.erase(posLivres.begin());
        sprites[resp] = new CPIGAnimacao(GetAnimacao(idAnimacaoBase),0,corFundo,retiraFundo,idJanela);
        return resp;*/
        animacoes->Insere(new CPIGAnimacao(GetAnimacao(idAnimacaoBase),0,corFundo,retiraFundo,idJanela));
    }

    static void DestroiSprite(int idSprite){
        /*PIGSprite sprite = GetSprite(idSprite);
        delete sprite;
        sprites.erase(idSprite);*/
        sprites->Remove(idSprite);
    }

    static void DestroiObjeto(int idObjeto){
        /*PIGObjeto objeto = GetObjeto(idObjeto);
        delete objeto;
        sprites.erase(idObjeto);*/
        objetos->Remove(idObjeto);
    }

    static void DestroiAnimacao(int idAnimacao){
        /*PIGAnimacao anima = GetAnimacao(idAnimacao);
        delete anima;
        sprites.erase(idAnimacao);*/
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
/*std::vector<int> CPIGGerenciadorSprites::posLivres;
std::unordered_map<int,PIGSprite> CPIGGerenciadorSprites::sprites;
std::unordered_map<int,PIGSprite>::iterator CPIGGerenciadorSprites::it;*/
#endif //_CPIGGERENCIADORSPRITES_
