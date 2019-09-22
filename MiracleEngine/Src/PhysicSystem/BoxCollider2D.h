///////////////////////////////////////////////////////////////////////////////////////
//
//	BoxCollider2D.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _BOX_COLLIDER_2D_H
#define _BOX_COLLIDER_2D_H

#include "GAM200-Vector3.h"
#include "GAM200-Vector2.h"

#include "CircleCollider2D.h"
#include "Collider2D.h"

// namespace MiracleEngine

class BoxCollider2D : public Collider2D // renderer
{
public:

  // Default Constructor
	BoxCollider2D() 
  { 
  }

	// Auxiliary constructor
	BoxCollider2D(const Vector3& minPos, const Vector3& maxPos) : 
			mMinPos(minPos), mMaxPos(maxPos), mCenPos((mMinPos+mMaxPos)/2.f)
  { 
  }
  
  // Copy Constructor
  BoxCollider2D(const BoxCollider2D& _bc) : 
			mMinPos(_bc.mMinPos), mMaxPos(_bc.mMaxPos), mCenPos(_bc.mCenPos) 
  { 
  }
  
  // Update position
	void		Move(const Vector3& vec)
  {
    mMinPos += vec;
    mMaxPos += vec;
    mCenPos += vec;
}

	// BC vs. Point test
	bool		TestBCVsPoint(const Vector3& p)
  {
    return (p.X() >= mMinPos.X() && p.X() <= mMaxPos.X() &&
        p.Y() >= mMinPos.Y() && p.Y() <= mMaxPos.Y());
  }
	// BC vs. BC test
	bool		TestBCVsBC(const BoxCollider2D& aabb)
  {
    if (mMaxPos.X() < aabb.mMinPos.X() || mMaxPos.Y() < aabb.mMinPos.Y() ||
      mMinPos.X() > aabb.mMaxPos.X() || mMinPos.Y() > aabb.mMaxPos.Y())
      return false;

    return true;
  }
	// BC vs. CC (point in lozenge) test
	friend bool	TestCCVsBC(const CircleCollider2D& cc, const BoxCollider2D& aabb);

public:
	Vector3		mMinPos;	// Top-left point with minimum x and y values
	Vector3		mMaxPos;	// Bottom-right point with maximum x and y values
	Vector3		mCenPos;	// Midpoint of diagonal from mMinPos and mMaxPos
};
bool TestCCVsBC(const CircleCollider2D& cc, const BoxCollider2D& aabb)
{
  BoxCollider2D box = aabb;

  if (box.TestBCVsPoint(cc.mCenPos))
    return true;

  if (distance(aabb.mMinPos, Vector3(aabb.mMinPos.X(), aabb.mMaxPos.Y()), cc.mCenPos) <= cc.mRadius ||
    distance(Vector3(aabb.mMinPos.X(), aabb.mMaxPos.Y()), aabb.mMaxPos, cc.mCenPos) <= cc.mRadius ||
    distance(aabb.mMaxPos, Vector3(aabb.mMaxPos.X(), aabb.mMinPos.Y()), cc.mCenPos) <= cc.mRadius ||
    distance(Vector3(aabb.mMaxPos.X(), aabb.mMinPos.Y()), aabb.mMinPos, cc.mCenPos) <= cc.mRadius)
    return true;

  return false;
}

#endif
