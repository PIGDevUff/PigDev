#ifndef _CMAPACARACTERES_
#define _CMAPACARACTERES_

#include "CPIGCaractere.h"

typedef enum {PIG_TEXTO_ESQUERDA,PIG_TEXTO_DIREITA,PIG_TEXTO_CENTRO} PIGPosicaoTexto;

class CPIGFonte{

protected:

    static string delimitadores;

    PIGCaractere caracteres[PIG_TOTALESTILOS][PIG_ULTIMO_CAR-PIG_PRIMEIRO_CAR];

    int fontDescent;
    int estiloFixo;
    TTF_Font *font;

    string nome;
    int tamFonte;
    int janela;

    //cria o conjunto de glifos das letras com as características fornecidas
    void CriaLetrasSurface(PIGEstilo estilo, int nivelOutline, PIGCor corOutline, SDL_Surface *fundo,  PIGCor corFonte=BRANCO){
        TTF_SetFontStyle(font,estilo);
        for (Uint16 letra=PIG_PRIMEIRO_CAR;letra<PIG_ULTIMO_CAR;letra++){
            caracteres[estilo][letra-PIG_PRIMEIRO_CAR] = new CPIGCaractere(font,tamFonte,letra,corFonte,nivelOutline,corOutline,fundo);
        }
    }

    //inicia os atributos da classe
    void IniciaBase(string nomeFonte,int tamanhoFonte,int idJanela,PIGEstilo estilo){
        nome = nomeFonte;
        tamFonte = tamanhoFonte;
        estiloFixo = estilo;
        janela = idJanela;

        font = TTF_OpenFont(nome.c_str(), tamanhoFonte);
        if (font==NULL) throw CPIGErroArquivo(nomeFonte);

        fontDescent = TTF_FontDescent(font);

        for (int i=0;i<PIG_TOTALESTILOS;i++){
            for (int k=PIG_PRIMEIRO_CAR;k<PIG_ULTIMO_CAR;k++){
                caracteres[i][k-PIG_PRIMEIRO_CAR] = NULL;
            }
        }
    }

    int CalculaXPosicao(int x,int larg,PIGPosicaoTexto pos){
        switch(pos){
        case PIG_TEXTO_ESQUERDA:break;
        case PIG_TEXTO_DIREITA:
            x -= larg;break;
        case PIG_TEXTO_CENTRO:
            x -= larg/2;break;
        }
        return x;
    }

    inline static Uint16 ConvChar(Uint16 letra){
        if (letra>6500) letra+=64;
        return letra % 256;
    }

    //converte cada caractere da string no índice correpondente do vetor de glifos
    static vector<int> Converte(string original){
        vector<int> resp;
        Uint16 aux;
        for (unsigned int i=0;i<original.size();i++){
            aux = original[i];                          //esse caractere pode ter 2 bytes
            if (aux==65475) continue;                   //ignora certos símbolos
            aux = ConvChar(aux);                        //descobre o valor ASCII
            //if (aux-PIG_PRIMEIRO_CAR<0) continue;
            resp.push_back(aux);                        //converte para o índice do vetor
        }
        return resp;
    }

public:

    CPIGFonte(string nomeFonte,int tamanhoFonte,int estilo, string nomeFundo, int idJanela){
        IniciaBase(nomeFonte,tamanhoFonte,idJanela, estilo);
        SDL_Surface *fundo = IMG_Load(nomeFundo.c_str());//carrega a imagem de fundo
        SDL_SetSurfaceBlendMode(fundo,SDL_BLENDMODE_MOD);
        CriaLetrasSurface(estilo,0,BRANCO,fundo,BRANCO);
        SDL_FreeSurface(fundo);
    }

    CPIGFonte(string nomeFonte,int tamanhoFonte,int estilo, string nomeFundo,int outline,PIGCor corOutline, int idJanela){
        IniciaBase(nomeFonte,tamanhoFonte,idJanela, estilo);

        SDL_Surface *fundo = IMG_Load(nomeFundo.c_str());//carrega a imagem de fundo
        SDL_SetSurfaceBlendMode(fundo,SDL_BLENDMODE_MOD);
        CriaLetrasSurface(estilo,outline,corOutline,fundo);
        SDL_FreeSurface(fundo);
    }

