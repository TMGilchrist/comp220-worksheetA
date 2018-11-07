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

	pitch = 0;
	yaw = 0;

	//Generate matricies
	setViewMatrix();
	setProjectionMatrix(global::SCREEN_WIDTH, global::SCREEN_HEIGHT); //Doesn't actually work as intended, should really get current window size
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

	pitch = 0;
	yaw = 0;

	//Generate matricies
	setViewMatrix();
	setProjectionMatrix(global::SCREEN_WIDTH, global::SCREEN_HEIGHT); //Doesn't actually work as intended, should really get current window size
}


Camera::~Camera()
{
}

void Camera::setViewMatrix()
{
	//Generate the vew matrix
	viewMatrix = glm::lookAt
	(
		position,
		position + target,
		upVector
	);
}

void Camera::setProjectionMatrix(int screenWidth, int screenHeight)
{
	//Generate projection matrix
	projectionMatrix = glm::perspective
	(
		glm::radians(FoV),
		(float)screenWidth / (float)screenHeight, // Aspect Ratio
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
	glm::vec3 direction;

	direction.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	direction.y = sin(glm::radians(pitch)) * -1; // * -1 to inverse pitch for mouse movement
	direction.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));

	target = glm::normalize(direction);
	setViewMatrix();
}
