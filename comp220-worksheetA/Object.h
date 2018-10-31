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

	void Init();
	void FillBufferData(const Vertex VertexData[], int NumOfVertices, const int Indices[], int NumOfIndices);
	void CalculateModelMatrix();
	void SetVertexAttributes();
	void CleanUp();

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

