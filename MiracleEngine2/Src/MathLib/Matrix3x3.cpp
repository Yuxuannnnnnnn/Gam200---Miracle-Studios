///////////////////////////////////////////////////////////////////////////////////////
//
//	Vector3.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#include "PrecompiledHeaders.h"
#include "Matrix3x3.h"
#include <math.h> // cosf, sinf, fabsf
#define EPSILON    0.0001f
#define PI      3.14159265358f

namespace mathLib
{

	Matrix3x3::Matrix3x3() :
		m00{ 0.f }, m01{ 0.f }, m02{ 0.f },
		m10{ 0.f }, m11{ 0.f }, m12{ 0.f },
		m20{ 0.f }, m21{ 0.f }, m22{ 0.f }
	{
	}
  
	Matrix3x3::Matrix3x3(const float* pArr) :
		m00{ 0.f }, m01{ 0.f }, m02{ 0.f },
		m10{ 0.f }, m11{ 0.f }, m12{ 0.f },
		m20{ 0.f }, m21{ 0.f }, m22{ 0.f }
	{
		for (int i = 0; i < 9; ++i)
			m[i] = pArr[i];

	}
  
	Matrix3x3::Matrix3x3(float _00, float _01, float _02, 
						float _10, float _11, float _12, 
						float _20, float _21, float _22) :
		m00{ _00 }, m01{ _01 }, m02{ _02 },
		m10{ _10 }, m11{ _11 }, m12{ _12 },
		m20{ _20 }, m21{ _21 }, m22{ _22 }
	{
	}
  

	Matrix3x3& Matrix3x3::operator=(const Matrix3x3& rhs)
	{
		if (this == &rhs)
			return *this;

		for (int i = 0; i < 9; ++i)
			m[i] = rhs.m[i];

		return *this;
	}
  

	Matrix3x3& Matrix3x3::operator*=(const Matrix3x3& rhs)
	{
	// m00 m01 m02
	// m10 m11 m12
	// m20 m21 m22

	//x1 x2 x3   a1 a2 a3   X1 X2 X3
	//y1 y2 y3 X b1 b2 b3 = Y1 Y2 Y3
	//z1 z2 z3   c1 c2 c3   Z1 Z2 Z3
    
	//X1 = (x1 * a1) + (x2 * b1) + (x3 * c1)
	//Y1 = (y1 * a1) + (y2 * b1) + (y3 * c1)
	//Z1 = (z1 * a1) + (z2 * b1) + (z3 * c1)
	//etc...

	float X1 = (m00 * rhs.m00) + (m01 * rhs.m10) + (m02 * rhs.m20);
	float Y1 = (m10 * rhs.m00) + (m11 * rhs.m10) + (m12 * rhs.m20);
	float Z1 = (m20 * rhs.m00) + (m21 * rhs.m10) + (m22 * rhs.m20);
   
	float X2 = (m00 * rhs.m01) + (m01 * rhs.m11) + (m02 * rhs.m21);
	float Y2 = (m10 * rhs.m01) + (m11 * rhs.m11) + (m12 * rhs.m21);
	float Z2 = (m20 * rhs.m01) + (m21 * rhs.m11) + (m22 * rhs.m21);
    
	float X3 = (m00 * rhs.m02) + (m01 * rhs.m12) + (m02 * rhs.m22);
	float Y3 = (m10 * rhs.m02) + (m11 * rhs.m12) + (m12 * rhs.m22);
	float Z3 = (m20 * rhs.m02) + (m21 * rhs.m12) + (m22 * rhs.m22);
   
	m00 = X1;
	m10 = Y1;
	m20 = Z1;
    
	m01 = X2;
	m11 = Y2;
	m21 = Z2;
    
	m02 = X3;
	m12 = Y3;
	m22 = Z3;
    
	return *this;
	}
  

	Matrix3x3 operator*(const Matrix3x3& lhs, const Matrix3x3& rhs)
	{
	Matrix3x3 result = lhs;
	result *= rhs;
	return result;
	}

	Vector2 operator*(const Matrix3x3& pMtx, const Vector2& rhs)
	{
	// m00 m01 m02
	// m10 m11 m12
	// m20 m21 m22

	//x1 x2 x3   a   X
	//y1 y2 y3 X b = Y
	//z1 z2 z3   1   Z
    
	//X = (x1 * a) + (x2 * b) + (x3 * 1)
	//Y = (y1 * a) + (y2 * b) + (y3 * 1)
	//Z = (z1 * a) + (z2 * b) + (z3 * 1)
    
		Vector2 result;
	result.x = (pMtx.m00 * rhs.x) + (pMtx.m01 * rhs.y) + pMtx.m02;
	result.y = (pMtx.m10 * rhs.x) + (pMtx.m11 * rhs.y) + pMtx.m12;
	// no Z, only 2D
    
	return result;
	}
  
