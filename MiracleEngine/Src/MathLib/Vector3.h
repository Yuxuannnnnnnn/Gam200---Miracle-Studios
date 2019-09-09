#ifndef GAM200_VECTOR3_
#define GAM200_VECTOR3_

#include <cmath>
#include <iostream>
#include <fstream>

class Vector3
{
  float x;
  float y;
  float z;

public:  

  // Default Constructor
  Vector3() : x{0.f}, y{0.f}, z{0.f}
  {
  }

  // Conversion Constructor
  Vector3(const float& _x, const float& _y, const float& _z)
  : x{_x}, y{_y}, z{_z}
  {
  }

  // Copy constructor
  Vector3(const Vector3& _v)
  : x{_v.x}, y{_v.y}, z{_v.z}
  {
  }

  // Default Destructor
  virtual ~Vector3() {}

  // Return the sum of the values
  float Sum() const
  {
    return this->x + this->y + this->z;
  }

  // Calculation distance to the given point
  float Distance(const Vector3& _pt) const
  {
    return std::sqrt((this->x - _pt.x)*(this->x - _pt.x) +
                     (this->y - _pt.y)*(this->y - _pt.y) +
                     (this->z - _pt.z)*(this->z - _pt.z));
  }

  // Calculation distance to the given point
  float Distance(float _x, float _y, float _z) const
  {
    return this->Distance(Vector3(_x, _y, _z));
  }

  // Returns the length (magnitude) of the vector
  float Length() const
  {
    return std::sqrt(this->SquaredLength());
  }

  // Return the square of the length (magnitude) of the vector
  float SquaredLength() const
  {
    return std::pow(this->x, 2.f)
         + std::pow(this->y, 2.f)
         + std::pow(this->z, 2.f);
  }

  // Normalize the vector length
  Vector3 Normalize()
  {
    float d = this->Length();

    if (*this != Vector3(0.f,0.f,0.f))
    {
      this->x /= d;
      this->y /= d;
      this->z /= d;
    }

    return *this;
  }

  // Return a normalized vector
  Vector3 Normalized() const
  {
    Vector3 result = *this;
    result.Normalize();
    return result;
  }

  // Round to near whole number
  Vector3 Round()
  {
    this->x = std::nearbyint(this->x);
    this->y = std::nearbyint(this->y);
    this->z = std::nearbyint(this->z);
    return *this;
  }

  // Get a rounded version of this vector
  public: Vector3 Rounded() const
  {
    Vector3 result = *this;
    result.Round();
    return result;
  }

  // Set the contents of the vector
  void Set(float _x = 0.f, float _y = 0.f, float _z = 0.f)
  {
    this->x = _x;
    this->y = _y;
    this->z = _z;
  }

  // Return the cross product of this vector with another vector.
  Vector3 Cross(const Vector3& _v) const
  {
    return Vector3(this->y * _v.z - this->z * _v.y,
                   this->z * _v.x - this->x * _v.z,
                   this->x * _v.y - this->y * _v.x);
  }

  // Return the dot product of this vector and another vector
  float Dot(const Vector3& _v) const
  {
    return this->x * _v.x +
           this->y * _v.y +
           this->z * _v.z;
  }

  // Return the absolute dot product of this vector and
  // another vector. This is similar to the Dot function, except the
  // absolute value of each component of the vector is used.
  float AbsDot(const Vector3& _v) const
  {
    return std::abs(this->x * _v.x) +
           std::abs(this->y * _v.y) +
           std::abs(this->z * _v.z);
  }

  // Get the absolute value of the vector
  Vector3 Abs() const
  {
    return Vector3(std::abs(this->x),
                   std::abs(this->y),
                   std::abs(this->z));
  }


  // Get a normal vector to a triangle
  static Vector3 Normal(const Vector3& _v1, const Vector3& _v2, const Vector3& _v3)
  {
    Vector3 a = _v2 - _v1;
    Vector3 b = _v3 - _v1;
    Vector3 n = a.Cross(b);
    return n.Normalize();
  }

