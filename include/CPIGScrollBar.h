#ifndef _CPIGSCROLLBAR_
#define _CPIGSCROLLBAR_

#include "CPIGComponente.h"
#include "CPIGBotao.h"

typedef enum{PIG_HORIZONTAL,PIG_VERTICAL}PIG_Orientacao;

//tipo de função a ser usada em alterações na posição do handle da barra
//o parâmetro int devolverá à função o identificador do botão
//o parâmetro double devolverá à função a porcentagem atual da barra
//o parâmetro void* devolverá à função um parâmetro personalizado passado ao método DefineAcao();
//typedef void (*AcaoScroll)(int,double,void*);

class CPIGScrollBar : public CPIGComponente{

    int vMin,vAtual,vMax;
    double porcentagemConcluida;
    PIG_Orientacao orientacao;
    int xOriginal,yOriginal;
    PIGBotao botao1,botao2,handle;
    int altBotoes,largHandle,largUtil;
    int deltaBotao,deltaRodinha,deltaTeclado;
    int comprimento,largura;
    bool orientacaoCrescimento;
    int largReal,altReal;
    void *param;
    PIG_FuncaoSimples acao;
    SDL_Rect areaDeAcaoScroll;

    static int AcaoSetas(int idBotao, void* pontObjeto){
        CPIGScrollBar *scroll = (CPIGScrollBar*) pontObjeto;
        if (idBotao==scroll->id+1){
            scroll->AvancaHandle(scroll->vAtual,-scroll->deltaBotao);
        }else if (idBotao==scroll->id+2){
            scroll->AvancaHandle(scroll->vAtual,scroll->deltaBotao);
        }
        return 1;
    }

/***************Novos Métodos**************/


    void SetHabilitado(bool valor){
        habilitado = valor;
    }

    void SetFoco(bool valor){
        temFoco = valor;
    }

    void SetAcionado(bool valor){
        acionado = valor;
    }

    void SetMouseOver(bool valor){
        mouseOver = valor;
    }

/***************Métodos Modificados**************/

    void AjustaOrientacao(){
        if(orientacao == PIG_HORIZONTAL){
            CPIGSprite::SetDimensoes(largura,comprimento - (2*altBotoes));
            largReal = comprimento;
            altReal = largura;
            CPIGSprite::Move(xOriginal+altBotoes,yOriginal);
            if(botao1 && botao2){
                botao1->Move(xOriginal,yOriginal);
                botao2->Move(xOriginal + comprimento - altBotoes,yOriginal);
            }
            handle->Move(xOriginal+altBotoes +porcentagemConcluida*largUtil,yOriginal);
            handle->SetDimensoes(largura,largHandle);
            SetValorMinMax(vMin,vMax);
        }else{
            CPIGSprite::SetDimensoes(comprimento - (2*altBotoes),largura);
            largReal = largura;
            altReal = comprimento;
            CPIGSprite::Move(xOriginal,yOriginal+altBotoes);
            if(botao1 && botao2){
                botao1->Move(xOriginal,yOriginal);
                botao2->Move(xOriginal,yOriginal + comprimento - altBotoes);
            }
            handle->Move(xOriginal,yOriginal + altBotoes+porcentagemConcluida*largUtil);
            handle->SetDimensoes(largHandle,largura);
            SetValorMinMax(vMin,vMax);
        }
        AvancaHandle(vAtual);
    }

    void AjustaHandle(){
        if(orientacao == PIG_HORIZONTAL){
            if(orientacaoCrescimento)handle->Move(xOriginal+altBotoes +porcentagemConcluida*largUtil,yOriginal);
            else handle->Move(pos.x + larg - largHandle - porcentagemConcluida*largUtil,yOriginal);
        }else{
            if(orientacaoCrescimento)handle->Move(xOriginal,yOriginal + altBotoes + porcentagemConcluida*largUtil);
            else handle->Move(xOriginal,yOriginal + altBotoes + alt - largHandle - porcentagemConcluida*largUtil);
        }
    }

