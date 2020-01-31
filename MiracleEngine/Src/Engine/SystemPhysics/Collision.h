#ifndef _COLLISION_H
#define _COLLISION_H
#include "GameObject/Components/Physic/BoxCollider2DComponent.h"
#include "GameObject/Components/Physic/CircleCollider2DComponent.h"
#include "GameObject/Components/Physic/EdgeCollider2DComponent.h"
#include "GameObject/Components/Graphic/TransformComponent.h"
#include "GameObject/Components/Physic/RigidBody2DComponent.h"
#include "BoundingCircle.h"
#include "BoundingPolygon.h"
#include "BoundingEdge.h"
#include "BoundingLine.h"
#include "BoundingBox.h"




/*enum class COLLISION_TYPE {
	BOX_BOX,
	CIRCLE_CIRCLE,
	CIRCLE_BOX,
	CIRCLE_EDGE,
	BOX_EDGE
};*/



// For new collider box check
namespace Collision {

	bool CollisionCheck(const BCircle& circle, const Vector3& point);
	bool CollisionCheck(const BBox& box, const Vector3& point);
	bool CollisionCheck(const BPolygon& polygon, const Vector3& point);

	bool CollisionCheck(const BCircle& circleA, const BCircle& circleB);
	bool CollisionCheck(const BBox& boxA, const BBox& boxB);
	bool CollisionCheck(const BPolygon& polygonA, const BPolygon& polygonB);

	bool BCircleVsBCircle(const BCircle& circleA, const BCircle& circleB);
	bool BCircleVsPoint(const BCircle& circle, const Vector3& point);

	bool BBoxOverlaps(const BBox& boxA, const BBox& boxB);
	bool BBoxVsBBox(const BBox& boxA, const BBox& boxB);
	bool BBoxVsPoint(const BBox& box, const Vector3& point);

	bool BPolygonOverlaps(const BPolygon& polygonA, const BPolygon& polygonB);
	bool BPolygonVsBPolygon(const BPolygon& polygonA, const BPolygon& polygonB);
	bool BOBBOverlaps(const BPolygon& obbA, const BPolygon& obbB);
	bool BOBBVsBOBB(const BPolygon& obbA, const BPolygon& obbB);
	bool BPolygonVsPoint(const BPolygon& polygon, const Vector3& point);
	bool BOBBVsPoint(const BPolygon& obb, const Vector3& point);


	bool BCircleVsBBox(const BCircle& circle, const BBox& box);
	
};



////////////////////////////////////

void BOX_BOX_CollisionCR(Collider2D* colliderA,
	TransformComponent* transformA,
	RigidBody2DComponent* rigidbodyA,
	Collider2D* colliderB,
	TransformComponent* transformB,
	RigidBody2DComponent* rigidbodyB,
	double dt);

void CIRCLE_CIRCLE_CollisionCR(Collider2D* colliderA,
	TransformComponent* transformA,
	RigidBody2DComponent* rigidbodyA,
	Collider2D* colliderB,
	TransformComponent* transformB,
	RigidBody2DComponent* rigidbodyB,
	double dt);

void CIRCLE_BOX_CollisionCR(Collider2D* colliderA,
	TransformComponent* transformA,
	RigidBody2DComponent* rigidbodyA,
	Collider2D* colliderB,
	TransformComponent* transformB,
	RigidBody2DComponent* rigidbodyB,
	double dt);

void CIRCLE_EDGE_CollisionCR(Collider2D* colliderA,
	TransformComponent* transformA,
	RigidBody2DComponent* rigidbodyA,
	Collider2D* colliderB,
	double dt);

void BOX_EDGE_CollisionCR(Collider2D* colliderA,
	TransformComponent* transformA,
	RigidBody2DComponent* rigidbodyA,
	Collider2D* colliderB,
	double dt);


///////////////////////////////////////////////////////////////////////////////
	//Dynamic Collision Check

