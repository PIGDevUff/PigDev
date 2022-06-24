#ifndef _CPIGCOMPONENTE_
#define _CPIGCOMPONENTE_

#include "CPIGLabel.h"
#include "CPIGMouse.h"

typedef enum{PIG_POSICAO_CIMA_CENTRO,PIG_POSICAO_CIMA_ESQ,PIG_POSICAO_CIMA_DIR,PIG_POSICAO_BAIXO_CENTRO,PIG_POSICAO_BAIXO_DIR,PIG_POSICAO_BAIXO_ESQ,
             PIG_POSICAO_DIR_CIMA,PIG_POSICAO_DIR_BAIXO,PIG_POSICAO_DIR_CENTRO,PIG_POSICAO_ESQ_BAIXO,PIG_POSICAO_ESQ_CENTRO,PIG_POSICAO_ESQ_CIMA,
             PIG_POSICAO_CENTRO_CENTRO,PIG_POSICAO_PERSONALIZADA} PIGPosicaoComponente;
typedef enum{PIG_ANCORA_NORTE,PIG_ANCORA_SUL,PIG_ANCORA_LESTE,PIG_ANCORA_OESTE,PIG_ANCORA_NORDESTE,PIG_ANCORA_NOROESTE,PIG_ANCORA_SUDESTE,PIG_ANCORA_SUDOESTE,PIG_ANCORA_CENTRO}PIGAncora;
typedef enum{PIG_COMPONENTE_NAOTRATADO,PIG_COMPONENTE_SEMFOCO,PIG_COMPONENTE_MOUSEOVER,PIG_COMPONENTE_INVISIVEL,PIG_COMPONENTE_DESABILITADO,PIG_COMPONENTE_TRATADO}PIGEstadoEvento;
typedef enum{PIG_FORM,PIG_BOTAOCLICK,PIG_BOTAOONOFF,PIG_AREADETEXTO,PIG_CAMPOTEXTO,PIG_RADIOBOX,PIG_CHECKBOX,PIG_LISTBOX,PIG_DROPDOWN,PIG_GAUGEBAR,PIG_GAUGECIRCULAR,PIG_SLIDEBAR,PIG_ITEMCOMPONENTE,PIG_OUTROCOMPONENTE}PIGTipoComponente;

class CPIGComponente: public CPIGSprite{

protected:

    bool temFoco,visivel,habilitado,mouseOver,acionado;
    int audioComponente;
    PIGPosicaoComponente posLabel,posComponente;
    PIGLabel lab,hint;
    PIGFuncaoSimples acao;
    PIGCor coresBasicas[10];
    PIGTipoComponente tipo;
    int margemEsq,margemDir,margemCima,margemBaixo;
    bool imagemPropria;
    void *param;

    //inicializa o componente com valores padrão
    void IniciaBase(bool imagem){
        lab = new CPIGLabel("",BRANCO,0,idJanela);
        hint = new CPIGLabel("",BRANCO,0,idJanela);
        imagemPropria = imagem;
        SetPosicaoPadraoLabel(PIG_POSICAO_CENTRO_CENTRO);
        audioComponente = -1;
        margemEsq = margemDir = margemCima = margemBaixo = 0;
        mouseOver = acionado = temFoco = false;
        habilitado = visivel = true;
        param = NULL;
        acao = NULL;
    }

    //escreve o label
    inline void EscreveLabel(){
        if (lab->GetTexto()!="")
            lab->Desenha();
    }

    //escreve o hint do componente na tela
    void EscreveHint(){
        if (mouseOver&&hint->GetTexto()!=""){
            SDL_Rect r = CPIGGerenciadorJanelas::GetJanela(idJanela)->GetAreaBloqueada();

            if (r.h>0){
                CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetanguloVazado(r.x,r.y,r.h,r.w,AMARELO);
                CPIGGerenciadorJanelas::GetJanela(idJanela)->DesbloqueiaArea();
            }

            SDL_Point p;
            if (CPIGGerenciadorJanelas::GetJanela(idJanela)->GetUsandoCameraFixa())
                p = CPIGMouse::PegaXYTela();
            else p = CPIGMouse::PegaXYWorld();
            hint->Move(p.x+5,p.y+5);
            hint->Desenha();

            if (r.h>0)
                CPIGGerenciadorJanelas::GetJanela(idJanela)->BloqueiaArea(r.x,r.y,r.h,r.w);
        }
    }

