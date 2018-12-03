/**
GameObject

Holds the information for an object, including mesh and texture data, 
position in the gameworld and physics components.

New instances of GameObject should be created using the ObjectBuilder class MakeObject function.
*/

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
	Calls the appropriate function to create physics components, including transform, rigidboy and collider.

	@param colliderType : The type of collider that should be created.
	@param mass : The mass of the object's rigidbody.
	*/
	void SetupPhysicsComponents(std::string colliderType, btScalar mass);

	/**
	Create a box collider and setup transform and rigidbody.
	*/
	void CreateBoxCollider();

	/**
	Create a sphere collider and setup transform and rigidbody.
	*/
	void CreateSphereCollider();

	/**
	Create a convex hull collider and setup transform and rigidbody.
	*/
	void CreateConvexCollider();

	/**
	Add this gameobject's rigidbody to the specified phsyics world so it can interact with the physics system.
	*/
	void AddToPhysicsWorld(btDiscreteDynamicsWorld* physicsWorld);


	/*----------------------
	Getters and Setters
	----------------------*/

	/**
	Attach a meshCollection to the game object.
	*/
	void setMesh(MeshCollection* objectMesh) 
	{
		mesh = objectMesh;
	}

	/**
	Set the object's scale. Use to resize object. 1.0 is the default size.
	*/
	void setScale(glm::vec3 Scale) 
	{
		scale = Scale;
	}
	
	void setProgramID(const char* vert, const char* fragment) 
	{
		programID = LoadShaders(vert, fragment);
	}

	glm::mat4& getModelMatrix() 
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

	glm::vec3& GetRotation() 
	{
		return rotation;		
	}

	void SetRotation(glm::vec3 Rotation) 
	{
		rotation = Rotation;
	}

	btRigidBody* getRigidbody() 
	{
		return rigidBody;
	}

	void setRigidBody(btRigidBody* RigidBody) 
	{
		rigidBody = RigidBody;
	}

	glm::vec3& getPosition() 
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

	//The shaders to use to render this object
	GLuint programID;

	//The object's rigidbody
	btRigidBody* rigidBody;

	//Model Matrix of the object
	glm::mat4 modelMatrix;

	//The material for this object
	Material material;

	//These could be moved into a transform class
	//Transformation Matricies
	glm::mat4 translationMatrix;
	glm::mat4 rotationMatrix;
	glm::mat4 scaleMatrix;

	//Position, scale and rotation vectors
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation;

	//Rotation axes
	glm::vec3 xAxis;
	glm::vec3 yAxis;
	glm::vec3 zAxis;

	//Mass of the object
	btScalar mass;

	//If this is a dynamic physics object
	bool isDynamic;
};

