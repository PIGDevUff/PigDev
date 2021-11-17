#ifndef _CPIGMAPACARACTERESDINAMICOS_
#define _CPIGMAPACARACTERESDINAMICOS_

#include "CPIGStringFormatada.h"

class CPIGMapaCaracteresDinamicos:public CPIGMapaCaracteres{

private:

    //processa uma string para transformá-la em StringFormatada
    CPIGStringFormatada Processa(string textoOrig){
        CPIGStringFormatada resp;
        PIGCor cor = BRANCO;
        PIGEstilo estilo = PIG_ESTILO_NORMAL;
        int larguraTotal = 0;
        int estado = 0;//estado atual da máquinda de estados
        unsigned int i = 0;

        vector<PIGCor> pilhaCor;
        vector<PIGEstilo> pilhaEstilo;
        pilhaCor.push_back(cor);
        pilhaEstilo.push_back(estilo);

        Uint16 letra,letraAnt;

        while (i<textoOrig.size()){
            letraAnt = letra;
            letra = textoOrig[i];
            //letra = letra %256;
            letra = ConvChar(letra);

            switch (estado){
            case 0://estado sem formatacao
                if (letra == '<'){//alerta de entrada de formatacao
                   estado = 1;
                }else if (letra=='@'){//alerta de saída de cor
                    estado = 3;
                }else if (letra==PIG_SIMBOLO_NEGRITO||letra==PIG_SIMBOLO_ITALICO||letra==PIG_SIMBOLO_SUBLINHADO||letra==PIG_SIMBOLO_CORTADO){//alerta de saída de negrito, itálico, underline ou strike
                    estado = 4;
                }else{
                    larguraTotal += larguraLetra[estilo][letra-PIG_PRIMEIRO_CAR];
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
                    larguraTotal += larguraLetra[estilo][letraAnt-PIG_PRIMEIRO_CAR];
                    resp.Adiciona(letraAnt,larguraTotal,cor,estilo);//devolve o token anterior

                    larguraTotal += larguraLetra[estilo][letra-PIG_PRIMEIRO_CAR];
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
                    larguraTotal += larguraLetra[estilo][letraAnt-PIG_PRIMEIRO_CAR];
                    resp.Adiciona(letraAnt,larguraTotal,cor,estilo);//devolve o token anterior

                    larguraTotal += larguraLetra[estilo][letra-PIG_PRIMEIRO_CAR];
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
                    larguraTotal += larguraLetra[estilo][letraAnt-PIG_PRIMEIRO_CAR];
                    resp.Adiciona(letraAnt,larguraTotal,cor,estilo);//devolve o token anterior

                    larguraTotal += larguraLetra[estilo][letra-PIG_PRIMEIRO_CAR];
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
    CPIGMapaCaracteresDinamicos(string nomeFonte, int tamanhoFonte, int idJanela):CPIGMapaCaracteres(nomeFonte,tamanhoFonte,PIG_ESTILO_NORMAL,BRANCO,idJanela){
        for (int estilo=1;estilo<PIG_TOTALESTILOS;estilo++)
            CriaLetrasSurface(estilo, 0, BRANCO, NULL, BRANCO);

        SDL_SetRenderTarget(render, NULL);
    }

    //escreve uma string já formatada, alinhada com o ponto x,y e o parâmetro pos
    void Escreve(CPIGStringFormatada formatada, int x, int y, PIGPosTexto pos=PIG_TEXTO_ESQUERDA, float ang=0, int alvoTextura=0){
        int delta = 0;
        switch(pos){
        case PIG_TEXTO_ESQUERDA:
            break;
        case PIG_TEXTO_DIREITA:
            x -= formatada.LargTotalPixels();delta = formatada.LargTotalPixels();break;
        case PIG_TEXTO_CENTRO:
            x -= formatada.LargTotalPixels()/2;delta = formatada.LargTotalPixels()/2;break;
        }

        SDL_Rect rectDestino;
        rectDestino.x = x;
        int *altJanela = CPIGGerenciadorJanelas::GetJanela(janela)->GetAltura();
        //rectDestino.y = CGerenciadorJanelas::GetJanela(janela)->GetAltura()-y-tamFonte;
        PIGCor corAtual = BRANCO;
        PIGEstilo estiloAtual = PIG_ESTILO_NORMAL;
        SDL_Point ponto = {delta,tamFonte};

        for (int i=0;i<formatada.size();i++){
            Uint16 aux = formatada.GetLetra(i);

            aux = ConvChar(aux);
            if (aux-PIG_PRIMEIRO_CAR<0) continue;
            corAtual = formatada.GetCor(i);
            estiloAtual = formatada.GetEstilo(i);

            if (alvoTextura)
                SDL_SetTextureBlendMode(glyphsT[estiloAtual][aux-PIG_PRIMEIRO_CAR], SDL_BLENDMODE_NONE);
            else SDL_SetTextureBlendMode(glyphsT[estiloAtual][aux-PIG_PRIMEIRO_CAR], SDL_BLENDMODE_BLEND);

            SDL_SetTextureColorMod(glyphsT[estiloAtual][aux-PIG_PRIMEIRO_CAR],corAtual.r,corAtual.g,corAtual.b);

            rectDestino.w = larguraLetra[estiloAtual][aux-PIG_PRIMEIRO_CAR];
            rectDestino.h = tamFonte+alturaExtra[estiloAtual][aux-PIG_PRIMEIRO_CAR];
            rectDestino.y = *altJanela-y-rectDestino.h;

            SDL_RenderCopyEx(render,glyphsT[estiloAtual][aux-PIG_PRIMEIRO_CAR],NULL,&rectDestino,-ang,&ponto,PIG_FLIP_NENHUM);

            rectDestino.x += rectDestino.w;
            ponto.x -= rectDestino.w;
        }
    }

    //escreve ums string normal, alinha com o ponto x,y e o parâmetro pos
    void Escreve(string texto, int x, int y, PIGCor cor=BRANCO, PIGPosTexto pos=PIG_TEXTO_ESQUERDA, float ang=0, int alvoTextura=0)override{
        if (texto=="") return;
        CPIGStringFormatada formatada = Processa(texto);
        Escreve(formatada,x,y,pos,ang,alvoTextura);
    }

    void Escreve(string texto, SDL_Texture *textura, PIGCor cor){
        SDL_SetRenderTarget(render,textura);
        SDL_SetRenderDrawColor(render,0,0,0,0);
        int *altJanela = CPIGGerenciadorJanelas::GetJanela(janela)->GetAltura();

        SDL_SetTextureBlendMode(textura, SDL_BLENDMODE_BLEND);
        SDL_SetTextureColorMod(textura,cor.r,cor.g,cor.b);

        Escreve(texto,0,*altJanela-tamFonte+fontDescent,cor,PIG_TEXTO_ESQUERDA,0,1);

        SDL_SetRenderTarget(render, NULL);
    }

    //escreve uma string longa (múltiplas linhas), incluindo formatação interna, alinhada de acordo com o ponto x,y e o parâmetro pos
    void EscreveLonga(string texto, int x, int y, int largMax, int espacoEntreLinhas, PIGCor corFonte=BRANCO, PIGPosTexto pos=PIG_TEXTO_ESQUERDA, float angulo=0) override{
        if (texto=="") return;
        CPIGStringFormatada formatada = Processa(texto);
        //formatada.Print();
        vector<CPIGStringFormatada> linhas = formatada.ExtraiLinhas(largMax,delimitadores);
        EscreveLonga(linhas,x,y,espacoEntreLinhas,pos,angulo);
        linhas.clear();
        formatada.Clear();
    }

    //escreve uma string longa (múltiplas linhas), com formatação já processada e fornecida, alinhada de acordo com o ponto x,y e o parâmetro pos
    void EscreveLonga(vector<CPIGStringFormatada> linhas, int x, int y, int espacoEntreLinhas, PIGPosTexto pos=PIG_TEXTO_ESQUERDA, float angulo=0){
        int yTotal=y;
        for (unsigned int k=0;k<linhas.size();k++){
            Escreve(linhas[k],x,yTotal,pos,angulo);
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

typedef CPIGMapaCaracteresDinamicos* PIGMapaCaracteresDinamicos;
#endif //_CPIGMAPACARACTERESDINAMICOS_