    //detecta se o mouse está sobre o componente ou não
    virtual int ChecaMouseOver(SDL_Point pMouse){
        if (visivel==false||habilitado==false)
            return -1;

        SDL_Rect r={(int)pos.x,(int)pos.y,larg,alt};
        SetMouseOver(SDL_PointInRect(&pMouse,&r));
        return mouseOver;
    }

    static PIGPosicaoComponente ConverteStringPosicao(string str){
        transform(str.begin(), str.end(), str.begin(), ::toupper);
        if (str=="CIMA_CENTRO") return PIG_POSICAO_CIMA_CENTRO;
        if (str=="CIMA_ESQ") return PIG_POSICAO_CIMA_ESQ;
        if (str=="CIMA_DIR") return PIG_POSICAO_CIMA_DIR;
        if (str=="BAIXO_CENTRO") return PIG_POSICAO_BAIXO_CENTRO;
        if (str=="BAIXO_DIR") return PIG_POSICAO_BAIXO_DIR;
        if (str=="BAIXO_ESQ") return PIG_POSICAO_BAIXO_ESQ;
        if (str=="DIR_CIMA") return PIG_POSICAO_DIR_CIMA;
        if (str=="DIR_BAIXO") return PIG_POSICAO_DIR_BAIXO;
        if (str=="DIR_CENTRO") return PIG_POSICAO_DIR_CENTRO;
        if (str=="ESQ_BAIXO") return PIG_POSICAO_ESQ_BAIXO;
        if (str=="ESQ_CENTRO") return PIG_POSICAO_ESQ_CENTRO;
        if (str=="ESQ_CIMA") return PIG_POSICAO_ESQ_CIMA;
        if (str=="CENTRO_CENTRO") return PIG_POSICAO_CENTRO_CENTRO;
        return PIG_POSICAO_PERSONALIZADA;
    }

    //move o label de acordo com a posição
    void PosicionaLabel(){
        int altLabel,largLabel;
        lab->GetDimensoes(altLabel,largLabel);
        switch(posLabel){
            case PIG_POSICAO_CIMA_CENTRO:
                lab->Move(pos.x+larg/2-largLabel/2,pos.y+alt+5);
                break;
            case PIG_POSICAO_CIMA_DIR:
                lab->Move(pos.x+larg,pos.y+alt+5);
                break;
            case PIG_POSICAO_CIMA_ESQ:
                lab->Move(pos.x-largLabel,pos.y+alt+5);
                break;
            case PIG_POSICAO_BAIXO_CENTRO:
                lab->Move(pos.x+larg/2-largLabel/2,pos.y-altLabel);
                break;
            case PIG_POSICAO_BAIXO_DIR:
                lab->Move(pos.x+larg,pos.y-altLabel);
                break;
            case PIG_POSICAO_BAIXO_ESQ:
                lab->Move(pos.x-largLabel,pos.y-altLabel);
                break;
            case PIG_POSICAO_ESQ_BAIXO:
                lab->Move(pos.x-5-largLabel,pos.y);
                break;
            case PIG_POSICAO_ESQ_CENTRO:
                lab->Move(pos.x-5-largLabel,pos.y+(alt-altLabel)/2);
                break;
            case PIG_POSICAO_ESQ_CIMA:
                lab->Move(pos.x-5-largLabel,pos.y + (alt-altLabel));
                break;
            case PIG_POSICAO_DIR_BAIXO:
                lab->Move(pos.x+larg+5,pos.y);
                break;
            case PIG_POSICAO_DIR_CENTRO:
                lab->Move(pos.x+larg+5,pos.y + (alt-altLabel)/2);
                break;
            case PIG_POSICAO_DIR_CIMA:
                lab->Move(pos.x+larg+5,pos.y + (alt-altLabel));
                break;
            case PIG_POSICAO_CENTRO_CENTRO:
                //printf("px %d larg %d larglabel %d py %d alt %d altLabel %d\n",(int)pos.x,larg,largLabel,(int)pos.y,alt,altLabel);
                lab->Move(pos.x+larg/2-largLabel/2,pos.y+(alt-altLabel)/2);
                break;
            case PIG_POSICAO_PERSONALIZADA:
                //lab->Move(pos.x+labelX,pos.y+labelY);
                break;
            }
            //PIGPonto2D p = lab->GetXY();
            //printf("id: %d p (%d): %d,%d\n",id,posLabel,(int)p.x,(int)p.y);
    }

