#include "main.h"
#include <iostream>


int main(int argc, char ** argsv)
{
	//Create SDL window
	Window windowMain = Window("Shader Practice");
	SDL_Window* window = windowMain.getWindow();

	//Initalise Open_GL and GLEW. Get Open_GL context.
	GLManager glManager = GLManager(window);
	SDL_GLContext glContext = glManager.getGLContext();


	//Vertex array
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	/*
	// An array of 3 vectors which represents 3 vertices
	static const GLfloat g_vertex_buffer_data[] = 
	{
	   -0.5f, -0.5f, 0.0f,
	   0.5f, -0.5f, 0.0f,
	   0.0f,  0.5f, 0.0f,
	};*/

	/*
	// This will identify our vertex buffer
	GLuint vertexbuffer;
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	*/

	// An array of 3 vectors which represents 3 vertices
	//{x, y, z, r, g, b, a}
	static const Vertex v[] =
	{
		{-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f},
		{0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f},
		{0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f},
	};


	// This will identify our vertex buffer
	GLuint vertexbuffer;
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(Vertex), v, GL_STATIC_DRAW);


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
	Camera camera = Camera();
	glm::mat4 MVP = camera.getProjectionMatrix() * camera.getViewMatrix() * modelMatrix;

	GLuint MVPLocation = glGetUniformLocation(programID, "MVP");


	/*----------------------
	      Main Game Loop
	------------------------*/

	//Event loop, we will loop until running is set to false
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


		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

		// 1st attribute buffer : vertices
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

		/*
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
		*/

		/*---------------------
		Send Uniform Values
		----------------------*/

		//MVP matrix
		glUniformMatrix4fv(MVPLocation, 1, false, &MVP[0][0]);

		//Set triangle colour
		glUniform4f(colour1Location, 0, 0, 1, 0);
		glUniform4f(colour2Location, 1, 0, 0, 0);


		// Draw the triangle
		glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
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