#ifndef _CPIGGERENCIADORSPRITES_
#define _CPIGGERENCIADORSPRITES_

#include "CPIGSprite.h"
#include "CPIGObjeto.h"
#include "CPIGAnimacao.h"

class CPIGGerenciadorSprites{

private:
    static std::unordered_map<std::string,int> spritesSimples;
    static std::vector<int> posLivres;
    static std::unordered_map<int,PIGSprite> sprites;
    static std::unordered_map<int,PIGSprite>::iterator it;

public:

    static PIGSprite GetSprite(int idSprite){
        it = sprites.find(idSprite);
        if (it==sprites.end()) throw CPIGErroIndice(idSprite,"sprites");
        return it->second;
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
        for (int i=0;i<MAX_SPRITES;i++)
            posLivres.push_back(i);
    }

    static void Encerra(){
        for(it = sprites.begin(); it != sprites.end(); ++it) {
            delete it->second;
        }
    }

    static int CriaSprite(std::string nomeArquivoBMP,int retiraFundo=1,PIG_Cor *corFundo=NULL,int idJanela=0){
        int resp = posLivres[0];
        posLivres.erase(posLivres.begin());
        sprites[resp] = new CPIGSprite(nomeArquivoBMP,retiraFundo,corFundo,idJanela);
        return resp;
    }

    static int CriaSprite(int idSpriteBase,int retiraFundo=1,PIG_Cor *corFundo=NULL,int idJanela=0){
        int resp = posLivres[0];
        posLivres.erase(posLivres.begin());
        sprites[resp] = new CPIGSprite(GetSprite(idSpriteBase),retiraFundo,corFundo,idJanela);
        return resp;
    }

    static int CriaObjeto(std::string nomeArquivoBMP,PIG_Cor *corFundo=NULL,int retiraFundo=1,int idJanela=0){
        int resp = posLivres[0];
        posLivres.erase(posLivres.begin());
        sprites[resp] = new CPIGObjeto(nomeArquivoBMP,corFundo,retiraFundo,idJanela);
        return resp;
    }

    static int CriaObjeto(int idObjetoBase,int retiraFundo=1,PIG_Cor *corFundo=NULL,int idJanela=0){
        int resp = posLivres[0];
        posLivres.erase(posLivres.begin());
        sprites[resp] = new CPIGObjeto(GetObjeto(idObjetoBase),corFundo,retiraFundo,idJanela);
        return resp;
    }

    static int CriaObjetoOffScreen(PIGOffscreenRenderer offRenderer,PIG_Cor *corFundo=NULL,int retiraFundo=1,int idJanela=0){
        int resp = posLivres[0];
        posLivres.erase(posLivres.begin());
        sprites[resp] = new CPIGObjeto(offRenderer,corFundo,retiraFundo,idJanela);
        return resp;
    }

    static int CriaAnimacao(std::string nomeArquivoBMP,PIG_Cor *corFundo=NULL,int retiraFundo=1,int idJanela=0){
        int resp = posLivres[0];
        posLivres.erase(posLivres.begin());
        sprites[resp] = new CPIGAnimacao(nomeArquivoBMP,0,corFundo,retiraFundo,idJanela);
        return resp;
    }

    static int CriaAnimacao(int idAnimacaoBase,PIG_Cor *corFundo=NULL,int retiraFundo=1,int idJanela=0){
        int resp = posLivres[0];
        posLivres.erase(posLivres.begin());
        sprites[resp] = new CPIGAnimacao(GetAnimacao(idAnimacaoBase),0,corFundo,retiraFundo,idJanela);
        return resp;
    }

    static void DestroiSprite(int idSprite){
        PIGSprite sprite = GetSprite(idSprite);
        delete sprite;
        sprites.erase(idSprite);
    }

    static void DestroiObjeto(int idObjeto){
        PIGObjeto objeto = GetObjeto(idObjeto);
        delete objeto;
        sprites.erase(idObjeto);
    }

    static void DestroiAnimacao(int idAnimacao){
        PIGAnimacao anima = GetAnimacao(idAnimacao);
        delete anima;
        sprites.erase(idAnimacao);
    }

    static void DesenhaSprite(std::string nomeArq,int x,int y,int retiraFundo=1, int idJanela=0){
        int id;
        std::unordered_map<std::string, int>::iterator it = spritesSimples.find(nomeArq);
        if (it == spritesSimples.end()){//não achou
            id = CriaSprite(nomeArq,retiraFundo,NULL,idJanela);
            spritesSimples[nomeArq] = id;
        }else{
            id = it->second;
        }
        if (sprites[id]){
            sprites[id]->Move(x,y);
            sprites[id]->Desenha();
        }
    }

};
std::unordered_map<std::string,int> CPIGGerenciadorSprites::spritesSimples;
std::vector<int> CPIGGerenciadorSprites::posLivres;
std::unordered_map<int,PIGSprite> CPIGGerenciadorSprites::sprites;
std::unordered_map<int,PIGSprite>::iterator CPIGGerenciadorSprites::it;
#endif //_CPIGGERENCIADORSPRITES_
