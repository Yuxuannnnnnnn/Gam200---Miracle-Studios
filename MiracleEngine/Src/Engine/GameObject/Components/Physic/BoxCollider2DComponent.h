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

#include "ICollider2D.h"

typedef unsigned int outcode;
#define TOP 0x0008 //1000
#define BOTTOM 0x0004 //0100
#define RIGHT 0x0002 //0010
#define LEFT 0x0001 //0001

enum class OutCode_Type {
	TOP_LEFT = 1001,
	TOP_CENTER = 1000,
	TOP_RIGHT = 1010,
	CENTER_LEFT = 0001,
	CENTER = 0000,
	CENTER_RIGHT = 0010,
	BOTTOM_LEFT = 0101,
	BOTTOM_CENTER = 0100,
	BOTTOM_RIGHT = 0110
};

class BoxCollider2D : public Collider2D // renderer
{
public:
	// AABB
	Vector3		mMaxPos;	// Bottom-right point with maximum x and y values
	Vector3		mMinPos;	// Top-left point with minimum x and y values

	//OBB
	Vector3 mOrigin; // corner[0].dot(axis[a])
	Vector3 mCorner[4]; // Corners of the box, where 0 is the lower left.
	Vector3 mAxis[2];  // Two edges of the box extended away from corner[0].

	Vector3 mScale;
	float mAngle;

public:
	BoxCollider2D();
	BoxCollider2D(const BoxCollider2D& rhs) = default;
	virtual ~BoxCollider2D() = default;
	
	BoxCollider2D& operator=(const BoxCollider2D& rhs) = delete;
	
	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser& document) override;
	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;
	void Inspect() override;

///////////////////////////////////////////////////////////////////////////////
	// Function Setting and Getting only

};

#endif

