#pragma once
#include <glm\glm.hpp>
#include <SDL.h>
#include <SDL_image.h>

#include "shader.h"

class Skybox
{
public:
	Skybox();
	~Skybox();

	void Init(const char* vertexShader, const char* fragmentShader);

	void SetupBuffers();

	unsigned int LoadCubemap(std::vector<std::string> faces);

	unsigned int GetCubemapTexture() 
	{
		return cubemapTexture;
	}

	GLuint GetProgramID() 
	{
		return programID;
	}

	GLuint GetSkyboxVAO() 
	{
		return skyboxVAO;
	}

private:
	//ID of the shader to use for this skybox
	GLuint programID;

	//Define a skybox cube
	float skyboxVertices[108] =
	{
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};


	//File paths for each skybox face - order matters
	std::vector<std::string> skyboxFaces
	{
		//right, back,
		"Resources/Skyboxes/hw_nightsky/nightsky_right.tga",
		"Resources/Skyboxes/hw_nightsky/nightsky_left.tga",

		"Resources/Skyboxes/hw_nightsky/nightsky_up.tga",
		"Resources/Skyboxes/hw_nightsky/nightsky_down.tga",

		"Resources/Skyboxes/hw_nightsky/nightsky_back.tga",
		"Resources/Skyboxes/hw_nightsky/nightsky_front.tga"
	};

	unsigned int cubemapTexture;

	GLuint skyboxVAO, skyboxVBO;
};

