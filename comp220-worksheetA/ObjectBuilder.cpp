#include "ObjectBuilder.h"



ObjectBuilder::ObjectBuilder()
{
}


ObjectBuilder::~ObjectBuilder()
{
}

void ObjectBuilder::Init()
{
	materialPresets = MaterialPresets();
	materialPresets.Init();

	//Load Meshes
	tankMesh = new MeshCollection();
	loadMeshFromFile("Resources/Tank1.FBX", tankMesh); //Need to move the mvp calculations into shaders.

	teaPotMesh = new MeshCollection();
	loadMeshFromFile("Resources/teapot.FBX", teaPotMesh); //Need to move the mvp calculations into shaders.

	//Add meshes to vector
	meshes.push_back(tankMesh);
	meshes.push_back(teaPotMesh);

	//Load diffuseTextures <- should be added to vector like the meshes? This would require changing to pointer.
	tankTextureID = loadTextureFromFile("Resources/Tank1DF.PNG");
	checkerTextureID = loadTextureFromFile("Resources/checkerboard.PNG");
	redTextureID = loadTextureFromFile("Resources/Red.PNG");

	diffuseTextures.push_back(tankTextureID);
	diffuseTextures.push_back(checkerTextureID);
	diffuseTextures.push_back(redTextureID);

	spotLightTextureID = loadTextureFromFile("Resources/spotlightSpecMap.jpg");
	specularTextures.push_back(spotLightTextureID);
}

GameObject * ObjectBuilder::MakeObject(const char * vertexShader, const char * fragmentShader, MeshCollection * mesh, GLuint diffuseTexture, Material material, glm::vec3 position, glm::vec3 scale)
{
	//Create new object
	GameObject* object = new GameObject();

	//Init object variables with the shaders to use
	object->Init(vertexShader, fragmentShader);

	//Set diffuseTextures
	object->setDiffuseTextureID(diffuseTexture);
	object->SetMaterial(material);

	//Position object
	object->setScale(scale);
	object->setTranslation(position);

	//Set object meshes
	object->setMesh(mesh);

	return object;
}

GameObject* ObjectBuilder::MakeObject(const char * vertexShader, const char * fragmentShader, MeshCollection* mesh, GLuint diffuseTexture, GLuint specularTexture, Material material, glm::vec3 position, glm::vec3 scale)
{
	//Create new object
	GameObject* object = new GameObject();

	//Init object variables with the shaders to use
	object->Init(vertexShader, fragmentShader);

	//Set diffuseTextures
	object->setDiffuseTextureID(diffuseTexture);
	object->setSpecularTextureID(specularTexture);
	object->SetMaterial(material);
	   
	//Position object
	object->setScale(scale);
	object->setTranslation(position);

	//Set object meshes
	object->setMesh(mesh);

	return object;
}
