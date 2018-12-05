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
	
	//Init material presets
	materialPresets = MaterialPresets();
	materialPresets.Init();

	//Initialise Bullet Physics
	physics = PhysicsManager();
	physics.Init();

	//Init DebugDrawer
	debugDrawer = OpenGLBulletDebugDrawer();
	debugDrawer.CreateShader();
	physics.getDynamicsWorld()->setDebugDrawer(&debugDrawer);

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
	//Ambient, diffuse, direction
	DirectionalLight moonLight = { 
								   glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
								   glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 
								   glm::vec3(-0.5f, 0.0f, -1.0f) 
								 };

	//Lighting
	//81.0f / 255.0f, 68.0f / 255.0f, 200.0f / 255.0f, 1.0f
	//1.0f, 1.0f, 1.0f, 1.0f
	//ambientLightColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	ambientLightColour = glm::vec4(145.0f / 255.0f, 150.0f / 255.0f, 198.0f / 255.0f, 1.0f);
	//ambientLightColour = glm::vec4(135.0f / 255.0f, 115.0f / 255.0f, 215.0f / 255.0f, 1.0f);
	diffuseLightColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	specularLightColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	lightDirection = glm::vec3(-0.5f, 0.0f, -1.0f);
	ambientIntensity = 10.0f;

	cameraPosition = camera->getPosition();
}

void Game::CreateObjects()
{
	GameObject* tank1 = objectBuilder.MakeObject("DiffuseTextureLightingVert.glsl", "DiffuseTextureLightingFragment.glsl",
												objectBuilder.getMeshes()[0], objectBuilder.getDiffuseTextures()[3], objectBuilder.getSpecularTextures()[0],
												materialPresets.GetMetal());

	GameObject* tank2 = objectBuilder.MakeObject("DiffuseTextureLightingVert.glsl", "DiffuseTextureLightingFragment.glsl",
												objectBuilder.getMeshes()[0], objectBuilder.getDiffuseTextures()[0],
												materialPresets.GetPlainGreen(), glm::vec3(10.0, 0.0, 0.0));

	GameObject* teapot1 = objectBuilder.MakeObject("DiffuseTextureLightingVert.glsl", "DiffuseTextureLightingFragment.glsl",
												  objectBuilder.getMeshes()[1], objectBuilder.getDiffuseTextures()[1], objectBuilder.getSpecularTextures()[0],
												  materialPresets.GetPlainGreen(), glm::vec3(0, 15.0, 5.0), glm::vec3(0.25, 0.25, 0.25));

	GameObject* teapot2 = objectBuilder.MakeObject("DiffuseTextureLightingVert.glsl", "DiffuseTextureLightingFragment.glsl",
												  objectBuilder.getMeshes()[1], objectBuilder.getDiffuseTextures()[1],
												  materialPresets.GetPlainRed(), glm::vec3(20, 15.0, 5.0), glm::vec3(0.25, 0.25, 0.25));

	GameObject* tower = objectBuilder.MakeObject("DiffuseTextureLightingVert.glsl", "DiffuseTextureLightingFragment.glsl",
													objectBuilder.getMeshes()[2], objectBuilder.getDiffuseTextures()[3], objectBuilder.getSpecularTextures()[0],
													materialPresets.GetDeepPurple(), glm::vec3(0.0, -10.0, 0.0), glm::vec3(200, 200, 600));
	
	GameObject* terrain = objectBuilder.MakeObject("BlinnPhongVert.glsl", "BlinnPhongFragment.glsl",
													objectBuilder.getMeshes()[5], objectBuilder.getDiffuseTextures()[2], objectBuilder.getSpecularTextures()[0],
													materialPresets.GetStone(), glm::vec3(0, 0.0, 0.0), glm::vec3(10.0, 10.0, 10.0));

	GameObject* tree = objectBuilder.MakeObject("DiffuseTextureLightingVert.glsl", "DiffuseTextureLightingFragment.glsl",
												   objectBuilder.getMeshes()[6], objectBuilder.getDiffuseTextures()[4], objectBuilder.getSpecularTextures()[0],
												   materialPresets.GetPlainWhite(), glm::vec3(400.0, -100.0, 300.0), glm::vec3(50.0, 50.0, 50.0));

	GameObject* tree2 = objectBuilder.MakeObject("DiffuseTextureLightingVert.glsl", "DiffuseTextureLightingFragment.glsl",
												 objectBuilder.getMeshes()[6], objectBuilder.getDiffuseTextures()[4], objectBuilder.getSpecularTextures()[0],
												 materialPresets.GetPlainWhite(), glm::vec3(400.0, -80.0, 0.0), glm::vec3(40.0, 40.0, 40.0));

	GameObject* tree3 = objectBuilder.MakeObject("DiffuseTextureLightingVert.glsl", "DiffuseTextureLightingFragment.glsl",
												 objectBuilder.getMeshes()[6], objectBuilder.getDiffuseTextures()[4], objectBuilder.getSpecularTextures()[0],
												 materialPresets.GetPlainWhite(), glm::vec3(0.0, -100.0, 450.0), glm::vec3(50.0, 50.0, 50.0));

	GameObject* treeScene = objectBuilder.MakeObject("DiffuseTextureLightingVert.glsl", "DiffuseTextureLightingFragment.glsl",
													 objectBuilder.getMeshes()[7], objectBuilder.getDiffuseTextures()[4], objectBuilder.getSpecularTextures()[0],
													 materialPresets.GetPlainWhite(), glm::vec3(0.0, 0.0, 0.0), glm::vec3(50.0, 50.0, 50.0));


	/*
	Note on positioning:
	+X = left, -X = right.
	+Y = Up, -Y = Down.	
	+Z = Forwards, -Z = backwards.	
	*/
						

	terrain->SetRotation(glm::vec3(-1.5, 0.0, -0.55));
	terrain->SetPosition(400.0, 0.0, -1000.0);

	terrain->setMass(0.0f);
	terrain->SetupObjectPhysics(physics.CreateCollisionShape(terrain, ConvexHullCollider), physics.getDynamicsWorld());


	tower->SetRotation(glm::vec3(-1.5, 0, 0));
	tower->SetPosition(1100.0, -5.0, 800);

	tree->setScale(glm::vec3(100.0f, 100.0f, 100.0f));

	//Add objects to vector of game objects
	//objects.push_back(tank1);
	objects.push_back(tower);
	objects.push_back(terrain);

	objects.push_back(tree);
	objects.push_back(tree2);
	objects.push_back(tree3);

	objects.push_back(treeScene);
}

