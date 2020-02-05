#include "PrecompiledHeaders.h"
#include "PhysicsSystem.h"

PhysicsSystem::PhysicsSystem()
{
}

void PhysicsSystem::Update(double dt)
{
	UpdateVelocity(dt);
	CollisionUpdate(dt);
	ApplyVelocityToObject(dt);
}

void PhysicsSystem::Draw()
{
	RigidbodyDraw();
	AllColliderDraw();	
}

void PhysicsSystem::AllColliderDataUpdate()
{
	_allEnableColliders.clear();

	for (auto& it : GetComponentMap(EdgeCollider2D))
	{
		if (!it.second || !it.second->GetEnable())
			continue;

		Collider2D* obj = (Collider2D*)it.second;

		UpdateColliderData(obj);

		_allEnableColliders.push_back(obj);
	}

	for (auto& it : GetComponentMap(CircleCollider2D))
	{
		if (!it.second || !it.second->GetEnable())
			continue;

		Collider2D* obj = (Collider2D*)it.second;

		if (GetComponentMap(RigidBody2D).find(it.first) != GetComponentMap(RigidBody2D).end())
			obj->_attachedRigidboy = true;
		else
			obj->_attachedRigidboy = false;

		UpdateColliderData(obj);

		_allEnableColliders.push_back(obj);
	}

	for (auto& it : GetComponentMap(BoxCollider2D))
	{
		if (!it.second || !it.second->GetEnable())
			continue;

		Collider2D* obj = (Collider2D*)it.second;

		if (GetComponentMap(RigidBody2D).find(it.first) != GetComponentMap(RigidBody2D).end())
			obj->_attachedRigidboy = true;
		else
			obj->_attachedRigidboy = false;

		UpdateColliderData(obj);

		_allEnableColliders.push_back(obj);
	}
}