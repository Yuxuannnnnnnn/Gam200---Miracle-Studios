#pragma once

#ifndef ANIMATEDMESH_H
#define ANIMATEDMESH_H

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Elementbuffer.h"
#include "BufferLayout.h"
#include "Texture2D.h"

class AnimatedMesh
{
public:
	void Select();
	AnimatedMesh(float u0, float v0, float u1, float v1);
	~AnimatedMesh();
private:
	VertexArray* _vao;
	VertexBuffer* _vbo;
	ElementBuffer* _ebo;
};

#endif

