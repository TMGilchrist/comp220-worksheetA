#pragma once
#pragma once

#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <gl/glew.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "shader.h"
#include "WindowManager.h"
#include "Camera.h"
#include "GLManager.h"
#include "inputManager.h"
#include "characterController.h"

#include "Vertex.h"
#include "Texture.h"
#include "Mesh.h"
#include "GeometryModels.h"
#include "Model.h"
#include "GameObject.h"

class Game
{
public:
	Game();
	~Game();

	/**
	Initialise sdl and openGL components and deltaTime.
	*/
	void Init();

	/**
	Setup game components. Initialise camera, input manager and controller.
	*/
	void Setup();

	/**
	Create game objects and add to the objects vector.
	*/
	void CreateObjects();

	/**
	The main game loop. Runs until escape is pressed or the window is closed.
	*/
	void GameLoop();

	/**
	Cleanup components
	*/
	void Cleanup();


private:
	WindowManager* windowMain;
	SDL_Window* window;

	GLManager glManager;
	SDL_GLContext glContext;

	//Delta time and the time last frame
	float deltaTime;
	float lastFrame;

	GLuint programID;
	GLuint MVPLocation;
	Camera* camera;

	InputManager* input;
	CharacterController controller;

	//Uniform locations
	GLuint textureUniformLocation;
	GLuint modelMatrixLocation;
	GLuint viewMatrixLocation;
	GLuint projectionMatrixLocation;

	GLuint	ambientMaterialColourLocation;
	GLuint ambientLightColourLocation;

	glm::vec4 ambientMaterialColour;
	glm::vec4 ambientLightColour;

	//Vector of game objects
	std::vector<GameObject*> objects;

	//Vector of meshes
	std::vector<MeshCollection*> meshes;

	//Vector of textures
	std::vector<GLuint*> textures;
};

