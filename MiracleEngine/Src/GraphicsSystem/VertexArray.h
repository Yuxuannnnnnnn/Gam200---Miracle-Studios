#pragma once
#include "VertexBuffer.h"


class VertexArray
{
private:
	GLuint _id;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb);

	void Select() const;
	void UnSelect() const;
};
