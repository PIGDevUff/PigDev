#ifndef _CPIGCursor_
#define _CPIGCursor_

class CPIGCursor:public CVisual{


private:


public:

    CPIGCursor(std::string nomeArquivo,int retiraFundo=1,int idJanela=0):
        CVisual(nomeArquivo,retiraFundo,NULL,idJanela){
    }

    void Desenha(){
        SDL_RenderCopy(renderer,text,NULL,&dest);
    }

};

typedef CPIGCursor *PIGCursor;
#endif //_CPIGCursor_
