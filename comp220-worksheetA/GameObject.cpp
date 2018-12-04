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

void GameObject::SetupPhysicsComponents(std::string colliderType, btScalar Mass)
{
	mass = Mass;
	isDynamic = (mass != 0.0f);

	if ((colliderType == "boxCollider") | (colliderType == "BoxCollider")) 
	{
		CreateBoxCollider();
	}

	else if ((colliderType == "sphereCollider") | (colliderType == "SphereCollider"))
	{
		CreateSphereCollider();
	}

	else if ((colliderType == "Collider") | (colliderType == "BoxCollider"))
	{

	}

	else if ((colliderType == "terrainCollider") | (colliderType == "TerrainCollider")) 
	{
		CreateTerrainCollider();
	}

	else 
	{
		//show error message
	}
}

void GameObject::CreateBoxCollider()
{
	//Create the collision shape
	btCollisionShape* boxCollider = new btBoxShape(btVector3(btScalar(scale.x / 2.0), btScalar(scale.y / 2.0), btScalar(scale.z / 2.0)));

	//Transform (position, rotation, scale) of the object
	btTransform transform;
	transform.setIdentity();

	//Objects position in the world. This should match the position of the object mesh being rendered.
	transform.setOrigin(btVector3(position.x, position.y, position.z));																									

	//Use this to rotate object. Takes in a quaternion.
	//transform.setRotation();

	//Calculate inertia.
	btVector3 localInertia(0, 0, 0);
	if (isDynamic)
		boxCollider->calculateLocalInertia(mass, localInertia);
	
	//Create the rigidbody
	btDefaultMotionState* motionState = new btDefaultMotionState(transform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, boxCollider, localInertia);
	rigidBody = new btRigidBody(rbInfo);
}

void GameObject::CreateSphereCollider()
{
	btCollisionShape* sphereCollider = new btSphereShape(btScalar(scale.x));

	btTransform transform;
	transform.setIdentity();

	transform.setOrigin(btVector3(position.x, position.y, position.z));

	btVector3 localInertia(0, 0, 0);
	if (isDynamic)
		sphereCollider->calculateLocalInertia(mass, localInertia);

	//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
	btDefaultMotionState* motionState = new btDefaultMotionState(transform);
	btRigidBody::btRigidBodyConstructionInfo sphereRbInfo(mass, motionState, sphereCollider, localInertia);
	rigidBody = new btRigidBody(sphereRbInfo);
}

void GameObject::CreateConvexCollider()
{
	//const btScalar* terrainData = mesh->GetVertexData();

	//Create the collision shape
	btCollisionShape* convexCollider = new btConvexHullShape();//new btBoxShape(btVector3(btScalar(scale.x / 2), btScalar(scale.y / 2), btScalar(scale.z / 2)));
	//terrainCollider.add


	//Transform (position, rotation, scale) of the object
	btTransform transform;
	transform.setIdentity();

	//Objects position in the world. This should match the position of the object mesh being rendered.
	transform.setOrigin(btVector3(position.x, position.y, position.z));

	//Use this to rotate object. Takes in a quaternion.
	//transform.setRotation();

	//Calculate inertia.
	btVector3 localInertia(0, 0, 0);
	if (isDynamic)
		convexCollider->calculateLocalInertia(mass, localInertia);

	//Create the rigidbody
	btDefaultMotionState* motionState = new btDefaultMotionState(transform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, convexCollider, localInertia);
	rigidBody = new btRigidBody(rbInfo);
}

void GameObject::CreateTerrainCollider()
{
	const void* terrainData = &mesh->GetVertexData();

	//Create the collision shape
	btHeightfieldTerrainShape* terrainCollider = new btHeightfieldTerrainShape(50, 50, terrainData, btScalar(1.0), btScalar(1.0), btScalar(1.0), 1);

	//Transform (position, rotation, scale) of the object
	btTransform transform;
	transform.setIdentity();

	//Objects position in the world. This should match the position of the object mesh being rendered.
	transform.setOrigin(btVector3(position.x, position.y, position.z));

	//Use this to rotate object. Takes in a quaternion.
	//transform.setRotation();

	//Calculate inertia.
	btVector3 localInertia(0, 0, 0);
	if (isDynamic)
		terrainCollider->calculateLocalInertia(mass, localInertia);

	//Create the rigidbody
	btDefaultMotionState* motionState = new btDefaultMotionState(transform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, terrainCollider, localInertia);
	rigidBody = new btRigidBody(rbInfo);
}

void GameObject::AddToPhysicsWorld(btDiscreteDynamicsWorld* physicsWorld)
{
	physicsWorld->addRigidBody(rigidBody);
}
