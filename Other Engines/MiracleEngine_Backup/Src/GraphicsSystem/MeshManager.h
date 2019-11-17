#pragma once
#include "QuadMesh.h"

class MeshManager
{
public:
	const QuadMesh& GetQuadMesh()
	{
		return _quadmesh;
	}
private:
	QuadMesh _quadmesh;
};