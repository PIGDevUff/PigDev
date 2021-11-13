#ifndef _CPIGREPOSITORIO_
#define _CPIGREPOSITORIO_

template <class T>
class CPIGRepositorio{

protected:
string tipoElementos;
vector<int> posLivres;
unordered_map<int,T> elementos;
typename unordered_map<int,T>::iterator it;

public:

    CPIGRepositorio(int qtdElementos, string tipoDeElementos){
        for (int i=qtdElementos-1;i>=0;i--)
            posLivres.push_back(i);
        tipoElementos = tipoDeElementos;
    }

    ~CPIGRepositorio(){
        for(it = elementos.begin(); it != elementos.end(); ++it)
            delete it->second;
    }

    int Insere(T valor){
        int resp = posLivres.back();
        posLivres.pop_back();
        elementos[resp] = valor;
        return resp;
    }

    void Remove(int id){
        posLivres.push_back(id);
        T elem = GetElemento(id);
        delete elem;
        elementos.erase(id);
    }

    T GetElemento(int id){
        it = elementos.find(id);
        if (it==elementos.end()) throw CPIGErroIndice(id,tipoElementos);
        return it->second;
    }

    inline int ProxID(){
        return posLivres.back();
    }

    T GetPrimeiroElemento(){
        it = elementos.begin();
        if (it == elementos.end()) return NULL;
        return it->second;
    }

    T GetProximoElemento(){
        ++it;
        if (it == elementos.end()) return NULL;
        return it->second;
    }

};

#endif // _CPIGREPOSITORIO_
