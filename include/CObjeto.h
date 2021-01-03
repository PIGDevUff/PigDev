typedef enum { PIG_OOBB, PIG_POLIGONO, PIG_CIRCULAR } PIG_ModoColisao;

class CObjeto : public CPigSprite {

protected:
    std::map<int, int> valoresIntInt;
    std::map<std::string, int> valoresStringInt;
    std::map<int, float> valoresIntFloat;
    std::map<std::string, float> valoresStringFloat;
    std::map<int, std::string> valoresIntString;
    std::map<std::string, std::string> valoresStringString;
    SDL_Point bb[4];
    int raio;
    PIG_ModoColisao modo;

    std::vector<SDL_Point> vertices;
    std::vector<SDL_Point> verticesOriginais;
    bool bbAlterado = true;

    void DesenhaBB() {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);//retângulo verde para o OOBB (com ângulo)
        SDL_RenderDrawLine(renderer, bb[0].x, altJanela - bb[0].y, bb[1].x, altJanela - bb[1].y);
        SDL_RenderDrawLine(renderer, bb[1].x, altJanela - bb[1].y, bb[2].x, altJanela - bb[2].y);
        SDL_RenderDrawLine(renderer, bb[2].x, altJanela - bb[2].y, bb[3].x, altJanela - bb[3].y);
        SDL_RenderDrawLine(renderer, bb[3].x, altJanela - bb[3].y, bb[0].x, altJanela - bb[0].y);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &dest);//retângulo vermelhor para o AABB (sem ângulo)
    }

    void DesenhaPoligono(PIG_Cor cor) {
        int i = 0;

        if (vertices.empty()) return;

        do {
            SDL_Rect rect;
            rect.x = vertices[i].x;
            rect.y = altJanela - (vertices[i].y + 10);
            rect.h = 10;
            rect.w = 10;

            SDL_SetRenderDrawColor(renderer, cor.r, cor.g, cor.b, 255);
            SDL_RenderDrawLine(
                renderer, vertices[i].x, altJanela - vertices[i].y,
                vertices[(i + 1) % vertices.size()].x,
                altJanela - vertices[(i + 1) % vertices.size()].y);
            SDL_RenderFillRect(renderer, &rect);

            i = (i + 1) % vertices.size();
        } while (i != 0);
    }

    void DesenhaCircular(PIG_Cor cor) {

        SDL_SetRenderDrawColor(renderer, cor.r, cor.g, cor.b, 255);

        SDL_RenderDrawLine(
            renderer,
            x + pivoRelativo.x - raio, altJanela - (y + pivoRelativo.y),
            x + pivoRelativo.x, altJanela - (y + pivoRelativo.y + raio));
        SDL_RenderDrawLine(
            renderer,
            x + pivoRelativo.x, altJanela - (y + pivoRelativo.y + raio),
            x + pivoRelativo.x + raio, altJanela - (y + pivoRelativo.y));
        SDL_RenderDrawLine(
            renderer,
            x + pivoRelativo.x + raio, altJanela - (y + pivoRelativo.y),
            x + pivoRelativo.x, altJanela - (y + pivoRelativo.y - raio));
        SDL_RenderDrawLine(
            renderer,
            x + pivoRelativo.x, altJanela - (y + pivoRelativo.y - raio),
            x + pivoRelativo.x - raio, altJanela - (y + pivoRelativo.y));

    }

    void AtualizaBB() {
        SDL_Point pivoAbs;

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
        pivoAbs.x = pivoRelativo.x + x;
        pivoAbs.y = -pivoRelativo.y + y + alt; //inverte o eixo Y, pois o pivoRel considera o eixo Y aumentando para baixo
        float angRad = -angulo * M_PI / 180.0;
        float seno = sin(angRad);
        float cosseno = cos(angRad);

        //matriz de rota��o
        // ( cos(ang) sin(ang))   (Vx)   (Rx)
        // (-sin(ang) cos(ang)) * (Vy) = (Ry)

        //vetor (Rx,Ry) � a resposta do vetor (Vx,Vy) rotacionado em ang

        bb[0].x = (x - pivoAbs.x) * cosseno + (y - pivoAbs.y) * seno + pivoAbs.x;
        bb[0].y = (y - pivoAbs.y) * cosseno - (x - pivoAbs.x) * seno + pivoAbs.y;

        bb[1].x = (x + larg - pivoAbs.x) * cosseno + (y - pivoAbs.y) * seno + pivoAbs.x;
        bb[1].y = (y - pivoAbs.y) * cosseno - (x + larg - pivoAbs.x) * seno + pivoAbs.y;

        bb[2].x = (x + larg - pivoAbs.x) * cosseno + (y + alt - pivoAbs.y) * seno + pivoAbs.x;
        bb[2].y = (y + alt - pivoAbs.y) * cosseno - (x + larg - pivoAbs.x) * seno + pivoAbs.y;

        bb[3].x = (x - pivoAbs.x) * cosseno + (y + alt - pivoAbs.y) * seno + pivoAbs.x;
        bb[3].y = (y + alt - pivoAbs.y) * cosseno - (x - pivoAbs.x) * seno + pivoAbs.y;
    }

    void AtualizaVertices() {
        double _angulo = M_PI * angulo / 180.0;

        SDL_Point pivo = {pivoRelativo.x + x, -pivoRelativo.y + y + alt};

        for (int i = 0; i < vertices.size(); i++) {
            vertices[i] = {verticesOriginais[i].x + x, verticesOriginais[i].y + y};

            int deltaX = vertices[i].x - pivo.x;
            int deltaY = vertices[i].y - pivo.y;

            vertices[i].x =
                (cos(_angulo) * deltaX) - (sin(_angulo) * deltaY) + pivo.x;
            vertices[i].y =
                (sin(_angulo) * deltaX) + (cos(_angulo) * deltaY) + pivo.y;
        }
    }


