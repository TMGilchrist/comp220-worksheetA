#include "Object.h"



Object::Object()
{
	//Translation and scale
	modelTranslation = glm::vec3(0.0f, 0.0f, 0.0f);
	modelScale = glm::vec3(1.0f, 1.0f, 1.0f);

	//Rotation
	modelRotation = glm::vec3(0.0f, 0.0f, 0.0f);
	xAxis = glm::vec3(1.0f, 0.0f, 0.0f);
	yAxis = glm::vec3(0.0f, 1.0f, 0.0f);
	zAxis = glm::vec3(0.0f, 0.0f, 1.0f);

	numOfIndices = 0;
	numOfVertices = 0;
}


Object::~Object()
{
	CleanUp();
}

void Object::Init()
{
	//Generate Vertex Attribute Array
	glGenVertexArrays(1, &vertexAttributes);
	glBindVertexArray(vertexAttributes);

	//Generate Vertex Buffer
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	//Generate Element Buffer
	glGenBuffers(1, &elementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
}

void Object::FillBufferData(const Vertex VertexData[], int NumOfVertices, unsigned int Indices[], int NumOfIndices)
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, NumOfVertices * sizeof(Vertex), VertexData, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, NumOfIndices * sizeof(unsigned int), Indices, GL_STATIC_DRAW);

	numOfIndices = NumOfIndices;
	numOfVertices = NumOfVertices;

	//Is it necessary to save the vertex and index data?

	SetVertexAttributes();
}

void Object::CalculateModelMatrix()
{
	//Calculate Transformation Matricies
	translationMatrix = glm::translate(modelTranslation);
	rotationMatrix = glm::rotate(modelRotation.x, xAxis) * glm::rotate(modelRotation.y, yAxis) * glm::rotate(modelRotation.z, zAxis);
	scaleMatrix = glm::scale(modelScale);

	modelMatrix = rotationMatrix * scaleMatrix * translationMatrix;
}

void Object::SetVertexAttributes()
{
	glBindVertexArray(vertexAttributes);

	//1st attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glVertexAttribPointer
	(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		sizeof(Vertex),     // stride
		(void*)0            // array buffer offset
	);

	//2nd attribute buffer : colour
	glEnableVertexAttribArray(1);
	glVertexAttribPointer
	(
		1,
		4,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void*)(3 * sizeof(float))
	);

	//3rd attribute buffer : UV coordinates
	glEnableVertexAttribArray(2);
	glVertexAttribPointer
	(
		2,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void*)(7 * sizeof(float))
	);

	//glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//Render();
}

void Object::CleanUp()
{
	glDeleteVertexArrays(1, &vertexAttributes);
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &elementBuffer);
}

void Object::BindTexure()
{
	//glUseProgram(programID); //Ask why this isn't needed...

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Object::Render()
{
	glBindVertexArray(vertexAttributes);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);

	glDrawElements(GL_TRIANGLES, numOfIndices, GL_UNSIGNED_INT, (void*)0);

}


//-----------------------------------------
//-----------------------------------------

MeshCollection::MeshCollection()
{
}

MeshCollection::~MeshCollection()
{
	destroy();
}

void MeshCollection::addMesh(Object * mesh)
{
	mesh->Init();
	mesh->setTextureID("Resources/Tank1DF");
	mesh->BindTexure();
	mesh->CalculateModelMatrix();

	meshes.push_back(mesh);
}

void MeshCollection::render()
{
	for (Object *mesh : meshes)
	{
		mesh->Render();
	}
}

void MeshCollection::destroy()
{
	auto iter = meshes.begin();
	while (iter != meshes.end())
	{
		if (*iter)
		{
			(*iter)->CleanUp();
			delete (*iter);
			(*iter) = nullptr;
			iter = meshes.erase(iter);
		}
		else
		{
			iter++;
		}
	}

	meshes.clear();
}