    CPIGFonte(string nomeFonte,int tamanhoFonte,int estilo, PIGCor corFonte,int outline,PIGCor corOutline, int idJanela){
        IniciaBase(nomeFonte,tamanhoFonte,idJanela, estilo);

        CriaLetrasSurface(estilo, outline, corOutline, NULL, corFonte);
    }

    CPIGFonte(string nomeFonte,int tamanhoFonte,int estilo, PIGCor corFonte, int idJanela){
        IniciaBase(nomeFonte,tamanhoFonte,idJanela, estilo);
        CriaLetrasSurface(estilo, 0, BRANCO, NULL);//, corFonte);
    }

    ~CPIGFonte(){
        TTF_CloseFont(font);
        for (int i=0;i<PIG_TOTALESTILOS;i++){
            for (int k=PIG_PRIMEIRO_CAR;k<PIG_ULTIMO_CAR;k++){
                if (caracteres[i][k-PIG_PRIMEIRO_CAR]){
                    delete caracteres[i][k-PIG_PRIMEIRO_CAR];
                }
            }
        }

    }

    void SubstituiGlyph(string nomeArq,uint16_t glyph, SDL_Rect rectImagem, int altNova, int largNova){
        glyph = glyph%256;
        if (glyph<PIG_PRIMEIRO_CAR||glyph>=PIG_ULTIMO_CAR) throw CPIGErroIndice(glyph,"caracter");//se o indice do glyph antigo não existe

        int h;
        SDL_Surface *surfExtra;

        #ifdef SHARE_BITMAP
        surfExtra = CPIGAssetLoader::LoadImage(nomeArq);
        #else
        surfExtra = IMG_Load(nomeArq.c_str()); //tenta ler o arquivo de imagem indicado
        #endif // SHARE_BITMAP

        if (surfExtra==NULL) throw CPIGErroArquivo(nomeArq); //se não for possível lança um erro

        caracteres[estiloFixo][glyph-PIG_PRIMEIRO_CAR]->SubstituiGlyph(surfExtra,rectImagem,altNova,largNova);

        SDL_FreeSurface(surfExtra);
    }

    int GetFonteDescent(){
        return -fontDescent;//o valor armazenado fica negativo; a resposta é dada com valor positivo
    }

    int GetFonteAscent(){
        return TTF_FontAscent(font); //quantidade base de pixels acima da linha base da letra (não inclui acento de vogais maiúsculas)
    }

    PIGMetricasFonte GetMetricasLetra(Uint16 letra, int estilo=0){
        PIGMetricasFonte metrica;
        int xMin,xMax,yMin,yMax,adv;
        if(estiloFixo>=0)
            estilo = estiloFixo;

        TTF_SetFontStyle(font,estilo);
        letra = letra%256;
        TTF_GlyphMetrics(font,letra,&xMin,&xMax,&yMin,&yMax,&adv);

        metrica.descent = -yMin;
        metrica.ascent = yMax;
        metrica.altura = yMax-yMin;
        metrica.recuo = xMin;
        metrica.avanco = xMax;
        metrica.largura = xMax-xMin;
        return metrica;
    }

    int GetTamanhoBaseFonte(){
        return tamFonte;
    }

    int GetLineSkip(){
        return TTF_FontLineSkip(font);
    }

    int GetLarguraLetra(Uint16 letra, int estilo=0){
        Uint16 aux = letra;
        aux = aux % 256;
        if(estiloFixo>=0)
            estilo = estiloFixo;
        return caracteres[estilo][aux-PIG_PRIMEIRO_CAR]->GetLargura();
    }

    vector<string> ExtraiLinhas(string texto, int largMax, string delim=delimitadores){
        vector<string> resp;
        if (texto=="") return resp;

        vector<string> palavras = PIGSeparaPalavras(texto,delim);
        string linhaAtual = "";   //linha atual (que está sendo montada) contém pelo menos a primeira palavra
        int tamanhoAtual = 0;

        for (string palavra : palavras){
            int largPalavra = GetLarguraPixelsString(palavra);

            if (palavra[0]=='\n'){//se existe uma quebra de linha forçada
                resp.push_back(linhaAtual);
                linhaAtual = "";
                tamanhoAtual = 0;
            }

            if (tamanhoAtual + largPalavra > largMax && linhaAtual!=""){//a palavra estouraria a largura máxima se fosse agregada                if (ttttt==0){
                resp.push_back(linhaAtual); //coloca a linha que está montada no vetor de linhas
                linhaAtual = palavra; //a palavra que estouraria o limite começa a próxima linha
                tamanhoAtual = largPalavra;
            }else{//não estourou o limite
                linhaAtual += palavra;
                tamanhoAtual += largPalavra;
            }
        }

        if (linhaAtual != ""){
            resp.push_back(linhaAtual); //pega a linha que sobrou do processamento (última linha que não foi quebrada)
        }

        palavras.clear();
        return resp;
    }

