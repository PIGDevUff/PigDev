#ifndef _CPIGGERADORPARTICULAS_
#define _CPIGGERADORPARTICULAS_

#include "CPIGParticula.h"

class CPIGGeradorParticulas: public CPIGObjeto{

private:

int id;
int maxParticulas;       //qtd de partículas vivvas e máximo de partículas vivas
std::vector<PIGParticula> parts;
double hpParticulas,maxTempo;
SDL_Rect maxEspaco;
int audioInicio,audioFim;
PIG_Cor *corFundoImagem;
bool retiraFundoImagem;

void IniciaBase(int idGerador,int maximoParticulas, int audioCriacao,int audioEncerramento, PIG_Cor *corFundo, bool retiraFundo, int idJanela){
    id = idGerador;
    maxParticulas = maximoParticulas;
    audioInicio = audioCriacao;
    audioFim = audioEncerramento;
    corFundoImagem = corFundo;
    retiraFundoImagem = retiraFundo;
    maxTempo = 9999999;
    maxEspaco = {INT_MIN,INT_MIN,INT_MAX,INT_MAX};
    hpParticulas = 1;
}

void MoveParticulas(){
    int i=0;
    while (i<parts.size()){
        parts[i]->TrataAutomacao();
        //printf("viva %d %d\n",i,parts[i]->viva);
        if (!parts[i]->viva){
            delete parts[i];
            //parts[i] = NULL;
            if (audioFim>=0)
                CPIGGerenciadorAudios::Play(audioFim);
            //printf("vai deletar\n");
            parts.erase(parts.begin()+i);
            //printf("deletou %d %d size %d\n",id,i,parts.size());
        }else i++;
    }
}

public:

    CPIGGeradorParticulas(int idGerador,int maximoParticulas,PIGObjeto objBase, int audioCriacao,int audioEncerramento, bool retiraFundo, PIG_Cor *corFundo, int idJanela)
        :CPIGObjeto(objBase,1,NULL,idJanela){
        IniciaBase(idGerador,maximoParticulas,audioCriacao,audioEncerramento,corFundo,retiraFundo,idJanela);
    }

    CPIGGeradorParticulas(int idGerador,int maximoParticulas,std::string nomeArqImagem,int audioCriacao,int audioEncerramento, bool retiraFundo, PIG_Cor *corFundo, int idJanela)
        :CPIGObjeto(nomeArqImagem,1,NULL,idJanela){
        id = idGerador;
        IniciaBase(idGerador,maximoParticulas,audioCriacao,audioEncerramento,corFundo,retiraFundo,idJanela);
    }

    ~CPIGGeradorParticulas(){
        for (int i=0;i<parts.size();i++)
            delete parts[i];
    }

    void DefineLimites(SDL_Rect espacoMax, double tempoMax){
        maxEspaco = espacoMax;
        maxTempo = tempoMax;
    }

    int CriaParticula(){
        if (parts.size()>=maxParticulas) return -1;

        PIGParticula part = new CPIGParticula(this,hpParticulas,retiraFundoImagem,corFundoImagem,idJanela);

        part->DefineLimites(maxEspaco,maxTempo);
        part->IniciaAutomacao();
        parts.push_back(part);

        if (audioInicio>=0)
            CPIGGerenciadorAudios::Play(audioInicio);
        //printf("Gerei5\n");
        return parts.size();
    }

    inline void MudaHP(int novoValor){
        hpParticulas = novoValor;
    }

    int Desenha() override{
        MoveParticulas();
        //CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetangulo(pos.x,pos.y,10,10,ROXO);
        for (int i=0;i<parts.size();i++)
            parts[i]->Desenha();
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
};

typedef CPIGGeradorParticulas* PIGGeradorParticulas;
#endif // _CPIGGERADORPARTICULAS_
