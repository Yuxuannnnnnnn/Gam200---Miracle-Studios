#pragma once
#include "../IComponent.h"

#ifndef BUTTONCOMPONENT_H
#define BUTTONCOMPONENT_H

class ButtonComponent : public BoxCollider2DComponent
{
public:
	bool _pressed;
	int _buttonType;

public:
	ButtonComponent();
	ButtonComponent(const ButtonComponent& rhs) = default;
	virtual ~ButtonComponent() = default;
	
	ButtonComponent& operator=(const ButtonComponent& rhs) = delete;

	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser& document) override
	{
		if (document.HasMember("ButtonType") && document["ButtonType"].IsInt())	//Checks if the variable exists in .Json file
		{
			_buttonType = (document["ButtonType"].GetInt());
		}
	}


	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override
	{
		rapidjson::Value value;

		value.SetBool(true);
		prototypeDoc.AddMember("ButtonComponent", rapidjson::Value(true));


		value.SetInt(_buttonType);
		prototypeDoc.AddMember("ButtonType", value);
	}

	void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
	{
		rapidjson::Value value;

		value.SetBool(true);
		prototypeDoc.AddMember("ButtonComponent", rapidjson::Value(true), allocator);


		value.SetInt(_buttonType);
		prototypeDoc.AddMember("ButtonType", value, allocator);
	}

	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
	{

		ButtonComponent* protoButtonCom = dynamic_cast<ButtonComponent*>(protoCom);

		bool addComponentIntoSceneFile = false;
		rapidjson::Value buttonType;

		if (protoButtonCom->_buttonType != _buttonType)	//If audiofile of Object is diff from prototype
		{
			addComponentIntoSceneFile = true;
			buttonType.SetInt(_buttonType);
		}


		if (addComponentIntoSceneFile)	//If anyone of component data of obj is different from Prototype
		{
			value.AddMember("ButtonComponent", rapidjson::Value(true), allocator);

			if (!buttonType.IsNull())
			{
				value.AddMember("ButtonType", buttonType, allocator);
			}
		}
	}


	void Inspect()
	{
		IComponent::Inspect();
	}



///////////////////////////////////////////////////////////////////////////////
	// Function Setting and Getting only
	IComponent* CloneComponent() { return nullptr; }
};

#endif