///////////////////////////////////////////////////////////////////////////////////////
//
//	Matrix4x4.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _MATRIX4X4_H_
#define _MATRIX4X4_H_

#include "Vector3.h"

namespace mathLib
{
#ifdef _MSC_VER
	// Supress warning: nonstandard extension used : nameless struct/union
#pragma warning( disable : 4201 )
#endif

	typedef union Matrix4x4
	{
		struct
		{
			float m00, m01, m02, m03;
			float m10, m11, m12, m13;
			float m20, m21, m22, m23;
			float m30, m31, m32, m33;
		};

		float m[16];
		float m2[4][4];

		Matrix4x4();
		Matrix4x4(const float* pArr);
		Matrix4x4(float _00, float _01, float _02, float _03,
			float _10, float _11, float _12, float _13,
			float _20, float _21, float _22, float _23,
			float _30, float _31, float _32,float _33);

		// Assignment operators
		Matrix4x4& operator=(const Matrix4x4& rhs);
		Matrix4x4& operator += (const Matrix4x4& rhs);
		Matrix4x4& operator -= (const Matrix4x4& rhs);
		Matrix4x4& operator *= (const Matrix4x4& rhs);
		Matrix4x4& operator *= (const float& rhs);

		Matrix4x4 operator+(const Matrix4x4& rhs);
		Matrix4x4 operator-(const Matrix4x4& rhs);
		Matrix4x4 operator*(const Matrix4x4& rhs);
		Matrix4x4 operator*(const float& rhs);

		static Matrix4x4 CreateScale(Vector3 scale);
		static Matrix4x4 CreateTranslation(Vector3 translation);
		static Matrix4x4 CreateRotationX(float angle);
		static Matrix4x4 CreateRotationY(float angle);
		static Matrix4x4 CreateRotationZ(float angle);
		static Matrix4x4 CreateView(Vector3 forward, Vector3 up, Vector3 right, Vector3 position);
		static Matrix4x4 CreatePerspectiveProjection(float width, float height, float fov, float nearPlane, float farPlane);
		static Matrix4x4 CreateOrthographicProjection(float left, float right, float top, float bottom, float farPlane, float nearPlane);


	} Matrix4x4, Mtx44;

#ifdef _MSC_VER
	// Supress warning: nonstandard extension used : nameless struct/union
#pragma warning( default : 4201 )
#endif
}

#endif 
