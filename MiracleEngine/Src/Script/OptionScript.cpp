#include "PrecompiledHeaders.h"
#include "GameObject/Components/Logic/PrecompiledScriptType.h"
#include "OptionScript.h"

OptionScript::OptionScript() :
	_currFullscreen{ false }, _newFullscreen{ false },
	_currMasterSound{ 0.f }, _newMasterSound{ 0.f },
	_currMusic{ 0.f }, _newMusic{ 0.f }, _adjustedMusic{ 0.f },
	_currSFX{ 0.f }, _newSFX{ 0.f }, _adjustedSFX{ 0.f }
{
}













void OptionScript::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("currFullscreen") && document["currFullscreen"].IsBool())	//Checks if the variable exists in .Json file
	{
		_currFullscreen = (document["currFullscreen"].GetBool());
	}


	if (document.HasMember("currResolution") && document["currResolution"].IsArray())	//Checks if the variable exists in .Json file
	{
		_currResolution = { document["currResolution"][0].GetFloat(), document["currResolution"][1].GetFloat(), document["currResolution"][2].GetFloat() };
	}


	if (document.HasMember("currMasterSound") && document["currMasterSound"].IsFloat())	//Checks if the variable exists in .Json file
	{
		_currMasterSound = (document["currMasterSound"].GetFloat());
	}

	if (document.HasMember("currMusic") && document["currMusic"].IsFloat())	//Checks if the variable exists in .Json file
	{
		_currMusic = (document["currMusic"].GetFloat());
	}

	if (document.HasMember("currSFX") && document["currSFX"].IsFloat())	//Checks if the variable exists in .Json file
	{
		_currSFX = (document["currSFX"].GetFloat());
	}
}

void OptionScript::DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
{
	rapidjson::Value value;

	value.SetString(rapidjson::StringRef(ToScriptName(_type)));
	prototypeDoc.AddMember("Script2Id", value, allocator);

	value.SetBool(_currFullscreen);
	prototypeDoc.AddMember("currFullscreen", value, allocator);


	value.SetArray();
	for (unsigned i = 0; i < 3; i++)
		value.PushBack(rapidjson::Value(_currResolution[i]).Move(), allocator);
	prototypeDoc.AddMember("currResolution", value, allocator);


	value.SetFloat(_currMasterSound);
	prototypeDoc.AddMember("currMasterSound", value, allocator);

	value.SetFloat(_currMusic);
	prototypeDoc.AddMember("currMusic", value, allocator);

	value.SetFloat(_currSFX);
	prototypeDoc.AddMember("currSFX", value, allocator);

}

void OptionScript::DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
{
	LogicComponent* protoLogicCom = dynamic_cast<LogicComponent*>(protoCom);

	size_t UId = protoLogicCom->GetScriptContianer()[_type];

	OptionScript* script = (OptionScript*)(MyLogicSystem.getScriptPtr(UId));

	if (!script)
	{
		DeSerialiseComponent(value, allocator);
		return;
	}

	rapidjson::Value currFullscreen;
	rapidjson::Value currResolution;
	rapidjson::Value currMasterSound;
	rapidjson::Value currMusic;
	rapidjson::Value currSFX;

	bool addComponentIntoSceneFile = false;

	if (script->_currFullscreen != _currFullscreen)
	{
		addComponentIntoSceneFile = true;
		currFullscreen.SetBool(_currFullscreen);
	}
	if (script->_currResolution != _currResolution)
	{
		addComponentIntoSceneFile = true;
		currResolution.SetArray();

		value.PushBack(rapidjson::Value(_currResolution[0]).Move(), allocator);
		value.PushBack(rapidjson::Value(_currResolution[1]).Move(), allocator);
		value.PushBack(rapidjson::Value(_currResolution[2]).Move(), allocator);
	}
	if (script->_currMasterSound != _currMasterSound)
	{
		addComponentIntoSceneFile = true;
		currMasterSound.SetFloat(_currMasterSound);
	}

	if (script->_currMusic != _currMusic)
	{
		addComponentIntoSceneFile = true;
		currMusic.SetFloat(_currMusic);
	}

	if (script->_currSFX != _currSFX)
	{
		addComponentIntoSceneFile = true;
		currSFX.SetFloat(_currSFX);
	}



	if (addComponentIntoSceneFile)    //If anyone of component data of obj is different from Prototype
	{
		rapidjson::Value scriptName;

		scriptName.SetString(rapidjson::StringRef(ToScriptName(_type)));
		value.AddMember("Script2Id", scriptName, allocator);

		if (!currFullscreen.IsNull())
			value.AddMember("currFullscreen", currFullscreen, allocator);
		if (!currResolution.IsNull())
			value.AddMember("currResolution", currResolution, allocator);
		if (!currMasterSound.IsNull())
			value.AddMember("currMasterSound", currMasterSound, allocator);
		if (!currMusic.IsNull())
			value.AddMember("currMusic", currMusic, allocator);
		if (!currSFX.IsNull())
			value.AddMember("currSFX", currSFX, allocator);
	}
}


void OptionScript::OnMouseDown()
{
	switch (_buttonType)
	{
	case (int)ButtonType::NONE:
		break;
	case (int)ButtonType::PLAY:
		EngineSystems::GetInstance()._sceneManager->ChangeScene("Level1");
		break;
	case (int)ButtonType::PAUSE:

		break;
	case (int)ButtonType::QUIT:

		break;
	case (int)ButtonType::MENU:

		break;
	case (int)ButtonType::RESTART:

		break;
	default:
		break;
	}
}

void OptionScript::OnMouseEnter()
{
	;
}
void OptionScript::OnMouseOver()
{
	;
}
void OptionScript::OnMouseExit()
{
	;
}

void OptionScript::Update()
{

}

