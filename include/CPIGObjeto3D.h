#ifndef _CPIGOBJETO3D_
#define _CPIGOBJETO3D_

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "CPIGMateriaisObjeto3D.h"
#include "CPIGMesh3D.h"

#include "../src/ogldev_antigo/animator.h"

class CPIGObjeto3D{

private:

string nomeArq;
Assimp::Importer importer;
aiScene* cena;
PIGMateriaisObjeto3D materiais;
SceneAnimator *ani = NULL;
PIGTimer timer;
PIGCor cor;

vector<PIGMesh3D> meshes;

vector<aiMatrix4x4> transf;
map<int,aiMatrix4x4> mapBone;

float px,py,pz;

bool Import3DFromFile(string pFile){
	// Check if file exists
	ifstream fin(pFile.c_str());
	if(!fin.fail()){
		fin.close();
	}else{
	    cout<<"Arquivo <"<<pFile<<"> nao pode ser aberto!"<<endl;
        return false;
	}
    //cout<<"importers ok"<<endl;
	cena = (aiScene*) importer.ReadFile(pFile, aiProcess_Triangulate | aiProcess_GenSmoothNormals  | aiProcess_CalcTangentSpace | aiProcess_SplitLargeMeshes);
    //cout<<"scene"<<endl;
	// If the import failed, report it
	if(!cena){
		cout<< importer.GetErrorString() <<endl;
		return false;
	}

	// We're done. Everything will be cleaned up by the importer destructor
	return true;
}

// All Setup For OpenGL goes here
bool InitGL(){
	//glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);		 // Enables Smooth Shading
	//glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	//glClearDepth(1.0f);				// Depth Buffer Setup
	//glEnable(GL_DEPTH_TEST);		// Enables Depth Testing
	//glDepthFunc(GL_LEQUAL);			// The Type Of Depth Test To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculation

	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);    // Uses default lighting parameters
	//glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	//glEnable(GL_NORMALIZE);

	return true;					// Initialization Went OK
}

//não está sendo utilizada
/*void IniciaBone(const struct aiNode *nd){
    aiMatrix4x4t<float> resp(0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0);
    for (int n=0; n < nd->mNumMeshes; ++n){
        //cout<<"Começando mesh: "<<n<<endl;
        const struct aiMesh* mesh = cena->mMeshes[nd->mMeshes[n]];
        for (int i=0;i<mesh->mNumVertices;i++){
            //cout<<"Começando vertice: "<<i<<endl;
            mapBone[n*100000+i] = resp;
        }
    }
    for (int k=0;k<nd->mNumChildren;k++)
        IniciaBone(nd->mChildren[k]);
}*/

//não está sendo utilizada
/*void CriaMapBone(const struct aiNode* nd){
    for (int n=0; n < nd->mNumMeshes; ++n){
        //cout<<"Começando mesh: "<<n<<endl;
        const struct aiMesh* mesh = cena->mMeshes[nd->mMeshes[n]];
        for (int b=0;b<mesh->mNumBones;b++){
            aiBone *bone = mesh->mBones[b];
            aiMatrix4x4 inv = ani->GetBoneMatrices(nd,n)[b];
            for (int w=0;w<bone->mNumWeights;w++){
                int vertex = bone->mWeights[w].mVertexId;
                float peso = bone->mWeights[w].mWeight;
                mapBone[n*100000+vertex] = mapBone[n*100000+vertex]+(inv*peso);
            }
        }
    }
    for (int k=0;k<nd->mNumChildren;k++)
        CriaMapBone(nd->mChildren[k]);
}*/

