#ifndef _CPIGGERENCIADORFONTES_
#define _CPIGGERENCIADORFONTES_

#include "CPIGMapaCaracteres.h"
#include "CPIGMapaCaracteresDinamicos.h"

class CPIGGerenciadorFontes{

private:
    static CPIGRepositorio<PIGMapaCaracteres> *fontes;

public:

    static PIGMapaCaracteres GetFonte(int idFonte){

        return fontes->GetElemento(idFonte);
    }

    static void Inicia(){
        TTF_Init();

        //fontes[0] = new CPIGMapaCaracteres(PIG_FONTE_PADRAO_NOME,PIG_FONTE_PADRAO_TAM,ESTILO_NORMAL,PIG_FONTE_PADRAO_COR,0);
        //fontes[0] = new CMapaCaracteres(PIG_FONTE_PADRAO_NOME,PIG_FONTE_PADRAO_TAM,ESTILO_NORMAL,PIG_FONTE_PADRAO_COR,0,VERDE,0);
        //fontes[0] = new CMapaCaracteres(PIG_FONTE_PADRAO_NOME,PIG_FONTE_PADRAO_TAM,ESTILO_NORMAL,"desenho.bmp",0,BRANCO,0);
        //fontes[0] = new CMapaCaracteresDinamicos("..//fontes//arial.ttf",PIG_FONTE_PADRAO_TAM,0);

        fontes = new CPIGRepositorio<PIGMapaCaracteres>(MAX_FONTES,"fontes");
        fontes->Insere(new CPIGMapaCaracteres(PIG_FONTE_PADRAO_NOME,PIG_FONTE_PADRAO_TAM,ESTILO_NORMAL,PIG_FONTE_PADRAO_COR,0));
    }

    static void Encerra(){
        delete fontes;

        TTF_Quit();
    }

    static int CriaFonteFundo(char *nome,int tamanho,int estilo,char *arquivoFundo,int contorno,PIG_Cor corContorno,int idJanela=0){
        return fontes->Insere(new CPIGMapaCaracteres(nome,tamanho,estilo,arquivoFundo,contorno,corContorno,idJanela));
    }

    static int CriaFonteFundo(char *nome,int tamanho,int estilo,char *arquivoFundo,int idJanela=0){
        return fontes->Insere(new CPIGMapaCaracteres(nome,tamanho,estilo,arquivoFundo,idJanela));
    }

    static int CriaFonteNormal(char *nome,int tamanho,int estilo,PIG_Cor corLetra,int contorno,PIG_Cor corContorno,int idJanela=0){
        return fontes->Insere(new CPIGMapaCaracteres(nome,tamanho,estilo,corLetra,contorno,corContorno,idJanela));
    }

    static int CriaFonteNormal(char *nome,int tamanho,int estilo,PIG_Cor corLetra=BRANCO,int idJanela=0){
        return fontes->Insere(new CPIGMapaCaracteres(nome,tamanho,estilo,corLetra,idJanela));
    }

    static int CriaFonteDinamica(char *nome,int tamanho,int idJanela=0){
        return fontes->Insere(new CPIGMapaCaracteresDinamicos(nome,tamanho,idJanela));
    }

    static void DestroiFonte(int idFonte){
        fontes->Remove(idFonte);
    }

};

CPIGRepositorio<PIGMapaCaracteres> *CPIGGerenciadorFontes::fontes;

#endif // _CPIGGERENCIADORFONTES_
