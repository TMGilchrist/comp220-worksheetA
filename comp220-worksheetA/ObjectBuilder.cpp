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
	loadMeshFromFile("Resources/Models/Tank1.FBX", tankMesh);

	teaPotMesh = new MeshCollection();
	loadMeshFromFile("Resources/Models/teapot.FBX", teaPotMesh);

	towerMesh = new MeshCollection();
	loadMeshFromFile("Resources/Models/Tower.FBX", towerMesh); 

	cubeMesh = new MeshCollection();
	loadMeshFromFile("Resources/Models/cube.nff", cubeMesh);

	sphereMesh = new MeshCollection();
	loadMeshFromFile("Resources/Models/sphere.nff", sphereMesh);

	terrainMesh = new MeshCollection();
	loadMeshFromFile("Resources/Models/landscapePrototype.FBX", terrainMesh);

	//Add meshes to vector
	meshes.push_back(tankMesh);
	meshes.push_back(teaPotMesh);
	meshes.push_back(towerMesh);
	meshes.push_back(cubeMesh);
	meshes.push_back(sphereMesh);
	meshes.push_back(terrainMesh);

	//Load diffuseTextures <- should be added to vector like the meshes? This would require changing to pointer.
	tankTextureID = loadTextureFromFile("Resources/Textures/Tank1DF.PNG");
	checkerTextureID = loadTextureFromFile("Resources/Textures/checkerboard.PNG");
	RockTextureID = loadTextureFromFile("Resources/Textures/painterlyRock.jpg");

	diffuseTextures.push_back(tankTextureID);
	diffuseTextures.push_back(checkerTextureID);
	diffuseTextures.push_back(RockTextureID);

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
	object->SetPosition(position.x, position.y, position.z);
	object->setScale(scale);


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
	object->SetPosition(position.x, position.y, position.z);
	object->setScale(scale);


	//Set object meshes
	object->setMesh(mesh);

	return object;
}
