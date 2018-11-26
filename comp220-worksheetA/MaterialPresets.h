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

private:
	//Material presets
	Material mat1;
	Material mat2;

};


