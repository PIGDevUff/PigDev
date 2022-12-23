#ifndef _CPIGREPOSITORIO_
#define _CPIGREPOSITORIO_

template <class T>
class CPIGRepositorio{

protected:

    string tipoElementos;           //string que armazena o tipo de elementos que serão armazenados neste repositório para fins de exibição de mensagem em caso de erro
    vector<int> posLivres;          //vector com as posições livres (NULL) do vetor de elementos
    T *elementos;                   //vetor de elementos em si (vetor é usado para que o acesso seja o mais rápido possível)
    int qtdElementos,maxElementos;  //quantidade atual de elementos e quantidade máxima de elementos

public:

    CPIGRepositorio(int maxQtd, string tipoDeElementos){
        tipoElementos = tipoDeElementos;
        maxElementos = maxQtd;
        posLivres.resize(maxElementos);
        elementos = (T*)calloc(maxElementos,sizeof(T));
        qtdElementos = 0;
        for (int i=maxElementos-1;i>=0;i--){
            posLivres.push_back(i);
        }
    }

    ~CPIGRepositorio(){
        for (int i=0;i<maxElementos;i++)
            if (elementos[i])
                delete elementos[i];
        free(elementos);
    }

    inline int Insere(T valor){
        int resp = posLivres.back();
        posLivres.pop_back();
        elementos[resp] = valor;
        qtdElementos++;
        return resp;
    }

    inline void Remove(int id){
        posLivres.push_back(id);
        T elem = GetElemento(id);
        delete elem;
        elementos[id] = NULL;
        qtdElementos--;
    }

    inline T GetElemento(int id){
        if (id<0||id>=maxElementos||elementos[id] == NULL) throw CPIGErroIndice(id,tipoElementos);
        return elementos[id];
    }

    inline int ProxID(){
        return posLivres.back();
    }

    inline int GetQtdElementos(){
        return qtdElementos;
    }
};
#endif // _CPIGREPOSITORIO_
