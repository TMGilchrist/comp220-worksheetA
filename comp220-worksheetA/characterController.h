#pragma once
#include "inputManager.h"
#include "Camera.h"

class CharacterController
{
public:
	CharacterController();
	CharacterController(InputManager &Input, Camera Camera);
	~CharacterController();

	void control();

private:
	InputManager input;
	Camera attachedCamera; //Camera directly controlled

	glm::vec3 cameraPosition;
	glm::vec3 cameraTarget;
};

