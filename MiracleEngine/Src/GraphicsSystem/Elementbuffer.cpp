#include "elementbuffer.h"

ElementBuffer::ElementBuffer()
	:_id{ 0 }, _count{0}
{
	
}
ElementBuffer::ElementBuffer(const GLuint* data, unsigned int count)
	:_count{count}
{
	glGenBuffers(1, &_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
}

unsigned int ElementBuffer::GetCount() const
{
	return _count;
}

ElementBuffer::~ElementBuffer()
{
	glDeleteBuffers(1, &_id);
}
void ElementBuffer::Select() const
{
	glBindBuffer(GL_ARRAY_BUFFER, _id);
}
void ElementBuffer::UnSelect() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}