    //Recebe um valor e move o handle de forma proporcional
    void AvancaHandle(int novoValor,int delta = 0){
        if(!orientacaoCrescimento) delta = -delta;
        vAtual = PIGLimitaValor(novoValor + delta,vMin,vMax);
        porcentagemConcluida = (1.0 * (vAtual - vMin))/(vMax - vMin);
        AjustaHandle();
        if (acao) acao(id,param);
    }

/*******************************************/
    int TrataClickTrilha(int px,int py){
        if(orientacao == PIG_HORIZONTAL){
            if(orientacaoCrescimento)porcentagemConcluida = (1.0 * ((px - largHandle/2) - pos.x))/(largUtil);
            else porcentagemConcluida = (1.0 * (pos.x + larg - (px + largHandle/2)))/(largUtil);
        }else{
            if(orientacaoCrescimento) porcentagemConcluida = (1.0 * ((py - largHandle/2) - pos.y))/(largUtil);
            else porcentagemConcluida = (1.0 * (pos.y + alt - (py + largHandle/2)))/(largUtil);
        }

        AvancaHandle(porcentagemConcluida*(vMax - vMin) + vMin,0);
        return PIG_SELECIONADO_TRATADO;
    }

    int TrataBotoes(PIG_Evento evento){
        if(botao1 && botao2){
            if(botao1->TrataEventoMouse(evento) == PIG_SELECIONADO_TRATADO || botao2->TrataEventoMouse(evento) == PIG_SELECIONADO_TRATADO) return PIG_SELECIONADO_TRATADO;
        }
        return PIG_NAO_SELECIONADO;
    }

    int TrataRodinha(PIG_Evento evento){
        if(evento.mouse.relY > 0){
            AvancaHandle(vAtual,deltaRodinha);
            return PIG_SELECIONADO_TRATADO;
        }else if (evento.mouse.relY < 0){
            AvancaHandle(vAtual,-deltaRodinha);
            return PIG_SELECIONADO_TRATADO;
        }
        return PIG_NAO_SELECIONADO;
    }

    //detecta se o mouse está sobre o componente ou não
    bool ChecaMouseOverAreaScroll(SDL_Point pMouse){
        if (visivel==false||habilitado==false)
            return -1;

        return SDL_PointInRect(&pMouse,&areaDeAcaoScroll);
    }

public:

    CPIGScrollBar(int idComponente,int px, int py,int larguraTotal,int comprimentoTotal,int larguraHandle,std::string imgHandle,std::string imgTrilha,int retiraFundoHandle=1,int retiraFundoTrilha=1,int janela=0):
        CPIGComponente(idComponente,px,py,larguraTotal,comprimentoTotal,imgTrilha,retiraFundoTrilha,janela){
            botao1 = botao2 = NULL;
            vMin = vAtual = 0;
            vMax = 100;
            porcentagemConcluida = 0;
            orientacao = PIG_HORIZONTAL;
            xOriginal = pos.x;
            yOriginal = pos.y;
            largReal = comprimento = comprimentoTotal;
            altReal = largura = larguraTotal;
            altBotoes = 0;
            deltaBotao = 1;
            deltaTeclado = deltaRodinha = 10;
            largHandle = larguraHandle;
            handle = new CPIGBotao(0,pos.x + altBotoes,pos.y,largura,largHandle,imgHandle,retiraFundoHandle,idJanela);
            handle->DefineBotaoRepeticao(true);
            handle->DefineTempoRepeticao(0.01);
            largUtil = comprimento - (2*altBotoes) - largHandle;
            acao = NULL;
            param = NULL;
            orientacaoCrescimento = true;
            AjustaOrientacao();
            AjustaHandle();
            areaDeAcaoScroll = {0,0,0,0};
    }

    CPIGScrollBar(std::string nomeArqParam):CPIGScrollBar(LeArquivoParametros(nomeArqParam)){}

    ~CPIGScrollBar(){
        if (botao1) delete botao1;
        if (botao2) delete botao2;
        delete handle;
    }

