#include "PrecompiledHeaders.h"
#include "PhysicsSystem.h"


void PhysicsSystem::UpdateVelocity(double dt)
{
	for (auto& it : GetComponentMap(RigidBody2D))
	{
		if (it.second->GetParentPtr()->GetDestory() || !it.second->GetEnable())
			continue;

		RigidBody2DComponent* obj = (RigidBody2DComponent*)it.second;

		if (!obj || obj->_static)
			continue;

		Vector3 newVel{ 0.f, 0.f , 0.f };

		// newVel = a * dt + currVel;;
		newVel = obj->_appliedForce / obj->_mass;
		newVel = obj->_velocity + newVel * (float)dt;

		// newVel = newVel * firction;
		newVel = newVel * (1.f - obj->_fictionVal);

		obj->_velocity = newVel;

		obj->_appliedForce = Vector3{ 0.f,0.f,0.f };
	}
}

void PhysicsSystem::ApplyVelocityToObject(double dt)
{
	for (auto& it : GetComponentMap(RigidBody2D))
	{
		if (it.second->GetParentPtr()->GetDestory() || !it.second->GetEnable())
			continue;

		RigidBody2DComponent* obj = (RigidBody2DComponent*)it.second;

		if (!obj || obj->_static)
			continue;

		// newPos = newVel * dt + currPos;

		TransformComponent* transform = (TransformComponent*)GetComponentMap(Transform)[it.first];

		transform->SetPos(transform->GetPos() + obj->_velocity * (float)dt);
	}
}


void PhysicsSystem::AddForce(size_t uId, Vector3 forceDir, float force)
{
	RigidBody2DComponent* object = (RigidBody2DComponent*)GetComponentMap(RigidBody2D)[uId];

	if (!object)
		return;

	forceDir.Normalize();
	object->_appliedForce += forceDir * force;
}

void PhysicsSystem::AddForwardForce(size_t uId, float force)
{
	RigidBody2DComponent* object = (RigidBody2DComponent*)GetComponentMap(RigidBody2D)[uId];
	TransformComponent* transform = (TransformComponent*)GetComponentMap(Transform)[uId];

	if (!object)
		return;

	Mtx33 temp = Mtx33::CreateRotation(transform->GetRotate());

	Vector2 result = temp * Vector2{ 0, 1 };
	object->_direction.Set(result._x, result._y);
	object->_direction.Normalize();

	object->_appliedForce += object->_direction * force;
}