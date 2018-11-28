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
	moveSpeed = 0.05f * deltaTime;

	bool debugSpeedEnabled = false;

	//This isn't multi-directional movement, this should be fixed!

	//Debug speed increase
	if (input->isPressed(SDLK_LSHIFT))
	{

		if (debugSpeedEnabled == false) 
		{
			moveSpeed = 0.5f * deltaTime;
			debugSpeedEnabled == true;
		}

		else
		{
			moveSpeed = 0.05f * deltaTime;
			debugSpeedEnabled = false;
		}

	}

	//Strafe forwards
	if (input->isPressed(SDLK_w))
	{
		attachedCamera->setPosition(cameraPosition + (moveSpeed * cameraTarget));
		attachedCamera->setViewMatrix();
	}

	//Strafe left
	if (input->isPressed(SDLK_a))
	{
		attachedCamera->setPosition(cameraPosition - (glm::normalize(glm::cross(cameraTarget, attachedCamera->getUpVector())) * moveSpeed));
		attachedCamera->setViewMatrix();
	}

	//Strafe backwards
	if (input->isPressed(SDLK_s))
	{
		attachedCamera->setPosition(cameraPosition - (moveSpeed * cameraTarget));
		attachedCamera->setViewMatrix();
	}

	//Strafe right
	if (input->isPressed(SDLK_d))
	{
		attachedCamera->setPosition(cameraPosition + (glm::normalize(glm::cross(cameraTarget, attachedCamera->getUpVector())) * moveSpeed));
		attachedCamera->setViewMatrix();
	}

	// Strafe up
	if (input->isPressed(SDLK_SPACE))
	{
		attachedCamera->setPosition(cameraPosition + (glm::vec3(0, 1, 0) * moveSpeed));
		attachedCamera->setViewMatrix();
	}

	// Strafe down
	if (input->isPressed(SDLK_LCTRL))
	{
		attachedCamera->setPosition(cameraPosition + (glm::vec3(0, -1, 0) * moveSpeed));
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
