#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &_id);
	glBindVertexArray(_id);
}

VertexArray::~VertexArray()
{
}

void VertexArray::AddBuffer(const VertexBuffer& vb)
{
}

void VertexArray::Select() const
{
	glBindVertexArray(_id);
}

void VertexArray::UnSelect() const
{
	glBindVertexArray(0);
}