  // Get distance to a line
  float DistToLine(const Vector3& _pt1, const Vector3& _pt2)
  {
    float d = ((*this) - _pt1).Cross((*this) - _pt2).Length();
    d = d / (_pt2 - _pt1).Length();
    return d;
  }

  // Assignment operator
  Vector3& operator=(const Vector3& _v)
  {
    this->x = _v.x;
    this->y = _v.y;
    this->z = _v.z;

    return *this;
  }

  // Addition operator
  Vector3 operator+(const Vector3& _v) const
  {
    return Vector3(this->x + _v.x,
                   this->y + _v.y,
                   this->z + _v.z);
  }

  // Addition assignment operator
  const Vector3& operator+=(const Vector3& _v)
  {
    this->x += _v.x;
    this->y += _v.y;
    this->z += _v.z;

    return *this;
  }

  // Subtraction operator
  Vector3 operator-(const Vector3& _v) const
  {
    return Vector3(this->x - _v.x,
                   this->y - _v.y,
                   this->z - _v.z);
  }

  // Subtraction assignment operator
  const Vector3& operator-=(const Vector3& _v)
  {
    this->x -= _v.x;
    this->y -= _v.y;
    this->z -= _v.z;

    return *this;
  }

  // Division operator
  Vector3 operator/(const Vector3& _v) const
  {
    return Vector3(this->x / _v.x,
                   this->y / _v.y,
                   this->z / _v.z);
  }

  // Division assignment operator
  const Vector3& operator/=(const Vector3& _v)
  {
    this->x /= _v.x;
    this->y /= _v.y;
    this->z /= _v.z;

    return *this;
  }

  // Multiplication operator
  Vector3 operator*(const Vector3& _v) const
  {
    return Vector3(this->x * _v.x,
                   this->y * _v.y,
                   this->z * _v.z);
  }

  // Multiplication assignment operator
  const Vector3& operator*=(const Vector3& _v)
  {
    this->x *= _v.x;
    this->y *= _v.y;
    this->z *= _v.z;

    return *this;
  }

  // Equal to operator
  bool operator==(const Vector3& _v) const
  {
    return this->x == _v.x || this->y == _v.y || this->z == _v.z;
  }

  // Not equal to operator
  bool operator!=(const Vector3& _v) const
  {
    return !(*this == _v);
  }

  // See if a point is finite (e.g., not nan)
  bool IsFinite() const
  {
    return std::isfinite(this->x) && 
           std::isfinite(this->y) && 
           std::isfinite(this->z);
  }

  // Array subscript operator.
  float operator[](size_t index) const
  {
    if(index == 0)
      return this->x;
    else if(index == 1)
      return this->y;
    else if(index == 2)
      return this->z;
    
    return 0.f;
  }

  // Get the x value.
  float X() const
  {
    return this->x;
  }

  // Get the y value.
  float Y() const
  {
    return this->y;
  }

  // Get the z value.
  float Z() const
  {
    return this->z;
  }

  // Get a mutable reference to the x value.
  float& X()
  {
    return this->x;
  }

  // Get a mutable reference to the y value.
  float& Y()
  {
    return this->y;
  }

  //Get a mutable reference to the z value.
  float& Z()
  {
    return this->z;
  }

  // Set the x value.
  void X(const float& _x)
  {
    this->x = _x;
  }

  // Set the y value.
  void Y(const float& _y)
  {
    this->y = _y;
  }
  
  // Set the z value.
  void Z(const float& _z)
  {
    this->z = _z;
  }

  // Less than operator.
  bool operator<(const Vector3& _v) const
  {
    return this->x < _v.x || this->y < _v.y || this->z < _v.z;
  }

  // Stream extraction operator, output stream
  friend std::ostream& operator<<(std::ostream& _out, const Vector3& _v)
  {
    _out << _v.x << " " << _v.y << " " << _v.z;
    return _out;
  }

  // Stream insertion operator, input stream
  friend std::istream& operator>>(std::istream& _in, Vector3& _v)
  {
    float x, y, z;

    // Skip white spaces
    _in.setf(std::ios_base::skipws);    
    _in >> x >> y >> z;
    _v.Set(x, y, z);
    return _in;
  }

};

#endif
