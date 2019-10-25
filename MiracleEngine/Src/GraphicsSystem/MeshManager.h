#pragma once
#include "QuadMesh.h"


class Mesh
{

};

class MeshManager
{
public:
	const QuadMesh& GetQuadMesh();

private:
	QuadMesh _quadmesh;
};