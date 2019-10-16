///////////////////////////////////////////////////////////////////////////////////////
//
//	CircleCollider2D.cpp
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#include "PrecompiledHeaders.h"
#include "CircleCollider2D.h"
//#include "GraphicsSystem/DebugRenderer.h"


CircleCollider2D::CircleCollider2D() : mCenPos(0.f, 0.f), mRadius(0.f)
{
}

CircleCollider2D::CircleCollider2D(const Vector3& center, float radius) : mCenPos{ center }, mRadius{ radius }
{
}

CircleCollider2D::CircleCollider2D(const CircleCollider2D& _cc) : mCenPos{ _cc.mCenPos }, mRadius{ _cc.mRadius }
{
}

CircleCollider2D::~CircleCollider2D()
{
}

void CircleCollider2D::Update(const Vector3& center, float radius)
{
	mCenPos = center;
	mRadius = radius;
}

bool CircleCollider2D::TestCircleVsPoint(const Vector3& pt) const
{
	Vector3 diff = pt - mCenPos;
	return (diff.Length() <= mRadius);
}

bool CircleCollider2D::TestCircleVsCircle(const CircleCollider2D& circle) const
{
	return (mCenPos.Distance(circle.mCenPos) <= (mRadius + circle.mRadius));
}

void CircleCollider2D::Draw()
{
	//DebugRenderer::GetInstance().DrawLine(mCenPos._x + mRadius, mCenPos._y, mCenPos._x - mRadius, mCenPos._y);
	//DebugRenderer::GetInstance().DrawLine(mCenPos._x, mCenPos._y + mRadius, mCenPos._x, mCenPos._y - mRadius);
}