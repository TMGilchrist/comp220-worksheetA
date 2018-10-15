#version 330 core

out vec4 colour;
//in vec4 testColour;

in vec4 vertexColourOut;

uniform vec4 triangleColour1; 
uniform vec4 triangleColour2; 


void main()
{
	//colour = vec3(1, 0, 0);
	//colour = mix(triangleColour1, triangleColour2, 0.5);
	colour = vertexColourOut;
}