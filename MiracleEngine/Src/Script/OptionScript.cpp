#include "PrecompiledHeaders.h"
#include "GameObject/Components/Logic/PrecompiledScriptType.h"
#include "OptionScript.h"
#include "Script/OptionScript.h"

OptionScript::OptionScript() :
	_currFullscreen{ false }, _newFullscreen{ false },
	Index{ 0 },
	_currMasterSound{ 0.f }, _newMasterSound{ 0.f },
	_currMusic{ 0.f }, _newMusic{ 0.f }, _adjustedMusic{ 0.f },
	_currSFX{ 0.f }, _newSFX{ 0.f }, _adjustedSFX{ 0.f }
{
}

OptionScript* OptionScript::Clone()
{
	return new OptionScript(*this);
}

void OptionScript::SetNewFullscreen()
{
	_newFullscreen = !_newFullscreen;
}
void OptionScript::IncreaseResolution()
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
	Index++;
	if (Index > _allResolution.size())
		Index = _allResolution.size(); // check if correct
}
void OptionScript::DecreaseResolution()
{
	Index--;
	if (Index < 0)
		Index = 0;
}
Vector3 OptionScript::DisplayNewResolution()
{
	// based on index, return the vector3 of the 
	return _allResolution[Index];
}
void OptionScript::IncreaseMasterSound()
{
	_newMasterSound += 0.1f;
	if (_newMasterSound > 1.0f)
		_newMasterSound = 1.0f;
}
void OptionScript::DecreaseMasterSound()
{
	_newMasterSound -= 0.1f;
	if (_newMasterSound < 0.0f)
		_newMasterSound = 0.0f;
}
void OptionScript::IncreaseMusic()
{
	_newMusic += 0.1f;
	if (_newMusic > 1.0f)
		_newMusic = 1.0f;
}
void OptionScript::DecreaseMusic()
{
	_newMusic -= 0.1f;
	if (_newMusic < 0.0f)
		_newMusic = 0.0f;
}
void OptionScript::IncreaseSFX()
{
	_newSFX += 0.1f;
	if (_newSFX > 1.0f)
		_newSFX = 1.0f;
}
void OptionScript::DecreaseSFX()
{
	_newSFX -= 0.1f;
	if (_newSFX < 0.0f)
		_newSFX = 0.0f;
}

void OptionScript::ApplySettings()
{
	// sets all new to current
	_currFullscreen = _newFullscreen;
	_currResolution = _allResolution[Index];
	_currMasterSound = _newMasterSound;
	_currMusic = _newMusic;
	_currSFX = _newSFX;
	// set adjusted Music & SFX
	_adjustedMusic = _newMusic * _newMasterSound;
	_adjustedSFX = _newSFX * _newMasterSound;

}

void OptionScript::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("ButtonType") && document["ButtonType"].IsInt())	//Checks if the variable exists in .Json file
		if (document.HasMember("currFullscreen") && document["currFullscreen"].IsBool())	//Checks if the variable exists in .Json file
		{
			_buttonType = (document["ButtonType"].IsInt());
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

void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator) {

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


void OptionScript::DiscardSettings()
{
	// sets all new to current
	_newFullscreen = _currFullscreen;
	_newResolution = _currResolution;
	_newMasterSound = _currMasterSound;
	_newMusic = _currMusic;
	_newSFX = _currSFX;
	//// set adjusted Music & SFX
	//_adjustedMusic = _newMusc * _newMasterSound;
	//_adjustedSFX = _newSFX * _newMasterSound;
}


void OptionScript::OnMouseDown()
{
	;
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

void OptionScript::Update(double dt)
{

}

void OptionScript::Init()
{
	_allResolution.push_back({ 1920, 1080, 1 });
}