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

	class Vector2 final {

	public:
		float x;
		float y;

		static const Vector2 Vec2Zero;
		static const Vector2 Vec2EX;
		static const Vector2 Vec2EY;
	public:

		// Default Constructor
		Vector2() = default;
		// Conversion Constructor
		Vector2(const float& _x, const float& _y = 0.f);
		// Copy constructor
		Vector2(const Vector2& _v);
		// Default destructor
		~Vector2() {}

		// Assignment operator
		Vector2& operator=(const Vector2& _v);

		// Calc distance to the given point
		double Distance(const Vector2& _pt) const;

		// Get the dot product of this vector and _v
		float Dot(const Vector2& _v) const;

		// See if a point is finite (e.g., not nan)
		bool IsFinite() const;

		// Get the length (magnitude) of the vector
		float Length() const;

		// Get the square of the length (magnitude) of the vector
		float SquaredLength() const;


		// Normalize the vector length.
		void Normalize();

		// Set the contents of the vector
		void Set(float _x = 0.f, float _y = 0.f);

		// Equal to operator.
		bool operator==(const Vector2& _v) const;

		// Not equal to operator.
		bool operator!=(const Vector2& _v) const;

		// less than operator.
		bool operator<(const Vector2& _v) const;

		// Multiplication operators
		const Vector2 operator*(const Vector2& _v) const;

		// Multiplication operators
		const Vector2 operator*(float _v) const;

		// Multiplication assignment operator
		const Vector2& operator*=(const Vector2& _v);

		// Multiplication assignment operator
		const Vector2& operator*=(float _v);

		// Addition operator
		const Vector2 operator+(const Vector2& _v) const;

		// Addition assignment  operator
		const Vector2& operator+=(const Vector2& _v);

		// Subtraction operator
		const Vector2 operator-(const Vector2& _v) const;

		// Subtraction assignment  operator
		const Vector2& operator-=(const Vector2& _v);

		// Division operator
		const Vector2 operator/(const Vector2& _v) const;
		// Division assignment  operator
		const Vector2& operator/=(const Vector2& _v);

		// Array subscript operator.
		float operator[](size_t index) const;

		// Stream extraction operator, output stream
		friend std::ostream& operator<<(std::ostream& _out, const Vector2& _v);

		// Stream insertion operator, input stream
		friend std::istream& operator>>(std::istream& _in, Vector2& _v);
	};
}

#endif
