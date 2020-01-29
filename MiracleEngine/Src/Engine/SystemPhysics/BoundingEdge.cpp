#include "PrecompiledHeaders.h"
#include "BoundingEdge.h"

BoundingEdge::BoundingEdge() :
	_startPoint{}, 
	_endPoint{}, 
	_normalVec{}, 
	_orthoDistance{0.f}
{}

BoundingEdge::BoundingEdge(const Vector3& start, const Vector3& end, const Vector3& origin) :
	_startPoint{ start }, 
	_endPoint{ end }, 
	_normalVec{}, 
	_orthoDistance{ Vec3Distance_LinetoPoint(start,end, origin) }
{
	Vector3 temp = start - end;
	_normalVec.Set(-temp._y, temp._x);
	_normalVec.Normalize();
}