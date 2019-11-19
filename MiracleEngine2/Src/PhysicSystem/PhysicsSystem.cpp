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
	UpdateStaticCollision(dt);
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

	std::unordered_map<size_t, Collider2D* >::iterator it;

	for (std::unordered_map<size_t, Collider2D* > tempList = _collider2dList;
		!tempList.empty();
		tempList.erase(it))
	{
		it = tempList.begin();

		if (!it->second->GetEnable() || !it->second->_componentEnable || 
			it->second->_type == (unsigned)ColliderType::NONE_COLLIDER||
			(ColliderTag)it->second->_tag == ColliderTag::BUILDING || 
			(ColliderTag)it->second->_tag == ColliderTag::EDGES)
			continue;

		for (auto it2 : tempList)
		{
			if (!it2.second->GetEnable() || !it2.second->_componentEnable || it->first == it2.first ||
				(ColliderTag)it2.second->_tag == ColliderTag::BUILDING ||
				(ColliderTag)it2.second->_tag == ColliderTag::EDGES)
				continue;

			if (!_collisionTable.CheckCollisionTable((ColliderTag)it->second->_tag, (ColliderTag)it2.second->_tag))
				continue;

			CollisionCheckResponse(it->second, it2.second, dt);
		}
	}
}

void PhysicsSystem::UpdateStaticCollision(double dt)
{
	std::unordered_map<size_t, Collider2D* >::iterator it;

	for(std::unordered_map<size_t, Collider2D* > tempList = _collider2dList;
		!tempList.empty();
		tempList.erase(it))
	{
		it = tempList.begin();

		if (!it->second->GetEnable() || !it->second->_componentEnable ||
			it->second->_type == (unsigned)ColliderType::NONE_COLLIDER||
			(ColliderTag)it->second->_tag == ColliderTag::BUILDING)
			continue;

		if (!_collisionTable.CheckCollisionTable((ColliderTag)it->second->_tag, ColliderTag::BUILDING))
			continue;

		TransformComponent* transform = _transformList[it->first];

		unsigned tileId = _collisionMap.GetTileOnMap(transform->GetPos());

		// center
		if (_collisionMap.GetTileType(tileId) == TileType::HARD_WALL)
		{
			Collider2D* other = _collider2dList[_collisionMap.GetTileUId(tileId)];
			CollisionCheckResponse(it->second, other, dt);
		}

		CollisionCheckTile(it->second, tileId, dt);
	}

	for (std::unordered_map<size_t, Collider2D* > tempList = _collider2dList;
		!tempList.empty();
		tempList.erase(it))
	{
		it = tempList.begin();

		if (!it->second->GetEnable() || !it->second->_componentEnable ||
			it->second->_type == (unsigned)ColliderType::NONE_COLLIDER ||
			(ColliderTag)it->second->_tag == ColliderTag::BUILDING)
			continue;

		for (auto it2 : tempList)
		{
			if (!it2.second->GetEnable() || !it2.second->_componentEnable || it->first == it2.first ||
				(ColliderTag)it2.second->_tag != ColliderTag::EDGES)
				continue;

			if (!_collisionTable.CheckCollisionTable((ColliderTag)it->second->_tag, ColliderTag::EDGES))
				continue;

			CollisionCheckResponse(it->second, it2.second, dt);
		}
	}


}

int PhysicsSystem::CollisionCheckTile(Collider2D* object, unsigned centerTileId, double dt, unsigned dir, unsigned checked)
{

	unsigned neighbourTileId = _collisionMap.GetNeighborTile(centerTileId, (TileDirection)dir);

	if (neighbourTileId != centerTileId)
	{
		TileType neighbourTileType = _collisionMap.GetTileType(neighbourTileId);

		if (neighbourTileType == TileType::HARD_WALL)
		{
			Collider2D* other = _collider2dList[_collisionMap.GetTileUId(neighbourTileId)];
			CollisionCheckResponse(object, other, dt);
			checked++;
		}
	}

	if (dir == (unsigned)TileDirection::TOTAL_DIR)
		return checked;

	return CollisionCheckTile(object, centerTileId, dt, ++dir, checked);
}


