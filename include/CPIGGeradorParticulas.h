#ifndef _CPIGGERADORPARTICULAS_
#define _CPIGGERADORPARTICULAS_

#include "CPIGParticula.h"

class CPIGGeradorParticulas{

private:

int id;
PIGObjeto modelo;        //modelo usado para criar as partículas
int maxParticulas;       //qtd de partículas vivvas e máximo de partículas vivas
std::vector<PIGParticula> parts;
double hpParticulas;
int audioInicio,audioFim;

public:

    CPIGGeradorParticulas(int idGerador,int maximoParticulas,PIGObjeto objBase, int audioCriacao,int audioEncerramento, int idJanela){
        id = idGerador;
        modelo = new CPIGObjeto(objBase,NULL,1,idJanela);
        maxParticulas = maximoParticulas;
        audioInicio = audioCriacao;
        audioFim = audioEncerramento;
        hpParticulas = 1;
    }

    CPIGGeradorParticulas(int idGerador,int maximoParticulas,std::string nomeArqImagem,int audioCriacao,int audioEncerramento, int idJanela){
        id = idGerador;
        modelo = new CPIGObjeto(nomeArqImagem,NULL,1,idJanela);
        maxParticulas = maximoParticulas;
        audioInicio = audioCriacao;
        audioFim = audioEncerramento;
        hpParticulas = 1;
    }

    ~CPIGGeradorParticulas(){
        for (int i=0;i<parts.size();i++)
            delete parts[i];
        delete modelo;
    }

    int CriaParticula(int fadingOut=0,int minX=-50,int minY=-50,int maxX=PIG_LARG_TELA+50,int maxY=PIG_ALT_TELA+50,float maxTempo=9999999.9){
        if (parts.size()>=maxParticulas) return -1;

        PIGParticula part = new CPIGParticula(modelo,1,NULL,1,modelo->GetIdJanela());

        part->DefineLimites({minX,minY,maxX,maxY},3);
        part->IniciaAutomacao();
        parts.push_back(part);

        if (audioInicio>=0)
            CPIGGerenciadorAudios::Play(audioInicio);
        //printf("Gerei5\n");
        return parts.size();
    }

    void MoveParticulas(){
        int i=0;
        while (i<parts.size()){
            parts[i]->TrataAutomacao();
            //printf("viva %d %d\n",i,parts[i]->viva);
            if (!parts[i]->viva){
                delete parts[i];
                parts[i] = NULL;
                if (audioFim>=0)
                    CPIGGerenciadorAudios::Play(audioFim);
                //printf("vai deletar\n");
                parts.erase(parts.begin()+i);
                //printf("deletou %d %d size %d\n",id,i,parts.size());
            }else i++;
        }
    }

    inline void Move(int nx,int ny){
        modelo->Move(nx,ny);
    }

    inline void Desloca(int dx,int dy){
        modelo->Desloca(dx,dy);
    }

    inline void SetAngulo(double angulo){
        modelo->SetAngulo(angulo);
    }

    inline void SetDimensoes(int altura,int largura){
        modelo->SetDimensoes(altura,largura);
    }

    inline void MudaHP(int novoValor){
        hpParticulas = novoValor;
    }

    inline void SetColoracao(PIG_Cor cor){
        modelo->SetColoracao(cor);
    }

    inline void SetOpacidade(int opacidade){
        modelo->SetOpacidade(opacidade);
    }

    void Desenha(){
        for (int i=0;i<parts.size();i++)
            parts[i]->Desenha();
    }

    inline void SetPivo(int pivoX,int pivoY){
        modelo->SetPivo(pivoX,pivoY);
    }

    inline void SetPivo(float pivoX,float pivoY){
        modelo->SetPivo(pivoX,pivoY);
    }

    inline void LimpaTransicoes(){
        modelo->LimpaTransicoes();
    }

    inline void InsereTransicao(double tempo, PIG_EstadoTransicao estado){
        modelo->InsereTransicao(new CPIGTransicao(tempo,estado));
    }

    inline void DefineTipoTransicao(PIG_TipoTransicao valor){
        modelo->DefineTipoTransicao(valor);
    }

    bool Colisao(PIGObjeto outro){
        bool resp = false;
        int i=0;
        while (!resp && i<parts.size()){
            resp |= parts[i]->Colisao(outro);
            i++;
        }
        return resp;
    }

    bool Colisao(){
        bool resp = false;
        int i=0;
        while (!resp && i<parts.size()-1){
            int j=i+1;
            while (!resp&&j<parts.size()){
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
