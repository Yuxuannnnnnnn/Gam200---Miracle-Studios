///////////////////////////////////////////////////////////////////////////////////////
//
//	CircleCollider2D.cpp
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#include "CircleCollider2D.h"



CircleCollider2D::CircleCollider2D() : mCenPos(0.f, 0.f), mRadius(0.f)
{
}

CircleCollider2D::CircleCollider2D(const Vector3& center, float radius) : mCenPos{ center }, mRadius{ radius }
{
}

CircleCollider2D::CircleCollider2D(const CircleCollider2D& _cc) : mCenPos{ _cc.mCenPos }, mRadius{ _cc.mRadius }
{
}

CircleCollider2D::~CircleCollider2D()
{
}

void CircleCollider2D::Move(const Vector3& vec)
{
	mCenPos += vec;
}

bool CircleCollider2D::TestCircleVsPoint(const Vector3& pt) const
{
	Vector3 diff = pt - mCenPos;
	return (diff.Length() <= mRadius);
}

bool CircleCollider2D::TestCircleVsCircle(const CircleCollider2D& circle) const
{
	return (mCenPos.Distance(circle.mCenPos) <= (mRadius + circle.mRadius));
}

/******************************************************************************/
/*!
	Check for collision between a line and circle.
 */
 /******************************************************************************/
int CircleCollider2D::CircleEdge_Intersection(const CircleCollider2D& circle,			//Circle data - input
	const Vector3& ptEnd,													//End circle position - input
	const EdgeCollider2D& lineSeg,												//Line segment - input
	Vector3& interPt,														//Intersection position of the circle - output 
	Vector3& normalAtCollision,												//Normal vector at collision time - output
	float& interTime,														//Intersection time ti - output
	bool& checkLineEdges)
{
	//Velocity vector and normal
	Vector3 velocity = ptEnd - circle.mCenPos;
	Vector3 velNormal(velocity.y, -velocity.x);

	//N.P0 - N.Bs
	float dist = lineSeg.m_normal * (lineSeg.m_pt0 - circle.mCenPos);

	if (dist > circle.mRadius)
	{
		EdgeCollider2D LNS1;
		Vector3 temp;
		//R*unit N
		temp = lineSeg.m_normal * circle.mRadius;
		//p0' and p1'
		LNS1.m_pt0 = lineSeg.m_pt0 - temp;
		LNS1.m_pt1 = lineSeg.m_pt1 - temp;
		LNS1.m_normal = lineSeg.m_normal;

		//BsP0'
		temp = LNS1.m_pt0 - circle.mCenPos;
		float tempf = temp * velNormal;
		//BsP1'
		temp = LNS1.m_pt1 - circle.mCenPos;
		tempf *= temp * velNormal;
		if (tempf < 0)
		{
			//Ti = ( N.P0 - N.Bs - R / N.V )
			interTime = (lineSeg.m_normal * lineSeg.m_pt0
				- lineSeg.m_normal * circle.mCenPos - circle.mRadius) /
				(lineSeg.m_normal * velocity);

			if (0 <= interTime && interTime <= 1)
			{
				interPt = circle.mCenPos + velocity * interTime;
				normalAtCollision = -lineSeg.m_normal;
				return 1;
			}
			return 0;
		}
		else
		{
			if (checkLineEdges)
				return CheckMovingCircleToEdge(false, circle, ptEnd, lineSeg, interPt, normalAtCollision, interTime);
			else
				return 0;
		}
	}
	else if (dist < -circle.mRadius)
	{
		EdgeCollider2D LNS2;
		Vector3 temp;
		//R* unit N
		temp =  lineSeg.m_normal * circle.mRadius;
		//P0' and P1'
		LNS2.m_pt0 = lineSeg.m_pt0 + temp;
		LNS2.m_pt1 = lineSeg.m_pt1 + temp;
		LNS2.m_normal = lineSeg.m_normal;

		//BsP0'
		temp = LNS2.m_pt0 - circle.mCenPos;
		float tempf = temp * velNormal;
		//BsP1'
		temp = LNS2.m_pt1 - circle.mCenPos;
		tempf *= temp * velNormal;
		if (tempf < 0)
		{
			//Ti = ( N.P0 - N.Bs + R / N.V )
			interTime = (lineSeg.m_normal * lineSeg.m_pt0
				- lineSeg.m_normal * circle.mCenPos + circle.mRadius) /
				(lineSeg.m_normal * velocity);

			if (0 <= interTime && interTime <= 1)
			{
				interPt = circle.mCenPos + velocity * interTime;
				normalAtCollision = lineSeg.m_normal;
				return 1;
			}
			return 0;
		}
		else
		{
			if (checkLineEdges)
				return CheckMovingCircleToEdge(false, circle, ptEnd, lineSeg, interPt, normalAtCollision, interTime);
			else
				return 0;
		}
	}
	else
	{
		if (checkLineEdges)
			return CheckMovingCircleToEdge(true, circle, ptEnd, lineSeg, interPt, normalAtCollision, interTime);
		else
			return 0;
	}
}

