#include "PrecompiledHeaders.h"
#include "BoundingCircle.h"
#include "Collision.h"

BoundingCircle::BoundingCircle() :
	_center{},
	_radius{ 0.f }
{}

BoundingCircle::BoundingCircle(const Vector3& center, const float& radius) :
	_center{ Vec3{center._x,center._y, 1.f} },
	_radius{ radius }
{}

BoundingCircle::BoundingCircle(const Vector3& center, const Vector3& scale) :
	_center{ center },
	_radius{ Vector3(scale._x * 0.5f, scale._y * 0.5f, 0).Length() }
{}

BoundingCircle::BoundingCircle(Vector3* points, int numPoints)
{
	// Compute bounding circle with tightest possible fit
	// Ritter's method
	Vector3 x = *points;
	Vector3 y = x;

	// Search a point y in pPos, which hasthe largest distance from x
	for (int i = 0; i < numPoints; ++i)
	{
		if (points[i].Distance(x) > y.Distance(x))
			y = points[i];
	}

	Vector3 z = y;

	// Search a point z in pPos, which has the largest distance from y
	for (int i = 0; i < numPoints; ++i)
	{
		if (points[i].Distance(y) > z.Distance(y))
			z = points[i];
	}

	// Set up an initial sphere B with its centre as the midpoint
	// of y and z, the radius as half of the distance between y and z
	_center = y + ((z - y) * 0.5f);
	_radius = (y.Distance(z)) * 0.5f;

	// Check if all points are covered by the BC
	for (int i = 0; i < numPoints; ++i)
	{
		// Construct a new BC, if point outside the BC
		if (!Collision::BCircleVsPoint(*this, points[i]))
		{
			Vector3 diff = points[i] - _center;
			float length = diff.Length();

			_radius = (_radius + length) / 2.f;
			_center = _center + diff / (1 / ((length - _radius) / length));
			_center.SetZ(1.f);
		}
	}

}