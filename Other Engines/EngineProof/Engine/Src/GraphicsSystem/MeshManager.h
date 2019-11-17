#pragma once
#include "QuadMesh.h"

class MeshManager
{
public:
	const QuadMesh& GetQuadMesh();

private:
	QuadMesh _quadmesh;
};