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

	pitch = -89; // Why does initing pitch=0 make it weird?? -> at pitch 0, rendering flips over?
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

	pitch = 0; // why does init pitch=0 do weird things?
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
	viewMatrix = glm::lookAt
	(
		position,
		position + target,
		upVector
	);
}

void Camera::setProjectionMatrix(int screenWidth, int screenHeight)
{
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
	std::cout << "Pitch : " << pitch << "\n";
	//Constrain upwards view
	if (pitch > 89.0f)
		pitch = 89.0f;

	//Constrain downwards view
	if (pitch < -89.0f)
		pitch = -89.0f;
}

void Camera::calculateCameraRotation()
{
	glm::vec3 front;

	std::cout << yaw << "\n";
	front.x = cos(glm::radians(yaw)) * sin(glm::radians(pitch));
	front.y = cos(glm::radians(pitch)) * -1; // * -1 to inverse pitch for mouse movement
	front.z = sin(glm::radians(yaw)) * sin(glm::radians(pitch)); 

	target = glm::normalize(front);
	setViewMatrix();
}
