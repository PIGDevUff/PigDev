#include "CMapaCaracteres.h"
#include "CMapaCaracteresDinamicos.h"
class CGerenciadorFontes{

private:
    static int totalFontes;
    static PoolNumeros numFontes;
    static MapaCaracteres fontes[MAX_FONTES];
    CGerenciadorFontes(){}

public:

    static MapaCaracteres GetFonte(int idFonte){
        return fontes[idFonte];
    }

    static void Inicia(){
        TTF_Init();

        fontes[0] = new CMapaCaracteres(PIG_FONTE_PADRAO_NOME,PIG_FONTE_PADRAO_TAM,ESTILO_NORMAL,PIG_FONTE_PADRAO_COR,0,BRANCO,0);
        //fontes[0] = new CMapaCaracteresDinamicos("..//fontes//arial.ttf",36,0);
        totalFontes = 1;

        for (int i=1;i<MAX_FONTES;i++)
            fontes[i] = NULL;

        numFontes = new CPoolNumeros(MAX_FONTES);
    }

    static void Encerra(){
        for (int i=0;i<MAX_FONTES;i++){
            if (fontes[i]) delete fontes[i];
        }
        delete numFontes;

        TTF_Quit();
    }

    static int CriaFonteFundo(char *nome,int tamanho,int estilo,char *arquivoFundo,int contorno,PIG_Cor corContorno,int idJanela=0){
        int resp = numFontes->RetiraLivre();
        fontes[resp] = new CMapaCaracteres(nome,tamanho,estilo,arquivoFundo,contorno,corContorno,idJanela);
        totalFontes++;
        return resp;
    }

    static int CriaFonteNormal(char *nome,int tamanho,int estilo,PIG_Cor corLetra,int contorno,PIG_Cor corContorno,int idJanela=0){
        int resp = numFontes->RetiraLivre();
        fontes[resp] = new CMapaCaracteres(nome,tamanho,estilo,corLetra,contorno,corContorno,idJanela);
        totalFontes++;
        return resp;
    }

    static int CriaFonteDinamica(char *nome,int tamanho,int idJanela=0){
        int resp = numFontes->RetiraLivre();
        fontes[resp] = new CMapaCaracteresDinamicos(nome,tamanho,idJanela);
        totalFontes++;
        return resp;
    }

    inline static int GetLarguraPixels(std::string texto,int numFonte=0){
        return fontes[numFonte]->GetLarguraPixelsString(texto);
    }

    inline static int GetFonteDescent(int numFonte=0){
        return fontes[numFonte]->GetFonteDescent();
    }

    inline static int GetFonteAscent(int numFonte=0){
        return fontes[numFonte]->GetFonteAscent();
    }

    inline static void EscreverCentralizada(std::string str,int x,int y,int numFonte=0,float angulo=0){
        fontes[numFonte]->EscreveStringCentralizado(str,x,y,angulo);
    }

    inline static void EscreverDireita(std::string str,int x,int y,int numFonte=0,float angulo=0){
        fontes[numFonte]->EscreveStringDireita(str,x,y,angulo);
    }

    inline static void EscreverEsquerda(std::string str,int x,int y,int numFonte=0,float angulo=0){
        fontes[numFonte]->EscreveStringEsquerda(str,x,y,angulo);
    }

    inline static void EscreverLongaCentralizada(std::string str,int x,int y,int largMax,int espacoEntreLinhas,int numFonte=0,float angulo=0){
        fontes[numFonte]->EscreveStringLongaCentralizado(str,x,y,largMax,espacoEntreLinhas,angulo);
    }

    inline static void EscreverLongaDireita(std::string str,int x,int y,int largMax,int espacoEntreLinhas,int numFonte=0,float angulo=0){
        fontes[numFonte]->EscreveStringLongaDireita(str,x,y,largMax,espacoEntreLinhas,angulo);
    }

    inline static void EscreverLongaEsquerda(std::string str,int x,int y,int largMax,int espacoEntreLinhas,int numFonte=0,float angulo=0){
        fontes[numFonte]->EscreveStringLongaEsquerda(str,x,y,largMax,espacoEntreLinhas,angulo);
    }


    inline static void EscreveInteiroEsquerda(int valor, int x, int y, int numFonte=0,float angulo=0){
        fontes[numFonte]->EscreveInteiroEsquerda(valor,x,y,angulo,0);
    }

    inline static void EscreveInteiroCentralizado(int valor, int x, int y, int numFonte=0, float angulo=0){
        fontes[numFonte]->EscreveInteiroCentralizado(valor,x,y,angulo);
    }

    inline static void EscreveInteiroDireita(int valor, int x, int y, int numFonte=0,float angulo=0){
        fontes[numFonte]->EscreveInteiroDireita(valor,x,y,angulo);
    }

    inline static void EscreveDoubleEsquerda(double valor, int casas, int x, int y, int numFonte=0,float angulo=0){
        fontes[numFonte]->EscreveDoubleEsquerda(valor,x,y,angulo,0);
    }

    inline static void EscreveDoubleCentralizado(double valor, int casas, int x, int y, int numFonte=0,float angulo=0){
        fontes[numFonte]->EscreveDoubleCentralizado(valor,x,y,angulo);
    }

    inline static void EscreveDoubleDireita(double valor, int casas, int x, int y, int numFonte=0,float angulo=0){
        fontes[numFonte]->EscreveDoubleDireita(valor,x,y,angulo);
    }

    inline static std::vector<std::string> ExtraiLinhasString(std::string texto,int largMax,int numFonte=0){
        return fontes[numFonte]->ExtraiLinhas(texto,largMax);
    }

    inline static PIG_Metricas_Fonte GetMetricas(Uint16 letra, PIG_Estilo estilo=ESTILO_NORMAL, int numFonte=0){
        return fontes[numFonte]->GetMetricasLetra(letra,estilo);
    }


    inline static int GetLarguraLetra(char letra, PIG_Estilo estilo=ESTILO_NORMAL,int numFonte = 0){
        return fontes[numFonte]->GetLarguraLetra(letra,estilo);
    }

    inline static int GetTamanhoBaseFonte(int numFonte = 0){
        return fontes[numFonte]->GetTamanhoBaseFonte();
    }

    inline static int GetLineSkip(int numFonte=0){
        return fontes[numFonte]->GetLineSkip();
    }

    inline static SDL_Surface *GetGlyph(Uint16 *ch,PIG_Cor cor=BRANCO,int numFonte=0){
        return fontes[numFonte]->GetGlyph(ch,cor);
    }

    static void DestroiFonte(int idFonte){
        if (idFonte==0) return;             //a fonte padrao só é destruida quando o gerenciador for encerrado
        numFontes->DevolveUsado(idFonte);
        delete fontes[idFonte];
        totalFontes--;
        fontes[idFonte] = NULL;
    }

};

PoolNumeros CGerenciadorFontes::numFontes;
int CGerenciadorFontes::totalFontes;
MapaCaracteres CGerenciadorFontes::fontes[MAX_FONTES];
