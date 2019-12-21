#include "PrecompiledHeaders.h"
#include "CollisionManager.h"
#include "Collision.h"

#include "Engine/EngineSystems.h"

void CollisionManager::Update(double dt)
{
	UpdateCollision(dt);
	UpdateStaticCollision(dt);
}

void CollisionManager::Draw()
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

void CollisionManager::UpdateCollision(double dt)
{
	for (auto it : _collider2dList)
	{
		if (!it.second->GetEnable() || !it.second->_componentEnable)
			continue;

		UpdateColliderData(it.second);
	}

	std::unordered_map<size_t, ICollider2D* >::iterator it;

	for (std::unordered_map<size_t, ICollider2D* > tempList = _collider2dList;
		!tempList.empty();
		tempList.erase(it))
	{
		it = tempList.begin();

		if (!it->second->GetEnable() || !it->second->_componentEnable ||
			it->second->_type == (unsigned)ColliderType::NONE_COLLIDER ||
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

void CollisionManager::AddObject(size_t uId, void* component)
{
	_collider2dList.insert({ uId, (ICollider2D*)component });
}

void CollisionManager::RemoveObject(size_t uId)
{
	_collider2dList.erase(uId);
}


void CollisionManager::UpdateStaticCollision(double dt)
{
	std::unordered_map<size_t, ICollider2D* >::iterator it;

	for (std::unordered_map<size_t, ICollider2D* > tempList = _collider2dList;
		!tempList.empty();
		tempList.erase(it))
	{
		it = tempList.begin();

		if (!it->second->GetEnable() || !it->second->_componentEnable ||
			it->second->_type == (unsigned)ColliderType::NONE_COLLIDER ||
			(ColliderTag)it->second->_tag == ColliderTag::BUILDING)
			continue;

		if (!_collisionTable.CheckCollisionTable((ColliderTag)it->second->_tag, ColliderTag::BUILDING))
			continue;

		TransformComponent* transform = _engineSystems._transforManager->GetTransform(it->first);

		unsigned tileId = _collisionMap.GetTileOnMap(transform->GetPos());

		// center
		if (_collisionMap.GetTileType(tileId) == TileType::HARD_WALL)
		{
			ICollider2D* other = _collider2dList[_collisionMap.GetTileUId(tileId)];
			CollisionCheckResponse(it->second, other, dt);
		}

		CollisionCheckTile(it->second, tileId, dt);
	}

	for (std::unordered_map<size_t, ICollider2D* > tempList = _collider2dList;
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

int CollisionManager::CollisionCheckTile(ICollider2D* object, unsigned centerTileId, double dt, unsigned dir, unsigned checked)
{
	unsigned neighbourTileId = _collisionMap.GetNeighborTile(centerTileId, (TileDirection)dir);

	if (neighbourTileId != centerTileId)
	{
		TileType neighbourTileType = _collisionMap.GetTileType(neighbourTileId);

		if (neighbourTileType == TileType::HARD_WALL)
		{
			ICollider2D* other = _collider2dList[_collisionMap.GetTileUId(neighbourTileId)];
			CollisionCheckResponse(object, other, dt);
			checked++;
		}
	}

	if (dir == (unsigned)TileDirection::TOTAL_DIR)
		return checked;

	return CollisionCheckTile(object, centerTileId, dt, ++dir, checked);
}

void CollisionManager::CollisionCheckResponse(ICollider2D* collider1, ICollider2D* collider2, double dt)
{
	TransformComponent* transform = _engineSystems._transforManager->GetTransform(collider1->GetParentId());
	TransformComponent* transform2 = _engineSystems._transforManager->GetTransform(collider2->GetParentId());

	RigidBody2D* rigidbody = nullptr;
	RigidBody2D* rigidbody2 = nullptr;

	if (collider1->_attachedRigidboy)
		rigidbody = _engineSystems._rigidbodyManager->_rigidBody2dList[collider1->GetParentId()];

	if (collider2->_attachedRigidboy)
		rigidbody2 = _engineSystems._rigidbodyManager->_rigidBody2dList[collider2->GetParentId()];

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

void CollisionManager::UpdateColliderData(ICollider2D* collider)
{
	switch (collider->_type)
	{
	case (unsigned)ColliderType::EDGE_COLLIDER:
	{
		EdgeCollider2D* object = (EdgeCollider2D*)collider;
		TransformComponent* transform = _engineSystems._transforManager->GetTransform(collider->GetParentId());

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
		TransformComponent* transform = _engineSystems._transforManager->GetTransform(collider->GetParentId());

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
		TransformComponent* transform = _engineSystems._transforManager->GetTransform(collider->GetParentId());

		object->mCenPos = transform->GetPos();
		object->mRadius = transform->GetScale()._y * 0.5f;
		break;
	}
	default:
		break;
	}
}
