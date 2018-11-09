#pragma once
#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>

class GLManager
{
public:

	/**
	Default constructor for the GLManager. Doesn't set a window.*/
	GLManager();

	/**
	Create a manager to handle openGL and GLEW setup. 

	@param SDL_WINDOW* window: The SDL window to use during setup.
	*/
	GLManager(SDL_Window* window);
	~GLManager();

	/**
	Set openGl version, create a context and initialise GLEW.
	*/
	void Init();

	/**
	Create a new Open_GL context
	*/
	int CreateGLContext();

	/**
	Initialise GLEW
	*/
	int initGLEW();



	/**
	Set the version information for Open_GL
	*/
	void setGLVersion();

	void setWindow(SDL_Window* Window) 
	{
		window = Window;
	}

	/**
	Return the openGL context for the application
	@return SDL_GLContext GLContext: the context created for this application 
	*/
	SDL_GLContext getGLContext()
	{
		return glContext;
	}

private:
	SDL_GLContext glContext;
	SDL_Window* window;
};

