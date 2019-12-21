#include "PrecompiledHeaders.h"
#include "Matrix4x4.h"

namespace mathLib {

	const Matrix4x4 Matrix4x4::Mtx44Identity =
		Matrix4x4 { 1.f, 0.f, 0.f, 0.f,
					0.f, 1.f, 0.f, 0.f,
					0.f, 0.f, 1.f, 0.f,
					0.f, 0.f, 0.f, 1.f };

	Matrix4x4::Matrix4x4() :
		m00{ 0.f }, m01{ 0.f }, m02{ 0.f }, m03{ 0.f },
		m10{ 0.f }, m11{ 0.f }, m12{ 0.f }, m13{ 0.f },
		m20{ 0.f }, m21{ 0.f }, m22{ 0.f }, m23{ 0.f },
		m30{ 0.f }, m31{ 0.f }, m32{ 0.f }, m33{ 0.f }
	{}

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
	{}

	Matrix4x4& Matrix4x4::operator=(const Matrix4x4& rhs)
	{
		if (this != &rhs)
		{
			for (int i = 0; i < 16; ++i)
				m[i] = rhs.m[i];
		}

		return *this;
	}

	float Matrix4x4::operator[](size_t index) const
	{
		if (index > 15)
			return 0.f;

		return this->m[index];
	}

	///////////////////////////////////////////////////////////////////////////////

	Matrix4x4 Matrix4x4::CreateScale(Vector3 scale)
	{
		Matrix4x4 newMatrix = Mtx44Identity;
		newMatrix.m[0] = scale._x;
		newMatrix.m[5] = scale._y;
		newMatrix.m[10] = scale._z;
		return newMatrix;
	}

	Matrix4x4 Matrix4x4::CreateTranslation(Vector3 translation)
	{
		Matrix4x4 newMatrix = Mtx44Identity;
		newMatrix.m[3] = translation._x;
		newMatrix.m[7] = translation._y;
		newMatrix.m[11] = translation._z;
		return newMatrix;
	}

	Matrix4x4 Matrix4x4::CreateRotationX(float angle)
	{
		Matrix4x4 newMatrix = Mtx44Identity;
		newMatrix.m[5] = std::cos(-angle);
		newMatrix.m[6] = -std::sin(-angle);
		newMatrix.m[9] = std::sin(-angle);
		newMatrix.m[10] = std::cos(-angle);
		return newMatrix;
	}

	Matrix4x4 Matrix4x4::CreateRotationY(float angle)
	{
		Matrix4x4 newMatrix = Mtx44Identity;
		newMatrix.m[0] = std::cos(-angle);
		newMatrix.m[2] = std::sin(-angle);
		newMatrix.m[8] = -std::sin(-angle);
		newMatrix.m[10] = std::cos(-angle);
		return newMatrix;
	}

	Matrix4x4 Matrix4x4::CreateRotationZ(float angle)
	{
		Matrix4x4 newMatrix = Mtx44Identity;
		newMatrix.m[0] = std::cos(-angle);
		newMatrix.m[1] = -std::sin(-angle);
		newMatrix.m[4] = std::sin(-angle);
		newMatrix.m[5] = std::cos(-angle);
		return newMatrix;
	}

	Matrix4x4 Matrix4x4::CreateView(Vector3 forward, Vector3 up, Vector3 right, Vector3 position)
	{
		Matrix4x4 newMatrixOne = Mtx44Identity;
		newMatrixOne.m[0] = right._x;
		newMatrixOne.m[1] = right._y;
		newMatrixOne.m[2] = right._z;
		newMatrixOne.m[4] = up._x;
		newMatrixOne.m[5] = up._y;
		newMatrixOne.m[6] = up._z;
		newMatrixOne.m[8] = forward._x;
		newMatrixOne.m[9] = forward._y;
		newMatrixOne.m[10] = forward._z;

		Matrix4x4 newMatrixTwo = Mtx44Identity;
		newMatrixTwo.m[3] = -position._x;
		newMatrixTwo.m[7] = -position._y;
		newMatrixTwo.m[11] = -position._z;

		Matrix4x4 newMatrix = newMatrixOne * newMatrixTwo;
		return newMatrix;
	}

	Matrix4x4 Matrix4x4::CreatePerspectiveProjection(float width, float height, float fov, float nearPlane, float farPlane)
	{
		Matrix4x4 newMatrix = Mtx44Identity;
		newMatrix.m[0] = (1.0f / std::tan((fov * M_PI / 180.0f) / 2.0f)) / (width / height);
		newMatrix.m[5] = 1.0f / std::tan((fov * M_PI / 180.0f) / 2.0f);
		newMatrix.m[10] = (farPlane + nearPlane) / (nearPlane - farPlane);
		newMatrix.m[11] = (2.0f * farPlane * nearPlane) / (nearPlane - farPlane);
		newMatrix.m[14] = -1.0f;
		return newMatrix;
	}

	Matrix4x4 Matrix4x4::CreateOrthographicProjection(float left, float right, float top, float bottom, float farPlane, float nearPlane)
	{
		Matrix4x4 newMatrix = Mtx44Identity;
		newMatrix.m[0] = 2.0f / (right - left);
		newMatrix.m[3] = -((right + left) / (right - left));
		newMatrix.m[5] = 2.0f / (top - bottom);
		newMatrix.m[7] = -((top + bottom) / (top - bottom));
		newMatrix.m[10] = 2.0f / (farPlane - nearPlane);
		newMatrix.m[11] = -((farPlane + nearPlane) / (farPlane - nearPlane));
		return newMatrix;
	}

