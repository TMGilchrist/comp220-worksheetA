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
	windowMain = WindowManager("Shader Practice");
	window = windowMain.getWindow();

	//Initalise Open_GL and GLEW. Get Open_GL context.
	//glManager = GLManager(window);
	glManager.setWindow(window);
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
	//Testing an object. A lot of these functions should be handled by the init.
	newObject = Mesh();
	newObject.Init();
	//newObject.setTextureID("checkerboard.png");
	newObject.setTextureID("Resources/Tank1DF.PNG");
	newObject.BindTexure();
	newObject.FillBufferData(GeometryModels::cube, 8, GeometryModels::cubeIndices, 36);
	newObject.CalculateModelMatrix();


	//Load Mesh
	tankMesh = new MeshCollection();
	loadMeshFromFile("Resources/Tank1.FBX", tankMesh); //Need to move the mvp calculations into shaders.

	programID = LoadShaders("vertexTextured.glsl", "fragmentTextured.glsl");


	GLuint textureUniformLocation = glGetUniformLocation(programID, "textureSampler");
	GLuint modelMatrixLocation = glGetUniformLocation(programID, "modelMatrix");

	//Set up a camera and init the projection matrix with window size
	camera = new Camera();
	camera->setProjectionMatrix(windowMain.getWidth(), windowMain.getHeight());

	//Caluclate MVP
	//glm::mat4 MVP = camera->getProjectionMatrix() * camera->getViewMatrix() * newObject.getModelMatrix(); //modelMatrix;
	MVPLocation = glGetUniformLocation(programID, "MVP");


	//Set up new inputManager and PlayerController
	input = new InputManager();
	controller = CharacterController(input, camera);
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
					windowMain.toggleFullScreen();

					//Recalculate projection matrix with new screen size
					camera->setProjectionMatrix(windowMain.getWidth(), windowMain.getHeight());
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


		//glm::mat4 MVP = camera->getProjectionMatrix() * camera->getViewMatrix() * newObject.getModelMatrix();// modelMatrix;


		//OpenGL rendering
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Linking shaders
		glUseProgram(programID);


		/*---------------------
		Send Uniform Values
		----------------------*/

		//MVP matrix
		//glUniformMatrix4fv(MVPLocation, 1, false, &MVP[0][0]);



		/*----------------
		Drawing Objects
		------------------*/

		//newObject.Render();
		tankMesh->render();

		//Refresh screen
		SDL_GL_SwapWindow(window);
	}
}

void Game::Cleanup()
{
	/*--------------------
	   Cleanup
	--------------------*/

	glDeleteProgram(programID);

	//Delete context
	SDL_GL_DeleteContext(glContext);

	//Destroy the window and quit SDL2, NB we should do this after all cleanup in this order!!!
	SDL_DestroyWindow(window);
	SDL_Quit();

	//return 0;
}