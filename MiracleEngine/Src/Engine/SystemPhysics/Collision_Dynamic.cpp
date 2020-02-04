#include "PrecompiledHeaders.h"
#include "Collision.h"

bool BoxVsBoxIntersection(BoxCollider2DComponent* boxA, BoxCollider2DComponent* boxB, CollisionData& data)
{
	return false;
}

bool CircleVsCircleIntersection(CircleCollider2DComponent* circleA, CircleCollider2DComponent* circleB, CollisionData& data)
{
	return false;
}

bool CircleVsBoxIntersection(CircleCollider2DComponent* circle, BoxCollider2DComponent* box, CollisionData& data)
{
	return false;
}

bool CircleVsEdgeIntersection(CircleCollider2DComponent* circle, EdgeCollider2DComponent* edge, CollisionData& data)
{
	return false;
}

bool BoxVsEdgeIntersection(BoxCollider2DComponent* box, EdgeCollider2DComponent* edge, CollisionData& data)
{
	return false;
}
