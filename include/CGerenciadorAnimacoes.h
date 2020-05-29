#include "CAnimacao.h"
class CGerenciadorAnimacoes{

private:
    static int totalAnimacoes;
    static PoolNumeros numAnimacoes;
    static Animacao animacoes[MAX_ANIMACOES];

public:

    static Animacao GetAnimacao(int idAnimacao){
        return animacoes[idAnimacao];
    }

    static void Inicia(SDL_Renderer *renderer=NULL){
        totalAnimacoes = 0;
        for (int i=0;i<MAX_ANIMACOES;i++)
            animacoes[i] = NULL;
        numAnimacoes = new CPoolNumeros(MAX_ANIMACOES);
    }

    static void Encerra(){
        for (int i=0;i<MAX_ANIMACOES;i++){
            if (animacoes[i]) delete animacoes[i];
        }
        delete numAnimacoes;
    }

    static int CriaAnimacao(std::string nomeArquivoBMP,PIG_Cor *corFundo=NULL,int retiraFundo=1,int idJanela=0){
        int resp = numAnimacoes->RetiraLivre();
        animacoes[resp] = new CAnimacao(nomeArquivoBMP,0,corFundo,retiraFundo,idJanela);
        totalAnimacoes++;
        return resp;
    }

    static int CriaAnimacao(int idAnimacaoBase,PIG_Cor *corFundo=NULL,int retiraFundo=1,int idJanela=0){
        int resp = numAnimacoes->RetiraLivre();
        animacoes[resp] = new CAnimacao(animacoes[idAnimacaoBase],0,corFundo,retiraFundo,idJanela);
        totalAnimacoes++;
        return resp;
    }

    static void DestroiAnimacao(int idAnimacao){
        numAnimacoes->DevolveUsado(idAnimacao);
        delete animacoes[idAnimacao];
        totalAnimacoes--;
        animacoes[idAnimacao] = NULL;
    }

    inline static void Move(int idAnimacao,int px,int py){
        animacoes[idAnimacao]->Move(px,py);
    }

    inline static void Desloca(int idAnimacao,int dx,int dy){
        animacoes[idAnimacao]->Desloca(dx,dy);
    }

    inline static void GetPosicaoXY(int idAnimacao, int *x,int *y){
        animacoes[idAnimacao]->GetXY(*x,*y);
    }

    inline static int Desenha(int idAnimacao){
        return animacoes[idAnimacao]->Desenha();
    }

    inline static void CriaFrame(int idAnimacao,int codFrame,int x,int y,int altura,int largura){
        animacoes[idAnimacao]->CriaFrame(codFrame,x,y,altura,largura);
    }

    inline static void CriaModo(int idAnimacao,int idModo, int loop){
        animacoes[idAnimacao]->CriaModo(idModo,loop);
    }

    inline static void InsereFrame(int idAnimacao, int idModo,int idFrame, float delayFrame,int idAudio){
        animacoes[idAnimacao]->InsereFrame(idModo,idFrame,delayFrame,idAudio);
    }

    inline static int GetModo(int idAnimacao){
        return animacoes[idAnimacao]->GetModoAtual();
    }

    inline static void MudaModo(int idAnimacao,int idModo,int indiceFrame,int forcado){
        animacoes[idAnimacao]->MudaModo(idModo,indiceFrame,forcado);
    }

    inline static void SetOpacidade(int idAnimacao,int valor){
        animacoes[idAnimacao]->SetOpacidade(valor);
    }

    inline static int GetOpacidade(int idAnimacao){
        return animacoes[idAnimacao]->GetOpacidade();
    }

    inline static void SetColoracao(int idAnimacao,PIG_Cor cor){
        animacoes[idAnimacao]->SetColoracao(cor);
    }

    inline static void SetPivo(int idAnimacao,int x,int y){
        animacoes[idAnimacao]->SetPivo(x,y);
    }

    inline static void GetPivo(int idAnimacao,int *x,int *y){
        animacoes[idAnimacao]->GetPivo(*x,*y);
    }

    inline static void SetFlip(int idAnimacao, PIG_Flip valor){
        animacoes[idAnimacao]->SetFlip(valor);
    }

    inline static PIG_Flip GetFlip(int idAnimacao){
        return animacoes[idAnimacao]->GetFlip();
    }

    inline static void SetAngulo(int idAnimacao,float valor){
        animacoes[idAnimacao]->SetAngulo(valor);
    }

    inline static float GetAngulo(int idAnimacao){
        return animacoes[idAnimacao]->GetAngulo();
    }

