#pragma once
#include "Tools/MathLib/Math.h"

typedef struct BoundingEdge
{
	Vector3		_centerPoint;
	Vector3		_startPoint;
	Vector3		_endPoint;
	Vector3		_normalVec;
	float		_orthoDistance;	// orthogonal distance from origin to edge

	BoundingEdge();
	BoundingEdge(const Vector3& start, const Vector3& end, const Vector3& origin = Vector3{});
	BoundingEdge(const Vector3& origin, const Vector3& scale, const float& rotateAngle);
} BEdge;