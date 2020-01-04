#include "PrecompiledHeaders.h"
#include "ICollider2D.h"

Collider2D::Collider2D() :
	_type{ (unsigned)ColliderType::NONE_COLLIDER },
	_tag{ (unsigned)ColliderTag::NONE },
	_layer{ 0 },
	_trigger{ true },
	_attachedRigidboy{ false },
	_componentEnable{ true }
{}

std::string Collider2D::ComponentName() const
{
	return "ColliderComponent";
}




void Collider2D::Inspect()
{
}
