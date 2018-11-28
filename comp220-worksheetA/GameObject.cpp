#include "GameObject.h"



GameObject::GameObject()
{
	rigidBody = nullptr;
}


GameObject::~GameObject()
{
}

void GameObject::Init(const char* vert, const char* fragment)
{
	programID = LoadShaders(vert, fragment);

	//Translation and scale
	modelTranslation = glm::vec3(0.0f, 0.0f, 0.0f);
	modelScale = glm::vec3(1.0f, 1.0f, 1.0f);

	//Rotation
	modelRotation = glm::vec3(0.0f, 0.0f, 0.0f);

	//Axes (could be defined as constants somewhere maybe?)
	xAxis = glm::vec3(1.0f, 0.0f, 0.0f);
	yAxis = glm::vec3(0.0f, 1.0f, 0.0f);
	zAxis = glm::vec3(0.0f, 0.0f, 1.0f);
}

void GameObject::Update()
{   
	if (rigidBody)
	{
		btTransform currentTransform;
		btMotionState* currentMotionState = rigidBody->getMotionState();
		currentMotionState->getWorldTransform(currentTransform);

		position = glm::vec3(currentTransform.getOrigin().getX(),
							 currentTransform.getOrigin().getY(),
							 currentTransform.getOrigin().getZ());
	}



	//Calculate Transformation Matricies
	translationMatrix = glm::translate(position);
	rotationMatrix = glm::rotate(modelRotation.x, xAxis) * glm::rotate(modelRotation.y, yAxis) * glm::rotate(modelRotation.z, zAxis);
	scaleMatrix = glm::scale(modelScale);

	//Calculate model matrix
	modelMatrix = rotationMatrix * scaleMatrix * translationMatrix;

	//Render model
	mesh->render();
}
