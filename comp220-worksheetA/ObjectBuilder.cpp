#include "ObjectBuilder.h"



ObjectBuilder::ObjectBuilder()
{
}


ObjectBuilder::~ObjectBuilder()
{
	//Delete meshes map.
	for (std::map<std::string, MeshCollection*>::iterator itr = meshes.begin(); itr != meshes.end(); itr++)
	{
		delete itr->second;
	}
}

void ObjectBuilder::Init()
{
	//Load material presets
	materials = MaterialPresets();
	materials.Init();

	//Load meshes and textures
	LoadMeshes();
	LoadTextures();
}

void ObjectBuilder::LoadMeshes()
{
	//Currently have to reassign currentMesh to clear the MeshCollection. Is this the best way to do so?
	currentMesh = new MeshCollection();
	loadMeshFromFile("Resources/Models/Tank1.FBX", currentMesh);
	meshes.insert(std::make_pair("Tank", currentMesh));

	currentMesh = new MeshCollection();
	loadMeshFromFile("Resources/Models/teapot.FBX", currentMesh);
	meshes.insert(std::make_pair("teapot", currentMesh));

	currentMesh = new MeshCollection();
	loadMeshFromFile("Resources/Models/Tower.FBX", currentMesh);
	meshes.insert(std::make_pair("Tower", currentMesh));

	currentMesh = new MeshCollection();
	loadMeshFromFile("Resources/Models/cube.nff", currentMesh);
	meshes.insert(std::make_pair("cube", currentMesh));

	currentMesh = new MeshCollection();
	loadMeshFromFile("Resources/Models/sphere.nff", currentMesh);
	meshes.insert(std::make_pair("sphere", currentMesh));

	currentMesh = new MeshCollection();
	loadMeshFromFile("Resources/Models/landscapePrototype.FBX", currentMesh);
	meshes.insert(std::make_pair("landscapePrototype", currentMesh));

	currentMesh = new MeshCollection();
	loadMeshFromFile("Resources/Models/Foliage/TreeType1.dae", currentMesh);
	meshes.insert(std::make_pair("TreeType1", currentMesh));

	currentMesh = new MeshCollection();
	loadMeshFromFile("Resources/Models/Foliage/treeExportTest4.FBX", currentMesh);
	meshes.insert(std::make_pair("treeSceneTest", currentMesh));
}

void ObjectBuilder::LoadTextures()
{
	currentTexture = loadTextureFromFile("Resources/Textures/checkerboard.PNG");
	textures.insert(std::make_pair("checkerboard", currentTexture));

	currentTexture = loadTextureFromFile("Resources/Textures/seamlessRock.jpg");
	textures.insert(std::make_pair("seamlessRock", currentTexture));

	currentTexture = loadTextureFromFile("Resources/Textures/ColorsheetTreeNormal.PNG");
	textures.insert(std::make_pair("ColoursheetTreeNormal", currentTexture));
	
	//currentTexture = loadTextureFromFile("Resources/Textures/Tower/tileable_bricks.jpg");
	//textures.insert(std::make_pair("tileableBricks", currentTexture));

	currentTexture = loadTextureFromFile("Resources/Textures/Tower/medium_bricks.jpg");
	textures.insert(std::make_pair("mediumBricks", currentTexture));

	currentTexture = loadTextureFromFile("Resources/spotlightSpecMap.jpg");
	textures.insert(std::make_pair("spotlightSpecMap", currentTexture));
}

GameObject * ObjectBuilder::MakeObject(Shader* shader, std::string meshName, std::string diffuseTextureName, Material material, glm::vec3 position, glm::vec3 scale, glm::vec3 rotation)
{
	//Create new object
	GameObject* object = new GameObject();

	//Init object variables with the shaders to use
	object->Init(shader);

	//Set diffuseTextures
	object->setDiffuseTextureID(textures[diffuseTextureName]);
	object->SetMaterial(material);

	//Position object
	object->SetPosition(position.x, position.y, position.z);
	object->setScale(scale);
	object->SetRotation(rotation);


	//Set object meshes
	object->setMesh(meshes[meshName]);

	return object;
}

GameObject* ObjectBuilder::MakeObject(Shader* shader, std::string meshName, std::string diffuseTextureName, std::string specularTextureName, Material material, glm::vec3 position, glm::vec3 scale, glm::vec3 rotation)
{
	//Create new object
	GameObject* object = new GameObject();

	//Init object variables with the shaders to use
	object->Init(shader);

	//Set diffuseTextures
	object->setDiffuseTextureID(textures[diffuseTextureName]);
	object->setSpecularTextureID(textures[specularTextureName]);
	object->SetMaterial(material);
	   
	//Position object
	object->SetPosition(position.x, position.y, position.z);
	object->setScale(scale);
	object->SetRotation(rotation);

	//Set object meshes
	object->setMesh(meshes[meshName]);

	return object;
}

GameObject * ObjectBuilder::MakePineTree1(Shader * shader, glm::vec3 position, glm::vec3 scale, glm::vec3 rotation)
{
	GameObject* tree = MakeObject(shader, "TreeType1", "ColoursheetTreeNormal", "spotlightSpecMap",	
								  materials.GetPlainWhite(), position, scale, rotation);

	return tree;
}
