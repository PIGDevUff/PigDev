class CAudio{

private:

Mix_Chunk *chunk;
int volume;
int tempoExecucao;
PIG_StatusAudio status;
int loops;
char nomeArq[200];

public:

CAudio(char *nomeArquivo,int nLoops,int tempoPlay=-1){
    strcpy(nomeArq,nomeArquivo);
    #ifdef SHARE_AUDIO
        chunk = CAssetLoader::LoadAudio(nomeArq);
    #else
        chunk = Mix_LoadWAV(nomeArq);
    #endif

    volume = VOLUME_PADRAO;
    tempoExecucao = tempoPlay;
    status = AUDIO_PARADO;
    loops = nLoops;
}

~CAudio(){
    #ifdef SHARE_AUDIO
        CAssetLoader::FreeAudio(nomeArq);
    #else
        Mix_FreeChunk(chunk);
    #endif
}

Mix_Chunk *GetChunk(){
    return chunk;
}

void SetVolume(int valor){
    volume = valor;
}

int GetVolume(){
    return volume;
}

int GetTempoPlay(){
    return tempoExecucao;
}

PIG_StatusAudio GetStatus(){
    return status;
}

int GetLoops(){
    return loops;
}

void SetPlay(){
    status = AUDIO_TOCANDO;
}

void SetPause(){
    status = AUDIO_PAUSADO;
}

void SetStop(){
    status = AUDIO_PARADO;
}

};

typedef CAudio *Audio;
