#include "PhysicsManager.h"



PhysicsManager::PhysicsManager()
{
}


PhysicsManager::~PhysicsManager()
{   /*
	//delete dynamics world
	delete dynamicsWorld;

	//delete solver
	delete solver;

	//delete broadphase
	delete overlappingPairCache;

	//delete dispatcher
	delete dispatcher;

	delete collisionConfiguration;*/
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
