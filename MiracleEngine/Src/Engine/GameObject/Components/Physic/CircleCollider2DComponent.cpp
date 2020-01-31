///////////////////////////////////////////////////////////////////////////////////////
//
//	CircleCollider2DComponent.cpp
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#include "PrecompiledHeaders.h"
#include "CircleCollider2DComponent.h"
//#include "GraphicsSystem/DebugRenderer.h"

CircleCollider2DComponent::CircleCollider2DComponent() :
	mCenPos{},
	mRadius{ 0.f }
{
	_type = (unsigned)ColliderType::CIRCLE_COLLIDER;
}

std::string CircleCollider2DComponent::ComponentName() const
{
	return std::string("CircleCollider Component");
}

void CircleCollider2DComponent::SerialiseComponent(Serialiser& document)
{
	Collider2D::SerialiseComponent(document);

}

void CircleCollider2DComponent::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	rapidjson::Value value;

	value.SetBool(true);
	prototypeDoc.AddMember("CircleCollider2DComponent", rapidjson::Value(true));

	Collider2D::DeSerialiseComponent(prototypeDoc);
}





void CircleCollider2DComponent::Inspect()
{
	Collider2D::Inspect();
}

///////////////////////////////////////////////////////////////////////////////
	// Function Setting and Getting only
