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

#include "GameObjectComponents/PhysicsComponents/Collider2D.h"
#include "GameObjectComponents/PhysicsComponents/RigidBody2D.h"
#include "GameObjectComponents/PickingCollider.h"

#include "../Tools/EventHandler/EventHandler.h"
#include "Engine/EngineSystems.h"

#include <unordered_map>


void PhysicsSystem::Update(double dt)
{
	UpdatePhyiscs(dt);

	UpdatePicking(dt);

	UpdateCollision(dt);
	UpdateTransform(dt);
	UpdateEvents();
}

void PhysicsSystem::UpdatePhyiscs(double dt)
{
	for (auto it : _rigidBody2dList)
		it.second->UpdateVec(dt);
}
void PhysicsSystem::UpdateCollision(double dt)
{
	for (auto it : _collider2dList)
		it.second->Update();

	std::unordered_map<size_t, Collider2D* > tempList = _collider2dList;

	while (!tempList.empty())
	{
		std::unordered_map<size_t, Collider2D* >::iterator it = tempList.begin();

		if (!it->second->_enable || it->second->_type == (unsigned)ColliderType::NONE_COLLIDER)
		{
			tempList.erase(it);
			continue;
		}

		for (auto it2 : tempList)
		{
			if (!it2.second->_enable || it->first == it2.first)
				continue;

			if (it->second->_type == (unsigned)ColliderType::BOX_COLLIDER)
			{
				if (it2.second->_type == (unsigned)ColliderType::BOX_COLLIDER)
				{
					Collision_Check_Response(COLLISION_TYPE::BOX_BOX, it->second, it2.second, dt);
				}
				else if (it2.second->_type == (unsigned)ColliderType::CIRCLE_COLLIDER)
				{
					Collision_Check_Response(COLLISION_TYPE::CIRCLE_BOX, it2.second, it->second, dt);
				}
				else if (it2.second->_type == (unsigned)ColliderType::LINE_COLLIDER)
				{
					Collision_Check_Response(COLLISION_TYPE::BOX_LINE, it->second, it2.second, dt);
				}
			}
			else if (it->second->_type == (unsigned)ColliderType::CIRCLE_COLLIDER)
			{
				if (it2.second->_type == (unsigned)ColliderType::BOX_COLLIDER)
				{
					Collision_Check_Response(COLLISION_TYPE::CIRCLE_BOX, it->second, it2.second, dt);
				}
				else if (it2.second->_type == (unsigned)ColliderType::CIRCLE_COLLIDER)
				{
					Collision_Check_Response(COLLISION_TYPE::CIRCLE_CIRCLE, it->second, it2.second, dt);
				}
				else if (it2.second->_type == (unsigned)ColliderType::LINE_COLLIDER)
				{
					Collision_Check_Response(COLLISION_TYPE::CIRCLE_LINE, it->second, it2.second, dt);
				}
			}
			else if (it->second->_type == (unsigned)ColliderType::LINE_COLLIDER)
			{
				if (it2.second->_type == (unsigned)ColliderType::BOX_COLLIDER)
				{
					Collision_Check_Response(COLLISION_TYPE::BOX_LINE, it2.second, it->second, dt);
				}
				else if (it2.second->_type == (unsigned)ColliderType::CIRCLE_COLLIDER)
				{
					Collision_Check_Response(COLLISION_TYPE::CIRCLE_LINE, it2.second, it->second, dt);
				}
				else if (it2.second->_type == (unsigned)ColliderType::LINE_COLLIDER)
				{
					continue;
				}
			}
		}

		tempList.erase(it);
	}

	for (auto it : _collider2dList)
		it.second->Draw();
}
void PhysicsSystem::UpdateTransform(double dt)
{
	for (auto it : _rigidBody2dList)
		it.second->UpdatePos(dt);
}
void PhysicsSystem::UpdateEvents()
{
	EventHandler::GetInstance().UpdateEvent();
}

void PhysicsSystem::UpdatePicking(double dt)
{
	(void)dt;

	/*for (auto it : _ListPickableObject)
	{
		it->TestBoxVsPoint()
	}*/
}