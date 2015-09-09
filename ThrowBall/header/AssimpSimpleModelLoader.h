#pragma once

#define TRUE                1
#define FALSE               0

#include <stdlib.h>

#include <gl/freeglut.h>

// assimp include files. These three are usually needed.
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <IL/il.h>

#include <string.h>
#include <map>

#define aisgl_min(x,y) (x<y?x:y)
#define aisgl_max(x,y) (y>x?y:x)

class AssimpSimpleModelLoader
{
private:
	// Global Assimp scene object
	const aiScene* scene;
	// Map image filenames to textureIds
	std::map<std::string, GLuint*> textureIdMap;
	GLuint*		textureIds;
	GLuint scene_list;
	aiVector3D scene_min, scene_max, scene_center;
	std::string basePath;
	std::string modelPath;
	std::string texturePath;
	std::string modelName;
public:
	AssimpSimpleModelLoader(std::string resourceDir,std::string modelDir,std::string textureDir,std::string modelName);
	~AssimpSimpleModelLoader();
	
	void setBasePath(std::string basePath);
	void setModelPath(std::string modelPath);
	void setTexturePath(std::string texturePath);
	void setModelName(std::string modelName);

	std::string getBasePath();
	std::string getModelPath();
	std::string getTexturePath();
	std::string getModelName();

	// Return the scene
	const aiScene* getScene();

	int loadasset(const char* path);
	void get_bounding_box (aiVector3D* min, aiVector3D* max);
	void get_bounding_box_for_node (const aiNode* nd, aiVector3D* min, aiVector3D* max, aiMatrix4x4* trafo);

	// Render Assimp Model
	void recursive_render(const aiScene *sc, const aiNode* nd);
	void apply_material(const aiMaterial *mtl);
	void color4_to_float4(const aiColor4D *c, float f[4]);
	void set_float4(float f[4], float a, float b, float c, float d);

	int LoadGLTextures(const aiScene* scene);
};