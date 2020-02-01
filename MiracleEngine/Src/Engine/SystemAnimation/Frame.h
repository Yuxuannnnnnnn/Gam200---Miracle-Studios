#pragma once

#ifndef FRAME_H
#define FRAME_H
#include "SystemGraphics/QuadMesh.h"
#include "Tools/FileIO/DeSerialiser.h"



/* ------------------------------------------------------
	frame constructor take in uv offset of bottom left 
	and top right vertices

	_u0, _v0 - bottom left
	_u1, _v1 - top right

 --------------------------------------------------------*/

class Frame
{
public:
	Frame() = default;
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

