#pragma once

#include "VertexBuffer.h"
#include "BufferLayout.h"

class VertexArray
{
private:
	unsigned int _id;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const BufferLayout& layout);

	void Select() const;
	void UnSelect() const;
};