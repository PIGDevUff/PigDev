#ifndef _CPIGGERADORPARTICULAS_
#define _CPIGGERADORPARTICULAS_

#include "CPIGParticula.h"
#include "CPIGAnimacao.h"

class CPIGGeradorParticulas: public CPIGAnimacao{

private:

    int maxParticulas;       //qtd de partículas vivas e máximo de partículas vivas
    vector<PIGParticula> parts;
    double hpParticulas,maxTempo;
    SDL_Rect maxEspaco;
    int audioInicio,audioFim;
    PIGCor *corFundoImagem;
    bool retiraFundoImagem;
    PIGAutomacao automacaoGDP;

    void IniciaBase(int maximoParticulas, int audioCriacao,int audioEncerramento, PIGCor *corFundo, bool retiraFundo){
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
        unsigned int i=0;
        while (i<parts.size()){
            //printf("viva %d %d %d\n",i,parts[i]->ChecaViva(),parts[i]->GetId());
            if (parts[i]->ChecaViva()==false){;
                //printf("antes del %d (%f)\n",parts[i]->GetID(),maxTempo);
                CPIGGerenciadorSprites::DestroiAnimacao(parts[i]->GetId());

                #ifdef PIGCOMAUDIO
                if (audioFim>=0)
                    CPIGGerenciadorAudios::Play(audioFim);
                #endif

                parts.erase(parts.begin()+i);
                //printf("deletou %d %d size %d\n",id,i,parts.size());
            }else{
                parts[i]->TrataAutomacao();
                //printf("atualizei part %d\n",i);
                i++;
            }
        }
    }

public:

    CPIGGeradorParticulas(int idGerador, int maximoParticulas, PIGObjeto objBase, int audioCriacao, int audioEncerramento, bool retiraFundo, PIGCor *corFundo, int idJanela)
        :CPIGAnimacao(idGerador,objBase,retiraFundo,corFundo,idJanela){
        IniciaBase(maximoParticulas,audioCriacao,audioEncerramento,corFundo,retiraFundo);
    }

    CPIGGeradorParticulas(int idGerador, int maximoParticulas, PIGAnimacao animaBase, int audioCriacao, int audioEncerramento, bool retiraFundo, PIGCor *corFundo, int idJanela)
        :CPIGAnimacao(idGerador,animaBase,retiraFundo,corFundo,idJanela){
        IniciaBase(maximoParticulas,audioCriacao,audioEncerramento,corFundo,retiraFundo);
    }

    CPIGGeradorParticulas(int idGerador, int maximoParticulas, string nomeArqImagem, int audioCriacao, int audioEncerramento, bool retiraFundo, PIGCor *corFundo, int idJanela)
        :CPIGAnimacao(idGerador,nomeArqImagem,retiraFundo,corFundo,idJanela){
        IniciaBase(maximoParticulas,audioCriacao,audioEncerramento,corFundo,retiraFundo);
    }

    virtual ~CPIGGeradorParticulas(){}

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
        //printf("com tempo %f\n",maxTempo);
        part->IniciaAutomacao();
        parts.push_back(part);

        #ifdef PIGCOMAUDIO
        if (audioInicio>=0)
            CPIGGerenciadorAudios::Play(audioInicio);
        #endif

        return parts.size();
    }

    inline void MudaHP(int novoValor){
        hpParticulas = novoValor;
    }

    int Desenha() override{
        AtualizaParticulas();
        //CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetangulo(pos.x,pos.y,10,10,ROXO);
        for (PIGParticula part:parts)
            part->Desenha();

        return 1;
    }

    bool Colisao(PIGObjeto outro){
        bool resp = false;
        for (PIGParticula part:parts){
            resp |= part->Colisao(outro);
        }
        return resp;
    }

    bool Colisao(){
        bool resp = false;
        unsigned int i=0;
        while (i<parts.size()-1){
            unsigned int j=i+1;
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

    inline void InsereTransicaoGDP(PIGTransicao t){
        CPIGSprite::InsereTransicao(t,&automacaoGDP);
    }

    inline void InsereTransicaoGDP(double tempo, PIGEstadoTransicao estado){
        CPIGSprite::InsereTransicao(tempo,estado,&automacaoGDP);
    }

    inline void LeTransicoesGDP(string nomeArq){
        CPIGSprite::LeTransicoes(nomeArq,&automacaoGDP);
    }

    inline void IniciaAutomacaoGDP(){
        CPIGSprite::IniciaAutomacao(&automacaoGDP);
    }

    inline void LimpaTransicoesGDP(){
        CPIGSprite::LimpaTransicoes(&automacaoGDP);
    }

    inline bool ExecutandoTransicaoGDP(){
        return CPIGSprite::ExecutandoTransicao(&automacaoGDP);
    }

    inline void TrataAutomacaoGDP(){
        CPIGSprite::TrataAutomacao(&automacaoGDP);
    }

    inline void InsereAcaoGDP(double tempo, double repeticao, PIGFuncaoSimples acao, void *param){
        CPIGSprite::InsereAcao(tempo,repeticao,acao,param,&automacaoGDP);
    }

    inline void DefineTipoTransicaoGDP(PIGTipoTransicao tipo){
        CPIGSprite::DefineTipoTransicao(tipo,&automacaoGDP);
    }

};

typedef CPIGGeradorParticulas* PIGGeradorParticulas;
#endif // _CPIGGERADORPARTICULAS_
