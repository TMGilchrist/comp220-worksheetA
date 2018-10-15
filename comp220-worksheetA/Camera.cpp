#include "Camera.h"



Camera::Camera(float initFoV, float initNearClip, float initFarClip) 
{
	//Initialise variables
	position = glm::vec3(8, 6, 4);
	target = glm::vec3(0, 0, 1);
	upVector = glm::vec3(0, 1, 0);
	FoV = initFoV;
	nearClip = initNearClip;
	farClip = initFarClip;

	xAxis = glm::normalize(glm::cross(upVector, zAxis));
	yAxis = glm::cross(zAxis, xAxis);

	//Generate matricies
	setViewMatrix();
	setProjectionMatrix();
}

Camera::Camera(glm::vec3 &Position, glm::vec3 &Target, glm::vec3 &UpVector, float initFoV, float initNearClip, float initFarClip)
{
	//Initialise variables
	position = Position;
	target = Target;
	upVector = UpVector;
	FoV = initFoV;
	nearClip = initNearClip;
	farClip = initFarClip;

	xAxis = glm::normalize(glm::cross(upVector, zAxis));
	yAxis = glm::cross(zAxis, xAxis);

	//Generate matricies
	setViewMatrix();
	setProjectionMatrix();
}


Camera::~Camera()
{
}

void Camera::setViewMatrix()
{
	viewMatrix = glm::lookAt
	(
		position,
		target, //position + target?
		upVector
	);
}

void Camera::setProjectionMatrix()
{
	projectionMatrix = glm::perspective
	(
		glm::radians(FoV),
		(float)global::SCREEN_HEIGHT / (float)global::SCREEN_WIDTH,   // Aspect Ratio
		nearClip,              
		farClip             
	);
}
