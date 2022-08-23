class Luz{

private:

GLuint idLuz;

public:

Luz(GLuint identificador){
    idLuz = identificador;
}

~Luz(){

}

void DefineCor(PIGCor ambiente, PIGCor difusa, PIGCor especular){
    GLfloat ambienteV[] = {ambiente.r/255.0f,ambiente.g/255.0f,ambiente.b/255.0f,1.0};
    GLfloat difusaV[] = {difusa.r/255.0f,difusa.g/255.0f,difusa.b/255.0f,1.0};
    GLfloat especularV[] = {especular.r/255.0f,especular.g/255.0f,especular.b/255.0f,1.0};

    glLightfv(idLuz,GL_AMBIENT,ambienteV);
    glLightfv(idLuz,GL_DIFFUSE,difusaV);
    glLightfv(idLuz,GL_SPECULAR,especularV);
}

void OnOff(bool valor){
    if (valor)
        glEnable(idLuz);
    else glDisable(idLuz);
}

void Posiciona(float x,float y,float z){
    GLfloat pos[] = {x,y,-z,1.0};
    glLightfv(idLuz,GL_POSITION,pos);
}

};
