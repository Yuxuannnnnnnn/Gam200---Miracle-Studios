#pragma once
#include "glew.h"

class ElementBuffer
{
public:
	ElementBuffer()
	{

	}
	ElementBuffer(unsigned int* data, unsigned int count);
	~ElementBuffer();
	void Select();
	void UnSelect();

	inline unsigned int GetCount() const 
	{
		return _count;
	}
private:
	GLuint _id;
	unsigned _count;

};