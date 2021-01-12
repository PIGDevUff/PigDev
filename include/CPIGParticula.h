#ifndef _CPIGPARTICULA_
#define _CPIGPARTICULA_

class CPIGParticula: public CPIGAnimacao{

private:
PIGTimer timer;
int idTimer;
int inix,iniy;
int dx,dy;
int menorX,maiorX,menorY,maiorY;
int hp;
int fading;
double escalaIniX,escalaIniY;//usados para ajustar o tamanho da particula em relação ao tamanho origninal. Se a particula aumentar ou diminuir com o tempo, ainda será aplicado outro fator no método Move();
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
    escalaIniX = escalaIniY = 1.0;
    fading = fadeOut;

    if (usaGerenciadorTimer){
        timer = NULL;
        idTimer = CPIGGerenciadorTimers::CriaTimer();
    }else{
        timer = new CPIGTimer(false);
        idTimer = -1;
    }

    viva = 1;
}

public:
    int viva;

    CPIGParticula(int x, int y, int deslocX,int deslocY,int vida, float anguloRot, float escalaIni, float escalaFim, int fadeOut, std::string nomeArq,int usaGerenciadorTimer=1,int idJanela=0):
        CPIGAnimacao(nomeArq,usaGerenciadorTimer,NULL,1,idJanela){
        tenhoAnimacaoBase = 0;
        IniciaBase(x,y,deslocX,deslocY,vida,anguloRot,escalaIni,escalaFim,fadeOut,usaGerenciadorTimer);
    }

    CPIGParticula(int x, int y, int deslocX,int deslocY,int vida, float anguloRot, float escalaIni, float escalaFim, int fadeOut, PIGAnimacao animacaoBase,int usaGerenciadorTimer=1,int idJanela=0):
        CPIGAnimacao(animacaoBase,usaGerenciadorTimer,NULL,1,idJanela){
        tenhoAnimacaoBase = 1;
        IniciaBase(x,y,deslocX,deslocY,vida,anguloRot,escalaIni,escalaFim,fadeOut,usaGerenciadorTimer);
        SetDimensoes(alt,larg);//para definir o valor de escalaIniX e escalaIniY
    }

    CPIGParticula(int x, int y, int deslocX,int deslocY,int vida, float anguloRot, float escalaIni, float escalaFim, int fadeOut, PIGObjeto objBase,int usaGerenciadorTimer=1,int idJanela=0):
        CPIGAnimacao(objBase,usaGerenciadorTimer,NULL,1,idJanela){
        tenhoAnimacaoBase = 0;
        IniciaBase(x,y,deslocX,deslocY,vida,anguloRot,escalaIni,escalaFim,fadeOut,usaGerenciadorTimer);
        SetDimensoes(alt,larg);//para definir o valor de escalaIniX e escalaIniY
    }

    void DefineLimites(int xMenor,int xMaior,int yMenor,int yMaior, float tempoMax){
        menorX = xMenor;
        maiorX = xMaior;
        menorY = yMenor;
        maiorY = yMaior;
        limTempo = tempoMax;
    }

    ~CPIGParticula(){
        if (timer){
            delete timer;
        }else{
            CPIGGerenciadorTimers::DestroiTimer(idTimer);
        }
    }

    void Move(){
        if (!viva) return;
        float decorrido;
        if (timer){
            decorrido = timer->GetTempoDecorrido();
        }else{
            decorrido = CPIGGerenciadorTimers::GetTimer(idTimer)->GetTempoDecorrido();
        }
        float porcTempoVida = decorrido/limTempo;
        if (porcTempoVida>1.0f){
            viva = false;
            return;
        }

        if (fading)
            CPIGAnimacao::SetOpacidade(255*(1-porcTempoVida));

        float fatorDim = escalaInicial*(1-porcTempoVida)+escalaFinal*(porcTempoVida);
        CPIGAnimacao::SetDimensoes(altOriginal*escalaIniY*fatorDim,largOriginal*escalaIniX*fatorDim);
        CPIGAnimacao::SetPivo(0.5f,0.5f);
        CPIGAnimacao::SetAngulo(decorrido*angRot);

        //int x = xini + dx*decorrido;
        //int y = yini + dy*decorrido;

        CPIGAnimacao::Move(inix+dx*decorrido,iniy+dy*decorrido);
        viva = (pos.x>menorX)&&(pos.x<maiorX)&&(pos.y>menorY)&&(pos.y<maiorY);
    }

    void SetDimensoes(int altura, int largura){
        CPIGAnimacao::SetDimensoes(altura,largura);
        escalaIniX = largura*1.0/largOriginal;
        escalaIniY = altura*1.0/altOriginal;
    }

    void MudaDirecao(int deslocX,int deslocY){
        dx = deslocX;
        dy = deslocY;
    }

    int Colisao(PIGObjeto outro){
        int resp = CPIGAnimacao::Colisao(outro);
        if (resp){
            hp--;
            viva = hp>0;
        }
        return resp;
    }

    int Colisao(CPIGParticula *outra){
        int resp = CPIGAnimacao::Colisao(outra);
        if (resp){
            hp--;
            viva = hp>0;

            outra->hp--;
            outra->viva = hp> 0;
        }
        return resp;
    }
};

typedef CPIGParticula* PIGParticula;
#endif //_CPIGPARTICULA_
