#ifndef _CPIGCAMPOTEXTOESENHA_
#define _CPIGCAMPOTEXTOESENHA_

#include "CPIGCaixaTexto.h"

class CPIGCampoTextoESenha: public CPIGCaixaTexto{

private:

    char mascara;//símbolo usado quando o campo for de senha
    std::string (CPIGCampoTextoESenha::*GetTextoVisivelPtr)();//ponteiro para a função que vai retornar o texto visivel

    //retorna o texto com a quantidade de símbolos (máscara) igual ao tamanho da string com textobase
    std::string GetTextoMask(){
        std::string resp;
        resp.assign(texto.size(),mascara);
        return resp;
    }

    //recupera a string com o texto visível (com máscara de senha ou não)
    std::string GetTextoVisivel(){
        return (this->*GetTextoVisivelPtr)();
    }

    //ajusta o alinhamento do cursor
    void AjustaAlinhamento(){
        std::string textoBase = GetTextoVisivel();
        std::string aux;

        aux.assign(textoBase,0,posCursor);
        xCursor = xBase + CPIGGerenciadorFontes::GetFonte(fonteTexto)->GetLarguraPixelsString(aux);

        AjustaBaseTextoEixoX(CPIGGerenciadorFontes::GetFonte(fonteTexto)->GetLarguraPixelsString(aux));
    }


    int SobeCursor(){return 1;} //não usa o SobeCursor

    int DesceCursor(){return 1;}//não usa o DesceCursor

    int PulaLinha(){return 1;}//não usa o PulaLinha


    void SetHabilitado(bool valor){
        habilitado = valor;
    }

    void SetAcionado(bool valor){
        acionado = valor;
    }

    void SetMouseOver(bool valor){
        mouseOver = valor;
    }

    void SetFoco(bool valor) override{
        temFoco = valor;
        if (temFoco) SDL_StartTextInput();
        else SDL_StopTextInput();
    }

public:

    CPIGCampoTextoESenha(int idComponente,int px, int py, int altura,int largura,std::string nomeArq,int maxCars = 200, bool apenasNumeros=false, int retiraFundo=1,int janela=0,bool campoSenha = false):
        CPIGCaixaTexto(idComponente,px,py,altura,largura,nomeArq,maxCars,apenasNumeros,retiraFundo,janela){
            yBaseOriginal = pos.y+margemVertBaixo;
            xBaseOriginal = pos.x+margemHorEsq;
            yBase = yBaseOriginal;
            xBase = xBaseOriginal;
            xCursor = xBase;
            yCursor = yBase;
            mascara = '*';
            if(campoSenha){
                GetTextoVisivelPtr = &CPIGCampoTextoESenha::GetTextoMask;
            }else{
                GetTextoVisivelPtr = &GetTexto;
            }
    }

    CPIGCampoTextoESenha(std::string nomeArqParam):CPIGCampoTextoESenha(LeArquivoParametros(nomeArqParam)){}

    ~CPIGCampoTextoESenha(){}

    static CPIGCampoTextoESenha LeArquivoParametros(std::string nomeArqParam){

        std::ifstream arquivo;
        int idComponente,px,py,altura,largura,maxCars = 200,retiraFundo=1,janela=0;
        bool apenasNumeros = false,campoSenha = false;

        std::string nomeArq = "",variavel;

        arquivo.open(nomeArqParam);

        if(!arquivo.is_open()) throw CPIGErroArquivo(nomeArqParam);
        //formato "x valor"
        while(!arquivo.eof()){
           arquivo >> variavel;
            if(variavel == "idComponente") arquivo >> idComponente;
            if(variavel == "px") arquivo >> px;
            if(variavel == "py") arquivo >> py;
            if(variavel == "altura") arquivo >> altura;
            if(variavel == "largura") arquivo >> largura;
            if(variavel == "nomeArq") arquivo >> nomeArq;
            if(variavel == "retiraFundo") arquivo >> retiraFundo;
            if(variavel == "janela") arquivo >> janela;
            if(variavel == "maxCars") arquivo >> maxCars;
            if(variavel == "apenasNumeros") arquivo >> apenasNumeros;
            if(variavel == "campoSenha") arquivo >> campoSenha;
        }
        arquivo.close();

        if(nomeArq == "") throw CPIGErroParametro("nomeArq",nomeArqParam);
       // std::cout<<idComponente<<" "<<px<<" "<<py<<" "<<altura<<" "<<largura<<" "<<nomeArq<<" "<<retiraFundo<<" "<<janela<<std::endl;
        return CPIGCampoTextoESenha(idComponente,px,py,altura,largura,nomeArq,maxCars,apenasNumeros,retiraFundo,janela,campoSenha);

    }

    //desenha o componente completo
    int Desenha() override{
        //imagem de fundo
        CPIGSprite::Desenha();

        SDL_Rect r={pos.x+margemHorEsq+1,*altJanela-pos.y-alt+margemVertCima,larg-(margemHorEsq+margemHorDir),alt-(margemVertBaixo+margemVertCima)};

        CPIGGerenciadorJanelas::GetJanela(idJanela)->ConverteCoordenadaWorldScreen(r.x,r.y,r.x,r.y);

        SDL_RenderSetClipRect(renderer,&r);


        CPIGGerenciadorFontes::GetFonte(fonteTexto)->Escreve(GetTextoVisivel(),xBase,yBase,BRANCO,PIG_TEXTO_ESQUERDA);
        DesenhaCursor();//desenha o cursor (se estiver em edição)

        //desbloqueia o desenho fora da area do componente
        SDL_RenderSetClipRect(renderer,NULL);

        DesenhaLabel();
        EscreveHint();
        return 1;
    }
    //define as margens do componente
    void SetMargens(int horEsq,int horDir, int vertBaixo,int vertCima){
        margemVertCima = vertCima;
        margemVertBaixo = vertBaixo;
        margemHorDir = horDir;
        margemHorEsq = horEsq;
        yBaseOriginal = pos.y+margemVertBaixo;
        xBaseOriginal = pos.x+margemHorEsq;
        yBase = yBaseOriginal;
        xBase = xBaseOriginal;
        xCursor = xBase;
        yCursor = yBase;
        AjustaAlinhamento();
    }

    int TrataEventoMouse(PIG_Evento evento){
        SDL_Point p = CPIGMouse::PegaXYWorld();
        //PigCamera cam = CGerenciadorJanelas::GetJanela(idJanela)->GetCamera();
        ChecaMouseOver(p);

        if(mouseOver){
            if (habilitado==false) return PIG_SELECIONADO_DESABILITADO;
            if (visivel==false) return PIG_SELECIONADO_INVISIVEL;
            if (evento.mouse.acao == PIG_MOUSE_PRESSIONADO && evento.mouse.botao == PIG_MOUSE_ESQUERDO) return TrataMouseBotaoEsquerdo(p);
            return PIG_SELECIONADO_MOUSEOVER;
        }

        return PIG_NAO_SELECIONADO;
    }

    int TrataEventoTeclado(PIG_Evento evento){
        return CPIGCaixaTexto::TrataEventoTeclado(evento);
    }

};

typedef CPIGCampoTextoESenha *PIGCampoTextoESenha;
#endif // _CPIGCAMPOTEXTOESENHA_
