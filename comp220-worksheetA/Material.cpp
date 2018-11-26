#include "Material.h"



Material::Material()
{
}


Material::~Material()
{
}

void Material::Init(glm::vec4 AmbientColour, glm::vec4 DiffuseColour, glm::vec4 SpecularColour, float SpecularPower)
{
	ambientColour = AmbientColour;
	diffuseColour = DiffuseColour;
	specularColour = SpecularColour;

	specularPower = SpecularPower;
}
