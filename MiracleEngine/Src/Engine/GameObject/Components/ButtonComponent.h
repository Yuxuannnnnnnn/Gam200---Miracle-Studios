#ifndef BUTTONCOMPONENT_H
#define BUTTONCOMPONENT_H

#pragma once
#include "../IComponent.h"

enum class ButtonStates {
	NORMAL,
	HOVERED,
	PRESSED,

	TOTAL_BUTTONSTATE
};

class ButtonComponent : public BoxCollider2DComponent
{
private:
	int _buttonUId;

	ButtonStates _currState;

	bool _haveHoverState;
	bool _havePressState;

	std::string _normalFileName;
	std::string _hoveredFileName;
	std::string _pressedFileName;

public:
	bool _pressedAtStart;


	ButtonComponent();
	ButtonComponent(const ButtonComponent& rhs) = default;
	virtual ~ButtonComponent() = default;
	
	ButtonComponent& operator=(const ButtonComponent& rhs) = delete;

	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser& document) override
	{
		if (document.HasMember("ButtonUId") && document["ButtonUId"].IsInt())	//Checks if the variable exists in .Json file
			_buttonUId = (document["ButtonUId"].GetInt());

		if (document.HasMember("B.NormalFileName") && document["B.NormalFileName"].IsString())
			_normalFileName = document["B.NormalFileName"].GetString();

		if (document.HasMember("B.HaveHoveredFile") && document["B.HaveHoveredFile"].IsBool())
		{
			_haveHoverState = true;

			if (document.HasMember("B.HoveredFileName") && document["B.HoveredFileName"].IsString())
				_hoveredFileName = document["B.HoveredFileName"].GetString();
		}
		if (document.HasMember("B.HavePressedFile") && document["B.HavePressedFile"].IsBool())
		{
			_havePressState = true;

			if (document.HasMember("B.PressedFileName") && document["B.PressedFileName"].IsString())
				_pressedFileName = document["B.PressedFileName"].GetString();
		}
	}


	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override
	{
		rapidjson::Value value;

		value.SetBool(true);
		prototypeDoc.AddMember("ButtonComponent", rapidjson::Value(true));

		value.SetInt(_buttonUId);
		prototypeDoc.AddMember("ButtonUId", value);

		value.SetString(rapidjson::StringRef(_normalFileName.c_str()));
		prototypeDoc.AddMember("B.NormalFileName", value);

		if (_haveHoverState)
		{
			value.SetBool(_haveHoverState);
			prototypeDoc.AddMember("B.HaveHoveredFile", value);

			value.SetString(rapidjson::StringRef(_hoveredFileName.c_str()));
			prototypeDoc.AddMember("B.HoveredFileName", value);
		}

		if (_havePressState)
		{
			value.SetBool(_havePressState);
			prototypeDoc.AddMember("B.HavePressedFile", value);

			value.SetString(rapidjson::StringRef(_pressedFileName.c_str()));
			prototypeDoc.AddMember("B.PressedFileName", value);
		}
	}

	void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
	{
		rapidjson::Value value;

		value.SetBool(true);
		prototypeDoc.AddMember("ButtonComponent", rapidjson::Value(true), allocator);


		value.SetInt(_buttonUId);
		prototypeDoc.AddMember("ButtonUId", value, allocator);

		value.SetString(rapidjson::StringRef(_normalFileName.c_str()));
		prototypeDoc.AddMember("B.NormalFileName", value, allocator);

		if (_haveHoverState)
		{
			value.SetBool(_haveHoverState);
			prototypeDoc.AddMember("B.HaveHoveredFile", value, allocator);

			value.SetString(rapidjson::StringRef(_hoveredFileName.c_str()));
			prototypeDoc.AddMember("B.HoveredFileName", value, allocator);
		}

		if (_havePressState)
		{
			value.SetBool(_havePressState);
			prototypeDoc.AddMember("B.HavePressedFile", value, allocator);

			value.SetString(rapidjson::StringRef(_pressedFileName.c_str()));
			prototypeDoc.AddMember("B.PressedFileName", value, allocator);
		}
	}

	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
	{

		ButtonComponent* protoButtonCom = dynamic_cast<ButtonComponent*>(protoCom);

		if (!protoButtonCom)
		{
			DeSerialiseComponent(value, allocator);
			return;
		}

		bool addComponentIntoSceneFile = false;
		rapidjson::Value buttonType;

		rapidjson::Value haveHoverState;
		rapidjson::Value havePressState;

		rapidjson::Value normalFileName;
		rapidjson::Value hoveredFileName;
		rapidjson::Value pressedFileName;


		if (protoButtonCom->_buttonUId != _buttonUId)	//If audiofile of Object is diff from prototype
		{
			addComponentIntoSceneFile = true;
			buttonType.SetInt(_buttonUId);
		}

		if (protoButtonCom->_normalFileName.compare(_normalFileName))
		{
			addComponentIntoSceneFile = true;
			normalFileName.SetString(rapidjson::StringRef(_normalFileName.c_str()));
		}

		if (_haveHoverState)
		{
			if (protoButtonCom->_haveHoverState != _haveHoverState)
			{
				addComponentIntoSceneFile = true;
				haveHoverState.SetBool(_haveHoverState);
			}


			if (protoButtonCom->_hoveredFileName.compare(_hoveredFileName))
			{
				addComponentIntoSceneFile = true;
				hoveredFileName.SetString(rapidjson::StringRef(_hoveredFileName.c_str()));
			}
		}

		if (_havePressState)
		{
			if (protoButtonCom->_havePressState != _havePressState)
			{
				addComponentIntoSceneFile = true;
				havePressState.SetBool(_havePressState);
			}

			if (protoButtonCom->_pressedFileName.compare(_pressedFileName))
			{
				addComponentIntoSceneFile = true;
				pressedFileName.SetString(rapidjson::StringRef(_pressedFileName.c_str()));
			}
		}


		if (addComponentIntoSceneFile)	//If anyone of component data of obj is different from Prototype
		{
			value.AddMember("ButtonComponent", rapidjson::Value(true), allocator);

			if (!buttonType.IsNull())
			{
				value.AddMember("ButtonUId", buttonType, allocator);
			}

			if (!haveHoverState.IsNull())	//if rapidjson::value container is not empty
			{
				value.AddMember("B.HaveHoveredFile", haveHoverState, allocator);
			}

			if (!havePressState.IsNull())	//if rapidjson::value container is not empty
			{
				value.AddMember("B.HavePressedFile", havePressState, allocator);
			}

			if (!normalFileName.IsNull())	//if rapidjson::value container is not empty
			{
				value.AddMember("B.NormalFileName", normalFileName, allocator);
			}

			if (!hoveredFileName.IsNull())	//if rapidjson::value container is not empty
			{
				value.AddMember("B.HoveredFileName", hoveredFileName, allocator);
			}

			if (!pressedFileName.IsNull())	//if rapidjson::value container is not empty
			{
				value.AddMember("B.PressedFileName", pressedFileName, allocator);
			}

		}
	}


	virtual void Inspect() override;

	size_t GetButtonUId();

	void ButtonNormalState();
	void ButtonHoveredState();
	void ButtonPressedState();


///////////////////////////////////////////////////////////////////////////////
	// Function Setting and Getting only
	ButtonComponent* CloneComponent() { return new ButtonComponent(*this); }
};

#endif