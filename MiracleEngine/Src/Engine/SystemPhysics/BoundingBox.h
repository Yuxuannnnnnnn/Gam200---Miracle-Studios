#pragma once
#include "Tools/MathLib/Math.h"
#include "BoundingCircle.h"

typedef struct BoundingBox
{
	BCircle _BC;

	Vector3 _minPoint;
	Vector3 _maxPoint;

	BoundingBox();
	// create from data
	BoundingBox(const Vector3& center, const Vector3& scale);
	//create from polygon
	BoundingBox(Vector3* points, int numPoints);

} BBox;