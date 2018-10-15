#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "globals.h"

class Camera
{
public:
	Camera(float initFoV = 60, float initNearClip = 0.1, float initFarClip = 100);
	Camera(glm::vec3 &Position, glm::vec3 &Target, glm::vec3 &UpVector, float initFoV=60, float initNearClip=0.1, float initFarClip=100);

	~Camera();

	void setViewMatrix();
	void setProjectionMatrix();

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

	void setPosition(glm::vec3 Position) 
	{
		position = Position;
	}

	void setTarget(glm::vec3 Target) 
	{
		target = Target;
	}

private:
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

	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
};

