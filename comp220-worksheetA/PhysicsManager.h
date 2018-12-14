/**
PhysicsManager

Handles the creation and deletion of a BulletPhysics dynamicsWorld. 
This is used as the basis for the game's physics system.

Also contains functions for the creation of rigidbodies and collision shapes for gameobjects.
*/

#pragma once
#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h>

#include "GameObject.h"
#include "Enums.h"
#include "Utility.h"


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

	/**
	Create collisionShape and rigidbody for object. (Maybe rename to make it obvious that this does both).

	@param object : The gameobject to create the collision shape and rigidbody for.
	@param shape : The type of collision shape to create.
	*/
	btRigidBody* CreateCollisionShape(GameObject* object, collisionShapes shape, const std::string& heightmapFile = "");
		
	/**
	Create a convexHull collisionShape

	@param object : The gameObject the shape is being created for.
	@param mesh : The mesh the collision shape is build around.
	@returns collider : A complex collision shape built around a mesh mesh.
	*/
	btCollisionShape* CreateConvexCollider(GameObject* object, MeshCollection* mesh);

	/**
	Create a heightfieldTerrain collisionShape

	@param object : The gameObject the shape is being created for.
	@param mesh : The mesh the collision shape is build around.
	@returns collider : A complex collision shape built around a heightmap mesh.
	*/
	btCollisionShape* CreateTerrainCollider(GameObject* object, MeshCollection* mesh, const std::string& heightmap);

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

