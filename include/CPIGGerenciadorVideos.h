#ifndef _CPIGGERENCIADORVIDEOS_
#define _CPIGGERENCIADORVIDEOS_

#include "CPIGVideo.h"

class CPIGGerenciadorVideos{

private:

//static int totalVideos;
static std::vector<int> posLivres;
static std::unordered_map<int,PIGVideo> videos;
static std::unordered_map<int,PIGVideo>::iterator it;

public:

static void Inicia(){
    av_register_all();
    avcodec_register_all();
    avdevice_register_all();
    avformat_network_init();

    /*totalVideos = 0;
    for (int i=0;i<MAX_VIDEOS;i++)
        videos[i] = NULL;
    numVideos = new CPIGPoolNumeros(MAX_VIDEOS);*/
    for (int i=0;i<MAX_VIDEOS;i++)
        posLivres.push_back(i);
}

static void Encerra(){
    /*for (int i=0;i<MAX_VIDEOS;i++){
        if (videos[i]) delete videos[i];
    }
    delete numVideos;*/
    for(it = videos.begin(); it != videos.end(); ++it) {
        delete it->second;
    }
    avformat_network_deinit();
}

static int CriaVideo(std::string nomeArquivo,int idJanela=0){
    /*int resp = numVideos->RetiraLivre();
    videos[resp] = new CPIGVideo(nomeArquivo,idJanela);
    totalVideos++;
    return resp;*/
    int resp = posLivres[0];
    posLivres.erase(posLivres.begin());
    videos[resp] = new CPIGVideo(nomeArquivo,idJanela);
    return resp;
}

static void DestroiVideo(int idVideo){
    /*numVideos->DevolveUsado(idVideo);
    delete videos[idVideo];
    totalVideos--;
    videos[idVideo] = NULL;*/
    PIGVideo video = GetVideo(idVideo);
    delete video;
    videos.erase(idVideo);
}

static PIGVideo GetVideo(int idVideo){
    /*if (idVideo<0||idVideo>=MAX_VIDEOS||videos[idVideo]==NULL) throw CPIGErroIndice(idVideo,"videos");
    return videos[idVideo];*/
    it = videos.find(idVideo);
    if (it==videos.end()) throw CPIGErroIndice(idVideo,"video");
    return it->second;
}

};

//int CPIGGerenciadorVideos::totalVideos;
//PIGPoolNumeros CPIGGerenciadorVideos::numVideos;
//PIGVideo CPIGGerenciadorVideos::videos[MAX_VIDEOS];
std::vector<int> CPIGGerenciadorVideos::posLivres;
std::unordered_map<int,PIGVideo> CPIGGerenciadorVideos::videos;
std::unordered_map<int,PIGVideo>::iterator CPIGGerenciadorVideos::it;
#endif // _CPIGGERENCIADORVIDEOS_
