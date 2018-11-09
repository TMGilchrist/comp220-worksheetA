#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec4 vertexColour;
layout(location = 2) in vec2 vertexTextureCoords;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

//uniform mat4 MVP;

out vec4 vertexColourOut;
out vec2 vertexTextureCoordsOut;


void main()
{
	vertexColourOut = vertexColour;
	vertexTextureCoordsOut = vertexTextureCoords;

	mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;
	gl_Position = MVP * vec4(vertexPosition, 1.0f);
}