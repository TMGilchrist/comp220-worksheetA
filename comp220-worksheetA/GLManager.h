#pragma once
#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>

class GLManager
{
public:
	GLManager(SDL_Window* window);
	~GLManager();

	//Create a new Open_GL context
	int CreateGLContext();

	//Initialise GLEW
	int initGLEW();

	//Set the version information for Open_GL
	void setGLVersion();

	SDL_GLContext getGLContext()
	{
		return glContext;
	}

private:
	SDL_GLContext glContext;
	SDL_Window* window;
};

