#pragma once
#include "Elementbuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"

class Mesh
{
public:
	virtual void Select() const = 0;
};

class QuadMesh : public Mesh
{
public:
	QuadMesh() //: _vbo{_positions, GetVBOSize()}, _ebo{_indices, GetIndices()}
	{
		_vao.Select();
		VertexBuffer vbo(_positions, GetVBOSize()); // bind vbo, bind, ebo must bind every single loop
		
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	}
	virtual void Select() const
	{
		_vao.Select();
	}
	virtual int GetVBOSize() const 
	{
		return 4 * 2 * sizeof(GLfloat);
	}
	virtual int GetIndicesCount() const
	{
		return 6;
	}
public:
	VertexArray _vao;
	VertexBuffer _vbo;
	ElementBuffer _ebo;
	GLfloat _positions[8] =
	{
		-0.5f, -0.5f, // 0
		0.5f , -0.5f, // 1
		0.5f , 0.5f,  // 2
		-0.5f, 0.5f   // 3
	};
	GLuint _indices[6] =
	{
		0,1,2,
		2,3,0
	};
};

class LineMesh : public Mesh
{

};

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