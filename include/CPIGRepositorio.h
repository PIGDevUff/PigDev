#ifndef _CPIGREPOSITORIO_
#define _CPIGREPOSITORIO_

template <class T>
class CPIGRepositorio{

protected:

    string tipoElementos;
    vector<int> posLivres;
    unordered_map<int,T> elementos;

public:

    CPIGRepositorio(int qtdElementos, string tipoDeElementos){
        posLivres.reserve(qtdElementos);
        for (int i=qtdElementos-1;i>=0;i--)
            posLivres.push_back(i);
        tipoElementos = tipoDeElementos;
    }

    ~CPIGRepositorio(){
        for(auto it = elementos.begin(); it != elementos.end(); it++)
            delete it->second;
    }

    inline int Insere(T valor){
        int resp = posLivres.back();
        posLivres.pop_back();
        elementos[resp] = valor;
        return resp;
    }

    inline void Remove(int id){
        posLivres.push_back(id);
        T elem = GetElemento(id);
        delete elem;
        elementos.erase(id);
    }

    inline T GetElemento(int id){
        if (elementos[id] == NULL) throw CPIGErroIndice(id,tipoElementos);
        return elementos[id];
    }

    inline int ProxID(){
        return posLivres.back();
    }

    inline int GetQtdElementos(){
        return elementos.size();
    }
};
#endif // _CPIGREPOSITORIO_
