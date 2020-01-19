#include "PrecompiledHeaders.h"
#include "Collision.h"
#include "../Tools/EventHandler/EventHandler.h"

// For new collider box check
namespace Collision {

	bool DefaultColliderDataCheck(const BBox& boxA, const BBox& boxB)
	{
		//first check circle collision
		if (!BCircleVsBCircle(boxA._BC, boxB._BC))
			return false;

		//then continue the Box collision check (SAT)
		if (!BBoxVsBBox(boxA, boxB))
			return false;

		return true;
	}

	bool BCircleVsBCircle(const BCircle& circleA, const BCircle& circleB)
	{
		return (circleA._center.Distance(circleB._center) <= (circleA._radius + circleB._radius));
	}

	bool BBoxVsBBox(const BBox& boxA, const BBox& boxB)
	{
		return BBoxOverlaps(boxA, boxB) && BBoxOverlaps(boxB, boxA);
	}

	bool BBoxOverlaps(const BBox& boxA, const BBox& boxB)
	{
		for (int a = 0; a < 2; ++a)
		{
			float det = boxA._normals[a].Dot(boxA._normals[a]);
			float t = boxB._origin.Dot(boxA._normals[a]) / det;

			// Find the extent of boxB on boxA's axis x
			float tMin = t;
			float tMax = t;

			for (int c = 1; c < 4; ++c) {
				t = boxB._corners[c].Dot(boxA._normals[a]) / det;

				if (t < tMin) {
					tMin = t;
				}
				else if (t > tMax) {
					tMax = t;
				}
			}

			// See if [tMin, tMax] intersects [-1, 1]
			if (tMin > 1.f || tMax < -1.f) {
				// There was no intersection along this dimension;
				// the boxes cannot possibly overlap.
				return false;
			}
		}

		// There was no dimension along which there has no intersection.
		// Therefore the boxes overlap.
		return true;
	}

	bool BBoxVsPoint(const BBox& box, const Vector3& point)
	{
		Vector3 vec = point - box._origin;

		for (int a = 0; a < 2; ++a)
		{
			float det = box._normals[a].Dot(box._normals[a]);
			float t = vec.Dot(box._normals[a]) / det;


			// See if [tMin, tMax] intersects [-1, 1]
			if (t > 1.f || t < -1.f) {
				// There was no intersection along this dimension;
				// the boxes cannot possibly overlap.
				return false;
			}
		}

		return true;
	}

	//bool BPolygonVsBPolygon(const BPolygon& polygonA, const BPolygon& polygonB);

};


void BOX_BOX_CollisionCR(Collider2D* colliderA,
	TransformComponent* transformA,
	RigidBody2DComponent* rigidbodyA,
	Collider2D* colliderB,
	TransformComponent* transformB,
	RigidBody2DComponent* rigidbodyB,
	double dt)
{
	BoxCollider2DComponent* boxA = dynamic_cast<BoxCollider2DComponent*>(colliderA);
	BoxCollider2DComponent* boxB = dynamic_cast<BoxCollider2DComponent*>(colliderB);

	Vector3 posNextA = Vector3::Vec3Zero;
	Vector3 posNextB = Vector3::Vec3Zero;
	Vector3 velA = Vector3::Vec3Zero;
	Vector3 velB = Vector3::Vec3Zero;
	Vector3 interPtA = Vector3::Vec3Zero;
	Vector3 interPtB = Vector3::Vec3Zero;
	Vector3 reflectedVecA = Vector3::Vec3Zero;
	Vector3 reflectedVecB = Vector3::Vec3Zero;
	Vector3 normal = Vector3::Vec3Zero;

	float massA = 1;
	float massB = 1;

	float interTime = 0.f;

	if (rigidbodyA)
	{
		velA = rigidbodyA->_velocity * (float)dt;
		posNextA = transformA->GetPos() + velA;
		massA = rigidbodyA->_mass;
	}
	else
	{
		posNextA = transformA->GetPos();
	}

	if (rigidbodyB)
	{
		velB = rigidbodyB->_velocity * (float)dt;
		posNextB = transformB->GetPos() + velB;
		massB = rigidbodyB->_mass;
	}
	else
	{
		posNextB = transformB->GetPos();
	}

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

			if (rigidbodyA)
				rigidbodyA->_velocity = reflectedVecA * rigidbodyA->_velocity.Length();

			if (rigidbodyB)
				rigidbodyB->_velocity = reflectedVecB * rigidbodyB->_velocity.Length();

			EventHandler::GetInstance().AddCollided2DEvent(boxA, boxB);
			EventHandler::GetInstance().AddCollided2DEvent(boxB, boxA);
		}
		else
		{
			if (boxA->_trigger || boxB->_trigger)
			{
				EventHandler::GetInstance().AddTriggered2DEvent(boxA, boxB);
				EventHandler::GetInstance().AddTriggered2DEvent(boxB, boxA);
			}
		}
	}

}

