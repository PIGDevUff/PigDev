#ifndef _CPIGBOTAO_
#define _CPIGBOTAO_

#include "CPIGComponente.h"

class CPIGBotao: public CPIGComponente{

private:
    int tecla;

protected:

    PIG_FuncaoSimples acao;
    void *param;
    PIGTimer timer;
    bool botaoRepeticao;
    double tempoRepeticao;

    void SetFoco(bool valor){
        temFoco = valor;
    }

    void SetAcionado(bool valor){
        acionado = valor;
        AjustaFrame();
    }

    void SetMouseOver(bool valor){
        mouseOver = valor;
        AjustaFrame();
    }

    void AjustaFrame(){
        if (visivel==false) return;
        frameAtual = 1;
        if (habilitado==false){
            frameAtual = 4;
        }else{
            if (acionado){
                frameAtual = 3;
            }else if (mouseOver){
                frameAtual = 2;
            }
        }
    }

    void TrataTimer(){
        if (timer->GetTempoDecorrido()>=tempoRepeticao){
            if (botaoRepeticao&&mouseOver&&CPIGMouse::GetEstadoBotaoEsquerdo()==PIG_MOUSE_PRESSIONADO){
                OnMouseClick();
            }else{
                SetAcionado(false);
            }
        }
    }

    int OnMouseClick(){
        SetAcionado(true);
        timer->Reinicia(false);
        if (acao) acao(id,param);//rever se NULL é necessário
        if (audioComponente>=0) CPIGGerenciadorAudios::Play(audioComponente);
        return PIG_SELECIONADO_TRATADO;
    }

    /*CPIGBotao LeArquivoParametros(std::string nomeArqParam){

        std::ifstream arquivo;
        int idComponente,px,py,altura,largura,retiraFundo = 0,janela = 0;

        std::string nomeArq = "",palavra;

        arquivo.open(nomeArqParam);
        //if(!arquivo.is_open()) printf("falha ler arquivo\n");
        //formato "x valor"
        while(!arquivo.eof()){
            arquivo >> palavra;
            if(palavra == "idComponente") arquivo >> idComponente;
            if(palavra == "px") arquivo >> px;
            if(palavra == "py") arquivo >> py;
            if(palavra == "altura") arquivo >> altura;
            if(palavra == "largura") arquivo >> largura;
            if(palavra == "nomeArq") arquivo >> nomeArq;
            if(palavra == "retiraFundo") arquivo >> retiraFundo;
            if(palavra == "janela") arquivo >> janela;
        }
        arquivo.close();

       // std::cout<<idComponente<<" "<<px<<" "<<py<<" "<<altura<<" "<<largura<<" "<<nomeArq<<" "<<retiraFundo<<" "<<janela<<std::endl;

        return CPIGBotao(idComponente,px,py,altura,largura,nomeArq,retiraFundo,janela);
    }*/

    static CPIGBotao LeParametros(int idComponente,string parametros){
        CPIGAtributos atrib = CPIGComponente::GetAtributos(parametros);

        CPIGBotao resp(idComponente,atrib.GetInt("px",0),atrib.GetInt("py",0),atrib.GetInt("altura",0),atrib.GetInt("largura",0),
                       atrib.GetString("nomeArq",""),atrib.GetInt("retiraFundo",1),atrib.GetInt("janela",0));
        return resp;
    }

public:

    CPIGBotao(int idComponente,int px, int py, int alt,int larg,std::string nomeArq, int retiraFundo=1,int janela=0):
        CPIGComponente(idComponente,px,py,alt,larg,nomeArq,retiraFundo,janela){
            tecla = PIG_TECLA_ENTER;//sem tecla de atalho
            param = NULL;//não tem parâmetro associado à ação
            CriaFramesAutomaticosPorLinha(1,1,4);
            MudaFrameAtual(1); //frame de estado normal do botao
            tempoRepeticao = 0.2;
            botaoRepeticao = false;
            SetPosicaoPadraoLabel(PIG_COMPONENTE_CENTRO_CENTRO);
            timer = new CPIGTimer(false);
            acao = NULL;//não tem ação registrada
        }

    CPIGBotao(int idComponente,std::string nomeArqParam):CPIGBotao(LeParametros(idComponente,nomeArqParam)){}

    ~CPIGBotao(){
        delete timer;
    }

    void DefineAcao(PIG_FuncaoSimples funcao,void *parametro){
        acao = funcao;
        param = parametro;
    }

    int TrataEventoMouse(PIG_Evento evento){
        SDL_Point p;
        if (CPIGGerenciadorJanelas::GetJanela(idJanela)->GetUsandoCameraFixa())
            p = CPIGMouse::PegaXYTela();
        else p = CPIGMouse::PegaXYWorld();

        ChecaMouseOver(p);

        if (mouseOver){
            if (!habilitado) return PIG_SELECIONADO_DESABILITADO;
            if (!visivel) return PIG_SELECIONADO_INVISIVEL;
            if(evento.mouse.acao==PIG_MOUSE_PRESSIONADO && evento.mouse.botao == PIG_MOUSE_ESQUERDO) return OnMouseClick();
            return PIG_SELECIONADO_MOUSEOVER;
        }

        return PIG_NAO_SELECIONADO;
    }

    int TrataEventoTeclado(PIG_Evento evento){
        if (evento.teclado.acao==PIG_TECLA_PRESSIONADA && evento.teclado.tecla==tecla){
            if (!habilitado) return PIG_SELECIONADO_DESABILITADO;
            if (!visivel) return PIG_SELECIONADO_INVISIVEL;
            if (timer->GetTempoDecorrido()>tempoRepeticao) return OnMouseClick();
        }

        return 0;
    }

    void DefineAtalho(int teclaAtalho){
        tecla = teclaAtalho;
    }

    void DefineTempoRepeticao(double segundos){
        tempoRepeticao = segundos;
    }

    void DefineBotaoRepeticao(bool repeticao){
        botaoRepeticao = repeticao;
    }

    void SetHabilitado(bool valor){
        habilitado = valor;
        AjustaFrame();
    }

    int Desenha(){

        if (visivel==false) return 0;

        TrataTimer();

        CPIGSprite::Desenha();

        DesenhaLabel();

        EscreveHint();

        return 1;
    }

};

typedef CPIGBotao *PIGBotao;
#endif // _CPIGBOTAO_