/******************************************************************************/
/*!
	Check for collision with a line edge. Extra credit.
*/
/******************************************************************************/
int CircleCollider2D::CheckMovingCircleToEdge(bool withinBothLines,						//Flag stating that the circle is starting from between 2 imaginary line segments distant +/- Radius respectively - input
	const CircleCollider2D& circle,													//Circle data - input
	const Vector3& ptEnd,													//End circle position - input
	const EdgeCollider2D& lineSeg,												//Line segment - input
	Vector3& interPt,														//Intersection position of the circle - output 
	Vector3& normalAtCollision,												//Normal vector at collision time - output
	float& interTime)
{
	bool p0inter = true;
	bool p1inter = true;

	Vector3 relVel = ptEnd - circle.mCenPos;
	Vector3 relVelNormal = relVel;
	relVelNormal.Normalize();

	Vector3 startToLineEdge0;
	startToLineEdge0 = lineSeg.m_pt0 - circle.mCenPos;

	float m0 = relVelNormal * startToLineEdge0;

	Vector3 startToLineEdge1;
	startToLineEdge1 = lineSeg.m_pt1 - circle.mCenPos;

	float m1 = relVelNormal * startToLineEdge1;

	float r = circle.mRadius * circle.mRadius;


	if (withinBothLines)
	{
		float n0 = startToLineEdge0.SquaredLength() - (m0 * m0);
		float n1 = startToLineEdge1.SquaredLength() - (m1 * m1);

		if (m0 < 0)
		{
			p0inter = false;
		}
		else if (n0 > r)
		{
			p0inter = false;
		}

		if (m1 < 0)
		{
			p1inter = false;
		}
		else if (n1 > r)
		{
			p1inter = false;
		}

		if (p0inter && p1inter)
		{
			if (m0 < m1)
			{
				p0inter = true;
				p1inter = false;
			}
			else
			{
				p0inter = false;
				p1inter = true;
			}
		}

		if (p0inter)
		{
			float s = r - n0;
			float tiFirst = (m0 - sqrt(s)) / relVel.Length();
			float tiSecond = (m0 + sqrt(s)) / relVel.Length();
			float ti = fminf(tiFirst, tiSecond);
			if (0 <= ti && ti <= 1)
			{
				interPt = circle.mCenPos + (relVel * ti);
				normalAtCollision = interPt - lineSeg.m_pt0;
				normalAtCollision.Normalize();
				interTime = ti;
				return 1;
			}
			return 0;
		}
		else if (p1inter)
		{
			float s = r - n1;
			float tiFirst = (m1 - sqrt(s)) / relVel.Length();
			float tiSecond = (m1 + sqrt(s)) / relVel.Length();
			float ti = fminf(tiFirst, tiSecond);
			if (0 <= ti && ti <= 1)
			{
				interPt = circle.mCenPos + (relVel * ti);
				normalAtCollision = interPt - lineSeg.m_pt1;
				normalAtCollision.Normalize();
				interTime = ti;
				return 1;
			}
			return 0;
		}
	}
	else
	{
		float n0 = startToLineEdge0.SquaredLength() - (m0 * m0);
		float n1 = startToLineEdge1.SquaredLength() - (m1 * m1);

		if (m0 < 0)
		{
			p0inter = false;
		}
		else if (n0 > r)
		{
			p0inter = false;
		}

		if (m1 < 0)
		{
			p1inter = false;
		}
		else if (n1 > r)
		{
			p1inter = false;
		}

		if (p0inter)
		{
			float s = r - n0;
			float tiFirst = (m0 - sqrt(s)) / relVel.Length();
			float tiSecond = (m0 + sqrt(s)) / relVel.Length();
			float ti = fminf(tiFirst, tiSecond);
			if (0 <= ti && ti <= 1)
			{
				interPt = circle.mCenPos + (relVel * ti);
				normalAtCollision = interPt - lineSeg.m_pt0;
				normalAtCollision.Normalize();
				interTime = ti;
				return 1;
			}
			return 0;
		}
		else if (p1inter)
		{
			float s = r - n1;
			float tiFirst = (m1 - sqrt(s)) / relVel.Length();
			float tiSecond = (m1 + sqrt(s)) / relVel.Length();
			float ti = fminf(tiFirst, tiSecond);
			if (0 <= ti && ti <= 1)
			{
				interPt = circle.mCenPos + (relVel * ti);
				normalAtCollision = interPt - lineSeg.m_pt1;
				normalAtCollision.Normalize();
				interTime = ti;
				return 1;
			}
			return 0;
		}
	}
	return 0;//no collision
}

/******************************************************************************/
/*!
	Check collision between dynamic/static circles.
 */
 /******************************************************************************/
