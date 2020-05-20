#include "CPigStringFormatada.h"

class CMapaCaracteresDinamicos:public CMapaCaracteres{

private:



    //cria uma cor a partir de uma string com um valor hexadecimal de 8 algarismos RRGGBBAA. Ex: 0xFF0000FF (vermelho)
    static PIG_Cor CriaCor(char *stringHexa){
        unsigned long total = strtoul(stringHexa,0,16);//transforma a string em um inteiro (decimal)
        PIG_Cor cor;
        cor.a = total %256;
        total /= 256;
        cor.b = total %256;
        total /= 256;
        cor.g = total %256;
        total /= 256;
        cor.r = total %256;
        return cor;
    }

    //processa uma string para transformá-la em StringFormatada
    CPigStringFormatada Processa(std::string textoOrig){
        CPigStringFormatada resp;
        PIG_Cor cor = BRANCO;
        PIG_Estilo estilo = ESTILO_NORMAL;
        int larguraTotal = 0;
        int estado = 0;//estado atual da máquinda de estados
        int i = 0;

        std::vector<PIG_Cor> pilhaCor;
        std::vector<PIG_Estilo> pilhaEstilo;
        pilhaCor.push_back(cor);
        pilhaEstilo.push_back(estilo);

        Uint16 letra,letraAnt;

        while (i<textoOrig.size()){
            letraAnt = letra;
            letra = textoOrig[i];
            letra = letra %256;

            switch (estado){
            case 0://estado sem formatacao
                if (letra == '<'){//alerta de entrada de formatacao
                   estado = 1;
                }else if (letra=='@'){//alerta de saída de cor
                    estado = 3;
                }else if (letra==PIG_SIMBOLO_NEGRITO||letra==PIG_SIMBOLO_ITALICO||letra==PIG_SIMBOLO_SUBLINHADO||letra==PIG_SIMBOLO_CORTADO){//alerta de saída de negrito, itálico, underline ou strike
                    estado = 4;
                }else{
                    larguraTotal += larguraLetra[estilo][letra-PRIMEIRO_CAR];
                    resp.Adiciona(letra,larguraTotal,cor,estilo);
                }
                break;
            case 1://alerta para inicio de formatacao
                if (letra == '@'){//realmente é entrada de cor
                    estado = 2;
                }else if (letra == PIG_SIMBOLO_NEGRITO){//negrito
                    estilo |= ESTILO_NEGRITO;
                    pilhaEstilo.push_back(estilo);
                    estado = 0;
                }else if (letra == PIG_SIMBOLO_ITALICO){
                    estilo |= ESTILO_ITALICO;
                    pilhaEstilo.push_back(estilo);
                    estado = 0;
                }else if (letra == PIG_SIMBOLO_SUBLINHADO){
                    estilo |= ESTILO_SUBLINHADO;
                    pilhaEstilo.push_back(estilo);
                    estado = 0;
                }else if (letra == PIG_SIMBOLO_CORTADO){
                    estilo |= ESTILO_CORTADO;
                    pilhaEstilo.push_back(estilo);
                    estado = 0;
                }else{//não é entrada de cor nem de formatacao de estilo
                    larguraTotal += larguraLetra[estilo][letraAnt-PRIMEIRO_CAR];
                    resp.Adiciona(letraAnt,larguraTotal,cor,estilo);//devolve o token anterior

                    larguraTotal += larguraLetra[estilo][letra-PRIMEIRO_CAR];
                    resp.Adiciona(letra,larguraTotal,cor,estilo);

                    estado = 0;
                }
                break;
            case 2://reconhecimento da cor
                char stringCor[11];
                strncpy(stringCor,&textoOrig[i],10); //pega os caracteres em hexadecimal (ex: 0xffa64312)
                stringCor[10]='\0';

                i+=9;//avança os outros 9 caracteres
                cor = CriaCor(stringCor);//converte para cor
                pilhaCor.push_back(cor);
                estado = 0;
                break;
            case 3://alerta para saida de cor
                if (letra == '>'){//realmente saída da cor
                    pilhaCor.pop_back();
                    if (pilhaCor.size()>1)//tira a cor da pilha e pega a de baixo
                        cor = pilhaCor[pilhaCor.size()-1];
                    else cor = BRANCO;
                }else{//não é saída de cor
                    larguraTotal += larguraLetra[estilo][letraAnt-PRIMEIRO_CAR];
                    resp.Adiciona(letraAnt,larguraTotal,cor,estilo);//devolve o token anterior

                    larguraTotal += larguraLetra[estilo][letra-PRIMEIRO_CAR];
                    resp.Adiciona(letra,larguraTotal,cor,estilo);
                }
                estado = 0;
                break;
            case 4://saida de negrito, itálico, underline ou strike
                if (letra=='>'){
                    pilhaEstilo.pop_back();
                    if (pilhaEstilo.size()>1)//tira a cor da pilha e pega a de baixo
                        estilo = pilhaEstilo[pilhaEstilo.size()-1];
                    else estilo = ESTILO_NORMAL;
                }else{//não é saída de cor
                    larguraTotal += larguraLetra[estilo][letraAnt-PRIMEIRO_CAR];
                    resp.Adiciona(letraAnt,larguraTotal,cor,estilo);//devolve o token anterior

                    larguraTotal += larguraLetra[estilo][letra-PRIMEIRO_CAR];
                    resp.Adiciona(letra,larguraTotal,cor,estilo);
                }
                estado = 0;
                break;
            }
            i++;
        }
        //system("pause");
        pilhaCor.clear();
        pilhaEstilo.clear();
        return resp;
    }

public:

