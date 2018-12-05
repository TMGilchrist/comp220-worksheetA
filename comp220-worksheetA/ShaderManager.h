#pragma once

#include <GL\glew.h>
#include <SDL_opengl.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <iostream>

#include <stdio.h>


class Shader
{
public:
	Shader();
	~Shader();

	void Use();

	GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
	bool Load(const std::string& vertexShaderFilename, const std::string& fragmentShaderFilename);


	GLint GetUniform(std::string name);

	GLuint& GetShaderProgramID()
	{
		return ShaderProgramID;
	}

private:
	void InitialiseUniforms();

	GLuint ShaderProgramID;

	std::map<std::string, GLint> UniformMap;

};