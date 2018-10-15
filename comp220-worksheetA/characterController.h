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

	void control();

private:
	InputManager* input;
	Camera* attachedCamera; //Camera directly controlled

	glm::vec3 cameraPosition;
	glm::vec3 cameraTarget;

	float movespeed;

	/*
	// position
	//glm::vec3 position = glm::vec3(0, 0, 5);

	// horizontal angle : toward -Z
	// vertical angle : 0, look at the horizon
	float horizontalAngle = 3.14f;
	float verticalAngle = 0.0f;
	
	// Initial Field of View
	float initialFoV = 45.0f;

	float speed = 3.0f; // 3 units / second
	float mouseSpeed = 0.005f;
	*/

	//Vertex object[];
};

