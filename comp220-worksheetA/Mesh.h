/**
Mesh

A 3d mesh containting vertex data. Used to render complex models.

MeshCollection

A collection of meshes comprising a 3d model.
*/

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
	void FillBufferData(Vertex VertexData[], int NumOfVertices, unsigned int Indices[], int NumOfIndices);
	
	void CopyVertexData(Vertex VertexData[]);

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

	@param TextureFile : The filepath to the texture to be loaded.
	*/
	void setTextureID(std::string TextureFile) 
	{
		textureID = loadTextureFromFile(TextureFile);
	}

	std::vector<Vertex> GetVertexData()
	{
		//return vertexData;
	}

private:
	//Buffers
	GLuint vertexBuffer;
	GLuint elementBuffer;
	GLuint vertexAttributes;

	//Number of vertices and indices
	int numOfVertices;
	int numOfIndices;

	//Vertex and index data
	//const Vertex vertexData[1];

	std::vector<Vertex> vertexData;

	static unsigned int indices[];



	//Texture
	GLuint textureID;

};

class MeshCollection
{
public:
	MeshCollection();
	~MeshCollection();

	/**
	Adds a new mesh to the meshCollection.

	@param mesh : The mesh to be added to the collection.
	*/
	void addMesh(Mesh* mesh);

	/**
	Draw each mesh in the mesh collection
	*/
	void render();

	/**
	Delete the mesh collection, destroying each mesh in it.
	*/
	void destroy();

private:
	std::vector<Mesh*> meshes;
};