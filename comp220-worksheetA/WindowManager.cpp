#include "WindowManager.h"

//Make an init function!!
WindowManager::WindowManager()
{

}

WindowManager::~WindowManager()
{
	SDL_DestroyWindow(window);
	//SDL_Quit();
}

void WindowManager::Init(const char* title, int Width, int Height)
{
	//Init SDL
	initSDL();

	//Create a window, note we have to free the pointer returned using the DestroyWindow Function
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Width, Height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	//Verify that window is created.
	verifyWindow();

	//Allow window to be resized
	SDL_SetWindowResizable(window, SDL_TRUE);
	SDL_GetWindowSize(window, &width, &height); //Is this line necessary? Check this.

	//Store window flags and init required flags.
	flags = SDL_GetWindowFlags(window);
	isFullscreen = false;
	isMaximised = false;
}

int WindowManager::initSDL()
{
	//Initialises the SDL Library, passing in SDL_INIT_VIDEO to only initialise the video subsystems
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		//Display an error message box
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_Init failed", SDL_GetError(), NULL);
		return 1;
	}

	return 0;
}

int WindowManager::verifyWindow()
{
	//Checks to see if the window has been created, the pointer will have a value of some kind
	if (window == nullptr)
	{
		//Show error
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_CreateWindow failed", SDL_GetError(), NULL);

		//Close the SDL Library
		SDL_Quit();
		return 1;
	}

	return 0;
}

void WindowManager::toggleFullScreen()
{
	//Fullscreen
	if (isFullscreen == false) 
	{
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		SDL_GetWindowSize(window, &width, &height);
		glViewport(0, 0, width, height);
		isFullscreen = true;
	}

	//Windowed
	else 
	{
		SDL_SetWindowFullscreen(window, 0);
		SDL_GetWindowSize(window, &width, &height);
		glViewport(0, 0, width, height);
		isFullscreen = false;
	}
}

void WindowManager::toggleMaximised()
{
	//Maximise
	if (isMaximised == false)
	{
		SDL_MaximizeWindow(window);
		isMaximised = true;
	}

	//Restore
	else
	{
		SDL_RestoreWindow(window);
		isMaximised = false;
	}
}

