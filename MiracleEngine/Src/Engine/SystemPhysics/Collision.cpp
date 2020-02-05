#include "PrecompiledHeaders.h"
#include "Collision.h"
#include "../Tools/EventHandler/EventHandler.h"

void BoxVsBoxCollisionUpdate(Collider2D* boxA, Collider2D* boxB, double dt)
{
	BoxCollider2DComponent* BoxA = dynamic_cast<BoxCollider2DComponent*>(boxA);
	BoxCollider2DComponent* BoxB = dynamic_cast<BoxCollider2DComponent*>(boxB);

	if (!BoxA || !BoxB) // check dynamic_cast success
		return;

	if (BoxA->_trigger || BoxB->_trigger)
	{
		if (Collision::CollisionCheck(BoxA->_data, BoxB->_data))
		{
			if (BoxA->_trigger)
				EventHandler::GetInstance().AddTriggered2DEvent(BoxA, BoxB);
			else
				EventHandler::GetInstance().AddTriggered2DEvent(BoxB, BoxA);
		}

		return;
	}

	CollisionData data;
	RigidBody2DComponent* rigidbodyA = nullptr;
	RigidBody2DComponent* rigidbodyB = nullptr;


	if (!BoxA->_attachedRigidboy)
	{
		rigidbodyA = (RigidBody2DComponent*)GetComponentMap(RigidBody2D)[BoxA->GetParentId()];

		if (rigidbodyA && rigidbodyA->GetEnable())
		{
			data.velA = rigidbodyA->_velocity * (float)dt;
			data.posNextA = BoxA->_data._AABB._BC._center + data.velA;
			data.massA = rigidbodyA->_mass;
		}
		else
		{
			rigidbodyA = nullptr;
			data.posNextA = BoxA->_data._AABB._BC._center;
		}
	}
	else
		data.posNextA = BoxA->_data._AABB._BC._center;

	if (BoxB->_attachedRigidboy)
	{
		rigidbodyB = (RigidBody2DComponent*)GetComponentMap(RigidBody2D)[BoxB->GetParentId()];

		if (rigidbodyB && rigidbodyB->GetEnable())
		{
			data.velB = rigidbodyB->_velocity * (float)dt;
			data.posNextB = BoxB->_data._AABB._BC._center + data.velB;
			data.massB = rigidbodyB->_mass;
		}
		else
		{
			rigidbodyB = nullptr;
			data.posNextB = BoxB->_data._AABB._BC._center;
		}
	}
	else
		data.posNextB = BoxB->_data._AABB._BC._center;


	// box static check
		// static response
	// box dynaimc check
		// dynamic response

	if (Collision::CollisionCheck(BoxA->_data, BoxB->_data))
	{
		std::cout << "box static check" << std::endl;

		if (rigidbodyA && rigidbodyB)
		{
			if (rigidbodyA->_static && rigidbodyB->_static)
				return; // redundant
			else if (rigidbodyA->_static)
			{
				// move only box b
			}
			else if (rigidbodyB->_static)
			{
				// move only box A
			}
			else
			{
			}
		}
		else if (rigidbodyA)
		{
			// move only box A
		}
		else if (rigidbodyB)
		{
			// move only box b
		}
		else
			return; // redundant

		EventHandler::GetInstance().AddCollided2DEvent(BoxA, BoxB);
		EventHandler::GetInstance().AddCollided2DEvent(BoxB, BoxA);
	}
	else if (BoxVsBoxIntersection(BoxA, BoxB, data))
	{
		std::cout << "box dynaimc check" << std::endl;

		EventHandler::GetInstance().AddCollided2DEvent(BoxA, BoxB);
		EventHandler::GetInstance().AddCollided2DEvent(BoxB, BoxA);
	}
}

