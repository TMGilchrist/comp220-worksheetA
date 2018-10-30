#include "inputManager.h"


InputManager::InputManager() 
{
	mouseSensitivity = 0.05f;	
}

InputManager::InputManager(Camera * Camera)
{
	mouseSensitivity = 0.05f;
	camera = Camera;
}

InputManager::~InputManager()
{
}

void InputManager::mouseInput(float xPos, float yPos)
{
	//Store mouse position
	xOffset = xPos * mouseSensitivity;
	yOffset = yPos * mouseSensitivity;
}


