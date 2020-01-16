#pragma once

#include "Tools/MathLib/Math.h"
#include "BoundingCircle.h"

typedef struct BoundingPolygon
{
	BCircle _BC;

	Vector3 _origin;
	Vector3* _corners;
	Vector3* _normals;
	float _rotationAngle;

	size_t _cornerNum;

	BoundingPolygon();
	BoundingPolygon(const BoundingPolygon& rhs);
	~BoundingPolygon();

	static BoundingPolygon CreateBBoxFromData(const Vec3& position, const Vec3& scale, const float& rotationAngle);
	static BoundingPolygon CreateBPolygonFromData(const std::vector<Vec3>& corners, const Vec3& center,  const float& rotationAngle);

} BBox, BPolygon;