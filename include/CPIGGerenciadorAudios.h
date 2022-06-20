#ifndef _CPIGGERENCIADORAUDIOS_
#define _CPIGGERENCIADORAUDIOS_

#include "CPIGAudio.h"

class CPIGGerenciadorAudios{

private:

    static CPIGRepositorio<PIGAudio> *audios;
    static int audioIds[PIG_QTD_CANAIS_PADRAO];
    static Mix_Music *background;
    static int volumeBackground;
    static PIGStatusAudio statusBackground;

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

    static void Inicia(){
        Mix_OpenAudio(PIG_FREQ_AUDIO_PADRAO,MIX_DEFAULT_FORMAT,2,PIG_TAMANHO_CHUNK);

        Mix_AllocateChannels(PIG_QTD_CANAIS_PADRAO);

        audios = new CPIGRepositorio<PIGAudio>(PIG_MAX_AUDIOS,"audios");
        for (int i=0;i<PIG_QTD_CANAIS_PADRAO;i++){
            audioIds[i] = -1;
        }

        Mix_ChannelFinished(TrataParadaAudio);
        background = NULL;
        volumeBackground = PIG_VOLUME_PADRAO;
        statusBackground = PIG_AUDIO_PARADO;
        Mix_HookMusicFinished(TrataParadaBackground);
    }

    static void Encerra(){
        StopTudo();

        delete audios;
        if (background)
            Mix_FreeMusic(background);
        Mix_CloseAudio();
    }

    inline static PIGAudio GetAudio(int idAudio){
        return audios->GetElemento(idAudio);
    }

    static void CarregaBackground(string nomeArquivo){
        if (background)
            Mix_FreeMusic(background);
        background = Mix_LoadMUS(nomeArquivo.c_str());
    }

    static void PlayBackground(int nVezes){
        if (background){
            Mix_PlayMusic(background, nVezes);
            statusBackground = PIG_AUDIO_TOCANDO;
        }
    }

    static void StopBackground(){
        if (background){
            Mix_HaltMusic();
            statusBackground = PIG_AUDIO_PARADO;
        }
    }

    static void PauseBackground(){
        if (background){
            Mix_PauseMusic();
            statusBackground = PIG_AUDIO_PAUSADO;
        }
    }

    static void ResumeBackground(){
        if (background){
            Mix_ResumeMusic();
            statusBackground = PIG_AUDIO_TOCANDO;
        }
    }

    inline static PIGStatusAudio GetStatusBackground(){
        return statusBackground;
    }

    inline static void SetVolumeBackground(int valor){
        volumeBackground = valor;
        Mix_VolumeMusic(volumeBackground);
    }

    inline static int GetVolumeBackground(){
        return volumeBackground;
    }

    inline static int CriaAudio(string nomeArquivo, int nLoops, int tempoExecucao=-1){
        return audios->Insere(new CPIGAudio(nomeArquivo,nLoops,tempoExecucao));
    }

    inline static int InsereAudio(PIGAudio audio){
        return audios->Insere(audio);
    }

    inline static void DestroiAudio(int idAudio){
        audios->Remove(idAudio);
    }

    inline static void SetVolumeTudo(int volume){
        Mix_Volume(-1,volume);

        PIGAudio audio = audios->GetPrimeiroElemento();
        while (audio){
            audio->SetVolume(volume);
            audio = audios->GetProximoElemento();
        }
    }

    inline static void Play(int idAudio){
        PIGAudio audio = GetAudio(idAudio);
        int c = audio->Play();
        audioIds[c] = idAudio;
    }

    inline static void StopTudo(){
        Mix_HaltChannel(-1);

        PIGAudio audio = audios->GetPrimeiroElemento();
        while (audio){
            audio->Stop();
            audio = audios->GetProximoElemento();
        }
    }

    inline static void PauseTudo(){
        Mix_Pause(-1);

        PIGAudio audio = audios->GetPrimeiroElemento();
        while (audio){
            audio->Pause();
            audio = audios->GetProximoElemento();

        }
    }

    inline static void ResumeTudo(){
        Mix_Resume(-1);

        PIGAudio audio = audios->GetPrimeiroElemento();
        while (audio){
            audio->Resume();
            audio = audios->GetProximoElemento();
        }
    }

};

CPIGRepositorio<PIGAudio> *CPIGGerenciadorAudios::audios;
int CPIGGerenciadorAudios::audioIds[PIG_QTD_CANAIS_PADRAO];
Mix_Music *CPIGGerenciadorAudios::background;
int CPIGGerenciadorAudios::volumeBackground;
PIGStatusAudio CPIGGerenciadorAudios::statusBackground;
#endif // _CPIGGERENCIADORAUDIOS_
