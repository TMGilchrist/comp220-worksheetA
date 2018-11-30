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

	//Init object builder.
	objectBuilder = ObjectBuilder();
	objectBuilder.Init();	
	
	//Initialise Bullet Physics
	physics = PhysicsManager();
	physics.Init();

	//Mouse settings
	SDL_ShowCursor(0);
	SDL_SetRelativeMouseMode(SDL_TRUE);

	//Init deltaTime
	deltaTime = 0.0f; // Time between current frame and last frame
	lastFrame = 0.0f; // Time of last frame
}

void Game::Setup()
{
	//Enable backface culling.
	glEnable(GL_CULL_FACE); 

	//Set up a camera and init the projection matrix with window size
	camera = new Camera();
	camera->setProjectionMatrix(windowMain->getWidth(), windowMain->getHeight());

	skybox = Skybox();
	skybox.Init("skyboxVertexShader.glsl", "skyboxFragmentShader.glsl");

	//Create game objects
	CreateObjects();
	CreatePhysicsObjects();

	//Setup lighting
	InitLighting();

	//Set up new inputManager and PlayerController
	input = new InputManager();
	controller = CharacterController(input, camera);
}

void Game::InitLighting() //Things here can probably be split up at some point into materials/lighting
{
	//Lighting
	//ambientLightColour = glm::vec4(136.0f / 255.0f, 0.0f / 255.0f, 204.0f / 255.0f, 0.3f);
	ambientLightColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	diffuseLightColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	specularLightColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	lightDirection = glm::vec3(0.0f, 0.0f, 1.0f);
	ambientIntensity = 0.5f;

	cameraPosition = camera->getPosition();
}

void Game::CreateObjects()
{
	/*---------------------
	Object creation
	---------------------*/

	//Material presets.
	MaterialPresets materialPresets = MaterialPresets();
	materialPresets.Init();

	GameObject* tank1 = objectBuilder.MakeObject("BlinnPhongVert.glsl", "BlinnPhongFragment.glsl",
												objectBuilder.getMeshes()[0], objectBuilder.getDiffuseTextures()[0], objectBuilder.getSpecularTextures()[0],
												materialPresets.GetMetal());

	GameObject* tank2 = objectBuilder.MakeObject("vertexTextured.glsl", "fragmentTextured.glsl", 
												objectBuilder.getMeshes()[0], objectBuilder.getDiffuseTextures()[0],
												materialPresets.GetPlainGreen(), glm::vec3(10.0, 0.0, 0.0));

	GameObject* teapot1 = objectBuilder.MakeObject("BlinnPhongVert.glsl", "BlinnPhongFragment.glsl", 
												  objectBuilder.getMeshes()[1], objectBuilder.getDiffuseTextures()[1], objectBuilder.getSpecularTextures()[0],
												  materialPresets.GetPlainGreen(), glm::vec3(0, 15.0, 5.0), glm::vec3(0.25, 0.25, 0.25));

	GameObject* teapot2 = objectBuilder.MakeObject("BlinnPhongVert.glsl", "BlinnPhongFragment.glsl",		
												  objectBuilder.getMeshes()[1], objectBuilder.getDiffuseTextures()[1],
												  materialPresets.GetPlainRed(), glm::vec3(20, 15.0, 5.0), glm::vec3(0.25, 0.25, 0.25));

	GameObject* tower = objectBuilder.MakeObject("BlinnPhongVert.glsl", "BlinnPhongFragment.glsl",
													objectBuilder.getMeshes()[2], objectBuilder.getDiffuseTextures()[1], objectBuilder.getSpecularTextures()[0],
													materialPresets.GetDeepPurple(), glm::vec3(0.0, -10.0, 0.0), glm::vec3(200, 200, 600)); //was 40, 40, 100
	
	GameObject* terrain = objectBuilder.MakeObject("BlinnPhongVert.glsl", "BlinnPhongFragment.glsl",
													objectBuilder.getMeshes()[5], objectBuilder.getDiffuseTextures()[2], objectBuilder.getSpecularTextures()[0],
													materialPresets.GetPlainWhite(), glm::vec3(0, 0.0, 0.0), glm::vec3(10.0, 10.0, 10.0));

	terrain->SetRotation(glm::vec3(-1.5, 0.0, -1.5));
	//Currently, for whateve reason (probably the import rotation?) x = z, y = x, z = y.
	terrain->SetPosition(500, 100, 0);
	tower->SetRotation(glm::vec3(-1.5, 0, 0));

	//x, z, y
	//tower->SetPosition(-5.0, -25.0, 1.2);
	tower->SetPosition(-150.0, -5.0, 600);

	//Add objects to vector of game objects
	objects.push_back(tank1);
	//objects.push_back(tank2);
	//objects.push_back(teapot1);
	//objects.push_back(teapot2);
	objects.push_back(tower);
	objects.push_back(terrain);
}

