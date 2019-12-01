///////////////////////////////////////////////////////////////////////////////////////
//
//	Vector2.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#include "PrecompiledHeaders.h"
#include "Vector2.h"

namespace mathLib {

	const Vector2 Vector2::Vec2Zero = Vector2{ 0.f,0.f};
	const Vector2 Vector2::Vec2EX = Vector2{ 1.f,0.f};
	const Vector2 Vector2::Vec2EY = Vector2{ 0.f,1.f};

	Vector2::Vector2() :
		_x{ 0.f }, _y{ 0.f } {}

	// Conversion Constructor
	Vector2::Vector2(const float& x, const float& y) : 
		_x{ x }, _y{ y } {}

	// Copy constructor
	Vector2::Vector2(const Vector2& rhs) : 
		_x{ rhs._x }, _y{ rhs._y } {}


	// Assignment operator
	Vector2& Vector2::operator=(const Vector2& rhs)
	{
		if (this != &rhs)
		{
			this->_x = rhs._x;
			this->_y = rhs._y;
		}

		return *this;
	}

	float Vector2::operator[](size_t index) const
	{
		if (index > 1)
			return 0.f;

		return m[index];
	}

	float& Vector2::GetX()
	{
		return _x;
	}

	float& Vector2::GetY()
	{
		return _y;
	}

	void Vector2::SetX(const float& x)
	{
		this->_x = x;
	}

	void Vector2::SetY(const float& y)
	{
		this->_y = y;
	}

	void Vector2::Set(float x, float y)
	{
		this->_x = x;
		this->_y = y;
	}

///////////////////////////////////////////////////////////////////////////////

	float Vector2::Sum() const
	{
		return this->_x + this->_y;
	}

	float Vector2::Distance(const Vector2& pt) const
	{
		return std::sqrt((this->_x - pt._x) * (this->_x - pt._x) +
			(this->_y - pt._y) * (this->_y - pt._y));
	}

	float Vector2::Distance(float x, float y) const
	{
		return this->Distance(Vector2(x, y));
	}

	float Vector2::Length() const
	{
		return std::sqrt(this->SquaredLength());
	}

	float Vector2::SquaredLength() const
	{
		return std::pow(this->_x, 2.f)
			+ std::pow(this->_y, 2.f);
	}

	Vector2& Vector2::Normalize()
	{
		float d = this->Length();

		if (*this != Vector2(0.f, 0.f))
		{
			this->_x /= d;
			this->_y /= d;
		}

		return *this;
	}

	Vector2 Vector2::Normalized() const
	{
		Vector2 result = *this;
		return result.Normalize();
	}

	Vector2& Vector2::Round()
	{
		this->_x = std::nearbyint(this->_x);
		this->_y = std::nearbyint(this->_y);
		return *this;
	}

	Vector2 Vector2::Rounded() const
	{
		Vector2 result = *this;
		return result.Round();
	}

	Vector2 Vector2::Cross(const Vector2& v) const
	{
		return Vector2(v._y, -v._x);
	}

	float Vector2::Dot(const Vector2& v) const
	{
		return this->_x * v._x +
			this->_y * v._y;
	}

	float Vector2::AbsDot(const Vector2& v) const
	{
		return std::abs(this->_x * v._x +
			this->_y * v._y);
	}

	Vector2 Vector2::Abs() const
	{
		return Vector2(std::abs(this->_x),
			std::abs(this->_y));
	}

	bool Vector2::IsFinite() const
	{
		return std::isfinite(this->_x) &&
			std::isfinite(this->_y);
	}

	/*float Vector2::DistToLine(const Vector2& lineEdge1, const Vector2& lineEdge2, const Vector2& pt)
	{
		float d = (pt - lineEdge1).Cross(pt - lineEdge2).Length();
		d = d / (lineEdge1 - lineEdge2).Length();
		return d;
	}*/

