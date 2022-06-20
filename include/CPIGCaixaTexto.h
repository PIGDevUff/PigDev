#ifndef _CPIGCaixaTexto_
#define _CPIGCaixaTexto_

#include "CPIGComponente.h"

class CPIGCaixaTexto: public CPIGComponente{

private:

    bool cursorExibido;
    int maxCaracteres;
    PIGTimer timer;

protected:

    inline void IniciaCoresBasicas(){
        coresBasicas[0] = CINZA;
        coresBasicas[1] = BRANCO;
        coresBasicas[2] = PRETO;
    }

    virtual void ProcessaAtributos(CPIGAtributos atrib)override{
        CPIGComponente::ProcessaAtributos(atrib);

        int valorInt = atrib.GetInt("fonte",-1);
        if (valorInt >= 0) SetFonteTexto(valorInt);

        string valorStr = atrib.GetString("texto","");
        if (valorStr != "") SetTexto(valorStr);

        valorStr = atrib.GetString("corFundo","");
        if (valorStr != "") SetCorFundo(PIGCriaCorString(valorStr));

        valorStr = atrib.GetString("corFonte","");
        if (valorStr != "") SetCorFonte(PIGCriaCorString(valorStr));

        valorStr = atrib.GetString("corCursor","");
        if (valorStr != "") SetCorCursor(PIGCriaCorString(valorStr));
    }

    //checa se o ponteiro do mouse está sobre o componente
    int ChecaMouseOver(SDL_Point pMouse) override{
        if (visivel==false) return -1;

        SDL_Rect r = {(int)pos.x + margemEsq,((int)pos.y) + margemBaixo,larg - (margemDir + margemEsq),alt - (margemBaixo + margemCima)};

        SetMouseOver(SDL_PointInRect(&pMouse,&r));
        return mouseOver;
    }

    //desenha o cursor
    void DesenhaCursor(){
        if (temFoco){
            if (cursorExibido){
                CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaLinhaSimples(xCursor,yCursor,xCursor,yCursor+altLetra,coresBasicas[2]);
            }
            if (timer&&timer->GetTempoDecorrido()>1){
                cursorExibido = !cursorExibido;
                timer->Reinicia(false);
            }
        }
    }

    //trata teclas de movimentaçăo do cursor
    virtual PIGEstadoEvento TrataTeclasEspeciais(PIGEvento evento){
        switch (evento.teclado.tecla){
            case PIG_TECLA_BACKSPACE:
                RetiraTextoBackSpace();break;
            case PIG_TECLA_DELETE:
                RetiraTextoDelete();break;
            case PIG_TECLA_DIREITA:
                AvancaCursor();break;
            case PIG_TECLA_ESQUERDA:
                VoltaCursor();break;
            case PIG_TECLA_CIMA:
                SobeCursor();break;
            case PIG_TECLA_BAIXO:
                DesceCursor();break;
            case PIG_TECLA_ENTER:
                PulaLinha();break;
        }
        return OnAction();
    }

    //trata os diversos tipos de eventos de teclado que podem ocorrer
    PIGEstadoEvento TrataEventoTeclado(PIGEvento evento)override{
        if (!temFoco) return PIG_COMPONENTE_SEMFOCO;
        if (!habilitado) return PIG_COMPONENTE_DESABILITADO;
        if (!visivel) return PIG_COMPONENTE_INVISIVEL;

        if (evento.teclado.acao==PIG_TECLA_EDICAO) return PIG_COMPONENTE_TRATADO;

        if (evento.teclado.acao==PIG_TECLA_INPUT){//caracteres normais
            string s = ConverteString(evento.teclado.texto);
            if (AdicionaTexto(s)){
                return OnAction();
            }
            return PIG_COMPONENTE_NAOTRATADO;
        }

        if (evento.teclado.acao==PIG_TECLA_PRESSIONADA){//teclas especiais
            return TrataTeclasEspeciais(evento);
        }
        return PIG_COMPONENTE_NAOTRATADO;
    }

    string texto;
    int fonteTexto;
    int posCursor;
    int xTexto,yTexto,xCursor,yCursor;
    int altLetra;

    virtual void AjustaPosicaoTextoCursor(){}//pure virtual, porque cada classe derivada vai fazer ajustes diferentes

    virtual int SobeCursor() = 0;

    virtual int DesceCursor() = 0;

    virtual int PulaLinha() = 0;

    virtual string GetTextoVisivel() =0;//pure virtual, porque cada classe derivada vai retornar um texto de forma diferente

    //posiciona o cursor uma posiçăo ŕ frente
    int AvancaCursor(){
        if (posCursor>=texto.size()) return 0;//năo tem caracter na frente do cursor
        posCursor++;
        AjustaPosicaoTextoCursor();
        return 1;
    }

    //posiciona o cursor uma posiçăo atrás
    int VoltaCursor(){
        if (posCursor==0) return 0;//năo tem caractere atrés do cursor
        posCursor--;
        AjustaPosicaoTextoCursor();
        return 1;
    }

    //reira um caracter com a tecla backspace
    int RetiraTextoBackSpace(){
        if (texto.size()==0||posCursor==0) return 0;//năo tem caractere atrés do cursor

        texto.erase(posCursor-1,1);//retira o caracter imediatamente atrás do cursor e retrocede com ele
        VoltaCursor();
        #ifdef PIGCOMAUDIO
        if (audioComponente>=0) CPIGGerenciadorAudios::Play(audioComponente);
        #endif
        return 1;
    }

