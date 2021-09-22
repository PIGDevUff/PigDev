#ifndef _CPIGASSETLOADER_
#define _CPIGASSETLOADER_

class CPIGHashNodeImagem{


public:
    int cont;
    SDL_Surface *imagem;
    CPIGHashNodeImagem(std::string nomeArq){
        cont = 1;
        //imagem = IMG_Load(nomeArq.c_str());
        SDL_Surface *aux = IMG_Load(nomeArq.c_str());
        imagem = SDL_ConvertSurfaceFormat(aux,SDL_PIXELFORMAT_RGBA32,0);
        SDL_FreeSurface(aux);
    }
    ~CPIGHashNodeImagem(){
        SDL_FreeSurface(imagem);
    }

};
typedef CPIGHashNodeImagem *PIGHashNodeImagem;

class CPIGHashNodeAudio{

public:
    int cont;
    Mix_Chunk *chunk;
    CPIGHashNodeAudio(std::string nomeArq){
        cont = 1;
        chunk = Mix_LoadWAV(nomeArq.c_str());
    }
    ~CPIGHashNodeAudio(){
        Mix_FreeChunk(chunk);
    }
};
typedef CPIGHashNodeAudio *PIGHashNodeAudio;

class CPIGAssetLoader{

private:

    static int totalBitmaps;
    static int totalAudios;
    static std::unordered_map<std::string,PIGHashNodeImagem> mapImagens;
    static std::unordered_map<std::string,PIGHashNodeAudio> mapAudios;

public:

    static void Inicia(){
        totalBitmaps=0;
        totalAudios=0;
    }

    static void Encerra(){
        for(std::unordered_map<std::string,PIGHashNodeImagem>::iterator it = mapImagens.begin(); it != mapImagens.end(); ++it) {
            delete it->second;
        }
        for(std::unordered_map<std::string,PIGHashNodeAudio>::iterator it = mapAudios.begin(); it != mapAudios.end(); ++it) {
            delete it->second;
        }
    }

    static SDL_Surface *LoadImage(std::string nomeArq){
        std::unordered_map<std::string, PIGHashNodeImagem>::iterator it = mapImagens.find(nomeArq);
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

    static void FreeImage(std::string nomeArq){
        std::unordered_map<std::string, PIGHashNodeImagem>::iterator it = mapImagens.find(nomeArq);
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

    static Mix_Chunk *LoadAudio(std::string nomeArq){
        std::unordered_map<std::string, PIGHashNodeAudio>::iterator it = mapAudios.find(nomeArq);
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

    static void FreeAudio(std::string nomeArq){
        std::unordered_map<std::string, PIGHashNodeAudio>::iterator it = mapAudios.find(nomeArq);
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

};

int CPIGAssetLoader::totalBitmaps;
std::unordered_map<std::string,PIGHashNodeImagem> CPIGAssetLoader::mapImagens;
int CPIGAssetLoader::totalAudios;
std::unordered_map<std::string,PIGHashNodeAudio> CPIGAssetLoader::mapAudios;
#endif // _CPIGASSETLOADER_
