#pragma once
#include <SDL.h>
#include <map>

class inputManager
{
public:
	inputManager();
	~inputManager();

	//Populate map with events
	void manageKeyboardEvents(SDL_Event event)
	{
		keyStates[event.key.keysym.sym] = event.key.state;
	}

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


private:
	//Map containing the key, and its state (pressed/released)
	std::map<SDL_Keycode, Uint8> keyStates;
};

