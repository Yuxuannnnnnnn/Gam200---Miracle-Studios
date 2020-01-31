#include "PrecompiledHeaders.h"
#include "BoundingLine.h"

BoundingLine::BoundingLine() :
	_startPoint{},
	_endPoint{}
{}

BoundingLine::BoundingLine(const Vector3& start, const Vector3& end) :
	_startPoint{ start },
	_endPoint{ end }
{
}