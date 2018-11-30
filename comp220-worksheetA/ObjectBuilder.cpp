#include "ObjectBuilder.h"



ObjectBuilder::ObjectBuilder()
{
}


ObjectBuilder::~ObjectBuilder()
{
	//Destroy vector of meshes
	auto iter2 = meshes.begin();
	while (iter2 != meshes.end())
	{
		if (*iter2)
		{
			//(*iter)->CleanUp(); Call destructor/cleanup here
			delete (*iter2);
			(*iter2) = nullptr;
			iter2 = meshes.erase(iter2);
		}

		else
		{
			iter2++;
		}
	}

	//These need to be vecotrs of pointers?
	/*
	//Destroy vector of game objects
	auto iter = diffuseTextures.begin();
	while (iter != diffuseTextures.end())
	{
		if (*iter)
		{
			//(*iter)->CleanUp(); Call destructor/cleanup here
			delete (*iter);
			(*iter) = nullptr;
			iter = diffuseTextures.erase(iter);
		}

		else
		{
			iter++;
		}
	}

	//Destroy vector of textures
	auto iter3 = specularTextures.begin();
	while (iter3 != textures.end())
	{
		if (*iter3)
		{
			//(*iter)->CleanUp(); Call destructor/cleanup here
			delete (*iter3);
			(*iter3) = nullptr;
			iter3 = textures.erase(iter3);
		}

		else
		{
			iter3++;
		}
	}*/
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
	RockTextureID = loadTextureFromFile("Resources/Textures/seamlessRock.jpg");

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
