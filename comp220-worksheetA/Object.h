#pragma once
#include <GL/glew.h>
#include <glm\glm.hpp>
#include "Vertex.h"

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
	void FillBufferData(const Vertex VertexData[], int NumOfVertices, const int Indices[], int NumOfIndices);
	
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

	/***/
	void Update();

private:
	GLuint vertexBuffer;
	GLuint elementBuffer;

	GLuint vertexAttributes;

	glm::mat4 modelMatrix;

	//Transformation Matricies
	glm::mat4 translationMatrix;
	glm::mat4 rotationMatrix;
	glm::mat4 scaleMatrix;

	static const Vertex vertexData[];
	static const int indices[];

	int numOfVertices;
	int numOfIndices;

};

