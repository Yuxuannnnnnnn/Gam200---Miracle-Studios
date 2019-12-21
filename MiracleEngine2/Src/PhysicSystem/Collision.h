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
#include "GameObjectComponents/PhysicsComponents/BoxCollider2DComponent.h"
#include "GameObjectComponents/PhysicsComponents/CircleCollider2DComponent.h"
#include "GameObjectComponents/PhysicsComponents/EdgeCollider2DComponent.h"
#include "GameObjectComponents/GraphicComponents/TransformComponent.h"
#include "GameObjectComponents/PhysicsComponents/RigidBody2DComponent.h"

/*enum class COLLISION_TYPE {
	BOX_BOX,
	CIRCLE_CIRCLE,
	CIRCLE_BOX,
	CIRCLE_EDGE,
	BOX_EDGE
};*/

void BOX_BOX_CollisionCR(ICollider2D* colliderA,
	TransformComponent* transformA,
	RigidBody2D* rigidbodyA,
	ICollider2D* colliderB,
	TransformComponent* transformB,
	RigidBody2D* rigidbodyB,
	double dt);

void CIRCLE_CIRCLE_CollisionCR(ICollider2D* colliderA,
	TransformComponent* transformA,
	RigidBody2D* rigidbodyA,
	ICollider2D* colliderB,
	TransformComponent* transformB,
	RigidBody2D* rigidbodyB,
	double dt);

void CIRCLE_BOX_CollisionCR(ICollider2D* colliderA,
	TransformComponent* transformA,
	RigidBody2D* rigidbodyA,
	ICollider2D* colliderB,
	TransformComponent* transformB,
	RigidBody2D* rigidbodyB,
	double dt);

void CIRCLE_EDGE_CollisionCR(ICollider2D* colliderA,
	TransformComponent* transformA,
	RigidBody2D* rigidbodyA,
	ICollider2D* colliderB,
	double dt);

void BOX_EDGE_CollisionCR(ICollider2D* colliderA,
	TransformComponent* transformA,
	RigidBody2D* rigidbodyA,
	ICollider2D* colliderB,
	double dt);


///////////////////////////////////////////////////////////////////////////////
	//Dynamic Collision Check

int BoxBox_Intersection(const BoxCollider2D& boxA,
	const Vector3& velA,														
	const BoxCollider2D& boxB,												
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

//int RayBox_Intersection(const Ray& ray,
//	const BoxCollider2D& circle,
//	float& interTime);

/*int RayCircle_Intersection(const Ray& ray,
	const CircleCollider2D& circle,
	float& interTime);		*/

///////////////////////////////////////////////////////////////////////////////
	//Dynamic Response

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

int CircleBox_Intersection(const CircleCollider2D& boxA,
	const Vector3& velA,
	const BoxCollider2D& circleB,
	const Vector3& velB,
	Vector3& interPtA,
	Vector3& interPtB,
	float& interTime);


void CircleBox_Response(Vector3& normal,
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

///////////////////////////////////////////////////////////////////////////////
	//Static Collision Check

bool TestAABBVsPoint(const BoxCollider2D& aabb, const Vector3& pt);
bool TestAABBVsAABB(const BoxCollider2D& aabb1, const BoxCollider2D& aabb2);
bool TestOBBVsPoint(const BoxCollider2D& obb, const Vector3& pt);
bool TestOBBVsOBB(const BoxCollider2D& obb1, const BoxCollider2D& obb2);
bool TestOverlaps(const BoxCollider2D& obb1, const BoxCollider2D& obb2);

bool TestBoxVsPoint(const BoxCollider2D& box, const Vector3& pt);
bool TestBoxVsBox(const BoxCollider2D& box1, const BoxCollider2D& box2);
int TestOutCode(const BoxCollider2D& box, const Vector3& pt);

bool TestCircleVsPoint(const CircleCollider2D& circle, const Vector3& pt);
bool TestCircleVsCircle(const CircleCollider2D& circle1, const CircleCollider2D& circle2);

bool TestCircleVsBox(const CircleCollider2D& circle, const BoxCollider2D& box);
bool TestCircleVsAABB(const CircleCollider2D& circle, const BoxCollider2D& aabb);
bool TestCircleVsOBB(const CircleCollider2D& circle, const BoxCollider2D& oobb);

bool TestCircleVsEdge(const CircleCollider2D& circle, const EdgeCollider2D& edge);
bool TestBoxVsEdge(const BoxCollider2D& box, const EdgeCollider2D& edge);
bool TestAABBVsEdge(const BoxCollider2D& obb, const EdgeCollider2D& edge);
bool TestOBBVsEdge(const BoxCollider2D& aabb, const EdgeCollider2D& edge);
#endif