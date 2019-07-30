#include "CJanela.h"
class CGerenciadorJanelas{

private:

static int qtdJanelas;
static Janela janelas[MAX_JANELAS];

public:


static void Inicia(char *nome,int altura=ALT_TELA,int largura=LARG_TELA){
    qtdJanelas = 0;
    for (int i=0;i<MAX_JANELAS;i++)
        janelas[i] = NULL;
    //printf("vai criar janela (%d)\n",qtdJanelas);
    janelas[qtdJanelas++] = new CJanela(nome,qtdJanelas,altura,largura);
    //printf("criada janela (%d)\n",qtdJanelas-1);
}

static void Encerra(){
    for (int i=0;i<qtdJanelas;i++)
        delete janelas[i];
}

static int GetQtdJanelas(){
    int resp = qtdJanelas;
    for (int i=0;i<qtdJanelas;i++)
        if (janelas[i]->GetFechada()) resp--;
    return resp;
}

static int CriaJanela(char *nome,int altura=ALT_TELA,int largura=LARG_TELA){
    if (qtdJanelas==MAX_JANELAS) return -1;
    janelas[qtdJanelas++] = new CJanela(nome,qtdJanelas,altura,largura);
    return qtdJanelas-1;//foi incrmentada log acima
}

static void FechaJanela(int idJanela){
    janelas[idJanela]->Fecha();
}

static void EscondeJanela(int idJanela){
    janelas[idJanela]->Esconde();
}

static void ExibeJanela(int idJanela){
    janelas[idJanela]->Exibe();
}

static void GanhaFocoJanela(int idJanela){
    janelas[idJanela]->GanhaFoco();
}

static Janela GetJanela(int idJanela){
    return janelas[idJanela];
}

static void IniciaDesenho(int idJanela=-1){
    if (idJanela>-1)
        janelas[idJanela]->IniciaDesenho();
    else{
        for (int i=0;i<qtdJanelas;i++){
            janelas[i]->IniciaDesenho();
        }
    }
}

static void EncerraDesenho(int idJanela=-1){
    if (idJanela>-1)
        janelas[idJanela]->EncerraDesenho();
    else{
        for (int i=0;i<qtdJanelas;i++){
            janelas[i]->EncerraDesenho();
        }
    }
}

static void DefineFundo(char *nomeArquivo,int idJanela=0){
    janelas[idJanela]->DefineFundo(nomeArquivo);
}

static void SaveScreenshotBMP(char *nomeArquivo,int idJanela=0) {
    janelas[idJanela]->SaveScreenshotBMP(nomeArquivo);
}

static int GetAltura(int idJanela=0){
    return janelas[idJanela]->GetAltura();
}

static int GetLargura(int idJanela=0){
    return janelas[idJanela]->GetLargura();
}

static void GetTitulo(char *tituloJanela,int idJanela=0){
    janelas[idJanela]->GetTitulo(tituloJanela);
}

static void SetTitulo(char *novoTitulo,int idJanela=0){
    janelas[idJanela]->SetTitulo(novoTitulo);
}

static PIG_Cor GetCorFundo(int idJanela=0){
    return janelas[idJanela]->GetCorFundo();
}

static void SetCorFundo(PIG_Cor cor,int idJanela=0){
    janelas[idJanela]->SetCorFundo(cor);
}

static float GetOpacidade(int idJanela=0){
    return janelas[idJanela]->GetOpacidade();
}

static void SetOpacidade(float valor,int idJanela=0){
    janelas[idJanela]->SetOpacidade(valor);
}

static void SetPosicao(int x,int y,int idJanela=0){
    janelas[idJanela]->SetPosicao(x,y);
}

static void GetPosicao(int *x,int *y,int idJanela=0){
    janelas[idJanela]->GetPosicao(x,y);
}

static void SetBorda(int valor,int idJanela=0){
    janelas[idJanela]->SetBorda(valor);
}

static void SetModo(int modo,int idJanela=0){
    janelas[idJanela]->SetModo(modo);
}

static int GetModo(int idJanela=0){
    return janelas[idJanela]->GetModo();
}

};

int CGerenciadorJanelas::qtdJanelas;
Janela CGerenciadorJanelas::janelas[MAX_JANELAS];
