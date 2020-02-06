#include "PrecompiledHeaders.h"
#include "BoundingPolygon.h"

BoundingPolygon::BoundingPolygon() :
	_AABB{},
	_numPoints{0},
	_pointArray{ nullptr },
	_ptrEdgeArray{ nullptr },
	_obbBox{false}
{}

BoundingPolygon::BoundingPolygon(const BoundingPolygon& rhs) :
	_AABB{ rhs._AABB },
	_numPoints{ rhs._numPoints },
	_pointArray{ new Vector3[rhs._numPoints] },
	_ptrEdgeArray{ new BEdge[rhs._numPoints] },
	_obbBox{ rhs._obbBox }
{
	for (size_t i = 0; i < _numPoints; ++i)
	{
		_pointArray[i] = rhs._pointArray[i];
		_ptrEdgeArray[i] = rhs._ptrEdgeArray[i];
	}
}

BoundingPolygon& BoundingPolygon::operator=(const BoundingPolygon& rhs)
{
	_AABB = rhs._AABB;
	_numPoints = rhs._numPoints;
	_obbBox = rhs._obbBox;

	if (_pointArray)
		delete[] _pointArray;

	if (_ptrEdgeArray)
		delete[] _ptrEdgeArray;

	_pointArray = new Vector3[rhs._numPoints];
	_ptrEdgeArray = new BEdge[rhs._numPoints];
	

	for (size_t i = 0; i < _numPoints; ++i)
	{
		_pointArray[i] = rhs._pointArray[i];
		_ptrEdgeArray[i] = rhs._ptrEdgeArray[i];
	}

	return *this;
}


BoundingPolygon::BoundingPolygon(Vector3* points, int numPoints) :
	_AABB{ points, numPoints },
	_numPoints{ numPoints },
	_pointArray{ new Vector3[numPoints] },
	_ptrEdgeArray{ new BEdge[numPoints] },
	_obbBox{ false }
{
	for (int i = 0; i < numPoints; ++i)
	{
		_pointArray[i] = points[i];
		_pointArray[i].SetZ(1.f);
	}

	for (int i = 0; i < numPoints; ++i)
		_ptrEdgeArray[i] = BEdge{ _pointArray[i] , _pointArray[(i + 1) % _numPoints] };
}

BoundingPolygon::~BoundingPolygon()
{
	if (_pointArray)
		delete[] _pointArray;

	if (_ptrEdgeArray)
		delete[] _ptrEdgeArray;
}

BoundingPolygon BoundingPolygon::CreateBoxPolygon(const Vec3& position, const Vec3& scale, const float& rotationAngle)
{
	BPolygon box;
	box._obbBox = true;

	box._numPoints = 4;
	box._pointArray = new Vector3[box._numPoints];
	box._ptrEdgeArray = new BEdge[box._numPoints];


	Vector3 X{ cos(rotationAngle) * scale._x * 0.5f, sin(rotationAngle) * scale._x * 0.5f };
	Vector3 Y{ -sin(rotationAngle) * scale._y * 0.5f, cos(rotationAngle) * scale._y * 0.5f };

	box._pointArray[0] = position - X + Y;
	box._pointArray[1] = position + X + Y;
	box._pointArray[2] = position + X - Y;
	box._pointArray[3] = position - X - Y;

	box._AABB = BBox{ box._pointArray , box._numPoints };


	for (int i = 0; i < box._numPoints; ++i)
		box._pointArray[i].SetZ(1.f);


	// box axis
	box._ptrEdgeArray[0] = BEdge{ box._pointArray[0] , box._pointArray[1] , Vec3{ position._x,position._y,1.f} };
	box._ptrEdgeArray[1] = BEdge{ box._pointArray[1] , box._pointArray[2] , Vec3{ position._x,position._y,1.f} };
	box._ptrEdgeArray[2] = BEdge{ box._pointArray[2] , box._pointArray[3] , Vec3{ position._x,position._y,1.f} };
	box._ptrEdgeArray[3] = BEdge{ box._pointArray[3] , box._pointArray[0] , Vec3{ position._x,position._y,1.f} };

	return box;
}
