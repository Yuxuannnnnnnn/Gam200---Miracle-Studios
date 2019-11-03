///////////////////////////////////////////////////////////////////////////////////////
//
//	Collision.cpp
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#include "PrecompiledHeaders.h"
#include "Collision.h"

#include "../Tools/EventHandler/EventHandler.h"

void Collision_Check_Response(COLLISION_TYPE type, Collider2D* rhs, Collider2D* lhs, double dt)
{
	(void)type;
	(void)rhs;
	(void)lhs;
	(void)dt;

	TransformComponent* gameTransformA = nullptr;
	TransformComponent* gameTransformB = nullptr;
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

	float massA = 1;
	float massB = 1;

	float interTime = 0.f;


	switch (type)
	{
	case COLLISION_TYPE::BOX_BOX:
	{
		BoxCollider2D* boxA = dynamic_cast<BoxCollider2D*>(rhs);
		BoxCollider2D* boxB = dynamic_cast<BoxCollider2D*>(lhs);

		gameTransformA = boxA->GetTransform();

		if (boxA->_attachedRigidboy)
		{
			gameBodyA = boxA->GetRigidbody();
			velA = gameBodyA->_velocity * (float)dt;
			posNextA = gameTransformA->GetPos() + velA;

			massA = gameBodyA->_mass;
		}
		else
			posNextA = gameTransformA->GetPos();

		gameTransformB = boxB->GetTransform();

		if (boxB->_attachedRigidboy)
		{
			gameBodyB = boxB->GetRigidbody();
			velB = gameBodyB->_velocity * (float)dt;
			posNextB = gameTransformB->GetPos() + velB;

			massB = gameBodyB->_mass;
		}
		else
			posNextB = gameTransformA->GetPos();

		if (BoxBox_Intersection(*boxA, velA, *boxB, velB, interPtA, interPtB, interTime))
		{
			if (!boxA->_trigger && !boxB->_trigger)
			{
				normal = interPtA - interPtB;
				normal.Normalize();

				reflectedVecA = velA;
				reflectedVecB = velB;

				BoxBox_Response(normal, interTime, velA, massA, interPtA, velB, massB, interPtB,
					reflectedVecA, posNextA, reflectedVecB, posNextB);

				if (gameBodyA)
					gameBodyA->_velocity = reflectedVecA * gameBodyA->_velocity.Length();

				if (gameBodyB)
					gameBodyB->_velocity = reflectedVecB * gameBodyB->_velocity.Length();

				//std::cout << "boxA collided boxB" << std::endl;
				EventHandler::GetInstance().AddCollided2DEvent(*boxA, *boxB);
				//std::cout << "boxB collided boxA" << std::endl;
				EventHandler::GetInstance().AddCollided2DEvent(*boxB, *boxA);
			}
			else
			{
				if (boxA->_trigger)
				{
					//std::cout << "boxB trigger boxA" << std::endl;
					EventHandler::GetInstance().AddTriggered2DEvent(*boxA, *boxB);
				}
				if (boxB->_trigger)
				{
					//std::cout << "boxA trigger boxB" << std::endl;
					EventHandler::GetInstance().AddTriggered2DEvent(*boxB, *boxA);
				}
			}
		}

		break;
	}
	case COLLISION_TYPE::BOX_LINE:
	{
		BoxCollider2D* boxA = dynamic_cast<BoxCollider2D*>(rhs);
		EdgeCollider2D* lineB = dynamic_cast<EdgeCollider2D*>(lhs);

		bool t = false;

		gameTransformA = boxA->GetTransform();

		if (boxA->_attachedRigidboy)
		{
			gameBodyA = boxA->GetRigidbody();
			velA = gameBodyA->_velocity * (float)dt;
			posNextA = gameTransformA->GetPos() + velA;
		}
		else
			posNextA = gameTransformA->GetPos();

		if (BoxEdge_Intersection(*boxA, posNextA, *lineB, interPtA, normalAtCollision, interTime, t))
		{
			if (!boxA->_trigger && !lineB->_trigger)
			{
				BoxEdge_Response(interPtA, normalAtCollision, posNextA, reflectedVecA);

				if (gameBodyA)
					gameBodyA->_velocity = reflectedVecA * gameBodyA->_velocity.Length();

				//std::cout << "boxA collided lineB" << std::endl;
				EventHandler::GetInstance().AddCollided2DEvent(*boxA, *lineB);
				//std::cout << "lineB collided boxA" << std::endl;
				EventHandler::GetInstance().AddCollided2DEvent(*lineB, *boxA);
			}
			else
			{
				if (boxA->_trigger)
				{
					//std::cout << "lineB trigger boxA" << std::endl;
					EventHandler::GetInstance().AddTriggered2DEvent(*boxA, *lineB);
				}
				if (lineB->_trigger)
				{
					//std::cout << "boxA trigger lineB" << std::endl;
					EventHandler::GetInstance().AddTriggered2DEvent(*lineB, *boxA);
				}
			}
		}

		break;
	}
	case COLLISION_TYPE::CIRCLE_CIRCLE:
	{
		CircleCollider2D* circleA = dynamic_cast<CircleCollider2D*>(rhs);
		CircleCollider2D* circleB = dynamic_cast<CircleCollider2D*>(lhs);

		gameTransformA = circleA->GetTransform();

		if (circleA->_attachedRigidboy)
		{
			gameBodyA = circleA->GetRigidbody();
			velA = gameBodyA->_velocity * (float)dt;
			posNextA = gameTransformA->GetPos() + velA;

			massA = gameBodyA->_mass;
		}
		else
			posNextA = gameTransformA->GetPos();

		gameTransformB = circleB->GetTransform();

		if (circleB->_attachedRigidboy)
		{
			gameBodyB = circleB->GetRigidbody();
			velB = gameBodyB->_velocity * (float)dt;
			posNextB = gameTransformB->GetPos() + velB;

			massB = gameBodyB->_mass;
		}
		else
			posNextB = gameTransformB->GetPos();


		if (circleA->TestCircleVsCircle(*circleB))
		{
			if (!circleA->_trigger && !circleB->_trigger)
			{
				Vector3 relVel = gameTransformA->GetPos() - gameTransformB->GetPos();

				if (relVel == Vector3::Vec3Zero)
					relVel = Vector3::Vec3EY;

				float TotalRadius = circleA->mRadius + circleB->mRadius;
				//relVelA.Normalize();

				Vector3 temp = relVel.Normalized();
				Vector3 reflectedVectorA = temp * TotalRadius - relVel;
				//Vector3 reflectedVectorB = -reflectedVectorA;

				if (gameBodyA)
				{
					gameBodyA->StopVelocity();
				}
				if (gameBodyB)
				{
					gameBodyB->StopVelocity();
				}

					
				gameTransformA->GetPos() += reflectedVectorA;
				gameTransformB->GetPos() -= reflectedVectorA;


				//std::cout << "circleA collided circleB" << std::endl;
				EventHandler::GetInstance().AddCollided2DEvent(*circleA, *circleB);
				//std::cout << "circleB collided circleA" << std::endl;
				EventHandler::GetInstance().AddCollided2DEvent(*circleB, *circleA);
			}
			else
			{
				if (circleA->_trigger)
				{
					//std::cout << "circleB trigger circleA" << std::endl;
					EventHandler::GetInstance().AddTriggered2DEvent(*circleA, *circleB);
				}
				if (circleB->_trigger)
				{
					//std::cout << "circleA trigger circleB" << std::endl;
					EventHandler::GetInstance().AddTriggered2DEvent(*circleB, *circleA);
				}
			}

		} else		
		if (CircleCircle_Intersection(*circleA, velA, *circleB, velB, interPtA, interPtB, interTime))
		{
			if (!circleA->_trigger && !circleB->_trigger)
			{
				normal = interPtA - interPtB;
				normal.Normalize();

				reflectedVecA = velA;
				reflectedVecB = velB;

				CircleCircle_Response(normal, interTime, velA, massA, interPtA, velB, massB, interPtB,
					reflectedVecA, posNextA, reflectedVecB, posNextB);

				if (gameBodyA)
					gameBodyA->_velocity = reflectedVecA * gameBodyA->_velocity.Length();

				if (gameBodyB)
					gameBodyB->_velocity = reflectedVecB * gameBodyB->_velocity.Length();

				//std::cout << "circleA collided circleB" << std::endl;
				EventHandler::GetInstance().AddCollided2DEvent(*circleA, *circleB);
				//std::cout << "circleB collided circleA" << std::endl;
				EventHandler::GetInstance().AddCollided2DEvent(*circleB, *circleA);
			}
			else
			{
				if (circleA->_trigger)
				{
					//std::cout << "circleB trigger circleA" << std::endl;
					EventHandler::GetInstance().AddTriggered2DEvent(*circleA, *circleB);
				}
				if (circleB->_trigger)
				{
					//std::cout << "circleA trigger circleB" << std::endl;
					EventHandler::GetInstance().AddTriggered2DEvent(*circleB, *circleA);
				}
			}
		}

		break;
	}
	case COLLISION_TYPE::CIRCLE_LINE:
	{
		CircleCollider2D* circleA = dynamic_cast<CircleCollider2D*>(rhs);
		EdgeCollider2D* lineB = dynamic_cast<EdgeCollider2D*>(lhs);

		bool t = false;

		gameTransformA = circleA->GetTransform();

		if (circleA->_attachedRigidboy)
		{
			gameBodyA = circleA->GetRigidbody();
			velA = gameBodyA->_velocity * (float)dt;
			posNextA = gameTransformA->GetPos() + velA;
		}
		else
			posNextA = gameTransformA->GetPos();

		if (CircleEdge_Intersection(*circleA, posNextA, *lineB, interPtA, normalAtCollision, interTime, t))
		{
			if (!circleA->_trigger && !lineB->_trigger)
			{
				CircleEdge_Response(interPtA, normalAtCollision, posNextA, reflectedVecA);

				if (gameBodyA)
					gameBodyA->_velocity = reflectedVecA * gameBodyA->_velocity.Length();

				//std::cout << "circleA collided lineB" << std::endl;
				EventHandler::GetInstance().AddCollided2DEvent(*circleA, *lineB);
				//std::cout << "lineB collided circleA" << std::endl;
				EventHandler::GetInstance().AddCollided2DEvent(*lineB, *circleA);
			}
			else
			{
				if (circleA->_trigger)
				{
					//std::cout << "lineB trigger circleA" << std::endl;
					EventHandler::GetInstance().AddTriggered2DEvent(*circleA, *lineB);
				}
				if (lineB->_trigger)
				{
					//std::cout << "circleA trigger lineB" << std::endl;
					EventHandler::GetInstance().AddTriggered2DEvent(*lineB, *circleA);
				}
			}
		}

		break;
	}
	case COLLISION_TYPE::CIRCLE_BOX:
	{
		CircleCollider2D* circleA = dynamic_cast<CircleCollider2D*>(rhs);
		BoxCollider2D* boxB = dynamic_cast<BoxCollider2D*>(lhs);

		gameTransformA = circleA->GetTransform();

		if (circleA->_attachedRigidboy)
		{
			gameBodyA = circleA->GetRigidbody();
			velA = gameBodyA->_velocity * (float)dt;
			posNextA = gameTransformA->GetPos() + velA;
		}
		else
			posNextA = gameTransformA->GetPos();

		gameTransformB = boxB->GetTransform();

		if (boxB->_attachedRigidboy)
		{
			gameBodyB = boxB->GetRigidbody();
			velB = gameBodyB->_velocity * (float)dt;
			posNextB = gameTransformB->GetPos() + velB;
		}
		else
			posNextB = gameTransformB->GetPos();

		if (CircleBox_Intersection(*circleA, velA, *boxB, velB, interPtA, interPtB, interTime))
		{
			if (!circleA->_trigger && !boxB->_trigger)
			{
				normal = interPtA - interPtB;
				normal.Normalize();

				reflectedVecA = velA;
				reflectedVecB = velB;

				CircleBox_Response(normal, interTime, velA, 1, interPtA, velB, 1, interPtB,
					reflectedVecA, posNextA, reflectedVecB, posNextB);

				if (gameBodyA)
					gameBodyA->_velocity = reflectedVecA * gameBodyA->_velocity.Length();

				if (gameBodyB)
					gameBodyB->_velocity = reflectedVecB * gameBodyB->_velocity.Length();

				//std::cout << "circleA collided boxB" << std::endl;
				EventHandler::GetInstance().AddCollided2DEvent(*circleA, *boxB);
				//std::cout << "boxB collided circleA" << std::endl;
				EventHandler::GetInstance().AddCollided2DEvent(*boxB, *circleA);
			}
			else
			{
				if (circleA->_trigger)
				{
					//std::cout << "boxB trigger circleA" << std::endl;
					EventHandler::GetInstance().AddTriggered2DEvent(*circleA, *boxB);
				}
				if (boxB->_trigger)
				{
					//std::cout << "circleA trigger boxB" << std::endl;
					EventHandler::GetInstance().AddTriggered2DEvent(*boxB, *circleA);
				}
			}
		}

		break;
	}
	
	default:
		break;
	}

}


