///////////////////////////////////////////////////////////////////////////////////////
//
//	PhysicsSystem.cpp
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#include "PrecompiledHeaders.h"
#include "PhysicsSystem.h"
#include "Collision.h"
#include "../Tools/EventHandler/EventHandler.h"
#include "Engine/EngineSystems.h"


RigidBody2D* PhysicsSystem::GetRigidBody2D(size_t uId)
{
	return _rigidBody2dList[uId];
}

TransformComponent* PhysicsSystem::GetTransform(size_t uId)
{
	return _transformList[uId];
}

///////////////////////////////////////////////////////////////////////////////

void PhysicsSystem::Update(double dt)
{
	UpdateButtons();
	UpdatePhyiscs(dt);
	UpdateCollision(dt);
	UpdateTransform(dt);
	UpdateEvents();
}

void PhysicsSystem::UpdatePhyiscs(double dt)
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

void PhysicsSystem::UpdateTransform(double dt)
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


void PhysicsSystem::UpdateCollision(double dt)
{
	for (auto it : _collider2dList)
	{
		if (!it.second->GetEnable() || !it.second->_componentEnable)
			continue;

		UpdateColliderData(it.second);
	}
	std::unordered_map<size_t, Collider2D* > tempList = _collider2dList;

	while (!tempList.empty())
	{
		std::unordered_map<size_t, Collider2D* >::iterator it = tempList.begin();

		if (!it->second->GetEnable() || !it->second->_componentEnable || it->second->_type == (unsigned)ColliderType::NONE_COLLIDER)
		{
			tempList.erase(it);
			continue;
		}

		for (auto it2 : tempList)
		{
			if (!it2.second->GetEnable() || !it2.second->_componentEnable || it->first == it2.first)
				continue;

			if (!_collisionTable.CheckCollisionTable((ColliderTag)it->second->_tag, (ColliderTag)it2.second->_tag))
				continue;

			TransformComponent* transform = _transformList[it->first];
			TransformComponent* transform2 = _transformList[it2.first];

			RigidBody2D* rigidbody = nullptr;
			RigidBody2D* rigidbody2 = nullptr;

			if (it->second->_attachedRigidboy)
				rigidbody = _rigidBody2dList[it->first];

			if (it2.second->_attachedRigidboy)
				rigidbody2 = _rigidBody2dList[it2.first];

			if (it->second->_type == (unsigned)ColliderType::BOX_COLLIDER)
			{
				if (it2.second->_type == (unsigned)ColliderType::BOX_COLLIDER)
				{
					BOX_BOX_CollisionCR(
						it->second, transform, rigidbody,
						it2.second, transform2, rigidbody2,
						dt);
				}
				else if (it2.second->_type == (unsigned)ColliderType::CIRCLE_COLLIDER)
				{
					CIRCLE_BOX_CollisionCR(
						it2.second, transform2, rigidbody2,
						it->second, transform, rigidbody,
						dt);
				}
				else if (it2.second->_type == (unsigned)ColliderType::EDGE_COLLIDER)
				{
					BOX_EDGE_CollisionCR(
						it->second, transform, rigidbody,
						it2.second, 
						dt);
				}
			}
			else if (it->second->_type == (unsigned)ColliderType::CIRCLE_COLLIDER)
			{
				if (it2.second->_type == (unsigned)ColliderType::BOX_COLLIDER)
				{
					CIRCLE_BOX_CollisionCR(
						it->second, transform, rigidbody,
						it2.second, transform2, rigidbody2,
						dt);
				}
				else if (it2.second->_type == (unsigned)ColliderType::CIRCLE_COLLIDER)
				{
					CIRCLE_CIRCLE_CollisionCR(
						it->second, transform, rigidbody,
						it2.second, transform2, rigidbody2,
						dt);
				}
				else if (it2.second->_type == (unsigned)ColliderType::EDGE_COLLIDER)
				{
					CIRCLE_EDGE_CollisionCR(
						it->second, transform, rigidbody,
						it2.second, 
						dt);
				}
			}
			else if (it->second->_type == (unsigned)ColliderType::EDGE_COLLIDER)
			{
				if (it2.second->_type == (unsigned)ColliderType::BOX_COLLIDER)
				{
					BOX_EDGE_CollisionCR(
						it2.second, transform2, rigidbody2,
						it->second,
						dt);
				}
				else if (it2.second->_type == (unsigned)ColliderType::CIRCLE_COLLIDER)
				{
					CIRCLE_EDGE_CollisionCR(
						it2.second, transform2, rigidbody2,
						it->second,
						dt);
				}
				// else if (it2.second->_type == (unsigned)ColliderType::EDGE_COLLIDER)
				// ignore edge edge collision

				continue;
			}
		}

		tempList.erase(it);
	}
}

