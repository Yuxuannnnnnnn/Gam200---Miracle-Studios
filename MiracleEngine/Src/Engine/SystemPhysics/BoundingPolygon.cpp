#include "PrecompiledHeaders.h"
#include "BoundingPolygon.h"

BoundingPolygon::BoundingPolygon() :
	_BC{},
	_origin{},
	_corners{ nullptr },
	_normals{ nullptr },
	_rotationAngle{ 0.f },
	_cornerNum{ 0 }
{}

BoundingPolygon::BoundingPolygon::BoundingPolygon(const BoundingPolygon& rhs) :
	_BC{ rhs._BC },
	_origin{ rhs._origin },
	_corners{ new Vector3[rhs._cornerNum] },
	_normals{ new Vector3[rhs._cornerNum] },
	_rotationAngle{ rhs._rotationAngle },
	_cornerNum{ rhs._cornerNum }
{
	for (size_t i = 0; i < rhs._cornerNum; ++i)
	{
		_normals[i] = rhs._normals[i];
		_corners[i] = rhs._corners[i];
	}
}

BoundingPolygon::~BoundingPolygon()
{
	if (_corners)
		delete[] _corners;

	if (_normals)
		delete[] _normals;
}


BoundingPolygon BoundingPolygon::CreateBBoxFromData(const Vec3& position, const Vec3& scale, const float& rotationAngle)
{
	BBox box;
	box._corners = new Vector3[4];
	box._normals = new Vector3[4];
	box._cornerNum = 4;

	box._origin = position;
	box._rotationAngle = rotationAngle;

	if (rotationAngle)
	{
		Vector3 X{ cos(rotationAngle), sin(rotationAngle) };
		Vector3 Y{ -sin(rotationAngle), cos(rotationAngle) };

		X *= 0.5f * scale._x;
		Y *= 0.5f * scale._y;

		box._corners[0] = position - X - Y;
		box._corners[1] = position + X - Y;
		box._corners[2] = position + X + Y;
		box._corners[3] = position - X + Y;
	}
	else
	{
		box._corners[0] = position + Vec3{ -0.5f * scale._x,  -0.5f * scale._y };
		box._corners[1] = position + Vec3{ 0.5f * scale._x,  -0.5f * scale._y };
		box._corners[2] = position + Vec3{ 0.5f * scale._x,  0.5f * scale._y };
		box._corners[3] = position + Vec3{ -0.5f * scale._x,  0.5f * scale._y };
	}

	// Make the length of each axis 1/edge length so we know any
	// dot product must be less than 1 to fall within the edge.

	

	// box axis
	box._normals[0] = (box._corners[1] - box._corners[0]) * 0.5f;
	box._normals[1] = (box._corners[3] - box._corners[0]) * 0.5f;
	// not use for box
	box._normals[2];
	box._normals[3];

	box._BC = BCircle::CreateBCircleFromBBox(box);

	return box;
}