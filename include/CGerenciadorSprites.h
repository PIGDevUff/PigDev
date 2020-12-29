#ifndef _CGERENCIADORSPRITES_
#define _CGERENCIADORSPRITES_

class CGerenciadorSprites{

private:

static std::unordered_map<std::string,PIGSprite> sprites;


public:


static void Inicia(){

}

static void Encerra(){
    Limpa();
}


static void Limpa(){
    for(std::unordered_map<std::string,PIGSprite>::iterator it = sprites.begin(); it != sprites.end(); ++it) {
        delete it->second;
    }
}

static void Desenha(std::string nomeArq,int x,int y,int retiraFundo=1, int idJanela=0){
    PIGSprite sprite = NULL;
    std::unordered_map<std::string, PIGSprite>::iterator it = sprites.find(nomeArq);
    if (it == sprites.end()){//não achou
        sprite = new CPigSprite(nomeArq,retiraFundo,NULL,idJanela);
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
std::unordered_map<std::string,PIGSprite> CGerenciadorSprites::sprites;

#endif // _CGERENCIADORSPRITES_
