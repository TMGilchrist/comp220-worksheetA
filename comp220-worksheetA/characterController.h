#pragma once
#include "inputManager.h"
#include "Camera.h"
#include "Vertex.h"
#include <iostream>


class CharacterController
{
public:
	CharacterController();
	CharacterController(InputManager* Input, Camera* Camera);
	~CharacterController();

	//Handle effects of keyboard input
	void handleKeyboard(float deltaTime);

	//Handle effects of mouse input
	void handleMouse();

private:
	InputManager* input;
	Camera* attachedCamera; //Camera directly controlled

	//Position and target of the attached camera
	glm::vec3 cameraPosition;
	glm::vec3 cameraTarget;

	//How fast the player can move
	float moveSpeed;
};

