#ifndef _CPIGCOMPONENTE_
#define _CPIGCOMPONENTE_

#include "CPIGLabel.h"
#include "CPIGMouse.h"

typedef enum{PIG_COMPONENTE_CIMA_CENTRO,PIG_COMPONENTE_CIMA_ESQ,PIG_COMPONENTE_CIMA_DIR,PIG_COMPONENTE_BAIXO_CENTRO,PIG_COMPONENTE_BAIXO_DIR,PIG_COMPONENTE_BAIXO_ESQ,
             PIG_COMPONENTE_DIR_CIMA,PIG_COMPONENTE_DIR_BAIXO,PIG_COMPONENTE_DIR_CENTRO,PIG_COMPONENTE_ESQ_BAIXO,PIG_COMPONENTE_ESQ_CENTRO,PIG_COMPONENTE_ESQ_CIMA,
             PIG_COMPONENTE_CENTRO_CENTRO,PIG_COMPONENTE_PERSONALIZADA} PIG_PosicaoComponente;
typedef enum{PIG_ANCORA_NORTE,PIG_ANCORA_SUL,PIG_ANCORA_LESTE,PIG_ANCORA_OESTE,PIG_ANCORA_NORDESTE,PIG_ANCORA_NOROESTE,PIG_ANCORA_SUDESTE,PIG_ANCORA_SUDOESTE,PIG_ANCORA_CENTRO}PIG_Ancora;
typedef enum{PIG_NAO_SELECIONADO,PIG_SELECIONADO_MOUSEOVER,PIG_SELECIONADO_INVISIVEL,PIG_SELECIONADO_DESABILITADO,PIG_SELECIONADO_TRATADO}PIG_EstadosEventos;

class CPIGComponente: public CPIGSprite{

protected:

    bool temFoco,visivel,habilitado,mouseOver,acionado;
    int audioComponente;
    int id;
    PIG_PosicaoComponente posLabel,posComponente;
    PIGLabel lab,hint;
    PIG_FuncaoSimples acao;
    PIG_Cor coresBasicas[10];
    int corAtual;
    int margemEsq,margemDir,margemCima,margemBaixo;
    void *param;

    //inicializa o componente com valores padrão
    void IniciaBase(int idComponente, int px, int py){
        id = idComponente;
        lab = new CPIGLabel("",0,BRANCO,idJanela);
        hint = new CPIGLabel("",0,BRANCO,idJanela);
        SetPosicaoPadraoLabel(PIG_COMPONENTE_CENTRO_CENTRO);
        audioComponente = -1;
        pos.x = px;
        pos.y = py;
        margemEsq = margemDir = margemCima = margemBaixo = 0;
        mouseOver = acionado = temFoco = false;
        habilitado = visivel = true;
        param = NULL;
        acao = NULL;
    }

