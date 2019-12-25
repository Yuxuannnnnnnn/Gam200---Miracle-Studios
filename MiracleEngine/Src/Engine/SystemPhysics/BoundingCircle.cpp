#include "PrecompiledHeaders.h"
#include "BoundingCircle.h"
#include "BoundingPolygon.h"

BoundingCircle::BoundingCircle() : 
	_center{}, 
	_radius{ 0.f } 
{}

BoundingCircle::BoundingCircle(Vector3 center, float radius) : 
	_center{ center }, 
	_radius{ radius } 
{}

BoundingCircle BoundingCircle::CreateBCircleFromBBox(const BoundingPolygon& box)
{
	float maxRadius = 0.f;

	for (size_t i = 0; i < box._cornerNum; ++i)
	{
		float radius = box._origin.Distance(box._corners[i]);

		if (maxRadius < radius)
			maxRadius = radius;
	}

	return BoundingCircle{ box._origin, maxRadius };
}