//
//	BoxCollider2D.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#include "BoxCollider2D.h"
#include "GraphicsSystem/DebugRenderer.h"

BoxCollider2D::BoxCollider2D() : 
	mMinPos{}, 
	mMaxPos{}, 
	mCorner{ {},{},{},{} }, 
	mAxis{ {},{} },
	mOrigin{},
	mAngle{ 0.f }
{
}

void BoxCollider2D::update() {

	//Get bounding rec
	Vector3 boundingBox_offset = { -0.5f * _gameObject->_scale._x, -0.5f * _gameObject->_scale._y };

	//Cal boundingRect minimum point
	mMinPos = _gameObject->_pos - (-boundingBox_offset);

	//boundingRect maximum point
	mMaxPos = _gameObject->_pos - boundingBox_offset;

	mAngle = _gameObject->_angle;

	Vector3 X(cos(mAngle), sin(mAngle));
	Vector3 Y(-sin(mAngle), cos(mAngle));

	X = X * _gameObject->_scale._x / 2;
	Y = Y * _gameObject->_scale._y / 2;

	mCorner[0] = _gameObject->_pos - X - Y;
	mCorner[1] = _gameObject->_pos + X - Y;
	mCorner[2] = _gameObject->_pos + X + Y;
	mCorner[3] = _gameObject->_pos - X + Y;

	ComputeAxes();

	mOrigin = _gameObject->_pos;
}

BoxCollider2D::BoxCollider2D(const Vector3& cenPos, const Vector3& scale,float angle)
{
	//Get bounding rec
	Vector3 boundingBox_offset = { -0.5f * scale._x, -0.5f * scale._y };

	//Cal boundingRect minimum point
	mMinPos = cenPos - (-boundingBox_offset);

	//boundingRect maximum point
	mMaxPos = cenPos - boundingBox_offset;

	Vector3 X(cos(angle), sin(angle));
	Vector3 Y(-sin(angle), cos(angle));

	X = X * scale._x / 2;
	Y = Y * scale._y / 2;

	mCorner[0] = cenPos - X - Y;
	mCorner[1] = cenPos + X - Y;
	mCorner[2] = cenPos + X + Y;
	mCorner[3] = cenPos - X + Y;

	ComputeAxes();

	mAngle = angle;

	mOrigin = cenPos;
}


BoxCollider2D::BoxCollider2D(const BoxCollider2D& _bc) :
	mMinPos(_bc.mMinPos), 
	mMaxPos(_bc.mMaxPos),
	mOrigin(_bc.mOrigin),
	mAngle(_bc.mAngle)
{
	for (int c = 0; c < 4; ++c)
		mCorner[c] = _bc.mCorner[c];

	for (int a = 0; a < 2; ++a)
		mAxis[a] = _bc.mAxis[a];
}

void BoxCollider2D::Update(const Vector3& cenPos, const Vector3& scale, float angle)
{
	//Get bounding rec
	Vector3 boundingBox_offset = { -0.5f * scale._x, -0.5f * scale._y };

	//Cal boundingRect minimum point
	mMinPos = cenPos - (-boundingBox_offset);

	//boundingRect maximum point
	mMaxPos = cenPos - boundingBox_offset;

	if (mAngle != angle)
	{
		Vector3 X(cos(angle), sin(angle));
		Vector3 Y(-sin(angle), cos(angle));

		X = X * scale._x / 2;
		Y = Y * scale._y / 2;

		mCorner[0] = cenPos - X - Y;
		mCorner[1] = cenPos + X - Y;
		mCorner[2] = cenPos + X + Y;
		mCorner[3] = cenPos - X + Y;
	}
	else
	{
		Vector3 oldCenter = (mCorner[0] + mCorner[1] + mCorner[2] + mCorner[3]) / 4;

		Vector3 translation = cenPos - oldCenter;

		for (int c = 0; c < 4; ++c) {
			mCorner[c] += translation;
		}
	}

	ComputeAxes();

	mAngle = angle;

	mOrigin = cenPos;
}

void BoxCollider2D::ComputeAxes() {
	mAxis[0] = mCorner[1] - mCorner[0];
	mAxis[1] = mCorner[3] - mCorner[0];




	// Make the length of each axis 1/edge length so we know any
	// dot product must be less than 1 to fall within the edge.

	mAxis[0].Normalize();
	mAxis[1].Normalize();
}

bool BoxCollider2D::TestAABBVsPoint(const Vector3& pt)
{
	return (pt.X() >= mMinPos.X() && pt.X() <= mMaxPos.X() &&
		pt.Y() >= mMinPos.Y() && pt.Y() <= mMaxPos.Y());
}

bool BoxCollider2D::TestAABBVsAABB(const BoxCollider2D& aabb)
{
	if (mMaxPos.X() < aabb.mMinPos.X() || mMaxPos.Y() < aabb.mMinPos.Y() ||
		mMinPos.X() > aabb.mMaxPos.X() || mMinPos.Y() > aabb.mMaxPos.Y())
		return false;

	return true;
}

