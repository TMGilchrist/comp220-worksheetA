#version 330 core

in vec4 vertexColourOut;
in vec2 vertexTextureCoordsOut;
in vec3 vertexNormalOut;
in vec4 worldSpaceVertex;

uniform vec4 triangleColour1; 
uniform vec4 triangleColour2; 

uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;

//Ambient lighting
uniform vec4 ambientLightColour;
uniform vec4 ambientMaterialColour;
uniform float ambientIntensity = 0.3;

//Diffuse lighting
uniform vec3 lightDirection=vec3(0.0f,0.0f,1.0f);
uniform vec4 diffuseLightColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
uniform vec4 diffuseMaterialColour = vec4(0.8f, 0.0f, 0.0f, 1.0f);

//Specular lighting
uniform vec3 cameraPosition; 
uniform vec4 specularLightColour = vec4(1);
uniform vec4 specularMaterialColour = vec4(1);
uniform float specularPower = 25.0f;

out vec4 colour;


void main()
{
	vec3 viewDirection = normalize(cameraPosition - worldSpaceVertex.xyz); //Normalize most things -> possibly -lightDirection as well.
	vec3 halfWay = normalize(-lightDirection + viewDirection);
 
	float specularIntensity = pow(clamp(dot(vertexNormalOut, halfWay), 0.0f, 1.0f), specularPower);

	//Reverse light direction to get vector from surface back towards the light source
	//Clamp to avoid visual errors
	float diffuseIntensity = clamp(dot(vertexNormalOut, normalize(-lightDirection)), 0.0f, 1.0f); //Should this be -lightdirection or positive?

	vec4 diffuseTextureColour = texture(diffuseTexture, vertexTextureCoordsOut);
	vec4 specularTextureColour = texture(specularTexture, vertexTextureCoordsOut);

	colour = (ambientLightColour * ambientMaterialColour * diffuseTextureColour * ambientIntensity ) + 
			 (diffuseLightColour * diffuseIntensity * diffuseMaterialColour * diffuseTextureColour) + 
			 (specularLightColour * specularIntensity * specularMaterialColour * specularTextureColour);
}