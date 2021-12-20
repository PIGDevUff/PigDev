#ifndef _CPIGCAMPOTEXTOESENHA_
#define _CPIGCAMPOTEXTOESENHA_

#include "CPIGCaixaTexto.h"

class CPIGCampoTextoESenha: public CPIGCaixaTexto{

private:

    char mascara;//símbolo usado quando o campo for de senha
    bool somenteNumeros;//se o campo só aceita números ou aceita também letras
    string (CPIGCampoTextoESenha::*GetTextoVisivelPtr)();//ponteiro para a funçăo que vai retornar o texto visivel

    void ProcessaAtributos(CPIGAtributos atrib)override{
        CPIGCaixaTexto::ProcessaAtributos(atrib);

        string valorStr = atrib.GetString("mascara","");
        if (valorStr != "") SetMascara(valorStr[0]);
    }

    static CPIGCampoTextoESenha LeParametros(int idComponente,CPIGAtributos atrib){
        CPIGCampoTextoESenha *resp;

        if (atrib.GetString("nomeArq","")!=""){
            resp = new CPIGCampoTextoESenha(idComponente,atrib.GetInt("altura",0),atrib.GetInt("largura",0),
                        atrib.GetString("nomeArq",""),atrib.GetInt("maxCaracters",200),atrib.GetInt("apenasNumeros",0),atrib.GetInt("campoSenha",0),
                        atrib.GetInt("retiraFundo",1),atrib.GetInt("janela",0));
        }else{
            resp = new CPIGCampoTextoESenha(idComponente,atrib.GetInt("altura",0),atrib.GetInt("largura",0),
                        atrib.GetInt("maxCaracters",200),atrib.GetInt("apenasNumeros",0),atrib.GetInt("campoSenha",0),atrib.GetInt("janela",0));
        }

        resp->ProcessaAtributos(atrib);

        return *resp;
    }

    //retorna o texto com a quantidade de símbolos (máscara) igual ao tamanho da string com textobase
    string GetTextoMask(){
        string resp;
        resp.assign(texto.size(),mascara);
        return resp;
    }

    //recupera a string com o texto visível (com máscara de senha ou năo)
    inline string GetTextoVisivel(){
        return (this->*GetTextoVisivelPtr)();
    }

    void IniciaPosicaoTexto(){
        yTexto = pos.y+margemBaixo;
        xTexto = pos.x+margemEsq;
    }

    //ajusta o alinhamento do cursor
    void AjustaPosicaoTextoCursor()override{
        string textoBase = GetTextoVisivel();
        int largTextoTotal = CPIGGerenciadorFontes::GetFonte(fonteTexto)->GetLarguraPixelsString(textoBase); //largura total do texto todo (em pixels)

        IniciaPosicaoTexto();

        string aux;
        aux.assign(textoBase,0,posCursor); //pega a string apenas do início até onde o cursor está
        int largTextoAteCursor = CPIGGerenciadorFontes::GetFonte(fonteTexto)->GetLarguraPixelsString(aux); //largura (em pixels) até o ponto do cursor

        if (largTextoTotal>larg-margemDir-margemEsq){ //não cabe todo dentro da caixa
            xTexto = (pos.x+larg-margemDir)-largTextoTotal;
            int deltaCursor = pos.x+margemEsq-(xTexto+largTextoAteCursor);
            if (deltaCursor>0)
                xTexto += deltaCursor;
        }else{
            xTexto = pos.x+margemEsq;
        }

        xCursor = xTexto + largTextoAteCursor;
        yCursor = yTexto;
        //printf("xc: %d\n",xCursor);
    }

    int SobeCursor(){return 1;} //năo usa o SobeCursor

    int DesceCursor(){return 1;}//năo usa o DesceCursor

    int PulaLinha(){return 1;}//năo usa o PulaLinha

    void IniciaBase(bool campoSenha, bool apenasNumero){
        mascara = '*';
        somenteNumeros = apenasNumero;
        if(campoSenha){
            GetTextoVisivelPtr = &CPIGCampoTextoESenha::CPIGCampoTextoESenha::GetTextoMask;
        }else{
            GetTextoVisivelPtr = &CPIGCampoTextoESenha::GetTexto;
        }
        CPIGCaixaTexto::IniciaCoresBasicas();
        tipo = PIG_CAMPOTEXTO;
    }

public:

    CPIGCampoTextoESenha(int idComponente, int altura, int largura, string nomeArq, int maxCars=PIG_MAX_CARS_CAIXATEXTO, bool apenasNumeros=false, bool campoSenha = false, int retiraFundo=1, int janela=0):
        CPIGCaixaTexto(idComponente,altura,largura,nomeArq,maxCars,retiraFundo,janela){
            IniciaBase(campoSenha,apenasNumeros);
    }

    CPIGCampoTextoESenha(int idComponente, int altura, int largura, int maxCars=PIG_MAX_CARS_CAIXATEXTO, bool apenasNumeros=false, bool campoSenha = false, int janela=0):
        CPIGCaixaTexto(idComponente,altura,largura,maxCars,janela){
            IniciaBase(campoSenha,apenasNumeros);
    }

    CPIGCampoTextoESenha(int idComponente,CPIGAtributos atrib):CPIGCampoTextoESenha(LeParametros(idComponente,atrib)){}

    virtual ~CPIGCampoTextoESenha(){}

    //desenha o componente completo
    int Desenha() override{
        if (!visivel) return 0;

        //imagem de fundo
        if (imagemPropria)
            CPIGSprite::Desenha();
        else CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetangulo((int)pos.x,(int)pos.y,alt,larg,coresBasicas[0]);

        CPIGGerenciadorJanelas::GetJanela(idJanela)->BloqueiaArea((int)pos.x+margemEsq,(int)pos.y+margemBaixo,alt-(margemBaixo+margemCima),larg-(margemEsq+margemDir));

        CPIGGerenciadorFontes::GetFonte(fonteTexto)->Escreve(GetTextoVisivel(),xTexto,yTexto,coresBasicas[1],PIG_TEXTO_ESQUERDA);
        DesenhaCursor();//desenha o cursor (se estiver em ediçăo)

        //desbloqueia o desenho fora da area do componente
        CPIGGerenciadorJanelas::GetJanela(idJanela)->DesbloqueiaArea();

        return CPIGComponente::Desenha();
    }

    PIGEstadoEvento TrataEventoMouse(PIGEvento evento)override{
        if (!habilitado) return PIG_COMPONENTE_DESABILITADO;
        if (!visivel) return PIG_COMPONENTE_INVISIVEL;

        SDL_Point p = GetPosicaoMouse();
        ChecaMouseOver(p);

        if(mouseOver){
            if (evento.mouse.acao == PIG_MOUSE_PRESSIONADO && evento.mouse.botao == PIG_MOUSE_ESQUERDO)
                return TrataMouseBotaoEsquerdo(p);
            return PIG_COMPONENTE_MOUSEOVER;
        }

        return PIG_COMPONENTE_NAOTRATADO;
    }

    void SetMascara(char c){
        mascara = c;
    }

    virtual int AdicionaTexto(string frase)override{
        if (somenteNumeros&&!PIGSomenteNumeros(frase)) return 0;//năo é número
        return CPIGCaixaTexto::AdicionaTexto(frase);
    }

};

typedef CPIGCampoTextoESenha *PIGCampoTextoESenha;
#endif // _CPIGCAMPOTEXTOESENHA_
