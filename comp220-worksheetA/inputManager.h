#pragma once
#include <SDL.h>
#include <map>
#include <iostream>

#include "globals.h"
#include "Camera.h"

class InputManager
{
public:
	InputManager();
	InputManager(Camera * Camera);

	~InputManager();

	//Populate map with keyboard events
	void manageKeyboardEvents(SDL_Event event)
	{
		keyStates[event.key.keysym.sym] = event.key.state;
	}

	//Handle mouse input (change camera yaw/pitch)
	void mouseInput(float xPos, float yPos);

	//Clear map of events
	void clearEvents()
	{
		keyStates.clear();
	}

	//Check if key is released
	bool isReleased(SDL_Keycode key)
	{
		return keyStates[key] == SDL_RELEASED;
	}

	//Check if key is pressed
	bool isPressed(SDL_Keycode key)
	{
		return keyStates[key] == SDL_PRESSED;
	}

	
	float getYOffset() 
	{
		return yOffset;
	}

	float getXOffset() 
	{
		return xOffset;
	}

private:
	//Map containing the key, and its state (pressed/released)
	std::map<SDL_Keycode, Uint8> keyStates;
	Camera* camera;

	float mouseSensitivity;

	//The cursor offsets (possibly redundant since SDL gives relative mouse offset?)
	float xOffset;
	float yOffset;
};

