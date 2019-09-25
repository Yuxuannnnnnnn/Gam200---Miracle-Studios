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

#include "../MathLib/Vector3.h"
#include "../MathLib/Vector2.h"

#include "Collider2D.h"
#include "EdgeCollider2D.h"

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

// namespace MiracleEngine

class BoxCollider2D;

class CircleCollider2D : public Collider2D // Renderer
{
public:
  // Default Constructor
	CircleCollider2D();
  
  // Conversion Constructor
	CircleCollider2D(const Vector3& center, float radius);
  
  // Copy Constructor
	CircleCollider2D(const CircleCollider2D& _cc);
  
  //Default Destructor
	~CircleCollider2D();
  
	void Move(const Vector3& vec);

	bool TestCircleVsPoint(const Vector3& p) const;

	bool TestCircleVsCircle(const CircleCollider2D& cc) const;
  
	

	int CircleCircle_Intersection(const CircleCollider2D& circleA,				//CircleA data - input
		const Vector3& velA,														//CircleA velocity - input
		const CircleCollider2D& circleB,													//CircleB data - input
		const Vector3& velB,														//CircleA velocity - input
		Vector3& interPtA,														//Intersection point of CircleA at collision time - output
		Vector3& interPtB,														//Intersection point of CircleB at collision time - output
		float& interTime);														//intersection time - output



	int CircleEdge_Intersection(const CircleCollider2D& circle,			//Circle data - input
		const Vector3& ptEnd,													//End circle position - input
		const EdgeCollider2D& lineSeg,												//Line segment - input
		Vector3& interPt,														//Intersection position of the circle - output 
		Vector3& normalAtCollision,												//Normal vector at collision time - output
		float& interTime,														//Intersection time ti - output
		bool& checkLineEdges);													//The last parameter is new - for Extra Credits: true = check collision with line segment edges

	// Extra credits
	int CheckMovingCircleToEdge(bool withinBothLines,						//Flag stating that the circle is starting from between 2 imaginary line segments distant +/- Radius respectively - input
		const CircleCollider2D& circle,													//Circle data - input
		const Vector3& ptEnd,													//End circle position - input
		const EdgeCollider2D& lineSeg,												//Line segment - input
		Vector3& interPt,														//Intersection position of the circle - output 
		Vector3& normalAtCollision,												//Normal vector at collision time - output
		float& interTime);														//Intersection time ti - output

	int RayCircle_Intersection(const Ray& ray,							//A ray containing the data of the moving dot - input
		const CircleCollider2D& circle,													//Static circle data - input
		float& interTime);														//Intersection time - output

	// RESPONSE FUNCTIONS
	void CircleEdge_Response(const Vector3& ptInter,				//Intersection position of the circle - input
		const Vector3& normal,													//Normal vector of reflection on collision time - input
		Vector3& ptEnd,															//Final position of the circle after reflection - output
		Vector3& reflected);														//Normalized reflection vector direction - output

	void CirclePillar_Response(const Vector3& normal,					//Normal vector of reflection on collision time - input
		const float& interTime,													//Intersection time - input
		const Vector3& ptStart,													//Starting position of the circle - input
		const Vector3& ptInter,													//Intersection position of the circle - input
		Vector3& ptEnd,															//Final position of the circle after reflection - output
		Vector3& reflectedVectorNormalized);										//Normalized reflection vector - output

	// Extra credits
	void CircleCircle_Response(Vector3& normal,							//Normal vector of reflection on collision time - input
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
	friend bool	TestCircleVsBox(const CircleCollider2D&, const BoxCollider2D&);
public:
	Vector3	mCenPos;
	float	mRadius;
};



#endif
