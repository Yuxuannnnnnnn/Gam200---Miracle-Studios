#pragma once
#include "Tools/MathLib/Math.h"

typedef struct BoundingLine
{
	Vector3		_startPoint;
	Vector3		_endPoint;

	BoundingLine();
	BoundingLine(const Vector3& start, const Vector3& end);
} BLine;