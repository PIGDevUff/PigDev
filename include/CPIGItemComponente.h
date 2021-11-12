/**************************************************
A classe CPIGItemComponente descreve o c�digo dos items que comp�em certos componentes como checkbox, radiobox, listbox e dropdown.
Todos esses componentes se caracterizam por possuir diversos itens e por se poder marcar/selecionar um ou mais desses itens.
Os elementos principais da classe CPIGItemComponente s�o: o texto do item (label, obrigat�rio), a imagem de fundo (textura b�sica do componente, opcional) e um �cone (imagem extra, opcional).
Al�m disso, os objetos da classe possuem um ponteiro para fun��o que permite que o frame do �cone seja alterado externamente.
O �cone pode ser alterado para representar a marca��o ou n�o do item dentro de um cehckbox ou radiobox.
O label � posicionado sempre internamente, mas pode estar alinhado � direita (com ou sem a presen�a do �cone), � esquerda (com ou sem a presen�a do �cone) ou centralizado (com ou sem a presen�a do �cone).
**************************************************/

#ifndef _CPIGITEMCOMPONENTE_
#define _CPIGITEMCOMPONENTE_

#include "CPIGSprite.h"

class CPIGItemComponente:public CPIGComponente{

private:

    void (*AjustaFrame)(CPIGItemComponente*);       //ponteiro para fun��o que ser� chamada sempre que algum estado do item mudar
    PIGSprite icone;
    PIGPosicaoComponente posIcone,posRelativaLabel;

    int OnMouseClick(){
        SetAcionado(!GetAcionado());
        if (audioComponente>=0) CPIGGerenciadorAudios::Play(audioComponente);
        return PIG_SELECIONADO_TRATADO;
    }

    void IniciaBase(std::string labelItem,std::string arqImagemIcone="",int alturaIcone=0,int larguraIcone=0){
        if (arqImagemIcone!=""){
            icone = new CPIGSprite(-1,arqImagemIcone,1,NULL,idJanela);
            icone->SetDimensoes(alturaIcone,larguraIcone);
            AlinhaIconeEsquerda();
            posIcone = PIG_COMPONENTE_ESQ_CENTRO;
        }else icone = NULL;
        SetLabel(labelItem);
        posRelativaLabel = PIG_COMPONENTE_CENTRO_CENTRO;
        SetPosicaoPadraoLabel(PIG_COMPONENTE_CENTRO_CENTRO);
        AjustaFrame = NULL;
        coresBasicas[0] = {0,0,0,0};
        corAtual = 0;
    }

public:

    //item com icone e com fundo
    CPIGItemComponente(int idComponente, int px, int py, int alturaIcone,int larguraIcone, string arqImagemIcone, string arqImagemFundo, string labelItem, int larguraLista, int alturaItemLista, int retiraFundo=1, int janela=0):
        CPIGComponente(idComponente,px,py,alturaItemLista,larguraLista,arqImagemFundo,retiraFundo,janela){
        IniciaBase(labelItem,arqImagemIcone,alturaIcone,larguraIcone);//,larguraLista,alturaItemLista);
    }

    //item com icone e sem fundo
    CPIGItemComponente(int idComponente, int px, int py, int alturaIcone,int larguraIcone, string arqImagemIcone, string labelItem, int larguraLista, int alturaItemLista, int retiraFundo=1, int janela=0):
        CPIGComponente(idComponente,px,py,alturaItemLista,larguraLista,janela){
        IniciaBase(labelItem,arqImagemIcone,alturaIcone,larguraIcone);//,larguraLista,alturaItemLista);
    }

    //item sem icone e com fundo
    CPIGItemComponente(int idComponente, int px, int py, string arqImagemFundo, string labelItem, int larguraLista, int alturaItemLista, int retiraFundo=1, int janela=0):
        CPIGComponente(idComponente,px,py,alturaItemLista,larguraLista,arqImagemFundo,retiraFundo,janela){
        IniciaBase(labelItem,"",0,0);//,larguraLista,alturaItemLista);
    }

    //item sem icone e sem fundo
    CPIGItemComponente(int idComponente, int px, int py, string labelItem, int larguraLista, int alturaItemLista, int retiraFundo=1, int janela=0):
        CPIGComponente(idComponente,px,py,alturaItemLista,larguraLista,janela){
        IniciaBase(labelItem,"",0,0);//,larguraLista,alturaItemLista);
    }

    ~CPIGItemComponente(){
        if (icone) delete icone;
    }

    bool GetAcionado(){
        return acionado;
    }

