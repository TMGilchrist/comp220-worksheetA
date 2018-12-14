#pragma once
#include <btBulletDynamicsCommon.h>
#include <vector>

#include "Vertex.h"


/**
Convert a Vertex struct to a Point struct. Each float value is converted to btScalar.

@param vert : The Vertex to convert.
@return newPoint : The new Point.
*/
Point VertexToPoint(Vertex vert);

btVector3 VertexToBtVector3(Vertex vert);

/**
Convert each Vertex in a vector to a Point and return a vector of the new Point values.

@param vertexData : The vector of Vertices to convert.
@return pointData : The vector of Points.
*/
std::vector<Point> VerticesToPoints(std::vector<Vertex> vertexData);

std::vector<btVector3> VerticesToBtVectors(std::vector<Vertex> vertexData);
