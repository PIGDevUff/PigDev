#ifndef _CPIGSCROLLBAR_
#define _CPIGSCROLLBAR_

#include "CPIGComponente.h"
#include "CPIGSlideBar.h"
#include "CPIGBotaoClick.h"

//tipo de função a ser usada em alterações na posição do handle da barra
//o parâmetro int devolverá à função o identificador do botão
//o parâmetro double devolverá à função a porcentagem atual da barra
//o parâmetro void* devolverá à função um parâmetro personalizado passado ao método DefineAcao();
//typedef void (*AcaoScroll)(int,double,void*);

class CPIGScrollBar : public CPIGSlideBar{

    int deltaBotao;
    PIGBotaoClick botao1,botao2;
    void *param;
    PIG_FuncaoSimples acao;

    static int AcaoSetas(int idBotao, void* pontObjeto){
        CPIGScrollBar *scroll = (CPIGScrollBar*) pontObjeto;
        if (idBotao==scroll->id+1){
            scroll->AvancaMarcador(-scroll->deltaBotao);
        }else if (idBotao==scroll->id+2){
            scroll->AvancaMarcador(scroll->deltaBotao);
        }
        return 1;
    }

    int TrataBotoes(PIG_Evento evento){
        if(botao1 && botao2){
            if(botao1->TrataEventoMouse(evento) == PIG_SELECIONADO_TRATADO || botao2->TrataEventoMouse(evento) == PIG_SELECIONADO_TRATADO) return PIG_SELECIONADO_TRATADO;
        }
        return PIG_NAO_SELECIONADO;
    }

public:

    CPIGScrollBar(int idComponente,int px, int py,int altura,int largura,std::string imgTrilha,int altMarcador,int largMarcador,std::string imgMarcador,int altBotao, int largBotao,string imgBotao1,string imgBotao2,int retiraFundoTrilha=1,int retiraFundoMarcador=1,int retiraFundoBotao=1,int janela=0):
        CPIGSlideBar(idComponente,px,py,altura,largura,imgTrilha,altMarcador,largMarcador,imgMarcador,retiraFundoTrilha,retiraFundoMarcador,janela){
            deltaBotao = 1;
            acao = NULL;
            param = NULL;
            botao1 = new CPIGBotaoClick(id + 1,px,py,altBotao,largBotao,imgBotao1,retiraFundoBotao,idJanela);
            botao2 = new CPIGBotaoClick(id + 2,px,py,altBotao,largBotao,imgBotao2,retiraFundoBotao,idJanela);
            botao1->DefineAcao(AcaoSetas,this);
            botao2->DefineAcao(AcaoSetas,this);
            botao1->DefineBotaoRepeticao(true);
            botao2->DefineBotaoRepeticao(true);
            botao1->DefineTempoRepeticao(0.01);
            botao2->DefineTempoRepeticao(0.01);
    }

    CPIGScrollBar(std::string nomeArqParam):CPIGSlideBar(LeArquivoParametros(nomeArqParam)){}

    ~CPIGScrollBar(){
        if (botao1) delete botao1;
        if (botao2) delete botao2;
    }

    static CPIGScrollBar LeArquivoParametros(std::string nomeArqParam){

        std::ifstream arquivo;
        int idComponente,px,py,largura,largBotao,larguraMarcador,altura,altBotao,alturaMarcador,retiraFundoMarcador=1,retiraFundoTrilha=1,retiraFundoBotao=1,janela=0;
        std::string imgMarcador = "",imgTrilha = "",imgBotao1="",imgBotao2="",variavel;

        arquivo.open(nomeArqParam);

        if(!arquivo.is_open()) throw CPIGErroArquivo(nomeArqParam);
        //formato "x valor"
        while(!arquivo.eof()){
           arquivo >> variavel;
            if(variavel == "idComponente") arquivo >> idComponente;
            if(variavel == "px") arquivo >> px;
            if(variavel == "py") arquivo >> py;
            if(variavel == "largura") arquivo >> largura;
            if(variavel == "larguraBotao") arquivo >> largBotao;
            if(variavel == "larguraMarcador") arquivo >> larguraMarcador;
            if(variavel == "altura") arquivo >> altura;
            if(variavel == "alturaBotao") arquivo >> altBotao;
            if(variavel == "alturaMarcador") arquivo >> alturaMarcador;
            if(variavel == "imgMarcador") arquivo >> imgMarcador;
            if(variavel == "imgTrilha") arquivo >> imgTrilha;
            if(variavel == "imgBotao1") arquivo >> imgBotao1;
            if(variavel == "imgBotao2") arquivo >> imgBotao2;
            if(variavel == "retiraFundoMarcador") arquivo >> retiraFundoMarcador;
            if(variavel == "retiraFundoTrilha") arquivo >> retiraFundoTrilha;
            if(variavel == "retiraFundoBotao") arquivo >> retiraFundoBotao;
            if(variavel == "janela") arquivo >> janela;
        }

        arquivo.close();

        if(imgMarcador == "") throw CPIGErroParametro("imgMarcador",nomeArqParam);
        if(imgTrilha == "") throw CPIGErroParametro("imgTrilha",nomeArqParam);
        if(imgBotao1 == "") throw CPIGErroParametro("imgBotao1",nomeArqParam);
        if(imgBotao2 == "") throw CPIGErroParametro("imgBotao2",nomeArqParam);

       // std::cout<<idComponente<<" "<<px<<" "<<py<<" "<<altura<<" "<<largura<<" "<<nomeArq<<" "<<retiraFundo<<" "<<janela<<std::endl;
        return CPIGScrollBar(idComponente,px,py,altura,largura,imgTrilha,alturaMarcador,larguraMarcador,imgMarcador,altBotao,largBotao,imgBotao1,imgBotao2,retiraFundoTrilha,retiraFundoMarcador,retiraFundoBotao,janela);
    }

    int TrataEventoMouse(PIG_Evento evento){
        int resp=CPIGSlideBar::TrataEventoMouse(evento);
        if (resp==PIG_NAO_SELECIONADO){
            int respBotao1 = botao1->TrataEventoMouse(evento);
            if (respBotao1 ==PIG_NAO_SELECIONADO){
                return botao2->TrataEventoMouse(evento);
            }else return respBotao1;
        }else return resp;
    }

    int Desenha(){
        if(visivel==false) return -1;

        if(botao1 && botao2){
            botao1->Desenha();
            botao2->Desenha();
        }

        CPIGSlideBar::Desenha();

        return 0;
    }

};
typedef CPIGScrollBar *PIGScrollBar;
#endif // _CPIGSCROLLBAR_
