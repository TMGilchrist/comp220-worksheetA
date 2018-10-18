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
	std::cout << "Position" << position.x << ", " << position.y << ", " << position.z << ", " << "\n";
	std::cout << "Target" << target.x << ", " << target.y << ", " << target.z << ", " << "\n";

	viewMatrix = glm::lookAt
	(
		position,
		position + target, // + target,
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
	glm::vec3 degreeTarget;

	
	front.x = glm::degrees(cos(glm::radians(yaw)) * cos(glm::radians(pitch)));
	front.y = glm::degrees(sin(glm::radians(yaw)) * cos(glm::radians(pitch)));
	front.z = glm::degrees(sin(glm::radians(pitch)));

	   
	tempTarget.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	tempTarget.y = sin(glm::radians(pitch));
	tempTarget.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	degreeTarget.x = cos(yaw) * cos(pitch);
	degreeTarget.y = sin(yaw) * cos(pitch);
	degreeTarget.z = sin(pitch);

	target = glm::normalize(tempTarget);
	//target = front;

	//target = targetPos;
	setViewMatrix();
}
