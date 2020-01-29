#include "PrecompiledHeaders.h"
#include "BoundingBox.h"

BoundingBox::BoundingBox() : 
	_BC{},
	_minPoint{},
	_maxPoint{}
{}

BoundingBox::BoundingBox(const Vector3& center, const Vector3& scale)
	: _BC{ center , scale }
{
	_minPoint = Vec3{ center._x,center._y, 1.f } - Vec3{ 0.5f * scale._x, 0.5f * scale._y };
	_maxPoint = Vec3{ center._x,center._y, 1.f } + Vec3{ 0.5f * scale._x, 0.5f * scale._y };
}

BoundingBox::BoundingBox(Vector3* points, int numPoints)
	: _BC{ points , numPoints }
{
	// @TODO: Compute top-left (minimum), bottom-right (maximum)
	// corners, and center of axis-aligned bounding box.
	_minPoint.Set(points[0]._x, points[0]._y, 1.f);
	_maxPoint.Set(points[0]._x, points[0]._y, 1.f);

	for (int i = 0; i < numPoints; ++i)
	{
		if (points[i]._x < _minPoint._x)
			_minPoint.SetX(points[i]._x);

		if (points[i]._x > _maxPoint._x)
			_maxPoint.SetX(points[i]._x);

		if (points[i]._y < _minPoint._y)
			_minPoint.SetY(points[i]._y);

		if (points[i]._y > _maxPoint._y)
			_maxPoint.SetY(points[i]._y);
	}
}