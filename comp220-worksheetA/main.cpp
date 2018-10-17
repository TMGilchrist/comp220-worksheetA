#include "main.h"
#include <iostream>


int main(int argc, char ** argsv)
{
	//Create SDL window
	Window windowMain = Window("Shader Practice");
	SDL_Window* window = windowMain.getWindow();
	//SDL_SetWindowResizable(window, SDL_TRUE);

	//Initalise Open_GL and GLEW. Get Open_GL context.
	GLManager glManager = GLManager(window);
	SDL_GLContext glContext = glManager.getGLContext();


	//Vertex array
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	//Mouse setup, can probably be moved to sdl init?
	SDL_ShowCursor(0);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	
	//Init deltaTime
	float deltaTime = 0.0f;	// Time between current frame and last frame
	float lastFrame = 0.0f; // Time of last frame


	// An array of 3 vectors which represents 3 vertices
	//{x, y, z, r, g, b, a}
	static const Vertex v[] =
	{
		{-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f},
		{0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f},
		{0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f},
	};

	//Define square verticies
	static const Vertex square[] =
	{
		{-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f},
		{0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f},
		{0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f},
		{-0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f}
	};

	static const Vertex saneCube[]=
	{
		//Top four vertices
		{0, 1, 1, 1.0f, 0.0f, 0.0f, 1.0f }, //0
		{0, 0, 1, 1.0f, 0.0f, 0.0f, 1.0f},  //1
		{1, 0, 1, 1.0f, 0.0f, 0.0f, 1.0f},  //2
		{1, 1, 1, 1.0f, 0.0f, 0.0f, 1.0f},  //3

		//Bottom four vertices
		{0, 0, 0, 1.0f, 0.0f, 0.0f, 1.0f},  //4
		{0, 1, 0, 1.0f, 0.0f, 0.0f, 1.0f},  //5
		{1, 1, 0, 1.0f, 0.0f, 0.0f, 1.0f},  //6
		{1, 0, 0, 1.0f, 0.0f, 0.0f, 1.0f}   //7
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


	// This will identify our vertex buffer
	GLuint vertexbuffer;
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(Vertex), saneCube, GL_STATIC_DRAW);

	//Create element buffer
	GLuint elementBuffer;
	glGenBuffers(1, &elementBuffer);
	//Bind element buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(Vertex), indices, GL_STATIC_DRAW);

	//Enable backface culling. Not all faces are properly rotated :c
	glEnable(GL_CULL_FACE); 

	GLuint programID = LoadShaders("vertexShader.glsl", "fragmentShader.glsl");
	GLuint colour1Location = glGetUniformLocation(programID, "triangleColour1");
	GLuint colour2Location = glGetUniformLocation(programID, "triangleColour2");



	/* ModelMatrix setup. This should be moved into gameloop later 
	   so that model can be moved in game. */

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



	//Create camera and calculate MVP matrix
	//Camera camera = Camera();
	//glm::mat4 MVP = camera.getProjectionMatrix() * camera.getViewMatrix() * modelMatrix;

	Camera* camera = new Camera();
	glm::mat4 MVP = camera->getProjectionMatrix() * camera->getViewMatrix() * modelMatrix;

	GLuint MVPLocation = glGetUniformLocation(programID, "MVP");

	InputManager* input = new InputManager();
	CharacterController controller = CharacterController(input, camera);

	/*----------------------
	      Main Game Loop
	------------------------*/

	//Event loop, we will loop until running is set to false
	bool gameRunning = true;

	//SDL Event structure, this will be checked in the while loop
	SDL_Event event;

	while (gameRunning)
	{
		//Poll for the events which have happened in this frame
		while (SDL_PollEvent(&event))
		{
			//Switch case for every message we are intereted in
			switch (event.type)
			{
				//QUIT Message, usually called when the window has been closed
				case SDL_QUIT:
					gameRunning = false;
					break;

				case SDL_KEYDOWN:
					//Update inputManager
					input->manageKeyboardEvents(event);

					//Check individual keys by code
					switch (event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							gameRunning = false;
							break;
					}

				case SDL_KEYUP:
					//Update inputManager
					input->manageKeyboardEvents(event);
					break;

				case SDL_MOUSEMOTION:
					//Pass location to inputManager
					std::cout << event.motion.x << " : " << event.motion.y;
					input->mouseInput(event.motion.xrel, event.motion.yrel);
					controller.handleMouse();
					break;
				
				case SDL_WINDOWEVENT:
					//Check for window being resized
					if (event.window.event == SDL_WINDOWEVENT_RESIZED) 
					{
						//Global screen size needs to be updated here
						//SDL_GetWindowSize(window); //Needs to be passed a pointer for screen height and width to fill.
					}
					break;
			}
		}



		//Update deltatime
		float currentFrame = SDL_GetTicks();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		
		//Handle keyboard input
		controller.control(deltaTime);


		if (windowMain.getFlags() & SDL_WINDOW_MOUSE_FOCUS)
		{
			//Reset cursor to center of screen
			SDL_WarpMouseInWindow(window, (global::SCREEN_WIDTH / 2), (global::SCREEN_HEIGHT / 2));
		}

		//std::cout << camera->getPosition().x << camera->getPosition().y << camera->getPosition().z;

		glm::mat4 MVP = camera->getProjectionMatrix() * camera->getViewMatrix() * modelMatrix;


		//OpenGL rendering
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);


		//Linking shaders
		glUseProgram(programID);


		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);

		//1st attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glVertexAttribPointer
		(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			sizeof(Vertex),                  // stride
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


		/*---------------------
		Send Uniform Values
		----------------------*/

		//MVP matrix
		glUniformMatrix4fv(MVPLocation, 1, false, &MVP[0][0]);

		//Set triangle colour
		glUniform4f(colour1Location, 0, 0, 1, 0);
		glUniform4f(colour2Location, 1, 0, 0, 0);


		// Draw the triangle
		//glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle

		//Draw cube
		//glDrawArrays(GL_TRIANGLES, 0, 36);

		//Draw Square
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glDisableVertexAttribArray(0);


		//Refresh screen
		SDL_GL_SwapWindow(window);

	}


	/*--------------------
		   Cleanup
	--------------------*/

	glDeleteProgram(programID);
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);

	//Delete context
	SDL_GL_DeleteContext(glContext);

	//Destroy the window and quit SDL2, NB we should do this after all cleanup in this order!!!
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}