	std::ostream& operator<<(std::ostream& out, const Matrix4x4& m)
	{
		out << m[0] << " " << m[1] << " " << m[2] << " " << m[3]
			<< "\n"
			<< m[4] << " " << m[5] << " " << m[6] << " " << m[7]
			<< "\n"
			<< m[8] << " " << m[9] << " " << m[10] << " " << m[11]
			<< "\n"
			<< m[12] << " " << m[13] << " " << m[14] << " " << m[15];

		return out;
	}

///////////////////////////////////////////////////////////////////////////////

	Matrix4x4& operator+= (Matrix4x4& lhs, const Matrix4x4& rhs)
	{
		for (int i = 0; i < 16; i++)
			lhs.m[i] += rhs.m[i];

		return lhs;
	}

	Matrix4x4& operator-= (Matrix4x4& lhs, const Matrix4x4& rhs)
	{
		for (int i = 0; i < 16; i++)
			lhs.m[i] -= rhs.m[i];

		return lhs;
	}

	Matrix4x4& operator*= (Matrix4x4& lhs, const Matrix4x4& rhs)
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

		float X1 = (lhs.m00 * rhs.m00) + (lhs.m01 * rhs.m10) + (lhs.m02 * rhs.m20) + (lhs.m03 * rhs.m30);
		float Y1 = (lhs.m10 * rhs.m00) + (lhs.m11 * rhs.m10) + (lhs.m12 * rhs.m20) + (lhs.m13 * rhs.m30);
		float Z1 = (lhs.m20 * rhs.m00) + (lhs.m21 * rhs.m10) + (lhs.m22 * rhs.m20) + (lhs.m23 * rhs.m30);
		float W1 = (lhs.m30 * rhs.m00) + (lhs.m31 * rhs.m10) + (lhs.m32 * rhs.m20) + (lhs.m33 * rhs.m30);

		float X2 = (lhs.m00 * rhs.m01) + (lhs.m01 * rhs.m11) + (lhs.m02 * rhs.m21) + (lhs.m03 * rhs.m31);
		float Y2 = (lhs.m10 * rhs.m01) + (lhs.m11 * rhs.m11) + (lhs.m12 * rhs.m21) + (lhs.m13 * rhs.m31);
		float Z2 = (lhs.m20 * rhs.m01) + (lhs.m21 * rhs.m11) + (lhs.m22 * rhs.m21) + (lhs.m23 * rhs.m31);
		float W2 = (lhs.m30 * rhs.m01) + (lhs.m31 * rhs.m11) + (lhs.m32 * rhs.m21) + (lhs.m33 * rhs.m31);

		float X3 = (lhs.m00 * rhs.m02) + (lhs.m01 * rhs.m12) + (lhs.m02 * rhs.m22) + (lhs.m03 * rhs.m32);
		float Y3 = (lhs.m10 * rhs.m02) + (lhs.m11 * rhs.m12) + (lhs.m12 * rhs.m22) + (lhs.m13 * rhs.m32);
		float Z3 = (lhs.m20 * rhs.m02) + (lhs.m21 * rhs.m12) + (lhs.m22 * rhs.m22) + (lhs.m23 * rhs.m32);
		float W3 = (lhs.m30 * rhs.m02) + (lhs.m31 * rhs.m12) + (lhs.m32 * rhs.m22) + (lhs.m33 * rhs.m32);

		float X4 = (lhs.m00 * rhs.m03) + (lhs.m01 * rhs.m13) + (lhs.m02 * rhs.m23) + (lhs.m03 * rhs.m33);
		float Y4 = (lhs.m10 * rhs.m03) + (lhs.m11 * rhs.m13) + (lhs.m12 * rhs.m23) + (lhs.m13 * rhs.m33);
		float Z4 = (lhs.m20 * rhs.m03) + (lhs.m21 * rhs.m13) + (lhs.m22 * rhs.m23) + (lhs.m23 * rhs.m33);
		float W4 = (lhs.m30 * rhs.m03) + (lhs.m31 * rhs.m13) + (lhs.m32 * rhs.m23) + (lhs.m33 * rhs.m33);

		lhs.m00 = X1;
		lhs.m10 = Y1;
		lhs.m20 = Z1;
		lhs.m30 = W1;

		lhs.m01 = X2;
		lhs.m11 = Y2;
		lhs.m21 = Z2;
		lhs.m31 = W2;

		lhs.m02 = X3;
		lhs.m12 = Y3;
		lhs.m22 = Z3;
		lhs.m32 = W3;

		lhs.m03 = X4;
		lhs.m13 = Y4;
		lhs.m23 = Z4;
		lhs.m33 = W4;

		return lhs;
	}

	Matrix4x4& operator*= (Matrix4x4& lhs, const float& rhs)
	{
		for (int i = 0; i < 16; i++)
			lhs.m[i] *= rhs;

		return lhs;
	}

	Matrix4x4 operator+(const Matrix4x4& lhs, const Matrix4x4& rhs)
	{
		Matrix4x4 result(lhs.m);
		result += rhs;
		return result;
	}

	Matrix4x4 operator-(const Matrix4x4& lhs, const Matrix4x4& rhs)
	{
		Matrix4x4 result(lhs.m);
		result -= rhs;
		return result;
	}

	Matrix4x4 operator*(const Matrix4x4& lhs, const Matrix4x4& rhs)
	{
		Matrix4x4 result(lhs.m);
		result *= rhs;
		return result;
	}

	Matrix4x4 operator*(const Matrix4x4& lhs, const float& rhs)
	{
		Matrix4x4 result(lhs.m);
		result *= rhs;
		return result;
	}

}
