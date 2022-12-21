#ifndef _CPIGGERENCIADORVIDEOS_
#define _CPIGGERENCIADORVIDEOS_

#include "CPIGVideo.h"
#include "CPIGRepositorio.h"

class CPIGGerenciadorVideos: public CPIGRepositorio<PIGVideo>{

public:

    CPIGGerenciadorVideos():CPIGRepositorio<PIGVideo>(PIG_MAX_VIDEOS,"CPIGVideo"){
        //av_register_all();
        //avcodec_register_all();
        avdevice_register_all();
        avformat_network_init();
    }

    ~CPIGGerenciadorVideos(){
        avformat_network_deinit();
    }

    inline int CriaVideo(string nomeArquivo, int idJanela=0){
        return Insere(new CPIGVideo(nomeArquivo,idJanela));
    }
};
CPIGGerenciadorVideos pigGerVideos;
#endif // _CPIGGERENCIADORVIDEOS_
