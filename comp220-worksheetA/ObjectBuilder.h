/**
ObjectBuilder

Creates new GameObjects from a list of arguments. 
This class also loads all meshes and textures that can be used in the game.
*/

#pragma once
#include <map>

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
	GameObject* MakeObject(Shader* shader, std::string meshName, std::string diffuseTextureName,
						   Material material, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f));

	/**
	Creates a new GameObject with a specular texture.
	*/
	GameObject* MakeObject(Shader* shader, std::string meshName, std::string diffuseTextureName, std::string specularTextureName,
						   Material material, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f));
	

	/*----------------------
	Getters and Setters
	----------------------*/

private:	
	//Maps of loaded meshes and textures.
	std::map<std::string, MeshCollection*> meshes;
	std::map<std::string, GLuint> textures;
	
	//The current mesh and texture being loaded.
	MeshCollection* currentMesh;
	GLuint currentTexture;
};

