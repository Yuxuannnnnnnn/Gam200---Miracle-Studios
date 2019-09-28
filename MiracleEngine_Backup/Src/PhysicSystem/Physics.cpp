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
	//std::cout << "~~~~~~~~~~~~~~~~~~" << std::endl;
	std::vector<RigidBody2D*>::iterator iterator = _ListRigidBody2D.begin();

	while (iterator != _ListRigidBody2D.end())
	{
		(*iterator)->UpdateVec(dt);
		iterator++;
	}
	//std::cout << "~~~~~~~~~~~~~~~~~~" << std::endl;
	std::vector<Collider2D*> tempList = _ListCollider2D;

	std::vector<Collider2D*>::iterator iterator2 = tempList.begin();

	while(iterator2 != tempList.end())
	{
		

		if (!(*iterator2)->_enable)
		{
			iterator2++;
			continue;
		}

		GameObject* gameObject = (*iterator2)->_gameObject;
		RigidBody2D* gameBody = (*iterator2)->_body;

		Vector3 posNext = gameObject->_pos;
		Vector3 velA;
		
		

		if(gameBody)
			velA = gameBody->_velocity * (float)dt;

			posNext += velA;

			Vector3 interPtA;
			Vector3 interPtB;
			float interTime;

			Vector3 normalAtCollision;

		for (auto it3 : tempList)
		{
			if (!it3->_enable || *iterator2 == it3)
				continue;
				

			Vector3 velB;

			if ((*iterator2)->_type == BOX_COLLIDER)
			{
				BoxCollider2D* box = dynamic_cast<BoxCollider2D*>((*iterator2));
				box->Update(gameObject->_pos, gameObject->_scale);

				if (it3->_type == BOX_COLLIDER)
				{
					BoxCollider2D* box2 = dynamic_cast<BoxCollider2D*>(it3);
					GameObject* gameObject2 = box2->_gameObject;
					RigidBody2D* gameBody2 = it3->_body;


					velB = gameBody2->_velocity * (float)dt;


					if (BoxBox_Intersection(*box, velA, *box2, velB, interPtA, interPtB, interTime))
					{
						Vector3 normal;
						normal = interPtA - gameObject2->_pos;
						normal.Normalize();

						Vector3 reflectedVecNor;

						BoxPillar_Response(normal, interTime, gameObject->_pos, interPtA,
							posNext, reflectedVecNor);


						gameBody->_velocity = reflectedVecNor;

						//reflect the other ball
						Vector3 posNextB;//not used yet, even though computed below
						normal._x = -normal._x;
						normal._y = -normal._y;

						BoxPillar_Response(normal, interTime, gameObject2->_pos, interPtA,
							posNextB, reflectedVecNor);

						gameBody2->_velocity = reflectedVecNor;
					}
				}
				else if (it3->_type == CIRCLE_COLLIDER)
				{
					CircleCollider2D* circle2 = dynamic_cast<CircleCollider2D*>(it3);
					RigidBody2D* gameBody2 = it3->_body;

				}
				else if (it3->_type == LINE_COLLIDER)
				{

				}
			}
			else if ((*iterator2)->_type == CIRCLE_COLLIDER)
			{
				CircleCollider2D* circle = dynamic_cast<CircleCollider2D*>((*iterator2));
				circle->Update(gameObject->_pos, gameObject->_scale._x/2);



				if (it3->_type == BOX_COLLIDER)
				{

				}
				else if (it3->_type == CIRCLE_COLLIDER)
				{
					CircleCollider2D* circle2 = dynamic_cast<CircleCollider2D*>(it3);
					GameObject* gameObject2 = circle2->_gameObject;
					RigidBody2D* gameBody2 = it3->_body;


					velB = gameBody2->_velocity * (float)dt;



					if (CircleCircle_Intersection(*circle, velA, *circle2, velB, interPtA, interPtB, interTime))
					{
						Vector3 normal;
						normal = interPtA - gameObject2->_pos;
						normal.Normalize();

						Vector3 reflectedVecNor;

						CirclePillar_Response(normal, interTime, gameObject->_pos, interPtA,
							posNext, reflectedVecNor);


						gameBody->_velocity = reflectedVecNor;

						//reflect the other ball
						Vector3 posNextB;//not used yet, even though computed below
						normal._x = -normal._x;
						normal._y = -normal._y;

						CirclePillar_Response(normal, interTime, gameObject2->_pos, interPtA,
							posNextB, reflectedVecNor);

						gameBody2->_velocity = reflectedVecNor;
					}
				}
				else if (it3->_type == LINE_COLLIDER)
				{
					EdgeCollider2D* line = dynamic_cast<EdgeCollider2D*>(it3);

					bool _true = true;

					

					if (CircleEdge_Intersection(*circle, posNext, *line, interPtA, normalAtCollision, interTime, _true))
					{
						/*Vector3 reflectedVec;

						CircleEdge_Response(interPtA, normalAtCollision, posNext, reflectedVec);

						gameBody->_velocity = reflectedVec;*/
						gameBody->_velocity = Vector3::Vec3Zero;

					}
					//std::cout << "YES2" << std::endl;
				}
			}
			else if ((*iterator2)->_type == LINE_COLLIDER)
			{
				//EdgeCollider2D* line = dynamic_cast<EdgeCollider2D*>((*iterator2));

				continue;

				if (it3->_type == BOX_COLLIDER)
				{

				}
				else if (it3->_type == CIRCLE_COLLIDER)
				{

				}
				else if (it3->_type == LINE_COLLIDER)
					continue;
			}

			
		}
		iterator2++;
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
}

Collider2D* Physics::CreateCircleCollider(const Vector3& _v, const float& r)
{
	CircleCollider2D* newCircle = new CircleCollider2D{ _v, r };
	newCircle->_type = CIRCLE_COLLIDER;

	Collider2D* result = dynamic_cast<Collider2D*>(newCircle);

	_ListCollider2D.push_back(result);

	return result;
}

Collider2D* Physics::CreateBoxCollider(const Vector3& _cenPos, const Vector3& _scale)
{
	BoxCollider2D* newBox = new BoxCollider2D{ _cenPos, _scale };
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