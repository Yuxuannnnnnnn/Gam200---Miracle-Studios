#pragma once

#include "Tools/MathLib/Math.h"

extern class BoundingPolygon;

typedef struct BoundingCircle
{
	Vector3 _center;
	float _radius;

	BoundingCircle();
	BoundingCircle(Vector3 center, float radius);


	static BoundingCircle CreateBCircleFromBBox(const BoundingPolygon& box);

	//static BoundingCircle CreateBCircleFromBPolygen(const BoundingPolygon& polygon);

} BCircle;