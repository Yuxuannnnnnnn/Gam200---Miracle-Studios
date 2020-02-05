#ifndef BUTTONCOMPONENT_H
#define BUTTONCOMPONENT_H

#pragma once
#include "../IComponent.h"
#include "Tools/MathLib/Math.h"

enum class ButtonStates {
	NORMAL,
	HOVERED,
	PRESSED,

	TOTAL_BUTTONSTATE
};

class ButtonComponent : public IComponent
{
private:
	TransformComponent* _transform;
	GraphicComponent* _graphic;

	int _buttonUId;

	ButtonStates _currState;

	bool _haveHoverState;
	bool _havePressState;

	Vec3 _normalScale;
	Vec3 _hoveredScale;
	Vec3 _pressedScale;

	std::string _normalFileName;
	std::string _hoveredFileName;
	std::string _pressedFileName;

	std::string _hoveredAudioFileName;
	std::string _pressedAudioFileName;
public:
	bool _pressedAtStart;


	ButtonComponent();
	ButtonComponent(const ButtonComponent& rhs) = default;
	virtual ~ButtonComponent() = default;
	
	virtual void Init() override;

	ButtonComponent& operator=(const ButtonComponent& rhs) = delete;

	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser& document) override
	{
		if (document.HasMember("ButtonUId") && document["ButtonUId"].IsInt())	//Checks if the variable exists in .Json file
			_buttonUId = (document["ButtonUId"].GetInt());

		if (document.HasMember("B.NormalFileName") && document["B.NormalFileName"].IsString())
			_normalFileName = document["B.NormalFileName"].GetString();

		if (document.HasMember("B.NormalScale") && document["B.NormalScale"].IsArray())	//Checks if the variable exists in .Json file
		{
			if (document["B.NormalScale"][0].IsFloat() && document["B.NormalScale"][1].IsFloat())	//Check the array values
				_normalScale = Vector3{ document["B.NormalScale"][0].GetFloat(), document["B.NormalScale"][1].GetFloat(), 1 };

			if (document["B.NormalScale"].Size() == 3)
			{
				_normalScale.SetZ(document["B.NormalScale"][2].GetFloat());
			}
		}

		if (document.HasMember("B.HaveHoveredFile") && document["B.HaveHoveredFile"].IsBool())
			_haveHoverState = document["B.HaveHoveredFile"].GetBool();

		if (_haveHoverState)
		{
			if (document.HasMember("B.HoveredFileName") && document["B.HoveredFileName"].IsString())
				_hoveredFileName = document["B.HoveredFileName"].GetString();

			if (document.HasMember("B.HoveredScale") && document["B.HoveredScale"].IsArray())	//Checks if the variable exists in .Json file
			{
				if (document["B.HoveredScale"][0].IsFloat() && document["B.HoveredScale"][1].IsFloat())	//Check the array values
					_hoveredScale = Vector3{ document["B.HoveredScale"][0].GetFloat(), document["B.HoveredScale"][1].GetFloat(), 1 };

				if (document["B.HoveredScale"].Size() == 3)
				{
					_hoveredScale.SetZ(document["B.HoveredScale"][2].GetFloat());
				}
			}

			if (document.HasMember("B.HoveredAudioFileName") && document["B.HoveredAudioFileName"].IsString())
				_hoveredAudioFileName = document["B.HoveredAudioFileName"].GetString();
		}

		if (document.HasMember("B.HavePressedFile") && document["B.HavePressedFile"].IsBool())
			_havePressState = document["B.HavePressedFile"].GetBool();

		if (_haveHoverState)
		{
			if (document.HasMember("B.PressedFileName") && document["B.PressedFileName"].IsString())
				_pressedFileName = document["B.PressedFileName"].GetString();

			if (document.HasMember("B.PressedScale") && document["B.PressedScale"].IsArray())	//Checks if the variable exists in .Json file
			{
				if (document["B.PressedScale"][0].IsFloat() && document["B.PressedScale"][1].IsFloat())	//Check the array values
					_pressedScale = Vector3{ document["B.PressedScale"][0].GetFloat(), document["B.PressedScale"][1].GetFloat(), 1 };

				if (document["B.PressedScale"].Size() == 3)
				{
					_pressedScale.SetZ(document["B.PressedScale"][2].GetFloat());
				}
			}

			if (document.HasMember("B.PressedAudioFileName") && document["B.PressedAudioFileName"].IsString())
				_pressedAudioFileName = document["B.PressedAudioFileName"].GetString();
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

		value.SetArray();
		value.PushBack(rapidjson::Value(_normalScale.GetX()).Move(), prototypeDoc.Allocator());
		value.PushBack(rapidjson::Value(_normalScale.GetY()).Move(), prototypeDoc.Allocator());
		value.PushBack(rapidjson::Value(_normalScale.GetZ()).Move(), prototypeDoc.Allocator());
		prototypeDoc.AddMember("B.NormalScale", value);

		value.SetBool(_haveHoverState);
		prototypeDoc.AddMember("B.HaveHoveredFile", value);

		if (_haveHoverState)
		{
			value.SetString(rapidjson::StringRef(_hoveredFileName.c_str()));
			prototypeDoc.AddMember("B.HoveredFileName", value);

			value.SetArray();
			value.PushBack(rapidjson::Value(_hoveredScale.GetX()).Move(), prototypeDoc.Allocator());
			value.PushBack(rapidjson::Value(_hoveredScale.GetY()).Move(), prototypeDoc.Allocator());
			value.PushBack(rapidjson::Value(_hoveredScale.GetZ()).Move(), prototypeDoc.Allocator());
			prototypeDoc.AddMember("B.HoveredScale", value);

			value.SetString(rapidjson::StringRef(_hoveredAudioFileName.c_str()));
			prototypeDoc.AddMember("B.HoveredAudioFileName", value);
		}

		value.SetBool(_havePressState);
		prototypeDoc.AddMember("B.HavePressedFile", value);

		if (_havePressState)
		{
			value.SetString(rapidjson::StringRef(_pressedFileName.c_str()));
			prototypeDoc.AddMember("B.PressedFileName", value);

			value.SetArray();
			value.PushBack(rapidjson::Value(_pressedScale.GetX()).Move(), prototypeDoc.Allocator());
			value.PushBack(rapidjson::Value(_pressedScale.GetY()).Move(), prototypeDoc.Allocator());
			value.PushBack(rapidjson::Value(_pressedScale.GetZ()).Move(), prototypeDoc.Allocator());
			prototypeDoc.AddMember("B.PressedScale", value);

			value.SetString(rapidjson::StringRef(_pressedAudioFileName.c_str()));
			prototypeDoc.AddMember("B.PressedAudioFileName", value);
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

		value.SetArray();
		value.PushBack(rapidjson::Value(_normalScale.GetX()).Move(), allocator);
		value.PushBack(rapidjson::Value(_normalScale.GetY()).Move(), allocator);
		value.PushBack(rapidjson::Value(_normalScale.GetZ()).Move(), allocator);
		prototypeDoc.AddMember("B.NormalScale", value, allocator);

		value.SetBool(_haveHoverState);
		prototypeDoc.AddMember("B.HaveHoveredFile", value, allocator);

		if (_haveHoverState)
		{
			value.SetString(rapidjson::StringRef(_hoveredFileName.c_str()));
			prototypeDoc.AddMember("B.HoveredFileName", value, allocator);

			value.SetArray();
			value.PushBack(rapidjson::Value(_hoveredScale.GetX()).Move(), allocator);
			value.PushBack(rapidjson::Value(_hoveredScale.GetY()).Move(), allocator);
			value.PushBack(rapidjson::Value(_hoveredScale.GetZ()).Move(), allocator);
			prototypeDoc.AddMember("B.HoveredScale", value, allocator);

			value.SetString(rapidjson::StringRef(_hoveredAudioFileName.c_str()));
			prototypeDoc.AddMember("B.HoveredAudioFileName", value, allocator);
		}

		value.SetBool(_havePressState);
		prototypeDoc.AddMember("B.HavePressedFile", value, allocator);

		if (_havePressState)
		{
			value.SetString(rapidjson::StringRef(_pressedFileName.c_str()));
			prototypeDoc.AddMember("B.PressedFileName", value, allocator);

			value.SetArray();
			value.PushBack(rapidjson::Value(_pressedScale.GetX()).Move(), allocator);
			value.PushBack(rapidjson::Value(_pressedScale.GetY()).Move(), allocator);
			value.PushBack(rapidjson::Value(_pressedScale.GetZ()).Move(), allocator);
			prototypeDoc.AddMember("B.PressedScale", value, allocator);

			value.SetString(rapidjson::StringRef(_pressedAudioFileName.c_str()));
			prototypeDoc.AddMember("B.PressedAudioFileName", value, allocator);
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

		rapidjson::Value normalScale;
		rapidjson::Value hoveredScale;
		rapidjson::Value pressedScale;

		rapidjson::Value normalFileName;
		rapidjson::Value hoveredFileName;
		rapidjson::Value pressedFileName;

		rapidjson::Value hoveredAudioFileName;
		rapidjson::Value pressedAudioFileName;


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

		if (protoButtonCom->_normalScale != _normalScale)
		{
			normalScale.SetArray();
			addComponentIntoSceneFile = true;
			normalScale.PushBack(rapidjson::Value(_normalScale._x), allocator);
			normalScale.PushBack(rapidjson::Value(_normalScale._y), allocator);
			normalScale.PushBack(rapidjson::Value(_normalScale._z), allocator);
		}

		if (protoButtonCom->_haveHoverState != _haveHoverState)
		{
			addComponentIntoSceneFile = true;
			haveHoverState.SetBool(_haveHoverState);
		}

		if (_haveHoverState)
		{
			if (protoButtonCom->_hoveredFileName.compare(_hoveredFileName))
			{
				addComponentIntoSceneFile = true;
				hoveredFileName.SetString(rapidjson::StringRef(_hoveredFileName.c_str()));
			}

			if (protoButtonCom->_hoveredScale != _hoveredScale)
			{
				hoveredScale.SetArray();
				addComponentIntoSceneFile = true;
				hoveredScale.PushBack(rapidjson::Value(_hoveredScale._x), allocator);
				hoveredScale.PushBack(rapidjson::Value(_hoveredScale._y), allocator);
				hoveredScale.PushBack(rapidjson::Value(_hoveredScale._z), allocator);
			}

			if (protoButtonCom->_hoveredAudioFileName.compare(_hoveredAudioFileName))
			{
				addComponentIntoSceneFile = true;
				hoveredAudioFileName.SetString(rapidjson::StringRef(_hoveredAudioFileName.c_str()));
			}
		}

		if (protoButtonCom->_havePressState != _havePressState)
		{
			addComponentIntoSceneFile = true;
			havePressState.SetBool(_havePressState);
		}

		if (_havePressState)
		{
			if (protoButtonCom->_pressedFileName.compare(_pressedFileName))
			{
				addComponentIntoSceneFile = true;
				pressedFileName.SetString(rapidjson::StringRef(_pressedFileName.c_str()));
			}

			if (protoButtonCom->_pressedScale != _pressedScale)
			{
				pressedScale.SetArray();
				addComponentIntoSceneFile = true;
				pressedScale.PushBack(rapidjson::Value(_pressedScale._x), allocator);
				pressedScale.PushBack(rapidjson::Value(_pressedScale._y), allocator);
				pressedScale.PushBack(rapidjson::Value(_pressedScale._z), allocator);
			}

			if (protoButtonCom->_pressedAudioFileName.compare(_pressedAudioFileName))
			{
				addComponentIntoSceneFile = true;
				pressedAudioFileName.SetString(rapidjson::StringRef(_pressedAudioFileName.c_str()));
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

			if (!normalScale.IsNull())	//if rapidjson::value container is not empty
			{
				value.AddMember("B.NormalScale", normalScale, allocator);
			}

			if (!hoveredScale.IsNull())	//if rapidjson::value container is not empty
			{
				value.AddMember("B.HoveredScale", hoveredScale, allocator);
			}

			if (!pressedScale.IsNull())	//if rapidjson::value container is not empty
			{
				value.AddMember("B.PressedScale", pressedScale, allocator);
			}

			if (!pressedAudioFileName.IsNull())	//if rapidjson::value container is not empty
			{
				value.AddMember("B.HoveredAudioFileName", pressedAudioFileName, allocator);
			}

			if (!pressedAudioFileName.IsNull())	//if rapidjson::value container is not empty
			{
				value.AddMember("B.PressedAudioFileName", pressedAudioFileName, allocator);
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