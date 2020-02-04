#include "PrecompiledHeaders.h"
#include "Collision.h"
#include "../Tools/EventHandler/EventHandler.h"

void BoxVsBoxCollisionUpdate(Collider2D* boxA, Collider2D* boxB, double dt)
{
	BoxCollider2DComponent* BoxA = dynamic_cast<BoxCollider2DComponent*>(boxA);
	BoxCollider2DComponent* BoxB = dynamic_cast<BoxCollider2DComponent*>(boxB);

	if (!BoxA || !BoxB) // check dynamic_cast success
		return;

	CollisionData data;

	TransformComponent* transformA = (TransformComponent*)GetComponentMap(Transform)[BoxA->GetParentId()];
	TransformComponent* transformB = (TransformComponent*)GetComponentMap(Transform)[BoxB->GetParentId()];

	RigidBody2DComponent* rigidbodyA = nullptr;
	RigidBody2DComponent* rigidbodyB = nullptr;

	if (BoxA->_attachedRigidboy)
	{
		rigidbodyA = (RigidBody2DComponent*)GetComponentMap(RigidBody2D)[BoxA->GetParentId()];

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

	if (BoxB->_attachedRigidboy)
	{
		rigidbodyB = (RigidBody2DComponent*)GetComponentMap(RigidBody2D)[BoxB->GetParentId()];

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


	// box static check
		// static response
	// box dynaimc check
		// dynamic response

	if (Collision::CollisionCheck(BoxA->_data, BoxB->_data))
	{

	}
	else if (BoxVsBoxIntersection(BoxA, BoxB, data))
	{

	}
}

void CircleVsCircleCollisionUpdate(Collider2D* circleA, Collider2D* circleB, double dt)
{
	CircleCollider2DComponent* CircleA = dynamic_cast<CircleCollider2DComponent*>(circleA);
	CircleCollider2DComponent* CircleB = dynamic_cast<CircleCollider2DComponent*>(circleB);

	if (!CircleA || !CircleB) // check dynamic_cast success
		return;

	CollisionData data;

	TransformComponent* transformA = (TransformComponent*)GetComponentMap(Transform)[CircleA->GetParentId()];
	TransformComponent* transformB = (TransformComponent*)GetComponentMap(Transform)[CircleB->GetParentId()];

	RigidBody2DComponent* rigidbodyA = nullptr;
	RigidBody2DComponent* rigidbodyB = nullptr;

	if (CircleA->_attachedRigidboy)
	{
		rigidbodyA = (RigidBody2DComponent*)GetComponentMap(RigidBody2D)[CircleA->GetParentId()];

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

	if (CircleB->_attachedRigidboy)
	{
		rigidbodyB = (RigidBody2DComponent*)GetComponentMap(RigidBody2D)[CircleB->GetParentId()];

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


	// circle static check
		// static response
	// circle dynaimc check
		// dynamic response

	if (Collision::CollisionCheck(CircleA->_data, CircleB->_data))
	{

	}
	else if (CircleVsCircleIntersection(CircleA, CircleB, data))
	{

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

	}
	else if (CircleVsBoxIntersection(Circle, Box, data))
	{

	}
}

void CircleVsEdgeCollisionUpdate(Collider2D* circle, Collider2D* edge, double dt)
{
	CircleCollider2DComponent* Circle = dynamic_cast<CircleCollider2DComponent*>(circle);
	EdgeCollider2DComponent* Edge = dynamic_cast<EdgeCollider2DComponent*>(edge);

	if (!Circle || !Edge) // check dynamic_cast success
		return;

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
}

void BoxVsEdgeCollisionUpdate(Collider2D* box, Collider2D* edge, double dt)
{
	BoxCollider2DComponent* Box = dynamic_cast<BoxCollider2DComponent*>(box);
	EdgeCollider2DComponent* Edge = dynamic_cast<EdgeCollider2DComponent*>(edge);

	if (!Edge || !Box) // check dynamic_cast success
		return;

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
}





