#ifndef _CPIGATRIBUTOS_
#define _CPIGATRIBUTOS_

class CPIGAtributos{

private:

map<int, string> valoresInt;
map<string, string> valoresString;

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
    valoresInt[chave] = std::to_string(valor);
}

void SetValorInt(string chave, int valor){
    std::transform(chave.begin(), chave.end(),chave.begin(), ::toupper);
    valoresString[chave] = std::to_string(valor);
}

void SetValorFloat(int chave, float valor){
    valoresInt[chave] = std::to_string(valor);
}

void SetValorFloat(string chave, float valor){
    std::transform(chave.begin(), chave.end(),chave.begin(), ::toupper);
    valoresString[chave] = std::to_string(valor);
}

void SetValorString(int chave, string valor){
    valoresInt[chave] = valor;
}

void SetValorString(string chave, string valor){
    std::transform(chave.begin(), chave.end(),chave.begin(), ::toupper);
    valoresString[chave] = valor;
}

bool GetValorInt(int chave, int &valor){
    map<int, string>::iterator it = valoresInt.find(chave);
    if (it == valoresInt.end())
        return false;
    valor = stoi(it->second);
    return true;
}

bool GetValorInt(string chave, int &valor){
    std::transform(chave.begin(), chave.end(),chave.begin(), ::toupper);
    map<string, string>::iterator it = valoresString.find(chave);
    if (it == valoresString.end())
        return false;
    valor = stoi(it->second);
    return true;
}

bool GetValorFloat(int chave, float &valor){
    map<int, string>::iterator it = valoresInt.find(chave);
    if (it == valoresInt.end())
        return false;
    valor = stof(it->second);
    return true;
}

bool GetValorFloat(string chave, float &valor){
    std::transform(chave.begin(), chave.end(),chave.begin(), ::toupper);
    map<string, string>::iterator it = valoresString.find(chave);
    if (it == valoresString.end())
        return false;
    valor = stof(it->second);
    return true;
}

bool GetValorString(int chave, string &valor){
    map<int, string>::iterator it = valoresInt.find(chave);
    if (it == valoresInt.end())
        return false;
    valor = it->second;
    return true;
}

bool GetValorString(string chave, string &valor){
    std::transform(chave.begin(), chave.end(),chave.begin(), ::toupper);
    map<string, string>::iterator it = valoresString.find(chave);
    if (it == valoresString.end())
        return false;
    valor = it->second;
    return true;
}

float GetFloat(string chave, float retNegativo){
    std::transform(chave.begin(), chave.end(),chave.begin(), ::toupper);
    map<string, string>::iterator it = valoresString.find(chave);
    if (it == valoresString.end())
        return retNegativo;
    return stof(it->second);
}

string GetString(string chave, string retNegativo){
    std::transform(chave.begin(), chave.end(),chave.begin(), ::toupper);
    map<string, string>::iterator it = valoresString.find(chave);
    if (it == valoresString.end())
        return retNegativo;
    return it->second;
}

int GetInt(string chave, int retNegativo){
    std::transform(chave.begin(), chave.end(),chave.begin(), ::toupper);
    map<string, string>::iterator it = valoresString.find(chave);
    if (it == valoresString.end())
        return retNegativo;
    return stoi(it->second);
}

void dump(){
    printf("starting dump...\n");

    for (map<string, string>::iterator it= valoresString.begin(); it!=valoresString.end(); it++){
        printf("%s: %s\n",it->first.c_str(),it->second.c_str());
    }

    for (map<int, string>::iterator it= valoresInt.begin(); it!=valoresInt.end(); it++){
        printf("%d: %s\n",it->first,it->second.c_str());
    }
}

static CPIGAtributos GetAtributos(string parametros){
    CPIGAtributos resp;
    stringstream ss(parametros);
    string variavel,valorString;

    while(ss >> variavel){
        ss >> valorString;
        resp.SetValorString(variavel,valorString);
    }

    return resp;
}

};
typedef CPIGAtributos *PIGAtributos;
#endif //_CPIGATRIBUTOS_