    virtual PIGEstadoEvento OnAction(){
        if (acao) acao(id,param);//rever se NULL é necessário
        #ifdef PIGCOMAUDIO
        if (audioComponente>=0) CPIGGerenciadorAudios::Play(audioComponente);
        #endif
        return PIG_COMPONENTE_TRATADO;
    }

    inline SDL_Point GetPosicaoMouse(){
        if (CPIGGerenciadorJanelas::GetJanela(idJanela)->GetUsandoCameraFixa())
            return CPIGMouse::PegaXYTela();
        else return CPIGMouse::PegaXYWorld();
    }

    virtual void ProcessaAtributos(CPIGAtributos atrib){
        int valorInt;
        string valorStr;

        int px = 0, py = 0;
        px = atrib.GetInt("px",0);
        py = atrib.GetInt("py",0);
        Move(px,py);

        int mEsq=0,mDir=0,mCima=0,mBaixo=0;
        mEsq = atrib.GetInt("margemEsq",0);
        mDir = atrib.GetInt("margemDir",0);
        mCima = atrib.GetInt("margemSup",0);
        mBaixo = atrib.GetInt("margemInf",0);
        SetMargens(mEsq,mDir,mCima,mBaixo);

        valorStr = atrib.GetString("label","");
        if (valorStr != "") SetLabel(atrib.GetString("label",""));

        valorStr = atrib.GetString("hint","");
        if (valorStr != "") SetHint(valorStr);

        valorInt = atrib.GetInt("audio",-1);
        if (valorInt != -1) SetAudio(valorInt);

        valorInt = atrib.GetInt("fonteLabel",0);
        if (valorInt != 0) SetFonteLabel(valorInt);

        valorInt = atrib.GetInt("fonteHint",0);
        if (valorInt != 0) SetFonteHint(valorInt);

        valorInt = atrib.GetInt("acionado",0);
        if (valorInt) SetAcionado(valorInt);

        valorInt = atrib.GetInt("habilitado",1);
        if (valorInt) SetHabilitado(1);

        valorInt = atrib.GetInt("visivel",1);
        if (valorInt) SetVisivel(1);

        valorStr = atrib.GetString("corLabel","");
        if (valorStr != "") SetCorLabel(PIGCriaCorString(valorStr));

        valorStr  = atrib.GetString("corHint","");
        if (valorStr != "") SetCorHint(PIGCriaCorString(valorStr));

        valorStr = atrib.GetString("posLabel","");
        if (valorStr != "") SetPosicaoPadraoLabel(ConverteStringPosicao(valorStr));
    }

    CPIGComponente(int idComponente, int altura, int largura, int janela=0)
    :CPIGSprite(idComponente,altura,largura,"",janela){
        IniciaBase(false);
    }

    CPIGComponente(int idComponente, int altura, int largura, string nomeArq, int retiraFundo=1, int janela=0)
    :CPIGSprite(idComponente,nomeArq,retiraFundo,NULL,janela){
        IniciaBase(true);
        CPIGSprite::SetDimensoes(altura,largura);
    }

public:

    virtual ~CPIGComponente(){
        if (lab) delete lab;
        if (hint) delete hint;
    }

