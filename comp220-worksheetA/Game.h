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

	void Init();
	void Setup();
	void GameLoop();
	void Cleanup();


private:
	WindowManager* windowMain;
	SDL_Window* window;

	GLManager glManager;
	SDL_GLContext glContext;

	float deltaTime;
	float lastFrame;

	GLuint programID;
	GLuint MVPLocation;
	Camera* camera;

	InputManager* input;
	CharacterController controller;

	Mesh newObject;
	MeshCollection* tankMesh;

	//Uniform locations
	GLuint textureUniformLocation;
	GLuint modelMatrixLocation;
	GLuint viewMatrixLocation;
	GLuint projectionMatrixLocation;

	//Vector of game objects
	std::vector<GameObject*> objects;
};

