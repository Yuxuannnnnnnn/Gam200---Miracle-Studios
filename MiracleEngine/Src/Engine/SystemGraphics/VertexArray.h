#pragma once

#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include "VertexBuffer.h"
#include "BufferLayout.h"
#include <glew.h>

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const BufferLayout& layout);

	void Select() const;
	void UnSelect() const;
private:
	GLuint _id;
};

#endif

