#ifndef _CPIGMAPACARACTERESDINAMICOS_
#define _CPIGMAPACARACTERESDINAMICOS_

#include "CPIGStringFormatada.h"

class CPIGFonteDinamica:public CPIGFonte{

private:

    //processa uma string para transformá-la em StringFormatada
    CPIGStringFormatada Processa(std::string textoOrig){
        CPIGStringFormatada resp;
        PIGCor cor = BRANCO;
        PIGEstilo estilo = PIG_ESTILO_NORMAL;
        int larguraTotal = 0;
        int estado = 0;//estado atual da máquinda de estados
        int i = 0;

        vector<PIGCor> pilhaCor;
        vector<PIGEstilo> pilhaEstilo;
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
                cor = PIGCriaCorHexa(stringCor);//converte para cor
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
    CPIGFonteDinamica(string nomeFonte, int tamanhoFonte, int idJanela):CPIGFonte(nomeFonte,tamanhoFonte,PIG_ESTILO_NORMAL,BRANCO,idJanela){
        for (int estilo=1;estilo<PIG_TOTALESTILOS;estilo++)
            CriaLetrasSurface(estilo, 0, BRANCO, NULL, BRANCO);
    }

    //escreve uma string já formatada, alinhada com o ponto x,y e o parâmetro pos
    void Escreve(CPIGStringFormatada formatada,int x,bool blend,int y,PIGPosicaoTexto pos=PIG_TEXTO_ESQUERDA,float ang=0){
        int xIni = x;
        x = CalculaXPosicao(x,formatada.LargTotalPixels(),pos);

        PIGCor corAtual = BRANCO;
        PIGEstilo estiloAtual = PIG_ESTILO_NORMAL;

        for (int i=0;i<formatada.size();i++){
            int aux = formatada.GetIntLetra(i);
            int indice = aux-PIG_PRIMEIRO_CAR;
            if (indice<0) continue;

            corAtual = formatada.GetCor(i);
            estiloAtual = formatada.GetEstilo(i);

            caracteres[estiloAtual][indice]->Desenha(x,y,corAtual,ang,{(double)xIni-x,(double)y},blend);

            x += caracteres[estiloAtual][indice]->GetLargura();
        }
    }

    //escreve ums string normal, alinha com o ponto x,y e o parâmetro pos
    void Escreve(string texto,int x,int y,bool blend,PIGCor cor=BRANCO,PIGPosicaoTexto pos=PIG_TEXTO_ESQUERDA,float ang=0)override{
        if (texto=="") return;
        CPIGStringFormatada formatada = Processa(texto);
        Escreve(formatada,x,y,blend,pos,ang);
    }

    //escreve uma string longa (múltiplas linhas), incluindo formatação interna, alinhada de acordo com o ponto x,y e o parâmetro pos
    void EscreveLonga(string texto,int x,int y,int largMax,int espacoEntreLinhas,bool blend,PIGCor corFonte=BRANCO,PIGPosicaoTexto pos=PIG_TEXTO_ESQUERDA,float angulo=0) override{
        if (texto=="") return;
        CPIGStringFormatada formatada = Processa(texto);
        //formatada.Print();
        vector<CPIGStringFormatada> linhas = formatada.ExtraiLinhas(largMax,delimitadores);
        EscreveLonga(linhas,x,y,espacoEntreLinhas,blend,pos,angulo);
        linhas.clear();
        formatada.Clear();
    }

    //escreve uma string longa (múltiplas linhas), com formatação já processada e fornecida, alinhada de acordo com o ponto x,y e o parâmetro pos
    void EscreveLonga(vector<CPIGStringFormatada> linhas, int x, int y, int espacoEntreLinhas,bool blend,PIGPosicaoTexto pos=PIG_TEXTO_ESQUERDA,float angulo=0){
        int yTotal=y;
        for (int k=0;k<linhas.size();k++){
            Escreve(linhas[k],x,yTotal,blend,pos,angulo);
            yTotal -= espacoEntreLinhas;
        }
    }

    //retorna a largura em pixels da string fornecida (faz a formatação internamente)
    int GetLarguraPixelsString(string texto) override{
        if (texto=="") return 0;
        CPIGStringFormatada formatada = Processa(texto);
        int resp = formatada.LargTotalPixels();
        formatada.Clear();
        return resp;
    }

    //retorna as linhas já formatadas e organizadas pela largura máxima fornecida
    vector<CPIGStringFormatada> ExtraiLinhas(string texto, int largMax){
        CPIGStringFormatada formatada = Processa(texto);
        vector<CPIGStringFormatada> linhas = formatada.ExtraiLinhas(largMax,delimitadores);
        formatada.Clear();
        return linhas;
    }
};

typedef CPIGFonteDinamica* PIGFonteDinamica;

#endif //_CPIGMAPACARACTERESDINAMICOS_
