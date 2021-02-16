#ifndef _CPIGGERADORPARTICULAS_
#define _CPIGGERADORPARTICULAS_

#include "CPIGParticula.h"
#include "CPIGAnimacao.h"

class CPIGGeradorParticulas: public CPIGAnimacao{

private:

int maxParticulas;       //qtd de partículas vivas e máximo de partículas vivas
std::vector<PIGParticula> parts;
double hpParticulas,maxTempo;
SDL_Rect maxEspaco;
int audioInicio,audioFim;
PIG_Cor *corFundoImagem;
bool retiraFundoImagem;
PIGAutomacao automacaoGDP;

void IniciaBase(int maximoParticulas, int audioCriacao,int audioEncerramento, PIG_Cor *corFundo, bool retiraFundo){
    maxParticulas = maximoParticulas;
    audioInicio = audioCriacao;
    audioFim = audioEncerramento;
    corFundoImagem = corFundo;
    retiraFundoImagem = retiraFundo;
    maxTempo = 9999999;
    maxEspaco = {INT_MIN,INT_MIN,INT_MAX,INT_MAX};
    hpParticulas = 1;
    automacaoGDP = NULL;
}

void AtualizaParticulas(){
    int i=0;
    while (i<parts.size()){
        parts[i]->ChecaTempoVida();
        //printf("viva %d %d %d\n",i,parts[i]->viva,parts[i]->GetID());
        if (parts[i]->viva==false){
            //delete parts[i];
            //printf("antes del %d\n",parts[i]->GetID());
            CPIGGerenciadorSprites::DestroiAnimacao(parts[i]->GetID());
            //parts[i] = NULL;
            if (audioFim>=0)
                CPIGGerenciadorAudios::Play(audioFim);

            parts.erase(parts.begin()+i);
            //printf("deletou %d %d size %d\n",id,i,parts.size());
        }else{
            parts[i]->TrataAutomacao();
            i++;
        }
    }
}

public:

    CPIGGeradorParticulas(int idGerador,int maximoParticulas,PIGObjeto objBase, int audioCriacao,int audioEncerramento, bool retiraFundo, PIG_Cor *corFundo, int idJanela)
        :CPIGAnimacao(idGerador,objBase,retiraFundo,corFundo,idJanela){
        IniciaBase(maximoParticulas,audioCriacao,audioEncerramento,corFundo,retiraFundo);
    }

    CPIGGeradorParticulas(int idGerador,int maximoParticulas,PIGAnimacao animaBase, int audioCriacao,int audioEncerramento, bool retiraFundo, PIG_Cor *corFundo, int idJanela)
        :CPIGAnimacao(idGerador,animaBase,retiraFundo,corFundo,idJanela){
        IniciaBase(maximoParticulas,audioCriacao,audioEncerramento,corFundo,retiraFundo);
    }

    CPIGGeradorParticulas(int idGerador,int maximoParticulas,std::string nomeArqImagem,int audioCriacao,int audioEncerramento, bool retiraFundo, PIG_Cor *corFundo, int idJanela)
        :CPIGAnimacao(idGerador,nomeArqImagem,retiraFundo,corFundo,idJanela){
        IniciaBase(maximoParticulas,audioCriacao,audioEncerramento,corFundo,retiraFundo);
    }

    ~CPIGGeradorParticulas(){
    }

    void DefineLimites(SDL_Rect espacoMax, double tempoMax){
        maxEspaco = espacoMax;
        maxTempo = tempoMax;
    }

    int CriaParticula(){
        if (parts.size()>=maxParticulas) return -1;

        int idPart = CPIGGerenciadorSprites::GetProxIndiceAnimacao();
        PIGParticula part = new CPIGParticula(idPart,this,hpParticulas,retiraFundoImagem,corFundoImagem,idJanela);
        idPart = CPIGGerenciadorSprites::InsereAnimacao(part);

        part->DefineLimites(maxEspaco,maxTempo);
        part->IniciaAutomacao();
        parts.push_back(part);

        if (audioInicio>=0)
            CPIGGerenciadorAudios::Play(audioInicio);

        return parts.size();
    }

    inline void MudaHP(int novoValor){
        hpParticulas = novoValor;
    }

    int Desenha() override{
        AtualizaParticulas();
        //CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetangulo(pos.x,pos.y,10,10,ROXO);
        for (int i=0;i<parts.size();i++)
            parts[i]->Desenha();

        return 1;
    }

    bool Colisao(PIGObjeto outro){
        bool resp = false;
        int i=0;
        while (i<parts.size()){
            resp |= parts[i]->Colisao(outro);
            i++;
        }
        return resp;
    }

    bool Colisao(){
        bool resp = false;
        int i=0;
        while (i<parts.size()-1){
            int j=i+1;
            while (j<parts.size()){
                resp |= parts[i]->Colisao(parts[j]);
                j++;
            }
            i++;
        }
        return resp;
    }

    inline int GetQtdAtivas(){
        return parts.size();
    }

void InsereTransicaoGDP(PIGTransicao t){
    CPIGSprite::InsereTransicao(t,&automacaoGDP);
}

void InsereTransicaoGDP(double tempo, PIG_EstadoTransicao estado){
    CPIGSprite::InsereTransicao(tempo,estado,&automacaoGDP);
}

void LeTransicoesGDP(string nomeArq){
    CPIGSprite::LeTransicoes(nomeArq,&automacaoGDP);
}

void IniciaAutomacaoGDP(){
    CPIGSprite::IniciaAutomacao(&automacaoGDP);
}

void LimpaTransicoesGDP(){
    CPIGSprite::LimpaTransicoes(&automacaoGDP);
}

bool ExecutandoTransicaoGDP(){
    return CPIGSprite::ExecutandoTransicao(&automacaoGDP);
}

void TrataAutomacaoGDP(){
    CPIGSprite::TrataAutomacao(&automacaoGDP);
}

void InsereAcaoGDP(double tempo, double repeticao, PIG_FuncaoSimples acao, void *param){
    CPIGSprite::InsereAcao(tempo,repeticao,acao,param,&automacaoGDP);
}

void DefineTipoTransicaoGDP(PIG_TipoTransicao tipo){
    CPIGSprite::DefineTipoTransicao(tipo,&automacaoGDP);
}

};

typedef CPIGGeradorParticulas* PIGGeradorParticulas;
#endif // _CPIGGERADORPARTICULAS_
