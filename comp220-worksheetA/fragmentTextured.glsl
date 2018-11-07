#version 330 core

in vec4 vertexColourOut;
in vec2 vertexTextureCoordsOut;

uniform vec4 triangleColour1; 
uniform vec4 triangleColour2; 

uniform sampler2D textureSampler;

out vec4 colour;


void main()
{
	colour = texture(textureSampler, vertexTextureCoordsOut);
}