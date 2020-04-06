#include "PrecompiledHeaders.h"
#include "OptionScript.h"

OptionScript::OptionScript() :
	_currFullscreen{ false }, _newFullscreen{ false },
	Index{ 0 },
	_currMasterSound{ 0 }, _newMasterSound{ 0 },
	_currMusic{ 0 }, _newMusic{ 0 },
	_currSFX{ 0 }, _newSFX{ 0 }
{
}

OptionScript* OptionScript::Clone()
{
	return new OptionScript(*this);
}

void OptionScript::SetNewFullscreen()
{
	if (DEBUGOUTPUT) std::cout << "SetFullscreen\n";
	_newFullscreen = !_newFullscreen;
	(_newFullscreen) ?
		_tickFullscreen->SetFileName("Tick.png") :
		_tickFullscreen->SetFileName("UnTick.png");
}
void OptionScript::IncreaseResolution()
{
	if (DEBUGOUTPUT) std::cout << "Res++\n";
	Index++;
	if (Index > _allResolution.size())
		Index = _allResolution.size();
}
void OptionScript::DecreaseResolution()
{
	if (DEBUGOUTPUT) std::cout << "Res--\n";
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
	if (DEBUGOUTPUT) std::cout << "Msound++\n";
	_newMasterSound += 1;
	if (_newMasterSound > 10)
		_newMasterSound = 10;
	_textMsound->SetFileName(IntToFileName(_newMasterSound));
}
void OptionScript::DecreaseMasterSound()
{
	if (DEBUGOUTPUT) std::cout << "Msound--\n";
	_newMasterSound -= 1;
	if (_newMasterSound < 0)
		_newMasterSound = 0;
	_textMsound->SetFileName(IntToFileName(_newMasterSound));
}
void OptionScript::IncreaseMusic()
{
	if (DEBUGOUTPUT) std::cout << "Mus++\n";
	_newMusic += 1;
	if (_newMusic > 10)
		_newMusic = 10;
	_textMus->SetFileName(IntToFileName(_newMusic));
}
void OptionScript::DecreaseMusic()
{
	if (DEBUGOUTPUT) std::cout << "Mus--\n";
	_newMusic -= 1;
	if (_newMusic < 0)
		_newMusic = 0;
	_textMus->SetFileName(IntToFileName(_newMusic));
}
void OptionScript::IncreaseSFX()
{
	if (DEBUGOUTPUT) std::cout << "Sfx++\n";
	_newSFX += 1;
	if (_newSFX > 10)
		_newSFX = 10;
	_textSfx->SetFileName(IntToFileName(_newSFX));
}
void OptionScript::DecreaseSFX()
{
	if (DEBUGOUTPUT) std::cout << "Sfx--\n";
	_newSFX -= 1;
	if (_newSFX < 0)
		_newSFX = 0;
	_textSfx->SetFileName(IntToFileName(_newSFX));
}

std::string OptionScript::IntToFileName(int i)
{
	switch (i)
	{
	case 0:
		return "0p.png";
	case 1:
		return "10p.png";
	case 2:
		return "20p.png";
	case 3:
		return "30p.png";
	case 4:
		return "40p.png";
	case 5:
		return "50p.png";
	case 6:
		return "60p.png";
	case 7:
		return "70p.png";
	case 8:
		return "80p.png";
	case 9:
		return "90p.png";
	case 10:
		return "100p.png";
	default:
		std::cout << "Impossibru O.o o.O \n";
		return "100p.png";
	}
}

