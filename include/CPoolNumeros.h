class CPoolNumeros{

typedef struct xxx{
    int valor;
    struct xxx *prox;
} Elem;

private:

    Elem *livres;
    int *usados;

public:

    int qtdTotal;

    CPoolNumeros(int qtd){
        qtdTotal = qtd;
        livres = NULL;
        Elem *aux;
        for (int i=0;i<qtd;i++){
            aux = (Elem*) malloc(sizeof(Elem));
            aux->valor = i;
            aux->prox = livres;
            livres = aux;
        }
        usados = (int*) calloc(sizeof(int),qtd);
    }

    ~CPoolNumeros(){
        Elem *aux,*ret;
        aux = livres;
        while (aux){
            ret = aux->prox;
            free(aux);
            aux = ret;
        }
        free(usados);
    }

    int RetiraLivre(){
        Elem *aux=livres;
        livres = livres->prox;
        usados[aux->valor] = 1;
        return aux->valor;
    }

    void DevolveUsado(int valor){
        if (usados[valor]==0){
            //printf("Erro de devolucao %d\n",valor);
            return;
        }

        usados[valor] = 0;
        Elem* aux = (Elem*) malloc(sizeof(Elem));
        aux->valor = valor;
        aux->prox = livres;
        livres = aux;
    }

    void ImprimeLivres(){
        for (int i=0;i<qtdTotal;i++){
            if (usados[i]==0)
                printf("%d\n",i);
        }
    }

    void ImprimeUsados(){
        for (int i=0;i<qtdTotal;i++){
            if (usados[i]==1)
                printf("%d\n",i);
        }
    }


};

typedef CPoolNumeros* PoolNumeros;
