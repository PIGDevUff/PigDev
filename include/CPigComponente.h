#ifndef _CPigComponente_
#define _CPigComponente_

#include "CVisual.h"

//typedef enum{COMPONENTE_NORMAL,COMPONENTE_MOUSEOVER,COMPONENTE_ACIONADO,COMPONENTE_DESABILITADO} PIG_EstadoComponente;
typedef enum{PIG_COMPONENTE_CIMA_CENTRO,PIG_COMPONENTE_CIMA_ESQ,PIG_COMPONENTE_CIMA_DIR,PIG_COMPONENTE_BAIXO_CENTRO,PIG_COMPONENTE_BAIXO_DIR,PIG_COMPONENTE_BAIXO_ESQ,
             PIG_COMPONENTE_DIR_CIMA,PIG_COMPONENTE_DIR_BAIXO,PIG_COMPONENTE_DIR_CENTRO,PIG_COMPONENTE_ESQ_BAIXO,PIG_COMPONENTE_ESQ_CENTRO,PIG_COMPONENTE_ESQ_CIMA,
             PIG_COMPONENTE_CENTRO_CENTRO,PIG_COMPONENTE_PERSONALIZADA} PIG_PosicaoComponente;
typedef enum{PIG_ANCORA_NORTE,PIG_ANCORA_SUL,PIG_ANCORA_LESTE,PIG_ANCORA_OESTE,PIG_ANCORA_NORDESTE,PIG_ANCORA_NOROESTE,PIG_ANCORA_SUDESTE,PIG_ANCORA_SUDOESTE,PIG_ANCORA_CENTRO}PIG_Ancora;
typedef enum{PIG_NAO_SELECIONADO,PIG_SELECIONADO_MOUSEOVER,PIG_SELECIONADO_INVISIVEL,PIG_SELECIONADO_DESABILITADO,PIG_SELECIONADO_TRATADO}PIG_EstadosEventos;

class CPigComponente: public CPigVisual{

protected:

    bool temFoco,visivel,habilitado,mouseOver,acionado;
    int audioComponente;
    int id;
    PIG_PosicaoComponente posLabel,posComponente;
    PigLabel lab,hint;

    //inicializa o componente com valores padrão
    void IniciaBase(int idComponente, int px, int py){
        id = idComponente;
        posLabel = PIG_COMPONENTE_CENTRO_CENTRO;
        lab = new CPigLabel("",0,BRANCO,idJanela);
        hint = new CPigLabel("",0,BRANCO,idJanela);
        PosicionaLabel();
        audioComponente = -1;
        x = px;
        y = py;
        temFoco = false;
        acionado = false;
        mouseOver = false;
        visivel = true;
        habilitado = true;
    }

    //escreve o hint do componente na tela
    void EscreveHint(){
        if (mouseOver&&hint->GetTexto()!=""){
            int mx,my;
            CMouse::PegaXY(mx,my);
            hint->Move(mx+16,my+5);
            hint->Desenha();
        }
    }

    //detecta se o mouse está sobre o componente ou não
    virtual int ChecaMouseOver(SDL_Point pMouse){
        if (visivel==false||habilitado==false)
            return -1;

        SDL_Rect r={x,y,larg,alt};
        SetMouseOver(SDL_PointInRect(&pMouse,&r));
        return mouseOver;
    }

