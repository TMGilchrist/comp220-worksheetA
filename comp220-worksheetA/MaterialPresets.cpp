#include "MaterialPresets.h"

MaterialPresets::MaterialPresets()
{
}

MaterialPresets::~MaterialPresets()
{
}

void MaterialPresets::Init()
{
	mat1 = Material();
	mat1.Init(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f), glm::vec4(0.0f, 0.8f, 0.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 10);

	mat2 = Material();
	mat2.Init(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f), glm::vec4(0.8f, 0.0f, 0.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 25);
}