void PhysicsSystem::UpdateColliderData(Collider2D* collider)
{
	switch (collider->_type)
	{
	case (unsigned)ColliderType::EDGE_COLLIDER:
	{
		EdgeCollider2D* object = (EdgeCollider2D*)collider;
		TransformComponent* transform = _transformList[collider->GetParentId()];

		float dir = transform->GetRotate();
		object->m_origin = transform->GetPos();
		Vector3 scale = transform->GetScale();

		//Direction vector
		Vector3 directionVec(cosf(dir), sinf(dir));
		directionVec.Round();

		//Get line segment normal
		object->m_normal._x = directionVec._y;
		object->m_normal._y = -directionVec._x;

		directionVec *= (scale / 2.f);

		//Get the p0 and p1
		object->m_pt0 = object->m_origin + directionVec;
		object->m_pt1 = object->m_origin - directionVec;
		break;
	}
	case (unsigned)ColliderType::BOX_COLLIDER:
	{
		BoxCollider2D* object = (BoxCollider2D*)collider;
		TransformComponent* transform = _transformList[collider->GetParentId()];

		object->mScale = transform->GetScale();
		object->mOrigin = transform->GetPos();

		//Get bounding rec
		Vector3 boundingBox_offset = { -0.5f * object->mScale._x, -0.5f * object->mScale._y };

		//Cal boundingRect minimum point
		object->mMinPos = object->mOrigin - (-boundingBox_offset);

		//boundingRect maximum point
		object->mMaxPos = object->mOrigin - boundingBox_offset;

		if (object->mAngle != transform->GetRotate())
		{
			object->mAngle = transform->GetRotate();

			Vector3 X{ cos(object->mAngle), sin(object->mAngle) };
			Vector3 Y{ -sin(object->mAngle), cos(object->mAngle) };

			X = X * object->mScale._x / 2;
			Y = Y * object->mScale._y / 2;

			object->mCorner[0] = object->mOrigin - X - Y;
			object->mCorner[1] = object->mOrigin + X - Y;
			object->mCorner[2] = object->mOrigin + X + Y;
			object->mCorner[3] = object->mOrigin - X + Y;
		}
		else
		{
			Vector3 oldCenter = (object->mCorner[0] + object->mCorner[1] + object->mCorner[2] + object->mCorner[3]) / 4;

			Vector3 translation = object->mOrigin - oldCenter;

			for (int c = 0; c < 4; ++c) {
				object->mCorner[c] += translation;
			}
		}

		object->mAxis[0] = object->mCorner[1] - object->mCorner[0];
		object->mAxis[1] = object->mCorner[3] - object->mCorner[0];

		// Make the length of each axis 1/edge length so we know any
		// dot product must be less than 1 to fall within the edge.

		object->mAxis[0].Normalize(); // so call x-axis of box
		object->mAxis[1].Normalize(); // sp call y-axis of box
		break;
	}
	case (unsigned)ColliderType::CIRCLE_COLLIDER:
	{
		CircleCollider2D* object = (CircleCollider2D*)collider;
		TransformComponent* transform = _transformList[collider->GetParentId()];

		object->mCenPos = transform->GetPos();
		object->mRadius = transform->GetScale()._y * 0.5f;
		break;
	}
	default:
		break;
	}
}



void PhysicsSystem::UpdateButtons()
{
	Vector3  pos = EngineSystems::GetInstance()._inputSystem->GetMousePos();

	for (auto it : _buttonList)
	{
		if (!it.second->GetEnable() || !it.second->_componentEnable)
			continue;

		UpdateColliderData(it.second);

		if (TestBoxVsPoint(*it.second, pos))
		{
			if (EngineSystems::GetInstance()._inputSystem->KeyDown(MOUSE_LBUTTON) ||
				(EngineSystems::GetInstance()._inputSystem->KeyHold(MOUSE_LBUTTON) && it.second->_pressed))
			{
				EventHandler::GetInstance().AddMouseClickEvent(it.first);
			}

			EventHandler::GetInstance().AddMouseHoverEvent(it.first);
		}
	}
}

