#pragma once


#include "glew.h"
#include "../Engine/FrameRateController.h"
#include <iostream>
class Animation
{
public:
	Animation(const void* data, unsigned int size);
	Animation();
	~Animation();

	void Select(double dt = 0.0);
	void UnSelect();
private:

	GLuint _id;
	float _frame = 1.0f;
	float _timer = 1.0f;

};