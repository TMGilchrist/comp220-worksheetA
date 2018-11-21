#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec4 vertexColour;
layout(location = 2) in vec2 vertexTextureCoords;
layout(location = 3) in vec3 vertexNormal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec4 vertexColourOut;
out vec2 vertexTextureCoordsOut;
out vec3 vertexNormalOut;


void main()
{
	vertexColourOut = vertexColour;
	vertexTextureCoordsOut = vertexTextureCoords;

	//Calculate MVP and position
	mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;
	vec4 mvpPosition = MVP * vec4(vertexPosition, 1.0f);

	vertexNormalOut = normalize((modelMatrix * vec4(vertexNormal, 0)).xyz);

	gl_Position = mvpPosition;

}