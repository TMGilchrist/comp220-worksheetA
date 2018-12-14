/**
Vertex

A single Vertex of a 3d mesh. 
*/

#pragma once
#include <btBulletDynamicsCommon.h>

/**
Coordinates.
RGB and Alpha values.
Texture coordinates.
Normal values.
*/
struct Vertex 
{
	float x, y, z;
	float r, g, b, a;
	float tu, tv;
	float xNormal, yNormal, zNormal;
};

struct Point
{
	btScalar x, y, z;
};