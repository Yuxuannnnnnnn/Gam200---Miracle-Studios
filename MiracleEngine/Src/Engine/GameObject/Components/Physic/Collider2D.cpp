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


void Collider2D::DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
{
	rapidjson::Value value;

	value.SetInt(_type);
	prototypeDoc.AddMember("ColliderTypeId", value, allocator);

	value.SetInt(_tag);
	prototypeDoc.AddMember("ColliderTag", value, allocator);

	value.SetBool(_trigger);
	prototypeDoc.AddMember("ColliderTrigger", value, allocator);
}