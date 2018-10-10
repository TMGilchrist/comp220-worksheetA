#pragma once
#include <SDL.h>
#include <string>
#include "globals.h"

class Window
{
public:
	Window();

	Window(const char* title);

	~Window();

	int initSDL();
	int verifyWindow();

	SDL_Window* getWindow() 
	{
		return window;
	};

private:
	SDL_Window* window;


};

