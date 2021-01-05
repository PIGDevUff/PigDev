#ifndef _CPIGREPOSITORIO_
#define _CPIGREPOSITORIO_

template <class T>
class CPIGRepositorio{

private:
std::string tipoElementos;
std::vector<int> posLivres;
std::unordered_map<int,T> elementos;
typename std::unordered_map<int,T>::iterator it;

public:

    CPIGRepositorio(int qtdElementos,std::string tipoDeElementos){
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

    int ProxID(){
        return posLivres.back();
    }

};

#endif // _CPIGREPOSITORIO_
