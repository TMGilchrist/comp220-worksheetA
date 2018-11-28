#pragma once
#include <glm\glm.hpp>
#include <btBulletDynamicsCommon.h>

#include "shader.h"
#include "Mesh.h"
#include "Material.h"


class GameObject
{
public:
	GameObject();



	~GameObject();

	/**
	Initalise member variables
	*/
	void Init(const char* vert, const char* fragment);

	/**
	Update function. Calculates the model matrix. Should be called whenever the object changes in some way. 
	*/
	void Update();

	/**
	Attach a meshCollection to the game object.
	*/
	void setMesh(MeshCollection* objectMesh) 
	{
		mesh = objectMesh;
	}

	/**
	Set the object's translation. Use to move the object around.
	*/
	void setTranslation(glm::vec3 Translation) 
	{
		modelTranslation = Translation;
	}

	/**
	Set the object's scale. Use to resize object. 1.0 is the default size.
	*/
	void setScale(glm::vec3 Scale) 
	{
		modelScale = Scale;
	}
	
	void setProgramID(const char* vert, const char* fragment) 
	{
		programID = LoadShaders(vert, fragment);
	}

	glm::mat4 getModelMatrix() 
	{
		return modelMatrix;
	}

	void setDiffuseTextureID(GLuint ID) 
	{
		diffuseTextureID = ID;
	}

	GLuint getDiffuseTextureID() 
	{
		return diffuseTextureID;
	}

	void setSpecularTextureID(GLuint ID)
	{
		specularTextureID = ID;
	}

	GLuint getSpecularTextureID()
	{
		return specularTextureID;
	}

	GLuint getProgramID() 
	{
		return programID;
	}

	void SetMaterial(Material newMaterial) 
	{
		material = newMaterial;
	}

	Material GetMaterial() 
	{
		return material;
	}

	glm::vec3 GetRotation() 
	{
		return modelRotation;		
	}

	void SetRotation(glm::vec3 Rotation) 
	{
		modelRotation = Rotation;
	}

btRigidBody* getRigidbody() 
	{
		return rigidBody;
	}

	void setRigidBody(btRigidBody* RigidBody) 
	{
		rigidBody = RigidBody;
	}

	glm::vec3 getPosition() 
	{
		return position;
	}

	void SetPosition(float x, float y, float z)
	{
		position = glm::vec3(x, y, z);
	}

private:
	//Mesh collection for the object's model.
	MeshCollection* mesh;

	//Object's textureID
	GLuint diffuseTextureID;
	GLuint specularTextureID;

	GLuint programID; //<- load different shaders for each object? 

	//The object's rigidbody
	btRigidBody* rigidBody;

	//The position of the object
	glm::vec3 position;

	//Model Matrix of the object
	glm::mat4 modelMatrix;

	Material material;

	//These could be moved into a transform class
	//Transformation Matricies
	glm::mat4 translationMatrix;
	glm::mat4 rotationMatrix;
	glm::mat4 scaleMatrix;

	//Translation, scale and rotation vectors
	glm::vec3 modelTranslation;
	glm::vec3 modelScale;
	glm::vec3 modelRotation;

	//Rotation axes
	glm::vec3 xAxis;
	glm::vec3 yAxis;
	glm::vec3 zAxis;
};

