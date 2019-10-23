#include "PrecompiledHeaders.h"
#include "Matrix4x4.h"

namespace mathLib
{

	Matrix4x4::Matrix4x4() :
		m00{ 0.f }, m01{ 0.f }, m02{ 0.f }, m03{ 0.f },
		m10{ 0.f }, m11{ 0.f }, m12{ 0.f }, m13{ 0.f },
		m20{ 0.f }, m21{ 0.f }, m22{ 0.f }, m23{ 0.f },
		m30{ 0.f }, m31{ 0.f }, m32{ 0.f }, m33{ 0.f }
	{
	}

	Matrix4x4::Matrix4x4(const float* pArr) :
		m00{ 0.f }, m01{ 0.f }, m02{ 0.f }, m03{ 0.f },
		m10{ 0.f }, m11{ 0.f }, m12{ 0.f }, m13{ 0.f },
		m20{ 0.f }, m21{ 0.f }, m22{ 0.f }, m23{ 0.f },
		m30{ 0.f }, m31{ 0.f }, m32{ 0.f }, m33{ 0.f }
	{
		for (int i = 0; i < 16; ++i)
			m[i] = pArr[i];
	}

	Matrix4x4::Matrix4x4(float _00, float _01, float _02, float _03, 
		float _10, float _11, float _12, float _13, 
		float _20, float _21, float _22, float _23, 
		float _30, float _31, float _32, float _33) :
		m00{ _00 }, m01{ _01 }, m02{ _02 }, m03{ _03 },
		m10{ _10 }, m11{ _11 }, m12{ _12 }, m13{ _13 },
		m20{ _20 }, m21{ _21 }, m22{ _22 }, m23{ _23 },
		m30{ _30 }, m31{ _31 }, m32{ _32 }, m33{ _33 }
	{
	}

	Matrix4x4& Matrix4x4::operator=(const Matrix4x4& rhs)
	{
		if (this == &rhs)
			return *this;

		for (int i = 0; i < 16; ++i)
			m[i] = rhs.m[i];

		return *this;
	}

	Matrix4x4& Matrix4x4::operator+=(const Matrix4x4& rhs)
	{
		for (int i = 0; i < 16; i++)
			m[i] += rhs.m[i];

		return *this;
	}

