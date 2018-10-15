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

	void control(float deltaTime);

private:
	InputManager* input;
	Camera* attachedCamera; //Camera directly controlled

	glm::vec3 cameraPosition;
	glm::vec3 cameraTarget;

	float movespeed;
};

