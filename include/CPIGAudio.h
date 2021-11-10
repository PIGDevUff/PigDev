#ifndef _CPIGAUDIO_
#define _CPIGAUDIO_

class CPIGAudio{

private:

Mix_Chunk *chunk;
int volume;
int tempoExecucao;
PIGStatusAudio status;
int loops;
string nomeArq;
int canal;

public:

CPIGAudio(string nomeArquivo, int nLoops, int tempoPlay=-1){
    nomeArq = nomeArquivo;
    #ifdef PIG_SHARE_AUDIO
        chunk = CPIGAssetLoader::LoadAudio(nomeArq);
    #else
        chunk = Mix_LoadWAV(nomeArq.c_str());
    #endif

    if (!chunk) throw CPIGErroArquivo(nomeArquivo);

    volume = PIG_VOLUME_PADRAO;
    tempoExecucao = tempoPlay;
    status = PIG_AUDIO_PARADO;
    loops = nLoops;
    canal = -1;
}

~CPIGAudio(){
    #ifdef PIG_SHARE_AUDIO
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

PIGStatusAudio GetStatus(){
    return status;
}

int GetLoops(){
    return loops;
}

int Play(){
    status = PIG_AUDIO_TOCANDO;
    canal = Mix_PlayChannelTimed(-1,chunk,loops,tempoExecucao);
    Mix_Volume(canal,volume);
    return canal;
}

void Pause(){
    status = PIG_AUDIO_PAUSADO;
    if (canal!=-1)
        Mix_Pause(canal);
}

void Resume(){
    status = PIG_AUDIO_TOCANDO;
    if (canal!=-1)
        Mix_Resume(canal);
}

void Stop(){
    status = PIG_AUDIO_PARADO;
    if (canal!=-1){
        Mix_HaltChannel(canal);
        canal = -1;
    }
}

};

typedef CPIGAudio *PIGAudio;
#endif // _CPIGAUDIO_
