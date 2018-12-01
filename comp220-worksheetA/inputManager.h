/**
InputManager

Get the state of the keyboard and mouse and store this data for use by a CharacterController.
*/

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

	/**
	Populate map with keyboard events

	@param event : The SDL event being raised.
	*/
	void manageKeyboardEvents(SDL_Event event)
	{
		keyStates[event.key.keysym.sym] = event.key.state;
	}

	/**
	Stores position of the mouse accounting for sensitivty value.

	@param xPos : The X position of the mouse cursor.
	@param yPos @ The Y position of the mouse cursor.
	*/
	void mouseInput(float xPos, float yPos);

	/**
	Clear map of events
	*/
	void clearEvents()
	{
		keyStates.clear();
	}

	/**
	Check if key is released.

	@param key : The key being checked.
	*/
	bool isReleased(SDL_Keycode key)
	{
		return keyStates[key] == SDL_RELEASED;
	}

	/**
	Check if key is pressed.

	@param key : The key being checked.
	*/
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

