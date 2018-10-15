#include "characterController.h"



CharacterController::CharacterController()
{
}

CharacterController::CharacterController(InputManager &Input, Camera Camera)
{
	input = Input;
	attachedCamera = Camera;

	cameraPosition = attachedCamera.getPosition();
	cameraTarget = attachedCamera.getTarget();
}


CharacterController::~CharacterController()
{
}

void CharacterController::control()
{
	cameraPosition = attachedCamera.getPosition();
	cameraTarget = attachedCamera.getTarget();

	//Check inputs.
	if (input.isPressed(SDLK_w))
	{	
		
		attachedCamera.setPosition(glm::vec3(cameraPosition.x + 1, cameraPosition.y, cameraPosition.z));
	}

	if (input.isPressed(SDLK_a))
	{		
	}

	if (input.isPressed(SDLK_s))
	{		
	}

	if (input.isPressed(SDLK_d))
	{		
	}
}