void CIRCLE_CIRCLE_CollisionCR(Collider2D* colliderA,
	TransformComponent* transformA,
	RigidBody2DComponent* rigidbodyA,
	Collider2D* colliderB,
	TransformComponent* transformB,
	RigidBody2DComponent* rigidbodyB,
	double dt)
{
	CircleCollider2DComponent* circleA = dynamic_cast<CircleCollider2DComponent*>(colliderA);
	CircleCollider2DComponent* circleB = dynamic_cast<CircleCollider2DComponent*>(colliderB);

	Vector3 posNextA = Vector3::Vec3Zero;
	Vector3 posNextB = Vector3::Vec3Zero;
	Vector3 velA = Vector3::Vec3Zero;
	Vector3 velB = Vector3::Vec3Zero;
	Vector3 interPtA = Vector3::Vec3Zero;
	Vector3 interPtB = Vector3::Vec3Zero;
	Vector3 reflectedVecA = Vector3::Vec3Zero;
	Vector3 reflectedVecB = Vector3::Vec3Zero;
	Vector3 normal = Vector3::Vec3Zero;

	float massA = 1;
	float massB = 1;

	float interTime = 0.f;

	if (rigidbodyA)
	{
		velA = rigidbodyA->_velocity * (float)dt;
		posNextA = transformA->GetPos() + velA;
		massA = rigidbodyA->_mass;
	}
	else
	{
		posNextA = transformA->GetPos();
	}

	if (rigidbodyB)
	{
		velB = rigidbodyB->_velocity * (float)dt;
		posNextB = transformB->GetPos() + velB;
		massB = rigidbodyB->_mass;
	}
	else
	{
		posNextB = transformB->GetPos();
	}

	if (TestCircleVsCircle(*circleA, *circleB))
	{
		if (!circleA->_trigger && !circleB->_trigger)
		{
			Vector3 relVel = transformA->GetPos() - transformB->GetPos();
			relVel._z = 0;

			if (relVel == Vector3::Vec3Zero)
				relVel = Vector3::Vec3EY;

			float TotalRadius = circleA->mRadius + circleB->mRadius;
			//relVelA.Normalize();

			Vector3 temp = relVel.Normalized();
			Vector3 reflectedVectorA = temp * TotalRadius - relVel;
			//Vector3 reflectedVectorB = -reflectedVectorA;

			if (rigidbodyA)
			{
				rigidbodyA->SetVelocity(Vec3::Vec3Zero);
			}
			if (rigidbodyB)
			{
				rigidbodyB->SetVelocity(Vec3::Vec3Zero);
			}


			transformA->GetPos() += reflectedVectorA;
			transformB->GetPos() -= reflectedVectorA;


			//std::cout << "circleA collided circleB" << std::endl;
			EventHandler::GetInstance().AddCollided2DEvent(circleA, circleB);
			//std::cout << "circleB collided circleA" << std::endl;
			EventHandler::GetInstance().AddCollided2DEvent(circleB, circleA);
		}
		else
		{
			if (circleA->_trigger || circleB->_trigger)
			{
				//std::cout << "circleB trigger circleA" << std::endl;
				EventHandler::GetInstance().AddTriggered2DEvent(circleA, circleB);
				//std::cout << "circleA trigger circleB" << std::endl;
				EventHandler::GetInstance().AddTriggered2DEvent(circleB, circleA);
			}
		}

	}
	else
		if (CircleCircle_Intersection(*circleA, velA, *circleB, velB, interPtA, interPtB, interTime))
		{
			if (!circleA->_trigger && !circleB->_trigger)
			{
				normal = interPtA - interPtB;
				normal._z = 0;
				normal.Normalize();

				reflectedVecA = velA;
				reflectedVecB = velB;

				CircleCircle_Response(normal, interTime, velA, massA, interPtA, velB, massB, interPtB,
					reflectedVecA, posNextA, reflectedVecB, posNextB);

				if (rigidbodyA)
				{
					rigidbodyA->_velocity = reflectedVecA * rigidbodyA->_velocity.Length();
				}

				if (rigidbodyB)
				{
					rigidbodyB->_velocity = reflectedVecB * rigidbodyB->_velocity.Length();
				}

				//std::cout << "circleA collided circleB" << std::endl;
				EventHandler::GetInstance().AddCollided2DEvent(circleA, circleB);
				//std::cout << "circleB collided circleA" << std::endl;
				EventHandler::GetInstance().AddCollided2DEvent(circleB, circleA);
			}
			else
			{
				if (circleA->_trigger || circleB->_trigger)
				{
					//std::cout << "circleB trigger circleA" << std::endl;
					EventHandler::GetInstance().AddTriggered2DEvent(circleA, circleB);
					//std::cout << "circleA trigger circleB" << std::endl;
					EventHandler::GetInstance().AddTriggered2DEvent(circleB, circleA);
				}
			}
		}

}

