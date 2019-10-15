#include "PrecompiledHeaders.h"
#include "vertexbuffer.h"

VertexBuffer::VertexBuffer() 
	:_id{0}
{

}
VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{

	glGenBuffers(1, &_id);
	glBindBuffer(GL_ARRAY_BUFFER, _id);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &_id);
}

void VertexBuffer::Select() const
{
	glBindBuffer(GL_ARRAY_BUFFER, _id);
}
void VertexBuffer::UnSelect() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}