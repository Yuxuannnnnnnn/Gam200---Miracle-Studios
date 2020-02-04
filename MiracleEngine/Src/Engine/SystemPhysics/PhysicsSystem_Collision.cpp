#include "PrecompiledHeaders.h"
#include "PhysicsSystem.h"


void PhysicsSystem::CollisionUpdate(double dt)
{
	AllColliderDataUpdate();
	//UpdateCollision(dt);
	//UpdateStaticCollision(dt);
}

void PhysicsSystem::UpdateColliderData(Collider2D* collider)
{
	switch (collider->_type)
	{
	case (unsigned)ColliderType::EDGE_COLLIDER:
	{
		EdgeCollider2DComponent* object = (EdgeCollider2DComponent*)collider;
		TransformComponent* transform = (TransformComponent*)GetComponentMap(Transform)[collider->GetParentId()];

		if (!transform || !object)
			return;

		Vector3 globalPos = transform->GetPos() + object->_center;

		object->_data = BEdge{ globalPos + object->_start,  globalPos + object->_end };
		break;
	}
	case (unsigned)ColliderType::BOX_COLLIDER:
	{
		BoxCollider2DComponent* object = (BoxCollider2DComponent*)collider;
		TransformComponent* transform = (TransformComponent*)GetComponentMap(Transform)[collider->GetParentId()];

		if (!transform || !object)
			return;

		Vector3 globalPos = transform->GetPos() + object->_center;

		object->_data = BoundingPolygon::CreateBoxPolygon(globalPos,
			object->_scale,
			object->_angle + transform->GetRotate());
		break;
	}
	case (unsigned)ColliderType::CIRCLE_COLLIDER:
	{
		CircleCollider2DComponent* object = (CircleCollider2DComponent*)collider;
		TransformComponent* transform = (TransformComponent*)GetComponentMap(Transform)[collider->GetParentId()];

		if (!transform || !object)
			return;

		Vector3 globalPos = transform->GetPos() + object->_center;

		object->_data = BCircle{ globalPos ,object->_radius };
		break;
	}
	default:
		break;
	}
}


void PhysicsSystem::UpdateCollision(double dt)
{
	_allEnableColliders.clear();

	for (auto& it : GetComponentMap(EdgeCollider2D))
	{
		if (!it.second || !it.second->GetEnable())
			continue;

		EdgeCollider2DComponent* object = (EdgeCollider2DComponent*)it.second;

		UpdateColliderData(object);

		_allEnableColliders.push_back(object);
	}

	for (auto& it : GetComponentMap(BoxCollider2D))
	{
		if (!it.second || !it.second->GetEnable())
			continue;

		BoxCollider2DComponent* object = (BoxCollider2DComponent*)it.second;

		UpdateColliderData(object);

		_allEnableColliders.push_back(object);
	}

	for (auto& it : GetComponentMap(CircleCollider2D))
	{
		if (!it.second || !it.second->GetEnable())
			continue;

		CircleCollider2DComponent* object = (CircleCollider2DComponent*)it.second;

		UpdateColliderData(object);

		_allEnableColliders.push_back(object);
	}

	std::vector<Collider2D*>::iterator it;

	for (std::vector<Collider2D*> tempList = _allEnableColliders; !tempList.empty(); tempList.erase(it))
	{
		it = tempList.begin();

		if ((*it)->_type == (unsigned)ColliderType::NONE_COLLIDER)
			continue;

		for (auto& it2 : tempList)
		{
			if (!it2->GetEnable() || (*it) == it2)
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

	//RigidBody2DComponent* rigidbody = nullptr;
	//RigidBody2DComponent* rigidbody2 = nullptr;

	//if (collider1->_attachedRigidboy)
	//	rigidbody = (RigidBody2DComponent*)GetComponentMap(RigidBody2D)[collider1->GetParentId()];

	//if (collider2->_attachedRigidboy)
	//	rigidbody2 = (RigidBody2DComponent*)GetComponentMap(RigidBody2D)[collider2->GetParentId()];

	//if (collider1->_type == (unsigned)ColliderType::BOX_COLLIDER)
	//{
	//	if (collider2->_type == (unsigned)ColliderType::BOX_COLLIDER)
	//	{
	//		BOX_BOX_CollisionCR(
	//			collider1, transform, rigidbody,
	//			collider2, transform2, rigidbody2,
	//			dt);
	//	}
	//	else if (collider2->_type == (unsigned)ColliderType::CIRCLE_COLLIDER)
	//	{
	//		CIRCLE_BOX_CollisionCR(
	//			collider2, transform2, rigidbody2,
	//			collider1, transform, rigidbody,
	//			dt);
	//	}
	//	else if (collider2->_type == (unsigned)ColliderType::EDGE_COLLIDER)
	//	{
	//		BOX_EDGE_CollisionCR(
	//			collider1, transform, rigidbody,
	//			collider2,
	//			dt);
	//	}
	//}
	//else if (collider1->_type == (unsigned)ColliderType::CIRCLE_COLLIDER)
	//{
	//	if (collider2->_type == (unsigned)ColliderType::BOX_COLLIDER)
	//	{
	//		CIRCLE_BOX_CollisionCR(
	//			collider1, transform, rigidbody,
	//			collider2, transform2, rigidbody2,
	//			dt);
	//	}
	//	else if (collider2->_type == (unsigned)ColliderType::CIRCLE_COLLIDER)
	//	{
	//		CIRCLE_CIRCLE_CollisionCR(
	//			collider1, transform, rigidbody,
	//			collider2, transform2, rigidbody2,
	//			dt);
	//	}
	//	else if (collider2->_type == (unsigned)ColliderType::EDGE_COLLIDER)
	//	{
	//		CIRCLE_EDGE_CollisionCR(
	//			collider1, transform, rigidbody,
	//			collider2,
	//			dt);
	//	}
	//}
	//else if (collider1->_type == (unsigned)ColliderType::EDGE_COLLIDER)
	//{
	//	if (collider2->_type == (unsigned)ColliderType::BOX_COLLIDER)
	//	{
	//		BOX_EDGE_CollisionCR(
	//			collider2, transform2, rigidbody2,
	//			collider1,
	//			dt);
	//	}
	//	else if (collider2->_type == (unsigned)ColliderType::CIRCLE_COLLIDER)
	//	{
	//		CIRCLE_EDGE_CollisionCR(
	//			collider2, transform2, rigidbody2,
	//			collider1,
	//			dt);
	//	}
	//	// else if (collider2->_type == (unsigned)ColliderType::EDGE_COLLIDER)
	//	// ignore edge edge collision
	//}
}
