#pragma once
#include <GL/glew.h>
#include <glm\glm.hpp>
#include "Vertex.h"

class Object
{
public:
	Object();
	~Object();

	Object(Vertex VertexData[], int Indices[]);

	void InitBuffers();
	void CalculateModelMatrix();
	void SetVertexAttributes();

	void Update();

private:
	GLuint vertexBuffer;
	GLuint elementBuffer;

	glm::mat4 modelMatrix;

	//Transformation Matricies
	glm::mat4 translationMatrix;
	glm::mat4 rotationMatrix;
	glm::mat4 scaleMatrix;

	static const Vertex vertexData[];
	static const int indices[];

};