void PhysicsSystem::CollisionCheckResponse(Collider2D* collider1, Collider2D* collider2, double dt)
{
	TransformComponent* transform = _transformList[collider1->GetParentId()];
	TransformComponent* transform2 = _transformList[collider2->GetParentId()];

	RigidBody2D* rigidbody = nullptr;
	RigidBody2D* rigidbody2 = nullptr;

	if (collider1->_attachedRigidboy)
		rigidbody = _rigidBody2dList[collider1->GetParentId()];

	if (collider2->_attachedRigidboy)
		rigidbody2 = _rigidBody2dList[collider2->GetParentId()];

	if (collider1->_type == (unsigned)ColliderType::BOX_COLLIDER)
	{
		if (collider2->_type == (unsigned)ColliderType::BOX_COLLIDER)
		{
			BOX_BOX_CollisionCR(
				collider1, transform, rigidbody,
				collider2, transform2, rigidbody2,
				dt);
		}
		else if (collider2->_type == (unsigned)ColliderType::CIRCLE_COLLIDER)
		{
			CIRCLE_BOX_CollisionCR(
				collider2, transform2, rigidbody2,
				collider1, transform, rigidbody,
				dt);
		}
		else if (collider2->_type == (unsigned)ColliderType::EDGE_COLLIDER)
		{
			BOX_EDGE_CollisionCR(
				collider1, transform, rigidbody,
				collider2,
				dt);
		}
	}
	else if (collider1->_type == (unsigned)ColliderType::CIRCLE_COLLIDER)
	{
		if (collider2->_type == (unsigned)ColliderType::BOX_COLLIDER)
		{
			CIRCLE_BOX_CollisionCR(
				collider1, transform, rigidbody,
				collider2, transform2, rigidbody2,
				dt);
		}
		else if (collider2->_type == (unsigned)ColliderType::CIRCLE_COLLIDER)
		{
			CIRCLE_CIRCLE_CollisionCR(
				collider1, transform, rigidbody,
				collider2, transform2, rigidbody2,
				dt);
		}
		else if (collider2->_type == (unsigned)ColliderType::EDGE_COLLIDER)
		{
			CIRCLE_EDGE_CollisionCR(
				collider1, transform, rigidbody,
				collider2,
				dt);
		}
	}
	else if (collider1->_type == (unsigned)ColliderType::EDGE_COLLIDER)
	{
		if (collider2->_type == (unsigned)ColliderType::BOX_COLLIDER)
		{
			BOX_EDGE_CollisionCR(
				collider2, transform2, rigidbody2,
				collider1,
				dt);
		}
		else if (collider2->_type == (unsigned)ColliderType::CIRCLE_COLLIDER)
		{
			CIRCLE_EDGE_CollisionCR(
				collider2, transform2, rigidbody2,
				collider1,
				dt);
		}
		// else if (collider2->_type == (unsigned)ColliderType::EDGE_COLLIDER)
		// ignore edge edge collision
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

		DrawDebugLine(
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

			DrawDebugLine(
				object->mCorner[0]._x, object->mCorner[0]._y,
				object->mCorner[1]._x, object->mCorner[1]._y);
			DrawDebugLine(
				object->mCorner[1]._x, object->mCorner[1]._y,
				object->mCorner[2]._x, object->mCorner[2]._y);
			DrawDebugLine(
				object->mCorner[2]._x, object->mCorner[2]._y,
				object->mCorner[3]._x, object->mCorner[3]._y);
			DrawDebugLine(
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
	if (EngineSystems::GetInstance()._inputSystem->KeyDown(KEYB_S) && EngineSystems::GetInstance()._inputSystem->KeyHold(MOUSE_RBUTTON))
	{
		InspectionImguiWindow::InspectGameObject(nullptr);
	}
	else if (EngineSystems::GetInstance()._inputSystem->KeyDown(KEYB_A) && EngineSystems::GetInstance()._inputSystem->KeyHold(MOUSE_RBUTTON))
	{
		Vector3  pos = EngineSystems::GetInstance()._inputSystem->GetMousePos();

		for (auto it : _pickList)
		{
			if (!it.second->GetEnable())
				continue;

			UpdateColliderData(it.second);

			if (TestBoxVsPoint(*it.second, pos))
			{
				_pickUId = it.second->GetParentId();
				InspectionImguiWindow::InspectGameObject(it.second->GetParentPtr());
				return;
			}
		}
	}
	else if (_pickUId != 0 && EngineSystems::GetInstance()._inputSystem->KeyHold(KEYB_W) && EngineSystems::GetInstance()._inputSystem->KeyHold(MOUSE_RBUTTON))
	{
		if (_pickList.find(_pickUId) == _pickList.end())
			return;

		TransformComponent* transform = _transformList[_pickUId];
		Vector3  pos = EngineSystems::GetInstance()._inputSystem->GetMousePos();
		transform->SetPos(pos);

		std::cout << "Picking  Pos :" << pos << std::endl;
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