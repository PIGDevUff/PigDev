#ifndef _CPIGGERENCIADORVIDEOS_
#define _CPIGGERENCIADORVIDEOS_

#include "CPIGVideo.h"

class CPIGGerenciadorVideos{

private:

static CPIGRepositorio<PIGVideo> *videos;
public:

static void Inicia(){
    av_register_all();
    avcodec_register_all();
    avdevice_register_all();
    avformat_network_init();

    videos = new CPIGRepositorio<PIGVideo>(PIG_MAX_VIDEOS,"videos");
}

static void Encerra(){
    delete videos;
    avformat_network_deinit();
}

static int CriaVideo(string nomeArquivo, int idJanela=0){
    return videos->Insere(new CPIGVideo(nomeArquivo,idJanela));
}

static void DestroiVideo(int idVideo){
    videos->Remove(idVideo);
}

static PIGVideo GetVideo(int idVideo){
    return videos->GetElemento(idVideo);
}

};
CPIGRepositorio<PIGVideo> *CPIGGerenciadorVideos::videos;
#endif // _CPIGGERENCIADORVIDEOS_
