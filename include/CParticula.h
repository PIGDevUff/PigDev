class CParticula: public CAnimacao{

private:
Timer timer;
int idTimer;
int inix,iniy;
int dx,dy;
int menorX,maiorX,menorY,maiorY;
int hp;
int fading;
float limTempo;
float angRot;
float escalaInicial,escalaFinal;
int tenhoAnimacaoBase;

void IniciaBase(int x, int y, int deslocX, int deslocY, int vida, float anguloRot, float escalaIni, float escalaFim, int fadeOut, int usaGerenciadorTimer){
    inix = x;
    iniy = y;
    dx = deslocX;
    dy = deslocY;
    hp = vida;
    angRot = anguloRot;
    escalaInicial = escalaIni;
    escalaFinal = escalaFim;
    fading = fadeOut;

    if (usaGerenciadorTimer){
        timer = NULL;
        idTimer = CGerenciadorTimers::CriaTimer();
    }else{
        timer = new CTimer(false);
        idTimer = -1;
    }

    viva = 1;
}

public:
    int viva;

    CParticula(int x, int y, int deslocX,int deslocY,int vida, float anguloRot, float escalaIni, float escalaFim, int fadeOut, char *nomeArq,int usaGerenciadorTimer=1,int idJanela=0):
        CAnimacao(nomeArq,usaGerenciadorTimer,NULL,1,idJanela){
        tenhoAnimacaoBase = 0;
        IniciaBase(x,y,deslocX,deslocY,vida,anguloRot,escalaIni,escalaFim,fadeOut,usaGerenciadorTimer);
    }

    CParticula(int x, int y, int deslocX,int deslocY,int vida, float anguloRot, float escalaIni, float escalaFim, int fadeOut, Animacao animacaoBase,int usaGerenciadorTimer=1,int idJanela=0):
        CAnimacao(animacaoBase,usaGerenciadorTimer,NULL,1,idJanela){
        tenhoAnimacaoBase = 1;
        IniciaBase(x,y,deslocX,deslocY,vida,anguloRot,escalaIni,escalaFim,fadeOut,usaGerenciadorTimer);
    }

    CParticula(int x, int y, int deslocX,int deslocY,int vida, float anguloRot, float escalaIni, float escalaFim, int fadeOut, Objeto objBase,int usaGerenciadorTimer=1,int idJanela=0):
        CAnimacao(objBase,usaGerenciadorTimer,NULL,1,idJanela){
        tenhoAnimacaoBase = 0;
        IniciaBase(x,y,deslocX,deslocY,vida,anguloRot,escalaIni,escalaFim,fadeOut,usaGerenciadorTimer);
    }

    void DefineLimites(int xMenor,int xMaior,int yMenor,int yMaior, float tempoMax){
        menorX = xMenor;
        maiorX = xMaior;
        menorY = yMenor;
        maiorY = yMaior;
        limTempo = tempoMax;
    }

    ~CParticula(){
        if (timer){
            delete timer;
        }else{
            CGerenciadorTimers::DestroiTimer(idTimer);
        }
    }

    void Move(){
        if (!viva) return;
        float decorrido;
        if (timer){
            decorrido = timer->GetTempoDecorrido();
        }else{
            decorrido = CGerenciadorTimers::GetTempoDecorrido(idTimer);
        }
        float porcTempoVida = decorrido/limTempo;
        if (porcTempoVida>1.0f){
            viva = false;
            return;
        }

        if (fading)
            CAnimacao::SetOpacidade(255*(1-porcTempoVida));

        int altura,largura;
        if (tenhoAnimacaoBase){
            altura = alt;
            largura = larg;
        }else CAnimacao::GetDimensoesOriginais(altura,largura);

        float fatorDim = escalaInicial*(1-porcTempoVida)+escalaFinal*(porcTempoVida);
        CAnimacao::SetDimensoes(altura*fatorDim,largura*fatorDim);
        CAnimacao::SetPivo(0.5f,0.5f);
        CAnimacao::SetAngulo(decorrido*angRot);

        //int x = xini + dx*decorrido;
        //int y = yini + dy*decorrido;

        CAnimacao::Move(inix+dx*decorrido,iniy+dy*decorrido);
        viva = (x>menorX)&&(x<maiorX)&&(y>menorY)&&(y<maiorY);
    }

    void MudaDirecao(int deslocX,int deslocY){
        dx = deslocX;
        dy = deslocY;
    }

    int Colisao(Objeto outro){
        int resp = CAnimacao::Colisao(outro);
        if (resp){
            hp--;
            viva = hp>0;
        }
        return resp;
    }

    int Colisao(CParticula *outra){
        int resp = CAnimacao::Colisao(outra);
        if (resp){
            hp--;
            viva = hp>0;

            outra->hp--;
            outra->viva = hp> 0;
        }
        return resp;
    }
};

typedef CParticula* Particula;
