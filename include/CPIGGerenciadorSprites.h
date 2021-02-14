#ifndef _CPIGGERENCIADORSPRITES_
#define _CPIGGERENCIADORSPRITES_

#include "CPIGSprite.h"
#include "CPIGObjeto.h"
#include "CPIGAnimacao.h"
#include "CPIGGeradorParticulas.h"

class CPIGGerenciadorSprites{

private:
    static std::unordered_map<std::string,int> spritesSimples;
    static CPIGRepositorio<PIGSprite> *sprites;
    static CPIGRepositorio<PIGObjeto> *objetos;
    static CPIGRepositorio<PIGAnimacao> *animacoes;
    static CPIGRepositorio<PIGGeradorParticulas> *geradores;

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

    static PIGGeradorParticulas GetGerador(int idGerador){
        return geradores->GetElemento(idGerador);
    }

    static void Inicia(){
        sprites = new CPIGRepositorio<PIGSprite>(PIG_MAX_SPRITES,"sprites");
        objetos = new CPIGRepositorio<PIGObjeto>(PIG_MAX_OBJETOS,"objetos");
        animacoes = new CPIGRepositorio<PIGAnimacao>(PIG_MAX_ANIMACOES,"animacoes");
        geradores = new CPIGRepositorio<PIGGeradorParticulas>(PIG_MAX_GERADORPARTICULAS,"geradores");
    }

    static void Encerra(){
        delete sprites;
        delete objetos;
        delete animacoes;
        delete geradores;
    }

    static int CriaSprite(std::string nomeArquivoBMP,int retiraFundo=1,PIG_Cor *corFundo=NULL,int idJanela=0){
        int id = sprites->ProxID();
        return sprites->Insere(new CPIGSprite(id,nomeArquivoBMP,retiraFundo,corFundo,idJanela));
    }

    static int CriaSprite(int idSpriteBase,int retiraFundo=1,PIG_Cor *corFundo=NULL,int idJanela=0){
        int id = sprites->ProxID();
        return sprites->Insere(new CPIGSprite(id,GetSprite(idSpriteBase),retiraFundo,corFundo,idJanela));
    }

    static int CriaSpriteOffScreen(PIGOffscreenRenderer offRenderer,int retiraFundo=1,PIG_Cor *corFundo=NULL,int idJanela=0){
        int id = sprites->ProxID();
        return sprites->Insere(new CPIGSprite(id,offRenderer,retiraFundo,corFundo,idJanela));
    }

    static int CriaObjeto(std::string nomeArquivoBMP,int retiraFundo=1,PIG_Cor *corFundo=NULL,int idJanela=0){
        int id = objetos->ProxID();
        return objetos->Insere(new CPIGObjeto(id,nomeArquivoBMP,retiraFundo,corFundo,idJanela));
    }

    static int CriaObjeto(int idObjetoBase,int retiraFundo=1,PIG_Cor *corFundo=NULL,int idJanela=0){
        int id = objetos->ProxID();
        return objetos->Insere(new CPIGObjeto(id,GetObjeto(idObjetoBase),retiraFundo,corFundo,idJanela));
    }

    static int CriaObjetoOffScreen(PIGOffscreenRenderer offRenderer,int retiraFundo=1,PIG_Cor *corFundo=NULL,int idJanela=0){
        int id = objetos->ProxID();
        return objetos->Insere(new CPIGObjeto(id,offRenderer,retiraFundo,corFundo,idJanela));
    }

    static int CriaAnimacao(std::string nomeArquivoBMP,int retiraFundo=1,PIG_Cor *corFundo=NULL,int idJanela=0){
        int id = animacoes->ProxID();
        return animacoes->Insere(new CPIGAnimacao(id,nomeArquivoBMP,retiraFundo,corFundo,idJanela));
    }

    static int CriaAnimacao(PIGAnimacao animaBase,int retiraFundo=1,PIG_Cor *corFundo=NULL,int idJanela=0){
        int id = animacoes->ProxID();
        return animacoes->Insere(new CPIGAnimacao(id,animaBase,retiraFundo,corFundo,idJanela));
    }

    static int CriaAnimacao(PIGObjeto objetoBase,int retiraFundo=1,PIG_Cor *corFundo=NULL,int idJanela=0){
        int id = animacoes->ProxID();
        return animacoes->Insere(new CPIGAnimacao(id,objetoBase,retiraFundo,corFundo,idJanela));
    }

    static int CriaGeradorParticulas(int maxParticulas,std::string nomeArquivoBMP,int audioCriacao, int audioEncerramento, bool retiraFundo=true, PIG_Cor *corFundo=NULL, int idJanela=0){
        int id = geradores->ProxID();
        return geradores->Insere(new CPIGGeradorParticulas(id,maxParticulas,nomeArquivoBMP,audioCriacao,audioEncerramento,retiraFundo,corFundo,idJanela));
    }

    static int CriaGeradorParticulas(int maxParticulas,PIGAnimacao animacaoBase,int audioCriacao, int audioEncerramento, bool retiraFundo=true, PIG_Cor *corFundo=NULL, int idJanela=0){
        int id = geradores->ProxID();
        return geradores->Insere(new CPIGGeradorParticulas(id,maxParticulas,animacaoBase,audioCriacao,audioEncerramento,retiraFundo,corFundo,idJanela));
    }

    static int CriaGeradorParticulas(int maxParticulas,PIGObjeto objetoBase,int audioCriacao, int audioEncerramento, bool retiraFundo=true, PIG_Cor *corFundo=NULL, int idJanela=0){
        int id = geradores->ProxID();
        return geradores->Insere(new CPIGGeradorParticulas(id,maxParticulas,objetoBase,audioCriacao,audioEncerramento,retiraFundo,corFundo,idJanela));
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

    static void DestroiGeradorParticulas(int idGerador){
        geradores->Remove(idGerador);
    }

    static void DesenhaSprite(std::string nomeArq,int x,int y,int retiraFundo=1, int idJanela=0){
        int id;
        std::unordered_map<std::string, int>::iterator it = spritesSimples.find(nomeArq);
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
std::unordered_map<std::string,int> CPIGGerenciadorSprites::spritesSimples;
CPIGRepositorio<PIGSprite> *CPIGGerenciadorSprites::sprites;
CPIGRepositorio<PIGObjeto> *CPIGGerenciadorSprites::objetos;
CPIGRepositorio<PIGAnimacao> *CPIGGerenciadorSprites::animacoes;
CPIGRepositorio<PIGGeradorParticulas> *CPIGGerenciadorSprites::geradores;
#endif //_CPIGGERENCIADORSPRITES_
