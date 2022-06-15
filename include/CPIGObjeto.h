#ifndef _CPIGOBJETO_
#define _CPIGOBJETO_

#include "CPIGAtributos.h"

typedef enum {PIG_COLISAO_NENHUMA, PIG_COLISAO_OOBB, PIG_COLISAO_POLIGONO, PIG_COLISAO_CIRCULAR} PIGModoColisao;

class CPIGObjeto: public CPIGSprite, public CPIGAtributos {

protected:

PIGPonto2D bb[4];
int raio;
PIGModoColisao modo;

vector<PIGPonto2D> vertices;
vector<PIGPonto2D> verticesOriginais;
bool bbAlterado;

void DesenhaBB(){
    for (int i=0;i<4;i++)
        CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaLinhaSimples(bb[i].x,bb[i].y,bb[(i+1)%4].x,bb[(i+1)%4].y,VERDE);
    CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetanguloVazado(pos.x,pos.y,alt,larg,VERMELHO);
}

void DesenhaPoligono(PIGCor cor) {
    int qtdVertices = vertices.size();
    for (int i=0;i<qtdVertices;i++){
        CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetangulo(vertices[i].x,vertices[i].y,10,10,cor);
        CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaLinhaSimples(vertices[i].x,vertices[i].y,vertices[(i + 1) % qtdVertices].x,vertices[(i + 1) % qtdVertices].y,cor);
    }
}

void DesenhaCircular(PIGCor cor) {
    SDL_SetRenderDrawColor(renderer, cor.r, cor.g, cor.b, 255);

    SDL_RenderDrawLine(
        renderer,
        pos.x + pivoAbs.x - raio, altJanela - (pos.y + pivoAbs.y),
        pos.x + pivoAbs.x, altJanela - (pos.y + pivoAbs.y + raio));
    SDL_RenderDrawLine(
        renderer,
        pos.x + pivoAbs.x, altJanela - (pos.y + pivoAbs.y + raio),
        pos.x + pivoAbs.x + raio, altJanela - (pos.y + pivoAbs.y));
    SDL_RenderDrawLine(
        renderer,
        pos.x + pivoAbs.x + raio, altJanela - (pos.y + pivoAbs.y),
        pos.x + pivoAbs.x, altJanela - (pos.y + pivoAbs.y - raio));
    SDL_RenderDrawLine(
        renderer,
        pos.x + pivoAbs.x, altJanela - (pos.y + pivoAbs.y - raio),
        pos.x + pivoAbs.x - raio, altJanela - (pos.y + pivoAbs.y));

}

void AtualizaBB() {
    PIGPonto2D pivoAux = {pivoAbs.x + pos.x, -pivoAbs.y + pos.y + alt};

    //SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
    //pivoAux.x = pivoRelativo.x + pos.x;
    //pivoAux.y = -pivoRelativo.y + pos.y + alt; //inverte o eixo Y, pois o pivoRel considera o eixo Y aumentando para baixo

    double angRad = -angulo * M_PI / 180.0;
    double seno = sin(angRad);
    double cosseno = cos(angRad);

    //matriz de rota��o
    // ( cos(ang) sin(ang))   (Vx)   (Rx)
    // (-sin(ang) cos(ang)) * (Vy) = (Ry)

    //vetor (Rx,Ry) � a resposta do vetor (Vx,Vy) rotacionado em ang

    bb[0].x = (pos.x - pivoAux.x) * cosseno + (pos.y - pivoAux.y) * seno + pivoAux.x;
    bb[0].y = (pos.y - pivoAux.y) * cosseno - (pos.x - pivoAux.x) * seno + pivoAux.y;

    bb[1].x = (pos.x + larg - pivoAux.x) * cosseno + (pos.y - pivoAux.y) * seno + pivoAux.x;
    bb[1].y = (pos.y - pivoAux.y) * cosseno - (pos.x + larg - pivoAux.x) * seno + pivoAux.y;

    bb[2].x = (pos.x + larg - pivoAux.x) * cosseno + (pos.y + alt - pivoAux.y) * seno + pivoAux.x;
    bb[2].y = (pos.y + alt - pivoAux.y) * cosseno - (pos.x + larg - pivoAux.x) * seno + pivoAux.y;

    bb[3].x = (pos.x - pivoAux.x) * cosseno + (pos.y + alt - pivoAux.y) * seno + pivoAux.x;
    bb[3].y = (pos.y + alt - pivoAux.y) * cosseno - (pos.x - pivoAux.x) * seno + pivoAux.y;

    //printf("bb %d,%d %d,%d, %d,%d %d,%d\n",bb[0].x,bb[0].y,bb[1].x,bb[1].y,bb[2].x,bb[2].y,bb[3].x,bb[3].y);
}

void AtualizaVertices() {
    double _angulo = M_PI * angulo / 180.0;

    PIGPonto2D pivo = {pivoAbs.x + pos.x, -pivoAbs.y + pos.y + alt};

    for (unsigned int i = 0; i < vertices.size(); i++) {
        vertices[i] = {verticesOriginais[i].x + pos.x, verticesOriginais[i].y + pos.y};

        int deltaX = vertices[i].x - pivo.x;
        int deltaY = vertices[i].y - pivo.y;

        vertices[i].x = (cos(_angulo) * deltaX) - (sin(_angulo) * deltaY) + pivo.x;
        vertices[i].y = (sin(_angulo) * deltaX) + (cos(_angulo) * deltaY) + pivo.y;
    }
}

void Atualiza(){
    if(bbAlterado) {
        AtualizaBB();
        AtualizaVertices();
        bbAlterado = false;
    }
}

bool ColisaoCirculoPoligono(vector<PIGPonto2D> vertices) {
    for(auto vertice : vertices) {
        if(PIGDistancia({pos.x + pivoAbs.x, pos.y + pivoAbs.y}, vertice) <= raio) {
            return true;
        }
    }

    int i = 0;

    do {
        int f = (i + 1) % vertices.size();

        float mPoligono = ((float)vertices[f].y - vertices[i].y) / ((float)vertices[f].x - vertices[i].x);

        if(mPoligono == 0 && PIGValorEntre((pos.x + pivoAbs.x), vertices[i].x, vertices[f].x) && PIGDistancia({(pos.x + pivoAbs.x), vertices[i].y}, {(pos.x + pivoAbs.x), (pos.y + pivoAbs.y)}) <= raio) {
            return true;
        } else if(std::isinf(mPoligono) && PIGValorEntre((pos.y + pivoAbs.y), vertices[i].y, vertices[f].y) && PIGDistancia({vertices[i].x, (pos.y + pivoAbs.y)}, {(pos.x + pivoAbs.x), (pos.y + pivoAbs.y)}) <= raio) {
            return true;
        } else {

            double mCirculo  = -1 / mPoligono;

            double xProxCentro = ((mPoligono * ((double)vertices[i].x)) - (mCirculo * ((double)pos.x + pivoAbs.x)) + ((double)pos.y + pivoAbs.y) - ((double)vertices[i].y))/(mPoligono - mCirculo);
            double yProxCentro = mPoligono * (xProxCentro - ((double)vertices[i].x)) + ((double)vertices[i].y);

            if(PIGDistancia({pos.x + pivoAbs.x, pos.y + pivoAbs.y}, {xProxCentro, yProxCentro}) <= raio && PIGValorEntre((int)xProxCentro, vertices[i].x, vertices[f].x)) return true;

            i = (i + 1) % vertices.size();
        }
    } while (i != 0);

    return false;
}


public:

CPIGObjeto(int idObjeto, string nomeArquivo, int retiraFundo = 1, PIGCor *corFundo = NULL, int janela = 0)
:CPIGSprite(idObjeto,nomeArquivo, retiraFundo, corFundo, janela),CPIGAtributos(){
    modo = PIG_COLISAO_OOBB;
    bbAlterado = true;
}

CPIGObjeto(int idObjeto, PIGOffscreenRenderer offRender, int retiraFundo = 1, PIGCor *corFundo = NULL, int janela = 0)
:CPIGSprite(idObjeto,offRender, retiraFundo, corFundo, janela),CPIGAtributos(){
    modo = PIG_COLISAO_OOBB;
    bbAlterado = true;
}

CPIGObjeto(int idObjeto, CPIGObjeto *objBase, int retiraFundo = 1, PIGCor *corFundo = NULL, int janela = 0)
:CPIGSprite(idObjeto,objBase, retiraFundo, corFundo, janela),CPIGAtributos(){
    SetModoColisao(objBase->modo);
    SetRaioColisaoCircular(objBase->raio);
    SetVertices(objBase->vertices);

    Move(pos.x,pos.y);
    SetAngulo(angulo);
    AtualizaBB();

    bbAlterado = true;
}

virtual ~CPIGObjeto(){}

void SetVertices(vector<PIGPonto2D> verts) {
    vertices = verts;
    verticesOriginais = verts;
}

void SetAngulo(double a) override{
    CPIGSprite::SetAngulo(a);
    bbAlterado = true;
}

void SetRaioColisaoCircular(int raio) {
    this->raio = raio;
}

void SetModoColisao(PIGModoColisao valor) {
    modo = valor;
}

PIGPonto2D GetBB(int i) {
    return bb[i];
}

vector<PIGPonto2D> GetVertices() {
    return vertices;
}

int GetRaio() {
    return raio;
}

PIGModoColisao GetModoColisao() {
    return modo;
}

virtual void Move(double nx, double ny) override {
    CPIGSprite::Move(nx,ny);
    bbAlterado = true;
}

virtual void Desloca(double dx, double dy) override {
    CPIGSprite::Desloca(dx,dy);
    bbAlterado = true;
}

int Desenha() override{
    CPIGSprite::Desenha();
    /*switch(modo) {//modo
        case PIG_COLISAO_OOBB:
            DesenhaBB();
            break;
        case PIG_COLISAO_POLIGONO:
            DesenhaPoligono({0, 0, 255, 255});
            break;
        case PIG_COLISAO_CIRCULAR:
            DesenhaCircular({0, 0, 255, 255});
            break;
    }*/
    return 0;
}

virtual bool Colisao(CPIGObjeto *outro){
    if (modo==PIG_COLISAO_NENHUMA||outro==NULL) return false;

    Atualiza();
    outro->Atualiza();

    PIGModoColisao modoOutro = outro->GetModoColisao();

    if(modo == PIG_COLISAO_OOBB) {
        if(modoOutro == PIG_COLISAO_OOBB) {
            if(ColisaoOOBB(outro) || outro->ColisaoOOBB(this)) {
                //fprintf(arqP,"%f,%f,%d,%d %f,%f,%d,%d\n",pos.x,pos.y,alt,larg,outro->pos.x,outro->pos.y,outro->alt,outro->larg);
                return true;//ColisaoPoligono(outro->GetVertices()) || outro->ColisaoPoligono({bb[0], bb[1], bb[2], bb[3]});
            }
        } else if(modoOutro == PIG_COLISAO_POLIGONO) {
            if(ColisaoOOBB(outro) && outro->ColisaoOOBB(this)) {
                return ColisaoPoligono(outro->GetVertices()) || outro->ColisaoPoligono({bb[0], bb[1], bb[2], bb[3]});
            }
        } else if(modoOutro == PIG_COLISAO_CIRCULAR) {
            return outro->ColisaoCirculoPoligono({bb[0], bb[1], bb[2], bb[3]});
        }
    } else if(modo == PIG_COLISAO_POLIGONO) {
        if(modoOutro == PIG_COLISAO_POLIGONO) {
            if(ColisaoOOBB(outro) && outro->ColisaoOOBB(this)) {
                return ColisaoPoligono(outro->GetVertices()) || outro->ColisaoPoligono(this->vertices);
            }
        } else if(modoOutro == PIG_COLISAO_OOBB) {
            if(ColisaoOOBB(outro) && outro->ColisaoOOBB(this)) {
                vector<PIGPonto2D> verticesOutro = {outro->GetBB(0), outro->GetBB(1), outro->GetBB(2), outro->GetBB(3)};
                return ColisaoPoligono(verticesOutro) || outro->ColisaoPoligono(vertices);
            }
        } else if(modoOutro == PIG_COLISAO_CIRCULAR) {
            return outro->ColisaoCirculoPoligono(vertices);
        }
    } else if(modo == PIG_COLISAO_CIRCULAR) {
        if(modoOutro == PIG_COLISAO_CIRCULAR) {
            return ColisaoCircular(outro);
        } else if(modoOutro == PIG_COLISAO_POLIGONO) {
            return ColisaoCirculoPoligono(outro->GetVertices());
        } else if(modoOutro == PIG_COLISAO_OOBB) {
            vector<PIGPonto2D> verticesOutro = {outro->GetBB(0), outro->GetBB(1), outro->GetBB(2), outro->GetBB(3)};
            return ColisaoCirculoPoligono(verticesOutro);
        }
    }
    return false;
}

bool PontoDentro(PIGPonto2D p) {
    int i = 0;
    int quant_intersecoes = 0;

    vector<PIGPonto2D> verticesAux;

    if(this->modo == PIG_COLISAO_OOBB) {
        verticesAux = {bb[0], bb[1], bb[2], bb[3]};
    } else {
        verticesAux = vertices;
    }

    do {
        if (Intersecao(i, (i + 1) % verticesAux.size(), verticesAux, p))
            quant_intersecoes++;

        i = (i + 1) % verticesAux.size();
    } while (i != 0);

    return !(quant_intersecoes % 2 == 0);
}

private:

bool Intersecao(int i, int f, vector<PIGPonto2D> v, PIGPonto2D p) {
    double m = ((double)v[f].y - v[i].y) /
              ((double)v[f].x - v[i].x);
    int x;

    if (m == 0)
        return p.y == v[i].y &&
               PIGValorEntre(p.x, v[i].x, v[f].x);

    if (p.y == v[i].y && p.x <= v[i].x) {
        int anterior = i == 0 ? v.size() - 1 : i - 1;
        return PIGValorEntre(p.y, v[anterior].y, v[f].y);
    }

    if (std::isinf(m))
        x = v[i].x;
    else
        x = (((double)p.y - v[i].y) / (double)m) +
            ((double)v[i].x);

    return (x >= p.x) && PIGValorEntre(p.y, v[i].y, v[f].y);
}

bool ColisaoCircular(CPIGObjeto *outro) {
    PIGPonto2D outroPivo = outro->GetPivo();
    PIGPonto2D outroPos = outro->GetXY();

    return PIGDistancia({outroPos.x + outroPivo.x, outroPos.y + outroPivo.y}, {pos.x + pivoAbs.x, pos.y + pivoAbs.y}) <= (float)(raio + outro->GetRaio());
}

bool ColisaoOOBB(CPIGObjeto *outro) {

    // caso em q o angulo é 0
    // caso em que o vetor que vai de bb[0] para bb[1] é paralelo ao eixo X, ou seja, nao ira existir uma "projecao" no eixo X
    // os pontos sao trocados para que seja usado o antigo bb[3] para bb[0]
    //bool swapei = false;
    //string str;
    //char cstr[100]="";
    //vector<string> vet;
    if (bb[1].y == bb[0].y) {
        for (int i = 1; i < 4; i++) {
            swap(bb[i].x, bb[0].x);
            swap(bb[i].y, bb[0].y);
            //swapei = true;
        }
    }else{
        /*sprintf(cstr,"bb== %d %d\n",bb[1].y,bb[0].y);
        vet.push_back(cstr);
        sprintf(cstr,"(%d,%d) (%d,%d) (%d,%d) (%d,%d)\n",bb[0].x,bb[0].y,bb[1].x,bb[1].y,bb[2].x,bb[2].y,bb[3].x,bb[3].y);
        vet.push_back(cstr);
        */
    }

    // projecao dos vetores no eixo X deste objeto
    double projecaoAB = PIGProjecaoX((double)(bb[1].y - bb[0].y) / (double)(bb[1].x - bb[0].x), bb[0]);//,swapei,vet);
    double projecaoCD = PIGProjecaoX((double)(bb[3].y - bb[2].y) / (double)(bb[3].x - bb[2].x), bb[2]);//,swapei,vet);

    /*if (!swapei){
        sprintf(cstr,"proj %f %f\n",projecaoAB,projecaoCD);
        vet.push_back(cstr);
    }*/

    //SDL_SetRenderDrawColor(renderer,255,255,255,255);
    //SDL_RenderDrawLine(renderer,(int)projecaoAB,300,(int)projecaoCD,300);

    // projecao dos pontos(com o angulo dos anteriores) no eixo X do outro objeto
    double projecao[4];
    for (int i = 0; i < 4; i++)
        projecao[i] = PIGProjecaoX((double)(bb[1].y - bb[0].y) / (double)(bb[1].x - bb[0].x), outro->GetBB(i));//,swapei,vet);

    /*if (!swapei){
        sprintf(cstr,"proj %f %f %f %f\n",projecao[0],projecao[1],projecao[2],projecao[3]);
        vet.push_back(cstr);
    }*/

    double menorA = (projecaoAB < projecaoCD) ? projecaoAB : projecaoCD;
    double maiorA = (projecaoAB > projecaoCD) ? projecaoAB : projecaoCD;
    double menorB = PIGMinVetor(projecao,4);
    double maiorB = PIGMaxVetor(projecao,4);

    if (!(menorA < maiorB && maiorA > menorB))
        return false;

    // projecao dos vetores no eixo Y deste objeto
    projecaoAB = PIGProjecaoY((double )(bb[2].y - bb[1].y) / (double )(bb[2].x - bb[1].x), bb[1]);
    projecaoCD = PIGProjecaoY((double )(bb[0].y - bb[3].y) / (double )(bb[0].x - bb[3].x), bb[3]);

    // projecao dos pontos(com o angulo dos anteriores) no eixo Y do outro objeto
    for (int i = 0; i < 4; i++)
        projecao[i] = PIGProjecaoY((double )(bb[2].y - bb[1].y) / (double )(bb[2].x - bb[1].x), outro->GetBB(i));

    menorA = (projecaoAB < projecaoCD) ? projecaoAB : projecaoCD;
    maiorA = (projecaoAB > projecaoCD) ? projecaoAB : projecaoCD;
    menorB = PIGMinVetor(projecao,4);
    maiorB = PIGMaxVetor(projecao,4);

    /*if (menorA < maiorB && maiorA > menorB){
        if (!swapei){
                sprintf(cstr,"swapei %d\n",swapei);
                vet.push_back(cstr);
                sprintf(cstr,"(%d,%d) (%d,%d) (%d,%d) (%d,%d)\n",bb[0].x,bb[0].y,bb[1].x,bb[1].y,bb[2].x,bb[2].y,bb[3].x,bb[3].y);
                vet.push_back(cstr);
                sprintf(cstr,"(%d,%d) (%d,%d) (%d,%d) (%d,%d)\n",outro->GetBB(0).x,outro->GetBB(0).y,outro->GetBB(1).x,outro->GetBB(1).y,outro->GetBB(2).x,outro->GetBB(2).y,outro->GetBB(3).x,outro->GetBB(3).y);
                vet.push_back(cstr);
                sprintf(cstr,"%f %f %f %f proj %f %f\n",menorA,maiorB,maiorA,menorB,projecaoAB,projecaoCD);
                vet.push_back(cstr);

                for (int f=0;f<vet.size();f++)
                    ;//printf("%s",vet[f].c_str());
                //system("pause");
        }
    }*/

    return (menorA < maiorB && maiorA > menorB);
}

bool ColisaoPoligono(vector<PIGPonto2D> vertices) {
    for (auto vertice : vertices) {
        if (PontoDentro(vertice)) return true;
    }
    return false;
}

};

typedef CPIGObjeto *PIGObjeto;
#endif // _CPIGOBJETO_
