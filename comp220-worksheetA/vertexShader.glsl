#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec4 vertexColour;
out vec4 testColour;

uniform mat4 modelMatrix;
uniform mat4 MVP;

out vec4 vertexColourOut;

void main()
{
	//gl_Position = vec4(vertexPosition, 1.0);
	//gl_Position = modelMatrix * vec4(vertexPosition, 1.0f);

	vertexColourOut = vertexColour;
	gl_Position = MVP * vec4(vertexPosition, 1.0f);


}