    //retira um caracter com a tecla delete
    int RetiraTextoDelete(){
        if (texto.size()==0||posCursor>=texto.size()) return 0;//năo tem caracter na frente do cursor

        texto.erase(posCursor,1);//retira o caracter imediatamente a frente do cursor

        #ifdef PIGCOMAUDIO
        if (audioComponente>=0) CPIGGerenciadorAudios::Play(audioComponente);
        #endif
        return 1;
    }

    //adiciona um texto (caracter ou string) na posiçăo indicada pelo cursor (se possível)
    virtual int AdicionaTexto(string frase){
        if (texto.size()+frase.size()>maxCaracteres) return 0;//ultrapassa o limite máximo de carcteres
        //if (somenteNumeros&&!PIGSomenteNumeros(frase)) return 0;//năo é número

        texto.insert(posCursor,frase);

        AvancaCursor();
        return 1;
    }

    //converte caracteres especiais, como acentos por exemplo
    string ConverteString(char *str){
        string resp(str);
        if (strlen(str)>1){
            if ((uint8_t)str[0]==195){
                resp = str[1];
            }/*else if ((uint8_t)str[0]==194){
                resp = str[1];
            }*/

        }
        return resp;
    }

    int CalculaPosicaoCursor(string linha, int xMouse){
        int delta = xMouse-xTexto;
        int largParcial = 0, largUltimaLetra = 0;

        for (unsigned int i=0;i<linha.size();i++){
            string aux;

            aux.assign(linha,0,i+1);

            largParcial = CPIGGerenciadorFontes::GetFonte(fonteTexto)->GetLarguraPixelsString(aux);

            //printf("aux: <%s> %d %d\n",aux.c_str(),largParcial,delta);

            if (delta<largParcial){
                if (delta-largUltimaLetra<largParcial-delta){
                    return i;
                }else return i+1;
                //if (linha[resp]=='\n')
                //    resp--;

            }
            largUltimaLetra = largParcial;
        }

        return linha.size();
    }

    //o botao esquerdo faz com que a ediçăo do trexto comece ou que o cursor seja reposicionado
    virtual PIGEstadoEvento TrataMouseBotaoEsquerdo(SDL_Point p, int inicioLinha=0){
        posCursor = CalculaPosicaoCursor(GetTextoVisivel(),p.x);
        AjustaPosicaoTextoCursor();
        return PIG_COMPONENTE_TRATADO;
    }

    void IniciaBase(int maxCars){
        margemEsq = margemDir = margemCima = margemBaixo = 5;
        posLabel = PIG_POSICAO_ESQ_BAIXO;//posiçăo padrăo do label
        posCursor = 0;//cursor no início do texto
        cursorExibido = true;
        timer = new CPIGTimer(false);//o timer do cursor que só será exibido quando estiver editando
        SetFonteTexto(0);
        maxCaracteres = maxCars;
        IniciaCoresBasicas();
        AjustaPosicaoTextoCursor();
    }

    void SetFoco(bool valor) override{
        CPIGComponente::SetFoco(valor);
        if (temFoco) SDL_StartTextInput();
        else SDL_StopTextInput();
    }

    CPIGCaixaTexto(int idComponente, int altura, int largura, string nomeArq, int maxCars=PIG_MAX_CARS_CAIXATEXTO, int retiraFundo=1, int janela=0):
        CPIGComponente(idComponente,altura,largura,nomeArq,retiraFundo,janela){
            IniciaBase(maxCars);
    }

    CPIGCaixaTexto(int idComponente, int altura, int largura, int maxCars=PIG_MAX_CARS_CAIXATEXTO, int janela=0):
        CPIGComponente(idComponente,altura,largura,janela){
            IniciaBase(maxCars);
    }

    virtual ~CPIGCaixaTexto(){
        delete timer;
    }


public:

    //define o texto a ser mostrado no componente
    virtual int SetTexto(string frase){
        texto = frase;
        posCursor=0;
        AjustaPosicaoTextoCursor();
        return 1;
    }

    //deifne a fonte de texto
    virtual void SetFonteTexto(int fonte){
        fonteTexto = fonte;
        altLetra = CPIGGerenciadorFontes::GetFonte(fonteTexto)->GetTamanhoBaseFonte()+CPIGGerenciadorFontes::GetFonte(fonteTexto)->GetFonteDescent();
        AjustaPosicaoTextoCursor();
    }

    //recupera o texto armazenado no componente
    string GetTexto(){
        return texto;
    }

    //define a cor do fundo
    void SetCorFundo(PIGCor cor){
        coresBasicas[0] = cor;
    }

    //define a cor da fonte
    void SetCorFonte(PIGCor cor){
        coresBasicas[1] = cor;
    }

    //define a cor do cursor
    void SetCorCursor(PIGCor cor){
        coresBasicas[2] = cor;
    }

    //reposiciona o componente
    virtual void Move(double nx, double ny)override{
        int dx = nx-pos.x;
        int dy = ny-pos.y;
        CPIGComponente::Desloca(dx,dy);
        xCursor += dx;
        yCursor += dy;
        xTexto += dx;
        yTexto += dy;
    }

    //define as margens do componente
    virtual void SetMargens(int mEsq, int mDir, int mCima, int mBaixo)override{
        CPIGComponente::SetMargens(mEsq,mDir,mCima,mBaixo);
        AjustaPosicaoTextoCursor();
    }

};

typedef CPIGCaixaTexto *PIGCaixaTexto;
#endif // _CPIGCAIXATEXTO_
