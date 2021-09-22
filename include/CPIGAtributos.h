#ifndef _CPIGATRIBUTOS_
#define _CPIGATRIBUTOS_

class CPIGAtributos{

private:

std::map<int, int> valoresIntInt;
std::map<std::string, int> valoresStringInt;
std::map<int, float> valoresIntFloat;
std::map<std::string, float> valoresStringFloat;
std::map<int, std::string> valoresIntString;
std::map<std::string, std::string> valoresStringString;

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

~CPIGAtributos(){}

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

void SetValorInt(std::string chave, int valor){
    valoresStringInt[chave] = valor;
}

void SetValorFloat(int chave, float valor){
    valoresIntFloat[chave] = valor;
}

void SetValorFloat(std::string chave, float valor){
    valoresStringFloat[chave] = valor;
}

void SetValorString(int chave, std::string valor){
    valoresIntString[chave] = valor;
}

void SetValorString(std::string chave, std::string valor){
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
    std::map<std::string, int>::iterator it;
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
    std::map<std::string, float>::iterator it;
    it = valoresStringFloat.find(chave);
    if (it == valoresStringFloat.end())
        return false;
    valor = it->second;
    return true;
}

bool GetValorString(int chave, std::string &valor){
    std::map<int, std::string>::iterator it;
    it = valoresIntString.find(chave);
    if (it == valoresIntString.end())
        return false;
    valor = it->second;
    return true;
}

bool GetValorString(std::string chave, std::string &valor){
    std::map<std::string, std::string>::iterator it;
    it = valoresStringString.find(chave);
    if (it == valoresStringString.end())
        return false;
    valor = it->second;
    return true;
}

float GetFloat(string chave, float retNegativo){
    std::map<std::string, float>::iterator it;
    it = valoresStringFloat.find(chave);
    if (it == valoresStringFloat.end())
        return retNegativo;
    return it->second;
}

string GetString(string chave, string retNegativo){
    std::map<std::string, string>::iterator it;
    it = valoresStringString.find(chave);
    if (it == valoresStringString.end())
        return retNegativo;
    return it->second;
}

int GetInt(string chave, int retNegativo){
    std::map<std::string, int>::iterator it;
    it = valoresStringInt.find(chave);
    if (it == valoresStringInt.end())
        return retNegativo;
    return it->second;
}

};
typedef CPIGAtributos *PIGAtributos;


#endif //_CPIGATRIBUTOS_
