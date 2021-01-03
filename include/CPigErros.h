using namespace std;

//classe base de erros na PIG
class CPIGErro{

protected:

    std::string mensagem;
    int codErro;


public:
    CPIGErro(){
        codErro = 1;
    }

    std::string GetMensagem(){
        return mensagem;
    }

    int GetCodigoErro(){
        return codErro;
    }

    void PrintErro(){
        std::cout <<" Erro " <<codErro<<": "<<mensagem<<std::endl;
    }
};


//Erro para abertura de arquivo em geral (imagem, audio, video, etc)
class CPIGErroArquivo: public CPIGErro{

protected:
    std::string nomeArquivo;

public:

    CPIGErroArquivo(std::string nomeArq):CPIGErro(){
        nomeArquivo = nomeArq;
        mensagem = "Nao foi possivel abrir o arquivo <"+nomeArq+">";
        codErro = 2;
        PrintErro();
    }

    std::string GetNomeArquivo(){
        return nomeArquivo;
    }

};


//Erro para falta de parâmetro ou valor incorreto
class CPIGErroParametro: public CPIGErro{

protected:
    std::string nomeParam;
    std::string nomeArq;

public:

    CPIGErroParametro(std::string parametro,std::string arquivo):CPIGErro(){
        nomeParam = parametro;
        nomeArq = arquivo;
        mensagem = "O parametro <"+nomeParam+"> nao foi definido ou possui valor incorreto no arquivo ("+nomeArq+")";
        codErro = 3;
        PrintErro();
    }

    std::string GetNomeParam(){
        return nomeParam;
    }

    std::string GetNomeArquivo(){
        return nomeArq;
    }

};

//Erro para índices de arrays
class CPIGErroIndice: public CPIGErro{

protected:
    std::string tipoDado;
    int indice;

public:

    CPIGErroIndice(int indVetor,std::string tipoDeDado):CPIGErro(){
        tipoDado = tipoDeDado;
        indice = indVetor;
        mensagem = "O indice <"+std::to_string(indice)+"> nao pode ser utlizado para referenciar um ("+tipoDado+")";
        codErro = 4;
        PrintErro();
    }

    std::string GetTipoDado(){
        return tipoDado;
    }

    int GetIndice(){
        return indice;
    }

};

//Erro para índices de arrays
class CPIGErroPonteiro: public CPIGErro{

protected:
    std::string tipoDado;
    int indice;

public:

    CPIGErroPonteiro(std::string tipoDeDado):CPIGErro(){
        tipoDado = tipoDeDado;
        indice = -1;
        mensagem = "Ponteiro <"+tipoDado+"> com valor NULO ou inconsistente";
        codErro = 5;
        PrintErro();
    }

    std::string GetTipoDado(){
        return tipoDado;
    }

    int GetIndice(){
        return indice;
    }

};

