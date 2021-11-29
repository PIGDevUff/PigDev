/**************************************************
A classe CPIGItemComponente descreve o código dos items que compõem certos componentes como checkbox, radiobox, listbox e dropdown.
Todos esses componentes se caracterizam por possuir diversos itens e por se poder marcar/selecionar um ou mais desses itens.
Os elementos principais da classe CPIGItemComponente são: o texto do item (label, obrigatório), a imagem de fundo (textura básica do componente, opcional) e um ícone (imagem extra, opcional).
Além disso, os objetos da classe possuem um ponteiro para função que permite que o frame do ícone seja alterado externamente.
O ícone pode ser alterado para representar a marcação ou não do item dentro de um checkbox ou radiobox.
O label é posicionado sempre internamente, mas pode estar alinhado à direita (com ou sem a presença do ícone), à esquerda (com ou sem a presença do ícone) ou centralizado (com ou sem a presença do ícone).
**************************************************/

#ifndef _CPIGITEMCOMPONENTE_
#define _CPIGITEMCOMPONENTE_

#include "CPIGSprite.h"

class CPIGItemComponente:public CPIGComponente{

private:

    void (*AjustaFrame)(CPIGItemComponente*);       //ponteiro para funçăo que será chamada sempre que algum estado do item mudar
    PIGSprite icone;
    int altIcone,largIcone;
    PIGPosicaoComponente posIcone,posRelativaLabel;
    bool habilitadoPorSi;

    PIGEstadoEvento OnMouseClick(){
        SetAcionado(!GetAcionado());
        if (audioComponente>=0) CPIGGerenciadorAudios::Play(audioComponente);
        return PIG_TRATADO;
    }

    void IniciaBase(string labelItem, string arqImagemIcone="", int alturaIcone=0, int larguraIcone=0,int retiraFundoIcone=1){
        altIcone = alturaIcone;
        largIcone = larguraIcone;
        if (arqImagemIcone!=""){
            icone = new CPIGSprite(-1,arqImagemIcone,retiraFundoIcone,NULL,idJanela);
            icone->SetDimensoes(altIcone,largIcone);
            AlinhaIconeEsquerda();
            posIcone = PIG_COMPONENTE_ESQ_CENTRO;
        }else icone = NULL;
        SetLabel(labelItem);
        posRelativaLabel = PIG_COMPONENTE_ESQ_CENTRO;
        SetPosicaoPadraoLabel(PIG_COMPONENTE_ESQ_CENTRO);
        AjustaFrame = NULL;
        coresBasicas[0] = {0,0,0,0};
        habilitadoPorSi=true;
        tipo = PIG_OUTROCOMPONENTE;
    }

public:

    //item com icone e com fundo
    CPIGItemComponente(int idComponente, int alturaIcone,int larguraIcone, string arqImagemIcone, string arqImagemFundo, string labelItem, int larguraLista, int alturaItemLista, int retiraFundo=1, int retiraFundoIcone=1, int janela=0):
        CPIGComponente(idComponente,alturaItemLista,larguraLista,arqImagemFundo,retiraFundo,janela){
        IniciaBase(labelItem,arqImagemIcone,alturaIcone,larguraIcone,retiraFundoIcone);
    }

    //item com icone e sem fundo
    CPIGItemComponente(int idComponente, int alturaIcone,int larguraIcone, string arqImagemIcone, string labelItem, int larguraLista, int alturaItemLista, int retiraFundoIcone=1, int janela=0):
        CPIGComponente(idComponente,alturaItemLista,larguraLista,janela){
        IniciaBase(labelItem,arqImagemIcone,alturaIcone,larguraIcone,retiraFundoIcone);
    }

    //item sem icone e com fundo
    CPIGItemComponente(int idComponente, string arqImagemFundo, string labelItem, int larguraLista, int alturaItemLista, int retiraFundo=1, int janela=0):
        CPIGComponente(idComponente,alturaItemLista,larguraLista,arqImagemFundo,retiraFundo,janela){
        IniciaBase(labelItem,"",0,0);
    }

    //item sem icone e sem fundo
    CPIGItemComponente(int idComponente, string labelItem, int larguraLista, int alturaItemLista, int retiraFundo=1, int janela=0):
        CPIGComponente(idComponente,alturaItemLista,larguraLista,janela){
        IniciaBase(labelItem,"",0,0);
    }

    virtual ~CPIGItemComponente(){
        if (icone) delete icone;
    }

    void SetAcionado(bool valor)override{
        if (acionado&&!valor){
            Desloca(-margemEsq,-margemBaixo);
            SetDimensoes(alt-(margemCima+margemBaixo),larg-(margemEsq+margemDir));
        }else if (!acionado&&valor){
            Desloca(margemEsq,margemBaixo);
            SetDimensoes(alt+(margemCima+margemBaixo),larg+(margemEsq+margemDir));
        }
        CPIGComponente::SetAcionado(valor);
        if (AjustaFrame) AjustaFrame(this);
    }

    void SetHabilitado(bool valor)override{
        habilitadoPorSi = valor;
        CPIGComponente::SetHabilitado(valor);
        if (AjustaFrame) AjustaFrame(this);
    }

    void SetHabilitadoLista(bool valor){
        if (valor){
           CPIGComponente::SetHabilitado(habilitadoPorSi);
        }else{
            habilitadoPorSi = habilitado;
            CPIGComponente::SetHabilitado(valor);
        }
        if (AjustaFrame) AjustaFrame(this);
    }

    void SetMouseOver(bool valor)override{
        CPIGComponente::SetMouseOver(valor);
        if (AjustaFrame) AjustaFrame(this);
    }

