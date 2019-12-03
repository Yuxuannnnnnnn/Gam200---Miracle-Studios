#include "PrecompiledHeaders.h"
#include "IdentityComponent.h"







IdentityComponent::IdentityComponent(GameObject* parent, size_t uId, IComponentSystem* component)
	: IComponentSystem(parent, uId)/*, _typeId{ (unsigned)TypeIdGO::NONE }*/, _ObjectType{""}
{
	//if (component)
	//{
	//	IdentityComponent* Icom = dynamic_cast<IdentityComponent*>(component);
	//	_typeId = Icom->_typeId;
	//	_name = Icom->_name;
	//	_ObjectType = Icom->_ObjectType;
	//}
}

IdentityComponent::IdentityComponent(IdentityComponent* component)
{
	//_typeId = component->_typeId;
	_name = component->_name;
	_ObjectType = component->_ObjectType;
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

	//if (document.HasMember("GameObjectType") && document["GameObjectType"].IsInt())	//Checks if the variable exists in .Json file
	//{
	//	_typeId = document["GameObjectType"].GetInt();
	//}	
	
	if (document.HasMember("ObjectType") && document["ObjectType"].IsString())	//Checks if the variable exists in .Json file
	{
		_ObjectType = document["ObjectType"].GetString();
	}
}

void IdentityComponent::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	rapidjson::Value value;

	value.SetString(rapidjson::StringRef(_name.c_str()));
	prototypeDoc.AddMember("Name", value);

	//value.SetInt(_typeId);
	//prototypeDoc.AddMember("GameObjectType", value);

	value.SetString(rapidjson::StringRef(_ObjectType.c_str()));
	prototypeDoc.AddMember("ObjectType", value);
}


void IdentityComponent::Inspect()
{
	ImGui::Spacing();
	std::string string = std::string("Game Object Type ");
	char ptr[100] = " ";
	strncpy(ptr, _ObjectType.c_str(), _ObjectType.length());
	ImGui::InputText(string.c_str(), ptr, 100);
	ImGui::Spacing();
	_ObjectType = ptr;


	char ptr1[100] = " ";
	strncpy(ptr1, _name.c_str(), _name.length());
	string = "Name of Object ";
	ImGui::InputText(string.c_str(), ptr1, 100);
	_name = ptr1;
	ImGui::Spacing();
}


//unsigned IdentityComponent::GameObjectType() const
//{
//	return _typeId;
//}
