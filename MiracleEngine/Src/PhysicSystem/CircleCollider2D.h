///////////////////////////////////////////////////////////////////////////////////////
//
//	CircleCollider2D.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _CIRCLE_COLLIDER_2D_H
#define _CIRCLE_COLLIDER_2D_H

#include "GAM200-Vector3.h"
#include "GAM200-Vector2.h"

#include "Collider2D.h"

// namespace MiracleEngine

class BoxCollider2D;

////////////////////////////////////////////////////////////////////////////////
/*!
@brief  the Shortest Distance Algorithm for a line segment to a point.

@param	Vector3 P
	The first vertex of the line segment
@param	Vector3 Q
	The second vertex of the line segment
@param	Vector3 R
	Arbitrary point to calculate its shortest distance to the line
	segment PQ.

@return 
	The shortest possible distance, as a floating point value, between
	the specified line segment and the arbitrary point.
*/
////////////////////////////////////////////////////////////////////////////////
inline float distance(Vector3 P, Vector3 Q, Vector3 R)
{
	Vector3 v = Q - P;
	Vector3 w = R - P;

	float c1 = w * v;

	if (c1 <= 0)
		return R.Distance(P);

	float c2 = v * v;

	if (c2 <= c1)
		return R.Distance(Q);

	float b = c1 / c2;
	Vector3 S = P + Vector3(b * v.X(), b * v.Y());

	return R.Distance(S);
}

class CircleCollider2D : public Collider2D // Renderer
{
public:
  // Default Constructor
	CircleCollider2D() : mCenPos(0.f, 0.f), mRadius(0.f) 
  { 
  }
  
  // Conversion Constructor
	CircleCollider2D(const Vector3& center, float radius) : mCenPos{center}, mRadius{radius}
  {  
  }
  
  // Copy Constructor
	CircleCollider2D(const CircleCollider2D& _cc) : mCenPos{_cc.mCenPos}, mRadius{_cc.mRadius} 
  { 
  }
  
  //Default Destructor
  ~CircleCollider2D() {}
  
	void		Move(const Vector3& vec)
  {
    mCenPos += vec;
  }

	bool		TestCCVsPoint(const Vector3& p) const
  {
    Vector3 diff = p - mCenPos;
    return (diff.Length() <= mRadius);
  }
	bool		TestCCvsCC(const CircleCollider2D& cc) const
  {
    return (mCenPos.Distance(cc.mCenPos) <= (mRadius + cc.mRadius));
  }
  
	friend bool	TestCCVsBC(const CircleCollider2D& cc, const BoxCollider2D& aabb);

public:
	Vector3	mCenPos;
	float	mRadius;
};



#endif
