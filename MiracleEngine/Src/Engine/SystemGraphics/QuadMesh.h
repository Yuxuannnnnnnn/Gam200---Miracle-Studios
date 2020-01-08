#pragma once

#ifndef QUADMESH_H
#define QUADMESH_H

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Elementbuffer.h"
#include "BufferLayout.h"
#include "Texture2D.h"

class QuadMesh
{
public:
	void Select();

	VertexBuffer* GetBuffer() const;
	QuadMesh();
	QuadMesh(float u0, float v0, float u1, float v1);
	~QuadMesh();
private:
	VertexArray* _vao;
	VertexBuffer* _vbo;
	ElementBuffer* _ebo;
};

#endif

