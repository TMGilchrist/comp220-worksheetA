/**
Lights

Definitions of different types of lights.
*/

#pragma once

#include <glm\glm.hpp>

struct PointLight
{
	glm::vec4 diffuseColour;
	glm::vec4 specularColour;
	glm::vec3 position;
};

struct DirectionalLight 
{
	glm::vec4 diffuseColour;
	glm::vec4 specularColour;
	glm::vec3 lightDirection;
};