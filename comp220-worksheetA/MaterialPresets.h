#pragma once
#include "Material.h"

class MaterialPresets
{
public:
	MaterialPresets();
	~MaterialPresets();

	void Init();

	Material GetMat1() 
	{
		return mat1;
	}

	Material GetMat2()
	{
		return mat2;
	}

	Material GetPlainWhite()
	{
		return plainWhite;
	}

private:
	//Material presets
	Material mat1;
	Material mat2;
	Material plainWhite;

};


