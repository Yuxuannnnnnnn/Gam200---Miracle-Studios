//
//	BoxCollider2D.cpp
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#include "PrecompiledHeaders.h"
#include "BoxCollider2DComponent.h"

BoxCollider2D::BoxCollider2D() :
	mMinPos{},
	mMaxPos{},
	mOrigin{},
	mCorner{ {},{},{},{} },
	mAxis{ {},{} },
	mScale{},
	mAngle{ -1.f }
{
	_type = (unsigned)ColliderType::BOX_COLLIDER;
}

std::string BoxCollider2D::ComponentName() const
{
	return std::string("BoxCollider2D Component");
}

void BoxCollider2D::SerialiseComponent(Serialiser& document)
{
	Collider2D::SerialiseComponent(document);
}

void BoxCollider2D::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	Collider2D::DeSerialiseComponent(prototypeDoc);
}

void BoxCollider2D::Inspect()
{
	IComponent::Inspect();
}

///////////////////////////////////////////////////////////////////////////////
	// Function Setting and Getting only