#ifndef _CPIGOFFSCREENLAYER_
#define _CPIGOFFSCREENLAYER_

#include "CPIGPilhaCoordenada.h"

class CPIGOffscreenLayer{

private:

GLuint frameBuffer,rbo, textColorBuffer;
int alt,larg;

public:

CPIGOffscreenLayer(int altura, int largura){
    larg = largura;
    alt = altura;

    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

    glGenTextures(1, &textColorBuffer);
    glBindTexture(GL_TEXTURE_2D, textColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, larg, alt, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    // attach it to currently bound framebuffer object
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textColorBuffer, 0);


    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, larg, alt);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    // check FBO status
    //printFramebufferInfo(frameBuffer);
    //bool status = checkFramebufferStatus(frameBuffer);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

///////////////////////////////////////////////////////////////////////////////
// print out the FBO infos
///////////////////////////////////////////////////////////////////////////////
void printFramebufferInfo(GLuint fbo){
    // bind fbo
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    std::cout << "\n===== FBO STATUS =====\n";

    // print max # of colorbuffers supported by FBO
    int colorBufferCount = 0;
    glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &colorBufferCount);
    std::cout << "Max Number of Color Buffer Attachment Points: " << colorBufferCount << std::endl;

    // get max # of multi samples
    int multiSampleCount = 0;
    glGetIntegerv(GL_MAX_SAMPLES, &multiSampleCount);
    std::cout << "Max Number of Samples for MSAA: " << multiSampleCount << std::endl;

    int objectType;
    int objectId;

    // print info of the colorbuffer attachable image
    for(int i = 0; i < colorBufferCount; ++i)
    {
        glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER,
                                              GL_COLOR_ATTACHMENT0+i,
                                              GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE,
                                              &objectType);
        if(objectType != GL_NONE)
        {
            glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER,
                                                  GL_COLOR_ATTACHMENT0+i,
                                                  GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME,
                                                  &objectId);

            std::string formatName;

            std::cout << "Color Attachment " << i << ": ";
            if(objectType == GL_TEXTURE)
            {
                //std::cout << "GL_TEXTURE, " << getTextureParameters(objectId) << std::endl;
            }
            else if(objectType == GL_RENDERBUFFER)
            {
                //std::cout << "GL_RENDERBUFFER, " << getRenderbufferParameters(objectId) << std::endl;
            }
        }
    }

    // print info of the depthbuffer attachable image
    glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER,
                                          GL_DEPTH_ATTACHMENT,
                                          GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE,
                                          &objectType);
    if(objectType != GL_NONE)
    {
        glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER,
                                              GL_DEPTH_ATTACHMENT,
                                              GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME,
                                              &objectId);

        std::cout << "Depth Attachment: ";
        switch(objectType)
        {
        case GL_TEXTURE:
            //std::cout << "GL_TEXTURE, " << getTextureParameters(objectId) << std::endl;
            break;
        case GL_RENDERBUFFER:
            //std::cout << "GL_RENDERBUFFER, " << getRenderbufferParameters(objectId) << std::endl;
            break;
        }
    }

    // print info of the stencilbuffer attachable image
    glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER,
                                          GL_STENCIL_ATTACHMENT,
                                          GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE,
                                          &objectType);
    if(objectType != GL_NONE)
    {
        glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER,
                                              GL_STENCIL_ATTACHMENT,
                                              GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME,
                                              &objectId);

        std::cout << "Stencil Attachment: ";
        switch(objectType)
        {
        case GL_TEXTURE:
            //std::cout << "GL_TEXTURE, " << getTextureParameters(objectId) << std::endl;
            break;
        case GL_RENDERBUFFER:
            //std::cout << "GL_RENDERBUFFER, " << getRenderbufferParameters(objectId) << std::endl;
            break;
        }
    }

    std::cout << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