    virtual int GetLarguraPixelsString(string texto){
        int resp=0;

        for (int i=0;i<texto.size();i++){
            Uint16 aux = texto[i];
            aux = aux % 256;
            if(texto[i] != '\n')
                resp += caracteres[estiloFixo][aux-PIG_PRIMEIRO_CAR]->GetLargura();
        }

        return resp;
    }

    /*inline Uint8 PIGConverteParaByte(Uint16 valor){
            if (aux==65475) continue;
            if (aux>6500) aux+=64;
            aux = aux % 256;//UTF16 string, retirando só o byte que interessa
    }*/


    /*Uint16 ConverteChar(Uint16 letra, bool &especial){
        printf(" funcao {%d} ",letra);
        if (!especial&&letra==65475){
            especial = true;
        }else if (!especial&&letra>65475){
            printf(" sem somar %d ",letra);
            especial = false;
            letra = letra % 256;
        }else{
            printf(" mod em %d ",letra);
            if (letra>6500&&letra<65475&&especial){
                letra+=64;
            }
            printf( " =%d ",letra);
            especial = false;
            letra = letra % 256;//UTF16 string, retirando só o byte que interessa
        }
        return letra;
    }*/

    virtual void Escreve(string texto,int x,int y,bool blend,PIGCor corFonte=BRANCO,PIGPosicaoTexto pos=PIG_TEXTO_ESQUERDA,float ang=0){
        if (texto=="") return;
        string strs(texto.c_str());

        int xIni = x;
        x = CalculaXPosicao(x,GetLarguraPixelsString(strs),pos);

        //printf("x: %d\n",x);

        pigGerJanelas.GetElemento(janela)->FazCorrente();

        //bool carEspecial=false;

        vector<int> conv = Converte(strs);

        for (int aux:conv){
            int indice = aux - PIG_PRIMEIRO_CAR;
            if (indice<0) continue;
            /*printf("letra: %d ",(Uint16)temp);
            if (carEspecial){
                printf(" esp ");
            }else{
                printf("<%c> %d ",char(aux),aux);
            }*/
            //printf(" auxpos %d\n",aux);
            //if (carEspecial||aux-PIG_PRIMEIRO_CAR<0) continue;
            //printf("%d %c\n",aux,(char)aux);

            caracteres[estiloFixo][indice]->Desenha(x,y,corFonte,ang,{(double)xIni-x,(double)y},blend);

            x += caracteres[estiloFixo][indice]->GetLargura();
        }
        //system("pause");

        //if (offscreenRender){
        //    offscreenRender->Desativa();
        //}

    }

    virtual void EscreveLonga(string texto,int x,int y,int largMax,int espacoEntreLinhas,bool blend,PIGCor corFonte=BRANCO,PIGPosicaoTexto pos=PIG_TEXTO_ESQUERDA,float angulo=0){
        if (texto=="") return;
        vector<string> linhas = ExtraiLinhas(texto,largMax);
        int yTotal=y;
        for (int k=0;k<linhas.size();k++){
            Escreve(linhas[k],x,yTotal,blend,corFonte,pos,angulo);
            yTotal -= espacoEntreLinhas;
        }
    }

    SDL_Surface *GetGlyph(Uint16 *emoji, PIGCor cor=BRANCO){
        return TTF_RenderUNICODE_Blended(font,emoji,cor);
    }

    SDL_Surface *GetSurface(char *str, PIGCor cor=BRANCO){
        return TTF_RenderText_Blended(font,str,cor);
    }
};

typedef CPIGFonte* PIGFonte;
string CPIGFonte::delimitadores = " \n";

#endif // _CMAPACARACTERES_
