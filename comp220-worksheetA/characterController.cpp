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

}


CharacterController::~CharacterController()
{
}

void CharacterController::handleKeyboard(float deltaTime)
{
	cameraPosition = attachedCamera->getPosition();
	cameraTarget = attachedCamera->getTarget();
	movespeed = 0.05f * deltaTime;

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
}

void CharacterController::handleMouse()
{
	//Update yaw and pitch of camera
	attachedCamera->increaseYaw(input->getXOffset());
	attachedCamera->increasePitch(input->getYOffset());

	//Ensure new pitch is not outside constraints
	attachedCamera->checkPitchConstraints();

	//Calculate new rotation
	attachedCamera->calculateCameraRotation();
}
