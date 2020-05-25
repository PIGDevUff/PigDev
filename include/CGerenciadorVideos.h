#include "CVideo.h"

class CGerenciadorVideos{

private:

static int totalVideos;
static PoolNumeros numVideos;
static Video videos[MAX_VIDEOS];

public:

static void Inicia(){
    av_register_all();
    avcodec_register_all();
    avdevice_register_all();
    avformat_network_init();

    totalVideos = 0;
    for (int i=0;i<MAX_VIDEOS;i++)
        videos[i] = NULL;
    numVideos = new CPoolNumeros(MAX_VIDEOS);
}

static void Encerra(){
    for (int i=0;i<MAX_VIDEOS;i++){
        if (videos[i]) delete videos[i];
    }
    delete numVideos;
    avformat_network_deinit();
}

static int CriaVideo(std::string nomeArquivo,int idJanela=0){
    int resp = numVideos->RetiraLivre();
    videos[resp] = new CVideo(nomeArquivo,idJanela);
    totalVideos++;
    return resp;
}

static void DestroiVideo(int idVideo){
    numVideos->DevolveUsado(idVideo);
    delete videos[idVideo];
    totalVideos--;
    videos[idVideo] = NULL;
}

static void SetSeek(int idVideo, double incremento){
    videos[idVideo]->SetSeek(incremento);
}

static void Play(int idVideo){
    videos[idVideo]->Play();
}

static void Stop(int idVideo){
    videos[idVideo]->Stop();
}

static void Pause(int idVideo){
    videos[idVideo]->Pause();
}

static void Resume(int idVideo){
    videos[idVideo]->Resume();
}

static int Desenha(int idVideo){
    videos[idVideo]->Desenha();
}

static void SetVolume(int idVideo, double valor){
    videos[idVideo]->SetVolume(valor);
}

static double GetVolume(int idVideo){
    return videos[idVideo]->GetVolume();
}

static std::string GetNomeArquivo(int idVideo){
    return videos[idVideo]->GetNomeArquivo();
}

static double GetTempoAtual(int idVideo){
    return videos[idVideo]->GetTempoAtual();
}

static std::string GetTempoAtualString(int idVideo){
    return videos[idVideo]->GetTempoAtualString();
}

static double GetTempoTotal(int idVideo){
    return videos[idVideo]->GetTempoTotal();
}

static std::string GetTempoTotalString(int idVideo){
    return videos[idVideo]->GetTempoTotalString();
}

static double GetTempoFrame(int idVideo){
    return videos[idVideo]->GetTempoFrame();
}

static double GetFPS(int idVideo){
    return videos[idVideo]->GetFPS();
}

static void SetAngulo(int idVideo, float a){
    videos[idVideo]->SetAngulo(a);
}

static double GetAngulo(int idVideo){
    return videos[idVideo]->GetAngulo();
}

static void SetFlip(int idVideo, PIG_Flip valor){
    videos[idVideo]->SetFlip(valor);
}

static PIG_Flip GetFlip(int idVideo){
    return videos[idVideo]->GetFlip();
}

static void SetPivo(int idVideo, int px,int py){
    videos[idVideo]->SetPivo(px,py);
}

static void SetPivo(int idVideo, float px,float py){
    videos[idVideo]->SetPivo(px,py);
}

static void GetPivo(int idVideo, int &px,int &py){
    videos[idVideo]->GetPivo(px,py);
}

static void Move(int idVideo, int nx,int ny){
    videos[idVideo]->Move(nx,ny);
}

static void SetDimensoes(int idVideo, int altura,int largura){
    videos[idVideo]->SetDimensoes(altura,largura);
}

static void GetDimensoes(int idVideo, int &altura, int &largura){
    videos[idVideo]->GetDimensoes(altura,largura);
}

static void GetDimensoesOriginais(int idVideo, int &altura,int &largura){
    videos[idVideo]->GetDimensoesOriginais(altura,largura);
}

static void OcupaJanelaInteira(int idVideo){
    videos[idVideo]->OcupaJanelaInteira();
}

static void UsaResolucaoOriginal(int idVideo){
    videos[idVideo]->UsaResolucaoOriginal();
}

static void SetColoracao(int idVideo, PIG_Cor cor){
    videos[idVideo]->SetColoracao(cor);
}

static void SetOpacidade(int idVideo, int valor){
    videos[idVideo]->SetOpacidade(valor);
}

static int GetOpacidade(int idVideo){
    return videos[idVideo]->GetOpacidade();
}

};

int CGerenciadorVideos::totalVideos;
PoolNumeros CGerenciadorVideos::numVideos;
Video CGerenciadorVideos::videos[MAX_VIDEOS];
