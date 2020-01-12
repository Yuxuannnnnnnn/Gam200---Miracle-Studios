#include "PrecompiledHeaders.h"
#include"EdgeCollider2DComponent.h"

EdgeCollider2DComponent::EdgeCollider2DComponent() :
	m_origin{},
	m_pt0{},
	m_pt1{},
	m_normal{}
{
	_type = (unsigned)ColliderType::EDGE_COLLIDER;
}

std::string EdgeCollider2DComponent::ComponentName() const
{
	return std::string("EdgeCollider2D Component");
}

void EdgeCollider2DComponent::SerialiseComponent(Serialiser& document)
{
	Collider2D::SerialiseComponent(document);

}

void EdgeCollider2DComponent::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	rapidjson::Value value;

	value.SetBool(true);
	prototypeDoc.AddMember("EdgeCollider2DComponent", rapidjson::Value(true));

	Collider2D::DeSerialiseComponent(prototypeDoc);
}



void EdgeCollider2DComponent::Inspect()
{
	IComponent::Inspect();
}

///////////////////////////////////////////////////////////////////////////////
// Function Setting and Getting only
 
