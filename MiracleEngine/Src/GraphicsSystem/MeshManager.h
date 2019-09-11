#pragma once
#include "Elementbuffer.h"
#include "VertexBuffer.h"

class MeshManager
{
public:
	MeshManager()
	{
		
		_vbo = VertexBuffer(_positions, 4 * 2 * sizeof(GLfloat)); // bind vbo, bind, ebo must bind every single loop
		_ebo = ElementBuffer(_indices, 6);
	}
	void Update()
	{
		_vbo = VertexBuffer(_positions, 4 * 2 * sizeof(GLfloat)); // bind vbo, bind, ebo must bind every single loop
		_ebo = ElementBuffer(_indices, 6);
		_vbo.Select();
		_ebo.Select();
	}
private:
	GLuint _indices[6] =
	{
		0,1,2,
		2,3,0
	};
	GLfloat _positions[8] =
	{
		-0.5f, -0.5f, // 0
		0.5f , -0.5f, // 1
		0.5f , 0.5f,  // 2
		-0.5f, 0.5f   // 3
	};
	VertexBuffer _vbo;
	ElementBuffer _ebo;
};