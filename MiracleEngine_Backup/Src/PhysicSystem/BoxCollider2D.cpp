//
//	BoxCollider2D.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#include "BoxCollider2D.h"

bool TestCircleVsBox(const CircleCollider2D& cc, const BoxCollider2D& aabb)
{
	BoxCollider2D box = aabb;

	if (box.TestBoxVsPoint(cc.mCenPos))
		return true;

	if (Vec3Distance_LinetoPoint(aabb.mMinPos, Vector3(aabb.mMinPos.X(), aabb.mMaxPos.Y()), cc.mCenPos) <= cc.mRadius ||
		Vec3Distance_LinetoPoint(Vector3(aabb.mMinPos.X(), aabb.mMaxPos.Y()), aabb.mMaxPos, cc.mCenPos) <= cc.mRadius ||
		Vec3Distance_LinetoPoint(aabb.mMaxPos, Vector3(aabb.mMaxPos.X(), aabb.mMinPos.Y()), cc.mCenPos) <= cc.mRadius ||
		Vec3Distance_LinetoPoint(Vector3(aabb.mMaxPos.X(), aabb.mMinPos.Y()), aabb.mMinPos, cc.mCenPos) <= cc.mRadius)
		return true;

	return false;
}

BoxCollider2D::BoxCollider2D() : mMinPos{}, mMaxPos{}
{
}

BoxCollider2D::BoxCollider2D(const Vector3& cenPos, const Vector3& scale)
{
	Update(cenPos, scale);
}

void BoxCollider2D::Update(const Vector3& cenPos, const Vector3& scale)
{
	//Get bounding rec
	Vector3 boundingBox_offset = { -0.5f * scale._x, -0.5f * scale._y };

	//Cal boundingRect minimum point
	mMinPos = cenPos - boundingBox_offset;

	//boundingRect maximum point
	mMaxPos = cenPos - (-boundingBox_offset);
}

BoxCollider2D::BoxCollider2D(const BoxCollider2D& _bc) :
	mMinPos(_bc.mMinPos), mMaxPos(_bc.mMaxPos)
{
}

bool BoxCollider2D::TestBoxVsPoint(const Vector3& pt)
{
	return (pt.X() >= mMinPos.X() && pt.X() <= mMaxPos.X() &&
		pt.Y() >= mMinPos.Y() && pt.Y() <= mMaxPos.Y());
}

bool BoxCollider2D::TestBoxVsBox(const BoxCollider2D& box)
{
	if (mMaxPos.X() < box.mMinPos.X() || mMaxPos.Y() < box.mMinPos.Y() ||
		mMinPos.X() > box.mMaxPos.X() || mMinPos.Y() > box.mMaxPos.Y())
		return false;

	return true;
}
