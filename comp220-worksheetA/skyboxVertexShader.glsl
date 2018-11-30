#version 330 core

layout(location = 0) in vec3 vertexPos;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 textureCoords;

void main()
{
	textureCoords = vertexPos;
    gl_Position = projectionMatrix * viewMatrix * vec4(vertexPos, 1.0);
}