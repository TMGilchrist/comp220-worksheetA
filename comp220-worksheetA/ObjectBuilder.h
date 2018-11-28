#pragma once
#include "GameObject.h"
#include "MaterialPresets.h"
#include "Model.h"

class ObjectBuilder
{
public:
	ObjectBuilder();
	~ObjectBuilder();

	void Init();

	/*GameObject* MakeObject(const char * vertexShader, const char * fragmentShader, MeshCollection* mesh, GLuint diffuseTexture,
							Material material, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f));*/

	GameObject* MakeObject(const char * vertexShader, const char * fragmentShader, MeshCollection* mesh, GLuint diffuseTexture,
						   Material material, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f));

	GameObject* MakeObject(const char * vertexShader, const char * fragmentShader, MeshCollection* mesh, GLuint diffuseTexture, GLuint specularTexture,
							Material material, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f));

	std::vector<MeshCollection*> getMeshes()
	{
		return meshes;
	}

	std::vector<GLuint> getDiffuseTextures()
	{
		return diffuseTextures;
	}

	std::vector<GLuint> getSpecularTextures()
	{
		return specularTextures;
	}

private:
	MaterialPresets materialPresets;

	//Vector of meshes
	std::vector<MeshCollection*> meshes;

	//Vectors for textures
	std::vector<GLuint> diffuseTextures;
	std::vector<GLuint> specularTextures;

	//Diffuse textures
	GLuint tankTextureID;
	GLuint checkerTextureID;
	GLuint RockTextureID;

	//Specular textures
	GLuint spotLightTextureID;

	//Meshes
	MeshCollection* tankMesh;
	MeshCollection* teaPotMesh;
	MeshCollection* towerMesh;

	MeshCollection* terrainMesh;

	MeshCollection* cubeMesh;
	MeshCollection* sphereMesh;
};

