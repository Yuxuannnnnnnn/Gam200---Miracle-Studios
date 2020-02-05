#include "PrecompiledHeaders.h"
#include "BoundingEdge.h"

BoundingEdge::BoundingEdge() :
	_centerPoint{},
	_startPoint{}, 
	_endPoint{}, 
	_normalVec{}, 
	_orthoDistance{0.f}
{}

BoundingEdge::BoundingEdge(const Vector3& start, const Vector3& end, const Vector3& origin) :
	_startPoint{ Vec3{start._x,start._y, 1.f} },
	_endPoint{ Vec3{end._x,end._y, 1.f} },
	_normalVec{}, 
	_orthoDistance{ 0.f }
{
	Vector3 temp = end - start;
	_centerPoint = start + temp * 0.5f;
	_normalVec.Set(-temp._y, temp._x);
	_normalVec.Normalize();

	Vec3 vec = origin - start;
	_orthoDistance = vec.AbsDot(_normalVec);
}

BoundingEdge::BoundingEdge(const Vector3& origin, const Vector3& scale, const float& rotateAngle)
{

}