//não está sendo utilizada
void recursive_render (const struct aiNode* nd, float scale){
	unsigned int i;
	unsigned int n=0, t;
	//aiMatrix4x4 m = nd->mTransformation;

	//aiMatrix4x4 m2;
	//aiMatrix4x4::Scaling(aiVector3D(scale, scale, scale), m2);
	//m = m * m2;

	// update transform
	//if (op1%2)
    //    m.Transpose();
	glPushMatrix();
	//glLoadIdentity();
	//glMultMatrixf((float*)&m);

	// draw all meshes assigned to this node
	//cout<<nd->mName.C_Str()<<" "<<nd->mNumMeshes<<endl;
	//aiMatrix4x4 mat = ani->GetGlobalTransform(nd);

	for (; n < nd->mNumMeshes; ++n){
		const struct aiMesh* mesh = cena->mMeshes[nd->mMeshes[n]];

		//apply_material(sc->mMaterials[mesh->mMaterialIndex]);
		materiais->AplicaMaterial(mesh->mMaterialIndex);
		//transf = ani->GetBoneMatrices(nd,n);

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

		long t1 = clock();

		for (t = 0; t < mesh->mNumFaces; ++t) {
			const struct aiFace* face = &mesh->mFaces[t];
			//GLenum face_mode = GL_TRIANGLES;


			/*switch(face->mNumIndices){
				case 1: face_mode = GL_POINTS; break;
				case 2: face_mode = GL_LINES; break;
				case 3: face_mode = GL_TRIANGLES; break;
				default: face_mode = GL_POLYGON; break;
			}*/

			glPushMatrix();

			glBegin(GL_TRIANGLES);

			for(i = 0; i < face->mNumIndices; i++){		// go through all vertices in face
				int vertexIndex = face->mIndices[i];	// get group index for current index
				//if(mesh->mColors[0] != nullptr){
					//if (px==0)
					//;//Color4f(&mesh->mColors[0][vertexIndex]);
                    //else{
                        glColor4f(1.0f,0.0f,0.0f,1.0f);
                    //}
				//}

				if(mesh->mNormals != nullptr)

					if(mesh->HasTextureCoords(0)){		//HasTextureCoords(texture_coordinates_set)
						glTexCoord2f(mesh->mTextureCoords[0][vertexIndex].x, 1 - mesh->mTextureCoords[0][vertexIndex].y); //mTextureCoords[channel][vertex]
					}

                    /*aiMatrix4x4t<float> resp(0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0);
                    for (int b=0;b<mesh->mNumBones;b++){
                        aiBone *bone = mesh->mBones[b];
                        aiMatrix4x4 inv = transf[b];//.Inverse();
                        for (int w=0;w<bone->mNumWeights;w++){
                            if (bone->mWeights[w].mVertexId==vertexIndex){
                                resp = resp+(inv*bone->mWeights[w].mWeight);
                                //resp = resp+(bone->mOffsetMatrix.Inverse()*bone->mWeights[w].mWeight);
                                //resp = resp + transf[w];
                            }
                        }
                    }*/

					aiVector3t<float> vert;
					aiMatrix4x4t<float> mat = mapBone[n*100000+vertexIndex];

					/*switch(op2){
                    case 1: mat = resp; break;
                    case 2: mat = m; break;
                    case 3: mat = ani->GetLocalTransform(nd); break;
                    case 4: mat = ani->GetGlobalTransform(nd); break;

                    case 5: mat = resp*m; break;
                    case 6: mat = resp*ani->GetLocalTransform(nd); break;
                    case 7: mat = resp*ani->GetGlobalTransform(nd); break;

                    case 8: mat = m*resp; break;
                    case 9: mat = m*ani->GetLocalTransform(nd); break;
                    case 10: mat = m*ani->GetGlobalTransform(nd); break;

                    case 11: mat = ani->GetLocalTransform(nd)*m; break;
                    case 12: mat = ani->GetLocalTransform(nd)*resp; break;

                    case 13: mat = ani->GetGlobalTransform(nd)*m; break;
                    case 14: mat = ani->GetGlobalTransform(nd)*resp; break;

					case 15: mat = m*resp*ani->GetLocalTransform(nd); break;
					case 16: mat = m*ani->GetLocalTransform(nd)*resp; break;
					case 17: mat = resp*m*ani->GetLocalTransform(nd); break;
                    case 18: mat = resp*ani->GetLocalTransform(nd)*m; break;
                    case 19: mat = ani->GetLocalTransform(nd)*resp*m; break;
                    case 20: mat = ani->GetLocalTransform(nd)*m*resp; break;

                    case 21: mat = m*resp*ani->GetGlobalTransform(nd); break;
					case 22: mat = m*ani->GetGlobalTransform(nd)*resp; break;
					case 23: mat = resp*m*ani->GetGlobalTransform(nd); break;
                    case 24: mat = resp*ani->GetGlobalTransform(nd)*m; break;
                    case 25: mat = ani->GetGlobalTransform(nd)*resp*m; break;
                    case 26: mat = ani->GetGlobalTransform(nd)*m*resp; break;

                    case 27: mat = ani->GetGlobalTransform(nd)*ani->GetLocalTransform(nd); break;
                    case 28: mat = ani->GetLocalTransform(nd)*ani->GetGlobalTransform(nd); break;

					case 29: mat = ani->GetGlobalTransform(nd)*ani->GetLocalTransform(nd)*resp; break;
                    case 30: mat = ani->GetLocalTransform(nd)*ani->GetGlobalTransform(nd)*resp; break;

					case 31: mat = ani->GetGlobalTransform(nd)*resp*ani->GetLocalTransform(nd); break;
                    case 32: mat = ani->GetLocalTransform(nd)*resp*ani->GetGlobalTransform(nd); break;

					case 33: mat = resp*ani->GetGlobalTransform(nd)*ani->GetLocalTransform(nd); break;
                    case 34: mat = resp*ani->GetLocalTransform(nd)*ani->GetGlobalTransform(nd); break;


					case 35: mat = ani->GetGlobalTransform(nd)*ani->GetLocalTransform(nd)*m; break;
                    case 36: mat = ani->GetLocalTransform(nd)*ani->GetGlobalTransform(nd)*m; break;

					case 37: mat = ani->GetGlobalTransform(nd)*m*ani->GetLocalTransform(nd); break;
                    case 38: mat = ani->GetLocalTransform(nd)*m*ani->GetGlobalTransform(nd); break;

                    case 39: mat = m*ani->GetGlobalTransform(nd)*ani->GetLocalTransform(nd); break;
                    case 40: mat = m*ani->GetLocalTransform(nd)*ani->GetGlobalTransform(nd); break;


					}
*/
					//if (op1>2)
                    //    mat.Transpose();

					vert = mat*mesh->mNormals[vertexIndex];
					glNormal3fv(&vert.x);
					vert = mat*mesh->mVertices[vertexIndex];
					glVertex3fv(&vert.x);
					mapBone[n*100000+vertexIndex] = aiMatrix4x4(0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0);

					total++;
					//glNormal3fv(&mesh->mNormals[vertexIndex].x);
					//glVertex3fv(&mesh->mVertices[vertexIndex].x);
					/*}else{
					glNormal3fv(&mesh->mNormals[vertexIndex].x);
					glVertex3fv(&mesh->mVertices[vertexIndex].x);
					}*/
			}
			glEnd();


            glPopMatrix();

		}

		cout<<"Tempo mesh: "<<(clock()-t1)/1000.0f<<endl;
	}

	// draw all children
	for (n = 0; n < nd->mNumChildren; ++n){
		recursive_render(nd->mChildren[n], scale);
	}

}

