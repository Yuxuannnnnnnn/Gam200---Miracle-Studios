#pragma once
#include "Tools/MathLib/Math.h"
#include "BoundingBox.h"
#include "BoundingEdge.h"

typedef struct BoundingPolygon
{
	BBox _AABB;

	int _numPoints;
	Vector3* _pointArray;
	BEdge*	_ptrEdgeArray;

	bool _obbBox; // use from AABB/OBB box, easy checking for coliision and creating

	BoundingPolygon();
	BoundingPolygon(Vector3* points, int numPoints);

	BoundingPolygon(const BoundingPolygon& rhs);

	BoundingPolygon& operator=(const BoundingPolygon& rhs);

	~BoundingPolygon();

	// create a OBB box if rotated
	static BoundingPolygon CreateBoxPolygon(const Vec3& position, const Vec3& scale, const float& rotationAngle);

}BPolygon;

///*
//
//inline bool ClockwiseOrderVertices(const Vertex2D& v0, const Vertex2D& v1, const Vertex2D& v2)
//{
//	// Compute correct order of vertices
//	// Compute area S to find the ordering of triangle vertices (using coefficients)
//	float C0 = v1.GetPosition().GetX() * v0.GetPosition().GetY() - v2.GetPosition().GetX() * v0.GetPosition().GetY();
//	float C1 = v2.GetPosition().GetX() * v1.GetPosition().GetY() - v0.GetPosition().GetX() * v1.GetPosition().GetY();
//	float C2 = v0.GetPosition().GetX() * v2.GetPosition().GetY() - v1.GetPosition().GetX() * v2.GetPosition().GetY();
//	float S = (-C0 - C1 - C2) / 2;
//
//	if (S > 0)
//		return true;
//
//	return false;
//}
//
//bool Triangle::IsCounterClockwise() const
//{
//	// @TODO: Return true if triangle is counter-clockwise oriented, false otherwise
//	// Compute correct order of vertices
//
//	// check for Clockwise
//	if (ClockwiseOrderVertices(mVertex[0], mVertex[1], mVertex[2]) == true)
//		return false;
//
//	return true;
//}
//
//bool PolygonalPillar::IsConvex() const
//{
//	// @TODO: Return true if polygon is convex, false otherwise
//	// Ensure that vertices are counter-clockwise oriented
//	if (!Triangle(mPtrVertexArray[0], mPtrVertexArray[1], mPtrVertexArray[2]).IsCounterClockwise())
//		return false;
//
//	bool convex = false;
//
//	for (int i = 0; i < mVertexCount; ++i)
//	{
//		Vector2D d1, d2;
//
//		if (i == (mVertexCount - 1))
//		{
//			d1 = mPtrVertexArray[0].GetPosition() - mPtrVertexArray[i].GetPosition();
//			d2 = mPtrVertexArray[1].GetPosition() - mPtrVertexArray[0].GetPosition();
//		}
//		else if (i == (mVertexCount - 2))
//		{
//			d1 = mPtrVertexArray[i + 1].GetPosition() - mPtrVertexArray[i].GetPosition();
//			d2 = mPtrVertexArray[0].GetPosition() - mPtrVertexArray[i + 1].GetPosition();
//		}
//		else
//		{
//			d1 = mPtrVertexArray[i + 1].GetPosition() - mPtrVertexArray[i].GetPosition();
//			d2 = mPtrVertexArray[i + 2].GetPosition() - mPtrVertexArray[i + 1].GetPosition();
//		}
//
//		float C = d1.GetX() * d2.GetY() - d1.GetY() * d2.GetX();
//
//		if (C >= 0)
//		{
//			if (i == 0) convex = true;
//			else if (!convex) return false;
//		}
//		else
//		{
//			if (i == 0) convex = false;
//			else if (convex) return false;
//		}
//	}
//	return true;
//}
//
//
//////////////////////////////////////////////////////////////////////////////////
///*!
//	@brief  Intersection test between an arbitrary point and counter-clockwise
//			oriented convex polygon.
//	@param	const Point2D& pt
//			Arbitrary point
//	@return	true if point is inside, that is, either in the interior or on
//			the convex polygon boundary; false otherwise
//*/
//////////////////////////////////////////////////////////////////////////////////
//bool PolygonalPillar::TestPillarVsPoint(const Point2D& pt) const
//{
//	// @TODO: Return true if point pt is in counter-clockwise oriented polygon;
//	// false otherwise
//	for (int i = 0; i < mVertexCount; ++i)
//	{
//		if (((pt - mPtrEdgeArray[i].GetStartPoint()) * mPtrEdgeArray[i].GetNml()) > 0)
//			return false;
//	}
//	return true;
//}
//
//////////////////////////////////////////////////////////////////////////////////
///*!
//	@brief  BC vs. convex polygon pillar (PP) test
//			The test proceeds in this manner:
//			for each edge E of PP
//				if BC contains either start or end point of E, there is intersection
//				otherwise if BC is in outside half-plane of E, there is no intersection
//				otherwise if BC is in inside half-plane of E, continue to next edge
//				otherwise if BC is intersected by (finite) E, there is intersection
//			if BC is in inside half-plane of all edges of PP, there is intersection
//			otherwise, there is no intersection
//
//			Or see page 7 from lecture notes
//	@param	const AABB& aabb
//			AABB to be tested against BC bc
//	@param	const BC& bc
//			BC to be tested against AABB
//	@return	bool
//			True if BC is intersecting with AABB; false otherwise
//*/
//////////////////////////////////////////////////////////////////////////////////
//bool PolygonalPillar::TestPillarVsBC(const BC& bc) const
//{
//	// @TODO: BC vs. convex polygon test.
//	// See notes in function header for additional information
//	if (TestPillarVsPoint(bc.mCenPos))
//		return true;
//
//	for (int i = 0; i < mVertexCount; ++i)
//	{
//		if (distance(mPtrEdgeArray[i].GetStartPoint(), mPtrEdgeArray[i].GetEndPoint(), bc.mCenPos) <= bc.mRadius)
//			return true;
//	}
//
//	return false;
//}
//
//////////////////////////////////////////////////////////////////////////////////
///*!
//	@brief  Since this function is a member of class PolygonalPillar, the
//			BC, AABB, and individual edges of the convex polygonal pillar (PP)
//			are used in the following hierarchical intersection tests. Note
//			that in this application, there are two types of pillars: circular
//			and polygonal. Also note that each pillar type uses both a BC and an
//			AABB. The hierarchical tests are performed as follows: First,
//			BC vs. BC test is performed. If it fails, there is no intersection.
//			If the pillar pointed to by parameter ps is a circular pillar (CP),
//			AABB (of PP) vs. BC (of CP) test is performed. If there
//			is no intersection, testing concludes and we are done. However,
//			if there is an intersection, the individual edges of PP are tested
//			against BC of CP.
//			On the other hand, if the pillar pointed to by parameter ps
//			is also a PP, AABB vs. AABB test is performed.
//			If there is an intersection, the more refined Separation Axis Theorem
//			test is performed between the two PPs.
//	@param	const Pillar *ps
//			Run-time type identification allows ps to point to either a
//			CircularPillar or PolygonalPillar object
//	@return	bool
//			True if polygonal pillar pointed to by the this pointer
//			is intersecting with pillar pointed to by argument ps; false otherwise
//*/
//////////////////////////////////////////////////////////////////////////////////
//bool PolygonalPillar::TestPillar(const Pillar* ps) const
//{
//	// @TODO: Hierarchical intersection tests between polygonal pillar 
//	// and other circular and polygonal pillars in the following order:
//	// 1. this->BC vs. ps->BC
//	// this->BC refers to the BC of object invoking this virtual function
//	// which we know is a polygonal pillar.
//	// ps->BC refers to the BC of the object pointed to by parameter ps
//	// may be pointing to either a circular or polygonal pillar. The correct
//	// object is resolved using runtime type identification by C++
//	// If this test fails, we are done - there is no collision
//	// otherwise, there may be a collision
//	BC	bc = this->GetBC();
//	if (bc.TestBCvsBC(ps->GetBC()) == false)
//		return false;
//
//	// 2. Next, perform this->BC vs. ps->AABB test
//	if (CS200::TestBCVsAABB(this->GetBC(), ps->GetAABB()) == false)
//		return false;
//
//	// 3. If test 2 fails, again there may or may not be an intersection.
//	// Perform this->AABB vs. ps->AABB test
//	AABB	aabb = this->GetAABB();
//	if (aabb.TestAABBVsAABB(ps->GetAABB()) == false)
//		return false;
//
//	// 4. If test 3 fails, perform this->polygon vs. ps->BC test
//	// only if the object is a circular pillar
//	if (const CircularPillar* pcp = dynamic_cast<const CircularPillar*>(ps))
//		return TestPillarVsBC(pcp->GetBC());
//
//	// 5. If test 4 fails, perform this->pillar vs. ps->pillar test
//	if (const PolygonalPillar* ppp = dynamic_cast<const PolygonalPillar*>(ps))
//		return ppp->TestPillarVsPP(*this);
//
//	return false;
//}
//

