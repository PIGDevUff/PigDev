#ifndef _CPIGGerenciadorJanelas_
#define _CPIGGerenciadorJanelas_

#include "CPIGJanela.h"
class CPIGGerenciadorJanelas{

private:

static int qtdJanelas;
static PIGJanela janelas[MAX_JANELAS];

public:

static void Inicia(std::string nome,int altura=ALT_TELA,int largura=LARG_TELA){
    qtdJanelas = 0;
    for (int i=0;i<MAX_JANELAS;i++)
        janelas[i] = NULL;

    janelas[qtdJanelas++] = new CPIGJanela(nome,qtdJanelas,altura,largura);
}

static void Encerra(){
    for (int i=0;i<qtdJanelas;i++)
        if (janelas[i]) delete janelas[i];
}

static int GetQtdJanelas(){
    int resp = qtdJanelas;
    for (int i=0;i<qtdJanelas;i++)
        if (GetJanela(i)->GetFechada()) resp--;
    return resp;
}

static int CriaJanela(std::string nome,int altura=ALT_TELA,int largura=LARG_TELA){
    if (qtdJanelas==MAX_JANELAS) return -1;
    janelas[qtdJanelas++] = new CPIGJanela(nome,qtdJanelas,altura,largura);
    return qtdJanelas-1;//foi incrmentada log acima
}

inline static PIGJanela GetJanela(int idJanela){
    if (idJanela<0||idJanela>=qtdJanelas||janelas[idJanela]==NULL) throw CPIGErroIndice(idJanela,"janelas");
    return janelas[idJanela];
}

static void IniciaDesenho(int idJanela=-1){
    if (idJanela>-1){
        GetJanela(idJanela)->IniciaDesenho();
    }else{
        for (int i=0;i<qtdJanelas;i++){
            GetJanela(i)->IniciaDesenho();
        }
    }
}

static void EncerraDesenho(int idJanela=-1){
    if (idJanela>-1){
        GetJanela(idJanela)->EncerraDesenho();
    }else{
        for (int i=0;i<qtdJanelas;i++){
            GetJanela(i)->EncerraDesenho();
        }
    }
}

static void DefineFundo(std::string nomeArquivo,int idJanela=0){
    GetJanela(idJanela)->DefineFundo(nomeArquivo);
}

static void SaveScreenshotBMP(std::string nomeArquivo,int idJanela=0) {
    GetJanela(idJanela)->SaveScreenshot(nomeArquivo,true);//true == bitmap
}

static void SaveScreenshotPNG(std::string nomeArquivo,int idJanela=0) {
    GetJanela(idJanela)->SaveScreenshot(nomeArquivo,false);//false == PNG
}


};

int CPIGGerenciadorJanelas::qtdJanelas;
PIGJanela CPIGGerenciadorJanelas::janelas[MAX_JANELAS];
#endif // _CPIGGerenciadorJanelas_
