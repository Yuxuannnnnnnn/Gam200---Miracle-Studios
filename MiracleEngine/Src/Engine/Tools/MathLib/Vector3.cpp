///////////////////////////////////////////////////////////////////////////////////////
//
//	Vector3.cpp
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#include "PrecompiledHeaders.h"
#include "Vector3.h"

namespace mathLib {

	const Vector3 Vector3::Vec3Zero = Vector3{ 0.f,0.f,0.f };
	const Vector3 Vector3::Vec3EX = Vector3{ 1.f,0.f,0.f };
	const Vector3 Vector3::Vec3EY = Vector3{ 0.f,1.f,0.f };
	const Vector3 Vector3::Vec3EZ = Vector3{ 0.f,0.f,1.f };

	Vector3::Vector3()
		: _x{ 0.f }, _y{ 0.f }, _z{ 0.f } {}

	// Conversion Constructor
	Vector3::Vector3(const float& x, const float& y, const float& z)
		: _x{ x }, _y{ y }, _z{ z } {}

	// Copy constructor
	Vector3::Vector3(const Vector3& v)
		: _x{ v._x }, _y{ v._y }, _z{ v._z } {}


	Vector3& Vector3::operator=(const Vector3& rhs)
	{
		if (this != &rhs)
		{
			this->_x = rhs._x;
			this->_y = rhs._y;
			this->_z = rhs._z;
		}

		return *this;
	}

	float Vector3::operator[](size_t index) const
	{
		if (index > 2)
			return 0.f;

		return m[index];
	}

	float& Vector3::GetX()
	{
		return this->_x;
	}

	float& Vector3::GetY()
	{
		return this->_y;
	}

	float& Vector3::GetZ()
	{
		return this->_z;
	}

	void Vector3::SetX(const float& x)
	{
		this->_x = x;
	}
	
	void Vector3::SetY(const float& y)
	{
		this->_y = y;
	}
	
	void Vector3::SetZ(const float& z)
	{
		this->_z = z;
	}

	void Vector3::Set(float x, float y, float z)
	{
		this->_x = x;
		this->_y = y;
		this->_z = z;
	}

///////////////////////////////////////////////////////////////////////////////

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
	Vector3 Vector3::Normalized() const
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
		return result.Round();
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
		return std::abs(this->_x * v._x +
			this->_y * v._y +
			this->_z * v._z);
	}

	// Get the absolute value of the vector
	Vector3 Vector3::Abs() const
	{
		return Vector3(std::abs(this->_x),
			std::abs(this->_y),
			std::abs(this->_z));
	}

	// See if a point is finite (e.g., not nan)
	bool Vector3::IsFinite() const
	{
		return std::isfinite(this->_x) &&
			std::isfinite(this->_y) &&
			std::isfinite(this->_z);
	}

	// Get distance to a line
	/*float Vector3::DistToLine(const Vector3& lineEdge1, const Vector3& lineEdge2, const Vector3& pt)
	{
		float d = (pt - lineEdge1).Cross(pt - lineEdge2).Length();
		d = d / (lineEdge1 - lineEdge2).Length();
		return d;
	}*/

	// Get a normal vector to a triangle
	/*Vector3 Vector3::Normal(const Vector3& v1, const Vector3& v2, const Vector3& v3)
	{
		Vector3 a = v2 - v1;
		Vector3 b = v3 - v1;
		Vector3 n = a.Cross(b);
		return n.Normalize();
	}*/

	// Stream extraction operator, output stream
	std::ostream& operator<<(std::ostream& out, const Vector3& v)
	{
		out << v[0] << " " << v[1] << " " << v[2];
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

///////////////////////////////////////////////////////////////////////////////

	Vector3 operator+(const Vector3& lhs)
	{
		return lhs.Abs();
	}

	Vector3 operator-(const Vector3& lhs)
	{
		return Vector3{ -lhs._x, -lhs._y, -lhs._z };
	}

	Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
	{
		return Vector3{ lhs._x + rhs._x,
						lhs._y + rhs._y,
						lhs._z + rhs._z };
	}

	Vector3 operator-(const Vector3& lhs, const Vector3& rhs)
	{
		return Vector3{ lhs._x - rhs._x,
						lhs._y - rhs._y,
						lhs._z - rhs._z };
	}

	Vector3 operator*(const Vector3& lhs, const Vector3& rhs)
	{
		return Vector3{ lhs._x * rhs._x,
						lhs._y * rhs._y,
						lhs._z * rhs._z };
	}

	Vector3 operator/(const Vector3& lhs, const Vector3& rhs)
	{
		if (rhs._x == 0 || rhs._y == 0 || rhs._z == 0)
			return lhs;

		return Vector3{ lhs._x / rhs._x,
						lhs._y / rhs._y,
						lhs._z / rhs._z };
	}

	Vector3& operator+=(Vector3& lhs, const Vector3& rhs)
	{
		lhs._x += rhs._x;
		lhs._y += rhs._y;
		lhs._z += rhs._z;

		return lhs;
	}

	Vector3& operator-=(Vector3& lhs, const Vector3& rhs)
	{
		lhs._x -= rhs._x;
		lhs._y -= rhs._y;
		lhs._z -= rhs._z;

		return lhs;
	}

	Vector3& operator*=(Vector3& lhs, const Vector3& rhs)
	{
		lhs._x *= rhs._x;
		lhs._y *= rhs._y;
		lhs._z *= rhs._z;

		return lhs;
	}

	Vector3& operator/=(Vector3& lhs, const Vector3& rhs)
	{
		if (rhs._x == 0 || rhs._y == 0 || rhs._z == 0)
			return lhs;

		lhs._x /= rhs._x;
		lhs._y /= rhs._y;
		lhs._z /= rhs._z;

		return lhs;
	}

	Vector3 operator*(const Vector3& lhs, const float& rhs)
	{
		return Vector3{ lhs._x * rhs,
						lhs._y * rhs,
						lhs._z * rhs };
	}

	Vector3 operator*(const float& lhs, const Vector3& rhs)
	{
		return Vector3{ lhs * rhs._x,
						lhs * rhs._y,
						lhs * rhs._z };
	}
	Vector3 operator/(const Vector3& lhs, const float& rhs)
	{
		if (rhs == 0)
			return lhs;

		return Vector3{ lhs._x / rhs,
						lhs._y / rhs,
						lhs._z / rhs };
	}
	
	Vector3& operator*=(Vector3& lhs, const float& rhs)
	{
		lhs._x *= rhs;
		lhs._y *= rhs;
		lhs._z *= rhs;

		return lhs;
	}
	Vector3& operator*=(const float& lhs, Vector3& rhs)
	{
		rhs._x *= lhs;
		rhs._y *= lhs;
		rhs._z *= lhs;

		return rhs;
	}

	Vector3& operator/=(Vector3& lhs, const float& rhs)
	{
		if (rhs == 0)
			return lhs;

		lhs._x /= rhs;
		lhs._y /= rhs;
		lhs._z /= rhs;

		return lhs;
	}
	
	bool operator==(const Vector3& lhs, const Vector3& rhs)
	{
		return ((lhs._x == rhs._x) &&
				(lhs._y == rhs._y) &&
				(lhs._z == rhs._z));
	}

	bool operator!=(const Vector3& lhs, const Vector3& rhs)
	{
		return !(lhs == rhs);
	}
}