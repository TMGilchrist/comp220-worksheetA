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

#include "Game.h"
