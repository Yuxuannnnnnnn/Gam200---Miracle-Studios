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
	_startPoint{ start }, 
	_endPoint{ end }, 
	_normalVec{}, 
	_orthoDistance{ Vec3Distance_LinetoPoint(start,end, origin) }
{
	Vector3 temp = start - end;
	_centerPoint = end + temp * 0.5f;
	_normalVec.Set(-temp._y, temp._x);
	_normalVec.Normalize();
}

BoundingEdge::BoundingEdge(const Vector3& origin, const Vector3& scale, const float& rotateAngle)
{

}