    void DefineFuncaoAjusteFrame(void (*funcao)(CPIGItemComponente*)){
        AjustaFrame = funcao;
        if (AjustaFrame) AjustaFrame(this);
    }

    int Desenha()override{
        if (!visivel) return 0;

        //fundo
        if (text)
            CPIGSprite::Desenha();
        else CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetangulo((int)pos.x,(int)pos.y,alt,larg,coresBasicas[0]);

        if (icone)
            icone->Desenha();

        return CPIGComponente::Desenha();
    }

    void SetDimensoesIcone(int alturaIcone,int larguraIcone){
        altIcone = alturaIcone;
        largIcone = larguraIcone;
        icone->SetDimensoes(altIcone,largIcone);
    }

    void AlinhaLabelDireita(){
        posRelativaLabel = PIG_COMPONENTE_DIR_CENTRO;
        int largLabel = lab->GetLargura();//CGerenciadorFontes::GetLarguraPixels(label,fonteLabel);
        if (icone){
            if (posIcone==PIG_COMPONENTE_ESQ_CENTRO){
                SetPosicaoPersonalizadaLabel(larg-largLabel,0);
            }else SetPosicaoPersonalizadaLabel(larg-largLabel-largIcone,0);
        }else{
            SetPosicaoPersonalizadaLabel(larg-largLabel,0);
        }
    }

    void AlinhaLabelEsquerda(){
        posRelativaLabel = PIG_COMPONENTE_ESQ_CENTRO;
        if (icone){
            if (posIcone==PIG_COMPONENTE_ESQ_CENTRO){
                SetPosicaoPersonalizadaLabel(largIcone,0);
            }else SetPosicaoPersonalizadaLabel(0,0);
        }else{
            SetPosicaoPersonalizadaLabel(0,0);
        }
    }

    void AlinhaLabelCentro(){
        posRelativaLabel = PIG_COMPONENTE_CENTRO_CENTRO;
        int largLabel = lab->GetLargura();//CGerenciadorFontes::GetLarguraPixels(label,fonteLabel);
        if (icone){
            if (posIcone==PIG_COMPONENTE_ESQ_CENTRO){
                SetPosicaoPersonalizadaLabel(largIcone+(larg-largIcone)/2-largLabel/2,0);
            }else SetPosicaoPersonalizadaLabel((larg-largIcone)/2-largLabel/2,0);
        }else{
            SetPosicaoPersonalizadaLabel(larg/2-largLabel/2,0);
        }
    }

    void AlinhaIconeDireita(){
        if (icone){
            posIcone=PIG_COMPONENTE_DIR_CENTRO;
            icone->Move(pos.x+larg-largIcone,pos.y);
            if (posRelativaLabel == PIG_COMPONENTE_ESQ_CENTRO){
                AlinhaLabelEsquerda();
            }else if (posRelativaLabel == PIG_COMPONENTE_CENTRO_CENTRO){
                AlinhaLabelCentro();
            }else if (posRelativaLabel == PIG_COMPONENTE_DIR_CENTRO){
                AlinhaLabelDireita();
            }
        }
    }

    void AlinhaIconeEsquerda(){
        if (icone){
            posIcone=PIG_COMPONENTE_ESQ_CENTRO;
            icone->Move(pos.x,pos.y);
            if (posRelativaLabel == PIG_COMPONENTE_ESQ_CENTRO){
                AlinhaLabelEsquerda();
            }else if (posRelativaLabel == PIG_COMPONENTE_CENTRO_CENTRO){
                AlinhaLabelCentro();
            }else if (posRelativaLabel == PIG_COMPONENTE_DIR_CENTRO){
                AlinhaLabelDireita();
            }
        }
    }

    //define a posiçăo do label (dentre posiçőes pré-estabelecidas)
    void SetPosicaoPadraoLabel(PIGPosicaoComponente pos)override{
        posLabel = pos;
        if (posRelativaLabel == PIG_COMPONENTE_ESQ_CENTRO){
            AlinhaLabelEsquerda();
        }else if (posRelativaLabel == PIG_COMPONENTE_CENTRO_CENTRO){
            AlinhaLabelCentro();
        }else if (posRelativaLabel == PIG_COMPONENTE_DIR_CENTRO){
            AlinhaLabelDireita();
        }
    }

    PIGEstadoEvento TrataEventoMouse(PIGEvento evento)override{
        if (!habilitado) return PIG_DESABILITADO;
        if (!visivel) return PIG_INVISIVEL;

        ChecaMouseOver(GetPosicaoMouse());

        if(mouseOver){
            if (evento.mouse.acao==PIG_MOUSE_PRESSIONADO && evento.mouse.botao == PIG_MOUSE_ESQUERDO){
                return OnMouseClick();
            }
            return PIG_MOUSEOVER;
        }

        return PIG_NAOSELECIONADO;
    }

    void Move(double nx, double ny)override{
        int dx = nx-pos.x;
        int dy = ny-pos.y;
        Desloca(dx,dy);
        SetPosicaoPadraoLabel(posLabel);
    }

    void Desloca(double dx, double dy)override{
        CPIGComponente::Desloca(dx,dy);
        if (icone) icone->Desloca(dx,dy);
        lab->Desloca(dx,dy);
    }

    PIGSprite GetIcone(){
        return icone;
    }

    void SetCorFundo(PIGCor cor){
        coresBasicas[0] = cor;
    }

};

typedef CPIGItemComponente *PIGItemComponente;
#endif //_CPIGITEMCOMPONENTE_
