#include "Game.h"



Game::Game()
{
}


Game::~Game()
{
}

void Game::Init()
{
	//Create SDL window
	windowMain = new WindowManager();
	windowMain->Init("Shader Practice");
	window = windowMain->getWindow();

	//Initalise Open_GL and GLEW. Get Open_GL context.
	glManager = GLManager(window);
	glManager.Init();
	glContext = glManager.getGLContext();

	//Initialise Bullet Physics
	physics = PhysicsManager();
	physics.Init();

	//Mouse setup, can probably be moved to sdl init?
	SDL_ShowCursor(0);
	SDL_SetRelativeMouseMode(SDL_TRUE);

	//Init deltaTime
	deltaTime = 0.0f; // Time between current frame and last frame
	lastFrame = 0.0f; // Time of last frame
}

void Game::Setup()
{
	//Init deltaTime
	float deltaTime = 0.0f;	// Time between current frame and last frame
	float lastFrame = 0.0f; // Time of last frame

	//Enable backface culling.
	glEnable(GL_CULL_FACE); 

	//Set up a camera and init the projection matrix with window size
	camera = new Camera();
	camera->setProjectionMatrix(windowMain->getWidth(), windowMain->getHeight());

	//Create game objects
	//CreateObjects();
	CreatePhysicsObjects();

	//Setup lighting
	InitLighting();

	//Set up new inputManager and PlayerController
	input = new InputManager();
	controller = CharacterController(input, camera);
}

void Game::InitLighting() //Things here can probably be split up at some point into materials/lighting
{
	//Material
	ambientMaterialColour = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	diffuseMaterialColour = glm::vec4(0.8f, 0.0f, 0.0f, 1.0f);
	specularMaterialColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	//Lighting
	lightDirection = glm::vec3(0.0f, 0.0f, 1.0f);
	ambientLightColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	diffuseLightColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	specularLightColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	ambientIntensity = 0.3f;

	cameraPosition = camera->getPosition();
	specularPower = 25;
}

void Game::CreateObjects()
{
	/*---------------------
	Object creation
	---------------------*/

	//Create an objectBuilder class that loads all meshes and then assigns them to different objects.

	//Load Tank Mesh
	MeshCollection* tankMesh = new MeshCollection();
	loadMeshFromFile("Resources/Tank1.FBX", tankMesh); 
	GLuint tankTextureID = loadTextureFromFile("Resources/Tank1DF.PNG");

	//Load Teapot Mesh
	MeshCollection* teaPotMesh = new MeshCollection();
	loadMeshFromFile("Resources/teapot.FBX", teaPotMesh);
	GLuint checkerTextureID = loadTextureFromFile("Resources/checkerboard.PNG");
	GLuint redTextureID = loadTextureFromFile("Resources/Red.PNG");

	//Add meshes to vector
	meshes.push_back(tankMesh);
	meshes.push_back(teaPotMesh);

	//Create new objects
	GameObject* tank1 = new GameObject();
	GameObject* tank2 = new GameObject();
	GameObject* teapot = new GameObject();

	//Init object variables with the shaders to use
	tank1->Init("vertexTextured.glsl", "fragmentTextured.glsl");
	tank2->Init("vertexTextured.glsl", "fragmentTextured.glsl");
	teapot->Init("BlinnPhongVert.glsl", "BlinnPhongFragment.glsl");

	//Set textures
	tank1->setDiffuseTextureID(tankTextureID);
	tank2->setDiffuseTextureID(tankTextureID);
	teapot->setDiffuseTextureID(checkerTextureID);

	//Scale objects
	teapot->setScale(glm::vec3(0.25, 0.25, 0.25));

	//Position objects
	tank2->setTranslation(glm::vec3(10.0, 0.0, 0.0));
	teapot->setTranslation(glm::vec3(10, 15.0, 5.0));

	//Set object meshes
	tank1->setMesh(tankMesh);
	tank2->setMesh(tankMesh);
	teapot->setMesh(teaPotMesh);

	//Add objects to vector of game objects
	objects.push_back(tank1);
	objects.push_back(tank2);
	objects.push_back(teapot);
}

