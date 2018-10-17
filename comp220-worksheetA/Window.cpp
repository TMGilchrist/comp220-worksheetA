#include "Window.h"


	Window::Window()
	{
		initSDL();

		//Create a window, note we have to free the pointer returned using the DestroyWindow Function
		window = SDL_CreateWindow("SDL_Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, global::SCREEN_WIDTH, global::SCREEN_WIDTH, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

		verifyWindow();
		SDL_SetWindowResizable(window, SDL_TRUE);
		flags = SDL_GetWindowFlags(window);
	}

	Window::Window(const char* title)
	{
		initSDL();

		//Create a window, note we have to free the pointer returned using the DestroyWindow Function
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, global::SCREEN_WIDTH, global::SCREEN_WIDTH, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

		verifyWindow();
		SDL_SetWindowResizable(window, SDL_TRUE);
		flags = SDL_GetWindowFlags(window);
	}

	Window::~Window()
	{
		SDL_DestroyWindow(window);
		//SDL_Quit();
	}

	int Window::initSDL()
	{
		//Initialises the SDL Library, passing in SDL_INIT_VIDEO to only initialise the video subsystems
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			//Display an error message box
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_Init failed", SDL_GetError(), NULL);
			return 1;
		}
	}

	int Window::verifyWindow()
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
	}

