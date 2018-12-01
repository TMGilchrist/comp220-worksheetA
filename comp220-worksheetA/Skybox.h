/**
Skybox

Handles the setup and loading of skybox textures into a cubemap that can be drawn around the gameworld.
*/

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

	/**
	Initalise the skybox and create a cubemap.

	@param vertexShader : The filepath to the vertex shader to use.
	@param fragmentShader : The filepath to the fragment shader to use.
	*/
	void Init(const char* vertexShader, const char* fragmentShader);

	/**
	Creates and fills the vertex attribute and vertex buffer objects.
	*/
	void SetupBuffers();

	/**
	Load a cubemap from a vector of six images.

	@returns textureID : The ID of the created cubemap texture.
	*/
	unsigned int LoadCubemap(std::vector<std::string> faces);


	/*----------------------
	Getters and Setters
	----------------------*/

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

	//Define a skybox cube.
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



	//Image source = http://haxor.thelaborat.org/resources/texture/skybox/

	//File paths for each skybox face - order matters. 
	//The filepaths should be able to be specified in a function to allow different skyboxes to be loaded.
	std::vector<std::string> skyboxFaces
	{
		"Resources/Skyboxes/blue_night/right.jpg",
		"Resources/Skyboxes/blue_night/left.jpg",
		"Resources/Skyboxes/blue_night/top.jpg",
		"Resources/Skyboxes/blue_night/bottom.jpg",
		"Resources/Skyboxes/blue_night/front.jpg",
		"Resources/Skyboxes/blue_night/back.jpg"
	};

	unsigned int cubemapTexture;

	GLuint skyboxVAO, skyboxVBO;
};

