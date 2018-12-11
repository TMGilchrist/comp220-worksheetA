#include "Texture.h"

GLuint loadTextureFromFile(const std::string& filename)
{
	GLuint textureID;


	GLenum	textureFormat = GL_RGB;
	GLenum	internalFormat = GL_RGB8;

	//Load image into surface
	SDL_Surface * surface = IMG_Load(filename.c_str());
	if (surface == nullptr)
	{
		printf("Could not load file %s", IMG_GetError());
		return 0;
	}

	//Check number of colours
	GLint	nOfColors = surface->format->BytesPerPixel;
	if (nOfColors == 4)					//contains an alpha channel
	{
		//Check for colour red and infer colour format
		if (surface->format->Rmask == 0x000000ff) 
		{
			textureFormat = GL_RGBA;
			internalFormat = GL_RGBA8;
		}

		else 
		{
			textureFormat = GL_BGRA;
			internalFormat = GL_RGBA8;
		}
	}

	else if (nOfColors == 3)					//no alpha channel
	{
		//Check for colour red and infer colour format
		if (surface->format->Rmask == 0x000000ff) 
		{
			textureFormat = GL_RGB;
			internalFormat = GL_RGB8;
		}

		else 
		{
			textureFormat = GL_BGR;
			internalFormat = GL_RGB8;
		}
	}

	//Create and bind texture
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	//Set parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//Pass texure to openGL
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, surface->w, surface->h, 0, textureFormat, GL_UNSIGNED_BYTE, surface->pixels);

	
	SDL_FreeSurface(surface);

	return textureID;
}

SDL_Surface* loadHeightMap(const std::string& filename)
{
	//Load image into surface
	SDL_Surface * surface = IMG_Load(filename.c_str());
	if (surface == nullptr)
	{
		printf("Could not load file %s", IMG_GetError());
		return 0;
	}

	return surface;
}

Uint8* getPixelColour(SDL_Surface * image, int x, int y)
{
	Uint32* pixels = (Uint32*)image->pixels;
	int offset = y * (image->pitch / sizeof(Uint32));

	Uint32* pixel = (Uint32*)pixels[offset + x];
	Uint8 * colour = (Uint8 *)pixel;
	return colour;
}