void Game::CreatePhysicsObjects()
{
	//Create physics objects
	GameObject* ground = objectBuilder.MakeObject("DiffuseTextureLightingVert.glsl", "DiffuseTextureLightingFragment.glsl",
												 objectBuilder.getMeshes()[3], objectBuilder.getDiffuseTextures()[1],
												 materialPresets.GetPlainRed(), glm::vec3(0, -10.0, 0.0), glm::vec3(100.0, 1.0, 100.0));

	ground->setMass(0.0f); //This should be the default value!
	//ground->SetupObjectPhysics(physics.CreateCollisionShape(ground, BoxCollider), physics.getDynamicsWorld());


	GameObject* sphere = objectBuilder.MakeObject("DiffuseTextureLightingVert.glsl", "DiffuseTextureLightingFragment.glsl",
												   objectBuilder.getMeshes()[4], objectBuilder.getDiffuseTextures()[1],
												   materialPresets.GetPlainGreen(), glm::vec3(0, 20, 10.0), glm::vec3(5.0, 5.0, 5.0));
	
	sphere->setMass(1.0f);
	sphere->SetupObjectPhysics(physics.CreateCollisionShape(sphere, SphereCollider), physics.getDynamicsWorld());


	//Add objects to vector of game objects
	//objects.push_back(ground);
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

				case SDLK_F1:
					debugDrawModeEnabled = !debugDrawModeEnabled;
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
		glClearColor(106.0f/255.0f, 9.0f/255.0f, 196.0f/255.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
				
		/*--------------------- 
		Draw skybox
		---------------------*/
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

		//Draw collision shape debug lines
		if (debugDrawModeEnabled) 
		{
			glDisable(GL_DEPTH_TEST); 
			debugDrawer.SetViewAndProjectMatrix(camera->getViewMatrix(), camera->getProjectionMatrix());
			physics.getDynamicsWorld()->debugDrawWorld();
			glEnable(GL_DEPTH_TEST);
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

	physics.CleanUp();

	objects.clear();
	meshes.clear();
	textures.clear();

	//Delete context
	SDL_GL_DeleteContext(glContext);

	//Destroy the window and quit SDL2, NB we should do this after all cleanup in this order!!!
	SDL_DestroyWindow(window);
	SDL_Quit();
}