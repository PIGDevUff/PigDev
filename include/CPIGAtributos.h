#ifndef _CPIGATRIBUTOS_
#define _CPIGATRIBUTOS_

class CPIGAtributos{

private:

    unordered_map<int, string> valoresInt;
    unordered_map<string, string> valoresString;

public:

    CPIGAtributos(){}

    CPIGAtributos(CPIGAtributos *outro){
        if (outro){
            valoresInt = outro->valoresInt;
            valoresString = outro->valoresString;
        }
    }

    virtual ~CPIGAtributos(){}

    void LimpaAtributos(){
        valoresInt.clear();
        valoresString.clear();
    }

    void SetValorInt(int chave, int valor){
        valoresInt[chave] = to_string(valor);
    }

    void SetValorInt(string chave, int valor){
        transform(chave.begin(), chave.end(), chave.begin(), ::toupper);
        valoresString[chave] = to_string(valor);
    }

    void SetValorFloat(int chave, float valor){
        valoresInt[chave] = to_string(valor);
    }

    void SetValorFloat(string chave, float valor){
        transform(chave.begin(), chave.end(), chave.begin(), ::toupper);
        valoresString[chave] = to_string(valor);
    }

    void SetValorString(int chave, string valor){
        valoresInt[chave] = valor;
    }

    void SetValorString(string chave, string valor){
        transform(chave.begin(), chave.end(), chave.begin(), ::toupper);
        valoresString[chave] = valor;
    }

    bool GetValorInt(int chave, int &valor){
        unordered_map<int, string>::iterator it = valoresInt.find(chave);
        if (it == valoresInt.end())
            return false;
        valor = stoi(it->second);
        return true;
    }

    bool GetValorInt(string chave, int &valor){
        transform(chave.begin(), chave.end(), chave.begin(), ::toupper);
        unordered_map<string, string>::iterator it = valoresString.find(chave);
        if (it == valoresString.end())
            return false;
        valor = stoi(it->second);
        return true;
    }

    bool GetValorFloat(int chave, float &valor){
        unordered_map<int, string>::iterator it = valoresInt.find(chave);
        if (it == valoresInt.end())
            return false;
        valor = stof(it->second);
        return true;
    }

    bool GetValorFloat(string chave, float &valor){
        transform(chave.begin(), chave.end(), chave.begin(), ::toupper);
        unordered_map<string, string>::iterator it = valoresString.find(chave);
        if (it == valoresString.end())
            return false;
        valor = stof(it->second);
        return true;
    }

    bool GetValorString(int chave, string &valor){
        unordered_map<int, string>::iterator it = valoresInt.find(chave);
        if (it == valoresInt.end())
            return false;
        valor = it->second;
        return true;
    }

    bool GetValorString(string chave, string &valor){
        transform(chave.begin(), chave.end(),chave.begin(), ::toupper);
        unordered_map<string, string>::iterator it = valoresString.find(chave);
        if (it == valoresString.end())
            return false;
        valor = it->second;
        return true;
    }

    float GetFloat(string chave, float retNegativo){
        transform(chave.begin(), chave.end(), chave.begin(), ::toupper);
        unordered_map<string, string>::iterator it = valoresString.find(chave);
        if (it == valoresString.end())
            return retNegativo;
        return stof(it->second);
    }

    string GetString(string chave, string retNegativo){
        transform(chave.begin(), chave.end(), chave.begin(), ::toupper);
        unordered_map<string, string>::iterator it = valoresString.find(chave);
        if (it == valoresString.end()){
            return retNegativo;
        }
        return it->second;
    }

    int GetInt(string chave, int retNegativo){
        transform(chave.begin(), chave.end(),chave.begin(), ::toupper);
        unordered_map<string, string>::iterator it = valoresString.find(chave);
        if (it == valoresString.end())
            return retNegativo;
        return stoi(it->second);
    }

    void dump(){
        cout<<"Starting dump..."<<endl;

        for (unordered_map<string, string>::iterator it= valoresString.begin(); it!=valoresString.end(); it++){
            cout<<it->first.c_str()<<" "<<it->second.c_str()<<endl;
        }

        for (unordered_map<int, string>::iterator it= valoresInt.begin(); it!=valoresInt.end(); it++){
            cout<<it->first<<" "<<it->second.c_str()<<endl;
        }
    }

    //le um conjunto de palavras da stream até encontrar uma que termine com " como último caractere, retorna a string toda
    static string LeString(string inicial, istream &ss){
        string resp = inicial,aux;

        if (resp[0]=='\"'){//se começa com aspas, retira as aspas
            resp.erase(0,1);
            if (resp[resp.size()-1]=='\"'){ //se termina com aspas também retira
                resp.erase(resp.end()-1);
            }else{//entra no loop procurando a palavras que vai terminar com aspas
                while (ss>>aux && aux[aux.size()-1]!='\"'){
                    resp += " " + aux;
                }
                if (aux[aux.size()-1]=='\"'){//acrescenta a última palavra que termina com aspas (depois de tirar as aspas)
                    aux.erase(aux.end()-1);
                    resp += " " + aux;
                }
            }
        }

        return resp;
    }

    static CPIGAtributos GetAtributos(string parametros){
        CPIGAtributos resp;
        stringstream ss(parametros);
        string variavel,valorString;

        while(ss >> variavel){
            ss >> valorString;
            valorString = LeString(valorString,ss);
            resp.SetValorString(variavel,valorString);
        }

        return resp;
    }
};
typedef CPIGAtributos *PIGAtributos;
#endif //_CPIGATRIBUTOS_
