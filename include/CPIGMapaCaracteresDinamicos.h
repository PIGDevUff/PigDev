#ifndef _CPIGMAPACARACTERESDINAMICOS_
#define _CPIGMAPACARACTERESDINAMICOS_

#include "CPIGStringFormatada.h"

class CPIGMapaCaracteresDinamicos:public CPIGMapaCaracteres{

private:

    //processa uma string para transformá-la em StringFormatada
    CPIGStringFormatada Processa(std::string textoOrig){
        CPIGStringFormatada resp;
        PIG_Cor cor = BRANCO;
        PIG_Estilo estilo = PIG_ESTILO_NORMAL;
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
                    larguraTotal += caracteres[estilo][letra-PIG_PRIMEIRO_CAR]->GetLargura();
                    resp.Adiciona(letra,larguraTotal,cor,estilo);
                }
                break;
            case 1://alerta para inicio de formatacao
                if (letra == '@'){//realmente é entrada de cor
                    estado = 2;
                }else if (letra == PIG_SIMBOLO_NEGRITO){//negrito
                    estilo |= PIG_ESTILO_NEGRITO;
                    pilhaEstilo.push_back(estilo);
                    estado = 0;
                }else if (letra == PIG_SIMBOLO_ITALICO){
                    estilo |= PIG_ESTILO_ITALICO;
                    pilhaEstilo.push_back(estilo);
                    estado = 0;
                }else if (letra == PIG_SIMBOLO_SUBLINHADO){
                    estilo |= PIG_ESTILO_SUBLINHADO;
                    pilhaEstilo.push_back(estilo);
                    estado = 0;
                }else if (letra == PIG_SIMBOLO_CORTADO){
                    estilo |= PIG_ESTILO_CORTADO;
                    pilhaEstilo.push_back(estilo);
                    estado = 0;
                }else{//não é entrada de cor nem de formatacao de estilo
                    larguraTotal += caracteres[estilo][letraAnt-PIG_PRIMEIRO_CAR]->GetLargura();
                    resp.Adiciona(letraAnt,larguraTotal,cor,estilo);//devolve o token anterior

                    larguraTotal += caracteres[estilo][letra-PIG_PRIMEIRO_CAR]->GetLargura();
                    resp.Adiciona(letra,larguraTotal,cor,estilo);

                    estado = 0;
                }
                break;
            case 2://reconhecimento da cor
                char stringCor[11];
                strncpy(stringCor,&textoOrig[i],10); //pega os caracteres em hexadecimal (ex: 0xffa64312)
                stringCor[10]='\0';

                i+=9;//avança os outros 9 caracteres
                cor = PIGCriaCor(stringCor);//converte para cor
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
                    larguraTotal += caracteres[estilo][letraAnt-PIG_PRIMEIRO_CAR]->GetLargura();
                    resp.Adiciona(letraAnt,larguraTotal,cor,estilo);//devolve o token anterior