    static CPIGScrollBar LeArquivoParametros(std::string nomeArqParam){

        std::ifstream arquivo;
        int idComponente,px,py,larguraTotal,larguraHandle,comprimentoTotal,retiraFundoHandle=1,retiraFundoTrilha=1,janela=0;
        std::string imgHandle = "",imgTrilha = "",variavel;

        arquivo.open(nomeArqParam);

        if(!arquivo.is_open()) throw CPIGErroArquivo(nomeArqParam);
        //formato "x valor"
        while(!arquivo.eof()){
           arquivo >> variavel;
            if(variavel == "idComponente") arquivo >> idComponente;
            if(variavel == "px") arquivo >> px;
            if(variavel == "py") arquivo >> py;
            if(variavel == "larguraTotal") arquivo >> larguraTotal;
            if(variavel == "larguraHandle") arquivo >> larguraHandle;
            if(variavel == "comprimentoTotal") arquivo >> comprimentoTotal;
            if(variavel == "imgHandle") arquivo >> imgHandle;
            if(variavel == "imgTrilha") arquivo >> imgTrilha;
            if(variavel == "retiraFundoHandle") arquivo >> retiraFundoHandle;
            if(variavel == "retiraFundoTrilha") arquivo >> retiraFundoTrilha;
            if(variavel == "janela") arquivo >> janela;
        }

        arquivo.close();

        if(imgHandle == "") throw CPIGErroParametro("imgHandle",nomeArqParam);
        if(imgTrilha == "") throw CPIGErroParametro("imgTrilha",nomeArqParam);

       // std::cout<<idComponente<<" "<<px<<" "<<py<<" "<<altura<<" "<<largura<<" "<<nomeArq<<" "<<retiraFundo<<" "<<janela<<std::endl;
        return CPIGScrollBar(idComponente,px,py,larguraTotal,comprimentoTotal,larguraHandle,imgHandle,imgTrilha,retiraFundoHandle,retiraFundoTrilha,janela);
    }

    void SetBotoes(int alturaBotoes,std::string imgBotao1,std::string imgBotao2,int retiraFundoB1 = 1,int retiraFundoB2 = 1){
        if (botao1==NULL){
            botao1 = new CPIGBotao(id + 1,xOriginal,yOriginal,alturaBotoes,largura,imgBotao1,retiraFundoB1,idJanela);
            botao2 = new CPIGBotao(id + 2,xOriginal,yOriginal,alturaBotoes,largura,imgBotao2,retiraFundoB2,idJanela);
            botao1->DefineAcao(AcaoSetas,this);
            botao2->DefineAcao(AcaoSetas,this);
            botao1->DefineBotaoRepeticao(true);
            botao2->DefineBotaoRepeticao(true);
            botao1->DefineTempoRepeticao(0.01);
            botao2->DefineTempoRepeticao(0.01);
            altBotoes = alturaBotoes;
            largUtil = comprimento - (2*altBotoes) - largHandle;
            AjustaOrientacao();
        }
    }

    void SetOrientacao(PIG_Orientacao novaOrientacao){
        orientacao = novaOrientacao;
        AjustaOrientacao();
    }
/*
    int TrataEvento(PIG_Evento evento){
        if(visivel==false||habilitado==false) return PIG_NAO_SELECIONADO;
        if(evento.tipoEvento == EVENTO_NULO) return PIG_NAO_SELECIONADO;
        //if(TrataBotoes(evento) == PIG_SELECIONADO_TRATADO) return PIG_SELECIONADO_TRATADO;
        if(evento.tipoEvento == EVENTO_TECLADO && setasAtivadas) return TrataEventoTeclado(evento);
        if(evento.tipoEvento == EVENTO_MOUSE) return TrataEventoMouse(evento);
        return PIG_NAO_SELECIONADO;
    }*/

