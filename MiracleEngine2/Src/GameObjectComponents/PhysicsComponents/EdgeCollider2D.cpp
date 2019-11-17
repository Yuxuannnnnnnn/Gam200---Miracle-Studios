#include "PrecompiledHeaders.h"
#include"EdgeCollider2D.h"

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
	Collider2D::SerialiseComponent(document);

}

void EdgeCollider2D::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	Collider2D::DeSerialiseComponent(prototypeDoc);
}

void EdgeCollider2D::Inspect()
{
	IComponentSystem::Inspect();
}

///////////////////////////////////////////////////////////////////////////////
// Function Setting and Getting only
 
