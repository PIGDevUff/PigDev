#ifndef _CPIGSTRINGFORMATADA_
#define _CPIGSTRINGFORMATADA_

class CPIGStringFormatada{

    vector<int> letras;
    vector<int> largAcumulada;
    vector<PIGCor> cores;
    vector<PIGEstilo> estilos;

public:

    ~CPIGStringFormatada(){
        Clear();
    }

    int GetIntLetra(int indice){
        return letras[indice];
    }

    PIGCor GetCor(int indice){
        return cores[indice];
    }

    PIGEstilo GetEstilo(int indice){
        return estilos[indice];
    }

    void Clear(){
        letras.clear();
        largAcumulada.clear();
        cores.clear();
        estilos.clear();
    }

    void Adiciona(int letra, int larguraAcumulada, PIGCor cor, PIGEstilo estilo){
        letras.push_back(letra);
        largAcumulada.push_back(larguraAcumulada);
        cores.push_back(cor);
        estilos.push_back(estilo);
    }


    /*void Print(){
        EXECUTA_SE_DEBUG(printf("__%s__ (%d)\n",letras.c_str(),LargTotalPixels()));
    }*/

    int LargTotalPixels(){
        if (letras.size()>0)
            return largAcumulada[letras.size()-1];
        return 0;
    }

    int size(){
        return letras.size();
    }

    vector<CPIGStringFormatada> SeparaPalavras(string delim){
        vector<CPIGStringFormatada> resp;
        if (letras.size()==0) return resp;
        int largBase=0;
        CPIGStringFormatada strAtual;
        for (unsigned int i=0;i<letras.size();i++){

            bool achou = false;
            for (char c:delim){
                if (c==letras[i])
                    achou = true;
            }

            if (achou){//achou delimitadores
                resp.push_back(strAtual);
                //strAtual.Print();
                strAtual.Clear();
                strAtual.Adiciona(letras[i],largAcumulada[i]-largBase,cores[i],estilos[i]);
                if (letras[i]!='\n'){
                    resp.push_back(strAtual);
                }

                strAtual.Clear();
                largBase = largAcumulada[i];
            }else strAtual.Adiciona(letras[i],largAcumulada[i]-largBase,cores[i],estilos[i]);
        }
        if (strAtual.letras.size()>0){
            resp.push_back(strAtual);
            //strAtual.Print();
        }
        return resp;
    }

    vector<CPIGStringFormatada> ExtraiLinhas(int largMax, string delim){
        vector<CPIGStringFormatada> resp;
        if (letras.size()==0) return resp;
        vector<CPIGStringFormatada> palavras = SeparaPalavras(delim);

        CPIGStringFormatada linhaAtual = palavras[0];   //linha atual (que está sendo montada) contém pelo menos a primeira palavra

        for (unsigned int i=1;i<palavras.size();i++){
            CPIGStringFormatada palavra = palavras[i];   //pega a próxima palavra

            if (linhaAtual.LargTotalPixels() + palavra.LargTotalPixels() > largMax){//a palavra estouraria a largura máxima se fosse agregada                if (ttttt==0){
                resp.push_back(linhaAtual); //coloca a linha que está montada no vetor de linhas
                linhaAtual = palavra; //a palavra que estouraria o limite começa a próxima linha
            }else{//não estourou o limite
                linhaAtual += palavra;
            }

            if (palavra.letras[palavra.letras.size()-1]=='\n'){//se existe uma quebra de linha forçada
                resp.push_back(linhaAtual);

                if (++i<palavras.size()){
                    linhaAtual = palavras[i]; //começa uma nova linha com a p´roxima palavra
                }else linhaAtual.letras.clear();
            }
        }

        if (linhaAtual.letras.size()>0){
            resp.push_back(linhaAtual); //pega a linha que sobrou do processamento (última linha que não foi quebrada)
        }

        palavras.clear();
        return resp;
    }

    CPIGStringFormatada operator +=(CPIGStringFormatada outra){
        int largAtual = LargTotalPixels();
        for (unsigned int i=0;i<outra.letras.size();i++){
            Adiciona(outra.letras[i],outra.largAcumulada[i]+largAtual,outra.cores[i],outra.estilos[i]);
        }
        return *this;
    }
};

#endif //_CPIGSTRINGFORMATADA_
