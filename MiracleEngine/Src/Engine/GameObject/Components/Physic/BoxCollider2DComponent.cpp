//
//	BoxCollider2DComponent.cpp
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#include "PrecompiledHeaders.h"
#include "BoxCollider2DComponent.h"

BoxCollider2DComponent::BoxCollider2DComponent() :
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

std::string BoxCollider2DComponent::ComponentName() const
{
	return std::string("BoxCollider2D Component");
}



void BoxCollider2DComponent::Inspect()
{
	IComponent::Inspect();
}

///////////////////////////////////////////////////////////////////////////////
	// Function Setting and Getting only