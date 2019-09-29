///////////////////////////////////////////////////////////////////////////////////////
//
//	Physics.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _PHYSICS_SYSTEM_H
#define _PHYSICS_SYSTEM_H

#include "Collider2D.h"
#include "RigidBody2D.h"
#include "EventHandler.h"

#include<iostream>
#include<vector>
#include<iterator>

class Physics final
{
public:
	//Dynamic array of Components
	std::vector<Collider2D*> _ListCollider2D;
	std::vector<RigidBody2D*> _ListRigidBody2D;

public:
	Physics();
	//Deletes all gameObjects in the list
	~Physics();

	void Update(double dt);
	
	Collider2D* CreateCircleCollider(const Vector3& _v, const float& r);

	Collider2D* CreateBoxCollider(const Vector3& _cenPos, const Vector3& _scale);

	Collider2D* CreateEdgeCollider(const Vector3& pos, float scale, float dir);

	RigidBody2D* CreateRigidBody2D();

private:
	//No replication of class object
	Physics(const Physics& rhs) = delete;
	Physics& operator= (const Physics& rhs) = delete;
};

#endif
/*
//Update object instances positions
for (unsigned int i = 0; i < GAME_OBJ_INST_NUM_MAX; ++i)
{
	GameObjInst* pBallInst = sGameObjInstList + i;

	// skip non-active object
	if (0 == (pBallInst->flag & FLAG_ACTIVE) ||
		pBallInst->pObject->type != TYPE_OBJECT_BALL)
		continue;

	CS230::Vec2 posNext;
	posNext.x = pBallInst->posCurr.x + pBallInst->velCurr.x * fpsT;
	posNext.y = pBallInst->posCurr.y + pBallInst->velCurr.y * fpsT;

	// Update the latest ball data with the lastest ball's position
	Circle& ballData = *((Circle*)pBallInst->pUserData);
	ballData.m_center.x = pBallInst->posCurr.x;
	ballData.m_center.y = pBallInst->posCurr.y;

	// Check collision with walls
	for (unsigned int j = 0; j < GAME_OBJ_INST_NUM_MAX; ++j)
	{
		GameObjInst* pInst = sGameObjInstList + j;

		if (0 == (pInst->flag & FLAG_ACTIVE))
			continue;

		switch (pInst->pObject->type)
		{
		case TYPE_OBJECT_WALL:
		{
			LineSegment& lineSegData = *((LineSegment*)pInst->pUserData);

			bool checkLineEdges = true;
			if (EXTRA_CREDITS == 2)
				checkLineEdges = false;

			if (CollisionIntersection_CircleLineSegment(ballData,
				posNext,
				lineSegData,
				interPtA,
				normalAtCollision,
				interTime,
				checkLineEdges))
			{
				CS230::Vec2 reflectedVec;

				CollisionResponse_CircleLineSegment(interPtA,
					normalAtCollision,
					posNext,
					reflectedVec);

				pBallInst->velCurr.x = reflectedVec.x * pBallInst->speed;
				pBallInst->velCurr.y = reflectedVec.y * pBallInst->speed;
			}
		}
		break;

		case TYPE_OBJECT_PILLAR:
		{
			Circle& pillarData = *((Circle*)pInst->pUserData);

			CS230::Vec2 velA = pBallInst->velCurr * fpsT;
			CS230::Vec2 velB = pInst->velCurr * fpsT;

			if (CollisionIntersection_CircleCircle(ballData, velA, pillarData,
				velB, interPtA, interPtB, interTime))
			{
				CS230::Vec2 normal;
				normal = interPtA - pInst->posCurr;
				CS230::Vector2DNormalize(normal, normal);
				//AEVec2Sub(&normal, &interPtA, &pInst->posCurr);
				//AEVec2Normalize(&normal, &normal);

				CS230::Vec2 reflectedVecNor;
				CollisionResponse_CirclePillar(normal, interTime, pBallInst->posCurr, interPtA,
					posNext, reflectedVecNor);

				pBallInst->velCurr.x = reflectedVecNor.x * pBallInst->speed;
				pBallInst->velCurr.y = reflectedVecNor.y * pBallInst->speed;
			}
		}
		break;

		case TYPE_OBJECT_BALL:
		{
			if ((EXTRA_CREDITS < 2) || (pInst == pBallInst))
				continue;

			Circle& otherBallData = *((Circle*)pInst->pUserData);

			CS230::Vec2 velA = pBallInst->velCurr * fpsT;
			CS230::Vec2 velB = pInst->velCurr * fpsT;

			//AEVec2Scale(&velA, &pBallInst->velCurr, fpsT);
			//AEVec2Scale(&velB, &pInst->velCurr, fpsT);

			if (CollisionIntersection_CircleCircle(ballData, velA, otherBallData,
				velB, interPtA, interPtB, interTime))
			{

				if (EXTRA_CREDITS >= 2)
				{
					CS230::Vec2 reflectedVecA, reflectedVecB;
					CS230::Vec2 posNextB;//not used yet, even though computed below

					CS230::Vec2 normal;
					normal = interPtA - interPtB;
					CS230::Vector2DNormalize(normal, normal);
					//AEVec2Sub(&normal, &interPtA, &interPtB);
					//AEVec2Normalize(&normal, &normal);							

					CollisionResponse_CircleCircle(normal, interTime, velA, ballData.m_mass, interPtA, velB, otherBallData.m_mass, interPtB,
						reflectedVecA, posNext, reflectedVecB, posNextB);

					pBallInst->speed = 0;// CS230::Vector2DLength(reflectedVecA) / fpsT;
					CS230::Vector2DNormalize(reflectedVecA, reflectedVecA);
					//AEVec2Length(&reflectedVecA) / fpsT;//A: new speed
					//AEVec2Normalize(&reflectedVecA, &reflectedVecA);//A: new speed direction

					pBallInst->velCurr.x = reflectedVecA.x * pBallInst->speed;
					pBallInst->velCurr.y = reflectedVecA.y * pBallInst->speed;

					pInst->speed = 0;// CS230::Vector2DLength(reflectedVecB) / fpsT;
					CS230::Vector2DNormalize(reflectedVecB, reflectedVecB);
					//pInst->speed = AEVec2Length(&reflectedVecB) / fpsT;//B: new speed
					//AEVec2Normalize(&reflectedVecB, &reflectedVecB);//B: new speed direction

					pInst->velCurr.x = reflectedVecB.x * pInst->speed;
					pInst->velCurr.y = reflectedVecB.y * pInst->speed;
				}
				else if (EXTRA_CREDITS == 1)//this is internal only - circle-circle no mass
				{

					CS230::Vec2 normal;
					normal = interPtA - pInst->posCurr;
					CS230::Vector2DNormalize(normal, normal);
					/*AEVec2Sub(&normal, &interPtA, &pInst->posCurr);
					AEVec2Normalize(&normal, &normal);

					CS230::Vec2 reflectedVecNor;
					CollisionResponse_CirclePillar(normal, interTime, pBallInst->posCurr, interPtA,
						posNext, reflectedVecNor);
					/*AECollisionResponse_CirclePillar(normal, interTime, pBallInst->posCurr, interPtA,
						posNext, reflectedVecNor);

					pBallInst->velCurr.x = reflectedVecNor.x * pBallInst->speed;
					pBallInst->velCurr.y = reflectedVecNor.y * pBallInst->speed;

					//reflect the other ball
					CS230::Vec2 posNextB;//not used yet, even though computed below
					normal.x = -normal.x;
					normal.y = -normal.y;
					CollisionResponse_CirclePillar(normal, interTime, pInst->posCurr, interPtA,
						posNextB, reflectedVecNor);
					/*AEVec2Set(&normal, -normal.x, -normal.y);
					AECollisionResponse_CirclePillar(normal, interTime, pInst->posCurr, interPtA,
						posNextB, reflectedVecNor);

					pInst->velCurr.x = reflectedVecNor.x * pInst->speed;
					pInst->velCurr.y = reflectedVecNor.y * pInst->speed;
				}
			}
			break;
		}
		}
	}

	pBallInst->posCurr.x = posNext.x;
	pBallInst->posCurr.y = posNext.y;
}

*/