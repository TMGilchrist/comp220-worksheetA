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

	GameObject* MakeObject(const char * vertexShader, const char * fragmentShader, MeshCollection* mesh, GLuint texture, Material material, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f));


	std::vector<MeshCollection*> getMeshes()
	{
		return meshes;
	}

	std::vector<GLuint> getTextures()
	{
		return textures;
	}

private:
	MaterialPresets materialPresets;

	//Vector of meshes
	std::vector<MeshCollection*> meshes;

	//Vector of textures
	std::vector<GLuint> textures;

	//Textures
	GLuint tankTextureID;
	GLuint checkerTextureID;
	GLuint redTextureID;

	MeshCollection* tankMesh;
	MeshCollection* teaPotMesh;
};

