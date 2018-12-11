#include "PhysicsManager.h"



PhysicsManager::PhysicsManager()
{
}


PhysicsManager::~PhysicsManager()
{   
}

void PhysicsManager::Init(btVector3 Gravity)
{
	//collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
	collisionConfiguration = new btDefaultCollisionConfiguration();

	//use the default collision dispatcher. For parallel processing you can use a different dispatcher (see Extras/BulletMultiThreaded)
	dispatcher = new btCollisionDispatcher(collisionConfiguration);

	//btDbvtBroadphase is a good general purpose broadphase. Broad check for objects that don't have to collide.
	overlappingPairCache = new btDbvtBroadphase();

	//the default constraint solver. Solves position and movement of physics objects.
	solver = new btSequentialImpulseConstraintSolver;

	//Physics scene. Pass in the components we just created.
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

	//Note btVector3. 1 Unit in Bullet = 1 unit in graphics = 1 meter 	 
	dynamicsWorld->setGravity(Gravity);
}

btRigidBody* PhysicsManager::CreateCollisionShape(GameObject* object, collisionShapes shape, const std::string& heightmapFile)
{
	btCollisionShape* collider;

	//Create specific collider shape
	if (shape == BoxCollider)
	{
		collider = new btBoxShape(btVector3(btScalar(object->getScale().x / 2.0), btScalar(object->getScale().y / 2.0), btScalar(object->getScale().z / 2.0)));
	}

	else if (shape == SphereCollider)
	{
		collider = new btSphereShape(btScalar(object->getScale().x));
	}

	else if (shape == ConvexHullCollider)
	{
		collider = CreateConvexCollider(object, object->getMesh());
	}

	else if (shape == TerrainCollider)
	{
		collider = CreateTerrainCollider(object, object->getMesh(), heightmapFile);
	}

	else
	{
		//show error message
		return nullptr;
	}

	return CreateRigidBody(object, collider);
}

btCollisionShape * PhysicsManager::CreateConvexCollider(GameObject * object, MeshCollection * mesh)
{
	//Convert the mesh vertices to Points
	//std::vector<Point> points = VerticesToPoints(mesh->GetVertexData());
	std::vector<btVector3> pointData = VerticesToBtVectors(mesh->GetVertexData());

	btConvexHullShape* collider = new btConvexHullShape();

	for (int i = 0; i < 100000; i++)
	{
		//collider->addPoint(pointData[i]);
	}

	return collider;
}

btCollisionShape* PhysicsManager::CreateTerrainCollider(GameObject* object, MeshCollection* mesh, const std::string& heightmapFile)
{
	/*const void* terrainData = &mesh->GetVertexData();

	int heightStickWidth = (mesh->GetVertexData().size() / 2);

	//Create the collision shape
	btHeightfieldTerrainShape* collider = new btHeightfieldTerrainShape(50, 50, terrainData, btScalar(1.0), btScalar(1.0), btScalar(1.0), 1);
	return collider;*/

	SDL_Surface* heightMap = loadHeightMap(heightmapFile);
	Uint32* pixels = (Uint32*)heightMap->pixels;

	//std::cout << pixels;

	btHeightfieldTerrainShape* collider = new btHeightfieldTerrainShape(heightMap->w, heightMap->h, pixels, btScalar(1.0), btScalar(1.0), btScalar(1.0), 1);
	return collider;
}

btRigidBody* PhysicsManager::CreateRigidBody(GameObject* object, btCollisionShape* collider)
{
	//Create transform
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(object->getPosition().x, object->getPosition().y, object->getPosition().z));

	//Calculate inertia.
	btVector3 localInertia(0, 0, 0);
	if (object->getIsDynamic())
		collider->calculateLocalInertia(object->getMass(), localInertia);

	//Create the rigidbody
	btDefaultMotionState* motionState = new btDefaultMotionState(transform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(object->getMass(), motionState, collider, localInertia);
	return new btRigidBody(rbInfo);
}


void PhysicsManager::CleanUp()
{
	//delete dynamics world
	delete dynamicsWorld;

	//delete solver
	delete solver;

	//delete broadphase
	delete overlappingPairCache;

	//delete dispatcher
	delete dispatcher;

	delete collisionConfiguration;
}
