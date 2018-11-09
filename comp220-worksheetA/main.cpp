#include "main.h"
#include <iostream>

/*Probably want to make a Game class to keep main neat*/


int main(int argc, char ** argsv)
{
	//Create SDL window
	WindowManager windowMain = WindowManager("Shader Practice");
	SDL_Window* window = windowMain.getWindow();

	//Initalise Open_GL and GLEW. Get Open_GL context.
	GLManager glManager = GLManager(window);
	glManager.Init();
	SDL_GLContext glContext = glManager.getGLContext();
	
	//Mouse setup, can probably be moved to sdl init?
	SDL_ShowCursor(0);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	
	//Init deltaTime
	float deltaTime = 0.0f;	// Time between current frame and last frame
	float lastFrame = 0.0f; // Time of last frame

	   
	//Testing an object. A lot of these functions should be handled by the init.
	/*
	Mesh newObject = Mesh();
	newObject.Init();
	//newObject.setTextureID("checkerboard.png");
	newObject.setTextureID("Resources/Tank1DF.PNG");
	newObject.BindTexure();
	newObject.FillBufferData(GeometryModels::cube, 8, GeometryModels::cubeIndices, 36);
	newObject.CalculateModelMatrix();*/


	//Enable backface culling. Not all faces are properly rotated :c
	//glEnable(GL_CULL_FACE); 


	//Load Mesh
	MeshCollection* tankMesh = new MeshCollection();
	loadMeshFromFile("Resources/Tank1.FBX", tankMesh); //Need to move the mvp calculations into shaders.
	GLuint TextureID = loadTextureFromFile("Resources/Tank1DF.PNG");

	//Create new objects
	GameObject* tank1 = new GameObject();
	GameObject* tank2 = new GameObject();

	tank1->Init();
	tank2->Init();

	tank2->setTranslation(glm::vec3(5.0, 0.0, 0.0));

	//Set object meshes
	tank1->setMesh(tankMesh);
	tank2->setMesh(tankMesh);

	//Add objects to vector of game objects
	std::vector<GameObject*> objects;
	objects.push_back(tank1);
	objects.push_back(tank2);
	
	//Set programID
	GLuint programID = LoadShaders("vertexTextured.glsl", "fragmentTextured.glsl");

	//Set uniform locations
	GLuint textureUniformLocation = glGetUniformLocation(programID, "textureSampler");
	GLuint modelMatrixLocation = glGetUniformLocation(programID, "modelMatrix");
	GLuint viewMatrixLocation = glGetUniformLocation(programID, "viewMatrix");
	GLuint projectionMatrixLocation = glGetUniformLocation(programID, "projectionMatrix");

	//Set up a camera and init the projection matrix with window size
	Camera* camera = new Camera();
	camera->setProjectionMatrix(windowMain.getWidth(), windowMain.getHeight());

	//Caluclate MVP
	//glm::mat4 MVP = camera->getProjectionMatrix() * camera->getViewMatrix() * newObject.getModelMatrix(); //modelMatrix;
	GLuint MVPLocation = glGetUniformLocation(programID, "MVP");


	//Set up new inputManager and PlayerController
	InputManager* input = new InputManager();
	CharacterController controller = CharacterController(input, camera);


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
		glClearColor(0.0, 0.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
			   
		//Linking shaders
		glUseProgram(programID);
			   

		/*---------------------
		Send Uniform Values
		----------------------*/

		//MVP matrix
		//glUniformMatrix4fv(MVPLocation, 1, false, &MVP[0][0]);

		glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));
		glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(camera->getProjectionMatrix()));
		//glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(tank1->getModelMatrix()));

		/*----------------
		Check vector of game objects
		----------------*/
		//tank1->Update();
				
		for (GameObject* object : objects) 
		{
			glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(object->getModelMatrix()));
			object->Update();
		}


		/*----------------
		Drawing Objects
		------------------*/

		//newObject.Render();
		//tankMesh->render();

		//Refresh screen
		SDL_GL_SwapWindow(window);
	}


	/*--------------------
		   Cleanup
	--------------------*/

	glDeleteProgram(programID);

	//Delete context
	SDL_GL_DeleteContext(glContext);

	//Destroy the window and quit SDL2, NB we should do this after all cleanup in this order!!!
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

int main1(int argc, char ** argsv) 
{
	Game game = Game();
	game.Init();
	//game.Setup();
	//game.GameLoop();
	//game.Cleanup();

	return 0;
}