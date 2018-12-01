/**
CharacterController

Moves a given camera based on inputs from an InputManager.
*/

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

	/**
	Processes keyboard input and determines effects.

	@param deltaTime : The game's deltaTime.
	*/
	void handleKeyboard(float deltaTime);

	/**
	Processes mouse input and determines effects.
	*/
	void handleMouse();

private:
	//Input source
	InputManager* input;

	//Camera being controlled by this controller
	Camera* attachedCamera;

	//Position and target of the attached camera
	glm::vec3 cameraPosition;
	glm::vec3 cameraTarget;

	//The movement speed of the character
	float moveSpeed;
};

