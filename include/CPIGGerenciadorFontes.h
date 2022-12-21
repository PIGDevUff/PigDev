#ifndef _CPIGGERENCIADORFONTES_
#define _CPIGGERENCIADORFONTES_

#include "SDL_ttf.h"

#include "CPIGFonte.h"
#include "CPIGFonteDinamica.h"

class CPIGGerenciadorFontes: public CPIGRepositorio<PIGFonte>{

public:

    CPIGGerenciadorFontes():CPIGRepositorio<PIGFonte>(PIG_MAX_FONTES,"CPIGFonte"){
        TTF_Init();

        //fontes[0] = new CPIGPIGMapaCaracteres(PIG_FONTE_PADRAO_NOME,PIG_FONTE_PADRAO_TAM,ESTILO_NORMAL,PIG_FONTE_PADRAO_COR,0);
        //fontes[0] = new CPIGMapaCaracteres(PIG_FONTE_PADRAO_NOME,PIG_FONTE_PADRAO_TAM,ESTILO_NORMAL,PIG_FONTE_PADRAO_COR,0,VERDE,0);
        //fontes[0] = new CPIGMapaCaracteres(PIG_FONTE_PADRAO_NOME,PIG_FONTE_PADRAO_TAM,ESTILO_NORMAL,"desenho.bmp",0,BRANCO,0);
        //fontes[0] = new CPIGMapaCaracteresDinamicos("..//fontes//arial.ttf",PIG_FONTE_PADRAO_TAM,0);

        //Insere(new CPIGFonte(PIG_FONTE_PADRAO_NOME,PIG_FONTE_PADRAO_TAM,PIG_ESTILO_NORMAL,PIG_FONTE_PADRAO_COR,0));
    }

    inline int CriaFonteFundo(string nome, int tamanho, PIGEstilo estilo, string arquivoFundo, int contorno, PIGCor corContorno, int idJanela=0){
        return Insere(new CPIGFonte(nome,tamanho,estilo,arquivoFundo,contorno,corContorno,idJanela));
    }

    inline int CriaFonteFundo(string nome, int tamanho, PIGEstilo estilo, string arquivoFundo, int idJanela=0){
        return Insere(new CPIGFonte(nome,tamanho,estilo,arquivoFundo,idJanela));
    }

    inline int CriaFonteNormal(string nome, int tamanho, PIGEstilo estilo, PIGCor corLetra, int contorno, PIGCor corContorno, int idJanela=0){
        return Insere(new CPIGFonte(nome,tamanho,estilo,corLetra,contorno,corContorno,idJanela));
    }

    inline int CriaFonteNormal(string nome, int tamanho, PIGEstilo estilo, PIGCor corLetra=PIG_FONTE_PADRAO_COR, int idJanela=0){
        return Insere(new CPIGFonte(nome,tamanho,estilo,corLetra,idJanela));
    }

    inline int CriaFonteDinamica(string nome, int tamanho, int idJanela=0){
        return Insere(new CPIGFonteDinamica(nome,tamanho,idJanela));
    }

    inline int InsereFonte(PIGFonte fonte){
        return Insere(fonte);
    }
};
CPIGGerenciadorFontes pigGerFontes;
#endif // _CPIGGERENCIADORFONTES_
