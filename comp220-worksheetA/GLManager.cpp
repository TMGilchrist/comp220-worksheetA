#include "GLManager.h"
#include <iostream>


GLManager::GLManager(SDL_Window* Window)
{
	//Get application window
	window = Window;

	//Setup Open_GL and GLEW
	setGLVersion();
	CreateGLContext();
	initGLEW();
	
}


GLManager::~GLManager()
{
}

int GLManager::CreateGLContext()
{
	//Create OPEN_GL context
	glContext = SDL_GL_CreateContext(window);
	if (glContext == nullptr)
	{
		//Show error
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "CreateContext failed", SDL_GetError(), NULL);

		SDL_DestroyWindow(window);
		SDL_Quit();

		return 1;
	}

	return 0;
}

int GLManager::initGLEW()
{
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
	SDL_GL_MakeCurrent(window, glContext);
	char * glVersion = (char*)glGetString(GL_VERSION);
	//glewGetString()
	std::cout << "GL Version " << glVersion << std::endl;
	//std::cout << "GL VERSION " << (char*)glGetString(GL_VERSION) << std::endl;
	//std::cout << "GL Vendor " << (char*)glGetString(GL_VENDOR) << std::endl;

	return 0;
}

void GLManager::setGLVersion()
{
	// Set our OpenGL version.
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);



}