void CIRCLE_BOX_CollisionCR(Collider2D* colliderA,
	TransformComponent* transformA,
	RigidBody2DComponent* rigidbodyA,
	Collider2D* colliderB,
	TransformComponent* transformB,
	RigidBody2DComponent* rigidbodyB,
	double dt)
{
	CircleCollider2DComponent* circleA = dynamic_cast<CircleCollider2DComponent*>(colliderA);
	BoxCollider2DComponent* boxB = dynamic_cast<BoxCollider2DComponent*>(colliderB);

	Vector3 posNextA = Vector3::Vec3Zero;
	Vector3 posNextB = Vector3::Vec3Zero;
	Vector3 velA = Vector3::Vec3Zero;
	Vector3 velB = Vector3::Vec3Zero;
	Vector3 interPtA = Vector3::Vec3Zero;
	Vector3 interPtB = Vector3::Vec3Zero;
	Vector3 reflectedVecA = Vector3::Vec3Zero;
	Vector3 reflectedVecB = Vector3::Vec3Zero;
	Vector3 normal = Vector3::Vec3Zero;

	float massA = 1;
	float massB = 1;

	float interTime = 0.f;



	if (rigidbodyA)
	{
		velA = rigidbodyA->_velocity * (float)dt;
		posNextA = transformA->GetPos() + velA;
		massA = rigidbodyA->_mass;
	}
	else
	{
		posNextA = transformA->GetPos();
	}

	if (rigidbodyB)
	{
		velB = rigidbodyB->_velocity * (float)dt;
		posNextB = transformB->GetPos() + velB;
		massB = rigidbodyB->_mass;
	}
	else
	{
		posNextB = transformB->GetPos();
	}

	if (TestCircleVsBox(*circleA, *boxB))
	{
		if (!circleA->_trigger && !boxB->_trigger)
		{
			if (rigidbodyA)
			{
				rigidbodyA->SetVelocity(Vec3::Vec3Zero);
			}

			if (rigidbodyB)
			{
				rigidbodyB->SetVelocity(Vec3::Vec3Zero);
			}

			Vector3 relVel = transformA->GetPos() - transformB->GetPos();
			relVel._z = 0;

			if (relVel == Vector3::Vec3Zero)
				relVel = Vector3::Vec3EX;

			Vector3 relNormal = relVel.Normalized();

			float diff = 0;

			if (relVel.AbsDot(boxB->mAxis[0]) > relVel.AbsDot(boxB->mAxis[1]))
			{
				diff = relVel.AbsDot(boxB->mAxis[0]) / (transformB->GetScale()._x * 0.5f + circleA->mRadius);
				if (relVel.Dot(boxB->mAxis[0]) > 0)
				{
					transformA->GetPos() = transformB->GetPos() + boxB->mAxis[0] * (circleA->mRadius + transformB->GetScale()._x * 0.5f) + Vector3(0, diff * relVel._y);
					rigidbodyA->_velocity = boxB->mAxis[0] * circleA->mRadius;
				}
				else
				{
					transformA->GetPos() = transformB->GetPos() + -boxB->mAxis[0] * (circleA->mRadius + transformB->GetScale()._x * 0.5f) + Vector3(0, diff * relVel._y);
					rigidbodyA->_velocity = -boxB->mAxis[0] * circleA->mRadius;
				}
			}
			else
			{
				diff = relVel.AbsDot(boxB->mAxis[1]) / (transformB->GetScale()._y * 0.5f + circleA->mRadius);

				if (relVel.Dot(boxB->mAxis[1]) > 0)
				{
					transformA->GetPos() = transformB->GetPos() + boxB->mAxis[1] * (circleA->mRadius + transformB->GetScale()._y * 0.5f) + Vector3(diff * relVel._x);
					rigidbodyA->_velocity = boxB->mAxis[1] * circleA->mRadius;
				}
				else
				{
					transformA->GetPos() = transformB->GetPos() + -boxB->mAxis[1] * (circleA->mRadius + transformB->GetScale()._y * 0.5f) + Vector3(diff * relVel._x);
					rigidbodyA->_velocity = -boxB->mAxis[1] * circleA->mRadius;
				}
			}
			// = gameTransformB->GetPos() + relVel * diff + relNormal * circleA->mRadius;



			//gameTransformA->GetPos() += relNormal * (1.f - diff) * circleA->mRadius - relVel;


			//Vector3 temp = relVel.Normalized();
			//Vector3 reflectedVectorA = temp * TotalRadius - relVel;
			////Vector3 reflectedVectorB = -reflectedVectorA;


			//std::cout << "circleA collided circleB" << std::endl;
			EventHandler::GetInstance().AddCollided2DEvent(circleA, boxB);
			//std::cout << "circleB collided circleA" << std::endl;
			EventHandler::GetInstance().AddCollided2DEvent(boxB, circleA);
		}
		else
		{
			if (circleA->_trigger || boxB->_trigger)
			{
				//std::cout << "circleB trigger circleA" << std::endl;
				EventHandler::GetInstance().AddTriggered2DEvent(circleA, boxB);
				//std::cout << "circleA trigger circleB" << std::endl;
				EventHandler::GetInstance().AddTriggered2DEvent(boxB, circleA);
			}
		}

	}
	else
		if (CircleBox_Intersection(*circleA, velA, *boxB, velB, interPtA, interPtB, interTime))
		{
			if (!circleA->_trigger && !boxB->_trigger)
			{
				normal = interPtA - interPtB;
				normal.Normalize();

				reflectedVecA = velA;
				reflectedVecB = velB;

				CircleBox_Response(normal, interTime, velA, massA, interPtA, velB, massB, interPtB,
					reflectedVecA, posNextA, reflectedVecB, posNextB);

				if (rigidbodyA)
					rigidbodyA->_velocity = reflectedVecA * rigidbodyA->_velocity.Length();

				if (rigidbodyB)
					rigidbodyB->_velocity = reflectedVecB * rigidbodyB->_velocity.Length();

				//std::cout << "circleA collided boxB" << std::endl;
				EventHandler::GetInstance().AddCollided2DEvent(circleA, boxB);
				//std::cout << "boxB collided circleA" << std::endl;
				EventHandler::GetInstance().AddCollided2DEvent(boxB, circleA);
			}
			else
			{
				if (circleA->_trigger || boxB->_trigger)
				{
					//std::cout << "boxB trigger circleA" << std::endl;
					EventHandler::GetInstance().AddTriggered2DEvent(circleA, boxB);
					//std::cout << "circleA trigger boxB" << std::endl;
					EventHandler::GetInstance().AddTriggered2DEvent(boxB, circleA);
				}
			}
		}

}

