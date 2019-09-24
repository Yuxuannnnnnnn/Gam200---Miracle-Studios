#pragma once

#include "glew.h"

class VertexBuffer
{
public:
	VertexBuffer(const void* data, unsigned int size);
	VertexBuffer();
	~VertexBuffer();

	void Select() const;
	void UnSelect() const;
private:

	GLuint _id;

};