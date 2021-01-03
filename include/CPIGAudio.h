#ifndef _CPIGAUDIO_
#define _CPIGAUDIO_

class CPIGAudio{

private:

Mix_Chunk *chunk;
int volume;
int tempoExecucao;
PIG_StatusAudio status;
int loops;
std::string nomeArq;
int canal;

public:

CPIGAudio(std::string nomeArquivo,int nLoops,int tempoPlay=-1){
    nomeArq = nomeArquivo;
    #ifdef SHARE_AUDIO
        chunk = CPIGAssetLoader::LoadAudio(nomeArq);
    #else
        chunk = Mix_LoadWAV(nomeArq.c_str());
    #endif

    if (!chunk) throw CPIGErroArquivo(nomeArquivo);

    volume = VOLUME_PADRAO;
    tempoExecucao = tempoPlay;
    status = AUDIO_PARADO;
    loops = nLoops;
    canal = -1;
}

~CPIGAudio(){
    #ifdef SHARE_AUDIO
        CPIGAssetLoader::FreeAudio(nomeArq);
    #else
        Mix_FreeChunk(chunk);
    #endif
}

Mix_Chunk *GetChunk(){
    return chunk;
}

void SetVolume(int valor){
    volume = valor;
    if (canal!=-1)
        Mix_Volume(canal,volume);
}


int GetCanal(){
    return canal;
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

void Play(){
    status = AUDIO_TOCANDO;
    canal = Mix_PlayChannelTimed(-1,chunk,loops,tempoExecucao);
    Mix_Volume(canal,volume);
}

void Pause(){
    status = AUDIO_PAUSADO;
    if (canal!=-1)
        Mix_Pause(canal);
}

void Resume(){
    status = AUDIO_TOCANDO;
    if (canal!=-1)
        Mix_Resume(canal);
}

void Stop(){
    status = AUDIO_PARADO;
    if (canal!=-1){
        Mix_HaltChannel(canal);
        canal = -1;
    }
}

};

typedef CPIGAudio *PIGAudio;
#endif // _CPIGAUDIO_
