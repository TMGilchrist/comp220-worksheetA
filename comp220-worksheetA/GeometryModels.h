#pragma once
#include"Vertex.h"

namespace GeometryModels 
{

	// Triangle Vertices
	//{x, y, z, r, g, b, a}
	static const Vertex triangle[] =
	{
		{-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f},
		{0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f},
		{0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f},
	};

	//Square Vertices
	//{x, y, z, r, g, b, a, tu, tv}
	static const Vertex square[] =
	{
		{-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
		{0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f},
		{0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f},
		{-0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f}
	};

	//Cube Vertices
	//{x, y, z, r, g, b, a, tu, tv}
	static const Vertex cube[] =
	{
		//Top four vertices
		{0, 1, 1, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f}, //0
		{0, 0, 1, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f},  //1
		{1, 0, 1, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f},  //2
		{1, 1, 1, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f},  //3

		//Bottom four vertices
		{0, 0, 0, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f},  //4
		{0, 1, 0, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f},  //5
		{1, 1, 0, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f},  //6
		{1, 0, 0, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f}   //7
	};

	//Cube Indices
	static const int cubeIndices[] =
	{
		1, 0 , 4,
		4, 0, 5,

		7, 2, 1,
		7, 1, 4,

		1, 2, 3,
		1, 3, 0,

		5, 0, 3,
		5, 3, 6,

		6, 3, 7,
		7, 3, 2,

		7, 4, 5,
		7, 5, 6
	};

	//Square Indices
	static const int squareIndices[] =
	{
		0,1,2,
		2,0,3
	};

}