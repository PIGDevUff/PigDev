#ifndef _CPIGIcone_
#define _CPIGIcone_

class CPIGIcone:public CPigVisual{


private:


public:

    CPIGIcone(std::string nomeArquivo,int retiraFundo=1,int idJanela=0):
        CPigVisual(nomeArquivo,retiraFundo,NULL,idJanela){
    }

    void Desenha(){
        SDL_RenderCopyEx(renderer,text,&frame,&dest,angulo,&pivoRelativo,flip);
    }

};

typedef CPIGIcone *PIGIcone;
#endif //_CPIGIcone_