bool checkFramebufferStatus(GLuint fbo){
    // check FBO status
    glBindFramebuffer(GL_FRAMEBUFFER, fbo); // bind
    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    switch(status)
    {
    case GL_FRAMEBUFFER_COMPLETE:
        std::cout << "Framebuffer complete." << std::endl;
        return true;

    case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
        std::cout << "[ERROR] Framebuffer incomplete: Attachment is NOT complete." << std::endl;
        return false;

    case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
        std::cout << "[ERROR] Framebuffer incomplete: No image is attached to FBO." << std::endl;
        return false;
/*
    case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS:
        std::cout << "[ERROR] Framebuffer incomplete: Attached images have different dimensions." << std::endl;
        return false;

    case GL_FRAMEBUFFER_INCOMPLETE_FORMATS:
        std::cout << "[ERROR] Framebuffer incomplete: Color attached images have different internal formats." << std::endl;
        return false;
*/
    case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
        std::cout << "[ERROR] Framebuffer incomplete: Draw buffer." << std::endl;
        return false;

    case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
        std::cout << "[ERROR] Framebuffer incomplete: Read buffer." << std::endl;
        return false;

    case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
        std::cout << "[ERROR] Framebuffer incomplete: Multisample." << std::endl;
        return false;

    case GL_FRAMEBUFFER_UNSUPPORTED:
        std::cout << "[ERROR] Framebuffer incomplete: Unsupported by FBO implementation." << std::endl;
        return false;

    default:
        std::cout << "[ERROR] Framebuffer incomplete: Unknown error." << std::endl;
        return false;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);   // unbind
}

inline void Ativa(){
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    PIGPrepara2DFixa(alt,larg,1);
}

inline void Desativa(){
    glBindFramebuffer(GL_FRAMEBUFFER,0);
}

void Merge(CPIGOffscreenLayer *layerSup){
    Ativa();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,layerSup->textColorBuffer);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBegin(GL_QUADS);
        glTexCoord2f(0,1);glVertex2f(0,0);
        glTexCoord2f(1,1);glVertex2f(larg,0);
        glTexCoord2f(1,0);glVertex2f(larg,alt);
        glTexCoord2f(0,0);glVertex2f(0,alt);
    glEnd();

    glDisable(GL_BLEND);

    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,0);

    Desativa();
}

SDL_Surface *GetSurface(){
    uint8_t *data = new uint8_t[alt*larg*4];
    GetPixels(data);
    return SDL_CreateRGBSurfaceWithFormatFrom(data,larg,alt,32,larg*4,SDL_PIXELFORMAT_RGBA32);
}

void PintarArea(int px, int py, PIGCor cor, PIGCor (*userFunctionPintarArea)(int, int, int, int, PIGCor, PIGCor) ){
    if (!(px>=0&&py>=0&&px<larg&&py<alt)) return;

    SDL_Surface *surface = GetSurface();
    SDL_LockSurface(surface);

    Uint32 *pBase = (Uint32*) surface->pixels;
    pBase += (px+(alt-py-1)*larg);
    Uint32 corBase = *pBase;

    Uint32 color = SDL_MapRGBA((const SDL_PixelFormat*) &surface->format->format,cor.r,cor.g,cor.b,cor.a);
    if (color==corBase) return;

    CPilhaCoordenada *pilha = new CPilhaCoordenada();
    pilha->Empilha(px,py);
    int x,y;
    Uint32 *p;
    while (pilha->Desempilha(x,y)){
        if (x>=0&&y>=0&&x<larg&&y<alt){
            p = (Uint32*) surface->pixels;
            p += (x+(alt-y-1)*larg);

            if ( (*p)==corBase){

                if (userFunctionPintarArea){
                    PIGCor corAtual;
                    SDL_GetRGBA(corBase,(const SDL_PixelFormat*) &surface->format->format,&(corAtual.r),&(corAtual.g),&(corAtual.b),&(corAtual.a));
                    cor = userFunctionPintarArea(x,y,alt,larg,corAtual,cor);
                    color = SDL_MapRGBA((const SDL_PixelFormat*) &surface->format->format,cor.r,cor.g,cor.b,cor.a);
                }

                *p = color;     //muda efetivamente a cor
                pilha->Empilha(x+1,y+0);
                pilha->Empilha(x+0,y+1);
                pilha->Empilha(x-1,y+0);
                pilha->Empilha(x+0,y-1);
            }
        }
    }

    delete pilha;
    SDL_UnlockSurface(surface);
    Ativa();
    glDrawPixels(larg,alt,GL_RGBA,GL_UNSIGNED_BYTE,surface->pixels);
    Desativa();
    SDL_FreeSurface(surface);
}

void GetPixels(void *data){
    glBindFramebuffer(GL_FRAMEBUFFER,frameBuffer);
    glReadPixels(0,0,larg,alt,GL_RGBA,GL_UNSIGNED_BYTE,data);
    glBindFramebuffer(GL_FRAMEBUFFER,0);
}

~CPIGOffscreenLayer(){
    Desativa();
    glDeleteTextures(1,&textColorBuffer);
    glDeleteFramebuffers(1,&frameBuffer);
    glDeleteRenderbuffers(1,&rbo);
}

};

typedef CPIGOffscreenLayer *PIGOffscreenLayer;
#endif // _CPIGOFFSCREENLAYER_
