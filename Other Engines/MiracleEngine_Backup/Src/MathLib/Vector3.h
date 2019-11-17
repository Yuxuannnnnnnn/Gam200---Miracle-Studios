///////////////////////////////////////////////////////////////////////////////////////
//
//	Vector3.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _SHUYU_VECTOR3_H
#define _SHUYU_VECTOR3_H

#include <cmath>
#include <fstream>

namespace mathLib {

	class Vector3 final {

	public:
		float _x;
		float _y;
		float _z;

		static const Vector3 Vec3Zero;
		static const Vector3 Vec3EX;
		static const Vector3 Vec3EY;
		static const Vector3 Vec3EZ;

	public:
		// Default Constructor
		Vector3();
		// Conversion Constructor
		Vector3(const float& x, const float& y = 0.f, const float& z = 0.f); 
		// Copy constructor
		Vector3(const Vector3& v); 
		// Default Destructor
		~Vector3() {} 

		// Return the sum of the values
		float Sum() const; 
		// Calculation distance to the given point
		float Distance(const Vector3& pt) const; 
		// Calculation distance to the given point
		float Distance(float x, float y, float z) const; 
		// Returns the length (magnitude) of the vector
		float Length() const; 
		// Return the square of the length (magnitude) of the vector
		float SquaredLength() const;
		// Normalize the vector length
		Vector3& Normalize();
		// Return a normalized vector
		Vector3& Normalized() const;
		// Round to near whole number
		Vector3& Round(); 
		// Get a rounded version of this vector
		Vector3 Rounded() const;
			// Set the contents of the vector
		void Set(float x = 0.f, float y = 0.f, float z = 0.f); 
		// Return the cross product of this vector with another vector.
		Vector3 Cross(const Vector3& v) const;
		// Return the dot product of this vector and another vector
		float Dot(const Vector3& v) const; 

			// Return the absolute dot product of this vector and
			// another vector. This is similar to the Dot function, except the
			// absolute value of each component of the vector is used.
		float AbsDot(const Vector3& v) const;

			// Get the absolute value of the vector
		Vector3 Abs() const;


			// Get a normal vector to a triangle
		static Vector3 Normal(const Vector3& v1, const Vector3& v2, const Vector3& v3);

			// Get distance to a line
		float DistToLine(const Vector3& pt1, const Vector3& pt2);

			// Assignment operator
		Vector3& operator=(const Vector3& v);

			// Addition operator
		Vector3 operator+(const Vector3& v) const;

			// Addition assignment operator
		const Vector3& operator+=(const Vector3& v);

			// Subtraction operator
		Vector3 operator-() const;

			// Subtraction operator
		Vector3 operator-(const Vector3& v) const;

			// Subtraction assignment operator
		const Vector3& operator-=(const Vector3& v);

			// Division operator
		Vector3 operator/(const Vector3& v) const;

		Vector3 operator/(const float& v) const;


			//// Division operator
			//Vector3 operator/(float _v) const
			//{
			//  return Vector3(this->x / _v,
			//                 this->y / _v,
			//                 this->z / _v);
			//}

			// Division assignment operator
		const Vector3& operator/=(const Vector3& v);

			// multiplication operator
			  // Vector3 operator*(const Vector3& _v) const
			  // {
			   // return vector3(this->x * _v.x,
							  // this->y * _v.y,
							  // this->z * _v.z);
			  // }

			  // Multiplication operator
		float operator*(const Vector3& v) const;

			// multiplication operator
		Vector3 operator*(const float& v) const;

			// Multiplication assignment operator
		const Vector3& operator*=(const Vector3& v);

			// Equal to operator
		bool operator==(const Vector3& v) const;

			// Not equal to operator
		bool operator!=(const Vector3& v) const;

			// See if a point is finite (e.g., not nan)
		bool IsFinite() const;

			// Array subscript operator.
		float operator[](size_t index) const;

			
			// Less than operator.
		bool operator<(const Vector3& v) const;

			// Stream extraction operator, output stream
		friend std::ostream& operator<<(std::ostream& out, const Vector3& v);

			// Stream insertion operator, input stream
		friend std::istream& operator>>(std::istream& in, Vector3& v);

		// Get the x value.
		float X() const
		{
			return this->_x;
		}

		// Get the y value.
		float Y() const
		{
			return this->_y;
		}

		// Get the z value.
		float Z() const
		{
			return this->_z;
		}

		// Get a mutable reference to the x value.
		float& X()
		{
			return this->_x;
		}

		// Get a mutable reference to the y value.
		float& Y()
		{
			return this->_y;
		}

		//Get a mutable reference to the z value.
		float& Z()
		{
			return this->_z;
		}

		// Set the x value.
		void X(const float& x)
		{
			this->_x = x;
		}

		// Set the y value.
		void Y(const float& y)
		{
			this->_y = y;
		}

		// Set the z value.
		void Z(const float& z)
		{
			this->_z = z;
		}

	};
}

#endif
