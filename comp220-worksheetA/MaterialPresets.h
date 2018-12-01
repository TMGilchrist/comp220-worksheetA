/**
MaterialPresets

A collection of pre-constructed Material objects that cane be accessed via a getter function.
Defining Materials here allows for a common library of Material types that can be used across the game.
*/

#pragma once
#include "Material.h"

class MaterialPresets
{
public:
	MaterialPresets();
	~MaterialPresets();

	void Init();

	Material GetPlainGreen() 
	{
		return plainGreen;
	}

	Material GetPlainRed()
	{
		return plainRed;
	}

	Material GetPlainWhite()
	{
		return plainWhite;
	}

	Material GetMetal() 
	{
		return metal;
	}

	Material GetDeepPurple()
	{
		return deepPurple;
	}

	Material GetStone() 
	{
		return stone;
	}

private:
	//Material presets
	Material plainGreen;
	Material plainRed;
	Material plainWhite;

	Material deepPurple;

	Material metal;
	Material stone;

};


