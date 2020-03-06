///////////////////////////////////////////////////////////////////////////////////////
//
//	SYMath.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _SHUYU_MATH_LIBRARY_H_
#define _SHUYU_MATH_LIBRARY_H_

#include "Vector2.h"
#include "Vector3.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include <limits>

#define MY_PI 3.141592653589793238463

using namespace mathLib;

float Vec3Distance_LinetoPoint(Vector3 P, Vector3 Q, Vector3 R);
bool Vec3D_InLineRange(Vector3 P, Vector3 Q, Vector3 R);

float RadToDeg(float& rad);
float DegToRad(float& deg);

#endif
