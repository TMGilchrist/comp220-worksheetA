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

	//Create game objects
	CreateObjects();

	//Setup lighting
	InitLighting();

	//Set up a camera and init the projection matrix with window size
	camera = new Camera();
	camera->setProjectionMatrix(windowMain->getWidth(), windowMain->getHeight());

	//Set up new inputManager and PlayerController
	input = new InputManager();
	controller = CharacterController(input, camera);
}

void Game::InitLighting()
{
	//Material
	ambientMaterialColour = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	diffuseMaterialColour = glm::vec4(0.8f, 0.0f, 0.0f, 1.0f);

	//Lighting
	lightDirection = glm::vec3(0.0f, 0.0f, 1.0f);
	ambientLightColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	diffuseLightColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	ambientIntensity = 0.3f;
	diffuseIntensity = 1.0f;
}

void Game::CreateObjects()
{
	/*---------------------
	Object creation
	---------------------*/

	//Create an objectBuilder class that loads all meshes and then assigns them to different objects.

	//Load Tank Mesh
	MeshCollection* tankMesh = new MeshCollection();
	loadMeshFromFile("Resources/Tank1.FBX", tankMesh); //Need to move the mvp calculations into shaders.
	GLuint tankTextureID = loadTextureFromFile("Resources/Tank1DF.PNG");

	//Load Teapot Mesh
	MeshCollection* teaPotMesh = new MeshCollection();
	loadMeshFromFile("Resources/teapot.FBX", teaPotMesh); //Need to move the mvp calculations into shaders.
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

		//Handle keyboard input
		controller.handleKeyboard(deltaTime);


		//OpenGL rendering
		glClearColor(0.0, 0.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	


		/*----------------
		Check vector of game objects   This should probably be changed to only update when the objects require updating.
		----------------*/

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
	diffuseIntensity = glGetUniformLocation(programID, "diffuseIntensity");

	//Textures
	textureUniformLocation = glGetUniformLocation(programID, "textureSampler");
}

void Game::SendUniforms(GameObject* object)
{
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
	glUniform1f(diffuseIntensityLocation, diffuseIntensity);
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