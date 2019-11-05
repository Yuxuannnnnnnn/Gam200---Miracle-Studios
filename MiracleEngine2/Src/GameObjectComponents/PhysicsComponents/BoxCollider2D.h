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

	//OOBB
	Vector3 mCorner[4]; // Corners of the box, where 0 is the lower left.
	Vector3 mAxis[2];  // Two edges of the box extended away from corner[0].
	Vector3 mOrigin; // corner[0].dot(axis[a])

	float mAngle;

	bool mOnce;
public:

	void SerialiseComponent(Serialiser& document) override;
	void Inspect() override;

	// Constructor
	BoxCollider2D(GameObject* parent, size_t uId, IComponentSystem* component = nullptr);

	BoxCollider2D(TransformComponent* transform = nullptr);
	virtual ~BoxCollider2D() {}

	// A copy empty shell object
	BoxCollider2D(const BoxCollider2D& rhs);
	//No replication of class object
	BoxCollider2D& operator= (const BoxCollider2D& rhs) = delete;

	void Draw();
	void Update();

	void Update(Vector3 pos, Vector3 scale, float angle);

	void ComputeAxes();

	bool TestAABBVsPoint(const Vector3& pt);
	bool TestAABBVsAABB(const BoxCollider2D& aabb);
	bool TestOOBBVsPoint(const Vector3& pt) const;
	bool TestOOBBVsOOBB(const BoxCollider2D& oobb) const;
	bool TestOverlaps(const BoxCollider2D& oobb) const;

	bool TestBoxVsPoint(const Vector3& pt);
	bool TestBoxVsBox(const BoxCollider2D& box);
	int TestOutCode(const Vector3& pt) const;
	


	friend bool	TestCircleVsBox(const CircleCollider2D& circle, const BoxCollider2D& box);
};

bool TestCircleVsAABB(const CircleCollider2D& circle, const BoxCollider2D& aabb);
bool TestCircleVsOOBB(const CircleCollider2D& circle, const BoxCollider2D& oobb);

#endif

