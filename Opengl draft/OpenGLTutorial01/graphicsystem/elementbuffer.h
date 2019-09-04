#pragma once
#include "glew.h"

class ElementBuffer
{
public:
	ElementBuffer(unsigned int* data, unsigned int count);
	~ElementBuffer();
	void Bind();
	void Unbind();

	inline unsigned int GetCount() const {
		return _count;
	}
private:
	GLuint _id;
	unsigned _count;

};