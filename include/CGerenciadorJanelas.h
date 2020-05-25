#include "CJanela.h"
class CGerenciadorJanelas{

private:

static int qtdJanelas;
static Janela janelas[MAX_JANELAS];

public:


static void Inicia(std::string nome,int altura=ALT_TELA,int largura=LARG_TELA){
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

static int CriaJanela(std::string nome,int altura=ALT_TELA,int largura=LARG_TELA){
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

static void DefineFundo(std::string nomeArquivo,int idJanela=0){
    janelas[idJanela]->DefineFundo(nomeArquivo);
}

static void SaveScreenshotBMP(std::string nomeArquivo,int idJanela=0) {
    janelas[idJanela]->SaveScreenshot(nomeArquivo,true);//true == bitmap
}

static void SaveScreenshotPNG(std::string nomeArquivo,int idJanela=0) {
    janelas[idJanela]->SaveScreenshot(nomeArquivo,false);//false == PNG
}

static int GetAltura(int idJanela=0){
    return janelas[idJanela]->GetAltura();
}

static int GetLargura(int idJanela=0){
    return janelas[idJanela]->GetLargura();
}

static int SetTamanho(int altura,int largura,int idJanela=0){
    janelas[idJanela]->SetTamanho(altura,largura);
}

static std::string GetTitulo(int idJanela=0){
    return janelas[idJanela]->GetTitulo();
}

static void SetTitulo(std::string novoTitulo,int idJanela=0){
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

static void DesenhaRetangulo(int x, int y, int alturaRet, int larguraRet, PIG_Cor cor, int idJanela=0){
    janelas[idJanela]->DesenhaRetangulo(x,y,alturaRet,larguraRet,cor);
}

static void DesenhaRetanguloVazado(int x, int y, int alturaRet, int larguraRet, PIG_Cor cor, int idJanela=0){
    janelas[idJanela]->DesenhaRetanguloVazado(x,y,alturaRet,larguraRet,cor);
}

static void DesenhaLinhaSimples(int x1,int y1,int x2,int y2,PIG_Cor cor,int idJanela=0){
    janelas[idJanela]->DesenhaLinhaSimples(x1,y1,x2,y2,cor);
}

static void DesenhaLinhasDisjuntas(int *x,int *y,int qtd,PIG_Cor cor,int idJanela=0){
    janelas[idJanela]->DesenhaLinhasDisjuntas(x,y,qtd,cor);
}

static void DesenhaLinhasSequencia(int *x,int *y,int qtd,PIG_Cor cor,int idJanela=0){
    janelas[idJanela]->DesenhaLinhasSequencia(x,y,qtd,cor);
}

static PIG_Cor GetPixel(int x, int y, int idJanela=0){
    return janelas[idJanela]->GetPixel(x,y);
}

};

int CGerenciadorJanelas::qtdJanelas;
Janela CGerenciadorJanelas::janelas[MAX_JANELAS];
