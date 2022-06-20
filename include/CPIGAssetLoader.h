#ifndef _CPIGASSETLOADER_
#define _CPIGASSETLOADER_

#include "SDL_image.h"
#include "SDL_mixer.h"

class CPIGHashNodeImagem{

public:
    int cont;
    SDL_Surface *imagem;

    CPIGHashNodeImagem(string nomeArq){
        cont = 1;
        SDL_Surface *aux = IMG_Load(nomeArq.c_str());
        imagem = SDL_ConvertSurfaceFormat(aux,SDL_PIXELFORMAT_RGBA32,0);
        SDL_FreeSurface(aux);
    }

    ~CPIGHashNodeImagem(){
        SDL_FreeSurface(imagem);
    }

};
typedef CPIGHashNodeImagem *PIGHashNodeImagem;

#ifdef PIGCOMAUDIO

class CPIGHashNodeAudio{

public:
    int cont;
    Mix_Chunk *chunk;

    CPIGHashNodeAudio(string nomeArq){
        cont = 1;
        chunk = Mix_LoadWAV(nomeArq.c_str());
    }

    ~CPIGHashNodeAudio(){
        Mix_FreeChunk(chunk);
    }
};
typedef CPIGHashNodeAudio *PIGHashNodeAudio;

#endif

class CPIGAssetLoader{

private:

    static int totalBitmaps;
    static unordered_map<string,PIGHashNodeImagem> mapImagens;

    #ifdef PIGCOMAUDIO
    static int totalAudios;
    static unordered_map<string,PIGHashNodeAudio> mapAudios;
    #endif

public:

    static void Inicia(){
        totalBitmaps=0;
        #ifdef PIGCOMAUDIO
        totalAudios=0;
        #endif
    }

    static void Encerra(){
        for(unordered_map<string,PIGHashNodeImagem>::iterator it = mapImagens.begin(); it != mapImagens.end(); ++it) {
            delete it->second;
        }
        #ifdef PIGCOMAUDIO
        for(unordered_map<string,PIGHashNodeAudio>::iterator it = mapAudios.begin(); it != mapAudios.end(); ++it) {
            delete it->second;
        }
        #endif
    }

    static SDL_Surface *LoadImage(string nomeArq){
        unordered_map<string, PIGHashNodeImagem>::iterator it = mapImagens.find(nomeArq);
        if (it == mapImagens.end()){//não achou
            PIGHashNodeImagem imagem = new CPIGHashNodeImagem(nomeArq);
            mapImagens[nomeArq]=imagem;
            totalBitmaps++;
            return imagem->imagem;
        }else{
            it->second->cont++;
            return it->second->imagem;
        }

    }

    static void FreeImage(string nomeArq){
        unordered_map<string, PIGHashNodeImagem>::iterator it = mapImagens.find(nomeArq);
        if (it == mapImagens.end()){//não achou
            printf("Nao existe asset carregado: %s\n",nomeArq.c_str());
        }else{
            it->second->cont--;
            if (it->second->cont==0){
                delete it->second;
                mapImagens.erase(it);
            }
        }
    }

    #ifdef PIGCOMAUDIO
    static Mix_Chunk *LoadAudio(string nomeArq){
        unordered_map<string, PIGHashNodeAudio>::iterator it = mapAudios.find(nomeArq);
        if (it == mapAudios.end()){//não achou
            PIGHashNodeAudio audio = new CPIGHashNodeAudio(nomeArq);
            mapAudios[nomeArq] = audio;
            totalAudios++;
            return audio->chunk;
        }else{
            it->second->cont++;
            return it->second->chunk;
        }
    }

    static void FreeAudio(string nomeArq){
        unordered_map<string, PIGHashNodeAudio>::iterator it = mapAudios.find(nomeArq);
        if (it == mapAudios.end()){//não achou
            printf("Nao existe asset carregado: %s\n",nomeArq.c_str());
        }else{
            it->second->cont--;
            if (it->second->cont==0){
                delete it->second;
                mapAudios.erase(it);
            }
        }
    }
    #endif //PIGCOMAUDIO

};

int CPIGAssetLoader::totalBitmaps;
unordered_map<string,PIGHashNodeImagem> CPIGAssetLoader::mapImagens;
#ifdef PIGCOMAUDIO
int CPIGAssetLoader::totalAudios;
unordered_map<string,PIGHashNodeAudio> CPIGAssetLoader::mapAudios;
#endif //PIGCOMAUDIO

#endif // _CPIGASSETLOADER_
