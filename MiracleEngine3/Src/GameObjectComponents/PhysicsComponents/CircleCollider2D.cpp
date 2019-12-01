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
	Collider2D::SerialiseComponent(document);

}

void CircleCollider2D::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	Collider2D::DeSerialiseComponent(prototypeDoc);
}

void CircleCollider2D::Inspect()
{
	IComponentSystem::Inspect();
}

///////////////////////////////////////////////////////////////////////////////
	// Function Setting and Getting only
