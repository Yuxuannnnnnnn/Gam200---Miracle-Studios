///////////////////////////////////////////////////////////////////////////////////////
//
//	Vector2.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _SHUYU_VECTOR2_H
#define _SHUYU_VECTOR2_H

#include <cmath>
#include <fstream>

/* 
1 byte  -> bool, char, unsigned char, signed char, __int8	
2 bytes -> __int16, short, unsigned short, wchar_t, __wchar_t	
4 bytes -> float, __int32, int, unsigned int, long, unsigned long	
8 bytes -> double, __int64, long double, long long	
*/

namespace mathLib {

	typedef union Vector2 {

	public:
		struct
		{
			float _x;
			float _y;
		};

		float m[2];

		static const Vector2 Vec2Zero;
		static const Vector2 Vec2EX;
		static const Vector2 Vec2EY;
	public:

		// Default Constructor
		Vector2();
		// Conversion Constructor
		Vector2(const float& x, const float& y = 0.f);
		// Copy constructor
		Vector2(const Vector2& rhs);
		// Default destructor
		~Vector2() {}

		Vector2& operator=(const Vector2& rhs);
		float operator[](size_t index) const;

		float& GetX();
		float& GetY();
		void SetX(const float& x);
		void SetY(const float& y);
		void Set(float x = 0.f, float y = 0.f);

	public: // other function

		float Sum() const;

		float Distance(const Vector2& pt) const;
		float Distance(float x, float y) const;

		float Length() const;
		float SquaredLength() const;

		Vector2& Normalize();
		Vector2 Normalized() const;

		Vector2& Round();
		Vector2 Rounded() const;

		Vector2 Cross(const Vector2& v) const;
		float Dot(const Vector2& v) const;
		float AbsDot(const Vector2& v) const;

		Vector2 Abs() const;

		bool IsFinite() const;

		// problems : not fix
		//static float DistToLine(const Vector2& lineEdge1, const Vector2& lineEdge2, const Vector2& pt);
		//static Vector2 Normal(const Vector2& v1, const Vector2& v2, const Vector2& v3);

		friend std::ostream& operator<<(std::ostream& out, const Vector2& v);
		friend std::istream& operator>>(std::istream& in, Vector2& v);
	
	} Vector2, Vec2;

	Vector2 operator+(const Vector2& lhs);
	Vector2 operator-(const Vector2& lhs);
	Vector2 operator+(const Vector2& lhs, const Vector2& rhs);
	Vector2 operator-(const Vector2& lhs, const Vector2& rhs);
	Vector2 operator*(const Vector2& lhs, const Vector2& rhs);
	Vector2 operator/(const Vector2& lhs, const Vector2& rhs);

	Vector2& operator+=(Vector2& lhs, const Vector2& rhs);
	Vector2& operator-=(Vector2& lhs, const Vector2& rhs);
	Vector2& operator*=(Vector2& lhs, const Vector2& rhs);
	Vector2& operator/=(Vector2& lhs, const Vector2& rhs);

	Vector2 operator*(const Vector2& lhs, const float& rhs);
	Vector2 operator*(const float& lhs, const Vector2& rhs);

	Vector2 operator/(const Vector2& lhs, const float& rhs);
	//Vector2 operator/(const float& lhs, const Vector2& rhs);

	Vector2& operator*=(Vector2& lhs, const float& rhs);
	Vector2& operator*=(const float& lhs, Vector2& rhs);

	Vector2& operator/=(Vector2& lhs, const float& rhs);
	//Vector2& operator/=(const float& lhs, Vector2& rhs);

	bool operator==(const Vector2& lhs, const Vector2& rhs);
	bool operator!=(const Vector2& lhs, const Vector2& rhs);
	//bool operator<(const Vector2& lhs, const Vector2& rhs);
	//bool operator>(const Vector2& lhs, const Vector2& rhs);
	//bool operator<=(const Vector2& lhs, const Vector2& rhs);
	//bool operator>=(const Vector2& lhs, const Vector2& rhs);
}

#endif
