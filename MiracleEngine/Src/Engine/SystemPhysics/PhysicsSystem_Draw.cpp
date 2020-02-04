#include "PrecompiledHeaders.h"
#include "PhysicsSystem.h"

void PhysicsSystem::AllColliderDraw()
{
	AllColliderDataUpdate();

	for (auto& it : GetComponentMap(BoxCollider2D))
	{
		if (!it.second || !it.second->GetEnable())
			continue;

		DrawBoxCollider2D((Collider2D*)it.second);
	}

	for (auto& it : GetComponentMap(CircleCollider2D))
	{
		if (!it.second || !it.second->GetEnable())
			continue;

		DraWCircleCollider2D((Collider2D*)it.second);
	}

	for (auto& it : GetComponentMap(EdgeCollider2D))
	{
		if (!it.second || !it.second->GetEnable())
			continue;

		DrawEdgeCollider2D((Collider2D*)it.second);
	}
}

void PhysicsSystem::AllColliderDataUpdate()
{
	for (auto& it : GetComponentMap(EdgeCollider2D))
	{
		if (!it.second || !it.second->GetEnable())
			continue;

		UpdateColliderData((Collider2D*)it.second);
	}

	for (auto& it : GetComponentMap(CircleCollider2D))
	{
		if (!it.second || !it.second->GetEnable())
			continue;

		UpdateColliderData((Collider2D*)it.second);
	}

	for (auto& it : GetComponentMap(BoxCollider2D))
	{
		if (!it.second || !it.second->GetEnable())
			continue;

		UpdateColliderData((Collider2D*)it.second);
	}
}

void PhysicsSystem::DrawBoxCollider2D(Collider2D* obj)
{
	BoxCollider2DComponent* object = dynamic_cast<BoxCollider2DComponent*>(obj);

	if (!object)
		return;

	DebugRenderer::GetInstance().DrawLine(
		object->_data._pointArray[0]._x,
		object->_data._pointArray[0]._y,
		object->_data._pointArray[1]._x,
		object->_data._pointArray[1]._y);

	DebugRenderer::GetInstance().DrawLine(
		object->_data._pointArray[1]._x,
		object->_data._pointArray[1]._y,
		object->_data._pointArray[2]._x,
		object->_data._pointArray[2]._y);

	DebugRenderer::GetInstance().DrawLine(
		object->_data._pointArray[2]._x,
		object->_data._pointArray[2]._y,
		object->_data._pointArray[3]._x,
		object->_data._pointArray[3]._y);

	DebugRenderer::GetInstance().DrawLine(
		object->_data._pointArray[3]._x,
		object->_data._pointArray[3]._y,
		object->_data._pointArray[0]._x,
		object->_data._pointArray[0]._y);


	Vector3 boxCenter = object->_data._AABB._BC._center;
	Vector3 X_axis = object->_data._ptrEdgeArray[0]._normalVec;
	Vector3 Y_axis = object->_data._ptrEdgeArray[1]._normalVec;

	DebugRenderer::GetInstance().DrawLine(
		boxCenter._x,
		boxCenter._y,
		boxCenter._x + X_axis._x * 10.f,
		boxCenter._y + X_axis._y * 10.f);

	DebugRenderer::GetInstance().DrawLine(
		boxCenter._x,
		boxCenter._y,
		boxCenter._x + Y_axis._x * 10.f,
		boxCenter._y + Y_axis._y * 10.f);
}

void PhysicsSystem::DraWCircleCollider2D(Collider2D* obj)
{
	CircleCollider2DComponent* object = dynamic_cast<CircleCollider2DComponent*>(obj);

	if (!object)
		return;

	DebugRenderer::GetInstance().DrawCircle(
		object->_data._center._x, object->_data._center._y,
		object->_radius);
}

void PhysicsSystem::DrawEdgeCollider2D(Collider2D* obj)
{
	EdgeCollider2DComponent* object = dynamic_cast<EdgeCollider2DComponent*>(obj);

	if (!object)
		return;

	DebugRenderer::GetInstance().DrawLine(
		object->_data._startPoint._x,
		object->_data._startPoint._y,
		object->_data._endPoint._x,
		object->_data._endPoint._y);

	DebugRenderer::GetInstance().DrawLine(
		object->_data._centerPoint._x,
		object->_data._centerPoint._y,
		object->_data._centerPoint._x + object->_data._normalVec._x * 10.f,
		object->_data._centerPoint._y + object->_data._normalVec._y * 10.f);
}

void PhysicsSystem::RigidbodyDraw()
{
	for (auto& it : GetComponentMap(RigidBody2D))
	{
		if (!it.second || !it.second->GetEnable())
			continue;

		RigidBody2DComponent* obj = (RigidBody2DComponent*)it.second;

		if (!obj || obj->_static)
			continue;

		Vector3 newVel = obj->_velocity.Normalized();
		float length = obj->_velocity.SquaredLength();

		TransformComponent* transform = (TransformComponent*)GetComponentMap(Transform)[it.first];

		if (!transform)
			continue;

		if (length > 50.f)
			length = 50.f;

		DebugRenderer::GetInstance().DrawLine(
			transform->GetPos()._x,
			transform->GetPos()._y,
			transform->GetPos()._x + newVel._x * length,
			transform->GetPos()._y + newVel._y * length);
	}
}