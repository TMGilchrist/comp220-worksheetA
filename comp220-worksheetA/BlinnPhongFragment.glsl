#version 330 core

in vec4 vertexColourOut;
in vec2 vertexTextureCoordsOut;
in vec3 vertexNormalOut;

uniform vec4 triangleColour1; 
uniform vec4 triangleColour2; 

uniform sampler2D textureSampler;

uniform vec4 ambientLightColour;
uniform vec4 ambientMaterialColour;
uniform float ambientIntensity = 0.3;

uniform vec3 lightDirection;
uniform vec4 diffuseLightColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
uniform vec4 diffuseMaterialColour = vec4(0.8f, 0.0f, 0.0f, 1.0f);
uniform float diffuseIntensity = 1.0;

out vec4 colour;


void main()
{
	//Reverse light direction to get vector from surface back towards the light source
	//Clamp to avoid visual errors
	float diffuseIntensity = clamp(dot(vertexNormalOut, -lightDirection), 0, 1);

	//colour = (ambientLightColour * ambientMaterialColour);
	colour = ((ambientLightColour * ambientMaterialColour) * 0.3 ) + (diffuseLightColour * diffuseIntensity * diffuseMaterialColour);
}