///////////////////////////////////////////////////////////////////////////////////////
//
//	Physics.cpp
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#include "Physics.h"
#include "Collision.h"

Physics::Physics() : 
	_ListCollider2D{}, 
	_ListRigidBody2D{}
{

}

Physics::~Physics()
{
	std::vector<Collider2D*>::iterator iterator = _ListCollider2D.begin();
	while (iterator != _ListCollider2D.end())
	{
		delete* iterator;
		iterator++;
	}

	std::vector<RigidBody2D*>::iterator iterator2 = _ListRigidBody2D.begin();
	while (iterator2 != _ListRigidBody2D.end())
	{
		delete* iterator2;
		iterator2++;
	}
}

void Physics::Update(double dt)
{

	FrameRateController::GetInstance().StartTimeCounter();

	//std::cout << "~~~~~~~~~~~~~~~~~~" << std::endl;
	std::vector<RigidBody2D*>::iterator iterator = _ListRigidBody2D.begin();

	while (iterator != _ListRigidBody2D.end())
	{
		(*iterator)->UpdateVec(dt);
		iterator++;
	}
	//std::cout << "~~~~~~~~~~~~~~~~~~" << std::endl;
	std::vector<Collider2D*> tempList = _ListCollider2D;

	while(!tempList.empty())
	{
		std::vector<Collider2D*>::iterator iterator2 = tempList.begin();

		if (!(*iterator2)->_enable)
		{
			tempList.erase(iterator2);
			continue;
		}

		for (auto it3 : tempList)
		{
			if (!it3->_enable || *iterator2 == it3)
				continue;

			if ((*iterator2)->_type == BOX_COLLIDER)
			{
				if (it3->_type == BOX_COLLIDER)
					UpdateCollision(BOX_BOX, (*iterator2), it3, dt);
				else if (it3->_type == CIRCLE_COLLIDER)
					UpdateCollision(CIRCLE_BOX, it3, (*iterator2), dt);
				else if (it3->_type == LINE_COLLIDER)
					UpdateCollision(BOX_LINE, (*iterator2), it3, dt);
			}
			else if ((*iterator2)->_type == CIRCLE_COLLIDER)
			{
				if (it3->_type == BOX_COLLIDER)
					UpdateCollision(CIRCLE_BOX, (*iterator2), it3, dt);
				else if (it3->_type == CIRCLE_COLLIDER)
					UpdateCollision(CIRCLE_CIRCLE, (*iterator2), it3, dt);
				else if (it3->_type == LINE_COLLIDER)
					UpdateCollision(CIRCLE_LINE, (*iterator2), it3, dt);
			}
			else if ((*iterator2)->_type == LINE_COLLIDER)
			{
				if (it3->_type == BOX_COLLIDER)
					UpdateCollision(BOX_LINE, it3, (*iterator2), dt);
				else if (it3->_type == CIRCLE_COLLIDER)
					UpdateCollision(CIRCLE_LINE, it3, (*iterator2), dt);
				else if (it3->_type == LINE_COLLIDER)
					continue;
			}
		}

		tempList.erase(iterator2);
	}

	//std::cout << "~~~~~~~~~~~~~~~~~~" << std::endl;
	std::vector<RigidBody2D*>::iterator iterator4 = _ListRigidBody2D.begin();

	while (iterator4 != _ListRigidBody2D.end())
	{
		(*iterator4)->UpdatePos(dt);
		iterator4++;
	}
	//std::cout << "~~~~~~~~~~~~~~~~~~" << std::endl;
	EventHandler::GetInstance().UpdateEvent();
	//std::cout << "~~~~~~~~~~~~~~~~~~" << std::endl;

	float time = FrameRateController::GetInstance().EndTimeCounter() / FrameRateController::GetInstance().GetFrameTime() * 100;
	ImGui::Text("Physics per Frame Percentage: %.3f %", time);

}

Collider2D* Physics::CreateCircleCollider(const Vector3& _v, const float& r)
{
	CircleCollider2D* newCircle = new CircleCollider2D{ _v, r };
	newCircle->_type = CIRCLE_COLLIDER;

	Collider2D* result = dynamic_cast<Collider2D*>(newCircle);

	_ListCollider2D.push_back(result);

	return result;
}

Collider2D* Physics::CreateBoxCollider(const Vector3& _cenPos, const Vector3& _scale, float angle)
{
	BoxCollider2D* newBox = new BoxCollider2D{ _cenPos, _scale, angle};
	newBox->_type = BOX_COLLIDER;

	Collider2D* result = dynamic_cast<Collider2D*>(newBox);

	_ListCollider2D.push_back(result);

	return result;
}


Collider2D* Physics::CreateEdgeCollider(const Vector3& pos, float scale, float dir)
{
	EdgeCollider2D* newLine = new EdgeCollider2D{ pos, scale, dir};
	newLine->_type = LINE_COLLIDER;

	Collider2D* result = dynamic_cast<Collider2D*>(newLine);

	_ListCollider2D.push_back(result);

	return result;
}

RigidBody2D* Physics::CreateRigidBody2D()
{
	RigidBody2D* result = new RigidBody2D{};

	_ListRigidBody2D.push_back(result);

	return result;
}