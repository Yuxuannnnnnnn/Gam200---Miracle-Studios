#pragma once
#include "glew.h"

class ElementBuffer
{
public:
	ElementBuffer()
	{

	}
	ElementBuffer(const GLuint* data, unsigned int count);
	~ElementBuffer();
	void Select() const;
	void UnSelect() const;

	inline unsigned int GetCount() const 
	{
		return _count;
	}
private:
	GLuint _id;
	unsigned _count;

};