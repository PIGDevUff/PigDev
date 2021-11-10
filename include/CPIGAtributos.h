#ifndef _CPIGATRIBUTOS_
#define _CPIGATRIBUTOS_

class CPIGAtributos{

private:

std::map<int, int> valoresIntInt;
std::map<string, int> valoresStringInt;
std::map<int, float> valoresIntFloat;
std::map<string, float> valoresStringFloat;
std::map<int, string> valoresIntString;
std::map<string, string> valoresStringString;

public:

CPIGAtributos(){}

CPIGAtributos(CPIGAtributos *outro){
    if (outro){
        valoresIntInt = outro->valoresIntInt;
        valoresStringInt = outro->valoresStringInt;
        valoresIntFloat = outro->valoresIntFloat;
        valoresStringFloat = outro->valoresStringFloat;
        valoresIntString = outro->valoresIntString;
        valoresStringString = outro->valoresStringString;
    }
}

virtual ~CPIGAtributos(){}

void LimpaAtributos(){
    valoresIntInt.clear();
    valoresStringInt.clear();
    valoresIntFloat.clear();
    valoresStringFloat.clear();
    valoresIntString.clear();
    valoresStringString.clear();
}

void SetValorInt(int chave, int valor){
    valoresIntInt[chave] = valor;
}

void SetValorInt(string chave, int valor){
    valoresStringInt[chave] = valor;
}

void SetValorFloat(int chave, float valor){
    valoresIntFloat[chave] = valor;
}

void SetValorFloat(string chave, float valor){
    valoresStringFloat[chave] = valor;
}

void SetValorString(int chave, string valor){
    valoresIntString[chave] = valor;
}

void SetValorString(string chave, string valor){
    valoresStringString[chave] = valor;
}

bool GetValorInt(int chave, int &valor){
    std::map<int, int>::iterator it;
    it = valoresIntInt.find(chave);
    if (it == valoresIntInt.end())
        return false;
    valor = it->second;
    return true;
}

bool GetValorInt(std::string chave, int &valor){
    std::map<string, int>::iterator it;
    it = valoresStringInt.find(chave);
    if (it == valoresStringInt.end())
        return false;
    valor = it->second;
    return true;
}

bool GetValorFloat(int chave, float &valor){
    std::map<int, float>::iterator it;
    it = valoresIntFloat.find(chave);
    if (it == valoresIntFloat.end())
        return false;
    valor = it->second;
    return true;
}

bool GetValorFloat(std::string chave, float &valor){
    std::map<string, float>::iterator it;
    it = valoresStringFloat.find(chave);
    if (it == valoresStringFloat.end())
        return false;
    valor = it->second;
    return true;
}

bool GetValorString(int chave, std::string &valor){
    std::map<int, string>::iterator it;
    it = valoresIntString.find(chave);
    if (it == valoresIntString.end())
        return false;
    valor = it->second;
    return true;
}

bool GetValorString(std::string chave, std::string &valor){
    std::map<string, string>::iterator it;
    it = valoresStringString.find(chave);
    if (it == valoresStringString.end())
        return false;
    valor = it->second;
    return true;
}

float GetFloat(string chave, float retNegativo){
    std::map<string, float>::iterator it;
    it = valoresStringFloat.find(chave);
    if (it == valoresStringFloat.end())
        return retNegativo;
    return it->second;
}

string GetString(string chave, string retNegativo){
    std::map<string, string>::iterator it;
    it = valoresStringString.find(chave);
    if (it == valoresStringString.end())
        return retNegativo;
    return it->second;
}

int GetInt(string chave, int retNegativo){
    std::map<string, int>::iterator it;
    it = valoresStringInt.find(chave);
    if (it == valoresStringInt.end())
        return retNegativo;
    return it->second;
}

void dump(){
    printf("starting dump...\n");
    for (std::map<string, int>::iterator it= valoresStringInt.begin(); it!=valoresStringInt.end(); it++){
        printf("%s: %d\n",it->first.c_str(),it->second);
    }
    for (std::map<string, string>::iterator it= valoresStringString.begin(); it!=valoresStringString.end(); it++){
        printf("%s: %s\n",it->first.c_str(),it->second.c_str());
    }
    for (std::map<string, float>::iterator it= valoresStringFloat.begin(); it!=valoresStringFloat.end(); it++){
        printf("%s: %f\n",it->first.c_str(),it->second);
    }
    for (std::map<int, int>::iterator it= valoresIntInt.begin(); it!=valoresIntInt.end(); it++){
        printf("%d: %d\n",it->first,it->second);
    }
    for (std::map<int, string>::iterator it= valoresIntString.begin(); it!=valoresIntString.end(); it++){
        printf("%d: %s\n",it->first,it->second.c_str());
    }
    for (std::map<int, float>::iterator it= valoresIntFloat.begin(); it!=valoresIntFloat.end(); it++){
        printf("%d: %f\n",it->first,it->second);
    }

}
};
typedef CPIGAtributos *PIGAtributos;


#endif //_CPIGATRIBUTOS_
