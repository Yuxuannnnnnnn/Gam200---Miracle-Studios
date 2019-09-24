#ifndef GAM200_VECTOR2_
#define GAM200_VECTOR2_

#include <cmath>
#include <iostream>
#include <fstream>

/* 
1 byte  -> bool, char, unsigned char, signed char, __int8	
2 bytes -> __int16, short, unsigned short, wchar_t, __wchar_t	
4 bytes -> float, __int32, int, unsigned int, long, unsigned long	
8 bytes -> double, __int64, long double, long long	
*/


class Vector2 {
  
  float x;
  float y;
  
public:

  // Default Constructor
  Vector2() : x{0.f}, y{0.f} {}
  // Conversion Constructor
  Vector2(const float& _x, const float& _y) : x{_x}, y{_y} {}
  // Copy constructor
  Vector2(const Vector2& _v) : x{_v.x}, y{_v.y} {}
  // Default destructor
  ~Vector2() {}
  
  // Assignment operator
  Vector2& operator=(const Vector2& _v)
  {
    if(this != &_v)
    {
      this->x = _v.x;
      this->y = _v.y;
    }
    
    return *this;
  }
  
  // Calc distance to the given point
  double Distance(const Vector2& _pt) const
  {
    return std::sqrt((this->x - _pt.x) * (this->x - _pt.x) + 
                     (this->y - _pt.y) * (this->y - _pt.y));
  }
  
  // Get the dot product of this vector and _v
  float Dot(const Vector2& _v) const
  {
    return ((this->x * _v.x) + (this->y * _v.y));
  }
  
  // See if a point is finite (e.g., not nan)
  bool IsFinite() const
  {
    return std::isfinite(this->x) && 
           std::isfinite(this->y);
  }
  
  // Get the length (magnitude) of the vector
  float Length() const
  {
    return std::sqrt(this->SquaredLength());
  }
  
  // Get the square of the length (magnitude) of the vector
  float SquaredLength() const
  {
    return std::pow(this->x, 2.f) + std::pow(this->y, 2.f); 
  }
  
  
  // Normalize the vector length.
  void Normalize()
  {
    float d = this->Length();
    
    if(d != 0.0)
    {
      this->x /= d;
      this->y /= d;
    }
  }
  
  // Set the contents of the vector
  void Set(float _x, float _y)
  {
    this->x = _x;
    this->y = _y;
  }
  
  // Return the x value
  float X() const
  {
    return this->x;
  }
  
  // Return a mutable x value.
  float& X()
  {
    return this->x;
  }
  
  // Set the x value.
  void X(const float& _v)
  {
    this->x = _v;
  }
  
  // Return the y value
  float Y() const
  {
    return this->y;
  }
  
  
  // Return a mutable y value.
  float& Y()
  {
    return this->y;
  }
  
  // Set the y value.
  void Y(const float& _v)
  {
    this->y = _v;
  }

  // Equal to operator.
  bool operator==(const Vector2& _v) const
  {
    return (this->x == _v.x) && (this->y == _v.y);
  }

  // Not equal to operator.
  bool operator!=(const Vector2& _v) const
  {
    return !(*this == _v);
  }
  
  // less than operator.
  bool operator<(const Vector2& _v) const
  {
   return this->x < _v.x || this->y < _v.y;
  }
  
  // Multiplication operators
  const Vector2 operator*(const Vector2& _v) const
  {
    return Vector2(this->x * _v.x, this->y * _v.y);
  }
  
  // Multiplication operators
  const Vector2 operator*(float _v) const
  {
    return Vector2(this->x * _v, this->y * _v);
  }
  
  // Multiplication assignment operator
  const Vector2& operator*=(const Vector2& _v)
  {
    this->x *= _v.x;
    this->y *= _v.y;
    
    return *this;
  }
  
  // Multiplication assignment operator
  const Vector2& operator*=(float _v)
  {
    this->x *= _v;
    this->y *= _v;
    
    return *this;
  }
  
  // Addition operator
  const Vector2 operator+(const Vector2& _v) const
  {
    return Vector2(this->x + _v.x, this->y + _v.y);
  }
  
  // Addition assignment  operator
  const Vector2& operator+=(const Vector2& _v)
  {
    this->x += _v.x;
    this->y += _v.y;
    
    return *this;
  }
  
  // Subtraction operator
  const Vector2 operator-(const Vector2& _v) const
  {
    return Vector2(this->x - _v.x, this->y - _v.y);
  }
  
  // Subtraction assignment  operator
  const Vector2& operator-=(const Vector2& _v)
  {
    this->x -= _v.x;
    this->y -= _v.y;
    
    return *this;
  }
  
  // Division operator
  const Vector2 operator/(const Vector2& _v) const
  {
    return Vector2(this->x / _v.x, this->y / _v.y);
  }
  
  // Division assignment  operator
  const Vector2& operator/=(const Vector2& _v)
  {
    this->x /= _v.x;
    this->y /= _v.y;
    
    return *this;
  }
  
  // Array subscript operator.
  float operator[](size_t index) const
  {
    if(index == 0)
      return this->x;
    else if(index == 1)
      return this->y;
    
    return 0.f;
  }
  
  // Stream extraction operator, output stream
  friend std::ostream& operator<<(std::ostream& _out, const Vector2& _v)
  {
    _out << _v[0] << " " << _v[1];
    return _out;
  }

  // Stream insertion operator, input stream
  friend std::istream& operator>>(std::istream& _in, Vector2& _v)
  {
    float x, y;
    // Skip white spaces
    _in.setf(std::ios_base::skipws);
    _in >> x >> y;
    _v.Set(x, y);
    return _in;
  }
  
};

#endif
