#include "PrecompiledHeaders.h"
#include "SplashScreen.h"

void SplashScreen::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("SS.ScreenDuration") && document["SS.ScreenDuration"].IsDouble())
		_ScreenDuration = document["SS.ScreenDuration"].GetDouble();
}

//function Not Needed for scripts
void SplashScreen::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
}

void SplashScreen::DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
{
	rapidjson::Value value;

	value.SetString(rapidjson::StringRef(ToScriptName(_type)));
	prototypeDoc.AddMember("Script2Id", value, allocator);

	value.SetDouble(_ScreenDuration);
	prototypeDoc.AddMember("SS.ScreenDuration", value, allocator);
}

void SplashScreen::DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
{

	LogicComponent* protoLogicCom = dynamic_cast<LogicComponent*>(protoCom);

	size_t UId = protoLogicCom->GetScriptContianer()[_type];

	SplashScreen* script = (SplashScreen*)(MyLogicSystem.getScriptPtr(UId));

	if (!script)
	{
		DeSerialiseComponent(value, allocator);
		return;
	}

	rapidjson::Value ScreenDuration;

	bool addComponentIntoSceneFile = false;

	if (script->_ScreenDuration != _ScreenDuration)
	{
		addComponentIntoSceneFile = true;
		ScreenDuration.SetDouble(_ScreenDuration);
	}

	if (addComponentIntoSceneFile)	//If anyone of component data of obj is different from Prototype
	{
		rapidjson::Value scriptName;

		scriptName.SetString(rapidjson::StringRef(ToScriptName(_type)));
		value.AddMember("Script2Id", scriptName, allocator);


		if (!ScreenDuration.IsNull())	//if rapidjson::value container is not empty
		{
			value.AddMember("SS.ScreenDuration", ScreenDuration, allocator);
		}
	}
}

void SplashScreen::Inspect()
{
}

SplashScreen::SplashScreen() : _init{ false }, _ScreenDuration{ 0.0 }, _timer{ 0.0 }, _once{ false }
{
}

SplashScreen* SplashScreen::Clone()
{
	return new SplashScreen(*this);
}

void SplashScreen::Init()
{
	_timer = _ScreenDuration;
	_once = false;
}

void SplashScreen::Update(double dt)
{
	if (!_init)
	{
		Init();
		_init = true;
	}

	if (_timer > 0)
		_timer -= dt;
	else if(!_once)
	{
		MyFactory.ChangeScene("MainMenu");
		_once = true;
	}
}