                    larguraTotal += caracteres[estilo][letra-PIG_PRIMEIRO_CAR]->GetLargura();
                    resp.Adiciona(letra,larguraTotal,cor,estilo);
                }
                estado = 0;
                break;
            case 4://saida de negrito, itálico, underline ou strike
                if (letra=='>'){
                    pilhaEstilo.pop_back();
                    if (pilhaEstilo.size()>1)//tira a cor da pilha e pega a de baixo
                        estilo = pilhaEstilo[pilhaEstilo.size()-1];
                    else estilo = PIG_ESTILO_NORMAL;
                }else{//não é saída de cor
                    larguraTotal += caracteres[estilo][letraAnt-PIG_PRIMEIRO_CAR]->GetLargura();
                    resp.Adiciona(letraAnt,larguraTotal,cor,estilo);//devolve o token anterior

                    larguraTotal += caracteres[estilo][letra-PIG_PRIMEIRO_CAR]->GetLargura();
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
    CPIGMapaCaracteresDinamicos(char *nomeFonte, int tamanhoFonte, int idJanela):CPIGMapaCaracteres(nomeFonte,tamanhoFonte,PIG_ESTILO_NORMAL,BRANCO,idJanela){
        for (int estilo=1;estilo<PIG_TOTALESTILOS;estilo++)
            CriaLetrasSurface(estilo, 0, BRANCO, NULL, BRANCO);
    }

    //escreve uma string já formatada, alinhada com o ponto x,y e o parâmetro pos
    void Escreve(CPIGStringFormatada formatada,int x,bool blend,int y,PIG_PosTexto pos=PIG_TEXTO_ESQUERDA,float ang=0){
        int xIni = x;
        x = CalculaXPosicao(x,formatada.LargTotalPixels(),pos);

        PIG_Cor corAtual = BRANCO;
        PIG_Estilo estiloAtual = PIG_ESTILO_NORMAL;

        for (int i=0;i<formatada.size();i++){
            Uint16 aux = formatada.GetLetra(i);
            //if (aux==65475) continue;
            //if (aux>6500) aux+=64;
            aux = aux % 256;//UTF16 string, retirando só o byte que interessa
            if (aux-PIG_PRIMEIRO_CAR<0) continue;

            corAtual = formatada.GetCor(i);
            estiloAtual = formatada.GetEstilo(i);

            caracteres[estiloAtual][aux-PIG_PRIMEIRO_CAR]->Desenha(x,y,corAtual,ang,{(double)xIni-x,(double)y},blend);

            x += caracteres[estiloAtual][aux-PIG_PRIMEIRO_CAR]->GetLargura();
        }
    }

    //escreve ums string normal, alinha com o ponto x,y e o parâmetro pos
    void Escreve(std::string texto,int x,int y,bool blend,PIG_Cor cor=BRANCO,PIG_PosTexto pos=PIG_TEXTO_ESQUERDA,float ang=0)override{
        if (texto=="") return;
        CPIGStringFormatada formatada = Processa(texto);
        Escreve(formatada,x,y,blend,pos,ang);
    }

    //escreve uma string longa (múltiplas linhas), incluindo formatação interna, alinhada de acordo com o ponto x,y e o parâmetro pos
    void EscreveLonga(std::string texto,int x,int y,int largMax,int espacoEntreLinhas,bool blend,PIG_Cor corFonte=BRANCO,PIG_PosTexto pos=PIG_TEXTO_ESQUERDA,float angulo=0) override{
        if (texto=="") return;
        CPIGStringFormatada formatada = Processa(texto);
        //formatada.Print();
        std::vector<CPIGStringFormatada> linhas = formatada.ExtraiLinhas(largMax,delimitadores);
        EscreveLonga(linhas,x,y,espacoEntreLinhas,blend,pos,angulo);
        linhas.clear();
        formatada.Clear();
    }

    //escreve uma string longa (múltiplas linhas), com formatação já processada e fornecida, alinhada de acordo com o ponto x,y e o parâmetro pos
    void EscreveLonga(std::vector<CPIGStringFormatada> linhas, int x, int y, int espacoEntreLinhas,bool blend,PIG_PosTexto pos=PIG_TEXTO_ESQUERDA,float angulo=0){
        int yTotal=y;
        for (int k=0;k<linhas.size();k++){
            Escreve(linhas[k],x,yTotal,blend,pos,angulo);
            yTotal -= espacoEntreLinhas;
        }
    }

    //retorna a largura em pixels da string fornecida (faz a formatação internamente)
    int GetLarguraPixelsString(std::string texto) override{
        if (texto=="") return 0;
        CPIGStringFormatada formatada = Processa(texto);
        int resp = formatada.LargTotalPixels();
        formatada.Clear();
        return resp;
    }

    //retorna as linhas já formatadas e organizadas pela largura máxima fornecida
    std::vector<CPIGStringFormatada> ExtraiLinhas(std::string texto, int largMax){
        CPIGStringFormatada formatada = Processa(texto);
        std::vector<CPIGStringFormatada> linhas = formatada.ExtraiLinhas(largMax,delimitadores);
        formatada.Clear();
        return linhas;
    }
};

typedef CPIGMapaCaracteresDinamicos* PIGMapaCaracteresDinamicos;

#endif //_CPIGMAPACARACTERESDINAMICOS_