void CIRCLE_EDGE_CollisionCR(Collider2D* colliderA,
	TransformComponent* transformA,
	RigidBody2DComponent* rigidbodyA,
	Collider2D* colliderB,
	double dt)
{
	CircleCollider2DComponent* circleA = dynamic_cast<CircleCollider2DComponent*>(colliderA);
	EdgeCollider2DComponent* lineB = dynamic_cast<EdgeCollider2DComponent*>(colliderB);

	Vector3 posNextA = Vector3::Vec3Zero;
	Vector3 velA = Vector3::Vec3Zero;
	Vector3 interPtA = Vector3::Vec3Zero;
	Vector3 reflectedVecA = Vector3::Vec3Zero;
	Vector3 normal = Vector3::Vec3Zero;
	Vector3 normalAtCollision = Vector3::Vec3Zero;

	float massA = 1;

	float interTime = 0.f;

	bool t = false;


	if (rigidbodyA)
	{
		velA = rigidbodyA->_velocity * (float)dt;
		posNextA = transformA->GetPos() + velA;
		massA = rigidbodyA->_mass;
	}
	else
	{
		posNextA = transformA->GetPos();
	}


	if (TestCircleVsEdge(*circleA, *lineB))
	{
		if (!circleA->_trigger && !lineB->_trigger)
		{
			float penc = circleA->mRadius - Vec3Distance_LinetoPoint(lineB->m_pt0, lineB->m_pt1, circleA->mCenPos);

			if (penc == 0)
				return;

			Vector3 dir = circleA->mCenPos - lineB->m_origin;

			if (lineB->m_normal.Dot(dir) > 0)
				transformA->GetPos() += penc * lineB->m_normal;
			else
				transformA->GetPos() -= penc * lineB->m_normal;

			if (rigidbodyA)
				rigidbodyA->SetVelocity(Vec3::Vec3Zero);

			//std::cout << "circleA collided lineB" << std::endl;
			EventHandler::GetInstance().AddCollided2DEvent(circleA, lineB);
			//std::cout << "lineB collided circleA" << std::endl;
			EventHandler::GetInstance().AddCollided2DEvent(lineB, circleA);
		}
		else
		{
			if (circleA->_trigger || lineB->_trigger)
			{
				//std::cout << "lineB trigger circleA" << std::endl;
				EventHandler::GetInstance().AddTriggered2DEvent(circleA, lineB);
				//std::cout << "circleA trigger lineB" << std::endl;
				EventHandler::GetInstance().AddTriggered2DEvent(lineB, circleA);
			}
		}

	}
	else if (CircleEdge_Intersection(*circleA, posNextA, *lineB, interPtA, normalAtCollision, interTime, t))
	{
		if (!circleA->_trigger && !lineB->_trigger)
		{

			CircleEdge_Response(interPtA, normalAtCollision, posNextA, reflectedVecA);

			if (rigidbodyA)
				rigidbodyA->_velocity = reflectedVecA * rigidbodyA->_velocity.Length();

			//std::cout << "circleA collided lineB" << std::endl;
			EventHandler::GetInstance().AddCollided2DEvent(circleA, lineB);
			//std::cout << "lineB collided circleA" << std::endl;
			EventHandler::GetInstance().AddCollided2DEvent(lineB, circleA);
		}
		else
		{
			if (circleA->_trigger || lineB->_trigger)
			{
				//std::cout << "lineB trigger circleA" << std::endl;
				EventHandler::GetInstance().AddTriggered2DEvent(circleA, lineB);
				//std::cout << "circleA trigger lineB" << std::endl;
				EventHandler::GetInstance().AddTriggered2DEvent(lineB, circleA);
			}
		}
	}



}

