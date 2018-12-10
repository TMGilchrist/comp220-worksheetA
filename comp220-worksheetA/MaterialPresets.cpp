#include "MaterialPresets.h"

MaterialPresets::MaterialPresets()
{
}

MaterialPresets::~MaterialPresets()
{
}

void MaterialPresets::Init()
{
	plainGreen = Material();
	plainGreen.Init(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f), glm::vec4(0.0f, 0.8f, 0.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 10);

	plainRed = Material();
	plainRed.Init(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f), glm::vec4(0.8f, 0.0f, 0.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 25);

	plainWhite = Material();
	plainWhite.Init(glm::vec4(1.0f, 1.0f, 1.0f, 0.0f), glm::vec4(0.8f, 0.8f, 0.8f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 5);

	deepPurple = Material();
	deepPurple.Init(glm::vec4(37.0 / 255, 5.0 /255, 43.0 / 255, 0.0f), glm::vec4(37.0 / 255, 5.0 / 255, 43.0 / 255, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 5);

	metal = Material();
	metal.Init(glm::vec4(1.0f, 1.0f, 1.0f, 0.0f), glm::vec4(0.8f, 0.8f, 0.8f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 25);

	stone = Material();
	stone.Init(glm::vec4(1.0f, 1.0f, 1.0f, 0.0f), glm::vec4(0.8f, 0.8f, 0.8f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 20);
}