    void SetAcionado(bool valor){
        if (acionado&&!valor){
            Desloca(-margemEsq,-margemBaixo);
            SetDimensoes(alt-(margemCima+margemBaixo),larg-(margemEsq+margemDir));
        }else if (!acionado&&valor){
            Desloca(margemEsq,margemBaixo);
            SetDimensoes(alt+(margemCima+margemBaixo),larg+(margemEsq+margemDir));
        }
        acionado = valor;
        if (AjustaFrame) AjustaFrame(this);
    }

    void SetHabilitado(bool valor){
        habilitado = valor;
        if (AjustaFrame) AjustaFrame(this);
    }

    void SetFoco(bool valor){
        temFoco = valor;
    }

    void SetMouseOver(bool valor){
        mouseOver = valor;
        if (AjustaFrame) AjustaFrame(this);
    }

    void DefineFuncaoAjusteFrame(void (*funcao)(CPIGItemComponente*)){
        AjustaFrame = funcao;
        if (AjustaFrame) AjustaFrame(this);
    }

    int Desenha()override{
        if (!visivel) return -1;

        //fundo
        if (text)
            CPIGSprite::Desenha();
        else CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetangulo((int)pos.x,(int)pos.y,alt,larg,coresBasicas[corAtual]);

        DesenhaLabel();

        if (icone)
            icone->Desenha();

        if (SDL_RenderIsClipEnabled(renderer)){
            SDL_Rect r;
            SDL_RenderGetClipRect(renderer,&r);
            SDL_RenderSetClipRect(renderer,NULL);
            EscreveHint();
            SDL_RenderSetClipRect(renderer,&r);
        }else{
            EscreveHint();
        }

        return 1;
    }

    void SetAlturaIcone(int alturaIcone){
        int altIcone,largIcone;
        icone->GetDimensoes(altIcone,largIcone);
        icone->SetDimensoes(alturaIcone,largIcone);
    }

    void SetLarguraIcone(int larguraIcone){
        int altIcone,largIcone;
        icone->GetDimensoes(altIcone,largIcone);
        icone->SetDimensoes(altIcone,larguraIcone);
    }

    void AlinhaLabelDireita(){
        posRelativaLabel = PIG_COMPONENTE_DIR_CENTRO;
        int largLabel = lab->GetLargura();//CGerenciadorFontes::GetLarguraPixels(label,fonteLabel);
        if (icone){
            int largIcone,altIcone;
            icone->GetDimensoes(altIcone,largIcone);
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
                int largIcone,altIcone;
                icone->GetDimensoes(altIcone,largIcone);
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
            int largIcone,altIcone;
            icone->GetDimensoes(altIcone,largIcone);
            if (posIcone==PIG_COMPONENTE_ESQ_CENTRO){
                SetPosicaoPersonalizadaLabel(largIcone+(larg-largIcone)/2-largLabel/2,0);
            }else SetPosicaoPersonalizadaLabel((larg-largIcone)/2-largLabel/2,0);
        }else{
            SetPosicaoPersonalizadaLabel(larg/2-largLabel/2,0);
        }
    }

    void AlinhaIconeDireita(){
        if (icone){
            int altIcone,largIcone;
            icone->GetDimensoes(altIcone,largIcone);
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

    //define a posi��o do label (dentre posi��es pr�-estabelecidas)
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

    int TrataEventoMouse(PIGEvento evento)override{
        SDL_Point p;
        if (CPIGGerenciadorJanelas::GetJanela(idJanela)->GetUsandoCameraFixa())
            p = CPIGMouse::PegaXYTela();
        else p = CPIGMouse::PegaXYWorld();

        ChecaMouseOver(p);

        if(mouseOver){
            if (habilitado==false) return PIG_SELECIONADO_DESABILITADO;
            if (visivel==false) return PIG_SELECIONADO_INVISIVEL;
            if (evento.mouse.acao==PIG_MOUSE_PRESSIONADO && evento.mouse.botao == PIG_MOUSE_ESQUERDO){
                return OnMouseClick();
            }
            return PIG_SELECIONADO_MOUSEOVER;
        }

        return PIG_NAO_SELECIONADO;
    }

    int TrataEventoTeclado(PIGEvento evento){
        return 0;
    }

    void Move(double nx, double ny)override{
        int dx = nx-pos.x;
        int dy = ny-pos.y;
        Desloca(dx,dy);
        SetPosicaoPadraoLabel(posLabel);
    }

    void Desloca(double dx, double dy)override{
        CPIGSprite::Desloca(dx,dy);
        if (icone) icone->Desloca(dx,dy);
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
