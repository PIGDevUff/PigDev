#ifndef _CPIGCAMPOTEXTOESENHA_
#define _CPIGCAMPOTEXTOESENHA_

#include "CPIGCaixaTexto.h"

class CPIGCampoTextoESenha: public CPIGCaixaTexto{

private:

    char mascara;//símbolo usado quando o campo for de senha
    std::string (CPIGCampoTextoESenha::*GetTextoVisivelPtr)();//ponteiro para a funçăo que vai retornar o texto visivel

    static CPIGCampoTextoESenha LeParametros(int idComponente,std::string parametros){
        CPIGAtributos atrib = CPIGComponente::GetAtributos(parametros);

        CPIGCampoTextoESenha resp(idComponente,atrib.GetInt("px",0),atrib.GetInt("py",0),atrib.GetInt("altura",0),atrib.GetInt("largura",0),
                        atrib.GetString("nomeArq",""),atrib.GetInt("maxCaracters",200),atrib.GetInt("apenasNumeros",0),atrib.GetInt("campoSenha",0),
                        atrib.GetInt("retiraFundo",1),atrib.GetInt("janela",0));

        return resp;

    }

    //retorna o texto com a quantidade de símbolos (máscara) igual ao tamanho da string com textobase
    std::string GetTextoMask(){
        std::string resp;
        resp.assign(texto.size(),mascara);
        return resp;
    }

    //recupera a string com o texto visível (com máscara de senha ou năo)
    std::string GetTextoVisivel(){
        return (this->*GetTextoVisivelPtr)();
    }

    void IniciaPosicaoTexto(){
        yTexto = pos.y+margemVertBaixo;
        xTexto = pos.x+margemHorEsq;
    }

    //ajusta o alinhamento do cursor
    void AjustaPosicaoTextoCursor()override{
        std::string textoBase = GetTextoVisivel();
        int largTextoTotal = CPIGGerenciadorFontes::GetFonte(fonteTexto)->GetLarguraPixelsString(textoBase); //largura total do texto todo (em pixels)

        IniciaPosicaoTexto();

        std::string aux;
        aux.assign(textoBase,0,posCursor); //pega a string apenas do início até onde o cursor está
        int largTextoAteCursor = CPIGGerenciadorFontes::GetFonte(fonteTexto)->GetLarguraPixelsString(aux); //largura (em pixels) até o ponto do cursor

        if (largTextoTotal>larg-margemHorDir-margemHorEsq){ //não cabe todo dentro da caixa
            xTexto = (pos.x+larg-margemHorDir)-largTextoTotal;
            int deltaCursor = pos.x+margemHorEsq-(xTexto+largTextoAteCursor);
            if (deltaCursor>0)
                xTexto += deltaCursor;
        }else{
            xTexto = pos.x+margemHorEsq;
        }

        xCursor = xTexto + largTextoAteCursor;
        yCursor = yTexto;
        //printf("xc: %d\n",xCursor);
    }

    int SobeCursor(){return 1;} //năo usa o SobeCursor

    int DesceCursor(){return 1;}//năo usa o DesceCursor

    int PulaLinha(){return 1;}//năo usa o PulaLinha


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

    CPIGCampoTextoESenha(int idComponente,int px, int py, int altura,int largura,std::string nomeArq,int maxCars = 200, bool apenasNumeros=false, bool campoSenha = false, int retiraFundo=1,int janela=0):
        CPIGCaixaTexto(idComponente,px,py,altura,largura,nomeArq,maxCars,apenasNumeros,retiraFundo,janela){
            mascara = '*';
            if(campoSenha){
                GetTextoVisivelPtr = &CPIGCampoTextoESenha::CPIGCampoTextoESenha::GetTextoMask;
            }else{
                GetTextoVisivelPtr = &CPIGCampoTextoESenha::GetTexto;
            }
    }

    CPIGCampoTextoESenha(int idComponente,std::string parametros):CPIGCampoTextoESenha(LeParametros(idComponente,parametros)){}

    //desenha o componente completo
    int Desenha() override{
        //imagem de fundo
        CPIGSprite::Desenha();

        SDL_Rect r={(int)(pos.x+margemHorEsq+1),(int)(*altJanela-pos.y-alt+margemVertCima),larg-(margemHorEsq+margemHorDir),alt-(margemVertBaixo+margemVertCima)};

        CPIGGerenciadorJanelas::GetJanela(idJanela)->ConverteCoordenadaWorldScreen(r.x,r.y,r.x,r.y);

        SDL_RenderSetClipRect(renderer,&r);


        CPIGGerenciadorFontes::GetFonte(fonteTexto)->Escreve(GetTextoVisivel(),xTexto,yTexto,BRANCO,PIG_TEXTO_ESQUERDA);
        DesenhaCursor();//desenha o cursor (se estiver em ediçăo)

        //desbloqueia o desenho fora da area do componente
        SDL_RenderSetClipRect(renderer,NULL);

        DesenhaLabel();
        EscreveHint();
        return 1;
    }

    int TrataEventoMouse(PIG_Evento evento){
        SDL_Point p = GetPosicaoMouse();
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
        int resp = CPIGCaixaTexto::TrataEventoTeclado(evento);
        return resp;
    }

};

typedef CPIGCampoTextoESenha *PIGCampoTextoESenha;
#endif // _CPIGCAMPOTEXTOESENHA_
