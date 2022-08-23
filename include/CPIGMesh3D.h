#ifndef _CPIGMESH3D_
#define _CPIGMESH3D_

#include <assimp/scene.h>

#include "../src/ogldev_antigo/animator.h"


class CPIGMesh3D{

private:

unsigned int meshID;
aiMesh *mesh;
aiNode *node;
vector<aiMatrix4x4> matrizes;
static inline void Color4f(const aiColor4D *color){
	glColor4f(color->r, color->g, color->b, color->a);
}

public:

CPIGMesh3D(unsigned int numMesh, aiMesh *m, aiNode *no){
    meshID = numMesh;
    mesh = m;
    node = no;
    matrizes.resize(mesh->mNumVertices);
    AtualizaSimples();
}

~CPIGMesh3D(){
    matrizes.clear();
}

unsigned int GetIndiceMaterial(){
    return mesh->mMaterialIndex;
}

void AtualizaMat(SceneAnimator *ani){
    for (unsigned int i=0;i<matrizes.size();i++)
        matrizes[i] = aiMatrix4x4(0.0f);//,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f);

    for (unsigned int b=0;b<mesh->mNumBones;b++){
        aiBone *bone = mesh->mBones[b];
        aiMatrix4x4 inv = ani->GetBoneMatrices(node,meshID)[b];
        for (unsigned int w=0;w<bone->mNumWeights;w++){
            unsigned int vertex = bone->mWeights[w].mVertexId;
            matrizes[vertex] = matrizes[vertex]+(inv*bone->mWeights[w].mWeight);
        }
    }
}

void AtualizaSimples(){
    for (unsigned int i=0;i<matrizes.size();i++)
        matrizes[i] = aiMatrix4x4();
}

int Render(SceneAnimator *ani, PIGCor cor){
    if (ani!=NULL)
        AtualizaMat(ani);

    //cout<<"c1"<<endl;
    if(mesh->mNormals == nullptr){
        glDisable(GL_LIGHTING);
    }else{
        glEnable(GL_LIGHTING);
    }

    if(mesh->mColors[0] != nullptr){
        glEnable(GL_COLOR_MATERIAL);
    }else{
        glDisable(GL_COLOR_MATERIAL);
    }



    //long t1 = clock();

//cout<<"c2"<<endl;
    for (unsigned int t = 0; t < mesh->mNumFaces; ++t) {
        const struct aiFace* face = &mesh->mFaces[t];

        glPushMatrix();

        glBegin(GL_TRIANGLES);

        for(unsigned int i = 0; i < face->mNumIndices; i++){		// go through all vertices in face
            int vertexIndex = face->mIndices[i];	// get group index for current index
            if(mesh->mColors[0] != nullptr){
                Color4f(&mesh->mColors[0][vertexIndex]);
            }else{
                glColor4ub(cor.r,cor.g,cor.b,cor.a);
            }


            if(mesh->mNormals != nullptr)
                if(mesh->HasTextureCoords(0)){		//HasTextureCoords(texture_coordinates_set)
                    glTexCoord2f(mesh->mTextureCoords[0][vertexIndex].x, 1 - mesh->mTextureCoords[0][vertexIndex].y); //mTextureCoords[channel][vertex]
                }

            aiMatrix4x4t<float> resp = matrizes[vertexIndex];

            aiVector3t<float> vert;
            vert = resp*mesh->mNormals[vertexIndex];
            glNormal3fv(&vert.x);
            vert = resp*mesh->mVertices[vertexIndex];
            glVertex3fv(&vert.x);
            total++;

        }
        glEnd();

        glPopMatrix();

    }

}


unsigned int GetQtdVertices(){
    return mesh->mNumVertices;
}

};

typedef CPIGMesh3D *PIGMesh3D;
#endif // _CPIGMESH3D_
