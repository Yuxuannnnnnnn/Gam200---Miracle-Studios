#pragma once
#include "PrecompiledHeaders.h"
#include "ButtonComponent.h"

ButtonComponent::ButtonComponent() :
	_transform{ nullptr },
	_graphic{ nullptr },
	_buttonUId{ 0 },
	_currState{ ButtonStates::NORMAL },
	_haveHoverState{ false },
	_havePressState{ false },
	_normalScale{ Vec3{1.f,1.f,1.f} },
	_hoveredScale{ Vec3{1.f,1.f,1.f} },
	_pressedScale{ Vec3{1.f,1.f,1.f} },
	_normalFileName{},
	_hoveredFileName{},
	_pressedFileName{},
	_hoveredAudioFileName{},
	_pressedAudioFileName{},
	_pressedAtStart{false}
{}

std::string ButtonComponent::ComponentName() const
{
	return std::string("Button Component");
}

void ButtonComponent::Init()
{
	_transform = (TransformComponent*)GetComponentMap(Transform)[GetParentId()];
	_graphic = (UIComponent*)GetComponentMap(UI)[this->GetParentId()];
}

void ButtonComponent::Inspect()
{
	IComponent::Inspect();
	ImGui::Spacing();

	ImGui::InputInt("Button ID", &_buttonUId);
	ImGui::Spacing();

	ImGui::NewLine();

	static auto& graphicList = MyResourceSystem.GetTexture2DList();
	std::vector<const char*> list(graphicList.size());

	static auto& AudioList = MyResourceSystem.GetSoundList();
	std::vector<const char*> soundlist(AudioList.size());

	//list[0] = "Choose a Texture ";

	int i = 0;
	int select1 = 0;
	int select2 = 0;
	int select3 = 0;

	int select4 = 0;
	int select5 = 0;

	for (auto& graphicPair = graphicList.begin(); graphicPair != graphicList.end(); graphicPair++)
	{
		const char* ptr = graphicPair->first.c_str();
		list[i] = ptr;

		if (!strncmp(ptr, _normalFileName.c_str(), 20))
			select1 = i;

		if (!strncmp(ptr, _normalFileName.c_str(), 20))
			select2 = i;

		if (!strncmp(ptr, _normalFileName.c_str(), 20))
			select3 = i;

		i++;
	}

	i = 0;
	for (auto& soundPair = AudioList.begin(); soundPair != AudioList.end(); soundPair++)
	{
		const char* ptr = soundPair->first.c_str();
		soundlist[i] = ptr;

		if (!strncmp(ptr, _hoveredAudioFileName.c_str(), 20))
			select4 = i;

		if (!strncmp(ptr, _pressedAudioFileName.c_str(), 20))
			select5 = i;
		i++;
	}


	static ComboFilterState s1 = { select1, 0 };
	static char buf1[128];
	static ImGuiFunctions function;
	static bool op = false;
	static bool* open = &op;

	if (_normalFileName.empty())
		strncpy(buf1, "type text here...", 18);
	else
		strncpy(buf1, _normalFileName.c_str(), _normalFileName.size());

	function.ComboFilter("Normal Texture", buf1, IM_ARRAYSIZE(buf1), list, (int)list.size(), s1, _normalFileName, open);
	ImGui::Spacing();

	ImGui::InputFloat2("Normal Scale X, Y", _normalScale.m);

	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Checkbox("Have Hovered State", &_haveHoverState);
	ImGui::Spacing();

	if (_haveHoverState)
	{
		static ComboFilterState s2 = { select2, 0 };
		static char buf2[128];

		if (_hoveredFileName.empty())
			strncpy(buf2, "type text here...", 18);
		else
			strncpy(buf2, _hoveredFileName.c_str(), _hoveredFileName.size());

		function.ComboFilter("Hovered Texture", buf2, IM_ARRAYSIZE(buf2), list, (int)list.size(), s2, _hoveredFileName, open);
		ImGui::Spacing();

		ImGui::InputFloat2("Hovered Scale X, Y", _hoveredScale.m);
		ImGui::Spacing();

		static ComboFilterState s4 = { select4, 0 };
		static char buf4[128];

		if (_hoveredAudioFileName.empty())
			strncpy(buf4, "type text here...", 18);
		else
			strncpy(buf4, _hoveredAudioFileName.c_str(), _hoveredAudioFileName.size());

		function.ComboFilter("Hovered Audio File", buf4, IM_ARRAYSIZE(buf4), soundlist, (int)soundlist.size(), s4, _hoveredAudioFileName, open);
		ImGui::Spacing();
	}

	
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Checkbox("Have Pressed State", &_havePressState);
	ImGui::Spacing();

	if (_havePressState)
	{
		static ComboFilterState s3 = { select3, 0 };
		static char buf3[128];

		if (_pressedFileName.empty())
			strncpy(buf3, "type text here...", 18);
		else
			strncpy(buf3, _pressedFileName.c_str(), _pressedFileName.size());

		function.ComboFilter("Pressed Texture", buf3, IM_ARRAYSIZE(buf3), list, (int)list.size(), s3, _pressedFileName, open);
		ImGui::Spacing();

		ImGui::InputFloat2("Pressed Scale X, Y", _pressedScale.m);
		ImGui::Spacing();

		static ComboFilterState s5 = { select5, 0 };
		static char buf5[128];

		if (_pressedAudioFileName.empty())
			strncpy(buf5, "type text here...", 18);
		else
			strncpy(buf5, _pressedAudioFileName.c_str(), _pressedAudioFileName.size());

		function.ComboFilter("Pressed Audio File", buf5, IM_ARRAYSIZE(buf5), soundlist, (int)soundlist.size(), s5, _pressedAudioFileName, open);
		ImGui::Spacing();
	}
}

///////////////////////////////////////////////////////////////////////////////
	// Function Setting and Getting only

size_t ButtonComponent::GetButtonUId()
{
	return (size_t)_buttonUId;
}

void ButtonComponent::ButtonNormalState()
{
	if (_currState == ButtonStates::NORMAL)
		return;

	_currState = ButtonStates::NORMAL;

	if (_graphic)
		_graphic->SetFileName(_normalFileName);

	if (_transform)
		_transform->SetScale(_normalScale);
}

void ButtonComponent::ButtonHoveredState()
{
	if (!_haveHoverState || _currState == ButtonStates::HOVERED)
		return;

	_currState = ButtonStates::HOVERED;

	if (_graphic)
		_graphic->SetFileName(_hoveredFileName);

	if (_transform)
		_transform->SetScale(_hoveredScale);

	MyAudioSystem.PlaySFX(_hoveredAudioFileName);
}

void ButtonComponent::ButtonPressedState()
{
	if (!_havePressState || _currState == ButtonStates::PRESSED)
		return;

	_currState = ButtonStates::PRESSED;

	if (_graphic)
		_graphic->SetFileName(_pressedFileName);

	if (_transform)
		_transform->SetScale(_pressedScale);
}


void ButtonComponent::SerialiseComponent(Serialiser& document) 
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


void ButtonComponent::DeSerialiseComponent(DeSerialiser& prototypeDoc) 
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

void ButtonComponent::DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
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

void ButtonComponent::DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
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