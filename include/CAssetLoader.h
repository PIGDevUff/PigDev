class CHashNodeImagem{

public:
    int cont;
    SDL_Surface *imagem;
    CHashNodeImagem(std::string nomeArq){
        cont = 1;
        imagem = IMG_Load(nomeArq.c_str());
    }
    ~CHashNodeImagem(){
        SDL_FreeSurface(imagem);
    }

};
typedef CHashNodeImagem *HashNodeImagem;

class CHashNodeAudio{

public:
    int cont;
    Mix_Chunk *chunk;
    CHashNodeAudio(std::string nomeArq){
        cont = 1;
        chunk = Mix_LoadWAV(nomeArq.c_str());
    }
    ~CHashNodeAudio(){
        Mix_FreeChunk(chunk);
    }
};
typedef CHashNodeAudio *HashNodeAudio;

class CAssetLoader{

private:

    static int totalBitmaps;
    static int totalAudios;
    static std::map<std::string,HashNodeImagem> mapImagens;
    static std::map<std::string,HashNodeAudio> mapAudios;

public:

    static void Inicia(){
        totalBitmaps=0;
        totalAudios=0;
    }

    static void Encerra(){
        for(std::map<std::string,HashNodeImagem>::iterator it = mapImagens.begin(); it != mapImagens.end(); ++it) {
            delete it->second;
        }
        for(std::map<std::string,HashNodeAudio>::iterator it = mapAudios.begin(); it != mapAudios.end(); ++it) {
            delete it->second;
        }
    }

    static SDL_Surface *LoadImage(std::string nomeArq){
        std::map<std::string, HashNodeImagem>::iterator it = mapImagens.find(nomeArq);
        if (it == mapImagens.end()){//não achou
            HashNodeImagem imagem = new CHashNodeImagem(nomeArq);
            mapImagens[nomeArq]=imagem;
            totalBitmaps++;
            return imagem->imagem;
        }else{
            it->second->cont++;
            return it->second->imagem;
        }

    }

    static void FreeImage(std::string nomeArq){
        std::map<std::string, HashNodeImagem>::iterator it = mapImagens.find(nomeArq);
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
        std::map<std::string, HashNodeAudio>::iterator it = mapAudios.find(nomeArq);
        if (it == mapAudios.end()){//não achou
            HashNodeAudio audio = new CHashNodeAudio(nomeArq);
            mapAudios[nomeArq] = audio;
            totalAudios++;
            return audio->chunk;
        }else{
            it->second->cont++;
            return it->second->chunk;
        }
    }

    static void FreeAudio(std::string nomeArq){
        std::map<std::string, HashNodeAudio>::iterator it = mapAudios.find(nomeArq);
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

int CAssetLoader::totalBitmaps;
std::map<std::string,HashNodeImagem> CAssetLoader::mapImagens;
int CAssetLoader::totalAudios;
std::map<std::string,HashNodeAudio> CAssetLoader::mapAudios;
