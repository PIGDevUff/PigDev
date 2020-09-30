#ifndef _CGERENCIADOROBJETOS_
#define _CGERENCIADOROBJETOS_

#include "CObjeto.h"
class CGerenciadorObjetos{

private:
    static int totalObjetos;
    static PoolNumeros numObjetos;
    static Objeto objetos[MAX_OBJETOS];

public:

    inline static Objeto GetObjeto(int idObjeto){
        if (idObjeto<0||idObjeto>=MAX_OBJETOS||objetos[idObjeto]==NULL) throw CPigErroIndice(idObjeto,"objetos");
        return objetos[idObjeto];
    }

    static void Inicia(){
        totalObjetos = 0;
        for (int i=0;i<MAX_OBJETOS;i++)
            objetos[i] = NULL;
        numObjetos = new CPoolNumeros(MAX_OBJETOS);
    }

    static void Encerra(){
        for (int i=0;i<MAX_OBJETOS;i++){
            if (objetos[i]) delete objetos[i];
        }
        delete numObjetos;
    }

    static int CriaObjeto(std::string nomeArquivoBMP,PIG_Cor *corFundo=NULL,int retiraFundo=1,int idJanela=0){
        int resp = numObjetos->RetiraLivre();
        objetos[resp] = new CObjeto(nomeArquivoBMP,corFundo,retiraFundo,idJanela);
        totalObjetos++;
        return resp;
    }

    static int CriaObjetoOffScreen(OffscreenRenderer offRenderer,PIG_Cor *corFundo=NULL,int retiraFundo=1,int idJanela=0){
        int resp = numObjetos->RetiraLivre();
        objetos[resp] = new CObjeto(offRenderer,corFundo,retiraFundo,idJanela);
        totalObjetos++;
        return resp;
    }

    static void DestroiObjeto(int idObjeto){
        if (idObjeto<0||idObjeto>=MAX_OBJETOS||objetos[idObjeto]==NULL) throw CPigErroIndice(idObjeto,"objetos");
        numObjetos->DevolveUsado(idObjeto);
        delete objetos[idObjeto];
        totalObjetos--;
        objetos[idObjeto] = NULL;
    }

    inline static void SetValorIntObjeto(int idObjeto, int chave, int valor){
        GetObjeto(idObjeto)->SetValoresInt(chave,valor);
    }

    inline static void SetValorIntObjeto(int idObjeto, std::string chave, int valor){
        GetObjeto(idObjeto)->SetValoresInt(chave,valor);
    }

    inline static void SetValorFloatObjeto(int idObjeto, int chave, float valor){
        GetObjeto(idObjeto)->SetValoresFloat(chave,valor);
    }

    inline static void SetValorFloatObjeto(int idObjeto, std::string chave, float valor){
        GetObjeto(idObjeto)->SetValoresFloat(chave,valor);
    }

    inline static void SetValorStringObjeto(int idObjeto, int chave, std::string valor){
        GetObjeto(idObjeto)->SetValoresString(chave,valor);
    }

    inline static void SetValorStringObjeto(int idObjeto, std::string chave, std::string valor){
        GetObjeto(idObjeto)->SetValoresString(chave,valor);
    }

    inline static bool GetValorIntObjeto(int idObjeto, int indice, int *valor){
        return GetObjeto(idObjeto)->GetValoresInt(indice,*valor);
    }

    inline static bool GetValorFloatObjeto(int idObjeto, int indice, float *valor){
        return GetObjeto(idObjeto)->GetValoresFloat(indice,*valor);
    }

    inline static bool GetValorStringObjeto(int idObjeto, int indice, char *valor){
        std::string str;
        bool resp = GetObjeto(idObjeto)->GetValoresString(indice,str);
        strcpy(valor,str.c_str());
        return resp;
    }

    inline static bool GetValorIntObjeto(int idObjeto, std::string indice, int *valor){
        return GetObjeto(idObjeto)->GetValoresInt(indice,*valor);
    }

    inline static bool GetValorFloatObjeto(int idObjeto, std::string indice, float *valor){
        return GetObjeto(idObjeto)->GetValoresFloat(indice,*valor);
    }

    inline static bool GetValorStringObjeto(int idObjeto, std::string indice, char *valor){
        std::string str;
        bool resp = GetObjeto(idObjeto)->GetValoresString(indice,str);
        strcpy(valor,str.c_str());
        return resp;
    }

