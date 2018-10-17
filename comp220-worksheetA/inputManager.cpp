#include "inputManager.h"


InputManager::InputManager() {}

InputManager::InputManager(Camera * Camera)
{
	//Init last mouse position to center of screen
	lastX = global::SCREEN_WIDTH / 2;
	lastY = global::SCREEN_HEIGHT / 2;

	mouseSensitivity = 0.01f;

	camera = Camera;
	firstMouse = true;
}

InputManager::~InputManager()
{
}

void InputManager::mouseInput(float xPos, float yPos)
{
	if (firstMouse) // this bool variable is initially set to true
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	//maybe calculate mouse offset using lastPos - currentPos?

	xOffset = xPos - lastX;
	yOffset = lastY - yPos;
	lastX = xPos;
	lastY = yPos;

	//Store mouse position
	xOffset = xPos * mouseSensitivity;
	yOffset = yPos * mouseSensitivity;

	/*
	//Update yaw and pitch of camera
	camera->increaseYaw(xOffset);
	camera->increasePitch(yOffset);

	//Ensure new pitch is not outside constraints
	camera->checkPitchConstraints();*/
}


