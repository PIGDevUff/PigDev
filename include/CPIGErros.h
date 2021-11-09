//classe base de erros na PIG
class CPIGErro{

protected:

    string mensagem;
    int codErro;


public:
    CPIGErro(){
        codErro = 1;
    }

    string GetMensagem(){
        return mensagem;
    }

    int GetCodigoErro(){
        return codErro;
    }

    void PrintErro(){
        cout <<" Erro " <<codErro<<": "<<mensagem<<endl;
    }
};


//Erro para abertura de arquivo em geral (imagem, audio, video, etc)
class CPIGErroArquivo: public CPIGErro{

protected:
    string nomeArquivo;

public:

    CPIGErroArquivo(string nomeArq):CPIGErro(){
        nomeArquivo = nomeArq;
        mensagem = "Nao foi possivel abrir o arquivo <"+nomeArq+">";
        codErro = 2;
        PrintErro();
    }

    string GetNomeArquivo(){
        return nomeArquivo;
    }

};


//Erro para falta de parâmetro ou valor incorreto
class CPIGErroParametro: public CPIGErro{

protected:
    string nomeParam;
    string nomeArq;

public:

    CPIGErroParametro(string parametro,string arquivo):CPIGErro(){
        nomeParam = parametro;
        nomeArq = arquivo;
        mensagem = "O parametro <"+nomeParam+"> nao foi definido ou possui valor incorreto no arquivo ("+nomeArq+")";
        codErro = 3;
        PrintErro();
    }

    string GetNomeParam(){
        return nomeParam;
    }

    string GetNomeArquivo(){
        return nomeArq;
    }

};

//Erro para índices de arrays
class CPIGErroIndice: public CPIGErro{

protected:
    string tipoDado;
    int indice;

public:

    CPIGErroIndice(int indVetor,string tipoDeDado):CPIGErro(){
        tipoDado = tipoDeDado;
        indice = indVetor;
        mensagem = "O indice <"+std::to_string(indice)+"> nao pode ser utlizado para referenciar um ("+tipoDado+")";
        codErro = 4;
        PrintErro();
    }

    string GetTipoDado(){
        return tipoDado;
    }

    int GetIndice(){
        return indice;
    }

};

//Erro para ponteiros especificos
class CPIGErroPonteiro: public CPIGErro{

protected:
    string tipoDado;
    int indice;

public:

    CPIGErroPonteiro(string tipoDeDado):CPIGErro(){
        tipoDado = tipoDeDado;
        indice = -1;
        mensagem = "Ponteiro <"+tipoDado+"> com valor NULO ou inconsistente";
        codErro = 5;
        PrintErro();
    }

    string GetTipoDado(){
        return tipoDado;
    }

    int GetIndice(){
        return indice;
    }

};

