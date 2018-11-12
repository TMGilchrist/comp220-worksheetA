#pragma once
#include <glm\glm.hpp>
#include "Mesh.h"

class GameObject
{
public:
	GameObject();



	~GameObject();

	/**
	Initalise member variables
	*/
	void Init();

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

	
	glm::mat4 getModelMatrix() 
	{
		return modelMatrix;
	}

private:
	//Mesh collection for the object's model.
	MeshCollection* mesh;

	//Model Matrix of the object
	glm::mat4 modelMatrix;

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

