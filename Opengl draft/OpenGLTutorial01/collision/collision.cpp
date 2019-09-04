#include "collision.h"
float g_dt = 1.0f / 60;

bool CollisionIntersection_RectRect(const AABB& aabb1, const Vec2& vel1,
	const AABB& aabb2, const Vec2& vel2)
{
	float tFirst_x = 0;
	float tFirst_y = 0;
	// get dt
	float tLast_x = g_dt;
	float tLast_y = g_dt;

	float dFirst, dLast;
	Vec2 vRel = { vel2._x - vel1._x, vel2._y - vel1._y };

	/*
	Implement the collision intersection over here.

	The steps are:
	Step 1: Check for collision detection between rectangles (assuMing static here).
			If the check returns no overlap you continue with the following steps.
	*/

	if (aabb1.max._x < aabb2.min._x || aabb1.min._x > aabb2.max._x)
		return 0;

	if (aabb1.max._y < aabb2.min._y || aabb1.min._y > aabb2.max._y)
		return 0;

	/*
	Step 2: Initialize and calculate the new velocity of Vb
			tFirst = 0
			tLast = dt
	*/

	/*

	Step 3: Working with one dimension (x-axis).
			if(Vb < 0)
				case 1
				case 4
			if(Vb > 0)
				case 2
				case 3

			case 5
	*/


	/* if relative velocity is 0, both object is not moving.
		therefore dont need to calculate tFirst and tLast in the case
	*/

	if (vRel._x < 0)
	{
		if (aabb1.min._x > aabb2.max._x)         // case 1
			return 0;

		else if (aabb1.max._x < aabb2.min._x)             // case 4 revisit
		{
			tFirst_x = std::max((aabb1.max._x - aabb2.min._x) / vRel._x, tFirst_x);
		}

		if (aabb1.min._x < aabb2.max._x)
		{
			tLast_x = std::min((aabb1.min._x - aabb2.max._x) / vRel._x, tLast_x);
		}

	}
	else if (vRel._x > 0)
	{
		if (aabb1.max._x < aabb2.min._x)
			return 0;

		else if (aabb1.min._x > aabb2.max._x)             // case 2 revisit
		{
			tFirst_x = std::max((aabb1.min._x - aabb2.max._x) / vRel._x, tFirst_x);
		}

		if (aabb1.max._x > aabb2.min._x)
		{
			tLast_x = std::min((aabb1.max._x - aabb2.min._x) / vRel._x, tLast_x);
		}
	}

	if (tFirst_x > tLast_x)
		return 0;
	/*
	Step 4: Repeat step 3 on the y-axis
	*/

	if (vRel._y < 0)
	{
		if (aabb1.min._y > aabb2.max._y)            // case 1
			return 0;

		else if (aabb1.max._y < aabb2.min._y)             // case 4 revisit
		{
			tFirst_y = std::max((aabb1.max._y - aabb2.min._y) / vRel._y, tFirst_y);
		}

		if (aabb1.min._y < aabb2.max._y)
		{
			tLast_y = std::min((aabb1.min._y - aabb2.max._y) / vRel._y, tLast_y);
		}

	}
	else if (vRel._y > 0)
	{
		if (aabb1.max._y < aabb2.min._y)
			return 0;

		else if (aabb1.min._y > aabb2.max._y)             // case 2 revisit
		{
			tFirst_y = std::max((aabb1.min._y - aabb2.max._y) / vRel._y, tFirst_y);
		}

		if (aabb1.max._y > aabb2.min._y)
		{
			tLast_y = std::min((aabb1.max._y - aabb2.min._y) / vRel._y, tLast_y);
		}
	}
	/*
	Step 5: Otherwise the rectangles intersect

	*/
	if (tFirst_y > tLast_y)
		return 0;

	return 1;
}