    void DefineAcao(PIGFuncaoSimples funcao, void *parametro){
        acao = funcao;
        param = parametro;
    }

    PIGTipoComponente GetTipo(){
        return tipo;
    }

    //desenha o componente, cada subclasse precisa implementar como fazer isso
    virtual inline int Desenha(){
        EscreveLabel();
        EscreveHint();
        return 1;
    }

    virtual PIGEstadoEvento TrataEventoMouse(PIGEvento evento){
        if (!habilitado) return PIG_COMPONENTE_DESABILITADO;
        if (!visivel) return PIG_COMPONENTE_INVISIVEL;
        return PIG_COMPONENTE_NAOTRATADO;
    }

    virtual PIGEstadoEvento TrataEventoTeclado(PIGEvento evento){
        if (!temFoco) return PIG_COMPONENTE_SEMFOCO;
        if (!habilitado) return PIG_COMPONENTE_DESABILITADO;
        if (!visivel) return PIG_COMPONENTE_INVISIVEL;
        return PIG_COMPONENTE_NAOTRATADO;
    }

    //define a mensagem de hint do componente
    void SetHint(string novoHint){
        hint->SetTexto(novoHint);
    }

    //recupera o hint
    string GetHint(){
        return hint->GetTexto();
    }

    //define a cor do hint
    void SetCorHint(PIGCor cor){
        hint->SetCorFonte(cor);
    }

    //recupera a cor do hint
    PIGCor GetCorHint(){
        return hint->GetColoracao();
    }

    //define a fonte do hint
    virtual void SetFonteHint(int fonte){
        hint->SetFonte(fonte);
    }

    //recupera a fonte do hint
    int GetFonteHint(){
        return hint->GetFonte();
    }

    //define o label do componente
    void SetLabel(string novoLabel){
        lab->SetTexto(novoLabel);
        PosicionaLabel();
    }

    //recupera o label
    string GetLabel(){
        return lab->GetTexto();
    }

    //define a cor do label
    void SetCorLabel(PIGCor corLabel){
        lab->SetCorFonte(corLabel);
    }

    //recupera a cor do label
    PIGCor GetCorLabel(){
        return lab->GetColoracao();
    }

    //define a fonte do label
    void SetFonteLabel(int fonte){
        lab->SetFonte(fonte);
        PosicionaLabel();
    }

    //recupera a fonte do label
    int GetFonteLabel(){
        return lab->GetFonte();
    }

    //define o audio padrão do componente
    virtual void SetAudio(int idAudio){
        audioComponente = idAudio;
    }

    //recupera o audio do componente
    virtual int GetAudio(){
        return audioComponente;
    }

    //define a posição do label (dentre posições pré-estabelecidas)
    virtual void SetPosicaoPadraoLabel(PIGPosicaoComponente pos){
        posLabel = pos;
        PosicionaLabel();
    }

    //define a posição do label (posição arbiraria, relativa à posição do componente)
    virtual void SetPosicaoPersonalizadaLabel(int rx, int ry){
        lab->Move(pos.x+rx,pos.y+ry);
        posLabel = PIG_POSICAO_PERSONALIZADA;//evitar que o usuário esqueça de chamar também a SetPosicaoPadraoLabel
        PosicionaLabel();
    }

    virtual void SetVisivel(bool valor){
        visivel = valor;
    }

    virtual void SetFoco(bool valor){
        temFoco = valor;
    }

    virtual void SetHabilitado(bool valor){
        habilitado = valor;
    }

    virtual void SetMouseOver(bool valor){
        mouseOver = valor;
    }

    virtual void SetAcionado(bool valor){
        acionado = valor;
    }

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

