#include "characterController.h"



CharacterController::CharacterController()
{
}

CharacterController::CharacterController(InputManager* Input, Camera* Camera)
{
	input = Input;
	attachedCamera = Camera;

	cameraPosition = attachedCamera->getPosition();
	cameraTarget = attachedCamera->getTarget();

	movespeed = 0.05f;
}


CharacterController::~CharacterController()
{
}

void CharacterController::control()
{
	cameraPosition = attachedCamera->getPosition();
	cameraTarget = attachedCamera->getTarget();


	//Check inputs.
	if (input->isPressed(SDLK_w))
	{
		attachedCamera->setPosition(cameraPosition + (movespeed * cameraTarget));
		attachedCamera->setViewMatrix();
	}

	if (input->isPressed(SDLK_a))
	{
		attachedCamera->setPosition(cameraPosition - (glm::normalize(glm::cross(cameraTarget, attachedCamera->getUpVector())) * movespeed));
		attachedCamera->setViewMatrix();
	}

	if (input->isPressed(SDLK_s))
	{
		attachedCamera->setPosition(cameraPosition - (movespeed * cameraTarget));
		attachedCamera->setViewMatrix();
	}

	if (input->isPressed(SDLK_d))
	{
		attachedCamera->setPosition(cameraPosition + (glm::normalize(glm::cross(cameraTarget, attachedCamera->getUpVector())) * movespeed));
		attachedCamera->setViewMatrix();
	}

	/*
	//Check inputs.
	if (input.isPressed(SDLK_w))
	{	
		std::cout << "W pressed";
		attachedCamera.setPosition(cameraPosition + (movespeed * cameraTarget));
		//attachedCamera.setPosition(glm::vec3(cameraPosition.x + 1, cameraPosition.y, cameraPosition.z));
	}

	if (input.isPressed(SDLK_a))
	{		
		attachedCamera.setPosition(cameraPosition - (glm::normalize(glm::cross(cameraTarget, attachedCamera.getUpVector())) * movespeed));
	}

	if (input.isPressed(SDLK_s))
	{		
		attachedCamera.setPosition(cameraPosition - (movespeed * cameraTarget));
	}

	if (input.isPressed(SDLK_d))
	{		
		attachedCamera.setPosition(cameraPosition + (glm::normalize(glm::cross(cameraTarget, attachedCamera.getUpVector())) * movespeed));
	}*/
}
