#pragma once

#include "glew.h"
#include "stb_image/stb_image.h"

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