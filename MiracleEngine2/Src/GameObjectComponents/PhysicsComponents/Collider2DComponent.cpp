#include "PrecompiledHeaders.h"
#include "ICollider2D.h"

ICollider2D::ICollider2D() :
	_type{ (unsigned)ColliderType::NONE_COLLIDER },
	_tag{ (unsigned)ColliderTag::NONE },
	_layer{ 0 },
	_trigger{ true },
	_attachedRigidboy{ false },
	_componentEnable{ true }
{}

std::string ICollider2D::ComponentName() const
{
	return "ColliderComponent";
}

void ICollider2D::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("ColliderTypeId") && document["ColliderTypeId"].IsInt())	//Checks if the variable exists in .Json file
		_type = document["ColliderTypeId"].GetUint();

	if (document.HasMember("ColliderTag") && document["ColliderTag"].IsInt())	//Checks if the variable exists in .Json file
		_tag = document["ColliderTag"].GetUint();
	
	if (document.HasMember("ColliderTrigger") && document["ColliderTrigger"].IsBool())	//Checks if the variable exists in .Json file
		_trigger = document["ColliderTrigger"].GetBool();
}

void ICollider2D::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	rapidjson::Value value;

	value.SetInt(_type);
	prototypeDoc.AddMember("ColliderTypeId", value);

	value.SetInt(_tag);
	prototypeDoc.AddMember("ColliderTag", value);

	value.SetBool(_trigger);
	prototypeDoc.AddMember("ColliderTrigger", value);
}



void ICollider2D::Inspect()
{
}