int BoxBox_Intersection(const BoxCollider2D& boxA,			
	const Vector3& velA,									
	const BoxCollider2D& boxB,							
	const Vector3& velB,									
	Vector3& interPtA,											
	Vector3& interPtB,											
	float& interTime)														//intersection time - output
{
	(void)interPtA;
	(void)interPtB;
	(void)interTime;

	//Vector3 relVel = velA - velB;
	//Vector3 relVelNormal = relVel.Normalized();

	//Vector3 startToEnd = boxB.mOrigin - boxA.mOrigin;

	//float m = startToEnd * relVelNormal;
	//float n = startToEnd.SquaredLength() - (m * m);
	//float r = c.mRadius * c.mRadius;

	return 0;
	
}



int BoxEdge_Intersection(const BoxCollider2D& box,
	const Vector3& ptEnd,													
	const EdgeCollider2D& lineSeg,										
	Vector3& interPt,												
	Vector3& normalAtCollision,										
	float& interTime,										
	bool& checkLineEdges)
{
	//Velocity vector and normal
	Vector3 velocity = ptEnd - box.mOrigin;
	Vector3 velNor = velocity.Normalized();

	float boxVecLength = 0;

	for (int i = 0; i < 4; i++)
	{
		float length = box.mCorner[0].AbsDot(velNor);

		if (boxVecLength > length)
			boxVecLength = length;
	}

	//N.(P0 - Bs)
	float dist = lineSeg.m_normal.Dot(lineSeg.m_pt0 - box.mOrigin);

	if (dist > boxVecLength)
	{
		EdgeCollider2D LNS1{nullptr};
		Vector3 temp;

		//R*unit N
		temp = lineSeg.m_normal * boxVecLength;

		//p0' and p1'
		LNS1.m_pt0 = lineSeg.m_pt0 - temp;
		LNS1.m_pt1 = lineSeg.m_pt1 - temp;
		LNS1.m_normal = lineSeg.m_normal;

		//BsP0'
		temp = LNS1.m_pt0 - box.mOrigin;

		float tempf = temp.Dot(velNor);

		//BsP1'
		temp = LNS1.m_pt1 - box.mOrigin;
		tempf *= temp.Dot(velNor);

		if (tempf < 0)
		{

			//Ti = ( N.P0 - N.Bs - R / N.V )
			interTime = (lineSeg.m_normal * lineSeg.m_pt0
				- lineSeg.m_normal * box.mOrigin - boxVecLength) /
				(lineSeg.m_normal * velocity);

			if (0 <= interTime && interTime <= 1)
			{
				interPt = box.mOrigin + velocity * interTime;
				normalAtCollision = -lineSeg.m_normal;
				return 1;
			}
			return 0;
		}
		else
		{

			if (checkLineEdges)
				return BoxLine_Intersection(false, box, ptEnd, lineSeg, interPt, normalAtCollision, interTime);
			else
				return 0;
		}
	}
	else if (dist < -boxVecLength)
	{

		EdgeCollider2D LNS2{nullptr};
		Vector3 temp;
		//R* unit N
		temp = lineSeg.m_normal * boxVecLength;
		//P0' and P1'
		LNS2.m_pt0 = lineSeg.m_pt0 + temp;
		LNS2.m_pt1 = lineSeg.m_pt1 + temp;
		LNS2.m_normal = lineSeg.m_normal;

		//BsP0'
		temp = LNS2.m_pt0 - box.mOrigin;
		float tempf = temp * velNor;
		//BsP1'
		temp = LNS2.m_pt1 - box.mOrigin;
		tempf *= temp * velNor;
		if (tempf < 0)
		{

			//Ti = ( N.P0 - N.Bs + R / N.V )
			interTime = (lineSeg.m_normal * lineSeg.m_pt0
				- lineSeg.m_normal * box.mOrigin + boxVecLength) /
				(lineSeg.m_normal * velocity);

			if (0 <= interTime && interTime <= 1)
			{
				interPt = box.mOrigin + velocity * interTime;
				normalAtCollision = lineSeg.m_normal;
				return 1;
			}
			return 0;
		}
		else
		{

			if (checkLineEdges)
				return BoxLine_Intersection(false, box, ptEnd, lineSeg, interPt, normalAtCollision, interTime);
			else
				return 0;
		}
	}
	else
	{
		if (checkLineEdges)
			return BoxLine_Intersection(true, box, ptEnd, lineSeg, interPt, normalAtCollision, interTime);
		else
			return 0;
	}

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

void BoxEdge_Response(const Vector3& ptInter,				
	const Vector3& normal,												
	Vector3& ptEnd,															
	Vector3& reflected)													
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
	Vector3& reflectedVectorNormalized)									
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
		EdgeCollider2D LNS1{nullptr};
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

		EdgeCollider2D LNS2{nullptr};
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
	CircleCollider2D c{nullptr};
	c.mRadius = circleA.mRadius + circleB.mRadius;
	c.mCenPos = circleB.mCenPos;

	Vector3 relVel = velA - velB;
	Vector3 relVelNormal = relVel;
	relVelNormal.Normalize();

	if (relVel == Vector3::Vec3Zero)
	{
		if (circleA.TestCircleVsCircle(circleB))
			return 1;

		return 0;
	}

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


int CircleBox_Intersection(const CircleCollider2D& boxA,
	const Vector3& velA,
	const BoxCollider2D& circleB,
	const Vector3& velB,
	Vector3& interPtA,
	Vector3& interPtB,
	float& interTime)
{
	return 0;
}


void CircleBox_Response(Vector3& normal,
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
