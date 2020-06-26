using namespace std;

//classe base de erros na PIG
class CPigErro{

protected:

    std::string mensagem;
    int codErro;


public:
    CPigErro(){
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
class CPigErroArquivo: public CPigErro{

protected:
    std::string nomeArquivo;

public:

    CPigErroArquivo(std::string nomeArq):CPigErro(){
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
class CPigErroParametro: public CPigErro{

protected:
    std::string nomeParam;
    std::string nomeArq;

public:

    CPigErroParametro(std::string parametro,std::string arquivo):CPigErro(){
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
class CPigErroIndice: public CPigErro{

protected:
    std::string tipoDado;
    int indice;

public:

    CPigErroIndice(int indVetor,std::string tipoDeDado):CPigErro(){
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

