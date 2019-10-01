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

#include "CircleCollider2D.h"

#include "Collider2D.h"

// namespace MiracleEngine

class BoxCollider2D : public Collider2D // renderer
{
public:
	// AABB
	Vector3		mMaxPos;	// Bottom-right point with maximum x and y values
	Vector3		mMinPos;	// Top-left point with minimum x and y values

	//OOBB
	Vector3 mCorner[4]; // Corners of the box, where 0 is the lower left.
	Vector3 mAxis[2];  // Two edges of the box extended away from corner[0].
	Vector3 mOrigin; // corner[0].dot(axis[a])

	float mAngle;
public:

  // Default Constructor
	BoxCollider2D();

	// Auxiliary constructor
	BoxCollider2D(const Vector3& cenPos, const Vector3& scale, float angle);
  
  // Copy Constructor
	BoxCollider2D(const BoxCollider2D& _bc);
	void Draw();
	void Update(const Vector3& cenPos, const Vector3& scale, float angle);

	void ComputeAxes();

	bool TestAABBVsPoint(const Vector3& pt);
	bool TestAABBVsAABB(const BoxCollider2D& aabb);
	bool TestOOBBVsPoint(const Vector3& pt) const;
	bool TestOOBBVsOOBB(const BoxCollider2D& oobb) const;
	bool TestOverlaps(const BoxCollider2D& oobb) const;

	bool TestBoxVsPoint(const Vector3& pt);
	bool TestBoxVsBox(const BoxCollider2D& box);
	friend bool	TestCircleVsBox(const CircleCollider2D& circle, const BoxCollider2D& box);
};

bool TestCircleVsAABB(const CircleCollider2D& circle, const BoxCollider2D& aabb);
bool TestCircleVsOOBB(const CircleCollider2D& circle, const BoxCollider2D& oobb);

#endif

