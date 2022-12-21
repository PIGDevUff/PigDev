#ifndef _CPIGGERENCIADORSPRITES_
#define _CPIGGERENCIADORSPRITES_

#include "CPIGSprite.h"
#include "CPIGRepositorio.h"

class CPIGGerenciadorSprites: public CPIGRepositorio<PIGSprite>{

private:

    unordered_map<string,int> spritesSimples;

public:

    CPIGGerenciadorSprites():CPIGRepositorio<PIGSprite>(PIG_MAX_SPRITES,"CPIGSprite"){}

    inline int CriaSprite(string nomeArquivo, int retiraFundo=1, PIGCor *corFundo=NULL, int idJanela=0){
        return Insere(new CPIGSprite(ProxID(),nomeArquivo,retiraFundo,corFundo,idJanela));
    }

    inline int CriaSprite(int idSpriteBase, int retiraFundo=1, PIGCor *corFundo=NULL, int idJanela=0){
        return Insere(new CPIGSprite(ProxID(),GetElemento(idSpriteBase),retiraFundo,corFundo,idJanela));
    }

    inline int CriaSpriteOffScreen(PIGOffscreenRenderer offRenderer, int retiraFundo=1, PIGCor *corFundo=NULL, int idJanela=0){
        return Insere(new CPIGSprite(ProxID(),offRenderer,retiraFundo,corFundo,idJanela));
    }

    inline void DesenhaSprite(string nomeArq, int x, int y, int retiraFundo=1, int idJanela=0){
        int id;
        auto it = spritesSimples.find(nomeArq);
        if (it == spritesSimples.end()){//não achou
            int next = ProxID();
            id = Insere(new CPIGSprite(next,nomeArq,retiraFundo,NULL,idJanela));
            spritesSimples[nomeArq] = id;
        }else{
            id = it->second;
        }
        PIGSprite sprite = elementos[id];
        if (sprite){
            sprite->Move(x,y);
            sprite->Desenha();
        }
    }

};
CPIGGerenciadorSprites pigGerSprites;
#endif //_CPIGGERENCIADORSPRITES_