public:

    CObjeto(std::string nomeArquivo, PIG_Cor *corFundo = NULL, int retiraFundo = 1, int janela = 0)
    : CPigSprite(nomeArquivo, retiraFundo, corFundo, janela){
        //ExtraiPixels();
    }

    CObjeto(OffscreenRenderer offRender, PIG_Cor *corFundo = NULL, int retiraFundo = 1, int janela = 0)
    : CPigSprite(offRender, retiraFundo, corFundo, janela){
        //ExtraiPixels();
    }

    CObjeto(CObjeto *objBase, PIG_Cor *corFundo = NULL, int retiraFundo = 1, int janela = 0)
    : CPigSprite(objBase, retiraFundo, corFundo, janela){
        //ExtraiPixels();
        SetDimensoes(objBase->alt, objBase->larg);
    }

    ~CObjeto(){
    }

    void SetValoresInt(int chave, int valor){
        valoresIntInt[chave] = valor;
    }

    void SetValoresInt(std::string chave, int valor){
        valoresStringInt[chave] = valor;
    }

    void SetValoresFloat(int chave, float valor){
        valoresIntFloat[chave] = valor;
    }

    void SetValoresFloat(std::string chave, float valor){
        valoresStringFloat[chave] = valor;
    }

    void SetValoresString(int chave, std::string valor){
        valoresIntString[chave] = valor;
    }

    void SetValoresString(std::string chave, std::string valor){
        valoresStringString[chave] = valor;
    }

    void SetVertices(std::vector<SDL_Point> vertices) {
        this->vertices = vertices;
        this->verticesOriginais = vertices;
    }

    void SetAngulo(float a) override{
        angulo = a;
        bbAlterado = true;
    }

    void SetRaioColisaoCircular(int raio) {
        this->raio = raio;
    }

    void SetModoColisao(PIG_ModoColisao modo) {
        this->modo = modo;
    }

    bool GetValoresInt(int chave, int &valor){
        std::map<int, int>::iterator it;
        it = valoresIntInt.find(chave);
        if (it == valoresIntInt.end())
            return false;
        valor = it->second;
        return true;
    }

    bool GetValoresInt(std::string chave, int &valor){
        std::map<std::string, int>::iterator it;
        it = valoresStringInt.find(chave);
        if (it == valoresStringInt.end())
            return false;
        valor = it->second;
        return true;
    }

    bool GetValoresFloat(int chave, float &valor){
        std::map<int, float>::iterator it;
        it = valoresIntFloat.find(chave);
        if (it == valoresIntFloat.end())
            return false;
        valor = it->second;
        return true;
    }

    bool GetValoresFloat(std::string chave, float &valor){
        std::map<std::string, float>::iterator it;
        it = valoresStringFloat.find(chave);
        if (it == valoresStringFloat.end())
            return false;
        valor = it->second;
        return true;
    }

    bool GetValoresString(int chave, std::string &valor){
        std::map<int, std::string>::iterator it;
        it = valoresIntString.find(chave);
        if (it == valoresIntString.end())
            return false;
        valor = it->second;
        return true;
    }

    bool GetValoresString(std::string chave, std::string &valor){
        std::map<std::string, std::string>::iterator it;
        it = valoresStringString.find(chave);
        if (it == valoresStringString.end())
            return false;
        valor = it->second;
        return true;
    }

    SDL_Point GetBB(int i) {
        return bb[i];
    }

    std::vector<SDL_Point> GetVertices() {
        return vertices;
    }

    int GetRaio() {
        return raio;
    }

    PIG_ModoColisao GetModoColisao() {
        return modo;
    }

    void Move(int nx, int ny) override {
        SDL_Point pivo = {x, y};

        x = nx;
        y = ny;
        dest.x = x;
        dest.y = altJanela - alt - y;

        bbAlterado = true;
    }

    int Desenha(OffscreenRenderer offRender = NULL) override{
        if (offRender == NULL){
            //SDL_Rect enquadrado = dest;
            //enquadrado.x -= CGerenciadorJanelas::GetJanela(idJanela)->GetCamera()->GetX();
            //enquadrado.y += CGerenciadorJanelas::GetJanela(idJanela)->GetCamera()->GetY();
            //SDL_RenderCopyEx(renderer, text, &frame, &enquadrado, -angulo, &pivoRelativo, flip);
            CPigSprite::Desenha();
            switch(9999) {//modo
                case PIG_OOBB:
                    DesenhaBB();
                    break;
                case PIG_POLIGONO:
                    DesenhaPoligono({0, 0, 255, 255});
                    break;
                case PIG_CIRCULAR:
                    DesenhaCircular({0, 0, 255, 255});
                    break;
            }

        }else{
            SDL_Texture *textAux = SDL_CreateTextureFromSurface(offRender->GetRenderer(), bitmap);
            SDL_Rect rectAux = dest;
            rectAux.y = offRender->GetAltura() - alt - y;
            SDL_RenderCopyEx(offRender->GetRenderer(), textAux, &frames[frameAtual], &rectAux, -angulo, &pivoRelativo, flip);
            SDL_DestroyTexture(textAux);
        }
        return 0;
    }

    void Atualiza(){
        if(bbAlterado) {
            AtualizaBB();
            AtualizaVertices();
            bbAlterado = false;
        }
    }

    bool Colisao(CObjeto *outro) {
        Atualiza();
        outro->Atualiza();

        PIG_ModoColisao modoOutro = outro->GetModoColisao();

        if(modo == PIG_OOBB) {
            if(modoOutro == PIG_OOBB) {
                if(ColisaoOOBB(outro) && outro->ColisaoOOBB(this)) {
                    return ColisaoPoligono(outro->GetVertices()) || outro->ColisaoPoligono({bb[0], bb[1], bb[2], bb[3]});
                }
            } else if(modoOutro == PIG_POLIGONO) {
                if(ColisaoOOBB(outro) && outro->ColisaoOOBB(this)) {
                    return ColisaoPoligono(outro->GetVertices()) || outro->ColisaoPoligono({bb[0], bb[1], bb[2], bb[3]});
                }
            } else if(modoOutro == PIG_CIRCULAR) {
                return outro->ColisaoCirculoPoligono({bb[0], bb[1], bb[2], bb[3]});
            }
        } else if(modo == PIG_POLIGONO) {
            if(modoOutro == PIG_POLIGONO) {
                if(ColisaoOOBB(outro) && outro->ColisaoOOBB(this)) {
                    return ColisaoPoligono(outro->GetVertices()) || outro->ColisaoPoligono(this->vertices);
                }
            } else if(modoOutro == PIG_OOBB) {
                if(ColisaoOOBB(outro) && outro->ColisaoOOBB(this)) {
                    std::vector<SDL_Point> verticesOutro = {outro->GetBB(0), outro->GetBB(1), outro->GetBB(2), outro->GetBB(3)};
                    return ColisaoPoligono(verticesOutro) || outro->ColisaoPoligono(vertices);
                }
            } else if(modoOutro == PIG_CIRCULAR) {
                return outro->ColisaoCirculoPoligono(vertices);
            }
        } else if(modo == PIG_CIRCULAR) {
            if(modoOutro == PIG_CIRCULAR) {
                return ColisaoCircular(outro);
            } else if(modoOutro == PIG_POLIGONO) {
                return ColisaoCirculoPoligono(outro->GetVertices());
            } else if(modoOutro == PIG_OOBB) {
                std::vector<SDL_Point> verticesOutro = {outro->GetBB(0), outro->GetBB(1), outro->GetBB(2), outro->GetBB(3)};
                return ColisaoCirculoPoligono(verticesOutro);
            }
        }
        return false;
    }

    bool PontoDentro(SDL_Point p) {
        int i = 0;
        int quant_intersecoes = 0;

        std::vector<SDL_Point> verticesAux;

        if(this->modo == PIG_OOBB) {
            verticesAux = {bb[0], bb[1], bb[2], bb[3]};
        } else {
            verticesAux = vertices;
        }

        do {
            if (Intersecao(i, (i + 1) % verticesAux.size(), p))
                quant_intersecoes++;

            i = (i + 1) % verticesAux.size();
        } while (i != 0);

        return !(quant_intersecoes % 2 == 0);
    }

    bool ColisaoCirculoPoligono(std::vector<SDL_Point> vertices) {
        for(auto vertice : vertices) {
            if(PIGDistancia({x + pivoRelativo.x, y + pivoRelativo.y}, vertice) <= raio) {
                return true;
            }
        }

        int i = 0;

        do {
            int f = (i + 1) % vertices.size();

            float mPoligono = ((float)vertices[f].y - vertices[i].y) / ((float)vertices[f].x - vertices[i].x);

            if(mPoligono == 0 && PIGValorEntre((x + pivoRelativo.x), vertices[i].x, vertices[f].x) && PIGDistancia({(x + pivoRelativo.x), vertices[i].y}, {(x + pivoRelativo.x), (y + pivoRelativo.y)}) <= raio) {
                return true;
            } else if(std::isinf(mPoligono) && PIGValorEntre((y + pivoRelativo.y), vertices[i].y, vertices[f].y) && PIGDistancia({vertices[i].x, (y + pivoRelativo.y)}, {(x + pivoRelativo.x), (y + pivoRelativo.y)}) <= raio) {
                return true;
            } else {

                float mCirculo  = -1 / mPoligono;

                float xProxCentro = ((mPoligono * ((float)vertices[i].x)) - (mCirculo * ((float)x + pivoRelativo.x)) + ((float)y + pivoRelativo.y) - ((float)vertices[i].y))/(mPoligono - mCirculo);
                float yProxCentro = mPoligono * (xProxCentro - ((float)vertices[i].x)) + ((float)vertices[i].y);

                // SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);//retângulo verde para o OOBB (com ângulo)
                // SDL_RenderDrawLine(renderer, x + pivoRelativo.x, altJanela - (y + pivoRelativo.y), (int)xProxCentro, altJanela - (int)yProxCentro);
                // SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                // SDL_RenderDrawRect(renderer, &dest);//retângulo vermelhor para o AABB (sem ângulo)

                if(PIGDistancia({x + pivoRelativo.x, y + pivoRelativo.y}, {(int)xProxCentro, (int)yProxCentro}) <= raio && PIGValorEntre((int)xProxCentro, vertices[i].x, vertices[f].x)) return true;

                i = (i + 1) % vertices.size();
            }
        } while (i != 0);

        return false;
    }

