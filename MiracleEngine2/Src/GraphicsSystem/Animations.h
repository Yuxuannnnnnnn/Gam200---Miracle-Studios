#pragma once


#include "glew.h"
#include <iostream>
class Animations
{
public:
	Animations(const void* data, unsigned int size);
	Animations();
	~Animations();

	void Select(double dt = 0.0);
	void UnSelect();
private:

	GLuint _id;
	double _frame = 1.0f;
	double _timer = 1.0f;
	int i = 0;
};