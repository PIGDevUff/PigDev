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

        //fontes[0] = new CPIGPIGMapaCaracteres(PIG_FONTE_PADRAO_NOME,PIG_FONTE_PADRAO_TAM,ESTILO_NORMAL,PIG_FONTE_PADRAO_COR,0);
        //fontes[0] = new CPIGMapaCaracteres(PIG_FONTE_PADRAO_NOME,PIG_FONTE_PADRAO_TAM,ESTILO_NORMAL,PIG_FONTE_PADRAO_COR,0,VERDE,0);
        //fontes[0] = new CPIGMapaCaracteres(PIG_FONTE_PADRAO_NOME,PIG_FONTE_PADRAO_TAM,ESTILO_NORMAL,"desenho.bmp",0,BRANCO,0);
        //fontes[0] = new CPIGMapaCaracteresDinamicos("..//fontes//arial.ttf",PIG_FONTE_PADRAO_TAM,0);

        fontes = new CPIGRepositorio<PIGMapaCaracteres>(PIG_MAX_FONTES,"fontes");
        fontes->Insere(new CPIGMapaCaracteres(PIG_FONTE_PADRAO_NOME,PIG_FONTE_PADRAO_TAM,PIG_ESTILO_NORMAL,PIG_FONTE_PADRAO_COR,0));
        //fontes->Insere(new CPIGMapaCaracteresDinamicos("..//fontes//arial.ttf",PIG_FONTE_PADRAO_TAM,0));
    }

    static void Encerra(){
        delete fontes;

        TTF_Quit();
    }

    static int CriaFonteFundo(string nome, int tamanho, PIGEstilo estilo, string arquivoFundo, int contorno, PIGCor corContorno, int idJanela=0){
        return fontes->Insere(new CPIGMapaCaracteres(nome,tamanho,estilo,arquivoFundo,contorno,corContorno,idJanela,NULL));
    }

    static int CriaFonteFundo(string nome, int tamanho, PIGEstilo estilo, string arquivoFundo, int idJanela=0){
        return fontes->Insere(new CPIGMapaCaracteres(nome,tamanho,estilo,arquivoFundo,idJanela,NULL));
    }

    static int CriaFonteNormal(string nome, int tamanho, PIGEstilo estilo, PIGCor corLetra, int contorno, PIGCor corContorno, int idJanela=0){
        return fontes->Insere(new CPIGMapaCaracteres(nome,tamanho,estilo,corLetra,contorno,corContorno,idJanela,NULL));
    }

    static int CriaFonteNormal(string nome, int tamanho, PIGEstilo estilo, PIGCor corLetra=PIG_FONTE_PADRAO_COR, int idJanela=0){
        return fontes->Insere(new CPIGMapaCaracteres(nome,tamanho,estilo,corLetra,idJanela,NULL));
    }

    static int CriaFonteFundoOffScreen(string nome, int tamanho, PIGEstilo estilo, string arquivoFundo, int contorno, PIGCor corContorno, PIGOffscreenRenderer off, int layer=0){
        return fontes->Insere(new CPIGMapaCaracteres(nome,tamanho,estilo,arquivoFundo,contorno,corContorno,-1,off->GetLayer(layer)->render));
    }

    static int CriaFonteFundoOffScreen(string nome, int tamanho, PIGEstilo estilo, string arquivoFundo, PIGOffscreenRenderer off, int layer=0){
        return fontes->Insere(new CPIGMapaCaracteres(nome,tamanho,estilo,arquivoFundo,-1,off->GetLayer(layer)->render));
    }

    static int CriaFonteNormalOffScreen(string nome, int tamanho, PIGEstilo estilo, PIGCor corLetra, int contorno, PIGCor corContorno, PIGOffscreenRenderer off, int layer=0){
        return fontes->Insere(new CPIGMapaCaracteres(nome,tamanho,estilo,corLetra,contorno,corContorno,-1,off->GetLayer(layer)->render));
    }

    static int CriaFonteNormalOffScreen(string nome, int tamanho, PIGEstilo estilo, PIGOffscreenRenderer off, PIGCor corLetra=PIG_FONTE_PADRAO_COR, int layer=0){
        return fontes->Insere(new CPIGMapaCaracteres(nome,tamanho,estilo,corLetra,-1,off->GetLayer(layer)->render));
    }

    static int CriaFonteDinamica(string nome, int tamanho, int idJanela=0){
        return fontes->Insere(new CPIGMapaCaracteresDinamicos(nome,tamanho,idJanela));
    }

    static void DestroiFonte(int idFonte){
        fontes->Remove(idFonte);
    }

    //static SDL_Surface *GetSurface(char *str, PIGCor cor,int idFonte=0){
        //return fontes->GetElemento(idFonte)->GetSurface(str,cor);
    //}

};

CPIGRepositorio<PIGMapaCaracteres> *CPIGGerenciadorFontes::fontes;

#endif // _CPIGGERENCIADORFONTES_
