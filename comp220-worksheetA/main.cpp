#include "main.h"
#include <iostream>


int main(int argc, char ** argsv)
{
	//SDL window init stuff. Move to seperate function/class

	//Initialises the SDL Library, passing in SDL_INIT_VIDEO to only initialise the video subsystems
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		//Display an error message box
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_Init failed", SDL_GetError(), NULL);
		return 1;
	}

	//Create a window, note we have to free the pointer returned using the DestroyWindow Function
	SDL_Window* window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 640, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	//Checks to see if the window has been created, the pointer will have a value of some kind
	if (window == nullptr)
	{
		//Show error
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_CreateWindow failed", SDL_GetError(), NULL);

		//Close the SDL Library
		SDL_Quit();
		return 1;
	}


	//Create OPEN_GL context
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	if (glContext == nullptr)
	{
		//Show error
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "CreateContext failed", SDL_GetError(), NULL);

		SDL_DestroyWindow(window);
		SDL_Quit();

		return 1;
	}

	//Init GLEW
	glewExperimental = GL_TRUE;
	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		//Show error
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "GLEW initilisation failed", (char*)glewGetErrorString(error), NULL);

		SDL_DestroyWindow(window);
		SDL_Quit();

		return 1;
	}


	// Set our OpenGL version.
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);


	//Vertex array
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// An array of 3 vectors which represents 3 vertices
	static const GLfloat g_vertex_buffer_data[] = 
	{
	   -0.5f, -0.5f, 0.0f,
	   0.5f, -0.5f, 0.0f,
	   0.0f,  0.5f, 0.0f,
	};


	// This will identify our vertex buffer
	GLuint vertexbuffer;
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	GLuint programID = LoadShaders("vertexShader.glsl", "fragmentShader.glsl");
	GLuint colour1Location = glGetUniformLocation(programID, "triangleColour1");
	GLuint colour2Location = glGetUniformLocation(programID, "triangleColour2");


	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);

	glm::mat4 modelMatrix = glm::translate(position);

	GLuint modelMatrixLocation = glGetUniformLocation(programID, "modelMatrix");


	//Event loop, we will loop until running is set to false, usually if escape has been pressed or window is closed
	bool running = true;

	//SDL Event structure, this will be checked in the while loop
	SDL_Event ev;

	while (running)
	{
		//Poll for the events which have happened in this frame
		while (SDL_PollEvent(&ev))
		{
			//Switch case for every message we are intereted in
			switch (ev.type)
			{
				//QUIT Message, usually called when the window has been closed
				case SDL_QUIT:
					running = false;
					break;

				//KEYDOWN Message, called when a key has been pressed down
				case SDL_KEYDOWN:

					//Check the actual key code of the key that has been pressed
					switch (ev.key.keysym.sym)
					{
						//Escape key
						case SDLK_ESCAPE:
							running = false;
							break;
					}
			}
		}


		//OpenGL rendering
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);


		//Linking shaders
		glUseProgram(programID);


		// 1st attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

		glVertexAttribPointer
		(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);


		//Apply transformations
		glUniformMatrix4fv(modelMatrixLocation, 1, false, glm::value_ptr(modelMatrix));

		//Set triangle colour
		glUniform4f(colour1Location, 0, 0, 1, 0);
		glUniform4f(colour2Location, 1, 0, 0, 0);

		// Draw the triangle
		glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
		glDisableVertexAttribArray(0);


		
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