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

    janelas[qtdJanelas++] = new CJanela(nome,qtdJanelas,altura,largura);
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
    janelas[qtdJanelas++] = new CJanela(nome,qtdJanelas,altura,largura);
    return qtdJanelas-1;//foi incrmentada log acima
}

static void FechaJanela(int idJanela){
    GetJanela(idJanela)->Fecha();
}

static void EscondeJanela(int idJanela){
    GetJanela(idJanela)->Esconde();
}

static void ExibeJanela(int idJanela){
    GetJanela(idJanela)->Exibe();
}

static void GanhaFocoJanela(int idJanela){
    GetJanela(idJanela)->GanhaFoco();
}

inline static Janela GetJanela(int idJanela){
    if (idJanela<0||idJanela>=qtdJanelas||janelas[idJanela]==NULL) throw CPigErroIndice(idJanela,"janelas");
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

static int GetAltura(int idJanela=0){
    return GetJanela(idJanela)->GetAltura();
}

static int GetLargura(int idJanela=0){
    return GetJanela(idJanela)->GetLargura();
}

static int SetTamanho(int altura,int largura,int idJanela=0){
    GetJanela(idJanela)->SetTamanho(altura,largura);
}

static std::string GetTitulo(int idJanela=0){
    return GetJanela(idJanela)->GetTitulo();
}

static void SetTitulo(std::string novoTitulo,int idJanela=0){
    GetJanela(idJanela)->SetTitulo(novoTitulo);
}

static PIG_Cor GetCorFundo(int idJanela=0){
    return GetJanela(idJanela)->GetCorFundo();
}

static void SetCorFundo(PIG_Cor cor,int idJanela=0){
    GetJanela(idJanela)->SetCorFundo(cor);
}

static float GetOpacidade(int idJanela=0){
    return GetJanela(idJanela)->GetOpacidade();
}

static void SetOpacidade(float valor,int idJanela=0){
    GetJanela(idJanela)->SetOpacidade(valor);
}

static void SetPosicao(int x,int y,int idJanela=0){
    GetJanela(idJanela)->SetPosicao(x,y);
}

static void GetPosicao(int *x,int *y,int idJanela=0){
    GetJanela(idJanela)->GetPosicao(x,y);
}

static void SetBorda(int valor,int idJanela=0){
    GetJanela(idJanela)->SetBorda(valor);
}

static void SetModo(int modo,int idJanela=0){
    GetJanela(idJanela)->SetModo(modo);
}

static int GetModo(int idJanela=0){
    return GetJanela(idJanela)->GetModo();
}

static void DesenhaRetangulo(int x, int y, int alturaRet, int larguraRet, PIG_Cor cor, int idJanela=0){
    GetJanela(idJanela)->DesenhaRetangulo(x,y,alturaRet,larguraRet,cor);
}

static void DesenhaRetanguloVazado(int x, int y, int alturaRet, int larguraRet, PIG_Cor cor, int idJanela=0){
    GetJanela(idJanela)->DesenhaRetanguloVazado(x,y,alturaRet,larguraRet,cor);
}

static void DesenhaLinhaSimples(int x1,int y1,int x2,int y2,PIG_Cor cor,int idJanela=0){
    GetJanela(idJanela)->DesenhaLinhaSimples(x1,y1,x2,y2,cor);
}

static void DesenhaLinhasDisjuntas(int *x,int *y,int qtd,PIG_Cor cor,int idJanela=0){
    GetJanela(idJanela)->DesenhaLinhasDisjuntas(x,y,qtd,cor);
}

static void DesenhaLinhasSequencia(int *x,int *y,int qtd,PIG_Cor cor,int idJanela=0){
    GetJanela(idJanela)->DesenhaLinhasSequencia(x,y,qtd,cor);
}

static PIG_Cor GetPixel(int x, int y, int idJanela=0){
    return GetJanela(idJanela)->GetPixel(x,y);
}

};

int CGerenciadorJanelas::qtdJanelas;
Janela CGerenciadorJanelas::janelas[MAX_JANELAS];
