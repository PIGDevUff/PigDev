#ifndef _CPIGGERENCIADORAUDIOS_
#define _CPIGGERENCIADORAUDIOS_

#include "CPIGAudio.h"
class CPIGGerenciadorAudios{

private:
//static int totalAudios;
//static PIGPoolNumeros numAudios;
//static PIGAudio audios[MAX_AUDIOS];
/*static std::vector<int> posLivres;
static std::unordered_map<int,PIGAudio> audios;
static std::unordered_map<int,PIGAudio>::iterator it;
*/
static CPIGRepositorio<PIGAudio> *audios;

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

    /*totalAudios = 0;
    for (int i=0;i<MAX_AUDIOS;i++){
        audios[i] = NULL;
    }*/
    /*for (int i=0;i<MAX_AUDIOS;i++)
        posLivres.push_back(i);
*/
    audios = new CPIGRepositorio<PIGAudio>(MAX_AUDIOS,"audios");
    for (int i=0;i<QTD_CANAIS_PADRAO;i++){
        audioIds[i] = -1;
    }
    //numAudios = new CPIGPoolNumeros(MAX_AUDIOS);

    Mix_ChannelFinished(TrataParadaAudio);
    background = NULL;
    volumeBackground = VOLUME_PADRAO;
    statusBackground = AUDIO_PARADO;
    Mix_HookMusicFinished(TrataParadaBackground);
}

static void Encerra(){
    StopTudo();
    /*for (int i=0;i<MAX_AUDIOS;i++){
        if (audios[i]) delete audios[i];
    }
    delete numAudios;*/
    /*for(it = audios.begin(); it != audios.end(); ++it) {
        delete it->second;
    }*/
    delete audios;
    if (background)
        Mix_FreeMusic(background);
    Mix_CloseAudio();
}

inline static PIGAudio GetAudio(int idAudio){
    /*if (idAudio<0||idAudio>=MAX_AUDIOS||audios[idAudio]==NULL) throw CPIGErroIndice(idAudio,"audios");
    return audios[idAudio];*/
    /*it = audios.find(idAudio);
    if (it==audios.end()) throw CPIGErroIndice(idAudio,"audios");
    return it->second;*/
    return audios->GetElemento(idAudio);
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
    /*int resp = numAudios->RetiraLivre();
    audios[resp] = new CPIGAudio(nomeArquivo,nLoops,tempoExecucao);
    totalAudios++;
    return resp;*/
    /*int resp = posLivres[0];
    posLivres.erase(posLivres.begin());
    audios[resp] = new CPIGAudio(nomeArquivo,nLoops,tempoExecucao);
    return resp;*/
    return audios->Insere(new CPIGAudio(nomeArquivo,nLoops,tempoExecucao));
}

static void DestroiAudio(int idAudio){
    /*if (idAudio<0||idAudio>=totalAudios||audios[idAudio]==NULL) throw CPIGErroIndice(idAudio,"audios");
    numAudios->DevolveUsado(idAudio);
    delete audios[idAudio];
    totalAudios--;
    audios[idAudio] = NULL;*/
    /*PIGAudio audio = GetAudio(idAudio);
    delete audio;
    audios.erase(idAudio);*/
    audios->Remove(idAudio);
}

/*inline static void SetVolume(int idAudio,int volume){
    GetAudio(idAudio)->SetVolume(volume);
}

inline static int GetVolume(int idAudio){
    return GetAudio(idAudio)->GetVolume();
}*/

inline static void SetVolumeTudo(int volume){
    Mix_Volume(-1,volume);
    /*for (int i=0;i<MAX_AUDIOS;i++)
        if (audios[i])
            audios[i]->SetVolume(volume);*/
    /*for(it = audios.begin(); it != audios.end(); ++it) {
        it->second->SetVolume(volume);
    }*/
}

inline static void Play(int idAudio){
    PIGAudio audio = GetAudio(idAudio);
    audio->Play();
    audioIds[audio->GetCanal()] = idAudio;
}

/*inline static void Pause(int idAudio){
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
}*/

inline static void StopTudo(){
    Mix_HaltChannel(-1);
    /*for (int i=0;i<MAX_AUDIOS;i++){
        if (audios[i]){
            audios[i]->Stop();
        }
    }*/
    PIGAudio audio = audios->GetPrimeiroElemento();
    while (audio){
        audio->Stop();
        audio = audios->GetProximoElemento();

    }
    /*for(it = audios.begin(); it != audios.end(); ++it) {
        it->second->Stop();
    }*/
}

inline static void PauseTudo(){
    Mix_Pause(-1);
    /*for (int i=0;i<MAX_AUDIOS;i++){
        if (audios[i])
            audios[i]->Pause();
    }*/
    /*for(it = audios.begin(); it != audios.end(); ++it) {
        it->second->Pause();
    }*/
    PIGAudio audio = audios->GetPrimeiroElemento();
    while (audio){
        audio->Pause();
        audio = audios->GetProximoElemento();

    }
}

inline static void ResumeTudo(){
    Mix_Resume(-1);
    /*for (int i=0;i<MAX_AUDIOS;i++){
        if (audios[i])
            audios[i]->Resume();
    }*/
    /*for(it = audios.begin(); it != audios.end(); ++it) {
        it->second->Resume();
    }*/
    PIGAudio audio = audios->GetPrimeiroElemento();
    while (audio){
        audio->Resume();
        audio = audios->GetProximoElemento();
    }
}

};
CPIGRepositorio<PIGAudio> *CPIGGerenciadorAudios::audios;
/*std::vector<int> CPIGGerenciadorAudios::posLivres;
std::unordered_map<int,PIGAudio> CPIGGerenciadorAudios::audios;
std::unordered_map<int,PIGAudio>::iterator CPIGGerenciadorAudios::it;*/
//PIGAudio CPIGGerenciadorAudios::audios[MAX_AUDIOS];
//int CPIGGerenciadorAudios::totalAudios;
//PIGPoolNumeros CPIGGerenciadorAudios::numAudios;
int CPIGGerenciadorAudios::audioIds[QTD_CANAIS_PADRAO];
Mix_Music *CPIGGerenciadorAudios::background;
int CPIGGerenciadorAudios::volumeBackground;
PIG_StatusAudio CPIGGerenciadorAudios::statusBackground;
#endif // _CPIGGERENCIADORAUDIOS_
