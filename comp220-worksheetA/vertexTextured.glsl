#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec4 vertexColour;
layout(location = 2) in vec2 vertexTextureCoords;
//layout(location = 2) in vec2 vertexUniformLocation;

uniform mat4 modelMatrix;
uniform mat4 MVP;

out vec4 testColour;
out vec4 vertexColourOut;
out vec2 vertexTextureCoordsOut;

void main()
{
	//gl_Position = vec4(vertexPosition, 1.0);
	//gl_Position = modelMatrix * vec4(vertexPosition, 1.0f);

	vertexColourOut = vertexColour;
	vertexTextureCoordsOut = VertexTextureCoords;

	gl_Position = MVP * vec4(vertexPosition, 1.0f);


}