    //escreve o hint do componente na tela
    void EscreveHint(){
        if (mouseOver&&hint->GetTexto()!=""){
            SDL_Point p;
            if (CPIGGerenciadorJanelas::GetJanela(idJanela)->GetUsandoCameraFixa())
                p = CPIGMouse::PegaXYTela();
            else p = CPIGMouse::PegaXYWorld();
            hint->Move(p.x+16,p.y+5);
            hint->Desenha();
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

    //move o label de acordo com a posição
    void PosicionaLabel(){
        int altLabel,largLabel;
        lab->GetDimensoes(altLabel,largLabel);
        switch(posLabel){
            case PIG_COMPONENTE_CIMA_CENTRO:
                lab->Move(pos.x+larg/2-largLabel/2,pos.y+alt+5);
                break;
            case PIG_COMPONENTE_CIMA_DIR:
                lab->Move(pos.x+larg,pos.y+alt+5);
                break;
            case PIG_COMPONENTE_CIMA_ESQ:
                lab->Move(pos.x-largLabel,pos.y+alt+5);
                break;
            case PIG_COMPONENTE_BAIXO_CENTRO:
                lab->Move(pos.x+larg/2-largLabel/2,pos.y-altLabel);
                break;
            case PIG_COMPONENTE_BAIXO_DIR:
                lab->Move(pos.x+larg,pos.y-altLabel);
                break;
            case PIG_COMPONENTE_BAIXO_ESQ:
                lab->Move(pos.x-largLabel,pos.y-altLabel);
                break;
            case PIG_COMPONENTE_ESQ_BAIXO:
                lab->Move(pos.x-5-largLabel,pos.y);
                break;
            case PIG_COMPONENTE_ESQ_CENTRO:
                lab->Move(pos.x-5-largLabel,pos.y+(alt-altLabel)/2);
                break;
            case PIG_COMPONENTE_ESQ_CIMA:
                lab->Move(pos.x-5-largLabel,pos.y + (alt-altLabel));
                break;
            case PIG_COMPONENTE_DIR_BAIXO:
                lab->Move(pos.x+larg+5,pos.y);
                break;
            case PIG_COMPONENTE_DIR_CENTRO:
                lab->Move(pos.x+larg+5,pos.y + (alt-altLabel)/2);
                break;
            case PIG_COMPONENTE_DIR_CIMA:
                lab->Move(pos.x+larg+5,pos.y + (alt-altLabel));
                break;
            case PIG_COMPONENTE_CENTRO_CENTRO:
                //printf("px %d larg %d larglabel %d py %d alt %d altLabel %d\n",(int)pos.x,larg,largLabel,(int)pos.y,alt,altLabel);
                lab->Move(pos.x+larg/2-largLabel/2,pos.y+(alt-altLabel)/2);
                break;
            case PIG_COMPONENTE_PERSONALIZADA:
                //lab->Move(pos.x+labelX,pos.y+labelY);
                break;
            }
            //PIGPonto2D p = lab->GetXY();
            //printf("p (%d): %d,%d\n",posLabel,(int)p.x,(int)p.y);
    }

    //desenha o label
    inline void DesenhaLabel(){
        lab->Desenha();
    }

    virtual int OnAction(){
        if (acao) acao(id,param);//rever se NULL é necessário
        if (audioComponente>=0) CPIGGerenciadorAudios::Play(audioComponente);
        return PIG_SELECIONADO_TRATADO;
    }

public:

    CPIGComponente(int idComponente,int px,int py, int altura, int largura, int janela=0)
    :CPIGSprite(idComponente,altura, largura, "",janela){
        IniciaBase(idComponente,px,py);
    }

    CPIGComponente(int idComponente,int px,int py, int altura, int largura, std::string nomeArq,int retiraFundo=1,int janela=0)
    :CPIGSprite(idComponente,nomeArq,retiraFundo,NULL,janela){
        IniciaBase(idComponente,px,py);
        CPIGSprite::SetDimensoes(altura,largura);
    }

    virtual ~CPIGComponente(){
        if (lab) delete lab;
        if (hint) delete hint;
    }

    void DefineAcao(PIG_FuncaoSimples funcao,void *parametro){
        acao = funcao;
        param = parametro;
    }

    static CPIGAtributos GetAtributos(string parametros){
        CPIGAtributos resp;
        stringstream ss(parametros);
        string variavel,valorString;
        int valorInteiro;

        while(ss >> variavel){
            if(variavel == "idComponente") {ss >> valorInteiro; resp.SetValorInt(variavel,valorInteiro);}
            if(variavel == "px") {ss >> valorInteiro; resp.SetValorInt(variavel,valorInteiro);}
            if(variavel == "py") {ss >> valorInteiro; resp.SetValorInt(variavel,valorInteiro);}
            if(variavel == "altura") {ss >> valorInteiro; resp.SetValorInt(variavel,valorInteiro);}
            if(variavel == "largura") {ss >> valorInteiro; resp.SetValorInt(variavel,valorInteiro);}
            if(variavel == "alturaLinha") {ss >> valorInteiro; resp.SetValorInt(variavel,valorInteiro);}
            if(variavel == "alturaItem") {ss >> valorInteiro; resp.SetValorInt(variavel,valorInteiro);}
            if(variavel == "larguraItem") {ss >> valorInteiro; resp.SetValorInt(variavel,valorInteiro);}
            if(variavel == "alturaMarcador") {ss >> valorInteiro; resp.SetValorInt(variavel,valorInteiro);}
            if(variavel == "larguraMarcador") {ss >> valorInteiro; resp.SetValorInt(variavel,valorInteiro);}
            if(variavel == "nomeArq") {ss >> valorString; resp.SetValorString(variavel,valorString);}
            if(variavel == "nomeArqMarcador") {ss >> valorString; resp.SetValorString(variavel,valorString);}
            if(variavel == "nomeArqItem") {ss >> valorString; resp.SetValorString(variavel,valorString);}
            if(variavel == "label") {ss >> valorString; resp.SetValorString(variavel,valorString);}
            if(variavel == "retiraFundo") {ss >> valorInteiro; resp.SetValorInt(variavel,valorInteiro);}
            if(variavel == "retiraFundoMarcador") {ss >> valorInteiro; resp.SetValorInt(variavel,valorInteiro);}
            if(variavel == "raioInterno") {ss >> valorInteiro; resp.SetValorInt(variavel,valorInteiro);}
            if(variavel == "label") {ss >> valorInteiro; resp.SetValorInt(variavel,valorInteiro);}
            if(variavel == "janela") {ss >> valorInteiro; resp.SetValorInt(variavel,valorInteiro);}
        }

        return resp;
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
        return lab->GetColoracao();
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
    virtual void SetPosicaoPadraoLabel(PIG_PosicaoComponente pos){
        posLabel = pos;
        PosicionaLabel();
    }

    //define a posição do label (posição arbiraria, relativa à posição do componente)
    virtual void SetPosicaoPersonalizadaLabel(int rx, int ry){
        lab->Move(pos.x+rx,pos.y+ry);
        posLabel = PIG_COMPONENTE_PERSONALIZADA;//evitar que o usuário esqueça de chamar também a SetPosicaoPadraoLabel
        PosicionaLabel();
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

    void SetPosPadraoExternaComponente(PIG_PosicaoComponente pos,CPIGComponente *componenteAssociado){
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

    //ainda nao funcionando
    /*void SetPosPadraoComponenteNaTela(PIG_Ancora ancora){
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

    void SetCorBasica(int indice, PIG_Cor cor){
        if (indice<0||indice>=10) return;
        coresBasicas[indice] = cor;
    }

    void Move(double nx, double ny)override{
        CPIGSprite::Desloca(nx-pos.x,ny-pos.y);
        PosicionaLabel();
    }

    void SetDimensoes(int altura,int largura)override{
        CPIGSprite::SetDimensoes(altura,largura);
        PosicionaLabel();
    }

    inline SDL_Point GetPosicaoMouse(){
        if (CPIGGerenciadorJanelas::GetJanela(idJanela)->GetUsandoCameraFixa())
            return CPIGMouse::PegaXYTela();
        else return CPIGMouse::PegaXYWorld();
    }

    virtual void SetMargens(int mEsq,int mDir,int mCima,int mBaixo){
        margemEsq = mEsq;
        margemDir = mDir;
        margemCima = mCima;
        margemBaixo = mBaixo;
    }

};

typedef CPIGComponente *PIGComponente;
#endif // _CPIGCOMPONENTE_