void RenderMeshes (aiNode *node){
	glPushMatrix();

	for (unsigned int n=0; n < meshes.size(); n++){
        PIGMesh3D mesh = meshes[n];
		materiais->AplicaMaterial(mesh->GetIndiceMaterial());
		mesh->Render(ani,cor);
	}

	glPopMatrix();
}

void CriaMeshes(aiNode *node){
    for (unsigned int n=0;n<node->mNumMeshes;n++){
        meshes.push_back(new CPIGMesh3D(n,cena->mMeshes[node->mMeshes[n]],node));
    }
    for (unsigned int n = 0; n < node->mNumChildren; ++n){
		CriaMeshes(node->mChildren[n]);
	}
}


public:


CPIGObjeto3D(string nomeArquivo){
    nomeArq = nomeArquivo;
    bool aux = Import3DFromFile(nomeArq);
    materiais = new CPIGMateriaisObjeto3D(cena,nomeArq);
    aux = InitGL();
    if (cena->HasAnimations())
        ani = new SceneAnimator(cena,0);
    px = py = pz = 0.0f;
    CriaMeshes(cena->mRootNode);
    timer = new CPIGTimer(false);
    cor = BRANCO;
    cout<<"PIGObjeto do arquivo "<<nomeArquivo<<" criado com "<<GetQtdVertices()<<" vertices"<<endl;
}

~CPIGObjeto3D(){
    if (ani!=NULL) delete ani;
    delete timer;
    delete materiais;
    for (unsigned int n=0;n<meshes.size();n++)
        delete meshes[n];
    meshes.clear();
}

void SetCor(PIGCor novaCor){
    cor = novaCor;
}

int Render(){
    //return 1;
    glEnable(GL_TEXTURE);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);    /* Uses default lighting parameters */

	glEnable(GL_BLEND);

	//GLfloat dif[4] = {1.0f,1.0f,0.0f,1.0f};
	//glLightfv(GL_LIGHT1, GL_AMBIENT, dif);
	//glLightfv(GL_LIGHT1, GL_DIFFUSE, dif);
	//glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
	//glEnable(GL_LIGHT1);

    //glEnable(GL_DEPTH_TEST);

	//glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_NORMALIZE);

	//cout<<"ok1"<<endl;
	if (ani)
	ani->Calculate(timer->GetTempoDecorrido());

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(px,py,pz);
    //recursive_render(g_scene,g_scene->mRootNode,1);
    RenderMeshes(cena->mRootNode);
    //cout <<"total verts: "<<total<<endl;
    total=0;
    glPopMatrix();
    return 1;
}

void Desloca(float dx, float dy, float dz){
    px += dx;
    py += dy;
    pz += dz;
}

void Move(float nx, float ny, float nz){
    Desloca(nx-px,ny-py,nz-pz);
}

unsigned int GetQtdVertices(){
    unsigned int resp=0;
    for (int i=0;i<meshes.size();i++)
        resp += meshes[i]->GetQtdVertices();
    return resp;
}

};

typedef CPIGObjeto3D *PIGObjeto3D;

#endif _CPIGOBJETO3D_