void Game::CreatePhysicsObjects()
{
	
	/*------------------------------
	Create the gameObject and mesh
	------------------------------*/

	MeshCollection* cubeMesh = new MeshCollection();
	loadMeshFromFile("Resources/cube.nff", cubeMesh);

	GameObject* ground = new GameObject();

	//Init object variables with the shaders to use
	ground->Init("BlinnPhongVert.glsl", "BlinnPhongFragment.glsl");

	ground->SetPosition(0.0f, -10.0f, 0.0f);
	ground->setScale(glm::vec3(100.0f, 1.0f, 100.0f));
	//ground->setTranslation(glm::vec3(0.0f, -10.0f, -120.0f));


	//Set object meshes
	ground->setMesh(cubeMesh);


	/*------------------------------------
	Create rigidbody and collisionBody
	------------------------------------*/

	//The btScalar values should be half of the respective size of the object.
	btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(50.0), btScalar(0.5), btScalar(50.0)));

	//Transform (position, rotation, scale) of the object
	btTransform groundTransform;
	groundTransform.setIdentity();

	//Objects position in the world. This should match the position of the object mesh being rendered.
	glm::vec3 groundPosition = ground->getPosition();
	groundTransform.setOrigin(btVector3(groundPosition.x, groundPosition.y, groundPosition.z)); //+8 to put the collider at the right level... 
																									//why does the collider sit 8 units lower than the mesh????

	//Use this to rotate object. Takes in a quaternion.
	//groundTransform.setRotation();

	//Set the mass of the object. 0 for static objects. Do not use negative mass.
	btScalar mass(0.0);

	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	bool isDynamic = (mass != 0.0f);

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
	physics.getDynamicsWorld()->addRigidBody(groundBody);

	ground->setRigidBody(groundBody);


	//Add objects to vector of game objects
	objects.push_back(ground);



	/*------------------------------
	Create the gameObject and mesh
	------------------------------*/

	MeshCollection* sphereMesh = new MeshCollection();
	loadMeshFromFile("Resources/sphere.nff", sphereMesh);
	
	GameObject* sphere = new GameObject();

	//Init object variables with the shaders to use
	sphere->Init("BlinnPhongVert.glsl", "BlinnPhongFragment.glsl");

	//sphere->setScale(glm::vec3(4.0f, 4.0f, 4.0f));
	//sphere->setTranslation(glm::vec3(0.0f, 5.0f, 10.0f));
	sphere->SetPosition(0.0f, 5.0f, 10.0f);

	//Set object meshes
	sphere->setMesh(sphereMesh);
	
	/*------------------------------------
	Create rigidbody and collisionBody
	------------------------------------*/

	btCollisionShape* sphereShape = new btSphereShape(btScalar(1.0));
	//collisionShapes.push_back(sphereShape);

	/// Create Dynamic Objects
	btTransform sphereTransform;
	sphereTransform.setIdentity();

	//sphereTransform.setOrigin(btVector3(0, 5, 10));
	glm::vec3 spherePosition = sphere->getPosition();
	sphereTransform.setOrigin(btVector3(spherePosition.x, spherePosition.y, spherePosition.z));

	btScalar sphereMass(1.0f);

	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	bool sphereIsDynamic = (sphereMass != 0.0f);

	btVector3 localSphereInertia(0, 0, 0);
	if (sphereIsDynamic)
		sphereShape->calculateLocalInertia(mass, localSphereInertia);

	//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
	btDefaultMotionState* sphereMotionState = new btDefaultMotionState(sphereTransform);
	btRigidBody::btRigidBodyConstructionInfo sphereRbInfo(sphereMass, sphereMotionState, sphereShape, localSphereInertia);
	btRigidBody* sphereBody = new btRigidBody(sphereRbInfo);

	physics.getDynamicsWorld()->addRigidBody(sphereBody);
	sphere->setRigidBody(sphereBody);

	//Add objects to vector of game objects
	objects.push_back(sphere);

}

void Game::GameLoop()
{
	/*----------------------
	  Main Game Loop
	------------------------*/

	//Event loop, we will loop until running is set to false
	bool gameIsRunning = true;

	//SDL Event structure, this will be checked in the while loop
	SDL_Event event;

	while (gameIsRunning)
	{
		//Poll for the events which have happened in this frame
		while (SDL_PollEvent(&event))
		{
			//Switch case for every message we are intereted in
			switch (event.type)
			{
				//QUIT Message, usually called when the window has been closed
			case SDL_QUIT:
				gameIsRunning = false;
				break;

			case SDL_KEYDOWN:
				//Update inputManager
				input->manageKeyboardEvents(event);

				//Check individual keys by code
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					gameIsRunning = false;
					break;

				case SDLK_F2:
					windowMain->toggleFullScreen();

					//Recalculate projection matrix with new screen size
					camera->setProjectionMatrix(windowMain->getWidth(), windowMain->getHeight());
					break;

				}

			case SDL_KEYUP:
				//Update inputManager
				input->manageKeyboardEvents(event);
				break;

			case SDL_MOUSEMOTION:
				//Pass location to inputManager

				input->mouseInput(event.motion.xrel, event.motion.yrel);
				controller.handleMouse();

				break;
			}
		}

		
		//Update deltatime
		float currentFrame = SDL_GetTicks();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		physics.getDynamicsWorld()->stepSimulation(deltaTime, 10); //This shouldn't use deltaTime but fixed time.

		//Handle keyboard input
		controller.handleKeyboard(deltaTime);

		//OpenGL rendering
		glClearColor(0.0, 0.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	


		/*----------------------------
		Check vector of game objects          <-This should probably be changed to only update when the objects require updating.
		----------------------------*/

		for (GameObject* object : objects)
		{
			//Setup program and uniforms unique to object
			glUseProgram(object->getProgramID());
			SetUniformLocations(object->getProgramID());

			//Bind and send texture. I would like the texture uniform to be part of SendUniforms, but I'm not sure how that would work with multiple textures?
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, object->getDiffuseTextureID());
			glUniform1i(textureUniformLocation, 0);

			//Send uniforms
			SendUniforms(object);

			//Update object
			object->Update();
		}


		//Refresh screen
		SDL_GL_SwapWindow(window);
	}
}