void PhysicsSystem::UpdateEvents()
{
	EventHandler::GetInstance().UpdateEvent();
}

void PhysicsSystem::DrawRigidbody2D()
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

		DebugRenderer::GetInstance().DrawLine(
			_transformList[it.first]->GetPos()._x,
			_transformList[it.first]->GetPos()._y,
			_transformList[it.first]->GetPos()._x + newVel._x * length,
			_transformList[it.first]->GetPos()._y + newVel._y * length);
	}
}

void PhysicsSystem::DrawCollider2D()
{
	for (auto it : _collider2dList)
	{
		if (!it.second->GetEnable() || !it.second->_componentEnable)
			continue;

		UpdateColliderData(it.second);
		
		switch (it.second->_type)
		{
		case (unsigned)ColliderType::EDGE_COLLIDER:
		{
			EdgeCollider2D* object = (EdgeCollider2D*)it.second;
			
			DebugRenderer::GetInstance().DrawLine(
				object->m_pt0._x,
				object->m_pt0._y, 
				object->m_pt1._x, 
				object->m_pt1._y);

			DebugRenderer::GetInstance().DrawLine(
				object->m_origin._x, 
				object->m_origin._y,
				object->m_origin._x + object->m_normal._x * 10.f, 
				object->m_origin._y + object->m_normal._y * 10.f);
			break;
		}
		case (unsigned)ColliderType::BOX_COLLIDER:
		{
			BoxCollider2D* object = (BoxCollider2D*)it.second;

			DebugRenderer::GetInstance().DrawLine(
				object->mCorner[0]._x, object->mCorner[0]._y,
				object->mCorner[1]._x, object->mCorner[1]._y);
			DebugRenderer::GetInstance().DrawLine(
				object->mCorner[1]._x, object->mCorner[1]._y,
				object->mCorner[2]._x, object->mCorner[2]._y);
			DebugRenderer::GetInstance().DrawLine(
				object->mCorner[2]._x, object->mCorner[2]._y,
				object->mCorner[3]._x, object->mCorner[3]._y);
			DebugRenderer::GetInstance().DrawLine(
				object->mCorner[3]._x, object->mCorner[3]._y,
				object->mCorner[0]._x, object->mCorner[0]._y);

			DebugRenderer::GetInstance().DrawLine(
				object->mOrigin._x, object->mOrigin._y,
				object->mOrigin._x + object->mAxis[0]._x * 40.f,
				object->mOrigin._y + object->mAxis[0]._y * 40.f);
			DebugRenderer::GetInstance().DrawLine(
				object->mOrigin._x, object->mOrigin._y,
				object->mOrigin._x + object->mAxis[1]._x * 40.f,
				object->mOrigin._y + object->mAxis[1]._y * 40.f);
			break;
		}
		case (unsigned)ColliderType::CIRCLE_COLLIDER:
		{
			CircleCollider2D* object = (CircleCollider2D*)it.second;

			DebugRenderer::GetInstance().DrawCircle(
				object->mCenPos._x, object->mCenPos._y, 
				object->mRadius);
			break;
		}
		default:
			break;
		}
	}
}

void PhysicsSystem::DrawButton()
{

}


///////////////////////////////////////////////////////////////////////////////

void PhysicsSystem::UpdateDraw()
{
	DrawRigidbody2D();
	DrawCollider2D();
	DrawButton();
}

void PhysicsSystem::UpdatePicking()
{
	if (EngineSystems::GetInstance()._inputSystem->KeyDown(MOUSE_RBUTTON))
	{
		Vector3  pos = EngineSystems::GetInstance()._inputSystem->GetMousePos();

		for (auto it : _pickList)
		{
			if (!it.second->GetEnable())
				continue;

			UpdateColliderData(it.second);

			if (TestBoxVsPoint(*it.second, pos))
			{
				InspectionImguiWindow::InspectGameObject(it.second->GetParentPtr());
				std::cout << "Picking  Pos :" << pos << std::endl;
				std::cout << "Picked :" << it.second->GetParentId() << std::endl;
				return;
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
void PhysicsSystem::AddForce(size_t uId, Vector3 forceDir, float force)
{
	RigidBody2D* object = EngineSystems::GetInstance()._physicsSystem->GetRigidBody2D(uId);

	if (!object)
		return;

	forceDir.Normalize();
	object->_appliedForce += forceDir * force;
}

void PhysicsSystem::AddForwardForce(size_t uId, float force)
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