	/*Vector2 Vector2::Normal(const Vector2& v1, const Vector2& v2, const Vector2& v3)
	{
		Vector2 a = v2 - v1;
		Vector2 b = v3 - v1;
		Vector2 n = a.Cross(b);
		return n.Normalize();
	}*/

	// Stream extraction operator, output stream
	std::ostream& operator<<(std::ostream& out, const Vector2& v)
	{
		out << v[0] << " " << v[1];
		return out;
	}

	// Stream insertion operator, input stream
	std::istream& operator>>(std::istream& in, Vector2& v)
	{
		float x, y;
		// Skip white spaces
		in.setf(std::ios_base::skipws);
		in >> x >> y;
		v.Set(x, y);
		return in;
	}

///////////////////////////////////////////////////////////////////////////////

	Vector2 operator+(const Vector2& lhs)
	{
		return lhs.Abs();
	}

	Vector2 operator-(const Vector2& lhs)
	{
		return Vector2{ -lhs._x, -lhs._y };
	}

	Vector2 operator+(const Vector2& lhs, const Vector2& rhs)
	{
		return Vector2{ lhs._x + rhs._x,
						lhs._y + rhs._y };
	}

	Vector2 operator-(const Vector2& lhs, const Vector2& rhs)
	{
		return Vector2{ lhs._x - rhs._x,
						lhs._y - rhs._y };
	}

	Vector2 operator*(const Vector2& lhs, const Vector2& rhs)
	{
		return Vector2{ lhs._x * rhs._x,
						lhs._y * rhs._y };
	}

	Vector2 operator/(const Vector2& lhs, const Vector2& rhs)
	{
		if (rhs._x == 0 || rhs._y == 0)
			return lhs;

		return Vector2{ lhs._x / rhs._x,
						lhs._y / rhs._y };
	}

	Vector2& operator+=(Vector2& lhs, const Vector2& rhs)
	{
		lhs._x += rhs._x;
		lhs._y += rhs._y;

		return lhs;
	}

	Vector2& operator-=(Vector2& lhs, const Vector2& rhs)
	{
		lhs._x -= rhs._x;
		lhs._y -= rhs._y;

		return lhs;
	}

	Vector2& operator*=(Vector2& lhs, const Vector2& rhs)
	{
		lhs._x *= rhs._x;
		lhs._y *= rhs._y;

		return lhs;
	}

	Vector2& operator/=(Vector2& lhs, const Vector2& rhs)
	{
		if (rhs._x == 0 || rhs._y == 0)
			return lhs;

		lhs._x /= rhs._x;
		lhs._y /= rhs._y;

		return lhs;
	}

	Vector2 operator*(const Vector2& lhs, const float& rhs)
	{
		return Vector2{ lhs._x * rhs,
						lhs._y * rhs};
	}

	Vector2 operator*(const float& lhs, const Vector2& rhs)
	{
		return Vector2{ lhs * rhs._x,
						lhs * rhs._y};
	}

	Vector2 operator/(const Vector2& lhs, const float& rhs)
	{
		if (rhs == 0)
			return lhs;

		return Vector2{ lhs._x / rhs,
						lhs._y / rhs};
	}

	Vector2& operator*=(Vector2& lhs, const float& rhs)
	{
		lhs._x *= rhs;
		lhs._y *= rhs;

		return lhs;
	}

	Vector2& operator*=(const float& lhs, Vector2& rhs)
	{
		rhs._x *= lhs;
		rhs._y *= lhs;

		return rhs;
	}

	Vector2& operator/=(Vector2& lhs, const float& rhs)
	{
		if (rhs == 0)
			return lhs;

		lhs._x /= rhs;
		lhs._y /= rhs;

		return lhs;
	}

	bool operator==(const Vector2& lhs, const Vector2& rhs)
	{
		return ((lhs._x == rhs._x) &&
			(lhs._y == rhs._y));
	}

	bool operator!=(const Vector2& lhs, const Vector2& rhs)
	{
		return !(lhs == rhs);
	}
}