void CircleVsCircleCollisionUpdate(Collider2D* circleA, Collider2D* circleB, double dt)
{
	CircleCollider2DComponent* CircleA = dynamic_cast<CircleCollider2DComponent*>(circleA);
	CircleCollider2DComponent* CircleB = dynamic_cast<CircleCollider2DComponent*>(circleB);

	if (!CircleA || !CircleB) // check dynamic_cast success
		return;

	if (CircleA->_trigger || CircleB->_trigger)
	{
		if (Collision::CollisionCheck(CircleA->_data, CircleB->_data))
		{
			if (CircleA->_trigger)
				EventHandler::GetInstance().AddTriggered2DEvent(CircleA, CircleB);
			else
				EventHandler::GetInstance().AddTriggered2DEvent(CircleB, CircleA);
		}

		return;
	}

	CollisionData data;
	RigidBody2DComponent* rigidbodyA = nullptr;
	RigidBody2DComponent* rigidbodyB = nullptr;

	if (CircleA->_attachedRigidboy)
	{
		rigidbodyA = (RigidBody2DComponent*)GetComponentMap(RigidBody2D)[CircleA->GetParentId()];

		if (rigidbodyA && rigidbodyA->GetEnable())
		{
			data.velA = rigidbodyA->_velocity * (float)dt;
			data.posNextA = CircleA->_data._center + data.velA;
			data.massA = rigidbodyA->_mass;
		}
		else
		{
			rigidbodyA = nullptr;
			data.posNextA = CircleA->_data._center;
		}
	}
	else
		data.posNextA = CircleA->_data._center;

	if (CircleB->_attachedRigidboy)
	{
		rigidbodyB = (RigidBody2DComponent*)GetComponentMap(RigidBody2D)[CircleB->GetParentId()];

		if (rigidbodyB && rigidbodyB->GetEnable())
		{
			data.velB = rigidbodyB->_velocity * (float)dt;
			data.posNextB = CircleB->_data._center + data.velB;
			data.massB = rigidbodyB->_mass;
		}
		else
		{
			rigidbodyB = nullptr;
			data.posNextB = CircleB->_data._center;
		}
	}
	else
		data.posNextB = CircleB->_data._center;


	// circle static check
		// static response
	// circle dynaimc check
		// dynamic response

	if (Collision::CollisionCheck(CircleA->_data, CircleB->_data))
	{
		std::cout << "circle static check" << std::endl;
		if (rigidbodyA && rigidbodyB)
		{
			if (rigidbodyA->_static && rigidbodyB->_static)
				return; // redundant
			else if (rigidbodyA->_static)
			{
				// move only box b
				Vec3 vec = data.posNextB - data.posNextA;
				float distance = vec.Length();

				if (!distance)
					return;

				Vec3 dir = vec.Normalized();
				float totalradius = CircleA->_data._radius + CircleB->_data._radius;

				Vec3 newVec = (dir * totalradius - vec) / (float)dt;

				rigidbodyB->_velocity = newVec;
			}
			else if (rigidbodyB->_static)
			{
				// move only box A
				Vec3 vec = data.posNextA - data.posNextB;
				float distance = vec.Length();

				if (!distance)
					return;

				Vec3 dir = vec.Normalized();
				float totalradius = CircleB->_data._radius + CircleA->_data._radius;

				Vec3 newVec = (dir * totalradius - vec) / (float)dt;

				rigidbodyA->_velocity = newVec;
			}
			else
			{
				Vec3 vec = data.posNextB - data.posNextA;
				float distance = vec.Length();

				if (!distance)
					return;

				Vec3 dir = vec.Normalized();
				float totalradius = CircleA->_data._radius + CircleB->_data._radius;

				Vec3 newVec = (dir * totalradius - vec) / (float)dt;

				rigidbodyB->_velocity = newVec * 0.5f;
				rigidbodyA->_velocity = -newVec * 0.5f;
			}
		}
		else if (rigidbodyA && !rigidbodyA->_static)
		{
			// move only box A
			Vec3 vec = data.posNextA - data.posNextB;
			float distance = vec.Length();

			if (!distance)
				return;

			Vec3 dir = vec.Normalized();
			float totalradius = CircleB->_data._radius + CircleA->_data._radius;

			Vec3 newVec = (dir * totalradius - vec) / (float)dt;

			rigidbodyA->_velocity = newVec;
		}
		else if (rigidbodyB && !rigidbodyB->_static)
		{
			// move only box b
			Vec3 vec = data.posNextB - data.posNextA;
			float distance = vec.Length();

			if (!distance)
				return;

			Vec3 dir = vec.Normalized();
			float totalradius = CircleA->_data._radius + CircleB->_data._radius;

			Vec3 newVec = (dir * totalradius - vec) / (float)dt;

			rigidbodyB->_velocity = newVec;
		}
		else
			return; // redundant

		EventHandler::GetInstance().AddCollided2DEvent(CircleA, CircleB);
		EventHandler::GetInstance().AddCollided2DEvent(CircleB, CircleA);
	}
	else if (CircleVsCircleIntersection(CircleA, CircleB, data))
	{
		std::cout << "circle dynaimc check" << std::endl;


		data.normal = data.interPtA - data.interPtB;
		data.normal._z = 0.f;
		data.normal.Normalize();

		data.reflectedVecA = data.velA;
		data.reflectedVecB = data.velB;

		CircleVsCircleResponse(data);


		if (rigidbodyA && rigidbodyB)
		{
			if (rigidbodyA->_static && rigidbodyB->_static)
				return; // redundant
			else if (rigidbodyA->_static)
			{
				// move only box b
				rigidbodyB->_velocity = data.reflectedVecB * rigidbodyB->_velocity.Length();
			}
			else if (rigidbodyB->_static)
			{
				// move only box A
				rigidbodyA->_velocity = data.reflectedVecA * rigidbodyA->_velocity.Length();
			}
			else
			{
				rigidbodyB->_velocity = data.reflectedVecB * rigidbodyB->_velocity.Length();
				rigidbodyA->_velocity = data.reflectedVecA * rigidbodyA->_velocity.Length();
			}
		}
		else if (rigidbodyA)
		{
			// move only box A
			rigidbodyA->_velocity = data.reflectedVecA * rigidbodyA->_velocity.Length();
		}
		else if (rigidbodyB)
		{
			// move only box b
			rigidbodyB->_velocity = data.reflectedVecB * rigidbodyB->_velocity.Length();
		}
		else
			return; // redundant

		EventHandler::GetInstance().AddCollided2DEvent(CircleA, CircleB);
		EventHandler::GetInstance().AddCollided2DEvent(CircleB, CircleA);
	}
}

