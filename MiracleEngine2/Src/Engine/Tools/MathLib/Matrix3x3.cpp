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

namespace mathLib {

	const Matrix3x3 Matrix3x3::Mtx33Identity =
		Matrix3x3 { 1.f, 0.f, 0.f,
					0.f, 1.f, 0.f,
					0.f, 0.f, 1.f};

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
		if (this != &rhs)
		{
			for (int i = 0; i < 9; ++i)
				m[i] = rhs.m[i];
		}

		return *this;
	}

	float Matrix3x3::operator[](size_t index) const
	{
		if (index > 8)
			return 0.f;

		return this->m[index];
	}

///////////////////////////////////////////////////////////////////////////////
  
	Matrix3x3 Matrix3x3::CreateScale(Vector2 scale)
	{
		Matrix3x3 newMatrix = Mtx33Identity;
		newMatrix.m[0] = scale._x;
		newMatrix.m[4] = scale._y;
		return newMatrix;
	}

	Matrix3x3 Matrix3x3::CreateTranslation(Vector2 translation)
	{
		Matrix3x3 newMatrix = Mtx33Identity;
		newMatrix.m[2] = translation._x;
		newMatrix.m[5] = translation._y;
		return newMatrix;
	}

	Matrix3x3 Matrix3x3::CreateRotation(float angle)
	{
		// m00 m01 m02
		// m10 m11 m12
		// m20 m21 m22

		//cos(r) -sin(r) 0
		//sin(r)  cos(r) 0
		//  0       0    1

		// rad = angle in deg  * PI / 180

		Matrix3x3 newMatrix = Mtx33Identity;
		newMatrix.m[0] = cosf(angle);
		newMatrix.m[1] = -sinf(angle);
		newMatrix.m[3] = sinf(angle);
		newMatrix.m[4] = cosf(angle);
		return newMatrix;
	}

	
  
	Matrix3x3 Matrix3x3::CreateTranspose(const Matrix3x3& pMtx)
	{
		// m00 m01 m02
		// m10 m11 m12
		// m20 m21 m22
    
		// x1 x2 x3   x1 y1 z1
		// y1 y2 y3 = x2 y2 z2
		// z1 z2 z3   x3 y3 z3
    
		Matrix3x3 newMatrix = Matrix3x3{};
    
		newMatrix.m[0] = pMtx.m[0];
		newMatrix.m[1] = pMtx.m[3];
		newMatrix.m[2] = pMtx.m[6];

		newMatrix.m[3] = pMtx.m[1];
		newMatrix.m[4] = pMtx.m[4];
		newMatrix.m[5] = pMtx.m[7];

		newMatrix.m[6] = pMtx.m[2];
		newMatrix.m[7] = pMtx.m[5];
		newMatrix.m[8] = pMtx.m[8];

		return newMatrix;
	}

	Matrix3x3 Matrix3x3::CreateInverse(float& determinant, const Matrix3x3& pMtx)
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
		determinant = (pMtx.m00 * Adj.m00) + (pMtx.m01 * Adj.m01) 
						+ (pMtx.m02 * Adj.m02);

		Matrix3x3 result = Matrix3x3{};

		if (fabsf(determinant) < EPSILON)
			return result;
    
		for (int i = 0; i < 9; ++i)
			result.m[i] = Adj.m[i] / determinant;
    
		//Transpose inverse matrix
		 return CreateTranspose(result);
	}

	std::ostream& operator<<(std::ostream& out, const Matrix3x3& m)
	{
		out << m[0] << " " << m[1] << " " << m[2]
			<< "\n"
			<< m[3] << " " << m[4] << " " << m[5]
			<< "\n"
			<< m[6] << " " << m[7] << " " << m[8];

		return out;
	}

///////////////////////////////////////////////////////////////////////////////

	Matrix3x3& operator+=(Matrix3x3& lhs, const Matrix3x3& rhs)
	{
		for (int i = 0; i < 9; i++)
			lhs.m[i] += rhs.m[i];

		return lhs;
	}

	Matrix3x3& operator-=(Matrix3x3& lhs, const Matrix3x3& rhs)
	{
		for (int i = 0; i < 9; i++)
			lhs.m[i] -= rhs.m[i];

		return lhs;
	}

	Matrix3x3& operator*=(Matrix3x3& lhs, const Matrix3x3& rhs)
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

		float X1 = (lhs.m00 * rhs.m00) + (lhs.m01 * rhs.m10) + (lhs.m02 * rhs.m20);
		float Y1 = (lhs.m10 * rhs.m00) + (lhs.m11 * rhs.m10) + (lhs.m12 * rhs.m20);
		float Z1 = (lhs.m20 * rhs.m00) + (lhs.m21 * rhs.m10) + (lhs.m22 * rhs.m20);

		float X2 = (lhs.m00 * rhs.m01) + (lhs.m01 * rhs.m11) + (lhs.m02 * rhs.m21);
		float Y2 = (lhs.m10 * rhs.m01) + (lhs.m11 * rhs.m11) + (lhs.m12 * rhs.m21);
		float Z2 = (lhs.m20 * rhs.m01) + (lhs.m21 * rhs.m11) + (lhs.m22 * rhs.m21);

		float X3 = (lhs.m00 * rhs.m02) + (lhs.m01 * rhs.m12) + (lhs.m02 * rhs.m22);
		float Y3 = (lhs.m10 * rhs.m02) + (lhs.m11 * rhs.m12) + (lhs.m12 * rhs.m22);
		float Z3 = (lhs.m20 * rhs.m02) + (lhs.m21 * rhs.m12) + (lhs.m22 * rhs.m22);

		lhs.m00 = X1;
		lhs.m10 = Y1;
		lhs.m20 = Z1;

		lhs.m01 = X2;
		lhs.m11 = Y2;
		lhs.m21 = Z2;

		lhs.m02 = X3;
		lhs.m12 = Y3;
		lhs.m22 = Z3;

		return lhs;
	}

	Matrix3x3& operator*=(Matrix3x3& lhs, const float& rhs)
	{
		for (int i = 0; i < 9; i++)
			lhs.m[i] *= rhs;

		return lhs;
	}

	Matrix3x3 operator+(const Matrix3x3& lhs, const Matrix3x3& rhs)
	{
		Matrix3x3 result(lhs.m);
		result += rhs;
		return result;
	}

	Matrix3x3 operator-(const Matrix3x3& lhs, const Matrix3x3& rhs)
	{
		Matrix3x3 result(lhs.m);
		result -= rhs;
		return result;
	}

	Matrix3x3 operator*(const Matrix3x3& lhs, const Matrix3x3& rhs)
	{
		Matrix3x3 result(lhs.m);
		result *= rhs;
		return result;
	}

	Matrix3x3 operator*(const Matrix3x3& lhs, const float& rhs)
	{
		Matrix3x3 result(lhs.m);
		result *= rhs;
		return result;
	}

	Vector2  operator*(const Matrix3x3& lhs, const Vector2& rhs)
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
		result._x = (lhs.m00 * rhs._x) + (lhs.m01 * rhs._y) + lhs.m02;
		result._y = (lhs.m10 * rhs._x) + (lhs.m11 * rhs._y) + lhs.m12;
		// no Z, only 2D

		return result;
	}
}

