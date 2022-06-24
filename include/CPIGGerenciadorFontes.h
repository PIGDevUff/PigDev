#ifndef _CPIGGERENCIADORFONTES_
#define _CPIGGERENCIADORFONTES_

#include "SDL_ttf.h"

#include "CPIGFonte.h"
#include "CPIGFonteDinamica.h"

class CPIGGerenciadorFontes{

private:
    static CPIGRepositorio<PIGFonte> *fontes;

public:

    inline static PIGFonte GetFonte(int idFonte){
        return fontes->GetElemento(idFonte);
    }

    inline static void Inicia(){
        TTF_Init();

        //fontes[0] = new CPIGPIGMapaCaracteres(PIG_FONTE_PADRAO_NOME,PIG_FONTE_PADRAO_TAM,ESTILO_NORMAL,PIG_FONTE_PADRAO_COR,0);
        //fontes[0] = new CPIGMapaCaracteres(PIG_FONTE_PADRAO_NOME,PIG_FONTE_PADRAO_TAM,ESTILO_NORMAL,PIG_FONTE_PADRAO_COR,0,VERDE,0);
        //fontes[0] = new CPIGMapaCaracteres(PIG_FONTE_PADRAO_NOME,PIG_FONTE_PADRAO_TAM,ESTILO_NORMAL,"desenho.bmp",0,BRANCO,0);
        //fontes[0] = new CPIGMapaCaracteresDinamicos("..//fontes//arial.ttf",PIG_FONTE_PADRAO_TAM,0);

        fontes = new CPIGRepositorio<PIGFonte>(PIG_MAX_FONTES,"fontes");
        fontes->Insere(new CPIGFonte(PIG_FONTE_PADRAO_NOME,PIG_FONTE_PADRAO_TAM,PIG_ESTILO_NORMAL,PIG_FONTE_PADRAO_COR,0));
        //fontes->Insere(new CPIGMapaCaracteresDinamicos("..//fontes//arial.ttf",PIG_FONTE_PADRAO_TAM,0));
    }

    inline static void Encerra(){
        delete fontes;

        TTF_Quit();
    }

    inline static int CriaFonteFundo(string nome, int tamanho, PIGEstilo estilo, string arquivoFundo, int contorno, PIGCor corContorno, int idJanela=0){
        return fontes->Insere(new CPIGFonte(nome,tamanho,estilo,arquivoFundo,contorno,corContorno,idJanela,NULL));
    }

    inline static int CriaFonteFundo(string nome, int tamanho, PIGEstilo estilo, string arquivoFundo, int idJanela=0){
        return fontes->Insere(new CPIGFonte(nome,tamanho,estilo,arquivoFundo,idJanela,NULL));
    }

    inline static int CriaFonteNormal(string nome, int tamanho, PIGEstilo estilo, PIGCor corLetra, int contorno, PIGCor corContorno, int idJanela=0){
        return fontes->Insere(new CPIGFonte(nome,tamanho,estilo,corLetra,contorno,corContorno,idJanela,NULL));
    }

    inline static int CriaFonteNormal(string nome, int tamanho, PIGEstilo estilo, PIGCor corLetra=PIG_FONTE_PADRAO_COR, int idJanela=0){
        return fontes->Insere(new CPIGFonte(nome,tamanho,estilo,corLetra,idJanela,NULL));
    }

    inline static int CriaFonteFundoOffScreen(string nome, int tamanho, PIGEstilo estilo, string arquivoFundo, int contorno, PIGCor corContorno, PIGOffscreenRenderer off, int layer=0){
        return fontes->Insere(new CPIGFonte(nome,tamanho,estilo,arquivoFundo,contorno,corContorno,-1,off->GetLayer(layer)->render));
    }

    inline static int CriaFonteFundoOffScreen(string nome, int tamanho, PIGEstilo estilo, string arquivoFundo, PIGOffscreenRenderer off, int layer=0){
        return fontes->Insere(new CPIGFonte(nome,tamanho,estilo,arquivoFundo,-1,off->GetLayer(layer)->render));
    }

    inline static int CriaFonteNormalOffScreen(string nome, int tamanho, PIGEstilo estilo, PIGCor corLetra, int contorno, PIGCor corContorno, PIGOffscreenRenderer off, int layer=0){
        return fontes->Insere(new CPIGFonte(nome,tamanho,estilo,corLetra,contorno,corContorno,-1,off->GetLayer(layer)->render));
    }

    inline static int CriaFonteNormalOffScreen(string nome, int tamanho, PIGEstilo estilo, PIGOffscreenRenderer off, PIGCor corLetra=PIG_FONTE_PADRAO_COR, int layer=0){
        return fontes->Insere(new CPIGFonte(nome,tamanho,estilo,corLetra,-1,off->GetLayer(layer)->render));
    }

    inline static int CriaFonteDinamica(string nome, int tamanho, int idJanela=0){
        return fontes->Insere(new CPIGFonteDinamica(nome,tamanho,idJanela));
    }

    inline static int InsereFonte(PIGFonte fonte){
        return fontes->Insere(fonte);
    }

    inline static void DestroiFonte(int idFonte){
        fontes->Remove(idFonte);
    }

    //static SDL_Surface *GetSurface(char *str, PIGCor cor,int idFonte=0){
        //return fontes->GetElemento(idFonte)->GetSurface(str,cor);
    //}

};

CPIGRepositorio<PIGFonte> *CPIGGerenciadorFontes::fontes;

#endif // _CPIGGERENCIADORFONTES_
