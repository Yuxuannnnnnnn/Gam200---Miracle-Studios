///////////////////////////////////////////////////////////////////////////////////////
//
//	Collision.cpp
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#include "Collision.h"

void UpdateCollision(COLLISION_TYPE type, Collider2D* rhs, Collider2D* lhs, double dt)
{
	GameObject* gameObjectA = nullptr;
	GameObject* gameObjectB = nullptr;
	RigidBody2D *gameBodyA = nullptr; 
	RigidBody2D* gameBodyB = nullptr;

	Vector3 posNextA = Vector3::Vec3Zero;
	Vector3 posNextB = Vector3::Vec3Zero;
	Vector3 velA = Vector3::Vec3Zero; 
	Vector3 velB = Vector3::Vec3Zero;
	Vector3 interPtA = Vector3::Vec3Zero;
	Vector3 interPtB = Vector3::Vec3Zero;
	Vector3 reflectedVecA = Vector3::Vec3Zero; 
	Vector3 reflectedVecB = Vector3::Vec3Zero;
	Vector3 normal = Vector3::Vec3Zero; 
	Vector3 normalAtCollision = Vector3::Vec3Zero;

	float interTime = 0.f;


	switch (type)
	{
	case BOX_BOX:
	{
		break;
	}
	case CIRCLE_CIRCLE:
	{
		CircleCollider2D* circleA = dynamic_cast<CircleCollider2D*>(rhs);
		CircleCollider2D* circleB = dynamic_cast<CircleCollider2D*>(lhs);

		gameObjectA = circleA->_gameObject;
		gameBodyA = circleA->_body;

		if (gameBodyA)
		{
			velA = gameBodyA->_velocity * (float)dt;
			posNextA = gameObjectA->_pos + velA;
		}
		else
			posNextA = gameObjectA->_pos;

		circleA->Update(gameObjectA->_pos, gameObjectA->_scale._x / 2);

		gameObjectB = circleB->_gameObject;
		gameBodyB = circleB->_body;

		if (gameBodyB)
		{
			velB = gameBodyB->_velocity * (float)dt;
			posNextB = gameObjectB->_pos + velB;
		}
		else
			posNextB = gameObjectB->_pos;

		circleB->Update(gameObjectB->_pos, gameObjectB->_scale._x / 2);

		if (CircleCircle_Intersection(*circleA, velA, *circleB, velB, interPtA, interPtB, interTime))
		{
			normal = interPtA - interPtB;
			normal.Normalize();

			reflectedVecA = velA;
			reflectedVecB = velB;

			std::cout << "collided" << std::endl;

			CircleCircle_Response(normal, interTime, velA, 1, interPtA, velB, 1, interPtB,
				reflectedVecA, posNextA, reflectedVecB, posNextB);

			if (gameBodyA)
				gameBodyA->_velocity = reflectedVecA * gameBodyA->_velocity.Length();

			if (gameBodyB)
				gameBodyB->_velocity = reflectedVecB * gameBodyB->_velocity.Length();
		}


		break;
	}
	case CIRCLE_LINE:
	{
		CircleCollider2D* circleA = dynamic_cast<CircleCollider2D*>(rhs);
		EdgeCollider2D* lineB = dynamic_cast<EdgeCollider2D*>(lhs);

		gameObjectA = circleA->_gameObject;
		gameBodyA = circleA->_body;

		if (gameBodyA)
		{
			velA = gameBodyA->_velocity * (float)dt;
			posNextA = gameObjectA->_pos + velA;
		}
		else
			posNextA = gameObjectA->_pos;

		circleA->Update(gameObjectA->_pos, gameObjectA->_scale._x / 2);

		bool t = true;

		if (CircleEdge_Intersection(*circleA, posNextA, *lineB, interPtA, normalAtCollision, interTime, t))
		{
			CircleEdge_Response(interPtA, normalAtCollision, posNextA, reflectedVecA);

			gameBodyA->_velocity = reflectedVecA * gameBodyA->_velocity.Length();
		}

		break;
	}
	case CIRCLE_BOX:
	{
		CircleCollider2D* circleA = dynamic_cast<CircleCollider2D*>(rhs);
		BoxCollider2D* boxB = dynamic_cast<BoxCollider2D*>(lhs);

		if (TestCircleVsBox(*circleA, *boxB))
		{
			EventHandler::GetInstance().AddCollisionEvent(*rhs, *lhs);
			EventHandler::GetInstance().AddCollisionEvent(*lhs, *rhs);
		}

		break;
	}
	case BOX_LINE:
	{
		BoxCollider2D* boxA = dynamic_cast<BoxCollider2D*>(rhs);
		EdgeCollider2D* lineB = dynamic_cast<EdgeCollider2D*>(lhs);

		break;
	}
	default:
		break;
	}

}