    //construtor com o nome do arquivo da fonte, o tamanha e a janela
    CMapaCaracteresDinamicos(char *nomeFonte, int tamanhoFonte, int idJanela):CMapaCaracteres(){
        IniciaBase(nomeFonte,tamanhoFonte,idJanela, -1);

        for (int estilo=0;estilo<PIG_TOTALESTILOS;estilo++)
            CriaLetras(estilo, 0, BRANCO, NULL, BRANCO);

        SDL_SetRenderTarget(render, NULL);
    }


    //escreve uma string simples, incluindo formatação interna, alinhada à direita do ponto x,y
    void EscreveStringDireita(std::string texto, int x, int y, float ang=0)override{
        CPigStringFormatada formatada = Processa(texto);
        EscreveStringEsquerda(formatada,x-formatada.LargTotalPixels(),y,ang,formatada.LargTotalPixels());
        formatada.Clear();
    }

    //escreve uma string simples, incluindo formatação interna, alinhada no ponto x,y
    void EscreveStringCentralizado(std::string texto, int x, int y, float ang=0)override{
        CPigStringFormatada formatada = Processa(texto);
        EscreveStringEsquerda(formatada,x-formatada.LargTotalPixels()/2,y,ang,formatada.LargTotalPixels()/2);
        formatada.Clear();
    }

    //escreve uma string simples, incluindo formatação interna, alinhada à esquerda do ponto x,y
    void EscreveStringEsquerda(std::string texto, int x, int y, float ang=0, int delta=0)override{
        CPigStringFormatada formatada = Processa(texto);
        EscreveStringEsquerda(formatada,x,y,ang,delta);
        formatada.Clear();
    }


    //escreve uma string simples, com formatação já processada e fornecida, alinhada à direita do ponto x,y
    void EscreveStringDireita(CPigStringFormatada str,int x, int y,float ang=0){
        EscreveStringEsquerda(str,x-str.LargTotalPixels(),y,ang,str.LargTotalPixels());
    }

    //escreve uma string simples, com formatação já processada e fornecida, alinhada no ponto x,y
    void EscreveStringCentralizado(CPigStringFormatada str,int x, int y,float ang=0){
        EscreveStringEsquerda(str,x-str.LargTotalPixels()/2,y,ang,str.LargTotalPixels()/2);
    }

    //escreve uma string simples, com formatação já processada e fornecida, alinhada à esquerda do ponto x,y
    void EscreveStringEsquerda(CPigStringFormatada str,int x, int y,float ang=0, int delta=0){
        //printf("derivada\n");
        SDL_Rect rectDestino;
        rectDestino.x = x;
        //rectDestino.y = CGerenciadorJanelas::GetJanela(janela)->GetAltura()-y-tamFonte;
        PIG_Cor corAtual = BRANCO;
        PIG_Estilo estiloAtual = ESTILO_NORMAL;
        SDL_Point ponto = {delta,tamFonte};

        for (int i=0;i<str.size();i++){
            Uint16 aux = str.GetLetra(i);
            aux = aux %256;
            corAtual = str.GetCor(i);
            estiloAtual = str.GetEstilo(i);

            SDL_SetTextureColorMod(glyphsT[estiloAtual][aux-PRIMEIRO_CAR],corAtual.r,corAtual.g,corAtual.b);

            rectDestino.w = larguraLetra[estiloAtual][aux-PRIMEIRO_CAR];
            rectDestino.h = tamFonte+alturaExtra[estiloAtual][aux-PRIMEIRO_CAR];
            rectDestino.y = CGerenciadorJanelas::GetJanela(janela)->GetAltura()-y-rectDestino.h;

            SDL_RenderCopyEx(render,glyphsT[estiloAtual][aux-PRIMEIRO_CAR],NULL,&rectDestino,-ang,&ponto,FLIP_NENHUM);

            rectDestino.x += rectDestino.w;
            ponto.x -= rectDestino.w;
        }
    }