int CircleCollider2D::CircleCircle_Intersection(const CircleCollider2D& circleA,				//CircleA data - input
	const Vector3& velA,														//CircleA velocity - input
	const CircleCollider2D& circleB,													//CircleB data - input
	const Vector3& velB,														//CircleA velocity - input
	Vector3& interPtA,														//Intersection point of CircleA at collision time - output
	Vector3& interPtB,														//Intersection point of CircleB at collision time - output
	float& interTime)
{
	CircleCollider2D c;
	c.mRadius = circleA.mRadius + circleB.mRadius;
	c.mCenPos = circleB.mCenPos;

	Vector3 relVel = velA - velB;
	Vector3 relVelNormal = relVel;
	relVelNormal.Normalize();

	Vector3 startToCircle;
	startToCircle = c.mCenPos - circleA.mCenPos;

	float m = startToCircle * relVelNormal;
	float n = startToCircle.SquaredLength() - (m * m);
	float r = c.mRadius * c.mRadius;

	if (m < 0)
	{
		return 0;
	}
	else if (n > r)
	{
		return 0;
	}
	else
	{
		float s = r - n;
		float tiFirst = (m - sqrt(s)) / relVel.Length();
		float tiSecond = (m + sqrt(s)) / relVel.Length();
		float ti = fminf(tiFirst, tiSecond);
		if (0 <= ti && ti <= 1)
		{
			interPtA = circleA.mCenPos + (velA * ti);
			interPtB = circleB.mCenPos + (velB * ti);
			interTime = ti;
			return 1;
		}
		return 0;
	}
}

/******************************************************************************/
/*!
	Helper function with collision between circles.
 */
 /******************************************************************************/
int CircleCollider2D::RayCircle_Intersection(const Ray& ray,							//A ray containing the data of the moving dot - input
	const CircleCollider2D& circle,													//Static circle data - input
	float& interTime)
{
	// your code goes here
	(void)(ray);
	(void)(circle);
	(void)(interTime);

	return 0;
}


/******************************************************************************/
/*!
	Calculate the collision response between circle and line.
 */
 /******************************************************************************/
void CircleCollider2D::CircleEdge_Response(const Vector3& ptInter,
	const Vector3& normal,
	Vector3& ptEnd,
	Vector3& reflected)
{
	//Assuming that the normal passed in is already normalized
	Vector3 penetrateVec;
	penetrateVec = ptEnd - ptInter;

	//Calculate projected vector
	Vector3 projectedVec;
	float projectedDist = 2 * (penetrateVec * normal);
	projectedVec = normal* projectedDist;

	//Calculate point after reflection
	ptEnd = ptInter + penetrateVec - projectedVec;

	//Calculation normalized reflection vector
	Vector3 reflectVec;
	reflectVec = ptEnd - ptInter;
	reflected = reflectVec;
	reflected.Normalize();
}

/******************************************************************************/
/*!
	Calculate collision response between circle and static circle.
 */
 /******************************************************************************/
void CircleCollider2D::CirclePillar_Response(const Vector3& normal,
	const float& interTime,
	const Vector3& ptStart,
	const Vector3& ptInter,
	Vector3& ptEnd,
	Vector3& reflectedVectorNormalized)
{
	(void)(interTime);
	(void)(ptStart);

	//Assuming that the normal passed in is already normalized
	Vector3 penetrateVec;
	penetrateVec = ptEnd - ptInter;

	//Calculate projected vector
	Vector3 projectedVec;
	float projectedDist = 2 *(penetrateVec * normal);
	projectedVec =  normal * projectedDist;

	//Calculate point after reflection
	ptEnd = ptInter + penetrateVec - projectedVec;

	//Calculation normalized reflection vector
	Vector3 reflectVec;
	reflectVec = ptEnd - ptInter;
	reflectedVectorNormalized = reflectVec;
	reflectedVectorNormalized.Normalize();
}

/******************************************************************************/
/*!
	Extra credits
 */
 /******************************************************************************/
void CircleCollider2D::CircleCircle_Response(Vector3& normal,
	const float interTime,
	Vector3& velA,
	const float& massA,
	Vector3& interPtA,
	Vector3& velB,
	const float& massB,
	Vector3& interPtB,
	Vector3& reflectedVectorA,
	Vector3& ptEndA,
	Vector3& reflectedVectorB,
	Vector3& ptEndB)
{
	reflectedVectorA = velA - normal * (((2 * (velA.x - velB.x)) / (massA + massB)) * massB);
	reflectedVectorB = velB + normal * (((2 * (velA.x - velB.x)) / (massA + massB)) * massA);

	float velLengthA;
	velLengthA = reflectedVectorA.Length();
	float velLengthB;
	velLengthB = reflectedVectorB.Length();

	Vector3 relVelNormalA = reflectedVectorA;
	relVelNormalA.Normalize();
	Vector3 relVelNormalB = reflectedVectorB;
	relVelNormalB.Normalize();

	ptEndA = interPtA + relVelNormalA * (velLengthA * (1.f - interTime));
	ptEndB = interPtB + relVelNormalB * (velLengthB * (1.f - interTime));
}