    PIGPosicaoComponente GetPosComponente(){
        return posComponente;
    }

/* //ainda nao funcionando
    void SetPosPadraoExternaComponente(PIGPosicaoComponente pos, CPIGComponente *componenteAssociado){
        int altComponente,largComponente;
        PIGPonto2D p = componenteAssociado->GetXY();

        posComponente = pos;
        componenteAssociado->GetDimensoes(altComponente,largComponente);

        switch(pos){
        case PIG_COMPONENTE_CIMA_CENTRO:
            Move(p.x + (largComponente - larg)/2,p.y+altComponente);
            break;
        case PIG_COMPONENTE_CIMA_ESQ:
            Move(p.x,p.y+altComponente);
            break;
        case PIG_COMPONENTE_CIMA_DIR:
            Move(p.x + largComponente - larg,p.y+altComponente);
            break;
        case PIG_COMPONENTE_BAIXO_CENTRO:
            Move(p.x + (largComponente - larg)/2,p.y - alt);
            break;
        case PIG_COMPONENTE_BAIXO_ESQ:
            Move(p.x,p.y - alt);
            break;
        case PIG_COMPONENTE_BAIXO_DIR:
            Move(p.x + largComponente - larg,p.y - alt);
            break;
        case PIG_COMPONENTE_DIR_BAIXO:
            Move(p.x + largComponente,p.y);
            break;
        case PIG_COMPONENTE_DIR_CENTRO:
            Move(p.x + largComponente,p.y + (altComponente - alt)/2);
            break;
        case PIG_COMPONENTE_DIR_CIMA:
            Move(p.x + largComponente,p.y + altComponente - alt);
            break;
        case PIG_COMPONENTE_ESQ_BAIXO:
            Move(p.x - larg,p.y);
            break;
        case PIG_COMPONENTE_ESQ_CIMA:
            Move(p.x - larg,p.y + altComponente - alt);
            break;
        case PIG_COMPONENTE_ESQ_CENTRO:
            Move(p.x - larg,p.y + (altComponente - alt)/2);
            break;
        case PIG_COMPONENTE_CENTRO_CENTRO:
            Move(p.x + (largComponente - larg)/2,p.y + (altComponente - alt)/2);
            break;
        }

    }

    void SetPosPadraoComponenteNaTela(PIG_Ancora ancora){
        int largJanela,altJanela;

        largJanela = CPIGGerenciadorJanelas::GetJanela(idJanela)->GetLargura();
        //altJanela = CPIGGerenciadorJanelas::GetJanela(idJanela)->GetAltura();

        switch(ancora){
        case PIG_ANCORA_SUL:
            Move((largJanela - larg)/2,0);
            break;
        case PIG_ANCORA_SUDOESTE:
            Move(0,0);
            break;
        case PIG_ANCORA_SUDESTE:
            Move(largJanela - larg,0);
            break;
        case PIG_ANCORA_NORTE:
            Move((largJanela - larg)/2,*altJanela - alt);
            break;
        case PIG_ANCORA_NOROESTE:
            Move(0,*altJanela - alt);
            break;
        case PIG_ANCORA_NORDESTE:
            Move(largJanela - larg,*altJanela - alt);
            break;
        case PIG_ANCORA_CENTRO:
            Move((largJanela - larg)/2,(*altJanela - alt)/2);
            break;
        case PIG_ANCORA_OESTE:
            Move(0,(*altJanela - alt)/2);
            break;
        case PIG_ANCORA_LESTE:
            Move(largJanela - larg,(*altJanela - alt)/2);
            break;
        }

    }*/

    virtual void Move(double nx, double ny)override{
        CPIGSprite::Desloca(nx-pos.x,ny-pos.y);
        PosicionaLabel();
    }

    virtual void Desloca(double dx, double dy)override{
        CPIGSprite::Desloca(dx,dy);
        PosicionaLabel();
    }

    void SetDimensoes(int altura, int largura)override{
        CPIGSprite::SetDimensoes(altura,largura);
        PosicionaLabel();
    }

    virtual void SetMargens(int mEsq, int mDir, int mCima, int mBaixo){
        margemEsq = mEsq;
        margemDir = mDir;
        margemCima = mCima;
        margemBaixo = mBaixo;
    }

};

typedef CPIGComponente *PIGComponente;
#endif // _CPIGCOMPONENTE_
