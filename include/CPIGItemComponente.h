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
        #ifdef PIGCOMAUDIO
        if (audioComponente>=0) CPIGGerenciadorAudios::Play(audioComponente);
        #endif
        return PIG_COMPONENTE_TRATADO;
    }

    void IniciaBase(string labelItem, string arqImagemIcone="", int alturaIcone=0, int larguraIcone=0,int retiraFundoIcone=1){
        altIcone = alturaIcone;
        largIcone = larguraIcone;
        if (arqImagemIcone!=""){
            icone = new CPIGSprite(-1,arqImagemIcone,retiraFundoIcone,NULL,idJanela);
            icone->SetDimensoes(altIcone,largIcone);
            AlinhaIcone(PIG_POSICAO_ESQ_CENTRO);
        }else icone = NULL;
        SetLabel(labelItem);
        posRelativaLabel = PIG_POSICAO_ESQ_CENTRO;
        SetPosicaoPadraoLabel(PIG_POSICAO_ESQ_CENTRO);
        AjustaFrame = NULL;
        coresBasicas[0] = {0,0,0,0};
        habilitadoPorSi=true;
        tipo = PIG_ITEMCOMPONENTE;
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
        if (imagemPropria)
            CPIGSprite::Desenha();
        else CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetangulo((int)pos.x,(int)pos.y,alt,larg,coresBasicas[0]);

        if (icone)
            icone->Desenha();
        //CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetanguloVazado((int)pos.x,(int)pos.y,alt,larg,AMARELO);

        return CPIGComponente::Desenha();
    }

    void SetDimensoesIcone(int alturaIcone,int larguraIcone){
        altIcone = alturaIcone;
        largIcone = larguraIcone;
        icone->SetDimensoes(altIcone,largIcone);
    }

    void AlinhaLabel(PIGPosicaoComponente valor){
        posRelativaLabel = valor;
        int largLabel = lab->GetLargura();
        if (icone&&(valor==PIG_POSICAO_DIR_CENTRO||valor==PIG_POSICAO_CENTRO_CENTRO||valor==PIG_POSICAO_ESQ_CENTRO)){
            switch(posRelativaLabel){
            case PIG_POSICAO_ESQ_CENTRO:
                if (posIcone==PIG_POSICAO_ESQ_CENTRO){
                    SetPosicaoPersonalizadaLabel(largIcone+margemEsq,0);
                }else SetPosicaoPersonalizadaLabel(margemEsq,0);
                break;
            case PIG_POSICAO_CENTRO_CENTRO:
                if (posIcone==PIG_POSICAO_ESQ_CENTRO){
                    SetPosicaoPersonalizadaLabel(margemEsq+largIcone+(larg-largIcone-margemEsq-margemDir)/2-largLabel/2,0);
                }else SetPosicaoPersonalizadaLabel(margemDir+(larg-largIcone-margemEsq-margemDir)/2-largLabel/2,0);
                break;
            case PIG_POSICAO_DIR_CENTRO:
                if (posIcone==PIG_POSICAO_ESQ_CENTRO){
                    SetPosicaoPersonalizadaLabel(larg-largLabel-margemDir,0);
                }else SetPosicaoPersonalizadaLabel(larg-largLabel-largIcone-margemDir,0);
                break;
            }
        }else{
            switch(posRelativaLabel){
            case PIG_POSICAO_ESQ_CENTRO: SetPosicaoPersonalizadaLabel(margemEsq,0); break;
            case PIG_POSICAO_CENTRO_CENTRO: SetPosicaoPersonalizadaLabel(margemEsq+(larg-margemEsq-margemDir)/2-largLabel/2,0); break;
            case PIG_POSICAO_DIR_CENTRO: SetPosicaoPersonalizadaLabel(larg-largLabel-margemDir,0); break;
            }
        }

    }

    void AlinhaIcone(PIGPosicaoComponente valor){
        if (icone&&(valor==PIG_POSICAO_DIR_CENTRO||valor==PIG_POSICAO_ESQ_CENTRO)){
            posIcone=valor;
            if (valor==PIG_POSICAO_DIR_CENTRO)
                icone->Move(pos.x+larg-largIcone-margemDir,pos.y);
            else icone->Move(pos.x+margemEsq,pos.y);
            AlinhaLabel(posRelativaLabel);
        }
    }

    //define a posiçăo do label (dentre posiçőes pré-estabelecidas)
    void SetPosicaoPadraoLabel(PIGPosicaoComponente pos)override{
        AlinhaLabel(pos);
    }

    PIGEstadoEvento TrataEventoMouse(PIGEvento evento)override{
        if (!habilitado) return PIG_COMPONENTE_DESABILITADO;
        if (!visivel) return PIG_COMPONENTE_INVISIVEL;

        ChecaMouseOver(GetPosicaoMouse());

        if(mouseOver){
            if (evento.mouse.acao==PIG_MOUSE_PRESSIONADO && evento.mouse.botao == PIG_MOUSE_ESQUERDO){
                return OnMouseClick();
            }
            return PIG_COMPONENTE_MOUSEOVER;
        }

        return PIG_COMPONENTE_NAOTRATADO;
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
