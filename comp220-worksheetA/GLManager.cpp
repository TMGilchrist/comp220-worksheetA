#include "GLManager.h"
#include <iostream>



GLManager::GLManager()
{
}

GLManager::GLManager(SDL_Window* Window)
{
	//Get application window
	window = Window;
}


GLManager::~GLManager()
{
}

void GLManager::Init()
{
	//Setup Open_GL and GLEW
	setGLVersion();
	CreateGLContext();
	initGLEW();
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

	//Output gl version
	SDL_GL_MakeCurrent(window, glContext);
	char * glVersion = (char*)glGetString(GL_VERSION);
	std::cout << "GL Version " << glVersion << std::endl;

	return 0;
}

void GLManager::setGLVersion()
{
	// Set our OpenGL version.
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
}
