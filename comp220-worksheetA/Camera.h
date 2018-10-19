#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "globals.h"
#include <iostream>
#include "Window.h"

class Camera
{
public:
	Camera(float initFoV = 60, float initNearClip = 0.1, float initFarClip = 1000);
	Camera(glm::vec3 &Position, glm::vec3 &Target, glm::vec3 &UpVector, float initFoV = 60, float initNearClip = 0.1, float initFarClip = 1000);

	~Camera();

	//Calculate view matrix
	void setViewMatrix();

	//Caluclate projection matrix
	void setProjectionMatrix(int screenWidth, int screenHeight);

	//Keep camera inside pitch constraints
	void checkPitchConstraints();

	//Calculate the camera's rotation, based on mouse position
	void calculateCameraRotation();


	//Specialised setters to increase pitch and yaw instead of just replacing with new values
	void increasePitch(float Pitch)
	{
		pitch += Pitch;
	}

	void increaseYaw(float Yaw)
	{
		yaw += Yaw;
	}

	/*---------------------
	  Getters and Setters
	---------------------*/

	glm::mat4 getViewMatrix()
	{
		return viewMatrix;
	}

	glm::mat4 getProjectionMatrix()
	{
		return projectionMatrix;
	}

	glm::vec3 getPosition()
	{
		return position;
	}

	glm::vec3 getTarget()
	{
		return target;
	}

	glm::vec3 getUpVector()
	{
		return upVector;
	}

	void setPosition(glm::vec3 Position)
	{
		position = Position;
	}

	void setTarget(glm::vec3 Target)
	{
		target = Target;
	}

	void setPitch(float Pitch)
	{
		pitch = Pitch;
	}

	void setYaw(float Yaw) 
	{
		yaw = Yaw;
	}

	void setWindowHeight(int Height) 
	{
		windowHeight = Height;
	}

	void setWindowWidth(int Width) 
	{
		windowWidth = Width;
	}

private:
	int windowHeight;
	int windowWidth;

	//Vertical field of view in degrees.
	float FoV;

	// Near clipping plane. Keep as big as possible, or you'll get precision issues.
	float nearClip;

	// Far clipping plane. Keep as little as possible.
	float farClip;

	// the position of your camera, in world space
	glm::vec3 position;

	// where you want to look at, in world space
	glm::vec3 target;

	//Orientation of camera, (0, 1, 0) is normal.
	glm::vec3 upVector;

	//Actually opposite direction to camera facing
	glm::vec3 zAxis;

	glm::vec3 xAxis;
	glm::vec3 yAxis;

	//Matricies
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	//Yaw and pitch
	float pitch;
	float yaw;
};

