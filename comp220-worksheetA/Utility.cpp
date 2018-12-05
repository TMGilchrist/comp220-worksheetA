#include "Utility.h"

Point VertexToPoint(Vertex vert)
{
	Point newPoint;
	newPoint.x = vert.x; //Can you just convert float to btScalar like this? Who knows? 
	newPoint.y = vert.y;
	newPoint.z = vert.z;

	return newPoint;
}

btVector3 VertexToBtVector3(Vertex vert)
{
	btVector3 newVector;
	newVector.setX(vert.x); //Can you just convert float to btScalar like this? Who knows? 
	newVector.setY(vert.y);
	newVector.setZ(vert.z);

	return newVector;
}

std::vector<Point> VerticesToPoints(std::vector<Vertex> vertexData)
{
	std::vector<Point> pointData;

	for (int i = 0; i < vertexData.size(); i++)
	{
		pointData.push_back(VertexToPoint(vertexData[i]));
	}

	return pointData;
}

std::vector<btVector3> VerticesToBtVectors(std::vector<Vertex> vertexData)
{
	std::vector<btVector3> vectorData;

	for (int i = 0; i < vertexData.size(); i++)
	{
		vectorData.push_back(VertexToBtVector3(vertexData[i]));
	}

	return vectorData;
}
