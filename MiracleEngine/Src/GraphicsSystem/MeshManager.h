#pragma once
#include "Elementbuffer.h"
#include "VertexBuffer.h"

class Mesh
{
public:
	virtual int GetSize() const = 0;
};

class QuadMesh : public Mesh
{
public:
	QuadMesh()
	{
		
	}
	virtual int GetSize() const override
	{
		return 4 * 2 * sizeof(GLfloat);
	}
public:
	GLfloat positions[8] =
	{
		-0.5f, -0.5f, // 0
		0.5f , -0.5f, // 1
		0.5f , 0.5f,  // 2
		-0.5f, 0.5f   // 3
	};
};


class MeshManager
{
public:
	QuadMesh _quadmesh;
private:

};