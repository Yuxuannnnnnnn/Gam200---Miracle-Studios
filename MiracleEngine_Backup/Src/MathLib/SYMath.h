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

using namespace mathLib;

#define PI acos(-1)

////////////////////////////////////////////////////////////////////////////////
/*!
@brief  the Shortest Distance Algorithm for a line segment to a point.

@param	Vector3 P
	The first vertex of the line segment
@param	Vector3 Q
	The second vertex of the line segment
@param	Vector3 R
	Arbitrary point to calculate its shortest distance to the line
	segment PQ.

@return
	The shortest possible distance, as a floating point value, between
	the specified line segment and the arbitrary point.
*/
////////////////////////////////////////////////////////////////////////////////
float Vec3Distance_LinetoPoint(Vector3 P, Vector3 Q, Vector3 R);

void Vec3Scale(Vector3& pResult, Vector3& pVec0, float s);

void Vec3Add(Vector3& pResult, Vector3& pVec0, Vector3& pVec1);

void Vec3Zero(Vector3& pResult);

#endif
