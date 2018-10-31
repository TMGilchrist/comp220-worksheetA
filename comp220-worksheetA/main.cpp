#include "main.h"
#include <iostream>

/*Probably want to make a Game class to keep main neat*/

int main(int argc, char ** argsv)
{
	//Create SDL window
	Window windowMain = Window("Shader Practice");
	SDL_Window* window = windowMain.getWindow();

	//Initalise Open_GL and GLEW. Get Open_GL context.
	GLManager glManager = GLManager(window);
	SDL_GLContext glContext = glManager.getGLContext();
	
	//Mouse setup, can probably be moved to sdl init?
	SDL_ShowCursor(0);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	
	//Init deltaTime
	float deltaTime = 0.0f;	// Time between current frame and last frame
	float lastFrame = 0.0f; // Time of last frame


	/*-----------------
	  Vertex Arrays
	-----------------*/

	// An array of 3 vectors which represents 3 vertices
	//{x, y, z, r, g, b, a}
	static const Vertex triangle[] =
	{
		{-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f},
		{0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f},
		{0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f},
	};

	//Define square verticies
	//{x, y, z, r, g, b, a, tu, tv}
	static const Vertex square[] =
	{
		{-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
		{0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f},
		{0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f},
		{-0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f}
	};

	//Cube
	//{x, y, z, r, g, b, a, tu, tv}
	static const Vertex saneCube[]=
	{
		//Top four vertices
		{0, 1, 1, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f}, //0
		{0, 0, 1, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f},  //1
		{1, 0, 1, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f},  //2
		{1, 1, 1, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f},  //3

		//Bottom four vertices
		{0, 0, 0, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f},  //4
		{0, 1, 0, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f},  //5
		{1, 1, 0, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f},  //6
		{1, 0, 0, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f}   //7
	};

	//Define triangles in the cube
	static const int indices[] =
	{
		1, 0 , 4,
		4, 0, 5, 

		7, 2, 1, 
		7, 1, 4,

		1, 2, 3,
		1, 3, 0, 

		5, 0, 3, 
		5, 3, 6, 

		6, 3, 7, 
		7, 3, 2, 

		7, 4, 5, 
		7, 5, 6
	};

	static const int squareIndices[] =
	{
		0,1,2,
		2,0,3
	};


	/* The following buffer code should be moved to an Object or Model class so that each object can track it's own buffer. */

	//Cube	
	// This will identify our vertex buffer
	GLuint vertexBuffer;
	// Generate 1 buffer, put the resulting identifier in vertexBuffer
	glGenBuffers(1, &vertexBuffer);
	// The following commands will talk about our 'vertexBuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(Vertex), saneCube, GL_STATIC_DRAW);

	//Create element buffer
	GLuint elementBuffer;
	glGenBuffers(1, &elementBuffer);
	//Bind element buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(Vertex), indices, GL_STATIC_DRAW);

	/*
	//Square
	// This will identify our vertex buffer
	GLuint vertexBuffer;
	// Generate 1 buffer, put the resulting identifier in vertexBuffer
	glGenBuffers(1, &vertexBuffer);
	// The following commands will talk about our 'vertexBuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex), square, GL_STATIC_DRAW);

	//Create element buffer
	GLuint elementBuffer;
	glGenBuffers(1, &elementBuffer);
	//Bind element buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(Vertex), squareIndices, GL_STATIC_DRAW);
	*/

	//Enable backface culling. Not all faces are properly rotated :c
	glEnable(GL_CULL_FACE); 


	//unsigned int numberOfVerts = 0;
	//unsigned int numberOfIndices = 0;

	//loadModelFromFile("", vertexBuffer, elementBuffer, numberOfVerts, numberOfIndices);


	GLuint textureID = loadTextureFromFile("checkerboard.png");
	GLuint programID = LoadShaders("vertexTextured.glsl", "fragmentTextured.glsl");
	//GLuint programID = LoadShaders("vertexShader.glsl", "fragmentShader.glsl"); //NonTexturedShaders

	GLuint colour1Location = glGetUniformLocation(programID, "triangleColour1");
	GLuint colour2Location = glGetUniformLocation(programID, "triangleColour2");

	GLuint textureUniformLocation = glGetUniformLocation(programID, "textureSampler");



	/* ModelMatrix setup. This should be moved into Object class later. 
	   Also should encapuslate some of these in functions */

	//Translation and scale
	glm::vec3 modelTranslation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 modelScale = glm::vec3(1.0f, 1.0f, 1.0f);

	//Rotation
	glm::vec3 modelRotation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 xAxis = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 yAxis = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 zAxis = glm::vec3(0.0f, 0.0f, 1.0f);

	//Transformation Matricies
	glm::mat4 translationMatrix = glm::translate(modelTranslation);
	glm::mat4 rotationMatrix = glm::rotate(modelRotation.x, xAxis) * glm::rotate(modelRotation.y, yAxis) * glm::rotate(modelRotation.z, zAxis);
	glm::mat4 scaleMatrix = glm::scale(modelScale);

	//Caluclate modelMatrix
	glm::mat4 modelMatrix = rotationMatrix * scaleMatrix * translationMatrix;

	GLuint modelMatrixLocation = glGetUniformLocation(programID, "modelMatrix");

	//Set up a camera and init the projection matrix with window size
	Camera* camera = new Camera();
	camera->setProjectionMatrix(windowMain.getWidth(), windowMain.getHeight());

	//Caluclate MVP
	glm::mat4 MVP = camera->getProjectionMatrix() * camera->getViewMatrix() * modelMatrix;

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

					//std::cout << "  <" << event.motion.xrel << " : " << event.motion.yrel << ">  ";
					controller.handleMouse();
					break;
				
				case SDL_WINDOWEVENT:
					//Check for window being resized
					if (event.window.event == SDL_WINDOWEVENT_RESIZED) 
					{
						//Update size of screen variables <- needed for mouse calculations
					}
					break;
			}
		}



		//Update deltatime
		float currentFrame = SDL_GetTicks();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		
		//Handle keyboard input
		controller.handleKeyboard(deltaTime);


		glm::mat4 MVP = camera->getProjectionMatrix() * camera->getViewMatrix() * modelMatrix;


		//OpenGL rendering
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);



		//Linking shaders
		glUseProgram(programID);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID);

		//if we want another texture do the following:
		//glActiveTexture(GL_Texture1);
		//glBindTexture(GL_TEXTURE_2D, anotherTextureID);

		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);


		/*---------------------
		Set vertex Atrributes
		---------------------*/

		//1st attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glVertexAttribPointer
		(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			sizeof(Vertex),     // stride
			(void*)0            // array buffer offset
		);

		//2nd attribute buffer : colour
		glEnableVertexAttribArray(1);
		glVertexAttribPointer
		(
			1,
			4,
			GL_FLOAT,
			GL_FALSE,
			sizeof(Vertex),
			(void*)(3 * sizeof(float))
		);

		//3rd attribute buffer : UV coordinates
		glEnableVertexAttribArray(2);
		glVertexAttribPointer
		(
			2,
			2,
			GL_FLOAT,
			GL_FALSE,
			sizeof(Vertex),
			(void*)(7 * sizeof(float))
		);


		/*---------------------
		Send Uniform Values
		----------------------*/

		//MVP matrix
		glUniformMatrix4fv(MVPLocation, 1, false, &MVP[0][0]);

		//Set triangle colour
		glUniform4f(colour1Location, 0, 0, 1, 0);
		glUniform4f(colour2Location, 1, 0, 0, 0);
		glUniform1i(textureUniformLocation, 0);


		/*----------------
		Drawing Objects
		------------------*/

		//Draw square
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glDisableVertexAttribArray(0);

		//Draw Cube
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glDisableVertexAttribArray(0);


		//Refresh screen
		SDL_GL_SwapWindow(window);

	}


	/*--------------------
		   Cleanup
	--------------------*/

	glDeleteProgram(programID);
	glDeleteBuffers(1, &vertexBuffer);

	glDeleteBuffers(1, &elementBuffer);
	glDeleteTextures(1, &textureID);

	//Delete context
	SDL_GL_DeleteContext(glContext);

	//Destroy the window and quit SDL2, NB we should do this after all cleanup in this order!!!
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}