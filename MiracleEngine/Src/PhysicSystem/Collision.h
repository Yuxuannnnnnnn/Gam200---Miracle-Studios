///////////////////////////////////////////////////////////////////////////////////////
//
//	Collision.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _COLLISION_H
#define _COLLISION_H
#include "CollisionComponent/CircleCollider2D.h"
#include "CollisionComponent/BoxCollider2D.h"
#include "CollisionComponent/EdgeCollider2D.h"

#include "Tools/EventHandler/EventHandler.h"

enum COLLISION_TYPE {
	BOX_BOX,
	CIRCLE_CIRCLE,
	CIRCLE_LINE,
	CIRCLE_BOX,
	BOX_LINE
};

void UpdateCollision(COLLISION_TYPE type, Collider2D* rhs, Collider2D* lhs, double dt);


int BoxBox_Intersection(const BoxCollider2D& circleA,				
	const Vector3& velA,														
	const BoxCollider2D& circleB,												
	const Vector3& velB,														
	Vector3& interPtA,														
	Vector3& interPtB,														
	float& interTime);														

int BoxEdge_Intersection(const BoxCollider2D& circle,			
	const Vector3& ptEnd,													
	const EdgeCollider2D& lineSeg,											
	Vector3& interPt,														
	Vector3& normalAtCollision,												
	float& interTime,														
	bool& checkLineEdges);

int BoxLine_Intersection(bool withinBothLines,
	const BoxCollider2D& circle,
	const Vector3& ptEnd,
	const EdgeCollider2D& lineSeg,
	Vector3& interPt,	
	Vector3& normalAtCollision,	
	float& interTime);

int RayBox_Intersection(const Ray& ray,
	const BoxCollider2D& circle,
	float& interTime);

void BoxEdge_Response(const Vector3& ptInter,
	const Vector3& normal,
	Vector3& ptEnd,	
	Vector3& reflected);

void BoxStaticBox_Response(const Vector3& normal,
	const float& interTime,
	const Vector3& ptStart,
	const Vector3& ptInter,
	Vector3& ptEnd,
	Vector3& reflectedVectorNormalized);

void BoxBox_Response(Vector3& normal,
	const float interTime,
	Vector3& velA,
	const float& massA,
	Vector3& interPtA,
	Vector3& velB,
	const float& massB,
	Vector3& interPtB,
	Vector3& reflectedVectorA,
	Vector3& ptEndA,
	Vector3& reflectedVectorB,
	Vector3& ptEndB);



int CircleCircle_Intersection(const CircleCollider2D& circleA,				
	const Vector3& velA,														
	const CircleCollider2D& circleB,												
	const Vector3& velB,													
	Vector3& interPtA,														
	Vector3& interPtB,													
	float& interTime);														



int CircleEdge_Intersection(const CircleCollider2D& circle,			
	const Vector3& ptEnd,													
	const EdgeCollider2D& lineSeg,												
	Vector3& interPt,														
	Vector3& normalAtCollision,												
	float& interTime,														
	bool& checkLineEdges);													


int CircleLine_Intersection(bool withinBothLines,						
	const CircleCollider2D& circle,													
	const Vector3& ptEnd,													
	const EdgeCollider2D& lineSeg,												
	Vector3& interPt,														
	Vector3& normalAtCollision,												
	float& interTime);														

int RayCircle_Intersection(const Ray& ray,							
	const CircleCollider2D& circle,												
	float& interTime);													


void CircleEdge_Response(const Vector3& ptInter,				
	const Vector3& normal,												
	Vector3& ptEnd,															
	Vector3& reflected);													

void CircleStaticCircle_Response(const Vector3& normal,					
	const float& interTime,													
	const Vector3& ptStart,													
	const Vector3& ptInter,													
	Vector3& ptEnd,															
	Vector3& reflectedVectorNormalized);										

void CircleCircle_Response(Vector3& normal,							
	const float interTime,													
	Vector3& velA,															
	const float& massA,														
	Vector3& interPtA,														
	Vector3& velB,															
	const float& massB,														
	Vector3& interPtB,														
	Vector3& reflectedVectorA,												
	Vector3& ptEndA,														
	Vector3& reflectedVectorB,
	Vector3& ptEndB);														

#endif