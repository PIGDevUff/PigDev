#ifndef _CPIGTRANSICAO_
#define _CPIGTRANSICAO_

template <typename T>
struct s{
T ini,fim;
};

#define PIG_TROCA(x,y,z){z aux=x;x=y;y=aux;}

class CPIGTransicao{

private:
int id;
struct s<int> *x,*y,*alt,*larg;
struct s<PIG_Cor> *cor;
struct s<double> *ang;
struct s<double> *personalizada[10];
double tempoAtual,tempoTotal;
int idTimer;

public:

CPIGTransicao(int idTransicao,double tempoTransicao){
    id = idTransicao;
    tempoTotal = tempoTransicao;
    idTimer = CPIGGerenciadorTimers::CriaTimer(true);
    x = y = alt = larg = NULL;
    cor = NULL;
    ang = NULL;
    for (int i=0;i<10;i++)
        personalizada[i] = NULL;
}

CPIGTransicao(string str){

}

int GetID(){
    return id;
}

~CPIGTransicao(){
    if (x) free(x);
    if (y) free(y);
    if (alt) free(alt);
    if (larg) free(larg);
    if (cor) free(cor);
    if (ang) free(ang);
    for (int i=0;i<10;i++)
        if (personalizada[i]) free(personalizada[i]);
    CPIGGerenciadorTimers::DestroiTimer(idTimer);
}

void IniciaTransicao(){
    CPIGGerenciadorTimers::GetTimer(idTimer)->Reinicia(false);
}

int CalculaTransicao(){
    tempoAtual =  CPIGGerenciadorTimers::GetTimer(idTimer)->GetTempoDecorrido()/tempoTotal;
    if (tempoAtual>1){
        tempoAtual=1;
        return 0;
    }
    return 1;
}

void InsereTransicaoX(int ini, int fim){
    if (x) free(x);
    x = (struct s<int>*) malloc(sizeof(struct s<int>));
    x->ini = ini;
    x->fim = fim;
}

void InsereTransicaoY(int ini, int fim){
    if (y) free(y);
    y = (struct s<int>*) malloc(sizeof(struct s<int>));
    y->ini = ini;
    y->fim = fim;
}

void InsereTransicaoAltura(int ini, int fim){
    if (alt) free(alt);
    alt = (struct s<int>*) malloc(sizeof(struct s<int>));
    alt->ini = ini;
    alt->fim = fim;
}

void InsereTransicaoLargura(int ini, int fim){
    if (larg) free(larg);
    larg = (struct s<int>*) malloc(sizeof(struct s<int>));
    larg->ini = ini;
    larg->fim = fim;
}

void InsereTransicaoCor(PIG_Cor ini, PIG_Cor fim){
    if (cor) free(cor);
    cor = (struct s<PIG_Cor>*) malloc(sizeof(struct s<PIG_Cor>));
    cor->ini = ini;
    cor->fim = fim;
}

void InsereTransicaoAngulo(double ini, double fim){
    if (ang) free(ang);
    ang = (struct s<double>*) malloc(sizeof(struct s<double>));
    ang->ini = ini;
    ang->fim = fim;
}

void InsereTransicaoPersonalizada(int indice,double ini, double fim){
    if (personalizada[indice]) free(personalizada[indice]);
    personalizada[indice] = (struct s<double>*) malloc(sizeof(struct s<double>));
    personalizada[indice]->ini = ini;
    personalizada[indice]->fim = fim;
}

int GetX(int &valor){
    if (!x) return 0;
    valor = x->fim*(tempoAtual) + x->ini*(1-tempoAtual);
    return 1;
}

int GetY(int &valor){
    if (!y) return 0;
    valor = y->fim*(tempoAtual) + y->ini*(1-tempoAtual);
    return 1;
}

int GetAltura(int &valor){
    if (!alt) return 0;
    valor = alt->fim*(tempoAtual) + alt->ini*(1-tempoAtual);
    return 1;
}

int GetLargura(int &valor){
    if (!larg) return 0;
    valor = larg->fim*(tempoAtual) + larg->ini*(1-tempoAtual);
    return 1;
}

int GetCor(PIG_Cor &valor){
    if (!cor) return 0;
    valor = PIGMixCor(cor->ini,cor->fim,tempoAtual);
    return 1;
}

int GetAngulo(double &valor){
    if (!ang) return 0;
    valor = ang->fim*(tempoAtual) + ang->ini*(1-tempoAtual);
    return 1;
}

int GetPersonalizada(int indice,double &valor){
    if (!personalizada[indice]) return 0;
    valor = personalizada[indice]->fim*(tempoAtual) + personalizada[indice]->ini*(1-tempoAtual);
    return 1;
}

void Inverte(){
    if (x) PIG_TROCA(x->ini,x->fim,int);
    if (y) PIG_TROCA(y->ini,y->fim,int);
    if (alt) PIG_TROCA(alt->ini,alt->fim,int);
    if (larg) PIG_TROCA(larg->ini,larg->fim,int);
    if (cor) PIG_TROCA(cor->ini,cor->fim,PIG_Cor);
    if (ang) PIG_TROCA(ang->ini,ang->fim,double);
    for (int i=0;i<10;i++)
        if (personalizada[i]) PIG_TROCA(personalizada[i]->ini,personalizada[i]->fim,double);
}

};
typedef CPIGTransicao *PIGTransicao;

#endif // _CPIGTRANSICAO_