int BoxBox_Intersection(const BoxCollider2DComponent& boxA,
	const Vector3& velA,
	const BoxCollider2DComponent& boxB,
	const Vector3& velB,
	Vector3& interPtA,
	Vector3& interPtB,
	float& interTime);

int BoxEdge_Intersection(const BoxCollider2DComponent& circle,
	const Vector3& ptEnd,
	const EdgeCollider2DComponent& lineSeg,
	Vector3& interPt,
	Vector3& normalAtCollision,
	float& interTime,
	bool& checkLineEdges);

int BoxLine_Intersection(bool withinBothLines,
	const BoxCollider2DComponent& circle,
	const Vector3& ptEnd,
	const EdgeCollider2DComponent& lineSeg,
	Vector3& interPt,
	Vector3& normalAtCollision,
	float& interTime);

int CircleCircle_Intersection(const CircleCollider2DComponent& circleA,
	const Vector3& velA,
	const CircleCollider2DComponent& circleB,
	const Vector3& velB,
	Vector3& interPtA,
	Vector3& interPtB,
	float& interTime);

int CircleEdge_Intersection(const CircleCollider2DComponent& circle,
	const Vector3& ptEnd,
	const EdgeCollider2DComponent& lineSeg,
	Vector3& interPt,
	Vector3& normalAtCollision,
	float& interTime,
	bool& checkLineEdges);


int CircleLine_Intersection(bool withinBothLines,
	const CircleCollider2DComponent& circle,
	const Vector3& ptEnd,
	const EdgeCollider2DComponent& lineSeg,
	Vector3& interPt,
	Vector3& normalAtCollision,
	float& interTime);

//int RayBox_Intersection(const Ray& ray,
//	const BoxCollider2DComponent& circle,
//	float& interTime);

/*int RayCircle_Intersection(const Ray& ray,
	const CircleCollider2DComponent& circle,
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

int CircleBox_Intersection(const CircleCollider2DComponent& boxA,
	const Vector3& velA,
	const BoxCollider2DComponent& circleB,
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

bool TestAABBVsPoint(const BoxCollider2DComponent& aabb, const Vector3& pt);
bool TestAABBVsAABB(const BoxCollider2DComponent& aabb1, const BoxCollider2DComponent& aabb2);
bool TestOBBVsPoint(const BoxCollider2DComponent& obb, const Vector3& pt);
bool TestOBBVsOBB(const BoxCollider2DComponent& obb1, const BoxCollider2DComponent& obb2);
bool TestOverlaps(const BoxCollider2DComponent& obb1, const BoxCollider2DComponent& obb2);

bool TestBoxVsPoint(const BoxCollider2DComponent& box, const Vector3& pt);
bool TestBoxVsBox(const BoxCollider2DComponent& box1, const BoxCollider2DComponent& box2);
int TestOutCode(const BoxCollider2DComponent& box, const Vector3& pt);

bool TestCircleVsPoint(const CircleCollider2DComponent& circle, const Vector3& pt);
bool TestCircleVsCircle(const CircleCollider2DComponent& circle1, const CircleCollider2DComponent& circle2);

bool TestCircleVsBox(const CircleCollider2DComponent& circle, const BoxCollider2DComponent& box);
bool TestCircleVsAABB(const CircleCollider2DComponent& circle, const BoxCollider2DComponent& aabb);
bool TestCircleVsOBB(const CircleCollider2DComponent& circle, const BoxCollider2DComponent& oobb);

bool TestCircleVsEdge(const CircleCollider2DComponent& circle, const EdgeCollider2DComponent& edge);
bool TestBoxVsEdge(const BoxCollider2DComponent& box, const EdgeCollider2DComponent& edge);
bool TestAABBVsEdge(const BoxCollider2DComponent& obb, const EdgeCollider2DComponent& edge);
bool TestOBBVsEdge(const BoxCollider2DComponent& aabb, const EdgeCollider2DComponent& edge);
#endif