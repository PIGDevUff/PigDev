#ifndef _CGERENCIADORFONTES_
#define _CGERENCIADORFONTES_

#include "CMapaCaracteres.h"
#include "CMapaCaracteresDinamicos.h"

class CGerenciadorFontes{

private:
    static int totalFontes;
    static PoolNumeros numFontes;
    static MapaCaracteres fontes[MAX_FONTES];

public:

    static MapaCaracteres GetFonte(int idFonte){
        return fontes[idFonte];
    }

    static void Inicia(){
        TTF_Init();

        fontes[0] = new CMapaCaracteres(PIG_FONTE_PADRAO_NOME,PIG_FONTE_PADRAO_TAM,ESTILO_NORMAL,PIG_FONTE_PADRAO_COR,0);
        //fontes[0] = new CMapaCaracteres(PIG_FONTE_PADRAO_NOME,PIG_FONTE_PADRAO_TAM,ESTILO_NORMAL,PIG_FONTE_PADRAO_COR,0,VERDE,0);
        //fontes[0] = new CMapaCaracteres(PIG_FONTE_PADRAO_NOME,PIG_FONTE_PADRAO_TAM,ESTILO_NORMAL,"desenho.bmp",0,BRANCO,0);
        //fontes[0] = new CMapaCaracteresDinamicos("..//fontes//arial.ttf",PIG_FONTE_PADRAO_TAM,0);
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

    static int CriaFonteFundo(char *nome,int tamanho,int estilo,char *arquivoFundo,int idJanela=0){
        int resp = numFontes->RetiraLivre();
        fontes[resp] = new CMapaCaracteres(nome,tamanho,estilo,arquivoFundo,idJanela);
        totalFontes++;
        return resp;
    }

    static int CriaFonteNormal(char *nome,int tamanho,int estilo,PIG_Cor corLetra,int contorno,PIG_Cor corContorno,int idJanela=0){
        int resp = numFontes->RetiraLivre();
        fontes[resp] = new CMapaCaracteres(nome,tamanho,estilo,corLetra,contorno,corContorno,idJanela);
        totalFontes++;
        return resp;
    }

    static int CriaFonteNormal(char *nome,int tamanho,int estilo,PIG_Cor corLetra=BRANCO,int idJanela=0){
        int resp = numFontes->RetiraLivre();
        fontes[resp] = new CMapaCaracteres(nome,tamanho,estilo,corLetra,idJanela);
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

    inline static void EscreverString(std::string str,int x,int y,int numFonte,PIG_Cor corFonte=BRANCO,PIG_PosTexto pos = CPIG_TEXTO_ESQUERDA,float angulo=0){
        fontes[numFonte]->Escreve(str,x,y,corFonte,pos,angulo);
    }

    inline static void EscreverInteiro(int valor,int x,int y,int numFonte,PIG_Cor corFonte=BRANCO,PIG_PosTexto pos = CPIG_TEXTO_ESQUERDA,float angulo=0){
        std::stringstream str;
        str<<valor;
        fontes[numFonte]->Escreve(str.str(),x,y,corFonte,pos,angulo);
    }

    inline static void EscreverReal(double valor,int x,int y,int numFonte,int casas=2,PIG_Cor corFonte=BRANCO,PIG_PosTexto pos = CPIG_TEXTO_ESQUERDA,float angulo=0){
        std::stringstream str;
        str.setf(std::ios_base::fixed, std::ios_base::floatfield);
        str<<std::setprecision(casas)<<valor;
        fontes[numFonte]->Escreve(str.str(),x,y,corFonte,pos,angulo);
    }

    inline static void EscreverLonga(std::string str,int x,int y,int largMax,int espacoEntreLinhas,int numFonte,PIG_Cor corFonte=BRANCO,PIG_PosTexto pos = CPIG_TEXTO_ESQUERDA,float angulo=0){
        fontes[numFonte]->EscreveLonga(str,x,y,largMax,espacoEntreLinhas,corFonte,pos,angulo);
    }

    inline static std::vector<std::string> ExtraiLinhasString(std::string texto,int largMax,int numFonte){
        return fontes[numFonte]->ExtraiLinhas(texto,largMax);
    }

    inline static PIG_Metricas_Fonte GetMetricas(Uint16 letra, int numFonte,PIG_Estilo estilo=ESTILO_NORMAL){
        return fontes[numFonte]->GetMetricasLetra(letra,estilo);
    }

    inline static int GetLarguraLetra(char letra,int numFonte, PIG_Estilo estilo=ESTILO_NORMAL ){
        return fontes[numFonte]->GetLarguraLetra(letra,estilo);
    }

    inline static int GetTamanhoBaseFonte(int numFonte){
        return fontes[numFonte]->GetTamanhoBaseFonte();
    }

    inline static int GetLineSkip(int numFonte){
        return fontes[numFonte]->GetLineSkip();
    }

    inline static SDL_Surface *GetGlyph(Uint16 *ch,int numFonte,PIG_Cor cor=BRANCO){
        return fontes[numFonte]->GetGlyph(ch,cor);
    }

    static void DestroiFonte(int idFonte){
        if (idFonte==0) return;             //a fonte padrao só é destruida quando o gerenciador for encerrado
        numFontes->DevolveUsado(idFonte);
        delete fontes[idFonte];
        totalFontes--;
        fontes[idFonte] = NULL;
    }

    static void SubstituiCaracter(uint16_t caracter,string nomeArquivo,int largNova,int x,int y,int altura,int largura,int numFonte){
        fontes[numFonte]->SubstituiGlyph(nomeArquivo,caracter,largNova,x,y,altura,largura);
    }

};

PoolNumeros CGerenciadorFontes::numFontes;
int CGerenciadorFontes::totalFontes;
MapaCaracteres CGerenciadorFontes::fontes[MAX_FONTES];

#endif // _CGERENCIADORFONTES_