	void Mtx33Identity(Matrix3x3& pResult)
	{
	// 1 0 0 
	// 0 1 0 = Identity Matrix 
	// 0 0 1 
    
	pResult.m00 = 1;
	pResult.m01 = 0;
	pResult.m02 = 0;

	pResult.m10 = 0;
	pResult.m11 = 1;
	pResult.m12 = 0;

	pResult.m20 = 0;
	pResult.m21 = 0;
	pResult.m22 = 1;
	}
  
	void Mtx33Translate(Matrix3x3& pResult, float x, float y)
	{
	// m00 m01 m02
	// m10 m11 m12
	// m20 m21 m22
    
	//1 0 x
	//0 1 y
	//0 0 1
    
	Mtx33Identity(pResult);
	pResult.m02 = x;
	pResult.m12 = y;
	}

	void Mtx33Scale(Matrix3x3& pResult, float x, float y)
	{
	// m00 m01 m02
	// m10 m11 m12
	// m20 m21 m22
    
	//x 0 0
	//0 y 0
	//0 0 1
    
	Mtx33Identity(pResult);
	pResult.m00 = x;
	pResult.m11 = y;
	}
 

	void Mtx33RotRad(Matrix3x3& pResult, float angle)
	{
	// m00 m01 m02
	// m10 m11 m12
	// m20 m21 m22
    
	//cos(r) -sin(r) 0
	//sin(r)  cos(r) 0
	//  0       0    1
    
	Mtx33Identity(pResult);
	pResult.m00 = cosf(angle);
	pResult.m01 = -sinf(angle);
	pResult.m10 = sinf(angle);
	pResult.m11 = cosf(angle);
	}
  

	void Mtx33RotDeg(Matrix3x3& pResult, float angle)
	{
	Mtx33RotRad(pResult, angle * PI / 180);
	}
  
	void Mtx33Transpose(Matrix3x3& pResult, const Matrix3x3& pMtx)
	{
	// m00 m01 m02
	// m10 m11 m12
	// m20 m21 m22
    
	// x1 x2 x3   x1 y1 z1
	// y1 y2 y3 = x2 y2 z2
	// z1 z2 z3   x3 y3 z3
    
	Matrix3x3 temp = pMtx;
    
	pResult.m00 = temp.m00;
	pResult.m01 = temp.m10;
	pResult.m02 = temp.m20;

	pResult.m10 = temp.m01;
	pResult.m11 = temp.m11;
	pResult.m12 = temp.m21;

	pResult.m20 = temp.m02;
	pResult.m21 = temp.m12;
	pResult.m22 = temp.m22;
	}

	void Mtx33Inverse(Matrix3x3* pResult, float* determinant, 
										const Matrix3x3& pMtx)
	{
	// m00 m01 m02
	// m10 m11 m12
	// m20 m21 m22
    
	// x1 x2 x3   +X1 -X2 +X3
	// y1 y2 y3 = -Y1 +Y2 -Y3 * (1 / det)
	// z1 z2 z3   +Z1 -Z2 +Z3
    
	// +X1 =  ((y2 * z3) - (z2 * y3))
	// -X2 = -((y1 * z3) - (z1 * y3))
	// +X2 =  ((y1 * z2) - (z1 * y2))
	//etc...
    
	//Find Adj matrix
	Matrix3x3 Adj;
	Adj.m00 = (pMtx.m11 * pMtx.m22) - (pMtx.m21 * pMtx.m12);
	Adj.m01 = -((pMtx.m10 * pMtx.m22) - (pMtx.m20 * pMtx.m12));
	Adj.m02 = (pMtx.m10 * pMtx.m21) - (pMtx.m20 * pMtx.m11);

	Adj.m10 = -((pMtx.m01 * pMtx.m22) - (pMtx.m21 * pMtx.m02));
	Adj.m11 = (pMtx.m00 * pMtx.m22) - (pMtx.m20 * pMtx.m02);
	Adj.m12 = -((pMtx.m00 * pMtx.m21) - (pMtx.m20 * pMtx.m01));

	Adj.m20 = (pMtx.m01 * pMtx.m12) - (pMtx.m11 * pMtx.m02);
	Adj.m21 = -((pMtx.m00 * pMtx.m12) - (pMtx.m10 * pMtx.m02));
	Adj.m22 = (pMtx.m00 * pMtx.m11) - (pMtx.m10 * pMtx.m01);

	//Calculate and checks if determinant is close to 0
	*determinant = (pMtx.m00 * Adj.m00) + (pMtx.m01 * Adj.m01) 
					+ (pMtx.m02 * Adj.m02);
	if (fabsf(*determinant) < EPSILON)
	{
		pResult = NULL;
		return;
	}
    
	for (int i = 0; i < 9; ++i)
		pResult->m[i] = Adj.m[i] / *determinant;
    
	//Transpose inverse matrix
	Mtx33Transpose(*pResult, *pResult);
	}
}