void CircleVsBoxCollisionUpdate(Collider2D* circle, Collider2D* box, double dt)
{
	CircleCollider2DComponent* Circle = dynamic_cast<CircleCollider2DComponent*>(circle);
	BoxCollider2DComponent* Box = dynamic_cast<BoxCollider2DComponent*>(box);

	if (!Circle || !Box) // check dynamic_cast success
		return;

	CollisionData data;

	TransformComponent* transformA = (TransformComponent*)GetComponentMap(Transform)[Circle->GetParentId()];
	TransformComponent* transformB = (TransformComponent*)GetComponentMap(Transform)[Box->GetParentId()];

	RigidBody2DComponent* rigidbodyA = nullptr;
	RigidBody2DComponent* rigidbodyB = nullptr;

	if (Circle->_attachedRigidboy)
	{
		rigidbodyA = (RigidBody2DComponent*)GetComponentMap(RigidBody2D)[Circle->GetParentId()];

		if (rigidbodyA && rigidbodyA->GetEnable())
		{
			data.velA = rigidbodyA->_velocity * (float)dt;
			data.posNextA = transformA->GetPos() + data.velA;
			data.massA = rigidbodyA->_mass;
		}
		else
		{
			rigidbodyA = nullptr;
			data.posNextA = transformA->GetPos();
		}
	}
	else
		data.posNextA = transformA->GetPos();

	if (Box->_attachedRigidboy)
	{
		rigidbodyB = (RigidBody2DComponent*)GetComponentMap(RigidBody2D)[Box->GetParentId()];

		if (rigidbodyB && rigidbodyB->GetEnable())
		{
			data.velB = rigidbodyB->_velocity * (float)dt;
			data.posNextB = transformB->GetPos() + data.velB;
			data.massB = rigidbodyB->_mass;
		}
		else
		{
			rigidbodyB = nullptr;
			data.posNextB = transformB->GetPos();
		}
	}
	else
		data.posNextB = transformB->GetPos();


	// circle box static check
		// static response
	// circle box dynaimc check
		// dynamic response

	if (Collision::CollisionCheck(Box->_data, Circle->_data))
	{
		std::cout << "circle box static check" << std::endl;
	}
	else if (CircleVsBoxIntersection(Circle, Box, data))
	{
		std::cout << "circle box dynaimc check" << std::endl;
	}
}