    //move o label de acordo com a posição
    void PosicionaLabel(){
        int altLabel,largLabel;
        lab->GetDimensoes(altLabel,largLabel);// = lab->GetAltura(),largLabel=lab->GetLargura();
        switch(posLabel){
            case PIG_COMPONENTE_CIMA_CENTRO:
                lab->Move(x+larg/2-largLabel/2,y+alt+5);
                break;
            case PIG_COMPONENTE_CIMA_DIR:
                lab->Move(x+larg,y+alt+5);//,fonteLabel,CPIG_TEXTO_DIREITA);
                break;
            case PIG_COMPONENTE_CIMA_ESQ:
                lab->Move(x-largLabel,y+alt+5);//,fonteLabel,CPIG_TEXTO_ESQUERDA);
                break;
            case PIG_COMPONENTE_BAIXO_CENTRO:
                lab->Move(x+larg/2-largLabel/2,y-altLabel);//,fonteLabel,CPIG_TEXTO_CENTRO);
                break;
            case PIG_COMPONENTE_BAIXO_DIR:
                lab->Move(x+larg,y-altLabel);//,fonteLabel,CPIG_TEXTO_DIREITA);
                break;
            case PIG_COMPONENTE_BAIXO_ESQ:
                lab->Move(x-largLabel,y-altLabel);//,fonteLabel,CPIG_TEXTO_ESQUERDA);
                break;
            case PIG_COMPONENTE_ESQ_BAIXO:
                lab->Move(x-5-largLabel,y);//,fonteLabel);//,CPIG_TEXTO_DIREITA);
                break;
            case PIG_COMPONENTE_ESQ_CENTRO:
                lab->Move(x-5-largLabel,y+(alt-altLabel)/2);//,fonteLabel,CPIG_TEXTO_DIREITA);
                break;
            case PIG_COMPONENTE_ESQ_CIMA:
                lab->Move(x-5-largLabel,y + (alt-altLabel));//,fonteLabel,CPIG_TEXTO_ESQUERDA);
                break;
            case PIG_COMPONENTE_DIR_BAIXO:
                lab->Move(x+larg+5,y);//,fonteLabel,CPIG_TEXTO_ESQUERDA);
                break;
            case PIG_COMPONENTE_DIR_CENTRO:
                lab->Move(x+larg+5,y + (alt-altLabel)/2);//,fonteLabel,CPIG_TEXTO_ESQUERDA);
                break;
            case PIG_COMPONENTE_DIR_CIMA:
                lab->Move(x+larg+5,y + (alt-altLabel));//,fonteLabel,CPIG_TEXTO_ESQUERDA);
                break;
            case PIG_COMPONENTE_CENTRO_CENTRO:
                lab->Move(x+larg/2-largLabel/2,y+(alt-altLabel)/2);//,fonteLabel,CPIG_TEXTO_CENTRO);
                break;
            case PIG_COMPONENTE_PERSONALIZADA:
                //lab->Move(x+labelX,y+labelY);//,fonteLabel,CPIG_TEXTO_ESQUERDA);
                break;
            }
    }

    //desenha o label
    inline void DesenhaLabel(){
        lab->Desenha();
    }

public:

    CPigComponente(int idComponente,int px,int py, int altura, int largura, int janela=0):CPigVisual(altura, largura, "",janela){
        IniciaBase(idComponente,px,py);
    }

    CPigComponente(int idComponente,int px,int py, int altura, int largura, std::string nomeArq,int retiraFundo=1,int janela=0):CPigVisual(nomeArq,retiraFundo,NULL,janela){
        IniciaBase(idComponente,px,py);
        CPigVisual::SetDimensoes(altura,largura);
    }

    ~CPigComponente(){
        if (lab) delete lab;
        if (hint) delete hint;
    }

    //recupera o id do componente
    int GetId(){
        return id;
    }

    //desenha o componente, cada subclasse precisa implementar como fazer isso
    virtual int Desenha()=0;

    virtual int TrataEventoMouse(PIG_Evento evento)=0;
    virtual int TrataEventoTeclado(PIG_Evento evento)=0;

    //define a mensagem de hint do componente
    void SetHint(std::string novoHint){
        hint->SetTexto(novoHint);
    }

    //define o label do componente
    virtual void SetLabel(std::string novoLabel){
        lab->SetTexto(novoLabel);
        PosicionaLabel();
    }

    //define a cor do label
    virtual void SetCorLabel(PIG_Cor corLabel){
        lab->SetCor(corLabel);
    }

    //recupera a cor do label
    virtual PIG_Cor GetCorLabel(){
        return lab->GetCor();
    }

    //define o audio padrão do componentePIG_COMPONENTE_CENTRO_CENTRO
    virtual void SetAudio(int idAudio){
        audioComponente = idAudio;
    }

    //define a fonte do hint
    virtual void SetFonteHint(int fonte){
        hint->SetFonte(fonte);
    }

    //define a cor do hint
    virtual void SetCorHint(PIG_Cor cor){
        hint->SetCor(cor);
    }

    //recupera o hint
    std::string GetHint(){
        return hint->GetTexto();
    }

    //recupera a fonte do hint
    int GetFonteHint(){
        return hint->GetFonte();
    }

    //define a fonte do label
    virtual void SetFonteLabel(int fonte){
        lab->SetFonte(fonte);
        PosicionaLabel();
    }

    //recupera o label
    std::string GetLabel(){
        return lab->GetTexto();
    }

    //define a posição do label (dentre posições pré-estabelecidas)
    virtual int SetPosicaoPadraoLabel(PIG_PosicaoComponente pos){
        posLabel = pos;
        PosicionaLabel();
        return 1;
    }

    //define a posição do label (posição arbiraria, relativa à posição do componente)
    virtual int SetPosicaoPersonalizadaLabel(int rx, int ry){
        lab->Move(x+rx,y+ry);
        posLabel = PIG_COMPONENTE_PERSONALIZADA;//evitar que o usuário esqueça de chamar também a SetPosicaoPadraoLabel
        PosicionaLabel();
        return 1;
    }

