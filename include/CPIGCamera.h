#ifndef _CPIGCAMERA_
#define _CPIGCAMERA_

#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/intersect.hpp>

typedef enum{PIG_CAMERA2D_FIXA,PIG_CAMERA2D_MOVEL,PIG_CAMERA3D} PIG_TipoCamera;

class CPIGCamera{

private:

PIG_TipoCamera tipo;
double afastamento;
float px,py,pz;
float raioX,raioY,raioZ;
int altJanela,largJanela;

public:

CPIGCamera(int altura,int largura){
    altJanela = altura;
    largJanela = largura;
    px = py = pz = 0;
    afastamento = 1.f;
    //printf("camera \n");
    //SetTipoCamera(PIG_CAMERA2D_FIXA);
    //printf("camera setada\n");
}

SDL_Point GetXY(){
    return {(int)px,(int)py};
}

void Move(float nx,float ny,float nz){
    Desloca(nx-px,ny-py,nz-pz);
}

void Desloca(float dx,float dy,float dz){
    px += dx;
    py += dy;
    pz += dz;
}

void CalculaRaio(int mx,int my){
    //normalised device coordinates
    glm::vec3 ndc;
    ndc.x = (2.0f*mx/PIG_LARG_TELA) -1.0f;
    ndc.y = (2.0f*my/PIG_ALT_TELA) -1.0f;
    ndc.z = 1.0f;
    //printf("NDC: %f %f %f\n",ndc.x,ndc.y,ndc.z);

    //clip space
    glm::vec4 ray_clip = glm::vec4(ndc.x,ndc.y, -1.0f, 1.0f);

    float vecProj[16];
    glGetFloatv(GL_PROJECTION_MATRIX, vecProj);

    //glm::mat4 projMatrix = glm::make_mat4(vecProj);
    glm::mat4 projMatrix = glm::make_mat4(vecProj);

    //eye space
    glm::vec4 ray_eye = glm::inverse(projMatrix) * ray_clip;
    ray_eye = glm::vec4(ray_eye.x,ray_eye.y, -1.0f, 0.0f);

    float vecModel[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, vecModel);

    glm::mat4 modelMatrix = glm::make_mat4(vecModel);


    glm::vec3 ray_wor = glm::vec3(glm::inverse(modelMatrix) * ray_eye);
    // don't forget to normalise the vector at some point
    ray_wor = glm::normalize(ray_wor);

    raioX = ray_wor.x;
    raioY = ray_wor.y;
    raioZ = ray_wor.z;

    //printf("Raio: %f %f %f\n",raioX,raioY,raioZ);
}

void SetTipoCamera(PIG_TipoCamera novoTipo){
    tipo = novoTipo;
    switch(tipo){
    case PIG_CAMERA2D_FIXA: PIGPrepara2DFixa(altJanela,largJanela,0); break;
    case PIG_CAMERA2D_MOVEL: PIGPrepara2DMovel(altJanela,largJanela,afastamento,px,py,pz); break;
    case PIG_CAMERA3D: PIGPrepara3D(altJanela,largJanela,px,py,pz); break;
    }
}

void GetXY(int mx,int my,float &x, float &y){
    int rx;
}

void GetXYZ(float &x,float &y,float &z){
    x = px;
    y = py;
    z = pz;
}

PIG_TipoCamera GetTipoCamera(){
    return tipo;
}

void Atualiza(){
    SetTipoCamera(tipo);
}

double SetAfastamento(double valor){
    return afastamento = valor;
}

inline double GetAfastamento(){
    return afastamento;
}

void ConverteCoordenadaWorldScreen(int xObj, int yObj, int &cx, int &cy){
    cx = xObj;
    cy = yObj;
    if (tipo==PIG_CAMERA2D_MOVEL){
        cx -= px;
        cy -= py;
    }
}

void ConverteCoordenadaScreenWorld(int xTela, int yTela, int &cx, int &cy){
    double deltax = (xTela-PIG_LARG_TELA/2)*afastamento;
    double deltay = (yTela-PIG_ALT_TELA/2)*afastamento;
    cx = px +PIG_LARG_TELA/2 + deltax;
    cy = py +PIG_ALT_TELA/2 + deltay;
}

};
typedef CPIGCamera *PIGCamera;
#endif // _CPIGCAMERA_