    int TrataEventoMouse(PIG_Evento evento){
        SDL_Point p;
        if (CPIGGerenciadorJanelas::GetJanela(idJanela)->GetUsandoCameraFixa())
            p = CPIGMouse::PegaXYTela();
        else p = CPIGMouse::PegaXYWorld();
        ChecaMouseOver(p);

        if(TrataBotoes(evento) == PIG_SELECIONADO_TRATADO) return PIG_SELECIONADO_TRATADO;
        handle->TrataEventoMouse(evento);

        if(orientacao == PIG_VERTICAL && (ChecaMouseOverAreaScroll(p) || mouseOver)){
            if(evento.mouse.acao == PIG_MOUSE_RODINHA) return TrataRodinha(evento);
        }

        if (mouseOver){
            if((evento.mouse.acao == PIG_MOUSE_PRESSIONADO && evento.mouse.botao == PIG_MOUSE_ESQUERDO) || handle->GetAcionado()){
                return TrataClickTrilha(p.x,p.y);
            }
            return PIG_SELECIONADO_MOUSEOVER;
        }
        return PIG_NAO_SELECIONADO;
    }

    int TrataEventoTeclado(PIG_Evento evento){
        if (!temFoco) return 0;
        if(evento.teclado.acao == PIG_TECLA_PRESSIONADA){
            if(orientacao == PIG_HORIZONTAL){
                if(evento.teclado.tecla== PIG_TECLA_DIREITA) AvancaHandle(vAtual,deltaTeclado);
                if(evento.teclado.tecla == PIG_TECLA_ESQUERDA) AvancaHandle(vAtual,-deltaTeclado);
            }else{
                if(evento.teclado.tecla== PIG_TECLA_CIMA) AvancaHandle(vAtual,deltaTeclado);
                if(evento.teclado.tecla == PIG_TECLA_BAIXO) AvancaHandle(vAtual,-deltaTeclado);
            }
            return PIG_SELECIONADO_TRATADO;
        }
        return PIG_NAO_SELECIONADO;
    }


/***************Novos Métodos**************/

    void GetDimensoes(int &altura,int &largura)override{
        altura = altReal;
        largura = largReal;
    }

    void GetDimensoesTrilha(int &altura,int &largura){
        CPIGSprite::GetDimensoes(altura,largura);
    }

    void MudaOrientacaoCrescimento(){
        orientacaoCrescimento = !orientacaoCrescimento;
        AvancaHandle(vAtual);
    }

    void SetDimensoes(int largura,int comprimento){
        this->largura = largura;
        this->comprimento = comprimento;
        largUtil = comprimento - (2*altBotoes) - largHandle;
        AjustaOrientacao();
    }

    void Move(int px,int py){
        xOriginal = px;
        yOriginal = py;
        AjustaOrientacao();

    }

    void SetAreaDeAcaoScroll(int x,int y,int altura,int largura){
        areaDeAcaoScroll = {x,y,largura,altura};
    }

/***************Métodos Modificados**************/

    void SetDeltas(int dBotao = 1,int dRodinha = 10,int dTeclado = 10){
        deltaBotao = dBotao;
        deltaRodinha = dRodinha;
        deltaTeclado = dTeclado;
    }

/*******************************************/

    int Desenha(){
        if(visivel==false) return -1;

        CPIGSprite::Desenha();
        //SDL_RenderCopyEx(renderer, text, &frames[frameAtual],&dest,-angulo,&pivoRelativo,flip);

        if(botao1 && botao2){
            botao1->Desenha();
            botao2->Desenha();
        }
        handle->Desenha();
        return 0;
    }

    int GetValorAtual(){
        return vAtual;
    }

    void SetValorMinMax(int minimo,int maximo){
        vMin = minimo;
        vMax = maximo;
        vAtual = PIGLimitaValor(vAtual, vMin,vMax);
        AvancaHandle(vAtual);
    }

    void SetValorAtual(int valor){
        AvancaHandle(valor);
    }

};
typedef CPIGScrollBar *PIGScrollBar;
#endif // _CPIGSCROLLBAR_
