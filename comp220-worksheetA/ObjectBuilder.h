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

	@param shader : The shader to use to render the new object.
	@param meshName : The name of the mesh to use for this object.
	@param diffuseTextureName : The name of the texture to use for this object.
	@param material : The material to assign to this object.
	@param position : Optional parameter to set the position of the object.
	@param scale : Optional parameter to set the scale of the object.
	@param rotation : Optional parameter to set the rotation of the object.

	@returns object : A new GameObject.
	*/
	GameObject* MakeObject(Shader* shader, std::string meshName, std::string diffuseTextureName,
						   Material material, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f));

	/**
	Creates a new GameObject with a specular texture.

	@param shader : The shader to use to render the new object.
	@param meshName : The name of the mesh to use for this object.
	@param diffuseTextureName : The name of the texture to use for this object.
	@param specularTextureName : The name of the specular texture to use for this object.
	@param material : The material to assign to this object.
	@param position : Optional parameter to set the position of the object.
	@param scale : Optional parameter to set the scale of the object.
	@param rotation : Optional parameter to set the rotation of the object.

	@returns object : A new GameObject.
	*/
	GameObject* MakeObject(Shader* shader, std::string meshName, std::string diffuseTextureName, std::string specularTextureName,
						   Material material, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f));
	
	/**
	Creates a new pineTree1 preset object. Only shader and position data needs to be specified.

	@param shader : The shader to use to render the new object.
	@param position : Optional parameter to set the position of the object.
	@param scale : Optional parameter to set the scale of the object.
	@param rotation : Optional parameter to set the rotation of the object.

	@returns tree : A new tree GameObject.
	*/
	GameObject* MakePineTree1(Shader* shader, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f));


	/*----------------------
	Getters and Setters
	----------------------*/

private:	
	//Material presets
	MaterialPresets materials;

	//Maps of loaded meshes and textures.
	std::map<std::string, MeshCollection*> meshes;
	std::map<std::string, GLuint> textures;
	
	//The current mesh and texture being loaded.
	MeshCollection* currentMesh;
	GLuint currentTexture;
};

