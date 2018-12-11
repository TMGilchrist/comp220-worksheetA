/**
Texture

Contains tools to work with textures.
*/

#pragma once


#include <GL\glew.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

#include <string>

/**
Loads a texture from a given filepath and returns a textureID.

@param filename : The filepath to the texture to be loaded.
@param textureID : The textureID for the texture being loaded. Used to refer to the texture in OpenGL.
*/
GLuint loadTextureFromFile(const std::string& filename);

SDL_Surface* loadHeightMap(const std::string& filename);

Uint8* getPixelColour(SDL_Surface* image, int x, int y);