private:

    bool Intersecao(int i, int f, SDL_Point p) {
        float m = ((float)vertices[f].y - vertices[i].y) /
                  ((float)vertices[f].x - vertices[i].x);
        int x;

        if (m == 0)
            return p.y == vertices[i].y &&
                   PIGValorEntre(p.x, vertices[i].x, vertices[f].x);

        if (p.y == vertices[i].y && p.x <= vertices[i].x) {
            int anterior = i == 0 ? vertices.size() - 1 : i - 1;
            return PIGValorEntre(p.y, vertices[anterior].y, vertices[f].y);
        }

        if (std::isinf(m))
            x = vertices[i].x;
        else
            x = (((float)p.y - vertices[i].y) / (float)m) +
                ((float)vertices[i].x);

        return (x >= p.x) && PIGValorEntre(p.y, vertices[i].y, vertices[f].y);
    }

    bool ColisaoCircular(CObjeto *outro) {
        int pivox, pivoy, posx, posy;

        outro->GetPivoRelativo(pivox, pivoy);
        outro->GetXY(posx, posy);

        return PIGDistancia({posx + pivox, posy + pivoy}, {x + pivoRelativo.x, y + pivoRelativo.y}) <= (float)(raio + outro->GetRaio());
    }

    int ColisaoOOBB(CObjeto *outro) {

        // caso em q o angulo é 0
        // caso em que o vetor que vai de bb[0] para bb[1] é paralelo ao eixo X, ou seja, nao ira existir uma "projecao" no eixo X
        // os pontos sao trocados para que seja usado o antigo bb[3] para bb[0]
        if (bb[1].y == bb[0].y) {
            for (int i = 1; i < 4; i++) {
                std::swap(bb[i].x, bb[0].x);
                std::swap(bb[i].y, bb[0].y);
            }
        }

        // projecao dos vetores no eixo X deste objeto
        double projecaoAB = PIGProjecaoX((double)(bb[1].y - bb[0].y) / (double)(bb[1].x - bb[0].x), bb[0]);
        double projecaoCD = PIGProjecaoX((double)(bb[3].y - bb[2].y) / (double)(bb[3].x - bb[2].x), bb[2]);

        //SDL_SetRenderDrawColor(renderer,255,255,255,255);
        //SDL_RenderDrawLine(renderer,(int)projecaoAB,300,(int)projecaoCD,300);

        // projecao dos pontos(com o angulo dos anteriores) no eixo X do outro objeto
        double projecao[4];
        for (int i = 0; i < 4; i++)
            projecao[i] = PIGProjecaoX((double)(bb[1].y - bb[0].y) / (double)(bb[1].x - bb[0].x), outro->GetBB(i));

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

        return (menorA < maiorB && maiorA > menorB);
    }

    bool ColisaoPoligono(std::vector<SDL_Point> vertices) {
        for (auto vertice : vertices) {
            if (PontoDentro(vertice)) return true;
        }
        return false;
    }


};

typedef CObjeto *Objeto;
