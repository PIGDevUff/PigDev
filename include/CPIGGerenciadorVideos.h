#ifndef _CPIGGERENCIADORVIDEOS_
#define _CPIGGERENCIADORVIDEOS_

#include "CPIGVideo.h"

class CPIGGerenciadorVideos{

private:

    static CPIGRepositorio<PIGVideo> *videos;

public:

    inline static void Inicia(){
        av_register_all();
        avcodec_register_all();
        avdevice_register_all();
        avformat_network_init();

        videos = new CPIGRepositorio<PIGVideo>(PIG_MAX_VIDEOS,"videos");
    }

    inline static void Encerra(){
        delete videos;
        avformat_network_deinit();
    }

    inline static int CriaVideo(string nomeArquivo, int idJanela=0){
        return videos->Insere(new CPIGVideo(nomeArquivo,idJanela));
    }

    inline static int InsereVideo(PIGVideo video){
        return videos->Insere(video);
    }

    inline static void DestroiVideo(int idVideo){
        videos->Remove(idVideo);
    }

    inline static PIGVideo GetVideo(int idVideo){
        return videos->GetElemento(idVideo);
    }

};
CPIGRepositorio<PIGVideo> *CPIGGerenciadorVideos::videos;
#endif // _CPIGGERENCIADORVIDEOS_
