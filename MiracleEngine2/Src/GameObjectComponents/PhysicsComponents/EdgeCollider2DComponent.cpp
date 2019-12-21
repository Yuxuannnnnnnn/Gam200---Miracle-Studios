#include "PrecompiledHeaders.h"
#include"EdgeCollider2DComponent.h"

EdgeCollider2D::EdgeCollider2D() :
	m_origin{},
	m_pt0{},
	m_pt1{},
	m_normal{}
{
	_type = (unsigned)ColliderType::EDGE_COLLIDER;
}

std::string EdgeCollider2D::ComponentName() const
{
	return std::string("EdgeCollider2D Component");
}

void EdgeCollider2D::SerialiseComponent(Serialiser& document)
{
	ICollider2D::SerialiseComponent(document);

}

void EdgeCollider2D::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	ICollider2D::DeSerialiseComponent(prototypeDoc);
}

void EdgeCollider2D::Inspect()
{
	IComponent::Inspect();
}

///////////////////////////////////////////////////////////////////////////////
// Function Setting and Getting only
 
