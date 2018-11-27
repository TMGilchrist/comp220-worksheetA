#pragma once
#include <glm\glm.hpp>

class Material
{
public:
	Material();
	~Material();

	void Init(glm::vec4 AmbientColour, glm::vec4 DiffuseColour, glm::vec4 SpecularColour, float SpecularPower);

	glm::vec4 GetAmbientColour() 
	{
		return ambientColour;
	}

	glm::vec4 GetDiffuseColour() 
	{
		return diffuseColour;
	}

	glm::vec4 GetSpecularColour() 
	{
		return specularColour;
	}

	float GetSpecularPower()
	{
		return specularPower;
	}

private:
	//Material colours
	glm::vec4 ambientColour;
	glm::vec4 diffuseColour;
	glm::vec4 specularColour;

	//Material specular properties
	float specularPower;
};

