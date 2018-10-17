#include "Camera.h"



Camera::Camera(float initFoV, float initNearClip, float initFarClip) 
{
	//Initialise variables
	position = glm::vec3(0, 6, -10);
	target = glm::vec3(0, 0, 1);
	upVector = glm::vec3(0, 1, 0);
	FoV = initFoV;
	nearClip = initNearClip;
	farClip = initFarClip;

	zAxis = glm::normalize(position - target);
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

	zAxis = glm::normalize(position - target);
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
		target, // + target,
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

void Camera::checkPitchConstraints()
{
	//Constrain upwards view
	if (pitch > 89.0f)
		pitch = 89.0f;

	//Constrain downwards view
	if (pitch < -89.0f)
		pitch = -89.0f;
}

void Camera::calculateCameraRotation()
{
	//glm::vec3 targetPos;
	glm::vec3 front;
	glm::vec3 tempTarget;

	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));





	//Might have to make a temp variable to then normalize into target
	//glm::vec3 tempTarget;

	tempTarget.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	tempTarget.y = sin(glm::radians(pitch));
	tempTarget.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	target = glm::normalize(tempTarget);

	//target = targetPos;
	setViewMatrix();
}
