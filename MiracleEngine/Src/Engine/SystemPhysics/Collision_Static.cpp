#include "PrecompiledHeaders.h"
#include "Collision.h"

// For new collider box check
namespace Collision {

	bool CollisionCheck(const BCircle& circle, const Vector3& point)
	{
		return BCircleVsPoint(circle, point);
	}

	bool CollisionCheck(const BBox& box, const Vector3& point)
	{
		if (!CollisionCheck(box._BC, point))
			return false;

		return BBoxVsPoint(box, point);
	}

	bool CollisionCheck(const BPolygon& polygon, const Vector3& point)
	{
		if (!CollisionCheck(polygon._AABB, point))
			return false;

		if (polygon._obbBox)
			return BOBBVsPoint(polygon, point);
		else
			return BPolygonVsPoint(polygon, point);

		return true;
	}

	bool CollisionCheck(const BCircle& circleA, const BCircle& circleB)
	{
		return BCircleVsBCircle(circleA, circleB);
	}

	bool CollisionCheck(const BCircle& circle, const BBox& box)
	{
		//first check circle collision
		if (!CollisionCheck(circle, box._BC))
			return false;

		return BCircleVsBBox(circle, box);
	}

	bool CollisionCheck(const BBox& boxA, const BBox& boxB)
	{
		if (!CollisionCheck(boxA._BC, boxB))
			return false;

		//then continue the Box collision check (SAT)
		return BBoxVsBBox(boxA, boxB);
	}

	bool CollisionCheck(const BPolygon& polygonA, const BPolygon& polygonB)
	{
		if (!CollisionCheck(polygonA._AABB, polygonB._AABB))
			return false;

		if (polygonA._obbBox && polygonB._obbBox)
			return BOBBVsBOBB(polygonA, polygonB);
		else
			return BPolygonVsBPolygon(polygonA, polygonB);

		return true;
	}