int BoxBox_Intersection(const BoxCollider2D& circleA,			
	const Vector3& velA,									
	const BoxCollider2D& circleB,							
	const Vector3& velB,									
	Vector3& interPtA,											
	Vector3& interPtB,											
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



int BoxEdge_Intersection(const BoxCollider2D& circle,		
	const Vector3& ptEnd,													
	const EdgeCollider2D& lineSeg,										
	Vector3& interPt,												
	Vector3& normalAtCollision,										
	float& interTime,										
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

int BoxLine_Intersection(bool withinBothLines,					
	const BoxCollider2D& circle,												
	const Vector3& ptEnd,													
	const EdgeCollider2D& lineSeg,											
	Vector3& interPt,														
	Vector3& normalAtCollision,											
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

int RayBox_Intersection(const Ray& ray,	
	const BoxCollider2D& circle,
	float& interTime)														//Intersection time - output
{
	(void)ray;
	(void)circle;
	(void)interTime;

	return 0;
}

void BoxEdge_Response(const Vector3& ptInter,				
	const Vector3& normal,												
	Vector3& ptEnd,															
	Vector3& reflected)														//Normalized reflection vector direction - output
{
	(void)ptInter;
	(void)normal;
	(void)ptEnd;
	(void)reflected;
}

void BoxStaticBox_Response(const Vector3& normal,
	const float& interTime,	
	const Vector3& ptStart,
	const Vector3& ptInter,	
	Vector3& ptEnd,		
	Vector3& reflectedVectorNormalized)										//Normalized reflection vector - output
{
	(void)normal;
	(void)interTime;
	(void)ptStart;
	(void)ptInter;
	(void)ptEnd;
	(void)reflectedVectorNormalized;
}

void BoxBox_Response(Vector3& normal,	
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


int CircleEdge_Intersection(const CircleCollider2D& circle,			
	const Vector3& ptEnd,													
	const EdgeCollider2D& lineSeg,											
	Vector3& interPt,														
	Vector3& normalAtCollision,												
	float& interTime,														
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
				return 1;
			}
			return 0;
		}
		else
		{
			
			if (checkLineEdges)
				return CircleLine_Intersection(false, circle, ptEnd, lineSeg, interPt, normalAtCollision, interTime);
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
				interPt = circle.mCenPos + velocity * interTime;
				normalAtCollision = lineSeg.m_normal;
				return 1;
			}
			return 0;
		}
		else
		{
			
			if (checkLineEdges)
				return CircleLine_Intersection(false, circle, ptEnd, lineSeg, interPt, normalAtCollision, interTime);
			else
				return 0;
		}
	}
	else
	{
		if (checkLineEdges)
			return CircleLine_Intersection(true, circle, ptEnd, lineSeg, interPt, normalAtCollision, interTime);
		else
			return 0;
	}

	return 0;
}


int CircleLine_Intersection(bool withinBothLines,						
	const CircleCollider2D& circle,													
	const Vector3& ptEnd,													
	const EdgeCollider2D& lineSeg,											
	Vector3& interPt,														
	Vector3& normalAtCollision,												
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


int CircleCircle_Intersection(const CircleCollider2D& circleA,				
	const Vector3& velA,													
	const CircleCollider2D& circleB,											
	const Vector3& velB,													
	Vector3& interPtA,													
	Vector3& interPtB,														
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


int RayCircle_Intersection(const Ray& ray,							
	const CircleCollider2D& circle,								
	float& interTime)
{
	// your code goes here
	(void)(ray);
	(void)(circle);
	(void)(interTime);

	return 0;
}


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

void CircleStaticCircle_Response(const Vector3& normal,
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

	float p = normal * ((velA - velB) * 2 / (massA + massB));

	reflectedVectorA = velA - normal * p * massB;
	reflectedVectorB = velB + normal * p * massA;

	float velLengthA;
	velLengthA = reflectedVectorA.Length();
	float velLengthB;
	velLengthB = reflectedVectorB.Length();

	Vector3 relVelNormalA = reflectedVectorA;
	relVelNormalA.Normalize();
	Vector3 relVelNormalB = reflectedVectorB;
	relVelNormalB.Normalize();

	//Calculate point after reflection
	ptEndA = interPtA + relVelNormalA * (velLengthA * (1.f - interTime));
	ptEndB = interPtB + relVelNormalB * (velLengthB * (1.f - interTime));


	//Calculation normalized reflection vector
	reflectedVectorA = ptEndA - interPtA;
	reflectedVectorA.Normalize();
	reflectedVectorB = ptEndB - interPtB;
	reflectedVectorB.Normalize();
}