//////////////////////////////////////////////////////////////////////////////////
///*!
//	@brief  BC vs. AABB test
//
//	@param	const BC& bc
//			BC to be tested against AABB
//	@param	const AABB& aabb
//			AABB to be tested against BC bc
//	@return	bool
//			True if BC is intersecting with AABB; false otherwise
//	@Notes	This a friend function to classes CS200::BC and CS200::AABB
//*/
//////////////////////////////////////////////////////////////////////////////////
//bool TestBCVsAABB(const BC& bc, const AABB& aabb)
//{
//	// @TODO: Return true if BC bc is intersecting with AABB aabb;
//	// otherwise return false.
//	AABB box = aabb;
//
//	if (box.TestAABBVsPoint(bc.mCenPos))
//		return true;
//
//	if (distance(aabb.mMinPos, Point2D(aabb.mMinPos.GetX(), aabb.mMaxPos.GetY()), bc.mCenPos) <= bc.mRadius ||
//		distance(Point2D(aabb.mMinPos.GetX(), aabb.mMaxPos.GetY()), aabb.mMaxPos, bc.mCenPos) <= bc.mRadius ||
//		distance(aabb.mMaxPos, Point2D(aabb.mMaxPos.GetX(), aabb.mMinPos.GetY()), bc.mCenPos) <= bc.mRadius ||
//		distance(Point2D(aabb.mMaxPos.GetX(), aabb.mMinPos.GetY()), aabb.mMinPos, bc.mCenPos) <= bc.mRadius)
//		return true;
//
//	return false;
//}
//


//*/