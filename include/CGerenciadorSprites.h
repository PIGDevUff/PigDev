#ifndef _CGERENCIADORSPIRTES_
#define _CGERENCIADORSPIRTES_

//#include "CPigIcone.h"

class CGerenciadorSprites{

private:

static std::map<std::string,PIGVisual> sprites;


public:


static void Inicia(){

}

static void Encerra(){
    Limpa();
}


static void Limpa(){
    for(std::map<std::string,PIGVisual>::iterator it = sprites.begin(); it != sprites.end(); ++it) {
        delete it->second;
    }
}

static void Desenha(std::string nomeArq,int x,int y,int retiraFundo=1, int idJanela=0){
    PIGVisual sprite = NULL;
    std::map<std::string, PIGVisual>::iterator it = sprites.find(nomeArq);
    if (it == sprites.end()){//não achou
        sprite = new CPigVisual(nomeArq,retiraFundo,NULL,idJanela);
        sprites[nomeArq]=sprite;
    }else{
        sprite = it->second;
    }
    if (sprite){
        sprite->Move(x,y);
        sprite->Desenha();
    }
}


};
std::map<std::string,PIGVisual> CGerenciadorSprites::sprites;

#endif // _CGERENCIADORSPIRTES_
