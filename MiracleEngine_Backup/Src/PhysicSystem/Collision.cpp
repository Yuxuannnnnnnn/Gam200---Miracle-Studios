///////////////////////////////////////////////////////////////////////////////////////
//
//	Collision.cpp
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#include "Collision.h"

int BoxBox_Intersection(const BoxCollider2D& circleA,				//CircleA data - input
	const Vector3& velA,														//CircleA velocity - input
	const BoxCollider2D& circleB,													//CircleB data - input
	const Vector3& velB,														//CircleA velocity - input
	Vector3& interPtA,														//Intersection point of CircleA at collision time - output
	Vector3& interPtB,														//Intersection point of CircleB at collision time - output
	float& interTime)														//intersection time - output
{
	(void)circleA;
	(void)velA;
	(void)circleB;
	(void)velB;
	(void)interPtA;
	(void)interPtB;
	(void)interTime;

	return 0;
}



int BoxEdge_Intersection(const BoxCollider2D& circle,			//Circle data - input
	const Vector3& ptEnd,													//End circle position - input
	const EdgeCollider2D& lineSeg,												//Line segment - input
	Vector3& interPt,														//Intersection position of the circle - output 
	Vector3& normalAtCollision,												//Normal vector at collision time - output
	float& interTime,														//Intersection time ti - output
	bool& checkLineEdges)													//The last parameter is new - for Extra Credits: true = check collision with line segment edges
{
	(void)circle;
	(void)ptEnd;
	(void)lineSeg;
	(void)interPt;
	(void)normalAtCollision;
	(void)interTime;
	(void)checkLineEdges;

	return 0;
}

// Extra credits
int CheckMovingBoxToEdge(bool withinBothLines,						//Flag stating that the circle is starting from between 2 imaginary line segments distant +/- Radius respectively - input
	const BoxCollider2D& circle,													//Circle data - input
	const Vector3& ptEnd,													//End circle position - input
	const EdgeCollider2D& lineSeg,												//Line segment - input
	Vector3& interPt,														//Intersection position of the circle - output 
	Vector3& normalAtCollision,												//Normal vector at collision time - output
	float& interTime)														//Intersection time ti - output
{
	(void)withinBothLines;
	(void)circle;
	(void)ptEnd;
	(void)lineSeg;
	(void)interPt;
	(void)normalAtCollision;
	(void)interTime;

	return 0;
}

int RayBox_Intersection(const Ray& ray,							//A ray containing the data of the moving dot - input
	const BoxCollider2D& circle,													//Static circle data - input
	float& interTime)														//Intersection time - output
{
	(void)ray;
	(void)circle;
	(void)interTime;

	return 0;
}

// RESPONSE FUNCTIONS
void BoxEdge_Response(const Vector3& ptInter,				//Intersection position of the circle - input
	const Vector3& normal,													//Normal vector of reflection on collision time - input
	Vector3& ptEnd,															//Final position of the circle after reflection - output
	Vector3& reflected)														//Normalized reflection vector direction - output
{
	(void)ptInter;
	(void)normal;
	(void)ptEnd;
	(void)reflected;
}

void BoxPillar_Response(const Vector3& normal,					//Normal vector of reflection on collision time - input
	const float& interTime,													//Intersection time - input
	const Vector3& ptStart,													//Starting position of the circle - input
	const Vector3& ptInter,													//Intersection position of the circle - input
	Vector3& ptEnd,															//Final position of the circle after reflection - output
	Vector3& reflectedVectorNormalized)										//Normalized reflection vector - output
{
	(void)normal;
	(void)interTime;
	(void)ptStart;
	(void)ptInter;
	(void)ptEnd;
	(void)reflectedVectorNormalized;
}

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
	Vector3& ptEndB)														//Final position of the circle B after reflection - output
{
	(void)normal;
	(void)interTime;
	(void)velA;
	(void)massA;
	(void)interPtA;
	(void)velB;
	(void)massB;
	(void)interPtB;
	(void)reflectedVectorA;
	(void)ptEndA;
	(void)reflectedVectorB;
	(void)ptEndB;
}

/******************************************************************************/
/*!
	Check for collision between a line and circle.
 */
 /******************************************************************************/
int CircleEdge_Intersection(const CircleCollider2D& circle,			//Circle data - input
	const Vector3& ptEnd,													//End circle position - input
	const EdgeCollider2D& lineSeg,												//Line segment - input
	Vector3& interPt,														//Intersection position of the circle - output 
	Vector3& normalAtCollision,												//Normal vector at collision time - output
	float& interTime,														//Intersection time ti - output
	bool& checkLineEdges)
{
	//Velocity vector and normal
	Vector3 velocity = ptEnd - circle.mCenPos;
	Vector3 velNormal(velocity._y, -velocity._x);



	//N.P0 - N.Bs
	float dist = lineSeg.m_normal.Dot(lineSeg.m_pt0 - circle.mCenPos);

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
		float tempf = temp.Dot(velNormal);
		//BsP1'
		temp = LNS1.m_pt1 - circle.mCenPos;
		tempf *= temp.Dot(velNormal);
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

				std::cout << "velocity !" << velocity << std::endl;

				std::cout << "dist !" << dist << std::endl;
				std::cout << "circle.mRadius !" << circle.mRadius << std::endl;

				std::cout << "DDDDDDDDDD !" << interPt << std::endl;
				std::cout << lineSeg.m_normal << std::endl;
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
		temp = lineSeg.m_normal * circle.mRadius;
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
				std::cout << "AAAAAAAAA !" << std::endl;
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
int CheckMovingCircleToEdge(bool withinBothLines,						//Flag stating that the circle is starting from between 2 imaginary line segments distant +/- Radius respectively - input
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
				std::cout << "CCCCCCCC !" << std::endl;
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
				std::cout << "BBBBBBBBBB !" << std::endl;
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
int CircleCircle_Intersection(const CircleCollider2D& circleA,				//CircleA data - input
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
int RayCircle_Intersection(const Ray& ray,							//A ray containing the data of the moving dot - input
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
void CircleEdge_Response(const Vector3& ptInter,
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
	projectedVec = normal * projectedDist;

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
void CirclePillar_Response(const Vector3& normal,
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
	float projectedDist = 2 * (penetrateVec * normal);
	projectedVec = normal * projectedDist;

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
void CircleCircle_Response(Vector3& normal,
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
	reflectedVectorA = velA - normal * (((2 * (velA._x - velB._x)) / (massA + massB)) * massB);
	reflectedVectorB = velB + normal * (((2 * (velA._x - velB._x)) / (massA + massB)) * massA);

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
