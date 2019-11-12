#include "PrecompiledHeaders.h"
#include "Collider2D.h"

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

void Collider2D::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("ColliderTypeId") && document["ColliderTypeId"].IsInt())	//Checks if the variable exists in .Json file
		_type = document["ColliderTypeId"].GetUint();

	if (document.HasMember("ColliderTag") && document["ColliderTag"].IsInt())	//Checks if the variable exists in .Json file
		_tag = document["ColliderTag"].GetUint();
	
	if (document.HasMember("ColliderTrigger") && document["ColliderTrigger"].IsBool())	//Checks if the variable exists in .Json file
		_trigger = document["ColliderTrigger"].GetBool();
}



void Collider2D::Inspect()
{
}
