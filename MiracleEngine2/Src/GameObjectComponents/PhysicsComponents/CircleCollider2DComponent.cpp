///////////////////////////////////////////////////////////////////////////////////////
//
//	CircleCollider2D.cpp
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#include "PrecompiledHeaders.h"
#include "CircleCollider2DComponent.h"
//#include "GraphicsSystem/DebugRenderer.h"

CircleCollider2D::CircleCollider2D() :
	mCenPos{},
	mRadius{ 0.f }
{
	_type = (unsigned)ColliderType::CIRCLE_COLLIDER;
}

std::string CircleCollider2D::ComponentName() const
{
	return std::string("CircleCollider2D Component");
}

void CircleCollider2D::SerialiseComponent(Serialiser& document)
{
	ICollider2D::SerialiseComponent(document);

}

void CircleCollider2D::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	ICollider2D::DeSerialiseComponent(prototypeDoc);
}

void CircleCollider2D::Inspect()
{
	IComponent::Inspect();
}

///////////////////////////////////////////////////////////////////////////////
	// Function Setting and Getting only
