/**
ObjectBuilder

Creates new GameObjects from a list of arguments. 
This class also loads all meshes and textures that can be used in the game.
*/

#pragma once
#include "GameObject.h"
#include "MaterialPresets.h"
#include "Model.h"

class ObjectBuilder
{
public:
	ObjectBuilder();
	~ObjectBuilder();

	/**
	Initalise the ObjectBuilder. This loads in all meshes and textures that will be used. Also initalises material presets.
	*/
	void Init();

	/**
	Loads in all meshes to be used and stores them in the meshes vector
	*/
	void LoadMeshes();

	/**
	Loads in all diffuse and specular textures to be used and stores them in the diffuse and specular texutres vecotrs.
	*/
	void LoadTextures();

	/**
	Creates a new GameObject without a specular texture.
	*/
	GameObject* MakeObject(const char * vertexShader, const char * fragmentShader, MeshCollection* mesh, GLuint diffuseTexture,
						   Material material, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f));

	/**
	Creates a new GameObject with a specular texture.
	*/
	GameObject* MakeObject(const char * vertexShader, const char * fragmentShader, MeshCollection* mesh, GLuint diffuseTexture, GLuint specularTexture,
						   Material material, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f));
	

	/*----------------------
	Getters and Setters
	----------------------*/

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

	GLuint StoneBrickID;
	GLuint StoneBrick2ID;

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

