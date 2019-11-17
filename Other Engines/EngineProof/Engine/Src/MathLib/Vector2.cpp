///////////////////////////////////////////////////////////////////////////////////////
//
//	Vector2.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#include "Vector2.h"

namespace mathLib {

	const Vector2 Vector2::Vec2Zero = Vector2{ 0.f,0.f};
	const Vector2 Vector2::Vec2EX = Vector2{ 1.f,0.f};
	const Vector2 Vector2::Vec2EY = Vector2{ 0.f,1.f};

	// Conversion Constructor
	Vector2::Vector2(const float& _x, const float& _y) : 
		x{ _x }, 
		y{ _y } 
	{

	}

	// Copy constructor
	Vector2::Vector2(const Vector2& _v) : 
		x{ _v.x }, 
		y{ _v.y } 
	{

	}


	// Assignment operator
	Vector2& Vector2::operator=(const Vector2& _v)
	{
		if (this != &_v)
		{
			this->x = _v.x;
			this->y = _v.y;
		}

		return *this;
	}

	// Calc distance to the given point
	double Vector2::Distance(const Vector2& _pt) const
	{
		return std::sqrt((this->x - _pt.x) * (this->x - _pt.x) +
			(this->y - _pt.y) * (this->y - _pt.y));
	}

	// Get the dot product of this vector and _v
	float Vector2::Dot(const Vector2& _v) const
	{
		return ((this->x * _v.x) + (this->y * _v.y));
	}

	// See if a point is finite (e.g., not nan)
	bool Vector2::IsFinite() const
	{
		return std::isfinite(this->x) &&
			std::isfinite(this->y);
	}

	// Get the length (magnitude) of the vector
	float Vector2::Length() const
	{
		return std::sqrt(this->SquaredLength());
	}

	// Get the square of the length (magnitude) of the vector
	float Vector2::SquaredLength() const
	{
		return std::pow(this->x, 2.f) + std::pow(this->y, 2.f);
	}


	// Normalize the vector length.
	void Vector2::Normalize()
	{
		float d = this->Length();

		if (d != 0.0)
		{
			this->x /= d;
			this->y /= d;
		}
	}

	// Set the contents of the vector
	void Vector2::Set(float _x, float _y)
	{
		this->x = _x;
		this->y = _y;
	}


	// Equal to operator.
	bool Vector2::operator==(const Vector2& _v) const
	{
		return (this->x == _v.x) && (this->y == _v.y);
	}

	// Not equal to operator.
	bool Vector2::operator!=(const Vector2& _v) const
	{
		return !(*this == _v);
	}

	// less than operator.
	bool Vector2::operator<(const Vector2& _v) const
	{
		return this->x < _v.x || this->y < _v.y;
	}

	// Multiplication operators
	const Vector2 Vector2::operator*(const Vector2& _v) const
	{
		return Vector2(this->x * _v.x, this->y * _v.y);
	}

	// Multiplication operators
	const Vector2 Vector2::operator*(float _v) const
	{
		return Vector2(this->x * _v, this->y * _v);
	}

	// Multiplication assignment operator
	const Vector2& Vector2::operator*=(const Vector2& _v)
	{
		this->x *= _v.x;
		this->y *= _v.y;

		return *this;
	}

	// Multiplication assignment operator
	const Vector2& Vector2::operator*=(float _v)
	{
		this->x *= _v;
		this->y *= _v;

		return *this;
	}

	// Addition operator
	const Vector2 Vector2::operator+(const Vector2& _v) const
	{
		return Vector2(this->x + _v.x, this->y + _v.y);
	}

	// Addition assignment  operator
	const Vector2& Vector2::operator+=(const Vector2& _v)
	{
		this->x += _v.x;
		this->y += _v.y;

		return *this;
	}

	// Subtraction operator
	const Vector2 Vector2::operator-(const Vector2& _v) const
	{
		return Vector2(this->x - _v.x, this->y - _v.y);
	}

	// Subtraction assignment  operator
	const Vector2& Vector2::operator-=(const Vector2& _v)
	{
		this->x -= _v.x;
		this->y -= _v.y;

		return *this;
	}

	// Division operator
	const Vector2 Vector2::operator/(const Vector2& _v) const
	{
		return Vector2(this->x / _v.x, this->y / _v.y);
	}

	// Division assignment  operator
	const Vector2& Vector2::operator/=(const Vector2& _v)
	{
		this->x /= _v.x;
		this->y /= _v.y;

		return *this;
	}

	// Array subscript operator.
	float Vector2::operator[](size_t index) const
	{
		if (index == 0)
			return this->x;
		else if (index == 1)
			return this->y;

		return 0.f;
	}

	// Stream extraction operator, output stream
	 std::ostream& operator<<(std::ostream& _out, const Vector2& _v)
	{
		_out << _v[0] << " " << _v[1];
		return _out;
	}

	// Stream insertion operator, input stream
	 std::istream& operator>>(std::istream& _in, Vector2& _v)
	{
		float x, y;
		// Skip white spaces
		_in.setf(std::ios_base::skipws);
		_in >> x >> y;
		_v.Set(x, y);
		return _in;
	}

}