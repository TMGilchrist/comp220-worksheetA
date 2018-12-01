/**
Model

Two functions to load 3d models from a filepath.
*/

#pragma once

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include <string>
#include <vector>

#include <GL\glew.h>
#include <SDL_opengl.h>

#include "vertex.h"
#include "Mesh.h"

/**
Load a model directly into openGL.

@param filename : The filepath of the 3d model file to load.
@param VBO : The vertex buffer object to load the model into.
@param EBO : The element buffer object to load the model into.
@param numVerts : A variable to hold the number of verticies in the model.
@param numIndices : A variable to hold the number of indicies in the model.
*/
bool loadModelFromFile(const std::string& filename, GLuint VBO, GLuint EBO, unsigned int& numVerts, unsigned int& numIndices);

/**
Load a 3d model from a file into the specified meshCollection.

@param filename : The filepath to the 3d model file to load.
@param pMeshCollection : The meshCollection to load this model into.
*/
bool loadMeshFromFile(const std::string& filename, MeshCollection * pMeshCollection);