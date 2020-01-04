#pragma once
#include "../IComponent.h"
#include <string>

#ifndef IDENTITYCOMPONENT_H
#define IDENTITYCOMPONENT_H


//Every Object is compulsory to have this Identity Component to store their uId and Type
class IdentityComponent: public IComponent
{
private:

	//unsigned _typeId;  //Change to string
	std::string _ObjectType; // GameObject Type
	std::string _name;

public:
	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser& document) override
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


	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override
	{
		rapidjson::Value value;

		value.SetBool(true);
		prototypeDoc.AddMember("IdentityComponent", rapidjson::Value(true));

		value.SetString(rapidjson::StringRef(_ObjectType.c_str()));
		prototypeDoc.AddMember("ObjectType", value);

		value.SetString(rapidjson::StringRef(_name.c_str()));
		prototypeDoc.AddMember("Name", value);

		//value.SetInt(_typeId);
		//prototypeDoc.AddMember("GameObjectType", value);
	}

	void DeserialiseComponentSceneFile(IComponent* protoCom, DeSerialiser& SceneFile) override
	{

		IdentityComponent* protoIdentityCom = dynamic_cast<IdentityComponent*>(protoCom);

		bool addComponentIntoSceneFile = false;

		rapidjson::Value ObjectType;
		ObjectType.SetString(rapidjson::StringRef(_ObjectType.c_str()));

		rapidjson::Value name;

		if (protoIdentityCom->_name.compare(_name))	//If audiofile of Object is diff from prototype
		{
			addComponentIntoSceneFile = true;
			name.SetString(rapidjson::StringRef(_name.c_str()));
		}


		if (addComponentIntoSceneFile)	//If anyone of component data of obj is different from Prototype
		{
			SceneFile.AddMember("IdentityComponent", rapidjson::Value(true));
			SceneFile.AddMember("ObjectType", ObjectType);

			if (!name.IsNull())
			{
				SceneFile.AddMember("Name", name);
			}
		}
	}

	void Inspect() override
	{
		ImGui::Spacing();
		std::string string = std::string("Game Object Type ");
		//strncpy(_current_ObjectType, _ObjectType.c_str(), _ObjectType.length());


		static char objType[100] = "\0";
		strncpy(objType, _ObjectType.c_str(), _ObjectType.length());
		ImGui::InputText(string.c_str(), objType, 100);
		_ObjectType = objType;
		ImGui::Spacing();

		static char Name[100] = "\0";
		strncpy(Name, _name.c_str(), _name.length());
		//strncpy(_current_Name, _name.c_str(), _name.length());
		string = "Name of Object ";
		ImGui::InputText(string.c_str(), Name, 100);
		_name = Name;
		ImGui::Spacing();
	}







	IdentityComponent(GameObject* parent = nullptr, size_t uId = 0, IComponent * component = nullptr); //Constructor
	IdentityComponent(IdentityComponent* component);

	//unsigned GameObjectType() const;

	const std::string& ObjectType() const
	{
		return _ObjectType;
	}

	void SetObjectType(std::string ObjectType)
	{
		_ObjectType = ObjectType;
	}
};


#endif 
