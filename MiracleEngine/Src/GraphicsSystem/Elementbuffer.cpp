#include "elementbuffer.h"

ElementBuffer::ElementBuffer(unsigned int* data, unsigned int count)
	:_count{count}
{
	glGenBuffers(1, &_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
}

ElementBuffer::~ElementBuffer()
{
	glDeleteBuffers(1, &_id);
}
void ElementBuffer::Select()
{
	glBindBuffer(GL_ARRAY_BUFFER, _id);
}
void ElementBuffer::UnSelect()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}