/**
WindowManager

Handles the initialistion of SDL and it's required components as well as the creation of the SDL window for the game.
*/

#pragma once
#include <SDL.h>
#include <string>
#include <SDL_opengl.h>
#include "globals.h"

class WindowManager
{
public:
	WindowManager();
	~WindowManager();

	/**
	Calls InitSDL and creates an SDL window.

	@param title : The title of the SDL window.
	@param Width : The width of the SDL window.
	@param Height : The height of the SDL window.
	*/
	void Init(const char* title="Default Window", int Width = global::SCREEN_WIDTH, int Height = global::SCREEN_HEIGHT);

	/**
	Initalise SDL ready for window creation
	*/
	int initSDL();

	/**
	Verify that window has been created successfully
	*/
	int verifyWindow();

	/**
	Toggle the state of the window between fullscreen and windowed
	*/
	void toggleFullScreen();

	/**
	Toggled between maximised and non-maximised
	*/
	void toggleMaximised();


	/*----------------------
	Getters and Setters
	----------------------*/

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

