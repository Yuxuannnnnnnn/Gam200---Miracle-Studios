///////////////////////////////////////////////////////////////////////////////////////
//
//	Matrix3x3.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _MATRIX3X3_H_
#define _MATRIX3X3_H_

#define EPSILON    0.0001f
#define PI      acos(-1) //3.14159265358f

#include "Vector2.h"

namespace mathLib
{

	typedef union Matrix3x3 {

	public:
		struct 
		{
			float m00, m01, m02;
			float m10, m11, m12;
			float m20, m21, m22;
		};

		float m[9];
		float m2[3][3];

		static const Matrix3x3 Mtx33Identity;

	public:
		Matrix3x3();
		Matrix3x3(const float *pArr);
		Matrix3x3(float _00, float _01, float _02,
				  float _10, float _11, float _12,
				  float _20, float _21, float _22);

		Matrix3x3& operator=(const Matrix3x3 &rhs);
		float operator[](size_t index) const;

	public:

		static Matrix3x3 CreateScale(Vector2 scale);
		static Matrix3x3 CreateTranslation(Vector2 translation);
		static Matrix3x3 CreateRotation(float RAD_angle);

		static Matrix3x3 CreateTranspose(const Matrix3x3& pMtx);
		static Matrix3x3 CreateInverse(float& determinant, const Matrix3x3& pMtx);


		friend std::ostream& operator<<(std::ostream& out, const Matrix3x3& m);

	} Matrix3x3, Mtx33;

	Matrix3x3& operator+=(Matrix3x3& lhs, const Matrix3x3& rhs);
	Matrix3x3& operator-=(Matrix3x3& lhs, const Matrix3x3& rhs);
	Matrix3x3& operator*=(Matrix3x3& lhs, const Matrix3x3& rhs);
	Matrix3x3& operator*=(Matrix3x3& lhs, const float& rhs);

	Matrix3x3 operator+(const Matrix3x3& lhs, const Matrix3x3& rhs);
	Matrix3x3 operator-(const Matrix3x3& lhs, const Matrix3x3& rhs);
	Matrix3x3 operator*(const Matrix3x3& lhs, const Matrix3x3& rhs);
	Matrix3x3 operator*(const Matrix3x3& lhs, const float& rhs);

	Vector2  operator * (const Matrix3x3 &lhs, const Vector2&rhs);

}

#endif
