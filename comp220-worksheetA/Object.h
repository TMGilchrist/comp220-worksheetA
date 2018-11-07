#pragma once
#include <GL/glew.h>
#include <glm\glm.hpp>
#include <vector>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm\gtx\transform.hpp>

#include "Vertex.h"
#include "Texture.h"


class Object
{
public:
	Object();
	~Object();

	//Object(Vertex VertexData[], int Indices[]);

	/**
	Set up buffer and vertex attribute array
	*/
	void Init();

	/**
	Add mesh data to the buffers and set vertex attributes.

	@param VertexData : The mesh vertices
	@param NumOfVertices : Number of unique vertices in mesh
	@param Indices : The indices that define the mesh
	@param NumOfIndices : Number of indices in mesh

	*/
	void FillBufferData(Vertex* VertexData, int NumOfVertices, unsigned int* Indices, int NumOfIndices);
	
	/**
	Calculate the model matrix from the transform matrices
	*/
	void CalculateModelMatrix();
	
	/**
	Set the vertex attributes
	*/
	void SetVertexAttributes();
	
	/**
	Delete buffers and the vertex attribute array
	*/
	void CleanUp();

	/**
	Bind the model's texture
	*/
	void BindTexure();

	void Render();

	/***/
	void Update();


	/**
	Load texture from filepath.
	*/
	void setTextureID(std::string TextureFile) 
	{
		textureID = loadTextureFromFile(TextureFile);
	}


	glm::mat4 getModelMatrix() 
	{
		return modelMatrix;
	}
private:
	GLuint vertexBuffer;
	GLuint elementBuffer;
	GLuint vertexAttributes;

	glm::mat4 modelMatrix;

	//Transformation Matricies
	glm::mat4 translationMatrix;
	glm::mat4 rotationMatrix;
	glm::mat4 scaleMatrix;

	//Translation and scale vectors
	glm::vec3 modelTranslation;
	glm::vec3 modelScale;

	//Rotation vecotrs
	glm::vec3 modelRotation;
	glm::vec3 xAxis;
	glm::vec3 yAxis;
	glm::vec3 zAxis;

	//Mesh Data
	//static const Vertex vertexData[];
	//static const int indices[];

	static const Vertex vertexData[];
	static unsigned int indices[];

	int numOfVertices;
	int numOfIndices;

	//Texture
	GLuint textureID;

};

class MeshCollection
{
public:
	MeshCollection();
	~MeshCollection();

	void addMesh(Object *mesh);

	void render();
	void destroy();
private:
	std::vector<Object*> meshes;
};