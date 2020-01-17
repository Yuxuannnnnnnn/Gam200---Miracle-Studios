#include "PrecompiledHeaders.h"
#include "PhysicsSystem.h"

void PhysicsSystem::Update(double dt)
{
	UpdateVelocity(dt);
	ApplyVelocityToObject(dt);
}



/////////////////////////////////////////////////////

void PhysicsSystem::Draw()
{
	RigidbodyDraw();
	CollisionDraw();
}

/////////////////////////////////////////////////////////////////////////////
void PhysicsSystem::UpdateVelocity(double dt)
{
	for (auto& it : GetComponentMap(RigidBody2D))
	{
		if (it.second->GetParentPtr()->GetDestory() || !it.second->GetEnable())
			continue;

		RigidBody2DComponent* obj = (RigidBody2DComponent*)it.second;

		if (!obj->_componentEnable || obj->_static)
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

		if (!obj->_componentEnable || obj->_static)
			continue;

		// newPos = newVel * dt + currPos;
		((TransformComponent*)GetComponentMap(Transform)[it.first])->GetPos() += obj->_velocity * (float)dt;
	}
}

void PhysicsSystem::RigidbodyDraw()
{
	for (auto& it : GetComponentMap(RigidBody2D))
	{
		if (it.second->GetParentPtr()->GetDestory() || !it.second->GetEnable())
			continue;

		RigidBody2DComponent* obj = (RigidBody2DComponent*)it.second;

		if (!obj->_componentEnable || obj->_static)
			continue;

		Vector3 newVel = obj->_velocity.Normalized();
		float length = obj->_velocity.SquaredLength();

		TransformComponent* transform = (TransformComponent*)GetComponentMap(Transform)[it.first];

		if (length > 50.f)
			length = 50.f;

		DrawDebugLine(
			transform->GetPos()._x,
			transform->GetPos()._y,
			transform->GetPos()._x + newVel._x * length,
			transform->GetPos()._y + newVel._y * length);
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


void PhysicsSystem::CollisionUpdate(double dt)
{
	UpdateCollision(dt);
	UpdateStaticCollision(dt);
}

void PhysicsSystem::CollisionDraw()
{
	for (auto& it : GetComponentMap(EdgeCollider2D))
	{
		if (it.second->GetParentPtr()->GetDestory() || !it.second->GetEnable())
			continue;

		EdgeCollider2DComponent* object = (EdgeCollider2DComponent*)it.second;

		if (!object->_componentEnable)
			continue;

		UpdateColliderData(object);

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
	}

	for (auto& it : GetComponentMap(BoxCollider2D))
	{
		if (it.second->GetParentPtr()->GetDestory() || !it.second->GetEnable())
			continue;

		BoxCollider2DComponent* object = (BoxCollider2DComponent*)it.second;

		if (!object->_componentEnable)
			continue;

		UpdateColliderData(object);

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
	}

	for (auto& it : GetComponentMap(CircleCollider2D))
	{
		if (it.second->GetParentPtr()->GetDestory() || !it.second->GetEnable())
			continue;

		CircleCollider2DComponent* object = (CircleCollider2DComponent*)it.second;

		if (!object->_componentEnable)
			continue;

		UpdateColliderData(object);

		DebugRenderer::GetInstance().DrawCircle(
			object->mCenPos._x, object->mCenPos._y,
			object->mRadius);
	}
}

void PhysicsSystem::UpdateCollision(double dt)
{
	_allEnableColliders.clear();

	for (auto& it : GetComponentMap(EdgeCollider2D))
	{
		if (it.second->GetParentPtr()->GetDestory() || !it.second->GetEnable())
			continue;

		EdgeCollider2DComponent* object = (EdgeCollider2DComponent*)it.second;

		if (!object->_componentEnable)
			continue;

		UpdateColliderData(object);

		_allEnableColliders.push_back(object);
	}

	for (auto& it : GetComponentMap(BoxCollider2D))
	{
		if (it.second->GetParentPtr()->GetDestory() || !it.second->GetEnable())
			continue;

		BoxCollider2DComponent* object = (BoxCollider2DComponent*)it.second;

		if (!object->_componentEnable)
			continue;

		UpdateColliderData(object);

		_allEnableColliders.push_back(object);
	}

	for (auto& it : GetComponentMap(CircleCollider2D))
	{
		if (it.second->GetParentPtr()->GetDestory() || !it.second->GetEnable())
			continue;

		CircleCollider2DComponent* object = (CircleCollider2DComponent*)it.second;

		if (!object->_componentEnable)
			continue;

		UpdateColliderData(object);

		_allEnableColliders.push_back(object);
	}

	std::vector<Collider2D*>::iterator it;

	for (std::vector<Collider2D*> tempList = _allEnableColliders; !tempList.empty(); tempList.erase(it))
	{
		it = tempList.begin();

		if ((*it)->_type == (unsigned)ColliderType::NONE_COLLIDER ||
			(ColliderTag)(*it)->_tag == ColliderTag::BUILDING ||
			(ColliderTag)(*it)->_tag == ColliderTag::EDGES)
			continue;

		for (auto& it2 : tempList)
		{
			if (it2->GetEnable() || !it2->_componentEnable || (*it) == it2 ||
				(ColliderTag)it2->_tag == ColliderTag::BUILDING ||
				(ColliderTag)it2->_tag == ColliderTag::EDGES)
				continue;

			if (!_collisionTable.CheckCollisionTable((ColliderTag)(*it)->_tag, (ColliderTag)it2->_tag))
				continue;

			CollisionCheckResponse(*it, it2, dt);
		}
	}
}


void PhysicsSystem::UpdateStaticCollision(double dt)
{
	std::vector<Collider2D*>::iterator it;

	for (std::vector<Collider2D*> tempList = tempList; !tempList.empty(); tempList.erase(it))
	{
		it = tempList.begin();

		if ((*it)->_type == (unsigned)ColliderType::NONE_COLLIDER ||
			(ColliderTag)(*it)->_tag == ColliderTag::BUILDING ||
			(ColliderTag)(*it)->_tag == ColliderTag::EDGES)
			continue;

		if (!_collisionTable.CheckCollisionTable((ColliderTag)(*it)->_tag, ColliderTag::BUILDING))
			continue;

		TransformComponent* transform = (TransformComponent*)GetComponentMap(Transform)[(*it)->GetParentId()];

		unsigned tileId = _collisionMap.GetTileOnMap(transform->GetPos());

		// center
		if (_collisionMap.GetTileType(tileId) == TileType::HARD_WALL)
		{
			Collider2D* other = (BoxCollider2DComponent*)GetComponentMap(BoxCollider2D)[_collisionMap.GetTileUId(tileId)];
			CollisionCheckResponse(*it, other, dt);
		}

		CollisionCheckTile(*it, tileId, dt);
	}

	for (std::vector<Collider2D*> tempList = tempList; !tempList.empty(); tempList.erase(it))
	{
		it = tempList.begin();

		if ((*it)->_type == (unsigned)ColliderType::NONE_COLLIDER ||
			(ColliderTag)(*it)->_tag == ColliderTag::BUILDING ||
			(ColliderTag)(*it)->_tag == ColliderTag::EDGES)
			continue;

		for (auto& it2 : tempList)
		{
			if (*it == it2 ||
				(ColliderTag)it2->_tag == ColliderTag::BUILDING ||
				(ColliderTag)it2->_tag == ColliderTag::EDGES)
				continue;

			if (!_collisionTable.CheckCollisionTable((ColliderTag)(*it)->_tag, ColliderTag::EDGES))
				continue;

			CollisionCheckResponse(*it, it2, dt);
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
			Collider2D* other = (BoxCollider2DComponent*)GetComponentMap(BoxCollider2D)[_collisionMap.GetTileUId(neighbourTileId)];
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
	TransformComponent* transform = (TransformComponent*)GetComponentMap(Transform)[collider1->GetParentId()];
	TransformComponent* transform2 = (TransformComponent*)GetComponentMap(Transform)[collider2->GetParentId()];

	RigidBody2DComponent* rigidbody = nullptr;
	RigidBody2DComponent* rigidbody2 = nullptr;

	if (collider1->_attachedRigidboy)
		rigidbody = (RigidBody2DComponent*)GetComponentMap(RigidBody2D)[collider1->GetParentId()];

	if (collider2->_attachedRigidboy)
		rigidbody2 = (RigidBody2DComponent*)GetComponentMap(RigidBody2D)[collider2->GetParentId()];

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

///////////////////////////////////////////////////////////////////////////////

void PhysicsSystem::UpdateColliderData(Collider2D* collider)
{
	switch (collider->_type)
	{
	case (unsigned)ColliderType::EDGE_COLLIDER:
	{
		EdgeCollider2DComponent* object = (EdgeCollider2DComponent*)collider;
		TransformComponent* transform = (TransformComponent*)GetComponentMap(Transform)[collider->GetParentId()];

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
		BoxCollider2DComponent* object = (BoxCollider2DComponent*)collider;
		TransformComponent* transform = (TransformComponent*)GetComponentMap(Transform)[collider->GetParentId()];

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
		CircleCollider2DComponent* object = (CircleCollider2DComponent*)collider;
		TransformComponent* transform = (TransformComponent*)GetComponentMap(Transform)[collider->GetParentId()];

		object->mCenPos = transform->GetPos();
		object->mRadius = transform->GetScale()._y * 0.5f;
		break;
	}
	default:
		break;
	}
}

void PhysicsSystem::ButtonUpdate()
{
	Vector3  pos = EngineSystems::GetInstance()._inputSystem->GetMousePos();

	for (auto& it : GetComponentMap(Button))
	{
		if (it.second->GetParentPtr()->GetDestory() || !it.second->GetEnable())
			continue;

		ButtonComponent* object = (ButtonComponent*)it.second;

		if (!object->_componentEnable)
			continue;

		_engineSystems._physicsSystem->UpdateColliderData(object);

		if (TestBoxVsPoint(*object, pos))
		{
			if (EngineSystems::GetInstance()._inputSystem->KeyDown(MOUSE_LBUTTON) ||
				(EngineSystems::GetInstance()._inputSystem->KeyHold(MOUSE_LBUTTON) && object->_pressed))
			{
				EventHandler::GetInstance().AddMouseClickEvent(it.first);
			}

			EventHandler::GetInstance().AddMouseHoverEvent(it.first);
		}
	}
}

void PhysicsSystem::ButtonDraw()
{
	for (auto it : GetComponentMap(Button))
	{
		if (it.second->GetParentPtr()->GetDestory() || !it.second->GetEnable())
			continue;

		ButtonComponent* object = (ButtonComponent*)it.second;

		if (!object->_componentEnable)
			continue;

		_engineSystems._physicsSystem->UpdateColliderData(object);

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
	}
}