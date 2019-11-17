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

using namespace mathLib;

#define PI acos(-1)

float Vec3Distance_LinetoPoint(Vector3 P, Vector3 Q, Vector3 R);

void Vec3Scale(Vector3& pResult, Vector3& pVec0, float s);

void Vec3Add(Vector3& pResult, Vector3& pVec0, Vector3& pVec1);

void Vec3Zero(Vector3& pResult);

#endif
