#pragma once
#include "Tools/MathLib/Math.h"

typedef struct BoundingCircle
{
	Vector3 _center;
	float _radius;

	BoundingCircle();
	// create from data
	BoundingCircle(const Vector3& center, const float& radius);
	//create from box
	BoundingCircle(const Vector3& center, const Vector3& scale);
	//create from polygon
	BoundingCircle(Vector3* points, int numPoints);
} BCircle;