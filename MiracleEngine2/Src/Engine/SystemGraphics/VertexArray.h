#pragma once

#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

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

	//void AddBuffer(Animations& vb, const BufferLayout& layout);
	void Select() const;
	void UnSelect() const;
};

#endif

