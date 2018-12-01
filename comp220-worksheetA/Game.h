/**
Game

The main game class. This contains the main game loop and the intialisation and setup functions for game components.
*/

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

#include "MaterialPresets.h"
#include "ObjectBuilder.h"
#include "PhysicsManager.h"
#include "Skybox.h"

#include "Lights.h"

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
	Setup the lighting uniforms and values.
	This should likely be moved into a lighting manager class at some point.
	*/
	void InitLighting();

	/**
	Create game objects and add to the objects vector.
	*/
	void CreateObjects();

	/**
	Create game objects that have physics components.
	*/
	void CreatePhysicsObjects();

	/**
	The main game loop. Runs until escape is pressed or the window is closed.
	*/
	void GameLoop();

	/**
	Sets the uniform location variables for a certain program. 
	This needs to be called every time the active program is changed. 

	@param programID : The ID of the program being used.
	*/
	void SetUniformLocations(GLuint programID);

	/**
	Send across the uniform variables. This must be called after SetUniformLocations has been called.

	@param object : The gameObject which is sending the uniforms.
	*/
	void SendUniforms(GameObject* object);

	/**
	Cleanup components
	*/
	void Cleanup();


private:
	//Manager classes
	WindowManager* windowMain;
	GLManager glManager;
	PhysicsManager physics;
	ObjectBuilder objectBuilder;
	MaterialPresets materialPresets;

	SDL_GLContext glContext;
	SDL_Window* window;
	Skybox skybox;

	//Delta time and the time last frame
	float deltaTime;
	float lastFrame;

	//The camera being used to render the game
	Camera* camera;

	//
	InputManager* input;
	CharacterController controller;

	GLuint programID;

	//Vector of game objects
	std::vector<GameObject*> objects;

	//Vector of meshes
	std::vector<MeshCollection*> meshes;

	//Vector of textures
	std::vector<GLuint*> textures;


	/*----------------------------------------------
	Lighting related uniforms.
	Probably move these out to a lightingManager
	----------------------------------------------*/

	//Ambient
	glm::vec4 ambientLightColour;
	float ambientIntensity;

	//Diffuse
	glm::vec4 diffuseLightColour;
	glm::vec3 lightDirection;

	//Specular
	glm::vec4 specularLightColour;
	glm::vec3 cameraPosition;
	float specularPower;
	   

	//Uniform locations
	GLuint diffuseTextureLocation;
	GLuint specularTextureLocation;

	GLuint modelMatrixLocation;
	GLuint viewMatrixLocation;
	GLuint projectionMatrixLocation;
	GLuint MVPLocation;

	GLuint	ambientMaterialColourLocation;
	GLuint ambientLightColourLocation;
	GLuint ambientIntensityLocation;

	GLuint diffuseMaterialColourLocation;
	GLuint diffuseLightColourLocation;
	GLuint lightDirectionLocation;
	GLuint diffuseIntensityLocation;

	GLuint specularMaterialColourLocation;
	GLuint specularLightColourLocation;
	GLuint cameraPositionLocation;
	GLuint specularPowerLocation;
};

