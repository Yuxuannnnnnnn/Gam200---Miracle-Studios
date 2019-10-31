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

class CircleCollider2D : public Collider2D
{
public:
	Vector3	mCenPos;
	float	mRadius;

public:
    // Constructor
	CircleCollider2D(TransformComponent* transform = nullptr);
	virtual ~CircleCollider2D() {}

	// A copy empty shell object
	CircleCollider2D(const CircleCollider2D& rhs);
	//No replication of class object
	CircleCollider2D& operator= (const CircleCollider2D& rhs) = delete;

	void Draw();
	void Update();

	bool TestCircleVsPoint(const Vector3& p) const;
	bool TestCircleVsCircle(const CircleCollider2D& cc) const;

	friend bool	TestCircleVsBox(const CircleCollider2D& circle, const BoxCollider2D& box);
};



#endif
