class CPilhaCoordenada{

private:

typedef struct Ponto{
    int x,y;
    struct Ponto *prox;
} Ponto;

Ponto *ini;

public:

    CPilhaCoordenada(){
        ini = NULL;
    }

    void Empilha(int x,int y){
        Ponto *novo = (Ponto*)malloc(sizeof(Ponto));
        novo->x = x;
        novo->y = y;
        novo->prox = ini;

        ini = novo;
    }

    int Desempilha(int &x,int &y){
        if (ini==NULL) return 0;
        Ponto *antigo = ini;
        ini = ini->prox;
        x = antigo->x;
        y = antigo->y;
        free(antigo);
        return 1;
    }

    ~CPilhaCoordenada(){
        Ponto *aux = ini;
        while (ini){
            ini = ini->prox;
            free(aux);
        }
    }

};
