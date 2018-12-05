/**
PhysicsManager

Handles the creation and deletion of a BulletPhysics dynamicsWorld. 
This is used as the basis for the game's physics system.
*/

#pragma once
#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h>

#include "GameObject.h"
#include "Enums.h"


class PhysicsManager
{
public:
	PhysicsManager();
	~PhysicsManager();

//Why does this have to be here? Should it be here? 

	/**
	Initialise the physics manager.

	@param btVector3 Gravity : The gravity the phsyics should use. Defaults to (0, -10, 0).
	*/
	void Init(btVector3 Gravity= btVector3(0, -10, 0));

	void CleanUp();

	/**
	Get the physics scene
	
	@return dynamicsWorld : A physics scene that handles the physics of any rigidbodies that are added to it.
	*/
	btDiscreteDynamicsWorld* getDynamicsWorld() 
	{
		return dynamicsWorld;
	}

	btRigidBody* CreateCollisionShape(GameObject* object, collisionShapes shape);
		
	/**
	Create a heightfieldTerrain
	*/
	btCollisionShape* CreateTerrainCollider(GameObject* object, MeshCollection* mesh);

	/**
	Return a new rigidbody. Creates required components including transform and inertia.

	@param object : The GameObject the rigidbody is being created for.
	@param collider : The collisionShape used to create the rigidbody.
	@returns A new btRigidBody.
	*/
	btRigidBody* CreateRigidBody(GameObject* object, btCollisionShape* collider);

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

