#pragma once

#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include "glew.h"

class VertexBuffer
{
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	// fill up uv data for dynamic buffer for different frames
	void FillDynamicBuffer(const void* data, unsigned int size);

	void Select() const;
	void UnSelect() const;
private:

	GLuint _id;

};

#endif