	bool CollisionCheck(const BPolygon& polygon, const BCircle& circle)
	{
		if (!CollisionCheck(circle, polygon._AABB))
			return false;

		return BCircleVsBPolygon(circle, polygon);
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool BCircleVsBCircle(const BCircle& circleA, const BCircle& circleB)
	{
		return (circleA._center.Distance(circleB._center) <= (circleA._radius + circleB._radius));
	}

	bool BCircleVsPoint(const BCircle& circle, const Vector3& point)
	{
		return (point.Distance(circle._center) <= circle._radius);
	}

	bool BCircleVsBPolygon(const BCircle& circle, const BPolygon& polygon)
	{
		if (BPolygonVsPoint(polygon, circle._center))
			return true;

		for (int n = 0; n < polygon._numPoints; n++)
		{
			if (BEdgeVSBCircle(polygon._ptrEdgeArray[n], circle))
				return true;
		}

		return false;
	}

	bool BBoxOverlaps(const BBox& boxA, const BBox& boxB)
	{
		if (boxA._maxPoint._x < boxB._minPoint._x || boxA._maxPoint._y < boxB._minPoint._y ||
			boxA._minPoint._x > boxB._maxPoint._x || boxA._minPoint._y > boxB._maxPoint._y)
			return false;

		return true;
	}

	bool BBoxVsBBox(const BBox& boxA, const BBox& boxB)
	{
		return BBoxOverlaps(boxA, boxB);// && BBoxOverlaps(boxB, boxA);
	}

	bool BBoxVsPoint(const BBox& box, const Vector3& point)
	{
		return (point._x > box._minPoint._x&& point._x  < box._maxPoint._x &&
			point._y  > box._minPoint._y&& point._y < box._maxPoint._y);
	}


	bool BPolygonOverlaps(const BPolygon& polygonA, const BPolygon& polygonB)
	{

		for (int n = 0; n < polygonA._numPoints; n++)
		{
			float minA, maxA, minB, maxB;
			minA = maxA = maxB = minB = 0.f;

			Vec3 normal = polygonA._ptrEdgeArray[n]._normalVec;

			BPolygonProjInterval(polygonA, normal, minA, maxA);
			BPolygonProjInterval(polygonB, normal, minB, maxB);

			if (minA > maxB || maxA < minB)
				return false;
		}

		return true;
	}


	void BPolygonProjInterval(const BPolygon& polygon, const Vector3& normal, float& min, float& max)
	{
		min = max = normal.Dot(polygon._pointArray[0]);

		for (int n = 1; n < polygon._numPoints; n++)
		{
			float t = normal.Dot(polygon._pointArray[n]);

			if (t < min)
				min = t;
			else if (t > max)
				max = t;
		}
	}

	bool BPolygonVsBPolygon(const BPolygon& polygonA, const BPolygon& polygonB)
	{
		return BPolygonOverlaps(polygonA, polygonB) && BPolygonOverlaps(polygonB, polygonA);
	}

	bool BOBBOverlaps(const BPolygon& obbA, const BPolygon& obbB)
	{
		//check with asix of the box

		for (int a = 0; a < 2; ++a)
		{
			Vector3 normal = obbA._ptrEdgeArray[a]._normalVec * obbA._ptrEdgeArray[a]._orthoDistance;
			float det = normal.Dot(normal);
			Vector3 vec = obbB._AABB._BC._center - obbA._AABB._BC._center;
			float t = vec.Dot(normal) / det;

			// Find the extent of boxB on boxA's axis x
			float tMin = t;
			float tMax = t;

			for (int c = 0; c < 4; ++c) {
				Vector3 vec2 = obbB._pointArray[c];

				vec = vec2 - obbA._AABB._BC._center;
				t = vec.Dot(normal) / det;

				if (t < tMin) {
					tMin = t;
				}
				else if (t > tMax) {
					tMax = t;
				}
			}

			// See if [tMin, tMax] intersects [-1, 1]
			if (tMin > 1.f || tMax < -1.f) {
				// There was no intersection along this dimension;
				// the boxes cannot possibly overlap.
				return false;
			}
		}

		// There was no dimension along which there has no intersection.
		// Therefore the boxes overlap.
		return true;
	}

	bool BOBBVsBOBB(const BPolygon& obbA, const BPolygon& obbB)
	{
		return BOBBOverlaps(obbA, obbB) && BOBBOverlaps(obbB, obbA);
	}

	bool BPolygonVsPoint(const BPolygon& polygon, const Vector3& point)
	{
		// just with all the normal of the edges

		for (int n = 0; n < polygon._numPoints; ++n)
		{
			Vector3 vec = point - polygon._pointArray[n];

			float t = vec.Dot(polygon._ptrEdgeArray[n]._normalVec);

			if (t > 0)
				return false;
		}

		// point lie inside or on the edge of the polygon
		return true;
	}

	bool BOBBVsPoint(const BPolygon& obb, const Vector3& point)
	{
		// just check with axis

		Vector3 vec = point - obb._AABB._BC._center;

		for (int a = 0; a < 2; ++a)
		{
			Vector3 normal = obb._ptrEdgeArray[a]._normalVec * obb._ptrEdgeArray[a]._orthoDistance;
			float det = normal.Dot(normal);
			float t = vec.Dot(normal) / det;


			// See if [tMin, tMax] intersects [-1, 1]
			if (t > 1.f || t < -1.f) {
				// There was no intersection along this dimension;
				// the boxes cannot possibly overlap.
				return false;
			}
		}

		return true;
	}

	bool BCircleVsBBox(const BCircle& circle, const BBox& box)
	{
		if (BBoxVsPoint(box, circle._center))
			return true;

		if (Vec3Distance_LinetoPoint(box._minPoint, Vec3{ box._minPoint._x, box._maxPoint._y, 1.f}, circle._center) <= circle._radius ||
			Vec3Distance_LinetoPoint(box._minPoint, Vec3{ box._maxPoint._x, box._minPoint._y, 1.f }, circle._center) <= circle._radius ||
			Vec3Distance_LinetoPoint(box._maxPoint, Vec3{ box._minPoint._x, box._maxPoint._y, 1.f }, circle._center) <= circle._radius ||
			Vec3Distance_LinetoPoint(box._maxPoint, Vec3{ box._maxPoint._x, box._minPoint._y, 1.f }, circle._center) <= circle._radius)
			return true;

		return false;
	}

	bool BEdgeVSBCircle(const BEdge& edge, const BCircle& circle)
	{
		if (Vec3Distance_LinetoPoint(edge._startPoint, edge._endPoint, circle._center) <= circle._radius)
			return true;

		return false;
	}

	bool BEdgeVSBPolygon(const BEdge& edge, const BPolygon& obb)
	{
		{
			Vector3 normal = edge._normalVec;
			float det = normal.Dot(normal);
			Vector3 vec = obb._pointArray[0] - edge._centerPoint;
			float t = vec.Dot(normal) / det;

			// Find the extent of boxB on boxA's axis x
			float tMin = t;
			float tMax = t;

			for (int c = 1; c < obb._numPoints; ++c) {
				Vector3 vec2 = obb._pointArray[c];

				vec = vec2 - edge._centerPoint;
				t = vec.Dot(normal) / det;

				if (t < tMin) {
					tMin = t;
				}
				else if (t > tMax) {
					tMax = t;
				}
			}

			// See if [tMin, tMax] intersects [-1, 1]
			if (tMin > 1.f || tMax < -1.f) {
				// There was no intersection along this dimension;
				// the boxes cannot possibly overlap.
				return false;
			}
		}
		{
			Vector3 normal = edge._startPoint - edge._centerPoint;
			float det = normal.Dot(normal);
			Vector3 vec = obb._pointArray[0] - edge._centerPoint;
			float t = vec.Dot(normal) / det;

			// Find the extent of boxB on boxA's axis x
			float tMin = t;
			float tMax = t;

			for (int c = 1; c < obb._numPoints; ++c) {
				Vector3 vec2 = obb._pointArray[c];

				vec = vec2 - edge._centerPoint;
				t = vec.Dot(normal) / det;

				if (t < tMin) {
					tMin = t;
				}
				else if (t > tMax) {
					tMax = t;
				}
			}

			// See if [tMin, tMax] intersects [-1, 1]
			if (tMin > 1.f || tMax < -1.f) {
				// There was no intersection along this dimension;
				// the boxes cannot possibly overlap.
				return false;
			}
		}

		// There was no dimension along which there has no intersection.
		// Therefore the boxes overlap.
		return true;
	}
		
};