bool BoxCollider2D::TestOOBBVsPoint(const Vector3& pt) const
{
	for (int i = 0; i < 2; i++)
	{
		double t = mAxis[i].AbsDot(mOrigin - pt);

		float tMax = 0;

		for (int c = 0; c < 4; ++c) {

			float d = mAxis[i].AbsDot(mOrigin - mCorner[c]);
			if (d > tMax)
				tMax = d;
		}

		if (tMax < t)
			return false;
	}

	return true;
}

bool BoxCollider2D::TestOOBBVsOOBB(const BoxCollider2D& oobb) const
{
	return TestOverlaps(oobb) && oobb.TestOverlaps(*this);
}

bool BoxCollider2D::TestOverlaps(const BoxCollider2D& oobb) const {

	double t = oobb.mCorner[0].Dot(mAxis[0]);

	// Find the extent of box 2 on axis a
	double tMin = t;
	double tMax = t;

	for (int c = 1; c < 4; ++c) {
		t = oobb.mCorner[c].Dot(mAxis[1]);

		if (t < tMin) {
			tMin = t;
		}
		else if (t > tMax) {
			tMax = t;
		}
	}
	// See if [tMin, tMax] intersects [0, 1]
	if ((tMin > (double)mOrigin._x + 1.0) || (tMax < mOrigin._x)) {
		// There was no intersection along this dimension;
		// the boxes cannot possibly overlap.
		return false;
	}

	t = oobb.mCorner[0].Dot(mAxis[1]);

	// Find the extent of box 2 on axis a
	tMin = t;
	tMax = t;

	for (int c = 1; c < 4; ++c) {
		t = oobb.mCorner[c].Dot(mAxis[1]);

		if (t < tMin) {
			tMin = t;
		}
		else if (t > tMax) {
			tMax = t;
		}
	}
	// See if [tMin, tMax] intersects [0, 1]
	if ((tMin > (double)mOrigin._y + 1.0) || (tMax < mOrigin._y)) {
		// There was no intersection along this dimension;
		// the boxes cannot possibly overlap.
		return false;
	}
	// There was no dimension along which there is no intersection.
	// Therefore the boxes overlap.
	return true;
}

bool BoxCollider2D::TestBoxVsPoint(const Vector3& pt)
{

	if (mAngle)
		return TestOOBBVsPoint(pt);

	return TestAABBVsPoint(pt);
}

bool BoxCollider2D::TestBoxVsBox(const BoxCollider2D& box)
{
	if (mAngle)
		TestOOBBVsOOBB(box);

	return TestAABBVsAABB(box);
}

bool TestCircleVsBox(const CircleCollider2D& circle, const BoxCollider2D& box)
{
	if (box.mAngle)
		return TestCircleVsOOBB(circle, box);

	return TestCircleVsAABB(circle, box);
}

bool TestCircleVsAABB(const CircleCollider2D& circle, const BoxCollider2D& aabb)
{
	BoxCollider2D box = aabb;

	if (box.TestAABBVsPoint(circle.mCenPos))
		return true;

	if (Vec3Distance_LinetoPoint(aabb.mMinPos, Vector3(aabb.mMinPos.X(), aabb.mMaxPos.Y()), circle.mCenPos) <= circle.mRadius ||
		Vec3Distance_LinetoPoint(Vector3(aabb.mMinPos.X(), aabb.mMaxPos.Y()), aabb.mMaxPos, circle.mCenPos) <= circle.mRadius ||
		Vec3Distance_LinetoPoint(aabb.mMaxPos, Vector3(aabb.mMaxPos.X(), aabb.mMinPos.Y()), circle.mCenPos) <= circle.mRadius ||
		Vec3Distance_LinetoPoint(Vector3(aabb.mMaxPos.X(), aabb.mMinPos.Y()), aabb.mMinPos, circle.mCenPos) <= circle.mRadius)
		return true;

	return false;
}

bool TestCircleVsOOBB(const CircleCollider2D& circle, const BoxCollider2D& oobb)
{
	return oobb.TestOOBBVsPoint(circle.mCenPos);
}

void BoxCollider2D::Draw()
{
	DebugRenderer::GetInstance().DrawLine(mCorner[0]._x, mCorner[0]._y, mCorner[1]._x, mCorner[1]._y);
	DebugRenderer::GetInstance().DrawLine(mCorner[1]._x, mCorner[1]._y, mCorner[2]._x, mCorner[2]._y);
	DebugRenderer::GetInstance().DrawLine(mCorner[2]._x, mCorner[2]._y, mCorner[3]._x, mCorner[3]._y);
	DebugRenderer::GetInstance().DrawLine(mCorner[3]._x, mCorner[3]._y, mCorner[0]._x, mCorner[0]._y);

	DebugRenderer::GetInstance().DrawLine(mOrigin._x, mOrigin._y, mOrigin._x + mAxis[0]._x * 40.f, mOrigin._y + mAxis[0]._y * 40.f);
	DebugRenderer::GetInstance().DrawLine(mOrigin._x, mOrigin._y, mOrigin._x + mAxis[1]._x * 40.f, mOrigin._y + mAxis[1]._y * 40.f);
}