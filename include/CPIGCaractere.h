#ifndef _CPIGCARACTERE_
#define _CPIGCARACTERE_

class CPIGCaractere{

private:

int alturaExtra;
int larguraLetra;
GLuint texturas;
int tamFonte;
SDL_Surface *surf;

public:

    CPIGCaractere(TTF_Font *font,int tamanhoFonte, Uint16 letra, PIG_Cor corFonte, int nivelOutline, PIG_Cor corOutline, SDL_Surface *fundo){
        tamFonte = tamanhoFonte;

        surf = TTF_RenderGlyph_Blended(font,letra,corFonte);//superficie gerada com a forna da letra simples

        if (fundo){
            SDL_BlitScaled(fundo,NULL,surf,NULL);
        }

        larguraLetra = surf->w;//largura da letra com o estilo específico
        alturaExtra = surf->h-tamFonte;//qtd de pixels a mais na altura, para letras maiúsculas acentudadas como Á, Ó, É...

        if (nivelOutline>0){//faz o outline da letra, se houver
            TTF_SetFontOutline(font,nivelOutline);
            SDL_Surface *out = TTF_RenderGlyph_Blended(font,letra,corOutline);
            larguraLetra = out->w;//largura da letra com o estilo específico
            alturaExtra = out->h-tamFonte;//qtd de pixels a mais na altura, para letras maiúsculas acentudadas como Á, Ó, É...
            SDL_BlitSurface(out,NULL,surf,NULL);
            SDL_FreeSurface(out);
            TTF_SetFontOutline(font,0);
        }
        texturas = PIGCriaTexturaSurface(surf,false);
    }

    ~CPIGCaractere(){
        SDL_FreeSurface(surf);
        glDeleteTextures(1,&texturas);
    }

    int GetAltura(){
        return alturaExtra;
    }

    int GetLargura(){
        return larguraLetra;
    }

    void Desenha(int x, int y, PIG_Cor corFonte, float ang, PIGPonto2D pivoAbs,bool blend){
        glPushMatrix();

        glTranslatef(x+pivoAbs.x,y+pivoAbs.y,0);

        glRotatef(ang,0.0f,0,1.0f);

        glTranslatef(-pivoAbs.x,-pivoAbs.y,0); //esse é ponto pivo (-100,40) em relação ao ponto referência do quad

        glEnable(GL_TEXTURE_2D);
        if (blend) glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_COLOR_MATERIAL);

        glBindTexture(GL_TEXTURE_2D,texturas);
        glColor4ub(corFonte.r,corFonte.g,corFonte.b,corFonte.a);
        glBegin(GL_QUADS);
            glTexCoord2f(0,1);glVertex2f(0,0);
            glTexCoord2f(1,1);glVertex2f(0+larguraLetra,0);
            glTexCoord2f(1,0);glVertex2f(0+larguraLetra,0+tamFonte+alturaExtra);
            glTexCoord2f(0,0);glVertex2f(0,0+tamFonte+alturaExtra);
        glEnd();
        //if (blend) glDisable(GL_BLEND);
        glBindTexture(GL_TEXTURE_2D,0);
        glDisable(GL_TEXTURE_2D);

        glPopMatrix();

        //printf("%d\n",texturas);
    }

    void SubstituiGlyph(SDL_Surface *surfNova,SDL_Rect origemImagem,int alt, int larg){
        SDL_FreeSurface(surf);
        glDeleteTextures(1,&texturas);

        SDL_Surface *aux = SDL_CreateRGBSurfaceWithFormat(0, larg, alt, 32, SDL_PIXELFORMAT_RGBA32);
        SDL_BlitScaled(surfNova,&origemImagem,aux,NULL);
        surf = aux;

        larguraLetra = larg;
        texturas = PIGCriaTexturaSurface(surf);
    }
};

typedef CPIGCaractere *PIGCaractere;

#endif //_CPIGCARACTERE_
