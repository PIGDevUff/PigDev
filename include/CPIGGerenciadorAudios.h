#ifndef _CPIGGERENCIADORAUDIOS_
#define _CPIGGERENCIADORAUDIOS_

#include "CPIGAudio.h"
#include "CPIGRepositorio.h"

class CPIGGerenciadorAudios: public CPIGRepositorio<PIGAudio>{

private:

    static int audioIds[PIG_QTD_CANAIS_PADRAO];
    Mix_Music *background;
    int volumeBackground;
    PIGStatusAudio statusBackground;

    inline static void TrataParadaAudio(int canal){
        SDL_Event eventoAudio;
        eventoAudio.type = SDL_USEREVENT;
        eventoAudio.user.code = PIG_EVENTO_AUDIO;
        eventoAudio.user.data1 = (int*)malloc(sizeof(int));
        *((int*)eventoAudio.user.data1) = audioIds[canal];
        SDL_PushEvent(&eventoAudio);
        audioIds[canal] = -1;
    }

    inline static void TrataParadaBackground(){
        SDL_Event eventoAudio;
        eventoAudio.type = SDL_USEREVENT;
        eventoAudio.user.code = PIG_EVENTO_AUDIO;
        eventoAudio.user.data1 = (int*)malloc(sizeof(int)*1);
        *((int*)eventoAudio.user.data1) = PIG_AUDIO_BACKGROUND;
        SDL_PushEvent(&eventoAudio);
    }

public:

    CPIGGerenciadorAudios():CPIGRepositorio<PIGAudio>(PIG_MAX_AUDIOS,"CPIGAudio"){
        Mix_OpenAudio(PIG_FREQ_AUDIO_PADRAO,MIX_DEFAULT_FORMAT,2,PIG_TAMANHO_CHUNK);

        Mix_AllocateChannels(PIG_QTD_CANAIS_PADRAO);

        for (int i=0;i<PIG_QTD_CANAIS_PADRAO;i++){
            audioIds[i] = -1;
        }

        Mix_ChannelFinished(TrataParadaAudio);
        background = NULL;
        volumeBackground = PIG_VOLUME_PADRAO;
        statusBackground = PIG_AUDIO_PARADO;
        Mix_HookMusicFinished(TrataParadaBackground);
    }

    ~CPIGGerenciadorAudios(){
        StopTudo();

        if (background)
            Mix_FreeMusic(background);
        Mix_CloseAudio();
    }

    void CarregaBackground(string nomeArquivo){
        if (background)
            Mix_FreeMusic(background);
        background = Mix_LoadMUS(nomeArquivo.c_str());
    }

    void PlayBackground(int nVezes){
        if (background){
            Mix_PlayMusic(background, nVezes);
            statusBackground = PIG_AUDIO_TOCANDO;
        }
    }

    void StopBackground(){
        if (background){
            Mix_HaltMusic();
            statusBackground = PIG_AUDIO_PARADO;
        }
    }

    void PauseBackground(){
        if (background){
            Mix_PauseMusic();
            statusBackground = PIG_AUDIO_PAUSADO;
        }
    }

    void ResumeBackground(){
        if (background){
            Mix_ResumeMusic();
            statusBackground = PIG_AUDIO_TOCANDO;
        }
    }

    PIGStatusAudio GetStatusBackground(){
        return statusBackground;
    }

    inline void SetVolumeBackground(int valor){
        volumeBackground = valor;
        Mix_VolumeMusic(volumeBackground);
    }

    inline int GetVolumeBackground(){
        return volumeBackground;
    }

    inline int CriaAudio(string nomeArquivo, int nLoops, int tempoExecucao=-1){
        return Insere(new CPIGAudio(nomeArquivo,nLoops,tempoExecucao));
    }

    inline void SetVolumeTudo(int volume){
        Mix_Volume(-1,volume);

        auto it = elementos.begin();
        while (it != elementos.end()){
            it->second->SetVolume(volume);
            it++;
        }
    }

    inline void Play(int idAudio){
        PIGAudio audio = GetElemento(idAudio);
        int c = audio->Play();
        audioIds[c] = idAudio;
    }

    inline void StopTudo(){
        Mix_HaltChannel(-1);

        auto it = elementos.begin();
        while (it != elementos.end()){
            it->second->Stop();
            it++;
        }
    }

    inline void PauseTudo(){
        Mix_Pause(-1);

        auto it = elementos.begin();
        while (it != elementos.end()){
            it->second->Pause();
            it++;
        }
    }

    inline void ResumeTudo(){
        Mix_Resume(-1);

        auto it = elementos.begin();
        while (it != elementos.end()){
            it->second->Resume();
            it++;
        }
    }

};

int CPIGGerenciadorAudios::audioIds[PIG_QTD_CANAIS_PADRAO];
CPIGGerenciadorAudios pigGerAudios;
#endif // _CPIGGERENCIADORAUDIOS_
