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

	int _linkUId;

public:

	virtual void Init() override;

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

		if (document.HasMember("LinkUId") && document["LinkUId"].IsInt())
		{
			_linkUId = document["LinkUId"].GetInt();
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

		value.SetInt(_linkUId);
		prototypeDoc.AddMember("LinkUId", value);

		//value.SetInt(_typeId);
		//prototypeDoc.AddMember("GameObjectType", value);
	}

	void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
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


	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator) 
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

	void Inspect() override;


	const std::string& GetName() const
	{
		return _name;
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

	IdentityComponent* CloneComponent() { return new IdentityComponent(*this); }
};


#endif 
