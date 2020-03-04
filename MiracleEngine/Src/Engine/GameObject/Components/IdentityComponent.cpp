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
		MyFactory.SaveNewLinkID(_linkUId, GetParentId());
}

void IdentityComponent::LoadResource()
{
#ifdef LEVELEDITOR
	if (MyResourceSystem.GetPrototypeResource(_ObjectType))
		MyResourceManager.AddNewPrototypeResource({ _ObjectType , MyResourceSystem.GetPrototypeResourcePath(_ObjectType) });
#endif // LEVELEDITOR
}



const std::string& IdentityComponent::GetName() const
{
	return _name;
}

const std::string& IdentityComponent::ObjectType() const
{
	return _ObjectType;
}

void IdentityComponent::SetObjectType(std::string ObjectType)
{
	_ObjectType = ObjectType;
}

int IdentityComponent::GetLinkID()
{
	return _linkUId;
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
		MyFactory.SaveNewLinkID(_linkUId, GetParentId());
	ImGui::Spacing();
}

//unsigned IdentityComponent::GameObjectType() const
//{
//	return _typeId;
//}

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

	if (document.HasMember("LinkUId") && document["LinkUId"].IsInt())
	{
		_linkUId = document["LinkUId"].GetInt();
	}
}

void IdentityComponent::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	rapidjson::Value value;

	value.SetBool(true);
	prototypeDoc.AddMember("IdentityComponent", rapidjson::Value(true));

	value.SetString(rapidjson::StringRef(_ObjectType.c_str()));
	prototypeDoc.AddMember("ObjectType", value);

	value.SetString(rapidjson::StringRef(_name.c_str()));
	prototypeDoc.AddMember("Name", value);

	value.SetInt(_linkUId);
	prototypeDoc.AddMember("LinkUId", value);

	//value.SetInt(_typeId);
	//prototypeDoc.AddMember("GameObjectType", value);
}

void IdentityComponent::DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
{
	rapidjson::Value value;

	value.SetBool(true);
	prototypeDoc.AddMember("IdentityComponent", rapidjson::Value(true), allocator);

	value.SetString(rapidjson::StringRef(_ObjectType.c_str()));
	prototypeDoc.AddMember("ObjectType", value, allocator);

	value.SetString(rapidjson::StringRef(_name.c_str()));
	prototypeDoc.AddMember("Name", value, allocator);

	value.SetInt(_linkUId);
	prototypeDoc.AddMember("LinkUId", value, allocator);

	//value.SetInt(_typeId);
	//prototypeDoc.AddMember("GameObjectType", value);
}

void IdentityComponent::DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
{

	IdentityComponent* protoIdentityCom = dynamic_cast<IdentityComponent*>(protoCom);

	bool addComponentIntoSceneFile = false;

	rapidjson::Value ObjectType;
	rapidjson::Value LinkUId;

	ObjectType.SetString(rapidjson::StringRef(_ObjectType.c_str()));

	rapidjson::Value Name("IdentityComponent", allocator);
	value.AddMember(Name, rapidjson::Value(true), allocator);
	Name.SetString("ObjectType", allocator);
	value.AddMember(Name, ObjectType, allocator);

	rapidjson::Value name;
	if (protoIdentityCom->_name.compare(_name))	//If audiofile of Object is diff from prototype
	{
		addComponentIntoSceneFile = true;
		name.SetString(rapidjson::StringRef(_name.c_str()));

		Name.SetString("Name", allocator);
		value.AddMember(Name, name, allocator);
	}

	if (protoIdentityCom->_linkUId != _linkUId)
	{
		addComponentIntoSceneFile = true;
		LinkUId.SetInt(_linkUId);

		value.AddMember("LinkUId", _linkUId, allocator);
	}
}
