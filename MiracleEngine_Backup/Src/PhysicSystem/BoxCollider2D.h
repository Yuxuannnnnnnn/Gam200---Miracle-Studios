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
	Vector3		mMaxPos;	// Bottom-right point with maximum x and y values
	Vector3		mMinPos;	// Top-left point with minimum x and y values

public:

  // Default Constructor
	BoxCollider2D();

	// Auxiliary constructor
	BoxCollider2D(const Vector3& cenPos, const Vector3& scale);
  
  // Copy Constructor
	BoxCollider2D(const BoxCollider2D& _bc);
  
	void Update(const Vector3& cenPos, const Vector3& scale);

	// Box vs. Point test
	bool TestBoxVsPoint(const Vector3& pt);

	// BC vs. BC test
	bool TestBoxVsBox(const BoxCollider2D& box);

	// BC vs. CC (point in lozenge) test
	friend bool	TestCircleVsBox(const CircleCollider2D& cc, const BoxCollider2D& aabb);
};

#endif
