///////////////////////////////////////////////////////////////////////////////////////
//
//	Vector3.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _MATRIX3X3_H_
#define _MATRIX3X3_H_

#include "Vector2.h"

namespace mathLib
{
	#ifdef _MSC_VER
	// Supress warning: nonstandard extension used : nameless struct/union
	#pragma warning( disable : 4201 )
	#endif

	typedef union Matrix3x3
	{
		struct 
		{
			float m00, m01, m02;
			float m10, m11, m12;
			float m20, m21, m22;
		};

		float m[9];
		float m2[3][3];

		Matrix3x3();
		Matrix3x3(const float *pArr);
		Matrix3x3(float _00, float _01, float _02,
				  float _10, float _11, float _12,
				  float _20, float _21, float _22);
		Matrix3x3& operator=(const Matrix3x3 &rhs);

		// Assignment operators
		Matrix3x3& operator *= (const Matrix3x3 &rhs);

	} Matrix3x3, Mtx33;

	#ifdef _MSC_VER
	// Supress warning: nonstandard extension used : nameless struct/union
	#pragma warning( default : 4201 )
	#endif

	Matrix3x3 operator * (const Matrix3x3 &lhs, const Matrix3x3 &rhs);
	

	Vector2  operator * (const Matrix3x3 &pMtx, const Vector2&rhs);
	

	void Mtx33Identity(Matrix3x3 &pResult);
	

	void Mtx33Translate(Matrix3x3 &pResult, float x, float y);
	
	void Mtx33Scale(Matrix3x3 &pResult, float x, float y);
	
	void Mtx33RotRad(Matrix3x3 &pResult, float angle);
	

	void Mtx33RotDeg(Matrix3x3 &pResult, float angle);
	

	void Mtx33Transpose(Matrix3x3 &pResult, const Matrix3x3 &pMtx);
	
	void Mtx33Inverse(Matrix3x3 *pResult, float *determinant, const Matrix3x3 &pMtx);
}

#endif
