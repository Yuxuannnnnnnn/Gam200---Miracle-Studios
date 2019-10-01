///////////////////////////////////////////////////////////////////////////////////////
//
//	Vector3.cpp
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#include "Vector3.h"
#include<iostream>

namespace mathLib {

	const Vector3 Vector3::Vec3Zero = Vector3{ 0.f,0.f,0.f };
	const Vector3 Vector3::Vec3EX = Vector3{ 1.f,0.f,0.f };
	const Vector3 Vector3::Vec3EY = Vector3{ 0.f,1.f,0.f };
	const Vector3 Vector3::Vec3EZ = Vector3{ 0.f,0.f,1.f };

	Vector3::Vector3()
		: _x{ 0.f }, _y{ 0.f }, _z{ 0.f }
	{

	}

	// Conversion Constructor
	Vector3::Vector3(const float& x, const float& y, const float& z)
		: _x{ x }, _y{ y }, _z{ z }
	{
	}

	// Copy constructor
	Vector3::Vector3(const Vector3& v)
		: _x{ v._x }, _y{ v._y }, _z{ v._z }
	{
	}

	// Return the sum of the values
	float Vector3::Sum() const
	{
		return this->_x + this->_y + this->_z;
	}

	// Calculation distance to the given point
	float Vector3::Distance(const Vector3& pt) const
	{
		return std::sqrt((this->_x - pt._x) * (this->_x - pt._x) +
			(this->_y - pt._y) * (this->_y - pt._y) +
			(this->_z - pt._z) * (this->_z - pt._z));
	}

	// Calculation distance to the given point
	float Vector3::Distance(float x, float y, float z) const
	{
		return this->Distance(Vector3(x, y, z));
	}

	// Returns the length (magnitude) of the vector
	float Vector3::Length() const
	{
		return std::sqrt(this->SquaredLength());
	}

	// Return the square of the length (magnitude) of the vector
	float Vector3::SquaredLength() const
	{
		return std::pow(this->_x, 2.f)
			+ std::pow(this->_y, 2.f)
			+ std::pow(this->_z, 2.f);
	}

	// Normalize the vector length
	Vector3& Vector3::Normalize()
	{
		float d = this->Length();

		if (*this != Vector3(0.f, 0.f, 0.f))
		{
			this->_x /= d;
			this->_y /= d;
			this->_z /= d;
		}

		return *this;
	}

	// Return a normalized vector
	Vector3& Vector3::Normalized() const
	{
		Vector3 result = *this;
		return result.Normalize();
	}

	// Round to near whole number
	Vector3& Vector3::Round()
	{
		this->_x = std::nearbyint(this->_x);
		this->_y = std::nearbyint(this->_y);
		this->_z = std::nearbyint(this->_z);
		return *this;
	}

		// Get a rounded version of this vector
	Vector3 Vector3::Rounded() const
	{
		Vector3 result = *this;
		result.Round();
		return result;
	}

		// Set the contents of the vector
		void Vector3::Set(float x, float y, float z)
		{
			this->_x = x;
			this->_y = y;
			this->_z = z;
		}

		// Return the cross product of this vector with another vector.
		Vector3 Vector3::Cross(const Vector3& v) const
		{
			return Vector3(this->_y * v._z - this->_z * v._y,
				this->_z * v._x - this->_x * v._z,
				this->_x * v._y - this->_y * v._x);
		}

		// Return the dot product of this vector and another vector
		float Vector3::Dot(const Vector3& v) const
		{
			return this->_x * v._x +
				this->_y * v._y +
				this->_z * v._z;
		}

		// Return the absolute dot product of this vector and
		// another vector. This is similar to the Dot function, except the
		// absolute value of each component of the vector is used.
		float Vector3::AbsDot(const Vector3& v) const
		{
			return std::abs(this->_x * v._x) +
				std::abs(this->_y * v._y) +
				std::abs(this->_z * v._z);
		}

		// Get the absolute value of the vector
		Vector3 Vector3::Abs() const
		{
			return Vector3(std::abs(this->_x),
				std::abs(this->_y),
				std::abs(this->_z));
		}


		// Get a normal vector to a triangle
		Vector3 Vector3::Normal(const Vector3& v1, const Vector3& v2, const Vector3& v3)
		{
			Vector3 a = v2 - v1;
			Vector3 b = v3 - v1;
			Vector3 n = a.Cross(b);
			return n.Normalize();
		}

