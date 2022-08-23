#ifndef _CPIGMATERIAISMOBJETO3D_
#define _CPIGMATERIAISMOBJETO3D_

#include <assimp/scene.h>

#define STB_IMAGE_IMPLEMENTATION
#include "assimp/stb_image.h"

class CPIGMateriaisObjeto3D{

private:

map<string, GLuint> textureIdMap;	// map image filenames to textureIds
GLuint*	textureIds;
aiScene *cena;
string nomeArq;

static inline void set_float4(float f[4], float a, float b, float c, float d){
	f[0] = a;
	f[1] = b;
	f[2] = c;
	f[3] = d;
}

static inline void color4_to_float4(const aiColor4D *c, float f[4]){
	f[0] = c->r;
	f[1] = c->g;
	f[2] = c->b;
	f[3] = c->a;
}

void freeTextureIds(){
	//cout<<"limpar"<<endl;
	textureIdMap.clear(); //no need to delete pointers in it manually here. (Pointers point to textureIds deleted in next step)
    //cout<<"limpei"<<endl;
	if (textureIds){
		delete[] textureIds;
		textureIds = nullptr;
	}
}

public:

CPIGMateriaisObjeto3D(aiScene *scene, string nomeArquivo){
    cena = scene;
    nomeArq = nomeArquivo;
    textureIds = NULL;
    LoadGLTextures();
}

~CPIGMateriaisObjeto3D(){
    freeTextureIds();
}

bool LoadGLTextures(){
	freeTextureIds();
    if (cena->HasTextures()) return 1;
        //abortGLInit("Support for meshes with embedded textures is not implemented");

	/* getTexture Filenames and Numb of Textures */
	for (unsigned int m=0; m<cena->mNumMaterials; m++){
		int texIndex = 0;
		aiReturn texFound = AI_SUCCESS;

		aiString path;	// filename

		while (texFound == AI_SUCCESS){
			texFound = cena->mMaterials[m]->GetTexture(aiTextureType_DIFFUSE, texIndex, &path);
			textureIdMap[path.data] = 0; //fill map with textures, pointers still NULL yet
			texIndex++;
		}
	}

	const size_t numTextures = textureIdMap.size();

	/* create and fill array with GL texture ids */
	textureIds = new GLuint[numTextures];
	glGenTextures(static_cast<GLsizei>(numTextures), textureIds); /* Texture name generation */

	/* get iterator */
	map<string, GLuint>::iterator itr = textureIdMap.begin();

	string basepath = PIGCaminhoBaseDiretorio(nomeArq);
	for (size_t i=0; i<numTextures; i++){

		//save IL image ID
		string filename = (*itr).first;  // get filename
		(*itr).second =  textureIds[i];	  // save texture id for filename in map
		itr++;								  // next texture

		//ilBindImage(imageIds[i]); /* Binding of DevIL image name */
		string fileloc = basepath + filename;	/* Loading of image */
		//success = ilLoadImage(fileloc.c_str());
        int x, y, n;
        unsigned char *data = stbi_load(fileloc.c_str(), &x, &y, &n, STBI_rgb_alpha);

		if (nullptr != data ){
            // Convert every colour component into unsigned byte.If your image contains
            // alpha channel you can replace IL_RGB with IL_RGBA
            //success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);

            // Binding of texture name
            glBindTexture(GL_TEXTURE_2D, textureIds[i]);
			// redefine standard texture values
            // We will use linear interpolation for magnification filter
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
            // We will use linear interpolation for minifying filter
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
            // Texture specification
            glTexImage2D(GL_TEXTURE_2D, 0, n, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);// Texture specification.

            // we also want to be able to deal with odd texture dimensions
            glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
            glPixelStorei( GL_UNPACK_ROW_LENGTH, 0 );
            glPixelStorei( GL_UNPACK_SKIP_PIXELS, 0 );
            glPixelStorei( GL_UNPACK_SKIP_ROWS, 0 );
            stbi_image_free(data);
        }
	}

	return true;
}

void AplicaMaterial(int indice){
	float c[4];

	const aiMaterial *mtl = cena->mMaterials[indice];

	GLenum fill_mode;
	int ret1, ret2;
	aiColor4D diffuse;
	aiColor4D specular;
	aiColor4D ambient;
	aiColor4D emission;
	ai_real shininess, strength;
	int two_sided;
	int wireframe;
	unsigned int max;	// changed: to unsigned

	int texIndex = 0;
	aiString texPath;	//contains filename of texture

	if(AI_SUCCESS == mtl->GetTexture(aiTextureType_DIFFUSE, texIndex, &texPath))
	{
		//bind texture
		unsigned int texId = textureIdMap[texPath.data];
		glBindTexture(GL_TEXTURE_2D, texId);
	}

	set_float4(c, 0.8f, 0.8f, 0.8f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
		color4_to_float4(&diffuse, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, c);

	set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_SPECULAR, &specular))
		color4_to_float4(&specular, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);

	set_float4(c, 0.2f, 0.2f, 0.2f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_AMBIENT, &ambient))
		color4_to_float4(&ambient, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, c);

	set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_EMISSIVE, &emission))
		color4_to_float4(&emission, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, c);

	max = 1;
	ret1 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS, &shininess, &max);
	max = 1;
	ret2 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS_STRENGTH, &strength, &max);
	if((ret1 == AI_SUCCESS) && (ret2 == AI_SUCCESS))
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess * strength);
	else {
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0f);
		set_float4(c, 0.0f, 0.0f, 0.0f, 0.0f);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);
	}

	max = 1;
	if(AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_ENABLE_WIREFRAME, &wireframe, &max))
		fill_mode = wireframe ? GL_LINE : GL_FILL;
	else fill_mode = GL_FILL;
	glPolygonMode(GL_FRONT_AND_BACK, fill_mode);

	max = 1;
	if((AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_TWOSIDED, &two_sided, &max)) && two_sided)
		glEnable(GL_CULL_FACE);
	else glDisable(GL_CULL_FACE);
}

};

typedef CPIGMateriaisObjeto3D *PIGMateriaisObjeto3D;

#endif //_CPIGMATERIAISOBJETO3D_
