#ifndef _CPIGMODOANIMACAO_
#define _CPIGMODOANIMACAO_

//struct com as informações de cada estágio (frame) do modo
typedef struct{
    int frame;      //número do frame
    double tempo;   //tempo de exibição do frame
    int audio;      //audio a ser tocado quando o frame for exibido
    int altura,largura;
}PIGEstagioAnimacao;

class CPIGModoAnimacao{

private:

    int frameAtual;                         //número do frame atual
    bool loop;                              //se o modo tem loop ou não
    bool encerrou;                          //indica se o modo terminou de eibir todos os frames
    vector<PIGEstagioAnimacao> estagios;    //informações dos estágios (frames) que compõem o modo

public:

    //construtor do modo
    CPIGModoAnimacao(bool emLoop=true){
        frameAtual = 0;
        loop = emLoop;
        encerrou = false;
    }

    CPIGModoAnimacao(CPIGModoAnimacao *modoBase){
        encerrou = modoBase->encerrou;
        estagios = modoBase->estagios;
        SetLoop(modoBase->loop);
        SetIndiceFrameAtual(modoBase->frameAtual);
    }

    //destrutor
    ~CPIGModoAnimacao(){
        estagios.clear();
    }

    //cria um novo estágio (frame)
    inline int InsereEstagio(int idFrame, double tempo, int idAudio, int altura, int largura){
        PIGEstagioAnimacao estagio={idFrame,tempo,idAudio,altura,largura};
        estagios.push_back(estagio);
        return estagios.size()-1;
    }

    //define o tempo de um estágio (frame) já criado
    inline void SetTempo(int idEstagio, double novoTempo){
        estagios[idEstagio].tempo = novoTempo;
    }

    //define o audio de um estágio (frame) já criado
    inline void SetAudio(int idEstagio, int idAudio){
        estagios[idEstagio].audio = idAudio;
    }

    //define se o modo estraáem loop ou não
    inline void SetLoop(bool emLoop){
        loop = emLoop;
    }

    //retorna se o modo está em loop ou não
    inline bool GetLoop(){
        return loop;
    }

    //muda arbitrariamente o índice (posição da sequência de frames) do frame a ser exibido
    inline void SetIndiceFrameAtual(int indice){
        if (indice<frameAtual)
            encerrou = false;
        frameAtual = indice;
    }

    //retorna o índice (posiçãod o vetor) do frame atual
    inline int GetIndiceFrameAtual(){
        return frameAtual;
    }

    //retorna o número do frame atual
    inline int GetFrameAtual(){
        return estagios[frameAtual].frame;
    }

    //retorna o audio do frame atual
    inline int GetAudioAtual(){
        return estagios[frameAtual].audio;
    }

    //retorna o tempo de exibição do frame atual
    inline double GetTempoAtual(){
        return estagios[frameAtual].tempo;
    }

    //retorna o audio de um frame já criado (pelo seu índice no vetor)
    inline int GetAudioFrame(int indiceFrame){
        return estagios[indiceFrame].audio;
    }

    //retorna o tempo de um frame já criado (pelo seu índice no vetor)
    inline double GetTempoFrame(int indiceFrame){
        return estagios[indiceFrame].tempo;
    }

    inline void GetDimensoesAtual(int &altura, int &largura){
        //if (estagios[frameAtual].altura < 0) return false;
        altura = estagios[frameAtual].altura;
        largura = estagios[frameAtual].largura;
        //return true;
    }

    //teste se já passou o tempo necessário para mudar de frame
    int TestaTempo(double tempoDecorrido){
        encerrou = false;
        if (estagios.size()==0) return 0;//nao foi criado nenhum estagio nesse modo
        int frameAntigo = frameAtual;//armazena o valor do frameAtual
        if (tempoDecorrido>=estagios[frameAtual].tempo){
            if (frameAtual < estagios.size()-1){//se ainda nao chegou no último estágio
                frameAtual++;
            }else{//chegou no último estágio
                if (loop)
                    frameAtual = 0;//se está em loop, volta ao primeiro frame
                else encerrou=true;
            }
        }
        return frameAtual!=frameAntigo;//retorna se alterou o frameAtual
    }

    //retorna se o modo já exibiu todos os frames (apenas se não estiver em loop)
    inline bool GetEncerrou(){
        return encerrou;
    }

};

typedef CPIGModoAnimacao *PIGModoAnimacao;
#endif // _CPIGMODOANIMACAO_