void OptionScript::ApplySettings()
{
	// sets all new to current
	_currFullscreen = _newFullscreen;
	//_currResolution = _allResolution[Index]; // disabled as no assets for displaying resolution
	_currMasterSound = _newMasterSound;
	_currMusic = _newMusic;
	_currSFX = _newSFX;

	{
		std::string fileName = "./Resources/TextFiles/Window\\init.json";

		DeSerialiser document(fileName); //Create a deserialiser file

		rapidjson::Value value;

		value.SetBool(_currFullscreen);
		document.AddMember("currFullscreen", value);

		if (_currFullscreen)
			MyWindowsSystem.getWindow().SetFullscreenWindowMode();
		else
			MyWindowsSystem.getWindow().SetNonFullScreenWindowMode();


		value.SetArray();
		for (unsigned i = 0; i < 3; i++)
			value.PushBack(rapidjson::Value(_currResolution[i]).Move(), document.GetAllocator());
		document.AddMember("currResolution", value);


		value.SetFloat(_currMasterSound * 0.1f);
		document.AddMember("currMasterSound", value);

		value.SetFloat(_currMusic * 0.1f);
		document.AddMember("currMusic", value);

		value.SetFloat(_currSFX * 0.1f);
		document.AddMember("currSFX", value);

		MyAudioSystem.SetMasterVolume(_currMasterSound * 0.1f);
		MyAudioSystem.SetBGMVolume(_currMusic * 0.1f);
		MyAudioSystem.SetSFXVolume(_currSFX * 0.1f);


		document.ProduceJsonFile();
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

void OptionScript::SerialiseComponent(Serialiser & document)
{
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

void OptionScript::DeSerialiseComponent(rapidjson::Value & prototypeDoc, rapidjson::MemoryPoolAllocator<> & allocator)
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

void OptionScript::DeserialiseComponentSceneFile(IComponent * protoCom, rapidjson::Value & value, rapidjson::MemoryPoolAllocator<> & allocator)
{
	LogicComponent* protoLogicCom = dynamic_cast<LogicComponent*>(protoCom);

	size_t UId = protoLogicCom->GetScriptContianer()[_type];

	OptionScript* script = (OptionScript*)(MyLogicSystem.getScriptPtr(UId));

	if (!script)
	{
		DeSerialiseComponent(value, allocator);
		return;
	}

	rapidjson::Value currFullscreen;/*
	rapidjson::Value currResolution;*/
	rapidjson::Value currMasterSound;
	rapidjson::Value currMusic;
	rapidjson::Value currSFX;

	bool addComponentIntoSceneFile = false;

	if (script->_currFullscreen != _currFullscreen)
	{
		addComponentIntoSceneFile = true;
		currFullscreen.SetBool(_currFullscreen);
	}
	//if (script->_currResolution != _currResolution)
	//{
	//	addComponentIntoSceneFile = true;
	//	currResolution.SetArray();

	//	value.PushBack(rapidjson::Value(_currResolution[0]).Move(), allocator);
	//	value.PushBack(rapidjson::Value(_currResolution[1]).Move(), allocator);
	//	value.PushBack(rapidjson::Value(_currResolution[2]).Move(), allocator);
	//}
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
		//if (!currResolution.IsNull())
		//	value.AddMember("currResolution", currResolution, allocator);
		if (!currMasterSound.IsNull())
			value.AddMember("currMasterSound", currMasterSound, allocator);
		if (!currMusic.IsNull())
			value.AddMember("currMusic", currMusic, allocator);
		if (!currSFX.IsNull())
			value.AddMember("currSFX", currSFX, allocator);
	}
}




void OptionScript::Init()
{
	_allResolution.push_back({ 800, 600, 0 });
	_allResolution.push_back({ 1280, 720, 0 });
	_allResolution.push_back({ 1366, 768, 0 });
	_allResolution.push_back({ 1600, 900, 0 });
	_allResolution.push_back({ 1920, 1080, 0 });

	_currFullscreen = _newFullscreen = MyWindowsSystem.getWindow().GetFullscreen();
	_currResolution = _currResolution = { MyWindowsSystem.getWindow().GetWindowWidth(), MyWindowsSystem.getWindow().GetWindowHeight() };
	_currMusic = _newMusic = static_cast<int>(MyAudioSystem.BGMvolume * 10);
	_currSFX = _newSFX = static_cast<int>(MyAudioSystem.SFXvolume * 10);
	_currMasterSound  = _newMasterSound = static_cast<int>(MyAudioSystem.MasterVolume * 10);

	// get the 5 related graphic items
	for (auto itr : _engineSystems._factory->getObjectlist())
	{
		if (((IdentityComponent*)itr.second->GetComponent(ComponentId::CT_Identity))->ObjectType().compare("tickFullscreen") == 0)
			_tickFullscreen = GetComponentObject(itr.second, UI);
		if (((IdentityComponent*)itr.second->GetComponent(ComponentId::CT_Identity))->ObjectType().compare("textResolution") == 0)
			_textResolution = GetComponentObject(itr.second, UI);
		if (((IdentityComponent*)itr.second->GetComponent(ComponentId::CT_Identity))->ObjectType().compare("textMsound") == 0)
			_textMsound = GetComponentObject(itr.second, UI);
		if (((IdentityComponent*)itr.second->GetComponent(ComponentId::CT_Identity))->ObjectType().compare("textMus") == 0)
			_textMus = GetComponentObject(itr.second, UI);
		if (((IdentityComponent*)itr.second->GetComponent(ComponentId::CT_Identity))->ObjectType().compare("textSfx") == 0)
			_textSfx = GetComponentObject(itr.second, UI);
	}
	// set initial values to current values
	(_currFullscreen) ?
		_tickFullscreen->SetFileName("Tick.png") :
		_tickFullscreen->SetFileName("UnTick.png");
	_textMsound->SetFileName(IntToFileName(_currMasterSound));
	_textMus->SetFileName(IntToFileName(_currMusic));
	_textSfx->SetFileName(IntToFileName(_currSFX));
}

void OptionScript::Update(double dt)
{

}