void CircleVsEdgeCollisionUpdate(Collider2D* circle, Collider2D* edge, double dt)
{
	CircleCollider2DComponent* Circle = dynamic_cast<CircleCollider2DComponent*>(circle);
	EdgeCollider2DComponent* Edge = dynamic_cast<EdgeCollider2DComponent*>(edge);

	if (!Circle || !Edge) // check dynamic_cast success
		return;

	if (Circle->_trigger || Edge->_trigger)
	{
		if (Collision::BEdgeVSBCircle(Edge->_data, Circle->_data))
		{
			if (Circle->_trigger)
				EventHandler::GetInstance().AddTriggered2DEvent(Circle, Edge);
			else
				EventHandler::GetInstance().AddTriggered2DEvent(Edge, Circle);
		}

		return;
	}

	CollisionData data;

	TransformComponent* transformA = (TransformComponent*)GetComponentMap(Transform)[Circle->GetParentId()];
	TransformComponent* transformB = (TransformComponent*)GetComponentMap(Transform)[Edge->GetParentId()];

	RigidBody2DComponent* rigidbodyA = nullptr;
	RigidBody2DComponent* rigidbodyB = nullptr;

	if (Circle->_attachedRigidboy)
	{
		rigidbodyA = (RigidBody2DComponent*)GetComponentMap(RigidBody2D)[Circle->GetParentId()];

		if (rigidbodyA && rigidbodyA->GetEnable())
		{
			data.velA = rigidbodyA->_velocity * (float)dt;
			data.posNextA = Circle->_data._center + data.velA;
			data.massA = rigidbodyA->_mass;
		}
		else
		{
			rigidbodyA = nullptr;
			data.posNextA = Circle->_data._center;
		}
	}
	else
		data.posNextA = Circle->_data._center;

	// circle edge static check
		// static response
	// circle edge dynaimc check
		// dynamic response

	if (Collision::BEdgeVSBCircle(Edge->_data, Circle->_data))
	{
		std::cout << "circle edge static check" << std::endl;

		if (!rigidbodyA || rigidbodyA->_static)
			return;

		float penc = Circle->_data._radius - Vec3Distance_LinetoPoint(Edge->_data._startPoint, Edge->_data._endPoint, Circle->_data._center);

		if (penc == 0)
			return;

		Vector3 dir = Circle->_data._center - Edge->_data._centerPoint;

		if (Edge->_data._normalVec.Dot(dir) > 0)
			rigidbodyA->_velocity = penc * Edge->_data._normalVec / (float)dt;
		else
			rigidbodyA->_velocity = -penc * Edge->_data._normalVec / (float)dt;

		EventHandler::GetInstance().AddCollided2DEvent(Circle, Edge);
		EventHandler::GetInstance().AddCollided2DEvent(Edge, Circle);
	}
	else if (CircleVsEdgeIntersection(Circle, Edge, data))
	{
		std::cout << "circle edge dynaimc check" << std::endl;

		if (!rigidbodyA || rigidbodyA->_static)
			return;

		CircleVsEdgeResponse(data);

		rigidbodyA->_velocity = data.reflectedVecA * rigidbodyA->_velocity.Length();

		EventHandler::GetInstance().AddCollided2DEvent(Circle, Edge);
		EventHandler::GetInstance().AddCollided2DEvent(Edge, Circle);
	}	
}

void BoxVsEdgeCollisionUpdate(Collider2D* box, Collider2D* edge, double dt)
{
	BoxCollider2DComponent* Box = dynamic_cast<BoxCollider2DComponent*>(box);
	EdgeCollider2DComponent* Edge = dynamic_cast<EdgeCollider2DComponent*>(edge);

	if (!Edge || !Box) // check dynamic_cast success
		return;

	if (Box->_trigger || Edge->_trigger)
	{
		if (Collision::BEdgeVSBPolygon(Edge->_data, Box->_data))
		{
			if (Box->_trigger)
				EventHandler::GetInstance().AddTriggered2DEvent(Box, Edge);
			else
				EventHandler::GetInstance().AddTriggered2DEvent(Edge, Box);
		}

		return;
	}

	CollisionData data;

	TransformComponent* transformA = (TransformComponent*)GetComponentMap(Transform)[Box->GetParentId()];
	TransformComponent* transformB = (TransformComponent*)GetComponentMap(Transform)[Edge->GetParentId()];

	RigidBody2DComponent* rigidbodyA = nullptr;
	RigidBody2DComponent* rigidbodyB = nullptr;

	if (Box->_attachedRigidboy)
	{
		rigidbodyA = (RigidBody2DComponent*)GetComponentMap(RigidBody2D)[Box->GetParentId()];

		if (rigidbodyA && rigidbodyA->GetEnable())
		{
			data.velA = rigidbodyA->_velocity * (float)dt;
			data.posNextA = transformA->GetPos() + data.velA;
			data.massA = rigidbodyA->_mass;
		}
		else
		{
			rigidbodyA = nullptr;
			data.posNextA = transformA->GetPos();
		}
	}
	else
		data.posNextA = transformA->GetPos();

	// box edge static check
		// static response
	// box edge dynaimc check
		// dynamic response

	if (Collision::BEdgeVSBPolygon(Edge->_data, Box->_data))
	{
		std::cout << "box edge static check" << std::endl;

		if (!rigidbodyA || rigidbodyA->_static)
			return;

		float penc = -Box->_data._AABB._BC._radius;

		for (int c = 0; c < Box->_data._numPoints; ++c) {
			float t = Edge->_data._normalVec.Dot(Box->_data._pointArray[c] - Edge->_data._centerPoint);

			if (t < 0 && penc < t)
				penc = t;
		}

		if (penc == -Box->_data._AABB._BC._radius)
			return;

		Vector3 dir = Box->_data._AABB._BC._center - Edge->_data._centerPoint;

		if (Edge->_data._normalVec.Dot(dir) > 0)
			rigidbodyA->_velocity = -penc * Edge->_data._normalVec / (float)dt;
		else
			rigidbodyA->_velocity = penc * Edge->_data._normalVec / (float)dt;

		EventHandler::GetInstance().AddCollided2DEvent(Box, Edge);
		EventHandler::GetInstance().AddCollided2DEvent(Edge, Box);
	}
	else if (BoxVsEdgeIntersection(Box, Edge, data))
	{
		std::cout << "box edge dynaimc check" << std::endl;
	}
}





