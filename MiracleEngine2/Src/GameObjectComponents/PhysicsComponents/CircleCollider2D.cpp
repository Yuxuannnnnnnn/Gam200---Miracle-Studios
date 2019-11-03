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


void CircleCollider2D::SerialiseComponent(Serialiser& document)
{
	Collider2D::SerialiseComponent(document);

}

void CircleCollider2D::Inspect()
{
	IComponentSystem::Inspect();
}

CircleCollider2D::CircleCollider2D(GameObject* parent, size_t uId, IComponentSystem* component)
	: Collider2D(parent, uId, component), mCenPos(0.f, 0.f), mRadius(0.f)
{

	if (component)
	{
		CircleCollider2D* circle2DComponent = dynamic_cast<CircleCollider2D*>(component);
		mCenPos = circle2DComponent->mCenPos;
		mRadius = circle2DComponent->mRadius;
	}
}

CircleCollider2D::CircleCollider2D(TransformComponent* transform) :
	mCenPos{},
	mRadius{ 0.f },
	Collider2D(transform)
{/*
	mCenPos = _transform->GetPos();
	mRadius = _transform->GetScale().X();*/

	_type = (unsigned)ColliderType::CIRCLE_COLLIDER;
}

CircleCollider2D::CircleCollider2D(const CircleCollider2D& rhs) :
	mCenPos{ rhs.mCenPos },
	mRadius{ rhs.mRadius },
	Collider2D(nullptr)
{
	_type = (unsigned)ColliderType::CIRCLE_COLLIDER;
}

void CircleCollider2D::Draw()
{
	DebugRenderer::GetInstance().DrawCircle(mCenPos._x, mCenPos._y, mRadius);
}

void CircleCollider2D::Update()
{
	_transform = reinterpret_cast<TransformComponent*>(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT));

	mCenPos = _transform->GetPos();
	mRadius = _transform->GetScale().X() * 0.5f;
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