    inline static void GetPosicaoXY(int idObjeto, int *x, int *y){
        GetObjeto(idObjeto)->GetXY(*x,*y);
    }

    inline static void Move(int idObjeto, int x, int y){
        GetObjeto(idObjeto)->Move(x,y);
    }

    inline static void Desloca(int idObjeto, int dx, int dy){
        GetObjeto(idObjeto)->Desloca(dx,dy);
    }

    inline static void SetAngulo(int idObjeto, float angulo){
        GetObjeto(idObjeto)->SetAngulo(angulo);
    }

    inline static float GetAngulo(int idObjeto){
        return GetObjeto(idObjeto)->GetAngulo();
    }

    inline static void SetPivo(int idObjeto, int x, int y){
        GetObjeto(idObjeto)->SetPivo(x,y);
    }

    inline static void SetPivo(int idObjeto, float relX, float relY){
        GetObjeto(idObjeto)->SetPivo(relX,relY);
    }

    inline static void GetPivo(int idObjeto, int *x,int *y){
        GetObjeto(idObjeto)->GetPivo(*x,*y);
    }

    inline static void SetFlip(int idObjeto, PIG_Flip valor){
        GetObjeto(idObjeto)->SetFlip(valor);
    }

    inline static PIG_Flip GetFlip(int idObjeto){
        return GetObjeto(idObjeto)->GetFlip();
    }

    inline static void SetDimensoes(int idObjeto, int altura, int largura){
        GetObjeto(idObjeto)->SetDimensoes(altura,largura);
    }

    inline static void GetDimensoes(int idObjeto, int *altura, int *largura){
        GetObjeto(idObjeto)->GetDimensoes(*altura,*largura);
    }

    inline static void GetDimensoesOriginais(int idObjeto, int *altura, int *largura){
        GetObjeto(idObjeto)->GetDimensoesOriginais(*altura,*largura);
    }

    inline static void CriaFrame(int idObjeto, int xBitmap, int yBitmap,int altura,int largura){
        SDL_Rect r;
        r.x = xBitmap;
        r.y = yBitmap;
        r.h = altura;
        r.w = largura;
        GetObjeto(idObjeto)->DefineFrame(r);
    }

    inline static void SetColoracao(int idObjeto, PIG_Cor cor){
        GetObjeto(idObjeto)->SetColoracao(cor);
    }

    inline static void SetOpacidade(int idObjeto, int valor){
        GetObjeto(idObjeto)->SetOpacidade(valor);
    }

    inline static int GetOpacidade(int idObjeto){
        return GetObjeto(idObjeto)->GetOpacidade();
    }

    inline static void Desenha(int idObjeto,OffscreenRenderer offRender=NULL){
        GetObjeto(idObjeto)->Desenha(offRender);
    }

    //inline static int TestaColisaoPoligono(int idObjeto1, int idObjeto2) {
    //    return GetObjeto(idObjeto1)->ColisaoPoligono(GetObjeto(idObjeto2)) || GetObjeto(idObjeto2)->ColisaoPoligono(GetObjeto(idObjeto1));
   // }

    inline static int TestaColisao(int idObjeto1, int idObjeto2) {
        return GetObjeto(idObjeto1)->Colisao(GetObjeto(idObjeto2)) && GetObjeto(idObjeto2)->Colisao(GetObjeto(idObjeto1));
    }

    inline static void DefineAreaColisao(int idObjeto, int *x, int *y, int quantidadePontos) {
        std::vector<SDL_Point> vertices;

        for (int i = 0; i < quantidadePontos; i++) {
            SDL_Point aux = {x[i], y[i]};
            vertices.push_back(aux);
        }

        GetObjeto(idObjeto)->SetVertices(vertices);
    }

    inline static PIG_Cor **GetPixels(int idObjeto){
        return GetObjeto(idObjeto)->GetPixels();
    }

    inline static void AtualizaPixels(int idObjeto,int retiraFundo=1){
        GetObjeto(idObjeto)->AtualizaPixels(retiraFundo);
    }
};


PoolNumeros CGerenciadorObjetos::numObjetos;
int CGerenciadorObjetos::totalObjetos;
Objeto CGerenciadorObjetos::objetos[MAX_OBJETOS];
#endif // _CGERENCIADOROBJETOS_