void Game::CreatePhysicsObjects()
{
	//Material presets.
	MaterialPresets materialPresets = MaterialPresets();
	materialPresets.Init();

	/*------------------------------
	Create the Ground gameObject and mesh
	------------------------------*/

	GameObject* ground = objectBuilder.MakeObject("BlinnPhongVert.glsl", "BlinnPhongFragment.glsl",
												 objectBuilder.getMeshes()[3], objectBuilder.getDiffuseTextures()[1],
												 materialPresets.GetPlainRed(), glm::vec3(0, -10.0, 0.0), glm::vec3(100.0, 1.0, 100.0));

	/*------------------------------------
	Create Ground rigidbody and collisionBody
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
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
	btRigidBody* groundBody = new btRigidBody(rbInfo);

	//add the body to the dynamics world
	physics.getDynamicsWorld()->addRigidBody(groundBody);
	ground->setRigidBody(groundBody);

	//Add objects to vector of game objects
	objects.push_back(ground);


	/*------------------------------
	Create the Sphere gameObject and mesh
	------------------------------*/

	GameObject* sphere = objectBuilder.MakeObject("BlinnPhongVert.glsl", "BlinnPhongFragment.glsl",
												   objectBuilder.getMeshes()[4], objectBuilder.getDiffuseTextures()[1],
												   materialPresets.GetPlainGreen(), glm::vec3(0, 20, 10.0), glm::vec3(5.0, 5.0, 5.0));
	
	/*------------------------------------
	Create Sphere rigidbody and collisionBody
	------------------------------------*/

	btCollisionShape* sphereShape = new btSphereShape(btScalar(5));
	//collisionShapes.push_back(sphereShape);

	/// Create Dynamic Objects
	btTransform sphereTransform;
	sphereTransform.setIdentity();

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
		//glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		//glClearColor(37.0 / 255, 5.0 / 255, 43.0 / 255, 1.0f);
		glClearColor(106.0f/255.0f, 9.0f/255.0f, 196.0f/255.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		
		// draw skybox
		glDepthMask(GL_FALSE);
		glUseProgram(skybox.GetProgramID());

		glm::mat4 view = glm::mat4(glm::mat3(camera->getViewMatrix()));

		GLuint skyboxViewLocation = glGetUniformLocation(skybox.GetProgramID(), "viewMatrix");
		GLuint skyboxProjLocation = glGetUniformLocation(skybox.GetProgramID(), "projectionMatrix");

		glUniformMatrix4fv(skyboxViewLocation, 1, GL_FALSE, glm::value_ptr(glm::mat4(glm::mat3(camera->getViewMatrix()))));
		glUniformMatrix4fv(skyboxProjLocation, 1, GL_FALSE, glm::value_ptr(camera->getProjectionMatrix()));

		glBindVertexArray(skybox.GetSkyboxVAO());

		glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.GetCubemapTexture());
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(0);
		glDepthMask(GL_TRUE);


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
			glUniform1i(diffuseTextureLocation, 0);

			if (object->getSpecularTextureID() > 100) 
			{
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, object->getSpecularTextureID());
				glUniform1i(specularTextureLocation, 1);
			}

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
	specularMaterialColourLocation = glGetUniformLocation(programID, "specularMaterialColour");
	specularPowerLocation = glGetUniformLocation(programID, "specularPower");

	//Lighting
	cameraPositionLocation = glGetUniformLocation(programID, "cameraPosition");
	lightDirectionLocation = glGetUniformLocation(programID, "lightDirection");

	ambientLightColourLocation = glGetUniformLocation(programID, "ambientLightColour");
	diffuseLightColourLocation = glGetUniformLocation(programID, "diffuseLightColour");
	specularLightColourLocation = glGetUniformLocation(programID, "specularLightColour");

	ambientIntensity = glGetUniformLocation(programID, "ambientIntensity");

	//Textures
	diffuseTextureLocation = glGetUniformLocation(programID, "diffuseTexture");
	specularTextureLocation = glGetUniformLocation(programID, "specularTexture");
}

void Game::SendUniforms(GameObject* object)
{
	//Matrices
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(camera->getProjectionMatrix()));
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(object->getModelMatrix()));

	//Materials

	glUniform4fv(ambientMaterialColourLocation, 1, value_ptr(object->GetMaterial().GetAmbientColour()));
	glUniform4fv(diffuseMaterialColourLocation, 1, value_ptr(object->GetMaterial().GetDiffuseColour()));
	glUniform4fv(specularMaterialColourLocation, 1, value_ptr(object->GetMaterial().GetSpecularColour()));
	glUniform1f(specularPowerLocation, object->GetMaterial().GetSpecularPower());

	//Lighting
	glUniform3fv(lightDirectionLocation, 1, value_ptr(lightDirection));
	glUniform4fv(ambientLightColourLocation, 1, value_ptr(ambientLightColour));
	glUniform4fv(diffuseLightColourLocation, 1, value_ptr(diffuseLightColour));
	glUniform1f(ambientIntensityLocation, ambientIntensity);

	glUniform4fv(specularLightColourLocation, 1, value_ptr(specularLightColour));
	glUniform3fv(cameraPositionLocation, 1, value_ptr(camera->getPosition()));
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