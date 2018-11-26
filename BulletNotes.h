/*Bullet3 2.87
Debug/Release libraries. Use debug while in debug mode.
Use correct 32/64 version.

Properties: C++ -> CodeGeneration -> RuntimeLibrary -> change from Multithreaded Debug DLL to Multithreaded Debug.
Link other lib files as well:
	Bullet3Common_Debug.lib
	Bullet3Collision_Debug.lib
	Bullet3Dynamics_Debug.lib
	Bullet3Geometry_Debug.lib
	Bullet3OpenCL_clew_Debug.lib
	
	LinearMath.lib
	BulletCollision_Debug.lib
	BulletDynamics_Debug.lib


Two types of physics objects in Bullet: CollisionShape and Rigidbody.
CollisionShape - Collision volume, basic shapes to create a collision mesh.
Rigidbody - simulated object. Forces act on it.	

Each object should have a CollisionShape and Rigidbody.

*/

/*-----------------------
Main.cpp
-----------------------*/

#include <btBulletDynamicsCommon.h>


/*-----------------------
Game.cpp
-----------------------*/

///In init function (Could move into a CollisionManager class)

	//collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();

	//use the default collision dispatcher. For parallel processing you can use a different dispatcher (see Extras/BulletMultiThreaded)
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

	//btDbvtBroadphase is a good general purpose broadphase. Broad check for objects that don't have to collide.
	btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();

	//the default constraint solver. Solves position and movement of physics objects.
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

	//Physics scene. Pass in the components we just created.
	btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, 
																		 overlappingPairCache, 
																		 solver, 
																		 collisionConfiguration);

																		 
	//Note btVector3. 1 Unit in Bullet = 1 unit in graphics = 1 meter 	 
	dynamicsWorld->setGravity(btVector3(0, -10, 0));


///In create objects (could be moved to new class)

	//Load in a mesh (cube). Scale up to 100x1x100. Position it at (0, -10, -120)

	//The btScalar values should be half of the respective size of the object.
	btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(50.0), btScalar(0.5), btScalar(50.0)));

	//Transform (position, rotation, scale) of the object
	btTransform groundTransform;
	groundTransform.setIdentity();
	
	//Objects position in the world. This should match the position of the object mesh being rendered.
	groundTransform.setOrigin(btVector3(0, -10, -120));
	
	//Use this to rotate object. Takes in a quaternion.
	groudTransform.setRotation();
	
	//Set the mass of the object. 0 for static objects. Do not use negative mass.
	btScalar mass(0.);
	
	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	bool isDynamic = (mass != 0.f);

	//Do you only have one localInertia vector for all objects?	 <- yes
	//Calculate inertia. This should be done for every object.
	btVector3 localInertia(0, 0, 0);
	if (isDynamic)
		groundShape->calculateLocalInertia(mass, localInertia);

	
	//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
	btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
	
	//Link collisionShape and rigidbody together.
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
	
	//Create the rigidbody
	btRigidBody* groundBody = new btRigidBody(rbInfo);

	//add the body to the dynamics world
	dynamicsWorld->addRigidBody(groundBody);
	groundGO-->setRigidBody(groundBody);
	
	//add ground to 
	
///Creating Sphere. Note, variable names must be changed or {} scope operators used.
	//Load in sphere
	
	btCollisionShape* colShape = new btSphereShape(btScalar(1.));
	collisionShapes.push_back(colShape);

	/// Create Dynamic Objects
	btTransform startTransform;
	startTransform.setIdentity();
	
	startTransform.setOrigin(btVector3(0, -10, -120));
	btScalar mass(1.f);

	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	bool isDynamic = (mass != 0.f);

	btVector3 localInertia(0, 0, 0);
	if (isDynamic)
		colShape->calculateLocalInertia(mass, localInertia);

	startTransform.setOrigin(btVector3(2, 10, 0));

	//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
	btRigidBody* sphereBody = new btRigidBody(rbInfo);

	dynamicsWorld->addRigidBody(sphereBody);
	sphereGO->setRigidBody(sphereBody);
	
	//Add sphere to gameobjects list.
	
///After the timer update <- used fixed step. Check how much time has passed then update physics.
	dynamicsWorld->stepSimulation(timer.GetDeltaTime()z, 10); //This shouldn't use deltaTime but fixed time.
	
	btTransform sphereTransform;
	sphereBody->getMotionState()->getWorldTransofrm(sphereTransform);
	
	btVector3 updatedSpherePos = sphereTransform.getOrigin();
	sphereGO->setPosition(updatedSpherePos.getX(), updatedSpherePos.getY(), updatedSpherePos.getZ());
	
	
///In cleanup function

	//delete dynamics world
	delete dynamicsWorld;

	//delete solver
	delete solver;

	//delete broadphase
	delete overlappingPairCache;

	//delete dispatcher
	delete dispatcher;

	delete collisionConfiguration;
	
	
	auto iter = gameObjectList.begin();
		dynamicWorld->removeRigidBody(*iter)->getRigidBody();
		delete(*iter);
	
	
/*-----------------------
GameObject.h
-----------------------*/	


//Getters and setters


private:
	btRigidBody body;

	
	
//Update

if (RigidBody)
{
	Vector3 transform;
	RigidBody->getMotionState()->getWorldTransform(transform);
	
	btVector3 physicsPos = transform
	
}

//Deconstruct

glDeleteTExtures(1, ~DiffuseTExture);

if(rigidbody)
{
	delete RigidBody->getMotionState();
	delete RigidBody->getCollisionShape();
	
	delete RigidBody;
	
}



/*-----------------------
Applying Forces
-----------------------*/	

sphereBody->applyForce(btVector3(0.0f, 10000.0of, 0.0f), btVector3(0.0f, 0.0f, 0.0f));

//or

sphereBody->applyImpulse();






	

