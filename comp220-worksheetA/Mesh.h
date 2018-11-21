#pragma once
#include <GL/glew.h>
#include <glm\glm.hpp>
#include <vector>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm\gtx\transform.hpp>

#include "Vertex.h"
#include "Texture.h"


class Mesh
{
public:
	Mesh();
	~Mesh();

	//Mesh(Vertex VertexData[], int Indices[]);

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
	void FillBufferData(const Vertex VertexData[], int NumOfVertices, unsigned int Indices[], int NumOfIndices);
		
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
	void BindTexture();

	/**
	Render the mesh
	*/
	void Render();

	/**
	Load texture from filepath.
	*/
	void setTextureID(std::string TextureFile) 
	{
		textureID = loadTextureFromFile(TextureFile);
	}

private:
	//Buffers
	GLuint vertexBuffer;
	GLuint elementBuffer;
	GLuint vertexAttributes;

	//Vertex and index data
	static const Vertex vertexData[];
	static unsigned int indices[];

	//Number of vertices and indices
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

	void addMesh(Mesh *mesh);

	void render();
	void destroy();
private:
	std::vector<Mesh*> meshes;
};