    //escreve uma string longa (múltiplas linhas), incluindo formatação interna, alinhada à direita do ponto x,y
    void EscreveStringLongaDireita(std::string texto,int x,int y,int largMax,int espacoEntreLinhas,float angulo=0) override{
        CPigStringFormatada formatada = Processa(texto);
        //formatada.Print();
        std::vector<CPigStringFormatada> linhas = formatada.ExtraiLinhas(largMax,PigDelimitadores);
        EscreveStringLongaDireita(linhas,x,y,espacoEntreLinhas,angulo);
        linhas.clear();
        formatada.Clear();
    }

    //escreve uma string longa (múltiplas linhas), incluindo formatação interna, alinhada no ponto x,y
    void EscreveStringLongaCentralizado(std::string texto,int x,int y,int largMax,int espacoEntreLinhas,float angulo=0) override{
        CPigStringFormatada formatada = Processa(texto);
        //formatada.Print();
        std::vector<CPigStringFormatada> linhas = formatada.ExtraiLinhas(largMax,PigDelimitadores);
        EscreveStringLongaCentralizado(linhas,x,y,espacoEntreLinhas,angulo);
        linhas.clear();
        formatada.Clear();
    }

    //escreve uma string longa (múltiplas linhas), incluindo formatação interna, alinhada à esquerda do ponto x,y
    void EscreveStringLongaEsquerda(std::string texto,int x,int y,int largMax,int espacoEntreLinhas,float angulo=0) override{
        CPigStringFormatada formatada = Processa(texto);
        //formatada.Print();
        std::vector<CPigStringFormatada> linhas = formatada.ExtraiLinhas(largMax,PigDelimitadores);
        EscreveStringLongaEsquerda(linhas,x,y,espacoEntreLinhas,angulo);
        linhas.clear();
        formatada.Clear();
    }


    //escreve uma string longa (múltiplas linhas), com formatação já processada e fornecida, alinhada à direita do ponto x,y
    void EscreveStringLongaDireita(std::vector<CPigStringFormatada> linhas, int x, int y, int espacoEntreLinhas,float angulo=0){
        int yTotal=y;
        for (int k=0;k<linhas.size();k++){
            EscreveStringDireita(linhas[k],x,yTotal,angulo);
            yTotal -= espacoEntreLinhas;
        }
    }

    //escreve uma string longa (múltiplas linhas), com formatação já processada e fornecida, alinhada no ponto x,y
    void EscreveStringLongaCentralizado(std::vector<CPigStringFormatada> linhas, int x, int y, int espacoEntreLinhas,float angulo=0){
        int yTotal=y;
        for (int k=0;k<linhas.size();k++){
            EscreveStringCentralizado(linhas[k],x,yTotal,angulo);
            yTotal -= espacoEntreLinhas;
        }
    }

    //escreve uma string longa (múltiplas linhas), com formatação já processada e fornecida, alinhada à esquerda do ponto x,y
    void EscreveStringLongaEsquerda(std::vector<CPigStringFormatada> linhas, int x, int y, int espacoEntreLinhas,float angulo=0){
        int yTotal=y;
        for (int k=0;k<linhas.size();k++){
            EscreveStringEsquerda(linhas[k],x,yTotal,angulo);
            yTotal -= espacoEntreLinhas;
        }
    }


    //retorna a largura em pixels da string fornecida (faz a formatação internamente)
    int GetLarguraPixelsString(std::string texto) override{
        CPigStringFormatada formatada = Processa(texto);
        int resp = formatada.LargTotalPixels();
        formatada.Clear();
        return resp;
    }

    //retorna as linhas já formatadas e organizadas pela largura máxima fornecida
    std::vector<CPigStringFormatada> ExtraiLinhas(std::string texto, int largMax){
        CPigStringFormatada formatada = Processa(texto);
        std::vector<CPigStringFormatada> linhas = formatada.ExtraiLinhas(largMax,PigDelimitadores);
        formatada.Clear();
        return linhas;
    }
};

typedef CMapaCaracteres* MapaCaracteres;