		// Get distance to a line
		float Vector3::DistToLine(const Vector3& pt1, const Vector3& pt2)
		{
			float d = ((*this) - pt1).Cross((*this) - pt2).Length();
			d = d / (pt2 - pt1).Length();
			return d;
		}

		// Assignment operator
		Vector3& Vector3::operator=(const Vector3& v)
		{
			this->_x = v._x;
			this->_y = v._y;
			this->_z = v._z;

			return *this;
		}

		// Addition operator
		Vector3 Vector3::operator+(const Vector3& v) const
		{
			return Vector3(this->_x + v._x,
				this->_y + v._y,
				this->_z + v._z);
		}

		// Addition assignment operator
		const Vector3& Vector3::operator+=(const Vector3& v)
		{
			this->_x += v._x;
			this->_y += v._y;
			this->_z += v._z;

			return *this;
		}

		// Subtraction operator
		Vector3 Vector3::operator-() const
		{
			return Vector3(-this->_x,
				-this->_y,
				-this->_z);
		}

		// Subtraction operator
		Vector3 Vector3::operator-(const Vector3& v) const
		{
			return Vector3(this->_x - v._x,
				this->_y - v._y,
				this->_z - v._z);
		}

		// Subtraction assignment operator
		const Vector3& Vector3::operator-=(const Vector3& v)
		{
			this->_x -= v._x;
			this->_y -= v._y;
			this->_z -= v._z;

			return *this;
		}

		// Division operator
		Vector3 Vector3::operator/(const Vector3& v) const
		{
			return Vector3(this->_x / v._x,
				this->_y / v._y,
				this->_z / v._z);
		}

		Vector3 Vector3::operator/(const float& v) const
		{
			return Vector3(this->_x / v,
				this->_y / v,
				this->_z / v);
		}


		//// Division operator
		//Vector3 operator/(float _v) const
		//{
		//  return Vector3(this->_x / _v,
		//                 this->_y / _v,
		//                 this->_z / _v);
		//}

		// Division assignment operator
		const Vector3& Vector3::operator/=(const Vector3& v)
		{
			this->_x /= v._x;
			this->_y /= v._y;
			this->_z /= v._z;

			return *this;
		}

		// multiplication operator
		  // Vector3 operator*(const Vector3& _v) const
		  // {
		   // return vector3(this->_x * v._x,
						  // this->_y * v._y,
						  // this->_z * v._z);
		  // }

		  // Multiplication operator
		float Vector3::operator*(const Vector3& v) const
		{
			return this->Dot(v);
		}

		// multiplication operator
		Vector3 Vector3::operator*(const float& v) const
		{
			return Vector3(this->_x * v,
				this->_y * v,
				this->_z * v);
		}

		// Multiplication assignment operator
		const Vector3& Vector3::operator*=(const Vector3& v)
		{
			this->_x *= v._x;
			this->_y *= v._y;
			this->_z *= v._z;

			return *this;
		}


		// Equal to operator
		bool Vector3::operator==(const Vector3& v) const
		{
			return this->_x == v._x && this->_y == v._y && this->_z == v._z;
		}

		// Not equal to operator
		bool Vector3::operator!=(const Vector3& v) const
		{
			return !(*this == v);
		}

		// See if a point is finite (e.g., not nan)
		bool Vector3::IsFinite() const
		{
			return std::isfinite(this->_x) &&
				std::isfinite(this->_y) &&
				std::isfinite(this->_z);
		}

		// Array subscript operator.
		float Vector3::operator[](size_t index) const
		{
			if (index == 0)
				return this->_x;
			else if (index == 1)
				return this->_y;
			else if (index == 2)
				return this->_z;

			return 0.f;
		}


		// Less than operator.
		bool Vector3::operator<(const Vector3& v) const
		{
			return this->_x < v._x || this->_y < v._y || this->_z < v._z;
		}

		// Stream extraction operator, output stream
		std::ostream& operator<<(std::ostream& out, const Vector3& v)
		{
			out << v._x << " " << v._y << " " << v._z;
			return out;
		}

		// Stream insertion operator, input stream
		std::istream& operator>>(std::istream& in, Vector3& v)
		{
			float x, y, z;

			// Skip white spaces
			in.setf(std::ios_base::skipws);
			in >> x >> y >> z;
			v.Set(x, y, z);
			return in;
		}

}