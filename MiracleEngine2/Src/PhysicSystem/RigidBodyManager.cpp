#include "PrecompiledHeaders.h"
#include "RigidBodyManager.h"

void RigidbodyManager::UpdateVelocity(double dt)
{
	for (auto it : _rigidBody2dList)
	{
		if (!it.second->GetEnable() || !it.second->_componentEnable)
			continue;

		if (it.second->_static)
			continue;

		Vector3 newVel{ 0.f, 0.f , 0.f };

		// newVel = a * dt + currVel;;
		newVel = it.second->_appliedForce / it.second->_mass;
		newVel = it.second->_velocity + newVel * (float)dt;

		// newVel = newVel * firction;
		newVel = newVel * (1.f - it.second->_fictionVal);

		it.second->_velocity = newVel;

		it.second->_appliedForce = Vector3{ 0.f,0.f,0.f };
	}
}

void RigidbodyManager::ApplyVelocityToObject(double dt)
{
	for (auto it : _rigidBody2dList)
	{
		if (!it.second->GetEnable() || !it.second->_componentEnable)
			continue;

		if (it.second->_static)
			continue;

		// newPos = newVel * dt + currPos;
		_transformList[it.first]->GetPos() += it.second->_velocity * (float)dt;
	}
}

void RigidbodyManager::Draw()
{
	for (auto it : _rigidBody2dList)
	{
		if (!it.second->GetEnable() || !it.second->_componentEnable)
			continue;

		if (it.second->_static)
			continue;

		Vector3 newVel = it.second->_velocity.Normalized();
		float length = it.second->_velocity.SquaredLength();

		if (length > 50.f)
			length = 50.f;

		DrawDebugLine(
			_transformList[it.first]->GetPos()._x,
			_transformList[it.first]->GetPos()._y,
			_transformList[it.first]->GetPos()._x + newVel._x * length,
			_transformList[it.first]->GetPos()._y + newVel._y * length);
	}
}

void RigidbodyManager::AddObject(size_t uId)
{

}

void RigidbodyManager::RemoveObject(size_t uId)
{
	_rigidBody2dList.erase(uId);
}


void RigidbodyManager::AddForce(size_t uId, Vector3 forceDir, float force)
{
	RigidBody2D* object = EngineSystems::GetInstance()._physicsSystem->GetRigidBody2D(uId);

	if (!object)
		return;

	forceDir.Normalize();
	object->_appliedForce += forceDir * force;
}

void RigidbodyManager::AddForwardForce(size_t uId, float force)
{
	RigidBody2D* object = EngineSystems::GetInstance()._physicsSystem->GetRigidBody2D(uId);
	TransformComponent* transform = EngineSystems::GetInstance()._physicsSystem->GetTransform(uId);

	if (!object)
		return;

	Mtx33 temp = Mtx33::CreateRotation(transform->GetRotate());

	Vector2 result = temp * Vector2{ 0, 1 };
	object->_direction.Set(result._x, result._y);
	object->_direction.Normalize();

	object->_appliedForce += object->_direction * force;
}
