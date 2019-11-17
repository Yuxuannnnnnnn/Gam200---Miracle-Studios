#include "PrecompiledHeaders.h"
#include "IdentityComponent.h"







IdentityComponent::IdentityComponent(GameObject* parent, size_t uId, IComponentSystem* component)
	: IComponentSystem(parent, uId), _typeId{(unsigned)TypeIdGO::NONE}
{
	if (component)
	{
		IdentityComponent* Icom = dynamic_cast<IdentityComponent*>(component);
		_typeId = Icom->_typeId;
		_name = Icom->_name;
	}
}



std::string IdentityComponent::ComponentName() const
{
	return std::string("Identity Component");
}



void IdentityComponent::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("Name") && document["Name"].IsString())	//Checks if the variable exists in .Json file
	{
		_name = document["Name"].GetString();
	}

	if (document.HasMember("GameObjectType") && document["GameObjectType"].IsInt())	//Checks if the variable exists in .Json file
	{
		_typeId = document["GameObjectType"].GetInt();
	}
}


void IdentityComponent::Inspect()
{
}


unsigned IdentityComponent::GameObjectType() const
{
	return _typeId;
}
