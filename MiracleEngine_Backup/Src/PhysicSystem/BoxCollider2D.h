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

#include "../MathLib/Vector3.h"
#include "../MathLib/Vector2.h"

#include "CircleCollider2D.h"
#include "Collider2D.h"

// namespace MiracleEngine

class BoxCollider2D : public Collider2D // renderer
{
public:

  // Default Constructor
	BoxCollider2D();

	// Auxiliary constructor
	BoxCollider2D(const Vector3& minPos, const Vector3& maxPos);
  
  // Copy Constructor
	BoxCollider2D(const BoxCollider2D& _bc);
  
  // Update position
	void Move(const Vector3& vec);

	// Box vs. Point test
	bool TestBoxVsPoint(const Vector3& pt);

	// BC vs. BC test
	bool TestBoxVsBox(const BoxCollider2D& box);

	// BC vs. CC (point in lozenge) test
	friend bool	TestCircleVsBox(const CircleCollider2D& cc, const BoxCollider2D& aabb);

	int BoxBox_Intersection(const BoxCollider2D& circleA,				//CircleA data - input
		const Vector3& velA,														//CircleA velocity - input
		const BoxCollider2D& circleB,													//CircleB data - input
		const Vector3& velB,														//CircleA velocity - input
		Vector3& interPtA,														//Intersection point of CircleA at collision time - output
		Vector3& interPtB,														//Intersection point of CircleB at collision time - output
		float& interTime);														//intersection time - output



	int BoxEdge_Intersection(const BoxCollider2D& circle,			//Circle data - input
		const Vector3& ptEnd,													//End circle position - input
		const EdgeCollider2D& lineSeg,												//Line segment - input
		Vector3& interPt,														//Intersection position of the circle - output 
		Vector3& normalAtCollision,												//Normal vector at collision time - output
		float& interTime,														//Intersection time ti - output
		bool& checkLineEdges);													//The last parameter is new - for Extra Credits: true = check collision with line segment edges

	// Extra credits
	int CheckMovingBoxToEdge(bool withinBothLines,						//Flag stating that the circle is starting from between 2 imaginary line segments distant +/- Radius respectively - input
		const BoxCollider2D& circle,													//Circle data - input
		const Vector3& ptEnd,													//End circle position - input
		const EdgeCollider2D& lineSeg,												//Line segment - input
		Vector3& interPt,														//Intersection position of the circle - output 
		Vector3& normalAtCollision,												//Normal vector at collision time - output
		float& interTime);														//Intersection time ti - output

	int RayBox_Intersection(const Ray& ray,							//A ray containing the data of the moving dot - input
		const BoxCollider2D& circle,													//Static circle data - input
		float& interTime);														//Intersection time - output

	// RESPONSE FUNCTIONS
	void BoxEdge_Response(const Vector3& ptInter,				//Intersection position of the circle - input
		const Vector3& normal,													//Normal vector of reflection on collision time - input
		Vector3& ptEnd,															//Final position of the circle after reflection - output
		Vector3& reflected);														//Normalized reflection vector direction - output

	void BoxPillar_Response(const Vector3& normal,					//Normal vector of reflection on collision time - input
		const float& interTime,													//Intersection time - input
		const Vector3& ptStart,													//Starting position of the circle - input
		const Vector3& ptInter,													//Intersection position of the circle - input
		Vector3& ptEnd,															//Final position of the circle after reflection - output
		Vector3& reflectedVectorNormalized);										//Normalized reflection vector - output

	// Extra credits
	void BoxBox_Response(Vector3& normal,							//Normal vector of reflection on collision time - input
		const float interTime,													//Intersection time - input
		Vector3& velA,															//Velocity of CircleA - input
		const float& massA,														//Mass of CircleA - input
		Vector3& interPtA,														//Intersection position of circle A at collision time - input
		Vector3& velB,															//Velocity of CircleB - input
		const float& massB,														//Mass of CircleB - input
		Vector3& interPtB,														//Intersection position of circle B at collision time - input
		Vector3& reflectedVectorA,												//Non-Normalized reflected vector of Circle A - output
		Vector3& ptEndA,															//Final position of the circle A after reflection - output
		Vector3& reflectedVectorB,												//Non-Normalized reflected vector of Circle B - output
		Vector3& ptEndB);														//Final position of the circle B after reflection - output

public:
	Vector3		mMinPos;	// Top-left point with minimum x and y values
	Vector3		mMaxPos;	// Bottom-right point with maximum x and y values
	Vector3		mCenPos;	// Midpoint of diagonal from mMinPos and mMaxPos
};

bool TestCircleVsBox(const CircleCollider2D& cc, const BoxCollider2D& aabb)
{
  BoxCollider2D box = aabb;

  if (box.TestBoxVsPoint(cc.mCenPos))
    return true;

  if (distance(aabb.mMinPos, Vector3(aabb.mMinPos.X(), aabb.mMaxPos.Y()), cc.mCenPos) <= cc.mRadius ||
    distance(Vector3(aabb.mMinPos.X(), aabb.mMaxPos.Y()), aabb.mMaxPos, cc.mCenPos) <= cc.mRadius ||
    distance(aabb.mMaxPos, Vector3(aabb.mMaxPos.X(), aabb.mMinPos.Y()), cc.mCenPos) <= cc.mRadius ||
    distance(Vector3(aabb.mMaxPos.X(), aabb.mMinPos.Y()), aabb.mMinPos, cc.mCenPos) <= cc.mRadius)
    return true;

  return false;
}

#endif
