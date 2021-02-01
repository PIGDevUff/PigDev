#ifndef _CPIGTRANSICAO_
#define _CPIGTRANSICAO_

typedef struct {
    int x,y,alt,larg;
    double ang;
    PIG_Cor cor;
    int opacidade;
    double personalizada[10];
} PIG_EstadoTransicao;

PIG_EstadoTransicao operator+(PIG_EstadoTransicao a, PIG_EstadoTransicao b){
    PIG_EstadoTransicao c;
    c.x = a.x+b.x;
    c.y = a.y+b.y;
    c.alt = a.alt+b.alt;
    c.larg = a.larg+b.larg;
    c.ang = a.ang+b.ang;
    c.cor = b.cor;
    c.opacidade = a.opacidade+b.opacidade;
    return c;
}

class CPIGTransicao{

private:
PIG_EstadoTransicao ini,fim,delta;
double tempoAtual,tempoTotal,sobraAnterior; //sobraAnterior é um tempo excedido na transição anterior a ser descontado nesta transição
int idTimer;

public:

CPIGTransicao(double tempoTransicao,PIG_EstadoTransicao modificacao){
    tempoTotal = tempoTransicao;
    idTimer = CPIGGerenciadorTimers::CriaTimer(true);
    delta = modificacao;
    sobraAnterior=0;
}

CPIGTransicao(CPIGTransicao *outro){
    tempoTotal = outro->tempoTotal;
    idTimer = CPIGGerenciadorTimers::CriaTimer(true);
    delta = outro->delta;
    sobraAnterior=0;
}

CPIGTransicao(string str){

}

~CPIGTransicao(){
    CPIGGerenciadorTimers::DestroiTimer(idTimer);
}

void IniciaTransicao(PIG_EstadoTransicao inicio,double sobra=0){
    ini = inicio;
    fim = ini+delta;
    CPIGGerenciadorTimers::GetTimer(idTimer)->Reinicia(false);
    tempoAtual = 0.0;
    sobraAnterior = sobra;
}

double CalculaTransicao(){
    double t = CPIGGerenciadorTimers::GetTimer(idTimer)->GetTempoDecorrido()+sobraAnterior;
    tempoAtual =  t/tempoTotal;
    if (tempoAtual>1){
        tempoAtual=1;
    }
    return t-tempoTotal;
}

void InsereTransicaoX(int valorIni, int valorFim){
    ini.x = valorIni;
    fim.x = valorFim;
}

void InsereTransicaoY(int valorIni, int valorFim){
    ini.y = valorIni;
    fim.y = valorFim;
}

void InsereTransicaoAltura(int valorIni, int valorFim){
    ini.alt = valorIni;
    fim.alt = valorFim;
}

void InsereTransicaoLargura(int valorIni, int valorFim){
    ini.larg = valorIni;
    fim.larg = valorFim;
}

void InsereTransicaoCor(PIG_Cor valorIni, PIG_Cor valorFim){
    ini.cor = valorIni;
    fim.cor = valorFim;
}

void InsereTransicaoOpacidade(int valorIni, int valorFim){
    ini.opacidade = valorIni;
    fim.opacidade = valorFim;
}

void InsereTransicaoAngulo(double valorIni, double valorFim){
    ini.ang = valorIni;
    fim.ang = valorFim;
}

void InsereTransicaoPersonalizada(int indice,double valorIni, double valorFim){
    ini.personalizada[indice] = valorIni;
    fim.personalizada[indice] = valorFim;
}

int GetX(){
    return fim.x*(tempoAtual) + ini.x*(1-tempoAtual);
}

int GetY(){
    return fim.y*(tempoAtual) + ini.y*(1-tempoAtual);
}

int GetAltura(){
    return fim.alt*(tempoAtual) + ini.alt*(1-tempoAtual);
}

int GetLargura(){
    return fim.larg*(tempoAtual) + ini.larg*(1-tempoAtual);
}

PIG_Cor GetCor(){
    return PIGMixCor(ini.cor,fim.cor,tempoAtual);
}

int GetOpacidade(){
    return fim.opacidade*(tempoAtual) + ini.opacidade*(1-tempoAtual);
}

double GetAngulo(){
    return fim.ang*(tempoAtual) + ini.ang*(1-tempoAtual);
}

double GetPersonalizada(int indice){
    return fim.personalizada[indice]*(tempoAtual) + ini.personalizada[indice]*(1-tempoAtual);
}

PIG_EstadoTransicao GetEstado(){
    PIG_EstadoTransicao atual;
    //atual.tempoAtual = tempoAtual;
    atual.x = fim.x*(tempoAtual) + ini.x*(1-tempoAtual);
    atual.y = fim.y*(tempoAtual) + ini.y*(1-tempoAtual);
    atual.alt = fim.alt*(tempoAtual) + ini.alt*(1-tempoAtual);
    atual.larg = fim.larg*(tempoAtual) + ini.larg*(1-tempoAtual);
    atual.ang = fim.ang*(tempoAtual) + ini.ang*(1-tempoAtual);
    atual.cor = PIGMixCor(ini.cor,fim.cor,tempoAtual);
    atual.opacidade = fim.opacidade*(tempoAtual) + ini.opacidade*(1-tempoAtual);
    //fprintf(arqP,"get %f %d %d %d %d %f\n",atual.tempoAtual,atual.x,atual.y,atual.alt,atual.larg,atual.ang);
    return atual;
}

PIG_EstadoTransicao GetFim(){
    return fim;
}

void Inverte(){
    delta.x *= -1;
    delta.y *= -1;
    delta.alt *= -1;
    delta.larg *= -1;
    delta.ang *= -1;
    delta.opacidade *= -1;
}

CPIGTransicao *PreparaApos(double tempo, PIG_EstadoTransicao estado){
    return new CPIGTransicao(tempo,estado);
}

};
typedef CPIGTransicao *PIGTransicao;

#endif // _CPIGTRANSICAO_
