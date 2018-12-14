#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec4 vertexColour;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec4 vertexColourOut;

void main()
{
	vertexColourOut = vertexColour;
	mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;
	gl_Position= MVP * vec4(vertexPosition, 1.0f);
}