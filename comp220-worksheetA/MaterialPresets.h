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

private:
	//Material presets
	Material plainGreen;
	Material plainRed;
	Material plainWhite;

	Material deepPurple;

	Material metal;

};