void BOX_EDGE_CollisionCR(Collider2D* colliderA,
	TransformComponent* transformA,
	RigidBody2DComponent* rigidbodyA,
	Collider2D* colliderB,
	double dt)
{
	BoxCollider2DComponent* boxA = dynamic_cast<BoxCollider2DComponent*>(colliderA);
	EdgeCollider2DComponent* edgeB = dynamic_cast<EdgeCollider2DComponent*>(colliderB);

	Vector3 posNextA = Vector3::Vec3Zero;
	Vector3 velA = Vector3::Vec3Zero;
	Vector3 interPtA = Vector3::Vec3Zero;
	Vector3 reflectedVecA = Vector3::Vec3Zero;
	Vector3 normalAtCollision = Vector3::Vec3Zero;

	float massA = 1;

	float interTime = 0.f;

	bool t = false;

	if (rigidbodyA)
	{
		velA = rigidbodyA->_velocity * (float)dt;
		posNextA = transformA->GetPos() + velA;
		massA = rigidbodyA->_mass;
	}
	else
	{
		posNextA = transformA->GetPos();
	}

	if (BoxEdge_Intersection(*boxA, posNextA, *edgeB, interPtA, normalAtCollision, interTime, t))
	{
		if (!boxA->_trigger && !edgeB->_trigger)
		{
			BoxEdge_Response(interPtA, normalAtCollision, posNextA, reflectedVecA);

			if (rigidbodyA)
				rigidbodyA->_velocity = reflectedVecA * rigidbodyA->_velocity.Length();

			EventHandler::GetInstance().AddCollided2DEvent(boxA, edgeB);
			EventHandler::GetInstance().AddCollided2DEvent(edgeB, boxA);
		}
		else
		{
			if (boxA->_trigger || edgeB->_trigger)
			{
				EventHandler::GetInstance().AddTriggered2DEvent(boxA, edgeB);
				EventHandler::GetInstance().AddTriggered2DEvent(edgeB, boxA);
			}
		}
	}

}

///////////////////////////////////////////////////////////////////////////////
	//Dynamic Collision Check

