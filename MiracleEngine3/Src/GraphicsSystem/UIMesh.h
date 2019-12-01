#pragma once

#ifndef UIMESH_H
#define UIMESH_H

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Elementbuffer.h"
#include "BufferLayout.h"

class UIMesh
{
public:
	void Select();
	UIMesh();
	~UIMesh();
private:
	VertexArray* _vao;
	VertexBuffer* _vbo;
	ElementBuffer* _ebo;
};

#endif