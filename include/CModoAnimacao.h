//struct com aqs informaçõesde cada estágio (frame) do modo
typedef struct{
    int frame;      //número do frame
    double tempo;   //tempo de exibição do frame
    int audio;      //audio a ser tocado quando o frame for exibido
}EstagioAnimacao;

class CModoAnimacao{

private:

int frameAtual;                         //número do frame atual
bool loop;                              //se o modo tem loop ou não
bool encerrou;                          //indica se o modo terminou de eibir todos os frames
std::vector<EstagioAnimacao> estagios;  //informações dos estágios (frames) que compõem o modo

public:

    //construtor do modo
    CModoAnimacao(bool emLoop=true){
        frameAtual = 0;
        loop = emLoop;
        encerrou = false;
    }

    //destrutor
    ~CModoAnimacao(){
        estagios.clear();
    }

    //cria um novo estágio (frame)
    int InsereEstagio(int idFrame, double tempo, int idAudio){
        EstagioAnimacao estagio={idFrame,tempo,idAudio};
        estagios.push_back(estagio);
        return estagios.size()-1;
    }

    //define o tempo de um estágio (frame) já criado
    void SetTempo(int idEstagio, double novoTempo){
        estagios[idEstagio].tempo = novoTempo;
    }

    //define o audio de um estágio (frame) já criado
    void SetAudio(int idEstagio, int idAudio){
        estagios[idEstagio].audio = idAudio;
    }

    //define se o modo estraáem loop ou não
    void SetLoop(bool emLoop){
        loop = emLoop;
    }

    //retorna se o modo está em loop ou não
    bool GetLoop(){
        return loop;
    }

    //muda arbitrariamente o índice (posição da sequência de frames) do frame a ser exibido
    void SetIndiceFrameAtual(int indice){
        if (indice<frameAtual)
            encerrou = false;
        frameAtual = indice;
    }

    //retorna o índice (posiçãod o vetor) do frame atual
    int GetIndiceFrameAtual(){
        return frameAtual;
    }

    //retorna o número do frame atual
    int GetFrameAtual(){
        return estagios[frameAtual].frame;
    }

    //retorna o audio do frame atual
    int GetAudioAtual(){
        return estagios[frameAtual].audio;
    }

    //retorna o tempo de exibição do frame atual
    double GetTempoAtual(){
        return estagios[frameAtual].tempo;
    }

    //retorna o audio de um frame já criado (pelo seu índice no vetor)
    int GetAudioFrame(int indiceFrame){
        return estagios[indiceFrame].audio;
    }

    //retorna o tempo de um frame já criado (pelo seu índice no vetor)
    double GetTempoFrame(int indiceFrame){
        return estagios[indiceFrame].tempo;
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
    bool GetEncerrou(){
        return encerrou;
    }

};

typedef CModoAnimacao *ModoAnimacao;
