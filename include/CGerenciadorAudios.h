#ifndef _CGERENCIADORAUDIOS_
#define _CGERENCIADORAUDIOS_

#include "CAudio.h"
class CGerenciadorAudios{

private:
static int totalAudios;
static PoolNumeros numAudios;
static Audio audios[MAX_AUDIOS];
static int audioIds[QTD_CANAIS_PADRAO];
static Mix_Music *background;
static int volumeBackground;
static PIG_StatusAudio statusBackground;

inline static void TrataParadaAudio(int canal){
    SDL_Event eventoAudio;
    eventoAudio.type = SDL_USEREVENT;
    eventoAudio.user.code = EVENTO_AUDIO;
    eventoAudio.user.data1 = (int*)malloc(sizeof(int));
    *((int*)eventoAudio.user.data1) = audioIds[canal];
    SDL_PushEvent(&eventoAudio);
    audioIds[canal] = -1;
}

inline static void TrataParadaBackground(){
    SDL_Event eventoAudio;
    eventoAudio.type = SDL_USEREVENT;
    eventoAudio.user.code = EVENTO_AUDIO;
    eventoAudio.user.data1 = (int*)malloc(sizeof(int)*1);
    *((int*)eventoAudio.user.data1) =  ID_BACKGROUND;
    SDL_PushEvent(&eventoAudio);
}

public:

static void Inicia(){
    Mix_OpenAudio(FREQ_AUDIO_PADRAO,MIX_DEFAULT_FORMAT,2,TAMANHO_CHUNK);

    Mix_AllocateChannels(QTD_CANAIS_PADRAO);

    totalAudios = 0;
    for (int i=0;i<MAX_AUDIOS;i++){
        audios[i] = NULL;
    }
    for (int i=0;i<QTD_CANAIS_PADRAO;i++){
        audioIds[i] = -1;
    }
    numAudios = new CPoolNumeros(MAX_AUDIOS);

    Mix_ChannelFinished(TrataParadaAudio);
    background = NULL;
    volumeBackground = VOLUME_PADRAO;
    statusBackground = AUDIO_PARADO;
    Mix_HookMusicFinished(TrataParadaBackground);
}

static void Encerra(){
    StopTudo();
    for (int i=0;i<MAX_AUDIOS;i++){
        if (audios[i]) delete audios[i];
    }
    delete numAudios;
    if (background)
        Mix_FreeMusic(background);
    Mix_CloseAudio();
}

inline static Audio GetAudio(int idAudio){
    if (idAudio<0||idAudio>=MAX_AUDIOS||audios[idAudio]==NULL) throw CPigErroIndice(idAudio,"audios");
    return audios[idAudio];
}

static void CarregaBackground(std::string nomeArquivo){
    if (background)
        Mix_FreeMusic(background);
    background = Mix_LoadMUS(nomeArquivo.c_str());
}

static void PlayBackground(int nVezes){
    if (background){
        Mix_PlayMusic(background, nVezes);
        statusBackground = AUDIO_TOCANDO;
    }
}

static void StopBackground(){
    if (background){
        Mix_HaltMusic();
        statusBackground = AUDIO_PARADO;
    }
}

static void PauseBackground(){
    if (background){
        Mix_PauseMusic();
        statusBackground = AUDIO_PAUSADO;
    }
}

static void ResumeBackground(){
    if (background){
        Mix_ResumeMusic();
        statusBackground = AUDIO_TOCANDO;
    }
}

static PIG_StatusAudio GetStatusBackground(){
    return statusBackground;
}

static void SetVolumeBackground(int valor){
    volumeBackground = valor;
    Mix_VolumeMusic(volumeBackground);
}

static int GetVolumeBackground(){
    return volumeBackground;
}

static int CriaAudio(std::string nomeArquivo,int nLoops,int tempoExecucao=-1){
    int resp = numAudios->RetiraLivre();
    audios[resp] = new CAudio(nomeArquivo,nLoops,tempoExecucao);
    totalAudios++;
    return resp;
}

static void DestroiAudio(int idAudio){
    if (idAudio<0||idAudio>=totalAudios||audios[idAudio]==NULL) throw CPigErroIndice(idAudio,"audios");
    numAudios->DevolveUsado(idAudio);
    delete audios[idAudio];
    totalAudios--;
    audios[idAudio] = NULL;
}

inline static void SetVolume(int idAudio,int volume){
    GetAudio(idAudio)->SetVolume(volume);
}

inline static int GetVolume(int idAudio){
    return GetAudio(idAudio)->GetVolume();
}

inline static void SetVolumeTudo(int volume){
    Mix_Volume(-1,volume);
    for (int i=0;i<MAX_AUDIOS;i++)
        if (audios[i])
            audios[i]->SetVolume(volume);
}

inline static void Play(int idAudio){
    Audio audio = GetAudio(idAudio);
    audio->Play();
    audioIds[audio->GetCanal()] = idAudio;
}

inline static void Pause(int idAudio){
    GetAudio(idAudio)->Pause();
}

inline static void Resume(int idAudio){
    GetAudio(idAudio)->Resume();
}

inline static void Stop(int idAudio){
    GetAudio(idAudio)->Stop();
}

inline static PIG_StatusAudio GetStatus(int idAudio){
    return GetAudio(idAudio)->GetStatus();
}

inline static void StopTudo(){
    Mix_HaltChannel(-1);
    for (int i=0;i<MAX_AUDIOS;i++){
        if (audios[i]){
            audios[i]->Stop();
        }
    }
}

inline static void PauseTudo(){
    Mix_Pause(-1);
    for (int i=0;i<MAX_AUDIOS;i++){
        if (audios[i])
            audios[i]->Pause();
    }
}

inline static void ResumeTudo(){
    Mix_Resume(-1);
    for (int i=0;i<MAX_AUDIOS;i++){
        if (audios[i])
            audios[i]->Resume();
    }
}

};

Audio CGerenciadorAudios::audios[MAX_AUDIOS];
int CGerenciadorAudios::totalAudios;
PoolNumeros CGerenciadorAudios::numAudios;
int CGerenciadorAudios::audioIds[QTD_CANAIS_PADRAO];
Mix_Music *CGerenciadorAudios::background;
int CGerenciadorAudios::volumeBackground;
PIG_StatusAudio CGerenciadorAudios::statusBackground;
#endif // _CGERENCIADORAUDIOS_
