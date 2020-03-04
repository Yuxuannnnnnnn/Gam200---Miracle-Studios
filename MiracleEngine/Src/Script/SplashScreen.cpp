#include "PrecompiledHeaders.h"
#include "SplashScreen.h"

void SplashScreen::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("SS.ScreenDuration") && document["SS.ScreenDuration"].IsDouble())
		_ScreenDuration = document["SS.ScreenDuration"].GetDouble();
}

void SplashScreen::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
}

void SplashScreen::DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
{
}

void SplashScreen::DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
{
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
