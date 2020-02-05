#include "PrecompiledHeaders.h"
#include "IdentityComponent.h"


IdentityComponent::IdentityComponent(GameObject* parent, size_t uId, IComponent* component)
	: IComponent(parent, uId)/*, _typeId{ (unsigned)TypeIdGO::NONE }*/, _ObjectType{ "none" }, _name{ "none" }, _linkUId{ 0 }
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

void IdentityComponent::Init()
{
	if (_linkUId)
		MyLinkFactory.SaveNewLinkID(_linkUId, GetParentId());
}

void IdentityComponent::Inspect()
{
	ImGui::Spacing();
	std::string string = std::string("Game Object Type ");
	//strncpy(_current_ObjectType, _ObjectType.c_str(), _ObjectType.length());


	char objType[100] = "\0";
	strncpy(objType, _ObjectType.c_str(), _ObjectType.length());
	ImGui::InputText(string.c_str(), objType, 100);
	_ObjectType = objType;
	ImGui::Spacing();

	char Name[100] = "\0";
	strncpy(Name, _name.c_str(), _name.length());
	//strncpy(_current_Name, _name.c_str(), _name.length());
	string = "Name of Object ";
	ImGui::InputText(string.c_str(), Name, 100);
	_name = Name;
	ImGui::Spacing();


	ImGui::Spacing();
	ImGui::InputInt("Linking ID", &_linkUId);
	ImGui::Spacing();
	ImGui::Spacing();
	if (ImGui::Button("Save Link ID"))
		MyLinkFactory.SaveNewLinkID(_linkUId, GetParentId());
	ImGui::Spacing();
}

//unsigned IdentityComponent::GameObjectType() const
//{
//	return _typeId;
//}
