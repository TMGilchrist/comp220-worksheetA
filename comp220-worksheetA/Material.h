#pragma once
#include <glm\glm.hpp>

class Material
{
public:
	Material();
	~Material();

private:
	//Material colours
	glm::vec4 ambientColour;
	glm::vec4 diffuseColour;
	glm::vec4 specularColour;

	//Material specular properties
	float specularPower;
};

