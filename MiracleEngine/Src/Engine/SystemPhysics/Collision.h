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

struct CollisionData {
	Vector3 posNextA;
	Vector3 posNextB;
	Vector3 velA;
	Vector3 velB;
	Vector3 interPtA;
	Vector3 interPtB;
	Vector3 reflectedVecA;
	Vector3 reflectedVecB;
	Vector3 normal;
	float massA;
	float massB;
	float interTime;
	

	CollisionData() :
		posNextA{},
		posNextB{},
		velA{},
		velB{},
		interPtA{},
		interPtB{},
		reflectedVecA{},
		reflectedVecB{},
		normal{},
		massA{ 1.f },
		massB{ 1.f },
		interTime{ 0.f }
	{}
};


//////////////////////////////////

void BoxVsBoxCollisionUpdate(Collider2D* boxA, Collider2D* boxB, double dt);
void CircleVsCircleCollisionUpdate(Collider2D* circleA, Collider2D* circleB, double dt);
void CircleVsBoxCollisionUpdate(Collider2D* circle, Collider2D* box, double dt);
void CircleVsEdgeCollisionUpdate(Collider2D* circle, Collider2D* edge, double dt);
void BoxVsEdgeCollisionUpdate(Collider2D* box, Collider2D* edge, double dt);


////////////////////////////////// Static

namespace Collision {

	// vs point
	bool CollisionCheck(const BCircle& circle, const Vector3& point);
	bool CollisionCheck(const BBox& box, const Vector3& point);
	bool CollisionCheck(const BPolygon& polygon, const Vector3& point);

	// vs each other
	bool CollisionCheck(const BCircle& circleA, const BCircle& circleB);
	bool CollisionCheck(const BCircle& circle, const BBox& box);
	bool CollisionCheck(const BBox& boxA, const BBox& boxB);
	bool CollisionCheck(const BPolygon& polygonA, const BPolygon& polygonB);
	bool CollisionCheck(const BPolygon& polygon, const BCircle& circle);

	// circle function
	bool BCircleVsBCircle(const BCircle& circleA, const BCircle& circleB);
	bool BCircleVsPoint(const BCircle& circle, const Vector3& point);
	bool BCircleVsBBox(const BCircle& circle, const BBox& box);
	bool BCircleVsBPolygon(const BCircle& circle, const BPolygon& polygon);

	// AABB box function
	bool BBoxOverlaps(const BBox& boxA, const BBox& boxB);
	bool BBoxVsBBox(const BBox& boxA, const BBox& boxB);
	bool BBoxVsPoint(const BBox& box, const Vector3& point);

	// OBB box function
	bool BOBBOverlaps(const BPolygon& obbA, const BPolygon& obbB);
	bool BOBBVsBOBB(const BPolygon& obbA, const BPolygon& obbB);
	bool BOBBVsPoint(const BPolygon& obb, const Vector3& point);

	// Polygon function
	bool BPolygonOverlaps(const BPolygon& polygonA, const BPolygon& polygonB);
	bool BPolygonVsBPolygon(const BPolygon& polygonA, const BPolygon& polygonB);
	bool BPolygonVsPoint(const BPolygon& polygon, const Vector3& point);

	// Edge Function

	bool BEdgeVSBCircle(const BEdge& edge, const BCircle& circle);
	bool BEdgeVSBOBB(const BEdge& edge, const BPolygon& obb);
};

////////////////////////////////// Dynamic

bool BoxVsBoxIntersection(BoxCollider2DComponent* boxA, BoxCollider2DComponent* boxB, CollisionData& data);
bool CircleVsCircleIntersection(CircleCollider2DComponent* circleA, CircleCollider2DComponent* circleB, CollisionData& data);
bool CircleVsBoxIntersection(CircleCollider2DComponent* circle, BoxCollider2DComponent* box, CollisionData& data);
bool CircleVsEdgeIntersection(CircleCollider2DComponent* circle, EdgeCollider2DComponent* edge, CollisionData& data);
bool BoxVsEdgeIntersection(BoxCollider2DComponent* box, EdgeCollider2DComponent* edge, CollisionData& data);

#endif