    virtual void SetVisivel(bool valor){
        visivel = valor;
    }

    virtual void SetFoco(bool valor)=0;

    virtual void SetHabilitado(bool valor)=0;

    virtual void SetMouseOver(bool valor)=0;

    virtual void SetAcionado(bool valor)=0;

    bool GetFoco(){
        return temFoco;
    }

    bool GetVisivel(){
        return visivel;
    }

    bool GetHabilitado(){
        return habilitado;
    }

    bool GetAcionado(){
        return acionado;
    }

    bool GetMouseOver(){
        return mouseOver;
    }

    PIG_PosicaoComponente GetPosComponente(){
        return posComponente;
    }

    void SetPosPadraoExternaComponente(PIG_PosicaoComponente pos,CPigComponente *componenteAssociado){
        int xComponente,yComponente,altComponente,largComponente;
        int largura,altura;

        posComponente = pos;
        componenteAssociado->GetDimensoes(altComponente,largComponente);
        componenteAssociado->GetXY(xComponente,yComponente);
        this->GetDimensoes(altura,largura);

        switch(pos){
        case PIG_COMPONENTE_CIMA_CENTRO:
            Move(xComponente + (largComponente - largura)/2,yComponente+altComponente);
            break;
        case PIG_COMPONENTE_CIMA_ESQ:
            Move(xComponente,yComponente+altComponente);
            break;
        case PIG_COMPONENTE_CIMA_DIR:
            Move(xComponente + largComponente - largura,yComponente+altComponente);
            break;
        case PIG_COMPONENTE_BAIXO_CENTRO:
            Move(xComponente + (largComponente - largura)/2,yComponente - altura);
            break;
        case PIG_COMPONENTE_BAIXO_ESQ:
            Move(xComponente,yComponente - altura);
            break;
        case PIG_COMPONENTE_BAIXO_DIR:
            Move(xComponente + largComponente - largura,yComponente - altura);
            break;
        case PIG_COMPONENTE_DIR_BAIXO:
            Move(xComponente + largComponente,yComponente);
            break;
        case PIG_COMPONENTE_DIR_CENTRO:
            Move(xComponente + largComponente,yComponente + (altComponente - altura)/2);
            break;
        case PIG_COMPONENTE_DIR_CIMA:
            Move(xComponente + largComponente,yComponente + altComponente - altura);
            break;
        case PIG_COMPONENTE_ESQ_BAIXO:
            Move(xComponente - largura,yComponente);
            break;
        case PIG_COMPONENTE_ESQ_CIMA:
            Move(xComponente - largura,yComponente + altComponente - altura);
            break;
        case PIG_COMPONENTE_ESQ_CENTRO:
            Move(xComponente - largura,yComponente + (altComponente - altura)/2);
            break;
        case PIG_COMPONENTE_CENTRO_CENTRO:
            Move(xComponente + (largComponente - largura)/2,yComponente + (altComponente - altura)/2);
            break;
        }

    }

    void SetPosPadraoComponenteNaTela(PIG_Ancora ancora){
        int largTela,altTela;
        int altura,largura;
        largTela = CGerenciadorJanelas::GetLargura(idJanela);
        altTela = CGerenciadorJanelas::GetAltura(idJanela);

        this->GetDimensoes(altura,largura);

        switch(ancora){
        case PIG_ANCORA_SUL:
            Move((largTela - largura)/2,0);
            break;
        case PIG_ANCORA_SUDOESTE:
            Move(0,0);
            break;
        case PIG_ANCORA_SUDESTE:
            Move(largTela - largura,0);
            break;
        case PIG_ANCORA_NORTE:
            Move((largTela - largura)/2,altTela - altura);
            break;
        case PIG_ANCORA_NOROESTE:
            Move(0,altTela - altura);
            break;
        case PIG_ANCORA_NORDESTE:
            Move(largTela - largura,altTela - altura);
            break;
        case PIG_ANCORA_CENTRO:
            Move((largTela - largura)/2,(altTela - altura)/2);
            break;
        case PIG_ANCORA_OESTE:
            Move(0,(altTela - altura)/2);
            break;
        case PIG_ANCORA_LESTE:
            Move(largTela - largura,(altTela - altura)/2);
            break;
        }

    }

    void Move(int nx, int ny)override{
        int dx = nx-x;
        int dy = ny-y;
        CPigVisual::Desloca(dx,dy);
        lab->Desloca(dx,dy);
    }

};

typedef CPigComponente *PigComponente;
#endif // _CPigComponente_
