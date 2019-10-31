///////////////////////////////////////////////////////////////////////////////////////
//
//	Physics.cpp
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#include "PrecompiledHeaders.h"
#include "Physics.h"
#include "Collision.h"

#include "../Tools/EventHandler/EventHandler.h"

Physics::Physics() :
	_ListCollider2D{},
	_ListRigidBody2D{},
	_ListPickableObject{},
	_enable{ true }
{

}

Physics::~Physics()
{
	Clear();
}

void Physics::Clear()
{
	std::vector<Collider2D*>::iterator iterator = _ListCollider2D.begin();
	while (iterator != _ListCollider2D.end())
	{
		delete* iterator;
		iterator++;
	}
	_ListCollider2D.clear();

	std::vector<RigidBody2D*>::iterator iterator2 = _ListRigidBody2D.begin();
	while (iterator2 != _ListRigidBody2D.end())
	{
		delete* iterator2;
		iterator2++;
	}
	_ListRigidBody2D.clear();

	std::vector<PickingCollider*>::iterator iterator3 = _ListPickableObject.begin();
	while (iterator3 != _ListPickableObject.end())
	{
		delete* iterator3;
		iterator3++;
	}
	_ListPickableObject.clear();
}

void Physics::Update(double dt)
{
	if (!_enable)
		return;

	UpdatePhyiscs(dt);

	UpdatePicking(dt);

	UpdateCollision(dt);
	UpdateTransform(dt);
	UpdateEvents();
}

void Physics::UpdatePhyiscs(double dt)
{
	for (auto it : _ListRigidBody2D)
		it->UpdateVec(dt);
}
void Physics::UpdateCollision(double dt)
{
	for (auto it : _ListCollider2D)
		it->Update();

	std::vector<Collider2D*> tempList = _ListCollider2D;

	while (!tempList.empty())
	{
		std::vector<Collider2D*>::iterator it = tempList.begin();

		if (!(*it)->_enable || (*it)->_type == (unsigned)ColliderType::NONE_COLLIDER)
		{
			tempList.erase(it);
			continue;
		}

		for (auto it2 : tempList)
		{
			if (!it2->_enable || *it == it2)
				continue;

			if ((*it)->_type == (unsigned)ColliderType::BOX_COLLIDER)
			{
				if (it2->_type == (unsigned)ColliderType::BOX_COLLIDER)
				{
					Collision_Check_Response(COLLISION_TYPE::BOX_BOX, (*it), it2, dt);
				}
				else if (it2->_type == (unsigned)ColliderType::CIRCLE_COLLIDER)
				{
					Collision_Check_Response(COLLISION_TYPE::CIRCLE_BOX, it2, (*it), dt);
				}
				else if (it2->_type == (unsigned)ColliderType::LINE_COLLIDER)
				{
					Collision_Check_Response(COLLISION_TYPE::BOX_LINE, (*it), it2, dt);
				}
			}
			else if ((*it)->_type == (unsigned)ColliderType::CIRCLE_COLLIDER)
			{
				if (it2->_type == (unsigned)ColliderType::BOX_COLLIDER)
				{
					Collision_Check_Response(COLLISION_TYPE::CIRCLE_BOX, (*it), it2, dt);
				}
				else if (it2->_type == (unsigned)ColliderType::CIRCLE_COLLIDER)
				{
					Collision_Check_Response(COLLISION_TYPE::CIRCLE_CIRCLE, (*it), it2, dt);
				}
				else if (it2->_type == (unsigned)ColliderType::LINE_COLLIDER)
				{
					Collision_Check_Response(COLLISION_TYPE::CIRCLE_LINE, (*it), it2, dt);
				}
			}
			else if ((*it)->_type == (unsigned)ColliderType::LINE_COLLIDER)
			{
				if (it2->_type == (unsigned)ColliderType::BOX_COLLIDER)
				{
					Collision_Check_Response(COLLISION_TYPE::BOX_LINE, it2, (*it), dt);
				}
				else if (it2->_type == (unsigned)ColliderType::CIRCLE_COLLIDER)
				{
					Collision_Check_Response(COLLISION_TYPE::CIRCLE_LINE, it2, (*it), dt);
				}
				else if (it2->_type == (unsigned)ColliderType::LINE_COLLIDER)
				{
					continue;
				}
			}
		}

		tempList.erase(it);
	}

	for (auto it : _ListCollider2D)
		it->Draw();
}
void Physics::UpdateTransform(double dt)
{
	for (auto it : _ListRigidBody2D)
		it->UpdatePos(dt);
}
void Physics::UpdateEvents()
{
	EventHandler::GetInstance().UpdateEvent();
}

void Physics::UpdatePicking(double dt)
{
	(void)dt;

	/*for (auto it : _ListPickableObject)
	{
		it->TestBoxVsPoint()
	}*/
}




Collider2D* Physics::CreateCircleCollider(TransformComponent* transform)
{
	CircleCollider2D* newCircle = new CircleCollider2D{ transform };
	newCircle->_type = (unsigned)ColliderType::CIRCLE_COLLIDER;

	Collider2D* result = dynamic_cast<Collider2D*>(newCircle);

	_ListCollider2D.push_back(result);

	return result;
}

Collider2D* Physics::CreateBoxCollider(TransformComponent* transform)
{
	BoxCollider2D* newBox = new BoxCollider2D{ transform };
	newBox->_type = (unsigned)ColliderType::BOX_COLLIDER;

	Collider2D* result = dynamic_cast<Collider2D*>(newBox);

	_ListCollider2D.push_back(result);

	return result;
}


Collider2D* Physics::CreateEdgeCollider(TransformComponent* transform)
{
	EdgeCollider2D* newLine = new EdgeCollider2D{ transform };
	newLine->_type = (unsigned)ColliderType::LINE_COLLIDER;

	Collider2D* result = dynamic_cast<Collider2D*>(newLine);

	_ListCollider2D.push_back(result);

	return result;
}

RigidBody2D* Physics::CreateRigidBody2D(TransformComponent* transform)
{
	RigidBody2D* result = new RigidBody2D{ transform };

	_ListRigidBody2D.push_back(result);

	return result;
}

PickingCollider* Physics::CreatePickableObject(TransformComponent* transform)
{
	PickingCollider* result = new PickingCollider{ transform };

	_ListPickableObject.push_back(result);

	return result;
}