#include "GameObject.h"



GameObject::GameObject()
{
	rigidBody = nullptr;
}


GameObject::~GameObject()
{
}

void GameObject::Init(Shader Shader)
{
	shader = Shader;

	//Translation and scale
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);

	//Rotation
	rotation = glm::vec3(0.0f, 0.0f, 0.0f);

	//Axes (could be defined as constants somewhere maybe?)
	xAxis = glm::vec3(1.0f, 0.0f, 0.0f);
	yAxis = glm::vec3(0.0f, 1.0f, 0.0f);
	zAxis = glm::vec3(0.0f, 0.0f, 1.0f);
}

void GameObject::Update()
{   
	//Update object position based on its rigidbody
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
	rotationMatrix = glm::rotate(rotation.x, xAxis) * glm::rotate(rotation.y, yAxis) * glm::rotate(rotation.z, zAxis);
	scaleMatrix = glm::scale(scale);

	//Calculate model matrix
	modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;;

	//Render model
	mesh->render();
}

void GameObject::SetupObjectPhysics(btRigidBody* RigidBody, btDiscreteDynamicsWorld* physicsWorld)
{
	rigidBody = RigidBody;
	AddToPhysicsWorld(physicsWorld);
}

void GameObject::AddToPhysicsWorld(btDiscreteDynamicsWorld* physicsWorld)
{
	physicsWorld->addRigidBody(rigidBody);
}
