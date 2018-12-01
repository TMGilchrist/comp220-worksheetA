/**
shader

Tools to work with shaders.
*/


#pragma once
#include <GL\glew.h>
#include <SDL_opengl.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

/**
Load a pair of shaders from file.

@param vertex_file_path : The path to the vertex shader file.
@param fragment_file_path : The path to the fragment shader file.

@returns ProgramID : The ID for a program using the specified shaders. Used to specify which shaders an object uses.
*/
GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
