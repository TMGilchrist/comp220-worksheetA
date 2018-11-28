#pragma once
#include <btBulletDynamicsCommon.h>

class PhysicsManager
{
public:
	PhysicsManager();
	~PhysicsManager();

	/**
	Initialise the physics manager.

	@param btVector3 Gravity : The gravity the phsyics should use. Defaults to (0, -10, 0).
	*/
	void Init(btVector3 Gravity= btVector3(0, -10, 0));

	//Get the physics scene
	btDiscreteDynamicsWorld* getDynamicsWorld() 
	{
		return dynamicsWorld;
	}

private:
	//collision configuration contains default setup for memory, collision setup.
	btDefaultCollisionConfiguration* collisionConfiguration;

	//Collision dispatcher. 
	btCollisionDispatcher* dispatcher;

	//Broad check for objects that don't have to collide.
	btBroadphaseInterface* overlappingPairCache;

	//Default constraint solver. Solves position and movement of physics objects.
	btSequentialImpulseConstraintSolver* solver;

	//Physics scene.
	btDiscreteDynamicsWorld* dynamicsWorld;

};

