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

#include "Collider2D.h"
#include "EdgeCollider2D.h"

// namespace MiracleEngine

class BoxCollider2D;

class CircleCollider2D : public Collider2D // Renderer
{
public:
	Vector3	mCenPos;
	float	mRadius;

public:
  // Default Constructor
	CircleCollider2D();
  
  // Conversion Constructor
	CircleCollider2D(const Vector3& center, float radius);
  
  // Copy Constructor
	CircleCollider2D(const CircleCollider2D& _cc);
  
  //Default Destructor
	~CircleCollider2D();

	void Update(const Vector3& center, float radius);

	bool TestCircleVsPoint(const Vector3& p) const;

	bool TestCircleVsCircle(const CircleCollider2D& cc) const;

	friend bool	TestCircleVsBox(const CircleCollider2D& circle, const BoxCollider2D& box);
};



#endif