int BoxBox_Intersection(const BoxCollider2DComponent& boxA,
	const Vector3& velA,
	const BoxCollider2DComponent& boxB,
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



int BoxEdge_Intersection(const BoxCollider2DComponent& box,
	const Vector3& ptEnd,
	const EdgeCollider2DComponent& lineSeg,
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
		EdgeCollider2DComponent LNS1{};
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
			interTime = (lineSeg.m_normal.Dot(lineSeg.m_pt0)
				- lineSeg.m_normal.Dot(box.mOrigin) - boxVecLength) /
				(lineSeg.m_normal.Dot(velocity));

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

		EdgeCollider2DComponent LNS2{};
		Vector3 temp;
		//R* unit N
		temp = lineSeg.m_normal * boxVecLength;
		//P0' and P1'
		LNS2.m_pt0 = lineSeg.m_pt0 + temp;
		LNS2.m_pt1 = lineSeg.m_pt1 + temp;
		LNS2.m_normal = lineSeg.m_normal;

		//BsP0'
		temp = LNS2.m_pt0 - box.mOrigin;
		float tempf = temp.Dot(velNor);
		//BsP1'
		temp = LNS2.m_pt1 - box.mOrigin;
		tempf *= temp.Dot(velNor);
		if (tempf < 0)
		{

			//Ti = ( N.P0 - N.Bs + R / N.V )
			interTime = (lineSeg.m_normal.Dot(lineSeg.m_pt0)
				- lineSeg.m_normal.Dot(box.mOrigin) + boxVecLength) /
				(lineSeg.m_normal.Dot(velocity));

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
	const BoxCollider2DComponent& circle,
	const Vector3& ptEnd,
	const EdgeCollider2DComponent& lineSeg,
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
	float p = normal.Dot(((velA - velB) * 2 / (massA + massB)));

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


int CircleEdge_Intersection(const CircleCollider2DComponent& circle,
	const Vector3& ptEnd,
	const EdgeCollider2DComponent& lineSeg,
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
		EdgeCollider2DComponent LNS1{};
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
			interTime = (lineSeg.m_normal.Dot(lineSeg.m_pt0)
				- lineSeg.m_normal.Dot(circle.mCenPos) - circle.mRadius) /
				(lineSeg.m_normal.Dot(velocity));

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

		EdgeCollider2DComponent LNS2{};
		Vector3 temp;
		//R* unit N
		temp = lineSeg.m_normal * circle.mRadius;
		//P0' and P1'
		LNS2.m_pt0 = lineSeg.m_pt0 + temp;
		LNS2.m_pt1 = lineSeg.m_pt1 + temp;
		LNS2.m_normal = lineSeg.m_normal;

		//BsP0'
		temp = LNS2.m_pt0 - circle.mCenPos;
		float tempf = temp.Dot(velNormal);
		//BsP1'
		temp = LNS2.m_pt1 - circle.mCenPos;
		tempf *= temp.Dot(velNormal);
		if (tempf < 0)
		{

			//Ti = ( N.P0 - N.Bs + R / N.V )
			interTime = (lineSeg.m_normal.Dot(lineSeg.m_pt0)
				- lineSeg.m_normal.Dot(circle.mCenPos) + circle.mRadius) /
				(lineSeg.m_normal.Dot(velocity));

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
	const CircleCollider2DComponent& circle,
	const Vector3& ptEnd,
	const EdgeCollider2DComponent& lineSeg,
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

	float m0 = relVelNormal.Dot(startToLineEdge0);

	Vector3 startToLineEdge1;
	startToLineEdge1 = lineSeg.m_pt1 - circle.mCenPos;

	float m1 = relVelNormal.Dot(startToLineEdge1);

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


int CircleCircle_Intersection(const CircleCollider2DComponent& circleA,
	const Vector3& velA,
	const CircleCollider2DComponent& circleB,
	const Vector3& velB,
	Vector3& interPtA,
	Vector3& interPtB,
	float& interTime)
{
	CircleCollider2DComponent c{};
	c.mRadius = circleA.mRadius + circleB.mRadius;
	c.mCenPos = circleB.mCenPos;

	Vector3 relVel = velA - velB;
	Vector3 relVelNormal = relVel;
	relVelNormal.Normalize();

	if (relVel == Vector3::Vec3Zero)
	{
		if (TestCircleVsCircle(circleA, circleB))
			return 1;

		return 0;
	}

	Vector3 startToCircle;
	startToCircle = c.mCenPos - circleA.mCenPos;

	float m = startToCircle.Dot(relVelNormal);
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
	float projectedDist = 2 * (penetrateVec.Dot(normal));
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
	float projectedDist = 2 * (penetrateVec.Dot(normal));
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
	float p = normal.Dot(((velA - velB) * 2 / (massA + massB)));

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


int CircleBox_Intersection(const CircleCollider2DComponent& circleA,
	const Vector3& velA,
	const BoxCollider2DComponent& boxB,
	const Vector3& velB,
	Vector3& interPtA,
	Vector3& interPtB,
	float& interTime)
{
	BoxCollider2DComponent newBox{ boxB };


	Vector3 relVel = velB - velA;

	if (relVel == Vector3::Vec3Zero)
		return false;

	Vector3 nextPos = circleA.mCenPos;

	newBox.mScale = Vector3(boxB.mScale._x * 0.5f + circleA.mRadius, boxB.mScale._y * 0.5f + circleA.mRadius);

	MyPhysicsSystem.UpdateColliderData(&newBox);

	int outcode = TestOutCode(newBox, nextPos);

	if (outcode == (int)OutCode_Type::CENTER)
	{
		Vector3 relVel2 = nextPos - boxB.mOrigin;

		float xPenc = 1.f - relVel2.AbsDot(boxB.mAxis[0]) / (boxB.mScale._x * 0.5f);
		float yPenc = 1.f - relVel2.AbsDot(boxB.mAxis[1]) / (boxB.mScale._y * 0.5f);

		Vector3 relVel3{ xPenc * (boxB.mScale._x * 0.5f) , yPenc * (boxB.mScale._y * 0.5f) };

		float ti = relVel3.SquaredLength() / relVel.SquaredLength();

		if (0 <= ti && ti <= 1)
		{
			interPtA = circleA.mCenPos + (velA * ti);
			interPtB = boxB.mOrigin + (velB * ti);
			interTime = ti;
			return 1;
		}
		return false;
	}
	return false;
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
	float p = normal.Dot(((velA - velB) * 2 / (massA + massB)));

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

///////////////////////////////////////////////////////////////////////////////
	//Static Collision Check

bool TestAABBVsPoint(const BoxCollider2DComponent& aabb, const Vector3& pt)
{
	return (pt._x >= aabb.mMinPos._x && pt._x <= aabb.mMaxPos._x &&
		pt._y >= aabb.mMinPos._y && pt._y <= aabb.mMaxPos._y);
}

bool TestAABBVsAABB(const BoxCollider2DComponent& aabb1, const BoxCollider2DComponent& aabb2)
{
	if (aabb1.mMaxPos._x < aabb2.mMinPos._x || aabb1.mMaxPos._y < aabb2.mMinPos._y ||
		aabb1.mMinPos._x > aabb2.mMaxPos._x || aabb1.mMinPos._y > aabb2.mMaxPos._y)
		return false;

	return true;
}

bool TestOBBVsPoint(const BoxCollider2DComponent& obb, const Vector3& pt)
{
	int oc = TestOutCode(obb, pt);

	if (oc == (int)OutCode_Type::CENTER)
		return true;

	return false;
}

bool TestOBBVsOBB(const BoxCollider2DComponent& obb1, const BoxCollider2DComponent& obb2)
{
	return TestOverlaps(obb1, obb2) && TestOverlaps(obb2, obb1);
}

bool TestOverlaps(const BoxCollider2DComponent& obb1, const BoxCollider2DComponent& obb2)
{
	double t = obb2.mCorner[0].Dot(obb1.mAxis[0]);

	// Find the extent of box 2 on axis a
	double tMin = t;
	double tMax = t;

	for (int c = 1; c < 4; ++c) {
		t = obb2.mCorner[c].Dot(obb1.mAxis[1]);

		if (t < tMin) {
			tMin = t;
		}
		else if (t > tMax) {
			tMax = t;
		}
	}
	// See if [tMin, tMax] intersects [0, 1]
	if ((tMin > (double)obb1.mOrigin._x + 1.0) || (tMax < obb1.mOrigin._x)) {
		// There was no intersection along this dimension;
		// the boxes cannot possibly overlap.
		return false;
	}

	t = obb2.mCorner[0].Dot(obb1.mAxis[1]);

	// Find the extent of box 2 on axis a
	tMin = t;
	tMax = t;

	for (int c = 1; c < 4; ++c) {
		t = obb2.mCorner[c].Dot(obb1.mAxis[1]);

		if (t < tMin) {
			tMin = t;
		}
		else if (t > tMax) {
			tMax = t;
		}
	}
	// See if [tMin, tMax] intersects [0, 1]
	if ((tMin > (double)obb1.mOrigin._y + 1.0) || (tMax < obb1.mOrigin._y)) {
		// There was no intersection along this dimension;
		// the boxes cannot possibly overlap.
		return false;
	}
	// There was no dimension along which there is no intersection.
	// Therefore the boxes overlap.
	return true;
}

bool TestBoxVsPoint(const BoxCollider2DComponent& box, const Vector3& pt)
{
	if (box.mAngle)
		return TestOBBVsPoint(box, pt);

	return TestAABBVsPoint(box, pt);
}

bool TestBoxVsBox(const BoxCollider2DComponent& box1, const BoxCollider2DComponent& box2)
{
	if (box1.mAngle)
		TestOBBVsOBB(box1, box2);

	return TestAABBVsAABB(box1, box2);
}

int TestOutCode(const BoxCollider2DComponent& box, const Vector3& pt)
{
	outcode code = 0;

	Vector3 relVel = box.mOrigin - pt;

	float top = (box.mOrigin - box.mCorner[2]).AbsDot(box.mAxis[0]);
	float right = (box.mOrigin - box.mCorner[2]).AbsDot(box.mAxis[1]);
	float down = -top;
	float left = -right;

	float axis0 = relVel.Dot(box.mAxis[0]);
	float axis1 = relVel.Dot(box.mAxis[1]);

	if (axis0 > top)
		code |= TOP;
	else if (axis0 < down)
		code |= BOTTOM;

	if (axis1 > right)
		code |= RIGHT;
	else if (axis1 < left)
		code |= LEFT;

	return (int)code;
}

bool TestCircleVsPoint(const CircleCollider2DComponent& circle, const Vector3& pt)
{
	Vector3 diff = pt - circle.mCenPos;
	return (diff.Length() <= circle.mRadius);
}

bool TestCircleVsCircle(const CircleCollider2DComponent& circle1, const CircleCollider2DComponent& circle2)
{
	return (circle1.mCenPos.Distance(circle2.mCenPos) <= (circle1.mRadius + circle2.mRadius));
}

bool TestCircleVsBox(const CircleCollider2DComponent& circle, const BoxCollider2DComponent& box)
{
	if (box.mAngle)
		return TestCircleVsOBB(circle, box);

	return TestCircleVsAABB(circle, box);
}

bool TestCircleVsAABB(const CircleCollider2DComponent& circle, const BoxCollider2DComponent& aabb)
{
	if (TestAABBVsPoint(aabb, circle.mCenPos))
		return true;

	if (Vec3Distance_LinetoPoint(aabb.mMinPos, Vector3(aabb.mMinPos._x, aabb.mMaxPos._y), circle.mCenPos) <= circle.mRadius ||
		Vec3Distance_LinetoPoint(Vector3(aabb.mMinPos._x, aabb.mMaxPos._y), aabb.mMaxPos, circle.mCenPos) <= circle.mRadius ||
		Vec3Distance_LinetoPoint(aabb.mMaxPos, Vector3(aabb.mMaxPos._x, aabb.mMinPos._y), circle.mCenPos) <= circle.mRadius ||
		Vec3Distance_LinetoPoint(Vector3(aabb.mMaxPos._x, aabb.mMinPos._y), aabb.mMinPos, circle.mCenPos) <= circle.mRadius)
		return true;

	return false;
}

bool TestCircleVsOBB(const CircleCollider2DComponent& circle, const BoxCollider2DComponent& oobb)
{
	if (TestOBBVsPoint(oobb, circle.mCenPos))
		return true;

	if (Vec3Distance_LinetoPoint(oobb.mCorner[0], oobb.mCorner[1], circle.mCenPos) <= circle.mRadius ||
		Vec3Distance_LinetoPoint(oobb.mCorner[1], oobb.mCorner[2], circle.mCenPos) <= circle.mRadius ||
		Vec3Distance_LinetoPoint(oobb.mCorner[2], oobb.mCorner[3], circle.mCenPos) <= circle.mRadius ||
		Vec3Distance_LinetoPoint(oobb.mCorner[3], oobb.mCorner[0], circle.mCenPos) <= circle.mRadius)
		return true;

	return false;
}

bool TestCircleVsEdge(const CircleCollider2DComponent& circle, const EdgeCollider2DComponent& edge)
{
	if (Vec3Distance_LinetoPoint(edge.m_pt0, edge.m_pt1, circle.mCenPos) <= circle.mRadius)
		return true;

	return false;
}

bool TestBoxVsEdge(const BoxCollider2DComponent& box, const EdgeCollider2DComponent& edge)
{
	if (box.mAngle)
		return TestOBBVsEdge(box, edge);

	return TestAABBVsEdge(box, edge);
}

bool TestAABBVsEdge(const BoxCollider2DComponent& obb, const EdgeCollider2DComponent& edge)
{
	//TODO
	return false;
}

bool TestOBBVsEdge(const BoxCollider2DComponent& aabb, const EdgeCollider2DComponent& edge)
{
	//TODO
	return false;
}