    inline static int ColisaoAnimacoes(int idAnimacao1,int idAnimacao2){
        return animacoes[idAnimacao1]->Colisao(animacoes[idAnimacao2]);
    }

    inline static int ColisaoObjeto(int idAnimacao,Objeto obj){
        return animacoes[idAnimacao]->Colisao(obj);
    }

    inline static void SetDimensoes(int idAnimacao,int altura,int largura){
        animacoes[idAnimacao]->SetDimensoes(altura,largura);
    }

    inline static void GetDimensoes(int idAnimacao,int *altura,int *largura){
        animacoes[idAnimacao]->GetDimensoes(*altura,*largura);
    }

    inline static void SetValorIntAnimacao(int idAnimacao, int chave, int valor){
        animacoes[idAnimacao]->SetValoresInt(chave,valor);
    }

    inline static void SetValorIntAnimacao(int idAnimacao, std::string chave, int valor){
        animacoes[idAnimacao]->SetValoresInt(chave,valor);
    }

    inline static void SetValorFloatAnimacao(int idAnimacao, int chave, float valor){
        animacoes[idAnimacao]->SetValoresFloat(chave,valor);
    }

    inline static void SetValorFloatAnimacao(int idAnimacao, std::string chave, float valor){
        animacoes[idAnimacao]->SetValoresFloat(chave,valor);
    }

    inline static void SetValorStringAnimacao(int idAnimacao, int chave, std::string valor){
        animacoes[idAnimacao]->SetValoresString(chave,valor);
    }

    inline static void SetValorStringAnimacao(int idAnimacao, std::string chave, std::string valor){
        animacoes[idAnimacao]->SetValoresString(chave,valor);
    }

    inline static bool GetValorIntAnimacao(int idAnimacao, int indice, int *valor){
        return animacoes[idAnimacao]->GetValoresInt(indice,*valor);
    }

    inline static bool GetValorFloatAnimacao(int idAnimacao, int indice, float *valor){
        return animacoes[idAnimacao]->GetValoresFloat(indice,*valor);
    }

    inline static bool GetValorStringAnimacao(int idAnimacao, int indice, std::string &valor){
        return animacoes[idAnimacao]->GetValoresString(indice,valor);
    }

    inline static bool GetValorIntAnimacao(int idAnimacao, std::string indice, int *valor){
        return animacoes[idAnimacao]->GetValoresInt(indice,*valor);
    }

    inline static bool GetValorFloatAnimacao(int idAnimacao, std::string indice, float *valor){
        return animacoes[idAnimacao]->GetValoresFloat(indice,*valor);
    }

    inline static bool GetValorStringAnimacao(int idAnimacao, std::string indice, std::string &valor){
        return animacoes[idAnimacao]->GetValoresString(indice,valor);
    }

    inline static void PausaAnimacao(int idAnimacao){
        animacoes[idAnimacao]->Pausa();
    }

    inline static void DespausaAnimacao(int idAnimacao){
        animacoes[idAnimacao]->Despausa();
    }

    inline static void SetTempoFrameAnimacao(int idAnimacao, int idModo, int indiceFrame, double tempo){
        animacoes[idAnimacao]->SetTempoFrame(idModo,indiceFrame,tempo);
    }

    inline static void SetAudioFrameAnimacao(int idAnimacao, int idModo, int indiceFrame, int idAudio){
        animacoes[idAnimacao]->SetAudioFrame(idModo,indiceFrame,idAudio);
    }

    inline static void SetLoopModoAnimacao(int idAnimacao, int idModo, bool loop){
        animacoes[idAnimacao]->SetLoopModo(idModo,loop);
    }

    inline static double GetTempoFrameAnimacao(int idAnimacao, int idModo, int indiceFrame){
        return animacoes[idAnimacao]->GetTempoFrame(idModo,indiceFrame);
    }

    inline static bool GetLoopModoAnimacao(int idAnimacao, int idModo){
        return animacoes[idAnimacao]->GetLoopModo(idModo);
    }

    inline static int GetAudioFrameAnimacao(int idAnimacao, int idModo, int indiceFrame){
        return animacoes[idAnimacao]->GetAudioFrame(idModo,indiceFrame);
    }
};

PoolNumeros CGerenciadorAnimacoes::numAnimacoes;
int CGerenciadorAnimacoes::totalAnimacoes;
Animacao CGerenciadorAnimacoes::animacoes[MAX_ANIMACOES];