void Game::SetUniformLocations(GLuint programID)
{
	//Matrices
	modelMatrixLocation = glGetUniformLocation(programID, "modelMatrix");
	viewMatrixLocation = glGetUniformLocation(programID, "viewMatrix");
	projectionMatrixLocation = glGetUniformLocation(programID, "projectionMatrix");
	MVPLocation = glGetUniformLocation(programID, "MVP");

	//Materials
	ambientMaterialColourLocation = glGetUniformLocation(programID, "ambientMaterialColour");
	diffuseMaterialColourLocation = glGetUniformLocation(programID, "diffuseMaterialColour");

	//Lighting
	lightDirectionLocation = glGetUniformLocation(programID, "lightDirection");
	ambientLightColourLocation = glGetUniformLocation(programID, "ambientLightColour");
	diffuseLightColourLocation = glGetUniformLocation(programID, "diffuseLightColour");
	ambientIntensity = glGetUniformLocation(programID, "ambientIntensity");

	specularMaterialColourLocation = glGetUniformLocation(programID, "specularMaterialColour");
	specularLightColourLocation = glGetUniformLocation(programID, "specularLightColour");
	cameraPositionLocation = glGetUniformLocation(programID, "cameraPosition");
	specularPowerLocation = glGetUniformLocation(programID, "specularPower");

	//Textures
	textureUniformLocation = glGetUniformLocation(programID, "textureSampler");
}

void Game::SendUniforms(GameObject* object)
{
	//cameraPosition = camera->getPosition();

	//Matrices
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(camera->getProjectionMatrix()));
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(object->getModelMatrix()));

	//Materials
	glUniform4fv(ambientMaterialColourLocation, 1, value_ptr(ambientMaterialColour));
	glUniform4fv(diffuseMaterialColourLocation, 1, value_ptr(diffuseMaterialColour));

	//Lighting
	glUniform3fv(lightDirectionLocation, 1, value_ptr(lightDirection));
	glUniform4fv(ambientLightColourLocation, 1, value_ptr(ambientLightColour));
	glUniform4fv(diffuseLightColourLocation, 1, value_ptr(diffuseLightColour));
	glUniform1f(ambientIntensityLocation, ambientIntensity);

	glUniform4fv(specularLightColourLocation, 1, value_ptr(specularLightColour));
	glUniform4fv(specularMaterialColourLocation, 1, value_ptr(specularMaterialColour));
	glUniform3fv(cameraPositionLocation, 1, value_ptr(camera->getPosition()));
	glUniform1f(specularPowerLocation, specularPower);
}

void Game::Cleanup()
{
	/*--------------------
	   Cleanup
	--------------------*/

	glDeleteProgram(programID);

	

	//Destroy vector of game objects
	auto iter = objects.begin();
	while (iter != objects.end())
	{
		if (*iter)
		{
			//(*iter)->CleanUp(); Call destructor/cleanup here
			delete (*iter);
			(*iter) = nullptr;
			iter = objects.erase(iter);
		}

		else
		{
			iter++;
		}
	}

	//Destroy vector of meshes
	auto iter2 = meshes.begin();
	while (iter2 != meshes.end())
	{
		if (*iter2)
		{
			//(*iter)->CleanUp(); Call destructor/cleanup here
			delete (*iter2);
			(*iter2) = nullptr;
			iter2 = meshes.erase(iter2);
		}

		else
		{
			iter2++;
		}
	}

	//Destroy vector of textures
	auto iter3 = textures.begin();
	while (iter3 != textures.end())
	{
		if (*iter3)
		{
			//(*iter)->CleanUp(); Call destructor/cleanup here
			delete (*iter3);
			(*iter3) = nullptr;
			iter3 = textures.erase(iter3);
		}

		else
		{
			iter3++;
		}
	}


	objects.clear();
	meshes.clear();
	textures.clear();

	//Delete context
	SDL_GL_DeleteContext(glContext);

	//Destroy the window and quit SDL2, NB we should do this after all cleanup in this order!!!
	SDL_DestroyWindow(window);
	SDL_Quit();
}