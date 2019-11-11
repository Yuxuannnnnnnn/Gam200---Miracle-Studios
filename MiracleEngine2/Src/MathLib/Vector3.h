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

	typedef union Vector3  {

	public:
		
		struct
		{
			float _x;
			float _y;
			float _z;
		};

		float m[3];
		
		static const Vector3 Vec3Zero;
		static const Vector3 Vec3EX;
		static const Vector3 Vec3EY;
		static const Vector3 Vec3EZ;

	public: // default Class function

		Vector3();
		Vector3(const float& x, const float& y = 0.f, const float& z = 0.f); 
		Vector3(const Vector3& v); 
		~Vector3() {} 

		Vector3& operator=(const Vector3& rhs);
		float operator[](size_t index) const;

		float& GetX();
		float& GetY();
		float& GetZ();
		void SetX(const float& x);
		void SetY(const float& y);
		void SetZ(const float& z);
		void Set(float x = 0.f, float y = 0.f, float z = 0.f);

	public: // other function

		float Sum() const; 
		
		float Distance(const Vector3& pt) const; 
		float Distance(float x, float y, float z) const; 

		float Length() const; 
		float SquaredLength() const;
		
		Vector3& Normalize();
		Vector3 Normalized() const;
		
		Vector3& Round(); 
		Vector3 Rounded() const;
		
		Vector3 Cross(const Vector3& v) const;
		float Dot(const Vector3& v) const; 
		float AbsDot(const Vector3& v) const;
		
		Vector3 Abs() const;
		
		bool IsFinite() const;

		//static float DistToLine(const Vector3& lineEdge1, const Vector3& lineEdge2, const Vector3& pt);
		//static Vector3 Normal(const Vector3& v1, const Vector3& v2, const Vector3& v3);

		friend std::ostream& operator<<(std::ostream& out, const Vector3& v);
		friend std::istream& operator>>(std::istream& in, Vector3& v);

	} Vector3, Vec3;

	Vector3 operator+(const Vector3& lhs);
	Vector3 operator-(const Vector3& lhs);
	Vector3 operator+(const Vector3& lhs, const Vector3& rhs);
	Vector3 operator-(const Vector3& lhs, const Vector3& rhs);
	Vector3 operator*(const Vector3& lhs, const Vector3& rhs);
	Vector3 operator/(const Vector3& lhs, const Vector3& rhs);

	Vector3& operator+=(Vector3& lhs, const Vector3& rhs);
	Vector3& operator-=(Vector3& lhs, const Vector3& rhs);
	Vector3& operator*=(Vector3& lhs, const Vector3& rhs);
	Vector3& operator/=(Vector3& lhs, const Vector3& rhs);

	Vector3 operator*(const Vector3& lhs, const float& rhs);
	Vector3 operator*(const float& lhs, const Vector3& rhs);

	Vector3 operator/(const Vector3& lhs, const float& rhs);
	//Vector3 operator/(const float& lhs, const Vector3& rhs);

	Vector3& operator*=(Vector3& lhs, const float& rhs);
	Vector3& operator*=(const float& lhs, Vector3& rhs);

	Vector3& operator/=(Vector3& lhs,const float& rhs);
	//Vector3& operator/=(const float& lhs, Vector3& rhs);

	bool operator==(const Vector3& lhs, const Vector3& rhs);
	bool operator!=(const Vector3& lhs, const Vector3& rhs);
	//bool operator<(const Vector3& lhs, const Vector3& rhs);
	//bool operator>(const Vector3& lhs, const Vector3& rhs);
	//bool operator<=(const Vector3& lhs, const Vector3& rhs);
	//bool operator>=(const Vector3& lhs, const Vector3& rhs);
	
}

#endif
