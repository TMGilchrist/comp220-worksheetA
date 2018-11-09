#pragma once
#include <SDL.h>
#include <string>
#include <SDL_opengl.h>
#include "globals.h"

class WindowManager
{
public:
	WindowManager();
	WindowManager(const char* title);
	WindowManager(const char* title, int Height, int Width);

	~WindowManager();

	//Initalise SDL ready for window creation
	int initSDL();

	//Verify that window has been created successfully
	int verifyWindow();

	//Toggle the state of the window between fullscreen and windowed
	void toggleFullScreen();

	//Toggled between maximised and non-maximised
	void toggleMaximised();


	SDL_Window* getWindow() 
	{
		return window;
	};

	int getFlags() 
	{
		return flags;
	}

	int getHeight() 
	{
		return height;
	}

	int getWidth() 
	{
		return width;
	}

private:
	//The application window
	SDL_Window* window;
	int height;
	int width;

	//Mask of the window's flags
	int flags;

	//Flags for screen state. Should have been able to use the flags above but didn't work for some reason.
	bool isFullscreen;
	bool isMaximised;


};

