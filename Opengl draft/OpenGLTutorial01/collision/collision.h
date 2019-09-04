#pragma once
#include <algorithm>
#include"../GameObject.h"

bool CollisionIntersection_RectRect(const AABB& aabb1, const Vec2& vel1,
	const AABB& aabb2, const Vec2& vel2);