	Matrix4x4& Matrix4x4::operator-=(const Matrix4x4& rhs)
	{
		for (int i = 0; i < 16; i++)
			m[i] -= rhs.m[i];

		return *this;
	}

	Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& rhs)
	{
		// m00 m01 m02 m03
		// m10 m11 m12 m13
		// m20 m21 m22 m23
		// m30 m31 m32 m33 

		//x1 x2 x3 x4   a1 a2 a3 a4   X1 X2 X3 X4
		//y1 y2 y3 y4 X b1 b2 b3 b4 = Y1 Y2 Y3 Y4
		//z1 z2 z3 z4   c1 c2 c3 c4   Z1 Z2 Z3 Z4
		//w1 w2 w3 w4   d1 d2 d3 d4   W1 W2 W3 W4

		//X1 = (x1 * a1) + (x2 * b1) + (x3 * c1) + (x4 * d1)
		//Y1 = (y1 * a1) + (y2 * b1) + (y3 * c1) + (y4 * d1)
		//Z1 = (z1 * a1) + (z2 * b1) + (z3 * c1) + (z4 * d1)
		//W1 = (w1 * a1) + (w2 * b1) + (w3 * c1) + (w4 * d1)
		//etc...

		float X1 = (m00 * rhs.m00) + (m01 * rhs.m10) + (m02 * rhs.m20) + (m03 * rhs.m30);
		float Y1 = (m10 * rhs.m00) + (m11 * rhs.m10) + (m12 * rhs.m20) + (m13 * rhs.m30);
		float Z1 = (m20 * rhs.m00) + (m21 * rhs.m10) + (m22 * rhs.m20) + (m23 * rhs.m30);
		float W1 = (m30 * rhs.m00) + (m31 * rhs.m10) + (m32 * rhs.m20) + (m33 * rhs.m30);

		float X2 = (m00 * rhs.m01) + (m01 * rhs.m11) + (m02 * rhs.m21) + (m03 * rhs.m31);
		float Y2 = (m10 * rhs.m01) + (m11 * rhs.m11) + (m12 * rhs.m21) + (m13 * rhs.m31);
		float Z2 = (m20 * rhs.m01) + (m21 * rhs.m11) + (m22 * rhs.m21) + (m23 * rhs.m31);
		float W2 = (m30 * rhs.m01) + (m31 * rhs.m11) + (m32 * rhs.m21) + (m33 * rhs.m31);

		float X3 = (m00 * rhs.m02) + (m01 * rhs.m12) + (m02 * rhs.m22) + (m03 * rhs.m32);
		float Y3 = (m10 * rhs.m02) + (m11 * rhs.m12) + (m12 * rhs.m22) + (m13 * rhs.m32);
		float Z3 = (m20 * rhs.m02) + (m21 * rhs.m12) + (m22 * rhs.m22) + (m23 * rhs.m32);
		float W3 = (m30 * rhs.m02) + (m31 * rhs.m12) + (m32 * rhs.m22) + (m33 * rhs.m32);

		float X4 = (m00 * rhs.m03) + (m01 * rhs.m13) + (m02 * rhs.m23) + (m03 * rhs.m33);
		float Y4 = (m10 * rhs.m03) + (m11 * rhs.m13) + (m12 * rhs.m23) + (m13 * rhs.m33);
		float Z4 = (m20 * rhs.m03) + (m21 * rhs.m13) + (m22 * rhs.m23) + (m23 * rhs.m33);
		float W4 = (m30 * rhs.m03) + (m31 * rhs.m13) + (m32 * rhs.m23) + (m33 * rhs.m33);

		m00 = X1;
		m10 = Y1;
		m20 = Z1;
		m30 = W1;

		m01 = X2;
		m11 = Y2;
		m21 = Z2;
		m31 = W2;

		m02 = X3;
		m12 = Y3;
		m22 = Z3;
		m32 = W3;

		m03 = X4;
		m13 = Y4;
		m23 = Z4;
		m33 = W4;

		return *this;
	}

	Matrix4x4& Matrix4x4::operator*=(const float& rhs)
	{
		for (int i = 0; i < 16; i++)
			m[i] *= rhs;

		return *this;
	}

	Matrix4x4 Matrix4x4::operator+(const Matrix4x4& rhs)
	{
		Matrix4x4 result(this->m);
		result += rhs;
		return result;

	}
	Matrix4x4 Matrix4x4::operator-(const Matrix4x4& rhs)
	{
		Matrix4x4 result(this->m);
		result -= rhs;
		return result;

	}
	Matrix4x4 Matrix4x4::operator*(const Matrix4x4& rhs)
	{
		Matrix4x4 result(this->m);
		result *= rhs;
		return result;
	}

	Matrix4x4 Matrix4x4::operator*(const float& rhs)
	{
		Matrix4x4 result(this->m);
		result *= rhs;
		return result;
	}

	Matrix4x4 Matrix4x4::CreateScale(Vector3 scale)
	{
		Matrix4x4 newMatrix = Matrix4x4();
		newMatrix.m2[0] = scale.x;
		newMatrix.m2[5] = scale.y;
		newMatrix.m2[10] = scale.z;
		return newMatrix;
	}

	Matrix4x4 Matrix4x4::CreateTranslation(Vector3 translation)
	{
		Matrix4x4 newMatrix = Matrix4x4();
		newMatrix.m2[3] = translation.x;
		newMatrix.m2[7] = translation.y;
		newMatrix.m2[11] = translation.z;
		return newMatrix;
	}

	Matrix4x4 Matrix4x4::CreateRotationX(float angle)
	{
		Matrix4x4 newMatrix = Matrix4x4();
		newMatrix.m2[5] = std::cos(-angle);
		newMatrix.m2[6] = -std::sin(-angle);
		newMatrix.m2[9] = std::sin(-angle);
		newMatrix.m2[10] = std::cos(-angle);
		return newMatrix;
	}

	Matrix4x4 Matrix4x4::CreateRotationY(float angle)
	{
		Matrix4x4 newMatrix = Matrix4x4();
		newMatrix.m2[0] = std::cos(-angle);
		newMatrix.m2[2] = std::sin(-angle);
		newMatrix.m2[8] = -std::sin(-angle);
		newMatrix.m2[10] = std::cos(-angle);
		return newMatrix;
	}

	Matrix4x4 Matrix4x4::CreateRotationZ(float angle)
	{
		Matrix4x4 newMatrix = Matrix4x4();
		newMatrix.m2[0] = std::cos(-angle);
		newMatrix.m2[1] = -std::sin(-angle);
		newMatrix.m2[4] = std::sin(-angle);
		newMatrix.m2[5] = std::cos(-angle);
		return newMatrix;
	}

	Matrix4x4 Matrix4x4::CreateView(Vector3 forward, Vector3 up, Vector3 right, Vector3 position)
	{
		Matrix4x4 newMatrix = Matrix4x4();
		newMatrix.m2[0] = (1.0f / std::tan((fov * M_PI / 180.0f) / 2.0f)) / (width / height);
		newMatrix.m2[5] = 1.0f / std::tan((fov * M_PI / 180.0f) / 2.0f);
		newMatrix.m2[10] = (farPlane + nearPlane) / (nearPlane - farPlane);
		newMatrix.m2[11] = (2.0f * farPlane * nearPlane) / (nearPlane - farPlane);
		newMatrix.m2[14] = -1.0f;
		return newMatrix;
	}
	}

	Matrix4x4 Matrix4x4::CreatePerspectiveProjection(float width, float height, float fov, float nearPlane, float farPlane)
	{
		Matrix4x4 newMatrix = Matrix4x4();
		newMatrix.m2[0] = (1.0f / std::tan((fov * M_PI / 180.0f) / 2.0f)) / (width / height);
		newMatrix.m2[5] = 1.0f / std::tan((fov * M_PI / 180.0f) / 2.0f);
		newMatrix.m2[10] = (farPlane + nearPlane) / (nearPlane - farPlane);
		newMatrix.m2[11] = (2.0f * farPlane * nearPlane) / (nearPlane - farPlane);
		newMatrix.m2[14] = -1.0f;
		return newMatrix;
	}

	Matrix4x4 Matrix4x4::CreateOrthographicProjection(float left, float right, float top, float bottom, float farPlane, float nearPlane)
	{
		Matrix4x4 newMatrix = Matrix4x4();
		newMatrix.m2[0] = 2.0f / (right - left);
		newMatrix.m2[3] = -((right + left) / (right - left));
		newMatrix.m2[5] = 2.0f / (top - bottom);
		newMatrix.m2[7] = -((top + bottom) / (top - bottom));
		newMatrix.m2[10] = 2.0f / (farPlane - nearPlane);
		newMatrix.m2[11] = -((farPlane + nearPlane) / (farPlane - nearPlane));
		return newMatrix;
	}

}