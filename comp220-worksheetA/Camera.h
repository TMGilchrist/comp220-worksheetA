#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "globals.h"
#include <iostream>
#include "WindowManager.h"

class Camera
{
public:
	/**
	Create new camera with default values
	
	@param float initFoV: The field of view.
	@param float initNearClip: The near clipping plane (should not be smaller than 0.1).
	@param float initFarClip: The far clipping plane (should not be too large).
	*/
	Camera(float initFoV = 60, float initNearClip = 0.1, float initFarClip = 1000, float PitchConstraintUp = 89, float PitchConstraintDown = -89);

	/**
	Create new camera with custom starting location.
	
	@param vec3 &Position: Starting position of camera.
	@param vec3 &Target: Starting facing of camera.
	@param vec3 &UpVector: Orientation of camera (0, -1, 0 for upside down).

	@param float initFoV: The field of view.
	@param float initNearClip: The near clipping plane (should not be smaller than 0.1).
	@param float initFarClip: The far clipping plane (should not be too large).
	*/
	Camera(glm::vec3 &Position, glm::vec3 &Target, glm::vec3 &UpVector, float initFoV = 60, float initNearClip = 0.1, float initFarClip = 1000, float PitchConstraintUp = 89, float PitchConstraintDown = -89);

	~Camera();

	/**
	Calculate view matrix
	*/
	void setViewMatrix();

	/**
	Caluclate projection matrix

	@param int screenWidth: Width of screen, used to calculate aspect ratio.
	@param int screenHeight: Height of screen, used to calculate aspect ratio.
	*/
	void setProjectionMatrix(int screenWidth, int screenHeight);

	/**
	Keep camera inside pitch constraints
	*/
	void checkPitchConstraints();

	/**
	Calculate the camera's rotation, based on mouse position
	*/
	void calculateCameraRotation();


	/**
	Specialised setter to increase pitch instead of just replacing with new value.

	@param float pitch: The amount to change the pitch by.
	*/
	void increasePitch(float Pitch)
	{
		pitch += Pitch;
	}

	/**
	Specialised setter to increase yaw instead of just replacing with new value.

	@param float yaw: The amount to change the yaw by.
	*/
	void increaseYaw(float Yaw)
	{
		yaw += Yaw;
	}

	/*---------------------
	  Getters and Setters
	---------------------*/

	//These mat4/mat3's should be returned by reference!
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

	float pitchConstraintUp;
	float pitchConstraintDown;
	//float yawConstraint;
};

