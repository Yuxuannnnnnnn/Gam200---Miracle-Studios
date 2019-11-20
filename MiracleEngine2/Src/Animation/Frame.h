#pragma once

#ifndef FRAME_H
#define FRAME_H
#include "../GraphicsSystem/QuadMesh.h"


/* ------------------------------------------------------

 --------------------------------------------------------*/

class Frame
{
public:
	Frame(float u0, float v0, float u1, float v1);
	void Select();

	float _timedelay = 0.1;
	float _u0;
	float _v0;

	float _u1;
	float _v1;

	//float w;
	//float h;
	QuadMesh _quadMesh;
};

#endif

